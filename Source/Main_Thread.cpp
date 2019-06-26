#include "Main_Thread.h"

#include "rl_fs.h"


uint32_t oxy1=0;
uint32_t oxy2=0;

const uint32_t crc32_tab[] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
    0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
    0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
    0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

Main_Thread::BUFFER_StateTypeDef Main_Thread::buffer_transmit = BUFFER_TRANSMIT_0;

bool Main_Thread::CH0_Ready = false;
bool Main_Thread::CH0_init_Ready = false;
bool Main_Thread::CH1_Ready = false;
bool Main_Thread::CH1_init_Ready = false;
bool Main_Thread::ADC_Ready = false;
bool Main_Thread::ADC_Init_Ready = false;
bool Main_Thread::start_transmit_ftdi = false;
bool Main_Thread::start_transmit_bluetooth = false;
bool Main_Thread::error_sending = false;
bool Main_Thread::saving_to_sd = false;
FILE* Main_Thread::file;

std::uint8_t Main_Thread::write_buff[UART_SEND_TOTAL_SIZE];

std::uint8_t Main_Thread::CH0_read_buffer_0[UART_READ_BUFFER_SIZE];
std::uint8_t Main_Thread::CH1_read_buffer_0[UART_READ_BUFFER_SIZE];

std::uint8_t Main_Thread::CH3_read_buffer_0[UART_READ_BUFFER_SIZE];
std::uint8_t Main_Thread::save_to_SD_buffer_0[UART_READ_BUFFER_SIZE];
std::uint8_t Main_Thread::save_to_SD_buffer_signals[UART_READ_BUFFER_SIZE];
std::uint8_t Main_Thread::size_of_save_to_SD_buffer_0 = 0;
std::uint32_t Main_Thread::function_value_pos_in_SD = 0;
std::uint32_t Main_Thread::HR_value_pos_in_SD=0;

std::uint8_t Main_Thread::CH0_function_buffer_0[FUNCTION_BUFFER_SIZE];
std::uint8_t Main_Thread::CH0_function_buffer_storage_0[FUNCTION_BUFFER_STORAGE_SIZE];
std::uint32_t Main_Thread::CH0_function_buffer_storage_pos=0;

std::uint8_t Main_Thread::CH1_function_buffer_0[FUNCTION_BUFFER_SIZE];
std::uint8_t Main_Thread::CH1_function_buffer_storage_0[FUNCTION_BUFFER_STORAGE_SIZE];
std::uint32_t Main_Thread::CH1_function_buffer_storage_pos=0;

std::uint8_t Main_Thread::CH0_processsing_buffer_0[UART_READ_BUFFER_SIZE/2];
std::uint8_t Main_Thread::CH0_processsing_buffer_1[UART_READ_BUFFER_SIZE/2];

std::uint8_t Main_Thread::CH1_processsing_buffer_0[UART_READ_BUFFER_SIZE/2];
std::uint8_t Main_Thread::CH1_processsing_buffer_1[UART_READ_BUFFER_SIZE/2];

std::uint8_t Main_Thread::transmit_buffer_0[UART_SEND_BUFFER_SIZE];
std::uint8_t Main_Thread::transmit_buffer_1[UART_SEND_BUFFER_SIZE];

uint16_t Main_Thread::CH0_buffer_pos = 0;
uint16_t Main_Thread::CH1_buffer_pos = 0;

std::uint32_t Main_Thread::adc_value=0;
std::uint16_t Main_Thread::ADC_buffer[ADC_BUFFER_SIZE];
std::uint16_t Main_Thread::ADC_buffer_storage[ADC_BUFFER_STORAGE_SIZE];
std::uint32_t Main_Thread::ADC_buffer_pos=0;
std::uint32_t Main_Thread::ADC_buffer_storage_pos=0;

const float32_t fir_coefficient[NUM_TAPS]={

    +0.0010103811860354812, -0.00045811610763767032, -0.0030991693162776006, -0.0054070422836590172,-0.0035905054695007255,
    +0.0044893161407239777 ,+ 0.013556796147238726,+ 0.011433006469166862 ,-0.010029928664181082 ,-0.041107603536671908 ,
    -0.05244351602413698 ,-0.01312328930103062 ,+ 0.081971636676991505 , + 0.19861232633402243 ,+0.27904465702901166   ,
    +0.27904465702901166  ,+0.19861232633402243 , +0.081971636676991505 ,-0.01312328930103062 ,-0.05244351602413698 ,
    -0.041107603536671908  , -0.010029928664181082 ,+ 0.011433006469166862 ,+0.013556796147238726 ,+0.0044893161407239777,
    -0.0035905054695007255 , -0.0054070422836590172  ,-0.0030991693162776006 , -0.00045811610763767032,+ 0.0010103811860354812
};

const float32_t fir_coefficient_250Hz_Order10[NUM_TAPS]={

    -0.005218989906672902 , -0.0074937206692433722,  0.01493805854856124  ,  0.10685006477929745 ,  0.23896227610234308  ,
    0.30392462229142903  ,  0.23896227610234308  ,  0.10685006477929745  , 0.01493805854856124  , -0.0074937206692433722, -0.005218989906672902
};

const float32_t fir_coefficient_500Hz[NUM_TAPS]={

    +0.0053145402913309919 , +0.018327611671120649  , +0.059495137562790477  , +0.12457336692876832   ,  +0.18635946467144601  ,
    +0.21185975774908705  ,  +0.18635946467144601  , +0.12457336692876832  , +0.059495137562790477  , +0.018327611671120649  , +0.0053145402913309919
};

static float32_t  firState_f32[BLOCK_SIZE + NUM_TAPS - 1];
static uint32_t blockSize = BLOCK_SIZE;

/*Main Thread Constructor Generated Code*/
Main_Thread::Main_Thread():
    timer_timer_led_green(timeOut_timer_led_green_function, eVirtualTimer::Periodic),
    timer_timer_led_red(timeOut_timer_led_red_function, eVirtualTimer::Periodic),
    timer_timer_leds(timeOut_timer_leds_function, eVirtualTimer::Periodic),
    process_Receive_Commands(process_Receive_CommandsRun,eObject::eThread::PriorityNormal ),
    thread_Read_ADC(thread_Read_ADCRun,eObject::eThread::PriorityNormal ),
    thread_Process_CH1(thread_Process_CH1Run,eObject::eThread::PriorityNormal ),
    thread_Process_CH0(thread_Process_CH0Run,eObject::eThread::PriorityNormal ),
    timer_timer_ADC(timer_ADC_timeout, eVirtualTimer::Periodic)
{

    timer_timer_leds.start(TIMER_timer_leds_PERIOD_MS);
    int i=0;

    for(i=0; i<UART_READ_BUFFER_SIZE ;++i){

        Main_Thread::instance().save_to_SD_buffer_signals[i]=0;

    }

    for(i=0; i<UART_SEND_BUFFER_SIZE ;++i){

        Main_Thread::instance().transmit_buffer_0[i]=0;
        Main_Thread::instance().transmit_buffer_1[i]=0;
    }

    for(i=HEADER_START_POS; i<HEADER_SIZE ;++i){
        Main_Thread::instance().transmit_buffer_0[i]=HEADER_ID;
        Main_Thread::instance().transmit_buffer_1[i]=HEADER_ID;
    }

    process_Receive_Commands.start();

    //HAL_UART_Receive_DMA(&huart1, &CH2_read_buffer_0[0], 16);
    HAL_UART_Receive_DMA(&huart6, &CH3_read_buffer_0[0], UART_READ_BUFFER_SIZE);

    thread_Process_CH0.start();

    //		#ifdef OXIMETER_DUAL
    thread_Process_CH1.start();
    //	  #endif

    HAL_UART_Receive_DMA(&huart2, &CH0_read_buffer_0[0], UART_READ_BUFFER_SIZE);

    //		#ifdef OXIMETER_DUAL
    HAL_UART_Receive_DMA(&huart3, &CH1_read_buffer_0[0], UART_READ_BUFFER_SIZE);
    //		#endif

    HAL_ADC_Start_DMA(&hadc1, &adc_value, 1);
    thread_Read_ADC.start();
    HAL_TIM_Base_Start_IT(&htim2);
    //timer_timer_ADC.start(TIMER_timer_ADC_PERIOD_MS);
}
/*End of Main Thread Constructor Generated Code*/


