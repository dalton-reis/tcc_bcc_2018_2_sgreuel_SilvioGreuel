<template>
  <v-layout column justify-center>
    <h1>Bluetooth</h1>
    <v-btn dark large @click="connectToDevice()">Connect</v-btn>

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
      messages: [],
      device: "",
      serviceUuid: 0xFFE0,
      characteristicUuid: 0xFFE1,
      receiveSeparator: "!",
      characteristic: ""
    }
  },
  computed: {
    bottonUpMessages: function() {
      return this.messages.slice().reverse()
    }
  },
  methods: {
    log: function(message) {
      alert(message)
    },
    receive:function(message)  {
      this.messages.push({
        order: this.messages.length + 1,
        data: message
      })
    },
    connectToDevice: function (device) {
      return (device ? Promise.resolve(device) : this.requestBluetoothDevice()).
          then((device) => this.connectDeviceAndCacheCharacteristic(device)).
          then((characteristic) => this.startNotifications(characteristic)).
          catch((error) => {
            this.log(error);
            return Promise.reject(error);
          });
    },

    disconnectFromDevice: function(device) {
      if (!device) {
        return;
      }

      this.log('Disconnecting from "' + device.name + '" bluetooth device...');

      device.removeEventListener('gattserverdisconnected',
          this.handleDisconnection.bind(this));

      if (!device.gatt.connected) {
        this.log('"' + device.name +
            '" bluetooth device is already disconnected');
        return;
      }

      device.gatt.disconnect();

      this.log('"' + device.name + '" bluetooth device disconnected');
    },

    requestBluetoothDevice: function() {
      this.log('Requesting bluetooth device...');

      return navigator.bluetooth.requestDevice({
        filters: [{services: [this.serviceUuid]}],
      }).then((device) => {
        this.log('"' + device.name + '" bluetooth device selected');

        this.device = device;
        this.device.addEventListener('gattserverdisconnected', this.handleDisconnection.bind(this));

        return this.device;
      });
    },

    connectDeviceAndCacheCharacteristic: function(device) {
      if (device.gatt.connected && this.characteristic) {
        return Promise.resolve(this.characteristic);
      }

      this.log('Connecting to GATT server...');

      return device.gatt.connect().
          then((server) => {
            this.log('GATT server connected', 'Getting service...');

            return server.getPrimaryService(this.serviceUuid);
          }).
          then((service) => {
            this.log('Service found', 'Getting characteristic...');

            return service.getCharacteristic(this.characteristicUuid);
          }).
          then((characteristic) => {
            this.log('Characteristic found');

            this.characteristic = characteristic; // Remember characteristic.

            return this.characteristic;
        });
    },

    startNotifications: function(characteristic) {
      this.log('Starting notifications...');

      return characteristic.startNotifications().
          then(() => {
            this.log('Notifications started');

            characteristic.addEventListener('characteristicvaluechanged',
                this.handleCharacteristicValueChanged.bind(this));
          });
    },

  
    stopNotifications: function(characteristic) {
      this.log('Stopping notifications...');

      return characteristic.stopNotifications().
          then(() => {
            this.log('Notifications stopped');

            characteristic.removeEventListener('characteristicvaluechanged',
                this.handleCharacteristicValueChanged.bind(this));
          });
    },

  
    handleDisconnection: function(event) {
      let device = event.target;

      this.log('"' + device.name +
          '" bluetooth device disconnected, trying to reconnect...');

      this.connectDeviceAndCacheCharacteristic(device).
          then((characteristic) => this.startNotifications(characteristic)).
          catch((error) => this.log(error));
    },

    handleCharacteristicValueChanged: function(event) {
      let value = new TextDecoder().decode(event.target.value);

      for (let c of value) {
        if (c === this.receiveSeparator) {
          let data = this.receiveBuffer.trim();
          this.receiveBuffer = '';

          if (data) {
            this.receive(data);
          }
        } else {
          this.receiveBuffer += c;
        }
      }
    },
    
  }
}
</script>
