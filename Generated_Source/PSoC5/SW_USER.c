/*******************************************************************************
* File Name: SW_USER.c  
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
#include "SW_USER.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SW_USER__PORT == 15 && ((SW_USER__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SW_USER_Write
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
void SW_USER_Write(uint8 value) 
{
    uint8 staticBits = (SW_USER_DR & (uint8)(~SW_USER_MASK));
    SW_USER_DR = staticBits | ((uint8)(value << SW_USER_SHIFT) & SW_USER_MASK);
}


/*******************************************************************************
* Function Name: SW_USER_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SW_USER_DM_STRONG     Strong Drive 
*  SW_USER_DM_OD_HI      Open Drain, Drives High 
*  SW_USER_DM_OD_LO      Open Drain, Drives Low 
*  SW_USER_DM_RES_UP     Resistive Pull Up 
*  SW_USER_DM_RES_DWN    Resistive Pull Down 
*  SW_USER_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SW_USER_DM_DIG_HIZ    High Impedance Digital 
*  SW_USER_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SW_USER_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SW_USER_0, mode);
}


/*******************************************************************************
* Function Name: SW_USER_Read
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
*  Macro SW_USER_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SW_USER_Read(void) 
{
    return (SW_USER_PS & SW_USER_MASK) >> SW_USER_SHIFT;
}


/*******************************************************************************
* Function Name: SW_USER_ReadDataReg
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
uint8 SW_USER_ReadDataReg(void) 
{
    return (SW_USER_DR & SW_USER_MASK) >> SW_USER_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SW_USER_INTSTAT) 

    /*******************************************************************************
    * Function Name: SW_USER_ClearInterrupt
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
    uint8 SW_USER_ClearInterrupt(void) 
    {
        return (SW_USER_INTSTAT & SW_USER_MASK) >> SW_USER_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
