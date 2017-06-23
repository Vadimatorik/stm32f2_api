#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

/**********************************************************************
 * Область enum class-ов.
 **********************************************************************/

/*
 * Перечень имеющихся физических портов ввода-вывода контроллера
 * (зависит от выбранного в stm32_f20x_f21x_conf.h контроллера).
 */
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE) \
	|defined(STM32F205RF)|defined(STM32F205RG)
enum class EC_PORT_NAME {
    A   = 0,
    B   = 1,
    C   = 2,
    D   = 3,
    H   = 4
};

#endif

#endif
