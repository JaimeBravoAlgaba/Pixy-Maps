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
#include <PixyMaps.h>
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