#pragma once

#include "stm32_f20x_f21x_conf.h"
#ifdef MODULE_SPI

#include <cstdio>
#include "stm32_f20x_f21x_spi_struct.h"

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_CLK_POLARITY POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV, EC_SPI_CFG_INTERRUPT_TX I_TX,
           EC_SPI_CFG_INTERRUPT_RX I_RX, EC_SPI_CFG_INTERRUPT_ERROR I_ER, EC_SPI_CFG_DMA_TX_BUF DMATX, EC_SPI_CFG_DMA_RX_BUF DMARX, EC_SPI_CFG_CS CS, EC_SPI_CFG_SSM SSM, EC_SPI_CFG_SSM_MODE SSM_MODE >
constexpr spi_cfg< MODE, POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME, R_MODE, FORMAT,
                   BR_DEV, I_TX, I_RX, I_ER, DMATX, DMARX, CS, SSM, SSM_MODE >::spi_cfg() : spi_cfg_struct( {
    .c1_msk = this->c1_reg_msk_get(),
    .c2_msk = this->c2_reg_msk_get()
} ) {
        /*
         * Параметры ниже указываются при любых режимах.
         */
        static_assert( ( MODE == EC_SPI_CFG_MODE::MASTER ) ||
                       ( MODE == EC_SPI_CFG_MODE::SLAVE ),
                "Invalid template parameter!The MODE can be MASTER or SLAVE!" );

        static_assert( ( POLAR == EC_SPI_CFG_CLK_POLARITY::IDLE_0 ) ||
                       ( POLAR == EC_SPI_CFG_CLK_POLARITY::IDLE_1 ),
                "Invalid template parameter!The POLAR can be IDLE_0 or IDLE_1!" );

        static_assert( ( PHASE == EC_SPI_CFG_CLK_PHASE::FIRST ) ||
                       ( PHASE == EC_SPI_CFG_CLK_PHASE::SECOND ),
                "Invalid template parameter!The PHASE can be FIRST or SECOND!" );

        static_assert( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_1 ) ||
                       ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ),
                "Invalid template parameter!The MODE can be LINE_1 or LINE_2!" );

        static_assert( ( FRAME == EC_SPI_CFG_DATA_FRAME::FRAME_16_BIT ) ||
                       ( FRAME == EC_SPI_CFG_DATA_FRAME::FRAME_8_BIT ),
                "Invalid template parameter!The FRAME can be FRAME_8_BIT or FRAME_16_BIT!" );

        static_assert( ( R_MODE == EC_SPI_CFG_RECEIVE_MODE::FULL_DUPLEX ) ||
                       ( R_MODE == EC_SPI_CFG_RECEIVE_MODE::RECEIVE_ONLY ),
                "Invalid template parameter!The R_MODE can be FULL_DUPLEX or RECEIVE_ONLY!" );

        static_assert( ( FORMAT == EC_SPI_CFG_FRAME_FORMAT::MOTOROLA ) ||
                       ( FORMAT == EC_SPI_CFG_FRAME_FORMAT::TI ),
                "Invalid template parameter!The FORMAT can be MOTOROLA or TI!" );

        static_assert( ( BR_DEV <= EC_SPI_CFG_BAUD_RATE_DEV::DEV_256 ) &&
                       ( BR_DEV >= EC_SPI_CFG_BAUD_RATE_DEV::DEV_2 ),
                "Invalid template parameter!The BR_DEV can be from DEV_2 to DEV_256!" );

        static_assert( ( I_TX == EC_SPI_CFG_INTERRUPT_TX::ON ) ||
                       ( I_TX == EC_SPI_CFG_INTERRUPT_TX::OFF ),
                "Invalid template parameter!The I_TX can be ON or OFF!" );

        static_assert( ( I_RX == EC_SPI_CFG_INTERRUPT_RX::ON ) ||
                       ( I_RX == EC_SPI_CFG_INTERRUPT_RX::OFF ),
                "Invalid template parameter!The I_RX can be ON or OFF!" );

        static_assert( ( I_ER == EC_SPI_CFG_INTERRUPT_ERROR::ON ) ||
                       ( I_ER == EC_SPI_CFG_INTERRUPT_ERROR::OFF ),
                "Invalid template parameter!The I_ER can be ON or OFF!" );

        static_assert( ( DMATX == EC_SPI_CFG_DMA_TX_BUF::DISABLED ) ||
                       ( DMATX == EC_SPI_CFG_DMA_TX_BUF::ENABLED ),
                "Invalid template parameter!The DMATX can be DISABLED or ENABLED!" );

        static_assert( ( DMARX == EC_SPI_CFG_DMA_RX_BUF::DISABLED ) ||
                       ( DMARX == EC_SPI_CFG_DMA_RX_BUF::ENABLED ),
                "Invalid template parameter!The DMARX can be ON or OFF!" );

        static_assert( ( CS == EC_SPI_CFG_CS::DISABLED ) ||
                       ( CS == EC_SPI_CFG_CS::ENABLED ),
                "Invalid template parameter!The CS can be DISABLED or ENABLED!" );

        /*
         * В случае, если используется только одна линия.
         */
        static_assert( !( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_1 ) &&
                          ( ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::RECEIVE_ONLY ) ||
                            ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::TRANSMIT_ONLY ) ) ),
                "Invalid template parameter!"
                "NUM_LINE is selected as LINE_1"
                "The ONE_LINE_MODE can be RECEIVE_ONLY or TRANSMIT_ONLY!" );

            static_assert( ( NUM_LINE != EC_SPI_CFG_NUMBER_LINE::LINE_1 ) &&
                           ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::USE_2_LINE ),
                "Invalid template parameter!"
                "NUM_LINE is selected as LINE_2"
                "The ONE_LINE_MODE can be USE_2_LINE!" );

        /*
         * Если SPI сконфигурирован как мастер.
         */
        static_assert( !( ( MODE == EC_SPI_CFG_MODE::SLAVE )  &&
                          ( SSM == EC_SPI_CFG_SSM::SSM_ON ) &&
                          ( SSM_MODE != EC_SPI_CFG_SSM_MODE::NO_USE ) ),
                "Invalid template parameter!"                   // Если выбран режим отслеживания во время
                "SSM is selected as SSM_ON"                     // slave режима, то нужно укзаать, какой именно.
                "The SSM_MODE not can be NO_USE!" );
 }

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_CLK_POLARITY POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV, EC_SPI_CFG_INTERRUPT_TX I_TX,
           EC_SPI_CFG_INTERRUPT_RX I_RX, EC_SPI_CFG_INTERRUPT_ERROR I_ER, EC_SPI_CFG_DMA_TX_BUF DMATX, EC_SPI_CFG_DMA_RX_BUF DMARX, EC_SPI_CFG_CS CS, EC_SPI_CFG_SSM SSM, EC_SPI_CFG_SSM_MODE SSM_MODE >
