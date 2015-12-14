/*******************************************************************************
* File Name: R_SSEL.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "R_SSEL.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 R_SSEL__PORT == 15 && ((R_SSEL__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: R_SSEL_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void R_SSEL_Write(uint8 value) 
{
    uint8 staticBits = (R_SSEL_DR & (uint8)(~R_SSEL_MASK));
    R_SSEL_DR = staticBits | ((uint8)(value << R_SSEL_SHIFT) & R_SSEL_MASK);
}


/*******************************************************************************
* Function Name: R_SSEL_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  R_SSEL_DM_STRONG     Strong Drive 
*  R_SSEL_DM_OD_HI      Open Drain, Drives High 
*  R_SSEL_DM_OD_LO      Open Drain, Drives Low 
*  R_SSEL_DM_RES_UP     Resistive Pull Up 
*  R_SSEL_DM_RES_DWN    Resistive Pull Down 
*  R_SSEL_DM_RES_UPDWN  Resistive Pull Up/Down 
*  R_SSEL_DM_DIG_HIZ    High Impedance Digital 
*  R_SSEL_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void R_SSEL_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(R_SSEL_0, mode);
}


/*******************************************************************************
* Function Name: R_SSEL_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro R_SSEL_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 R_SSEL_Read(void) 
{
    return (R_SSEL_PS & R_SSEL_MASK) >> R_SSEL_SHIFT;
}


/*******************************************************************************
* Function Name: R_SSEL_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 R_SSEL_ReadDataReg(void) 
{
    return (R_SSEL_DR & R_SSEL_MASK) >> R_SSEL_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(R_SSEL_INTSTAT) 

    /*******************************************************************************
    * Function Name: R_SSEL_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 R_SSEL_ClearInterrupt(void) 
    {
        return (R_SSEL_INTSTAT & R_SSEL_MASK) >> R_SSEL_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
