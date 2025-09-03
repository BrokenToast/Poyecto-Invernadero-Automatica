#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

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
  int getDato(uint8_t direccion_inicio_alto,uint8_t direccion_inicio_bajo,uint8_t direccion_fin_alto,uint8_t direccion_fin_bajo){

    // Esta espera es importante para que si se llama multiples veces no se junten los mensajes.
    delaySensor(500);

    // Inicializamos la array de direccion id_sensor,función(escribir o leer),direccion de memoria inicio alto byte, direccion de memoria inicio bajo byte,
    // direccion de memoria fin alto byte,direccion de memoria fin bajo byte
    uint8_t direccion[8]={
      this->id_sensor,
      this->leer,
      direccion_inicio_alto,
      direccion_inicio_bajo,
      direccion_fin_alto,
      direccion_fin_bajo
    };

    // Generamos los codigos CRC-16-Mondbus
    CRC16Modbus(direccion,6);

    // Reccorremos la direccioón y vamos escribiendo en el puerto serie del sensor.
    for (uint8_t byte:direccion)
    {
      sensor.write(byte);
    }

    delaySensor(200);

    uint8_t lectura[8]={};
    int index=0;
    // Mientras que haya datos en el bufer del puerto del sensor, lo recorremos y lo vamos almacenando dentro del array lectura;
    while (sensor.available())
    {
      lectura[index]=sensor.read();
      ++index;
    }
    
    // Sacamos el código CRC que nos a generado el sensor;
    int codigo_crc_repuesta=(lectura[5]*0x100)+lectura[6];
    lectura[5]=0;
    lectura[6]=0;
    CRC16Modbus(lectura,5);
    // Gegeneramos un código CRC 
    int codigo_crc_generado= (lectura[5]*0x100)+lectura[6];


    if (codigo_crc_generado==codigo_crc_generado)
    {
      // Tenemos que unir los dos bytes de datos asi que cojemos el mas significativo y le multiplicamos por 0x100, luego sumamos el byte de menos peso
      return (lectura[3]*0x100)+lectura[4];
    }else{
      return getDato(direccion_inicio_alto,direccion_inicio_bajo,direccion_fin_alto,direccion_fin_bajo);
    }
  
  }

  /**
   * @brief 
   * 
   * @param datos 
   * @param longitud 
   */
  void CRC16Modbus(uint8_t *datos,int longitud){
    // 1º tenemos que inicializar el la variable CRC 0xFFFF
    uint16_t crc=0xFFFF;

    // Realizamos un 
    for (int i = 0; i < longitud; i++)
    {
        crc ^= *(datos+i) ;

        for (short c = 0; c < 8; c++)
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
  void delaySensor(unsigned long ms){
    uint32_t start = micros();

    while (ms > 0) {
      yield();
      while ( ms > 0 && (micros() - start) >= 1000) {
        ms--;
        start += 1000;
      }
    }
  }
public:
  SensorSuelo(uint8_t id_sensor, int rx=2, int tx=3): sensor(rx,tx) 
  {
    this->id_sensor=id_sensor;
    this->sensor.begin(4800);
  }

  ~SensorSuelo()
  {
    delete this;
  }

  float getHumedad(){
    return getDato(0x00,0x00,0x00,0x01)/10.0;
  }
  float getTemperatura(){
    return getDato(0x00,0x01,0x00,0x02)/10.0;
  }
  int getConductividad(){
    return getDato(0x00,0x02,0x00,0x03);
  }
  float getPh(){
    return getDato(0x00,0x03,0x00,0x04)/10.0;
  } 
  int getNitrogeno(){
    return getDato(0x00,0x04,0x00,0x05);
  }
  int getFosforo(){
    return getDato(0x00,0x05,0x00,0x06);
  }
  int getPotasio(){
    return getDato(0x00,0x06,0x00,0x06);
  }
  int getSalinidad(){
    return getDato(0x00,0x07,0x00,0x07);
  }
  int getTDS(){
    return getDato(0x00,0x08,0x00,0x08);
  }
  // int getFactorConductividad(){
    
  // }
  // int getFactorSalinidad(){
    
  // }
  // int getFactorTDS(){
    
  // }

};

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

SensorSuelo suelo(1,2,3);
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("H:");
  Serial.begin(9600);
}


void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("H:");
  lcd.print(suelo.getHumedad());
  lcd.print("%");
  lcd.print("PH:");
  lcd.print(suelo.getPh());
  lcd.setCursor(0,1);
  lcd.print("N:");
  lcd.print(suelo.getNitrogeno());
  lcd.print("P:");
  lcd.print(suelo.getFosforo());
  lcd.print("K:");
  lcd.print(suelo.getPotasio());
  Serial.println();
  delay(1000);

}
