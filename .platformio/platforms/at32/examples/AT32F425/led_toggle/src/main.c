/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.0
  * @date     2021-12-31
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

#include "at32f425_board.h"
#include "at32f425_clock.h"

/** @addtogroup AT32F425_periph_examples
  * @{
  */
  
/** @addtogroup 425_GPIO_led_toggle GPIO_led_toggle
  * @{
  */
  

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  system_clock_config();

  at32_board_init();

  while(1)
  {
    at32_led_toggle(LED2);
    delay_ms(200);
    at32_led_toggle(LED3);
    delay_ms(200);
    at32_led_toggle(LED4);
    delay_ms(200);
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 
