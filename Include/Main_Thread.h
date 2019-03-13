#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H


#include <eApplicationBase.h>
#include <eVirtualTimer.h>

#include <eThread.h>

#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

#include "arm_math.h"

//#define OXIMETER_ONE
#define OXIMETER_DUAL
//#define OXIMETER_DUAL_ADC

#define FUNCTION_BUFFER_SIZE 25

#define ADC_BUFFER_SIZE 100
#define ADC_BUFFER_STORAGE_SIZE ADC_BUFFER_SIZE*4
#define TIMER_TIMEOUT_ADC_READ 4 ////en milisegundos

#define DATA_INIT_BUFFER_POS 4
#define DATA_INIT_BUFFER_ID 0x09B
#define DATA_BUFFER_TRANSMIT_0 0x011
#define DATA_BUFFER_TRANSMIT_1 0x022
#define SPO2_BUFFER_POS 5
#define BPM_BUFFER_POS 6
#define PI_BUFFER_POS 8
#define DATA_GRAPH_HR_INIT_BUFFER_POS 10
#define DATA_GRAPH_FT_INIT_BUFFER_POS DATA_GRAPH_HR_INIT_BUFFER_POS+ADC_BUFFER_SIZE
#define DATA_GRAPH_FT_2_INIT_BUFFER_POS DATA_GRAPH_FT_INIT_BUFFER_POS+FUNCTION_BUFFER_SIZE

#define ERROR_ID 0x0F
#define HEADER_ID 0x0FA
#define HEADER_START_POS 0
#define HEADER_END_POS DATA_GRAPH_FT_INIT_BUFFER_POS+(FUNCTION_BUFFER_SIZE*2)
#define HEADER_SIZE 4

#define UART_SEND_BUFFER_SIZE HEADER_END_POS+HEADER_SIZE
#define UART_SEND_TOTAL_SIZE UART_SEND_BUFFER_SIZE+4

#define UART_READ_BUFFER_SIZE 256

//#define TEST_LENGTH_SAMPLES  320
#define SNR_THRESHOLD_F32    140.0f
#define BLOCK_SIZE            ADC_BUFFER_SIZE
#define NUM_TAPS              29

using namespace eObject;

class Main_Thread:public eObject::eApplicationBase<Main_Thread>
{
public:
   static const std::uint16_t INIT_PROCESS_CH0_HALF = eObject::eThread::EventFlag2; // me salte una pila de flags y puse #23 preguntar a tony por esto
    
   static const std::uint16_t INIT_PROCESS_CH0_FULL = eObject::eThread::EventFlag3;

   static const std::uint16_t INIT_PROCESS_CH1_HALF = eObject::eThread::EventFlag4; // me salte una pila de flags y puse #23 preguntar a tony por esto

   static const std::uint16_t INIT_PROCESS_CH1_FULL = eObject::eThread::EventFlag5;
  
   static const std::uint16_t INIT_TRANSMIT = eObject::eThread::EventFlag6;
  
   static const std::uint16_t Timer_timer_ADCPeriodic_Complete = eObject::eThread::EventFlag7;

   static const std::uint16_t INIT_PROGRAM = eObject::eThread::EventFlag8;

   static const std::uint16_t RECEIVE_COMMANDS = eObject::eThread::EventFlag9;
   
   
static void timer_ADC_timeout(void const *argument);    /*End of Timer public definitions*/
    
    /*Main thread Constructor*/
    Main_Thread();

typedef enum{
	BUFFER_TRANSMIT_0 = 0,
	BUFFER_TRANSMIT_1,
	BUFFER_TRANSMIT_NONE,
}BUFFER_StateTypeDef;

    ////Main function, this function is executed infinitely when app.exec() in main.cpp
    virtual void userLoop() E_DECLARE_OVERRIDE;

    static bool CH0_Ready;
    static bool CH1_Ready;
    static bool ADC_Ready;
    static bool start_transmit_ftdi;
    static bool start_transmit_bluetooth;

    static std::uint8_t write_buff[UART_SEND_TOTAL_SIZE];

    static std::uint8_t CH0_read_buffer_0[UART_READ_BUFFER_SIZE];
    static std::uint8_t CH1_read_buffer_0[UART_READ_BUFFER_SIZE];
    static std::uint8_t CH2_read_buffer_0[16];
    static std::uint8_t CH3_read_buffer_0[16];

    static std::uint8_t CH0_function_buffer_0[FUNCTION_BUFFER_SIZE];
    static std::uint8_t CH1_function_buffer_0[FUNCTION_BUFFER_SIZE];

    static std::uint8_t transmit_buffer_0[UART_SEND_BUFFER_SIZE];
    static std::uint8_t transmit_buffer_1[UART_SEND_BUFFER_SIZE];

    static std::uint8_t CH0_processsing_buffer_0[UART_READ_BUFFER_SIZE/2];
    static std::uint8_t CH0_processsing_buffer_1[UART_READ_BUFFER_SIZE/2];

    static std::uint8_t CH1_processsing_buffer_0[UART_READ_BUFFER_SIZE/2];
    static std::uint8_t CH1_processsing_buffer_1[UART_READ_BUFFER_SIZE/2];

    static std::uint16_t CH0_buffer_pos;
    static std::uint16_t CH1_buffer_pos;

    static std::uint32_t adc_value;
    static std::uint16_t ADC_buffer[ADC_BUFFER_SIZE];
    static std::uint8_t ADC_buffer_storage[ADC_BUFFER_STORAGE_SIZE];
    static std::uint32_t ADC_buffer_pos;
    static std::uint32_t ADC_buffer_storage_pos;


    static void setBufferOffset(const BUFFER_StateTypeDef);
    /*User declare thread objects*/
    eObject::eThread process_Receive_Commands;

    eObject::eThread thread_Read_ADC;

    eObject::eThread thread_Process_CH1;

    eObject::eThread thread_Process_CH0;

    eObject::eThread thread_transmit;

    /*End of User declare thread objects*/

    void process_9A_buff_CH0(std::uint8_t function_value);
    void process_9A_buff_CH1(std::uint8_t function_value);

private:
    eVirtualTimer timer_timer_ADC;

    static const std::uint32_t TIMER_timer_ADC_PERIOD_MS = TIMER_TIMEOUT_ADC_READ;


    /*User declare thread objects functions*/
    static void process_Receive_CommandsRun(eObject::eThread &thread);

    static void thread_Read_ADCRun(eObject::eThread &thread);

    static void thread_Process_CH1Run(eObject::eThread &thread);

    static void thread_Process_CH0Run(eObject::eThread &thread);

    static void thread_transmitRun(eObject::eThread &thread);

    static void process_second_halfRun(eObject::eThread &thread);

    static void process_first_halfRun(eObject::eThread &thread);
    /*End of User declare thread objects functions*/

    static BUFFER_StateTypeDef buffer_transmit;

    uint32_t crc32(const void *buf, size_t size);

};


#endif // MAIN_THREAD_H
