//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


classAIOCRData *eAIOCRData;
//---------------------------------------------------------------------------
classAIOCRData::classAIOCRData()
{
}
//---------------------------------------------------------------------------
classAIOCRData::~classAIOCRData()
{
}
//---------------------------------------------------------------------------

void __fastcall classAIOCRData::funcReadDocument08His()
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

void __fastcall classAIOCRData::funcReadDocument08OwnInfo()
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

void __fastcall classAIOCRData::funcReadDocument08ShareOwn()
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

//221215//#DOC8_OVERLAP//열람화면//한글표시위치정보//
void __fastcall classAIOCRData::funcGetDoc8ViewBoundary()
{
	GPoint		gPoint;
	TScale		gScale;
	TScale		tScale;

	//===========================================================================
	bpMiddleW	= frmMain->mGetImageInfo.nImageWidth * 0.030755;

	//===========================================================================
	gPoint.x  	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.1624;
	gScale.w	= frmMain->mGetImageInfo.nImageWidth * 0.0362;
	gScale.h	= frmMain->mGetImageInfo.nImageHeight * 0.1114;//350;
	m_bpDoc8OwnInfo[0].gLT	= gPoint;
	m_bpDoc8OwnInfo[0].gWH	= gScale;
	m_bpDoc8OwnInfo[0].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[0].gLT);
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.3184;
	gScale.h 	= frmMain->mGetImageInfo.nImageHeight * 0.1910;//600;
	m_bpDoc8OwnInfo[1].gLT	= gPoint;
	m_bpDoc8OwnInfo[1].gWH	= gScale;
	m_bpDoc8OwnInfo[1].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[1].gLT);
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.7705;
	gScale.h 	= frmMain->mGetImageInfo.nImageHeight * 0.1770;//556;
	m_bpDoc8OwnInfo[2].gLT	= gPoint;
	m_bpDoc8OwnInfo[2].gWH	= gScale;
	m_bpDoc8OwnInfo[2].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[2].gLT);
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.0905;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.9583;
	m_bpDoc8OwnInfo[12].gLT	= gPoint;
	m_bpDoc8OwnInfo[12].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[12].gLT);
	//===========================================================================
	gPoint.x  	= frmMain->mGetImageInfo.nImageWidth * 0.7938;
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.1051;
	gScale.w  	= frmMain->mGetImageInfo.nImageWidth * 0.0554;//244;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0439;//138;
	m_bpDoc8OwnInfo[3].gLT	= gPoint;
	m_bpDoc8OwnInfo[3].gWH	= gScale;
	m_bpDoc8OwnInfo[3].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[3].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.1490;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.1044;//328;
	m_bpDoc8OwnInfo[4].gLT	= gPoint;
	m_bpDoc8OwnInfo[4].gWH	= gScale;
	m_bpDoc8OwnInfo[4].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[4].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.2534;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0700;//220;
	m_bpDoc8OwnInfo[5].gLT	= gPoint;
	m_bpDoc8OwnInfo[5].gWH	= gScale;
	m_bpDoc8OwnInfo[5].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[5].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.3235;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0445;//140;
	m_bpDoc8OwnInfo[6].gLT	= gPoint;
	m_bpDoc8OwnInfo[6].gWH	= gScale;
	m_bpDoc8OwnInfo[6].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[6].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.3680;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.2292;//720;
	m_bpDoc8OwnInfo[7].gLT	= gPoint;
	m_bpDoc8OwnInfo[7].gWH	= gScale;
	m_bpDoc8OwnInfo[7].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[7].gLT);
	//===========================================================================
	gPoint.x  	= frmMain->mGetImageInfo.nImageWidth * 0.8141;
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.5973;
	gScale.w 	= frmMain->mGetImageInfo.nImageWidth * 0.030077;//여기만 5자리//소수5자리의 7값이 차지하는 pixel이 큼//
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0649;//204;
	m_bpDoc8OwnInfo[8].gLT	= gPoint;
	m_bpDoc8OwnInfo[8].gWH	= gScale;
	m_bpDoc8OwnInfo[8].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[8].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.6622;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0636;//200;
	m_bpDoc8OwnInfo[9].gLT	= gPoint;
	m_bpDoc8OwnInfo[9].gWH	= gScale;
	m_bpDoc8OwnInfo[9].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[9].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.7259;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.1248;//392;
	m_bpDoc8OwnInfo[10].gLT	= gPoint;
	m_bpDoc8OwnInfo[10].gWH	= gScale;
	m_bpDoc8OwnInfo[10].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[10].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.8507;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.1076;//338;
	m_bpDoc8OwnInfo[11].gLT	= gPoint;
	m_bpDoc8OwnInfo[11].gWH	= gScale;
	m_bpDoc8OwnInfo[11].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[11].gLT);
	//===========================================================================
	//241203//#등급#추가//
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.5000;
	gScale.h 	= frmMain->mGetImageInfo.nImageHeight * 0.1770;//556;
	m_bpDoc8OwnInfo[13].gLT	= gPoint;
	m_bpDoc8OwnInfo[13].gWH	= gScale;
	m_bpDoc8OwnInfo[13].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[13].gLT);
	//===========================================================================
}
//---------------------------------------------------------------------------

