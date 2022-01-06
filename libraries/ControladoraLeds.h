#include <Adafruit_NeoPixel.h>
#include "EstiloTiraLeds.h"


#define PIN_NEOPIXEL   6

/**
 * Clase para controlar la tira led.
 *
 * Se comunicará con ella para encender los leds definidos en el estado.
 * Calculará en qué estado nos encontramos en función de la frecuencia de la señal.
 * 
 */
class ControladoraLeds {

  private:
    unsigned long frecuenciaDelta ;      ///< Cada cuantos Hz se cambiará de estado.
    unsigned long periodoParpadeo ;      ///< Cada cuantos ms parpadearán los leds.

    Adafruit_NeoPixel pixels ;           ///< Clase que se comunica con la tira led, instaciada en el constructor.

    EstiloTiraLeds estilo ;              ///< Clase que contiene el estilo que usará la tira led, instaciada en el constructor.
    EstiloTiraLeds::estado estadoActual; ///< Estado actual de la tira led.
    int idEstadoActual ;                 ///< Identifica en qué estado nos encontramos actualmente.
   
    float frecuenciaActual;              ///< Frecuencia actual de la señal.
    unsigned long tiempoAnterior ;       ///< Variable auxiliar para el parpadeo de los leds.

  public:
    /**
     * Constructor de la clase. 
     * 
     * Inicializa miembros de la clase. Habilita la tira led llamando al constructor de Adafruit_NeoPixel.
     * 
     * @param frecuenciaDelta son los Hz necesarios para pasar de un estado a otro.
     * @param periodoParpadeo es el periodo en ms de parpadeo de leds.
     * 
     */  
    ControladoraLeds( unsigned long frecuenciaDelta, unsigned long periodoParpadeo, int estilo ) ;

    /**
     * Aplica todos los estados definidos en estilo para despues apagar la tira.
     * 
     */ 
    void checkLeds() ;

    /**
     * Getter del miembro frecuenciaActual.
     * 
     */
    unsigned long getFrecuenciaActual() ;

    /**
     * Setter del miembro frecuenciaActual.
     * 
     */
    void setFrecuenciaActual( float frecuenciaActual ) ;

    /**
     * Setter del miembro idEstadoActual.
     * 
     * Para saber el estado en el que nos encontramos, dividimos la frecuencia actual entre la delta
     * y restamos el numero de estados. Cualquier valor que esté entre 0 y NUMERODEESTADOS -1 , es válido.
     * En cualquier otro caso, se devolverá el estado más cercano (0 o NUMERODEESTADOS - 1)
     * 
     */
    void setIdEstadoActual() ;

    /**
     * Getter del miembro idEstadoActual.
     * 
     */
    int getIdEstadoActual() ;

    /**
     * Actualiza el miembro estadoActual y lo aplica.
     * 
     */
    void aplicarEstadoActual() ;

    /**
     * Aplica el estado que recibe como parametro a la tira led.
     * 
     * @param estado es el estado que tiene que aplicar.
     * 
     */
    void aplicarEstado( EstiloTiraLeds::estado estado ) ;

    /**
     * Apaga todos los leds de la tira.
     * 
     */
    void apagaTodosLosLeds() ;

    /**
     * Selecciona los leds indicados en estadoActual.
     *    Hasta que no se llama a pixels.show(), no se actualiza la tira led.
     */
    void seleccionaLeds( EstiloTiraLeds::estado estadoActual );

    /**
     * Enciende los leds indicados en estadoActual.
     * 
     */
    void enciendeLeds( EstiloTiraLeds::estado estadoActual );

    /**
     * Parpadea los leds indicados en estadoActual.
     * 
     * Para saber el tiempo transcurrido, usamos millis(). Si éste es superior al periodo
     * de parpadeo cambiamos el estado de la tira.
     */
    void parpadeaLeds( EstiloTiraLeds::estado estadoActual );

} ;