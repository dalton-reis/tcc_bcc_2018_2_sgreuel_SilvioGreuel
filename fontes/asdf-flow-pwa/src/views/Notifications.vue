<template>
  <v-layout column align-center>
    <h1>Local Notifications</h1>

    <v-text-field v-model="permission" label="Permission" box readonly></v-text-field>
    <v-text-field v-model="customMessage" label="Custom Message" box></v-text-field>
    <v-btn dark large @click="sendCustomMessage()">Send Custom Message</v-btn>

    <v-flex xs12 v-for="message in messages">
      <v-card class="white--text">
        <v-card-title primary-title>
          <v-layout column justify-center>
          <div>{{message}}</div>
          </v-layout>
        </v-card-title>
      </v-card>
    </v-flex>

  </v-layout>

</template>

<script>
export default {
  mqtt: {
    '#': function(val) {
      let message = val.toString('utf8').split(':')

      if (message.length == 3
       && message[0] == 'string'
       && message[1] == 'local'
       ) {
         this.notify(message[2])
      }
    }
  },
  data ()  {
    return {
      permission: 'not requested',
      customMessage: '',
      messages: []
    }
  },
  mounted () {
    this.subscribe()
  },
  methods: {
    subscribe: function ()  {
      this.$mqtt.subscribe("#")
    },
    sendCustomMessage: function() {
      this.notify(this.customMessage)
      this.customMessage = ''
    },
    notify: function(message) {
      Notification.requestPermission(permission => {
        this.permission = permission
        if (this.permission != 'granted') {return;} 
        
          this.messages.push(message)

          const options = {
            body: message,
            icon: 'img/icons/mstile-150x150.png',
            vibrate: [100, 50, 100],
            data: {
              dateOfArrival: Date.now(),
              primaryKey: 1
            },
          }
          navigator
            .serviceWorker
            .getRegistration()
            .then(reg => {
              reg.showNotification(message, options)
            })
        })
    }
  }
  
}
</script>

<style>

</style>