constexpr uint32_t spi_cfg< MODE, POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME, R_MODE, FORMAT,
                            BR_DEV, I_TX, I_RX, I_ER, DMATX, DMARX, CS, SSM, SSM_MODE >::c1_reg_msk_get ( void ) {
    uint32_t msk = 0;

    msk     |= M_EC_TO_U32(MODE) | M_EC_TO_U32(POLAR) | M_EC_TO_U32(PHASE) |
               M_EC_TO_U32(NUM_LINE) | M_EC_TO_U32(FRAME) | M_EC_TO_U32(R_MODE) |
               M_EC_TO_U32(BR_DEV) << M_EC_TO_U8(EC_C1_REG_BIT_FIELD_POS::BR);

    if ( MODE == EC_SPI_CFG_MODE::SLAVE ) {
        msk     |= M_EC_TO_U32(SSM) | M_EC_TO_U32(SSM_MODE);
    }

    return msk;
}

template < EC_SPI_CFG_MODE MODE, EC_SPI_CFG_CLK_POLARITY POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME FRAME, EC_SPI_CFG_RECEIVE_MODE R_MODE, EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV BR_DEV, EC_SPI_CFG_INTERRUPT_TX I_TX,
           EC_SPI_CFG_INTERRUPT_RX I_RX, EC_SPI_CFG_INTERRUPT_ERROR I_ER, EC_SPI_CFG_DMA_TX_BUF DMATX, EC_SPI_CFG_DMA_RX_BUF DMARX, EC_SPI_CFG_CS CS, EC_SPI_CFG_SSM SSM, EC_SPI_CFG_SSM_MODE SSM_MODE >