void Main_Thread::process_9A_buff_CH0(std::uint8_t function_value){

    std::uint8_t local_function_value = function_value;
    CH0_function_buffer_0[CH0_buffer_pos] = function_value;

    if(CH0_function_buffer_0[CH0_buffer_pos] > 100){
        CH0_function_buffer_0[CH0_buffer_pos] = 0;
    }
    else if(CH0_function_buffer_0[CH0_buffer_pos] > 97 || CH0_function_buffer_0[CH0_buffer_pos] <= 0){

        if(CH0_buffer_pos == 0){
            CH0_function_buffer_0[CH0_buffer_pos]= CH0_function_buffer_0[FUNCTION_BUFFER_SIZE - 1];
        }
        else{
            CH0_function_buffer_0[CH0_buffer_pos]= CH0_function_buffer_0[CH0_buffer_pos - 1];
        }
    }
    CH0_buffer_pos++;

    if(CH0_buffer_pos >= FUNCTION_BUFFER_SIZE){

        CH0_buffer_pos=0;

        std::memcpy(&CH0_function_buffer_storage_0[CH0_function_buffer_storage_pos], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
        CH0_function_buffer_storage_pos += FUNCTION_BUFFER_SIZE;

        if(CH0_function_buffer_storage_pos >= FUNCTION_BUFFER_STORAGE_SIZE){
            CH0_function_buffer_storage_pos=0;
            Main_Thread::instance().CH0_init_Ready = true;
        }

        if(Main_Thread::instance().CH0_init_Ready){

            Main_Thread::instance().CH0_Ready = true;
            Main_Thread::instance().eventSet(Main_Thread::INIT_TRANSMIT);
        }
    }
}

void Main_Thread::process_9A_buff_CH1(std::uint8_t function_value){

    std::uint8_t local_function_value = function_value;
    CH1_function_buffer_0[CH1_buffer_pos] = function_value;

    if(CH1_function_buffer_0[CH1_buffer_pos] > 100){
        CH1_function_buffer_0[CH1_buffer_pos] = 0;
    }
    else if(CH1_function_buffer_0[CH1_buffer_pos] > 97  || CH1_function_buffer_0[CH1_buffer_pos] <= 0){

        if(CH1_buffer_pos == 0){
            CH1_function_buffer_0[CH1_buffer_pos]= CH1_function_buffer_0[FUNCTION_BUFFER_SIZE - 1];
        }
        else{
            CH1_function_buffer_0[CH1_buffer_pos]= CH1_function_buffer_0[CH1_buffer_pos - 1];
        }
    }

    CH1_buffer_pos++;

    if(CH1_buffer_pos >= FUNCTION_BUFFER_SIZE){

        CH1_buffer_pos=0;

        std::memcpy(&CH1_function_buffer_storage_0[CH1_function_buffer_storage_pos], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
        CH1_function_buffer_storage_pos += FUNCTION_BUFFER_SIZE;

        if(CH1_function_buffer_storage_pos >= FUNCTION_BUFFER_STORAGE_SIZE){
            CH1_function_buffer_storage_pos=0;
            Main_Thread::instance().CH1_init_Ready = true;
        }

        if(Main_Thread::instance().CH1_init_Ready){

            Main_Thread::instance().CH1_Ready = true;
            Main_Thread::instance().eventSet(Main_Thread::INIT_TRANSMIT);
        }
    }
}

void process_9B_buff_CH0(){}

bool Main_Thread::save_to_file_pacient_signals(const uint16_t size){

    uint32_t function_0_data_offset = size_of_save_to_SD_buffer_0 + 42 + function_value_pos_in_SD;
    uint32_t function_1_data_offset = size_of_save_to_SD_buffer_0 + 42 + DATA_FUNCTION_SIZE + function_value_pos_in_SD;
    uint32_t ADC_data_offset = size_of_save_to_SD_buffer_0 + 42 + (DATA_FUNCTION_SIZE*2) + HR_value_pos_in_SD;  ///Mas 56 por las variables de los tamaños de los buffers y promedios de valores

    file = fopen ("M:\\pacient_data_temp.dat","r+");

    if (file == NULL) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    }
    else {
        // write data to file
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

        fseek(file, function_0_data_offset, SEEK_SET); ///Escribe apartir del los datos del paciente para

        fwrite(&save_to_SD_buffer_signals[ADC_BUFFER_SIZE_IN_8BITS], sizeof (uint8_t), FUNCTION_BUFFER_SIZE , file);

        fseek(file, function_1_data_offset, SEEK_SET); ///Escribe apartir del los datos del paciente para

        fwrite(&save_to_SD_buffer_signals[ADC_BUFFER_SIZE_IN_8BITS + FUNCTION_BUFFER_SIZE], sizeof (uint8_t), FUNCTION_BUFFER_SIZE , file);

        fseek(file, ADC_data_offset, SEEK_SET); ///Escribe apartir del los datos del paciente para

        fwrite(&save_to_SD_buffer_signals[0], sizeof (uint8_t), ADC_BUFFER_SIZE_IN_8BITS , file);

        function_value_pos_in_SD += FUNCTION_BUFFER_SIZE;
        HR_value_pos_in_SD += ADC_BUFFER_SIZE_IN_8BITS;

        if(function_value_pos_in_SD >= DATA_FUNCTION_SIZE){

            function_value_pos_in_SD = 0;
            HR_value_pos_in_SD = 0;
        }

        fclose (file);

    }
}

bool Main_Thread::check_if_SD_is_functional(void){

    // Initialize the M: drive.
    if (finit ("M:") != fsOK) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    }
    // Mount the M: drive.
    if (fmount ("M:") != fsOK) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    }

    file = fopen ("M:\\test.dat","w");
    if (file == NULL) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }
    else {
        // write data to file
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        fclose (file);
    }
    funmount ("M:");
    funinit ("M:");
}

bool Main_Thread::save_to_file_pacient_data(void){


    // Initialize the M: drive.
    if (finit ("M:") != fsOK) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);

    }
    // Mount the M: drive.
    if (fmount ("M:") != fsOK) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);

    }
    // Update a log file on SD card.
    file = fopen ("M:\\pacient_data_temp.dat","w");
    if (file == NULL) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    }
    else {                                           //SPO2  BPM    PI        function size      ADC data Size
        uint32_t i = 0, sizes[8], sizes_reverse[8] = {DATA_FUNCTION_SIZE, DATA_ADC_BUFFER_SIZE,
                                                      SPO2_FUNCTION_BUFFER_SIZE, SPO2_FUNCTION_BUFFER_SIZE,
                                                      BPM_FUNCTION_BUFFER_SIZE, BPM_FUNCTION_BUFFER_SIZE,
                                                      PI_FUNCTION_BUFFER_SIZE, PI_FUNCTION_BUFFER_SIZE};
        uint8_t 	prom_values[10]={ 99, 99, 00, 72, 00, 72, 17, 148, 17, 148};

        for(i=0; i < 8; i++){  ////espacio para buffers

            sizes[i] = (sizes_reverse[i]<<24 & 0x0FF000000);
            sizes[i] |= (sizes_reverse[i]<<8 & 0x0FF0000);
            sizes[i] |= (sizes_reverse[i]>>8 & 0x0FF00);
            sizes[i] |= (sizes_reverse[i]>>24 & 0x0FF);
        }

        // write data to file
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        //fread (&count[0], sizeof (uint8_t), 44, f);
        fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),size_of_save_to_SD_buffer_0,file);  ///datos del paciente

        //fseek(file, size_of_save_to_SD_buffer_0, SEEK_SET);

        fwrite(prom_values, sizeof (uint8_t), 10, file); ///espacio para promedio de valores

        fwrite(sizes, sizeof (uint32_t), 8, file);  ///espacio para tamaño de buffers 14 * 4

        for(i=0; i < TOTAL_SIGNALS_SIZE; i+=250){  ////espacio para buffers

            fwrite(&save_to_SD_buffer_signals[0],sizeof (uint8_t), 250,file);
        }
        fclose (file);

    }
    // The drive is no more needed.
    //funmount ("M:");
    //funinit ("M:");
}


