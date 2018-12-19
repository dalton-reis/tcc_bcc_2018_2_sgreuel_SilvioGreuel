<template>
  <v-layout column justify-center>
    <h1>Account</h1>
    <v-text-field v-model="id" label="Id" box readonly></v-text-field>
    <v-text-field v-model="name" label="Name" box readonly></v-text-field>
    <v-text-field v-model="token" label="Token" box readonly></v-text-field>
    <v-select :items="devices" item-text="name" item-value="token" v-model="device" return-object></v-select>
    <v-btn dark large @click="start()">Start</v-btn>


    <v-flex xs12 v-for="message in bottonUpMessages">
      <v-card class="white--text">
        <v-card-title primary-title>
          <v-layout column justify-center>
          <div class="headline">{{message.order}}</div>
          <div>{{message.data}}</div>
          </v-layout>
        </v-card-title>
      </v-card>
    </v-flex>


  </v-layout>
</template>
<script>
import Vue from "vue"
import VueMqtt from 'vue-mqtt'
import { get } from "../utils/http"

export default {
  data () {
    return {
      id: "",
      name: "",
      token: "",
      started: false,
      messages: [],
      device: null,
      devices: []
    }
  },
  computed: {
    bottonUpMessages: function() {
      return this.messages.slice().reverse()
    }
  },
  mqtt: {
    '#': function(message) {
      this.messages.push({
        order: this.messages.length + 1,
        data: message.toString('utf8')
      })
    }
  },
  mounted () {
    this.load()
  },
  methods: {
    start: function () {
      if (this.started) { return; }
      if (this.device == null) { return; }

      this.started = true

      // const broker = 'wss://broker.greuel.com.br:15675/ws'
      const broker = 'wss://athletic-prawn.rmq.cloudamqp.com:443/ws/mqtt'
      Vue.use(VueMqtt, broker, {
        clientId: this.device.token,
        username: 'iot',
        password: 'iot'
      })

      this.subscribe()
    },
    subscribe: function ()  {
      if (!this.started) { return; }
      this.$mqtt.subscribe("#")
    },
    publish: function () {
      if (!this.started) { return; }
      this.$mqtt.publish("sensor", "hey")
    },
    load: function () {
      let self = this;
      get("/api/profile")
        .then(res => res.json())
        .then(json => {
          self.id = json.id
          self.name = json.name
          self.token = json.token
        })

      get(`/api/devices`)
        .then(res => res.json())
        .then(json => {
          this.devices = json.devices
        })
    }
  }
}
</script>
