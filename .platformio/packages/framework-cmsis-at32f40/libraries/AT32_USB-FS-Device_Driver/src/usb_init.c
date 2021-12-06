/**
  ******************************************************************************
  * File   : usb_init.c
  * Version: V1.2.2
  * Date   : 2020-07-01
  * Brief  : Initialization routines & global variables
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*  The number of current endpoint, it will be used to specify an endpoint */
 uint8_t	EPindex;
/*  The number of current device, it is an index to the Device_Table */
/* uint8_t	Device_no; */
/*  Points to the DEVICE_INFO structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_INFO *pInformation;
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */
DEVICE_PROP *pProperty;
/*  Temporary save the state of Rx & Tx status. */
/*  Whenever the Rx or Tx state is changed, its value is saved */
/*  in this variable first and will be set to the EPRB or EPRA */
/*  at the end of interrupt process */
uint16_t	SaveState ;
uint16_t  wInterrupt_Mask;
DEVICE_INFO	Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : USB_Init
* Description    : USB system initialization
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

/* Re-enumerate the USB */
void reenumerate() {
    //  pinMode(PA12, OUTPUT);
    GPIO_InitType GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Pins = GPIO_Pins_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_PU;
    GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_WriteBit(GPIOA, GPIO_Pins_12, Bit_RESET); //Blue Pill
    for(int i=0;i<1512;i++){};

  	GPIO_InitStruct.GPIO_Pins = GPIO_Pins_12;
  	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStruct);

    for(int i=0;i<512;i++){};
}

void USB_BluePill_Reenumerate()
{
  //__HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitType GPIO_InitStruct = {0};

  GPIO_InitStruct.GPIO_Pins = GPIO_Pins_12;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT_OD;
  GPIO_InitStruct.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_WriteBit(GPIOA, GPIO_Pins_12, Bit_RESET);
  //HAL_Delay(1);
}

/**
  * @brief  USB system initialization.
  * @param  None.   
  * @retval None.
  */
void USB_Init(void)
{
  //reenumerate();
  //USB_BluePill_Reenumerate();
  pInformation = &Device_Info;
  pInformation->ControlState = 2;
  pProperty = &Device_Property;
  pUser_Standard_Requests = &User_Standard_Requests;
  /* Initialize devices one by one */
  pProperty->Init();
  //reenumerate();
  //USB_BluePill_Reenumerate();
}


