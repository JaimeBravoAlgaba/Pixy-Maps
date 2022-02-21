#ifndef __VISION_SERVICE__
    #define __VISION_SERVICE__
    
    #include <Wire.h>
    #include "Pixy/Pixy.h"

    // COLORES RGB
    #define RGB_RED 255,0,0
    #define RGB_GREEN 0,255,0
    #define RGB_BLUE 0,0,255

    // COLORES PIXY
    #define SIG_RED     1
    #define SIG_BLUE    2
    
    // CIRCUITO
    #define SIG_TRAJ    SIG_RED
    #define SIG_CAR     SIG_BLUE
    #define TRAJ_POINTS 6

    /**
     * @brief Estructura para describir puntos 2D.
     * 
     */
    struct point{
        float x;
        float y;
    };

    /**
     * @brief Clase para definir el mapa detectado.
     * 
     * @param corners Vector con las 4 esquinas del mapa.
     */
    class PixyMap{
        public:
            point corners[4];

            PixyMap();
            bool getCorners();
    };

#endif