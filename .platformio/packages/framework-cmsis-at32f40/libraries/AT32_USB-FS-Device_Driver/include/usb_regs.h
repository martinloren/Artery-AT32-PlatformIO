/**
  ******************************************************************************
  * File   : usb_reg.h 
  * Version: V1.2.2
  * Date   : 2020-07-01
  * Brief  : Interface prototype functions to USB cell registers
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_REGS_H
#define __USB_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum _EP_DBUF_DIR
{
  /* double buffered endpoint direction */
  EP_DBUF_ERR,
  EP_DBUF_OUT,
  EP_DBUF_IN
}EP_DBUF_DIR;

/* endpoint buffer number */
enum EP_BUF_NUM
{
  EP_NOBUF,
  EP_BUF0,
  EP_BUF1
};

/* Exported constants --------------------------------------------------------*/
#define RegBase  (0x40005C00L)  /* USB_IP Peripheral Registers base address */
extern int PMAAddr;                /* USB_IP Packet Memory Area base address, default is 0x40006000*/

/******************************************************************************/
/*                         General registers                                  */
/******************************************************************************/

/* Control register */
#define CTRL    ((__IO unsigned *)(RegBase + 0x40))
/* Interrupt status register */
#define INTSTS    ((__IO unsigned *)(RegBase + 0x44))
/* Frame number register */
#define FRNUM     ((__IO unsigned *)(RegBase + 0x48))
/* Device address register */
#define DEVADR   ((__IO unsigned *)(RegBase + 0x4C))
/* Buffer Table address register */
#define BUFTBL  ((__IO unsigned *)(RegBase + 0x50))
/******************************************************************************/
/*                         Endpoint registers                                 */
/******************************************************************************/
#define EP0REG  ((__IO unsigned *)(RegBase)) /* endpoint 0 register address */

/* Endpoint Addresses (w/direction) */
#define EP0_OUT     ((uint8_t)0x00)  
#define EP0_IN      ((uint8_t)0x80) 
#define EP1_OUT     ((uint8_t)0x01)  
#define EP1_IN      ((uint8_t)0x81)  
#define EP2_OUT     ((uint8_t)0x02)  
#define EP2_IN      ((uint8_t)0x82)  
#define EP3_OUT     ((uint8_t)0x03)  
#define EP3_IN      ((uint8_t)0x83) 
#define EP4_OUT     ((uint8_t)0x04)  
#define EP4_IN      ((uint8_t)0x84)
#define EP5_OUT     ((uint8_t)0x05)  
#define EP5_IN      ((uint8_t)0x85)
#define EP6_OUT     ((uint8_t)0x06)  
#define EP6_IN      ((uint8_t)0x86)
#define EP7_OUT     ((uint8_t)0x07)  
#define EP7_IN      ((uint8_t)0x87)

/* endpoints enumeration */
#define ENDP0       ((uint8_t)0)
#define ENDP1       ((uint8_t)1)
#define ENDP2       ((uint8_t)2)
#define ENDP3       ((uint8_t)3)
#define ENDP4       ((uint8_t)4)
#define ENDP5       ((uint8_t)5)
#define ENDP6       ((uint8_t)6)
#define ENDP7       ((uint8_t)7)

/******************************************************************************/
/*                       INTSTS interrupt events                                */
/******************************************************************************/
#define INTSTS_CTFR    (0x8000) /* Correct TRansfer (clear-only bit) */
#define INTSTS_DOVR   (0x4000) /* DMA OVeR/underrun (clear-only bit) */
#define INTSTS_ERRF    (0x2000) /* ERRor (clear-only bit) */
#define INTSTS_WKUPF   (0x1000) /* WaKe UP (clear-only bit) */
#define INTSTS_SUSPF   (0x0800) /* SUSPend (clear-only bit) */
#define INTSTS_RSTF  (0x0400) /* RESET (clear-only bit) */
#define INTSTS_SOFF    (0x0200) /* Start Of Frame (clear-only bit) */
#define INTSTS_ESOF   (0x0100) /* Expected Start Of Frame (clear-only bit) */


#define INTSTS_DIR    (0x0010)  /* DIRection of transaction (read-only bit)  */
#define INTSTS_EP_ID  (0x000F)  /* EndPoint IDentifier (read-only bit)  */