bool Main_Thread::save_pacient_data_to_database(void){

    file = fopen ("M:\\pacient_data_temp.dat","r");
    if (file == NULL) {
        // error handling
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

    }
    else {                                           //SPO2  BPM    PI        function size      ADC data Size
        uint32_t i = 0, sizes[8], sizes_reverse[8];/* = {DATA_FUNCTION_SIZE, DATA_ADC_BUFFER_SIZE,
                                                      SPO2_FUNCTION_BUFFER_SIZE, SPO2_FUNCTION_BUFFER_SIZE,
                                                      BPM_FUNCTION_BUFFER_SIZE, BPM_FUNCTION_BUFFER_SIZE,
                                                      PI_FUNCTION_BUFFER_SIZE, PI_FUNCTION_BUFFER_SIZE};*/
        uint8_t prom_values[10];

        /*for(i=0; i < 8; i++){  ////espacio para buffers

            sizes[i] = (sizes_reverse[i]<<24 & 0x0FF000000);
            sizes[i] |= (sizes_reverse[i]<<8 & 0x0FF0000);
            sizes[i] |= (sizes_reverse[i]>>8 & 0x0FF00);
            sizes[i] |= (sizes_reverse[i]>>24 & 0x0FF);
        }*/

        // read data from file
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

        fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),size_of_save_to_SD_buffer_0,file);  ///datos del paciente

        fread(prom_values, sizeof (uint8_t), 10, file); ///espacio para promedio de valores

        fread(sizes, sizeof (uint32_t), 8, file);  ///espacio para tamaño de buffers 14 * 4

        fclose (file);



        file = fopen ("M:\\base_datos_oximetria.dat","a");

        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

            fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),size_of_save_to_SD_buffer_0,file);

            fwrite(prom_values, sizeof (uint8_t), 10, file); ///espacio para promedio de valores

            fwrite(sizes, sizeof (uint32_t), 8, file);  ///espacio para tamaño de buffers 14 * 4

            fclose (file);
        }
    }
}

bool Main_Thread::save_pacient_signals_to_database(void){


    uint32_t function_value_pos_in_SD_old = function_value_pos_in_SD;
    uint32_t HR_value_pos_in_SD_old = HR_value_pos_in_SD;

    uint32_t i = 0;
    uint32_t function_0_data_offset = size_of_save_to_SD_buffer_0 + 42 + function_value_pos_in_SD;
    uint32_t function_1_data_offset = size_of_save_to_SD_buffer_0 + 42 + DATA_FUNCTION_SIZE + function_value_pos_in_SD;
    uint32_t ADC_data_offset = size_of_save_to_SD_buffer_0 + 42 + (DATA_FUNCTION_SIZE*2) + HR_value_pos_in_SD;  ///Mas 56 por las variables de los tamaños de los buffers y promedios de valores

      FILE file_write;
    for(i = function_value_pos_in_SD_old; i<DATA_FUNCTION_SIZE; i+=FUNCTION_BUFFER_SIZE){  ///Function 0

        file = fopen ("M:\\pacient_data_temp.dat","r");
        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{

            fseek(file, function_0_data_offset, SEEK_SET);

            function_0_data_offset+=FUNCTION_BUFFER_SIZE;

            fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);  ///datos del paciente

            fclose (file);

            file = fopen ("M:\\base_datos_oximetria.dat","a");
            if (file == NULL) {
                // error handling
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

            }
            else{

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);

                fclose (file);
            }
        }
    }

    function_0_data_offset = size_of_save_to_SD_buffer_0 + 42;

    for(i = 0; i < function_value_pos_in_SD_old; i+=FUNCTION_BUFFER_SIZE){  ///Function 0

        file = fopen ("M:\\pacient_data_temp.dat","r");
        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{

            fseek(file, function_0_data_offset, SEEK_SET);

            function_0_data_offset+=FUNCTION_BUFFER_SIZE;

            fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);  ///datos del paciente

            fclose (file);

            file = fopen ("M:\\base_datos_oximetria.dat","a");
            if (file == NULL) {
                // error handling
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

            }
            else{

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);

                fclose (file);
            }
        }
    }



    for(i = function_value_pos_in_SD_old; i<DATA_FUNCTION_SIZE; i+=FUNCTION_BUFFER_SIZE){  ///Function 0

        file = fopen ("M:\\pacient_data_temp.dat","r");
        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{

            fseek(file, function_1_data_offset, SEEK_SET);

            function_1_data_offset+=FUNCTION_BUFFER_SIZE;

            fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);  ///datos del paciente

            fclose (file);

            file = fopen ("M:\\base_datos_oximetria.dat","a");
            if (file == NULL) {
                // error handling
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

            }
            else{

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);

                fclose (file);
            }
        }
    }

    function_1_data_offset = size_of_save_to_SD_buffer_0 + 42 + DATA_FUNCTION_SIZE;

    for(i = 0; i < function_value_pos_in_SD_old; i+=FUNCTION_BUFFER_SIZE){  ///Function 0

        file = fopen ("M:\\pacient_data_temp.dat","r");
        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{

            fseek(file, function_1_data_offset, SEEK_SET);

            function_1_data_offset+=FUNCTION_BUFFER_SIZE;

            fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);  ///datos del paciente

            fclose (file);

            file = fopen ("M:\\base_datos_oximetria.dat","a");
            if (file == NULL) {
                // error handling
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

            }
            else{

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),FUNCTION_BUFFER_SIZE,file);

                fclose (file);
            }
        }
    }



    for(i = HR_value_pos_in_SD_old; i<DATA_ADC_BUFFER_SIZE; i+=ADC_BUFFER_SIZE_IN_8BITS){  ///Function 0

        file = fopen ("M:\\pacient_data_temp.dat","r");
        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{

            fseek(file, ADC_data_offset, SEEK_SET);

            ADC_data_offset+=ADC_BUFFER_SIZE_IN_8BITS;

            fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),ADC_BUFFER_SIZE_IN_8BITS,file);  ///datos del paciente

            fclose (file);

            file = fopen ("M:\\base_datos_oximetria.dat","a");
            if (file == NULL) {
                // error handling
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

            }
            else{

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),ADC_BUFFER_SIZE_IN_8BITS,file);

                fclose (file);
            }
        }
    }

    ADC_data_offset = size_of_save_to_SD_buffer_0 + 42 + (DATA_FUNCTION_SIZE*2);

    for(i = 0; i < HR_value_pos_in_SD_old; i+=ADC_BUFFER_SIZE_IN_8BITS){  ///Function 0

        file = fopen ("M:\\pacient_data_temp.dat","r");
        if (file == NULL) {
            // error handling
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        }
        else{

            fseek(file, ADC_data_offset, SEEK_SET);

            ADC_data_offset+=ADC_BUFFER_SIZE_IN_8BITS;

            fread(&save_to_SD_buffer_0[0],sizeof (uint8_t),ADC_BUFFER_SIZE_IN_8BITS,file);  ///datos del paciente

            fclose(file);

            file = fopen ("M:\\base_datos_oximetria.dat","a");
            if (file == NULL) {
                // error handling
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

            }
            else{

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

                fwrite(&save_to_SD_buffer_0[0],sizeof (uint8_t),ADC_BUFFER_SIZE_IN_8BITS,file);

                fclose (file);
            }
        }
    }
}

