/******************************************************************************
* Copyright (C) 2010 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xaxidma_g.c
* @addtogroup axidma_v9_13
* @{
*
* Provide a template for user to define their own hardware settings.
*
* If using XPS, then XPS will automatically generate this file.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a jz   08/16/10 First release
* 2.00a jz   08/10/10 Second release, added in xaxidma_g.c, xaxidma_sinit.c,
*                     updated tcl file, added xaxidma_porting_guide.h
* 3.00a jz   11/22/10 Support IP core parameters change
* 4.00a rkv  02/22/11 Added support for simple DMA mode
* 6.00a srt  01/24/12 Added support for Multi-Channel DMA mode
* 7.02a srt  01/23/13 Replaced *_TDATA_WIDTH parameters to *_DATA_WIDTH
*		      (CR 691867)
* 9.7   rsp  04/25/18 In XAxiDma_Config add SG length width.
* 9.8   rsp  07/18/18 Sync XAxiDma_Config initializer fields
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xaxidma.h"

/************************** Constant Definitions *****************************/
#define XPAR_AXIDMA_0_INCLUDE_SG	0

XAxiDma_Config XAxiDma_ConfigTable[] =
{
	{
		XPAR_AXIDMA_0_DEVICE_ID,
		XPAR_AXIDMA_0_BASEADDR,
		XPAR_AXIDMA_0_SG_INCLUDE_STSCNTRL_STRM,
		XPAR_AXIDMA_0_INCLUDE_MM2S,
		XPAR_AXIDMA_0_INCLUDE_MM2S_DRE,
		XPAR_AXIDMA_0_M_AXI_MM2S_DATA_WIDTH,
		XPAR_AXIDMA_0_INCLUDE_S2MM,
		XPAR_AXIDMA_0_INCLUDE_S2MM_DRE,
		XPAR_AXIDMA_0_M_AXI_S2MM_DATA_WIDTH,
		XPAR_AXIDMA_0_INCLUDE_SG,
		XPAR_AXIDMA_0_NUM_MM2S_CHANNELS,
		XPAR_AXIDMA_0_NUM_S2MM_CHANNELS,
		XPAR_AXI_DMA_0_MM2S_BURST_SIZE,
		XPAR_AXI_DMA_0_S2MM_BURST_SIZE,
		XPAR_AXI_DMA_0_MICRO_DMA,
		XPAR_AXI_DMA_0_ADDR_WIDTH,
		XPAR_AXIDMA_0_SG_LENGTH_WIDTH
	}
};
/** @} */