#define CLR_CTFR    (~INTSTS_CTFR)   /* clear Correct TRansfer bit */
#define CLR_DOVR   (~INTSTS_DOVR)  /* clear DMA OVeR/underrun bit*/
#define CLR_ERRF    (~INTSTS_ERRF)   /* clear ERRor bit */
#define CLR_WKUPF   (~INTSTS_WKUPF)  /* clear WaKe UP bit     */
#define CLR_SUSPF   (~INTSTS_SUSPF)  /* clear SUSPend bit     */
#define CLR_RSTF  (~INTSTS_RSTF) /* clear RESET bit      */
#define CLR_SOFF    (~INTSTS_SOFF)   /* clear Start Of Frame bit   */
#define CLR_ESOF   (~INTSTS_ESOF)  /* clear Expected Start Of Frame bit */

/******************************************************************************/
/*             CTRL control register bits definitions                         */
/******************************************************************************/
#define CTRL_CTFR_IEN   (0x8000) /* Correct TRansfer Mask */
#define CTRL_DOVR_IEN  (0x4000) /* DMA OVeR/underrun Mask */
#define CTRL_ERR_IEN   (0x2000) /* ERRor Mask */
#define CTRL_WKUP_IEN  (0x1000) /* WaKe UP Mask */
#define CTRL_SUSP_IEN  (0x0800) /* SUSPend Mask */
#define CTRL_RST_IEN (0x0400) /* RESET Mask   */
#define CTRL_SOF_IEN   (0x0200) /* Start Of Frame Mask */
#define CTRL_ESOF_IEN  (0x0100) /* Expected Start Of Frame Mask */


#define CTRL_RESUME (0x0010) /* RESUME request */
#define CTRL_FSUSP  (0x0008) /* Force SUSPend */
#define CTRL_LPWR (0x0004) /* Low-power MODE */
#define CTRL_PDWN   (0x0002) /* Power DoWN */
#define CTRL_FRST   (0x0001) /* Force USB RESet */

/******************************************************************************/
/*                FRNUM Frame Number Register bit definitions                   */
/******************************************************************************/
#define FRNUM_RXDP (0x8000) /* status of D+ data line */
#define FRNUM_RXDM (0x4000) /* status of D- data line */
#define FRNUM_LCK  (0x2000) /* LoCKed */
#define FRNUM_LSOF (0x1800) /* Lost SOF */
#define FRNUM_FN  (0x07FF) /* Frame Number */
/******************************************************************************/
/*               DEVADR Device ADDRess bit definitions                         */
/******************************************************************************/
#define DEVADR_EN (0x80)
#define DEVADR_ADR (0x7F)
/******************************************************************************/
/*                            Endpoint register                               */
/******************************************************************************/
/* bit positions */
#define EP_CTFR_RX      (0x8000) /* EndPoint Correct TRansfer RX */
#define EP_DTOG_RX     (0x4000) /* EndPoint Data TOGGLE RX */
#define EP_STS_RX      (0x3000) /* EndPoint RX STATus bit field */
#define EP_SETUP       (0x0800) /* EndPoint SETUP */
#define EP_T_FIELD     (0x0600) /* EndPoint TYPE */
#define EP_SUBTYPE        (0x0100) /* EndPoint KIND */
#define EP_CTFR_TX      (0x0080) /* EndPoint Correct TRansfer TX */
#define EP_DTOG_TX     (0x0040) /* EndPoint Data TOGGLE TX */
#define EP_STS_TX      (0x0030) /* EndPoint TX STATus bit field */
#define EPADR_FIELD   (0x000F) /* EndPoint ADDRess FIELD */

/* EndPoint REGister MASK (no toggle fields) */
#define EPREG_MASK     (EP_CTFR_RX|EP_SETUP|EP_T_FIELD|EP_SUBTYPE|EP_CTFR_TX|EPADR_FIELD)

/* EP_TYPE[1:0] EndPoint TYPE */
#define EP_TYPE_MASK   (0x0600) /* EndPoint TYPE Mask */
#define EP_BULK        (0x0000) /* EndPoint BULK */
#define EP_CONTROL     (0x0200) /* EndPoint CONTROL */
#define EP_ISOCHRONOUS (0x0400) /* EndPoint ISOCHRONOUS */
#define EP_INTERRUPT   (0x0600) /* EndPoint INTERRUPT */
#define EP_T_MASK      (~EP_T_FIELD & EPREG_MASK)


