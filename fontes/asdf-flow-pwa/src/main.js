import '@babel/polyfill'
import Vue from "vue";
// import VueMqtt from 'vue-mqtt'
import './plugins/vuetify'
import App from "./App.vue";
import router from "./router";
import store from "./store";
import "./registerServiceWorker";
import 'roboto-fontface/css/roboto/roboto-fontface.css'
import 'material-design-icons-iconfont/dist/material-design-icons.css'

Vue.config.productionTip = false;

// const broker = 'wss://athletic-prawn.rmq.cloudamqp.com:443/ws/mqtt'
// Vue.use(VueMqtt, broker, {
//   clientId: '0000',
//   username: 'iot',
//   password: 'iot'
// })

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount("#app");
