#include"Datos.h"
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getNitrogeno(){
    return this->nitrogeno;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getPotasio(){
    return this->potasio;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getFosforo(){
    return this->fosforo;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getSalinidad(){
    return this->salinidad;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getPh(){
    return this->ph;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getHumedadInterna(){
    return this->humedad_interna;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getHumedadExterna(){
    return this->humedad_externa;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getTemperaturaInterna(){
    return this->temperatura_interna;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Datos::getTemperaturaExterna(){
    return this->temperatura_externa;
}
/**
 * @brief Get the Temperatura Suelo object
 * 
 * @return float 
 */
float Datos::getTemperaturaSuelo(){
    return this->temperatura_suelo;
}
/**
 * @brief Get the Humedad Suelo object
 * 
 * @return int 
 */
float Datos::getHumedadSuelo(){
    return this->humedad_suelo;
}
/**
 * @brief 
 * 
 * @return int 
 */
void Datos::obtenerDatosSuelo(){
    
    this->nitrogeno=this->sensor_suelo.getNitrogeno();
    this->delay(100);
    this->potasio=this->sensor_suelo.getPotasio();
    this->delay(100);
    this->fosforo=this->sensor_suelo.getFosforo();
    this->delay(100);
    this->ph=this->sensor_suelo.getPh();
    this->delay(100);
    this->salinidad=this->sensor_suelo.getSalinidad();
    this->delay(100);
    this->temperatura_suelo=this->sensor_suelo.getTemperatura();
    this->delay(100);
    this->humedad_suelo=this->sensor_suelo.getHumedad();
    this->delay(100);

    this->datos_DTH_externo.begin();
     this->temperatura_externa=this->datos_DTH_externo.readTemperature();
    this->humedad_externa=this->datos_DTH_externo.readHumidity();
    this->datos_DTH_interno.begin();
    this->humedad_interna=this->datos_DTH_interno.readHumidity();
    this->temperatura_interna=this->datos_DTH_interno.readTemperature();
}

void Datos::delay(int tiempo){
    int tiempo_final=millis()+tiempo+1;
    while (tiempo_final>millis()){}
}