/* EP_SUBTYPE EndPoint KIND */
#define EPKIND_MASK    (~EP_SUBTYPE & EPREG_MASK)

/* STAT_TX[1:0] STATus for TX transfer */
#define EP_TX_DIS      (0x0000) /* EndPoint TX DISabled */
#define EP_TX_STALL    (0x0010) /* EndPoint TX STALLed */
#define EP_TX_NAK      (0x0020) /* EndPoint TX NAKed */
#define EP_TX_VALID    (0x0030) /* EndPoint TX VALID */
#define EPTX_DTOG1     (0x0010) /* EndPoint TX Data TOGgle bit1 */
#define EPTX_DTOG2     (0x0020) /* EndPoint TX Data TOGgle bit2 */
#define EPTX_DTOGMASK  (EP_STS_TX|EPREG_MASK)

/* STAT_RX[1:0] STATus for RX transfer */
#define EP_RX_DIS      (0x0000) /* EndPoint RX DISabled */
#define EP_RX_STALL    (0x1000) /* EndPoint RX STALLed */
#define EP_RX_NAK      (0x2000) /* EndPoint RX NAKed */
#define EP_RX_VALID    (0x3000) /* EndPoint RX VALID */
#define EPRX_DTOG1     (0x1000) /* EndPoint RX Data TOGgle bit1 */
#define EPRX_DTOG2     (0x2000) /* EndPoint RX Data TOGgle bit1 */
#define EPRX_DTOGMASK  (EP_STS_RX|EPREG_MASK)
/* Exported macro ------------------------------------------------------------*/
/* SetCTRL */
#define _SetCTRL(wRegValue)  (*CTRL   = (uint16_t)wRegValue)

/* SetINTSTS */
#define _SetINTSTS(wRegValue)  (*INTSTS   = (uint16_t)wRegValue)

/* SetDEVADR */
#define _SetDEVADR(wRegValue) (*DEVADR  = (uint16_t)wRegValue)

/* SetBUFTBL */
#define _SetBUFTBL(wRegValue)(*BUFTBL = (uint16_t)(wRegValue & 0xFFF8))

/* GetCTRL */
#define _GetCTRL()   ((uint16_t) *CTRL)

/* GetINTSTS */
#define _GetINTSTS()   ((uint16_t) *INTSTS)

/* GetFRNUM */
#define _GetFRNUM()    ((uint16_t) *FRNUM)

/* GetDEVADR */
#define _GetDEVADR()  ((uint16_t) *DEVADR)

/* GetBUFTBL */
#define _GetBUFTBL() ((uint16_t) *BUFTBL)

/* SetENDPOINT */
#define _SetENDPOINT(bEpNum,wRegValue)  (*(EP0REG + bEpNum)= \
    (uint16_t)wRegValue)

/* GetENDPOINT */
#define _GetENDPOINT(bEpNum)        ((uint16_t)(*(EP0REG + bEpNum)))

/*******************************************************************************
* Macro Name     : SetEPType
* Description    : sets the type in the endpoint register(bits EP_TYPE[1:0])
* Input          : bEpNum: Endpoint Number. 
*                  wType											 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPType(bEpNum,wType) (_SetENDPOINT(bEpNum,\
                                  ((_GetENDPOINT(bEpNum) & EP_T_MASK) | wType )))

/*******************************************************************************
* Macro Name     : GetEPType
* Description    : gets the type in the endpoint register(bits EP_TYPE[1:0]) 
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : Endpoint Type
*******************************************************************************/
#define _GetEPType(bEpNum) (_GetENDPOINT(bEpNum) & EP_T_FIELD)

