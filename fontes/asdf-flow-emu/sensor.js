const mqtt = require('mqtt')
// const broker = 'mqtt://greuel.com.br:1883'
const broker = 'mqtt://athletic-prawn.rmq.cloudamqp.com:1883'
const client  = mqtt.connect(broker ,
{
    username: 'iot',
    password: 'iot',
    clientId: '1ca68d4d-5a31-4940-8f74-3a67636adc31'
})

const rand = (max, min) => Math.random() * (max - min) + min;
 
client.on('connect', function () {
    console.log('connect')
    sub(client)
    pub(client)
})

const pub = (client) => {
    setInterval(() => {
        const metric = `guid:token:f146dae9-56a5-4c9a-8fe6-13b7e955b1cc
guid:device:1ca68d4d-5a31-4940-8f74-3a67636adc31
double:celsius:${rand(20, 45)}
double:humidity:${rand(50, 65)}`
        console.log(metric)
        client.publish('sensor/telemetry', metric)
    }, 1000)
}

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

client.on('error', function (err) {
    console.log('error:', err)
})

client.on('reconnect', function (rec) {
    console.log('reconnect:', rec)
})