/******************************************************************************
* Copyright (c) 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsecure_ecdsacrvs.c
*
* This file contains the curve information of all the ECDSA curves supported
* in Versal.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   har  08/24/20 Initial release
* 4.3   har  08/24/20 Updated file version to sync with library version
*
* </pre>
*
* @note
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xsecure_ecdsacrvs.h"

/************************** Constant Definitions *****************************/
#ifdef XSECURE_ECDSA_SUPPORT_NIST_P384
static const u8 XSecure_EcdsaNistP384_d0[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x74U, 0xB1U, 0xB5U, 0xBDU,
	0xA7U, 0x16U, 0xEBU, 0x5BU, 0xFAU, 0x99U, 0x41U, 0x5BU,
	0xE0U, 0x1FU, 0xE5U, 0x45U, 0x4BU, 0xFEU, 0x48U, 0x25U,
	0x00U, 0x2EU, 0x92U, 0xCCU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0x44U, 0xDCU, 0x8FU, 0xE8U
};

static const u8 XSecure_EcdsaNistP384_d1[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFEU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
};

static const u8 XSecure_EcdsaNistP384_d2[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x00U, 0x00U, 0x00U, 0x00U,
	0xFDU, 0xFFU, 0xFFU, 0xFFU, 0x01U, 0x00U, 0x00U, 0x00U,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFCU, 0xFFU, 0xFFU, 0xFFU,
	0xFCU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
};

static const u8 XSecure_EcdsaNistP384_d3[] = {
	0xF9U, 0xBFU, 0x4FU, 0x60U, 0x52U, 0x51U, 0xB8U, 0x6CU,
	0x81U, 0x1CU, 0x39U, 0xD0U, 0x69U, 0x48U, 0x61U, 0x68U,
	0x30U, 0x04U, 0xA4U, 0xA7U, 0x24U, 0xBFU, 0x31U, 0xC4U,
	0x2FU, 0x02U, 0x20U, 0x19U, 0x9BU, 0x20U, 0xF2U, 0x77U,
	0xE2U, 0x8AU, 0x93U, 0x94U, 0xEEU, 0x4BU, 0x37U, 0xE3U,
	0x94U, 0x20U, 0x02U, 0x1FU, 0xF4U, 0x21U, 0x2BU, 0xB6U
};

static const u8 XSecure_EcdsaNistP384_d4[] = {
	0xB7U, 0x0AU, 0x76U, 0x72U, 0x38U, 0x5EU, 0x54U, 0x3AU,
	0x6CU, 0x29U, 0x55U, 0xBFU, 0x5DU, 0xF2U, 0x02U, 0x55U,
	0x38U, 0x2AU, 0x54U, 0x82U, 0xE0U, 0x41U, 0xF7U, 0x59U,
	0x98U, 0x9BU, 0xA7U, 0x8BU, 0x62U, 0x3BU, 0x1DU, 0x6EU,
	0x74U, 0xADU, 0x20U, 0xF3U, 0x1EU, 0xC7U, 0xB1U, 0x8EU,
	0x37U, 0x05U, 0x8BU, 0xBEU, 0x22U, 0xCAU, 0x87U, 0xAAU
};

static const u8 XSecure_EcdsaNistP384_d5[] = {
	0x5FU, 0x0EU, 0xEAU, 0x90U, 0x7CU, 0x1DU, 0x43U, 0x7AU,
	0x9DU, 0x81U, 0x7EU, 0x1DU, 0xCEU, 0xB1U, 0x60U, 0x0AU,
	0xC0U, 0xB8U, 0xF0U, 0xB5U, 0x13U, 0x31U, 0xDAU, 0xE9U,
	0x7CU, 0x14U, 0x9AU, 0x28U, 0xBDU, 0x1DU, 0xF4U, 0xF8U,
	0x29U, 0xDCU, 0x92U, 0x92U, 0xBFU, 0x98U, 0x9EU, 0x5DU,
	0x6FU, 0x2CU, 0x26U, 0x96U, 0x4AU, 0xDEU, 0x17U, 0x36U
};