/*******************************************************************************
* Macro Name     : SetEPTxStatus
* Description    : sets the status for tx transfer (bits STAT_TX[1:0]).
* Input          : bEpNum: Endpoint Number. 
*                  wState: new state
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPTxStatus(bEpNum,wState) {\
    register uint16_t _wRegVal;       \
    _wRegVal = _GetENDPOINT(bEpNum) & EPTX_DTOGMASK;\
    /* toggle first bit ? */     \
    if((EPTX_DTOG1 & wState)!= 0)      \
      _wRegVal ^= EPTX_DTOG1;        \
    /* toggle second bit ?  */         \
    if((EPTX_DTOG2 & wState)!= 0)      \
      _wRegVal ^= EPTX_DTOG2;        \
    _SetENDPOINT(bEpNum, (_wRegVal | EP_CTFR_RX|EP_CTFR_TX));    \
  } /* _SetEPTxStatus */

/*******************************************************************************
* Macro Name     : SetEPRxStatus
* Description    : sets the status for rx transfer (bits STAT_TX[1:0])
* Input          : bEpNum: Endpoint Number. 
*                  wState: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPRxStatus(bEpNum,wState) {\
    register uint16_t _wRegVal;   \
    \
    _wRegVal = _GetENDPOINT(bEpNum) & EPRX_DTOGMASK;\
    /* toggle first bit ? */  \
    if((EPRX_DTOG1 & wState)!= 0) \
      _wRegVal ^= EPRX_DTOG1;  \
    /* toggle second bit ? */  \
    if((EPRX_DTOG2 & wState)!= 0) \
      _wRegVal ^= EPRX_DTOG2;  \
    _SetENDPOINT(bEpNum, (_wRegVal | EP_CTFR_RX|EP_CTFR_TX)); \
  } /* _SetEPRxStatus */

/*******************************************************************************
* Macro Name     : SetEPRxTxStatus
* Description    : sets the status for rx & tx (bits STAT_TX[1:0] & STAT_RX[1:0])
* Input          : bEpNum: Endpoint Number. 
*                  wStaterx: new state.
*                  wStatetx: new state.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPRxTxStatus(bEpNum,wStaterx,wStatetx) {\
    register uint32_t _wRegVal;   \
    \
    _wRegVal = _GetENDPOINT(bEpNum) & (EPRX_DTOGMASK |EP_STS_TX) ;\
    /* toggle first bit ? */  \
    if((EPRX_DTOG1 & wStaterx)!= 0) \
      _wRegVal ^= EPRX_DTOG1;  \
    /* toggle second bit ? */  \
    if((EPRX_DTOG2 & wStaterx)!= 0) \
      _wRegVal ^= EPRX_DTOG2;  \
    /* toggle first bit ? */     \
    if((EPTX_DTOG1 & wStatetx)!= 0)      \
      _wRegVal ^= EPTX_DTOG1;        \
    /* toggle second bit ?  */         \
    if((EPTX_DTOG2 & wStatetx)!= 0)      \
      _wRegVal ^= EPTX_DTOG2;        \
    _SetENDPOINT(bEpNum, _wRegVal | EP_CTFR_RX|EP_CTFR_TX);    \
  } /* _SetEPRxTxStatus */
/*******************************************************************************
* Macro Name     : GetEPTxStatus / GetEPRxStatus 
* Description    : gets the status for tx/rx transfer (bits STAT_TX[1:0]
*                  /STAT_RX[1:0])
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : status .
*******************************************************************************/
#define _GetEPTxStatus(bEpNum) ((uint16_t)_GetENDPOINT(bEpNum) & EP_STS_TX)

#define _GetEPRxStatus(bEpNum) ((uint16_t)_GetENDPOINT(bEpNum) & EP_STS_RX)

/*******************************************************************************
* Macro Name     : SetEPTxValid / SetEPRxValid 
* Description    : sets directly the VALID tx/rx-status into the enpoint register
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPTxValid(bEpNum)     (_SetEPTxStatus(bEpNum, EP_TX_VALID))

#define _SetEPRxValid(bEpNum)     (_SetEPRxStatus(bEpNum, EP_RX_VALID))

/*******************************************************************************
* Macro Name     : GetTxStallStatus / GetRxStallStatus.
* Description    : checks stall condition in an endpoint.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : TRUE = endpoint in stall condition.
*******************************************************************************/
#define _GetTxStallStatus(bEpNum) (_GetEPTxStatus(bEpNum) \
                                   == EP_TX_STALL)
#define _GetRxStallStatus(bEpNum) (_GetEPRxStatus(bEpNum) \
                                   == EP_RX_STALL)

