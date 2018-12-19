<template>

      <v-layout column align-center>
        <h1>Home</h1>
        <v-text-field v-model="user" label="User"></v-text-field >
        <v-text-field mask="####" v-model="pin" label="Pin"></v-text-field >
        <v-btn color="info" @click="login">Login with Pin</v-btn>
        <v-btn color="info" @click="twitter">Login with Twitter</v-btn>
        <v-btn color="error" @click="logout">Logout</v-btn>


        <v-snackbar
          v-model="errorSnackbar"
          :timeout="errorSnackbarTimeout"
        >
          {{errorSnackbarMessage}}
          <v-btn
            dark
            flat
            @click="snackbar = false"
          >
            Close
          </v-btn>
      </v-snackbar>
      </v-layout>
    
</template>
<script>
import { post } from '../utils/http'
import { setJwt } from '../utils/jwt'
export default {
  data () {
    return {
      user: null,
      pin: null,
      errorSnackbar: false,
      errorSnackbarMessage: '',
      errorSnackbarTimeout: 6000
    }
  },
  methods: {
    twitter: function() {
      window.open("https://localhost:44347/auth/signin/Twitter")
    },
    login: function() {
      post('/auth/authenticate', {
        user: this.user,
        pin: this.pin
      })
      .then(res => res.json())
      .then(json => {
        if (json.message) {
          console.log(json.message)
          throw new Error(json.message)
        }
        setJwt(json.jwtToken)
        this.$router.push({path: 'account'})
      })
      .catch(err => {
        this.errorSnackbarMessage = err.message
        this.errorSnackbar = true
      })
    },
    logout: function() {
      fetch("https://localhost:44347/auth/signout", {
        mode: "cors",
        method: "GET",
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json'
        },
        credentials: "include"
      })
      .then(res => res.json())
      .then(json => {console.log(json)})
    }
  }
}
</script>
