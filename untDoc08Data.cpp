//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------
#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)


classDOC08Data *e08DataAlpha;
classDOC08Data *e08DataAIOCR;

//---------------------------------------------------------------------------
classDOC08Data::classDOC08Data()
{
}
//---------------------------------------------------------------------------
classDOC08Data::~classDOC08Data()
{
	OutputDebugStringA("~DOC08Data\n");
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcClearVector()
{
	funcFreeImageInfo();

	m_nHistoryCount = 0;//m_vHISTORY.size()
	m_nOwnInfoCount = 0;//m_vOWNINFONAME.size()
	m_nShareOwnCount = 0;//m_vSHAREOWNNAME.size()//#SHAREOWN#

	//push_back할 곳에서 처리한다//m_vOldLandDocInfo.clear();
	m_ResultDoc08His.clear();
	m_ResultDoc08OwnInfo.clear();
	m_ResultDoc08ShareOwn.clear();

//#한글화편집#DirectTable//
	m_ResultDoc08_History.clear();
	m_ResultDoc08_HistoryStat.clear();


	m_vLAND.clear();
	m_vJIBUN.clear();
	m_vLEVEL.clear();//241203//#등급#추가//
	m_vMEMO.clear();
	m_vCAUTION.clear();

	m_vJIMOK.clear();
	m_vAREA.clear();
	m_vVALUE1.clear();
	m_vVALUE2.clear();
	m_vHISTORY.clear();
	m_vOWNINFODATE.clear();
	m_vOWNINFOREASON.clear();
	m_vOWNINFOADDRESS.clear();
	m_vOWNINFONAME.clear();

	m_vSHAREOWNDATE.clear();
	m_vSHAREOWNREASON.clear();
	m_vSHAREOWNRATIO.clear();
	m_vSHAREOWNADDRESS.clear();
	m_vSHAREOWNNAME.clear();
	m_vSHARECOMMENT.clear();

	m_asLand		= "";
	m_asJibun		= "";
	m_asLevel		= "";//241203//#등급#//
	m_asMemo		= "";
	m_asCaution		= "";

	m_asJimok		= "";
	m_asArea		= "";
	m_asValue1		= "";
	m_asValue2		= "";
	m_asHistory		= "";
	m_asOwnInfoDate   	= "";
	m_asOwnInfoReason	= "";
	m_asOwnInfoAddress	= "";
	m_asOwnInfoName   	= "";

	m_asShareOwnDate   	= "";
	m_asShareOwnReason	= "";
	m_asShareOwnRatio	= "";
	m_asShareOwnAddress	= "";
	m_asShareOwnName   	= "";
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcAssignImageInfo(GetImageInfo _imgInfo)
{
	memset(&mGetImageInfo, 0x00, sizeof(GetImageInfo));
	mGetImageInfo = _imgInfo;
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcFreeImageInfo()
{
	memset(&mGetImageInfo, 0x00, sizeof(GetImageInfo));
}
//---------------------------------------------------------------------------

//구대장-기본정보//
void __fastcall classDOC08Data::funcProcessDataInfo()
{
	//==============================================================
	if(m_vOldLandDocInfo.size() > 0)
	{
		AnsiString  asStr	= "";
		int nPos = frmMain->funcGetJibunPos(frmMain->m_asLandNm);
		if(nPos > 0)
		{
			if(m_nDOCKIND == 0)//토지대장//
			{
				asStr		= frmMain->m_asLandNm.SubString(1, nPos-1);
				m_asLand	= asStr;//211206//개행해서 사용할 것임//m_asLand	= StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
				m_asJibun	= frmMain->m_asLandNm.SubString(nPos, frmMain->m_asLandNm.Length() - nPos+1);
			}
			else if(m_nDOCKIND == 1)//임야대장//
			{
				asStr		= frmMain->m_asLandNm.SubString(1, nPos-2-1);//'산' 보정//
				m_asLand	= asStr;//211206//개행해서 사용할 것임//StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
				m_asJibun	= frmMain->m_asLandNm.SubString(nPos-1, frmMain->m_asLandNm.Length() - nPos+2);
			}

			//231116//마지막 공백으로 인해, slData->Count 오류발생하여 nStartW 위치 오류발생하여 추가//
			if(m_asLand.SubString(m_asLand.Length(), 1) == " ")
				m_asLand = m_asLand.SubString(1, m_asLand.Length()-1);
		}
		m_asLevel	= m_vOldLandDocInfo[0].LEVEL;//241203//#등급#추가//
		m_asMemo	= m_vOldLandDocInfo[0].MEMO;
		m_asCaution	= "본 인쇄물은 참고자료로 법적 효력이 없습니다.";
	}
}
//---------------------------------------------------------------------------

TScale __fastcall classDOC08Data::funcGetRealScaleToScreenScale(TScale gWH)
{
	TScale tScale;
	tScale.w	= (int)((double)gWH.w * (double)frmMain->m_dDocFactor);
	tScale.h	= (int)((double)gWH.h * (double)frmMain->m_dDocFactor);

	return tScale;
}
//---------------------------------------------------------------------------

TScale __fastcall classDOC08Data::funcGetScreenScaleToRealScale(TScale tWH)
{
	TScale gScale;
	gScale.w	= (int)((double)tWH.w / (double)frmMain->m_dDocFactor);
	gScale.h	= (int)((double)tWH.h / (double)frmMain->m_dDocFactor);

	return gScale;
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcProcessDataHis()
{
	AnsiString  asStr		= "";
	AnsiString  asJimok		= "";
	AnsiString  asArea		= "";
	AnsiString  asValue1	= "";
	AnsiString  asValue2	= "";
	AnsiString  asHistory	= "";
	AnsiString  asUnit		= "";
	bool		bUnit		= false;

	m_asJimok		= "";
	m_asArea		= "";
	m_asValue1	= "";
	m_asValue2	= "";
	m_asHistory	= "";

	for(int i = 0; i < (int)m_ResultDoc08His.size(); i++)
	{
		if( i != 0 )
		{
			m_asJimok		= m_asJimok + "/";
			m_asArea		= m_asArea	+ "/";
			m_asValue1	= m_asValue1 + "/";
			m_asValue2	= m_asValue2 + "/";
			m_asHistory	= m_asHistory + "/";
		}
		//
		asJimok	= (char*)m_ResultDoc08His[i].JIMOK;
		if( asJimok.IsEmpty() )
			asJimok = "-";
		m_asJimok	= m_asJimok + asJimok;
		//
		asArea	= (char*)m_ResultDoc08His[i].AREA;
		if( asArea.IsEmpty() )
		{
			asArea = "-";
        }

		m_asArea	= m_asArea + asArea;
		//
		asValue1	= (char*)m_ResultDoc08His[i].VALUE1;
		if( asValue1.IsEmpty() )
			asValue1 = "-";
		m_asValue1	= m_asValue1 + asValue1;
		//
		asValue2	= (char*)m_ResultDoc08His[i].VALUE2;
		if( asValue2.IsEmpty() )
			asValue2 = "-";
		m_asValue2	= m_asValue2 + asValue2;
		//
		asHistory	= (char*)m_ResultDoc08His[i].HISTORY;
		if( asHistory.IsEmpty() )
			asHistory = "-";
		m_asHistory	= m_asHistory + asHistory;
	}
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcProcessDataOwnInfo()
{
	AnsiString asStr		= "";
	AnsiString asDate		= "";
	AnsiString asReason		= "";
	AnsiString asAddress	= "";
	AnsiString asName		= "";

	m_asOwnInfoDate   	= "";
	m_asOwnInfoReason	= "";
	m_asOwnInfoAddress	= "";
	m_asOwnInfoName   	= "";

	for(int i = 0; i < (int)m_ResultDoc08OwnInfo.size(); i++)
	{
		if( !m_asOwnInfoDate.IsEmpty() )
			m_asOwnInfoDate	= m_asOwnInfoDate	+ "/";
		if( !m_asOwnInfoReason.IsEmpty() )
			m_asOwnInfoReason	= m_asOwnInfoReason	+ "/";
		if( !m_asOwnInfoAddress.IsEmpty() )
			m_asOwnInfoAddress	= m_asOwnInfoAddress	+ "/";
		if( !m_asOwnInfoName.IsEmpty() )
			m_asOwnInfoName	= m_asOwnInfoName	+ "/";

		//소유자-년월일
		asStr	= eFunc->funcGetKindCodeToKindName(801, (char*)m_ResultDoc08OwnInfo[i].ERA_CODE);
		asDate  = (char*)m_ResultDoc08OwnInfo[i].HIS_DATE;
		if(asStr == "서기")
			asDate	= asDate;
		else
			asDate	= asStr + asDate;

		if( asDate.IsEmpty() )
			asDate = "-";
		m_asOwnInfoDate	= m_asOwnInfoDate + asDate;
		//소유자-사고
		asReason  	= (char*)m_ResultDoc08OwnInfo[i].REASON;
		if( asReason.IsEmpty() )
			asReason = "-";
		m_asOwnInfoReason	= m_asOwnInfoReason + asReason;
		//소유자-주소
		asAddress	= (char*)m_ResultDoc08OwnInfo[i].OWN_ADDRESS;
		if( asAddress.IsEmpty() )
			asAddress = "-";
		m_asOwnInfoAddress	= m_asOwnInfoAddress + asAddress;
		//소유자-성명
		asName  	= (char*)m_ResultDoc08OwnInfo[i].OWN_NAME;
		if( asName.IsEmpty() )
			asName = "-";
		m_asOwnInfoName	= m_asOwnInfoName + asName;
	}
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcProcessDataShareOwn()
{
	AnsiString asStr		= "";
	AnsiString asDate		= "";
	AnsiString asReason		= "";
	AnsiString asRatio		= "";
	AnsiString asAddress	= "";
	AnsiString asName		= "";

	m_asShareOwnDate   	= "";
	m_asShareOwnReason	= "";
	m_asShareOwnRatio		= "";
	m_asShareOwnAddress	= "";
	m_asShareOwnName   	= "";

	for(int i = 0; i < (int)m_ResultDoc08ShareOwn.size(); i++)
	{
		if( !m_asShareOwnDate.IsEmpty() )
			m_asShareOwnDate	= m_asShareOwnDate	+ "/";
		if( !m_asShareOwnReason.IsEmpty() )
			m_asShareOwnReason	= m_asShareOwnReason	+ "/";
		if( !m_asShareOwnRatio.IsEmpty() )
			m_asShareOwnRatio	= m_asShareOwnRatio	+ "/";
		if( !m_asShareOwnAddress.IsEmpty() )
			m_asShareOwnAddress	= m_asShareOwnAddress	+ "/";
		if( !m_asShareOwnName.IsEmpty() )
			m_asShareOwnName	= m_asShareOwnName	+ "/";

		//소유자-년월일
		asStr	= eFunc->funcGetKindCodeToKindName(801, (char*)m_ResultDoc08ShareOwn[i].ERA_CODE);
		asDate  = (char*)m_ResultDoc08ShareOwn[i].HIS_DATE;
		if(asStr == "서기")
			asDate	= asDate;
		else
			asDate	= asStr + asDate;
//		asDate  = frmMain->funcChangeDateFormatString(3, (char*)m_ResultDoc08ShareOwn[i].HIS_DATE);
//		if(asStr == "서기")
//			asDate	= asDate;
//		else
//			asDate	= asStr + asDate;

		if( asDate.IsEmpty() )
			asDate = "-";
		m_asShareOwnDate	= m_asShareOwnDate + asDate;
		//소유자-사고
		asReason  	= (char*)m_ResultDoc08ShareOwn[i].REASON;
		if( asReason.IsEmpty() )
			asReason = "-";
		m_asShareOwnReason	= m_asShareOwnReason + asReason;
		//소유자-사고
		asRatio  	= (char*)m_ResultDoc08ShareOwn[i].RATIO;
		if( asRatio.IsEmpty() )
			asRatio = "-";
		m_asShareOwnRatio	= m_asShareOwnRatio + asRatio;
		//소유자-주소
		asAddress	= (char*)m_ResultDoc08ShareOwn[i].OWN_ADDRESS;
		if( asAddress.IsEmpty() )
			asAddress = "-";
		m_asShareOwnAddress	= m_asShareOwnAddress + asAddress;
		//소유자-성명
		asName  	= (char*)m_ResultDoc08ShareOwn[i].OWN_NAME;
		if( asName.IsEmpty() )
			asName = "-";
		m_asShareOwnName	= m_asShareOwnName + asName;
	}
	//===========================================================
}
//---------------------------------------------------------------------------

//=================================================================
//부책:구대장 [오버랩] 항목별 위치//
//=================================================================
void __fastcall classDOC08Data::funcGetDoc8ViewBoundary(GetImageInfo _imgInfo)
{
	funcAssignImageInfo(_imgInfo);

	GPoint		gPoint;
	TScale		gScale;
	TScale		tScale;
	double		nRate = 1.0;

//260630//
//	if( frmMain->m_bAIOCR )//AIOCR 번역본//
//		nRate = 0.5;

	//===========================================================================
	frmMain->bpMiddleW	= mGetImageInfo.nImageWidth * 0.030755;

	//===========================================================================
	gPoint.x  	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.1624;
	gScale.w	= mGetImageInfo.nImageWidth * 0.0362;
	gScale.h	= mGetImageInfo.nImageHeight * 0.1114;//350;
	m_bpDoc8OwnInfo[0].gLT	= gPoint;
	m_bpDoc8OwnInfo[0].gWH	= gScale;
	m_bpDoc8OwnInfo[0].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[0].gLT);
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.3184;
	gScale.h 	= mGetImageInfo.nImageHeight * 0.1910;//600;
	m_bpDoc8OwnInfo[1].gLT	= gPoint;
	m_bpDoc8OwnInfo[1].gWH	= gScale;
	m_bpDoc8OwnInfo[1].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[1].gLT);
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.7705;
	gScale.h 	= mGetImageInfo.nImageHeight * 0.1770;//556;
	m_bpDoc8OwnInfo[2].gLT	= gPoint;
	m_bpDoc8OwnInfo[2].gWH	= gScale;
	m_bpDoc8OwnInfo[2].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[2].gLT);
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.0905 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.9583;
	m_bpDoc8OwnInfo[12].gLT	= gPoint;
	m_bpDoc8OwnInfo[12].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[12].gLT);
	//===========================================================================
	gPoint.x  	= mGetImageInfo.nImageWidth * 0.7938 * nRate;
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.1051;
	gScale.w  	= mGetImageInfo.nImageWidth * 0.0554;//244;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0439;//138;
	m_bpDoc8OwnInfo[3].gLT	= gPoint;
	m_bpDoc8OwnInfo[3].gWH	= gScale;
	m_bpDoc8OwnInfo[3].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[3].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.1490;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.1044;//328;
	m_bpDoc8OwnInfo[4].gLT	= gPoint;
	m_bpDoc8OwnInfo[4].gWH	= gScale;
	m_bpDoc8OwnInfo[4].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[4].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.2534;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0700;//220;
	m_bpDoc8OwnInfo[5].gLT	= gPoint;
	m_bpDoc8OwnInfo[5].gWH	= gScale;
	m_bpDoc8OwnInfo[5].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[5].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.3235;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0445;//140;
	m_bpDoc8OwnInfo[6].gLT	= gPoint;
	m_bpDoc8OwnInfo[6].gWH	= gScale;
	m_bpDoc8OwnInfo[6].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[6].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.3680;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.2292;//720;
	m_bpDoc8OwnInfo[7].gLT	= gPoint;
	m_bpDoc8OwnInfo[7].gWH	= gScale;
	m_bpDoc8OwnInfo[7].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[7].gLT);
	//===========================================================================
	gPoint.x  	= mGetImageInfo.nImageWidth * 0.8141 * nRate;
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.5973;
	gScale.w 	= mGetImageInfo.nImageWidth * 0.030077;//여기만 5자리//소수5자리의 7값이 차지하는 pixel이 큼//
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0649;//204;
	m_bpDoc8OwnInfo[8].gLT	= gPoint;
	m_bpDoc8OwnInfo[8].gWH	= gScale;
	m_bpDoc8OwnInfo[8].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[8].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.6622;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0636;//200;
	m_bpDoc8OwnInfo[9].gLT	= gPoint;
	m_bpDoc8OwnInfo[9].gWH	= gScale;
	m_bpDoc8OwnInfo[9].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[9].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.7259;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.1248;//392;
	m_bpDoc8OwnInfo[10].gLT	= gPoint;
	m_bpDoc8OwnInfo[10].gWH	= gScale;
	m_bpDoc8OwnInfo[10].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[10].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.8507;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.1076;//338;
	m_bpDoc8OwnInfo[11].gLT	= gPoint;
	m_bpDoc8OwnInfo[11].gWH	= gScale;
	m_bpDoc8OwnInfo[11].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[11].gLT);
	//===========================================================================
	//241203//#등급#추가//
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.5000;
	gScale.h 	= mGetImageInfo.nImageHeight * 0.1770;//556;
	m_bpDoc8OwnInfo[13].gLT	= gPoint;
	m_bpDoc8OwnInfo[13].gWH	= gScale;
	m_bpDoc8OwnInfo[13].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[13].gLT);
	//===========================================================================
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcSetDoc8ViewBoundary()
{
	for(int i = 0; i < 13; i++)
		m_bpDoc8OwnInfo[i].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[i].gLT);
}
//---------------------------------------------------------------------------

//=================================================================
//부책:공유지연명부 [오버랩] 항목별 위치//
//=================================================================
void __fastcall classDOC08Data::funcGetDoc8ViewBoundaryShare(GetImageInfo _imgInfo)
{
	funcAssignImageInfo(_imgInfo);

	GPoint		gPoint;
	TScale		gScale;
	TScale		tScale;
	double		nRate = 1.0;

	if( frmMain->m_bAIOCR )//AIOCR 번역본//
		nRate = 0.5;

	//===========================================================================
	frmMain->bpMiddleW	= mGetImageInfo.nImageWidth * 0.030755;

	//===========================================================================
	gPoint.x  	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.1624;
	gScale.w	= mGetImageInfo.nImageWidth * 0.0362;
	gScale.h	= mGetImageInfo.nImageHeight * 0.1114;//350;
	m_bpDoc8ShareOwn[0].gLT	= gPoint;
	m_bpDoc8ShareOwn[0].gWH	= gScale;
	m_bpDoc8ShareOwn[0].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[0].gLT);
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.3184;
	gScale.h 	= mGetImageInfo.nImageHeight * 0.1910;//600;
	m_bpDoc8ShareOwn[1].gLT	= gPoint;
	m_bpDoc8ShareOwn[1].gWH	= gScale;
	m_bpDoc8ShareOwn[1].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[1].gLT);
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.6000;//231203//0.7705;
	gScale.h 	= mGetImageInfo.nImageHeight * 0.1770;//556;
	m_bpDoc8ShareOwn[2].gLT	= gPoint;
	m_bpDoc8ShareOwn[2].gWH	= gScale;
	m_bpDoc8ShareOwn[2].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[2].gLT);
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.08600 * nRate;//231121//0.0905;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.9583;
	m_bpDoc8ShareOwn[8].gLT	= gPoint;
	m_bpDoc8ShareOwn[8].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[8].gLT);
	//===========================================================================
	//231205//Add Comment Position//
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.3000 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.9583;
	gScale.w	= mGetImageInfo.nImageWidth * 0.4250;
	gScale.h	= mGetImageInfo.nImageHeight * 0.0100;
	m_bpDoc8ShareOwn[9].gLT	= gPoint;
	m_bpDoc8ShareOwn[9].gWH	= gScale;
	m_bpDoc8ShareOwn[9].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[9].gLT);
	//===========================================================================
	//231205//Add DeleteLine Position//가변적//
//	gPoint.x 	= mGetImageInfo.nImageWidth * 0.3111;
//	gPoint.y 	= mGetImageInfo.nImageHeight * 0.9583;
//	gScale.w	= mGetImageInfo.nImageWidth * 0.8800;
//	gScale.h	= mGetImageInfo.nImageHeight * 0.0500;//350;
//	m_bpDoc8ShareOwn[10].gLT	= gPoint;
//	m_bpDoc8ShareOwn[10].gWH	= gScale;
//	m_bpDoc8ShareOwn[10].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[9].gLT);
	//===========================================================================

	gPoint.x  	= mGetImageInfo.nImageWidth * 0.8238 * nRate;//231121//7938;
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.0857;//231120//1044;
	gScale.w  	= mGetImageInfo.nImageWidth * 0.0300;//231120//03074;//여기만 5자리//소수5자리의 7값이 차지하는 pixel이 큼//
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0649;
	m_bpDoc8ShareOwn[3].gLT	= gPoint;
	m_bpDoc8ShareOwn[3].gWH	= gScale;
	m_bpDoc8ShareOwn[3].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[3].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.1506;//231120//1693;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0649;
	m_bpDoc8ShareOwn[4].gLT	= gPoint;
	m_bpDoc8ShareOwn[4].gWH	= gScale;
	m_bpDoc8ShareOwn[4].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[4].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.2155;//231120//2342;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.0432;
	m_bpDoc8ShareOwn[5].gLT	= gPoint;
	m_bpDoc8ShareOwn[5].gWH	= gScale;
	m_bpDoc8ShareOwn[5].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[5].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.2587;//231120//2774;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.1248;
	m_bpDoc8ShareOwn[6].gLT	= gPoint;
	m_bpDoc8ShareOwn[6].gWH	= gScale;
	m_bpDoc8ShareOwn[6].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[6].gLT);
	//===========================================================================
	gPoint.y  	= mGetImageInfo.nImageHeight * 0.3835;//231120//4022;
	gScale.h  	= mGetImageInfo.nImageHeight * 0.1076;
	m_bpDoc8ShareOwn[7].gLT	= gPoint;
	m_bpDoc8ShareOwn[7].gWH	= gScale;
	m_bpDoc8ShareOwn[7].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[7].gLT);
	//===========================================================================

	//===========================================================================
	//241203//#등급#추가//
	//===========================================================================
	gPoint.x 	= mGetImageInfo.nImageWidth * 0.8797 * nRate;
	gPoint.y 	= mGetImageInfo.nImageHeight * 0.5100;
	gScale.h 	= mGetImageInfo.nImageHeight * 0.1500;
	m_bpDoc8ShareOwn[10].gLT	= gPoint;
	m_bpDoc8ShareOwn[10].gWH	= gScale;
	m_bpDoc8ShareOwn[10].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[10].gLT);
	//===========================================================================



	m_nTopBottomGap	= mGetImageInfo.nImageHeight * (0.0857 + 0.3650);//231121//(0.0857 + 0.4134);
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcSetDoc8ViewBoundaryShare()
{
	for(int i = 0; i < DOC08_SHAREOWN_CNT; i++)//241203//#등급#추가//
		m_bpDoc8ShareOwn[i].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[i].gLT);
}
//---------------------------------------------------------------------------


