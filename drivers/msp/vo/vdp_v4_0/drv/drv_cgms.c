/*
 * Copyright (C) 2017, Hisilicon Tech. Co., Ltd.
 * SPDX-License-Identifier: GPL-2.0
 */

#include "drv_cgms.h"
#include "vdp_software_selfdefine.h"

#ifndef __DISP_PLATFORM_BOOT__
HI_S32 DRV_CGMS_Init(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_FMT_E enFmt,DISP_CGMS_INFO_S *pstCgms)
{
    CgmsCheckNullPointer(pstCgms);

	pstCgms->bEnable = HI_FALSE;

	pstCgms->enAttachedDisp = enDisp;

	pstCgms->enType = HI_DRV_DISP_CGMSA_A;

	pstCgms->enMode = HI_DRV_DISP_CGMSA_COPY_FREELY;

	pstCgms->enCurFormat = enFmt;

	return HI_SUCCESS;
}

HI_S32 DRV_CGMS_DeInit(DISP_CGMS_INFO_S *pstCgms)
{
	return HI_SUCCESS;
}


HI_S32 DISP_CGMS_SetEnable(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
	DISP_VENC_E enChannel;

	if (pstCgms->enAttachedDisp == HI_DRV_DISPLAY_1)
	{
		enChannel = DISP_VENC_HDATE0;
	}
	else if(pstCgms->enAttachedDisp == HI_DRV_DISPLAY_0)
	{
		enChannel = DISP_VENC_SDATE0;
	}
	else
	{
		enChannel = DISP_VENC_MAX;
	}

	if (stCgmsCfg.enType == HI_DRV_DISP_CGMSA_A)
	{
		if (enFormat == HI_DRV_DISP_FMT_PAL
				|| enFormat == HI_DRV_DISP_FMT_PAL_N
				|| enFormat == HI_DRV_DISP_FMT_PAL_Nc)
		{
			SDATE_HDATE_VBI_SetWssEn(enChannel,stCgmsCfg.bEnable);
		}
		else
		{
			if (pstCgms->enCurFormat == HI_DRV_DISP_FMT_PAL
					|| pstCgms->enCurFormat == HI_DRV_DISP_FMT_PAL_N
					|| pstCgms->enCurFormat ==HI_DRV_DISP_FMT_PAL_Nc)
			{
				SDATE_HDATE_VBI_SetWssEn(enChannel,HI_FALSE);
			}

			SDATE_HDATE_VBI_SetCgmsTypeAEn(enChannel,stCgmsCfg.bEnable);
		}
	}
	else if (stCgmsCfg.enType == HI_DRV_DISP_CGMSA_B)
	{
		VDP_VBI_SetCgmsTypeBEn(enChannel,stCgmsCfg.bEnable);
	}
	else
	{

	}

	return HI_SUCCESS;
}

HI_S32 DISP_CGMS_SetTypeA(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
	HI_U32 u32Data;

	DISP_VENC_E enChannel;

	if (pstCgms->enAttachedDisp == HI_DRV_DISPLAY_1)
	{
		enChannel = DISP_VENC_HDATE0;
	}
	else if(pstCgms->enAttachedDisp == HI_DRV_DISPLAY_0)
	{
		enChannel = DISP_VENC_SDATE0;
	}
	else
	{
		enChannel = DISP_VENC_MAX;
	}

	switch (enFormat)
	{
		case HI_DRV_DISP_FMT_1080i_50:
		case HI_DRV_DISP_FMT_1080i_60:
		case HI_DRV_DISP_FMT_720P_50:
		case HI_DRV_DISP_FMT_720P_60:
		case HI_DRV_DISP_FMT_480P_60:
			{
				if (stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_FREELY)
				{
					u32Data = 0x88003;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NO_MORE)
				{
					u32Data = 0x28083;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_ONCE)
				{
					u32Data = 0xd8043;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NEVER)
				{
					u32Data = 0x780c3;
				}
				else
				{
					HI_ERR_DISP("Invalid Mode %d\n",stCgmsCfg.enMode);
					return HI_ERR_DISP_INVALID_PARA;
				}

			}
			break;
		case HI_DRV_DISP_FMT_576P_50:
			{
				if (stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_FREELY)
				{
					u32Data = 0x0008;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NO_MORE)
				{
					u32Data = 0x2008;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_ONCE)
				{
					u32Data = 0x1008;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NEVER)
				{
					u32Data = 0x3008;
				}
				else
				{
					HI_ERR_DISP("Invalid Mode %d\n",stCgmsCfg.enMode);
					return HI_ERR_DISP_INVALID_PARA;
				}

			}
			break;
		case HI_DRV_DISP_FMT_NTSC:
		case HI_DRV_DISP_FMT_NTSC_J:
			{
				if (stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_FREELY)
				{
					u32Data = 0x88003;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NO_MORE)
				{
					u32Data = 0x28083;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_ONCE)
				{
					u32Data = 0xd8043;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NEVER)
				{
					u32Data = 0x780c3;
				}
				else
				{
					HI_ERR_DISP("Invalid Mode %d\n",stCgmsCfg.enMode);
					return HI_ERR_DISP_INVALID_PARA;
				}

			}
			break;
		case HI_DRV_DISP_FMT_PAL:
		case HI_DRV_DISP_FMT_PAL_N:
		case HI_DRV_DISP_FMT_PAL_Nc:
			{
				if (stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_FREELY)
				{
					u32Data = 0x0008;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NO_MORE)
				{
					u32Data = 0x2008;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_ONCE)
				{
					u32Data = 0x1008;
				}
				else if(stCgmsCfg.enMode == HI_DRV_DISP_CGMSA_COPY_NEVER)
				{
					u32Data = 0x3008;
				}
				else
				{
					HI_ERR_DISP("Invalid Mode %d\n",stCgmsCfg.enMode);
					return HI_ERR_DISP_INVALID_PARA;
				}

			}
			break;
		default:
			HI_ERR_DISP("Invalid format %d \n",enFormat);
			return HI_ERR_DISP_INVALID_PARA;

	}

	if (enFormat == HI_DRV_DISP_FMT_PAL_N
			|| enFormat == HI_DRV_DISP_FMT_PAL_Nc
			|| enFormat == HI_DRV_DISP_FMT_PAL)
	{
		SDATE_HDATE_VBI_SetWssData(enChannel,u32Data);
	}
	else
	{
		SDATE_HDATE_VBI_SetCgmsTypeA(enChannel,u32Data);
	}

	return HI_SUCCESS;
}