constexpr uint32_t spi_cfg< MODE, POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME, R_MODE, FORMAT,
                            BR_DEV, I_TX, I_RX, I_ER, DMATX, DMARX, CS, SSM, SSM_MODE >::c2_reg_msk_get ( void ) {
    uint32_t msk = 0;
    msk     |= M_EC_TO_U32(FORMAT) | M_EC_TO_U32(I_TX) | M_EC_TO_U32(I_RX) |
               M_EC_TO_U32(I_ER) | M_EC_TO_U32(DMATX) | M_EC_TO_U32(DMARX);

    if ( MODE == EC_SPI_CFG_MODE::MASTER ) {
        msk |= M_EC_TO_U32(CS);
    }

    return msk;
}


template < EC_SPI_NAME     SPIx, EC_SPI_CFG_CLK_POLARITY   POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE   NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE  ONE_LINE_MODE, EC_SPI_CFG_DATA_FRAME    FRAME,
           EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV    BR_DEV, EC_SPI_CFG_CS   CS >
const spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >* spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::instance ( void ) {
    static const  spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM > obj;
    return &obj;
}

/*
 * Реализация SPI на прерываниях через ОС.
 */
template < EC_SPI_NAME     SPIx, EC_SPI_CFG_CLK_POLARITY   POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE   NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE  ONE_LINE_MODE, EC_SPI_CFG_DATA_FRAME    FRAME,
           EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV    BR_DEV, EC_SPI_CFG_CS   CS >
constexpr spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::spi_master_hardware_os ( void ) {
    static_assert( ( SPIx == EC_SPI_NAME::SPI1 ) ||
                   ( SPIx == EC_SPI_NAME::SPI2 ) ||
                   ( SPIx == EC_SPI_NAME::SPI3 ),
                   "Invalid template parameter!The SPIx can be SPI1, SPI2 or SPI3!" );
}



template < EC_SPI_NAME     SPIx, EC_SPI_CFG_CLK_POLARITY   POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE   NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE  ONE_LINE_MODE, EC_SPI_CFG_DATA_FRAME    FRAME,
           EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV    BR_DEV, EC_SPI_CFG_CS   CS >
uint32_t spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::tx_e_flag_get ( void ) const {
    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    volatile uint32_t result = *M_U32_TO_P(M_GET_BB_P_PER((uint32_t)&S->S, M_EC_TO_U8(EC_S_REG_BIT_FIELD_POS::TXE)));
    return result;
}

template < EC_SPI_NAME     SPIx, EC_SPI_CFG_CLK_POLARITY   POLAR, EC_SPI_CFG_CLK_PHASE PHASE, EC_SPI_CFG_NUMBER_LINE   NUM_LINE, EC_SPI_CFG_ONE_LINE_MODE  ONE_LINE_MODE, EC_SPI_CFG_DATA_FRAME    FRAME,
           EC_SPI_CFG_FRAME_FORMAT FORMAT, EC_SPI_CFG_BAUD_RATE_DEV    BR_DEV, EC_SPI_CFG_CS   CS >
uint32_t spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::rx_n_e_flag_get ( void ) const {
    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    volatile uint32_t result = *M_U32_TO_P(M_GET_BB_P_PER((uint32_t)&S->S, M_EC_TO_U8(EC_S_REG_BIT_FIELD_POS::RXNE)));
    return result;
}


template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
int spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::reinit ( void ) const {
    this->mutex = USER_OS_STATIC_MUTEX_CREATE( &this->mutex_buf );
    this->semaphore = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &this->semaphore_buf );

    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    S->C1   =   0;                        // Отключаем SPI.
    S->S    =   0;                        // Сбрасываем все флаги прерываний.
    S->C1   =   this->cfg.c1_msk;         // Конфигурируем SPI.
    S->C2   =   this->cfg.c2_msk;

    return 0;
}

template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
void spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::on ( void ) const {
    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    S->C1 |= M_EC_TO_U32(EC_C1_REG_BIT_MSK::SPE);                   // Запскаем SPI.
}

template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
void spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::off ( void ) const {
    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    S->C1 &= ~M_EC_TO_U32(EC_C1_REG_BIT_MSK::SPE);                  // Отключаем SPI.
}

