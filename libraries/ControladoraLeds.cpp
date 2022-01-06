#include "ControladoraLeds.h"


ControladoraLeds::ControladoraLeds( unsigned long frecuenciaDelta, unsigned long periodoParpadeo, int estilo ) : 
    frecuenciaDelta(frecuenciaDelta),
    periodoParpadeo(periodoParpadeo),      
    pixels(NUMERODELEDS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800),
    estilo(estilo)
    {
        pixels.begin();                    ///< Inicializa la tira led.
        pixels.setBrightness(150);         ///< Define el nivel de brillo de la tira (0-255).  
        apagaTodosLosLeds();
    }

void ControladoraLeds::checkLeds(){
    // Aplica todos los estados para despues apagar la tira.
    EstiloTiraLeds::EstadosPosibles estados = estilo.getEstados();
    for ( int i = 0 ; i < NUMEROESTADOS ; i++){
        aplicarEstado(estados.estados[i]);
        delay(150);
    }
    apagaTodosLosLeds();      
}


unsigned long ControladoraLeds::getFrecuenciaActual(){
    return frecuenciaActual ;
}

void ControladoraLeds::setFrecuenciaActual( float frecuenciaActual ){
    this->frecuenciaActual = frecuenciaActual ;
}

void ControladoraLeds::setIdEstadoActual( ){

    this->idEstadoActual = (int)(frecuenciaActual / frecuenciaDelta) - NUMEROESTADOS ;

    if (idEstadoActual < 0) 
        idEstadoActual = 0 ;

    else if (idEstadoActual >= NUMEROESTADOS )
        idEstadoActual = (int)(NUMEROESTADOS - 1) ;
}


int ControladoraLeds::getIdEstadoActual(){
    return idEstadoActual;
}

void ControladoraLeds::aplicarEstadoActual( ){
    estadoActual = estilo.getEstado(idEstadoActual) ;
    aplicarEstado(estadoActual) ;
}

void ControladoraLeds::aplicarEstado( EstiloTiraLeds::estado estado ){
    if( !estado.parpadeando )
        enciendeLeds(estado);
    else parpadeaLeds(estado);      
}

void ControladoraLeds::apagaTodosLosLeds( ){
    pixels.clear();
    pixels.show();
}

void ControladoraLeds::seleccionaLeds( EstiloTiraLeds::estado estadoActual ){
    pixels.clear();
    for (int i = 0 ; i < NUMERODELEDS ; i++ )
        pixels.setPixelColor(i, estadoActual.leds[i]);
}

void ControladoraLeds::enciendeLeds( EstiloTiraLeds::estado estadoActual ){
    seleccionaLeds(estadoActual);
    pixels.show();
}

void ControladoraLeds::parpadeaLeds( EstiloTiraLeds::estado estadoActual ){
    unsigned long tiempoActual = millis();

    // Comprueba si la tira está encendida/apagada comprobando el primer led.
    bool encendido = !(pixels.getPixelColor(0) == 0x000000);

    // Si se ha superado el periodo y los leds están apagados, enciéndelos.
    if((unsigned long)(tiempoActual - tiempoAnterior) >= periodoParpadeo && !encendido){
        tiempoAnterior = tiempoActual;
        enciendeLeds(estadoActual);
    }

    // Si se ha superado el periodo y los leds están encendidos, apágalos.
    if((unsigned long)(tiempoActual - tiempoAnterior) >= periodoParpadeo && encendido){
        tiempoAnterior = tiempoActual;
        apagaTodosLosLeds();
    }
}