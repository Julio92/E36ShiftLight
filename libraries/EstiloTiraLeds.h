#include <Adafruit_NeoPixel.h>


#define NUMERODELEDS   8
#define NUMEROESTADOS 12

/**
 * Clase para controlar de qué forma se encenderá la tira led.
 *
 * Se definirán distintos estilos donde se definirá en qué orden se encieden los leds, 
 * de qué color, si parapdearán o no, etc.
 * De momento, solo es posible usar un estilo, pero se implementarán más en un futuro.
 * 
 */
class EstiloTiraLeds {
  public:
    /// Los distintos colores que usará la tira led. 
    static uint32_t verde, naranja, rojo, purpura, azul, blanco, amarillo, apagado;
    
    /// El estado de la tira led se compone del color de cada uno de los leds y de si va a parpadear o no.
    struct estado {      
      uint32_t leds[NUMERODELEDS] ; /// < Cada posicion del array identifica un led de la tira. 
      bool parpadeando ;
    } ;

    /// Tendremos varios estados posibles.
    struct EstadosPosibles{
      estado estados[NUMEROESTADOS];
    };    
    static EstadosPosibles estadosPosibles;

    static int estiloActual; 

    /**
     * Constructor. 
     * 
     * @param estilo para seleccionar el estilo que tendrá la tira led.
     * 
     */
    EstiloTiraLeds( int estilo ) ;

    /**
     * Inicializa los valores RGB para los distintos colores. 
     * 
     */
    static void definirColores();

    /**
     * En función del estilo elegido, define unos estados u otros.
     * El estado contiene qué leds se van a encender, de qué color, y si parpadearán o no.
     * 
     */
    static void definirEstados();

    /**
     * Devuelve el estado indicado.
     * @param id indica la posición dentro de estadosPosibles.estados[] que se quiere devolver.
     * 
     * @return el estado indicado si es válido, estado incial (0) en cualquier otro caso.
     */
    estado getEstado(int id);

    /**
     * Getter del miembro estadosPosibles.
     * 
     */
    static EstadosPosibles getEstados();

} ;