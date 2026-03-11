/** Light on/off pin PB12, 1Hz frequency */
#include "at32f435_437_clock.h"
#include "delay.h"

#define BLACKPILL // BLUEPILL BLACKPILL QFP48_FLASHER


// Just add the following code to extend sram size to 512KB, and the rest of the code is same as the original main.c ----------
#define EXTEND_SRAM FLASH_EOPB0_SRAM_512K //512KB RAM

#ifdef __cplusplus
extern "C" {
#endif
void extend_sram(void);
#ifdef __cplusplus
}
#endif

/**
  * @brief  to extend sram size, it goes integrated in the Startup file, 
  * so it will be executed before main function, and it will check if the sram size is expected, 
  * if not, it will change eopb0 to extend sram size, then reset system to make it take effect.
  * @param  none
  * @retval none
  */
void extend_sram(void)
{
  /* check if ram has been set to expectant size, if not, change eopb0 */
  if(((USD->eopb0) & 0x07) != EXTEND_SRAM)
  {
    flash_unlock();
    /* erase user system data bytes */
    flash_user_system_data_erase();

    /* change sram size */
    flash_eopb0_config(EXTEND_SRAM);

    /* system reset */
    nvic_system_reset();
  }
}

//--------------------------------------------------------------------------------------------------------------------


#ifdef BLUEPILL
    #define LEDPERIPH   CRM_GPIOC_PERIPH_CLOCK
    #define LEDPORT     (GPIOC)
    #define LEDPIN      (GPIO_PINS_13)
#endif
#ifdef BLACKPILL
    #define LEDPERIPH   CRM_GPIOB_PERIPH_CLOCK
    #define LEDPORT     (GPIOB)
    #define LEDPIN      (GPIO_PINS_12)
#endif
#ifdef QFP48_FLASHER
    #define LEDPERIPH   CRM_GPIOB_PERIPH_CLOCK
    #define LEDPORT     (GPIOB)
    #define LEDPIN      (GPIO_PINS_14)
#endif

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

//Flash LEDs quickly
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
