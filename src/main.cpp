#include <Arduino.h>
#include "Datos.h"
#include "Actuaciones.h"
#include "Parametros.h"


#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm        modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient  mqtt(client);

/**
 * @brief Funcion que nos permite conectarnos al MQTT
 * 
 * @return boolean 
 */
boolean mqttConnect() {
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Or, if you want to authenticate MQTT:
  boolean status = mqtt.connect("esp32", mqtt_user, mqtt_pass);
  
  if (!status)
  {
    Serial.println("Error al conectar al mqtt");
  }else{
    Serial.println("Conectado al mqtt");
  }
  

  return mqtt.connected();
}
/**
 * @brief Nos permite enviar datos al servidor mqtt
 * 
 * @param topic 
 * @param datos 
 */
void mqttEnviar(const char* topic, String datos) {
  Serial.println(datos);
  char caracteres[30];
  datos.toCharArray(caracteres,15);
  Serial.println(caracteres);
  mqtt.publish(topic, caracteres);
}

/**
 * @brief Nos permite enviar un error al mqtt
 * 
 * @param error 
 */
void mqttError(const char* topic, String error) {
  char* caracteres;
  error.toCharArray(caracteres,15);
  mqtt.publish("invernadero/error",caracteres);
}

//Datos datos(18,19,1,22,23);
Datos datos(
  PIN_RX_SENSOR_SUELO,
  PIN_TX_SENSOR_SUELO,
  ID_SENSOR_SUELO,
  PIN_DATA_AM2301A_INTERNA,
  PIN_DATA_AM2301A_EXTERNA
);
//Actucaciones actuadores(32,33,25,26,14,12,21);
Actucaciones actuadores(
  PIN_STEP_VENTANA1,
  PIN_DIR_VENTANA1,
  PIN_STEP_VENTANA2,
  PIN_DIR_VENTANA2,
  PIN_STEP_PERISTALTICA,
  PIN_DIR_PERISTALTICA,
  PIN_BOMBA_AGUA
);
/**
 * @brief Función que nos permite actializar los datos y subir directamente al servidor mqtt
 * 
 */
void actualizarDatos(){
  datos.obtenerDatosSuelo();
  mqttEnviar("invernadero/nitrogeno",String(datos.getNitrogeno()));
  mqttEnviar("invernadero/potasio",String(datos.getPotasio()));
  mqttEnviar("invernadero/fosforo",String(datos.getFosforo()));
  mqttEnviar("invernadero/ph",String(datos.getPh()));
  mqttEnviar("invernadero/temperaturasuelo",String(datos.getTemperaturaSuelo()));
  mqttEnviar("invernadero/humedadsuelo",String(datos.getHumedadSuelo()));
  mqttEnviar("invernadero/temperaturain",String(datos.getTemperaturaInterna()));
  mqttEnviar("invernadero/humedadin",String(datos.getHumedadInterna()));
  mqttEnviar("invernadero/temperaturaex",String(datos.getTemperaturaExterna()));
  mqttEnviar("invernadero/humedadex",String(datos.getHumedadExterna()));
}
void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);
  Serial.println("Espere");
  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  delay(6000);

    // Restart takes quite some time
  // To skip it, call init() instead of restart()
  modem.restart();
  // modem.init();

  if (GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }

  if (!modem.waitForNetwork()) {
    Serial.println("Error al conectar a la red");
    delay(10000);
    return;
  }

  SerialMon.println(" success");
  delay(5000);

  if (modem.isNetworkConnected()) { SerialMon.println("Network connected"); }

  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  for (int i = 0; i < 3; i++)
  {
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" fail");
      delay(10000);
    }else{
      SerialMon.println(" success");
      break;
    }
  }

  if (modem.isGprsConnected()) { 
    SerialMon.println("GPRS connected");
  }

  Serial.println(modem.getLocalIP());

  // MQTT Broker setup
  mqtt.setServer(broker, port);

  mqttConnect();
}

void loop() {
  Serial.println("llegue");
  actualizarDatos();

  // if (datos.getHumedadSuelo()<MINIMA_HUMEDAD_SUELO)
  // {
  //   actuadores.riego(10000);
  //   actualizarDatos();
  // }

  // if (datos.getNitrogeno()<MINIMO_NITROGENO);
  // {
  //   actuadores.dosificacionNutrientes(40);
  //   actualizarDatos();
  // }
  // int temeperatura_interna=datos.getTemperaturaInterna();

  // if (temeperatura_interna > RANGO_TEMPERATURA_INTERNA_1 && temeperatura_interna < RANGO_TEMPERATURA_INTERNA_2)
  // {
  //   actuadores.abrirVentanas(25);
  // }else if(temeperatura_interna > RANGO_TEMPERATURA_INTERNA_2 && temeperatura_interna < RANGO_TEMPERATURA_INTERNA_3){
  //   actuadores.abrirVentanas(50);
  // }else if(temeperatura_interna > RANGO_TEMPERATURA_INTERNA_3 && temeperatura_interna < RANGO_TEMPERATURA_INTERNA_4){
  //   actuadores.abrirVentanas(75);
  // }else if(temeperatura_interna > RANGO_TEMPERATURA_INTERNA_4){
  //   actuadores.abrirVentanas(100);
  // }else{
  //   actuadores.cerrarVentanas();
  // }

  mqtt.loop();
  delay(1000);
}
