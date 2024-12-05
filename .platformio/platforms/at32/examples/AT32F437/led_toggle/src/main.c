/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes */
#include "at32f435_437_clock.h"
#include "delay.h"

#define LEDPERIPH   CRM_GPIOB_PERIPH_CLOCK
#define LEDPORT     (GPIOB)
#define LEDPIN      (GPIO_PINS_12)

/** @addtogroup AT32F437_periph_examples
  * @{
  */

/** @addtogroup 437_GPIO_led_toggle GPIO_led_toggle
  * @{
  */

/**
  * @brief  gpio configuration.
  * @param  none
  * @retval none
  */
static void gpio_config(void)
{
    gpio_init_type gpio_init_struct;
    crm_periph_clock_enable(LEDPERIPH, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    //configure the led gpio
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = LEDPIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(LEDPORT, &gpio_init_struct);
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
    system_clock_config();
    delay_init();

    gpio_config();

    gpio_bits_reset(LEDPORT, LEDPIN);

    for (;;) {
        delay_ms(500);
        LEDPORT->odt ^= LEDPIN;  // toggle pin
    }

    return 0;
}

/**
  * @}
  */

/**
  * @}
  */