//Funcion que calcula valor CRC-32---------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
uint32_t Main_Thread::crc32(const void *buf, size_t size)
{
    const uint8_t *p = (uint8_t *)buf;
    uint32_t crc;

    crc = ~0U;
    while (size--)
        crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    return crc ^ ~0U;
}
//----------------------------------------------------------------------------------------------------------------------------

/*Thread function Generated Code*/
/*End of Thread function Generated Code*/

void Main_Thread::userLoop()
{

    std::int32_t signal = 0;
    eObject::eThread::ThreadEventFlags receivedSignal;

    uint32_t crcValue;
    uint8_t i,c=0,n=0, buf_8b[4];
    std::uint32_t pos =0;
    std::uint32_t pos_func_buffer_0 =0;
    std::uint32_t pos_func_buffer_1 =0;

    check_if_SD_is_functional();

    while(true){
        eventWaitAny(signal, osWaitForever);
        receivedSignal = static_cast<eThread::ThreadEventFlags>(signal);

        if((receivedSignal & INIT_PROGRAM) == INIT_PROGRAM){
            //		#endif
            start_transmit_ftdi = true;
            start_transmit_bluetooth = true;
        }

        if((receivedSignal & INIT_TRANSMIT) == INIT_TRANSMIT){

            if(OXIMETER_1_ACTIVE != 1){ //Si no esta activo el Oximetro 1 no espero por el para transmitir
                CH0_Ready = true;
            }
            if(OXIMETER_2_ACTIVE != 1){ //Si no esta activo el Oximetro 2 no espero por el para transmitir
                CH1_Ready = true;
            }
            if(ADC_ACTIVE != 1){ //Si no esta activo el ADC no espero por el para transmitir
                ADC_Ready = true;
            }

            if(CH0_Ready && CH1_Ready && ADC_Ready){
                CH0_Ready = false;
                CH1_Ready = false;
                ADC_Ready = true;

                if(buffer_transmit == BUFFER_TRANSMIT_0){

                    //Copio lo guardado en los buffer de almacen hacia el buffer de transmision 0--------------------------------------------
                    //std::memcpy( &transmit_buffer_0[DATA_GRAPH_HR_INIT_BUFFER_POS], &ADC_buffer_storage[pos], ADC_BUFFER_SIZE);

                    c=0;
                    for(i=0; i < ADC_BUFFER_SIZE ;++i){

                        c = i*2;
                        transmit_buffer_0[DATA_GRAPH_HR_INIT_BUFFER_POS + c] = ((ADC_buffer_storage[pos + i]>>8) & 0x0FF);
                        transmit_buffer_0[DATA_GRAPH_HR_INIT_BUFFER_POS + c + 1] = ((ADC_buffer_storage[pos + i]) & 0x0FF);
                    }

                    pos+=ADC_BUFFER_SIZE;
                    if(pos >= ADC_BUFFER_STORAGE_SIZE){
                        pos=0;
                    }

                    std::memcpy(&transmit_buffer_0[DATA_GRAPH_FT_INIT_BUFFER_POS], (&CH0_function_buffer_storage_0[pos_func_buffer_0]), FUNCTION_BUFFER_SIZE);

                    pos_func_buffer_0+=FUNCTION_BUFFER_SIZE;
                    if(pos_func_buffer_0 >= FUNCTION_BUFFER_STORAGE_SIZE){
                        pos_func_buffer_0=0;
                    }

                    std::memcpy(&transmit_buffer_0[DATA_GRAPH_FT_2_INIT_BUFFER_POS], (&CH1_function_buffer_storage_0[pos_func_buffer_1]), FUNCTION_BUFFER_SIZE);

                    pos_func_buffer_1+=FUNCTION_BUFFER_SIZE;
                    if(pos_func_buffer_1 >= FUNCTION_BUFFER_STORAGE_SIZE){
                        pos_func_buffer_1=0;
                    }
                    //-----------------------------------------------------------------------------------------------------------------------

                    crcValue = Main_Thread::instance().crc32((void*)&transmit_buffer_0, UART_SEND_BUFFER_SIZE);

                    for(i=0; i<4 ;++i){
                        buf_8b[i] = ((uint8_t*)&crcValue)[3-i];
                    }

                    std::memcpy( write_buff, transmit_buffer_0, sizeof(transmit_buffer_0));
                    std::memcpy( write_buff + UART_SEND_BUFFER_SIZE, buf_8b, sizeof(buf_8b));

                    if(start_transmit_ftdi){

                        HAL_UART_Transmit_DMA(&huart6, write_buff, UART_SEND_TOTAL_SIZE);
                        if(saving_to_sd){
                            std::memcpy(save_to_SD_buffer_signals, (&write_buff[DATA_GRAPH_HR_INIT_BUFFER_POS]), 250);
                            save_to_file_pacient_signals(250);
                        }

                    }

                    buffer_transmit = BUFFER_TRANSMIT_1;
                }
                else if(buffer_transmit == BUFFER_TRANSMIT_1){

                    //Copio lo guardado en los buffer de almacen hacia el buffer de transmision 1--------------------------------------------
                    //std::memcpy( &transmit_buffer_1[DATA_GRAPH_HR_INIT_BUFFER_POS], (uint8_t*)(&ADC_buffer_storage[pos]), ADC_BUFFER_SIZE*2);
                    c=0;
                    for(i=0; i < ADC_BUFFER_SIZE ;++i){

                        c = i*2;
                        transmit_buffer_1[DATA_GRAPH_HR_INIT_BUFFER_POS + c] = ((ADC_buffer_storage[pos + i]>>8) & 0x0FF);
                        transmit_buffer_1[DATA_GRAPH_HR_INIT_BUFFER_POS + c + 1] = ((ADC_buffer_storage[pos + i]) & 0x0FF);
                    }

                    pos+=ADC_BUFFER_SIZE;
                    if(pos >= ADC_BUFFER_STORAGE_SIZE){
                        pos=0;
                    }

                    std::memcpy(&transmit_buffer_1[DATA_GRAPH_FT_INIT_BUFFER_POS], (&CH0_function_buffer_storage_0[pos_func_buffer_0]), FUNCTION_BUFFER_SIZE);

                    pos_func_buffer_0+=FUNCTION_BUFFER_SIZE;
                    if(pos_func_buffer_0 >= FUNCTION_BUFFER_STORAGE_SIZE){
                        pos_func_buffer_0=0;
                    }

                    std::memcpy(&transmit_buffer_1[DATA_GRAPH_FT_2_INIT_BUFFER_POS], (&CH1_function_buffer_storage_0[pos_func_buffer_1]), FUNCTION_BUFFER_SIZE);

                    pos_func_buffer_1+=FUNCTION_BUFFER_SIZE;
                    if(pos_func_buffer_1 >= FUNCTION_BUFFER_STORAGE_SIZE){
                        pos_func_buffer_1=0;
                    }
                    //-----------------------------------------------------------------------------------------------------------------------

                    //transmit_buffer_1[DATA_INIT_BUFFER_POS]=DATA_BUFFER_TRANSMIT_1;
                    crcValue = Main_Thread::instance().crc32((void*)&transmit_buffer_1, UART_SEND_BUFFER_SIZE);

                    for(i=0; i<4 ;++i){
                        buf_8b[i] = ((uint8_t*)&crcValue)[3-i];
                    }

                    std::memcpy( write_buff, transmit_buffer_1, sizeof(transmit_buffer_1));
                    std::memcpy( write_buff + UART_SEND_BUFFER_SIZE, buf_8b, sizeof(buf_8b));

                    if(start_transmit_ftdi){

                        HAL_UART_Transmit_DMA(&huart6, write_buff, UART_SEND_TOTAL_SIZE);
                        if(saving_to_sd){
                            std::memcpy(save_to_SD_buffer_signals, (&write_buff[DATA_GRAPH_HR_INIT_BUFFER_POS]), 250);
                            save_to_file_pacient_signals(250);
                        }
                    }

                    buffer_transmit = BUFFER_TRANSMIT_0;
                }
            }
        }

        if((receivedSignal & STOP_SAVING_TO_SD) == STOP_SAVING_TO_SD){

            save_pacient_data_to_database();

            save_pacient_signals_to_database();
        }
    }
}