/*******************************************************************************
* Macro Name     : SetEP_SUBTYPE / ClearEP_SUBTYPE.
* Description    : set & clear EP_SUBTYPE bit.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEP_SUBTYPE(bEpNum)    (_SetENDPOINT(bEpNum, \
                                (EP_CTFR_RX|EP_CTFR_TX|((_GetENDPOINT(bEpNum) | EP_SUBTYPE) & EPREG_MASK))))
#define _ClearEP_SUBTYPE(bEpNum)  (_SetENDPOINT(bEpNum, \
                                (EP_CTFR_RX|EP_CTFR_TX|(_GetENDPOINT(bEpNum) & EPKIND_MASK))))

/*******************************************************************************
* Macro Name     : Set_Status_Out / Clear_Status_Out.
* Description    : Sets/clears directly STATUS_OUT bit in the endpoint register.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _Set_Status_Out(bEpNum)    _SetEP_SUBTYPE(bEpNum)
#define _Clear_Status_Out(bEpNum)  _ClearEP_SUBTYPE(bEpNum)

/*******************************************************************************
* Macro Name     : SetEPDoubleBuff / ClearEPDoubleBuff.
* Description    : Sets/clears directly EP_SUBTYPE bit in the endpoint register.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPDoubleBuff(bEpNum)   _SetEP_SUBTYPE(bEpNum)
#define _ClearEPDoubleBuff(bEpNum) _ClearEP_SUBTYPE(bEpNum)

/*******************************************************************************
* Macro Name     : ClearEP_CTFR_RX / ClearEP_CTFR_TX.
* Description    : Clears bit CTR_RX / CTR_TX in the endpoint register.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _ClearEP_CTFR_RX(bEpNum)   (_SetENDPOINT(bEpNum,\
                                   _GetENDPOINT(bEpNum) & 0x7FFF & EPREG_MASK))
#define _ClearEP_CTFR_TX(bEpNum)   (_SetENDPOINT(bEpNum,\
                                   _GetENDPOINT(bEpNum) & 0xFF7F & EPREG_MASK))

/*******************************************************************************
* Macro Name     : ToggleDTOG_RX / ToggleDTOG_TX .
* Description    : Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _ToggleDTOG_RX(bEpNum)    (_SetENDPOINT(bEpNum, \
                                   EP_CTFR_RX|EP_CTFR_TX|EP_DTOG_RX | (_GetENDPOINT(bEpNum) & EPREG_MASK)))
#define _ToggleDTOG_TX(bEpNum)    (_SetENDPOINT(bEpNum, \
                                   EP_CTFR_RX|EP_CTFR_TX|EP_DTOG_TX | (_GetENDPOINT(bEpNum) & EPREG_MASK)))

/*******************************************************************************
* Macro Name     : ClearDTOG_RX / ClearDTOG_TX.
* Description    : Clears DTOG_RX / DTOG_TX bit in the endpoint register.
* Input          : bEpNum: Endpoint Number. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _ClearDTOG_RX(bEpNum)  if((_GetENDPOINT(bEpNum) & EP_DTOG_RX) != 0)\
    _ToggleDTOG_RX(bEpNum)
#define _ClearDTOG_TX(bEpNum)  if((_GetENDPOINT(bEpNum) & EP_DTOG_TX) != 0)\
    _ToggleDTOG_TX(bEpNum)
/*******************************************************************************
* Macro Name     : SetEPAddress.
* Description    : Sets address in an endpoint register.
* Input          : bEpNum: Endpoint Number.
*                  bAddr: Address. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPAddress(bEpNum,bAddr) _SetENDPOINT(bEpNum,\
    EP_CTFR_RX|EP_CTFR_TX|(_GetENDPOINT(bEpNum) & EPREG_MASK) | bAddr)

/*******************************************************************************
* Macro Name     : GetEPAddress.
* Description    : Gets address in an endpoint register.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _GetEPAddress(bEpNum) ((uint8_t)(_GetENDPOINT(bEpNum) & EPADR_FIELD))

#define _pEPTxAddr(bEpNum) ((uint32_t *)((_GetBUFTBL()+bEpNum*8  )*2 + PMAAddr))
#define _pEPTxCount(bEpNum) ((uint32_t *)((_GetBUFTBL()+bEpNum*8+2)*2 + PMAAddr))
#define _pEPRxAddr(bEpNum) ((uint32_t *)((_GetBUFTBL()+bEpNum*8+4)*2 + PMAAddr))
#define _pEPRxCount(bEpNum) ((uint32_t *)((_GetBUFTBL()+bEpNum*8+6)*2 + PMAAddr))

/*******************************************************************************
* Macro Name     : SetEPTxAddr / SetEPRxAddr.
* Description    : sets address of the tx/rx buffer.
* Input          : bEpNum: Endpoint Number.
*                  wAddr: address to be set (must be word aligned).
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPTxAddr(bEpNum,wAddr) (*_pEPTxAddr(bEpNum) = ((wAddr >> 1) << 1))
#define _SetEPRxAddr(bEpNum,wAddr) (*_pEPRxAddr(bEpNum) = ((wAddr >> 1) << 1))

/*******************************************************************************
* Macro Name     : GetEPTxAddr / GetEPRxAddr.
* Description    : Gets address of the tx/rx buffer.
* Input          : bEpNum: Endpoint Number.
* Output         : None.
* Return         : address of the buffer.
*******************************************************************************/
#define _GetEPTxAddr(bEpNum) ((uint16_t)*_pEPTxAddr(bEpNum))
#define _GetEPRxAddr(bEpNum) ((uint16_t)*_pEPRxAddr(bEpNum))

