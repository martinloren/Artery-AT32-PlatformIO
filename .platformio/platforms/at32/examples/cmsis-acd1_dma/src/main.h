/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/**************** UART printf ****************/
#define AT32_PRINT_UART                USART1
#define USARTx_IRQn                    USART1_IRQn
#define USARTx_IRQ_Handler             USART1_IRQHandler
#define AT32_PRINT_UART_RCC            RCC_APB2PERIPH_USART1

/*Tx*/
#define AT32_PRINT_UARTTX_PIN          GPIO_Pins_9 
#define AT32_PRINT_UARTTX_GPIO         GPIOA
#define AT32_PRINT_UARTTX_GPIO_RCC     RCC_APB2PERIPH_GPIOA

/*Rx*/
#define AT32_PRINT_UARTRX_PIN          GPIO_Pins_10
#define AT32_PRINT_UARTRX_GPIO         GPIOA
#define AT32_PRINT_UARTRX_GPIO_RCC     RCC_APB2PERIPH_GPIOA
/**************** End UART printf ****************/

void AT32_Board_Init(void);
void AT32_USB_GPIO_init(void);

#endif /* __MAIN_H */


