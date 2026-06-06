#ifndef Comunicaciones_h
#define Comunicaciones_h
#endif
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
void reigo(int tiempo);
/**
 * @brief Nos permite abrir la ventana.
 * 
 * @param porcentajes Porcentaje de la ventana abierta.
 */
void ventanas(int porcentajes);