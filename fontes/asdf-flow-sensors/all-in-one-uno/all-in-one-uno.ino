#include <SoftwareSerial.h>
#include "DHT.h"

#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6 
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13

#define FIELD_TOKEN             "guid:token:00000000-0000-0000-0000-000000000000"
#define FIELD_DEVICE            "guid:device:22222222-2222-2222-2222-222222222222"

#define FIELD_COUNTER           "int:counter:"
#define FIELD_DHT11_TEMPERATURE "float:temperature:"
#define FIELD_DHT11_HUMIDITY    "float:humidity:"
#define FIELD_WATER             "float:water:"
#define FIELD_VIBRATION         "bool:vibration:"
#define FIELD_MOTION            "bool:motion:"
#define FIELD_LEVEL             "bool:level:"

#define END_OF_MESSAGE "!"
#define SEND_DELAY 1

#define ANALOG_PIN_IN_DHT11 A0
#define ANALOG_PIN_IN_WATER A1
#define DIGITAL_PIN_VIBRATION D7
#define DIGITAL_PIN_MOTION D8
#define DIGITAL_PIN_LEVEL D5

char g_valueBuffer[6];
static unsigned long g_loopCounter = 0;

#define DHT_PIN ANALOG_PIN_IN_DHT11 
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void delayInSeconds(int);
void incrementLoopCounter();

void espLoop(float, float, float, bool, bool, bool);
void printLoopCounter();
void printSensorValue(String, float);
void printSensorValue(String, bool);
void printEnd();

void bluetoothLoop(float, float, float, bool, bool, bool);
void printLoopCounterOnBluetooth();
void printSensorValueOnBluetooth(String, float);
void printSensorValueOnBluetooth(String, bool);
void printEndOnBluetooth();

//                        RX, TX
SoftwareSerial Bluetooth (10, 11);
void setup() {
	Serial.begin(115200);
	while(!Serial) { }
  Bluetooth.begin(9600);

  pinMode(ANALOG_PIN_IN_DHT11  , INPUT);
  pinMode(ANALOG_PIN_IN_WATER  , INPUT);  
  pinMode(DIGITAL_PIN_VIBRATION, INPUT);
  pinMode(DIGITAL_PIN_MOTION   , INPUT);
}

void loop () {
  incrementLoopCounter();
  
	float water       = analogRead(ANALOG_PIN_IN_WATER);
	float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();
  bool vibration    = digitalRead(DIGITAL_PIN_VIBRATION);
  bool motion       = digitalRead(DIGITAL_PIN_MOTION);
  bool level        = digitalRead(DIGITAL_PIN_LEVEL);

  bluetoothLoop(water, temperature, humidity, vibration, motion, level);
  espLoop(water, temperature, humidity, vibration, motion, level);
}

void espLoop(float water, float temperature, float humidity, bool vibration, bool motion, bool level) {
  int millsBetween = 500;
  // printHeaders();
  // printLoopCounter();
  // printEnd();
  // delay(millsBetween);

  // printHeaders();
  // printSensorValue(FIELD_LDR, ldr);
  // printEnd();
  // delay(millsBetween);

  printHeaders();
  printSensorValue(FIELD_DHT11_HUMIDITY, humidity);
  printEnd();
  delay(millsBetween);

  printHeaders();
  printSensorValue(FIELD_DHT11_TEMPERATURE, temperature);
  printEnd();
  delay(millsBetween);

  printHeaders();
  printSensorValue(FIELD_WATER, water);
  printEnd();
  delay(millsBetween);

  printHeaders();
  printSensorValue(FIELD_VIBRATION, vibration);
  printEnd();
  delay(millsBetween);

  printHeaders();
  printSensorValue(FIELD_MOTION, motion);
  printEnd();
  delay(millsBetween);

  printHeaders();
  printSensorValue(FIELD_LEVEL, level);
  printEnd();
  delay(millsBetween);
}

void bluetoothLoop(float water, float temperature, float humidity, bool vibration, bool motion, bool level) {
  printHeadersOnBluetooth();
  
  printLoopCounterOnBluetooth();
  
  printSensorValueOnBluetooth(FIELD_DHT11_HUMIDITY   , humidity);
  printSensorValueOnBluetooth(FIELD_DHT11_TEMPERATURE, temperature);
  printSensorValueOnBluetooth(FIELD_WATER            , water);
  printSensorValueOnBluetooth(FIELD_VIBRATION        , vibration);
  printSensorValueOnBluetooth(FIELD_MOTION           , motion);
  printSensorValueOnBluetooth(FIELD_LEVEL            , level);
  
  printEndOnBluetooth();
  //delayInSeconds(SEND_DELAY);
}

//Esp
void printHeaders() {
  //Serial.println(FIELD_DEVICE);
  Serial.println(FIELD_TOKEN);
}

void printLoopCounter() {
	Serial.println(String(g_loopCounter));
}


void printSensorValue(String description, float value) {
  Serial.print(description.c_str());
	dtostrf(value, 4, 2, g_valueBuffer);
	Serial.println(g_valueBuffer);	
}

void printSensorValue(String description, bool value) {
  Serial.print(description.c_str());
  if(value) {
    Serial.println("true");
  } else {
    Serial.println("false");
  }
}

void printEnd() {
  Serial.print("!");  
}


//Bluetooth
void printLoopCounterOnBluetooth() {
  Bluetooth.print(FIELD_COUNTER);
  Bluetooth.println(String(g_loopCounter));
}

void printHeadersOnBluetooth() {
  //Serial.println(FIELD_DEVICE);
  Bluetooth.println(FIELD_TOKEN);
}


void printSensorValueOnBluetooth(String description, float value) {
  Bluetooth.print(description.c_str());
  dtostrf(value, 4, 2, g_valueBuffer);
  Bluetooth.println(g_valueBuffer);  
}

void printSensorValueOnBluetooth(String description, bool value) {
  Bluetooth.print(description.c_str());
  if(value) {
    Bluetooth.println("true");
  } else {
    Bluetooth.println("false");
  }
}

void printEndOnBluetooth() {
  Bluetooth.print("!");  
}


void incrementLoopCounter() {
	g_loopCounter++;
}

void delayInSeconds(int seconds) {
	delay(seconds * 1000);
}