void __fastcall classAIOCRData::funcSetDoc8ViewBoundary()
{
	for(int i = 0; i < 13; i++)
		m_bpDoc8OwnInfo[i].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[i].gLT);
}
//---------------------------------------------------------------------------

//열람화면//한글표시위치정보//
void __fastcall classAIOCRData::funcGetDoc8ViewBoundaryShare()
{
	GPoint		gPoint;
	TScale		gScale;
	TScale		tScale;

	memset(m_bpDoc8ShareOwn, 0x00, sizeof(m_bpDoc8ShareOwn));//231211//

	//===========================================================================
	bpMiddleW	= frmMain->mGetImageInfo.nImageWidth * 0.030755;

	//===========================================================================
	gPoint.x  	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.1624;
	gScale.w	= frmMain->mGetImageInfo.nImageWidth * 0.0362;
	gScale.h	= frmMain->mGetImageInfo.nImageHeight * 0.1114;//350;
	m_bpDoc8ShareOwn[0].gLT	= gPoint;
	m_bpDoc8ShareOwn[0].gWH	= gScale;
	m_bpDoc8ShareOwn[0].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[0].gLT);
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.3184;
	gScale.h 	= frmMain->mGetImageInfo.nImageHeight * 0.1910;//600;
	m_bpDoc8ShareOwn[1].gLT	= gPoint;
	m_bpDoc8ShareOwn[1].gWH	= gScale;
	m_bpDoc8ShareOwn[1].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[1].gLT);
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.6000;//231203//0.7705;
	gScale.h 	= frmMain->mGetImageInfo.nImageHeight * 0.1770;//556;
	m_bpDoc8ShareOwn[2].gLT	= gPoint;
	m_bpDoc8ShareOwn[2].gWH	= gScale;
	m_bpDoc8ShareOwn[2].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[2].gLT);
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.08600;//231121//0.0905;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.9583;
	m_bpDoc8ShareOwn[8].gLT	= gPoint;
	m_bpDoc8ShareOwn[8].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[8].gLT);
	//===========================================================================
	//231205//Add Comment Position//
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.3000;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.9583;
	gScale.w	= frmMain->mGetImageInfo.nImageWidth * 0.4250;
	gScale.h	= frmMain->mGetImageInfo.nImageHeight * 0.0100;
	m_bpDoc8ShareOwn[9].gLT	= gPoint;
	m_bpDoc8ShareOwn[9].gWH	= gScale;
	m_bpDoc8ShareOwn[9].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[9].gLT);
	//===========================================================================
	//231205//Add DeleteLine Position//가변적//
