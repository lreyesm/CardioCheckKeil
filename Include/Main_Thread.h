#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H


#include <eApplicationBase.h>
#include <eVirtualTimer.h>

#include <eThread.h>

#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "tim.h"

#include "arm_math.h"

//#define OXIMETER_ONE
#define OXIMETER_DUAL
//#define OXIMETER_DUAL_ADC

#define FUNCTION_BUFFER_SIZE 25
#define FUNCTION_BUFFER_SIZE_TOTAL FUNCTION_BUFFER_SIZE*2
#define FUNCTION_BUFFER_STORAGE_SIZE FUNCTION_BUFFER_SIZE*4

#define ADC_BUFFER_SIZE 100
#define ADC_BUFFER_SIZE_IN_8BITS ADC_BUFFER_SIZE*2
#define ADC_BUFFER_STORAGE_SIZE ADC_BUFFER_SIZE*4
#define TIMER_TIMEOUT_ADC_READ 4 ////en milisegundos

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define HEADER_ID 0x0FA
//#define TAIL_ID 0x0FA
#define HEADER_START_POS 0
//#define TAIL_START_POS 162
#define HEADER_SIZE 2
//#define TAIL_SIZE 2
#define CHECK_SUM_SIZE 4 //32bits

#define DATA_INIT_BUFFER_POS HEADER_START_POS + HEADER_SIZE  //2
#define DATA_INIT_BUFFER_ID 0x09B
//#define DATA_BUFFER_TRANSMIT_0 0x011
//#define DATA_BUFFER_TRANSMIT_1 0x022
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OXIMETER_1_ACTIVE  1  //CH0 el pegado a la fuente
#define OXIMETER_2_ACTIVE  1  //CH1 el de mas arriba
#define ADC_ACTIVE         1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SPO2_BUFFER_OXY1_POS DATA_INIT_BUFFER_POS //2
#define BPM_BUFFER_OXY1_POS SPO2_BUFFER_OXY1_POS+1 //3
#define PI_BUFFER_OXY1_POS SPO2_BUFFER_OXY1_POS+3 //5
#define SPO2_BUFFER_OXY2_POS PI_BUFFER_OXY1_POS+2 //7
#define BPM_BUFFER_OXY2_POS SPO2_BUFFER_OXY2_POS+1 //8
#define PI_BUFFER_OXY2_POS SPO2_BUFFER_OXY2_POS+3 //10

#define DESPLAZAMIENTO_EN_ENVIO_DE_PROMEDIOS 5

#define DATA_GRAPH_HR_INIT_BUFFER_POS DATA_INIT_BUFFER_POS+10 //12
#define DATA_GRAPH_FT_INIT_BUFFER_POS DATA_GRAPH_HR_INIT_BUFFER_POS + ADC_BUFFER_SIZE*2 //212 //por 2 porque adc buffer es de 16bits
#define DATA_GRAPH_FT_2_INIT_BUFFER_POS DATA_GRAPH_FT_INIT_BUFFER_POS+FUNCTION_BUFFER_SIZE //237

#define CHECKING_CONNECTION  0x0AC ////Chequeando conexion solo para android
#define ACKNOWLEDGE_END_OF_RECORDING  0x0AF ////acknowledge de fin de grabacion y salvar en BD
#define INIT_PROG_ID 0x0AA   ////Inicio de Programa
#define INIT_SEND_ID 0x0FE  ////Inicio de Envio de informacion
#define INIT_SAVE_TO_SD 0x0FD  ////Inicio de salva de informacion en SD
#define STOP_SAVE_TO_SD 0x0FC  ////Fin de salva de informacion en SD
#define ERROR_ID 0x0F  ////Envio de Error de recivo

//#define HEADER_END_POS 160

//#define CURRENT_OXYMETER_OXY1_POS DATA_INIT_BUFFER_POS+1 //3
#define STATUS_CHECK_ADC_0 DATA_GRAPH_FT_2_INIT_BUFFER_POS+FUNCTION_BUFFER_SIZE //262 ----------Enviar aqui status de electrodos -------------------
#define STATUS_CHECK_ADC_1 STATUS_CHECK_ADC_0 + 1 //263
#define STATUS_CHECK_OXY1_POS STATUS_CHECK_ADC_1 + 1//264
#define STATUS_CHECK_OXY2_POS STATUS_CHECK_OXY1_POS+1 //265

//#define CURRENT_OXYMETER_OXY2_POS DATA_GRAPH_FT_INIT_BUFFER_POS+(FUNCTION_BUFFER_SIZE*2) //260
//#define SPO2_BUFFER_OXY2_POS CURRENT_OXYMETER_OXY2_POS //260