int __fastcall classDOC08Data::funcGetStartW(int _nType, int _nIndex, int _nCount, int _nTextW)
{
	TPoint	tPoint;
	TScale  tScale;
	int nMiddleWidth	= frmAlphaDoc8->m_nMiddleWidth * frmMain->m_dDocFactor;
	int nStartW    = 0;

	//==========================================================================================
	tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[_nType].gLT);
	tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[_nType].gWH);
	//==========================================================================================

	if(_nType <= 2)//동리, 지번//
	{
		nStartW    = tPoint.x + tScale.w - ((tScale.w - _nCount * _nTextW)/2);//세로쓰기-중간//
	}
	else if(_nType == 2 && _nCount > 0)//적요(괄호내용)//
	{
		nStartW    = tPoint.x + (tScale.w - _nTextW) / 2;//세로쓰기-중간//
	}
	else if(_nType == 10 && _nCount > 0)//241203//#등급#추가//
	{
		nStartW    = tPoint.x + (tScale.w - _nTextW) / 2;//세로쓰기-중간//
	}
	else if(_nType == 9)//주석//
	{
		if(_nIndex < 5)
			nStartW    = tPoint.x;//가로쓰기//
		else
			nStartW    = tPoint.x + tScale.w / 2;//가로쓰기//
	}
	else
	{
		if(frmMain->m_asFormatType == "A")
		{
			if(_nType != 5)//RATIO 외 항목//
			{
				if(_nIndex < 11)//[11 CELL]//index 11, 12은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - (_nIndex-1) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 24)//[11 CELL]//index 24, 25은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - ((_nIndex-1) - 13) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 26 && _nIndex < 39)//[13 CELL]//
					nStartW = tPoint.x - ((_nIndex-1) - 15) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 52)//[13 CELL]//
					nStartW = tPoint.x - ((_nIndex-1) - 28) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
			}
			else//RATIO//
			{
				if(_nIndex < 11)//[11 CELL]//index 11, 12은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - _nIndex * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 24)//[11 CELL]//index 24, 25은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - (_nIndex - 13) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 26 && _nIndex < 39)//[13 CELL]//
					nStartW = tPoint.x - (_nIndex - 15) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 52)//[13 CELL]//
					nStartW = tPoint.x - (_nIndex - 29) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
			}

			if(_nIndex >= 26)
				nStartW    -= nMiddleWidth;
		}
		else if(frmMain->m_asFormatType == "B")
		{
			if(_nType != 5)//RATIO 외 항목//
			{
				if(_nIndex < 13)
					nStartW = tPoint.x - (_nIndex-1) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 38)
					nStartW = tPoint.x - ((_nIndex-1) - 13) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 51)
					nStartW = tPoint.x - ((_nIndex-1) - 26) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
			}
			else
			{
				if(_nIndex < 13)
					nStartW = tPoint.x - _nIndex * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 38)
					nStartW = tPoint.x - (_nIndex - 13) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 51)
					nStartW = tPoint.x - (_nIndex - 26) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
			}

			if(_nIndex >= 26)
				nStartW    -= nMiddleWidth;

			if(_nIndex % 2)//공유지연명부B Width=165.4로 애매하므로 두 개의 Cell 마다 1 pixcel 보정//
			{
				nStartW -= 1;
			}
		}
	}

	return nStartW;
}
//---------------------------------------------------------------------------

