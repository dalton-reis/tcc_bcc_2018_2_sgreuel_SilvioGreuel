<template>
  <v-container
        fluid
        grid-list-lg
      >
        <v-layout row wrap>
          <h1>Buttons</h1>

          <v-flex xs12 v-for="button in buttons">
            <v-card class="white--text">
              <v-card-title primary-title>
                <v-layout column justify-center>
                  <div class="headline">{{button.name}}</div>
                </v-layout>
              </v-card-title>
              <v-card-actions>
                <v-btn flat dark @click="trigger(button.id)">Trigger</v-btn>
              </v-card-actions>
            </v-card>
          </v-flex>

        </v-layout>
      </v-container>

</template>
<script>
import { get } from "../utils/http"

export default {
  data () {
    return {
      buttons: []
    }
  },
  mounted () {
    this.load()
  },
  methods: {
    trigger: function (id) {
      get(`/api/buttons/${id}/trigger`)
        .then(res => res.text())
        .then(text=> { console.log(text) })
        .catch(err => { alert('Unable to trigger button') })
    },
    load: function () {
      get("/api/buttons")
        .then(res => res.json())
        .then(json => {
          this.buttons = json.buttons
        })
    }
  }
}
</script>
