/*******************************************************************************
* File Name: TFT_PM.c
* Version 1.70
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TFT.h" 

#if (CY_UDB_V0)
    static TFT_BACKUP_STRUCT TFT_backup = 
    {
        TFT_READ_LOW_PULSE,
        TFT_READ_HIGH_PULSE 
    };
#endif /* (CY_UDB_V0) */


/*******************************************************************************
* Function Name: TFT_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the user configuration of GraphicLCDIntf.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TFT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_SaveConfig(void) 
{   
    /* Saves D0/D1 Regs are non-retention for the UDB array version 0 */
    #if (CY_UDB_V0)                       
        TFT_backup.lowPulseWidth  = TFT_READ_LO_PULSE_REG;
        TFT_backup.highPulseWidth = TFT_READ_HI_PULSE_REG;      
    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: TFT_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of GraphicLCDIntf.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TFT_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void TFT_RestoreConfig(void) 
{    
    /* Restores D0/D1 Regs are non-retention for the UDB array version 0 */
    #if (CY_UDB_V0)                         
        TFT_READ_LO_PULSE_REG = TFT_backup.lowPulseWidth;
        TFT_READ_HI_PULSE_REG = TFT_backup.highPulseWidth;
    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: TFT_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TFT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TFT_Sleep(void) 
{
    TFT_Stop();
    TFT_SaveConfig();
}


/*******************************************************************************
* Function Name: TFT_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TFT_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void TFT_Wakeup(void) 
{
    TFT_RestoreConfig();
    TFT_Enable();
}


/* [] END OF FILE */