int __fastcall classDOC08Data::funcGetStartH(int _nType, int _nIndex, int _nCount, int _nTextH)
{
	TPoint	tPoint;
	TScale  tScale;
	int nStartH    = 0;
	int nTopBottomGap = (int)((double)m_nTopBottomGap * (double)frmMain->m_dDocFactor);//231205//(double)(m_nTopBottomGap - this->realTop) * frmMain->m_dDocFactor;

	//==========================================================================================
	tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[_nType].gLT);
	tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[_nType].gWH);
	//==========================================================================================

	if(_nType == 0 || _nType == 1)//동리, 지번//
	{
		nStartH    = tPoint.y + (tScale.h - _nTextH) / 2;//중간
	}
	else if(_nType == 2)//적요//
	{
		nStartH    = tPoint.y;//231204//상단// + (tScale.h - _nTextH) / 2;//중간//
	}
	else if(_nType == 10)//241203//#등급#추가//
	{
		nStartH    = tPoint.y;
	}
	else if(_nType == 9)//주석//
	{
		if(_nIndex < 5)
			nStartH    = tPoint.y + tScale.h * _nIndex;//가로쓰기//
		else
			nStartH    = tPoint.y + tScale.h * (_nIndex-5);//가로쓰기//
	}
	else
	{
		if(frmMain->m_asFormatType == "A")
		{
			if(_nType == 5)//RATIO//
			{
				if(_nIndex < 11 || (_nIndex >= 26 && _nIndex < 39))
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2 + nTopBottomGap;//Grid2
			}
			else if(_nType == 6)//ADDRESS//
			{
				if(_nIndex < 11 || (_nIndex >= 26 && _nIndex < 39))
					nStartH = tPoint.y;//Grid1
				else
					nStartH = tPoint.y + nTopBottomGap;//Grid2
			}
			else//RATIO, ADDRESS 외 항목//
			{
				if(_nIndex < 11 || (_nIndex >= 26 && _nIndex < 39))
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2 + nTopBottomGap;//Grid2
			}
		}
		else if(frmMain->m_asFormatType == "B")
		{
			if(_nType == 5)//RATIO//
			{
				if(_nIndex < 13 || (_nIndex >= 26 && _nIndex < 38))
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2 + nTopBottomGap;//Grid2
            }
			else if(_nType == 6)//ADDRESS//
			{
				if(_nIndex < 13 || (_nIndex >= 26 && _nIndex < 38))
					nStartH = tPoint.y;//Grid1
				else
					nStartH = tPoint.y + nTopBottomGap;//Grid2
			}
			else//RATIO, ADDRESS 외 항목//
			{
				if(_nIndex < 13 || (_nIndex >= 26 && _nIndex < 38))
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2 + nTopBottomGap;//Grid2
			}
		}
	}

	return nStartH;
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcDeleteOwnInfo()
{
	m_asJimok	= "";
	m_asArea	= "";
	m_asValue1	= "";
	m_asValue2	= "";
	m_asHistory	= "";
	m_asOwnInfoDate	= "";
	m_asOwnInfoReason	= "";
	m_asOwnInfoAddress	= "";
	m_asOwnInfoName	= "";
//======================================================================
//231118//#SHAREOWN#
//구대장 공유지연명부 소유자정보//
	m_asShareOwnDate	= "";
	m_asShareOwnReason	= "";
	m_asShareOwnRatio	= "";
	m_asShareOwnAddress	= "";
	m_asShareOwnName	= "";
//======================================================================

	m_vJIMOK.clear();
	m_vAREA.clear();
	m_vVALUE1.clear();
	m_vVALUE2.clear();
	m_vHISTORY.clear();
	m_vOWNINFODATE.clear();
	m_vOWNINFOREASON.clear();
	m_vOWNINFOADDRESS.clear();
	m_vOWNINFONAME.clear();
//======================================================================
//231118//#SHAREOWN#
//구대장 공유지연명부 소유자정보//
	m_vSHAREOWNDATE.clear();
	m_vSHAREOWNREASON.clear();
	m_vSHAREOWNADDRESS.clear();
	m_vSHAREOWNNAME.clear();
	m_vSHARECOMMENT.clear();
//======================================================================
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcProcessOwnNames(bool _bSkipInfo)
{
	//---
	if(frmMain->m_asLandCd.Length() == 19)
	{
		frmMain->m_asLandNm  	= frmMain->func_ConvertLandcdToAddress(frmMain->m_asLandCd);

		if(frmMain->m_asLandCd.SubString(11, 1) == "1")//토지대장//
		{
			m_nDOCKIND	= 0;
		}
		else if(frmMain->m_asLandCd.SubString(11, 1) == "2")//임야대장//
		{
			m_nDOCKIND	= 1;
		}

		if( !_bSkipInfo )
			funcProcessDataInfo();
	}

	//---
	m_nHistoryCount	= m_ResultDoc08His.size();
	m_nOwnInfoCount	= m_ResultDoc08OwnInfo.size();
	m_nShareOwnCount	= m_ResultDoc08ShareOwn.size();

	funcDrawOwnInfo();
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcDrawOwnInfo()
{
	DATA_STRUCT		tempV;

	m_vLAND.clear();
	m_vJIBUN.clear();
	m_vLEVEL.clear();//241203//#등급#추가//
	m_vMEMO.clear();
	m_vCAUTION.clear();

	memset(&tempV, 0x00, sizeof(DATA_STRUCT));
	strcpy(tempV.DATA, m_asLand.c_str());
	m_vLAND.push_back(tempV);
	memset(&tempV, 0x00, sizeof(DATA_STRUCT));
	strcpy(tempV.DATA, m_asJibun.c_str());
	m_vJIBUN.push_back(tempV);

	//=======================================
	//241203//#등급#추가//
	//=======================================
	memset(&tempV, 0x00, sizeof(DATA_STRUCT));
	strcpy(tempV.DATA, m_asLevel.c_str());
	m_vLEVEL.push_back(tempV);
	//=======================================

	memset(&tempV, 0x00, sizeof(DATA_STRUCT));
	strcpy(tempV.DATA, m_asMemo.c_str());
	m_vMEMO.push_back(tempV);
	memset(&tempV, 0x00, sizeof(DATA_STRUCT));
	strcpy(tempV.DATA, m_asCaution.c_str());
	m_vCAUTION.push_back(tempV);

	//=================================================================
	//부책//
	//=================================================================
	if(frmMain->m_bSUBBOOK)
	{
		AnsiString 	asJimok 	= m_asJimok;
		AnsiString 	asArea 		= m_asArea;
		AnsiString 	asValue1 	= m_asValue1;
		AnsiString 	asValue2 	= m_asValue2;
		AnsiString 	asHistory 	= m_asHistory;
		AnsiString 	asDate		= m_asOwnInfoDate;
		AnsiString 	asReason 	= m_asOwnInfoReason;
		AnsiString 	asAddress 	= m_asOwnInfoAddress;
		AnsiString 	asName  	= m_asOwnInfoName;
		AnsiString 	asStr		= "";
		int 		nPos = 0;

		m_vJIMOK.clear();
		m_vAREA.clear();
		m_vVALUE1.clear();
		m_vVALUE2.clear();
		m_vHISTORY.clear();
		m_vOWNINFODATE.clear();
		m_vOWNINFOREASON.clear();
		m_vOWNINFOADDRESS.clear();
		m_vOWNINFONAME.clear();

		if( !asJimok.IsEmpty() )
		{
			int nCnt = 0;

			while(asJimok != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asJimok.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asJimok.SubString(1, nPos-1);
				}
				else{
					asStr = asJimok;
					nPos = asJimok.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vJIMOK.push_back(tempV);
				asJimok = asJimok.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt < (int)m_ResultDoc08His.size())
			{
				nCnt++;
				asStr = "";
				strcpy(tempV.DATA, asStr.c_str());
				m_vJIMOK.push_back(tempV);
			}

			if(nCnt == 0) return;
		}

		//AREA
		if( !asArea.IsEmpty() )
		{
			int nCnt = 0;

			while(asArea != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asArea.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asArea.SubString(1, nPos-1);
				}
				else
				{
					nCnt++;
					asStr = asArea;
					nPos = asArea.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vAREA.push_back(tempV);
				asArea = asArea.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt < (int)m_ResultDoc08His.size())
			{
				nCnt++;
				asStr = "";
				strcpy(tempV.DATA, asStr.c_str());
				m_vAREA.push_back(tempV);
			}

			if(nCnt == 0) return;
		}

		//VALUE
		if( !asValue1.IsEmpty() )
		{
			int nCnt = 0;

			while(asValue1 != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asValue1.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asValue1.SubString(1, nPos-1);
				}
				else{
					asStr = asValue1;
					nPos = asValue1.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vVALUE1.push_back(tempV);
				asValue1 = asValue1.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt < (int)m_ResultDoc08His.size())
			{
				nCnt++;
				asStr = "";
				strcpy(tempV.DATA, asStr.c_str());
				m_vVALUE1.push_back(tempV);
			}

			if(nCnt == 0) return;
		}

		//VALUE2
		if( !asValue2.IsEmpty() )
		{
			int nCnt = 0;

			while(asValue2 != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asValue2.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asValue2.SubString(1, nPos-1);
				}
				else{
					asStr = asValue2;
					nPos = asValue2.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vVALUE2.push_back(tempV);
				asValue2 = asValue2.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt < (int)m_ResultDoc08His.size())
			{
				nCnt++;
				asStr = "";
				strcpy(tempV.DATA, asStr.c_str());
				m_vVALUE2.push_back(tempV);
			}

			if(nCnt == 0) return;
		}

		//HISTORY
		if( !asHistory.IsEmpty() )
		{
			int nCnt = 0;

			while(asHistory != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asHistory.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asHistory.SubString(1, nPos-1);
				}
				else{
					asStr = asHistory;
					nPos = asHistory.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vHISTORY.push_back(tempV);
				asHistory = asHistory.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt == 0) return;
		}

		//DATE
		if( !m_asOwnInfoDate.IsEmpty() )
		{
			int nCnt = 0;

			while(asDate != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asDate.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asDate.SubString(1, nPos-1);
				}
				else{
					asStr = asDate;
					nPos = asDate.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vOWNINFODATE.push_back(tempV);
				asDate = asDate.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt == 0) return;
		}
		//REASON
		if( !m_asOwnInfoReason.IsEmpty() )
		{
			int nCnt = 0;

			while(asReason != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asReason.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asReason.SubString(1, nPos-1);
				}
				else{
					asStr = asReason;
					nPos = asReason.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vOWNINFOREASON.push_back(tempV);
				asReason = asReason.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt == 0) return;
		}
		//ADDRESS
		if( !m_asOwnInfoAddress.IsEmpty() )
		{
			int nCnt = 0;

			while(asAddress != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asAddress.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asAddress.SubString(1, nPos-1);
				}
				else{
					asStr = asAddress;
					nPos = asAddress.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vOWNINFOADDRESS.push_back(tempV);
				asAddress = asAddress.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt == 0) return;
		}
		//NAME
		if( !m_asOwnInfoName.IsEmpty() )
		{
			int nCnt = 0;

			while(asName != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asName.Pos("/");
				//==========================================================
				//#CODE_SIMPLIFY#//
				if(nPos){
					asStr = asName.SubString(1, nPos-1);
				}
				else{
					asStr = asName;
					nPos = asName.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vOWNINFONAME.push_back(tempV);
				asName = asName.Delete(1, nPos);
				//======================================================================
			}

			if(nCnt == 0) return;
		}
	}
//=============================================================================
//231118//#SHAREOWN//
//=============================================================================
	//=================================================================
	//공유지연명부//
	//=================================================================
	else
	{
		AnsiString 	asDate		= m_asShareOwnDate;
		AnsiString 	asReason 	= m_asShareOwnReason;
		AnsiString 	asRatio 	= m_asShareOwnRatio;
		AnsiString 	asAddress 	= m_asShareOwnAddress;
		AnsiString 	asName  	= m_asShareOwnName;
		AnsiString 	asStr		= "";
		int 		nPos = 0;

		//======================================================================
		//231118//#SHAREOWN#
		m_vSHAREOWNDATE.clear();
		m_vSHAREOWNREASON.clear();
		m_vSHAREOWNRATIO.clear();
		m_vSHAREOWNADDRESS.clear();
		m_vSHAREOWNNAME.clear();
		m_vSHARECOMMENT.clear();
		//======================================================================

		//======================================================================
		//DATE
		if( !m_asShareOwnDate.IsEmpty() )
		{
			AnsiString 	asDate		= m_asShareOwnDate;
			int nCnt = 0;

			while(asDate != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asDate.Pos("/");
				if(nPos){
					asStr = asDate.SubString(1, nPos-1);
				}
				else{
					asStr = asDate;
					nPos = asDate.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vSHAREOWNDATE.push_back(tempV);
				asDate = asDate.Delete(1, nPos);
			}

			if(nCnt == 0) return;
		}
		//REASON
		if( !m_asShareOwnReason.IsEmpty() )
		{
			AnsiString 	asReason 	= m_asShareOwnReason;
			int nCnt = 0;

			while(asReason != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asReason.Pos("/");
				if(nPos){
					asStr = asReason.SubString(1, nPos-1);
				}
				else{
					asStr = asReason;
					nPos = asReason.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vSHAREOWNREASON.push_back(tempV);
				asReason = asReason.Delete(1, nPos);
			}

			if(nCnt == 0) return;
		}
		//RATIO
		if( !m_asShareOwnRatio.IsEmpty() )
		{
			AnsiString 	asRatio 	= m_asShareOwnRatio;
			int nCnt = 0;

			while(asRatio != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asRatio.Pos("/");
				if(nPos){
					asStr = asRatio.SubString(1, nPos-1);
				}
				else{
					asStr = asRatio;
					nPos = asRatio.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vSHAREOWNRATIO.push_back(tempV);
				asRatio = asRatio.Delete(1, nPos);
			}

			if(nCnt == 0) return;
		}
		//ADDRESS
		if( !m_asShareOwnAddress.IsEmpty() )
		{
			AnsiString 	asAddress 	= m_asShareOwnAddress;
			int nCnt = 0;

			while(asAddress != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asAddress.Pos("/");
				if(nPos){
					asStr = asAddress.SubString(1, nPos-1);
				}
				else{
					asStr = asAddress;
					nPos = asAddress.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vSHAREOWNADDRESS.push_back(tempV);
				asAddress = asAddress.Delete(1, nPos);
			}

			if(nCnt == 0) return;
		}
		//NAME
		if( !m_asShareOwnName.IsEmpty() )
		{
			AnsiString 	asName  	= m_asShareOwnName;
			int nCnt = 0;

			while(asName != "")
			{
				memset(&tempV, 0x00, sizeof(DATA_STRUCT));

				nPos = asName.Pos("/");
				if(nPos){
					asStr = asName.SubString(1, nPos-1);
				}
				else{
					asStr = asName;
					nPos = asName.Length();
				}
				nCnt++;
				strcpy(tempV.DATA, asStr.c_str());
				m_vSHAREOWNNAME.push_back(tempV);
				asName = asName.Delete(1, nPos);
			}

			if(nCnt == 0) return;
		}
	}
}
//---------------------------------------------------------------------------

//======================================================================
// DOC08 번역 데이터를 표시//
//======================================================================
//- CreatePen(...): 선을 그릴 때 사용할 펜 객체를 생성합니다. 선 스타일, 두께, 색을 정합니다.
//- SelectObject(hdc, pen): 방금 만든 펜을 해당 DC에 장착합니다. 이 함수는 기존 펜 핸들을 반환하므로, 원래 펜으로 되돌리려면 반환값을 저장해야 합니다.
//- SetROP2(hdc, R2_COPYPEN): 펜이 화면에 그려질 때의 혼합 방식을 설정합니다. R2_COPYPEN은 보통 현재 펜 색으로 그대로 그리는 일반 모드입니다.
//- SetBkMode(hdc, TRANSPARENT): 글자 배경을 투명으로 처리합니다. 텍스트를 쓸 때 배경 사각형을 덮어쓰지 않게 합니다.
//- SetTextColor(hdc, cPenColor): 이후 출력되는 글자의 색을 설정합니다.
void __fastcall classDOC08Data::funcRedrawOwnInfo()
{
	int fontwidth		  = frmMain->m_nFontSize;
	int fontheight 		= fontwidth;
	int nMiddleWidth	= (int)((double)frmMain->bpMiddleW * (double)frmMain->m_dDocFactor);
	SHARP_POSITION_STRUCT	tempData;
	TPoint	tPoint;
	TScale  tScale;
	TPaintBox *pbRect;

	if( !frmMain->m_bAIOCR )//기구축DB 번역본//
		pbRect = frmMain->pbRect2;
	else//AIOCR 번역본//
		pbRect = frmMain->pbRect4;

	if(pbRect->Visible)
	{
		//##########################################################################################
		// 공통 사용 변수(PaintBox)
		//##########################################################################################
		HDC 	hdc 		= pbRect->Canvas->Handle;
		TColor	cPenColor 	= pbRect->Color;
		HFONT   font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		// 기본 펜 생성
		HPEN 	pen	    = ::CreatePen(PS_SOLID, 1, cPenColor);
		// 원래 GDI 객체 백업 저장 (폰트, 펜)
		HFONT 	oldFont = (HFONT)::SelectObject(hdc, font);
		HPEN 	oldPen  = (HPEN)::SelectObject(hdc, pen);

		//::SetBkMode(hdc, TRANSPARENT);

		//##########################################################################################
		// 공통 사용 변수(String, Position)
		//##########################################################################################
		AnsiString 	asData		= "";//한 셀 포함 문자//
		AnsiString 	asCaption 	= "";//TextOut에 표기할 문자//
		AnsiString 	asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		int 		nTxtLen 	= 0;
		bool		bPartSharp		= false;
		bool		bAllSharp		= false;//#1016//전체삭제-취소선//
		int 		nTextW			= 0;
		int 		nTextH			= 0;
		int			nStartW			= 0;
		int			nStartH			= 0;
		int			nSumH			= 0;
		int			nPartSharp1		= 0;
		int			nPartSharp2		= 0;
		int			nAllSharp1		= 0;
		int			nAllSharp2		= 0;
		//==============================================================


		//부분삭제선//여기에서만 초기화한다//
		m_vSharpPos.clear();


		//##########################################################################################
		//#
		//# CAUTION - 좌측하단 문구표시// 컬러 다름. 배경 흰색//
		//#
		//##########################################################################################
		{
			//==============================================================
			TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
			HPEN penC    = ::CreatePen(PS_SOLID, 1, cPenColorC);
		    HPEN oldPenC = (HPEN)::SelectObject(hdc, penC);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColorC);
			pbRect->Canvas->Brush->Color	= clWhite;

			//==============================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[12].gLT);
			int nTextW	= pbRect->Canvas->TextWidth(m_vCAUTION[0].DATA)+1;
			int nTextH	= pbRect->Canvas->TextHeight(m_vCAUTION[0].DATA)+1;
			m_vCAUTION[0].tRect.Left 		= tPoint.x;
			m_vCAUTION[0].tRect.Top 		= tPoint.y;
			m_vCAUTION[0].tRect.Right		= tPoint.x + nTextW;
			m_vCAUTION[0].tRect.Bottom	= tPoint.y + nTextH;

			//======================================================
			asCaption = (char*)m_vCAUTION[0].DATA;
			TextOutA(hdc, tPoint.x, tPoint.y, asCaption.c_str(), (int)asCaption.Length());

			//==============================================================
		    ::SelectObject(hdc, oldPenC);
			::SetROP2 (hdc, oldro);
			::DeleteObject( penC );
		}

		//##########################################################################################
		//#
		//# LAND, JIBUN, LEVEL, MEMO
		//#
		//##########################################################################################
		{
			//==============================================================
			//지번폰트크게//
			HFONT   fontL = ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
			HFONT   oldFontL = (HFONT)::SelectObject(hdc, fontL);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetTextColor(hdc, cPenColor);
			pbRect->Canvas->Brush->Color	= clWhite;

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;

			//=================================================
			//211206//읍면동명, 리명 구분하여 두 줄 처리//
			//======================================
			// LAND
			//======================================
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[0].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[0].gWH);
			//공통//
			nTextW	= pbRect->Canvas->TextWidth("동")+1;//임의글자로 체크//
			nTextH	= pbRect->Canvas->TextHeight("동")+1;//임의글자로 체크//
			//=========================================================

			if(m_asLand.Length() > 0)
			{
				m_asLand	= StringReplace(m_asLand, " ", "_", TReplaceFlags() << rfReplaceAll);
				asData = m_asLand;
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				//=================================================
				//211206//읍면동명, 리명 구분하여 두 줄 처리//
				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				int nPos	= asData.Pos("_");
				while(nPos > 0)
				{
					asTemp 	= asData.SubString(1, nPos-1);
					slData->Add(asTemp);
					asData  = asData.Delete(1, nPos);
					nPos	= asData.Pos("_");
				}
				slData->Add(asData);

				//==========================================================================================
				nStartW	= tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW) / 2);
				m_vLAND[0].tRect.Left		= nStartW - nTextW * slData->Count;
				m_vLAND[0].tRect.Right	= nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];
					nTxtLen = asData.Length();
					nSumH	= 0;
					//라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asData.SubString(j+1, 2);
							nSumH	+= pbRect->Canvas->TextHeight(asTemp);
							j++;
						}
						else
						{
							if(asData.c_str()[j] == '%')//부분삭제//
								continue;
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									nSumH	+= pbRect->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH	+= pbRect->Canvas->TextHeight(asCaption);
						}
					}

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumH) / 2;

					//==========================================================================================
					if(z == 0)
					{
						m_vLAND[0].tRect.Top 	= nStartH;
						m_vLAND[0].tRect.Bottom	= nStartH + nSumH;

						//==========================================================================================
						//minji@230310//사장님REQ//imgDoc08Mover->Left	= m_vLAND[0].tRect.Right + ;
						if( !frmMain->m_bAIOCR )//기구축DB 번역본//
						{
							frmMain->imgDoc08Mover->Left	= m_vLAND[0].tRect.Right + 32;//minji@230310//사장님REQ//
							frmMain->imgDoc08Mover->Top		= m_vLAND[0].tRect.Top;
						}
						else//AIOCR 번역본//
						{
							frmMain->imgDoc08Mover4->Left	= m_vLAND[0].tRect.Right + 32;//minji@230310//사장님REQ//
							frmMain->imgDoc08Mover4->Top	= m_vLAND[0].tRect.Top;
						}
						//==========================================================================================
					}
					else
					{
						if(m_vLAND[0].tRect.Top > nStartH)
							m_vLAND[0].tRect.Top = nStartH;
						if(m_vLAND[0].tRect.Bottom < nStartH + nSumH)
							m_vLAND[0].tRect.Bottom = nStartH + nSumH;
					}
					//=========================================================

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}

							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//==========================================================================================

					if(z == 0)
					{
						m_vLAND[0].tRect.Bottom	= nStartH + nTextH;
					}
					else
					{
						if(m_vLAND[0].tRect.Bottom < nStartH + nTextH)
							m_vLAND[0].tRect.Bottom = nStartH + nTextH;
					}
					//==========================================================================================
				}

				delete slData;
				slData	= NULL;
			}

			//======================================
			// JIBUN
			//======================================
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================

			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[1].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[1].gWH);
			//=========================================================

			if(m_asJibun.Length() > 0)
			{
				asData 	= m_asJibun;
				if(frmMain->m_nBonbuType == 1)
					asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				else if(frmMain->m_nBonbuType == 2)
					asData	= StringReplace(asData, "-", ".", TReplaceFlags() << rfReplaceAll);
				else if(frmMain->m_nBonbuType == 3)
					asData	= StringReplace(asData, "-", "/", TReplaceFlags() << rfReplaceAll);
				else if(frmMain->m_nBonbuType == 4)
					asData	= StringReplace(asData, "-", " - ", TReplaceFlags() << rfReplaceAll);
				else if(frmMain->m_nBonbuType == 5)
					asData	= StringReplace(asData, "-", " | ", TReplaceFlags() << rfReplaceAll);
				else if(frmMain->m_nBonbuType == 6)
					asData	= StringReplace(asData, "-", "의", TReplaceFlags() << rfReplaceAll);
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				for(int j = 0; j < nTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asTemp = asData.SubString(j+1, 2);
						nSumH	+= pbRect->Canvas->TextHeight(asTemp);
						j++;
					}
					else
					{
						asCaption = asData.SubString(j+1, 1);
						nSumH	+= pbRect->Canvas->TextHeight(asCaption);
					}
				}

				//실제 표시//
				//=========================================================
				nTextW	= pbRect->Canvas->TextWidth("번");//임의글자로 체크//
				nTextH	= pbRect->Canvas->TextHeight("번");//임의글자로 체크//
				nStartW	= tPoint.x + (tScale.w - nTextW) / 2;
				nStartH	= tPoint.y + (tScale.h - nSumH) / 2;
				//=========================================================

				//==========================================================================================
				m_vJIBUN[0].tRect.Left	= nStartW;
				m_vJIBUN[0].tRect.Right	= nStartW + nTextW;
				m_vJIBUN[0].tRect.Top		= nStartH;
				m_vJIBUN[0].tRect.Bottom	= nStartH + nSumH;
				//==========================================================================================

				for(int j = 0; j < nTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						j++;
					}
					else
					{
						asCaption = asData.SubString(j+1, 1);
						TextOutA(hdc, nStartW+nTextW/2, nStartH, asCaption.c_str(), (int)asCaption.Length());
					}
					nStartH	+= nTextH+1;
				}
			}

			::SetROP2 (hdc, oldro);
			::SelectObject(hdc, oldFontL );



			//==============================================================
			//211216//도청김훈곤주무관Req//지번폰트크게=>레벨,메모 표시할 때는 원복//
			oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetTextColor(hdc, cPenColor);
			//==============================================================

			//==============================================================
			//241203//#등급#//
			//==============================================================
			//======================================
			// LEVEL
			//======================================
			bAllSharp	= false;
	   		bPartSharp	= false;

			//==========================================================================================

			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[13].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[13].gWH);
			//=========================================================

			if(m_asLevel.Length() > 0)
			{
				asData = m_asLevel;
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
	//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
	//			int nPos	= asData.Pos("_");
	//			while(nPos > 0)
	//			{
	//				asTemp 	= asData.SubString(1, nPos-1);
	//				slData->Add(asTemp);
	//				asData  = asData.Delete(1, nPos);
	//				nPos	= asData.Pos("_");
	//			}
	//			if( !asData.IsEmpty() )
	//				slData->Add(asData);
				//공통//
				//=========================================================
				nTextW	= pbRect->Canvas->TextWidth("등")+1;//임의글자로 체크//
				nTextH	= pbRect->Canvas->TextHeight("등")+1;//임의글자로 체크//
				//=========================================================

				//개행없는 데이터 처리//
				int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen	= tScale.h/nTextW;
					asTemp	= "";

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asTemp	+ asData.SubString(j+1, 2);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								slData->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;

								//+++++++++++++++++++++++++++++++++++++++++++++++++++
								if(asData.c_str()[j+2] == '_')
									j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
							}
							else
							{
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
							}
							j++;
						}
						else
						{
							//========================================================
							if(asData.c_str()[j] == '_')
							{
								if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
								{
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;

									//+++++++++++++++++++++++++++++++++++++++++++++++++++
									//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
									if(asData.c_str()[j+1] == '_')
										j++;
									//+++++++++++++++++++++++++++++++++++++++++++++++++++
								}
							}
							else
							{
								//========================================================
								//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
								}
								//========================================================
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									//========================================================
									//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if(asData.c_str()[j+1] == '%')
									{
										nLineTxtLen	= nLineTxtLen + 1;
										asTemp = asTemp + asData.SubString(j+2, 1);
										j++;
									}
									//========================================================
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;

									//+++++++++++++++++++++++++++++++++++++++++++++++++++
									//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
									if(asData.c_str()[j+1] == '_')
										j++;
									//+++++++++++++++++++++++++++++++++++++++++++++++++++
								}
								else
								{
									nLineTxtCnt++;
								}
							}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						slData->Add(asTemp);
						asTemp	= "";
					}
				}
				//=========================================================

				//=========================================================
				//Width 시작위치 계산//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경//
				nStartW	= tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW)/2);//세로쓰기-중간//
				//=========================================================

				//==========================================================================================
				m_vLEVEL[0].tRect.Left		= nStartW - nTextW * slData->Count;
				m_vLEVEL[0].tRect.Right 	= nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];
					asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
					asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
					asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
					asData	= StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//

					nTxtLen = asData.Length();
					nSumH	= 0;
					//라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asData.SubString(j+1, 2);
							nSumH	+= pbRect->Canvas->TextHeight(asTemp);
							j++;
						}
						else
						{
							if(asData.c_str()[j] == '%')//부분삭제//
								continue;
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									nSumH	+= pbRect->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH	+= pbRect->Canvas->TextHeight(asCaption);
						}
					}

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumH) / 2;
					//=========================================================

					//==========================================================================================
					if(z == 0)
					{
						m_vLEVEL[0].tRect.Top	= nStartH;
						m_vLEVEL[0].tRect.Bottom	= nStartH + nSumH;
					}
					else
					{
						if(m_vLEVEL[0].tRect.Top < nStartH)
							m_vLEVEL[0].tRect.Top = nStartH;
						if(m_vLEVEL[0].tRect.Bottom < nStartH + nSumH)
							m_vLEVEL[0].tRect.Bottom = nStartH + nSumH;
					}
					//==========================================================================================

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}

							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================
				}
				delete slData;
				slData	= NULL;
			}


			//======================================
			// MEMO
			//======================================
			bAllSharp	= false;
	   		bPartSharp	= false;

			//==========================================================================================

			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[2].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[2].gWH);
			//=========================================================

			if(m_asMemo.Length() > 0)
			{
				asData = m_asMemo;
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
	//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
	//			int nPos	= asData.Pos("_");
	//			while(nPos > 0)
	//			{
	//				asTemp 	= asData.SubString(1, nPos-1);
	//				slData->Add(asTemp);
	//				asData  = asData.Delete(1, nPos);
	//				nPos	= asData.Pos("_");
	//			}
	//			if( !asData.IsEmpty() )
	//				slData->Add(asData);
				//공통//
				//=========================================================
				nTextW	= pbRect->Canvas->TextWidth("메")+1;//임의글자로 체크//
				nTextH	= pbRect->Canvas->TextHeight("메")+1;//임의글자로 체크//
				//=========================================================

				//개행없는 데이터 처리//
				int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen	= tScale.h/nTextW;
					asTemp	= "";

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asTemp	+ asData.SubString(j+1, 2);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								slData->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;

								//+++++++++++++++++++++++++++++++++++++++++++++++++++
								if(asData.c_str()[j+2] == '_')
									j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
							}
							else
							{
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
							}
							j++;
						}
						else
						{
							//========================================================
							if(asData.c_str()[j] == '_')
							{
								if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
								{
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;

									//+++++++++++++++++++++++++++++++++++++++++++++++++++
									//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
									if(asData.c_str()[j+1] == '_')
										j++;
									//+++++++++++++++++++++++++++++++++++++++++++++++++++
								}
							}
							else
							{
								//========================================================
								//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
								}
								//========================================================
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									//========================================================
									//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if(asData.c_str()[j+1] == '%')
									{
										nLineTxtLen	= nLineTxtLen + 1;
										asTemp = asTemp + asData.SubString(j+2, 1);
										j++;
									}
									//========================================================
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;

									//+++++++++++++++++++++++++++++++++++++++++++++++++++
									//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
									if(asData.c_str()[j+1] == '_')
										j++;
									//+++++++++++++++++++++++++++++++++++++++++++++++++++
								}
								else
								{
									nLineTxtCnt++;
								}
							}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						slData->Add(asTemp);
						asTemp	= "";
					}
				}
				//=========================================================

				//=========================================================
				//Width 시작위치 계산//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경//
				nStartW	= tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW)/2);//세로쓰기-중간//
				//=========================================================

				//==========================================================================================
				m_vMEMO[0].tRect.Left		= nStartW - nTextW * slData->Count;
				m_vMEMO[0].tRect.Right 	= nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];
					asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
					asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
					asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
					asData	= StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//

					nTxtLen = asData.Length();
					nSumH	= 0;
					//라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asData.SubString(j+1, 2);
							nSumH	+= pbRect->Canvas->TextHeight(asTemp);
							j++;
						}
						else
						{
							if(asData.c_str()[j] == '%')//부분삭제//
								continue;
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									nSumH	+= pbRect->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH	+= pbRect->Canvas->TextHeight(asCaption);
						}
					}

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumH) / 2;
					//=========================================================

					//==========================================================================================
					if(z == 0)
					{
						m_vMEMO[0].tRect.Top	= nStartH;
						m_vMEMO[0].tRect.Bottom	= nStartH + nSumH;
					}
					else
					{
						if(m_vMEMO[0].tRect.Top < nStartH)
							m_vMEMO[0].tRect.Top = nStartH;
						if(m_vMEMO[0].tRect.Bottom < nStartH + nSumH)
							m_vMEMO[0].tRect.Bottom = nStartH + nSumH;
					}
					//==========================================================================================

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}

							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================
				}
				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# JIMOK
		//#
		//##########################################################################################
		{
			//==============================================================
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[3].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[3].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= pbRect->Canvas->TextHeight("지")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vJIMOK.size(); i++)
			{
				asData = m_vJIMOK[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					asData	= asData.Delete(1, 1);
				}
				//=====================================================


				//=========================================
				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				int nPos	= asData.Pos("_");
				while(nPos > 0)
				{
					asTemp 	= asData.SubString(1, nPos-1);
					slData->Add(asTemp);
					asData	 	= asData.Delete(1, nPos);
					nPos		= asData.Pos("_");
				}
				if( !asData.IsEmpty() )
					slData->Add(asData);

				//==========================================================================================
				nStartH	= tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
				m_vJIMOK[i].tRect.Top 	= nStartH;
				m_vJIMOK[i].tRect.Bottom	= nStartH + nStartH*slData->Count;
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					nTextW	= pbRect->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간
					if(i >= 6)
						nStartW	-= nMiddleWidth;

					//==========================================================================================
					if(z == 0)
					{
						m_vJIMOK[i].tRect.Left 	= nStartW;
						m_vJIMOK[i].tRect.Bottom 	= nStartW + nTextW;
					}
					else
					{
						if(m_vJIMOK[i].tRect.Left > nStartW)
							m_vJIMOK[i].tRect.Left = nStartW;
						if(m_vJIMOK[i].tRect.Right < nStartW + nTextW)
							m_vJIMOK[i].tRect.Right = nStartW + nTextW;
					}
					//=========================================================

					//==========================================================================================
					if(nStartW < frmMain->pnlImgDocView->Left || nStartW > frmMain->pnlImgDocView->Left + frmMain->pnlImgDocView->Width
					|| nStartH < frmMain->pnlImgDocView->Top || nStartH > frmMain->pnlImgDocView->Top + frmMain->pnlImgDocView->Height)
					{
						continue;
					}
					//==========================================================================================

					nTxtLen = asData.Length();
					for(int j = 0; j < nTxtLen; j++)
					{
						if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
						{
							bPartSharp	= true;
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
						{
							nPartSharp2	= nStartW + nTextW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							bPartSharp	= false;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
						else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
						{
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
						{
							nPartSharp2	= nStartW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							//여기선 flag해제하면 안됨//
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
					}

					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					asCaption 	= asData;
					TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());

					nStartH	+= nTextH;
				}

				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# AREA
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
	   		bPartSharp	= false;

			//==============================================================
			AnsiString  asUnit		= "";
			AnsiString  asUnitNew	= "";
			//임야는 단위를 ㎡ 변환시에만 표시하는데, 단위를 별도 체킹하지 않으므로 한번만 표시하므로 플래그 해제//
			bool		bForestUnitDisp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[4].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[4].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= pbRect->Canvas->TextHeight("면")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vAREA.size(); i++)
			{
				asData = m_vAREA[i].DATA;
				if(asData == "-")//NoData
					continue;

				//230203//임야대장에도 ㎡ 가 있을 수 있다//
				if(asData.AnsiPos("㎡") > 0 || asData.AnsiPos("평방미터") > 0 || asData.AnsiPos("평") > 0)
				{
					//No Action//
				}
				else//있는 그대로? 확인하고 주석 기재할 것//
				{
					asData = eFunc->funcChangeAreaFormatStr(3, asData);//220119//#21//임야대장 지적 -> 정단무보 변경없이 입력그대로두기//
				}

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					asData	= asData.Delete(1, 1);
				}
				//=====================================================

				//211201//#12//지적 단위변환//
				//=========================================
				// 단위확인//
				int nPos	= 0;
				AnsiString  asTempUnit	= "";
				bool		bUnit	= false;
				if(m_nDOCKIND == 0)//토지대장//
				{
					for(int u = 0; u < (int)frmMain->m_vAREAUNIT.size(); u++)
					{
						asTempUnit	= frmMain->m_vAREAUNIT[u].DATA;
						nPos	= asData.AnsiPos(asTempUnit);
						if(nPos > 0)
						{
							bUnit	= true;
							asUnit	= asData.SubString(nPos, asTempUnit.Length());
							asData	= StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
						}

						if(bUnit)
						{
							if(asUnit == "평방미터")//220120
								asUnit	= "㎡";
							break;
						}
					}
				}

				//=========================================
				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				nPos	= asData.Pos("_");
				while(nPos > 0)
				{
					asTemp 	= asData.SubString(1, nPos-1);
					slData->Add(asTemp);
					asData	 	= asData.Delete(1, nPos);
					nPos		= asData.Pos("_");
				}
				if( !asData.IsEmpty() )
					slData->Add(asData);

				//==========================================================================================
				nStartH	= tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
				m_vAREA[i].tRect.Top 	= nStartH;
				m_vAREA[i].tRect.Bottom	= nStartH + nStartH*slData->Count;
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					//211206//
					int nSharpPos1	= 0;
					int nSharpPos2	= 0;
					if(frmDoc8View->chkAreaChange->Checked)
					{
						if(m_nDOCKIND == 0)//토지대장//
						{
							if(asUnit == "평" || asUnit == "홉" || asUnit == "작")
							{
								//211206//=============
								nSharpPos1	= asData.Pos("%");
								if(nSharpPos1 > 0)
									asData	= asData.Delete(nSharpPos1, 1);
								nSharpPos2	= asData.Pos("%");
								if(nSharpPos2 > 0)
									asData	= asData.Delete(nSharpPos2, 1);
								//=====================

								asData	= eFunc->funcChangeAreaFormatStr(1, asData + asUnit);//평->㎡

								//211206//=============
								if(nSharpPos1 > 0)
									asData	= "%" + asData;
								if(nSharpPos2 > 0)
									asData	= asData + "%";
								//=====================

								asUnitNew	= "㎡";

								//==========================================
								//230213//㎡일때는 맨처음에만 단위 표시한다//
								if(i > 0)
								{
									bUnit = false;
								}
								//==========================================
							}
							else
							{
								asUnitNew	= asUnit;
							}
						}
						else if(m_nDOCKIND == 1)//임야대장//
						{
							//211206//=============
							nSharpPos1	= asData.Pos("%");
							if(nSharpPos1 > 0)
								asData	= asData.Delete(nSharpPos1, 1);
							nSharpPos2	= asData.Pos("%");
							if(nSharpPos2 > 0)
								asData	= asData.Delete(nSharpPos2, 1);
							//=====================

							asData	= eFunc->funcChangeAreaFormatStr(1, asData);//정단무보->㎡

							//211206//=============
							if(nSharpPos1 > 0)
								asData	= "%" + asData;
							if(nSharpPos2 > 0)
								asData	= asData + "%";
							//=====================

							if( !bForestUnitDisp )
							{
								asUnitNew	= "㎡";
								bUnit	= true;
								bForestUnitDisp	= true;
							}
						}
					}

					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					nTextW	= pbRect->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간
					if(i >= 6)
						nStartW	-= nMiddleWidth;

					//==========================================================================================
					if(z == 0)
					{
						m_vAREA[i].tRect.Left 		= nStartW;
						m_vAREA[i].tRect.Bottom 	= nStartW + nTextW;
					}
					else
					{
						if(m_vAREA[i].tRect.Left > nStartW)
							m_vAREA[i].tRect.Left = nStartW;
						if(m_vAREA[i].tRect.Right < nStartW + nTextW)
							m_vAREA[i].tRect.Right = nStartW + nTextW;
					}
					//=========================================================

					//==========================================================================================
					if(nStartW < frmMain->pnlImgDocView->Left || nStartW > frmMain->pnlImgDocView->Left + frmMain->pnlImgDocView->Width
					|| nStartH < frmMain->pnlImgDocView->Top || nStartH > frmMain->pnlImgDocView->Top + frmMain->pnlImgDocView->Height)
					{
						continue;
					}
					//==========================================================================================


					nTxtLen = asData.Length();
					for(int j = 0; j < nTxtLen; j++)
					{
						if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
						{
							bPartSharp	= true;
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
						{
							nPartSharp2	= nStartW + nTextW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							bPartSharp	= false;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
						else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
						{
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
						{
							if(asData.c_str()[j] =='%')//종료//211201//
								bPartSharp	= false;
							nPartSharp2	= nStartW + nTextW-1;//211201//nPartSharp2	= nStartW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							//여기선 flag해제하면 안됨//
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
					}

					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					asCaption 	= asData;
					TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());

					nStartH	+= nTextH;
				}

				//=========================================
				//단위표시//
				if(bUnit)
				{
					if(frmDoc8View->chkAreaChange->Checked)
					{
						int nTxtW	= pbRect->Canvas->TextWidth(asUnitNew)+1;
						nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위
						if(i >= 6)
							nStartW	-= nMiddleWidth;

						TextOutA(hdc, nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnitNew.c_str(), (int)asUnitNew.Length());
					}
					else
					{
						int nTxtW	= pbRect->Canvas->TextWidth(asUnit)+1;
						nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위
						if(i >= 6)
							nStartW	-= nMiddleWidth;
						TextOutA(hdc, nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit.c_str(), (int)asUnitNew.Length());
					}
				}
				//=========================================

				delete slData;
				slData	= NULL;
				//=========================================
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# VALUE1
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[5].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[5].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= pbRect->Canvas->TextHeight("과")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vVALUE1.size(); i++)
			{
				asData = m_vVALUE1[i].DATA;

				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
				//221108//DB에는 기준수확량, 임대가격, 토지등급 텍스트에 []처리 되어 있으므로 삭제( <> 로 표현되어야 하기에 아래코드에서 처리)
				asData	= StringReplace(asData, "[", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "]", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					asData	= asData.Delete(1, 1);
				}
				//=====================================================


				//=========================================
				// 단위확인//
				int nPos	= 0;
				AnsiString  asUnit	= "";
				bool		bUnit	= false;
				for(int u = 0; u < (int)frmMain->m_vVALUEUNIT.size(); u++)
				{
					asUnit	= frmMain->m_vVALUEUNIT[u].DATA;

					nPos	= asData.AnsiPos(asUnit);
					if(nPos > 0)
					{
						bUnit	= true;
						asUnit	= asData.SubString(nPos, asUnit.Length());
						asData	= StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
					}

					if(bUnit)
						break;
				}
				//=========================================

				//=========================================
				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				int nPos1	= asData.AnsiPos("기준수확량");
				int nPos2	= asData.AnsiPos("임대가격");
				int nPos3	= asData.AnsiPos("토지등급");

				nPos	= 1;
				while(nPos1 > 0 || nPos2 > 0 || nPos3 > 0 || nPos > 0)
				{
					if(nPos1 > 0)
						asTemp 	= "기준수확량";
					if(nPos2 > 0)
						asTemp 	= "임대가격";
					if(nPos3 > 0)
						asTemp 	= "토지등급";

					if(nPos1 > 0 || nPos2 > 0 || nPos3 > 0)
					{
						if(nPos2 > nPos1)		nPos	= nPos2;
						else if(nPos3 > nPos1)	nPos	= nPos3;
						else if(nPos3 > nPos2)	nPos	= nPos3;
						else if(nPos1 > 0)		nPos	= nPos1;
						else if(nPos2 > 0)	nPos	= nPos2;
						else if(nPos3 > 0)	nPos	= nPos3;

						//=====================================
						//211201//#2
						int nEndPos	= asTemp.Length() + nPos - 1;
						if(asData.c_str()[nEndPos] =='%')
							nEndPos++;
						asTemp 	= asData.SubString(1, nEndPos);
						asData  = asData.Delete(1, nEndPos);
						if(asTemp.Pos("기준수확량") > 0 || asTemp.Pos("임대가격") > 0)
						{
							//=======================================
							//211208//31025.254.1	//OLD//asTemp 	= "<" + asTemp + ">";
							if(asTemp.SubString(1, 1) == "%" && asTemp.SubString(asTemp.Length(), 1) != "%")
							{
								asTemp 	= "<" + asTemp + "%>";
								if(!asData.IsEmpty() && asData.SubString(asData.Length(), 1) =='%' && asData.SubString(1, 1) != "%")
								{
									asData	= "%" + asData;
								}
							}
							else
							{
								asTemp 	= "<" + asTemp + ">";
							}
							//=======================================
						}
						slData->Add(asTemp);
						//=====================================

						nPos1	= 0;
						nPos2	= 0;
						nPos3	= 0;
					}
					nPos	= asData.Pos("_");
					//==================================
					if(nPos > 0)
					{
						asTemp 	= asData.SubString(1, nPos-1);
						asData	= asData.Delete(1, nPos);
						if( !asTemp.IsEmpty() )
							slData->Add(asTemp);
					}
					nPos1	= asData.AnsiPos("기준수확량");
					nPos2	= asData.AnsiPos("임대가격");
					nPos3	= asData.AnsiPos("토지등급");
					//==================================
				}
				if( !asData.IsEmpty() )
					slData->Add(asData);

				//==========================================================================================
				nStartH	= tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
				m_vVALUE1[i].tRect.Top 		= nStartH;
				m_vVALUE1[i].tRect.Bottom	= nStartH + nStartH*slData->Count;
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					nTextW	= pbRect->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간
					if(i >= 6)
						nStartW	-= nMiddleWidth;

					//==========================================================================================
					if(z == 0)
					{
						m_vJIMOK[i].tRect.Left 		= nStartW;
						m_vJIMOK[i].tRect.Bottom 	= nStartW + nTextW;
					}
					else
					{
						if(m_vJIMOK[i].tRect.Left > nStartW)
							m_vJIMOK[i].tRect.Left = nStartW;
						if(m_vJIMOK[i].tRect.Right < nStartW + nTextW)
							m_vJIMOK[i].tRect.Right = nStartW + nTextW;
					}
					//=========================================================

					int nPartTextWidth	= 0;//211229//25031.181.2//
					nTxtLen = asData.Length();
					for(int j = 0; j < nTxtLen; j++)
					{
						if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
						{
							bPartSharp	= true;
							nPartSharp1	= nStartW + nPartTextWidth;//211229//25031.181.2//nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
						{
							nPartSharp2	= nStartW + nPartTextWidth-1;//211229//25031.181.2//nPartSharp2	= nStartW + nTextW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							bPartSharp	= false;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
						else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
						{
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
						{
							nPartSharp2	= nStartW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							//여기선 flag해제하면 안됨//
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
						else//211229//25031.181.2//
						{
							asTemp	= asData.SubString(j, 1);
							nPartTextWidth	+= pbRect->Canvas->TextWidth(asTemp);
						}
					}

					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					asCaption 	= asData;
					TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());

					nStartH	+= nTextH;
				}

				//=========================================
				//단위표시//
				if(bUnit)
				{
					int nTxtW	= pbRect->Canvas->TextWidth(asUnit)+1;
					nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
					if(i >= 6)
						nStartW	-= nMiddleWidth;
					TextOutA(hdc, nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit.c_str(), (int)asUnit.Length());
				}
				//=========================================

				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# VALUE2
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1		= 0;
			nAllSharp2		= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[6].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[6].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= pbRect->Canvas->TextHeight("과")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vVALUE2.size(); i++)
			{
				asData = m_vVALUE2[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					asData	= asData.Delete(1, 1);
				}
				//=====================================================


				//=========================================
				// 단위확인//
				int nPos	= 0;
				AnsiString  asUnit	= "";
				bool		bUnit	= false;
				for(int u = 0; u < (int)frmMain->m_vVALUE2UNIT.size(); u++)
				{
					asUnit	= frmMain->m_vVALUE2UNIT[u].DATA;

					nPos	= asData.AnsiPos(asUnit);
					if(nPos > 0)
					{
						bUnit	= true;
						asUnit	= asData.SubString(nPos, asUnit.Length());
						asData	= StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
					}

					if(bUnit)
						break;
				}
				//=========================================

				//=========================================
				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				nPos	= asData.Pos("_");
				while(nPos > 0)
				{
					asTemp 	= asData.SubString(1, nPos-1);
					slData->Add(asTemp);
					asData	 	= asData.Delete(1, nPos);
					nPos		= asData.Pos("_");
				}
				if( !asData.IsEmpty() )
					slData->Add(asData);

				//==========================================================================================
				nStartH	= tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
				m_vVALUE2[i].tRect.Top 		= nStartH;
				m_vVALUE2[i].tRect.Bottom	= nStartH + nStartH*slData->Count;
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					nTextW	= pbRect->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간
					if(i >= 6)
						nStartW	-= nMiddleWidth;

					//==========================================================================================
					if(z == 0)
					{
						m_vVALUE2[i].tRect.Left 	= nStartW;
						m_vVALUE2[i].tRect.Bottom 	= nStartW + nTextW;
					}
					else
					{
						if(m_vVALUE2[i].tRect.Left > nStartW)
							m_vVALUE2[i].tRect.Left = nStartW;
						if(m_vVALUE2[i].tRect.Right < nStartW + nTextW)
							m_vVALUE2[i].tRect.Right = nStartW + nTextW;
					}
					//=========================================================

					nTxtLen = asData.Length();
					for(int j = 0; j < nTxtLen; j++)
					{
						if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
						{
							bPartSharp	= true;
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
						{
							nPartSharp2	= nStartW + nTextW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							bPartSharp	= false;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
						else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
						{
							nPartSharp1	= nStartW;
							continue;
						}
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
						{
							nPartSharp2	= nStartW-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nPartSharp1;
							tempData.tpSTT.y	= nStartH + nTextH/2;
							tempData.tpEND.x	= nPartSharp2;
							tempData.tpEND.y	= nStartH + nTextH/2;
							m_vSharpPos.push_back(tempData);
							//여기선 flag해제하면 안됨//
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							continue;
						}
					}

					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					asCaption 	= asData;
					TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());

					nStartH	+= nTextH;
				}

				//=========================================
				//단위표시//
				if(bUnit)
				{
					int nTxtW	= pbRect->Canvas->TextWidth(asUnit)+1;
					nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
					if(i >= 6)
						nStartW	-= nMiddleWidth;
					TextOutA(hdc, nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit.c_str(), (int)asUnit.Length());
				}
				//=========================================

				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# HISTORY
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			bPartSharp	= false;
			nAllSharp1		= 0;
			nAllSharp2		= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			bool	bOverCell		= false;//#OVERCELL//
			int		nOverCellW		= 0;//#OVERCELL//

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[7].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[7].gWH);
			//=========================================================
			//공통//
			nTextW	= pbRect->Canvas->TextWidth("연")-1;/*+1*/;//임의글자로 체크//
			nTextH	= pbRect->Canvas->TextHeight("연")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vHISTORY.size(); i++)
			{
				asData = m_vHISTORY[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
				//221020//[REQ]연혁개행처리//			asData	= StringReplace(asData, "_", "", TReplaceFlags() << rfReplaceAll);//211208//금란차장Req//연혁은 개행문자('_') 제거//

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					asData	= asData.Delete(1, 1);
				}
				//=====================================================

				//---
				nTxtLen = asData.Length();

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				//연혁에는 개행하지 않음//
	//			int nPos	= asData.Pos("_");
	//			while(nPos > 0)
	//			{
	//				asTemp 	= asData.SubString(1, nPos-1);
	//				slData->Add(asTemp);
	//				asData  = asData.Delete(1, nPos);
	//				nPos	= asData.Pos("_");
	//			}
	//			slData->Add(asData);

				//개행없는 데이터 처리//
				int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					//연혁 셀 넘치는 경우 처리//#OVERCELL//
					int nMaxTxtLen   	= 0;
					int nMaxWLineLen   	= 0;
					int nMaxHLineLen	= 0;
					int nCountTxtLen	= 0;
					nMaxWLineLen	= tScale.w/nTextW;
					nMaxHLineLen	= tScale.h/nTextH;
					nMaxTxtLen		= nMaxWLineLen * nMaxHLineLen;

					nLineTxtLen	= tScale.h/nTextH;
					asTemp	= "";

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asTemp	+ asData.SubString(j+1, 2);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								slData->Add(asTemp);
								asTemp	= "";
								nCountTxtLen	+= nLineTxtCnt+1;
								nLineTxtCnt	= 0;
							}
							else
							{
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
							}
							j++;
						}
						else
						{
							//=====================================
							//221020//[REQ]연혁 개행처리 & 자동개행//
							if(asData.SubString(j+1, 1) == "_")
							{
								if( !asTemp.IsEmpty())
								{
									slData->Add(asTemp);
									asTemp	= "";
									nCountTxtLen	+= nLineTxtCnt+1;
									nLineTxtCnt	= 0;
								}
							}
							else
							//=====================================
							{
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									slData->Add(asTemp);
									asTemp	= "";
									nCountTxtLen	+= nLineTxtCnt+1;
									nLineTxtCnt	= 0;
								}
								else
								{
									if(asData.c_str()[j] == '%')//부분삭제//데이터에는 저장, 길이에는 포함하지 않는다. 추후 제거할 것이므로//
										continue;
									nLineTxtCnt++;
								}
							}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						slData->Add(asTemp);
						asTemp	= "";
						nCountTxtLen	+= nLineTxtCnt;
					}

					//연혁 셀 넘치는 경우 처리//#OVERCELL//
					if(nCountTxtLen > nMaxTxtLen)
					{
						bOverCell	= true;
					}
					else
					{
						bOverCell	= false;
					}
				}
				//=========================================================

				//공통//
				//=========================================================
				nTextH	= pbRect->Canvas->TextHeight("연")+1;//임의글자로 체크//
				if(bOverCell)
				{
					if(nOverCellW == 0)//맨처음데이터//
						nOverCellW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//
					nStartW	= nOverCellW;
				}
				else
				{
					nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//
				}
				if(i >= 6)
					nStartW	-= nMiddleWidth;

				bool	bRevise	= false;//셀당 Width 보정 1회만 하기 위한 플래그//

				//==========================================================================================
				m_vHISTORY[i].tRect.Left	= nStartW - nTextW * slData->Count;
				m_vHISTORY[i].tRect.Right = nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					nTxtLen = asData.Length();

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					if( !bRevise && nStartW < tPoint.x - i*tScale.w)//맨처음에만 보정해준다//
					{
						nStartW	 -= 4;/*Gap*/
						bRevise	= true;
					}
					nStartH	= tPoint.y;//세로쓰기-상단//
					m_vHISTORY[i].tRect.Top	= nStartH;
					//=========================================================


					//==========================================================================================
					if(nStartW < frmMain->pnlImgDocView->Left || nStartW > frmMain->pnlImgDocView->Left + frmMain->pnlImgDocView->Width
					|| nStartH < frmMain->pnlImgDocView->Top || nStartH > frmMain->pnlImgDocView->Top + frmMain->pnlImgDocView->Height)
					{
						continue;
					}
					//==========================================================================================


					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//한글이라 2byte이므로 j==1로 체크//
//							{
//								nPartSharp1	= nStartH;
//								nStartH	+= nTextH;//211208
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH+nTextH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								asCaption = asData.SubString(j+1, 1);
//								TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
//								nPartSharp1	= nStartH-1;//211201//#10//아래코드랑 순서 변경//41021.303.1//
//								nStartH	+= nTextH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								asCaption = asData.SubString(j+1, 1);
//								TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
//								nStartH	+= nTextH;
//								nPartSharp2	= nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//==========================================================================================
					if(z == 0)
					{
						m_vHISTORY[i].tRect.Bottom	= nStartH;
					}
					else
					{
						if(m_vHISTORY[i].tRect.Bottom < nStartH)
							m_vHISTORY[i].tRect.Bottom = nStartH;
					}
					//==========================================================================================
				}

				delete slData;
				slData	= NULL;

				if(bOverCell)
				{
					nOverCellW	= nStartW - nTextW;
				}
				else
				{
					nOverCellW	= 0;
				}
			}

			::SetROP2 (hdc, oldro);
		}



		//##########################################################################################
		//#
		//# DATE
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[8].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[8].gWH);
			//=========================================================
			//공통//
			nTextW	= pbRect->Canvas->TextWidth("일")+1;//임의글자로 체크//
			nTextH	= pbRect->Canvas->TextHeight("일")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFODATE.size(); i++)
			{
				asData = m_vOWNINFODATE[i].DATA;
				if(asData == "-")//NoData
					continue;

				//=====================================================
				//211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
	//			asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				//=====================================================
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					bAllSharp	= true;
					asData	= asData.Delete(1, 1);
				}
				else
				{
					bAllSharp	= false;
				}
				//=====================================================

				if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
				{
					bAllSharp	= true;
					asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				}
				else
				{
					bAllSharp	= false;
				}

				//=====================================================
				//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
				if(asData != "판독불가")
				//=====================================================
				{
					//260530//
					if( !frmMain->m_bAIOCR )//기구축DB 번역본//
					{
						asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
						asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
					}
					else//AIOCR 번역본//
					{
						AnsiString  _asData = asData;
						asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
						if(asData == "Error")
							asData = _asData;
						else
							asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
					}
				}

				//---
				nTxtLen = asData.Length();

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
				//일자에는 개행하지 않음//
				if(nTxtLen > 0)
				{
					//=====================================================
					//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
					if(asData != "판독불가")
					//=====================================================
					{
						//년도//
						int nPos 	= asData.AnsiPos("년");
						asTemp 	= asData.SubString(1, nPos+1);
						slData->Add(asTemp);
						asData  = asData.Delete(1, nPos+1);
						//월일//
						asTemp 	= asData;
						//211216//도청김훈곤주무관Req//Date에 5줄로 맞춰달라//
						asTemp	= StringReplace(asTemp, "월", "월 ", TReplaceFlags() << rfReplaceAll);
						//====================================================
						//211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
						if(asTemp.AnsiPos("월") == 0)
							asTemp	= " 월" + asTemp;
						if(asTemp.AnsiPos("일") == 0)
							asTemp	= asTemp + " 일";
						//====================================================
						slData->Add(asTemp);
					}
					//=====================================================
					//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
					else
					{
						slData->Add("판 독");
						slData->Add("불 가");
					}
					//=====================================================
				}
				//=========================================================

				//======================================
				if(i == 10)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)2*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else if(i == 23)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)4*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else
					nStartW	= tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				//======================================
				if(i >= 11)
					nStartW	-= (nMiddleWidth + ((double)2*(double)frmMain->m_dDocFactor));
				//=========================================================

				//==========================================================================================
				m_vOWNINFODATE[i].tRect.Left	= nStartW - nTextW * slData->Count;
				m_vOWNINFODATE[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					nTxtLen = asData.Length();

					//=========================================================
					//Height 계산//
					int nSumHeight	= 0;
					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					for(int j = 0; j < asTemp.Length(); j++)
					{
						if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asTemp.SubString(j+1, 2);
							nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asTemp.Length() && (asTemp.c_str()[j] >= '0' && asTemp.c_str()[j] <= '9'))
							{
								if(asTemp.c_str()[j+1] >= '0' && asTemp.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asTemp.SubString(j+1, 2);
									nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asTemp.SubString(j+1, 1);
							nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						}
					}
					//=========================================================

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//nStartH	= tScale.h;//세로쓰기-상단//
					//=========================================================

					if(bAllSharp)//전체삭제//
						nAllSharp1	= nStartH;

					//==========================================================================================
					if(z == 0)
					{
						m_vOWNINFODATE[i].tRect.Top 	= nStartH;
						m_vOWNINFODATE[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vOWNINFODATE[i].tRect.Top > nStartH)
							m_vOWNINFODATE[i].tRect.Top = nStartH;
						if(m_vOWNINFODATE[i].tRect.Bottom < nStartH + nSumHeight)
							m_vOWNINFODATE[i].tRect.Bottom = nStartH + nSumHeight;
					}
					//=========================================================

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1	= nStartH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제//
					if(bAllSharp)
					{
						nAllSharp2	= nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x	= nStartW + nTextW/2;
						tempData.tpSTT.y	= nAllSharp1;
						tempData.tpEND.x	= nStartW + nTextW/2;
						tempData.tpEND.y	= nAllSharp2;
						m_vSharpPos.push_back(tempData);
						//bAllSharp	= false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# REASON
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
			bPartSharp	= false;

	   		//==============================================================
			int		nComment		= 0;
			bool	bComment		= 0;
			TStringList *slComment 		= new TStringList;
			slComment	= new TStringList();
			slComment->Text = "";
			slComment->Clear();
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[9].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[9].gWH);
			//=========================================================
			//공통//
			nTextW	= pbRect->Canvas->TextWidth("사")/*+1*/;//임의글자로 체크//
			nTextH	= pbRect->Canvas->TextHeight("사")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFOREASON.size(); i++)
			{
				asData = m_vOWNINFOREASON[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				//asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				//asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				//소유권이전, 소유권보존 자동개행처리//
				AnsiString  asTmp1	= "";
				AnsiString  asTmp2	= "";
				for(int r = 0; r < (int)frmMain->m_vREASONDATA.size(); r++)
				{
					asTmp1	= frmMain->m_vREASONDATA[r].DATA;
					asTmp2	= StringReplace(asTmp1, "_", "", TReplaceFlags() << rfReplaceAll);
					asTmp2	= StringReplace(asTmp2, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(m_vREASONDATA)를 제외하고는 공백처리하지 않음//
					if(asData.AnsiPos(asTmp2))
					{
						asData	= StringReplace(asData, asTmp2, asTmp1, TReplaceFlags() << rfReplaceAll);
					}
				}
				//=====================================================


				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					bAllSharp	= true;
					asData	= asData.Delete(1, 1);
				}
				else
				{
					bAllSharp	= false;
				}

				if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
				{
					//=================================================================================
					//211229//
					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					if(asTemp.Length() < 20)
					{
						bAllSharp	= true;
						asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					}
					//=================================================================================
				}
				else
				{
					bAllSharp	= false;
				}
				//=====================================================



				//---
				nTxtLen = asData.Length();

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();

				//개행없는 데이터 처리//
				int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen	= tScale.h/nTextW;
					asTemp	= "";

					//=================================================================================
					//주석처리//
					//211229//
					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					if(asTemp.Length() >= 20)
					//211229//if(asData.Length() >= 20)//asData.Pos("법률") > 0 || asData.Pos("분배농지") > 0)
					{
						asTemp	= "";//211229//

						bComment	= true;
						if(nComment == 0)
							asTemp 	= "⑴";
						else if(nComment == 1)
							asTemp 	= "⑵";
						else if(nComment == 2)
							asTemp 	= "⑶";
						else if(nComment == 3)
							asTemp 	= "⑷";
						else if(nComment == 4)
							asTemp 	= "⑸";
						asData 	= asTemp + asData;
						slData->Add("하단기재");//211216//도청김훈곤주무관Req//주석:하단기재//41023.628
						//211201//#11//주석 취소선 적용//asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
						asData	= StringReplace(asData, "_", "", TReplaceFlags() << rfReplaceAll);
						asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(m_vREASONDATA)를 제외하고는 공백처리하지 않음//
						slComment->Add(asData);
						slData->Add(asTemp);
						nComment++;
					}
					//=================================================================================
					else//일반적인 데이터//
					{
						//개행 문자에 따른 줄바꿈기능//
						int nPos	= asData.Pos("_");
						while(nPos > 0)
						{
							asTemp 	= asData.SubString(1, nPos-1);
							slData->Add(asTemp);
							asData  = asData.Delete(1, nPos);
							nPos	= asData.Pos("_");
						}
						if( !asData.IsEmpty() )
							slData->Add(asData);

						//길이에 따른 자동줄바꿈기능//
	//					for(int j = 0; j < nTxtLen; j++)
	//					{
	//						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
	//						{
	//							asTemp = asTemp	+ asData.SubString(j+1, 2);
	//							if(nLineTxtCnt >= nLineTxtLen-1)
	//							{
	//								slData->Add(asTemp);
	//								asTemp	= "";
	//								nLineTxtCnt	= 0;
	//							}
	//							else
	//							{
	//								nLineTxtCnt++;
	//							}
	//							j++;
	//						}
	//						else
	//						{
	//							if(asData.c_str()[j] == '%')//부분삭제//
	//								continue;
	//							asTemp = asTemp + asData.SubString(j+1, 1);
	//							if(nLineTxtCnt >= nLineTxtLen-1)
	//							{
	//								slData->Add(asTemp);
	//								asTemp	= "";
	//								nLineTxtCnt	= 0;
	//							}
	//							else
	//							{
	//								nLineTxtCnt++;
	//							}
	//						}
	//					}
	//					if( !asTemp.IsEmpty() )
	//					{
	//						slData->Add(asTemp);
	//						asTemp	= "";
	//					}
					}
				}
				//=========================================================

				//======================================
				if(i == 10)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)2*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else if(i == 23)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)4*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else
					nStartW	= tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				//======================================
				if(i >= 11)
					nStartW	-= (nMiddleWidth + ((double)2*(double)frmMain->m_dDocFactor));
				//=========================================================

				//==========================================================================================
				m_vOWNINFOREASON[i].tRect.Left	= nStartW - nTextW * slData->Count;
				m_vOWNINFOREASON[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					nTxtLen = asData.Length();

					//=========================================================
					//Height 계산//
					int nSumHeight	= 0;
					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					for(int j = 0; j < asTemp.Length(); j++)
					{
						if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asTemp.SubString(j+1, 2);
							nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
							j++;
						}
						else
						{
							asCaption = asTemp.SubString(j+1, 1);
							nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						}
					}
					//=========================================================

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//nStartH	= tScale.h;//세로쓰기-상단//
					//=========================================================

					//==========================================================================================
					if(z == 0)
					{
						m_vOWNINFOREASON[i].tRect.Top 	= nStartH;
						m_vOWNINFOREASON[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vOWNINFOREASON[i].tRect.Top > nStartH)
							m_vOWNINFOREASON[i].tRect.Top = nStartH;
						if(m_vOWNINFOREASON[i].tRect.Bottom < nStartH + nSumHeight)
							m_vOWNINFOREASON[i].tRect.Bottom = nStartH + nSumHeight;
					}

					if(bAllSharp)//전체삭제//
						nAllSharp1	= nStartH;

 					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							//=========================================================
