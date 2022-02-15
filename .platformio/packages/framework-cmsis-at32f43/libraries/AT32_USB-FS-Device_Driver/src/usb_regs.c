/**
  ******************************************************************************
  * File   : usb_reg.c 
  * Version: V1.2.2
  * Date   : 2020-07-01
  * Brief  : Interface functions to USB cell registers
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
int PMAAddr = 0x40006000;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Set the CTRL register value.
  * @param  wRegValue:  new register value.     
  * @retval None.
  */
void SetCTRL(uint16_t wRegValue)
{
  _SetCTRL(wRegValue);
}

/**
  * @brief  returns the CTRL register value.
  * @param  None.     
  * @retval CTRL register Value..
  */
uint16_t GetCTRL(void)
{
  return(_GetCTRL());
}

/**
  * @brief  Set the INTSTS register value.
  * @param  wRegValue:  new register value.      
  * @retval None.
  */
void SetINTSTS(uint16_t wRegValue)
{
  _SetINTSTS(wRegValue);
}

/**
  * @brief  Returns the INTSTS register value.
  * @param  None.    
  * @retval INTSTS register Value.
  */
uint16_t GetINTSTS(void)
{
  return(_GetINTSTS());
}

/**
  * @brief  Returns the FRNUM register value.
  * @param  None.    
  * @retval FRNUM register Value.
  */
uint16_t GetFRNUM(void)
{
  return(_GetFRNUM());
}

/**
  * @brief  Set the DEVADR register value.
  * @param  wRegValue:  new register value.    
  * @retval None.
  */
void SetDEVADR(uint16_t wRegValue)
{
  _SetDEVADR(wRegValue);
}

/**
  * @brief  Returns the DEVADR register value.
  * @param  None.    
  * @retval DEVADR register Value.
  */
uint16_t GetDEVADR(void)
{
  return(_GetDEVADR());
}

/**
  * @brief  Set the BUFTBL.
  * @param  wRegValue: New register value.    
  * @retval None.
  */
void SetBUFTBL(uint16_t wRegValue)
{
  _SetBUFTBL(wRegValue);
}

/**
  * @brief  Returns the BUFTBL register value.
  * @param  None    
  * @retval BUFTBL address.
  */
uint16_t GetBUFTBL(void)
{
  return(_GetBUFTBL());
}

/**
  * @brief  Set the Endpoint register value.
  * @param  bEpNum: Endpoint Number. 
  * @param  wRegValue:  New register value. 
  * @retval None.
  */
void SetENDPOINT(uint8_t bEpNum, uint16_t wRegValue)
{
  _SetENDPOINT(bEpNum, wRegValue);
}

/**
  * @brief  Return the Endpoint register value.
  * @param  bEpNum: Endpoint Number. 
  * @retval Endpoint register value.
  */
uint16_t GetENDPOINT(uint8_t bEpNum)
{
  return(_GetENDPOINT(bEpNum));
}

/**
  * @brief  sets the type in the endpoint register.
  * @param  bEpNum: Endpoint Number. 
  * @param  wType: type definition.
  * @retval None.
  */
void SetEPType(uint8_t bEpNum, uint16_t wType)
{
  _SetEPType(bEpNum, wType);
}

/**
  * @brief  Returns the endpoint type.
  * @param  bEpNum: Endpoint Number. 
  * @retval Endpoint Type.
  */
uint16_t GetEPType(uint8_t bEpNum)
{
  return(_GetEPType(bEpNum));
}

/**
  * @brief  Set the status of Tx endpoint.
  * @param  bEpNum: Endpoint Number. 
  * @param  wState: new state.
  * @retval None.
  */
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState)
{
  _SetEPTxStatus(bEpNum, wState);
}

/**
  * @brief  Set the status of Rx endpoint.
  * @param  bEpNum: Endpoint Number. 
  * @param  wState: new state.
  * @retval None.
  */
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState)
{
  _SetEPRxStatus(bEpNum, wState);
}

/**
  * @brief  sets the status for Double Buffer Endpoint to STALL
  * @param  bEpNum: Endpoint Number. 
  * @param  bDir: Endpoint direction.
  * @retval None.
  */
void SetDouBleBuffEPStall(uint8_t bEpNum, uint8_t bDir)
{
  uint16_t Endpoint_DTOG_Status;
  Endpoint_DTOG_Status = GetENDPOINT(bEpNum);
  if (bDir == EP_DBUF_OUT)
  { /* OUT double buffered endpoint */
    _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPRX_DTOG1);
  }
  else if (bDir == EP_DBUF_IN)
  { /* IN double buffered endpoint */
    _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPTX_DTOG1);
  }
}

