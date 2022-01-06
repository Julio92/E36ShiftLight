#include "InterfazE36.h"


InterfazE36::InterfazE36( int pin_entrada_rpm ){
    pin_entrada_rpm = pin_entrada_rpm ;
    margenError = 0.00;
} 

float InterfazE36::getFrecuenciaActual(){
    setFrecuenciaActual();
    return frecuenciaActual;
}

void InterfazE36::setFrecuenciaActual(){
    unsigned long duracionCicloAlto, duracionCicloBajo, periodo;
      
    // PulseIn devuelve los us (microsegundos) que la señal está en estado alto/bajo.
    duracionCicloAlto = pulseIn(PIN_RPM, HIGH);
    duracionCicloBajo = pulseIn(PIN_RPM, LOW) ;

    // El periodo equivale a la duración total del ciclo (alto + bajo).
    periodo = duracionCicloAlto + duracionCicloBajo ;

    // Calcula la frecuencia en Hz (1 segundo = 100.000 us).
    frecuenciaActual = ( 1000000.0 / periodo ) ;
    frecuenciaActual +=( frecuenciaActual * ( margenError ) );  // Restamos el margen de error.

    // Dependiendo de la frecuencia, el margen de error varía ligeramente.
    // En las frecuencias en las que trabaja, vamos a restar el margen de error.
    // Guardamos el margen de error para la siguiente iteración.
    if ( frecuenciaActual < 265 )
      margenError = -0.01;
    else margenError = -0.005 ;

}

int InterfazE36::getPinRPM(){
    return pin_entrada_rpm ;
}

int InterfazE36::pin_entrada_rpm;
float InterfazE36::frecuenciaActual ;
double InterfazE36::margenError;