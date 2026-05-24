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
    int temperatura_interna;
    int temperatura_externa;

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
        datos_DTH_externo(datos_DTH_externo, DHT21){};
    int getNitrogeno();
    int getPotasio();
    int getFosforo();
    int getSalinidad();
    int getPh();
    int getHumedadInterna();
    int getHumedadExterna();
    int getTemperaturaInterna();
    int getTemperaturaExterna();
    void obtenerDatosSuelo();
};

