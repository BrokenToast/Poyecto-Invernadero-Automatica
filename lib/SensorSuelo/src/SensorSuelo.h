// math_operations.h
#ifndef SENSORSUELO_H
#define SENSORSUELO_H

#include <Arduino.h>
#include "HardwareSerial.h"

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

  HardwareSerial sensor;

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
  SensorSuelo(uint8_t id_sensor, int rx_port, int tx_port);
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
};
#endif