/**
  * @brief  Returns the endpoint Tx status.
  * @param  bEpNum: Endpoint Number. 
  * @retval Endpoint TX Status.
  */
uint16_t GetEPTxStatus(uint8_t bEpNum)
{
  return(_GetEPTxStatus(bEpNum));
}

/**
  * @brief  Returns the endpoint Rx status.
  * @param  bEpNum: Endpoint Number. 
  * @retval Endpoint RX Status.
  */
uint16_t GetEPRxStatus(uint8_t bEpNum)
{
  return(_GetEPRxStatus(bEpNum));
}

/**
  * @brief  Valid the endpoint Tx Status.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void SetEPTxValid(uint8_t bEpNum)
{
  _SetEPTxStatus(bEpNum, EP_TX_VALID);
}

/**
  * @brief  Valid the endpoint Rx Status.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void SetEPRxValid(uint8_t bEpNum)
{
  _SetEPRxStatus(bEpNum, EP_RX_VALID);
}

/**
  * @brief  Clear the EP_SUBTYPE bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void SetEP_SUBTYPE(uint8_t bEpNum)
{
  _SetEP_SUBTYPE(bEpNum);
}

/**
  * @brief  set the  EP_SUBTYPE bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ClearEP_SUBTYPE(uint8_t bEpNum)
{
  _ClearEP_SUBTYPE(bEpNum);
}

/**
  * @brief  Clear the Status Out of the related Endpoint
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void Clear_Status_Out(uint8_t bEpNum)
{
  _ClearEP_SUBTYPE(bEpNum);
}

/**
  * @brief  Set the Status Out of the related Endpoint
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void Set_Status_Out(uint8_t bEpNum)
{
  _SetEP_SUBTYPE(bEpNum);
}

/**
  * @brief  Enable the double buffer feature for the endpoint.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void SetEPDoubleBuff(uint8_t bEpNum)
{
  _SetEP_SUBTYPE(bEpNum);
}

/**
  * @brief  Disable the double buffer feature for the endpoint. 
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ClearEPDoubleBuff(uint8_t bEpNum)
{
  _ClearEP_SUBTYPE(bEpNum);
}

/**
  * @brief  Returns the Stall status of the Tx endpoint. 
  * @param  bEpNum: Endpoint Number. 
  * @retval Tx Stall status.
  */
uint16_t GetTxStallStatus(uint8_t bEpNum)
{
  return(_GetTxStallStatus(bEpNum));
}

/**
  * @brief  Returns the Stall status of the Rx endpoint. 
  * @param  bEpNum: Endpoint Number. 
  * @retval Rx Stall status.
  */
uint16_t GetRxStallStatus(uint8_t bEpNum)
{
  return(_GetRxStallStatus(bEpNum));
}

/**
  * @brief  Clear the CTRF_RX bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ClearEP_CTFR_RX(uint8_t bEpNum)
{
  _ClearEP_CTFR_RX(bEpNum);
}

/**
  * @brief  Clear the CTRF_TX bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ClearEP_CTFR_TX(uint8_t bEpNum)
{
  _ClearEP_CTFR_TX(bEpNum);
}

/**
  * @brief  Toggle the DTOG_RX bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ToggleDTOG_RX(uint8_t bEpNum)
{
  _ToggleDTOG_RX(bEpNum);
}

/**
  * @brief  Toggle the DTOG_TX bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ToggleDTOG_TX(uint8_t bEpNum)
{
  _ToggleDTOG_TX(bEpNum);
}

/**
  * @brief  Clear the DTOG_RX bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ClearDTOG_RX(uint8_t bEpNum)
{
  _ClearDTOG_RX(bEpNum);
}

/**
  * @brief  Clear the DTOG_TX bit.
  * @param  bEpNum: Endpoint Number. 
  * @retval None.
  */
void ClearDTOG_TX(uint8_t bEpNum)
{
  _ClearDTOG_TX(bEpNum);
}

/**
  * @brief  Set the endpoint address.
  * @param  bEpNum: Endpoint Number. 
  * @param  bAddr: New endpoint address. 
  * @retval None.
  */
void SetEPAddress(uint8_t bEpNum, uint8_t bAddr)
{
  _SetEPAddress(bEpNum, bAddr);
}

/**
  * @brief  Get the endpoint address.
  * @param  bEpNum: Endpoint Number. 
  * @retval Endpoint address.
  */
uint8_t GetEPAddress(uint8_t bEpNum)
{
  return(_GetEPAddress(bEpNum));
}

