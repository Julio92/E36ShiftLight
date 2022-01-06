#include "EstiloTiraLeds.h"

EstiloTiraLeds::EstiloTiraLeds( int estilo )
{
    estiloActual = estilo ;
    definirColores();
    definirEstados();  
}

void EstiloTiraLeds::definirColores(){
    verde    = Adafruit_NeoPixel::Color(0, 150, 0);
    naranja  = Adafruit_NeoPixel::Color(127, 63, 0);
    rojo     = Adafruit_NeoPixel::Color(150, 0, 0);
    purpura  = Adafruit_NeoPixel::Color(74, 0, 105);
    azul     = Adafruit_NeoPixel::Color(0, 0, 255);
    blanco   = Adafruit_NeoPixel::Color(255, 255, 255);
    amarillo = Adafruit_NeoPixel::Color(255, 233, 0);
    apagado  = Adafruit_NeoPixel::Color(0, 0, 0);
}

void EstiloTiraLeds::definirEstados() {

    if( estiloActual == 1 ) {
        estadosPosibles.estados[0] = {{ apagado,  apagado, apagado,  apagado, apagado, apagado,  apagado, apagado}, false }; // frqActual < 200 Hz 
        estadosPosibles.estados[1] = {{ verde,    apagado, apagado,  apagado, apagado, apagado,  apagado, verde},   false }; // 200 Hz < frqActual < 215 Hz 
        estadosPosibles.estados[2] = {{ verde,    verde,   apagado,  apagado, apagado, apagado,  verde,   verde},   false }; // 215 Hz < frqActual < 230 Hz 
        estadosPosibles.estados[3] = {{ verde,    verde,   amarillo, apagado, apagado, amarillo, verde,   verde},   false }; // 230 Hz < frqActual < 245 Hz 
        estadosPosibles.estados[4] = {{ verde,    verde,   amarillo, rojo,    rojo,    amarillo, verde,   verde},   false }; // 245 Hz < frqActual < 260 Hz    
        estadosPosibles.estados[5] = {{ verde,    verde,   rojo,     rojo,    rojo,    rojo,     verde,   verde},   false }; // 260 Hz < frqActual < 275 Hz 
        estadosPosibles.estados[6] = {{ verde,    rojo,    rojo,     rojo,    rojo,    rojo,     rojo,    verde},   false }; // 275 Hz < frqActual < 290 Hz 
        estadosPosibles.estados[7] = {{ rojo,     rojo,    rojo,     rojo,    rojo,    rojo,     rojo,    rojo},    false }; // 290 Hz < frqActual < 305 Hz 
        estadosPosibles.estados[8] = {{ rojo,     rojo,    rojo,     rojo,    rojo,    rojo,     rojo,    rojo},    true  }; // 305 Hz < frqActual < 320 Hz 
        estadosPosibles.estados[9] = {{ blanco,   blanco,  blanco,   blanco,  blanco,  blanco,   blanco,  blanco},  true  }; // 320 Hz < frqActual < 335 Hz 
        estadosPosibles.estados[10]= {{ azul,     azul,    azul,     azul,    azul,    azul,     azul,    azul},    true  }; // 335 Hz < frqActual < 350 Hz 
        estadosPosibles.estados[11]= {{ azul,     azul,    azul,     azul,    azul,    azul,     azul,    azul},    false }; // frqActual > 350 Hz
    }
    else {
        estadosPosibles.estados[0] = {{ apagado,  apagado, apagado, apagado,  apagado,  apagado,  apagado, apagado}, false }; // frqActual < 200 Hz 
        estadosPosibles.estados[1] = {{ verde,    apagado, apagado, apagado,  apagado,  apagado,  apagado, apagado}, false }; // 200 Hz < frqActual < 215 Hz 
        estadosPosibles.estados[2] = {{ verde,    verde,   apagado, apagado,  apagado,  apagado,  apagado, apagado}, false }; // 215 Hz < frqActual < 230 Hz 
        estadosPosibles.estados[3] = {{ verde,    verde,   verde,   apagado,  apagado,  apagado,  apagado, apagado}, false }; // 230 Hz < frqActual < 245 Hz 
        estadosPosibles.estados[4] = {{ verde,    verde,   verde,   amarillo, apagado,  apagado,  apagado, apagado}, false }; // 245 Hz < frqActual < 260 Hz    
        estadosPosibles.estados[5] = {{ verde,    verde,   verde,   amarillo, amarillo, apagado,  apagado, apagado}, false }; // 260 Hz < frqActual < 275 Hz 
        estadosPosibles.estados[6] = {{ verde,    verde,   verde,   amarillo, amarillo, rojo,     apagado, apagado}, false }; // 275 Hz < frqActual < 290 Hz 
        estadosPosibles.estados[7] = {{ verde,    verde,   verde,   amarillo, amarillo, rojo,     rojo,    apagado}, false }; // 290 Hz < frqActual < 305 Hz 
        estadosPosibles.estados[8] = {{ verde,    verde,   verde,   amarillo, amarillo, rojo,     rojo,    rojo},    false }; // 305 Hz < frqActual < 320 Hz 
        estadosPosibles.estados[9] = {{ rojo,     rojo,    rojo,    rojo,     rojo,     rojo,     rojo,    rojo},    true  }; // 320 Hz < frqActual < 335 Hz 
        estadosPosibles.estados[10]= {{ azul,     azul,    azul,    azul,     azul,     azul,     azul,    azul},    true  }; // 335 Hz < frqActual < 350 Hz 
        estadosPosibles.estados[11]= {{ azul,     azul,    azul,    azul,     azul,     azul,     azul,    azul},    false }; // frqActual > 350 Hz        
    }
}

EstiloTiraLeds::estado EstiloTiraLeds::getEstado(int id){
    // Si solicita un estado inválido, devolvemos el estado inicial (0).
    if (id >= 0 && id < NUMEROESTADOS)
        return estadosPosibles.estados[id];
    
    return estadosPosibles.estados[0] ;
}

EstiloTiraLeds::EstadosPosibles EstiloTiraLeds::getEstados(){
    return estadosPosibles;
}


// Hay que definir los miembros estáticos de la clase, fuera de la clase... cosas de C++.
uint32_t EstiloTiraLeds::verde, EstiloTiraLeds::naranja, EstiloTiraLeds::rojo, EstiloTiraLeds::purpura, 
         EstiloTiraLeds::azul,  EstiloTiraLeds::blanco,  EstiloTiraLeds::amarillo, EstiloTiraLeds::apagado ;
         
EstiloTiraLeds::EstadosPosibles EstiloTiraLeds::estadosPosibles;
int EstiloTiraLeds::estiloActual;