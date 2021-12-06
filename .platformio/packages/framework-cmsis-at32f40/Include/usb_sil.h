/**
  ******************************************************************************
  * File   : usb_sil.h 
  * Version: V1.2.2
  * Date   : 2020-07-01
  * Brief  : Simplified Interface Layer function prototypes.
  ******************************************************************************
  */



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_SIL_H
#define __USB_SIL_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint32_t USB_SIL_Init(void);
uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize);
uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer);

/* External variables --------------------------------------------------------*/

#endif /* __USB_SIL_H */


