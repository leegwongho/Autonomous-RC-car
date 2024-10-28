/*
 * ultrasonic.c
 *
 *  Created on: Oct 10, 2024
 *      Author: Parkdongjin
 */


#include "ultrasonic.h"

uint16_t center_VALUE1 = 0;
uint16_t center_VALUE2 = 0;
uint16_t right_VALUE1 = 0;
uint16_t right_VALUE2 = 0;
uint16_t left_VALUE1 = 0;
uint16_t left_VALUE2 = 0;

uint16_t centerEcho = 0;
uint16_t rightEcho = 0;
uint16_t leftEcho = 0;

uint8_t centerFlag = 0;
uint8_t rightFlag = 0;
uint8_t leftFlag = 0;

uint8_t c_Distance = 0;
uint8_t r_Distance = 0;
uint8_t l_Distance = 0;

//center = tim5_ch1(PA0)		right = tim5_ch2(PA1)		left = tim5_ch3(PA2)
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	if((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && (htim -> Instance == TIM5))
	{
		if(centerFlag == 0)
		{
			center_VALUE1 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_1);
			centerFlag = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if(centerFlag == 1)
		{
			center_VALUE2 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_1);

			if(center_VALUE2 > center_VALUE1)
			{
				centerEcho = center_VALUE2 - center_VALUE1;
			}
			else if(center_VALUE1 > center_VALUE2)	//overflow
			{
				centerEcho = (0xffff - center_VALUE1) + center_VALUE2;
			}
			c_Distance = centerEcho/58;
			centerFlag = 0;
			if(c_Distance >= 50)
			{
				c_Distance = 50;
			}
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim5, TIM_IT_CC1);
		}
	}

	if((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) && (htim -> Instance == TIM5))
	{
			if(rightFlag == 0)
			{
				right_VALUE1 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2);
				rightFlag = 1;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
			}
			else if(rightFlag == 1)
			{
				right_VALUE2 = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2);
				// __HAL_TIM_SET_COUNTER(&htim5, 0);

				if(right_VALUE2 > right_VALUE1)
				{
					rightEcho = right_VALUE2 - right_VALUE1;
				}
				else if(right_VALUE1 > right_VALUE2)	//overflow
				{
					rightEcho = (0xffff - right_VALUE1) + right_VALUE2;
				}
				r_Distance = rightEcho/58;
				rightFlag = 0;
				if(r_Distance >= 50)
				{
					r_Distance = 50;
				}
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
				__HAL_TIM_DISABLE_IT(&htim5, TIM_IT_CC2);
			}
		}


	if((htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) && (htim -> Instance == TIM4))
	{
			if(leftFlag == 0)
			{
				left_VALUE1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
				leftFlag = 1;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_FALLING);
			}
			else if(leftFlag == 1)
			{
				left_VALUE2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
				// __HAL_TIM_SET_COUNTER(&htim5, 0);

				if(left_VALUE2 > left_VALUE1)
				{
					leftEcho = left_VALUE2 - left_VALUE1;
				}
				else if(left_VALUE1 > left_VALUE2)	//overflow
				{
					leftEcho = (0xffff - left_VALUE1) + left_VALUE2;
				}
				l_Distance = leftEcho/58;
				leftFlag = 0;
				if(l_Distance >= 50)
				{
					l_Distance = 50;
				}
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_RISING);
				__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_CC4);
			}
		}
}

void HCSR04_read_ch1()
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_Delay(10);  //10
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

    __HAL_TIM_SET_COUNTER(&htim5, 0);
    // 타이머 채널에 대한 인터럽트 활성화
    __HAL_TIM_ENABLE_IT(&htim5, TIM_IT_CC1);
//    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC2);
//    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC3);
}

void HCSR04_read_ch2()
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
    HAL_Delay(10);  //10
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

    __HAL_TIM_SET_COUNTER(&htim5, 0);
    __HAL_TIM_ENABLE_IT(&htim5, TIM_IT_CC2);

}

void HCSR04_read_ch3()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_Delay(10);  //10
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

    __HAL_TIM_SET_COUNTER(&htim4, 0);
    __HAL_TIM_ENABLE_IT(&htim4, TIM_IT_CC4);
}
