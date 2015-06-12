/*******************************************************************************
* File Name: ACC_INT2.c  
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
#include "ACC_INT2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ACC_INT2__PORT == 15 && ((ACC_INT2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ACC_INT2_Write
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
void ACC_INT2_Write(uint8 value) 
{
    uint8 staticBits = (ACC_INT2_DR & (uint8)(~ACC_INT2_MASK));
    ACC_INT2_DR = staticBits | ((uint8)(value << ACC_INT2_SHIFT) & ACC_INT2_MASK);
}


/*******************************************************************************
* Function Name: ACC_INT2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ACC_INT2_DM_STRONG     Strong Drive 
*  ACC_INT2_DM_OD_HI      Open Drain, Drives High 
*  ACC_INT2_DM_OD_LO      Open Drain, Drives Low 
*  ACC_INT2_DM_RES_UP     Resistive Pull Up 
*  ACC_INT2_DM_RES_DWN    Resistive Pull Down 
*  ACC_INT2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ACC_INT2_DM_DIG_HIZ    High Impedance Digital 
*  ACC_INT2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ACC_INT2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ACC_INT2_0, mode);
}


/*******************************************************************************
* Function Name: ACC_INT2_Read
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
*  Macro ACC_INT2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ACC_INT2_Read(void) 
{
    return (ACC_INT2_PS & ACC_INT2_MASK) >> ACC_INT2_SHIFT;
}


/*******************************************************************************
* Function Name: ACC_INT2_ReadDataReg
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
uint8 ACC_INT2_ReadDataReg(void) 
{
    return (ACC_INT2_DR & ACC_INT2_MASK) >> ACC_INT2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ACC_INT2_INTSTAT) 

    /*******************************************************************************
    * Function Name: ACC_INT2_ClearInterrupt
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
    uint8 ACC_INT2_ClearInterrupt(void) 
    {
        return (ACC_INT2_INTSTAT & ACC_INT2_MASK) >> ACC_INT2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
