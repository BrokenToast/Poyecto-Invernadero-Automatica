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
Actucaciones::Actucaciones(int pin_step_ventana1,int pin_dire_ventana1,int pin_step_ventana2,int pin_dire_ventana2,int pin_step_peristaltica,int pin_dire_peristaltica,int pin_motor_agua,int cantidad_pasos_ventana){
    this->pin_step_ventana1=pin_step_ventana1;
    this->pin_dire_ventana1=pin_dire_ventana1;
    this->pin_step_ventana2=pin_step_ventana2;
    this->pin_dire_ventana2=pin_dire_ventana2;
    this->pin_step_peristaltica=pin_step_peristaltica;
    this->pin_dire_peristaltica=pin_dire_peristaltica;
    this->pin_motor_agua=pin_motor_agua;
    this->cantidad_pasos_ventana=cantidad_pasos_ventana;
    pinMode(pin_dire_ventana1,OUTPUT);
    pinMode(pin_step_ventana1,OUTPUT);
    pinMode(pin_dire_ventana2,OUTPUT);
    pinMode(pin_step_ventana2,OUTPUT);
    pinMode(pin_dire_peristaltica,OUTPUT);
    pinMode(pin_step_peristaltica,OUTPUT); 
    pinMode(pin_motor_agua,OUTPUT);
    this->cantidad_pasos_ventana=cantidad_pasos_ventana;
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
        delay(1);
        digitalWrite(pin_step,1);
        delay(2);
    }
}
/**
 * @brief Nos permite dosificar nutrientes a la planta
 * 
 * @param cantidad 
 * @return Devuelve la cantidad de nutrientes dosificador,0=nitrogeno,1=potasio,2=fosforo
 */
void Actucaciones::dosificacionNutrientes(int cantidad){
    // 70 ml por minuto
    digitalWrite(this->pin_dire_peristaltica,1);
    this->moverPasos(this->pin_step_peristaltica,this->pin_dire_peristaltica,10000,1);
    
}
/**
 * @brief Nos permite abrir las ventana.
 * 
 * @param porcentajes Porcentaje de la ventana abierta.
 */
void Actucaciones::abrirVentanas(int porcentaje){
    int cantidad_pasos=(porcentaje*this->cantidad_pasos_ventana)/100;
    this->cantidad_pasos_dados=cantidad_pasos;
    this->moverPasos(this->pin_step_ventana1,this->pin_dire_ventana1,cantidad_pasos,1);
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
 * @brief Nos permite cerrar las ventanas.
 * 
 * @param porcentajes Porcentaje de la ventana abierta.
 */
void Actucaciones::cerrarVentanas(){
        this->moverPasos(this->pin_step_ventana1,this->pin_dire_ventana1,this->cantidad_pasos_dados,0);
}