const mqtt = require('mqtt')
// const broker ='mqtt://greuel.com.br:1883'
const broker = 'mqtt:///athletic-prawn.rmq.cloudamqp.com:1883'
const client  = mqtt.connect(broker,
{
    username: 'iot',
    password: 'iot',
    clientId: '6ec5ecfd-d0c2-4848-8115-64d78d59c49a',
    protocol: 'MQIsdp'
})

const rand = (max, min) => Math.random() * (max - min) + min;
 
client.on('connect', function () {
    sub(client)
})

const sub = (client) => {
    client.subscribe('switch');
}

client.on('message', function (topic, message) {
  message =  message.toString('utf8')
  message =  message.split('=')
  message = {
      [message[0]]: message[1]
  }
  console.log(message)
})
