/*                   PIXY-MAPS: Motor Service                */
/*                                                           */
/* version  : V1.0  [26/01/2022]                             */
/* creation :       [26/01/2022]                             */
/*___________________________________________________________*/
// DESCRIPCIÓN:
//
//   Este archivo incluye funciones para la gestión de los
// motores del robot móvil.
/*___________________________________________________________*/
#include <Arduino.h>
#include <MotorService.h>

/**
 * @brief Incializa los motores Izquierdo y Derecho.
 * 
 */
void setupMotors(){
    
    // Setup Left Motor:
    pinMode(MOTOR_LA, OUTPUT);
    pinMode(MOTOR_LB, OUTPUT);
    pinMode(MOTOR_LS, OUTPUT);

    // Setup Right Motor:
    pinMode(MOTOR_RA, OUTPUT);
    pinMode(MOTOR_RB, OUTPUT);
    pinMode(MOTOR_RS, OUTPUT);
}

/**
 * @brief Establece el PWM de un motor dado.
 * 
 * @param motor   Izquierdo: 0 (MOTOR_L), Derecho: 1 (MOTOR_R).
 * @param speed   Valor entre -255 y 255.
 */
void moveMotor(uint8_t motor, int16_t speed){
    int a, b, s;

    switch (motor){
        case MOTOR_L:
            a = MOTOR_LA;
            b = MOTOR_LB;
            s = MOTOR_LS;
            break;
        case MOTOR_R:
            a = MOTOR_RA;
            b = MOTOR_RB;
            s = MOTOR_RS;
            break;    
        default:
            return;
    }

    if (speed < 0){
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        speed = -speed;
    }
    else if(speed > 0){
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
    }
    else{
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
    }
    analogWrite(s, speed);
}

/**
 * @brief Returns the current position of the car as a tuple<int, int>.
 * 
 * @param payload String with the blocks detected by the Pixy cam.
 * @return std::tuple<int, int> 
 */
std::tuple<int,int> getCurrPos(String payload){
    // Payload structure: {CurrentPosition:[int,int];Trajectory:[[int,int],[int,int],...]}
    // Extraccion del string con CurrentPosition:
    int pos1 = payload.indexOf("CurrentPos");
    int pos2 = payload.indexOf("Trajectory");
    String currPos = payload.substring(pos1 , pos2);

    // Extracción de x e y:
    pos1 = currPos.indexOf("[");
    pos2 = currPos.indexOf(",");    

    int x = currPos.substring(pos1+1, pos2).toInt();
    
    pos1 = currPos.indexOf("]");
    int y = currPos.substring(pos2+1, pos1).toInt();

    return std::tuple<int,int> {x,y};
}