#define UART_SEND_BUFFER_SIZE STATUS_CHECK_OXY2_POS + 1 //266
#define UART_SEND_TOTAL_SIZE UART_SEND_BUFFER_SIZE + CHECK_SUM_SIZE //270

#define UART_READ_BUFFER_SIZE 256

#define MAX_TIME_RECORDING 300////en segundos (solo valores pares)
#define DATA_FUNCTION_SIZE  (int)(FUNCTION_BUFFER_SIZE*MAX_TIME_RECORDING*2.5)  ////FUNCTION_BUFFER_SIZE * 150
#define DATA_ADC_BUFFER_SIZE  (int)(ADC_BUFFER_SIZE*MAX_TIME_RECORDING*2.5)  ////
#define DATA_ADC_BUFFER_SIZE_8BITS  DATA_ADC_BUFFER_SIZE*2 
#define SPO2_TIME_RECORDING MAX_TIME_RECORDING //en segundos
#define SPO2_FUNCTION_BUFFER_SIZE int(SPO2_TIME_RECORDING*2.5)
#define BPM_FUNCTION_BUFFER_SIZE SPO2_FUNCTION_BUFFER_SIZE //EN 16BITS
#define BPM_FUNCTION_BUFFER_SIZE_8BITS BPM_FUNCTION_BUFFER_SIZE*2 //EN 8BITS
#define PI_FUNCTION_BUFFER_SIZE SPO2_FUNCTION_BUFFER_SIZE  //EN 16BITS
#define PI_FUNCTION_BUFFER_SIZE_8BITS PI_FUNCTION_BUFFER_SIZE*2 //EN 8BITS

#define TOTAL_SIGNALS_SIZE DATA_FUNCTION_SIZE*2+DATA_ADC_BUFFER_SIZE*2+SPO2_FUNCTION_BUFFER_SIZE*2+BPM_FUNCTION_BUFFER_SIZE*4+PI_FUNCTION_BUFFER_SIZE*4

//#define TEST_LENGTH_SAMPLES  320
#define SNR_THRESHOLD_F32    140.0f
#define BLOCK_SIZE            ADC_BUFFER_SIZE
#define NUM_TAPS              30 //Specific Order de filtro de Matlab + 1

using namespace eObject;

class Main_Thread:public eObject::eApplicationBase<Main_Thread>
{
public:
    static void timeOut_timer_led_green_function(void const *argument);    /*End of Timer public definitions*/
    
    static void timeOut_timer_led_red_function(void const *argument);    /*End of Timer public definitions*/
    
    /*Timer public definitions*/
    enum Timer_Events{
        Timer_timer_led_greenPeriodic_Complete, /*Put the correct number to the event (binary number 1,2,4,8...)*/
        Timer_timer_led_redPeriodic_Complete, /*Put the correct number to the event (binary number 1,2,4,8...)*/
        Timer_timer_ledsPeriodic_Complete /*Put the correct number to the event (binary number 1,2,4,8...)*/    };

    static void timeOut_timer_leds_function(void const *argument);    /*End of Timer public definitions*/
    
    static const std::uint16_t INIT_PROCESS_CH0_HALF = eObject::eThread::EventFlag2; // me salte una pila de flags y puse #23 preguntar a tony por esto
    
    static const std::uint16_t INIT_PROCESS_CH0_FULL = eObject::eThread::EventFlag3;

    static const std::uint16_t INIT_PROCESS_CH1_HALF = eObject::eThread::EventFlag4; // me salte una pila de flags y puse #23 preguntar a tony por esto

    static const std::uint16_t INIT_PROCESS_CH1_FULL = eObject::eThread::EventFlag5;

    static const std::uint16_t INIT_TRANSMIT = eObject::eThread::EventFlag6;

    static const std::uint16_t Timer_timer_ADCPeriodic_Complete = eObject::eThread::EventFlag7;

    static const std::uint16_t INIT_PROGRAM = eObject::eThread::EventFlag8;

    static const std::uint16_t RECEIVE_COMMANDS = eObject::eThread::EventFlag9;

    static const std::uint16_t SAVE_TO_SD = eObject::eThread::EventFlag10;