//	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.3111;
//	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.9583;
//	gScale.w	= frmMain->mGetImageInfo.nImageWidth * 0.8800;
//	gScale.h	= frmMain->mGetImageInfo.nImageHeight * 0.0500;//350;
//	m_bpDoc8ShareOwn[10].gLT	= gPoint;
//	m_bpDoc8ShareOwn[10].gWH	= gScale;
//	m_bpDoc8ShareOwn[10].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[9].gLT);
	//===========================================================================

	gPoint.x  	= frmMain->mGetImageInfo.nImageWidth * 0.8238;//231121//7938;
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.0857;//231120//1044;
	gScale.w  	= frmMain->mGetImageInfo.nImageWidth * 0.0300;//231120//03074;//여기만 5자리//소수5자리의 7값이 차지하는 pixel이 큼//
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0649;
	m_bpDoc8ShareOwn[3].gLT	= gPoint;
	m_bpDoc8ShareOwn[3].gWH	= gScale;
	m_bpDoc8ShareOwn[3].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[3].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.1506;//231120//1693;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0649;
	m_bpDoc8ShareOwn[4].gLT	= gPoint;
	m_bpDoc8ShareOwn[4].gWH	= gScale;
	m_bpDoc8ShareOwn[4].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[4].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.2155;//231120//2342;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.0432;
	m_bpDoc8ShareOwn[5].gLT	= gPoint;
	m_bpDoc8ShareOwn[5].gWH	= gScale;
	m_bpDoc8ShareOwn[5].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[5].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.2587;//231120//2774;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.1248;
	m_bpDoc8ShareOwn[6].gLT	= gPoint;
	m_bpDoc8ShareOwn[6].gWH	= gScale;
	m_bpDoc8ShareOwn[6].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[6].gLT);
	//===========================================================================
	gPoint.y  	= frmMain->mGetImageInfo.nImageHeight * 0.3835;//231120//4022;
	gScale.h  	= frmMain->mGetImageInfo.nImageHeight * 0.1076;
	m_bpDoc8ShareOwn[7].gLT	= gPoint;
	m_bpDoc8ShareOwn[7].gWH	= gScale;
	m_bpDoc8ShareOwn[7].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[7].gLT);
	//===========================================================================

	//===========================================================================
	//241203//#등급#추가//
	//===========================================================================
	gPoint.x 	= frmMain->mGetImageInfo.nImageWidth * 0.8797;
	gPoint.y 	= frmMain->mGetImageInfo.nImageHeight * 0.5100;
	gScale.h 	= frmMain->mGetImageInfo.nImageHeight * 0.1500;
	m_bpDoc8ShareOwn[10].gLT	= gPoint;
	m_bpDoc8ShareOwn[10].gWH	= gScale;
	m_bpDoc8ShareOwn[10].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[10].gLT);
	//===========================================================================



	m_nTopBottomGap	= frmMain->mGetImageInfo.nImageHeight * (0.0857 + 0.3650);//231121//(0.0857 + 0.4134);
}
//---------------------------------------------------------------------------

void __fastcall classAIOCRData::funcSetDoc8ViewBoundaryShare()
{
	for(int i = 0; i < DOC08_SHAREOWN_CNT; i++)//241203//#등급#추가//
		m_bpDoc8ShareOwn[i].tLT	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[i].gLT);
}
//---------------------------------------------------------------------------


int __fastcall classAIOCRData::funcGetStartW(int _nType, int _nIndex, int _nCount, int _nTextW)
{
	TPoint	tPoint;
	TScale  tScale;
	int nMiddleWidth	= frmAlphaDoc8->m_nMiddleWidth * frmMain->m_dDocFactor;
	int nStartW    = 0;

	//==========================================================================================
	tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[_nType].gLT);
	tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[_nType].gWH);
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

int __fastcall classAIOCRData::funcGetStartH(int _nType, int _nIndex, int _nCount, int _nTextH)
{
	TPoint	tPoint;
	TScale  tScale;
	int nStartH    = 0;
	int nTopBottomGap = (int)((double)m_nTopBottomGap * (double)frmMain->m_dDocFactor);//231205//(double)(m_nTopBottomGap - this->realTop) * frmMain->m_dDocFactor;

	//==========================================================================================
	tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8ShareOwn[_nType].gLT);
	tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[_nType].gWH);
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