//							//minji@230201//[해결]%소유권이전%_성변경 => 처리 시 '이전'에만 취소선이 표시되는 문제 수정//
//							if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2 + nTextH;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							}
//							//=========================================================
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1	= nStartH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//220126//TEST//if(slComment->Count == 0)//211229//25031.36//%소유권이전_성명경정%
					{
						//전체삭제//
						if(bAllSharp)
						{
							nAllSharp2	= nStartH-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
							tempData.tpSTT.x	= nStartW + nTextW/2;
							tempData.tpSTT.y	= nAllSharp1;
							tempData.tpEND.x	= nStartW + nTextW/2;
							tempData.tpEND.y	= nAllSharp2;
							m_vSharpPos.push_back(tempData);
							//bAllSharp	= false;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						}
					}
				}

				delete slData;
				slData	= NULL;
			}

			//======================================================
			// 주석표시//
			int nCommentTextH	= 0;
			bool	bCommentAllSharp	= false;
			bool	bCommentPartSharp	= false;
			for(int m = 0; m < slComment->Count; m++)
			{
				asCaption		= slComment->Strings[m];

				if(asCaption.SubString(1, 1) == "#")//전체삭제//
				{
					bCommentAllSharp	= true;
					asData	= asCaption.Delete(1, 1);
				}
				else
				{
					bCommentAllSharp	= false;
				}

				//211229//25031.36//%소유권이전_성명경정%
				if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
				{
					bCommentAllSharp	= true;
					asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				}
				else
				{
					bCommentAllSharp	= false;
				}
				//======================================================
				//211201//#11//주석 취소선 적용//
				int nCommentTextLen	= asCaption.Length();
				int nCommentW	= tPoint.x-10*tScale.w;
				int nCommentH	= tPoint.y+tScale.h+14+m*nCommentTextH;
				int nPosSharp1	= 0;
				int nPosSharp2	= 0;
				bCommentPartSharp	= false;
				for(int n = 0; n < nCommentTextLen; n++)
				{
					if(!bCommentPartSharp && asCaption.c_str()[n] =='%')//가로쓰기 부분삭제 시작지점//
					{
						nPosSharp1	= n+1;
						bCommentPartSharp	= true;
						nPartSharp1	= nCommentW + nTextW-1;
						continue;
					}
					else if(bCommentPartSharp && asCaption.c_str()[n] =='%')//가로쓰기 부분삭제 종료지점//
					{
						nPosSharp2	= n;

						AnsiString  asTemp	= asCaption.SubString(nPosSharp1+1, nPosSharp2-nPosSharp1);
						nPartSharp2		= nCommentW + pbRect->Canvas->TextWidth(asTemp) + asTemp.Length();
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x	= nPartSharp1;
						tempData.tpSTT.y	= nCommentH + nTextH/2;
						tempData.tpEND.x	= nPartSharp2;
						tempData.tpEND.y	= nCommentH + nTextH/2;
						m_vSharpPos.push_back(tempData);
						bCommentPartSharp	= false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						continue;
					}
				}
				//comment---
				if(bCommentAllSharp)//211208//
				{
					memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
					tempData.tpSTT.x	= nStartW + nTextW/2;
					tempData.tpSTT.y	= nAllSharp1;
					tempData.tpEND.x	= nStartW + nTextW/2;
					tempData.tpEND.y	= nAllSharp2;
					m_vSharpPos.push_back(tempData);
					//bAllSharp	= false;
				}
				//======================================================

				asCaption	= StringReplace(asCaption, "%", "", TReplaceFlags() << rfReplaceAll);
				nCommentTextH	= pbRect->Canvas->TextHeight(asCaption)+1;
				TPoint	tPoint1	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[11].gLT);
				TScale  tScale1	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[11].gWH);
				TextOutA(hdc, tPoint1.x-10*tScale1.w, tPoint1.y+tScale1.h+14+m*nCommentTextH, asCaption.c_str(), (int)asCaption.Length());

			}
			delete slComment;
			slComment	= NULL;
			//======================================================

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# ADDRESS
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================

			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[10].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[10].gWH);
			//=========================================================
			//공통//
			nTextW	= pbRect->Canvas->TextWidth("주")/*+1*/;//임의글자로 체크//
			nTextH	= pbRect->Canvas->TextHeight("주")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFOADDRESS.size(); i++)
			{
				asData = m_vOWNINFOADDRESS[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					bAllSharp	= true;
					asData	= asData.Delete(1, 1);
				}
				else
				{
					bAllSharp	= false;
				}

				if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
				{
					bAllSharp	= true;
					asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				}
				else
				{
					bAllSharp	= false;
				}
				//=====================================================

				//---
				nTxtLen = asData.Length();

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();

				//개행없는 데이터 처리//
				int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen	= tScale.h/nTextW;
					asTemp	= "";

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asTemp	+ asData.SubString(j+1, 2);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								slData->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
							else
							{
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
							}
							j++;
						}
						else
						{
							//========================================================
							//211201//#4//주소 개행('_')
							if(asData.c_str()[j] == '_')
							{
								if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
								{
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;
								}
							}
							else
							{
								//========================================================
								//211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
								}
								//========================================================
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									//========================================================
									//211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if(asData.c_str()[j+1] == '%')
									{
										nLineTxtLen	= nLineTxtLen + 1;
										asTemp = asTemp + asData.SubString(j+2, 1);
										j++;
									}
									//========================================================
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;
								}
								else
								{
									nLineTxtCnt++;
								}
							}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						slData->Add(asTemp);
						asTemp	= "";
					}
				}
				//=========================================================

				//======================================
				if(i == 10)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)2*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else if(i == 23)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)4*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else
					nStartW	= tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				//======================================
				if(i >= 11)
					nStartW	-= (nMiddleWidth + ((double)2*(double)frmMain->m_dDocFactor));
				//=========================================================
				//220112//31039.18.1(부여두리)
				if(slData->Count == 4)
					nStartW -= 2;


				//==========================================================================================
				m_vOWNINFOADDRESS[i].tRect.Left	= nStartW - nTextW * slData->Count;
				m_vOWNINFOADDRESS[i].tRect.Right 	= nStartW;
				//==========================================================================================


				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];
					nTxtLen = asData.Length();

					//211206//주소:세로쓰기, 너비중간정렬, 길이상단정렬//
	//				//=========================================================
	//				//Height 계산//
	//				int nSumHeight	= 0;
	//				asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
	//				for(int j = 0; j < asTemp.Length(); j++)
	//				{
	//					if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
	//					{
	//						asCaption = asTemp.SubString(j+1, 2);
	//						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
	//						j++;
	//					}
	//					else
	//					{
	//						asCaption = asTemp.SubString(j+1, 1);
	//						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
	//					}
	//				}
	//				//=========================================================
	//
	//				//실제 표시//
	//				//=========================================================
	//				nStartW	-= nTextW;
	//				nStartH	= bsAddress.y + (bsAddress.h - nSumHeight) / 2;//세로쓰기-중간//
					nStartW	-= nTextW;
					nStartH	= tPoint.y;//세로쓰기-상단//
					m_vOWNINFOADDRESS[i].tRect.Top 	= nStartH;

					if(bAllSharp)//전체삭제//
						nAllSharp1	= nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//한글이라 2byte이므로 j==1로 체크//