HI_S32 DISP_CGMS_SetTypeB(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
	HI_ERR_DISP("CGMS_B is unsupported\n",enFormat);

	return HI_ERR_DISP_INVALID_OPT;
}

HI_S32 DRV_CGMS_Set(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
	if (enFormat >= HI_DRV_DISP_FMT_BUTT)
	{
		HI_ERR_DISP("Invalid format %d\n",enFormat);
		return HI_ERR_DISP_INVALID_PARA;
	}

	if (stCgmsCfg.enType >= HI_DRV_DISP_CGMSA_TYPE_BUTT)
	{
		HI_ERR_DISP("Invalid Type %d\n",stCgmsCfg.enType);
		return HI_ERR_DISP_INVALID_PARA;
	}

	if (stCgmsCfg.enMode >= HI_DRV_DISP_CGMSA_MODE_BUTT)
	{
		HI_ERR_DISP("Invalid Mode %d\n",stCgmsCfg.enMode);
		return HI_ERR_DISP_INVALID_PARA;
	}

	if (stCgmsCfg.enMode == pstCgms->enMode
			&& stCgmsCfg.enType == pstCgms->enType
			&& stCgmsCfg.bEnable == pstCgms->bEnable
			&& enFormat == pstCgms->enCurFormat)
	{
		return HI_SUCCESS;
	}

	DISP_CGMS_SetEnable(pstCgms,enFormat,stCgmsCfg);

	if (stCgmsCfg.bEnable == HI_FALSE)
	{
		pstCgms->enMode = stCgmsCfg.enMode;
		pstCgms->enType = stCgmsCfg.enType;
		pstCgms->bEnable = stCgmsCfg.bEnable;
		pstCgms->enCurFormat = enFormat;

		return HI_SUCCESS;
	}

	if (stCgmsCfg.enType == HI_DRV_DISP_CGMSA_A)
	{
		(HI_VOID)DISP_CGMS_SetTypeA(pstCgms,enFormat,stCgmsCfg);
	}
	else
	{
		HI_ERR_DISP("Type %d can't be supported\n",stCgmsCfg.enType);

		return HI_ERR_DISP_INVALID_OPT;
	}

	pstCgms->enMode = stCgmsCfg.enMode;
	pstCgms->enType = stCgmsCfg.enType;
	pstCgms->bEnable = stCgmsCfg.bEnable;
	pstCgms->enCurFormat = enFormat;

	return HI_SUCCESS;
}


HI_S32 DRV_CGMS_Get(DISP_CGMS_INFO_S *pstCgms,DISP_CGMS_STATE_S *pstCurState)
{
    CgmsCheckNullPointer(pstCgms);

	pstCurState->bEnable = pstCgms->bEnable;

	pstCurState->enAttachedDisp = pstCgms->enAttachedDisp;

	pstCurState->enType = pstCgms->enType;

	pstCurState->enMode = pstCgms->enMode;

	return HI_SUCCESS;
}
#else
HI_S32 DRV_CGMS_Init(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_FMT_E enFmt,DISP_CGMS_INFO_S *pstCgms)
{
	return HI_SUCCESS;
}

HI_S32 DRV_CGMS_DeInit(DISP_CGMS_INFO_S *pstCgms)
{
	return HI_SUCCESS;
}

HI_S32 DRV_CGMS_Set(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
	return HI_SUCCESS;
}

HI_S32 DRV_CGMS_Get(DISP_CGMS_INFO_S *pstCgms,DISP_CGMS_STATE_S *pstCurState)
{
	return HI_SUCCESS;
}
#endif