/*******************************************************************************
* Macro Name     : SetEPCountRxReg.
* Description    : Sets counter of rx buffer with no. of blocks.
* Input          : pdwReg: pointer to counter.
*                  wCount: Counter.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _BlocksOf32(dwReg,wCount,wNBlocks) {\
    wNBlocks = wCount >> 5;\
    if((wCount & 0x1f) == 0)\
      wNBlocks--;\
    *pdwReg = (uint32_t)((wNBlocks << 10) | 0x8000);\
  }/* _BlocksOf32 */

#define _BlocksOf2(dwReg,wCount,wNBlocks) {\
    wNBlocks = wCount >> 1;\
    if((wCount & 0x1) != 0)\
      wNBlocks++;\
    *pdwReg = (uint32_t)(wNBlocks << 10);\
  }/* _BlocksOf2 */

#define _SetEPCountRxReg(dwReg,wCount)  {\
    uint16_t wNBlocks;\
    if(wCount > 62){_BlocksOf32(dwReg,wCount,wNBlocks);}\
    else {_BlocksOf2(dwReg,wCount,wNBlocks);}\
  }/* _SetEPCountRxReg */



#define _SetEPRxDblBuf0Count(bEpNum,wCount) {\
    uint32_t *pdwReg = _pEPTxCount(bEpNum); \
    _SetEPCountRxReg(pdwReg, wCount);\
  }
/*******************************************************************************
* Macro Name     : SetEPTxCount / SetEPRxCount.
* Description    : sets counter for the tx/rx buffer.
* Input          : bEpNum: endpoint number.
*                  wCount: Counter value.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPTxCount(bEpNum,wCount) (*_pEPTxCount(bEpNum) = wCount)
#define _SetEPRxCount(bEpNum,wCount) {\
    uint32_t *pdwReg = _pEPRxCount(bEpNum); \
    _SetEPCountRxReg(pdwReg, wCount);\
  }
/*******************************************************************************
* Macro Name     : GetEPTxCount / GetEPRxCount.
* Description    : gets counter of the tx buffer.
* Input          : bEpNum: endpoint number.
* Output         : None.
* Return         : Counter value.
*******************************************************************************/
#define _GetEPTxCount(bEpNum)((uint16_t)(*_pEPTxCount(bEpNum)) & 0x3ff)
#define _GetEPRxCount(bEpNum)((uint16_t)(*_pEPRxCount(bEpNum)) & 0x3ff)

