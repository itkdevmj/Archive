//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma warn -8004


cMainSub *eMainSub;
//---------------------------------------------------------------------------
cMainSub::cMainSub()
{
}
//---------------------------------------------------------------------------
cMainSub::~cMainSub()
{
}
//---------------------------------------------------------------------------


void cMainSub::funcInitResultComponent()
{
	frmMain->sgResult2->ColWidths[0]  = 90;
	frmMain->sgResult2->ColWidths[1]  = 242;//450;//420

	frmMain->sgResult2->Cells[0][0]   = "항목";
	frmMain->sgResult2->Cells[1][0]   = "DB 입력값";

	frmMain->Memo1->Lines->Text = "";
	frmMain->Memo1->Lines->Clear();
	frmMain->Memo1->Visible	= false;

	//======================================================================
	//241015//#전주#중앙정보테크//
	//======================================================================
	int nSkinColor	= frmMain->SIDOINI->ReadInteger(L"FUNCTIONS", L"VALUE", 16750131);
	for(int i = 0; i < frmMain->sgResult2->ColCount; i++)
	{
		frmMain->sgResult2->FontColors[i][0] 	= (TColor)RGB( 255, 255, 255 );
		frmMain->sgResult2->Colors[i][0] 		= (TColor)RGB(GetRValue(nSkinColor), GetGValue(nSkinColor), GetBValue(nSkinColor) );
	}

	for (int i = 1; i < frmMain->sgResult2->RowCount; i++)
	{
		frmMain->sgResult2->Cells[0][i] = L"";
		frmMain->sgResult2->Cells[1][i] = L"";
//		for (int j = 0; j < frmMain->sgResult2->ColCount; j++)
//		{
//			frmMain->sgResult2->FontColors[j][i] 	= clBlack;
//			frmMain->sgResult2->Colors[j][i] 		= clWhite;
//		}
	}

	frmMain->Memo1->Visible 				= false;//200526
	frmMain->pnlDocInfo->Visible 	= false;//M//191107
	frmMain->pnlSearchList->Refresh();
}
//---------------------------------------------------------------------------

