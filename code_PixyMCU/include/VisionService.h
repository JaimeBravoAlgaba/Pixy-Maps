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
    typedef struct Point{
        uint16_t x;
        uint16_t y;
    } Point;

#endif