template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
int spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::tx ( void* p_array_tx, uint16_t length, uint32_t timeout_ms ) const {
    (void)timeout_ms;
    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    if ( length == 0 ) return -1;

    USER_OS_TAKE_MUTEX( this->mutex, portMAX_DELAY );

    if ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ) {
        number_items = --length;    // Отнимаем сначала одну, т.к. одну передаем сразу (посылку).
        p_tx = &( static_cast< spi_frame_size* >( p_array_tx ) )[1];    // Если транзакция всего одна, то ничего страшного, он просто не будет пользовать этот указатель (handler не будет пользовать).
        this->handler_rx_copy_cfg_flag = false;
        this->handler_tx_point_inc_cfg_flag = true;
        S->D    = *( static_cast< spi_frame_size* >( p_array_tx ) );                    // Делаем первую отправку.
        S->C2   = this->cfg.c2_msk;                                                     // Включаем нужные прерывания + параметры конфиграции интерфейса (мы сбросили этот регистр в 0 в прерывании, чтрбы быстро выйти из прерывания).
    }

    this->on();             // Включаем SPI (после передачи отключаем, чтобы не висеть в прерыании).
    bool reult = USER_OS_TAKE_BIN_SEMAPHORE( this->semaphore, portMAX_DELAY );

    USER_OS_GIVE_MUTEX( this->mutex );


    return ( reult ) ? 1 : 0;
}

template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
int spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::tx ( void* p_array_tx, void* p_array_rx, uint16_t length, uint32_t timeout_ms ) const {
    (void)timeout_ms;
    (void)p_array_tx; (void)p_array_rx; (void)length;
    return 0;
}

template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
int spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::rx ( void* p_array_rx, uint16_t length, uint32_t timeout_ms, uint8_t out_value ) const {
    (void)p_array_rx; (void)length; (void)out_value; (void)timeout_ms;
    return 0;
}

template < TEMPLATE_SPI_MASTER_HARD_OS_HEADLINE >
void spi_master_hardware_os< TEMPLATE_SPI_MASTER_HARD_OS_PARAM >::handler ( void ) const {
    spi_registers_struct*   S = ( spi_registers_struct* )M_EC_TO_U32(SPIx);
    /*
         * Сначала проверяем RX, а потом TX. Т.к. после проверки TX мы можем выставить
         * последнюю посылку на передачу и очистить number_items. А потом проверив
         * RX решим, что передача закончена и нужно отдать симафор.
         * Так мы потеряем одну транзакцию.
         */
    // Если SPI планиурется использовать на прием или чисто на прием.
    if ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ) {
        if ( this->rx_n_e_flag_get() == 1 ) {                                       // Если пришли данные.
            if ( handler_rx_copy_cfg_flag == true ) {                               // Если мы копируем данные куда-то себе.
                *p_rx = S->D;                                                       // Забираем себе.
                p_rx++;                                                             // В сл. раз кладем в сл. ячейку ( разрядность учитывается на этапе компиляции ).
                if ( this->number_items == 0 ) {                                    // Если передача завершена - отдаем семафор.
                    USER_OS_PRIO_TASK_WOKEN     prio;
                    USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR( this->semaphore, &prio );
                    this->off();                                                    // Отключаем транзакции SPI.
                    S->C2 = 0;                                                      // Отключаем генtрацию прерываний.
                }
            } else {
                // Если RX себе не сохраняем, то просто считаем в никуда.
                volatile spi_frame_size input_buf;
                input_buf = S->D;               // Что бы ни случилосб (на всякий случай) считываем данные.
                (void)input_buf;
            }
        }
    } else if ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::RECEIVE_ONLY ) {
        // Тут дописать, когда только на прием. Пока ни к спеху.
        while( true ) {};
    }

    // Если линия прием-передача или только на передачу.
    if ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ) {
        if ( this->tx_e_flag_get() == 1 ) {                                         // Если буфер на передачу пуст.
            if ( this->number_items != 0 ) {                                        // Если мы еще должны что-то передавать.
                S->D = *p_tx;                                                       // Ставим на передачу (разрядность учитывается на этапе компиляции).
                if ( this->handler_tx_point_inc_cfg_flag ) {                        // Если нам нужно передавать разные данные.
                    this->p_tx++;                                                   // В сл. раз уже другие данные.
                }
                this->number_items--;                                               // Мы передали еще 1 байт.
            } else {    // Если мы все передали и ответа не дожидаемся, то отдаем семафор и выходим.
                if ( handler_rx_copy_cfg_flag == false ) {
                    USER_OS_PRIO_TASK_WOKEN     prio;
                    USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR( this->semaphore, &prio );
                    this->off();                                                    // Отключаем транзакции SPI.
                    S->C2 = 0;                                                      // Отключаем генерацию прерываний (у нас есть прерывание по пустому буферу на передачу, с ним мы не выдем).
                }
            }
        }

    } else {    // Если только передача сюда дописать!
        while( true ) {};
    }

    S->S = 0;                      // СбрасываФем флаги.
}

#endif
