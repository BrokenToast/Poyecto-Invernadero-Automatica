#ifndef Error_h
#define Error_h
#endif
#include "SoftwareSerial.h"
class Error{
    public:
        Error(int tx,int rx, int baud_rate);
        void setmensaje(char* mensaje);
        void enviar_mensaje();
    private:
        char *error;
        SoftwareSerial serie_error;
};