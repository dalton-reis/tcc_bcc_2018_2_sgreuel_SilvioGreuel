<template>
  <v-app dark>
    <v-navigation-drawer
      persistent
      :mini-variant="miniVariant"
      :clipped="clipped"
      v-model="drawer"
      enable-resize-watcher
      fixed
      app
    >

      <v-list
        dense
      >
        <template v-for="(item, i) in items">
          <v-layout
            v-if="item.heading"
            :key="i"
            row
            align-center
          >
            <v-flex xs6>
              <v-subheader v-if="item.heading">
                {{ item.heading }}
              </v-subheader>
            </v-flex>
            <v-flex xs6 class="text-xs-right">
              <v-btn small flat>edit</v-btn>
            </v-flex>
          </v-layout>
          <v-divider
            v-else-if="item.divider"
            :key="i"
            dark
            class="my-3"
          ></v-divider>
          <v-list-tile
            v-else
            :key="i"
            :to="item.link"
            :href="item.link"
          >
            <v-list-tile-action>
              <v-icon>{{ item.icon }}</v-icon>
            </v-list-tile-action>
            <v-list-tile-content>
              <v-list-tile-title>
                {{ item.title }}
              </v-list-tile-title>
            </v-list-tile-content>
          </v-list-tile>
        </template>
      </v-list>
    </v-navigation-drawer>

    <v-toolbar
      app
      :clipped-left="clipped"
    >
      <v-toolbar-side-icon @click.stop="drawer = !drawer"></v-toolbar-side-icon>
      <v-btn icon @click.stop="miniVariant = !miniVariant">
        <v-icon v-html="miniVariant ? 'chevron_right' : 'chevron_left'"></v-icon>
      </v-btn>

      <v-toolbar-title v-text="title"></v-toolbar-title>

      <v-spacer></v-spacer>

      <v-btn icon :to="home.link" :href="home.link">
        <v-icon>{{home.icon}}</v-icon>
      </v-btn>
    </v-toolbar>

    <v-content>
      <v-container fluid>
        <v-slide-y-transition mode="out-in">
          <router-view/>
        </v-slide-y-transition>
      </v-container>
    </v-content>

    <v-footer :fixed="fixed" app>
      <span>&copy;Asdf Flow 2018</span>
    </v-footer>
  </v-app>
</template>

<script>

export default {
  name: 'App',
  data () {
    return {
      clipped: false,
      drawer: false,
      fixed: false,
      home: {
        icon: 'home',
        title: 'Home',
        link: '/'
      },
      items: [
      {
        icon: 'account_circle',
        title: 'Account',
        link: '/account'
      },
      {
        icon: 'devices',
        title: 'Devices',
        link: '/devices'
      },
      {
        icon: 'call_split',
        title: 'Flows',
        link: '/flows'
      },
      {
        icon: 'radio_button_checked',
        title: 'Buttons',
        link: '/buttons'
      },
      {
        icon: 'bluetooth',
        title: 'MQTT',
        link: '/mqtt'
      },
      {
        divider: true
      },
      {
        icon: 'bluetooth',
        title: 'Bluetooth',
        link: '/bluetooth'
      },
      {
        icon: 'nfc',
        title: 'NFC',
        link: '/nfc'
      },
      {
        icon: 'notifications',
        title: 'Local Notifications',
        link: '/notifications'
      },
      {
        icon: 'vibration',
        title: 'Vibration',
        link: '/vibrations'
      }],
      //{
      //  icon: 'tap_and_play',
      //  title: 'Push Notifications',
      //  link: '/push'
      //}],
      miniVariant: false,
      right: true,
      rightDrawer: false,
      title: 'Asdf Flow'
    }
  }
}
</script>
