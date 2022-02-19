/**
  **************************************************************************
  * @file     cdc_class.c
  * @version  v2.0.4
  * @date     2021-12-31
  * @brief    usb cdc class type
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
#include "usbd_core.h"
#include "cdc_class.h"
#include "cdc_desc.h"

/** @addtogroup AT32F435_437_middlewares_usbd_class
  * @{
  */
  
/** @defgroup USB_cdc_class
  * @brief usb device class cdc demo
  * @{
  */  

/** @defgroup USB_cdc_class_private_functions
  * @{
  */

usb_sts_type class_init_handler(void *udev);
usb_sts_type class_clear_handler(void *udev);
usb_sts_type class_setup_handler(void *udev, usb_setup_type *setup);
usb_sts_type class_ept0_tx_handler(void *udev);
usb_sts_type class_ept0_rx_handler(void *udev);
usb_sts_type class_in_handler(void *udev, uint8_t ept_num);
usb_sts_type class_out_handler(void *udev, uint8_t ept_num);
usb_sts_type class_sof_handler(void *udev);
usb_sts_type class_event_handler(void *udev, usbd_event_type event);

void usb_vcp_cmd_process(void *udev, uint8_t cmd, uint8_t *buff, uint16_t len);
/* usb rx and tx buffer */
static uint32_t alt_setting = 0;
static uint8_t g_rx_buff[USBD_OUT_MAXPACKET_SIZE];
//static uint8_t g_tx_buff[USBD_IN_MAXPACKET_SIZE];
static uint8_t g_cmd[USBD_CMD_MAXPACKET_SIZE];
static uint8_t g_req;
static uint16_t g_len, g_rxlen;
__IO uint8_t g_tx_completed = 1, g_rx_completed = 0;

linecoding_type linecoding =
{
  115200,
  0x00,
  0x00,
  0x08
};

/* static variable */


/* usb device class handler */
usbd_class_handler class_handler = 
{
  class_init_handler,
  class_clear_handler,
  class_setup_handler,
  class_ept0_tx_handler,
  class_ept0_rx_handler,
  class_in_handler,
  class_out_handler,
  class_sof_handler,
  class_event_handler,
};

/**
  * @brief  initialize usb custom hid endpoint
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_init_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  
  /* open in endpoint */
  usbd_ept_open(pudev, USBD_CDC_INT_EPT, EPT_INT_TYPE, USBD_CMD_MAXPACKET_SIZE);
  
  /* open in endpoint */
  usbd_ept_open(pudev, USBD_CDC_BULK_IN_EPT, EPT_BULK_TYPE, USBD_IN_MAXPACKET_SIZE);
  
  /* open out endpoint */
  usbd_ept_open(pudev, USBD_CDC_BULK_OUT_EPT, EPT_BULK_TYPE, USBD_OUT_MAXPACKET_SIZE);
  
  /* set out endpoint to receive status */
  usbd_ept_recv(pudev, USBD_CDC_BULK_OUT_EPT, g_rx_buff, USBD_OUT_MAXPACKET_SIZE);
  
  g_tx_completed = 1;
  
  return status;
}

/**
  * @brief  clear endpoint or other state
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_clear_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  
  /* close in endpoint */
  usbd_ept_close(pudev, USBD_CDC_INT_EPT);
  
  /* close in endpoint */
  usbd_ept_close(pudev, USBD_CDC_BULK_IN_EPT);
  
  /* close out endpoint */
  usbd_ept_close(pudev, USBD_CDC_BULK_OUT_EPT);
  
  return status;
}

/**
  * @brief  usb device class setup request handler
  * @param  udev: to the structure of usbd_core_type
  * @param  setup: setup packet
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_setup_handler(void *udev, usb_setup_type *setup)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;

  switch(setup->bmRequestType & USB_REQ_TYPE_RESERVED)
  {
    /* class request */
    case USB_REQ_TYPE_CLASS:
      if(setup->wLength)
      {
        if(setup->bmRequestType & USB_REQ_DIR_DTH)
        {
          usb_vcp_cmd_process(udev, setup->bRequest, g_cmd, setup->wLength);
          usbd_ctrl_send(pudev, g_cmd, setup->wLength);
        }
        else
        {
          g_req = setup->bRequest;
          g_len = setup->wLength;
          usbd_ctrl_recv(pudev, g_cmd, g_len);
          
        }
      }
      break;
    /* standard request */
    case USB_REQ_TYPE_STANDARD:
      switch(setup->bRequest)
      {
        case USB_STD_REQ_GET_DESCRIPTOR:
          usbd_ctrl_unsupport(pudev);
          break;
        case USB_STD_REQ_GET_INTERFACE:
          usbd_ctrl_send(pudev, (uint8_t *)&alt_setting, 1);
          break;
        case USB_STD_REQ_SET_INTERFACE:
          alt_setting = setup->wValue;
          break;
        default:
          break;
      }
      break;
    default:
      usbd_ctrl_unsupport(pudev);
      break;
  }
  return status;
}

