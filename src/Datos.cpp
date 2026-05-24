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
 * @brief 
 * 
 * @return int 
 */
void Datos::obtenerDatosSuelo(){
    this->nitrogeno=this->sensor_suelo.getNitrogeno();
    this->potasio=this->sensor_suelo.getPotasio();
    this->fosforo=this->sensor_suelo.getFosforo();
    this->ph=this->sensor_suelo.getPh();
    this->salinidad=this->sensor_suelo.getSalinidad();

    this->humedad_interna=this->datos_DTH_interno.readHumidity();
    this->humedad_externa;this->datos_DTH_externo.readHumidity();
    this->temperatura_interna=this->datos_DTH_interno.readTemperature();
    this->temperatura_externa=this->datos_DTH_externo.readTemperature();
}