//======================================================================
// AIOCR 번역 데이터를 표시//
//======================================================================
void __fastcall classAIOCRData::funcRedrawOwnInfo()
{
	int fontwidth		= frmMain->m_nFontSize;
	int fontheight 		= fontwidth;
	int nMiddleWidth	= (int)((double)bpMiddleW * (double)frmMain->m_dDocFactor);
	TPoint	tPoint;
	TScale  tScale;

	if(frmMain->tcmpPaintBox[4]->Visible)
	{
		//##########################################################################################
		// 공통 사용 변수(PaintBox)
		//##########################################################################################
		HDC 	hdc 			= frmMain->tcmpPaintBox[4]->Canvas->Handle;
		HPEN 	pen;
		//지번폰트//
		HFONT   m_font, m_fontL;
		HFONT 	hOldFont, hOldFontL;
		TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
		TColor	cPenColor		= frmMain->tcmpPaintBox[4]->Color;//221128//#OWNINFO_OVERLAY//History, OwnInfo

		//##########################################################################################
		// 공통 사용 변수(String, Position)
		//##########################################################################################
		AnsiString 	asData		= "";//한 셀 포함 문자//
		AnsiString 	asCaption = "";//TextOut에 표기할 문자//
		AnsiString 	asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		int 		nTxtLen 	= 0;
		int 		nTextW			= 0;
		int 		nTextH			= 0;
		int			nStartW			= 0;
		int			nStartH			= 0;
		int			nSumH			= 0;
  	//==============================================================


		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================

		//==============================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
		::SelectObject(hdc, pen);
		int oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);//텍스트 배경 모드만 투명하게 설정//
		::SetTextColor(hdc, cPenColor);
		//frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;
		//==============================================================


		//##########################################################################################
		//#
		//# CAUTION
		//#
		//##########################################################################################
		{
			//==============================================================
			pen   = ::CreatePen(PS_SOLID, 1, cPenColorC);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColorC);
			frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[12].gLT);
			int nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(m_vCAUTION[0].DATA)+1;
			int nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(m_vCAUTION[0].DATA)+1;
			m_vCAUTION[0].tRect.Left 		= tPoint.x;
			m_vCAUTION[0].tRect.Top 		= tPoint.y;
			m_vCAUTION[0].tRect.Right		= tPoint.x + nTextW;
			m_vCAUTION[0].tRect.Bottom	= tPoint.y + nTextH;
			//==========================================================================================

			//======================================================
			// 좌측하단 문구표시//
			frmMain->tcmpPaintBox[4]->Canvas->TextOutA(tPoint.x, tPoint.y, m_vCAUTION[0].DATA);
			//======================================================

			::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}



		//==============================================================
		//지번폰트크게//
		//지번폰트//
		m_fontL	= ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontL  = (HFONT)::SelectObject(hdc, m_fontL);
		//==============================================================



		//##########################################################################################
		//#
		//# LAND, JIBUN, LEVEL, MEMO
		//#
		//##########################################################################################
		{
			//==============================================================
			pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColor);
			frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;
			//==============================================================

			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//=================================================
			//211206//읍면동명, 리명 구분하여 두 줄 처리//
			//======================================
			// LAND
			//======================================
			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[0].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[0].gWH);
			//공통//
			nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("동")+1;//임의글자로 체크//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("동")+1;//임의글자로 체크//
			//=========================================================

			if(m_asLand.Length() > 0)
			{
				m_asLand	= StringReplace(m_asLand, " ", "_", TReplaceFlags() << rfReplaceAll);
				asData = m_asLand;
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				//=================================================
				//읍면동명, 리명 구분하여 두 줄 처리//
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
							nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asTemp);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
						frmMain->imgDoc08Mover4->Left	= m_vLAND[0].tRect.Right + 32;//minji@230310//사장님REQ//
						frmMain->imgDoc08Mover4->Top	= m_vLAND[0].tRect.Top;
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
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}

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

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[1].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[1].gWH);
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
						nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asTemp);
						j++;
					}
					else
					{
						asCaption = asData.SubString(j+1, 1);
						nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
					}
				}

				//실제 표시//
				//=========================================================
				nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("번");//임의글자로 체크//
				nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("번");//임의글자로 체크//
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
						j++;
					}
					else
					{
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/2, nStartH, asCaption);
					}
					nStartH	+= nTextH+1;
				}
			}

			::SetROP2 (hdc, oldro);
			::DeleteObject( pen );




			//==============================================================
			//211216//도청김훈곤주무관Req//지번폰트크게=>레벨,메모 표시할 때는 원복//
			hOldFont  = (HFONT)::SelectObject(hdc, m_font);
			//==============================================================

			//======================================
			// LEVEL
			//======================================
			//==========================================================================================
			//221214//#DOC8_OVERLAP//
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[13].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[13].gWH);
			//=========================================================

			if(m_asLevel.Length() > 0)
			{
				asData = m_asLevel;
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
	      //적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
				//공통//
				//=========================================================
				nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("등")+1;//임의글자로 체크//
				nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("등")+1;//임의글자로 체크//
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
							nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asTemp);
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
									nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}
				delete slData;
				slData	= NULL;
			}


			//======================================
			// MEMO
			//======================================
			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[2].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[2].gWH);
			//=========================================================

			if(m_asMemo.Length() > 0)
			{
				asData = m_asMemo;
				//---
				nTxtLen = asData.Length();
				nSumH	= 0;

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
      	//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
				//공통//
				//=========================================================
				nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("메")+1;//임의글자로 체크//
				nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("메")+1;//임의글자로 체크//
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
				//221214//#DOC8_OVERLAP//Fixed.//
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
							nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asTemp);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
						}
					}

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumH) / 2;
					//=========================================================

					//==========================================================================================
					//221214//#DOC8_OVERLAP//
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

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}
				delete slData;
				slData	= NULL;
			}

			::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================



		//##########################################################################################
		//#
		//# JIMOK
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[3].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[3].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("지")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vJIMOK.size(); i++)
			{
				asData = m_vJIMOK[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//

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
					nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간//221214//#DOC8_OVERLAP//
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
					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					asCaption 	= asData;
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);

					nStartH	+= nTextH;
				}

				delete slData;
				slData	= NULL;
			}
		}

		//##########################################################################################
		//#
		//# AREA
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
		//==============================================================

			//==============================================================
			AnsiString  asUnit		= "";
			AnsiString  asUnitNew	= "";
			//임야는 단위를 ㎡ 변환시에만 표시하는데, 단위를 별도 체킹하지 않으므로 한번만 표시하므로 플래그 해제//
			bool		bForestUnitDisp	= false;

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[4].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[4].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("면")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vAREA.size(); i++)
			{
				asData = m_vAREA[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//

//				//=========================================
//				// 단위확인//
				int nPos	= 0;
//				AnsiString  asTempUnit	= "";
//				bool		bUnit	= false;
//				if(m_nDOCKIND == 0)//토지대장//
//				{
//					for(int u = 0; u < (int)frmMain->m_vAREAUNIT.size(); u++)
//					{
//						asTempUnit	= frmMain->m_vAREAUNIT[u].DATA;
//
//						nPos	= asData.AnsiPos(asTempUnit);
//						if(nPos > 0)
//						{
//							bUnit	= true;
//							asUnit	= asData.SubString(nPos, asTempUnit.Length());
//							asData	= StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
//						}
//
//						if(bUnit)
//						{
//							if(asUnit == "평방미터")//220120
//								asUnit	= "㎡";
//							break;
//						}
//					}
//				}

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

/*					if(frmDoc8View->chkAreaChange->Checked)
					{
						if(m_nDOCKIND == 0)//토지대장//
						{
							if(asUnit == "평" || asUnit == "홉" || asUnit == "작")
							{
								asData	= eFunc->funcChangeAreaFormatStr(1, asData + asUnit);//평->㎡
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
							asData	= eFunc->funcChangeAreaFormatStr(1, asData);//정단무보->㎡
						}
					}
*/

					asTemp	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간//221214//#DOC8_OVERLAP//
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

					asCaption 	= asData;
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);

					nStartH	+= nTextH;
				}

