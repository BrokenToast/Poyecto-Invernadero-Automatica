#ifndef Actucaciones_h
#define Actucaciones_h
#endif
#include "Arduino.h"
#include "Parametros.h"
class Actucaciones{
    private:
        int pin_step_ventana1;
        int pin_dire_ventana1;
        int pin_step_ventana2;
        int pin_dire_ventana2;
        int pin_step_peristaltica;
        int pin_dire_peristaltica;
        int pin_motor_agua;

        /**
         * @brief Esta variable nos indica cuanto esta abierta la ventana
         * 
         */
        int porcentaje_ventana;
        /**
         * @brief Esta función nos permite mover x cantidad de pasos un motor paso a paso.
         * 
         * @param cantidad 
         * @param direccion  
         */
        void moverPasos(int pin_step,int pin_dire,int cantidad,int direccion);
        void delayActuaciones(int tiempo);
    public:
        /**
         * @brief Construct a new Actucaciones object
         * 
         * @param pin_step_ventana1 
         * @param pin_dire_ventana1 
         * @param pin_step_ventana2 
         * @param pin_dire_ventana2 
         * @param pin_step_peristaltica 
         * @param pin_dire_peristaltica 
         * @param pin_motor_agua 
         */
        Actucaciones(int pin_step_ventana1,int pin_dire_ventana1,int pin_step_ventana2,int pin_dire_ventana2,int pin_step_peristaltica,int pin_dire_peristaltica,int pin_motor_agua);
        /**
         * @brief Nos permite dosificar nutrientes a la planta
         * 
         * @param cantidad 
         * @return Devuelve la cantidad de nutrientes dosificador,0=nitrogeno,1=potasio,2=fosforo
         */
        int* dosificacionNutrientes(int cantidad);
        /**
         * @brief Metodo que nos permite activar el riego por un determinado tiempo
         * 
         * @param tiempo El tiempo en segundo
         */
        void riego(int ml);
        /**
         * @brief Nos permite abrir la ventana.
         * 
         * @param porcentajes Porcentaje de la ventana abierta.
         */
        void abrirVentanas(int porcentajes);

        /**
         * @brief Nos permite cerrar las ventanas.
         * 
         * @param porcentajes Porcentaje de la ventana abierta.
         */
        void cerrarVentanas();
        
};