//							{
//								nPartSharp1	= nStartH;
//								nStartH	+= nTextH;//211208
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH+nTextH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1	= nStartH;
//								//시작지점에 문자는 출력해야죠.//continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//==========================================================================================

					if(z == 0)
					{
						m_vOWNINFOADDRESS[i].tRect.Bottom	= nStartH;
					}
					else
					{
						if(m_vOWNINFOADDRESS[i].tRect.Bottom < nStartH)
							m_vOWNINFOADDRESS[i].tRect.Bottom = nStartH;
					}
					//==========================================================================================

					//전체삭제//
					if(bAllSharp)
					{
						nAllSharp2	= nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x	= nStartW + nTextW/2;
						tempData.tpSTT.y	= nAllSharp1;
						tempData.tpEND.x	= nStartW + nTextW/2;
						tempData.tpEND.y	= nAllSharp2;
						m_vSharpPos.push_back(tempData);
						//bAllSharp	= false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# NAME
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nPartSharp1	= 0;
			nPartSharp2	= 0;
			nAllSharp1	= 0;
			nAllSharp2	= 0;
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[11].gLT);
			tScale	= funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[11].gWH);
			//=========================================================
			//공통//
			nTextW	= pbRect->Canvas->TextWidth("이")/*+1*/;//임의글자로 체크//
			nTextH	= pbRect->Canvas->TextHeight("이")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFONAME.size(); i++)
			{
				asData = m_vOWNINFONAME[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					bAllSharp	= true;
					asData	= asData.Delete(1, 1);
				}
				else
				{
					bAllSharp	= false;
				}
				//=====================================================

				//---
				nTxtLen = asData.Length();

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();

				//개행없는 데이터 처리//
				int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen	= tScale.h/nTextW;
					asTemp	= "";

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asTemp = asTemp	+ asData.SubString(j+1, 2);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								slData->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
							else
							{
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
							}
							j++;
						}
						else
						{
							//================================================
							//211201//#14//
							//개행 문자에 따른 줄바꿈기능//
							//========================================================
							//211201//#4//주소 개행('_')
							if(asData.c_str()[j] == '_')
							{
								slData->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
							else
							//========================================================
							{
								//========================================================
								//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
								}
								//========================================================

								//211101//
		//						if(asData.c_str()[j] == '%')//부분삭제//
		//							continue;
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									//========================================================
									//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if(asData.c_str()[j+1] == '%')
									{
										nLineTxtLen	= nLineTxtLen + 1;
										asTemp = asTemp + asData.SubString(j+2, 1);
										j++;
									}
									//========================================================
									slData->Add(asTemp);
									asTemp	= "";
									nLineTxtCnt	= 0;
								}
								else
								{
									nLineTxtCnt++;
								}
							}
							//================================================
	//						//길이에 따른 자동줄바꿈기능//
	//						//211101//
	////						if(asData.c_str()[j] == '%')//부분삭제//
	////							continue;
	//						asTemp = asTemp + asData.SubString(j+1, 1);
	//						if(nLineTxtCnt >= nLineTxtLen-1)
	//						{
	//							slData->Add(asTemp);
	//							asTemp	= "";
	//							nLineTxtCnt	= 0;
	//						}
	//						else
	//						{
	//							nLineTxtCnt++;
	//						}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						slData->Add(asTemp);
						asTemp	= "";
					}
				}
				//=========================================================

				//======================================
				if(i == 10)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)2*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else if(i == 23)
					nStartW	= tPoint.x - (i-1)*tScale.w - ((double)4*(double)frmMain->m_dDocFactor) - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else
					nStartW	= tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				//======================================
				if(i >= 11)
					nStartW	-= (nMiddleWidth + ((double)2*(double)frmMain->m_dDocFactor));
				//=========================================================

				//==========================================================================================
				m_vOWNINFONAME[i].tRect.Left	= nStartW - nTextW * slData->Count;
				m_vOWNINFONAME[i].tRect.Right = nStartW;
				//==========================================================================================

				for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];

					nTxtLen = asData.Length();

					//=========================================================
					//Height 계산//
					int nSumHeight	= 0;
					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					for(int j = 0; j < asTemp.Length(); j++)
					{
						if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asTemp.SubString(j+1, 2);
							nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
							j++;
						}
						else
						{
							asCaption = asTemp.SubString(j+1, 1);
							nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						}
					}
					//=========================================================

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//nStartH	= tScale.h;//세로쓰기-상단//
					//=========================================================

					//==========================================================================================
					if(z == 0)
					{
						m_vOWNINFONAME[i].tRect.Top 		= nStartH;
						m_vOWNINFONAME[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vOWNINFONAME[i].tRect.Top > nStartH)
							m_vOWNINFONAME[i].tRect.Top = nStartH;
						if(m_vOWNINFONAME[i].tRect.Bottom < nStartH + nSumHeight)
							m_vOWNINFONAME[i].tRect.Bottom = nStartH + nSumHeight;
					}

					if(bAllSharp)//전체삭제//
						nAllSharp1	= nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//41026.1.75//한글이라 2byte이므로 j==1로 체크//
//							{
//								nPartSharp1	= nStartH;
//								nStartH	+= nTextH;//211208
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH+nTextH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								bPartSharp	= true;
								nPartSharp1	= nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
								nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x	= nStartW + nTextW/2;
								tempData.tpSTT.y	= nPartSharp1;
								tempData.tpEND.x	= nStartW + nTextW/2;
								tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1	= nStartH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2	= nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x	= nStartW + nTextW/2;
//								tempData.tpSTT.y	= nPartSharp1;
//								tempData.tpEND.x	= nStartW + nTextW/2;
//								tempData.tpEND.y	= nPartSharp2;
//								m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제//
					if(bAllSharp)
					{
						nAllSharp2	= nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x	= nStartW + nTextW/2;
						tempData.tpSTT.y	= nAllSharp1;
						tempData.tpEND.x	= nStartW + nTextW/2;
						tempData.tpEND.y	= nAllSharp2;
						m_vSharpPos.push_back(tempData);
						//bAllSharp	= false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################
		//Sharp
		//##########################################
		{
			//------------------
			//일반폰트//
			TColor	cPenColorSharp	= (TColor)RGB(255, 0, 0);//부분삭제선//
			HPEN penSharp   = ::CreatePen(PS_SOLID, m_nSharpWidthOverlap, cPenColorSharp);
			HPEN oldPenSharp = (HPEN)::SelectObject(hdc, penSharp);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			//------------------
			TPoint tpStt, tpEnd;
			for(int i = 0; i < (int)m_vSharpPos.size(); i++)
			{
				tpStt	= m_vSharpPos[i].tpSTT;
				tpEnd	= m_vSharpPos[i].tpEND;
				::MoveToEx(hdc, tpStt.x, tpStt.y, NULL);
				::LineTo(hdc, tpEnd.x, tpEnd.y);
			}

			::SetROP2 (hdc, oldro);
			::SelectObject(hdc, oldPenSharp);  // 펜 복구
			::DeleteObject( penSharp );
		}

        // 원래 객체 복구
        ::SelectObject(hdc, oldPen);
        ::SelectObject(hdc, oldFont);
        // 생성 객체 삭제
        ::DeleteObject(pen);
        ::DeleteObject(font);
	}
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcGetStringListShareOwn()
{
	TPoint	tPoint;
	TScale  tScale;

	//##########################################################################################
	// 공통 사용 변수(String, Position)
	//##########################################################################################
	AnsiString 	asData			= "";//한 셀 포함 문자//
	AnsiString 	asCaption 		= "";//TextOut에 표기할 문자//
	AnsiString 	asTemp 			= "";//SubString, 길이체크 용으로 사용할 문자//
	int 		nCellTxtLen 	= 0;
	int 		nLineTxtLen 	= 0;
	int 		nTextW			= 0;
	int 		nTextH			= 0;
	int			nStartW			= 0;
	int			nStartH			= 0;
	int 		nDataKindIdx	= 0;//m_slShareOwnData.indx//231211//
	//==============================================================

 	TPaintBox *pbRect;

	if( !frmMain->m_bAIOCR )//기구축DB 번역본//
		pbRect = frmMain->pbRect2;
	else//AIOCR 번역본//
		pbRect = frmMain->pbRect4;

	//##########################################################################################
	//# CAUTION
	//##########################################################################################
	// Not Have To GetStringList

	//##########################################################################################
	//#
	//# LAND, JIBUN, LEVEL, MEMO
	//#
	//##########################################################################################
	{
		//======================================
		// LAND	//읍면동명, 리명 구분하여 두 줄 처리//
		//======================================
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("동")+1;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("동")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 0;//m_slShareOwnData.indx : 0 (LAND)

		//=========================================================
		if(m_asLand.Length() > 0)
		{
			m_asLand	= StringReplace(m_asLand, " ", "_", TReplaceFlags() << rfReplaceAll);
			asData = m_asLand;

		//##########################################################################################
		// StrringList에 셀>라인별 데이터 저장하기
		//##########################################################################################
			nCellTxtLen = asData.Length();

			//=================================================
			int nPos	= asData.Pos("_");
			while(nPos > 0)
			{
				asTemp 	= asData.SubString(1, nPos-1);
				m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
				asData  = asData.Delete(1, nPos);
				nPos	= asData.Pos("_");
			}
			m_slShareOwnData[nDataKindIdx][0]->Add(asData);

			//==========================================================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][0]->Count;
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);
			//오버랩 이동//
			m_vLAND[0].tRect.Left		= nStartW - nTextW * nSLCount;//소재지:세로쓰기-셀>라인개수//위치가변//
			m_vLAND[0].tRect.Right	= nStartW;//소재지:세로쓰기-셀>라인개수//위치가변//
			m_vLAND[0].tRect.Top 		= nStartH;//소재지:세로쓰기-중간//
			m_vLAND[0].tRect.Bottom	= nStartH;//소재지:세로쓰기-중간//

			for(int z = 0; z < nSLCount; z++)
			{
				asData		= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				nLineTxtLen = asData.Length();

				//=========================================================
				// 실제 표시를 위한 Height 계산//
				//=========================================================
				int nSumHeight	= 0;
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asTemp = asData.SubString(j+1, 2);
						nSumHeight	+= pbRect->Canvas->TextHeight(asTemp);
						j++;
					}
					else
					{
						if(asData.c_str()[j] == '%')//부분삭제//
							continue;
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asData.SubString(j+1, 1);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
					}
				}

				//=========================================================
				//실제 표시 위치//
				//=========================================================
				m_slShareOwnData2[nDataKindIdx][0]->Add(nSumHeight);//StringList별 Height저장//
				//오버랩 이동//
				if(m_vLAND[0].tRect.Top > nStartH)
					m_vLAND[0].tRect.Top = nStartH;//소재지:세로쓰기-중간//
				if(m_vLAND[0].tRect.Bottom < nStartH + nSumHeight)
					m_vLAND[0].tRect.Bottom = nStartH + nSumHeight;//소재지:세로쓰기-중간//
			}//for(int z = 0; z < nSLCount; z++)
		}//# LAND

		//======================================
		// JIBUN
		//======================================
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("번");//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("번");//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 1;//m_slShareOwnData.indx : 1 (JIBUN)

		//=========================================================
		if(m_asJibun.Length() > 0)
		{
			asData 	= m_asJibun;
			if(frmMain->m_nBonbuType == 1)
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
			else if(frmMain->m_nBonbuType == 2)
				asData	= StringReplace(asData, "-", ".", TReplaceFlags() << rfReplaceAll);
			else if(frmMain->m_nBonbuType == 3)
				asData	= StringReplace(asData, "-", "/", TReplaceFlags() << rfReplaceAll);
			else if(frmMain->m_nBonbuType == 4)
				asData	= StringReplace(asData, "-", " - ", TReplaceFlags() << rfReplaceAll);
			else if(frmMain->m_nBonbuType == 5)
				asData	= StringReplace(asData, "-", " | ", TReplaceFlags() << rfReplaceAll);
			else if(frmMain->m_nBonbuType == 6)
				asData	= StringReplace(asData, "-", "의", TReplaceFlags() << rfReplaceAll);

			//---
			m_slShareOwnData[nDataKindIdx][0]->Add(asData);
			asData = m_slShareOwnData[nDataKindIdx][0]->Strings[0];
			nLineTxtLen = asData.Length();

			//=========================================================
			// 실제 표시를 위한 Height 계산//
			//=========================================================
			int nSumHeight	= 0;
			for(int j = 0; j < nLineTxtLen; j++)
			{
				if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
				{
					asCaption = asData.SubString(j+1, 2);
					j++;
				}
				else
				{
					asCaption = asData.SubString(j+1, 1);
				}
				nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
			}

			//=========================================================
			//실제 표시 위치//
			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][0]->Count;
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			nStartW -= nTextW;
			nStartH = funcGetStartH(nDataKindIdx, 0, nSLCount, nSumHeight);
			m_slShareOwnData2[nDataKindIdx][0]->Add(nSumHeight);//StringList별 Height저장//
			//오버랩 이동//
			m_vJIBUN[0].tRect.Left	= nStartW - nTextW * nSLCount;
			m_vJIBUN[0].tRect.Right	= nStartW;
			m_vJIBUN[0].tRect.Top		= nStartH;
			m_vJIBUN[0].tRect.Bottom	= nStartH + nSumHeight;
			//==========================================================================================
		}//# JIBUN


		//======================================
		// LEVEL
		//======================================
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("등")+1;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("등")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 10;//m_slShareOwnData.indx : 10 (LEVEL)

		//==========================================================================================
		tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		//=========================================================
