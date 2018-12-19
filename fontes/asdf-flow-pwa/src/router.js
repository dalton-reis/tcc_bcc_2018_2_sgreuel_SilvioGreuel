import Vue from "vue";
import Router from "vue-router";
import Home from "./views/Home.vue";
import Account from "./views/Account.vue";
import Devices from "./views/Devices.vue";
import Flows from "./views/Flows.vue";
import Flow from "./views/Flow.vue";
import Buttons from "./views/Buttons.vue";
import Mqtt from "./views/Mqtt.vue";
import Bluetooth from "./views/Bluetooth.vue";
import Nfc from "./views/Nfc.vue";
import Notifications from "./views/Notifications.vue";
import Vibrations from "./views/Vibration.vue";
import Push from "./views/Push.vue";

Vue.use(Router);

export default new Router({
  mode: "history",
  base: process.env.BASE_URL,
  routes: [
    {
      path: "/",
      name: "home",
      component: Home
    },
    {
      path: "/account",
      name: "account",
      component: Account
    },
    {
      path: "/devices",
      name: "devices",
      component: Devices
    },
    {
      component: Flows,
      name: "flows",
      path: "/flows"
    },
    {
      component: Flow,
      name: "flow",
      path: "/flows/:id"
    },
    {
      component: Buttons,
      name: "buttons",
      path: "/buttons"
    },
    {
      component: Mqtt,
      name: "mqtt",
      path: "/mqtt"
    },
    {
      component: Bluetooth,
      name: "bluetooth",
      path: "/bluetooth"
    },
    {
      component: Nfc,
      name: "nfc",
      path: "/nfc"
    },
    {
      component: Notifications,
      name: "notifications",
      path: "/notifications"
    },
    {
      component: Vibrations,
      name: "vibrations",
      path: "/vibrations"
    },
    {
      component: Push,
      name: "push",
      path: "/push"
    }
  ]
});
