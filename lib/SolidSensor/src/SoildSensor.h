#ifndef SoildSensor_h
#define SoildSensor_h
#endif
#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>



struct direcciones_datos
{
  const uint16_t humedad=0x0000;
  const uint16_t temperatura=0x0001;
  const uint16_t conductividad=0x01002;
  const uint16_t ph=0x0003;
  const uint16_t nitrogeno=0x0004;
  const uint16_t fosforo=0x0005;
  const uint16_t potasio=0x0006;
  const uint16_t salinidad=0x0007;
  const uint16_t total_disolucion_solido=0x0008;
  const uint16_t factor_confuctividad=0x0022;
  const uint16_t factor_salinidad=0x0023;
  const uint16_t factor_total_disolucion_solido=0x0024;
};
struct direccion_offset
{
  const uint16_t temperatura=0x0050;
  const uint16_t humedad=0x0051;
  const uint16_t conductividad=0x0052;
  const uint16_t ph=0x0053;
  const uint16_t factor_nitrgeno_byte_alto=0x04E8;
  const uint16_t factor_nitrgeno_byte_bajo=0x04E9;
  const uint16_t nitrogeno=0x04EA;
  const uint16_t factor_fosforo_byte_alto=0x04F2;
  const uint16_t factor_fosforo_byte_bajo=0x04F3;
  const uint16_t fosforo=0x04F4;
  const uint16_t factor_potasio_byte_alto=0x04FC;
  const uint16_t factor_potasio_byte_bajo=0x04FD;
  const uint16_t potasio=0x04FE;
};



/**
 * @brief Clase que nos permite leer y escribir en el sensor de suelo halisense NPK-T(Temperatura)-PH-C(Conductividad)-S(Salinidad)
 * 
 */
class SensorSuelo
{
private:
  uint8_t id_sensor;
  
  const uint8_t leer=0x03;
  const uint8_t escribir=0x03;

  SoftwareSerial sensor;

  /**
   * @brief Método que nos permite obtener un dato del sensor.
   * 
   * @param direccion_inicio_alto 
   * @param direccion_inicio_bajo 
   * @param direccion_fin_alto 
   * @param direccion_fin_bajo 
   * @return int 
   */
  int getDato(uint8_t direccion_inicio_alto,uint8_t direccion_inicio_bajo,uint8_t direccion_fin_alto,uint8_t direccion_fin_bajo);

  /**
   * @brief 
   * 
   * @param datos 
   * @param longitud 
   */
  void CRC16Modbus(uint8_t *datos,int longitud);

  /**
   * @brief 
   * 
   * @param milis 
   */
  void delaySensor(unsigned long ms);
public:
  SensorSuelo(uint8_t id_sensor, int rx=2, int tx=3);
  ~SensorSuelo();
  float getHumedad();
  float getTemperatura();
  int getConductividad();
  float getPh();
  int getNitrogeno();
  int getFosforo();
  int getPotasio();
  int getSalinidad();
  int getTDS();
  // int getFactorConductividad(){
    
  // }
  // int getFactorSalinidad(){
    
  // }
  // int getFactorTDS(){
    
  // }

};