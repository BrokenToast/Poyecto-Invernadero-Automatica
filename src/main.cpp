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
  //SerialMon.print("Connecting to ");
  //SerialMon.print(broker);
  //pantallaInfo("Conectando al MQTT");

  // Or, if you want to authenticate MQTT:
  boolean status = mqtt.connect("esp32", mqtt_user, mqtt_pass);
  
  if (!status)
  {
    //Serial.println("Error al conectar al mqtt");
    //pantallaInfo("Error mqtt");
  }else{
    //Serial.println("Conectado al mqtt");
    //pantallaInfo("Conectado al mqtt");
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
  //Serial.println(datos);
  char caracteres[30];
  datos.toCharArray(caracteres,15);
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
/**
 * @brief Metodo que nos permite enviar datos a la pantalla
 * 
 * @param datos 
 */
void pantallaDatos(Datos datos){

}


Datos datos(
  PIN_RX_SENSOR_SUELO,
  PIN_TX_SENSOR_SUELO,
  ID_SENSOR_SUELO,
  PIN_DATA_AM2301A_INTERNA,
  PIN_DATA_AM2301A_EXTERNA
);

Actucaciones actuadores(
  PIN_STEP_VENTANA1,
  PIN_DIR_VENTANA1,
  PIN_STEP_VENTANA2,
  PIN_DIR_VENTANA2,
  PIN_STEP_PERISTALTICA,
  PIN_DIR_PERISTALTICA,
  PIN_BOMBA_AGUA, 
  PASO_VENTANA_100
);
/**
 * @brief Función que nos permite actializar los datos y subir directamente al servidor mqtt
 * 
 */
void actualizarDatos(){
  if (!mqtt.connected())
  {
    mqttConnect();
  } 
  
  char valor[30];
  datos.obtenerDatosSuelo();
  if (datos.getHumedadSuelo()>50)
  {
    //Serial.println(datos.getNitrogeno());
    sprintf(valor,"%i mg/kg",datos.getNitrogeno());
    mqttEnviar("invernadero/nitrogeno",valor);
    //Serial.println(datos.getPotasio());
    sprintf(valor,"%i mg/kg",datos.getPotasio());
    mqttEnviar("invernadero/potasio",valor);
    //Serial.println(datos.getFosforo());
    sprintf(valor,"%i mg/kg",datos.getFosforo());
    mqttEnviar("invernadero/fosforo",valor);
    //Serial.println(datos.getPh());
    mqttEnviar("invernadero/ph",String(datos.getPh()));
  }
  //Serial.println(datos.getTemperaturaSuelo());
  sprintf(valor,"%f ºC",datos.getTemperaturaSuelo());
  mqttEnviar("invernadero/temperaturasuelo",valor);
  //Serial.println(datos.getHumedadSuelo());
  sprintf(valor,"%i \%",datos.getHumedadSuelo());
  mqttEnviar("invernadero/humedadsuelo",valor);
  //Serial.println(datos.getTemperaturaInterna());
  sprintf(valor,"%i ºC",datos.getTemperaturaInterna());
  mqttEnviar("invernadero/temperaturain",valor);
  //Serial.println(datos.getHumedadInterna());
  sprintf(valor,"%i \%",datos.getHumedadInterna());
  mqttEnviar("invernadero/humedadin",valor);
  //Serial.println(datos.getTemperaturaExterna());
  sprintf(valor,"%i ºC",datos.getTemperaturaExterna());
  mqttEnviar("invernadero/temperaturaex",valor);
  //Serial.println(datos.getHumedadExterna());
  sprintf(valor,"%i \%",datos.getHumedadExterna());
  mqttEnviar("invernadero/humedadex",valor);
  
  char caracteres[50];
  sprintf(caracteres,"%i,%i,%i,%i,%i,%i,%i,%i,%i,1,0,",
    datos.getNitrogeno(),
    datos.getFosforo(),
    datos.getFosforo(),
    datos.getHumedadSuelo(),
    datos.getPh(),
    datos.getSalinidad(),
    datos.getHumedadInterna(),
    datos.getHumedadExterna(),
    datos.getTemperaturaInterna(),
    datos.getTemperaturaExterna()
  );
  Serial.println(caracteres);
}
void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);
  //Serial.println("Espere");
  //pantallaInfo("Espere");
  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  delay(6000);

  // To skip it, call init() instead of restart()
  modem.restart();

  if (GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }

  if (!modem.waitForNetwork()) {
    //Serial.println("Error al conectar a la red");
    //pantallaInfo("Error red");
    delay(10000);
    return;
  }

  //SerialMon.println(" success");
  //pantallaInfo("Conectado a la red");
  delay(5000);

  // if (modem.isNetworkConnected()) { SerialMon.println("Network connected"); }

  // GPRS connection parameters are usually set after network registration
  //SerialMon.print(F("Connecting to "));
  //SerialMon.print(apn);
  //pantallaInfo("Conectando al APN");
  for (int i = 0; i < 3; i++)
  {
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      //SerialMon.println(" fail");
      //pantallaInfo("Error APN");
      delay(10000);
    }else{
      //SerialMon.println(" success");
      //pantallaInfo("Conectado al APN");
      break;
    }
  }

  if (modem.isGprsConnected()) { 
    //SerialMon.println("GPRS connected");
    //pantallaInfo("GPRS conectado");
  }

  // MQTT Broker setup
  mqtt.setServer(broker, port);

  mqttConnect();
}

void loop() {
  actualizarDatos();

  if(datos.getHumedadSuelo()<50){
    actuadores.riego(6000);
    actualizarDatos();
  }

  if (datos.getNitrogeno()<MINIMO_NITROGENO && datos.getHumedadSuelo()>50);
  {
    actuadores.dosificacionNutrientes(20);
    actualizarDatos();
  }
  int temeperatura_interna=datos.getTemperaturaInterna();

  if (temeperatura_interna > RANGO_TEMPERATURA_INTERNA_1 && temeperatura_interna < RANGO_TEMPERATURA_INTERNA_2)
  {
    actuadores.abrirVentanas(25);
  }else if(temeperatura_interna > RANGO_TEMPERATURA_INTERNA_2 && temeperatura_interna < RANGO_TEMPERATURA_INTERNA_3){
    actuadores.abrirVentanas(50);
  }else if(temeperatura_interna > RANGO_TEMPERATURA_INTERNA_3 && temeperatura_interna < RANGO_TEMPERATURA_INTERNA_4){
    actuadores.abrirVentanas(75);
  }else if(temeperatura_interna > RANGO_TEMPERATURA_INTERNA_4){
    actuadores.abrirVentanas(100);
  }else{
    actuadores.cerrarVentanas();
  }

  mqtt.loop();
  delay(1000);
}
