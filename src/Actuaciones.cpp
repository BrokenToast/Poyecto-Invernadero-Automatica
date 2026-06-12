#include "Actuaciones.h"
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
Actucaciones::Actucaciones(int pin_step_ventana1,int pin_dire_ventana1,int pin_step_ventana2,int pin_dire_ventana2,int pin_step_peristaltica,int pin_dire_peristaltica,int pin_motor_agua){
   pinMode(pin_dire_ventana1,OUTPUT);
   pinMode(pin_step_ventana1,OUTPUT);
   pinMode(pin_dire_ventana2,OUTPUT);
   pinMode(pin_step_ventana2,OUTPUT);
   pinMode(pin_dire_peristaltica,OUTPUT);
   pinMode(pin_step_peristaltica,OUTPUT); 
   pinMode(pin_motor_agua,OUTPUT);
}
/**
 * @brief Esta función nos permite mover x cantidad de pasos un motor paso a paso.
 * 
 * @param cantidad 
 * @param direccion  
 */
void Actucaciones::moverPasos(int pin_step,int pin_dire,int cantidad,int direccion){
    digitalWrite(pin_dire,direccion);

    for (int i = 0; i < cantidad; i++)
    {
        digitalWrite(pin_step,0);
        delayActuaciones(1);
        digitalWrite(pin_step,1);
        delayActuaciones(1);
    }
}
/**
 * @brief Nos permite dosificar nutrientes a la planta
 * 
 * @param cantidad 
 * @return Devuelve la cantidad de nutrientes dosificador,0=nitrogeno,1=potasio,2=fosforo
 */
int* Actucaciones::dosificacionNutrientes(int cantidad){
    // 70 ml por minuto
    int tiempo_final=millis()+(cantidad*60000)/70;
    // Para que gire en sistendo horario;
    digitalWrite(this->pin_dire_peristaltica,1);

    while (millis()<tiempo_final)
    {
        digitalWrite(this->pin_step_peristaltica,0);
        delayActuaciones(1);
        digitalWrite(this->pin_step_peristaltica,1);
        delayActuaciones(1);
    }
    
}
/**
 * @brief Metodo que nos permite activar el riego por un determinado tiempo
 * 
 * @param tiempo El tiempo en segundo
 */
void Actucaciones::riego(int tiempo){
    digitalWrite(this->pin_motor_agua,1);
    delay(tiempo);
    digitalWrite(this->pin_motor_agua,0);
}
/**
 * @brief Nos permite abrir las ventana.
 * 
 * @param porcentajes Porcentaje de la ventana abierta.
 */
void Actucaciones::abrirVentanas(int porcentaje){
    int cantidad_pasos=(porcentaje*PASO_VENTANA_100)/100;
    this->moverPasos(this->pin_step_ventana1,this->pin_dire_ventana1,cantidad_pasos,1);
}

/**
 * @brief Nos permite cerrar las ventanas.
 * 
 * @param porcentajes Porcentaje de la ventana abierta.
 */
void Actucaciones::cerrarVentanas(){
    
}

void Actucaciones::delayActuaciones(int tiempo){
    int tiempo_fin=tiempo+millis();
    
    while (millis()<tiempo_fin){}
}