/*
				//=========================================
				//단위표시//
				if(bUnit)
				{
					if(frmDoc8View->chkAreaChange->Checked)
					{
						int nTxtW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asUnitNew)+1;
						nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//221214//#DOC8_OVERLAP//
						if(i >= 6)
							nStartW	-= nMiddleWidth;

						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnitNew);//221214//#DOC8_OVERLAP//
					}
					else
					{
						int nTxtW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asUnit)+1;
						nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//221214//#DOC8_OVERLAP//
						if(i >= 6)
							nStartW	-= nMiddleWidth;
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit);//221214//#DOC8_OVERLAP//
					}
				}
				//=========================================
*/

				delete slData;
				slData	= NULL;
				//=========================================
			}
		}



		//##########################################################################################
		//#
		//# VALUE1
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[5].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[5].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("과")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vVALUE1.size(); i++)
			{
				asData = m_vVALUE1[i].DATA;

				if(asData == "-")//NoData
					continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//

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
					nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간//221214//#DOC8_OVERLAP//
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

					asCaption 	= asData;
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);

					nStartH	+= nTextH;
				}

				//=========================================
				//단위표시//
				if(bUnit)
				{
					int nTxtW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asUnit)+1;
					nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
					if(i >= 6)
						nStartW	-= nMiddleWidth;
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit);
				}
				//=========================================

				delete slData;
				slData	= NULL;
			}
		}

		//##########################################################################################
		//#
		//# VALUE2
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			//221214//#DOC8_OVERLAP//
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[6].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[6].gWH);
			//=========================================================
			//공통-가로쓰기//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("과")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vVALUE2.size(); i++)
			{
				asData = m_vVALUE2[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//

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
					nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTemp);
					nStartW	= tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간//221214//#DOC8_OVERLAP//
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

					asData		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					asCaption 	= asData;
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);

					nStartH	+= nTextH;
				}

				//=========================================
				//단위표시//
				if(bUnit)
				{
					int nTxtW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asUnit)+1;
					nStartW	= tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
					if(i >= 6)
						nStartW	-= nMiddleWidth;
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit);
				}
				//=========================================

				delete slData;
				slData	= NULL;
			}
		}



		//##########################################################################################
		//#
		//# HISTORY
		//#
		//##########################################################################################
		{
			//==============================================================
			asData		= "";//한 셀 포함 문자//
			asCaption 	= "";//TextOut에 표기할 문자//
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			bool	bOverCell		= false;//#OVERCELL//
			int		nOverCellW		= 0;//#OVERCELL//

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[7].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[7].gWH);
			//=========================================================
			//공통//
			nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("연")-1;/*+1*/;//임의글자로 체크//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("연")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vHISTORY.size(); i++)
			{
				asData = m_vHISTORY[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//

				//---
				nTxtLen = asData.Length();

				TStringList *slData 		= new TStringList;
				slData	= new TStringList();
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
				nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("연")+1;//임의글자로 체크//
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
					m_vHISTORY[i].tRect.Top	= nStartH;//221214//#DOC8_OVERLAP//
					//=========================================================


					//==========================================================================================
					if(nStartW < frmMain->pnlImgDocView->Left || nStartW > frmMain->pnlImgDocView->Left + frmMain->pnlImgDocView->Width
					|| nStartH < frmMain->pnlImgDocView->Top || nStartH > frmMain->pnlImgDocView->Top + frmMain->pnlImgDocView->Height)
					{
						continue;
					}
					//==========================================================================================

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}

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
		}

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
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[8].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[8].gWH);
			//=========================================================
			//공통//
			nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("일")+1;//임의글자로 체크//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("일")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFODATE.size(); i++)
			{
				asData = m_vOWNINFODATE[i].DATA;
				if(asData == "-")//NoData
					continue;

				//=====================================================
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

				//=====================================================
				//230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
				if(asData != "판독불가")
				//=====================================================
				{
					asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
					asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
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
							nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asTemp.Length() && (asTemp.c_str()[j] >= '0' && asTemp.c_str()[j] <= '9'))
							{
								if(asTemp.c_str()[j+1] >= '0' && asTemp.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asTemp.SubString(j+1, 2);
									nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
									j++;
									continue;
								}
							}
							asCaption = asTemp.SubString(j+1, 1);
							nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}

				delete slData;
				slData	= NULL;
			}
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
			asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[9].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[9].gWH);
			//=========================================================
			//공통//
			nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("사")/*+1*/;//임의글자로 체크//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("사")+1;//임의글자로 체크//
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
					//일반적인 데이터//
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
							nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
							j++;
						}
						else
						{
							asCaption = asTemp.SubString(j+1, 1);
							nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}
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
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[10].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[10].gWH);
			//=========================================================
			//공통//
			nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("주")/*+1*/;//임의글자로 체크//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("주")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFOADDRESS.size(); i++)
			{
				asData = m_vOWNINFOADDRESS[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData	= StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);

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
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
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
					nStartW	-= nTextW;
					nStartH	= tPoint.y;//세로쓰기-상단//
					m_vOWNINFOADDRESS[i].tRect.Top 	= nStartH;//221214//#DOC8_OVERLAP//Fixed.//

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}

				delete slData;
				slData	= NULL;
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
			nTxtLen 	= 0;
			nTextW		= 0;
			nTextH		= 0;
			nStartW		= 0;
			nStartH		= 0;
			//==============================================================

			//==========================================================================================
			tPoint	= eFunc->funcSurveyMapToDevice(m_bpDoc8OwnInfo[11].gLT);
			tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8OwnInfo[11].gWH);
			//=========================================================
			//공통//
			nTextW	= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("이")/*+1*/;//임의글자로 체크//
			nTextH	= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("이")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)m_vOWNINFONAME.size(); i++)
			{
				asData = m_vOWNINFONAME[i].DATA;
				if(asData == "-")//NoData
					continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//

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
							if(asData.c_str()[j] == '_')
							{
								slData->Add(asTemp);
								asTemp	= "";
								nLineTxtCnt	= 0;
							}
							else
							//========================================================
							{
								asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
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
							nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
							j++;
						}
						else
						{
							asCaption = asTemp.SubString(j+1, 1);
							nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
						}
					}
					//=========================================================

					//실제 표시//
					//=========================================================
					nStartW	-= nTextW;
					nStartH	= tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//nStartH	= tScale.h;//세로쓰기-상단//
					//=========================================================

					//==========================================================================================
					//221214//#DOC8_OVERLAP//Not Fixed.//
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

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
							asCaption = asData.SubString(j+1, 2);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}

				delete slData;
				slData	= NULL;
			}
		}

		::SetROP2 (hdc, oldro);
		::DeleteObject( pen );

		::SelectObject(hdc, hOldFont);
		::DeleteObject(m_font);
	}
}
//---------------------------------------------------------------------------

