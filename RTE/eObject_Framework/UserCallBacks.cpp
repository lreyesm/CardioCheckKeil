/********************************************************************************
 * @file   UserCallBacks.cpp
 * @author Ing. Manuel Alejandro Linares Páez
 * @version 0.1.0
 * @date    TODO:
 * @brief   This file will gather the callback implementations for all peripherals
 * @details TODO:
 *******************************************************************************/

/******************************************************************************
 * Este ejemplo demuestra como implementar una función callback de un periférico
 * determinado, en este caso el callback de período transcurrido de los timers.
 ******************************************************************************/

/********************************************************************************
#include "../Include/TestProgram.h"
#include "tim.h"

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef *htim){
    switch (reinterpret_cast<std::uint32_t>(htim->Instance)){
    case TIM6_BASE:
        Test::TestProgram::GetInstance()->testThread.SignalSet(NFramework::OS::IOsThreadSupport::SIGNAL_FLAG_1);
        break;
    case TIM7_BASE:
        Test::TestProgram::GetInstance()->testThread.SignalSet(NFramework::OS::IOsThreadSupport::SIGNAL_FLAG_2);
        break;
    default:
        break;
    }
}
**********************************************************************************/
#include "../Include/Main_Thread.h"
#include "usart.h"
#include "adc.h"

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

    //uint32_t val[3];
    if(hadc->Instance == ADC1){

        //val[0]= Main_Thread::instance().adc_value;
			  Main_Thread::instance().thread_Read_ADC.eventSet(Main_Thread::Timer_timer_ADCPeriodic_Complete);
    }
}

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef *htim){

	  if(htim->Instance == TIM2){
       //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }   
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2){
        Main_Thread::instance().thread_Process_CH0.eventSet(Main_Thread::INIT_PROCESS_CH0_FULL);
    }
    if(huart->Instance == USART3){
        Main_Thread::instance().thread_Process_CH1.eventSet(Main_Thread::INIT_PROCESS_CH1_FULL);
    }
		if(huart->Instance == USART6){
        Main_Thread::instance().process_Receive_Commands.eventSet(Main_Thread::RECEIVE_COMMANDS);
    }
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){

    if(huart->Instance == USART2){
        Main_Thread::instance().thread_Process_CH0.eventSet(Main_Thread::INIT_PROCESS_CH0_HALF);
    }
    if(huart->Instance == USART3){
        Main_Thread::instance().thread_Process_CH1.eventSet(Main_Thread::INIT_PROCESS_CH1_HALF);
    }
		if(huart->Instance == USART6){
        //Main_Thread::instance().thread_Process_CH1.eventSet(Main_Thread::INIT_PROCESS_CH1_HALF);
    }
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2){
        //Main_Thread::instance().thread_Process_CH0.eventSet(Main_Thread::INIT_PROCESS_CH0_FULL);
    }
    if(huart->Instance == USART3){
        //Main_Thread::instance().thread_Process_CH1.eventSet(Main_Thread::INIT_PROCESS_CH1_FULL);
    }
		if(huart->Instance == USART6){
        //Main_Thread::instance().thread_Process_CH1.eventSet(Main_Thread::INIT_PROCESS_CH1_FULL);
			  if(Main_Thread::instance().buffer_transmit == Main_Thread::BUFFER_TRANSMIT_0){
			  	  Main_Thread::instance().transmit_buffer_0[STATUS_CHECK_BEAT] = 0x0FF;
				}
				else{
			  	  Main_Thread::instance().transmit_buffer_1[STATUS_CHECK_BEAT] = 0x0FF;
				}
    }
}