/**
  * @brief  Set the endpoint Tx buffer address.
  * @param  bEpNum: Endpoint Number. 
  * @param  wAddr: New address. 
  * @retval None.
  */
void SetEPTxAddr(uint8_t bEpNum, uint16_t wAddr)
{
  _SetEPTxAddr(bEpNum, wAddr);
}

/**
  * @brief  Set the endpoint Rx buffer address.
  * @param  bEpNum: Endpoint Number. 
  * @param  wAddr: New address. 
  * @retval None.
  */
void SetEPRxAddr(uint8_t bEpNum, uint16_t wAddr)
{
  _SetEPRxAddr(bEpNum, wAddr);
}

/**
  * @brief  Returns the endpoint Tx buffer address.
  * @param  bEpNum: Endpoint Number. 
  * @retval Tx buffer address.
  */
uint16_t GetEPTxAddr(uint8_t bEpNum)
{
  return(_GetEPTxAddr(bEpNum));
}

/**
  * @brief  Returns the endpoint Rx buffer address.
  * @param  bEpNum: Endpoint Number. 
  * @retval Rx buffer address.
  */
uint16_t GetEPRxAddr(uint8_t bEpNum)
{
  return(_GetEPRxAddr(bEpNum));
}

/**
  * @brief  Set the Tx count.
  * @param  bEpNum: Endpoint Number. 
  * @param  wCount: new count value. 
  * @retval None.
  */
void SetEPTxCount(uint8_t bEpNum, uint16_t wCount)
{
  _SetEPTxCount(bEpNum, wCount);
}

/**
  * @brief  Set the Count Rx Register value.
  * @param  *pdwReg: point to the register. 
  * @param  wCount: the new register value.
  * @retval None.
  */
void SetEPCountRxReg(uint32_t *pdwReg, uint16_t wCount)
{
  _SetEPCountRxReg(dwReg, wCount);
}

/**
  * @brief  Set the Rx count.
  * @param  bEpNum: Endpoint Number.  
  * @param  wCount: the new count value.
  * @retval None.
  */
void SetEPRxCount(uint8_t bEpNum, uint16_t wCount)
{
  _SetEPRxCount(bEpNum, wCount);
}

/**
  * @brief  Get the Tx count.
  * @param  bEpNum: Endpoint Number.  
  * @retval Tx count value.
  */
uint16_t GetEPTxCount(uint8_t bEpNum)
{
  return(_GetEPTxCount(bEpNum));
}

/**
  * @brief  Get the Rx count.
  * @param  bEpNum: Endpoint Number.  
  * @retval Rx count value.
  */
uint16_t GetEPRxCount(uint8_t bEpNum)
{
  return(_GetEPRxCount(bEpNum));
}

/**
  * @brief  Set the addresses of the buffer 0 and 1.
  * @param  bEpNum: Endpoint Number. 
  * @param  wBuf0Addr: new address of buffer 0. 
  * @param  wBuf1Addr: new address of buffer 1.
  * @retval None.
  */
void SetEPDblBuffAddr(uint8_t bEpNum, uint16_t wBuf0Addr, uint16_t wBuf1Addr)
{
  _SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr);
}

/**
  * @brief  Set the Buffer 0 address.
  * @param  bEpNum: Endpoint Number. 
  * @param  wBuf0Addr: new address of buffer 0. 
  * @retval None.
  */
void SetEPDblBuf0Addr(uint8_t bEpNum, uint16_t wBuf0Addr)
{
  _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);
}

/**
  * @brief  Set the Buffer 1 address.
  * @param  bEpNum: Endpoint Number. 
  * @param  wBuf1Addr: new address of buffer 1. 
  * @retval None.
  */
void SetEPDblBuf1Addr(uint8_t bEpNum, uint16_t wBuf1Addr)
{
  _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);
}

/**
  * @brief  Returns the address of the Buffer 0.
  * @param  bEpNum: Endpoint Number. 
  * @retval buffer 0 address.
  */
uint16_t GetEPDblBuf0Addr(uint8_t bEpNum)
{
  return(_GetEPDblBuf0Addr(bEpNum));
}

/**
  * @brief  Returns the address of the Buffer 1.
  * @param  bEpNum: Endpoint Number. 
  * @retval buffer 1 address.
  */
uint16_t GetEPDblBuf1Addr(uint8_t bEpNum)
{
  return(_GetEPDblBuf1Addr(bEpNum));
}

/**
  * @brief  Set the number of bytes for a double Buffer endpoint.
  * @param  bEpNum: Endpoint Number.
  * @param  bDin: Endpoint dir (IN/OUT). 
  * @param  wCount: buffer count. 
  * @retval None.
  */
