 
#include "SoftwareSerial.h"
class Error{
    public:
        /**
         * @brief Antes de construir un error tiene que estar declarada la constante global APANTALLa y AMQTT
         * 
         * @param mensaje Mensaje que contiene el error
         */
        Error(char* mensaje);
        /**
         * @brief Set the Mensaje object
         * 
         * @param mensaje 
         */
        void setMensaje(char* mensaje);
        /**
         * @brief Get the Mensaje object
         * 
         * @return char* 
         */
        char* getMensaje();
        /**
         * @brief Metodo que nos permite enviar el error a la pantalla
         * 
         */
        void enviar_pantalla();
        /**
         * @brief Métodos que nos permite enviar el error al servidor MQTT 
         * 
         */
        void enviar_mqtt();
    private:
        char *error;
};