/**
  * @brief  usb device endpoint 0 in status stage complete
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_ept0_tx_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  
  /* ...user code... */
  
  return status;
}

/**
  * @brief  usb device endpoint 0 out status stage complete
  * @param  udev: usb device core handler type
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_ept0_rx_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  uint32_t recv_len = usbd_get_recv_len(pudev, 0);
  /* ...user code... */
  if( g_req == SET_LINE_CODING)
  {
    /* class process */
    usb_vcp_cmd_process(udev, g_req, g_cmd, recv_len);
  }
  
  return status;
}

/**
  * @brief  usb device transmision complete handler
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_num: endpoint number
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_in_handler(void *udev, uint8_t ept_num)
{
  usbd_core_type *pudev = (usbd_core_type *)udev;
  usb_sts_type status = USB_OK;
  
  /* ...user code...
    trans next packet data
  */
  usbd_flush_tx_fifo(pudev, ept_num);
  g_tx_completed = 1;
  
  return status;
}

/**
  * @brief  usb device endpoint receive data
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_num: endpoint number
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_out_handler(void *udev, uint8_t ept_num)
{
  usb_sts_type status = USB_OK;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  
  /* get endpoint receive data length  */
  g_rxlen = usbd_get_recv_len(pudev, ept_num);
  
  /*set recv flag*/
  g_rx_completed = 1;
  
  return status;
}

/**
  * @brief  usb device sof handler
  * @param  udev: to the structure of usbd_core_type
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_sof_handler(void *udev)
{
  usb_sts_type status = USB_OK;
  
  /* ...user code... */
  
  return status;
}

/**
  * @brief  usb device event handler
  * @param  udev: to the structure of usbd_core_type
  * @param  event: usb device event
  * @retval status of usb_sts_type                            
  */
usb_sts_type class_event_handler(void *udev, usbd_event_type event)
{
  usb_sts_type status = USB_OK;
  switch(event)
  {
    case USBD_RESET_EVENT:
      
      /* ...user code... */
    
      break;
    case USBD_SUSPEND_EVENT:
      
      /* ...user code... */
    
      break;
    case USBD_WAKEUP_EVENT:
      /* ...user code... */
    
      break;
    case USBD_INISOINCOM_EVENT:
      break;
    case USBD_OUTISOINCOM_EVENT:
      break;
    
    default:
      break;
  }
  return status;
}

/**
  * @brief  usb device class rx data process
  * @param  udev: to the structure of usbd_core_type
  * @param  recv_data: receive buffer
  * @retval receive data len                            
  */
uint16_t usb_vcp_get_rxdata(void *udev, uint8_t *recv_data)
{
  uint16_t i_index = 0;
  uint16_t tmp_len = g_rxlen;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  
  if(g_rx_completed == 0)
  {
    return 0;
  }
  g_rx_completed = 0;
  tmp_len = g_rxlen;
  for(i_index = 0; i_index < g_rxlen; i_index ++)
  {
    recv_data[i_index] = g_rx_buff[i_index];
  }
  
  usbd_ept_recv(pudev, USBD_CDC_BULK_OUT_EPT, g_rx_buff, USBD_OUT_MAXPACKET_SIZE);
  
  return tmp_len;
}

/**
  * @brief  usb device class send data
  * @param  udev: to the structure of usbd_core_type
  * @param  send_data: send data buffer
  * @param  len: send length
  * @retval error status                            
  */
error_status usb_vcp_send_data(void *udev, uint8_t *send_data, uint16_t len)
{
  error_status status = SUCCESS;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  if(g_tx_completed)
  {
    g_tx_completed = 0;
    usbd_ept_send(pudev, USBD_CDC_BULK_IN_EPT, send_data, len);
  }
  else
  {
    status = ERROR;
  }
  return status;
}


/**
  * @brief  usb device function
  * @param  udev: to the structure of usbd_core_type
  * @param  cmd: request number
  * @param  buff: request buffer
  * @param  len: buffer length
  * @retval none                            
  */
void usb_vcp_cmd_process(void *udev, uint8_t cmd, uint8_t *buff, uint16_t len)
{
  switch(cmd)
  {
    case SET_LINE_CODING:
      linecoding.bitrate = (uint32_t)(buff[0] | (buff[1] << 8) | (buff[2] << 16) | (buff[3] <<24));
      linecoding.format = buff[4];
      linecoding.parity = buff[5];
      linecoding.data = buff[6];
      break;
    
    case GET_LINE_CODING:
      buff[0] = (uint8_t)linecoding.bitrate;
      buff[1] = (uint8_t)(linecoding.bitrate >> 8);
      buff[2] = (uint8_t)(linecoding.bitrate >> 16);
      buff[3] = (uint8_t)(linecoding.bitrate >> 24);
      buff[4] = (uint8_t)(linecoding.format);
      buff[5] = (uint8_t)(linecoding.parity);
      buff[6] = (uint8_t)(linecoding.data);
      break;
    
    default:
      break;
  }
}

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