//231212//funcSetComponent2, 3, 4 Merge//
//_nType : 1 => treSystemDblClick
//_nType : 2 => FTP Prev/Next File Path DB Info Display //FTP 앞뒤이미지 DB속성정보//
//_nType : 3 => PoiPopup>문서심볼클릭
void cMainSub::funcSetDBInfo(int _nType)
{
	DOCUMENT01_STRUCT	*mDoc1Struct;
	DOCUMENT02_STRUCT	*mDoc2Struct;
	DOCUMENT03_STRUCT	*mDoc3Struct;
	DOCUMENT04_STRUCT	*mDoc4Struct;
	DOCUMENT05_STRUCT	*mDoc5Struct;
	DOCUMENT06_STRUCT	*mDoc6Struct;
	DOCUMENT07_STRUCT	*mDoc7Struct;
	DOCUMENT08_STRUCT	*mDoc8Struct;
	DOCUMENT09_STRUCT	*mDoc9Struct;
	DOCUMENT11_STRUCT	*mDoc11Struct;
	DOCUMENT12_STRUCT	*mDoc12Struct;
	DOCUMENT13_STRUCT	*mDoc13Struct;
	DOCUMENT14_STRUCT	*mDoc14Struct;
	DOCUMENT15_STRUCT	*mDoc15Struct;
	DOCUMENT17_STRUCT	*mDoc17Struct;
	DOCUMENT18_STRUCT   *mDoc18Struct;
	DOCUMENT20_STRUCT   *mDoc20Struct;//231021//GAGAMLAYER in LandArchive
	MEMOINFO_STRUCT     *mMemoStruct;
	int                 nDocNum	= eTree->funcClickNodeToDocNum(frmMain->mSearchNode.tSelectNode);
	int					nRow	= 0;

    //Init
	funcInitResultComponent();//200928//
	frmMain->Memo1->Lines->Text = "";
	frmMain->Memo1->Lines->Clear();

	frmMain->m_asDownloadKindName	= "";///210303//#TB_COPY_DNLD

	if( !frmMain->pnlDocInfo->Visible )
	{
		frmMain->pgDocInfo->ActivePage	= frmMain->TabDocInfo;
		frmMain->pnlDocInfo->Visible 	= true;
	}

	//frmMain->sgResult2->LockUpdate = true;//200310

    //=========================================================================
	if (nDocNum == 1)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc1Struct = (DOCUMENT01_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc1Struct = (DOCUMENT01_STRUCT*)&frmSql->m_ResultDoc01DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc1Struct = (DOCUMENT01_STRUCT*)&frmMain->m_ResultDocument01[0];
    }
	else if (nDocNum == 2)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc2Struct = (DOCUMENT02_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc2Struct = (DOCUMENT02_STRUCT*)&frmSql->m_ResultDoc02DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc2Struct = (DOCUMENT02_STRUCT*)&frmMain->m_ResultDocument02[0];
    }
	else if (nDocNum == 3)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc3Struct = (DOCUMENT03_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc3Struct = (DOCUMENT03_STRUCT*)&frmSql->m_ResultDoc03DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc3Struct = (DOCUMENT03_STRUCT*)&frmMain->m_ResultDocument03[0];
    }
	else if (nDocNum == 4)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc4Struct = (DOCUMENT04_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc4Struct = (DOCUMENT04_STRUCT*)&frmSql->m_ResultDoc04DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc4Struct = (DOCUMENT04_STRUCT*)&frmMain->m_ResultDocument04[0];
    }
	else if (nDocNum == 5)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc5Struct = (DOCUMENT05_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc5Struct = (DOCUMENT05_STRUCT*)&frmSql->m_ResultDoc05DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc5Struct = (DOCUMENT05_STRUCT*)&frmMain->m_ResultDocument05[0];
    }
	else if (nDocNum == 6)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc6Struct = (DOCUMENT06_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc6Struct = (DOCUMENT06_STRUCT*)&frmSql->m_ResultDoc06DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc6Struct = (DOCUMENT06_STRUCT*)&frmMain->m_ResultDocument06[0];
    }
	else if (nDocNum == 7)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc7Struct = (DOCUMENT07_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc7Struct = (DOCUMENT07_STRUCT*)&frmSql->m_ResultDoc07DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc7Struct = (DOCUMENT07_STRUCT*)&frmMain->m_ResultDocument07[0];
    }
	else if (nDocNum == 8)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc8Struct = (DOCUMENT08_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc8Struct = (DOCUMENT08_STRUCT*)&frmSql->m_ResultDoc08DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc8Struct = (DOCUMENT08_STRUCT*)&frmMain->m_ResultDocument08[0];
    }
	else if (nDocNum == 9)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc9Struct = (DOCUMENT09_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc9Struct = (DOCUMENT09_STRUCT*)&frmSql->m_ResultDoc09DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc9Struct = (DOCUMENT09_STRUCT*)&frmMain->m_ResultDocument09[0];
    }
	else if (nDocNum == 11)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc11Struct = (DOCUMENT11_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc11Struct = (DOCUMENT11_STRUCT*)&frmSql->m_ResultDoc11DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc11Struct = (DOCUMENT11_STRUCT*)&frmMain->m_ResultDocument11[0];
    }
	else if (nDocNum == 12)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc12Struct = (DOCUMENT12_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc12Struct = (DOCUMENT12_STRUCT*)&frmSql->m_ResultDoc12DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc12Struct = (DOCUMENT12_STRUCT*)&frmMain->m_ResultDocument12[0];
    }
	else if (nDocNum == 13)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc13Struct = (DOCUMENT13_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc13Struct = (DOCUMENT13_STRUCT*)&frmSql->m_ResultDoc13DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc13Struct = (DOCUMENT13_STRUCT*)&frmMain->m_ResultDocument13[0];
    }
	else if (nDocNum == 14)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc14Struct = (DOCUMENT14_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc14Struct = (DOCUMENT14_STRUCT*)&frmSql->m_ResultDoc14DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc14Struct = (DOCUMENT14_STRUCT*)&frmMain->m_ResultDocument14[0];
    }
	else if (nDocNum == 15)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc15Struct = (DOCUMENT15_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc15Struct = (DOCUMENT15_STRUCT*)&frmSql->m_ResultDoc15DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc15Struct = (DOCUMENT15_STRUCT*)&frmMain->m_ResultDocument15[0];
    }
	else if (nDocNum == 17)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc17Struct = (DOCUMENT17_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc17Struct = (DOCUMENT17_STRUCT*)&frmSql->m_ResultDoc17DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc17Struct = (DOCUMENT17_STRUCT*)&frmMain->m_ResultDocument17[0];
    }
	else if (nDocNum == 18)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc18Struct = (DOCUMENT18_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc18Struct = (DOCUMENT18_STRUCT*)&frmSql->m_ResultDoc18DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc18Struct = (DOCUMENT18_STRUCT*)&frmMain->m_ResultDocument18[0];
    }
	else if (nDocNum == 20)
    {
        if(_nType == 1)//treSystemDblClick
    		mDoc20Struct = (DOCUMENT20_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 2)//FTP Prev/Next
			mDoc20Struct = (DOCUMENT20_STRUCT*)&frmSql->m_ResultDoc20DBInfo[0];
        else if(_nType == 3)//PoiPopup>문서심볼클릭
			mDoc20Struct = (DOCUMENT20_STRUCT*)&frmMain->m_ResultDocument20[0];
    }
	else if (nDocNum == 0)
    {
        if(_nType == 1)//treSystemDblClick
    		mMemoStruct = (MEMOINFO_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
        else if(_nType == 3)//PoiPopup>문서심볼클릭
    		mMemoStruct = (MEMOINFO_STRUCT*)&frmMain->m_ResultMemo[0];
    }

    //=========================================================================
	if (nDocNum == 1)
	{
		frmMain->sgResult2->RowCount = 9;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동종목";
		frmMain->sgResult2->Cells[0][nRow++]   = L"결의일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동전 주소";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동후 주소";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc1Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc1Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc1Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc1Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(1, mDoc1Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(101, mDoc1Struct->MEASURE_TYPE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc1Struct->PRCS_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc1Struct->BF_PNU));
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc1Struct->AF_PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc1Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc1Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc1Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 2)
	{
		frmMain->sgResult2->RowCount = 12;//200311//12;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"측량종목";
		frmMain->sgResult2->Cells[0][nRow++]   = L"측량일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"검사일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"결의일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"축척";
		frmMain->sgResult2->Cells[0][nRow++]   = L"도호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동전 주소코드";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동후 주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc2Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(102, mDoc2Struct->SURV_ITEM);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->SURV_DAY;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->INSPCT_DAY;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->SUBMIT_DATE;
		AnsiString asStr 	= (char*)mDoc2Struct->RDSCALE_CODE;
		if(asStr != "")
		{
			asStr.sprintf("%d00", asStr.ToInt());
			frmMain->sgResult2->Cells[1][nRow++] = asStr;
		}
		else
		{
			frmMain->sgResult2->Cells[1][nRow++] = "-";
		}
		frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->DOHO;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc2Struct->BF_PNU));
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc2Struct->AF_PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc2Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc2Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc2Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 3)
	{
		frmMain->sgResult2->RowCount = 9;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"측량일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"측량자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동전 주소코드";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동후 주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc3Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc3Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc3Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc3Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(3, mDoc3Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc3Struct->SURV_DAY;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc3Struct->SURV_NAME;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc3Struct->BF_PNU));
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc3Struct->AF_PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc3Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc3Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc3Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 4)
	{
		frmMain->sgResult2->RowCount = 10;//200311//11;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"신청일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"신청자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주민번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"발급번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc4Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(4, mDoc4Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->REQ_DAY;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->OWN_NAME;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->OWN_REG_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->ISSUE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc4Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc4Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc4Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc4Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 5)
	{
		frmMain->sgResult2->RowCount = 9;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동종목";
		frmMain->sgResult2->Cells[0][nRow++]   = L"결의일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동전 주소코드";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동후 주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc5Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc5Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc5Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc5Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(1, mDoc5Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(109, mDoc5Struct->MEASURE_TYPE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc5Struct->PRCS_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc5Struct->BF_PNU));
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc5Struct->AF_PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc5Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc5Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(1, mDoc5Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 6)
	{
		AnsiString asCompYear = "";

		frmMain->sgResult2->RowCount = 9;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"사업지구";
		frmMain->sgResult2->Cells[0][nRow++]   = L"준공년도";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동전 주소코드";
		frmMain->sgResult2->Cells[0][nRow++]   = L"이동후 주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc6Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc6Struct->ROLL_NO;//mDoc6Struct->ROLL_NUM;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc6Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc6Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(6, mDoc6Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(906, mDoc6Struct->ZONE_CODE);
		asCompYear = mDoc6Struct->COMP_YEAR;
		if( asCompYear == "0" )	asCompYear = "-";
		frmMain->sgResult2->Cells[1][nRow++] = asCompYear;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc6Struct->BF_PNU));
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc6Struct->AF_PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc6Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc6Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc6Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 7)
	{
		frmMain->sgResult2->RowCount = 7;//200311//8;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"도호1";
		frmMain->sgResult2->Cells[0][nRow++]   = L"도호2";
		frmMain->sgResult2->Cells[0][nRow++]   = "축척";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc7Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(7, mDoc7Struct->KIND_CODE);
		//백남수
		if(frmSearch->m_bDoc07Check == true){
			AnsiString strtemp = (char*)mDoc7Struct->DOHO_BON;
			if(strtemp == frmSearch->m_sDoc07DohoCheck) frmMain->sgResult2->Cells[1][nRow++] = strtemp + " [*인근지번 도호 참조]";
			else frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->DOHO_BON;
		}
		else frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->DOHO_BON;
		/////////////////////////////////////////////////////////////
		//송과장
		//frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->DOHO_BON;
		//////////////////////////////////////////////////////////////
		frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->DOHO_BU;
		AnsiString asStr 	= (char*)mDoc7Struct->SCALE;
		if(asStr != "")
		{
			asStr.sprintf("%d00", asStr.ToInt());
			frmMain->sgResult2->Cells[1][nRow++] = asStr;
		}
		else
		{
			frmMain->sgResult2->Cells[1][nRow++] = "-";
		}
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc7Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc7Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc7Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 8)
	{
		frmMain->sgResult2->RowCount = 8;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서종류";
		frmMain->sgResult2->Cells[0][nRow++]   = L"앞뒤구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로(C)";

		if (!mDoc8Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc8Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc8Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc8Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(8, mDoc8Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc8Struct->SINGU_NAME;
		if( strcmp(mDoc8Struct->ONOFF_CODE, "1") )//240322
			frmMain->sgResult2->Cells[1][nRow++] = "앞면";
		else
			frmMain->sgResult2->Cells[1][nRow++] = "뒷면";
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc8Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc8Struct->PATH_NAME;
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc8Struct->PATH_NAME_COLOR;
		frmMain->Memo1->Lines->Add(mDoc8Struct->PATH_NAME);//200311//
		frmMain->Memo1->Lines->Add(mDoc8Struct->PATH_NAME_COLOR);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc8Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 9)
	{
		frmMain->sgResult2->RowCount = 8;//200311//9;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"기준년";
		frmMain->sgResult2->Cells[0][nRow++]   = L"기준월";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc9Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc9Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(9, mDoc9Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc9Struct->BASE_YEAR;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc9Struct->BASE_MON;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc9Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc9Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc9Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc9Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc9Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc9Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 10)
	{
	}
	else if (nDocNum == 11)
	{
		frmMain->sgResult2->RowCount = 6;//200311//7;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc11Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc11Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc11Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc11Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(11, mDoc11Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc11Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc11Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc11Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc11Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 12)
	{
		frmMain->sgResult2->RowCount = 7;//200311//8;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"해당일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc12Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc12Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc12Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc12Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(12, mDoc12Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc12Struct->REQ_DAY;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc12Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc12Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc12Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc12Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 13)
	{
		frmMain->sgResult2->RowCount = 8;//200311//9;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"신청일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"신청자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주민번호";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc13Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(13, mDoc13Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->REQ_DAY;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->OWN_NAME ;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->OWN_REG_NO ;
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc13Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc13Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(42, mDoc13Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 14)
	{
		frmMain->sgResult2->RowCount = 8;//200311//9;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서종류";
		frmMain->sgResult2->Cells[0][nRow++]   = L"신청일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc14Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc14Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc14Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc14Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(1, mDoc14Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(111, mDoc14Struct->MEASURE_TYPE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc14Struct->PRCS_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc14Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc14Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc14Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(1, mDoc14Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 15)
	{
		frmMain->sgResult2->RowCount = 9;//200527//#9//명재씨Req//13;//200527//200311//14;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"롤번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서종목";
		frmMain->sgResult2->Cells[0][nRow++]   = L"등록일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"등록명";
		frmMain->sgResult2->Cells[0][nRow++]   = L"등록번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"소유구분";
//		frmMain->sgResult2->Cells[0][nRow++]   = L"법인주소";
//		frmMain->sgResult2->Cells[0][nRow++]   = L"신청인명";
//		frmMain->sgResult2->Cells[0][nRow++]   = L"신청인주민번호";
//		frmMain->sgResult2->Cells[0][nRow++]   = L"신청인주소";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc15Struct) return;
		nRow	= 1;
		//200519//#2
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->ROLL_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(15, mDoc15Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->DOC_KIND;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->PRCS_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->REG_NM;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->REG_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->OWN;
//		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->APP_ADDR;
//		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->REPS_NM;
//		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->REPS_NO;
//		frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->REPS_ADDR;
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc15Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc15Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc15Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 17)
	{
		frmMain->sgResult2->RowCount = 9;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"SEQ번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서명";
		frmMain->sgResult2->Cells[0][nRow++]   = L"표페이지";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"해당일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"주소코드";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc17Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->SEQ_NUM;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(17, mDoc17Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->DOC_NAME;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->PYO_PAGE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->PAGE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->DOC_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = funcMakeJibun(AnsiString(mDoc17Struct->PNU));
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc17Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc17Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc17Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
	else if (nDocNum == 18)
	{
		double X = 0;
		double Y = 0;
		AnsiString asStr 	= "";

		frmMain->sgResult2->RowCount = 9;//200311//10;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";
		frmMain->sgResult2->Cells[0][nRow++]   = L"해당년도";
		frmMain->sgResult2->Cells[0][nRow++]   = L"지구명";
		frmMain->sgResult2->Cells[0][nRow++]   = L"측량일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"검사일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"도근점";
		frmMain->sgResult2->Cells[0][nRow++]   = L"좌표";
		//200311//frmMain->sgResult2->Cells[0][nRow++]   = L"문서이미지경로";

		if (!mDoc18Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->KWON_NO;
		//201223//좌표계산부 첫페이지 표시 때문에 문서구분  '좌표계산부'를 00010으로 표시했으므로 관련하여 처리//
		asStr	= (char*)mDoc18Struct->PAGE_NO;
		if(!asStr.IsEmpty())
		{
			asStr	= eFunc->funcGetPageNoName(nDocNum, asStr.c_str());
		}
		if(asStr == "00010" && !strcmp(mDoc18Struct->KIND_CODE, "00") )
			frmMain->sgResult2->Cells[1][nRow++]	= eFunc->funcGetKindCodeToKindName(nDocNum, "01");
		else
			frmMain->sgResult2->Cells[1][nRow++]	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc18Struct->KIND_CODE);
		//201223//frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(18, mDoc18Struct->KIND_CODE);
		frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->JIGU_YEAR;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->JIGU_NAME;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->MEASURE_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->CHECK_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->DOGNPOINT;
		asStr 	= mDoc18Struct->BOJOPOINT;
		if(asStr != ""){
			int iPos = asStr.Pos("_");
			if(iPos > 0){
				X = asStr.SubString(1, iPos-1).ToDouble();
				asStr.Delete(1,iPos);
				if(asStr != "") Y = asStr.ToDouble();
				else Y = 0;
			}
		}
		frmMain->sgResult2->Cells[1][nRow++] = FloatToStr(X) + ", " + FloatToStr(Y);
		//200311//frmMain->sgResult2->Cells[1][nRow++] = mDoc18Struct->PATH_NAME;
		frmMain->Memo1->Lines->Add(mDoc18Struct->PATH_NAME);//200311//

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc18Struct->KIND_CODE);///210303//#TB_COPY_DNLD
	}
//=============================================================================
//231021//GAGAMLAYER in LandArchive
//=============================================================================
	else if (nDocNum == 20)
	{
		frmMain->sgResult2->RowCount = 8;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"권번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"토지소재코드";
		frmMain->sgResult2->Cells[0][nRow++]   = L"가감지구명";
		frmMain->sgResult2->Cells[0][nRow++]   = L"도호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"측량일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"결의(정리)일자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"페이지번호";
		frmMain->sgResult2->Cells[0][nRow++]   = L"문서구분";

		if (!mDoc20Struct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->KWON_NO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->UMDRI_CD;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->DOC_NAME;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->DOHO;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->SURV_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->PRCS_DATE;
		frmMain->sgResult2->Cells[1][nRow++] = mDoc20Struct->PAGE_NO;
		frmMain->sgResult2->Cells[1][nRow++] = eFunc->funcGetKindCodeToKindName(nDocNum, mDoc20Struct->KIND_CODE);
		frmMain->Memo1->Lines->Add(mDoc20Struct->PATH_NAME);

		frmMain->m_asDownloadKindName	= eFunc->funcGetKindCodeToKindName(nDocNum, mDoc20Struct->KIND_CODE);//#TB_COPY_DNLD
	}
//=============================================================================
	else if (nDocNum == 0)//#MEMOSEARCH#
	{
		AnsiString asStr 	= "";

		frmMain->sgResult2->RowCount = 7;//200311//8;
		nRow	= 1;
		frmMain->sgResult2->Cells[0][nRow++]   = L"위치";
		frmMain->sgResult2->Cells[0][nRow++]   = L"제목";
		frmMain->sgResult2->Cells[0][nRow++]   = L"최초등록일";
		frmMain->sgResult2->Cells[0][nRow++]   = L"최종변경일";
		frmMain->sgResult2->Cells[0][nRow++]   = L"최종변경자";
		frmMain->sgResult2->Cells[0][nRow++]   = L"첨부파일수";
		frmMain->sgResult2->Cells[0][nRow++]   = L"영역지점수";

		if (!mMemoStruct) return;
		nRow	= 1;
		frmMain->sgResult2->Cells[1][nRow++] = mMemoStruct->POI_NAME;
		frmMain->sgResult2->Cells[1][nRow++] = mMemoStruct->TITLE;
		asStr = mMemoStruct->POI_KEY;
		if(asStr.Length() < 8)
			asStr = "정보없음";
		else
			asStr = asStr.SubString(1, 8);
		frmMain->sgResult2->Cells[1][nRow++] = asStr;
		asStr = mMemoStruct->WRITE_DT;
		if(asStr.Length() < 8)
			asStr = "정보없음";
		else
			asStr = asStr.SubString(1, 8);
		frmMain->sgResult2->Cells[1][nRow++] = asStr;
		frmMain->sgResult2->Cells[1][nRow++] = frmUserManagement->funcReadUserName(AnsiString((char*)mMemoStruct->WRITE_ID));
		frmMain->sgResult2->Cells[1][nRow++] = mMemoStruct->FILE_CNT;
		frmMain->sgResult2->Cells[1][nRow++] = mMemoStruct->DATA_CNT;
	}

	if( !frmMain->pnlDocInfo->Visible )
	{
		frmMain->pgDocInfo->ActivePage	= frmMain->TabDocInfo;
		frmMain->pnlDocInfo->Visible 	= true;
	}

	//120(H), 346(T)
	if(frmMain->pnlDocInfo07->Visible)
		frmMain->pnlDocInfo->Height 	= frmMain->TabDocInfo->Top + 4 + frmMain->sgResult2->RowCount * frmMain->sgResult2->FixedRowHeight + frmMain->pnlDocInfo07->Height;//200211
	else
		frmMain->pnlDocInfo->Height 	= frmMain->TabDocInfo->Top + 4 + frmMain->sgResult2->RowCount * frmMain->sgResult2->FixedRowHeight;

	frmMain->pnlEtc->Top		= frmMain->pnlDocInfo->Top + frmMain->pnlDocInfo->Height;
	frmMain->StatusBar2->Top 	= frmMain->pnlEtc->Top + frmMain->pnlEtc->Height;//200402
}
//---------------------------------------------------------------------------

AnsiString cMainSub::funcMakeJibun(AnsiString _asPnu)
{
	AnsiString asResult = "";

	if (_asPnu.Length() == 19)
	{
		asResult = AnsiString(frmMain->func_ConvertLandcdToAddress(_asPnu));
	}

	return asResult;
}
//---------------------------------------------------------------------------

