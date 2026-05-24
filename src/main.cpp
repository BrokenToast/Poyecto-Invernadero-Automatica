#include <Arduino.h>
//#include "SensorSuelo.h"
#include "Datos.h"

// Select your modem:
#define TINY_GSM_MODEM_SIM800

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

#define SerialAT Serial2

// Define the serial console for debug prints, if needed
//#define TINY_GSM_DEBUG SerialMon

// Range to attempt to autobaud
// NOTE:  DO NOT AUTOBAUD in production code.  Once you've established
// communication, set a fixed baud rate using modem.setBaud(#).
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

// set GSM PIN, if any
#define GSM_PIN "0276"

// Your GPRS credentials, if any
const char apn[]      = "airtelwap.es";
const char gprsUser[] = "";
const char gprsPass[] = "";

// MQTT details
const char* broker = "luispatb.es";
const char* mqtt_user = "";
const char* mqtt_pass = "";

// Variables globales
const char* topic_potasio = "invernadero/potasio";
int valor_potasio;

const char* topic_fosforo = "invernadero/potasio";
int valor_fosforo;

const char* topic_nitrogeno = "invernadero/nitrogeno";
int valor_nitrogeno;

const char* topic_ph = "invernadero/ph";
int valor_ph;

const char* topic_temperatura_in= "invernadero/temperaturain";
int valor_temperatura_in;

const char* topic_temperatura_ex = "invernadero/temperaturaex";
int valor_temperatura_ex;

const char* topic_humedad_in= "invernadero/humedadin";
int valor_humedad_in;

const char* topic_humedad_ex = "invernadero/humedadex";
int valor_humedad_ex;

const char* info;

#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm        modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient  mqtt(client);

int ledStatus = LOW;

uint32_t lastReconnectAttempt = 0;

// void mqttCallback(char* topic, byte* payload, unsigned int len) {
//   SerialMon.print("Message arrived [");
//   SerialMon.print(topic);
//   SerialMon.print("]: ");
//   SerialMon.write(payload, len);
//   SerialMon.println();

//   // Only proceed if incoming message's topic matches
//   if (String(topic) == topicLed) {
//     ledStatus = !ledStatus;
//     digitalWrite(LED_PIN, ledStatus);
//     mqtt.publish(topicLedStatus, ledStatus ? "1" : "0");
//   }
// }

// boolean mqttConnect() {
//   SerialMon.print("Connecting to ");
//   SerialMon.print(broker);

//   // Connect to MQTT Broker
//   boolean status = mqtt.connect("GsmClientTest");

//   // Or, if you want to authenticate MQTT:
//   // boolean status = mqtt.connect("GsmClientName", "mqtt_user", "mqtt_pass");

//   if (status == false) {
//     SerialMon.println(" fail");
//     return false;
//   }
//   SerialMon.println(" success");
//   mqtt.publish(topicInit, "GsmClientTest started");
//   mqtt.subscribe(topicLed);
//   return mqtt.connected();
// }


void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT);

  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  // SerialAT.begin(9600);
  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  modem.restart();
  // modem.init();

  if (GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }

  if (!modem.waitForNetwork()) {
    info="Error al conectar a la red";
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected()) { SerialMon.println("Network connected"); }

  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected()) { SerialMon.println("GPRS connected"); }

  // MQTT Broker setup
  //mqtt.setServer(broker, 1883);
  //mqtt.setCallback(mqttCallback);
}

void loop() {
  // Make sure we're still registered on the network
//   if (!modem.isNetworkConnected()) {
//     SerialMon.println("Network disconnected");
//     if (!modem.waitForNetwork(180000L, true)) {
//       SerialMon.println(" fail");
//       delay(10000);
//       return;
//     }
//     if (modem.isNetworkConnected()) {
//       SerialMon.println("Network re-connected");
//     }

//     // and make sure GPRS/EPS is still connected
//     if (!modem.isGprsConnected()) {
//       SerialMon.println("GPRS disconnected!");
//       SerialMon.print(F("Connecting to "));
//       SerialMon.print(apn);
//       if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//         SerialMon.println(" fail");
//         delay(10000);
//         return;
//       }
//       if (modem.isGprsConnected()) { SerialMon.println("GPRS reconnected"); }
//     }
//   }

//   if (!mqtt.connected()) {
//     SerialMon.println("=== MQTT NOT CONNECTED ===");
//     // Reconnect every 10 seconds
//     uint32_t t = millis();
//     if (t - lastReconnectAttempt > 10000L) {
//       lastReconnectAttempt = t;
//       if (mqttConnect()) { lastReconnectAttempt = 0; }
//     }
//     delay(100);
//     return;
//   }

//   mqtt.loop();
}
