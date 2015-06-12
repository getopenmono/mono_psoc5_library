/*******************************************************************************
* File Name: nIRQ.c  
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
#include "nIRQ.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 nIRQ__PORT == 15 && ((nIRQ__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: nIRQ_Write
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
void nIRQ_Write(uint8 value) 
{
    uint8 staticBits = (nIRQ_DR & (uint8)(~nIRQ_MASK));
    nIRQ_DR = staticBits | ((uint8)(value << nIRQ_SHIFT) & nIRQ_MASK);
}


/*******************************************************************************
* Function Name: nIRQ_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  nIRQ_DM_STRONG     Strong Drive 
*  nIRQ_DM_OD_HI      Open Drain, Drives High 
*  nIRQ_DM_OD_LO      Open Drain, Drives Low 
*  nIRQ_DM_RES_UP     Resistive Pull Up 
*  nIRQ_DM_RES_DWN    Resistive Pull Down 
*  nIRQ_DM_RES_UPDWN  Resistive Pull Up/Down 
*  nIRQ_DM_DIG_HIZ    High Impedance Digital 
*  nIRQ_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void nIRQ_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(nIRQ_0, mode);
}


/*******************************************************************************
* Function Name: nIRQ_Read
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
*  Macro nIRQ_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 nIRQ_Read(void) 
{
    return (nIRQ_PS & nIRQ_MASK) >> nIRQ_SHIFT;
}


/*******************************************************************************
* Function Name: nIRQ_ReadDataReg
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
uint8 nIRQ_ReadDataReg(void) 
{
    return (nIRQ_DR & nIRQ_MASK) >> nIRQ_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(nIRQ_INTSTAT) 

    /*******************************************************************************
    * Function Name: nIRQ_ClearInterrupt
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
    uint8 nIRQ_ClearInterrupt(void) 
    {
        return (nIRQ_INTSTAT & nIRQ_MASK) >> nIRQ_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
