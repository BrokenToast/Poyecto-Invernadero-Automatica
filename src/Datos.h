#ifndef Datos_h
#define Datos_h
#endif
#include "SensorSuelo.h"
#include "DHT.h"
class Datos{
    private:
    int nitrogeno;
    int potasio;
    int fosforo;
    int ph;
    int salinidad;
    int humedad_interna;
    int humedad_externa;
    float humedad_suelo;
    int temperatura_interna;
    int temperatura_externa;
    float temperatura_suelo;

    DHT datos_DTH_interno;
    DHT datos_DTH_externo;

    SensorSuelo sensor_suelo;
    public:
    /**
     * @brief Construct a new Datos:: Datos object
     * 
     * @param rx_sensor_suelo 
     * @param tx_sensor_suelo 
     * @param datos_DTH_interno 
     * @param datos_DTH_externo 
     */
    Datos(int rx_sensor_suelo,
        int tx_sensor_suelo,
        int id_sensor_suelo,
        int datos_DTH_interno,
        int datos_DTH_externo): 
        sensor_suelo(id_sensor_suelo,rx_sensor_suelo, tx_sensor_suelo),
        datos_DTH_interno(datos_DTH_interno, DHT21),
        datos_DTH_externo(datos_DTH_externo, DHT21){
    };
    /**
     * @brief Get the Nitrogeno object
     * 
     * @return int 
     */
    int getNitrogeno();
    /**
     * @brief Get the Potasio object
     * 
     * @return int 
     */
    int getPotasio();
    /**
     * @brief Get the Fosforo object
     * 
     * @return int 
     */
    int getFosforo();
    /**
     * @brief Get the Salinidad object
     * 
     * @return int 
     */
    int getSalinidad();
    /**
     * @brief Get the Ph object
     * 
     * @return int 
     */
    int getPh();
    /**
     * @brief Get the Humedad Interna object
     * 
     * @return int 
     */
    int getHumedadInterna();
    /**
     * @brief Get the Humedad Externa object
     * 
     * @return int 
     */
    int getHumedadExterna();
    /**
     * @brief Get the Temperatura Interna object
     * 
     * @return int 
     */
    int getTemperaturaInterna();
    /**
     * @brief Get the Temperatura Externa object
     * 
     * @return int 
     */
    int getTemperaturaExterna();
    /**
     * @brief Get the Temperatura Suelo object
     * 
     * @return float 
     */
    float getTemperaturaSuelo();
    /**
     * @brief Get the Humedad Suelo object
     * 
     * @return float 
     */
    float getHumedadSuelo();
    /**
     * @brief Nos permite obtener los datos de los diferentes sensores 
     * 
     */
    void obtenerDatosSuelo();
};

