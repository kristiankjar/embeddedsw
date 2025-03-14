/******************************************************************************
* Copyright (c) 2021 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_efuseclient.c
*
* This file contains the implementation of the client interface functions for
* eFUSE programming.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   kal  07/29/21 Initial release
*       kpt  08/27/21 Added client API's to support puf helper data efuse
*                     programming
* 1.1   kpt  11/29/21 Replaced Xil_DCacheFlushRange with
*                     XNvm_DCacheFlushRange
*       kpt  01/13/22 Allocated CDO structure's in shared memory set by the
*                     user
*       am   02/28/22 Fixed MISRA C violations
*       kpt  03/16/22 Removed IPI related code and added mailbox support
*
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xil_cache.h"
#include "xnvm_efuseclient.h"
#include "xil_util.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @brief       This function sends IPI request to program eFuses with
 * 		user provided data
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	DataAddr	Address of the data structure where the eFUSE
 * 				data to be programmed is stored
 *
 * @return	- XST_SUCCESS - If the eFUSE programming is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseWrite(XNvm_ClientInstance *InstancePtr, const u64 DataAddr)
{
	volatile int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_WRITE);
	Payload[1U] = (u32)DataAddr;
	Payload[2U] = (u32)(DataAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));
	if (Status != XST_SUCCESS) {
		XNvm_Printf(XNVM_DEBUG_GENERAL, "eFUSE programming Failed \r\n");
	}
END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief       This function sends IPI request to program IV eFuses with
 * 		user provided data
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	IvAddr		Address of the data structure where the eFUSE
 * 				data to be programmed is stored
 * @param	EnvDisFlag	Flag that tells weather to enable/disable
 *				Environmental monitoring in XilNvm
 *
 * @return	- XST_SUCCESS - If the programming is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseWriteIVs(XNvm_ClientInstance *InstancePtr, const u64 IvAddr,
								const u32 EnvDisFlag)
{
	volatile int Status = XST_FAILURE;
	XNvm_EfuseDataAddr *EfuseData = NULL;
	u64 DataAddr;
	u32 Size;
	u32 TotalSize = sizeof(XNvm_EfuseDataAddr);
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Size = XMailbox_GetSharedMem(InstancePtr->MailboxPtr, (u64**)(UINTPTR)&EfuseData);

	if ((EfuseData == NULL) || (Size < TotalSize)) {
		goto END;
	}

	Status = Xil_SMemSet(EfuseData, TotalSize, 0U, TotalSize);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	EfuseData->EnvMonDisFlag = EnvDisFlag;
	EfuseData->IvAddr = IvAddr;
	DataAddr = (u64)(UINTPTR)EfuseData;

	XNvm_DCacheFlushRange(EfuseData, TotalSize);

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_WRITE);
	Payload[1U] = (u32)DataAddr;
	Payload[2U] = (u32)(DataAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));
END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to program PPK_INVLD eFuse
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PpkRevoke	Type of PPK_INVLD to be revoked
 * @param	EnvDisFlag	Flag that tells whether to enable/disable
 *				Environmental monitoring in XilNvm
 *
 * @return	- XST_SUCCESS - If the programming is successful
 *		- XST_FAILURE - If there is a failure
 *
 *****************************************************************************/
int XNvm_EfuseRevokePpk(XNvm_ClientInstance *InstancePtr, const XNvm_PpkType PpkRevoke,
								const u32 EnvDisFlag)
{
	volatile int Status = XST_FAILURE;
	XNvm_EfuseDataAddr *EfuseData = NULL;
	XNvm_EfuseMiscCtrlBits *MiscCtrlBits = NULL;
	u64 DataAddr;
	u32 Size;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];
	u32 TotalSize = sizeof(XNvm_EfuseDataAddr) + sizeof(XNvm_EfuseMiscCtrlBits);

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Size = XMailbox_GetSharedMem(InstancePtr->MailboxPtr, (u64**)(UINTPTR)&EfuseData);

	if ((EfuseData == NULL) || (Size < TotalSize)) {
		goto END;
	}

	MiscCtrlBits = (XNvm_EfuseMiscCtrlBits*)(UINTPTR)((u8*)EfuseData + sizeof(XNvm_EfuseDataAddr));

	Status = Xil_SMemSet(EfuseData, sizeof(XNvm_EfuseDataAddr), 0U, sizeof(XNvm_EfuseDataAddr));
	if (Status != XST_SUCCESS) {
		goto END;
	}

	Status = Xil_SMemSet(MiscCtrlBits, sizeof(XNvm_EfuseMiscCtrlBits), 0U, sizeof(XNvm_EfuseMiscCtrlBits));
	if (Status != XST_SUCCESS) {
		goto END;
	}

	if (PpkRevoke == XNVM_EFUSE_PPK0) {
		MiscCtrlBits->Ppk0Invalid = TRUE;
	}
	else if (PpkRevoke == XNVM_EFUSE_PPK1) {
		MiscCtrlBits->Ppk1Invalid = TRUE;
	}
	else if (PpkRevoke == XNVM_EFUSE_PPK2) {
		MiscCtrlBits->Ppk2Invalid = TRUE;
	}
	else {
		goto END;
	}

	EfuseData->EnvMonDisFlag = EnvDisFlag;
	EfuseData->MiscCtrlAddr = (UINTPTR)MiscCtrlBits;
	DataAddr = (u64)(UINTPTR)EfuseData;

	XNvm_DCacheFlushRange(EfuseData, TotalSize);

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_WRITE);
	Payload[1U] = (u32)DataAddr;
	Payload[2U] = (u32)(DataAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));
