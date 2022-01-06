#include <InterfazE36.h>

// Puntero a nuestra instancia de InterfazE36 y ControladoraLeds.
InterfazE36* interfaz = NULL ;
ControladoraLeds* controladora = NULL ;

void setup()
{
  // Configura los pines de Arduino.
  pinMode(PIN_RPM, INPUT);
  pinMode(PIN_NEOPIXEL, OUTPUT);

  // Instanciamos los objetos que necesitamos.
  interfaz = new InterfazE36(PIN_RPM);
  controladora = new ControladoraLeds(15, 50, 1);

  controladora->checkLeds();	
}

void loop()
{
  // Calcula la frecuencia actual de la señal.
  controladora->setFrecuenciaActual( interfaz->getFrecuenciaActual() );
  // En base a la frecuencia, calcula el estado en el que debe estar la tira led.
  controladora->setIdEstadoActual();
  // Aplica el estado a la tira led.
  controladora->aplicarEstadoActual();	
}
