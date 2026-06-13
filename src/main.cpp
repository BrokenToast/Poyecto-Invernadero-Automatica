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
  #ifdef SerialMon
    SerialMon.print("Connecting to ");
    SerialMon.print(broker);
  #endif

  // Or, if you want to authenticate MQTT:
  boolean status = mqtt.connect("esp32", mqtt_user, mqtt_pass);
  #ifdef SerialMon
    if (!status)
    {
      Serial.println("Error al conectar al mqtt");
    }else{
      Serial.println("Conectado al mqtt");
    }
  #endif

  return mqtt.connected();
}
/**
 * @brief Nos permite enviar datos al servidor mqtt
 * 
 * @param topic 
 * @param datos 
 */
void mqttEnviar(const char* topic, String datos) {
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
  #ifdef SerialMon
    Serial.println(datos.getNitrogeno());
    Serial.println(datos.getPotasio());
    Serial.println(datos.getFosforo());
    Serial.println(datos.getPh());
    Serial.println(datos.getTemperaturaSuelo());
    Serial.println(datos.getHumedadSuelo());
    Serial.println(datos.getTemperaturaInterna());
    Serial.println(datos.getHumedadInterna());
    Serial.println(datos.getTemperaturaExterna());
    Serial.println(datos.getHumedadExterna());
  #endif
  
  if (datos.getHumedadSuelo()>50)
  {
    sprintf(valor,"%i mg/kg",datos.getNitrogeno());
    mqttEnviar("invernadero/nitrogeno",valor);
    sprintf(valor,"%i mg/kg",datos.getPotasio());
    mqttEnviar("invernadero/potasio",valor);
    sprintf(valor,"%i mg/kg",datos.getFosforo());
    mqttEnviar("invernadero/fosforo",valor);
    mqttEnviar("invernadero/ph",String(datos.getPh()));
  }
  sprintf(valor,"%f ºC",datos.getTemperaturaSuelo());
  mqttEnviar("invernadero/temperaturasuelo",valor);
  sprintf(valor,"%f \%",datos.getHumedadSuelo());
  mqttEnviar("invernadero/humedadsuelo",valor);
  sprintf(valor,"%i ºC",datos.getTemperaturaInterna());
  mqttEnviar("invernadero/temperaturain",valor);
  sprintf(valor,"%i \%",datos.getHumedadInterna());
  mqttEnviar("invernadero/humedadin",valor);
  sprintf(valor,"%i ºC",datos.getTemperaturaExterna());
  mqttEnviar("invernadero/temperaturaex",valor);
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
  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
  delay(6000);

  // To skip it, call init() instead of restart()
  modem.restart();

  if (GSM_PIN && modem.getSimStatus() != 3) { modem.simUnlock(GSM_PIN); }

  if (!modem.waitForNetwork()) {
    #ifdef SerialMon
      Serial.println("Error al conectar a la red");
    #endif
    return;
  }

  delay(5000);

  #ifdef SerialMon
    if (modem.isNetworkConnected()) { SerialMon.println("Network connected"); }
  #endif
  // GPRS connection parameters are usually set after network registration
  for (int i = 0; i < 3; i++)
  {
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      #ifdef SerialMon
        SerialMon.println(" fail");
      #endif
      delay(10000);
    }else{
      #ifdef SerialMon
        SerialMon.println(" success");
      #endif
      break;
    }
  }
  #ifdef SerialMon
    if (modem.isGprsConnected()) { 
      SerialMon.println("GPRS connected");
    }
  #endif

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