static const u8 XSecure_EcdsaNistP384_d6[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFEU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP384_d7[] = {
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x01U, 0x00U, 0x00U, 0x00U, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x00U, 0x00U, 0x00U, 0x00U,
	0x01U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP384_d8[] = {
	0x01U, 0x00U, 0x00U, 0x00U, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x00U, 0x00U, 0x00U, 0x00U,
	0x02U, 0x00U, 0x00U, 0x00U, 0xFEU, 0xFFU, 0xFFU, 0xFFU,
	0x00U, 0x00U, 0x00U, 0x00U, 0x02U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0xFEU, 0xFFU, 0xFFU, 0xFFU,
	0x00U, 0x00U, 0x00U, 0x00U, 0x02U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP384_d9[] = {
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x8DU, 0xD6U, 0x3AU, 0x33U, 0x95U, 0xE6U, 0x13U, 0x13U,
	0x85U, 0x58U, 0x4FU, 0xB7U, 0x4DU, 0xF2U, 0xE5U, 0xA7U,
	0x20U, 0xD2U, 0xC8U, 0x0BU, 0x7EU, 0xB2U, 0x9CU, 0x38U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP384_d10[] = {
	0x11U, 0x28U, 0x56U, 0x99U, 0x1AU, 0xFCU, 0xA6U, 0x42U,
	0xEDU, 0x00U, 0x90U, 0x39U, 0x15U, 0xF7U, 0xBCU, 0x43U,
	0x8EU, 0x2DU, 0x2DU, 0xA7U, 0x8AU, 0xC9U, 0x42U, 0x0CU,
	0x92U, 0xE7U, 0xA0U, 0xF4U, 0xF9U, 0x01U, 0x96U, 0xCCU,
	0x43U, 0x9FU, 0x60U, 0xDEU, 0x06U, 0x06U, 0x03U, 0xBFU,
	0xC5U, 0x1CU, 0xABU, 0x4AU, 0x17U, 0x49U, 0x0DU, 0xD4U
};

static const u8 XSecure_EcdsaNistP384_d11[] = {
	0x01U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP384_d12[] = {
	0x73U, 0x29U, 0xC5U, 0xCCU, 0x6AU, 0x19U, 0xECU, 0xECU,
	0x7AU, 0xA7U, 0xB0U, 0x48U, 0xB2U, 0x0DU, 0x1AU, 0x58U,
	0xDFU, 0x2DU, 0x37U, 0xF4U, 0x81U, 0x4DU, 0x63U, 0xC7U,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
};

static const u8 XSecure_EcdsaNistP384_d13[] = {
	13U, 4U, 2U, 2U,
};
#endif

#ifdef XSECURE_ECDSA_SUPPORT_NIST_P521
static const u8 XSecure_EcdsaNistP521_d0[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xCAU, 0xA8U, 0x3DU, 0x0FU,
	0x39U, 0xF6U, 0x25U, 0xD7U, 0x97U, 0xECU, 0x95U, 0x9CU,
	0xF9U, 0x6EU, 0xB2U, 0x88U, 0x3EU, 0x1CU, 0x43U, 0x6AU,
	0x3AU, 0x49U, 0xE9U, 0x6CU, 0x33U, 0xBAU, 0xC9U, 0x67U,
	0xE5U, 0x14U, 0xC5U, 0x4CU, 0xFDU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0x8DU, 0x2BU, 0x53U, 0xF3U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d1[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0x01U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d2[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0x7FU, 0xFEU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0x01U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d3[] = {
	0xA6U, 0xE4U, 0x87U, 0x26U, 0x87U, 0x63U, 0x58U, 0xAEU,
	0x4FU, 0x65U, 0x14U, 0x80U, 0x1FU, 0xA8U, 0x35U, 0xEAU,
	0x8FU, 0xA2U, 0xF7U, 0x78U, 0x1AU, 0x96U, 0x1EU, 0xC4U,
	0xEFU, 0xB9U, 0x9AU, 0x83U, 0xDFU, 0xD8U, 0x9DU, 0x5EU,
	0x60U, 0x29U, 0x8BU, 0xBDU, 0x49U, 0x3FU, 0xF6U, 0xA8U,
	0x9CU, 0x0CU, 0xABU, 0xF0U, 0x84U, 0x78U, 0xC7U, 0xC8U,
	0x44U, 0x5AU, 0xDCU, 0xF9U, 0x8AU, 0xD9U, 0xCCU, 0x2DU,
	0x39U, 0x6DU, 0x51U, 0x77U, 0xA0U, 0x42U, 0x5BU, 0xD0U,
	0x10U, 0x01U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d4[] = {
	0x66U, 0xBDU, 0xE5U, 0xC2U, 0x31U, 0x7EU, 0x7EU, 0xF9U,
	0x9BU, 0x42U, 0x6AU, 0x85U, 0xC1U, 0xB3U, 0x48U, 0x33U,
	0xDEU, 0xA8U, 0xFFU, 0xA2U, 0x27U, 0xC1U, 0x1DU, 0xFEU,
	0x28U, 0x59U, 0xE7U, 0xEFU, 0x77U, 0x5EU, 0x4BU, 0xA1U,
	0xBAU, 0x3DU, 0x4DU, 0x6BU, 0x60U, 0xAFU, 0x28U, 0xF8U,
	0x21U, 0xB5U, 0x3FU, 0x05U, 0x39U, 0x81U, 0x64U, 0x9CU,
	0x42U, 0xB4U, 0x95U, 0x23U, 0x66U, 0xCBU, 0x3EU, 0x9EU,
	0xCDU, 0xE9U, 0x04U, 0x04U, 0xB7U, 0x06U, 0x8EU, 0x85U,
	0xC6U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d5[] = {
	0x50U, 0x66U, 0xD1U, 0x9FU, 0x76U, 0x94U, 0xBEU, 0x88U,
	0x40U, 0xC2U, 0x72U, 0xA2U, 0x86U, 0x70U, 0x3CU, 0x35U,
	0x61U, 0x07U, 0xADU, 0x3FU, 0x01U, 0xB9U, 0x50U, 0xC5U,
	0x40U, 0x26U, 0xF4U, 0x5EU, 0x99U, 0x72U, 0xEEU, 0x97U,
	0x2CU, 0x66U, 0x3EU, 0x27U, 0x17U, 0xBDU, 0xAFU, 0x17U,
	0x68U, 0x44U, 0x9BU, 0x57U, 0x49U, 0x44U, 0xF5U, 0x98U,
	0xD9U, 0x1BU, 0x7DU, 0x2CU, 0xB4U, 0x5FU, 0x8AU, 0x5CU,
	0x04U, 0xC0U, 0x3BU, 0x9AU, 0x78U, 0x6AU, 0x29U, 0x39U,
	0x18U, 0x01U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d6[] = {
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0x01U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d7[] = {
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d8[] = {
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x40U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d9[] = {
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x80U, 0xFBU, 0xCDU, 0x63U, 0xB7U, 0x70U,
	0x24U, 0x48U, 0xA2U, 0x28U, 0xDCU, 0x31U, 0xBBU, 0x23U,
	0x1BU, 0x25U, 0xE2U, 0x17U, 0x2DU, 0x7BU, 0x84U, 0x5BU,
	0xFFU, 0x19U, 0x40U, 0xCAU, 0x34U, 0x68U, 0x20U, 0x3EU,
	0xBCU, 0x3CU, 0xD7U, 0x02U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d10[] = {
	0x4AU, 0x5DU, 0x1AU, 0xB4U, 0x17U, 0xB7U, 0xC8U, 0x58U,
	0x70U, 0x77U, 0xC4U, 0x7BU, 0xB2U, 0x49U, 0x87U, 0x57U,
	0xB9U, 0x82U, 0xD7U, 0xA1U, 0x16U, 0x7FU, 0xEEU, 0x90U,
	0x97U, 0x60U, 0x0BU, 0x59U, 0xFCU, 0xE0U, 0x17U, 0xE4U,
	0x97U, 0x05U, 0x45U, 0xC5U, 0xEBU, 0x00U, 0x3DU, 0x81U,
	0xDCU, 0xC7U, 0x49U, 0x2EU, 0xD8U, 0x23U, 0x6EU, 0xDDU,
	0x3EU, 0x6EU, 0x75U, 0xB7U, 0x42U, 0xD1U, 0xF3U, 0xCFU,
	0xBCU, 0x67U, 0xE5U, 0xA8U, 0x61U, 0x6DU, 0xCCU, 0x5BU,
	0x45U, 0x01U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d11[] = {
	0x01U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
	0x00U, 0x00U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d12[] = {
	0x09U, 0x64U, 0x38U, 0x91U, 0x1EU, 0xB7U, 0x6FU, 0xBBU,
	0xAEU, 0x47U, 0x9CU, 0x89U, 0xB8U, 0xC9U, 0xB5U, 0x3BU,
	0xD0U, 0xA5U, 0x09U, 0xF7U, 0x48U, 0x01U, 0xCCU, 0x7FU,
	0x6BU, 0x96U, 0x2FU, 0xBFU, 0x83U, 0x87U, 0x86U, 0x51U,
	0xFAU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
	0xFFU, 0x01U, 0x00U, 0x00U
};

static const u8 XSecure_EcdsaNistP521_d13[] = {
	18U, 6U, 3U, 1U,
};
#endif

/**************************** Type Definitions *******************************/
EcdsaCrvInfo XSecure_EcdsaCrvsDb[] =
{
#ifdef XSECURE_ECDSA_SUPPORT_NIST_P384
	{
		ECDSA_NIST_P384,
		384U,
		ECDSA_PRIME,
		XSecure_EcdsaNistP384_d0,
		XSecure_EcdsaNistP384_d1,
		XSecure_EcdsaNistP384_d2,
		XSecure_EcdsaNistP384_d3,
		XSecure_EcdsaNistP384_d4,
		XSecure_EcdsaNistP384_d5,
		XSecure_EcdsaNistP384_d6,
		XSecure_EcdsaNistP384_d7,
		XSecure_EcdsaNistP384_d8,
		XSecure_EcdsaNistP384_d9,
		XSecure_EcdsaNistP384_d10,
		XSecure_EcdsaNistP384_d11,
		XSecure_EcdsaNistP384_d12,
		XSecure_EcdsaNistP384_d13
	},
#endif

#ifdef XSECURE_ECDSA_SUPPORT_NIST_P521
	{
		ECDSA_NIST_P521,
		521U,
		ECDSA_PRIME,
		XSecure_EcdsaNistP521_d0,
		XSecure_EcdsaNistP521_d1,
		XSecure_EcdsaNistP521_d2,
		XSecure_EcdsaNistP521_d3,
		XSecure_EcdsaNistP521_d4,
		XSecure_EcdsaNistP521_d5,
		XSecure_EcdsaNistP521_d6,
		XSecure_EcdsaNistP521_d7,
		XSecure_EcdsaNistP521_d8,
		XSecure_EcdsaNistP521_d9,
		XSecure_EcdsaNistP521_d10,
		XSecure_EcdsaNistP521_d11,
		XSecure_EcdsaNistP521_d12,
		XSecure_EcdsaNistP521_d13
	},
#endif
};

/***************** Macros (Inline Functions) Definitions *********************/
/*****************************************************************************/
/**
 * @brief	This function calculates the total number of curves supported.
 *
 * @return  Returns the number of curves supported
 *
 *****************************************************************************/
inline u32 XSecure_EcdsaCrvsGetCount()
{
	return sizeof(XSecure_EcdsaCrvsDb) / sizeof(EcdsaCrvInfo);
}

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/************************** Function Definitions *****************************/