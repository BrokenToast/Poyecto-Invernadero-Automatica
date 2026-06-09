#include "SensorSuelo.h"

int SensorSuelo::getDato(int direccion_inicio_alto,int direccion_inicio_bajo,int direccion_fin_alto,int direccion_fin_bajo){

  // Esta espera es importante para que si se llama multiples veces no se junten los mensajes.
  delaySensor(500);

  // Inicializamos la array de direccion id_sensor,función(escribir o leer),direccion de memoria inicio alto byte, direccion de memoria inicio bajo byte,
  // direccion de memoria fin alto byte,direccion de memoria fin bajo byte
  int direccion[8]={
    this->id_sensor,
    this->leer,
    direccion_inicio_alto,
    direccion_inicio_bajo,
    direccion_fin_alto,
    direccion_fin_bajo,
  };

  // Generamos los codigos CRC-16-Mondbus
  CRC16Modbus(direccion,6);

  // Reccorremos la direccioón y vamos escribiendo en el puerto serie del sensor.
  //Serial.printf("%i",direccion);
  for (int i = 0; i < 8; i++)
  {
    sensor.write(direccion[i]);
  }

  delaySensor(200);
  int lectura[20]={};
  int index=0;
  // Mientras que haya datos en el bufer del puerto del sensor, lo recorremos y lo vamos almacenando dentro del array lectura;
  while (sensor.available())
  {
    lectura[index]=sensor.read();
    ++index;
  }

  // Sacamos el código CRC que nos a generado el sensor;
  int codigo_crc_repuesta=(lectura[5]*256)+lectura[6];
  lectura[5]=0;
  lectura[6]=0;
  CRC16Modbus(lectura,5);
  //Gegeneramos un código CRC 
  int codigo_crc_generado= (lectura[5]*256)+lectura[6];
  
  // Tenemos que unir los dos bytes de datos asi que cojemos el mas significativo y le multiplicamos por 0x100, luego sumamos el byte de menos peso
  return (lectura[3]*256)+lectura[4];
}

/**
 * @brief 
 * 
 * @param datos 
 * @param longitud 
 */
void SensorSuelo::CRC16Modbus(int *datos,int longitud){
  // 1º tenemos que inicializar el la variable CRC 0xFFFF
  int crc=0xFFFF;

  for (int i = 0; i < longitud; ++i)
  {
      crc ^= *(datos+i) ;

      for (int c = 0; c < 8; ++c)
      {
          if (crc & 1)
          {      
              crc >>= 1;
              crc ^=0xA001;
          }else{
              crc >>= 1;
          }
      }
  }
  *(datos+(longitud+1))= crc / 0x100;
  *(datos+longitud)= crc % 0x100;
  }

/**
 * @brief 
 * 
 * @param milis 
 */
void SensorSuelo::delaySensor(unsigned long ms){
  int start = micros();

  while (ms > 0) {
      yield();
      while ( ms > 0 && (micros() - start) >= 1000) {
      ms--;
      start += 1000;
      }
  }
}
SensorSuelo::SensorSuelo(int id_sensor, int rx_port, int tx_port):sensor(1)
{
  this->id_sensor=id_sensor;
  this->sensor.begin(4800,SERIAL_8N1,rx_port,tx_port);
}
float SensorSuelo::getHumedad(){
  return getDato(0x00,0x00,0x00,0x01)/10.0;
}
float SensorSuelo::getTemperatura(){
  return getDato(0x00,0x01,0x00,0x02)/10.0;
}
int SensorSuelo::getConductividad(){
  return getDato(0x00,0x02,0x00,0x03);
}
float SensorSuelo::getPh(){
  return getDato(0x00,0x03,0x00,0x04)/10.0;
} 
int  SensorSuelo::getNitrogeno(){
  return getDato(0x00,0x04,0x00,0x05);
}
int SensorSuelo::getFosforo(){
  return getDato(0x00,0x05,0x00,0x06);
}
int SensorSuelo::getPotasio(){
  return getDato(0x00,0x06,0x00,0x06);
}
int SensorSuelo::getSalinidad(){
  return getDato(0x00,0x07,0x00,0x07);
}
int SensorSuelo::getTDS(){
  return getDato(0x00,0x08,0x00,0x08);
}
// int getFactorConductividad(){
  
// }
// int getFactorSalinidad(){
  
// }
// int getFactorTDS(){
  
// }