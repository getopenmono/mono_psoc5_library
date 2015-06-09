/*******************************************************************************
* File Name: GraphicLCDIntf_1_PM.c
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

#include "GraphicLCDIntf_1.h" 

#if (CY_UDB_V0)
    static GraphicLCDIntf_1_BACKUP_STRUCT GraphicLCDIntf_1_backup = 
    {
        GraphicLCDIntf_1_READ_LOW_PULSE,
        GraphicLCDIntf_1_READ_HIGH_PULSE 
    };
#endif /* (CY_UDB_V0) */


/*******************************************************************************
* Function Name: GraphicLCDIntf_1_SaveConfig
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
*  GraphicLCDIntf_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void GraphicLCDIntf_1_SaveConfig(void) 
{   
    /* Saves D0/D1 Regs are non-retention for the UDB array version 0 */
    #if (CY_UDB_V0)                       
        GraphicLCDIntf_1_backup.lowPulseWidth  = GraphicLCDIntf_1_READ_LO_PULSE_REG;
        GraphicLCDIntf_1_backup.highPulseWidth = GraphicLCDIntf_1_READ_HI_PULSE_REG;      
    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: GraphicLCDIntf_1_RestoreConfig
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
*  GraphicLCDIntf_1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void GraphicLCDIntf_1_RestoreConfig(void) 
{    
    /* Restores D0/D1 Regs are non-retention for the UDB array version 0 */
    #if (CY_UDB_V0)                         
        GraphicLCDIntf_1_READ_LO_PULSE_REG = GraphicLCDIntf_1_backup.lowPulseWidth;
        GraphicLCDIntf_1_READ_HI_PULSE_REG = GraphicLCDIntf_1_backup.highPulseWidth;
    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: GraphicLCDIntf_1_Sleep
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
*  GraphicLCDIntf_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void GraphicLCDIntf_1_Sleep(void) 
{
    GraphicLCDIntf_1_Stop();
    GraphicLCDIntf_1_SaveConfig();
}


/*******************************************************************************
* Function Name: GraphicLCDIntf_1_Wakeup
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
*  GraphicLCDIntf_1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void GraphicLCDIntf_1_Wakeup(void) 
{
    GraphicLCDIntf_1_RestoreConfig();
    GraphicLCDIntf_1_Enable();
}


/* [] END OF FILE */