/*******************************************************************************
* Macro Name     : SetEPDblBuf0Addr / SetEPDblBuf1Addr.
* Description    : Sets buffer 0/1 address in a double buffer endpoint.
* Input          : bEpNum: endpoint number.
*                : wBuf0Addr: buffer 0 address.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPDblBuf0Addr(bEpNum,wBuf0Addr) {_SetEPTxAddr(bEpNum, wBuf0Addr);}
#define _SetEPDblBuf1Addr(bEpNum,wBuf1Addr) {_SetEPRxAddr(bEpNum, wBuf1Addr);}

/*******************************************************************************
* Macro Name     : SetEPDblBuffAddr.
* Description    : Sets addresses in a double buffer endpoint.
* Input          : bEpNum: endpoint number.
*                : wBuf0Addr: buffer 0 address.
*                : wBuf1Addr = buffer 1 address.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPDblBuffAddr(bEpNum,wBuf0Addr,wBuf1Addr) { \
    _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);\
    _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);\
  } /* _SetEPDblBuffAddr */

/*******************************************************************************
* Macro Name     : GetEPDblBuf0Addr / GetEPDblBuf1Addr.
* Description    : Gets buffer 0/1 address of a double buffer endpoint.
* Input          : bEpNum: endpoint number.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _GetEPDblBuf0Addr(bEpNum) (_GetEPTxAddr(bEpNum))
#define _GetEPDblBuf1Addr(bEpNum) (_GetEPRxAddr(bEpNum))

/*******************************************************************************
* Macro Name     : SetEPDblBuffCount / SetEPDblBuf0Count / SetEPDblBuf1Count.
* Description    : Gets buffer 0/1 address of a double buffer endpoint.
* Input          : bEpNum: endpoint number.
*                : bDir: endpoint dir  EP_DBUF_OUT = OUT 
*                                      EP_DBUF_IN  = IN 
*                : wCount: Counter value    
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _SetEPDblBuf0Count(bEpNum, bDir, wCount)  { \
    if(bDir == EP_DBUF_OUT)\
      /* OUT endpoint */ \
    {_SetEPRxDblBuf0Count(bEpNum,wCount);} \
    else if(bDir == EP_DBUF_IN)\
      /* IN endpoint */ \
      *_pEPTxCount(bEpNum) = (uint32_t)wCount;  \
  } /* SetEPDblBuf0Count*/

#define _SetEPDblBuf1Count(bEpNum, bDir, wCount)  { \
    if(bDir == EP_DBUF_OUT)\
      /* OUT endpoint */ \
    {_SetEPRxCount(bEpNum,wCount);}\
    else if(bDir == EP_DBUF_IN)\
      /* IN endpoint */\
      *_pEPRxCount(bEpNum) = (uint32_t)wCount; \
  } /* SetEPDblBuf1Count */

#define _SetEPDblBuffCount(bEpNum, bDir, wCount) {\
    _SetEPDblBuf0Count(bEpNum, bDir, wCount); \
    _SetEPDblBuf1Count(bEpNum, bDir, wCount); \
  } /* _SetEPDblBuffCount  */

/*******************************************************************************
* Macro Name     : GetEPDblBuf0Count / GetEPDblBuf1Count.
* Description    : Gets buffer 0/1 rx/tx counter for double buffering.
* Input          : bEpNum: endpoint number.
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _GetEPDblBuf0Count(bEpNum) (_GetEPTxCount(bEpNum))
#define _GetEPDblBuf1Count(bEpNum) (_GetEPRxCount(bEpNum))


/* External variables --------------------------------------------------------*/
extern __IO uint16_t wIstr;  /* INTSTS register last read value */

