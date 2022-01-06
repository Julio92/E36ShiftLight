#include <Arduino.h>
#include "ControladoraLeds.h"


#define PIN_RPM        5

/**
 * Clase que hace de interfaz con el BMW E36.
 *
 * A partir de la señal de entrada, calcula su frecuencia. El coche emite un pulso cuadrado
 * de 0-12V, el cual hay que tratar para bajarlo a 0-5V. 
 * 
 * A mayor número de RPM, mayor es la frecuencia de la señal.
 * 
 */
class InterfazE36 {
  public:
    static int pin_entrada_rpm ;    ///< Es el pin de Arduino que recibe la señal del coche.
    static float frecuenciaActual ; ///< Es la frecuencia actual (en Hz) de la señal.
    static double margenError ;     ///< Intenta corregir el margen de error al medir la frecuencia.

    /**
     * Constructor. 
     * 
     * @param pin_entrada_rpm es el pin por el que recibimos la señal de RPM.
     * 
     */
    InterfazE36( int pin_entrada_rpm ) ;

    /**
     * Getter del miembro frecuenciaActual. 
     * 
     * Calcula la frecuencia actual y la devuelve.
     * @return frecuenciaActual
     * 
     */
    static float getFrecuenciaActual() ;

    /**
     * Setter del miembro frecuenciaActual. 
     * 
     * Calculamos el periodo de la señal (suma de la duración de un ciclo alto + ciclo bajo),
     * para después calcular su inversa obteniendo así la frecuencia.
     * 
     * La frecuencia se calcula en Hz.
     * 
     */
    static void setFrecuenciaActual();

    /**
     * Getter del miembro pin_entrada_rpm. 
     * 
     */
    static int getPinRPM();

} ;