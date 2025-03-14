/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xpuf_defs.h
* @addtogroup xpuf_api_ids XilPuf API IDs
* @{
*
* @cond xpuf_internal
* This file contains the xilpuf API IDs
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   kpt  01/04/22 Initial release
*
* </pre>
* @note
*
* @endcond
******************************************************************************/

#ifndef XPUF_DEFS_H
#define XPUF_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_printf.h"
#include "xil_types.h"

/************************** Constant Definitions ****************************/
/**@cond xpuf_internal
 * @{
 */
/* Enable client printfs by setting XPUF_DEBUG to 1 */
#define XPUF_DEBUG	(0U)

#if (XPUF_DEBUG)
#define XPUF_DEBUG_GENERAL (1U)
#else
#define XPUF_DEBUG_GENERAL (0U)
#endif

#define XPUF_MAX_SYNDROME_DATA_LEN_IN_WORDS		(350U)
#define XPUF_4K_PUF_SYN_LEN_IN_WORDS			(140U)
#define XPUF_EFUSE_TRIM_SYN_DATA_IN_WORDS		(127U)
#define XPUF_12K_PUF_SYN_LEN_IN_WORDS			(350U)
#define XPUF_ID_LEN_IN_WORDS				    (0x8U)
#define XPUF_WORD_LENGTH				        (0x4U)
#define XPUF_MAX_SYNDROME_DATA_LEN_IN_BYTES		(XPUF_MAX_SYNDROME_DATA_LEN_IN_WORDS * \
												 XPUF_WORD_LENGTH)
#define XPUF_4K_PUF_SYN_LEN_IN_BYTES			(XPUF_4K_PUF_SYN_LEN_IN_WORDS * \
												 XPUF_WORD_LENGTH)
#define XPUF_ID_LEN_IN_BYTES				    (XPUF_ID_LEN_IN_WORDS * \
												 XPUF_WORD_LENGTH)
#define XPUF_EFUSE_TRIM_SYN_DATA_IN_BYTES		(XPUF_EFUSE_TRIM_SYN_DATA_IN_WORDS * \
												 XPUF_WORD_LENGTH)

/***************** Macros (Inline Functions) Definitions *********************/
#define XPuf_Printf(DebugType, ...)	\
	if ((DebugType) == 1U) {xil_printf (__VA_ARGS__);}

/* Macro to typecast XILSECURE API ID */
#define XPUF_API(ApiId)	((u32)ApiId)

#define XPUF_API_ID_MASK	(0xFFU)

/************************** Variable Definitions *****************************/

/**************************** Type Definitions *******************************/

typedef struct {
	u8 RegMode;		/* PUF Registration Mode 4K/12K*/
	u8 PufOperation;
	   /* PUF Registration/ Regeneration On Demand/ ID only regeneration) */
	u8 GlobalVarFilter;
	u8 ReadOption;	/* Read helper data from eFuse Cache/DDR */
	u32 ShutterValue;	/**< Shutter value for PUF registration or regeneration */
	u64 SyndromeDataAddr;
	u64 ChashAddr;
	u64 AuxAddr;
	u64 PufIDAddr;
	u64 SyndromeAddr;
	u64 EfuseSynDataAddr;
				 /* Trimmed data to be written in efuse */
} XPuf_DataAddr;

/* XilPUF API ids */
typedef enum {
	XPUF_API_FEATURES = 0U,		/**< API id for features */
	XPUF_PUF_REGISTRATION,		/**< API id for PUF registration */
	XPUF_PUF_REGENERATION,		/**< API id for PUF regeneration */
	XPUF_PUF_CLEAR_PUF_ID,		/**< API id for PUF clear id */
	XPUF_API_MAX,			/**< Number of API features */
} XPuf_ApiId;

/**
 * @}
 * @endcond
 */

#ifdef __cplusplus
}
#endif

#endif  /* XPUF_DEFS_H */