//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
		if(m_asLevel.Length() > 0)
		{
			asData 		= m_asLevel;
			nCellTxtLen	= asData.Length();

		//##########################################################################################
		// StrringList에 셀>라인별 데이터 저장하기
		//##########################################################################################
			//자동개행//
			int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
			int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
			if(nTextW > 0)
			{
				nLineTxtLen	= tScale.h/nTextW;
				asTemp	= "";

				for(int j = 0; j < nCellTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asTemp = asTemp	+ asData.SubString(j+1, 2);
						if(nLineTxtCnt >= nLineTxtLen-1)
						{
							m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
							asTemp	= "";
							nLineTxtCnt	= 0;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++
							if(asData.c_str()[j+2] == '_')
								j++;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++
						}
						else
						{
							nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
						}
						j++;
					}
					else
					{
						//========================================================
						if(asData.c_str()[j] == '_')
						{
							if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
							{
								m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
								//220427//메모 Height 이상이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
								if(asData.c_str()[j+1] == '_')
									j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
							}
						}
						else
						{
							//========================================================
							//211201//#8//메모 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
							if(asData.c_str()[j] == '%')
							{
								nLineTxtLen	= nLineTxtLen + 1;
							}
							//========================================================
							asTemp = asTemp + asData.SubString(j+1, 1);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								//========================================================
								//211201//#8//메모 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j+1] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
									asTemp = asTemp + asData.SubString(j+2, 1);
									j++;
								}
								//========================================================
								m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
								//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
								if(asData.c_str()[j+1] == '_')
									j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
							}
							else
							{
								nLineTxtCnt++;
							}
						}
					}
				}
				if( !asTemp.IsEmpty() )
				{
					m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
					asTemp	= "";
				}
			}

			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][0]->Count;
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);
			//오버랩 이동//
			m_vLEVEL[0].tRect.Left	= nStartW - nTextW * nSLCount;//적요:세로쓰기-셀>라인개수//위치가변//
			m_vLEVEL[0].tRect.Right 	= nStartW;//적요:세로쓰기-셀>라인개수//위치가변//
			m_vLEVEL[0].tRect.Top 	= nStartH;//적요:세로쓰기-상단//위치고정//
			m_vLEVEL[0].tRect.Bottom	= nStartH;//적요:세로쓰기-상단//위치고정//

			for(int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//
				nLineTxtLen = asData.Length();

				//=========================================================
				// 실제 표시를 위한 Height 계산//
				//=========================================================
				int nSumHeight	= 0;
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						j++;
					}
					else
					{
						if(asData.c_str()[j] == '%')//부분삭제//
							continue;
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asData.SubString(j+1, 1);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
					}
				}
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				m_slShareOwnData2[nDataKindIdx][0]->Add(nSumHeight);//StringList별 Height저장//
				//오버랩 이동//
				if(m_vLEVEL[0].tRect.Bottom < nStartH + nSumHeight)
					m_vLEVEL[0].tRect.Bottom = nStartH + nSumHeight;//적요:세로쓰기-상단//
			}//for(int z = 0; z < nSLCount; z++)
		}//# LEVEL




		//======================================
		// MEMO
		//======================================
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("메")+1;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("메")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 2;//m_slShareOwnData.indx : 2 (MEMO)

		//==========================================================================================
		tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		//=========================================================
//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
		if(m_asMemo.Length() > 0)
		{
			asData 		= m_asMemo;
			nCellTxtLen	= asData.Length();

		//##########################################################################################
		// StrringList에 셀>라인별 데이터 저장하기
		//##########################################################################################
			//자동개행//
			int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
			int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
			if(nTextW > 0)
			{
				nLineTxtLen	= tScale.h/nTextW;
				asTemp	= "";

				for(int j = 0; j < nCellTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asTemp = asTemp	+ asData.SubString(j+1, 2);
						if(nLineTxtCnt >= nLineTxtLen-1)
						{
							m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
							asTemp	= "";
							nLineTxtCnt	= 0;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++
							if(asData.c_str()[j+2] == '_')
								j++;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++
						}
						else
						{
							nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
						}
						j++;
					}
					else
					{
						//========================================================
						if(asData.c_str()[j] == '_')
						{
							if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
							{
								m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
								//220427//메모 Height 이상이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
								if(asData.c_str()[j+1] == '_')
									j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
							}
						}
						else
						{
							//========================================================
							//211201//#8//메모 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
							if(asData.c_str()[j] == '%')
							{
								nLineTxtLen	= nLineTxtLen + 1;
							}
							//========================================================
							asTemp = asTemp + asData.SubString(j+1, 1);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								//========================================================
								//211201//#8//메모 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j+1] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
									asTemp = asTemp + asData.SubString(j+2, 1);
									j++;
								}
								//========================================================
								m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
								//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
								if(asData.c_str()[j+1] == '_')
									j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
							}
							else
							{
								nLineTxtCnt++;
							}
						}
					}
				}
				if( !asTemp.IsEmpty() )
				{
					m_slShareOwnData[nDataKindIdx][0]->Add(asTemp);
					asTemp	= "";
				}
			}

			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][0]->Count;
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);
			//오버랩 이동//
			m_vMEMO[0].tRect.Left		= nStartW - nTextW * nSLCount;//적요:세로쓰기-셀>라인개수//위치가변//
			m_vMEMO[0].tRect.Right 	= nStartW;//적요:세로쓰기-셀>라인개수//위치가변//
			m_vMEMO[0].tRect.Top 		= nStartH;//적요:세로쓰기-상단//위치고정//
			m_vMEMO[0].tRect.Bottom	= nStartH;//적요:세로쓰기-상단//위치고정//

			for(int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//
				nLineTxtLen = asData.Length();

				//=========================================================
				// 실제 표시를 위한 Height 계산//
				//=========================================================
				int nSumHeight	= 0;
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						j++;
					}
					else
					{
						if(asData.c_str()[j] == '%')//부분삭제//
							continue;
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asData.SubString(j+1, 1);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
					}
				}
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				m_slShareOwnData2[nDataKindIdx][0]->Add(nSumHeight);//StringList별 Height저장//
				//오버랩 이동//
				if(m_vMEMO[0].tRect.Bottom < nStartH + nSumHeight)
					m_vMEMO[0].tRect.Bottom = nStartH + nSumHeight;//적요:세로쓰기-상단//
			}//for(int z = 0; z < nSLCount; z++)
		}//# MEMO
	}//# LAND, JIBUN, LEVEL, MEMO


	//##########################################################################################
	//#
	//# DATE
	//#
	//##########################################################################################
	{
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("일")+1;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("일")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 3;//m_slShareOwnData.indx : 3 (DATE)
		//==============================================================

		//==========================================================================================
		//일자:내용별개행고정//NotUsed//tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[3].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		for( int i = 0; i < (int)m_vSHAREOWNDATE.size(); i++)
		{
			asData = m_vSHAREOWNDATE[i].DATA;
			if(asData == "-")//NoData
				continue;

			//=====================================================
			//211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
//			asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
			//=====================================================
			asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
			asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
			asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

			//=====================================================
			//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
			if(asData != "판독불가")
			//=====================================================
			{
				//260530//
				if( !frmMain->m_bAIOCR )//기구축DB 번역본//
				{
					asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
					asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
				}
				else//AIOCR 번역본//
				{
					AnsiString  _asData = asData;
					asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
					if(asData == "Error")
						asData = _asData;
					else
						asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
				}
			}

		//##########################################################################################
		// StrringList에 셀>라인별 데이터 저장하기
		//##########################################################################################
			nCellTxtLen = asData.Length();
			//일자에는 개행하지 않음//
			if(nCellTxtLen > 0)
			{
				//=====================================================
				//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
				if(asData != "판독불가")
				//=====================================================
				{
					//년도//
					int nPos 	= asData.AnsiPos("년");
					asTemp 	= asData.SubString(1, nPos+1);
					m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
					asData  = asData.Delete(1, nPos+1);
					//월일//
					asTemp 	= asData;
					//211216//도청김훈곤주무관Req//Date에 5줄로 맞춰달라//
					asTemp	= StringReplace(asTemp, "월", "월 ", TReplaceFlags() << rfReplaceAll);
					//====================================================
					//211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
					if(asTemp.AnsiPos("월") == 0)
						asTemp	= " 월" + asTemp;
					if(asTemp.AnsiPos("일") == 0)
						asTemp	= asTemp + " 일";
					//====================================================
					m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
				}
				//=====================================================
				//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
				else
				{
					m_slShareOwnData[nDataKindIdx][i]->Add("판 독");
					m_slShareOwnData[nDataKindIdx][i]->Add("불 가");
				}
				//=====================================================
			}


			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][i]->Count;
			nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
			nStartH = funcGetStartW(nDataKindIdx, i, 0, nTextH);
			//오버랩 이동//
			m_vSHAREOWNDATE[i].tRect.Left		= nStartW - nTextW * nSLCount;//일자:세로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNDATE[i].tRect.Right 	= nStartW;//일자:세로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNDATE[i].tRect.Top 		= nStartH;//일자:세로쓰기-중간//위치가변//
			m_vSHAREOWNDATE[i].tRect.Bottom 	= nStartH;//일자:세로쓰기-중간//위치가변//

			for(int z = 0; z < nSLCount; z++)
			{
				asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
				nLineTxtLen = asData.Length();

				//=========================================================
				// 실제 표시를 위한 Height 계산//
				//=========================================================
				int nSumHeight	= 0;
				asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				for(int j = 0; j < asTemp.Length(); j++)
				{
					if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asTemp.SubString(j+1, 2);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asTemp.Length() && (asTemp.c_str()[j] >= '0' && asTemp.c_str()[j] <= '9'))
						{
							if(asTemp.c_str()[j+1] >= '0' && asTemp.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asTemp.SubString(j+1, 2);
								nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asTemp.SubString(j+1, 1);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
					}
				}
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
				m_slShareOwnData2[nDataKindIdx][i]->Add(nSumHeight);//StringList별 Height저장//
				//오버랩 이동//
				if(m_vSHAREOWNDATE[i].tRect.Top > nStartH)
					m_vSHAREOWNDATE[i].tRect.Top = nStartH;//일자:세로쓰기-중간//위치가변//
				if(m_vSHAREOWNDATE[i].tRect.Bottom < nStartH + nSumHeight)
					m_vSHAREOWNDATE[i].tRect.Bottom = nStartH + nSumHeight;//일자:세로쓰기-중간//위치가변//
			}//for(int z = 0; z < nSLCount; z++)
		}//for( int i = 0; i < (int)m_vSHAREOWNDATE.size(); i++)
	}//# DATE//



	//##########################################################################################
	//#
	//# REASON
	//#
	//##########################################################################################
	{
		//231121//하단 주석처리(중복제거 후 표시)//
		AnsiString  asSymbol[10] = {"⑴", "⑵", "⑶", "⑷", "⑸", "⑹", "⑺", "⑻", "⑼", "⑽"};

		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("사")/*+1*/;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("사")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 4;//m_slShareOwnData.indx : 4 (REASON)
		//==============================================================

		//==========================================================================================
		tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		for( int i = 0; i < (int)m_vSHAREOWNREASON.size(); i++)
		{
			asData = m_vSHAREOWNREASON[i].DATA;
			if(asData == "-")//NoData
				continue;

			//=====================================================
			asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
			asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
			//asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
			//asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

			//241114//
			//=====================================================
			//소유권이전, 소유권보존 자동개행처리//
			AnsiString  asTmp1	= "";
			AnsiString  asTmp2	= "";
			for(int r = 0; r < (int)frmMain->m_vREASONDATA.size(); r++)
			{
				asTmp1	= frmMain->m_vREASONDATA[r].DATA;
				asTmp2	= StringReplace(asTmp1, "_", "", TReplaceFlags() << rfReplaceAll);
				asTmp2	= StringReplace(asTmp2, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(m_vREASONDATA)를 제외하고는 공백처리하지 않음//
				if(asData.AnsiPos(asTmp2))
				{
					asData	= StringReplace(asData, asTmp2, asTmp1, TReplaceFlags() << rfReplaceAll);
				}
			}
			//=====================================================

			//##########################################################################################
			// StrringList에 셀>라인별 데이터 저장하기
			//##########################################################################################
			nCellTxtLen = asData.Length();

			//개행없는 데이터 처리//
			int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
			int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
			if(nTextW > 0)
			{
				nLineTxtLen	= tScale.h/nTextW;
				asTemp	= "";

				//=================================================================================
				//주석처리//211229//
				asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				if(asTemp.Length() >= 20)
				//211229//if(asData.Length() >= 20)//asData.Pos("법률") > 0 || asData.Pos("분배농지") > 0)
				{
					asTemp	= "";//211229//

					bool bFound	= false;
					for(int k = 0; k < m_slShareOwnData[9][0]->Count; k++)
					{
						AnsiString  asCmt1 = "";
						AnsiString  asCmt2 = "";
						asCmt1 = m_slShareOwnData[9][0]->Strings[k];
						asCmt1 = asCmt1.SubString(3, asCmt1.Length()-1);
						asCmt2 = asData;
						asCmt2	= StringReplace(asCmt2, "_", "", TReplaceFlags() << rfReplaceAll);
						asCmt2  = StringReplace(asCmt2, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(m_vREASONDATA)를 제외하고는 공백처리하지 않음//

						if(asCmt1 == asCmt2)
						{
							bFound = true;
							m_slShareOwnData[nDataKindIdx][i]->Add("하단기재");//211216//도청김훈곤주무관Req//주석:하단기재//41023.628
							m_slShareOwnData[nDataKindIdx][i]->Add(asSymbol[k]);
							break;
						}
					}

					if( !bFound )//기존 주석 유형과 다른 경우 새로 추가//
					{
						m_slShareOwnData[nDataKindIdx][i]->Add("하단기재");//211216//도청김훈곤주무관Req//주석:하단기재//41023.628
						m_slShareOwnData[nDataKindIdx][i]->Add(asSymbol[m_slShareOwnData[9][0]->Count]);

						asData	= StringReplace(asData, "_", "", TReplaceFlags() << rfReplaceAll);
						asData  = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(m_vREASONDATA)를 제외하고는 공백처리하지 않음//
						asData  = asSymbol[m_slShareOwnData[9][0]->Count] + asData;
						m_slShareOwnData[9][0]->Add(asData);
					}
				}
				//=================================================================================
				else//일반적인 데이터//
				{
					//개행 문자에 따른 줄바꿈기능//
					int nPos    = asData.Pos("_");
					if(nPos > 0)
					{
						while(nPos > 0)
						{
							asTemp     = asData.SubString(1, nPos-1);
							m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
							asData  = asData.Delete(1, nPos);
							nPos    = asData.Pos("_");
						}
						if( !asData.IsEmpty() )
							m_slShareOwnData[nDataKindIdx][i]->Add(asData);
					}
//=============================================================================
//231116//개행없는 데이터 처리//
					else
					{
						asTemp = "";
						for(int j = 0; j < nCellTxtLen; j++)
						{
							if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
							{
								asTemp = asTemp    + asData.SubString(j+1, 2);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
									asTemp    = "";
									nLineTxtCnt    = 0;
								}
								else
								{
									nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
								}
								j++;
							}
							else
							{
								//================================================
								//개행 문자에 따른 줄바꿈기능//
								//========================================================
								if(asData.c_str()[j] == '_')
								{
									m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
									asTemp    = "";
									nLineTxtCnt    = 0;
								}
								else
								//========================================================
								{
									//========================================================
									//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if(asData.c_str()[j] == '%')
									{
										nLineTxtLen    = nLineTxtLen + 1;
									}
									//========================================================

									asTemp = asTemp + asData.SubString(j+1, 1);
									if(nLineTxtCnt >= nLineTxtLen-1)
									{
										//========================================================
										//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
										if(asData.c_str()[j+1] == '%')
										{
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
										//========================================================
										m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
										asTemp    = "";
										nLineTxtCnt    = 0;
									}
									else
									{
										nLineTxtCnt++;
									}
								}
							}
						}
						if( !asTemp.IsEmpty() )
						{
							m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
							asTemp    = "";
						}
					}
				}
			}


			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][i]->Count;
			nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, i, 0, 0);//사고:세로쓰기-중간
			//오버랩 이동//
			m_vSHAREOWNREASON[i].tRect.Left	= nStartW - nTextW * nSLCount;
			m_vSHAREOWNREASON[i].tRect.Right 	= nStartW;
			m_vSHAREOWNREASON[i].tRect.Top 	= nStartH;//사고:세로쓰기-중간//위치가변//
			m_vSHAREOWNREASON[i].tRect.Bottom = nStartH + tScale.h;//사고:세로쓰기-중간//위치가변//

			for(int z = 0; z < nSLCount; z++)
			{
				asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
				nLineTxtLen	= asData.Length();

				//=========================================================
				// 실제 표시를 위한 Height 계산//
				//=========================================================
				int nSumHeight	= 0;
				asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				for(int j = 0; j < asTemp.Length(); j++)
				{
					if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asTemp.SubString(j+1, 2);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
						j++;
					}
					else
					{
						asCaption = asTemp.SubString(j+1, 1);
						nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
					}
				}
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);//사고:세로쓰기-중간
				m_slShareOwnData2[nDataKindIdx][i]->Add(nSumHeight);//StringList별 Height저장//
				//오버랩 이동//
				if(m_vSHAREOWNREASON[i].tRect.Top > nStartH)
					m_vSHAREOWNREASON[i].tRect.Top = nStartH;//사고:세로쓰기-중간//위치가변//
				if(m_vSHAREOWNREASON[i].tRect.Bottom < nStartH + nSumHeight)
					m_vSHAREOWNREASON[i].tRect.Bottom = nStartH + nSumHeight;//사고:세로쓰기-중간//위치가변//
			}//for(int z = 0; z < nSLCount; z++)
		}

		//======================================================
		// 주석표시//
		nDataKindIdx	= 9;//m_slShareOwnData.indx : 9 (COMMENT)

		for(int z = 0; z < m_slShareOwnData[nDataKindIdx][0]->Count; z++)
		{
			asData		= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
			asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
			//오버랩 이동//231207//
			DATA_STRUCT		tempV;
			memset(&tempV, 0x00, sizeof(DATA_STRUCT));
			tempV.tRect.Left	= nStartW;
			tempV.tRect.Right 	= nStartW + pbRect->Canvas->TextWidth(asData);
			tempV.tRect.Top 	= nStartH;//주석:가로쓰기//
			tempV.tRect.Bottom 	= nStartH + pbRect->Canvas->TextHeight(asData)+1;//주석:가로쓰기//
			strcpy(tempV.DATA, asData.c_str());
			m_vSHARECOMMENT.push_back(tempV);
		}
	}



	//##########################################################################################
    //#
	//# RATIO
	//#
    //##########################################################################################
    {
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= 0;//아래에서 개별적으로//
		nTextH		= 0;//아래에서 개별적으로//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 5;//m_slShareOwnData.indx : 5 (RATIO)
		//==============================================================

		//==========================================================================================
		tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		for( int i = 0; i < (int)m_vSHAREOWNRATIO.size(); i++)
        {
//=============================================================================
//231114//위치이동//가로쓰기-자동개행은 처음이라//
//데이터 작업 전 한번 체크하고 가로쓰기 가운데정렬 맞추려고//
//for-loop 안에서 pbRect->Canvas->TextWidth를 다시해서 값이 틀어지므로//
//for-loop 안에서 체크하도록 위치 수정//
			nTextW	= pbRect->Canvas->TextWidth("분")+1;//임의글자로 체크//
			nTextH  = pbRect->Canvas->TextHeight("분")+1;//임의글자로 체크//
			nTextW  = nTextW/2;
//=============================================================================

			asData = m_vSHAREOWNRATIO[i].DATA;
            if(asData == "-")//NoData
                continue;

            //=====================================================
            asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
//				asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
			//=====================================================

			//##########################################################################################
			// StrringList에 셀>라인별 데이터 저장하기
			//##########################################################################################
			//가로쓰기-중간-개행//=========================================================================
			//---
			nCellTxtLen = asData.Length();

			//=============================================================
			//개행 문자에 따른 줄바꿈기능//
			int nPos    = asData.Pos("_");
			if(nPos > 0)
			{
				while(nPos > 0)
				{
					asTemp     = asData.SubString(1, nPos-1);
					m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
					asData  = asData.Delete(1, nPos);
					nPos    = asData.Pos("_");
				}
				if( !asData.IsEmpty() )
					m_slShareOwnData[nDataKindIdx][i]->Add(asData);
			}
			else//개행없는 데이터 처리//
			{
				int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(nTextW > 0)
				{
					nLineTxtLen    = tScale.w/(nTextW+1);
					asTemp    = "";

					//길이에 따른 자동줄바꿈기능//
					for(int j = 0; j < nCellTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							AnsiString  asPartStr = asData.SubString(j+1, 4);
							if(asPartStr == "분지" || asPartStr == "분의" || asPartStr == "지분")
							{
	//=============================================================================
	//231208//
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);//231208//
								asTemp = asPartStr;
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
								asTemp    = "";
								nLineTxtCnt    = 0;
								j += 3;
	//=============================================================================
							}
							else
							{
								asTemp = asTemp    + asData.SubString(j+1, 2);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
									asTemp    = "";
									nLineTxtCnt    = 0;
								}
								else
								{
									nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
								}
								j++;
							}
						}
						else
						{
							if(asData.c_str()[j] == '%')//부분삭제//
								continue;
							asTemp = asTemp + asData.SubString(j+1, 1);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
								asTemp    = "";
								nLineTxtCnt    = 0;
							}
							else
							{
								nLineTxtCnt++;
							}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
						asTemp    = "";
					}
				}
			}//개행없는 데이터 처리//
			//가로쓰기-중간-개행//==========================================================================================

			//=========================================================
			//실제 표시 위치//
			//=========================================================
			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][i]->Count;
			nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, i, nSLCount, nTextH);//지분:가로쓰기-중간//
			//오버랩 이동//
			m_vSHAREOWNRATIO[i].tRect.Left	= nStartW;//지분:가로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNRATIO[i].tRect.Right 	= nStartW;//지분:가로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNRATIO[i].tRect.Top 	= nStartH;//지분:가로쓰기-중간//위치가변//
			m_vSHAREOWNRATIO[i].tRect.Bottom 	= nStartH + nTextH * nSLCount;//지분:가로쓰기-중간//위치가변//

			for(int z = 0; z < nSLCount; z++)
			{
				asData    	= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
				nLineTxtLen = asData.Length();

				asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
				nTextW    = pbRect->Canvas->TextWidth(asTemp);
				//오버랩 이동//
				m_vSHAREOWNRATIO[i].tRect.Right 	= nStartW + nTextW;//지분:가로쓰기-셀>라인개수//위치가변//
			}//for(int z = 0; z < nSLCount; z++)
		}
	}



	//##########################################################################################
	//#
	//# ADDRESS
	//#
	//##########################################################################################
	{
		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("주")/*+1*/;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("주")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 6;//m_slShareOwnData.indx : 6 (ADDRESS)
		//==========================================================================================

		//==========================================================================================
		tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		//==========================================================================================
		for( int i = 0; i < (int)m_vSHAREOWNADDRESS.size(); i++)
		{
			asData = m_vSHAREOWNADDRESS[i].DATA;
			if(asData == "-")//NoData
				continue;

			//=====================================================
			asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
			asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
			//211201//#6//주소에서 괄호삭제 기능 제거//41026.1.186.2
//			asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
//			asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

			//##########################################################################################
			// StrringList에 셀>라인별 데이터 저장하기
			//##########################################################################################
			//---
			nCellTxtLen = asData.Length();

			//개행없는 데이터 처리//
			int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
			int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
			if(nTextW > 0)
			{
				nLineTxtLen	= tScale.h/nTextW;
				asTemp	= "";

				for(int j = 0; j < nCellTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asTemp = asTemp	+ asData.SubString(j+1, 2);
						if(nLineTxtCnt >= nLineTxtLen-1)
						{
							m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
							asTemp	= "";
							nLineTxtCnt	= 0;
						}
						else
						{
							nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
						}
						j++;
					}
					else
					{
						//========================================================
						//211201//#4//주소 개행('_')
						if(asData.c_str()[j] == '_')
						{
							if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
							{
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
						}
						else
						{
							//========================================================
							//211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
							if(asData.c_str()[j] == '%')
							{
								nLineTxtLen	= nLineTxtLen + 1;
							}
							//========================================================
							asTemp = asTemp + asData.SubString(j+1, 1);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								//========================================================
								//211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j+1] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
									asTemp = asTemp + asData.SubString(j+2, 1);
									j++;
								}
								//========================================================
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
							else
							{
								nLineTxtCnt++;
							}
						}
					}
				}
				if( !asTemp.IsEmpty() )
				{
					m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
					asTemp	= "";
				}
			}


			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][i]->Count;
			nStartW	= funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, i, 0, 0);//세로쓰기-상단//
			//오버랩 이동//
			m_vSHAREOWNADDRESS[i].tRect.Left		= nStartW - nTextW * nSLCount;//세로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNADDRESS[i].tRect.Right 	= nStartW;//세로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNADDRESS[i].tRect.Top 		= nStartH;//주소:세로쓰기-상단//위치고정//
			m_vSHAREOWNADDRESS[i].tRect.Bottom 	= nStartH + tScale.h;//사고:세로쓰기-중간//위치가변//

			for(int z = 0; z < nSLCount; z++)
			{
				asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
				nLineTxtLen = asData.Length();

				m_slShareOwnData2[nDataKindIdx][i]->Add(nStartH - m_vSHAREOWNADDRESS[i].tRect.Top);

				//오버랩 이동//세로쓰기-높이는 글자길이에 따르는데 nLineTxtLen을 체크해봐야 알기에 셀>라인별 가장 긴 Height로 저장//
				if(m_vSHAREOWNADDRESS[i].tRect.Bottom < nStartH)
					m_vSHAREOWNADDRESS[i].tRect.Bottom = nStartH;//세로쓰기//위치가변//
			}//for(int z = 0; z < nSLCount; z++)
		}
	}



	//##########################################################################################
	//#
	//# NAME
	//#
	//##########################################################################################
	{

		//==============================================================
		asData		= "";//한 셀 포함 문자//
		asCaption 	= "";//TextOut에 표기할 문자//
		asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		nCellTxtLen = 0;
		nLineTxtLen = 0;
		nTextW		= pbRect->Canvas->TextWidth("이")/*+1*/;//임의글자로 체크//
		nTextH		= pbRect->Canvas->TextHeight("이")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 7;//m_slShareOwnData.indx : 7 (NAME)
		//==========================================================================================

		//==========================================================================================
		tScale	= funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
		//==========================================================================================

		//==========================================================================================
		for( int i = 0; i < (int)m_vSHAREOWNNAME.size(); i++)
		{
			asData = m_vSHAREOWNNAME[i].DATA;
			if(asData == "-")//NoData
				continue;

			asData = eFunc->funcStringReplaceDoc08(asData);//260518//

			//##########################################################################################
			// StrringList에 셀>라인별 데이터 저장하기
			//##########################################################################################
			//---
			nCellTxtLen = asData.Length();

			//개행없는 데이터 처리//
			int nLineTxtLen	= 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
			int nLineTxtCnt	= 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
			if(nTextW > 0)
			{
				nLineTxtLen	= tScale.h/nTextW;
				asTemp	= "";

				for(int j = 0; j < nCellTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asTemp = asTemp	+ asData.SubString(j+1, 2);
						if(nLineTxtCnt >= nLineTxtLen-1)
						{
							m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
							asTemp	= "";
							nLineTxtCnt	= 0;
						}
						else
						{
							nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
						}
						j++;
					}
					else
					{
						//========================================================
						//211201//#4//개행('_')
						if(asData.c_str()[j] == '_')
						{
							if( !asTemp.IsEmpty() )//211208//31025.2.20.2//개행과 길이자동개행이 복합//
							{
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
						}
						else
						{
							//========================================================
							//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
							if(asData.c_str()[j] == '%')
							{
								nLineTxtLen	= nLineTxtLen + 1;
							}
							//========================================================
							asTemp = asTemp + asData.SubString(j+1, 1);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								//========================================================
								//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j+1] == '%')
								{
									nLineTxtLen	= nLineTxtLen + 1;
									asTemp = asTemp + asData.SubString(j+2, 1);
									j++;
								}
								//========================================================
								m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
							else
							{
								nLineTxtCnt++;
							}
						}
					}
				}
				if( !asTemp.IsEmpty() )
				{
					m_slShareOwnData[nDataKindIdx][i]->Add(asTemp);
					asTemp	= "";
				}
			}


			//=========================================================
			int nSLCount	= m_slShareOwnData[nDataKindIdx][i]->Count;
			nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
			nStartH = funcGetStartH(nDataKindIdx, i, 0, 0);//소유자명:세로쓰기-중간//
			//오버랩 이동//
			m_vSHAREOWNNAME[i].tRect.Left		= nStartW - nTextW * nSLCount;//세로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNNAME[i].tRect.Right	= nStartW;//세로쓰기-셀>라인개수//위치가변//
			m_vSHAREOWNNAME[i].tRect.Top 		= nStartH;//이름:세로쓰기-중간//위치가변//
			m_vSHAREOWNNAME[i].tRect.Bottom 	= nStartH;//이름:세로쓰기-중간//위치가변//

			for(int z = 0; z < nSLCount; z++)
			{
				asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
				nLineTxtLen = asData.Length();

				//=========================================================
				// 실제 표시를 위한 Height 계산//소유자명:세로쓰기-중간//
				//=========================================================
				int nSumHeight	= 0;
				asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
				for(int j = 0; j < asTemp.Length(); j++)
				{
					if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asTemp.SubString(j+1, 2);
						j++;
					}
					else
					{
						asCaption = asTemp.SubString(j+1, 1);
					}
					nSumHeight	+= pbRect->Canvas->TextHeight(asCaption);
				}

				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);//소유자명:세로쓰기-중간//
				m_slShareOwnData2[nDataKindIdx][i]->Add(nSumHeight);//StringList별 Height저장//
				if(m_vSHAREOWNNAME[i].tRect.Top > nStartH)
					m_vSHAREOWNNAME[i].tRect.Top = nStartH;//소유자명:세로쓰기-중간//위치가변//
				if(m_vSHAREOWNNAME[i].tRect.Bottom < nStartH + nSumHeight)
					m_vSHAREOWNNAME[i].tRect.Bottom = nStartH + nSumHeight;//소유자명:세로쓰기-중간//위치가변//
			}//for(int z = 0; z < nSLCount; z++)
		}
	}
}
//---------------------------------------------------------------------------

