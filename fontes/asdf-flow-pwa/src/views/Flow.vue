<template>
  <v-container
        fluid
        grid-list-lg
      >
        <v-layout row wrap>
          <h1>{{flow.name}} ({{flow.id}})</h1>

          <v-flex xs12  v-if="trigger == null">
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                  <div class="headline">Select a trigger</div>
                  <v-select :items="triggers" label="Triggers" v-model="triggerType"></v-select>
                  <v-text-field label="Name" v-model="triggerName"></v-text-field>
                  <v-text-field label="Topic" v-model="triggerTopic" v-if="triggerType == 'MQTT'"></v-text-field>
                </v-layout>
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="addTrigger()">Register</v-btn>
              </v-card-actions>
            </v-card>
          </v-flex>

          <v-flex xs12 v-for="node in nodes">
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                <div class="headline">{{node.id}} - {{node.name}}</div>
                <div>
                  <div v-if="node.context">
                    <pre>{{JSON.stringify(node.context, ' ', 2)}}</pre>
                  </div>
                  <div v-if="node.type">type: {{node.type}}</div>
                  <div v-if="node.url">url: {{node.url}}</div>
                  <div v-if="node.field">field: {{node.field}}</div>
                  <div v-if="node.key">key: {{node.key}}</div>
                  <div v-if="node.value">value: {{node.value}}</div>
                  <div v-if="node.content">content: {{node.content}}</div>
                  <div v-if="node.contentType">contentType: {{node.contentType}}</div>
                  <div v-if="node.left">left: {{node.left}}</div>
                  <div v-if="operationName(node.operation)">operation: {{operationName(node.operation)}}</div>
                  <div v-if="node.right">right: {{node.right}}</div>
                  <div v-if="node.device">device: {{deviceName(node.device)}}</div>
                </div>
                </v-layout>
              </v-card-title>
            </v-card>
          </v-flex>

          <v-flex xs12 v-if="nodes.length > 0">
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                <div class="headline">Add new step</div>
                <v-select :items="templates" item-text="name" label="Steps" v-model="nextNodeTemplate" return-object></v-select>
                <v-text-field v-for="field in fields" :label="field.name" v-model="field.value" v-if="field.type == 'System.String' && field.name != 'Type'"></v-text-field> 
                <v-select :items="decisions" v-for="field in fields" :label="field.name" v-model="field.value" v-if="field.type == 'Asdf.Domain.Actions.OperationType'"></v-select>
                <v-select :items="gpios" v-for="field in fields" :label="field.name" v-model="field.value" v-if="field.type == 'Asdf.Domain.Actions.GpioStatusType'"></v-select>
                <v-select :items="devices" item-text="name" item-value="token" v-for="field in fields" :label="field.name" v-model="field.value" v-if="field.type == 'System.Guid'"></v-select>
                <v-select :items="types" item-text="text" item-value="value" v-for="field in fields" :label="field.name" v-model="field.value" v-if="field.name == 'Type'"></v-select>
                </v-layout>
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="addRoot()"  v-if="nodes.length == 1">Add</v-btn>
                <v-btn flat dark @click="addPass()" v-if="nodes.length > 1">Pass</v-btn>
                <v-btn flat dark @click="addFail()" v-if="nodes.length > 1">Fail</v-btn>
              </v-card-actions>
            </v-card>
          </v-flex>

        </v-layout>
      </v-container>

</template>
<script>
import { post, get, del } from "../utils/http"

export default {
  data () {
    return {
      triggers: [],
      triggerType: "",
      triggerName: "",
      triggerTopic: "",
      trigger: null,
      nextNodeTemplate: null,
      flow: null, 
      nodes: [],
      templates: [],
      decisions: [
        { text: 'Equal', value : 0 },
        { text: 'Not Equal', value : 1 },
        { text: 'Greater Than', value : 2 },
        { text: 'Greater Than Or Equal', value : 3 },
        { text: 'Less Than', value : 4 },
        { text: 'Less Than Or Equal', value : 5 }
      ],
      gpios: [
        { text: 'Toggle', value : 0 },
        { text: 'Low', value : 1 },
        { text: 'High', value : 2 }
      ],
      types: [
        { text: 'String' , value: 'string'  },
        { text: 'Boolean', value: 'bool' },
        { text: 'Int'    , value: 'int' },
        { text: 'Float'  , value: 'float'},
        { text: 'Double' , value: 'double' },
        { text: 'Guid'   , value: 'guid' }
      ],
      devices: []
    }
  },
  computed: {
    fields: vm => {
      if (!vm.nextNodeTemplate)
        return []
      return vm.nextNodeTemplate.fields
    },
    lastNode: vm => {
      return vm.nodes[vm.nodes.length - 1]
    }
  },
  mounted () {
    this.clear()
    this.load()
  },
  methods: {
    operationName: function(val) {
      let decisions = this.decisions.filter(decision => decision.value == val)
      if (decisions.length <= 0) { return '' }
      return decisions[0].text
    },
    deviceName: function(val) {
      let devices = this.devices.filter(device => device.token == val)
      if (devices.length <= 0) { return '' }
      return devices[0].name
    },
    addTrigger: function () {
      post("/api/flows/add-trigger", {
          flowId: this.$route.params.id,
          triggerTopic: this.triggerTopic ,
          triggerName: this.triggerName,
          triggerType: this.triggerType
        })
        .then(() => {this.clear()})
        .then(() => {this.load()})
    },
    addRoot: function () {
      post("/api/flows/add-root", {
          nodeId: this.trigger.id ,
          node: this.nextNodeTemplate,
        })
        .then(() => {this.clear()})
        .then(() => {this.load()})
    },
    addPass: function () {
      post("/api/flows/add-pass", {
          nodeId: this.lastNode.id ,
          node: this.nextNodeTemplate,
        })
        .then(() => {this.clear()})
        .then(() => {this.load()})
    },
    addFail: function () {
      post("/api/flows/add-fail", {
          nodeId: this.lastNode.id ,
          node: this.nextNodeTemplate,
        })
        .then(() => {this.clear()})
        .then(() => {this.load()})
    },
    edit: function (id) {
      this.$router.push({path: `/flow/${id}`})
    },
    del: function (id) {
      del(`/api/flows/${id}`)
        .then(() => {this.load()})
    },
    clear: function () {
      this.name = ""
      this.nextNodeTemplate = null
    },
    load: function () {
      const flowId = this.$route.params.id;

      get("/api/triggers")
        .then(res => res.json())
        .then(json => {
          this.triggers = json.triggers
        })

      get(`/api/flows/${flowId}`)
        .then(res => res.json())
        .then(json => {
          this.flow = json.flow
          this.trigger = json.flow.trigger 
        })
        .then(() => {this.loadNodes()})

      get(`/api/templates`)
        .then(res => res.json())
        .then(json => {
          this.templates = json.templates
        })
      
      get(`/api/devices`)
        .then(res => res.json())
        .then(json => {
          this.devices = json.devices
        })
    },
    loadNodes: function () {
      if (this.trigger == null) {
        this.nodes = []
        return
      }

      let nodes = []
      nodes.push(this.trigger)

      let root = this.trigger.root

      let fail = null;
      let pass = null;

      while (root != null)
      {
        nodes.push(root)
        fail = root.fail
        pass = root.pass
        root = fail || pass
      }

      this.nodes = nodes;
    }
  }
}
</script>

