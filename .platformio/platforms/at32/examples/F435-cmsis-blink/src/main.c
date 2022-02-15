/** Light on/off pin PB12, 1Hz frequency */
#include "at32f435_437_clock.h"
#include "delay.h"

#define LEDPERIPH   CRM_GPIOB_PERIPH_CLOCK
#define LEDPORT     (GPIOB)
#define LEDPIN      (GPIO_PINS_12)


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