END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to program revoke id eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	RevokeId	RevokeId number to be revoked
 * @param 	EnvDisFlag	Flag that tells whether to enable/disable
 *				Environmental monitoring in XilNvm
 *
 * @return	- XST_SUCCESS - If the programming is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseWriteRevocationId(XNvm_ClientInstance *InstancePtr, const u32 RevokeId,
											const u32 EnvDisFlag)
{
	volatile int Status = XST_FAILURE;
	XNvm_EfuseDataAddr *EfuseData = NULL;
	XNvm_EfuseRevokeIds *WriteRevokeId = NULL;
	u32 RevokeIdRow;
	u32 RevokeIdBit;
	u64 DataAddr;
	u32 Size;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];
	u32 TotalSize = sizeof(XNvm_EfuseDataAddr) + sizeof(XNvm_EfuseRevokeIds);

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Size = XMailbox_GetSharedMem(InstancePtr->MailboxPtr, (u64**)(UINTPTR)&EfuseData);

	if ((EfuseData == NULL) || (Size < TotalSize)) {
		goto END;
	}

	WriteRevokeId = (XNvm_EfuseRevokeIds*)(UINTPTR)((u8*)EfuseData + sizeof(XNvm_EfuseDataAddr));

	Status = Xil_SMemSet(EfuseData, sizeof(XNvm_EfuseDataAddr), 0U, sizeof(XNvm_EfuseDataAddr));
	if (Status != XST_SUCCESS) {
		goto END;
	}

	Status = Xil_SMemSet(WriteRevokeId, sizeof(XNvm_EfuseRevokeIds), 0U, sizeof(XNvm_EfuseRevokeIds));
	if (Status != XST_SUCCESS) {
		goto END;
	}

	RevokeIdRow = RevokeId >> (XNVM_WORD_LEN + 1U);
	RevokeIdBit = RevokeId & (XNVM_WORD_LEN - 1U);

	if (RevokeIdRow > (XNVM_NUM_OF_REVOKE_ID_FUSES - 1U)) {
		goto END;
	}

	WriteRevokeId->RevokeId[RevokeIdRow] = ((u32)1U << RevokeIdBit);
	WriteRevokeId->PrgmRevokeId = TRUE;

	EfuseData->RevokeIdAddr = (UINTPTR)WriteRevokeId;
	EfuseData->EnvMonDisFlag = EnvDisFlag;
	DataAddr = (u64)(UINTPTR)EfuseData;

	XNvm_DCacheFlushRange(EfuseData, TotalSize);

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_WRITE);
	Payload[1U] = (u32)DataAddr;
	Payload[2U] = (u32)(DataAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to program User eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	UserFuseAddr	Address of the XNvm_EfuseUserData structure
 * 				where the user provided data to be programmed
 * @param	EnvDisFlag	Flag that tells whether to enable/disable
 *				Environmental monitoring in XilNvm
 *
 * @return	- XST_SUCCESS - If the programming is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseWriteUserFuses(XNvm_ClientInstance *InstancePtr, const u64 UserFuseAddr, const u32 EnvDisFlag)
{
	volatile int Status = XST_FAILURE;
	XNvm_EfuseDataAddr *EfuseData = NULL;
	u64 DataAddr;
	u32 Size;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];
	u32 TotalSize = sizeof(XNvm_EfuseDataAddr);

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Size = XMailbox_GetSharedMem(InstancePtr->MailboxPtr, (u64**)(UINTPTR)&EfuseData);

	if ((EfuseData == NULL) || (Size < TotalSize)) {
		goto END;
	}

	Status = Xil_SMemSet(EfuseData, TotalSize, 0U, TotalSize);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	EfuseData->EnvMonDisFlag = EnvDisFlag;
	EfuseData->UserFuseAddr = UserFuseAddr;
	DataAddr = (u64)(UINTPTR)EfuseData;

	XNvm_DCacheFlushRange(EfuseData, TotalSize);

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_WRITE);
	Payload[1U] = (u32)DataAddr;
	Payload[2U] = (u32)(DataAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read IV eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	IvAddr		Address of the output buffer to store the
 * 				IV eFuse data
 * @param	IvType		Type of the IV to read out
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadIv(XNvm_ClientInstance *InstancePtr, u64 IvAddr, const XNvm_IvType IvType)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_4U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_IV);
	Payload[1U] = (u32)IvType;
	Payload[2U] = (u32)IvAddr;
	Payload[3U] = (u32)(IvAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read Revocation ID eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	RevokeIdAddr	Address of the output buffer to store the
 * 				Revocation ID eFuse data
 * @param 	RevokeIdNum	Revocation ID to be read out
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadRevocationId(XNvm_ClientInstance *InstancePtr, const u64 RevokeIdAddr,
			const XNvm_RevocationId RevokeIdNum)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_4U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_REVOCATION_ID);
	Payload[1U] = (u32)RevokeIdNum;
	Payload[2U] = (u32)RevokeIdAddr;
	Payload[3U] = (u32)(RevokeIdAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read User eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	UserFuseAddr	Address of the output buffer to store the
 * 				User eFuse data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadUserFuses(XNvm_ClientInstance *InstancePtr, u64 UserFuseAddr)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_USER_FUSES);
	Payload[1U] = (u32)UserFuseAddr;
	Payload[2U] = (u32)(UserFuseAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read MiscCtrlBits
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	MiscCtrlBits	Address of the output buffer to store the
 * 				MiscCtrlBits eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadMiscCtrlBits(XNvm_ClientInstance *InstancePtr, const u64 MiscCtrlBits)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_MISC_CTRL_BITS);
	Payload[1U] = (u32)MiscCtrlBits;
	Payload[2U] = (u32)(MiscCtrlBits >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read SecCtrlBits
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	SecCtrlBits	Address of the output buffer to store the
 * 				SecCtrlBits eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadSecCtrlBits(XNvm_ClientInstance *InstancePtr, const u64 SecCtrlBits)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_SEC_CTRL_BITS);
	Payload[1U] = (u32)SecCtrlBits;
	Payload[2U] = (u32)(SecCtrlBits >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read SecMisc1Bits
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	SecMisc1Bits	Address of the output buffer to store the
 * 				SecMisc1Bits eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadSecMisc1Bits(XNvm_ClientInstance *InstancePtr, const u64 SecMisc1Bits)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_SEC_MISC1_BITS);
	Payload[1U] = (u32)SecMisc1Bits;
	Payload[2U] = (u32)(SecMisc1Bits >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
		return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read BootEnvCtrlBits
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	BootEnvCtrlBits	Address of the output buffer to store the
 * 				BootEnvCtrlBits eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadBootEnvCtrlBits(XNvm_ClientInstance *InstancePtr, const u64 BootEnvCtrlBits)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_BOOT_ENV_CTRL_BITS);
	Payload[1U] = (u32)BootEnvCtrlBits;
	Payload[2U] = (u32)(BootEnvCtrlBits >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read PufSecCtrlBits
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PufSecCtrlBits	Address of the output buffer to store the
 * 				PufSecCtrlBits eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadPufSecCtrlBits(XNvm_ClientInstance *InstancePtr, const u64 PufSecCtrlBits)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_PUF_SEC_CTRL_BITS);
	Payload[1U] = (u32)PufSecCtrlBits;
	Payload[2U] = (u32)(PufSecCtrlBits >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read OffChip ID eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	OffChipIdAddr	Address of the output buffer to store the
 * 				OffChip ID eFuse data
 * @param	OffChipIdNum	OffChip ID number to be read out
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadOffchipRevokeId(XNvm_ClientInstance *InstancePtr, const u64 OffChidIdAddr,
	const XNvm_OffchipId OffChipIdNum)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_4U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_OFFCHIP_REVOCATION_ID);
	Payload[1U] = (u32)OffChipIdNum;
	Payload[2U] = (u32)OffChidIdAddr;
	Payload[3U] = (u32)(OffChidIdAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read PpkHash
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PpkHashAddr	Address of the output buffer to store the
 * 				PpkHashAddr eFuses data
 * @param 	PpkHashType	Type of the PpkHash to be read out
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadPpkHash(XNvm_ClientInstance *InstancePtr, const u64 PpkHashAddr, const XNvm_PpkType PpkHashType)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_4U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_PPK_HASH);
	Payload[1U] = (u32)PpkHashType;
	Payload[2U] = (u32)PpkHashAddr;
	Payload[3U] = (u32)(PpkHashAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read DecEfuseOnly eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	DecOnlyAddr	Address of the output buffer to store the
 * 				DecEfuseOnly eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadDecOnly(XNvm_ClientInstance *InstancePtr, const u64 DecOnlyAddr)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_DEC_EFUSE_ONLY);
	Payload[1U] = (u32)DecOnlyAddr;
	Payload[2U] = (u32)(DecOnlyAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read DNA eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	DnaAddr		Address of the output buffer to store the
 * 				DNA eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadDna(XNvm_ClientInstance *InstancePtr, const u64 DnaAddr)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_DNA);
	Payload[1U] = (u32)DnaAddr;
	Payload[2U] = (u32)(DnaAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

#ifdef XNVM_ACCESS_PUF_USER_DATA

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to program Puf as User eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PufUserFuseAddr	Address of the XNvm_EfusePufFuseAddr structure
 * 				where the user provided data to be programmed
 *
 * @return	- XST_SUCCESS - If the programming is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseWritePufAsUserFuses(XNvm_ClientInstance *InstancePtr, const u64 PufUserFuseAddr)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_PUF_USER_FUSE_WRITE);
	Payload[1U] = (u32)PufUserFuseAddr;
	Payload[2U] = (u32)(PufUserFuseAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read Puf User eFuses
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PufUserFuseAddr	Address of the output buffer to store the
 * 				Puf User eFuses data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadPufAsUserFuses(XNvm_ClientInstance *InstancePtr, const u64 PufUserFuseAddr)
{
	int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_PUF_USER_FUSE);
	Payload[1U] = (u32)PufUserFuseAddr;
	Payload[2U] = (u32)(PufUserFuseAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}
#else

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to program Puf helper data
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PufHdAddr	Address of the XNvm_EfusePufHdAddr structure
 * 				where the user provided helper data to be programmed
 *
 * @return	- XST_SUCCESS - If the programming is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseWritePuf(XNvm_ClientInstance *InstancePtr, const u64 PufHdAddr) {
	volatile int Status = XST_FAILURE;
	u64 DataAddr;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	DataAddr = PufHdAddr;

	XNvm_DCacheFlushRange((UINTPTR)DataAddr, sizeof(XNvm_EfusePufHdAddr));

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_WRITE_PUF);
	Payload[1U] = (u32)DataAddr;
	Payload[2U] = (u32)(DataAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;

}

/*****************************************************************************/
/**
 * @brief	This function sends IPI request to read Puf helper data
 * 		requested by the user
 *
 * @param	InstancePtr Pointer to the client instance
 * @param	PufHdAddr	Address of the output buffer to store the
 * 				Puf helper data
 *
 * @return	- XST_SUCCESS - If the read is successful
 * 		- XST_FAILURE - If there is a failure
 *
 ******************************************************************************/
int XNvm_EfuseReadPuf(XNvm_ClientInstance *InstancePtr, const u64 PufHdAddr) {
	volatile int Status = XST_FAILURE;
	u32 Payload[XNVM_PAYLOAD_LEN_3U];

	if ((InstancePtr == NULL) || (InstancePtr->MailboxPtr == NULL)) {
		goto END;
	}

	Payload[0U] = Header(0U, (u32)XNVM_API_ID_EFUSE_READ_PUF);
	Payload[1U] = (u32)PufHdAddr;
	Payload[2U] = (u32)(PufHdAddr >> 32U);

	Status = XNvm_ProcessMailbox(InstancePtr->MailboxPtr, Payload, sizeof(Payload)/sizeof(u32));

END:
	return Status;
}
#endif
