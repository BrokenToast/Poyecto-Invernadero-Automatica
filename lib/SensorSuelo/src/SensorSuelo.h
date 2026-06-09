// math_operations.h
#ifndef SensorSuelo_H
#define SensorSuelo_H
#endif
#include "HardwareSerial.h"

/**
 * @brief Clase que nos permite leer y escribir en el sensor de suelo halisense NPK-T(Temperatura)-PH-C(Conductividad)-S(Salinidad)
 * 
 */
class SensorSuelo
{
public:
  int id_sensor;
  
  const int leer=0x03;
  const int escribir=0x03;

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
  int getDato(int direccion_inicio_alto,int direccion_inicio_bajo,int direccion_fin_alto,int direccion_fin_bajo);

  /**
   * @brief 
   * 
   * @param datos 
   * @param longitud 
   */
  void CRC16Modbus(int *datos,int longitud);

  /**
   * @brief 
   * 
   * @param milis 
   */
  void delaySensor(unsigned long ms);
  SensorSuelo(int id_sensor, int rx_port, int tx_port);
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