/* Exported functions ------------------------------------------------------- */
void SetCTRL(uint16_t /*wRegValue*/);
void SetINTSTS(uint16_t /*wRegValue*/);
void SetDEVADR(uint16_t /*wRegValue*/);
void SetBUFTBL(uint16_t /*wRegValue*/);
void SetBUFTBL(uint16_t /*wRegValue*/);
uint16_t GetCTRL(void);
uint16_t GetINTSTS(void);
uint16_t GetFRNUM(void);
uint16_t GetDEVADR(void);
uint16_t GetBUFTBL(void);
void SetENDPOINT(uint8_t /*bEpNum*/, uint16_t /*wRegValue*/);
uint16_t GetENDPOINT(uint8_t /*bEpNum*/);
void SetEPType(uint8_t /*bEpNum*/, uint16_t /*wType*/);
uint16_t GetEPType(uint8_t /*bEpNum*/);
void SetEPTxStatus(uint8_t /*bEpNum*/, uint16_t /*wState*/);
void SetEPRxStatus(uint8_t /*bEpNum*/, uint16_t /*wState*/);
void SetDouBleBuffEPStall(uint8_t /*bEpNum*/, uint8_t bDir);
uint16_t GetEPTxStatus(uint8_t /*bEpNum*/);
uint16_t GetEPRxStatus(uint8_t /*bEpNum*/);
void SetEPTxValid(uint8_t /*bEpNum*/);
void SetEPRxValid(uint8_t /*bEpNum*/);
uint16_t GetTxStallStatus(uint8_t /*bEpNum*/);
uint16_t GetRxStallStatus(uint8_t /*bEpNum*/);
void SetEP_SUBTYPE(uint8_t /*bEpNum*/);
void ClearEP_SUBTYPE(uint8_t /*bEpNum*/);
void Set_Status_Out(uint8_t /*bEpNum*/);
void Clear_Status_Out(uint8_t /*bEpNum*/);
void SetEPDoubleBuff(uint8_t /*bEpNum*/);
void ClearEPDoubleBuff(uint8_t /*bEpNum*/);
void ClearEP_CTFR_RX(uint8_t /*bEpNum*/);
void ClearEP_CTFR_TX(uint8_t /*bEpNum*/);
void ToggleDTOG_RX(uint8_t /*bEpNum*/);
void ToggleDTOG_TX(uint8_t /*bEpNum*/);
void ClearDTOG_RX(uint8_t /*bEpNum*/);
void ClearDTOG_TX(uint8_t /*bEpNum*/);
void SetEPAddress(uint8_t /*bEpNum*/, uint8_t /*bAddr*/);
uint8_t GetEPAddress(uint8_t /*bEpNum*/);
void SetEPTxAddr(uint8_t /*bEpNum*/, uint16_t /*wAddr*/);
void SetEPRxAddr(uint8_t /*bEpNum*/, uint16_t /*wAddr*/);
uint16_t GetEPTxAddr(uint8_t /*bEpNum*/);
uint16_t GetEPRxAddr(uint8_t /*bEpNum*/);
void SetEPCountRxReg(uint32_t * /*pdwReg*/, uint16_t /*wCount*/);
void SetEPTxCount(uint8_t /*bEpNum*/, uint16_t /*wCount*/);
void SetEPRxCount(uint8_t /*bEpNum*/, uint16_t /*wCount*/);
uint16_t GetEPTxCount(uint8_t /*bEpNum*/);
uint16_t GetEPRxCount(uint8_t /*bEpNum*/);
void SetEPDblBuf0Addr(uint8_t /*bEpNum*/, uint16_t /*wBuf0Addr*/);
void SetEPDblBuf1Addr(uint8_t /*bEpNum*/, uint16_t /*wBuf1Addr*/);
void SetEPDblBuffAddr(uint8_t /*bEpNum*/, uint16_t /*wBuf0Addr*/, uint16_t /*wBuf1Addr*/);
uint16_t GetEPDblBuf0Addr(uint8_t /*bEpNum*/);
uint16_t GetEPDblBuf1Addr(uint8_t /*bEpNum*/);
void SetEPDblBuffCount(uint8_t /*bEpNum*/, uint8_t /*bDir*/, uint16_t /*wCount*/);
void SetEPDblBuf0Count(uint8_t /*bEpNum*/, uint8_t /*bDir*/, uint16_t /*wCount*/);
void SetEPDblBuf1Count(uint8_t /*bEpNum*/, uint8_t /*bDir*/, uint16_t /*wCount*/);
uint16_t GetEPDblBuf0Count(uint8_t /*bEpNum*/);
uint16_t GetEPDblBuf1Count(uint8_t /*bEpNum*/);
EP_DBUF_DIR GetEPDblBufDir(uint8_t /*bEpNum*/);
void FreeUserBuffer(uint8_t bEpNum/*bEpNum*/, uint8_t bDir);
uint16_t ToWord(uint8_t, uint8_t);
uint16_t ByteSwap(uint16_t);
void Set_USB768ByteMode(void);
void Clear_USB768ByteMode(void);

#ifdef __cplusplus
}
#endif

#endif /* __USB_REGS_H */


