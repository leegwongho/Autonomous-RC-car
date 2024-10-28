/*
 * moter.h
 *
 *  Created on: Oct 10, 2024
 *      Author: Parkdongjin
 */

#ifndef INC_MOTER_H_
#define INC_MOTER_H_

#include "main.h"
extern TIM_HandleTypeDef htim3;
extern uint8_t rxData[1];
extern uint8_t pwmFlag;
extern uint8_t r_Distance;
extern uint8_t c_Distance;
extern uint8_t l_Distance;


void PWM_Init();
void FORWARD();
void BACKWARD();
void RIGHTTURN();
void LEFTTURN();
void PAUSE();
void START();
void SPEED();
void STOP();
void START_while();

#endif /* INC_MOTER_H_ */
