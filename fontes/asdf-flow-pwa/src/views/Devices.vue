<template>
  <v-container
        fluid
        grid-list-lg
      >
        <v-layout row wrap>
          <h1>Devices</h1>

          <v-flex xs12>
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                <div class="headline">New Device</div>
                  <v-text-field label="Name" v-model="name"></v-text-field>
                </v-layout>
                
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="add()">Register</v-btn>
              </v-card-actions>
            </v-card>
          </v-flex>

          <v-flex xs12 v-for="device in devices">
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                <div class="headline">{{device.name}}</div>
                  <v-text-field label="Token" v-model="device.token" readonly=""></v-text-field>
                </v-layout>
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="del(device.id)">Delete</v-btn>
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
      devices: []
    }
  },
  mounted () {
    this.clear()
    this.load()
  },
  methods: {
    add: function () {
      post("/api/devices", {name: this.name})
        .then(() => {this.clear()})
        .then(() => {this.load()})
    },
    del: function (id) {
      del(`/api/devices/${id}`)
        .then(() => {this.load()})
    },
    clear: function () {
      this.name = ""
    },
    load: function () {
      get("/api/devices")
        .then(res => res.json())
        .then(json => {
          this.devices = json.devices
        })
    }
  }
}
</script>