    static const std::uint16_t STOP_SAVING_TO_SD = eObject::eThread::EventFlag11;


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
    static bool CH0_init_Ready;
    static bool CH1_Ready;
    static bool CH1_init_Ready;
    static bool ADC_Ready;
    static bool ADC_Init_Ready;
    static bool start_transmit_ftdi;
    static bool already_saved_data;
    static bool error_sending;
    static bool saving_to_sd;
		static bool primera_vuelta;
		static bool amarillo_desconectado;
		static bool rojo_desconectado;
		static bool verde_desconectado;
		static bool AD8232_encendido;
		static bool AD8232_orden_encender;
		
		static std::uint32_t ekg_data_size;
		static std::uint32_t oxy_data_size;
		static std::uint32_t SPO2_BPM_PI_data_size;

    static std::uint8_t write_buff[UART_SEND_TOTAL_SIZE];

    static std::uint8_t CH0_read_buffer_0[UART_READ_BUFFER_SIZE];
    static std::uint8_t CH1_read_buffer_0[UART_READ_BUFFER_SIZE];

    static std::uint8_t CH3_read_buffer_0[UART_READ_BUFFER_SIZE];
    static std::uint8_t save_to_SD_buffer_0[UART_READ_BUFFER_SIZE];
    static std::uint8_t save_to_SD_buffer_signals[UART_READ_BUFFER_SIZE  + 10];

    static std::uint8_t size_of_save_to_SD_buffer_0;
    static std::uint32_t function_value_pos_in_SD;
    static std::uint32_t HR_value_pos_in_SD;
		static std::uint32_t SPO2_BPM_PI_value_pos_in_SD;

    static std::uint8_t CH0_function_buffer_0[FUNCTION_BUFFER_SIZE];
    static std::uint8_t CH0_function_buffer_storage_0[FUNCTION_BUFFER_STORAGE_SIZE];
    static std::uint32_t CH0_function_buffer_storage_pos;

    static std::uint8_t CH1_function_buffer_0[FUNCTION_BUFFER_SIZE];
    static std::uint8_t CH1_function_buffer_storage_0[FUNCTION_BUFFER_STORAGE_SIZE];
    static std::uint32_t CH1_function_buffer_storage_pos;

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
    static std::uint16_t ADC_buffer_storage[ADC_BUFFER_STORAGE_SIZE];
    static std::uint32_t ADC_buffer_pos;
    static std::uint32_t ADC_buffer_storage_pos;



    static void setBufferOffset(const BUFFER_StateTypeDef);
    /*User declare thread objects*/
    eObject::eThread process_Receive_Commands;

    eObject::eThread thread_Read_ADC;

    eObject::eThread thread_Process_CH1;

    eObject::eThread thread_Process_CH0;

    /*End of User declare thread objects*/

    void process_9A_buff_CH0(std::uint8_t function_value);
    void process_9A_buff_CH1(std::uint8_t function_value);

private:

    static FILE *file;
    static long fileSize;

    eVirtualTimer timer_timer_led_green;

    static const std::uint32_t TIMER_timer_led_green_PERIOD_MS = 2000;

    eVirtualTimer timer_timer_led_red;

    static const std::uint32_t TIMER_timer_led_red_PERIOD_MS = 1000;

    eVirtualTimer timer_timer_leds;

    static const std::uint32_t TIMER_timer_leds_PERIOD_MS = 5000;  ///Led azul

    eVirtualTimer timer_timer_ADC;

    static const std::uint32_t TIMER_timer_ADC_PERIOD_MS = TIMER_TIMEOUT_ADC_READ; //sustituir este timer por el TIM2 para iniciar conversion


    /*User declare thread objects functions*/
    static void process_Receive_CommandsRun(eObject::eThread &thread);

    static void thread_Read_ADCRun(eObject::eThread &thread);

    static void thread_Process_CH1Run(eObject::eThread &thread);

    static void thread_Process_CH0Run(eObject::eThread &thread);
    /*End of User declare thread objects functions*/

    static BUFFER_StateTypeDef buffer_transmit;

    uint32_t crc32(const void *buf, size_t size);

    static bool save_to_file_pacient_data(void);
    static bool save_to_file_pacient_signals(const uint16_t size);
    static bool check_if_SD_is_functional(void);

    static bool save_pacient_data_to_database(void);
    static bool save_pacient_signals_to_database(void);
		static bool save_pacient_signals_to_database_primera_vuelta(void);
		static bool change_places(uint32_t pos, uint32_t last_pos, uint32_t max_lenght);
		
		static void set_pin_as_analog(GPIO_TypeDef *GPIOx, uint16_t PINx);
		static bool electrodo_amarillo_desconectado(void);
		static bool electrodo_rojo_desconectado(void);
		static bool electrodo_verde_desconectado(void);

};


#endif // MAIN_THREAD_H