void SetEPDblBuffCount(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
  _SetEPDblBuffCount(bEpNum, bDir, wCount);
}

/**
  * @brief  Set the number of bytes for a double Buffer0 endpoint.
  * @param  bEpNum: Endpoint Number.
  * @param  bDin: Endpoint dir (IN/OUT). 
  * @param  wCount: buffer count. 
  * @retval None.
  */
void SetEPDblBuf0Count(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
  _SetEPDblBuf0Count(bEpNum, bDir, wCount);
}

/**
  * @brief  Set the number of bytes for a double Buffer1 endpoint.
  * @param  bEpNum: Endpoint Number.
  * @param  bDin: Endpoint dir (IN/OUT). 
  * @param  wCount: buffer count. 
  * @retval None.
  */
void SetEPDblBuf1Count(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
  _SetEPDblBuf1Count(bEpNum, bDir, wCount);
}

/**
  * @brief  Returns the number of byte received in the buffer 0 
            of a double Buffer endpoint.
  * @param  bEpNum: Endpoint Number.
  * @retval Endpoint Buffer 0 count.
  */
uint16_t GetEPDblBuf0Count(uint8_t bEpNum)
{
  return(_GetEPDblBuf0Count(bEpNum));
}

/**
  * @brief  Returns the number of byte received in the buffer 1 
            of a double Buffer endpoint.
  * @param  bEpNum: Endpoint Number.
  * @retval Endpoint Buffer 1 count.
  */
uint16_t GetEPDblBuf1Count(uint8_t bEpNum)
{
  return(_GetEPDblBuf1Count(bEpNum));
}

/**
  * @brief  gets direction of the double buffered endpoint.
  * @param  bEpNum: Endpoint Number.
  * @retval EP_DBUF_OUT, EP_DBUF_IN,
  *         EP_DBUF_ERR if the endpoint counter not yet programmed.
  */
EP_DBUF_DIR GetEPDblBufDir(uint8_t bEpNum)
{
  if ((uint16_t)(*_pEPRxCount(bEpNum) & 0xFC00) != 0)
    return(EP_DBUF_OUT);
  else if (((uint16_t)(*_pEPTxCount(bEpNum)) & 0x03FF) != 0)
    return(EP_DBUF_IN);
  else
    return(EP_DBUF_ERR);
}

/**
  * @brief  free buffer used from the application realizing it to the line
            toggles bit SW_BUF in the double buffered endpoint register.
  * @param  bEpNum: Endpoint Number.
  * @param  bDir: Endpoint dir (IN/OUT).
  * @retval None.
  */
void FreeUserBuffer(uint8_t bEpNum, uint8_t bDir)
{
  if (bDir == EP_DBUF_OUT)
  { /* OUT double buffered endpoint */
    _ToggleDTOG_TX(bEpNum);
  }
  else if (bDir == EP_DBUF_IN)
  { /* IN double buffered endpoint */
    _ToggleDTOG_RX(bEpNum);
  }
}

/**
  * @brief  merge two byte in a word.
  * @param  bh: byte high.
  * @param  bl: bytes low.
  * @retval resulted word..
  */
uint16_t ToWord(uint8_t bh, uint8_t bl)
{
  uint16_t wRet;
  wRet = (uint16_t)bl | ((uint16_t)bh << 8);
  return(wRet);
}

/**
  * @brief  Swap two byte in a word.
  * @param  wSwW: word to Swap.
  * @retval resulted word..
  */
uint16_t ByteSwap(uint16_t wSwW)
{
  uint8_t bTemp;
  uint16_t wRet;
  bTemp = (uint8_t)(wSwW & 0xff);
  wRet =  (wSwW >> 8) | ((uint16_t)bTemp << 8);
  return(wRet);
}

/**
  * @brief  Set USB SRAM size to 768 byte.
  * @param  None.
  * @retval None..
  */
void Set_USB768ByteMode(void)
{
    /*Enable 768 Byte, Enable RCC->MISC*/
    RCC->MISC |= 0x1 << 24;
    
    /*USB SRAM Base address*/
    PMAAddr = 0x40007800;
}

/**
  * @brief  Clear USB 768 byte mode, USB SRAM size is 512 byte.
  * @param  None.
  * @retval None..
  */
void Clear_USB768ByteMode(void)
{
    /*Clear 768 byte mode*/
    RCC->MISC &= ~(0x1 << 24);
    
    /*USB SRAM Base address*/
    PMAAddr = 0x40006000;
}
