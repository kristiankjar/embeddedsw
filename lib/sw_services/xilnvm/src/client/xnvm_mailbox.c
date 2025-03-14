/******************************************************************************
* Copyright (c) 2021 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_ipi.c
*
* This file contains the implementation of the client interface functions for
* IPI driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   kal  07/05/21 Initial release
* 1.1   kpt  01/13/21 Added API's to set and get the shared memory
*       kpt  03/16/22 Removed IPI related code and added mailbox support
*
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xil_types.h"
#include "xnvm_mailbox.h"

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/************************** Function Definitions *****************************/

/****************************************************************************/
/**
 * @brief  This function sends IPI request to the target module and gets the
 * response from it
 *
 * @param	MailboxPtr	Pointer to mailbox instance
 * @param	MsgPtr		Pointer to the payload message
 * @param	MsgLen		Length of the message
 *
 * @return
 *	-	XST_SUCCESS - If the IPI send and receive is successful
 *	-	XST_FAILURE - If there is a failure
 *
 * @note	Payload  consists of API id and call arguments to be written
 * 		in IPI buffer
 *
 ****************************************************************************/
int XNvm_ProcessMailbox(XMailbox *MailboxPtr, u32 *MsgPtr, u32 MsgLen)
{
	int Status = XST_FAILURE;
	u32 Response[RESPONSE_ARG_CNT];

	Status = (int)XMailbox_SendData(MailboxPtr, XNVM_TARGET_IPI_INT_MASK, MsgPtr, MsgLen,
				XILMBOX_MSG_TYPE_REQ, TRUE);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	Status = (int)XMailbox_Recv(MailboxPtr, XNVM_TARGET_IPI_INT_MASK, Response, RESPONSE_ARG_CNT,
				XILMBOX_MSG_TYPE_RESP);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	Status = (int)Response[0];

END:
	return Status;
}

/*****************************************************************************/
/**
*
* This function sets the instance of mailbox
*
* @param InstancePtr Pointer to the client instance
* @param MailboxPtr Pointer to the mailbox instance
*
* @return
* 	- XST_SUCCESS	On successful initialization
* 	- XST_FAILURE	On failure
*
******************************************************************************/
int XNvm_ClientInit(XNvm_ClientInstance* const InstancePtr, XMailbox* const MailboxPtr) {
	int Status = XST_FAILURE;

	if (InstancePtr != NULL) {
			InstancePtr->MailboxPtr = MailboxPtr;
			Status = XST_SUCCESS;
	}

	return Status;
}
