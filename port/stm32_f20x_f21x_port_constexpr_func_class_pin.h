#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port_struct.h"
#include "stm32_f20x_f21x_port_struct_class_pin.h"

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

constexpr pin::pin ( const pin_config_t* const pin_cfg_array ):
    p_bsr               ( this->p_bsr_get( pin_cfg_array ) ),
    p_bb_odr_read       ( this->odr_bit_read_bb_p_get( pin_cfg_array ) ),
    bsr_set_msk         ( this->set_msk_get( pin_cfg_array ) ),
    bsr_reset_msk       ( this->reset_msk_get( pin_cfg_array ) ),
    p_bb_idr_read       ( this->bb_p_idr_read_get( pin_cfg_array ) ) {};

/**********************************************************************
 * Область constexpr функций.
 **********************************************************************/

/*
 * Метод возвращает маску установки выхода в "1" через регистр BSR.
 */
constexpr uint32_t pin::set_msk_get ( const pin_config_t* const pin_cfg_array ) {
    return 1 << M_EC_TO_U8(pin_cfg_array->pin_name);
}

/*
 * Метод возвращает маску установки выхода в "0" через регистр BSR.
 */
constexpr uint32_t pin::reset_msk_get ( const pin_config_t* const pin_cfg_array ) {
    return 1 << M_EC_TO_U8( pin_cfg_array->pin_name ) + 16;
}

/*
 * Метод возвращает указатель на регистр BSR, к которому относится вывод.
 */
constexpr uint32_t pin::p_bsr_get( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port = p_base_port_address_get( pin_cfg_array->port );
    return p_port + 0x18;
}

/*
 * Метод возвращает указатель на bit_banding
 * область памяти, в которой находится бит состояния входа.
 */
constexpr uint32_t pin::bb_p_idr_read_get ( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port = p_base_port_address_get( pin_cfg_array->port );
    uint32_t p_idr  = p_port + 0x10;
    return M_GET_BB_P_PER(p_idr, M_EC_TO_U8(pin_cfg_array->pin_name));
}
/*
 * Метод возвращает указатель на bit banding область памяти,
 * с выставленным пользователем состоянием на выходе вывода.
 */
constexpr uint32_t pin::odr_bit_read_bb_p_get ( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port     = p_base_port_address_get( pin_cfg_array->port );
    uint32_t p_reg_odr  = p_port + 0x14;
    return M_GET_BB_P_PER(p_reg_odr, M_EC_TO_U8(pin_cfg_array->pin_name));
}

#endif