/*
void __fastcall classDOC08Data::funcRedrawShareOwn()
{
	int fontwidth		= frmMain->m_nFontSize;
	int fontheight 		= fontwidth;
	int nMiddleWidth	= (int)((double)frmMain->bpMiddleW * (double)frmMain->m_dDocFactor);
	TPoint	tPoint;//221214//#DOC8_OVERLAP//
	TScale  tScale;

	if(frmMain->tcmpPaintBox[4]->Visible && m_slShareOwnData != NULL)
	{
		//##########################################################################################
		// 공통 사용 변수(PaintBox)
		//##########################################################################################
		HDC 	hdc 			= frmMain->tcmpPaintBox[4]->Canvas->Handle;
		HPEN 	pen;
		//지번폰트//
		HFONT   m_font, m_fontL;
		HFONT 	hOldFont, hOldFontL;
		HFONT 	m_fontRatio, hOldFontRatio;//소유권보합폰트//231208//
		TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
		TColor	cPenColor		= frmMain->tcmpPaintBox[4]->Color;//221128//#SHAREOWN_OVERLAY//History, OwnInfo
		int 	oldro;

		//##########################################################################################
		// 공통 사용 변수(String, Position)
		//##########################################################################################
		AnsiString 	asData		= "";//한 셀 포함 문자//
		AnsiString 	asCaption 	= "";//TextOut에 표기할 문자//
		int 		nLineTxtLen	= 0;
		int 		nTextW		= 0;
		int 		nTextH		= 0;
		int			nStartW		= 0;
		int			nStartH		= 0;
		//==============================================================
		int 		nSLCount	= 0;
		int			nSumHeight	= 0;
		int 		nDataKindIdx	= 0;//m_slShareOwnData.indx

		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);

		//=====================================================================
		//(CAUTION) 데이터에만 사용//
		//=====================================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColorC);
		::SelectObject(hdc, pen);
		oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, cPenColorC);
		//frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;

		//##########################################################################################
		//#
		//# CAUTION
		//#
		//##########################################################################################
		{
			nDataKindIdx	= 8;
			//=================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[nDataKindIdx].gLT);
			int nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(m_vCAUTION[0].DATA)+1;
			int nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(m_vCAUTION[0].DATA)+1;
			m_vCAUTION[0].tRect.Left 		= tPoint.x;
			m_vCAUTION[0].tRect.Top 		= tPoint.y;
			m_vCAUTION[0].tRect.Right		= tPoint.x + nTextW;
			m_vCAUTION[0].tRect.Bottom	= tPoint.y + nTextH;

			//=================================================================
			// 좌측하단 문구표시//
			frmMain->tcmpPaintBox[4]->Canvas->TextOutA(tPoint.x, tPoint.y, m_vCAUTION[0].DATA);

			//=================================================================
			::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}



		//##########################################################################################
		//#
		//# LAND, JIBUN, LEVEL, MEMO
		//#
		//##########################################################################################

		//=====================================================================
		//(소재지, 지번) 데이터에만 사용//	//211216//도청김훈곤주무관Req//지번폰트크게//
		//=====================================================================
		m_fontL	= ::CreateFont(fontwidth+2, 0, 0, 0, 900, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontL  = (HFONT)::SelectObject(hdc, m_fontL);

		//==============================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
		::SelectObject(hdc, pen);
		oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, cPenColor);
		//frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;

		//==============================================================
		{
			//==============================================================
			// LAND
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("동")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("동")+1;//임의글자로 체크//
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 0;//m_slShareOwnData.indx : 0 (LAND)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vLAND[0].tRect.Left		= nStartW - nTextW * nSLCount;
			m_vLAND[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//231211//#DELETEPOS//
				nLineTxtLen = asData.Length();

				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, nSumHeight);//세로쓰기-중간//
				//==========================================================================================
				if(z == 0)
				{
					m_vLAND[0].tRect.Top 		= nStartH;
					m_vLAND[0].tRect.Bottom	= nStartH + nSumHeight;
					//
					frmMain->imgDoc08Mover4->Left	= m_vLAND[0].tRect.Right + 32;//minji@230310//사장님REQ//
					frmMain->imgDoc08Mover4->Top	= m_vLAND[0].tRect.Top;
				}
				else
				{
					if(m_vLAND[0].tRect.Top > nStartH)
						m_vLAND[0].tRect.Top = nStartH;
					if(m_vLAND[0].tRect.Bottom < nStartH + nSumHeight)
						m_vLAND[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//=========================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					//---
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						j++;
					}
					else
					{
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
					}

					nStartH	+= nTextH;
				}
			}//for(int z = 0; z < nSLCount; z++)

			//======================================
			// JIBUN
			//======================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("번")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("번")+1;//임의글자로 체크//
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 1;//m_slShareOwnData.indx : 1 (JIBUN)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vJIBUN[0].tRect.Left	= nStartW - nTextW * nSLCount;
			m_vJIBUN[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				nLineTxtLen = asData.Length();

				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, nSumHeight);//세로쓰기-중간//
				if(z == 0)
				{
					m_vJIBUN[0].tRect.Top 	= nStartH;
					m_vJIBUN[0].tRect.Bottom	= nStartH + nSumHeight;
				}
				else
				{
					if(m_vJIBUN[0].tRect.Top > nStartH)
						m_vJIBUN[0].tRect.Top = nStartH;
					if(m_vJIBUN[0].tRect.Bottom < nStartH + nSumHeight)
						m_vJIBUN[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//=========================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						j++;
					}
					else
					{
						if(asData.c_str()[j] =='%')
						{
							continue;
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
					}
					nStartH	+= nTextH+1;
				}
			}//for(int z = 0; z < nSLCount; z++)
			//# JIBUN


			//=================================================================
			//241203//#등급#추가//
			//=================================================================
			//======================================
			// LEVEL
			//======================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("등")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("등")+1;//임의글자로 체크//
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 10;//m_slShareOwnData.indx : 10 (LEVEL)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vLEVEL[0].tRect.Left	= nStartW - nTextW * nSLCount;
			m_vLEVEL[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//231211//#DELETEPOS//
				nLineTxtLen = asData.Length();
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);//세로쓰기-상단//
				if(z == 0)
				{
					m_vLEVEL[0].tRect.Top 	= nStartH;
					m_vLEVEL[0].tRect.Bottom	= nStartH + nSumHeight;
				}
				else
				{
					if(m_vLEVEL[0].tRect.Top > nStartH)
						m_vLEVEL[0].tRect.Top = nStartH;
					if(m_vLEVEL[0].tRect.Bottom < nStartH + nSumHeight)
						m_vLEVEL[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//==========================================================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
					}

					nStartH	+= nTextH;
				}
			}//for(int z = 0; z < nSLCount; z++)



			//======================================
			// MEMO
			//======================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("메")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("메")+1;//임의글자로 체크//
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 2;//m_slShareOwnData.indx : 2 (MEMO)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vMEMO[0].tRect.Left		= nStartW - nTextW * nSLCount;
			m_vMEMO[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//231211//#DELETEPOS//
				nLineTxtLen = asData.Length();
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);//세로쓰기-상단//
				if(z == 0)
				{
					m_vMEMO[0].tRect.Top 	= nStartH;
					m_vMEMO[0].tRect.Bottom	= nStartH + nSumHeight;
				}
				else
				{
					if(m_vMEMO[0].tRect.Top > nStartH)
						m_vMEMO[0].tRect.Top = nStartH;
					if(m_vMEMO[0].tRect.Bottom < nStartH + nSumHeight)
						m_vMEMO[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//==========================================================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
					}

					nStartH	+= nTextH;
				}
			}//for(int z = 0; z < nSLCount; z++)
		}
		// LAND, JIBUN, LEVEL, MEMO
		::SetROP2 (hdc, oldro);
		::DeleteObject( pen );



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);

		//==============================================================
		//(TB_DOCUMENT08_SHAREOWN) 데이터에 공통//
		//==============================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
		::SelectObject(hdc, pen);
		oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, cPenColor);
		//frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;
		//==============================================================

		//##########################################################################################
		//#
		//# DATE
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("일")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("일")+1;//임의글자로 체크//
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 3;//m_slShareOwnData.indx : 3 (DATE)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNDATE.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNDATE[i].tRect.Left	    = nStartW - nTextW * nSLCount;
				m_vSHAREOWNDATE[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();

					//=========================================================
					//실제 표시 위치//
					//=========================================================
					nStartW	-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNDATE[i].tRect.Top 		= nStartH;
						m_vSHAREOWNDATE[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNDATE[i].tRect.Top > nStartH)
							m_vSHAREOWNDATE[i].tRect.Top = nStartH;
						if(m_vSHAREOWNDATE[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNDATE[i].tRect.Bottom = nStartH + nSumHeight;
					}

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
		}



		//##########################################################################################
		//#
		//# REASON
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("사")+1;//임의글자로 체크//;
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("사")+1;//임의글자로 체크//;
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 4;//m_slShareOwnData.indx : 4 (REASON)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNREASON.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNREASON[i].tRect.Left	= nStartW - nTextW * nSLCount;
				m_vSHAREOWNREASON[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();

					//=========================================================
					//실제 표시 위치//
					//=========================================================
					nStartW	-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNREASON[i].tRect.Top 		= nStartH;
						m_vSHAREOWNREASON[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNREASON[i].tRect.Top > nStartH)
							m_vSHAREOWNREASON[i].tRect.Top = nStartH;
						if(m_vSHAREOWNREASON[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNREASON[i].tRect.Bottom = nStartH + nSumHeight;
					}

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
		}


		//==============================================================
		//소유권보합폰트//
		m_fontRatio	= ::CreateFont(fontwidth/2 + 4, 0, 0, 0, 900, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontRatio  = (HFONT)::SelectObject(hdc, m_fontRatio);
		//==============================================================
		//##########################################################################################
		//#
		//# RATIO
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 5;//m_slShareOwnData.indx : 5 (RATIO)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNRATIO.size(); i++)
			{
//=============================================================================
//231114//위치이동//가로쓰기-자동개행은 처음이라//
//데이터 작업 전 한번 체크하고 가로쓰기 가운데정렬 맞추려고//
//for-loop 안에서 frmMain->tcmpPaintBox[4]->Canvas->TextWidth를 다시해서 값이 틀어지므로//
//for-loop 안에서 체크하도록 위치 수정//
				nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("분")+1;//임의글자로 체크//
				nTextH  = frmMain->tcmpPaintBox[4]->Canvas->TextHeight("분")+1;//임의글자로 체크//
				nTextW = nTextW/2;
//=============================================================================

				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				nStartH = funcGetStartH(nDataKindIdx, i, nSLCount, nTextH);
				m_vSHAREOWNRATIO[i].tRect.Left	= nStartW - nTextW * nSLCount;
				m_vSHAREOWNRATIO[i].tRect.Right 	= nStartW;
				m_vSHAREOWNRATIO[i].tRect.Top		= nStartH;
				m_vSHAREOWNRATIO[i].tRect.Bottom 	= nStartH + nTextH * nSLCount;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					//
					asCaption	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
					//
					nStartH    += nTextH;
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
		}



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================

		//##########################################################################################
		//#
		//# ADDRESS
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("주")+1;//임의글자로 체크//;
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("주")+1;//임의글자로 체크//;
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 6;//m_slShareOwnData.indx : 6 (ADDRESS)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNADDRESS.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNADDRESS[i].tRect.Left	= nStartW - nTextW * nSLCount;
				m_vSHAREOWNADDRESS[i].tRect.Right = nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();

					//=========================================================
					//실제 표시 위치//
					//=========================================================
					nStartW	-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNADDRESS[i].tRect.Top 		= nStartH;
						m_vSHAREOWNADDRESS[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNADDRESS[i].tRect.Top > nStartH)
							m_vSHAREOWNADDRESS[i].tRect.Top = nStartH;
						if(m_vSHAREOWNADDRESS[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNADDRESS[i].tRect.Bottom = nStartH + nSumHeight;
					}

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}
		}



		//##########################################################################################
		//#
		//# NAME
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("이")+1;//임의글자로 체크//;
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("이")+1;//임의글자로 체크//;
			nStartW		= 0;
			nStartH		= 0;
			nDataKindIdx	= 7;//m_slShareOwnData.indx : 7 (NAME)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNNAME.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNNAME[i].tRect.Left		= nStartW - nTextW * nSLCount;
				m_vSHAREOWNNAME[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();
					nStartW		-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH 	= funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNNAME[i].tRect.Top 		= nStartH;
						m_vSHAREOWNNAME[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNNAME[i].tRect.Top > nStartH)
							m_vSHAREOWNNAME[i].tRect.Top = nStartH;
						if(m_vSHAREOWNNAME[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNNAME[i].tRect.Bottom = nStartH + nSumHeight;
					}

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							j++;
						}
						else
						{
							if(asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								continue;
							}
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
		}



		//##########################################
		//
		//# Comment
		//
		//##########################################
		nDataKindIdx	= 9;//m_slShareOwnData.indx : 9 (COMMENT)
		for( int i = 0; i < (int)m_vSHARECOMMENT.size(); i++)
		{
			nStartW = funcGetStartW(9, i, 0, 0);
			nStartH = funcGetStartH(9, i, 0, 0);
			asCaption 	= (char*)m_vSHARECOMMENT[i].DATA;//TextOut에 표기할 문자//
			m_vSHARECOMMENT[i].tRect.Left		= nStartW;//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Right 	= nStartW + frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asCaption);//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Top		= nStartH;//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Bottom 	= nStartH + frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption)+1;//주석:가로쓰기//
			frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
		}

//		::SetROP2 (hdc, oldro);
//		::DeleteObject( pen );

		::SelectObject(hdc, hOldFont);
		::DeleteObject(m_font);
	}
}
//---------------------------------------------------------------------------
*/