void __fastcall classAIOCRData::funcGetShareOwn()
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("동")+1;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("동")+1;//임의글자로 체크//
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
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asTemp);
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
								nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asData.SubString(j+1, 1);
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("번");//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("번");//임의글자로 체크//
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
				nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("등")+1;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("등")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 10;//m_slShareOwnData.indx : 10 (LEVEL)

		//==========================================================================================
		tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
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
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
								nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asData.SubString(j+1, 1);
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("메")+1;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("메")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 2;//m_slShareOwnData.indx : 2 (MEMO)

		//==========================================================================================
		tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
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
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
								nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asData.SubString(j+1, 1);
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("일")+1;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("일")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 3;//m_slShareOwnData.indx : 3 (DATE)
		//==============================================================

		//==========================================================================================
		//일자:내용별개행고정//NotUsed//tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[3].gWH);//자동개행 높이 계산용//항목별 1회//
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
				asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
				asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
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
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asTemp.Length() && (asTemp.c_str()[j] >= '0' && asTemp.c_str()[j] <= '9'))
						{
							if(asTemp.c_str()[j+1] >= '0' && asTemp.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asTemp.SubString(j+1, 2);
								nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
								j++;
								continue;
							}
						}
						asCaption = asTemp.SubString(j+1, 1);
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("사")/*+1*/;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("사")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 4;//m_slShareOwnData.indx : 4 (REASON)
		//==============================================================

		//==========================================================================================
		tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
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
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
						j++;
					}
					else
					{
						asCaption = asTemp.SubString(j+1, 1);
						nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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
			tempV.tRect.Right 	= nStartW + frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asData);
			tempV.tRect.Top 	= nStartH;//주석:가로쓰기//
			tempV.tRect.Bottom 	= nStartH + frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asData)+1;//주석:가로쓰기//
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
		tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
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
				nTextW    = frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTemp);
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("주")/*+1*/;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("주")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 6;//m_slShareOwnData.indx : 6 (ADDRESS)
		//==========================================================================================

		//==========================================================================================
		tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
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
		nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("이")/*+1*/;//임의글자로 체크//
		nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("이")+1;//임의글자로 체크//
		nStartW		= 0;
		nStartH		= 0;
		nDataKindIdx	= 7;//m_slShareOwnData.indx : 7 (NAME)
		//==========================================================================================

		//==========================================================================================
		tScale	= frmMain->funcGetRealScaleToScreenScale(m_bpDoc8ShareOwn[nDataKindIdx].gWH);//자동개행 높이 계산용//항목별 1회//
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
					nSumHeight	+= frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption);
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

