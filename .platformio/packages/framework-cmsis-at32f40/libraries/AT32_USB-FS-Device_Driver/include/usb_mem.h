/**
  ******************************************************************************
  * File   : usb_mem.h 
  * Version: V1.2.2
  * Date   : 2020-07-01
  * Brief  : Utility prototypes functions for memory/PMA transfers
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_MEM_H
#define __USB_MEM_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);

/* External variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /*__USB_MEM_H*/


