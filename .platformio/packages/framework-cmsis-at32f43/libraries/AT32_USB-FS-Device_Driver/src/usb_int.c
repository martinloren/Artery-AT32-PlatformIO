/**
  ******************************************************************************
  * File   : usb_int.c
  * Version: V1.2.2
  * Date   : 2020-07-01
  * Brief  : Endpoint CTRF (Low and High) interrupt's service routines
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t SaveRState;
__IO uint16_t SaveTState;

/* Extern variables ----------------------------------------------------------*/
extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Low priority Endpoint Correct Transfer interrupt's service.
  *         routine.
  * @param  None.               
  * @retval None.
  */
void CTR_LP(void)
{
  __IO uint16_t wEPVal = 0;
  /* stay in loop while pending interrupts */
  while (((wIstr = _GetINTSTS()) & INTSTS_CTFR) != 0)
  {
    /* extract highest priority endpoint number */
    EPindex = (uint8_t)(wIstr & INTSTS_EP_ID);
    if (EPindex != 0 )
    {
      /* Decode and service non control endpoints interrupt  */

      /* process related endpoint register */
      wEPVal = _GetENDPOINT(EPindex);      
      if ((wEPVal & EP_CTFR_TX) != 0)
      {
        /* clear int flag */
        _ClearEP_CTFR_TX(EPindex);

        /* call IN service function */
        (*pEpInt_IN[EPindex-1])();
        continue;
      } /* if((wEPVal & EP_CTFR_TX) != 0) */

      if ((wEPVal & EP_CTFR_RX) != 0)
      {
        /* clear int flag */
        _ClearEP_CTFR_RX(EPindex);

        /* call OUT service function */
        (*pEpInt_OUT[EPindex-1])();

      } /* if((wEPVal & EP_CTFR_RX) */

    }/* if(EPindex != 0) */
    else 
    {
      /* Decode and service control endpoint interrupt */
      /* calling related service routine */
      /* (Setup0_Process, In0_Process, Out0_Process) */

      /* save RX & TX status */
      /* and set both to NAK */
      
	    SaveRState = _GetENDPOINT(ENDP0);
	    SaveTState = SaveRState & EP_STS_TX;
	    SaveRState &=  EP_STS_RX;	

	    _SetEPRxTxStatus(ENDP0,EP_RX_NAK,EP_TX_NAK);

      /* DIR bit = origin of the interrupt */

      if ((wIstr & INTSTS_DIR) == 0)
      {
        /* DIR = 0 */

        /* DIR = 0      => IN  int */
        /* DIR = 0 implies that (EP_CTFR_TX = 1) always  */

        _ClearEP_CTFR_TX(ENDP0);
        In0_Process();

           /* before terminate set Tx & Rx status */

            _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
		  return;
      }
      else
      {
        /* DIR = 1 */

        /* DIR = 1 & CTR_RX       => SETUP or OUT int */
        /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */

        wEPVal = _GetENDPOINT(ENDP0);
        
        if ((wEPVal &EP_SETUP) != 0)
        {
          _ClearEP_CTFR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */
          Setup0_Process();
          /* before terminate set Tx & Rx status */

		      _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
          return;
        }

        else if ((wEPVal & EP_CTFR_RX) != 0)
        {
          _ClearEP_CTFR_RX(ENDP0);
          Out0_Process();
          /* before terminate set Tx & Rx status */
     
		     _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
          return;
        }
      }
    }/* if(EPindex != 0) else */

  }/* while(...) */
}

/**
  * @brief  High Priority Endpoint Correct Transfer interrupt's service.
  *         routine.
  * @param  None.               
  * @retval None.
  */
void CTR_HP(void)
{
  uint32_t wEPVal = 0;

  while (((wIstr = _GetINTSTS()) & INTSTS_CTFR) != 0)
  {
    _SetINTSTS((uint16_t)CLR_CTFR); /* clear CTR flag */
    /* extract highest priority endpoint number */
    EPindex = (uint8_t)(wIstr & INTSTS_EP_ID);
    if ( EPindex == 0 )
        return;
    /* process related endpoint register */
    wEPVal = _GetENDPOINT(EPindex);
    if ((wEPVal & EP_CTFR_RX) != 0)
    {
      /* clear int flag */
      _ClearEP_CTFR_RX(EPindex);

      /* call OUT service function */
      (*pEpInt_OUT[EPindex-1])();

    } /* if((wEPVal & EP_CTFR_RX) */
    else if ((wEPVal & EP_CTFR_TX) != 0)
    {
      /* clear int flag */
      _ClearEP_CTFR_TX(EPindex);

      /* call IN service function */
      (*pEpInt_IN[EPindex-1])();


    } /* if((wEPVal & EP_CTFR_TX) != 0) */

  }/* while(...) */
}


