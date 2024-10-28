/*
 * moter.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Parkdongjin
 */
#include "moter.h"

extern uint8_t u_distance_c;
extern uint8_t u_distance_r;
extern uint8_t u_distance_l;


void PWM_Init()
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void FORWARD()
{
	//pa8 pb10 /  pb4 pb5

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

//	TIM3->CCR1 = 500;
//	TIM3->CCR2 = 500;

	TIM3->CCR1 = 2000;
	TIM3->CCR2 = 2000;
}

void BACKWARD()
{
	//pa8 pb10 /  pb4 pb5

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

//	TIM3->CCR1 = 500;
//	TIM3->CCR2 = 500;

	TIM3->CCR1 = 2000;
	TIM3->CCR2 = 2000;
}

void RIGHTTURN()
{
	//pa8 pb10 /  pb4 pb5

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

//	TIM3->CCR1 = 500;
//	TIM3->CCR2 = 500;

	TIM3->CCR1 = 2000;
	TIM3->CCR2 = 2000;
}

void LEFTTURN()
{
	//pa8 pb10 /  pb4 pb5

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

//	TIM3->CCR1 = 500;
//	TIM3->CCR2 = 500;

	TIM3->CCR1 = 2000;
	TIM3->CCR2 = 2000;
}

void PAUSE()
{
	//pa8 pb10 /  pb4 pb5

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
}

void STOP()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);

	htim3.Instance -> CCR1 = 0;
	htim3.Instance -> CCR2 = 0;
}

uint8_t coner_f;

void START_while()
{


	uint8_t con_dis = 15;

	uint8_t coner_dis = 5;

	if (l_Distance < coner_dis && c_Distance < coner_dis && r_Distance < coner_dis){
		coner_f = 1;
	}
	else {
		coner_f = 0;
	}


	u_distance_c = c_Distance;
	u_distance_r = r_Distance;
	u_distance_l = l_Distance;


	if ( (c_Distance < con_dis) || (l_Distance < con_dis) || r_Distance < con_dis ){
		while (l_Distance > r_Distance){
			if (coner_f == 0){
				LEFTTURN();
			}
			else if (coner_f == 1){
				while (coner_f){
					LEFTTURN();
					if (l_Distance > coner_dis || c_Distance > coner_dis || r_Distance > coner_dis){
						break;
					}
				}
			}
			else if (r_Distance > u_distance_r){
				break;
			}


		}

		while (r_Distance > l_Distance) {
			if (coner_f == 0){
				RIGHTTURN();
			}
			else if (coner_f == 1){
				while (coner_f){
					RIGHTTURN();
					if (l_Distance > coner_dis || c_Distance > coner_dis || r_Distance > coner_dis){
						break;
					}
				}
			}
			else if (l_Distance > u_distance_l){
				break;
			}


		}


	}
	else {
		while (c_Distance >= con_dis){
			FORWARD();
			if (c_Distance < con_dis || r_Distance < con_dis || l_Distance < con_dis){
				break;
			}


		}
	}






}



void START()
{
	if(c_Distance < 20)
	{
		if(r_Distance > l_Distance)
		{
			RIGHTTURN();
		}
		if(r_Distance < l_Distance)
		{
			LEFTTURN();
		}
		else if (c_Distance < 5)
		{
			BACKWARD();
		}
	}

	else if(r_Distance < 20)
	{
		if(c_Distance > 20)
		{
			FORWARD();
			if(r_Distance < 15)
			{
				STOP();
				LEFTTURN();
			}
			if(l_Distance < 15)
			{
				STOP();
				RIGHTTURN();
			}
		}
//		else if (c_Distance < 5)
//		{
//			BACKWARD();
//		}
		else if(c_Distance < 20)
		{
			if(r_Distance > l_Distance)
			{
				STOP();
				RIGHTTURN();
			}
			if(r_Distance < l_Distance)
			{
				STOP();
				LEFTTURN();
			}
		}

	}

	else if(l_Distance < 20)
	{
		if(c_Distance > 20)
		{
			FORWARD();
			if(r_Distance < 15)
			{
				STOP();
				LEFTTURN();
			}
			if(l_Distance < 15)
			{
				STOP();
				RIGHTTURN();
			}
		}
//		else if (c_Distance < 5)
//		{
//			BACKWARD();
//		}
		else if(c_Distance < 20)
		{
			if(r_Distance > l_Distance)
			{
				STOP();
				RIGHTTURN();
			}
			if(r_Distance < l_Distance)
			{
				STOP();
				LEFTTURN();
			}
		}
	}

	else
	{
		FORWARD();
	}
}


void SPEED()
{
	TIM3->CCR1 = 700;
	TIM3->CCR2 = 700;

	if(TIM3->CCR1 >= 1000 || TIM3->CCR2 >= 1000)
	{
		TIM3->CCR1 = 1000;
		TIM3->CCR2 = 1000;
	}
	else
	{
		if(rxData[0] == 'i')
		{
			TIM3->CCR1 += 100;
			TIM3->CCR2 += 100;
		}
	}

	if(TIM3->CCR1 < 700 || TIM3->CCR2 < 700)
	{
		TIM3->CCR1 = 700;
		TIM3->CCR2 = 700;
	}
	else
	{
		if(rxData[0] == 'm')
		{
			TIM3->CCR1 -= 100;
			TIM3->CCR2 -= 100;
		}
	}
}
