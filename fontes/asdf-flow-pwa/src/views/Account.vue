<template>
  <v-layout column justify-center>
    <h1>Account</h1>
    <v-text-field v-model="id" label="Id" box readonly></v-text-field>
    <v-text-field v-model="name" label="Name" box readonly></v-text-field>
    <v-text-field v-model="token" label="Token" box readonly></v-text-field>
  </v-layout>
</template>
<script>

import { get } from "../utils/http"
export default {
  data () {
    return {
      id: "",
      name: "",
      token: "" 
    }
  },
  mounted () {
    this.load()
  },
  methods: {
    load: function () {
      let self = this;
      get("/api/profile")
        .then(res => res.json())
        .then(json => {
          self.id = json.id
          self.name = json.name
          self.token = json.token
        })
    }
  }
}
</script>