void __fastcall classAIOCRData::funcRedrawShareOwn()
{
	int fontwidth		= m_nFontSize;
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
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
		m_fontL	= ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
						j++;
					}
					else
					{
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
						j++;
					}
					else
					{
						if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
						{
							if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
							{
								asCaption = asData.SubString(j+1, 2);
								frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
							{
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
								{
									asCaption = asData.SubString(j+1, 2);
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
						}

						nStartH	+= nTextH;
					}
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
		}


		//==============================================================
		//소유권보합폰트//
		m_fontRatio	= ::CreateFont(fontwidth/2 + 4, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
					//
					nStartH    += nTextH;
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
		}



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;
						}
						else
						{
							if(asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
								continue;
							}
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
			frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
		}

//		::SetROP2 (hdc, oldro);
//		::DeleteObject( pen );

		::SelectObject(hdc, hOldFont);
		::DeleteObject(m_font);
	}
}
//---------------------------------------------------------------------------

void __fastcall classAIOCRData::funcInitShareOwn()
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

void __fastcall classAIOCRData::funcDeleteShareOwn()
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

void __fastcall classAIOCRData::funcInitStringListShareOwn()
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

void __fastcall classAIOCRData::funcDeleteStringListShareOwn()
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


void __fastcall classAIOCRData::funcRedrawStringListShareOwn()
{
	int fontwidth		= frmMain->m_nFontSize;
	int fontheight 		= fontwidth;
	int nMiddleWidth	= (int)((double)bpMiddleW * (double)frmMain->m_dDocFactor);
	SHARP_POSITION_STRUCT	tempData;
	TPoint	tPoint;//221214//#DOC8_OVERLAP//
	TScale  tScale;

	if(frmMain->tcmpPaintBox[4]->Visible && m_slShareOwnData != NULL)
	{
		//##########################################################################################
		// 공통 사용 변수(PaintBox)
		//##########################################################################################
		HDC 	hdc 			= frmMain->tcmpPaintBox[4]->Canvas->Handle;
		HPEN 	pen, penSharp;
		//지번폰트//
		HFONT   m_font, m_fontL;
		HFONT 	hOldFont, hOldFontL;
		HFONT 	m_fontRatio, hOldFontRatio;//소유권보합폰트//231208//
		TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
		TColor	cPenColor		= frmMain->tcmpPaintBox[4]->Color;//221128//#SHAREOWN_OVERLAY//History, OwnInfo
		TColor	cPenColorSharp	= (TColor)RGB(255, 0, 0);//부분삭제선//
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
		int			nSharp1		= 0;
		int			nSharp2		= 0;
		//==============================================================
		int 		nSLCount	= 0;
		int			nSumHeight	= 0;
		int 		nDataKindIdx	= 0;//m_slShareOwnData.indx

		//==============================================================
		m_vSharpPos.clear();//Paint할 때마다 초기화//

		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);

		//=====================================================================
		//(CAUTION) 데이터에만 사용//
		//=====================================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColorC);
		::SelectObject(hdc, pen);
		oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, cPenColorC);
		frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;

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
		m_fontL	= ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontL  = (HFONT)::SelectObject(hdc, m_fontL);

		//==============================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
		::SelectObject(hdc, pen);
		oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, cPenColor);
		frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;

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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("번")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("번")+1;//임의글자로 체크//
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
								frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
			nTextW		= frmMain->tcmpPaintBox[4]->Canvas->TextWidth("메")+1;//임의글자로 체크//
			nTextH		= frmMain->tcmpPaintBox[4]->Canvas->TextHeight("메")+1;//임의글자로 체크//
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
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
								frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
								j++;
								nStartH	+= nTextH;
								continue;
							}
						}
						//숫자 1자리//
						asCaption = asData.SubString(j+1, 1);
						frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
		}
		// LAND, JIBUN, LEVEL, MEMO
		::SetROP2 (hdc, oldro);
		::DeleteObject( pen );



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);

		//==============================================================
		//(TB_DOCUMENT08_SHAREOWN) 데이터에 공통//
		//==============================================================
		pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
		::SelectObject(hdc, pen);
		oldro = ::SetROP2(hdc, R2_COPYPEN);
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, cPenColor);
		frmMain->tcmpPaintBox[4]->Canvas->Brush->Color	= clWhite;
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
									frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
									j++;
									nStartH	+= nTextH;
									continue;
								}
							}
							//숫자 1자리//
							asCaption = asData.SubString(j+1, 1);
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
//			::DeleteObject( pen );
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
//			::DeleteObject( pen );
		}


		//==============================================================
		//소유권보합폰트//
		m_fontRatio	= ::CreateFont(fontwidth/2 + 4, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
			nSharp1		= 0;
			nSharp2		= 0;
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
					frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
							nSharp2		= nSharp1 + frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTempStr)+1;
							funcSetSharpPosition(nSharp1, nStartH + nTextH/2, nSharp2, nStartH + nTextH/2);
						}
					}
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//
					nStartH    += nTextH;
				}//for(int z = 0; z < nSLCount; z++)
			}
			::SetROP2 (hdc, oldro);
