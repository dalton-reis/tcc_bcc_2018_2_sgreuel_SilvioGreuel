<template>
  <v-container
        fluid
        grid-list-lg
      >
        <v-layout row wrap>
          <h1>Flows</h1>

          <v-flex xs12>
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                <div class="headline">New Flow</div>
                  <v-text-field label="Name" v-model="name"></v-text-field>
                </v-layout>
                
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="add()">Register</v-btn>
              </v-card-actions>
            </v-card>
          </v-flex>

          <v-flex xs12 v-for="flow in flows">
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                <div class="headline">{{flow.name}}</div>
                </v-layout>
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="del(flow.id)">Delete</v-btn>
                <v-btn flat dark @click="edit(flow.id)">Edit</v-btn>
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
      name: "",
      flows: []
    }
  },
  mounted () {
    this.clear()
    this.load()
  },
  methods: {
    add: function () {
      post("/api/flows", {name: this.name})
        .then(() => {this.clear()})
        .then(() => {this.load()})
    },
    edit: function (id) {
      this.$router.push({path: `/flows/${id}`})
    },
    del: function (id) {
      del(`/api/flows/${id}`)
        .then(() => {this.load()})
    },
    clear: function () {
      this.name = ""
    },
    load: function () {
      get("/api/flows")
        .then(res => res.json())
        .then(json => {
          this.flows = json.flows
        })
    }
  }
}
</script>

