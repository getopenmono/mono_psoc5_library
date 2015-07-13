/*******************************************************************************
* File Name: RP_INTR.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RP_INTR_H) /* Pins RP_INTR_H */
#define CY_PINS_RP_INTR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RP_INTR_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RP_INTR__PORT == 15 && ((RP_INTR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RP_INTR_Write(uint8 value) ;
void    RP_INTR_SetDriveMode(uint8 mode) ;
uint8   RP_INTR_ReadDataReg(void) ;
uint8   RP_INTR_Read(void) ;
uint8   RP_INTR_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RP_INTR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RP_INTR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RP_INTR_DM_RES_UP          PIN_DM_RES_UP
#define RP_INTR_DM_RES_DWN         PIN_DM_RES_DWN
#define RP_INTR_DM_OD_LO           PIN_DM_OD_LO
#define RP_INTR_DM_OD_HI           PIN_DM_OD_HI
#define RP_INTR_DM_STRONG          PIN_DM_STRONG
#define RP_INTR_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RP_INTR_MASK               RP_INTR__MASK
#define RP_INTR_SHIFT              RP_INTR__SHIFT
#define RP_INTR_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RP_INTR_PS                     (* (reg8 *) RP_INTR__PS)
/* Data Register */
#define RP_INTR_DR                     (* (reg8 *) RP_INTR__DR)
/* Port Number */
#define RP_INTR_PRT_NUM                (* (reg8 *) RP_INTR__PRT) 
/* Connect to Analog Globals */                                                  
#define RP_INTR_AG                     (* (reg8 *) RP_INTR__AG)                       
/* Analog MUX bux enable */
#define RP_INTR_AMUX                   (* (reg8 *) RP_INTR__AMUX) 
/* Bidirectional Enable */                                                        
#define RP_INTR_BIE                    (* (reg8 *) RP_INTR__BIE)
/* Bit-mask for Aliased Register Access */
#define RP_INTR_BIT_MASK               (* (reg8 *) RP_INTR__BIT_MASK)
/* Bypass Enable */
#define RP_INTR_BYP                    (* (reg8 *) RP_INTR__BYP)
/* Port wide control signals */                                                   
#define RP_INTR_CTL                    (* (reg8 *) RP_INTR__CTL)
/* Drive Modes */
#define RP_INTR_DM0                    (* (reg8 *) RP_INTR__DM0) 
#define RP_INTR_DM1                    (* (reg8 *) RP_INTR__DM1)
#define RP_INTR_DM2                    (* (reg8 *) RP_INTR__DM2) 
/* Input Buffer Disable Override */
#define RP_INTR_INP_DIS                (* (reg8 *) RP_INTR__INP_DIS)
/* LCD Common or Segment Drive */
#define RP_INTR_LCD_COM_SEG            (* (reg8 *) RP_INTR__LCD_COM_SEG)
/* Enable Segment LCD */
#define RP_INTR_LCD_EN                 (* (reg8 *) RP_INTR__LCD_EN)
/* Slew Rate Control */
#define RP_INTR_SLW                    (* (reg8 *) RP_INTR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RP_INTR_PRTDSI__CAPS_SEL       (* (reg8 *) RP_INTR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RP_INTR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RP_INTR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RP_INTR_PRTDSI__OE_SEL0        (* (reg8 *) RP_INTR__PRTDSI__OE_SEL0) 
#define RP_INTR_PRTDSI__OE_SEL1        (* (reg8 *) RP_INTR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RP_INTR_PRTDSI__OUT_SEL0       (* (reg8 *) RP_INTR__PRTDSI__OUT_SEL0) 
#define RP_INTR_PRTDSI__OUT_SEL1       (* (reg8 *) RP_INTR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RP_INTR_PRTDSI__SYNC_OUT       (* (reg8 *) RP_INTR__PRTDSI__SYNC_OUT) 


#if defined(RP_INTR__INTSTAT)  /* Interrupt Registers */

    #define RP_INTR_INTSTAT                (* (reg8 *) RP_INTR__INTSTAT)
    #define RP_INTR_SNAP                   (* (reg8 *) RP_INTR__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RP_INTR_H */


/* [] END OF FILE */