//			::DeleteObject( pen );
		}



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
//			::DeleteObject( pen );
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
							frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW+nTextW/3, nStartH, asCaption);
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
//			::DeleteObject( pen );
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
			m_vSHARECOMMENT[i].tRect.Right 	= nStartW + frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asCaption);//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Top		= nStartH;//주석:가로쓰기//
			m_vSHARECOMMENT[i].tRect.Bottom 	= nStartH + frmMain->tcmpPaintBox[4]->Canvas->TextHeight(asCaption)+1;//주석:가로쓰기//
			frmMain->tcmpPaintBox[4]->Canvas->TextOutA(nStartW, nStartH, asCaption);
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
				nSharp2		= nSharp1 + frmMain->tcmpPaintBox[4]->Canvas->TextWidth(asTempStr)+1;
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
			penSharp   = ::CreatePen(PS_SOLID, m_nSharpWidthOverlap, cPenColorSharp);
			::SelectObject(hdc, penSharp);
			int oldro1 = ::SetROP2(hdc, R2_COPYPEN);
			//------------------
			TPoint tpStt, tpEnd;
			for(int i = 0; i < (int)m_vSharpPos.size(); i++)
			{
				tpStt	= m_vSharpPos[i].tpSTT;
				tpEnd	= m_vSharpPos[i].tpEND;
				::MoveToEx(hdc, tpStt.x, tpStt.y, NULL);
				::LineTo(hdc, tpEnd.x, tpEnd.y);
			}

			::SetROP2 (hdc, oldro1);
			::DeleteObject( penSharp );
		}

		::SelectObject(hdc, hOldFont);
		::DeleteObject(m_font);
	}
}
//---------------------------------------------------------------------------

void __fastcall classAIOCRData::funcSetSharpPosition(int nSTTx, int nSTTy, int nENDx, int nENDy)
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

