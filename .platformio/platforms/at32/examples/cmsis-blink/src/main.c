/** Light on/off pin PC13, 100Hz frequency */

#include "at32f4xx.h"
#include "delay.h"

#define LEDPORT (GPIOC)
#define LED1 (13)
#define ENABLE_GPIO_CLOCK (RCC->APB2EN |= RCC_APB2EN_GPIOCEN) //RCC_APB2ENR_IOPCEN)
#define _MODER    CTRLH
#define GPIOMODER (GPIO_CTRLH_MDE13_0)


//Alternates blue and green LEDs quickly
int main(void)
{
    Delay_init();

    ENABLE_GPIO_CLOCK;              // enable the clock to GPIO
    LEDPORT->_MODER |= GPIOMODER;   // set pins to be general purpose output

    for (;;) {
        Delay_ms(1000);
        LEDPORT->OPTDT ^= (1<<LED1);  // toggle diodes ODR
    }

    return 0;
}
