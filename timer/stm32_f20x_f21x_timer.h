﻿#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

#include "mk_hardware_interfaces_timer.h"
#include "stm32_f20x_f21x_timer_struct.h"

//
// Генератор прямоугольных импульсов.
//
template < TIM1_OR_TIM8        P_TIM,                   // Используемый таймер.
           uint16_t            PRESCALER,               // Предделитель 1..0x10000.
           uint16_t            PERIOD_TOGGLE,           // Еще 1 делитель 1..0x10000.
           EC_TIM_CH_TOGGLE    CH_TOGGLE,               // Канал, на котором произволится генерация (именно таймера, не пина!).
           EC_TIM_CH_MODE      MODE >                   // На какие выводы выдавать сигнал?
class tim1_or_8_comp_one_channel : public tim_comp_one_channel_base {
public:
    tim1_or_8_comp_one_channel ();
    void reinit     ( void ) const;
    void on         ( void ) const;
    void off        ( void ) const;

private:
    constexpr uint32_t ccm1_reg_msk_get ();
    constexpr uint32_t ccm2_reg_msk_get ();
    constexpr uint32_t cce_reg_msk_get  ();
    constexpr uint32_t bdt_reg_msk_get  ();

    tim_1_or_8_registers_struct*            const tim;
    const tim_1_or_8_registers_struct       cfg;
};

//
// Генератор прерываний.
//
template < TIM6_OR_TIM7        P_TIM,                   // Используемый таймер.
           uint16_t            PRESCALER,               // Предделитель 1..0x10000.
           uint16_t            PERIOD_TOGGLE >          // Еще 1 делитель 1..0x10000.
class tim6_or_7_interrupt : public tim_interrupt_base {
public:
    tim6_or_7_interrupt ();
    void reinit                 ( void ) const;
    void clear_interrupt_flag   ( void ) const;         // Вызывать по входу в прерывание.
    void on                     ( void ) const;
    void off                    ( void ) const;

private:
    tim_6_or_7_registers_struct*            const tim;
    const tim_6_or_7_registers_struct       cfg;
};

#include "stm32_f20x_f21x_timer_func.h"

#endif
