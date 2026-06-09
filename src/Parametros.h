#ifndef Parametros_h
#define Parametros_h
#endif
#include "Arduino.h"
// Select your modem:
#define TINY_GSM_MODEM_SIM800

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Puerto de comunicación Serie para el modulo GSM
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
const char* broker = "95.123.32.136";
const int port = 12473;
const char* mqtt_user = "toast";
const char* mqtt_pass = "paso1234";

#define PUERTO_PANTALLA Serial

////////////////////////////////////////////////////////////
//                                                        //
//==========================Pines=========================//
//                                                        //
////////////////////////////////////////////////////////////

#define PIN_DIR_VENTANA1 33
#define PIN_STEP_VENTANA1 32
#define PIN_DIR_VENTANA2 26
#define PIN_STEP_VENTANA2 25
#define PIN_DIR_PERISTALTICA 12
#define PIN_STEP_PERISTALTICA 14
#define PIN_BOMBA_AGUA 21
#define PIN_DATA_AM2301A_INTERNA 22
#define PIN_DATA_AM2301A_EXTERNA 5
#define PIN_TX_SENSOR_SUELO 19
#define PIN_RX_SENSOR_SUELO 18

////////////////////////////////////////////////////////////
//                                                        //
//=================Parametros de actuación================//
//                                                        //
////////////////////////////////////////////////////////////

#define ID_SENSOR_SUELO 1
#define MINIMA_HUMEDAD_SUELO 40
#define RANGO_TEMPERATURA_INTERNA_1 23
#define RANGO_TEMPERATURA_INTERNA_2 26
#define RANGO_TEMPERATURA_INTERNA_3 28
#define RANGO_TEMPERATURA_INTERNA_4 30
#define MINIMO_NITROGENO 100
#define MINIMO_POTASIO 40
#define MINIMO_FOSFORO 40
