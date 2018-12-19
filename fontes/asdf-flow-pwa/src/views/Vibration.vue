<template>
  <v-layout column align-center>
    <h1>Local Notifications</h1>

    <v-text-field v-model="theme" label="Theme" box readonly></v-text-field>
    <v-text-field v-model="duration" label="Duration" box readonly></v-text-field>
    <v-btn dark large @click="vibrateTheme('mario')">Super Mario</v-btn>
    <v-btn dark large @click="vibrateTheme('tmnt')">Teenage Mutant Ninja Turtles</v-btn>
    <v-btn dark large @click="vibrateTheme('voltron')">Voltron</v-btn>
    <v-btn dark large @click="vibrateTheme('ff')">Final Fantasy</v-btn>
    <v-btn dark large @click="vibrateTheme('imperial')">Imperial March</v-btn>
    <v-btn dark large @click="vibrateTheme('power')">Power Rangers</v-btn>
    <v-btn dark large @click="vibrateTheme('sos')">S.O.S</v-btn>
    <v-btn dark large @click="vibrateTheme('mk')">Mortal Kombat</v-btn>
    <v-btn dark large @click="vibrateTheme('bond')">James Bond</v-btn>
  </v-layout>
</template>

<script>
export default {
  mqtt: {
    '#': function(val) {
      let message = val.toString('utf8').split(':')

      if (message.length == 3
       && message[0] == 'int'
       && message[1] == 'vibration'
       ) {
         this.vibrateTime(message[2])
      }

      if (message.length == 3
       && message[0] == 'string'
       && message[1] == 'vibration'
       ) {
         this.vibrateTheme(message[2])
      }
    }
  },
  data ()  {
    return {
      themes: {
        mario: [250,200,150,150,100,50,450,450,150,150,100,50,900,2250],
        tmnt: [75,75,75,75,75,75,75,75,150,150,150,450,75,75,75,75,75,525],
        voltron: [250,200,150,150,100,50,450,450,150,150,100,50,900,2250],
        ff: [50,100,50,100,50,100,400,100,300,100,350,50,200,100,100,50,600],
        imperial: [500,110,500,110,450,110,200,110,170,40,450,110,200,110,170,40,500],
        power: [150,150,150,150,75,75,150,150,150,150,450],
        sos: [100,30,100,30,100,200,200,30,200,30,200,200,100,30,100,30,100],
        mk: [100,200,100,200,100,200,100,200,100,100,100,100,100,200,100,200,100,200,100,200,100,100,100,100,100,200,100,200,100,200,100,200,100,100,100,100,100,100,100,100,100,100,50,50,100,800],
        bond: [0,300,100,50,100,50,100,50,100,50,100,50,100,50,150,150,150,450,100,50,100,50,150,150,150,450,100,50,100,50,150,150,150,450,150,150]
      },
      theme: '',
      duration: 0
    }
  },
  mounted () {
    this.subscribe()
  },
  methods: {
    subscribe: function ()  {
      this.$mqtt.subscribe("#")
    },
    vibrateTheme: function(theme) {
      this.theme = theme;
      let tempo = this.themes[theme];
      if (tempo) {
        this.theme = theme;
        this.duration = tempo.reduce((a, v) => a + v, 0);

        setTimeout(() => {
          this.theme = "";
          this.duration = 0;
        }, this.duration);

        this.vibrate(tempo);
      }
    },
    vibrate: function(tempo) {
      navigator.vibrate(tempo);
    }
  }
};
</script>