/*Threads Functions Implementation Generated Code*/
void Main_Thread::process_Receive_CommandsRun(eObject::eThread &thread)
{
    std::int32_t signal = 0;
    eObject::eThread::ThreadEventFlags receivedSignal;
    bool init = true;
    bool init_prog = true;
    bool init_save_to_sd = true;
    bool stop_save_to_sd = true;
    bool retransmit = true;
    std::uint8_t read_buff[UART_READ_BUFFER_SIZE], i;
    std::uint8_t transmit_buffer[UART_SEND_BUFFER_SIZE];
    std::uint8_t write_buffer[UART_SEND_TOTAL_SIZE];

    while(true){
        eventWaitAny(signal, osWaitForever);
        receivedSignal = static_cast<eThread::ThreadEventFlags>(signal);

        if((receivedSignal & RECEIVE_COMMANDS) == RECEIVE_COMMANDS){

            std::memcpy( read_buff, CH3_read_buffer_0, sizeof(CH3_read_buffer_0));
            init = true;
            init_prog = true;
            init_save_to_sd = true;
            stop_save_to_sd = true;

            ////////////Bluetooth or PC/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //--------------------------------------------------------------------
            for(i=0; i<4; i++){
                if(read_buff[i] != STOP_SAVE_TO_SD){
                    stop_save_to_sd = false;
                }
            }
            if(stop_save_to_sd){
                saving_to_sd = false;
                start_transmit_ftdi = false;

                uint32_t crcValue;
                uint8_t buf_8b[4];

                Main_Thread::instance().eventSet(STOP_SAVING_TO_SD);

                for(i = DATA_INIT_BUFFER_POS; i < DATA_GRAPH_HR_INIT_BUFFER_POS; i++){

                    transmit_buffer[i] = ACKNOWLEDGE_END_OF_RECORDING;

                }
                crcValue = Main_Thread::instance().crc32((void*)&transmit_buffer, UART_SEND_BUFFER_SIZE);

                for(i=0; i<4 ;++i){
                    buf_8b[i] = ((uint8_t*)&crcValue)[3-i];
                }

                std::memcpy( write_buffer, transmit_buffer, sizeof(transmit_buffer));
                std::memcpy( write_buffer + UART_SEND_BUFFER_SIZE, buf_8b, sizeof(buf_8b));

                HAL_UART_Transmit_DMA(&huart6, write_buffer, UART_SEND_TOTAL_SIZE);

                continue;
            }
            //            //--------------------------------------------------------------------
            //            if(saving_to_sd){
            //                std::memcpy(save_to_SD_buffer_0, CH3_read_buffer_0, sizeof(CH3_read_buffer_0));
            //                Main_Thread::instance().eventSet(SAVE_TO_SD);
            //                continue;
            //            }
            //            //--------------------------------------------------------------------
            //            for(i=0; i<4; i++){
            //                if(read_buff[i] != INIT_SAVE_TO_SD){
            //                    init_save_to_sd = false;
            //                }
            //            }
            //            if(init_save_to_sd){
            //                Main_Thread::instance().eventSet(SAVE_TO_SD);
            //            }
            //--------------------------------------------------------------------
            for(i=0; i<4; i++){
                if(read_buff[i] != INIT_PROG_ID){
                    init_prog = false;
                }
            }
            if(init_prog){

                uint32_t crcValue;
                uint8_t buf_8b[4];

                for(i = DATA_INIT_BUFFER_POS; i < DATA_GRAPH_HR_INIT_BUFFER_POS; i++){

                    transmit_buffer_0[i] = CHECKING_CONNECTION;

                }
                crcValue = Main_Thread::instance().crc32((void*)&transmit_buffer_0, UART_SEND_BUFFER_SIZE);

                for(i=0; i<4 ;++i){
                    buf_8b[i] = ((uint8_t*)&crcValue)[3-i];
                }

                std::memcpy( write_buff, transmit_buffer_0, sizeof(transmit_buffer_0));
                std::memcpy( write_buff + UART_SEND_BUFFER_SIZE, buf_8b, sizeof(buf_8b));

                HAL_UART_Transmit_DMA(&huart6, write_buff, UART_SEND_TOTAL_SIZE);

                HAL_Delay(200);
                NVIC_SystemReset();
            }
            //--------------------------------------------------------------------
            for(i=0; i<4; i++){
                if(read_buff[i] != INIT_SEND_ID){
                    init = false;
                }
            }
            if(init){

                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
                std::memcpy(save_to_SD_buffer_0, &read_buff[5], read_buff[4]);
                size_of_save_to_SD_buffer_0 = read_buff[4];
                saving_to_sd = true;
                Main_Thread::save_to_file_pacient_data();
                Main_Thread::instance().eventSet(INIT_PROGRAM);
                Main_Thread::instance().timer_timer_led_green.start(TIMER_timer_led_green_PERIOD_MS);
                continue;
            }
            //--------------------------------------------------------------------
            retransmit = true;
            for(i=0; i<4; i++){
                if(read_buff[i] != ERROR_ID){
                    retransmit = false;
                }
            }
            if(retransmit){
                init = false;
                Main_Thread::instance().timer_timer_led_green.restart();
                error_sending=true;
                continue;
            }
            //--------------------------------------------------------------------
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }
}
void Main_Thread::thread_Read_ADCRun(eObject::eThread &thread)
{
    std::uint16_t value_adc, i;

    arm_fir_instance_f32 S;
    arm_status status;
    float32_t  inputF32[ADC_BUFFER_SIZE], outputF32[ADC_BUFFER_SIZE];

    std::uint8_t temp_buff[ADC_BUFFER_SIZE];
    std::uint16_t temp_buff_16[ADC_BUFFER_SIZE];
    arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&fir_coefficient[0], &firState_f32[0], blockSize); //BLOCK_SIZE

    while(true){

        eventWait(Timer_timer_ADCPeriodic_Complete);

        value_adc = adc_value;
        ADC_buffer[ADC_buffer_pos]= value_adc << 3;  //para adc_16bits
        ADC_buffer_pos++;

        if(ADC_buffer_pos >= ADC_BUFFER_SIZE){

            ADC_buffer_pos=0;

            std::memcpy( (uint16_t*)&temp_buff_16[0], (uint16_t*)&ADC_buffer[0], sizeof(ADC_buffer)); //tener cuidado con el tamaño de las transferencias

            arm_q15_to_float((q15_t*)&temp_buff_16[0], inputF32, ADC_BUFFER_SIZE);

            arm_fir_f32(&S, inputF32 , outputF32, ADC_BUFFER_SIZE);

            arm_float_to_q15(&outputF32[0], (q15_t*)&temp_buff_16[0], ADC_BUFFER_SIZE);

            for(i=0; i<ADC_BUFFER_SIZE ;++i){  //Elimino el signo y lo subo a 16bits
                temp_buff_16[i] = temp_buff_16[i]<<1;
            }


            for(i=0; i<ADC_BUFFER_SIZE ;++i){  //Lo bajo a resolucion de 12bits
                temp_buff_16[i] = temp_buff_16[i]>>4;
            }

            std::memcpy( &ADC_buffer_storage[ADC_buffer_storage_pos], temp_buff_16, sizeof(temp_buff_16));
            ADC_buffer_storage_pos+=ADC_BUFFER_SIZE;
            if(ADC_buffer_storage_pos >= ADC_BUFFER_STORAGE_SIZE){
                ADC_Init_Ready = true;
                ADC_buffer_storage_pos = 0;
            }

            if(Main_Thread::instance().ADC_Init_Ready){

                Main_Thread::instance().ADC_Ready = true;
                Main_Thread::instance().eventSet(Main_Thread::INIT_TRANSMIT);
            }
        }
    }
}
void Main_Thread::thread_Process_CH1Run(eObject::eThread &thread) //USART3
{
    std::int32_t signal = 0;
    eObject::eThread::ThreadEventFlags receivedSignal;

    //    enum { pendiente_9A, pendiente_9B, pendiente_unknow, no_pendent};

    //    uint8_t message_pendent = no_pendent;

    uint32_t last_pendent_pos=0;
    uint8_t message_lenght;
    uint8_t message_id;
    //    uint8_t message_id_pendent;
    //    uint8_t message_lenght_pendent;
    bool pendent=false;

    uint8_t function_buffer_local[FUNCTION_BUFFER_SIZE];
    uint8_t processing_buffer_local[UART_READ_BUFFER_SIZE/2];

    while(true){
        thread.eventWaitAny(signal, osWaitForever);
        receivedSignal = static_cast<eThread::ThreadEventFlags>(signal);

        if((receivedSignal & INIT_PROCESS_CH1_HALF) == INIT_PROCESS_CH1_HALF){

            std::memcpy( CH1_processsing_buffer_0, &CH1_read_buffer_0[0], sizeof(CH1_processsing_buffer_0));
            std::memcpy(processing_buffer_local, &CH1_read_buffer_0[0], sizeof(processing_buffer_local));

            int i;
            for(i=0; i < UART_READ_BUFFER_SIZE/2; i++){ //el elemento i = serialData.size() no existe y da error al correr

                //Buscando la cabezera de todos los mensajes (0x0FA)----------------------------------------------------------------
                if(CH1_processsing_buffer_0[i] == (uint8_t)0x0FA){

                    if(i+3 >= UART_READ_BUFFER_SIZE/2){

                        last_pendent_pos = 3 - (UART_READ_BUFFER_SIZE/2 - i);
                        pendent = true;
                        break;
                    }

                    message_lenght = CH1_processsing_buffer_0[i + 1]; //tamaño del mensaje en bytes
                    message_id = CH1_processsing_buffer_0[i + 2]; //Identificador de mensaje

                    //Se encuesta para saber si es comando FUNCTION plethysmogram AND BARS GRAPH----------------------------------------------------------------
                    if(message_id == (uint8_t)0x09A){

                        Main_Thread::instance().process_9A_buff_CH1(CH1_processsing_buffer_0[i + 3]);

                        std::memcpy(&function_buffer_local[0], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));

                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }

                    if(message_id == (uint8_t)DATA_INIT_BUFFER_ID)/*0x9B*/{

                        uint16_t SPO2, BPM_L, BPM_H, PI_L, PI_H, STATUS_CHECK;

                        //current_oxymeter = OXYMETER_2;

                        SPO2 = CH1_processsing_buffer_0[i + 3];

                        BPM_L = CH1_processsing_buffer_0[i + 4];
                        BPM_H = CH1_processsing_buffer_0[i + 5];

                        PI_L = CH1_processsing_buffer_0[i + 6];
                        PI_H = CH1_processsing_buffer_0[i + 7];

                        STATUS_CHECK = CH1_processsing_buffer_0[i + 8];

                        if(SPO2 > 100){  //Valor invalido

                            SPO2 = 0x0FF;
                        }

                        if(buffer_transmit == BUFFER_TRANSMIT_0){

                            transmit_buffer_1[SPO2_BUFFER_OXY2_POS] = SPO2;
                            transmit_buffer_1[BPM_BUFFER_OXY2_POS] = BPM_L;
                            transmit_buffer_1[BPM_BUFFER_OXY2_POS+1] = BPM_H;
                            transmit_buffer_1[PI_BUFFER_OXY2_POS] = PI_L;
                            transmit_buffer_1[PI_BUFFER_OXY2_POS+1] = PI_H;
                            transmit_buffer_1[STATUS_CHECK_OXY2_POS] = STATUS_CHECK;

                        }else if(buffer_transmit == BUFFER_TRANSMIT_1){

                            transmit_buffer_0[SPO2_BUFFER_OXY2_POS] = SPO2;
                            transmit_buffer_0[BPM_BUFFER_OXY2_POS] = BPM_L;
                            transmit_buffer_0[BPM_BUFFER_OXY2_POS+1] = BPM_H;
                            transmit_buffer_0[PI_BUFFER_OXY2_POS] = PI_L;
                            transmit_buffer_0[PI_BUFFER_OXY2_POS+1] = PI_H;
                            transmit_buffer_0[STATUS_CHECK_OXY2_POS] = STATUS_CHECK;
                        }

                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }
                }
                if(pendent){
                    pendent =false;
                    std::uint8_t val = CH1_processsing_buffer_0[last_pendent_pos];
                    Main_Thread::instance().process_9A_buff_CH1(CH1_processsing_buffer_0[last_pendent_pos]);

                    std::memcpy(&function_buffer_local[0], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
                    //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                    i = i + last_pendent_pos;
                    continue;
                }
                if(CH1_processsing_buffer_0[i] == (uint8_t)0x09A){

                    if(i+1< UART_READ_BUFFER_SIZE/2 ){

                        Main_Thread::instance().process_9A_buff_CH1(CH1_processsing_buffer_0[i+1]);

                        std::memcpy(&function_buffer_local[0], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
                        continue;
                    }
                }

                //std::memcpy(function_buffer_local, (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
                //Main_Thread::instance().transmit_thread.eventSet(Main_Thread::Init_Transmition_CH1);
            }

        }

        if((receivedSignal & INIT_PROCESS_CH1_FULL) == INIT_PROCESS_CH1_FULL){
            std::memcpy( CH1_processsing_buffer_1, &CH1_read_buffer_0[UART_READ_BUFFER_SIZE/2], sizeof(CH1_processsing_buffer_1));
            std::memcpy(processing_buffer_local, &CH1_read_buffer_0[0], sizeof(processing_buffer_local));

            int i;
            for(i=0; i < UART_READ_BUFFER_SIZE/2; i++){ //el elemento i = serialData.size() no existe y da error al correr

                //Buscando la cabezera de todos los mensajes (0x0FA)----------------------------------------------------------------
                if(CH1_processsing_buffer_1[i] == (uint8_t)0x0FA){

                    if(i+3 >= UART_READ_BUFFER_SIZE/2){

                        last_pendent_pos = 3 - (UART_READ_BUFFER_SIZE/2 - i);
                        pendent = true;
                        break;
                    }
                    message_lenght = CH1_processsing_buffer_1[i + 1]; //tamaño del mensaje en bytes
                    message_id = CH1_processsing_buffer_1[i + 2]; //Identificador de mensaje


                    //Se encuesta para saber si es comando FUNCTION plethysmogram AND BARS GRAPH----------------------------------------------------------------
                    if(message_id == (uint8_t)0x09A){

                        Main_Thread::instance().process_9A_buff_CH1(CH1_processsing_buffer_1[i + 3]);

                        std::memcpy(&function_buffer_local[0], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }

                    if(message_id == (uint8_t)DATA_INIT_BUFFER_ID){

                        uint16_t SPO2, BPM_L, BPM_H, PI_L, PI_H, STATUS_CHECK;

                        //current_oxymeter = OXYMETER_2;

                        SPO2 = CH1_processsing_buffer_1[i + 3];

                        BPM_L = CH1_processsing_buffer_1[i + 4];
                        BPM_H = CH1_processsing_buffer_1[i + 5];

                        PI_L = CH1_processsing_buffer_1[i + 6];
                        PI_H = CH1_processsing_buffer_1[i + 7];

                        STATUS_CHECK = CH1_processsing_buffer_1[i + 8];

                        if(SPO2 > 100){  //Valor invalido

                            SPO2 = 0x0FF;
                        }

                        if(buffer_transmit == BUFFER_TRANSMIT_0){//oxy2

                            transmit_buffer_1[SPO2_BUFFER_OXY2_POS] = SPO2;
                            transmit_buffer_1[BPM_BUFFER_OXY2_POS] = BPM_L;
                            transmit_buffer_1[BPM_BUFFER_OXY2_POS+1] = BPM_H;
                            transmit_buffer_1[PI_BUFFER_OXY2_POS] = PI_L;
                            transmit_buffer_1[PI_BUFFER_OXY2_POS+1] = PI_H;
                            transmit_buffer_1[STATUS_CHECK_OXY2_POS] = STATUS_CHECK;

                        }else if(buffer_transmit == BUFFER_TRANSMIT_1){

                            transmit_buffer_0[SPO2_BUFFER_OXY2_POS] = SPO2;
                            transmit_buffer_0[BPM_BUFFER_OXY2_POS] = BPM_L;
                            transmit_buffer_0[BPM_BUFFER_OXY2_POS+1] = BPM_H;
                            transmit_buffer_0[PI_BUFFER_OXY2_POS] = PI_L;
                            transmit_buffer_0[PI_BUFFER_OXY2_POS+1] = PI_H;
                            transmit_buffer_0[STATUS_CHECK_OXY2_POS] = STATUS_CHECK;
                        }

                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }
                }
                if(pendent){
                    pendent =false;
                    std::uint8_t val = CH1_processsing_buffer_1[last_pendent_pos];

                    Main_Thread::instance().process_9A_buff_CH1(CH1_processsing_buffer_1[last_pendent_pos]);

                    std::memcpy(&function_buffer_local[0], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
                    //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                    i = i + last_pendent_pos;
                    continue;
                }
                if(CH1_processsing_buffer_1[i] == (uint8_t)0x09A){

                    if(i+1< UART_READ_BUFFER_SIZE/2 ){

                        Main_Thread::instance().process_9A_buff_CH1(CH1_processsing_buffer_1[i+1]);

                        std::memcpy(&function_buffer_local[0], (CH1_function_buffer_0), sizeof(CH1_function_buffer_0));
                        continue;
                    }
                }
            }
        }
    }
}
void Main_Thread::thread_Process_CH0Run(eObject::eThread &thread) //USART2
{
    std::int32_t signal = 0;
    eObject::eThread::ThreadEventFlags receivedSignal;

    enum { pendiente_9A, pendiente_9B, pendiente_unknow, no_pendent};

    uint8_t message_pendent = no_pendent;

    uint32_t last_pendent_pos=0;
    uint8_t message_lenght;
    uint8_t message_id;
    uint8_t message_id_pendent;
    uint8_t message_lenght_pendent;
    bool pendent=false;

    uint8_t function_buffer_local[FUNCTION_BUFFER_SIZE];
    uint8_t processing_buffer_local[UART_READ_BUFFER_SIZE/2];

    while(true){
        thread.eventWaitAny(signal, osWaitForever);
        receivedSignal = static_cast<eThread::ThreadEventFlags>(signal);

        if((receivedSignal & INIT_PROCESS_CH0_HALF) == INIT_PROCESS_CH0_HALF){

            std::memcpy( CH0_processsing_buffer_0, &CH0_read_buffer_0[0], sizeof(CH0_processsing_buffer_0));
            std::memcpy(processing_buffer_local, &CH0_read_buffer_0[0], sizeof(processing_buffer_local));

            int i;
            for(i=0; i < UART_READ_BUFFER_SIZE/2; i++){ //el elemento i = serialData.size() no existe y da error al correr

                //Buscando la cabezera de todos los mensajes (0x0FA)----------------------------------------------------------------
                if(CH0_processsing_buffer_0[i] == (uint8_t)0x0FA){

                    if(i+3 >= UART_READ_BUFFER_SIZE/2){

                        last_pendent_pos = 3 - (UART_READ_BUFFER_SIZE/2 - i);
                        pendent = true;
                        break;
                    }

                    message_lenght = CH0_processsing_buffer_0[i + 1]; //tamaño del mensaje en bytes
                    message_id = CH0_processsing_buffer_0[i + 2]; //Identificador de mensaje

                    //Se encuesta para saber si es comando FUNCTION plethysmogram AND BARS GRAPH----------------------------------------------------------------
                    if(message_id == (uint8_t)0x09A){

                        Main_Thread::instance().process_9A_buff_CH0(CH0_processsing_buffer_0[i + 3]);

                        std::memcpy(&function_buffer_local[0], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));

                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }

                    if(message_id == (uint8_t)DATA_INIT_BUFFER_ID){

                        uint16_t SPO2, BPM_L, BPM_H, PI_L, PI_H, STATUS_CHECK;

                        //current_oxymeter = OXYMETER_1;

                        SPO2 = CH0_processsing_buffer_0[i + 3];

                        BPM_L = CH0_processsing_buffer_0[i + 4];
                        BPM_H = CH0_processsing_buffer_0[i + 5];

                        PI_L = CH0_processsing_buffer_0[i + 6];
                        PI_H = CH0_processsing_buffer_0[i + 7];

                        STATUS_CHECK = CH0_processsing_buffer_0[i + 8];

                        if(SPO2 > 100){  //Valor invalido

                            SPO2 = 0x0FF;
                        }

                        if(buffer_transmit == BUFFER_TRANSMIT_0){

                            transmit_buffer_1[SPO2_BUFFER_OXY1_POS] = SPO2;
                            transmit_buffer_1[BPM_BUFFER_OXY1_POS] = BPM_L;
                            transmit_buffer_1[BPM_BUFFER_OXY1_POS+1] = BPM_H;
                            transmit_buffer_1[PI_BUFFER_OXY1_POS] = PI_L;
                            transmit_buffer_1[PI_BUFFER_OXY1_POS+1] = PI_H;
                            transmit_buffer_1[STATUS_CHECK_OXY1_POS] = STATUS_CHECK;

                        }else if(buffer_transmit == BUFFER_TRANSMIT_1){

                            transmit_buffer_0[SPO2_BUFFER_OXY1_POS] = SPO2;
                            transmit_buffer_0[BPM_BUFFER_OXY1_POS] = BPM_L;
                            transmit_buffer_0[BPM_BUFFER_OXY1_POS+1] = BPM_H;
                            transmit_buffer_0[PI_BUFFER_OXY1_POS] = PI_L;
                            transmit_buffer_0[PI_BUFFER_OXY1_POS+1] = PI_H;
                            transmit_buffer_0[STATUS_CHECK_OXY1_POS] = STATUS_CHECK;
                        }

                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }
                }
                if(pendent){
                    pendent =false;
                    std::uint8_t val = CH0_processsing_buffer_0[last_pendent_pos];
                    Main_Thread::instance().process_9A_buff_CH0(CH0_processsing_buffer_0[last_pendent_pos]);

                    std::memcpy(&function_buffer_local[0], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
                    //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                    i = i + last_pendent_pos;
                    continue;
                }
                if(CH0_processsing_buffer_0[i] == (uint8_t)0x09A){

                    if(i+1< UART_READ_BUFFER_SIZE/2 ){

                        Main_Thread::instance().process_9A_buff_CH0(CH0_processsing_buffer_0[i+1]);

                        std::memcpy(&function_buffer_local[0], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
                        continue;
                    }
                }

                //std::memcpy(function_buffer_local, (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
                //Main_Thread::instance().transmit_thread.eventSet(Main_Thread::Init_Transmition_CH0);
            }

        }

        if((receivedSignal & INIT_PROCESS_CH0_FULL) == INIT_PROCESS_CH0_FULL){
            std::memcpy( CH0_processsing_buffer_1, &CH0_read_buffer_0[UART_READ_BUFFER_SIZE/2], sizeof(CH0_processsing_buffer_1));
            std::memcpy(processing_buffer_local, &CH0_read_buffer_0[0], sizeof(processing_buffer_local));

            int i;
            for(i=0; i < UART_READ_BUFFER_SIZE/2; i++){ //el elemento i = serialData.size() no existe y da error al correr

                //Buscando la cabezera de todos los mensajes (0x0FA)----------------------------------------------------------------
                if(CH0_processsing_buffer_1[i] == (uint8_t)0x0FA){

                    if(i+3 >= UART_READ_BUFFER_SIZE/2){

                        last_pendent_pos = 3 - (UART_READ_BUFFER_SIZE/2 - i);
                        pendent = true;
                        break;
                    }
                    message_lenght = CH0_processsing_buffer_1[i + 1]; //tamaño del mensaje en bytes
                    message_id = CH0_processsing_buffer_1[i + 2]; //Identificador de mensaje


                    //Se encuesta para saber si es comando FUNCTION plethysmogram AND BARS GRAPH----------------------------------------------------------------
                    if(message_id == (uint8_t)0x09A){

                        Main_Thread::instance().process_9A_buff_CH0(CH0_processsing_buffer_1[i + 3]);

                        std::memcpy(&function_buffer_local[0], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }

                    if(message_id == (uint8_t)DATA_INIT_BUFFER_ID){

                        uint16_t SPO2, BPM_L, BPM_H, PI_L, PI_H, STATUS_CHECK;

                        //current_oxymeter = OXYMETER_1;

                        SPO2 = CH0_processsing_buffer_1[i + 3];

                        BPM_L = CH0_processsing_buffer_1[i + 4];
                        BPM_H = CH0_processsing_buffer_1[i + 5];

                        PI_L = CH0_processsing_buffer_1[i + 6];
                        PI_H = CH0_processsing_buffer_1[i + 7];

                        STATUS_CHECK = CH0_processsing_buffer_1[i + 8];

                        if(SPO2 > 100){  //Valor invalido

                            SPO2 = 0x0FF;
                        }

                        if(buffer_transmit == BUFFER_TRANSMIT_0){

                            transmit_buffer_1[SPO2_BUFFER_OXY1_POS] = SPO2;
                            transmit_buffer_1[BPM_BUFFER_OXY1_POS] = BPM_L;
                            transmit_buffer_1[BPM_BUFFER_OXY1_POS+1] = BPM_H;
                            transmit_buffer_1[PI_BUFFER_OXY1_POS] = PI_L;
                            transmit_buffer_1[PI_BUFFER_OXY1_POS+1] = PI_H;
                            transmit_buffer_1[STATUS_CHECK_OXY1_POS] = STATUS_CHECK;

                        }else if(buffer_transmit == BUFFER_TRANSMIT_1){

                            transmit_buffer_0[SPO2_BUFFER_OXY1_POS] = SPO2;
                            transmit_buffer_0[BPM_BUFFER_OXY1_POS] = BPM_L;
                            transmit_buffer_0[BPM_BUFFER_OXY1_POS+1] = BPM_H;
                            transmit_buffer_0[PI_BUFFER_OXY1_POS] = PI_L;
                            transmit_buffer_0[PI_BUFFER_OXY1_POS+1] = PI_H;
                            transmit_buffer_0[STATUS_CHECK_OXY1_POS] = STATUS_CHECK;
                        }

                        //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                        i = i + message_lenght - 1;
                        continue;
                    }
                }
                if(pendent){
                    pendent =false;
                    std::uint8_t val = CH0_processsing_buffer_1[last_pendent_pos];

                    Main_Thread::instance().process_9A_buff_CH0(CH0_processsing_buffer_1[last_pendent_pos]);

                    std::memcpy(&function_buffer_local[0], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
                    //Se salta el procesamiento de bytes hasta la siguiente cabecera (0x0FA)--------------------------------------------------
                    i = i + last_pendent_pos;
                    continue;
                }
                if(CH0_processsing_buffer_1[i] == (uint8_t)0x09A){

                    if(i+1< UART_READ_BUFFER_SIZE/2 ){

                        Main_Thread::instance().process_9A_buff_CH0(CH0_processsing_buffer_1[i+1]);

                        std::memcpy(&function_buffer_local[0], (CH0_function_buffer_0), sizeof(CH0_function_buffer_0));
                        continue;
                    }
                }
            }
        }
    }
}


/*End of Threads Functions Implementation Generated Code*/


void Main_Thread::setBufferOffset(const BUFFER_StateTypeDef offset)
{
    buffer_transmit = offset;
}
void Main_Thread::timer_ADC_timeout(void const *argument){

    ////To set Event For This timer timeOut
    //Main_Thread::instance().thread_Read_ADC.eventSet(Timer_timer_ADCPeriodic_Complete);

    ////To start this timer
    //timer_timer_ADC.start(TIMER_timer_ADC_PERIOD_MS);

    ////To wait for this timer timeOut event
    //eventWait(Timer_timer_ADCPeriodic_Complete);
}

void Main_Thread::timeOut_timer_leds_function(void const *argument){  ///Led azul

    ////To set Event For This timer timeOut
    //Main_Thread::instance().eventSet(Timer_timer_ledsPeriodic_Complete);
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    ////To start this timer
    //timer_timer_leds.start(TIMER_timer_leds_PERIOD_MS);

    ////To wait for this timer timeOut event
    //eventWait(Timer_timer_ledsPeriodic_Complete);
}

void Main_Thread::timeOut_timer_led_red_function(void const *argument){

    ////To set Event For This timer timeOut
    //Main_Thread::instance().eventSet(Timer_timer_led_redPeriodic_Complete);
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    ////To start this timer
    //timer_timer_led_red.start(TIMER_timer_led_red_PERIOD_MS);

    ////To wait for this timer timeOut event
    //eventWait(Timer_timer_led_redPeriodic_Complete);
}

void Main_Thread::timeOut_timer_led_green_function(void const *argument){

    ////To set Event For This timer timeOut
    //Main_Thread::instance().eventSet(Timer_timer_led_greenPeriodic_Complete);
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    if(error_sending){
        Main_Thread::instance().eventSet(INIT_PROGRAM);
        error_sending=false;
    }
    ////To start this timer
    //timer_timer_led_green.start(TIMER_timer_led_green_PERIOD_MS);

    ////To wait for this timer timeOut event
    //eventWait(Timer_timer_led_greenPeriodic_Complete);
}
