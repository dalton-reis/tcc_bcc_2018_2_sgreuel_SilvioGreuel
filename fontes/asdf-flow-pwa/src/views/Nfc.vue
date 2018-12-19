<template>
  <v-layout column justify-center>
    <h1>NFC</h1>

    <v-btn dark large @click="read()">Read</v-btn>

    <div  v-for="record in records">
      <div>{{record.type}}</div>
      <pre>{{record.data}}</pre>
    </div>

    <v-flex xs12 v-for="message in bottonUpMessages">
      <v-card class="white--text">
        <v-card-title primary-title>
          <v-layout column justify-center>
          <div class="headline">{{message.order}}</div>
          <div>{{message.data}}</div>
          </v-layout>
        </v-card-title>
        <v-card-actions>
          <v-btn flat dark @click="write(message.data)">Write</v-btn>
        </v-card-actions>
      </v-card>
    </v-flex>

  </v-layout>
</template>

<script>

export default {
  mqtt: {
    '#': function(message) {
      this.messages.push({
        order: this.messages.length + 1,
        data: message.toString('utf8')
      })
    }
  },
  data ()  {
    return {
      messages: [],
      records: []
    }
  },
  computed: {
    bottonUpMessages: function() {
      return this.messages.slice().reverse()
    }
  },
  mounted () {
    this.subscribe()
  },
  methods: {
    subscribe: function() {
      this.$mqtt.subscribe('#')
    },
    write: function(message) {
      alert('Writing')
      navigator
        .nfc
        .push(message)
        .then(() => {
          alert("Message pushed.");
        })
        .catch((error) => {
          alert("Push failed :-( try again.");
        }); 
    },
    read: function() {
      alert('Reading')
      navigator
        .nfc
        .watch((message) => {
          alert('Message received')
          this.processMessage(message)
        })
        .then(() => alert("Added a watch."))
        .catch(err => alert("Adding watch failed: " + err.name))
    },
    processMessage: function(message) {
      this.records = []
      for (let record of message.records) {
        this.records.push({
          type: record.recordType,
          data: record.data
        })
      }
    }
  }
}
</script>

