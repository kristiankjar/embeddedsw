/******************************************************************************
* Copyright (c) 2021 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_ipi.h
* @addtogroup xnvm_ipi_apis XilNvm IPI APIs
* @{
*
* @cond xnvm_internal
* This file contains IPI generic APIs for xilnvm library
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   kal  07/05/21 Initial release
* 1.1   kpt  01/13/21 Added macro XNVM_SHARED_MEM_SIZE
*       kpt  03/16/22 Removed IPI related code and added mailbox support
*
* </pre>
* @note
*
* @endcond
******************************************************************************/

#ifndef XNVM_IPI_H
#define XNVM_IPI_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xilmailbox.h"
#include "xparameters.h"

/************************** Constant Definitions ****************************/

/**@cond xnvm_internal
 * @{
 */
#define XILNVM_MODULE_ID			(11U)

/* 1 for API ID + 5 for API arguments + 1 for reserved + 1 for CRC */
#define PAYLOAD_ARG_CNT			(8U)
/* 1 for status + 3 for values + 3 for reserved + 1 for CRC */
#define RESPONSE_ARG_CNT		(8U)
#define XNVM_IPI_TIMEOUT		(0xFFFFFFFFU)
					/**< IPI timeout */
#define XNVM_TARGET_IPI_INT_MASK	(0x00000002U)
					/**< Target PMC IPI interrupt mask */
#define XNVM_IPI_UNUSED_PARAM		(0U)
#define XNVM_MODULE_ID_SHIFT		(8U)
#define XNVM_PAYLOAD_LEN_SHIFT		(16U)
#define XILNVM_MODULE_ID_MASK		(XILNVM_MODULE_ID << XNVM_MODULE_ID_SHIFT)

/* Max size of shared memory used to store the CDO command */
#define XNVM_SHARED_MEM_SIZE		(256U)

#define XNVM_PAYLOAD_LEN_1U		(1U)
#define XNVM_PAYLOAD_LEN_2U		(2U)
#define XNVM_PAYLOAD_LEN_3U		(3U)
#define XNVM_PAYLOAD_LEN_4U		(4U)
#define XNVM_PAYLOAD_LEN_5U		(5U)
#define XNVM_PAYLOAD_LEN_6U		(6U)
#define XNVM_PAYLOAD_LEN_7U		(7U)

/**************************** Type Definitions *******************************/
typedef struct {
	XMailbox *MailboxPtr;
} XNvm_ClientInstance;

/***************** Macros (Inline Functions) Definitions *********************/

static inline u32 Header(u32 Len, u32 ApiId)
{
	return ((Len << XNVM_PAYLOAD_LEN_SHIFT) |
		XILNVM_MODULE_ID_MASK | (ApiId));
}

/**
 * @}
 * @endcond
 */
/************************** Variable Definitions *****************************/

/************************** Function Definitions *****************************/
int XNvm_ProcessMailbox(XMailbox *MailboxPtr, u32 *MsgPtr, u32 MsgLen);
int XNvm_ClientInit(XNvm_ClientInstance* const InstancePtr, XMailbox* const MailboxPtr);

#ifdef __cplusplus
}
#endif

#endif  /* XNVM_IPI_H */