void __fastcall classDOC08Data::funcInitStringListShareOwn()
{
	for(int i = 0; i < DOC08_SHAREOWN_CNT; i++)//241203//#등급#추가//
	{
		for(int j = 0; j < 52; j++)
		{
			m_slShareOwnData[i][j] = new TStringList();
			m_slShareOwnData[i][j]->Clear();
			m_slShareOwnData[i][j]->Text = "";
			m_slShareOwnData2[i][j] = new TStringList();
			m_slShareOwnData2[i][j]->Clear();
			m_slShareOwnData2[i][j]->Text = "";
			m_vShareOwnDeletePos[i][j].clear();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcDeleteStringListShareOwn()
{
	for(int i = 0; i < DOC08_SHAREOWN_CNT; i++)//241203//#등급#추가//
	{
		for(int j = 0; j < 52; j++)
		{
			if(m_slShareOwnData[i][j] != NULL)
			{
				m_slShareOwnData[i][j]	= NULL;
				delete m_slShareOwnData[i][j];
			}
			if(m_slShareOwnData2[i][j] != NULL)
			{
				m_slShareOwnData2[i][j]	= NULL;
				delete m_slShareOwnData2[i][j];
			}
			m_vShareOwnDeletePos[i][j].clear();
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall classDOC08Data::funcRedrawStringListShareOwn()
{
	int fontwidth		= frmMain->m_nFontSize;
	int fontheight 		= fontwidth;
//NotUsed//	int nMiddleWidth	= (int)((double)frmMain->bpMiddleW * (double)frmMain->m_dDocFactor);
	SHARP_POSITION_STRUCT	tempData;
	TPoint	tPoint;
	TScale  tScale;
 	TPaintBox *pbRect;

	if( !frmMain->m_bAIOCR )//기구축DB 번역본//
		pbRect = frmMain->pbRect2;
	else//AIOCR 번역본//
		pbRect = frmMain->pbRect4;

	if(pbRect->Visible && m_slShareOwnData != NULL)
	{
		//##########################################################################################
		// 공통 사용 변수(PaintBox)
		//##########################################################################################
		HDC 	hdc 			= pbRect->Canvas->Handle;
		TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
		TColor	cPenColor		= pbRect->Color;//221128//#SHAREOWN_OVERLAY//History, OwnInfo
		TColor	cPenColorSharp	= (TColor)RGB(255, 0, 0);//부분삭제선//
		HFONT   font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		// 기본 펜 생성
		HPEN 	pen	    = ::CreatePen(PS_SOLID, 1, cPenColor);
		// 원래 GDI 객체 백업 저장 (폰트, 펜)
		HFONT 	oldFont = (HFONT)::SelectObject(hdc, font);
		HPEN 	oldPen  = (HPEN)::SelectObject(hdc, pen);

		//##########################################################################################
		// 공통 사용 변수(String, Position)
		//##########################################################################################
		AnsiString 	asData		= "";//한 셀 포함 문자//
		AnsiString 	asCaption 	= "";//TextOut에 표기할 문자//
		int 		nLineTxtLen	= 0;
		int 		nTextW		= pbRect->Canvas->TextWidth("가")+1;
		int 		nTextH		= pbRect->Canvas->TextHeight("가")+1;
		int			nStartW		= 0;
		int			nStartH		= 0;
		int			nSharp1		= 0;
		int			nSharp2		= 0;
		//==============================================================
		int 		nSLCount	= 0;
		int			nSumHeight	= 0;
		int 		nDataKindIdx	= 0;//m_slShareOwnData.indx


		//부분삭제선//여기에서만 초기화한다//
		m_vSharpPos.clear();

		//##########################################################################################
		//#
		//# CAUTION- 좌측하단 문구표시// 컬러 다름. 배경 흰색//
		//#
		//##########################################################################################
		{
			//==============================================================
			TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
			HPEN penC    = ::CreatePen(PS_SOLID, 1, cPenColorC);
		    HPEN oldPenC = (HPEN)::SelectObject(hdc, penC);
		    int oldro = ::SetROP2(hdc, R2_COPYPEN);
		    ::SetBkMode(hdc, TRANSPARENT);
		    ::SetTextColor(hdc, cPenColorC);
		    pbRect->Canvas->Brush->Color	= clWhite;

			nDataKindIdx	= 8;
			//==============================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[nDataKindIdx].gLT);
			int _nTextW	= pbRect->Canvas->TextWidth(m_vCAUTION[0].DATA)+1;
			int _nTextH	= pbRect->Canvas->TextHeight(m_vCAUTION[0].DATA)+1;
			m_vCAUTION[0].tRect.Left 		= tPoint.x;
			m_vCAUTION[0].tRect.Top 		= tPoint.y;
			m_vCAUTION[0].tRect.Right		= tPoint.x + _nTextW;
			m_vCAUTION[0].tRect.Bottom	= tPoint.y + _nTextH;

			//==============================================================
			asCaption = (char*)m_vCAUTION[0].DATA;
			TextOutA(hdc, tPoint.x, tPoint.y, asCaption.c_str(), (int)asCaption.Length());

			//==============================================================
		    ::SelectObject(hdc, oldPenC);
			::SetROP2 (hdc, oldro);
			::DeleteObject( penC );
		}

		//##########################################################################################
		//#
		//# LAND, JIBUN, LEVEL, MEMO
		//#
		//##########################################################################################
		{
			//==============================================================
			//지번폰트크게//
			HFONT   fontL = ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
			HFONT   oldFontL = (HFONT)::SelectObject(hdc, fontL);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetTextColor(hdc, cPenColor);
			pbRect->Canvas->Brush->Color	= clWhite;

			nTextW		= pbRect->Canvas->TextWidth("가")+1;
			nTextH		= pbRect->Canvas->TextHeight("가")+1;
			//==============================================================
			// LAND
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 0;//m_slShareOwnData.indx : 0 (LAND)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vLAND[0].tRect.Left		= nStartW - nTextW * nSLCount;
			m_vLAND[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//231211//#DELETEPOS//
				nLineTxtLen = asData.Length();

				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, nSumHeight);//세로쓰기-중간//
				//==========================================================================================
				if(z == 0)
				{
					m_vLAND[0].tRect.Top 	= nStartH;
					m_vLAND[0].tRect.Bottom	= nStartH + nSumHeight;

					//==========================================================================================
					//minji@230310//사장님REQ//imgDoc08Mover->Left	= m_vLAND[0].tRect.Right + ;
					if( !frmMain->m_bAIOCR )//기구축DB 번역본//
					{
						frmMain->imgDoc08Mover->Left	= m_vLAND[0].tRect.Right + 32;//minji@230310//사장님REQ//
						frmMain->imgDoc08Mover->Top		= m_vLAND[0].tRect.Top;
					}
					else//AIOCR 번역본//
					{
						frmMain->imgDoc08Mover4->Left	= m_vLAND[0].tRect.Right + 32;//minji@230310//사장님REQ//
						frmMain->imgDoc08Mover4->Top	= m_vLAND[0].tRect.Top;
					}
					//==========================================================================================
				}
				else
				{
					if(m_vLAND[0].tRect.Top > nStartH)
						m_vLAND[0].tRect.Top = nStartH;
					if(m_vLAND[0].tRect.Bottom < nStartH + nSumHeight)
						m_vLAND[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//231211//#DELETEPOS//
				int nSttIndex = -1;
				int nEndIndex = -1;
				if( (int)m_vShareOwnDeletePos[nDataKindIdx][0].size() > 0 )//LAND
				{
					nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][0][z].nSttIndex;
					nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][0][z].nEndIndex;
				}
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

				//=========================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					//---
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//231211//#DELETEPOS//
						if(j == nSttIndex)
						{
							nSharp1	= nStartH;
						}
						if(j == nEndIndex-1)
						{
							nSharp2	= nStartH + nTextH - 1;
							funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//LAND
						}
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						j++;
					}
					else
					{
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//231211//#DELETEPOS//
						if(j == nSttIndex)
						{
							nSharp1	= nStartH;
						}
						if(j == nEndIndex)
						{
							nSharp2	= nStartH + nTextH - 1;
							funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//LAND
						}
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}

					nStartH	+= nTextH;
				}
			}//for(int z = 0; z < nSLCount; z++)

			//======================================
			// JIBUN
			//======================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 1;//m_slShareOwnData.indx : 1 (JIBUN)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vJIBUN[0].tRect.Left	= nStartW - nTextW * nSLCount;
			m_vJIBUN[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				nLineTxtLen = asData.Length();

				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, nSumHeight);//세로쓰기-중간//
				if(z == 0)
				{
					m_vJIBUN[0].tRect.Top 	= nStartH;
					m_vJIBUN[0].tRect.Bottom	= nStartH + nSumHeight;
				}
				else
				{
					if(m_vJIBUN[0].tRect.Top > nStartH)
						m_vJIBUN[0].tRect.Top = nStartH;
					if(m_vJIBUN[0].tRect.Bottom < nStartH + nSumHeight)
						m_vJIBUN[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//=========================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						j++;
					}
					else
					{
						if(asData.c_str()[j] =='%')
						{
							continue;
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
					}
					nStartH	+= nTextH+1;
				}
			}//for(int z = 0; z < nSLCount; z++)
			//# JIBUN

			::SetROP2 (hdc, oldro);
			::SelectObject(hdc, oldFontL );
            // 생성 객체 삭제
            ::DeleteObject(fontL);



			//==============================================================
			//211216//도청김훈곤주무관Req//지번폰트크게=>레벨,메모 표시할 때는 원복//
			oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetTextColor(hdc, cPenColor);
			//==============================================================

			nTextW		= pbRect->Canvas->TextWidth("가")+1;
			nTextH		= pbRect->Canvas->TextHeight("가")+1;
			//=================================================================
			//241203//#등급#추가//
			//=================================================================
			//======================================
			// LEVEL
			//======================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 10;//m_slShareOwnData.indx : 10 (LEVEL)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vLEVEL[0].tRect.Left	= nStartW - nTextW * nSLCount;
			m_vLEVEL[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//231211//#DELETEPOS//
				nLineTxtLen = asData.Length();
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);//세로쓰기-상단//
				if(z == 0)
				{
					m_vLEVEL[0].tRect.Top 	= nStartH;
					m_vLEVEL[0].tRect.Bottom	= nStartH + nSumHeight;
				}
				else
				{
					if(m_vLEVEL[0].tRect.Top > nStartH)
						m_vLEVEL[0].tRect.Top = nStartH;
					if(m_vLEVEL[0].tRect.Bottom < nStartH + nSumHeight)
						m_vLEVEL[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//231211//#DELETEPOS//
				int nSttIndex = -1;
				int nEndIndex = -1;
				if( (int)m_vShareOwnDeletePos[nDataKindIdx][0].size() > 0 )//LEVEL
				{
					nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][0][z].nSttIndex;
					nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][0][z].nEndIndex;
				}
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

				//==========================================================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//231211//#DELETEPOS//
						if(j == nSttIndex)
						{
							nSharp1	= nStartH;
						}
						if(j == nEndIndex-1)
						{
							nSharp2	= nStartH + nTextH - 1;
							funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//LEVEL
						}
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//231211//#DELETEPOS//
						if(j == nSttIndex)
						{
							nSharp1	= nStartH;
						}
						if(j == nEndIndex)
						{
							nSharp2	= nStartH + nTextH - 1;
							funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//LEVEL
						}
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}

					nStartH	+= nTextH;
				}
			}//for(int z = 0; z < nSLCount; z++)



			//======================================
			// MEMO
			//======================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 2;//m_slShareOwnData.indx : 2 (MEMO)

			//==========================================================================================
			nSLCount  = m_slShareOwnData[nDataKindIdx][0]->Count;
			//==========================================================================================
			nStartW = funcGetStartW(nDataKindIdx, 0, nSLCount, nTextW);
			m_vMEMO[0].tRect.Left		= nStartW - nTextW * nSLCount;
			m_vMEMO[0].tRect.Right	= nStartW;

			for( int z = 0; z < nSLCount; z++)
			{
				asData	= m_slShareOwnData[nDataKindIdx][0]->Strings[z];
				asData	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//231211//#DELETEPOS//
				nLineTxtLen = asData.Length();
				//=========================================================
				//실제 표시 위치//
				//=========================================================
				nStartW	-= nTextW;
				nSumHeight	= m_slShareOwnData2[nDataKindIdx][0]->Strings[z].ToInt();
				nStartH = funcGetStartH(nDataKindIdx, 0, 0, 0);//세로쓰기-상단//
				if(z == 0)
				{
					m_vMEMO[0].tRect.Top 	= nStartH;
					m_vMEMO[0].tRect.Bottom	= nStartH + nSumHeight;
				}
				else
				{
					if(m_vMEMO[0].tRect.Top > nStartH)
						m_vMEMO[0].tRect.Top = nStartH;
					if(m_vMEMO[0].tRect.Bottom < nStartH + nSumHeight)
						m_vMEMO[0].tRect.Bottom = nStartH + nSumHeight;
				}

				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//231211//#DELETEPOS//
				int nSttIndex = -1;
				int nEndIndex = -1;
				if( (int)m_vShareOwnDeletePos[nDataKindIdx][0].size() > 0 )//MEMO
				{
					nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][0][z].nSttIndex;
					nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][0][z].nEndIndex;
				}
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

				//==========================================================================================
				for(int j = 0; j < nLineTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					{
						asCaption = asData.SubString(j+1, 2);
						TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//231211//#DELETEPOS//
						if(j == nSttIndex)
						{
							nSharp1	= nStartH;
						}
						if(j == nEndIndex-1)
						{
							nSharp2	= nStartH + nTextH - 1;
							funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//MEMO
						}
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						//231211//#DELETEPOS//
						if(j == nSttIndex)
						{
							nSharp1	= nStartH;
						}
						if(j == nEndIndex)
						{
							nSharp2	= nStartH + nTextH - 1;
							funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//MEMO
						}
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}

					nStartH	+= nTextH;
				}
			}//for(int z = 0; z < nSLCount; z++)

			::SetROP2 (hdc, oldro);
		}
		// LAND, JIBUN, LEVEL, MEMO

		//##########################################################################################
		//#
		//# DATE
		//#
		//##########################################################################################
		{
			//==============================================================
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 3;//m_slShareOwnData.indx : 3 (DATE)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNDATE.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNDATE[i].tRect.Left	    = nStartW - nTextW * nSLCount;
				m_vSHAREOWNDATE[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();

					//=========================================================
					//실제 표시 위치//
					//=========================================================
					nStartW	-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNDATE[i].tRect.Top 		= nStartH;
						m_vSHAREOWNDATE[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNDATE[i].tRect.Top > nStartH)
							m_vSHAREOWNDATE[i].tRect.Top = nStartH;
						if(m_vSHAREOWNDATE[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNDATE[i].tRect.Bottom = nStartH + nSumHeight;
					}

					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//231211//#DELETEPOS//
					int nSttIndex = -1;
					int nEndIndex = -1;
					if( (int)m_vShareOwnDeletePos[nDataKindIdx][i].size() > 0 )//DATE
					{
						nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nSttIndex;
						nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nEndIndex;
					}
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex-1)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//DATE
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//DATE
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}

			::SetROP2 (hdc, oldro);
		}



		//##########################################################################################
		//#
		//# REASON
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 4;//m_slShareOwnData.indx : 4 (REASON)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNREASON.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNREASON[i].tRect.Left	= nStartW - nTextW * nSLCount;
				m_vSHAREOWNREASON[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();

					//=========================================================
					//실제 표시 위치//
					//=========================================================
					nStartW	-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNREASON[i].tRect.Top 		= nStartH;
						m_vSHAREOWNREASON[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNREASON[i].tRect.Top > nStartH)
							m_vSHAREOWNREASON[i].tRect.Top = nStartH;
						if(m_vSHAREOWNREASON[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNREASON[i].tRect.Bottom = nStartH + nSumHeight;
					}

    				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    				//231211//#DELETEPOS//
    				int nSttIndex = -1;
    				int nEndIndex = -1;
					if( (int)m_vShareOwnDeletePos[nDataKindIdx][i].size() > 0 )//REASON
    				{
						nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nSttIndex;
						nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nEndIndex;
					}
    				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex-1)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//REASON
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//REASON
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# RATIO
		//#
		//##########################################################################################
		{
			//==============================================================
			//소유권보합폰트//
			HFONT   fontR = ::CreateFont(fontwidth+2+4, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
			HFONT   oldFontR = (HFONT)::SelectObject(hdc, fontR);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nTextW		= pbRect->Canvas->TextWidth("가")+1;//임의글자로 체크//;
			nTextH		= pbRect->Canvas->TextHeight("가")+1;//임의글자로 체크//;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 5;//m_slShareOwnData.indx : 5 (RATIO)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNRATIO.size(); i++)
			{
//=============================================================================
//231114//위치이동//가로쓰기-자동개행은 처음이라//
//데이터 작업 전 한번 체크하고 가로쓰기 가운데정렬 맞추려고//
//for-loop 안에서 pbRect->Canvas->TextWidth를 다시해서 값이 틀어지므로//
//for-loop 안에서 체크하도록 위치 수정//
				nTextW = nTextW/2;
//=============================================================================

				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				nStartH = funcGetStartH(nDataKindIdx, i, nSLCount, nTextH);
				m_vSHAREOWNRATIO[i].tRect.Left	= nStartW - nTextW * nSLCount;
				m_vSHAREOWNRATIO[i].tRect.Right 	= nStartW;
				m_vSHAREOWNRATIO[i].tRect.Top		= nStartH;
				m_vSHAREOWNRATIO[i].tRect.Bottom 	= nStartH + nTextH * nSLCount;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					//
					asCaption	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//231211//#DELETEPOS//
					int nSttIndex = -1;
					int nEndIndex = -1;
					AnsiString  asTempStr	= "";
					for(int x = 0; x < (int)m_vShareOwnDeletePos[nDataKindIdx][i].size(); x++)//RATIO
					{
						if(z == m_vShareOwnDeletePos[nDataKindIdx][i][x].nSLIndex)
						{
							nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][x].nSttIndex;
							nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][x].nEndIndex;

							asTempStr	= asCaption.SubString(nSttIndex+1, nEndIndex-nSttIndex+1);
							nSharp1		= nStartW + nSttIndex * nTextW;
							nSharp2		= nSharp1 + pbRect->Canvas->TextWidth(asTempStr)+1;
							funcSetSharpPosition(nSharp1, nStartH + nTextH/2, nSharp2, nStartH + nTextH/2);
						}
					}
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//
					nStartH    += nTextH;
				}//for(int z = 0; z < nSLCount; z++)
			}

			::SetROP2 (hdc, oldro);
			::SelectObject(hdc, oldFontR );
            // 생성 객체 삭제
            ::DeleteObject(fontR);
		}

		nTextW		= pbRect->Canvas->TextWidth("가")+1;//임의글자로 체크//;
		nTextH		= pbRect->Canvas->TextHeight("가")+1;//임의글자로 체크//;

		//##########################################################################################
		//#
		//# ADDRESS
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 6;//m_slShareOwnData.indx : 6 (ADDRESS)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNADDRESS.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNADDRESS[i].tRect.Left	= nStartW - nTextW * nSLCount;
				m_vSHAREOWNADDRESS[i].tRect.Right = nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();

					//=========================================================
					//실제 표시 위치//
					//=========================================================
					nStartW	-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH = funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNADDRESS[i].tRect.Top 		= nStartH;
						m_vSHAREOWNADDRESS[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNADDRESS[i].tRect.Top > nStartH)
							m_vSHAREOWNADDRESS[i].tRect.Top = nStartH;
						if(m_vSHAREOWNADDRESS[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNADDRESS[i].tRect.Bottom = nStartH + nSumHeight;
					}

    				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//231211//#DELETEPOS//
    				int nSttIndex = -1;
    				int nEndIndex = -1;
					if( (int)m_vShareOwnDeletePos[nDataKindIdx][i].size() > 0 )//ADDRESS
					{
						nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nSttIndex;
						nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nEndIndex;
					}
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex-1)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//ADDRESS
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//ADDRESS
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}

			::SetROP2 (hdc, oldro);
		}

		//##########################################################################################
		//#
		//# NAME
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
    		::SetTextColor(hdc, cPenColor);

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			nLineTxtLen = 0;
			nStartW		= 0;
			nStartH		= 0;
			nSharp1		= 0;
			nSharp2		= 0;
			nDataKindIdx	= 7;//m_slShareOwnData.indx : 7 (NAME)

			//==========================================================================================
			for( int i = 0; i < (int)m_vSHAREOWNNAME.size(); i++)
			{
				nSLCount  = m_slShareOwnData[nDataKindIdx][i]->Count;
				//==========================================================================================
				nStartW = funcGetStartW(nDataKindIdx, i, nSLCount, nTextW);
				m_vSHAREOWNNAME[i].tRect.Left		= nStartW - nTextW * nSLCount;
				m_vSHAREOWNNAME[i].tRect.Right 	= nStartW;
				//==========================================================================================

				for( int z = 0; z < nSLCount; z++)
				{
					asData		= m_slShareOwnData[nDataKindIdx][i]->Strings[z];
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					nLineTxtLen = asData.Length();
					nStartW		-= nTextW;
					nSumHeight	= m_slShareOwnData2[nDataKindIdx][i]->Strings[z].ToInt();
					nStartH 	= funcGetStartH(nDataKindIdx, i, 0, nSumHeight);
					if(z == 0)
					{
						m_vSHAREOWNNAME[i].tRect.Top 		= nStartH;
						m_vSHAREOWNNAME[i].tRect.Bottom	= nStartH + nSumHeight;
					}
					else
					{
						if(m_vSHAREOWNNAME[i].tRect.Top > nStartH)
							m_vSHAREOWNNAME[i].tRect.Top = nStartH;
						if(m_vSHAREOWNNAME[i].tRect.Bottom < nStartH + nSumHeight)
							m_vSHAREOWNNAME[i].tRect.Bottom = nStartH + nSumHeight;
					}

					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    				//231211//#DELETEPOS//
    				int nSttIndex = -1;
    				int nEndIndex = -1;
					if( (int)m_vShareOwnDeletePos[nDataKindIdx][i].size() > 0 )//NAME
					{
						nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nSttIndex;
						nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][z].nEndIndex;
    				}
    				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

					//=========================================================
					for(int j = 0; j < nLineTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex-1)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//NAME
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							j++;
						}
						else
						{
							if(asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								continue;
							}
							asCaption = asData.SubString(j+1, 1);
							TextOutA(hdc, nStartW+nTextW/3, nStartH, asCaption.c_str(), (int)asCaption.Length());
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							//231211//#DELETEPOS//
							if(j == nSttIndex)
							{
								nSharp1	= nStartH;
							}
							if(j == nEndIndex)
							{
								nSharp2	= nStartH + nTextH - 1;
								funcSetSharpPosition(nStartW + nTextW/2, nSharp1, nStartW + nTextW/2, nSharp2);//NAME
							}
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}

			::SetROP2 (hdc, oldro);
		}



		//##########################################
		//
		//# Comment
		//
		//##########################################
		nSharp1		= 0;
		nSharp2		= 0;
		nDataKindIdx	= 9;//m_slShareOwnData.indx : 9 (COMMENT)
		for( int i = 0; i < (int)m_vSHARECOMMENT.size(); i++)
		{
			nStartW = funcGetStartW(9, i, 0, 0);
			nStartH = funcGetStartH(9, i, 0, 0);
			asCaption 	= (char*)m_vSHARECOMMENT[i].DATA;//TextOut에 표기할 문자//
			m_vSHARECOMMENT[i].tRect.Left		= nStartW;//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Right 	= nStartW + pbRect->Canvas->TextWidth(asCaption);//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Top		= nStartH;//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Bottom 	= nStartH + pbRect->Canvas->TextHeight(asCaption)+1;//주석:가로쓰기//
			TextOutA(hdc, nStartW, nStartH, asCaption.c_str(), (int)asCaption.Length());
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			//231211//#DELETEPOS//
			int nSttIndex = -1;
			int nEndIndex = -1;
			AnsiString  asTempStr	= "";
			if( (int)m_vShareOwnDeletePos[nDataKindIdx][i].size() > 0)
			{
				nSttIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][0].nSttIndex;
				nEndIndex = (int)m_vShareOwnDeletePos[nDataKindIdx][i][0].nEndIndex;

				asTempStr	= asCaption.SubString(nSttIndex+1, nEndIndex-nSttIndex+1);
				nSharp1		= nStartW + (nSttIndex-1) * nTextW;
				nSharp2		= nSharp1 + pbRect->Canvas->TextWidth(asTempStr)+1;
				funcSetSharpPosition(nSharp1, nStartH + nTextH/2, nSharp2, nStartH + nTextH/2);
			}
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}



		//##########################################
		//
		//# Sharp
		//
		//##########################################
		{
			//------------------
			//일반폰트//
			TColor	cPenColorSharp	= (TColor)RGB(255, 0, 0);//부분삭제선//
			HPEN penSharp   = ::CreatePen(PS_SOLID, m_nSharpWidthOverlap, cPenColorSharp);
			HPEN oldPenSharp = (HPEN)::SelectObject(hdc, penSharp);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			//------------------
			TPoint tpStt, tpEnd;
			for(int i = 0; i < (int)m_vSharpPos.size(); i++)
			{
				tpStt	= m_vSharpPos[i].tpSTT;
				tpEnd	= m_vSharpPos[i].tpEND;
				::MoveToEx(hdc, tpStt.x, tpStt.y, NULL);
				::LineTo(hdc, tpEnd.x, tpEnd.y);
			}

			::SetROP2 (hdc, oldro);
			::SelectObject(hdc, oldPenSharp);  // 펜 복구
			::DeleteObject( penSharp );
		}

        // 원래 객체 복구
        ::SelectObject(hdc, oldPen);
        ::SelectObject(hdc, oldFont);
        // 생성 객체 삭제
        ::DeleteObject(pen);
        ::DeleteObject(font);
	}
}
//---------------------------------------------------------------------------

void __fastcall classDOC08Data::funcSetSharpPosition(int nSTTx, int nSTTy, int nENDx, int nENDy)
{
    SHARP_POSITION_STRUCT   tempData;

	memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
	tempData.tpSTT.x	= nSTTx;
	tempData.tpSTT.y	= nSTTy;
	tempData.tpEND.x	= nENDx;
	tempData.tpEND.y	= nENDy;
	m_vSharpPos.push_back(tempData);
}
//---------------------------------------------------------------------------

