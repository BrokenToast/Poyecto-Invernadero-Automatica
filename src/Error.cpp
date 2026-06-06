#include "Error.h"

Error::Error(){
    this->serie_error.begin(baud_rate,EspSoftwareSerial::SWSERIAL_8N1,rx,tx);
}

void Error::setmensaje(char* mensaje){
    this->error=mensaje;
    this->enviar_mensaje();
}

void Error::enviar_mensaje(){

}