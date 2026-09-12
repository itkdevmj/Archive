//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//#include "untSearch.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004
//#pragma warn -8012

TfrmSearch *frmSearch;
//---------------------------------------------------------------------------
__fastcall TfrmSearch::TfrmSearch(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::FormCreate(TObject *Sender)
{
	qry = new TStringList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(qry != NULL)
	{
		delete qry;
		qry = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcInitSearchSuccess()
{
	for(int i = 0; i < DF_DOC_CNT; i++)//200110//메모결과 [0]에 저장//
	{
		searchSuccess[i] = false;
		frmMain->totalCount[i] = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSetSearchFinish()
{
	frmMain->funcFreeImage();//221221//재검색을 하면 문서화면 초기화되는데 메모리가 되돌아오지 않아서 처리//
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcClearResultVector()
{
	frmMain->m_ResultDocument01.clear();
	frmMain->m_ResultDocument02.clear();
	frmMain->m_ResultDocument03.clear();
	frmMain->m_ResultDocument04.clear();
	frmMain->m_ResultDocument05.clear();
	frmMain->m_ResultDocument06.clear();
	frmMain->m_vLANDINFO.clear();//201009//
	frmMain->m_vLANDINFO_SUB.clear();//201227//
	frmMain->m_ResultDocument07.clear();
	frmMain->m_ResultDocument07_SUB.clear();//201227//
	frmMain->m_vDOC07PNU.clear();//201009//
	frmMain->m_ResultDocument08.clear();
	frmMain->m_ResultDocument09.clear();
	frmMain->m_ResultDocument11.clear();
	frmMain->m_ResultDocument12.clear();
	frmMain->m_ResultDocument13.clear();
	frmMain->m_ResultDocument14.clear();
	frmMain->m_ResultDocument15.clear();
	frmMain->m_ResultDocument17.clear();
	frmMain->m_ResultDocument18.clear();
	frmMain->m_ResultDocument20.clear();//231020//GAGAMLAYER
	frmMain->m_ResultMemo.clear();
	frmMain->m_vPNU_SIDOCODE.clear();//frmMain->m_v_SEARCHEDJIBUN 과 같은 역할인데...[TODO]
	frmMain->m_vDOC6_ZONECODE.clear();

	frmMain->m_ResultDocument08Pnu.clear();//211205//#OWNINFO#
	frmMain->m_nPathListSeqNo	= 0;
}
//---------------------------------------------------------------------------

//
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::funcSearch()
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcTotalSearchJibun()
{
//	frmMain->funcWriteLogData("통합/상세검색을 합니다.");//231219//#WriteLog//

	frmMain->funcSetWaitWindows(true);

	frmMain->funcInitSearchList();
	funcInitSearchSuccess();

//230207//funcSetUserHistState()Param변경//
//	AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "검색");//210305//#44710//1
//	if( !asKindCode.IsEmpty() )
//		frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), frmMain->m_nActiveDoc);
	frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "검색", frmMain->m_nActiveDoc);

	if(frmMain->m_nActiveDoc == 0)
	{
		//201201//검색결과, 구대장 > 이동결의서 > 측량결과도 > 종이지적도 > 나머지 //
		//구대장//
		if(frmMain->INIINFO.B_QRYCHECK[8])//통검은 지번 있는 것만//속도개선//지번없는 것은 설정에 따라 funcTotalSearchKeyword//
		{
			//200302
			bool bDocYN = false;

			if(frmSql->m_nKindOfDocIndex > -1)
			{
				bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC08_YN, "1")) ? (true):(false);
			}
			if(bDocYN)
				funcSearchSelect(8);
		}
		//이동결의서//
		if(frmMain->INIINFO.B_QRYCHECK[1])//통검은 지번 있는 것만//속도개선//지번없는 것은 설정에 따라 funcTotalSearchKeyword//
		{
			//200302
			bool bDocYN = false;

			if(frmSql->m_nKindOfDocIndex > -1)
			{
				bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC01_YN, "1")) ? (true):(false);
			}
			if(bDocYN)
				funcSearchSelect(1);
		}
		//측량결과도//
		if(frmMain->INIINFO.B_QRYCHECK[2])//통검은 지번 있는 것만//속도개선//지번없는 것은 설정에 따라 funcTotalSearchKeyword//
		{
			//200302
			bool bDocYN = false;

			if(frmSql->m_nKindOfDocIndex > -1)
			{
				bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC02_YN, "1")) ? (true):(false);
			}
			if(bDocYN)
				funcSearchSelect(2);
		}
		//종이지적도//
		if(frmMain->INIINFO.B_QRYCHECK[7])//통검은 지번 있는 것만//속도개선//지번없는 것은 설정에 따라 funcTotalSearchKeyword//
		{
			//200302
			bool bDocYN = false;

			if(frmSql->m_nKindOfDocIndex > -1)
			{
				bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC07_YN, "1")) ? (true):(false);
			}
			if(bDocYN)
				funcSearchSelect(7);
		}

		for(int i = 1; i < DF_DOC_CNT; i++)//191223//원복//#TAB00DEL#<검색>은 제외하기로//사장님Req//
		{
			if(i == 1 || i == 2 || i == 7 || i == 8)
				continue;

			if(frmMain->INIINFO.B_QRYCHECK[i])//통검은 지번 있는 것만//속도개선//지번없는 것은 설정에 따라 funcTotalSearchKeyword//
			{
				//200302
				bool bDocYN = false;

				if(i != 13 && i != 15 && i != 18)//지번있는 문서//
				{
					if(frmSql->m_nKindOfDocIndex > -1)
					{
						switch(i)
						{
							//201201//case 1:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC01_YN, "1")) ? (true):(false);	break;
							//201201//case 2:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC02_YN, "1")) ? (true):(false);	break;
							case 3:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC03_YN, "1")) ? (true):(false);	break;
							case 4:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC04_YN, "1")) ? (true):(false);	break;
							case 5:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC05_YN, "1")) ? (true):(false);	break;
							case 6:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC06_YN, "1")) ? (true):(false);	break;
							//201201//case 7:		bDocYN = true;	break;
							//201008//case 7:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC07_YN, "1")) ? (true):(false);	break;//201008//
							//201201//case 8:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC08_YN, "1")) ? (true):(false);	break;
							case 9:		bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC09_YN, "1")) ? (true):(false);	break;
							case 11:	bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC11_YN, "1")) ? (true):(false);	break;
							case 12:	bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC12_YN, "1")) ? (true):(false);	break;
							case 14:	bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC14_YN, "1")) ? (true):(false);	break;
							case 17:	bDocYN = (!strcmp(frmSql->m_vKINDOFDOCDATA[frmSql->m_nKindOfDocIndex].DOC17_YN, "1")) ? (true):(false);	break;
//231121//kindofdoc에 없는 필지인 경우 '통합검색'이 안 됨//							case 20:	bDocYN = frmSql->funcSQLGetGagamNoFromLandCd(frmMain->m_asSearchPnu); break;//231020//GAGAMLAYER in LandArchive
						}
					}

					//=========================================================
					//231121//kindofdoc에 없는 필지인 경우 '통합검색'이 안 됨//별도 처리//
					if(i == 20)
					{
						bDocYN = frmSql->funcSQLGetGagamNoFromLandCd(frmMain->m_asSearchPnu);//231020//GAGAMLAYER in LandArchive
					}
					//=========================================================

				}
				else//지번없는 문서//
				{
					switch(i)
					{
						case 13:	bDocYN = frmMain->INIINFO.B_DOCKIND[i];		break;
						case 15:	bDocYN = frmMain->INIINFO.B_DOCKIND[i];		break;
						case 18:	bDocYN = frmMain->INIINFO.B_DOCKIND[i];		break;
					}
                }
				if(bDocYN)
					funcSearchSelect(i);
			}
		}

		if(frmMain->INIINFO.B_MEMO)//메모//
		{
			funcSearchSelect(0);
		}
	}
	else//개별문서검색//
	{
		funcSearchSelect(frmMain->m_nActiveDoc);
	}


	//==================================================================
	//210204//#FIND_SPEED_TEST
	if(frmMain->m_ResultDocument08.size() > 0)//200926//
	{
		frmMain->totalCount[8] = frmMain->m_ResultDocument08.size();
		eTree->funcSettingTreeView(8);
		frmMain->totalCount[8] = frmMain->m_ResultDocument08.size();
	}
	if(frmMain->m_ResultDocument01.size() > 0)//200926//
	{
		frmMain->totalCount[1] = frmMain->m_ResultDocument01.size();
		eTree->funcSettingTreeView(1);
		frmMain->totalCount[1] = frmMain->m_ResultDocument01.size();
	}
	if(frmMain->m_ResultDocument02.size() > 0)//200926//
	{
		frmMain->totalCount[2] = frmMain->m_ResultDocument02.size();
		eTree->funcSettingTreeView(2);
		frmMain->totalCount[2] = frmMain->m_ResultDocument02.size();
	}
	if(frmMain->m_ResultDocument07.size() > 0)//200926//
	{
		frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
		eTree->funcSettingTreeView(7);
		frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
	}
	if(frmMain->m_ResultDocument03.size() > 0)//200926//
	{
		frmMain->totalCount[3] = frmMain->m_ResultDocument03.size();
		eTree->funcSettingTreeView(3);
		frmMain->totalCount[3] = frmMain->m_ResultDocument03.size();
	}
	if(frmMain->m_ResultDocument04.size() > 0)//200926//
	{
		frmMain->totalCount[4] = frmMain->m_ResultDocument04.size();
		eTree->funcSettingTreeView(4);
		frmMain->totalCount[4] = frmMain->m_ResultDocument04.size();
	}
	if(frmMain->m_ResultDocument06.size() > 0)//200926//
	{
		frmMain->totalCount[6] = frmMain->m_ResultDocument06.size();
		eTree->funcSettingTreeView(6);
		frmMain->totalCount[6] = frmMain->m_ResultDocument06.size();
	}
	if(frmMain->m_ResultDocument09.size() > 0)//200926//
	{
		frmMain->totalCount[9] = frmMain->m_ResultDocument09.size();
		eTree->funcSettingTreeView(9);
		frmMain->totalCount[9] = frmMain->m_ResultDocument09.size();
	}
	if(frmMain->m_ResultDocument11.size() > 0)//200926//
	{
		frmMain->totalCount[11] = frmMain->m_ResultDocument11.size();
		eTree->funcSettingTreeView(11);
		frmMain->totalCount[11] = frmMain->m_ResultDocument11.size();
	}
	if(frmMain->m_ResultDocument15.size() > 0)//200926//
	{
		frmMain->totalCount[15] = frmMain->m_ResultDocument15.size();
		eTree->funcSettingTreeView(15);
		frmMain->totalCount[15] = frmMain->m_ResultDocument15.size();
	}
	if(frmMain->m_ResultDocument17.size() > 0)//200926//
	{
		frmMain->totalCount[17] = frmMain->m_ResultDocument17.size();
		eTree->funcSettingTreeView(17);
		frmMain->totalCount[17] = frmMain->m_ResultDocument17.size();
	}
	if(frmMain->m_ResultDocument18.size() > 0)//200926//
	{
		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
		eTree->funcSettingTreeView(18);
		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
	}
	//==================================================================
	//==================================================================
	//231020//GAGAMLAYER in LandArchive
	//==================================================================
	if(frmMain->m_ResultDocument20.size() > 0)
	{
		frmMain->totalCount[20] = frmMain->m_ResultDocument20.size();
		eTree->funcSettingTreeView(20);
		frmMain->totalCount[20] = frmMain->m_ResultDocument20.size();
	}
	//==================================================================


	//funcSaveLog(2, 0, "");//save to file
	funcSaveLog(9, 0, "TREE");

	if(frmMain->treSystem->Items->Count == 0)//200302//moved
	{
		frmMain->lblJibunMent1->Caption = "검색결과가 없습니다.";
		if(frmMain->m_nActiveDoc == 0)//200526
		{
			if( !frmMain->INIUSERSETINFO.B_AUTOJIBUN )
				frmMain->lblJibunMent2->Visible = true;
			else
				frmMain->lblJibunMent2->Visible = false;
		}
		else
		{
			frmMain->lblJibunMent2->Visible = false;
		}
		frmMain->pnlJibunMent->Visible = true;
	}

	frmMain->funcSetWaitWindows(false);
	funcSetSearchFinish();
	frmMain->m_bSearching	= false;//200303
	funcSaveLog(2, 0, "");//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcTotalSearchKeyword()
{
//	frmMain->funcWriteLogData("키워드 검색을 합니다.");//231219//#WriteLog//

	frmMain->funcSetWaitWindows(true);

	frmMain->funcInitSearchList();
	funcInitSearchSuccess();

	funcSaveLog(0, 0, "");//first

//230207//funcSetUserHistState()Param변경//
//	AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "검색");//210305//#44710//1
//	if( !asKindCode.IsEmpty() )
//		frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), frmMain->m_nActiveDoc);
	frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "검색", frmMain->m_nActiveDoc);

	if(frmMain->m_nActiveDoc == 0)
	{
		for(int i = 1; i < DF_DOC_CNT; i++)//191223//원복//#TAB00DEL#<검색>은 제외하기로//사장님Req//
		{
			if(frmMain->INIINFO.B_QRYCHECK[i])//통검시 지번 없는 것도 검색//지번 자동변경 사용안함 일때만//
			{
				bool bDocYN = false;
				switch(i)
				{
					case 13:	bDocYN = frmMain->INIINFO.B_DOCKIND[i];		break;
					case 15:	bDocYN = frmMain->INIINFO.B_DOCKIND[i];		break;
					case 18:	bDocYN = frmMain->INIINFO.B_DOCKIND[i];		break;
				}
				if(bDocYN)
					funcSearchSelect(i);
			}
		}
		if(frmMain->INIINFO.B_MEMO)//메모//
		{
			funcSearchSelect(0);
		}
	}


	//==================================================================
	//210204//#FIND_SPEED_TEST
	if(frmMain->m_ResultDocument13.size() > 0)
	{
		frmMain->totalCount[13] = frmMain->m_ResultDocument13.size();
		eTree->funcSettingTreeView(13);
		frmMain->totalCount[13] = frmMain->m_ResultDocument13.size();
	}
	if(frmMain->m_ResultDocument15.size() > 0)//200926//
	{
		frmMain->totalCount[15] = frmMain->m_ResultDocument15.size();
		eTree->funcSettingTreeView(15);
		frmMain->totalCount[15] = frmMain->m_ResultDocument15.size();
	}
	if(frmMain->m_ResultDocument18.size() > 0)//200926//
	{
		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
		eTree->funcSettingTreeView(18);
		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
	}
	//==================================================================
	//==================================================================
	//231020//GAGAMLAYER in LandArchive
	//==================================================================
	if(frmMain->m_ResultDocument20.size() > 0)//200926//
	{
		frmMain->totalCount[20] = frmMain->m_ResultDocument20.size();
		eTree->funcSettingTreeView(20);
		frmMain->totalCount[20] = frmMain->m_ResultDocument20.size();
	}
	//==================================================================


	if(frmMain->treSystem->Items->Count == 0)//200302//moved
	{
		frmMain->lblJibunMent1->Caption = "검색결과가 없습니다.";
		if(frmMain->m_nActiveDoc == 0)//200526
		{
			if( !frmMain->INIUSERSETINFO.B_AUTOJIBUN )
				frmMain->lblJibunMent2->Visible = true;
			else
				frmMain->lblJibunMent2->Visible = false;
		}
		else
		{
			frmMain->lblJibunMent2->Visible = false;
		}
		frmMain->pnlJibunMent->Visible = true;
	}

	frmMain->funcSetWaitWindows(false);
	funcSetSearchFinish();
	frmMain->m_bSearching	= false;//200303
	funcSaveLog(2, 0, "");//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSearchSelect(int nType)
{
	funcSaveLog(9, 0, "QUERY_START");

	try{
		switch(nType)
		{
			case  1: func_Search1(); break;
			case  2: func_Search2(); break;
			case  3: func_Search3(); break;
			case  4: func_Search4(); break;
			case  5: func_Search5(); break;
			case  6: func_Search6(); break;
			case  7: func_Search7(); break;
			case  8: func_Search8(); break;
			case  9: func_Search9(); break;
//			case 10: func_Search10(); break;
			case 11: func_Search11(); break;
			case 12: func_Search12(); break;
			case 13: func_Search13(); break;
			case 14: func_Search14(); break;
			case 15: func_Search15(); break;
//			case 16: func_Search16(); break;
			case 17: func_Search17(); break;
			case 18: func_Search18(); break;
			case 20: func_Search20(); break;//231020//GAGAMLAYER//
			case  0: func_SearchMemo(); break;//#MEMOSEARCH#//
			default:
				break;
		}
	}
	__finally{
		searchSuccess[nType] = true;
	}
	funcSaveLog(9, 0, "QUERY_END");
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search1()
{
	AnsiString asItem  		= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asSql 		= "";
	AnsiString asColumn		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asSqlD 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu = "";//frmMain->m_asSearchPnu;

	asColumn = "distinct ROLL_NO, FRAME_NO, KWON_NO, KIND_CODE, PAGE_NO, SUBMIT_YEAR, PRCS_DATE, MEASURE_TYPE, GROUP_NO, GROUP_NO1, AF_PNU, PATH_NAME";
	asOrderBy = "ORDER BY PRCS_DATE DESC, MEASURE_TYPE, PATH_NAME, KWON_NO, FRAME_NO, AF_PNU ASC";

//	//=============================================================
//	//210302//TEST//
//	asPnu = frmMain->m_asSearchPnu;
//	asSql	= "select distinct A.ROLL_NO, A.FRAME_NO, A.KWON_NO, A.KIND_CODE, A.PAGE_NO, A.SUBMIT_YEAR, A.PRCS_DATE, A.MEASURE_TYPE, A.GROUP_NO, A.GROUP_NO1, A.AF_PNU, A.PATH_NAME from tb_document01 A,";
//	asSql	= asSql + " (SELECT distinct KWON_NO, PRCS_DATE, MEASURE_TYPE, GROUP_NO, GROUP_NO1, PATH_NAME FROM TB_DOCUMENT01";
//	asSql	= asSql + " WHERE (BF_PNU='" + asPnu.Trim() + "' OR AF_PNU='" + asPnu.Trim() + "') AND (KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50')";
//	asSql	= asSql + " ORDER BY PRCS_DATE DESC, MEASURE_TYPE, PATH_NAME, KWON_NO, FRAME_NO, AF_PNU ASC) B";
//	//asSql	= asSql + " where A.KWON_NO=B.KWON_NO AND A.PRCS_DATE=B.PRCS_DATE AND A.MEASURE_TYPE=B.MEASURE_TYPE AND A.GROUP_NO=B.GROUP_NO AND A.GROUP_NO1=B.GROUP_NO1";
//	asSql	= asSql + " where A.KWON_NO=B.KWON_NO AND A.PRCS_DATE=B.PRCS_DATE AND A.MEASURE_TYPE=B.MEASURE_TYPE AND A.GROUP_NO=B.GROUP_NO";
//	//201221//그룹1,2 처리//
//	if(frmMain->INIUSERSETINFO.DOC01GROUP == 2)
//	{
//		asSqlC =  " AND (A.GROUP_NO1=B.GROUP_NO1 OR A.KIND_CODE = '12' OR A.GROUP_NO1 = 1)";
//	}
////	else//210218//GROUP_NO가 같은 모든 데이터 검색이므로 결의서를 특정하면 구비서류등이 나오지 않음.//4413136025104950002//
////	//210108//결의서 또는 구비서류 또는 GROUP_NO1=1 인 데이터는 항상 검색//
////	{
////		asSqlC =  "";
////	}
//	asSql	= asSql + asSqlC;
//	asSql	= asSql + " ORDER BY PRCS_DATE DESC, MEASURE_TYPE, KIND_CODE, PATH_NAME, KWON_NO, FRAME_NO, AF_PNU ASC";
//	frmSql->funcReadDocument01(asSql.c_str());
//	//=============================================================

//	//210302//TEST//
	if(frmMain->m_nActiveDoc == 0)
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(BF_PNU='" + asPnu.Trim() + "' OR AF_PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(BF_PNU LIKE '" + asPnu.Trim() + "%' OR AF_PNU LIKE '" + asPnu.Trim() + "%') ";

			//=============================================================================
			//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
			//=============================================================================
			//ORG//frmMain->cboKindDoc1->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
			if(frmMain->m_asParamStr2 != "SYSTEM_OK_USER_B")
			{
				if( asSqlPNU.IsEmpty())
					asSqlA = "(KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";//200428//44250//KLReq//조서=신청서격//
				else
					asSqlA = "AND (KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";//200428//44250//KLReq//조서=신청서격//
			}
			else
			{
				if( asSqlPNU.IsEmpty())
					asSqlA = "(KIND_CODE = '10') ";//KLReq//조서=신청서격//
				else
					asSqlA = "AND (KIND_CODE = '10') ";//KLReq//조서=신청서격//
			}
			//=============================================================================

			//--
			asSql = "SELECT " + asColumn + " FROM TB_DOCUMENT01 WHERE " + asSqlPNU + asSqlA + asOrderBy;
			frmSql->funcReadDocument01(asSql.c_str());
		}
	}
	else//byCondition
	{
		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + frmMain->m_asSearchPnu + "' OR AF_PNU='" + frmMain->m_asSearchPnu + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + frmMain->m_asSearchPnu + "%' OR AF_PNU LIKE '" + frmMain->m_asSearchPnu + "%') ";

		if (frmMain->cboInputDoc1->ItemIndex > 0) //기본 -1  ,전체가 아니면
		{
			asItem = frmMain->m_BASECODE_101_DOC1[frmMain->cboInputDoc1->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )
				asSqlA = "MEASURE_TYPE = '" + asItem + "' ";
			else
				asSqlA = "AND MEASURE_TYPE = '" + asItem + "' ";
		}

		if (frmMain->cboKindDoc1->ItemIndex > 0) //기본 0
		{
			m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_001_DOC1[frmMain->cboKindDoc1->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty())
				asSqlB = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlB = "AND KIND_CODE = '" + asItem + "' ";
		}
		else
		{
			//=============================================================================
			//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
			//=============================================================================
			//ORG//frmMain->cboKindDoc1->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
			if(frmMain->m_asParamStr2 == "SYSTEM_OK_USER_B")
			{
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty())
					asSqlB = "KIND_CODE = '10' ";
				else
					asSqlB = "AND KIND_CODE = '10' ";
			}
        }

		startDate = StringReplace(frmMain->dtStartDayDoc1->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(frmMain->dtEndDayDoc1->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
		if( !startDate.IsEmpty() && !endDate.IsEmpty() )//if(frmMain->cbReqDay1->Checked)
		{
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty())
				asSqlC = "(PRCS_DATE >= '" + startDate + "' AND PRCS_DATE <= '" + endDate + "') ";
			else
				asSqlC = "AND (PRCS_DATE >= '" + startDate + "' AND PRCS_DATE <= '" + endDate + "') ";
		}

		if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() )//181217
			 asSqlD = "AF_PNU != '' ";
		else
			 asSqlD = " AND AF_PNU != '' ";

//		if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() )//181217
//			asSqlD = "(KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";
//		else
//			asSqlD = " AND (KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC + asSqlD;
		//--
		asSql = "SELECT " + asColumn + " FROM TB_DOCUMENT01 " + asWhere + asOrderBy;

		frmSql->funcReadDocument01(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument01.size() > 0)//200926//
//	{
//		frmMain->totalCount[1] = frmMain->m_ResultDocument01.size();
//		eTree->funcSettingTreeView(1);
//		frmMain->totalCount[1] = frmMain->m_ResultDocument01.size();
//	}

	funcSaveLog(1, 1, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search2()
{
	AnsiString asItem  		= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";

	//---
	asOrderBy = "ORDER BY ";

	if(frmMain->m_nActiveDoc == 0)//byJibun
	{
		//200810//결의일자->측량일자 변경요청
		//(울주군청의 경우 지번이 없는 데이터가 많고, 결의일자 없는 데이터가 많아서 상세검색도 어려움이 발생하여 변경//
		//통합검색일때는 '환경설정에서 설정한 일자'로 정렬//
	    if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
		    asOrderBy = asOrderBy + "SURV_DAY DESC, ";
	    else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
		    asOrderBy = asOrderBy + "INSPCT_DAY DESC, ";
	    else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
		    asOrderBy = asOrderBy + "SUBMIT_DATE DESC, ";
	    asOrderBy = asOrderBy + "KIND_CODE, PATH_NAME, AF_PNU, BF_PNU ASC";
    
		//---
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + asPnu.Trim() + "' OR AF_PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + asPnu.Trim() + "%' OR AF_PNU LIKE '" + asPnu.Trim() + "%') ";
		//--
		asSql = "SELECT * FROM TB_DOCUMENT02 WHERE " + asSqlPNU + asOrderBy;
		frmSql->funcReadDocument02(asSql.c_str());
	}
	else//byCondition
	{
		//200810//결의일자->측량일자 변경요청
		//(울주군청의 경우 지번이 없는 데이터가 많고, 결의일자 없는 데이터가 많아서 상세검색도 어려움이 발생하여 변경//
		//상세검색일때는 '측량일자'로 정렬//
		asOrderBy = asOrderBy + "SURV_DAY DESC, ";
		asOrderBy = asOrderBy + "KIND_CODE, PATH_NAME, AF_PNU, BF_PNU ASC";


		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + frmMain->m_asSearchPnu + "' OR AF_PNU='" + frmMain->m_asSearchPnu + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + frmMain->m_asSearchPnu + "%' OR AF_PNU LIKE '" + frmMain->m_asSearchPnu + "%') ";

		if (frmMain->cboInputDoc2->ItemIndex > 0) //기본 -1  ,전체가 아니면
		{
			asItem = frmMain->m_BASECODE_102_DOC2[frmMain->cboInputDoc2->ItemIndex-1].kind_code;//200526//#6//종목코드오류//
			if( asSqlPNU.IsEmpty() )
				asSqlA = "SURV_ITEM = '" + asItem + "' ";
			else
				asSqlA = "AND SURV_ITEM = '" + asItem + "' ";
		}

		startDate = StringReplace(frmMain->dtStartDayDoc2->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(frmMain->dtEndDayDoc2->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
		if( !startDate.IsEmpty() && !endDate.IsEmpty() )//if(frmMain->cbReqDay1->Checked)
		{
			//200810//결의일자->측량일자 변경요청
			//(울주군청의 경우 지번이 없는 데이터가 많고, 결의일자 없는 데이터가 많아서 상세검색도 어려움이 발생하여 변경//
//			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
//				asSqlB = "(SUBMIT_DATE >= '" + startDate + "' AND SUBMIT_DATE <= '" + endDate + "') ";
//			else
//				asSqlB = "AND (SUBMIT_DATE >= '" + startDate + "' AND SUBMIT_DATE <= '" + endDate + "') ";
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
				asSqlB = "(SURV_DAY >= '" + startDate + "' AND SURV_DAY <= '" + endDate + "') ";
			else
				asSqlB = "AND (SURV_DAY >= '" + startDate + "' AND SURV_DAY <= '" + endDate + "') ";
		}

		if(frmMain->edtDohoDoc2->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtDohoDoc2->Text;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )//181217
				asSqlC =  "DOHO = '" + asItem + "' ";
			else
				asSqlC =  "AND DOHO = '" + asItem + "' ";
		}

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT02 " + asWhere + asOrderBy;
		frmSql->funcReadDocument02(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument02.size() > 0)//200926//
//	{
//		frmMain->totalCount[2] = frmMain->m_ResultDocument02.size();
//		eTree->funcSettingTreeView(2);
//		frmMain->totalCount[2] = frmMain->m_ResultDocument02.size();
//	}

	funcSaveLog(1, 2, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search3()
{
	AnsiString asItem  		= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";

	asOrderBy = "ORDER BY SURV_DAY DESC, PATH_NAME, AF_PNU, BF_PNU ASC";

	if(frmMain->m_nActiveDoc == 0)//byJibun
	{
		//---
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + asPnu.Trim() + "' OR AF_PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + asPnu.Trim() + "%' OR AF_PNU LIKE '" + asPnu.Trim() + "%') ";
		//--
		asSql = "SELECT * FROM TB_DOCUMENT03 WHERE " + asSqlPNU + asOrderBy;
		frmSql->funcReadDocument03(asSql.c_str());
	}
	else//byCondition
	{
		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + frmMain->m_asSearchPnu + "' OR AF_PNU='" + frmMain->m_asSearchPnu + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + frmMain->m_asSearchPnu + "%' OR AF_PNU LIKE '" + frmMain->m_asSearchPnu + "%') ";

		startDate = StringReplace(frmMain->dtStartDayDoc3->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(frmMain->dtEndDayDoc3->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
		if( !startDate.IsEmpty() && !endDate.IsEmpty() )//if(frmMain->cbReqDay1->Checked)
		{
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
				asSqlB = "(SURV_DAY >= '" + startDate + "' AND SURV_DAY <= '" + endDate + "') ";
			else
				asSqlB = "AND (SURV_DAY >= '" + startDate + "' AND SURV_DAY <= '" + endDate + "') ";
		}

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT03 " + asWhere + asOrderBy;
		frmSql->funcReadDocument03(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument03.size() > 0)//200926//
//	{
//		frmMain->totalCount[3] = frmMain->m_ResultDocument03.size();
//		eTree->funcSettingTreeView(3);
//		frmMain->totalCount[3] = frmMain->m_ResultDocument03.size();
//	}

	funcSaveLog(1, 3, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search4()
{
	AnsiString asItem  		= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asSqlD 		= "";//230331//#ADD_FUNC_DOC04_44130//
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";



//============================================
//[DEBUG]
	TStringList *qry = new TStringList();
	qry->Clear();
	qry->Text = "";
//============================================

	asOrderBy = "ORDER BY LAW_NO DESC, REQ_DAY DESC, REC_NO, KIND_CODE, PATH_NAME, PNU, ROLL_NO ASC";//230410//LAW_NO 기준 폴더링으로 컬럼 추가//

	if(frmMain->m_nActiveDoc == 0)//byJibun
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

			//--
			asSql = "SELECT * FROM TB_DOCUMENT04 WHERE " + asSqlPNU + asOrderBy;
			frmSql->funcReadDocument04(asSql.c_str());

//============================================
//[DEBUG]
		qry->Add(asSql);
//============================================

		}
	}
	else//byCondition
	{
		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "PNU='" + frmMain->m_asSearchPnu + "' ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님
			asSqlPNU = "PNU LIKE '" + frmMain->m_asSearchPnu + "%' ";

		if (frmMain->cboKindDoc4->ItemIndex > 0) //기본 -1  ,전체가 아니면
		{
			//201021//특조법 상세 문서구분 검색표시 다르지 않아서 주석처리//m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_004_DOC4[frmMain->cboKindDoc4->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )
				asSqlA = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
		}
		if(frmMain->edtRecNoDoc4->Text.Trim().Length() > 0)
		{
			//REC_NO type is VARCHAR2 ---------------------------------
			AnsiString 	asRecNo  = frmMain->edtRecNoDoc4->Text;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
				asSqlB = "REC_NO = '" + asRecNo + "' ";//"9-102" format
			else
				asSqlB = "AND REC_NO = '" + asRecNo + "' ";//"9-102" format
		}
		if(frmMain->edtKwonNoDoc4->Text.Trim().Length() > 0)
		{
			//ROLL_NO type is VARCHAR2 ---------------------------------
			AnsiString 	asKwonNo  = frmMain->edtKwonNoDoc4->Text.Trim();
			if( !asKwonNo.IsEmpty() )
			{
//200205//KWON_NO//항상4자리 아닐 수 있음, 입력한 숫자값만 찾는다//				asKwonNo.sprintf("%04d", asKwonNo.ToInt());
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
					asSqlC = "KWON_NO = '" + asKwonNo + "' ";
				else
					asSqlC = "AND KWON_NO = '" + asKwonNo + "' ";
			}
		}
		//==================================================================================================
		//230331//#ADD_FUNC_DOC04_44130//신청인, 보증인 명 혼재. 이름 앞뒤로 '/'를 붙인다. ex) /홍길동/홍로동/  과 같이 글자 맨 앞, 뒤, 중간에 구분자 적용할 것//
		//==================================================================================================
		if(frmMain->edtNamesDoc4->Text.Trim().Length() > 0)
		{
			//OWN_NAME type is VARCHAR ---------------------------------
			AnsiString 	asName  = frmMain->edtNamesDoc4->Text;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
				asSqlB = "OWN_NAME LIKE '%" + asName + "%' ";
			else
				asSqlB = "AND OWN_NAME LIKE '%" + asName + "%' ";
		}
		//=================================================

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC + asSqlD;
		//Order By
		asOrderBy = "ORDER BY REQ_DAY DESC, PATH_NAME, PNU, ROLL_NO ASC";
		//--
		asSql = "SELECT * FROM TB_DOCUMENT04 " + asWhere + asOrderBy;
		frmSql->funcReadDocument04(asSql.c_str());

//============================================
//[DEBUG]
		qry->Add(asSql);
//============================================

	}

//============================================
//[DEBUG]
	 if(frmMain->m_bDEBUG && qry->Count > 0)
	 {
		AnsiString  asFileName	= frmMain->LOGPATH + "qry.txt";
		if(FileExists(asFileName))
			DeleteFile(asFileName);

		qry->SaveToFile(asFileName);

		qry->Clear();
		qry->Text	= "";
	 }
	 delete qry;
	 qry = NULL;
//============================================



	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument04.size() > 0)//200926//
//	{
//		frmMain->totalCount[4] = frmMain->m_ResultDocument04.size();
//		eTree->funcSettingTreeView(4);
//		frmMain->totalCount[4] = frmMain->m_ResultDocument04.size();
//	}

	funcSaveLog(1, 4, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search5()
{
	AnsiString asItem  		= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asWhere 		= "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";

	//Order By
	asOrderBy = "ORDER BY PRCS_DATE DESC, MEASURE_TYPE, PATH_NAME, AF_PNU, BF_PNU, ROLL_NO, GROUP_NO, GROUP_NO1 ASC";

	if(frmMain->m_nActiveDoc == 0)//byJibun
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(BF_PNU='" + asPnu.Trim() + "' OR AF_PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(BF_PNU LIKE '" + asPnu.Trim() + "%' OR AF_PNU LIKE '" + asPnu.Trim() + "%') ";

			//--
			asSql = "SELECT * FROM TB_DOCUMENT05 WHERE " + asSqlPNU + asOrderBy;
			frmSql->funcReadDocument05(asSql.c_str());
		}
	}
	else//byCondition
	{
		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + frmMain->m_asSearchPnu + "' OR AF_PNU='" + frmMain->m_asSearchPnu + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + frmMain->m_asSearchPnu + "%' OR AF_PNU LIKE '" + frmMain->m_asSearchPnu + "%') ";

		if (frmMain->cboInputDoc5->ItemIndex > 0)
		{
			asItem = frmMain->m_BASECODE_109_DOC5[frmMain->cboInputDoc5->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )
				asSqlA = "MEASURE_TYPE = '" + asItem + "' ";
			else
				asSqlA = "AND MEASURE_TYPE = '" + asItem + "' ";
		}

		startDate = StringReplace(frmMain->dtStartDayDoc5->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(frmMain->dtEndDayDoc5->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
		if( !startDate.IsEmpty() && !endDate.IsEmpty() )//if(frmMain->cbReqDay1->Checked)
		{
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
				asSqlB = "(PRCS_DATE >= '" + startDate + "' AND PRCS_DATE <= '" + endDate + "') ";
			else
				asSqlB = "AND (PRCS_DATE >= '" + startDate + "' AND PRCS_DATE <= '" + endDate + "') ";
		}

		if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
			asSqlC = "(KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";
		else
			asSqlC = " AND (KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT05 " + asWhere + asOrderBy;
		frmSql->funcReadDocument05(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument05.size() > 0)//200926//
//	{
//		frmMain->totalCount[5] = frmMain->m_ResultDocument05.size();
//		eTree->funcSettingTreeView(5);
//		frmMain->totalCount[5] = frmMain->m_ResultDocument05.size();
//	}

	funcSaveLog(1, 5, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search6()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";

	asOrderBy = "ORDER BY COMP_YEAR DESC, ZONE_CODE, KIND_CODE, KWON_NO, PAGE_NO ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		if(frmMain->m_asSearchText.Length() > 0 )//200318//if(frmMain->edtMainSearchText->Text.Trim().Length() > 0 )
		{
			AnsiString asZoneCode = "";
			AnsiString asZoneCol = "ZONE_CODE LIKE '%";
			AnsiString asLike = "%'";
			AnsiString asKeyword = frmMain->m_asSearchText;
			frmSql->funcZoneCodeLikeQuery(asKeyword);
			if(frmMain->m_vDOC6_ZONECODE.size() == 0)
			{
				//상세일때만 알림//frmMsg->funcMessageDlg("정보부재알림:", "해당되는 지구명이 없습니다.", 3);
				//200204//통합검색일때는 지구명 검색이 아닐 수 있으므로 종료할 필요 없다//return;
			}

			for(int i = 0; i < (int)frmMain->m_vDOC6_ZONECODE.size(); i++)
			{
				asZoneCode = frmMain->m_vDOC6_ZONECODE[i].zonecode;
				if(i == 0)//first
				{
					if( asSqlPNU.IsEmpty() )//181217
						asSqlA = " (";
					else
						asSqlA = " AND (";
				}
				else
					asSqlA = asSqlA + " OR ";

				asSqlA = asSqlA + asZoneCol + asZoneCode + asLike;//common

				if(i == (int)frmMain->m_vDOC6_ZONECODE.size() - 1)//last
					asSqlA = asSqlA + ") ";
			}
		}

		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + frmMain->m_asSearchPnu + "' OR AF_PNU='" + frmMain->m_asSearchPnu + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + frmMain->m_asSearchPnu + "%' OR AF_PNU LIKE '" + frmMain->m_asSearchPnu + "%') ";

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA;

		//--
		asSql = "SELECT * FROM TB_DOCUMENT06 WHERE " + asSqlPNU + asOrderBy;
		frmSql->funcReadDocument06(asSql.c_str());
	}
	else//byCondition
	{
		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(BF_PNU='" + frmMain->m_asSearchPnu + "' OR AF_PNU='" + frmMain->m_asSearchPnu + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(BF_PNU LIKE '" + frmMain->m_asSearchPnu + "%' OR AF_PNU LIKE '" + frmMain->m_asSearchPnu + "%') ";

		if(frmMain->edtZoneNmDoc6->Text.Trim().Length() > 0 )
		{
			AnsiString asZoneCode = "";
			AnsiString asZoneCol = "ZONE_CODE LIKE '%";
			AnsiString asLike = "%'";
			AnsiString asKeyword = frmMain->edtZoneNmDoc6->Text.Trim();
			frmSql->funcZoneCodeLikeQuery(asKeyword);
			if(frmMain->m_vDOC6_ZONECODE.size() == 0)
			{
				frmMsg->funcMessageDlg("정보부재알림:", "해당되는 지구명이 없습니다.", 3);
				return;
			}

			for(int i = 0; i < (int)frmMain->m_vDOC6_ZONECODE.size(); i++)
			{
				asZoneCode = frmMain->m_vDOC6_ZONECODE[i].zonecode;
				if(i == 0)//first
				{
					if( asSqlPNU.IsEmpty() )
						asSqlA = "(";
					else
						asSqlA = " AND (";
				}
				else
					asSqlA = asSqlA + " OR ";

				asSqlA = asSqlA + asZoneCol + asZoneCode + asLike;//common

				if(i == (int)frmMain->m_vDOC6_ZONECODE.size() - 1)//last
					asSqlA = asSqlA + ") ";
			}
		}
		if (frmMain->cboKindDoc6->ItemIndex > 0)
		{
			//201021//환지계획서 상세 문서구분 검색표시 다르지 않아서 주석처리//m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_006_DOC6[frmMain->cboKindDoc6->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )//일치검색//231014//asSqlPNU 추가//
				asSqlB = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlB = "AND KIND_CODE = '" + asItem + "' ";
//			if( asSqlA.IsEmpty() )
//				asSqlB = "KIND_CODE LIKE '%" + asItem + "%' ";
//			else
//				asSqlB = "AND KIND_CODE LIKE '%" + asItem + "%' ";
		}
		if (frmMain->edtKwonNoDoc6->Text.Trim().Length() > 0)
		{
			asItem = frmMain->edtKwonNoDoc6->Text.Trim();
//			if( asItem.Length() >= 4 )//권번호 보통 4자리인데, 5자리인경우도 있어서, 4자리 이상 입력하면 입력 그대로 검색하도록 변경//44760:5자리//
//			{
//				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
//					asSqlC = "KWON_NO = '" + asItem + "' ";
//				else
//					asSqlC = "AND KWON_NO = '" + asItem + "' ";
//			}
			if( !asItem.IsEmpty() )
			{
//200205//KWON_NO//항상4자리 아닐 수 있음, 입력한 숫자값만 찾는다//								asItem.sprintf("%04d", asItem.ToInt());
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
					asSqlC = "KWON_NO = '" + asItem + "' ";
				else
					asSqlC = "AND KWON_NO = '" + asItem + "' ";
			}
//			int nLen, nStt = 0;
//			asItem = frmMain->edtKwonNoDoc6->Text.Trim();
//			nLen = asItem.Length();
//			nStt = 5 - nLen + 1;
//			if( asSqlA.IsEmpty() && asSqlB.IsEmpty() )//181217
//				asSqlC = "SUBSTR(VOL_NUM, " + IntToStr(nStt) + ", " + IntToStr(nLen) + ") = '" + asItem + "' ";
//			else
//				asSqlC = "AND SUBSTR(VOL_NUM, " + IntToStr(nStt) + ", " + IntToStr(nLen) + ") = '" + asItem + "' ";
		}
		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC;

		//--
		asSql = "SELECT * FROM TB_DOCUMENT06 " + asWhere + asOrderBy;
		frmSql->funcReadDocument06(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument06.size() > 0)//200926//
//	{
//		frmMain->totalCount[6] = frmMain->m_ResultDocument06.size();
//		eTree->funcSettingTreeView(6);
//		frmMain->totalCount[6] = frmMain->m_ResultDocument06.size();
//	}

	funcSaveLog(1, 6, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search7()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asSqlD 		= "";
	AnsiString asWhere      = "";
	AnsiString asColumn     = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu 		= "";//frmMain->m_asSearchPnu;
	int			nLength		= frmMain->m_asSearchPnu.Length();

//231219//Mod//	asColumn 	= "distinct ROLL_NO, KWON_NO, KIND_CODE, SIDOSGG, UMD, RI, SCALE, DOHO_BON, X1, Y1, X2, Y2, BASE_X, BASE_Y, RATIOX, RATIOY, PATH_NAME";
	asColumn 	= "distinct ROLL_NO, KWON_NO, KIND_CODE, SIDOSGG, UMD, RI, SCALE, DOHO_BON, X1, Y1, X2, Y2, SIZE_X, SIZE_Y, BASE_X, BASE_Y, RATIOX, RATIOY, PATH_NAME";//231219//Mod//SIZE_X, SIZE_Y 추가([도곽선 표시]에 사용)
	asOrderBy 	= "KWON_NO, KIND_CODE, SCALE, DOHO_BON ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		if(nLength == 19)//통합검색 혹은 상세이면서 pnu=19인 경우//
		{
			frmMain->m_vLANDINFO.clear();
			frmMain->m_vLANDINFO_SUB.clear();//201227//

//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
			if(frmMain->_SIDOCODE == "36110" && frmMain->m_asSejongOldPnu.Length() == 19)
			{
				frmSql->funcQrySelect_LAND_INFO_MAPPOINT(false, frmMain->m_asSejongOldPnu);
			}
			else if(frmMain->_SIDOCODE != "11305")//v1.0.0.6//11305//강북구//이미지좌표값이 존재(TB_DOCUMENT07_PNU)하므로 아래 함수 처리 필요 없음//
			{
				frmSql->funcQrySelect_LAND_INFO_MAPPOINT(false, frmMain->m_asSearchPnu);
			}
			//OLD//frmSql->funcQrySelect_LAND_INFO_MAPPOINT(false, frmMain->m_asSearchPnu);

			m_bDoc07Check     = false;
			m_sDoc07DohoCheck = "";

			//201227//
			//===================================================================
			for(int i = 0; i < (int)frmMain->m_vLANDINFO.size(); i++)
			{
				frmSql->funcQrySelect_DOCUMENT07_MAPPOINT(false, i, "");//데이터 있으면 tree 구성 함수 안에서 처리한다//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
			}

			//201217//태안//
			//DOC07도곽좌표 없고, DOC07_PNU이미지 좌표만 있다면//
			//shape에 없는 좌표는 검색되지만, shape에 없는 좌표는 검색되지 않는다//
			if(frmMain->m_ResultDocument07.size() == 0)
			{
				frmSql->funcQrySelect_DOCUMENT07_PNU(false, frmMain->m_asSearchPnu);
			}

	//210204//#FIND_SPEED_TEST
//			if(frmMain->m_ResultDocument07.size() > 0)//200926//
//			{
//				frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
//				eTree->funcSettingTreeView(7);
//				frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
//			}

			frmSearch->funcSaveLog(1, 7, asSql);//save to file
		}
	}
	else//byCondition
	{
		//
		asItem = frmMain->edtUmdRiCd->Text.Trim();
//v1.0.0.6//11305//강북구//		if (frmMain->_SIDOCODE == "36110" && asItem.Length() == 10)//210203//시군구+읍면동+리코드//
//세종시, 강북구에는 다른 지역 자료도 존재해서 10자리로 들어오는 경우가 존재//
		if (asItem.Length() == 10)//210203//시군구+읍면동+리코드//
		{
			if(frmMain->_SIDOCODE == "36110" || frmMain->_SIDOCODE == "11305")//세종시, 강북구에는 다른 지역 자료도 존재해서 10자리로 들어오는 경우가 존재//
			{
				asSqlPNU = "SIDOSGG = '" + asItem.SubString(1, 5) + "' ";//201216//44131검색하는데 44133이 검색된다.
				asSqlPNU = asSqlPNU + "AND UMD = '" + asItem.SubString(6, 3) + "' ";
				asSqlPNU = asSqlPNU + "AND RI = '" + asItem.SubString(9, 2) + "' ";
			}
		}
		else if (asItem.Length() == 5)//읍면동+리코드//
		{
			//200427//asSqlPNU = "KWON_NO = '" + asItem + "' ";
			asSqlPNU = "SIDOSGG = '" + frmMain->_SIDOCODE + "' ";//201216//44131검색하는데 44133이 검색된다.
			asSqlPNU = asSqlPNU + "AND UMD = '" + asItem.SubString(1, 3) + "' ";
			asSqlPNU = asSqlPNU + "AND RI = '" + asItem.SubString(4, 2) + "' ";
		}
		else if (asItem.Length() == 3)//읍면동코드만//
		{
			//200427//asSqlPNU = "KWON_NO LIKE '" + asItem + "%' ";
			asSqlPNU = "SIDOSGG = '" + frmMain->_SIDOCODE + "' ";//201216//44131검색하는데 44133이 검색된다.
			asSqlPNU = "AND UMD = '" + asItem.SubString(1, 3) + "' ";
		}

		if (frmMain->cboKindDoc7->ItemIndex > 0)
		{
			m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_007_DOC7[frmMain->cboKindDoc7->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )//181217
				asSqlA = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
		}
		if(frmMain->edtDohoDoc7->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtDohoDoc7->Text;//'1'입력하면 '001'검색하도록 변경//
			if( !asItem.IsEmpty() )
			{
				asItem.sprintf("%03d", asItem.ToInt());
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
					asSqlB =  "DOHO_BON = '" + asItem + "' ";
				else
					asSqlB =  "AND DOHO_BON = '" + asItem + "' ";
			}
		}
		if(frmMain->cboScaleDoc7->ItemIndex > 0)
		{
			asItem  = frmMain->cboScaleDoc7->Text;
			asItem	= StringReplace(asItem, "1:", "", TReplaceFlags() << rfReplaceAll);
			if(asItem.Length() >= 3)
			{
				asItem = asItem.SubString(1, asItem.Length()-2);
				asItem.sprintf("%02d", asItem.ToInt());
			}

			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
				asSqlC = "SCALE = '" + asItem + "' ";
			else
				asSqlC = "AND SCALE = '" + asItem + "' ";
		}


//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
		if(nLength == 19)//통합검색 혹은 상세이면서 pnu=19인 경우//
		{
			frmMain->m_vLANDINFO.clear();
			frmMain->m_vLANDINFO_SUB.clear();//201227//

//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
			if(frmMain->_SIDOCODE == "36110" && frmMain->m_asSejongOldPnu.Length() == 19)
//=============================================================================
			{
				frmSql->funcQrySelect_LAND_INFO_MAPPOINT(false, frmMain->m_asSejongOldPnu);
			}
			else if(frmMain->_SIDOCODE != "11305")//v1.0.0.6//11305//강북구//이미지좌표값이 존재(TB_DOCUMENT07_PNU)하므로 아래 함수 처리 필요 없음//
			{
				frmSql->funcQrySelect_LAND_INFO_MAPPOINT(false, frmMain->m_asSearchPnu);
			}
			//OLD//frmSql->funcQrySelect_LAND_INFO_MAPPOINT(false, frmMain->m_asSearchPnu);

			m_bDoc07Check     = false;
			m_sDoc07DohoCheck = "";

			//201227//
			//===================================================================
			for(int i = 0; i < (int)frmMain->m_vLANDINFO.size(); i++)
			{
				frmSql->funcQrySelect_DOCUMENT07_MAPPOINT(false, i, /*asSqlPNU + */asSqlA + asSqlB + asSqlC);//데이터 있으면 tree 구성 함수 안에서 처리한다//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
			}

			//201217//태안//
			//DOC07도곽좌표 없고, DOC07_PNU이미지 좌표만 있다면//
			//shape에 없는 좌표는 검색되지만, shape에 없는 좌표는 검색되지 않는다//
			if(frmMain->m_ResultDocument07.size() == 0)
			{
				frmSql->funcQrySelect_DOCUMENT07_PNU(false, frmMain->m_asSearchPnu);//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
			}
		}
		else
		{
//=============================================================================
			//Where
			if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
				asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC;
			//Order By
			//191210//LAND_GBN 때문에 KIND_CODE, 2, 4, 6 이 맨 뒤에 나옴//asOrderBy = "ORDER BY SIDOSGG, UMD, RI, LAND_GBN, KIND_CODE, SCALE, DOHO_BON ASC";
			asOrderBy = "ORDER BY SIDOSGG, UMD, RI, KIND_CODE, SCALE, DOHO_BON ASC";

			//--
			asSql = "SELECT " + asColumn + " FROM TB_DOCUMENT07 " + asWhere + asOrderBy;//[TODO]TABLE 변경하기//
			frmSql->funcReadDocument07(asSql.c_str());

		//210204//#FIND_SPEED_TEST
	//		if(frmMain->m_ResultDocument07.size() > 0)//200926//
	//		{
	//			frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
	//			eTree->funcSettingTreeView(7);
	//			frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
	//		}
		}

		funcSaveLog(1, 7, asSql);//save to file
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search8()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";

	//[ORACLE]asOrderBy = "ORDER BY PNU, SINGU_NAME, KIND_CODE ASC, ONOFF_CODE ASC NULLS FIRST";
	//200624//PAGE_NO추가//문서구분 같은것이 여러장일때 같은 페이지의 앞뒤가 붙어서 나오지 않는다.
	asOrderBy = "ORDER BY PNU, SINGU_NAME, KIND_CODE ASC, PAGE_NO, ONOFF_CODE ASC, ISNULL(ONOFF_CODE)";//[MYSQL]

	if(frmMain->m_nActiveDoc == 0)
	{
    	//---
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

		//asSqlA = "AND (KIND_CODE = '13' OR KIND_CODE = '50') ";
		//--
		asSql = "SELECT * FROM TB_DOCUMENT08 WHERE " + asSqlPNU + asOrderBy;
		frmSql->funcReadDocument08(asSql.c_str());
//		//[TODO] 본번, 부번 있는지도 체크해야 함//
//		if(frmMain->m_asSearchText.Length() > 0 )
//		{
//			AnsiString asPnuCode = "";
//			AnsiString asPnuCol = "PNU LIKE '%";
//			AnsiString asLike = "%'";
//			AnsiString asKeyword = frmMain->m_asSearchText;
//			frmSql->funcSidoCodeLikeQuery(asKeyword);
//			if(frmMain->m_vPNU_SIDOCODE.size() == 0)
//			{
//				//상세일때만 알림//frmMsg->funcMessageDlg("정보부재알림:", "해당되는 지역명이 없습니다.", 3);
//				return;
//			}
//
//			for(int i = 0; i < (int)frmMain->m_vPNU_SIDOCODE.size(); i++)
//			{
//				asPnuCode = (char*)frmMain->m_vPNU_SIDOCODE[i].cSggCd;
//				asPnuCode = asPnuCode + (char*)frmMain->m_vPNU_SIDOCODE[i].cUmdCd;
//				asPnuCode = asPnuCode + (char*)frmMain->m_vPNU_SIDOCODE[i].cRiCd;
//
//				if(i == 0)//first
//					asSqlA = " (";
//				else
//					asSqlA = asSqlA + " OR ";
//
//				asSqlA = asSqlA + asPnuCol + asPnuCode + asLike;//common
//
//				if(i == (int)frmMain->m_vPNU_SIDOCODE.size() - 1)//last
//					asSqlA = asSqlA + ") ";
//			}
//		}
//		//Where
//		if( !asSqlA.IsEmpty() )
//			asWhere = "WHERE " + asSqlA + " ";
	}
	else//byCondition
	{
		int nLength = frmMain->m_asSearchPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "PNU='" + frmMain->m_asSearchPnu + "' ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님
			asSqlPNU = "PNU LIKE '" + frmMain->m_asSearchPnu + "%' ";

//231226//[구대장.문서구분]에서는 '전체'제거//항상 '검색조건'이 존재//
		{
			m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_008_DOC8[frmMain->cboKindDoc8->ItemIndex].kind_code;
			if( asSqlPNU.IsEmpty() )
				asSqlA = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
		}
//		if (frmMain->cboKindDoc8->ItemIndex > 0)//문서종류//
//		{
//			m_bKindDoc = true;
//
//			asItem = frmMain->m_BASECODE_008_DOC8[frmMain->cboKindDoc8->ItemIndex-1].kind_code;
//			if( asSqlPNU.IsEmpty() )
//				asSqlA = "KIND_CODE = '" + asItem + "' ";
//			else
//				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
//		}
		if (frmMain->cboInputDoc8->ItemIndex > 0)//문서구분//
		{
			m_bInputDoc = true;

			asItem = frmMain->m_BASECODE_108_DOC8[frmMain->cboInputDoc8->ItemIndex-1].kind_name;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )
				asSqlB = "SINGU_NAME = '" + asItem + "' ";
			else
				asSqlB = "AND SINGU_NAME = '" + asItem + "' ";
		}
		if (frmMain->cboInputDoc8->Text == "부책" && frmMain->edtNamesDoc8->Text.Length() > 0)
		{
			asItem = frmMain->edtNamesDoc8->Text;
			asItem = StringReplace(asItem, " ", "", TReplaceFlags() << rfReplaceAll);
			//220603//유사검색*문자 검색 기능 변경//asItem = StringReplace(asItem, "*", "△", TReplaceFlags() << rfReplaceAll);
			asItem = StringReplace(asItem, "*", "%", TReplaceFlags() << rfReplaceAll);//220603//유사검색*문자 검색 기능 변경//

			//==========================================================
			//221128//#DOC08_CHANGE_FOR_SEARCHING_OWNINFO_DATA//
			//OLD//
//			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
//				asSqlC = "OWN_NAMES LIKE '%" + asItem + "%' ";
//			else
//				asSqlC = "AND OWN_NAMES LIKE '%" + asItem + "%' ";

			//TB_DOCUMENT08.OWN_NAMES에서 찾으면 1, TB_DOCUMENT08_OWNINFO에서 찾으면 0(Default)
			bool bOwnNames	= frmMain->CONFIGDOC8INI->ReadInteger("FUNCTIONS", "OWN_NAMES_TYPE", 0);
			if(bOwnNames)//####################
			{
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
					asSqlC = "OWN_NAMES LIKE '%" + asItem + "%' ";
				else
					asSqlC = "AND OWN_NAMES LIKE '%" + asItem + "%' ";
			}
			else//####################
			{
				AnsiString  asSubQuery	= "";
				AnsiString  asSubColumn	= "B.PATH_NAME";
				AnsiString  asSubTable	= "";//231226//"TB_DOCUMENT08_OWNINFO A, TB_OLDLANDDOC_PATHLIST B";
				AnsiString  asSubWhere	= " AND A.PATHLIST_SEQNO=B.SEQNO";

				AnsiString  asKindDoc	= frmMain->cboKindDoc8->Text;
				if(asKindDoc.AnsiPos("공유지연명부") == 0)
					asSubTable = "TB_DOCUMENT08_OWNINFO A, TB_OLDLANDDOC_PATHLIST B";
				else
					asSubTable = "TB_DOCUMENT08_SHAREOWN A, TB_OLDLANDDOC_PATHLIST B";

//=====================================================================
//[v1.0.0.5]//230524//구대장.상세검색.부책.소유자명+주소검색 기능추가
//ORG//			asSubWhere = "A.OWN_NAME LIKE '%" + asItem + "%'" + asSubWhere;
//NEW//
				if(frmMain->cboOwnNamesDoc8->ItemIndex == 0)//소유자//
				{
					asSubWhere = "A.OWN_NAME LIKE '%" + asItem + "%'" + asSubWhere;
				}
				else//주소//
				{
					asSubWhere = "A.OWN_ADDRESS LIKE '%" + asItem + "%'" + asSubWhere;
				}
//=====================================================================

				asSubQuery = "(SELECT DISTINCT " + asSubColumn + " FROM " + asSubTable + " WHERE " + asSubWhere + " GROUP BY " + asSubColumn + ") ";
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )
					asSqlC = "PATH_NAME IN " + asSubQuery;
				else
					asSqlC = "AND PATH_NAME IN " + asSubQuery;
			}
			//==========================================================
		}

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC;

		//--
		asSql = "SELECT * FROM TB_DOCUMENT08 " + asWhere + asOrderBy;
		frmSql->funcReadDocument08(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument08.size() > 0)//200926//
//	{
//		frmMain->totalCount[8] = frmMain->m_ResultDocument08.size();
//		eTree->funcSettingTreeView(8);
//		frmMain->totalCount[8] = frmMain->m_ResultDocument08.size();
//	}

	funcSaveLog(1, 8, asSql);//save to file
}
//---------------------------------------------------------------------------


void __fastcall TfrmSearch::func_Search9()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu 		= "";

	//Order By
	asOrderBy = "ORDER BY KIND_CODE ASC, BASE_YEAR DESC, BASE_MON DESC, PATH_NAME, PNU ASC";//201020//#ALLSEARCHLABEL

	if(frmMain->m_nActiveDoc == 0)
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

			//--
			asSql = "SELECT * FROM TB_DOCUMENT09 WHERE " + asSqlPNU + asOrderBy;
			frmSql->funcReadDocument09(asSql.c_str());
		}
	}
	else//byCondition
	{
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
		{
			asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
		}
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
		{
			if (frmMain->cboGbn->ItemIndex <= 1)
			{
					asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";
			}
			else//220104//논산>공시지가 문서에 블럭지번 포함//확정예정, 블록, 기타//
			{
				AnsiString  asPnuSUR	= "";//시군구+읍면동+리코드//
				AnsiString  asPnuBonbu	= "";
				//SGG+UMD+RI
				if(nLength >= 10)
				{
					asPnuSUR	= asPnu.SubString(1, 10);
				}
				//BonBu
				if(nLength >= 11)
				{
					asPnuBonbu	= asPnu.SubString(12, asPnu.Length() - 12);
					if(asPnuBonbu.IsEmpty())
					{
						asSqlPNU = "(PNU LIKE '" + asPnuSUR.Trim() + "%'";
						if(frmMain->cboGbn->ItemIndex == 2)
							asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 11, 1)>='3' and SUBSTR(PNU, 11, 1)<='4')";
						else if(frmMain->cboGbn->ItemIndex == 3)
							asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 11, 1)>='5' and SUBSTR(PNU, 11, 1)<='8')";
						else if(frmMain->cboGbn->ItemIndex == 4)
							asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 11, 1)='9')";
						asSqlPNU = asSqlPNU + ") ";
					}
					else
					{
						asSqlPNU = "(PNU LIKE '" + asPnuSUR.Trim() + "%'";
						if(frmMain->cboGbn->ItemIndex == 2)
							asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 11, 1)>='3' and SUBSTR(PNU, 11, 1)<='4')";
						else if(frmMain->cboGbn->ItemIndex == 3)
							asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 11, 1)>='5' and SUBSTR(PNU, 11, 1)<='8')";
						else if(frmMain->cboGbn->ItemIndex == 4)
							asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 11, 1)='9')";
						asSqlPNU = asSqlPNU + " and (SUBSTR(PNU, 12, " + asPnuBonbu.Length() + ")='" + asPnuBonbu + "') ";
					}
				}
				else
				{
					asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";
				}
			}
		}


		//
		if (frmMain->cboKindDoc9->ItemIndex > 0)
		{
			m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_009_DOC9[frmMain->cboKindDoc9->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )//181217
				asSqlA = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
		}
		if(frmMain->edtYearDoc9->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtYearDoc9->Text;
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )//181217
				asSqlB = "BASE_YEAR = '" + asItem + "' ";
			else
				asSqlB = "AND BASE_YEAR = '" + asItem + "' ";
		}
		if(frmMain->edtMonDoc9->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtMonDoc9->Text;
    		if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )//181217
				asSqlC =  "BASE_MON LIKE '" + asItem + "%' ";
			else
				asSqlC =  "AND BASE_MON LIKE '" + asItem + "%' ";
		}
		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT09 " + asWhere + asOrderBy;
		frmSql->funcReadDocument09(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument09.size() > 0)//200926//
//	{
//		frmMain->totalCount[9] = frmMain->m_ResultDocument09.size();
//		eTree->funcSettingTreeView(9);
//		frmMain->totalCount[9] = frmMain->m_ResultDocument09.size();
//	}

	funcSaveLog(1, 9, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search10()
{

}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_Search11()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu 		= "";

	//Order By
	asOrderBy = "ORDER BY KWON_NO, PATH_NAME, PAGE_NO, PNU ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		asPnu = frmMain->m_asSearchPnu;
 		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

			//---
			asSql = "SELECT * FROM TB_DOCUMENT11 WHERE " + asSqlPNU + asOrderBy;
			frmSql->funcReadDocument11(asSql.c_str());
		}
	}
	else//byCondition
	{
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

		//
		if (frmMain->cboKindDoc11->ItemIndex > 0)
		{
			asItem = frmMain->m_BASECODE_011_DOC11[frmMain->cboKindDoc11->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )//181217
				asSqlA = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
		}
		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA;

		//--
		asSql = "SELECT * FROM TB_DOCUMENT11 " + asWhere + asOrderBy;
		frmSql->funcReadDocument11(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument11.size() > 0)//200926//
//	{
//		frmMain->totalCount[11] = frmMain->m_ResultDocument11.size();
//		eTree->funcSettingTreeView(11);
//		frmMain->totalCount[11] = frmMain->m_ResultDocument11.size();
//	}

	funcSaveLog(1, 11, asSql);//save to file
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::func_Search12()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu 		= "";

	//Order By
	asOrderBy = "ORDER BY REQ_DAY DESC, ROLL_NO, PAGE_NO, KWON_NO, PATH_NAME, PNU ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

			//--
			asSql = "SELECT * FROM TB_DOCUMENT12 WHERE " + asSqlPNU + asOrderBy;
			frmSql->funcReadDocument12(asSql.c_str());
		}
	}
	else//byCondition
	{
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

		//
		asItem  = frmMain->edtDate12->Text;
		if( asSqlPNU.IsEmpty() )//181217
			asSqlA = "REQ_DAY LIKE '" + asItem + "%' ";
		else
			asSqlA = "AND REQ_DAY LIKE '" + asItem + "%' ";
		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA;

		//--
		asSql = "SELECT * FROM TB_DOCUMENT12 " + asWhere + asOrderBy;
		frmSql->funcReadDocument12(asSql.c_str());
	}

	if(frmMain->m_ResultDocument12.size() > 0)//200926//
	{
		frmMain->totalCount[12] = frmMain->m_ResultDocument12.size();
		eTree->funcSettingTreeView(12);
		frmMain->totalCount[12] = frmMain->m_ResultDocument12.size();
	}

	funcSaveLog(1, 12, asSql);//save to file
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::func_Search13()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asSqlD 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";

	//Order By
	asOrderBy = "ORDER BY REQ_DAY DESC, ROLL_NO, PAGE_NO, KWON_NO, PATH_NAME ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		asSqlA =  "OWN_REG_NO LIKE '%" + frmMain->m_asSearchText + "%' ";

		if(asSqlA.IsEmpty())
			asSqlB = "OWN_NAME LIKE '%" + frmMain->m_asSearchText + "%' ";
		else
			asSqlB = "OR OWN_NAME LIKE '%" + frmMain->m_asSearchText + "%' ";

		//Where
		if(!asSqlA.IsEmpty() || !asSqlB.IsEmpty())
			asWhere = "WHERE " + asSqlA + asSqlB;
		//Order By
		asOrderBy = "ORDER BY REQ_DAY DESC, ROLL_NO, PAGE_NO, KWON_NO, PATH_NAME ASC";
		//--
		asSql = "SELECT * FROM TB_DOCUMENT13 " + asWhere + asOrderBy;
		frmSql->funcReadDocument13(asSql.c_str());
	}
	else//byCondition
	{
		//--
		//190225//보증인위촉대장밖에 없지만, '전체'를 선택하면 강제로 보증인위촉대장만 선택해야 한다면
		//차라리 '전체'를 빼는게 나은거 아닌가?
		//[TODO]
		//190225//frmMain->cboInputDoc13->ItemIndex = 1;
		if (frmMain->cboKindDoc13->ItemIndex > 0)
		{
			//asItem = frmMain->m_BASECODE_004_DOC4[frmMain->cboInputDoc13->ItemIndex-1].kind_code;
			asItem = frmMain->m_BASECODE_042_DOC13[frmMain->cboKindDoc13->ItemIndex-1].kind_code;
			asSqlA = "KIND_CODE = '" + asItem + "' ";
		}
//		if(frmMain->edtOwnNameDoc13->Text.Trim().Length() > 0)
//		{
//			AnsiString asOwnName  = frmMain->edtOwnNameDoc13->Text;
//			if(asSqlA.IsEmpty() )//181217
//				asSqlB = "OWN_NAME = '" + asOwnName + "' ";
//			else
//				asSqlB = "AND OWN_NAME = '" + asOwnName + "' ";
//		}
		if(frmMain->edtReqNoDoc13->Text.Trim().Length() > 0)
		{
			AnsiString asOwnReqNo  = frmMain->edtReqNoDoc13->Text;
			if(asSqlA.IsEmpty() && asSqlB.IsEmpty() )//181217
				asSqlC =  "OWN_REG_NO LIKE '%" + asOwnReqNo + "%' ";
			else
				asSqlC =  "AND OWN_REG_NO LIKE '%" + asOwnReqNo + "%' ";
		}
		if(frmMain->edtOwnNmDoc13->Text.Trim().Length() > 0)
		{
			AnsiString asOwnNm  = frmMain->edtOwnNmDoc13->Text;
			if( !asOwnNm.IsEmpty() )
			{
				if(asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() )//181217
					asSqlD = "OWN_NAME LIKE '%" + asOwnNm + "%' ";
				else
					asSqlD = "AND OWN_NAME LIKE '%" + asOwnNm + "%' ";
			}
		}
		//Where
		if(!asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() )
			asWhere = "WHERE " + asSqlA + asSqlB + asSqlC + asSqlD;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT13 " + asWhere + asOrderBy;
		frmSql->funcReadDocument13(asSql.c_str());
	}

	if(frmMain->m_ResultDocument13.size() > 0)//200926//
	{
		frmMain->totalCount[13] = frmMain->m_ResultDocument13.size();
		eTree->funcSettingTreeView(13);
		frmMain->totalCount[13] = frmMain->m_ResultDocument13.size();
	}

	funcSaveLog(1, 13, asSql);//save to file
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::func_Search14()
{
	AnsiString asItem  		= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asSqlD 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu 		= "";

	//Order By
	asOrderBy = "ORDER BY PRCS_DATE DESC, ROLL_NO, GROUP_NO, GROUP_NO1, PATH_NAME, PNU ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

			//--
			asSqlA = "AND (KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";
			asSql = "SELECT * FROM TB_DOCUMENT14 WHERE " + asSqlPNU + asSqlA + asOrderBy;
			frmSql->funcReadDocument14(asSql.c_str());
		}
	}
	else//byCondition
	{
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

		//
		if (frmMain->cboInputDoc14->ItemIndex > 0)
		{
			asItem = frmMain->m_BASECODE_111_DOC14[frmMain->cboInputDoc14->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )//181217
				asSqlA = "MEASURE_TYPE = '" + asItem + "' ";
			else
				asSqlA = "AND MEASURE_TYPE = '" + asItem + "' ";
		}
		//
		startDate = StringReplace(frmMain->dtStartDayDoc14->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(frmMain->dtEndDayDoc14->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
		if( !startDate.IsEmpty() && !endDate.IsEmpty() )//if(frmMain->cbReqDay1->Checked)
		{
			if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() )//181217
				asSqlB = "(PRCS_DATE >= '" + startDate + "' AND PRCS_DATE <= '" + endDate + "') ";
			else
				asSqlB = "AND (PRCS_DATE >= '" + startDate + "' AND PRCS_DATE <= '" + endDate + "') ";
		}
		//
		if(frmMain->edtKwonNoDoc14->Text.Trim().Length() > 0)
		{
			AnsiString asKwonNo  = frmMain->edtKwonNoDoc14->Text;
			if( !asKwonNo.IsEmpty() )
			{
//200205//KWON_NO//항상4자리 아닐 수 있음, 입력한 숫자값만 찾는다//				asKwonNo.sprintf("%04d", asKwonNo.ToInt());
				if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() )//181217
					asSqlC =  "KWON_NO = '" + asKwonNo + "' ";
				else
					asSqlC =  "AND KWON_NO = '" + asKwonNo + "' ";
			}
		}
		if( asSqlPNU.IsEmpty() && asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() )//190120
			asSqlD = "(KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";
		else
			asSqlD = " AND (KIND_CODE = '10' OR KIND_CODE = '13' OR KIND_CODE = '50') ";

		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA + asSqlB + asSqlC + asSqlD;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT14 " + asWhere + asOrderBy;
		frmSql->funcReadDocument14(asSql.c_str());
	}

	if(frmMain->m_ResultDocument14.size() > 0)//200926//
	{
		frmMain->totalCount[14] = frmMain->m_ResultDocument14.size();
		eTree->funcSettingTreeView(14);
		frmMain->totalCount[14] = frmMain->m_ResultDocument14.size();
	}

	funcSaveLog(1, 14, asSql);//save to file
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::func_Search15()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC 		= "";
	AnsiString asSqlD 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";

	//Order By
	asOrderBy = "ORDER BY REG_NM, PRCS_DATE DESC, PATH_NAME ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
//=======================================================================
//v1.0.0.5//REQ//FLOW(JOB_NO:473)//ADD_DOC15_KIND_CODE_05//
		asSqlA = "(KIND_CODE = '02' OR KIND_CODE = '03' OR KIND_CODE = '05' OR KIND_CODE = '09' OR KIND_CODE = '50') ";//200207//명재씨Req//44150
//OLD//
//		//200527//#8//명재씨Req//비법인에 '결의서' 기본 검색문서로 추가//
//		asSqlA = "(KIND_CODE = '02' OR KIND_CODE = '03' OR KIND_CODE = '09' OR KIND_CODE = '50') ";//200207//명재씨Req//44150
//=======================================================================
		asSqlB = "AND (REG_NM LIKE '%" + frmMain->m_asSearchText + "%' ";
		asSqlC = " OR APP_NM LIKE '%" + frmMain->m_asSearchText + "%') ";

		//Where
		asWhere = "WHERE " + asSqlA + asSqlB + asSqlC;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT15 " + asWhere + asOrderBy;
		frmSql->funcReadDocument15(asSql.c_str());
	}
	else//byCondition
	{
//=======================================================================
//v1.0.0.5//REQ//FLOW(JOB_NO:473)//ADD_DOC15_KIND_CODE_05//
		asSqlA = "(KIND_CODE = '02' OR KIND_CODE = '03' OR KIND_CODE = '05' OR KIND_CODE = '09' OR KIND_CODE = '50') ";//200207//명재씨Req//44150
//OLD//
//		//200527//#8//명재씨Req//비법인에 '결의서' 기본 검색문서로 추가//
//		asSqlA = "(KIND_CODE = '02' OR KIND_CODE = '03' OR KIND_CODE = '09' OR KIND_CODE = '50') ";//200207//명재씨Req//44150
//=======================================================================
		//Doc15_신청번호삭제//190110
		/*if(frmMain->edtDocNoDoc15->Text.Trim().Length() > 0)
		{
			AnsiString asDocNo  = frmMain->edtDocNoDoc15->Text;
			asSqlB = "AND KIND_CODE LIKE '%" + asDocNo + "%' ";
		}*/
		if(frmMain->edtRegNmDoc15->Text.Trim().Length() > 0)
		{
			AnsiString asRecNm  = frmMain->edtRegNmDoc15->Text;
			//220630//asSqlC = "AND REG_NM LIKE '%" + asRecNm + "%' ";
			//220630//#홍성_비법인에 '대표자명'데이터가 추가되어 상세검색에서 검색되도록 수정요청//
			asSqlC = "AND (REG_NM LIKE '%" + asRecNm + "%' OR REPS_NM LIKE '%" + asRecNm + "%') ";
		}
		if(frmMain->edtRegNoDoc15->Text.Trim().Length() > 0)
		{
			AnsiString asRecNo  = frmMain->edtRegNoDoc15->Text;
			//201211//DB데이터에 '-'있어도 무시하고, 검색어에 '-'가 있어도 무시하고 검색하자//
			asRecNo	= StringReplace(asRecNo, "-", "", TReplaceFlags() << rfReplaceAll);
			asSqlD = "AND REPLACE(REG_NO, '-', '') LIKE '%" + asRecNo + "%' ";
		}
		//Where
		//Doc15_신청번호삭제//190110//asWhere = "WHERE " + asSqlA + asSqlB + asSqlC + asSqlD;
		asWhere = "WHERE " + asSqlA + asSqlC + asSqlD;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT15 " + asWhere + asOrderBy;
		frmSql->funcReadDocument15(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument15.size() > 0)//200926//
//	{
//		frmMain->totalCount[15] = frmMain->m_ResultDocument15.size();
//		eTree->funcSettingTreeView(15);
//		frmMain->totalCount[15] = frmMain->m_ResultDocument15.size();
//	}

	funcSaveLog(1, 15, asSql);//save to file
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::func_Search16()
{
//	AnsiString asItem  		= "";
//	AnsiString asSql 		= "";
//	AnsiString asSqlA 		= "";
//	AnsiString asSqlB 		= "";
//	AnsiString asWhere   	= "";
//	AnsiString asOrderBy 	= "";
//
//	if(frmMain->m_nActiveDoc == 0)
//	{
//		//
//	}
//	else//byCondition
//	{
//		if(frmMain->edtRegNameDoc16->Text.Trim().Length() > 0)
//		{
//			AnsiString asRegName  = frmMain->edtRegNameDoc16->Text;
//			asSqlA = "REG_NM LIKE '%" + asRegName + "%' ";
//		}
//		if(frmMain->edtRegNoDoc16->Text.Trim().Length() > 0)
//		{
//			AnsiString asRegNo  = frmMain->edtRegNoDoc16->Text;
//			if(asSqlA.IsEmpty() )//181217
//				asSqlB = "REG_NO LIKE '%" + asRegNo + "%' ";
//			else
//				asSqlB = "AND REG_NO LIKE '%" + asRegNo + "%' ";
//		}
//		//Where
//		if(!asSqlA.IsEmpty() || !asSqlB.IsEmpty() )
//			asWhere = "WHERE " + asSqlA + asSqlB;
//		//Order By
//		asOrderBy = "ORDER BY CINDEX DESC, PATH_NAME ASC";
//		//--
//		asSql = "SELECT * FROM TB_DOCUMENT16 " + asWhere + asOrderBy;
//		frmSql->funcReadDocument16(asSql.c_str());
//	}
//
//	frmMain->totalCount[16] = frmSql->m_ResultDocument16.size();
//	funcSaveLog(1, 16, asSql);//save to file
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::func_Search17()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlPNU 	= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu 		= "";

	//Order By
	asOrderBy = "ORDER BY KWON_NO, KIND_CODE, PATH_NAME, PNU ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		asPnu = frmMain->m_asSearchPnu;
		if( !asPnu.IsEmpty() )//통합검색인데 지번이 없으면 검색 안함//200110
		{
			int nLength = asPnu.Length();
			if (nLength == 19)//pnu 19
				asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
			else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
				asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";

			//--
			asSql = "SELECT * FROM TB_DOCUMENT17 WHERE " + asSqlPNU + asOrderBy;
			frmSql->funcReadDocument17(asSql.c_str());
		}
	}
	else//byCondition
	{
		asPnu = frmMain->m_asSearchPnu;
		int nLength = asPnu.Length();
		if (nLength == 19)//pnu 19
			asSqlPNU = "(PNU='" + asPnu.Trim() + "') ";
		else if (nLength > 5 && nLength < 19)//pnu 19 아님//시군구 정보만 있을 때는 PNU 조건 미포함//
			asSqlPNU = "(PNU LIKE '" + asPnu.Trim() + "%') ";


		if (frmMain->cboKindDoc17->ItemIndex > 0)
		{
			//minji//cd_kind에 017이 없음. 007(지적도)와 같다고 판단함//asItem = frmMain->m_BASECODE_017_DOC17[frmMain->cboInputDoc17->ItemIndex].kind_code;
			asItem = frmMain->m_BASECODE_017_DOC17[frmMain->cboKindDoc17->ItemIndex-1].kind_code;
			if( asSqlPNU.IsEmpty() )//181217
				asSqlA = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlA = "AND KIND_CODE = '" + asItem + "' ";
		}
		//Where
		if( !asSqlPNU.IsEmpty() || !asSqlA.IsEmpty() )
			asWhere = "WHERE " + asSqlPNU + asSqlA;
		//--
		asSql = "SELECT * FROM TB_DOCUMENT17 " + asWhere + asOrderBy;
		frmSql->funcReadDocument17(asSql.c_str());
	}

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument17.size() > 0)//200926//
//	{
//		frmMain->totalCount[17] = frmMain->m_ResultDocument17.size();
//		eTree->funcSettingTreeView(17);
//		frmMain->totalCount[17] = frmMain->m_ResultDocument17.size();
//	}

	funcSaveLog(1, 17, asSql);//save to file
}
//---------------------------------------------------------------------------
//void __fastcall TfrmSearch::func_Search18()
//{
//	AnsiString asItem  		= "";
//	AnsiString asSql 		= "";
//	AnsiString asSqlA 		= "";
//	AnsiString asSqlB 		= "";
//	AnsiString asSqlC		= "";
//	AnsiString asSqlD 		= "";
//	AnsiString asSqlE		= "";
//	AnsiString asSqlF		= "";
//	AnsiString asPnu		= "";
//	AnsiString asWhere   	= "";
//	AnsiString asOrderBy 	= "";
//	AnsiString startDate 	= "";
//	AnsiString endDate   	= "";
//	AnsiString asColumn		= "";
//	AnsiString asSqlSub		= "";
//
//	asColumn 	= "distinct JIGU_YEAR, JIGU_NAME, KWON_NO, KIND_CODE, GROUP_NO, PAGE_NO, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME";
//	asOrderBy 	= "JIGU_YEAR DESC, JIGU_NAME, KWON_NO, KIND_CODE, PAGE_NO, DOGNPOINT, BOJOPOINT, PATH_NAME ASC";
//
//	if(frmMain->m_nActiveDoc == 0)
//	{
//		//201104//좌표계산부 논산, 계룡은 pnu 존재, 당진은 존재하지 않음으로 해서 19자리 완성된 경우는 pnu에서 찾는다//
//		asPnu = frmMain->m_asSearchPnu;
//		if( asPnu.Length() == 19 )//통합검색인데 지번이 있으면 검색함//
//		{
//			//좌표계산부-지번 검색
//			asWhere 	= "PNU='" + asPnu.Trim() + "' ";
//		}
//		else
//		{
//			//좌표계산부-지구명 검색
//			asWhere		= "JIGU_NAME LIKE '%" + frmMain->m_asSearchText + "%'";
//		}
//	}
//	else if(frmMain->m_bDognIconClicked)
//	{
////		asItem = frmMain->m_ResultDocument18All[frmMain->m_nSelectDognIndex].KWON_NO;
////		if(asItem.IsEmpty())
////		{
////			frmMsg->funcMessageDlg("DB 확인 요청:", "권번호를 확인해주세요.", 3);
////			return;
////		}
////		asWhere		= "KWON_NO = '" + asItem.Trim() + "'";
//
//		asItem  = frmMain->m_ResultDocument18All[frmMain->m_nSelectDognIndex].X;
//		if( !asItem.IsEmpty() )
//		{
//			asSqlA = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//		}
//		asItem  = frmMain->m_ResultDocument18All[frmMain->m_nSelectDognIndex].Y;
//		if( !asItem.IsEmpty() )
//		{
//			if(asSqlA.IsEmpty())
//				asSqlB = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//			else
//				asSqlB = "AND BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//		}
//		if( asSqlA.IsEmpty() || asSqlB.IsEmpty())
//			return;//좌표 없으면 아무액션 안하고 나감//
//
//		asSqlSub = "(SELECT DISTINCT KWON_NO FROM TB_DOCUMENT18 WHERE " + asSqlA + asSqlB + ")";
//		asWhere = "KWON_NO IN " + asSqlSub;
//	}
//	else
//	{
//		if(frmMain->edtJigu18->Text.Trim().Length() > 0)
//		{
//			asItem  = frmMain->edtJigu18->Text;
//			asSqlA = "JIGU_NAME LIKE '%" + asItem.Trim() + "%' ";
//		}
//		if(frmMain->edtDogn18->Text.Trim().Length() > 0)
//		{
//			asItem  = frmMain->edtDogn18->Text;
//			if(asSqlA.IsEmpty() )
//				asSqlB = "DOGNPOINT = '" + asItem.Trim() + "' ";
//			else
//				asSqlB = "AND DOGNPOINT = '" + asItem.Trim() + "' ";
//		}
//		if(frmMain->edtX18->Text.Trim().Length() > 0)//X, Y 반대로 해달라는 요청 있었음//
//		{
//			asItem  = frmMain->edtX18->Text;
//			if( !asItem.IsEmpty() )
//			{
//				if(asSqlA.IsEmpty() && asSqlB.IsEmpty() )
//					asSqlC = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//				else
//					asSqlC = "AND BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//			}
//		}
//		if(frmMain->edtY18->Text.Trim().Length() > 0)
//		{
//			asItem  = frmMain->edtY18->Text;
//			if( !asItem.IsEmpty() )
//			{
//				if(asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() )
//					asSqlD = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//				else
//					asSqlD = "AND BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
//			}
//		}
//
////		AnsiString asStartYear	= frmMain->dtStartDayDoc18->Text.SubString(1, 4);
////		AnsiString asStartMonth	= frmMain->dtStartDayDoc18->Text.SubString(6, 2);
////		AnsiString asStartDay	= frmMain->dtStartDayDoc18->Text.SubString(9, 2);
////		AnsiString asEndYear	= frmMain->dtEndDayDoc18->Text.SubString(1, 4);
////		AnsiString asEndMonth	= frmMain->dtEndDayDoc18->Text.SubString(6, 2);
////		AnsiString asEndDay		= frmMain->dtEndDayDoc18->Text.SubString(9, 2);
////		int nStartYear	= 0;
////		int nStartMonth	= 0;
////		int nStartDay	= 0;
////		int nEndYear	= 0;
////		int nEndMonth	= 0;
////		int nEndDay		= 0;
////		if( !asStartYear.Trim().IsEmpty() )
////			nStartYear = asStartYear.ToInt();
////		if( !asStartMonth.Trim().IsEmpty() )
////			nStartMonth = asStartMonth.ToInt();
////		if( !asStartDay.Trim().IsEmpty() )
////			nStartDay = asStartDay.ToInt();
////		if( !asEndYear.Trim().IsEmpty() )
////			nEndYear = asEndYear.ToInt();
////		if( !asEndMonth.Trim().IsEmpty() )
////			nEndMonth = asEndMonth.ToInt();
////		if( !asEndDay.Trim().IsEmpty() )
////			nEndDay = asEndDay.ToInt();
//
//		startDate = StringReplace(frmMain->dtStartDayDoc18->Text, "-","",TReplaceFlags()<<rfReplaceAll);
//		endDate   = StringReplace(frmMain->dtEndDayDoc18->Text, "-","",TReplaceFlags()<<rfReplaceAll);
//		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
//		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
//		if( !startDate.IsEmpty() && !endDate.IsEmpty() )
//		{
//			if(startDate.Length() == 8 && endDate.Length() == 8)
//			{
//				if( asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() && asSqlD.IsEmpty())
//					asSqlE = "(CHECK_DATE >= '" + startDate + "' AND CHECK_DATE <= '" + endDate + "') ";
//				else
//					asSqlE = "AND (CHECK_DATE >= '" + startDate + "' AND CHECK_DATE <= '" + endDate + "') ";
//			}
////			else
////			{
////				startDate.sprintf("%04d%02d%02d", nStartYear, nStartMonth, nStartDay);
////				asSqlE = "(CHECK_DATE >= '" + startDate + "' ";
////
////				endDate.sprintf("%04d%02d%02d", nEndYear, nEndMonth, 0);
////				asSqlE = "AND CHECK_DATE >= '" + endDate + "') ";
////
////				if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() || !asSqlE.IsEmpty())
////					asSqlE = "AND " + asSqlE;
////			}
////			{
////				int nStartYear	= 0;
////				int nStartMonth	= 0;
////				int nStartDay	= 0;
////				int nEndYear	= 0;
////				int nEndMonth	= 0;
////				int nEndDay		= 0;
////				int nPos		= -1;
////				AnsiString asDate = "";
////				AnsiString asTemp = "";
////				if(startDate.Length() < 8)//8자리가 아닐때//
////				{
////					asDate = frmMain->dtStartDayDoc18->Text;
////					int nPos = asStartDay.Pos("-");
////					if(nPos > 1)
////					{
////						asTemp = asDate.SubString(1, nPos-1);
////						if( !asTemp.IsEmpty() )
////						{
////							nStartYear = asTemp.ToInt();
////							asStartDay = asDate.Delete(1, nPos);
////							nPos = asDate.Pos("-");
////							if(nPos > 1)
////							{
////								asTemp = asDate.SubString(1, nPos-1);
////								if( !asTemp.IsEmpty() )
////								{
////									nStartMonth = asTemp.ToInt();
////									asTemp = asDate.Delete(1, nPos);
////									if( !asTemp.IsEmpty() )
////										nStartDay = asTemp.ToInt();
////								}
////							}
////						}
////				}
////				if(endDate.Length() < 8)//8자리가 아닐때//
////				{
////					asDate = frmMain->dtEndDayDoc18->Text;
////					nPos = asDate.Pos("-");
////					if(nPos > 1)
////					{
////						nEndYear = asDate.SubString(1, nPos-1);
////						asDate = asDate.Delete(1, nPos);
////
////						nPos = asDate.Pos("-");
////						if(nPos > 1)
////						{
////							nEndMonth = asDate.SubString(1, nPos-1);
////							nEndDay = asDate.Delete(1, nPos);
////						}
////					}
////				}
////			}
//		}
//		if (frmMain->cboKindDoc18->ItemIndex > 0) //기본 0
//		{
//			m_bKindDoc = true;
//
//			asItem = frmMain->m_BASECODE_018_DOC18[frmMain->cboKindDoc18->ItemIndex-1].kind_code;
//			if( asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() && asSqlD.IsEmpty() && asSqlE.IsEmpty())
//				asSqlF = "KIND_CODE = '" + asItem + "' ";
//			else
//				asSqlF = "AND KIND_CODE = '" + asItem + "' ";
//		}
//
//		//Where
//		if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() || !asSqlE.IsEmpty() || !asSqlF.IsEmpty() )
//			asWhere = asSqlA + asSqlB + asSqlC + asSqlD + asSqlE + asSqlF;
//
////		asSqlSub = "KWON_NO IN (SELECT DISTINCT KWON_NO FROM TB_DOCUMENT18 WHERE " + asWhere + ")";
////		asWhere  = asSqlSub;
//	}
//
//	asSql.sprintf("SELECT %s FROM TB_DOCUMENT18 WHERE %s ORDER BY %s", asColumn, asWhere, asOrderBy);
//	frmSql->funcReadDocument18(asSql.c_str());
//
//	if(frmMain->m_ResultDocument18.size() > 0)//200926//
//	{
//		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
//		eTree->funcSettingTreeView(18);
//		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
//	}
//
//	funcSaveLog(1, 18, asSql);//save to file
//}
////---------------------------------------------------------------------------

//201105//
void __fastcall TfrmSearch::func_Search18()
{
	AnsiString asItem  		= "";
	AnsiString asSql 		= "";
	AnsiString asSqlA 		= "";
	AnsiString asSqlB 		= "";
	AnsiString asSqlC		= "";
	AnsiString asSqlD 		= "";
	AnsiString asSqlE		= "";
	AnsiString asSqlF		= "";
	AnsiString asPnu		= "";
	AnsiString asWhere   	= "";
	AnsiString asOrderBy 	= "";
	AnsiString startDate 	= "";
	AnsiString endDate   	= "";
	AnsiString asColumn		= "";
	AnsiString asSqlSub		= "";

	//201215//asColumn 	= "distinct JIGU_YEAR, JIGU_NAME, KWON_NO, KIND_CODE, GROUP_NO, PAGE_NO, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME";
	asColumn 	= "*";
	asOrderBy 	= "JIGU_YEAR DESC, JIGU_NAME, KWON_NO, KIND_CODE, PAGE_NO, DOGNPOINT, BOJOPOINT, PATH_NAME ASC";

	if(frmMain->m_nActiveDoc == 0)
	{
		//201104//좌표계산부 논산, 계룡은 pnu 존재, 당진은 존재하지 않음으로 해서 19자리 완성된 경우는 pnu에서 찾는다//
		asPnu = frmMain->m_asSearchPnu;
		if( asPnu.Length() == 19 )//통합검색인데 지번이 있으면 검색함//
		{
			//좌표계산부-지번 검색
			asWhere 	= "PNU='" + asPnu.Trim() + "' ";
		}
		else
		{
			//좌표계산부-지구명 검색
			asWhere		= "JIGU_NAME LIKE '%" + frmMain->m_asSearchText + "%'";
		}
	}
	else if(frmMain->m_bDognIconClicked)
	{
		asItem  = frmMain->m_ResultDocument18All[frmMain->m_nSelectDognIndex].X;
		if( !asItem.IsEmpty() )
		{
			asSqlA = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
		}
		asItem  = frmMain->m_ResultDocument18All[frmMain->m_nSelectDognIndex].Y;
		if( !asItem.IsEmpty() )
		{
			if(asSqlA.IsEmpty())
				asSqlB = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
			else
				asSqlB = "AND BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
		}
		if( asSqlA.IsEmpty() || asSqlB.IsEmpty())
			return;//좌표 없으면 아무액션 안하고 나감//

		asSqlSub = "(SELECT DISTINCT KWON_NO FROM TB_DOCUMENT18 WHERE " + asSqlA + asSqlB + ")";
		asWhere = "KWON_NO IN " + asSqlSub;
	}
	else
	{
		if(frmMain->edtJigu18->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtJigu18->Text;
			asSqlA = "JIGU_NAME LIKE '%" + asItem.Trim() + "%' ";
		}
		if(frmMain->edtDogn18->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtDogn18->Text;
			if(asSqlA.IsEmpty() )
				asSqlB = "DOGNPOINT = '" + asItem.Trim() + "' ";
			else
				asSqlB = "AND DOGNPOINT = '" + asItem.Trim() + "' ";
		}
		if(frmMain->edtX18->Text.Trim().Length() > 0)//X, Y 반대로 해달라는 요청 있었음//
		{
			asItem  = frmMain->edtX18->Text;
			if( !asItem.IsEmpty() )
			{
				if(asSqlA.IsEmpty() && asSqlB.IsEmpty() )
					asSqlC = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
				else
					asSqlC = "AND BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
			}
		}
		if(frmMain->edtY18->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtY18->Text;
			if( !asItem.IsEmpty() )
			{
				if(asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() )
					asSqlD = "BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
				else
					asSqlD = "AND BOJOPOINT LIKE '%" + asItem.Trim() + "%' ";
			}
		}

		startDate = StringReplace(frmMain->dtStartDayDoc18->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(frmMain->dtEndDayDoc18->Text, "-","",TReplaceFlags()<<rfReplaceAll);
		startDate = StringReplace(startDate, " ","",TReplaceFlags()<<rfReplaceAll);
		endDate   = StringReplace(endDate, " ","",TReplaceFlags()<<rfReplaceAll);
		if( !startDate.IsEmpty() && !endDate.IsEmpty() )
		{
			if(startDate.Length() == 8 && endDate.Length() == 8)
			{
				if( asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() && asSqlD.IsEmpty())
					asSqlE = "(CHECK_DATE >= '" + startDate + "' AND CHECK_DATE <= '" + endDate + "') ";
				else
					asSqlE = "AND (CHECK_DATE >= '" + startDate + "' AND CHECK_DATE <= '" + endDate + "') ";
			}

		}
		if (frmMain->cboKindDoc18->ItemIndex > 0) //기본 0
		{
			m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_018_DOC18[frmMain->cboKindDoc18->ItemIndex-1].kind_code;
			if( asSqlA.IsEmpty() && asSqlB.IsEmpty() && asSqlC.IsEmpty() && asSqlD.IsEmpty() && asSqlE.IsEmpty())
				asSqlF = "KIND_CODE = '" + asItem + "' ";
			else
				asSqlF = "AND KIND_CODE = '" + asItem + "' ";
		}

		//Where
		if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() || !asSqlD.IsEmpty() || !asSqlE.IsEmpty() || !asSqlF.IsEmpty() )
			asWhere = asSqlA + asSqlB + asSqlC + asSqlD + asSqlE + asSqlF;
	}

	asSql.sprintf("SELECT %s FROM TB_DOCUMENT18 WHERE %s ORDER BY %s", asColumn, asWhere, asOrderBy);
	frmSql->funcReadDocument18(asSql.c_str());

	//210204//#FIND_SPEED_TEST
//	if(frmMain->m_ResultDocument18.size() > 0)//200926//
//	{
//		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
//		eTree->funcSettingTreeView(18);
//		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
//	}

	funcSaveLog(1, 18, asSql);//save to file
}
//---------------------------------------------------------------------------


//==================================================================
//231020//GAGAMLAYER in LandArchive
//==================================================================
void __fastcall TfrmSearch::func_Search20()
{
	AnsiString 	asItem  	= "";
	AnsiString 	asSql 		= "";
	AnsiString 	asSqlA 		= "";
	AnsiString 	asSqlB 		= "";
	AnsiString 	asSqlC		= "";
	AnsiString 	asSqlSubQry = "";
	AnsiString  asColumn	= "KWON_NO, GAGAM_NO, UMDRI_CD, DOHO, DOC_NAME, KIND_CODE, PAGE_NO, SURV_DATE, SURV_ETC, PRCS_DATE, PATH_NAME";//241211//
	AnsiString 	asWhere     = "";
	AnsiString 	asOrderBy 	= "";
	AnsiString 	asPnu 		= "";
	int			nLength 	= 0;

	asPnu = frmMain->m_asSearchPnu;
	nLength = asPnu.Length();

	//Order By
	//ORDER BY KWON_NO, GAGAM_NO DESC => KWON_NO는 ASC로 GAGAM_NO는 DESC로 정렬한다.//
	//아래와 같이 개별적으로 DESC를 지정해줘야, 원하는 데이터 순으로 정렬한다.//
	asOrderBy = "ORDER BY KWON_NO DESC, GAGAM_NO DESC, KIND_CODE, PAGE_NO";

	if(frmMain->m_nActiveDoc == 0)
	{
		if( nLength != 19 )
			return;

		asSqlSubQry = "GAGAM_NO IN (SELECT GAGAM_NO FROM TB_DOCUMENT20_LANDLIST WHERE LAND_CD='" + asPnu.Trim() + "') ";

		//--
		asSql = "SELECT " + asColumn + " FROM TB_DOCUMENT20 WHERE " + asSqlSubQry + asOrderBy;
		//---
		frmSql->funcReadDocument20(asSql.c_str());
	}
	else//byCondition
	{
		//
		if (frmMain->cboKindDoc20->ItemIndex > 0)
		{
			m_bKindDoc = true;

			asItem = frmMain->m_BASECODE_020_DOC20[frmMain->cboKindDoc20->ItemIndex-1].kind_code;
			asSqlA = "KIND_CODE = '" + asItem + "' ";
		}
		if(frmMain->edtYearDoc20->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtYearDoc20->Text;
			if( asSqlA.IsEmpty() )
				asSqlB = "(KWON_NO = '" + asItem + "' OR SUBSTR(SURV_DATE, 1, 4) = '" + asItem + "' OR SUBSTR(PRCS_DATE, 1, 4) = '" + asItem + "') ";
			else
				asSqlB = "AND (KWON_NO = '" + asItem + "' OR SUBSTR(SURV_DATE, 1, 4) = '" + asItem + "' OR SUBSTR(PRCS_DATE, 1, 4) = '" + asItem + "') ";
		}
		if(frmMain->edtDocName20->Text.Trim().Length() > 0)
		{
			asItem  = frmMain->edtDocName20->Text;
			if( asSqlA.IsEmpty() && asSqlB.IsEmpty())
				asSqlC = "DOC_NAME LIKE '%" + asItem + "%' ";
			else
				asSqlC = "AND DOC_NAME LIKE '%" + asItem + "%' ";
		}

		if( !asPnu.IsEmpty() )
		{
			asSqlSubQry = "GAGAM_NO IN (SELECT GAGAM_NO FROM TB_DOCUMENT20_LANDLIST WHERE LAND_CD LIKE '" + asPnu.Trim() + "%') ";
			if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty())
				asSqlSubQry = "AND " + asSqlSubQry;
		}

		//Where
		if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
			asWhere = "WHERE " + asSqlA + asSqlB + asSqlC ;
		//--
		asSql = "SELECT " + asColumn + " FROM TB_DOCUMENT20 " + asWhere + asSqlSubQry + asOrderBy;
		//---
		frmSql->funcReadDocument20(asSql.c_str());
	}

	funcSaveLog(1, 20, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::func_SearchMemo()
{
	AnsiString asSql 		= "";
	AnsiString asSqlA 		= "";//TITLE
	AnsiString asSqlB 		= "";//POI_NAME
	AnsiString asSqlC 		= "";//MEMO
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPnu        = "";
	AnsiString asStr        = "";

	asOrderBy  = "POI_KEY DESC";

	//통합검색
	//문서아이콘 클릭
	//메모아이콘 클릭 - 메모창 바로가기하므로 검색결과 표시 안함//
	if(frmMain->m_nActiveDoc == 0)//byJibun
	{
//		if( !frmMain->m_asSearchText.IsEmpty() )
//		{
//			//통합검색-메모
//			asSqlA		= "TITLE LIKE '%" + frmMain->m_asSearchText + "%' ";
//		}
//		//210308//#ADDRESS_DUP//
//		if( !frmMain->m_asSearchPnu.IsEmpty() && !frmMain->m_asSearchText.IsEmpty())
//		{
//			asStr = frmMain->m_asSearchText;//210308//#ADDRESS_DUP//frmMain->func_ConvertLandcdToAddress(frmMain->m_asSearchPnu);
//			if( !asStr.Trim().IsEmpty() )//지번정보 있는지//
//			{
//				if( asSqlA.IsEmpty() )
//					asSqlB		= "POI_NAME = '" + asStr + "' ";
//				else
//					asSqlB		= "OR POI_NAME = '" + asStr + "' ";//210412//#MEMO_KEYWORD
//			}
//		}
//
//		if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() )
//		{
//			asWhere = asSqlA + asSqlB;
//			//--
//			asSql.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", frmMain->TABLE_MEMOINFO, asWhere, asOrderBy);
//			frmSql->funcReadMemo(asSql.c_str());
//		}

		//210429//#GAGAM44150
		if( !frmMain->m_asSearchText.IsEmpty() )
		{
			asStr = frmMain->m_asSearchText;
			//TITLE
			asSqlA		= "TITLE LIKE '%" + frmMain->m_asSearchText + "%' ";
			//POI_NAME
			asSqlB		= "OR POI_NAME = '%" + asStr + "%' ";
			//MEMO
			asSqlC		= "OR MEMO = '%" + asStr + "%' ";
		}

		if( !asSqlA.IsEmpty() || !asSqlB.IsEmpty() || !asSqlC.IsEmpty() )
		{
			asWhere = asSqlA + asSqlB + asSqlC;
			//--
			asSql.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", frmMain->TABLE_MEMOINFO, asWhere, asOrderBy);
			frmSql->funcReadMemo(asSql.c_str());
		}
	}

	frmMain->totalCount[0] = frmMain->m_ResultMemo.size();

	if(frmMain->totalCount[0] > 0)
		eTree->funcSettingTreeView(0);

	funcSaveLog(1, 0, asSql);//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSaveLog(int nType, int _nDoc, AnsiString _asSql)
{
	if (!DirectoryExists(frmMain->_HIST_PATH))//210223//#_HIST_
		CreateDir(frmMain->_HIST_PATH);

	if(nType == 0)//first
	{
		if(qry != NULL)
		{
			qry->Clear();
			qry->Text = "";
			qry->Add("[" + Now().FormatString("YYYY-MM-DD hh:nn:ss") + "]");
		}
	}
	else if(nType == 1)//searched datetime
	{
		if(qry != NULL)
		{
			if(_asSql.Length())
			{
				qry->Add(_asSql.c_str());
				qry->Add("[" + IntToStr(_nDoc) + "]COUNT : " + IntToStr(frmMain->totalCount[_nDoc]));
			}
		}
	}
	else if(nType == 2)//save to file
	{
		if(qry != NULL)
		{
			if(!frmMain->m_asSearchPnu.IsEmpty() )
				asQryFile 	= frmMain->_HIST_PATH + "qry_" + Now().FormatString("yyyymmddhhmmss") + "_" + frmMain->m_asSearchPnu + ".txt";//210223//#_HIST_
			else
				asQryFile 	= frmMain->_HIST_PATH + "qry_" + Now().FormatString("yyyymmddhhmmss") + "_" + IntToStr(frmMain->m_nActiveDoc) + ".txt";//210223//#_HIST_
			qry->SaveToFile(asQryFile.c_str());
			qry->Text = "";
			qry->Clear();
		}
	}
	else if(nType == 3)//save to file
	{
		if(qry != NULL)
		{
			asQryFile 	= frmMain->_HIST_PATH + "qry_" + Now().FormatString("yyyymmddhhmmss") + "_" + IntToStr(frmMain->m_nActiveDoc) + "_group.txt";//210223//#_HIST_
			qry->SaveToFile(asQryFile.c_str());
			qry->Text = "";
			qry->Clear();
		}
	}
	else if(nType == 4)//index label check
	{
		if(frmMain->m_bMSG)
		{
			if(qry != NULL)
			{
				qry->Clear();
				qry->Text = "";
			}
		}
	}
	else if(nType == 5)//index label check
	{
		if(frmMain->m_bMSG)
		{
			if(qry != NULL)
			{
				qry->Add(_asSql);
			}
		}
	}
	else if(nType == 6)//save to file
	{
		if(frmMain->m_bMSG)
		{
			if(qry != NULL)
			{
				asQryFile 	= frmMain->_HIST_PATH + "qry_INDEX" + IntToStr(_nDoc) + "_" + Now().FormatString("yyyymmddhhmmss") + "_group.txt";//210223//#_HIST_
				qry->SaveToFile(asQryFile.c_str());
				qry->Text = "";
				qry->Clear();
			}
		}
	}
	else if(nType == 7)//save to file - Thumb
	{
		if(qry != NULL)
		{
			qry->Add(_asSql.c_str());
			qry->Add("[" + IntToStr(_nDoc) + "]COUNT : " + IntToStr((int)frmMain->m_vThumbPathList.size()));
			for(int i = 0; i < (int)frmMain->m_vThumbPathList.size(); i++)
				qry->Add("[" + IntToStr(i) + "] : " + frmMain->m_vThumbPathList[i].PATH_NAME);

			if(!frmMain->m_asSearchPnu.IsEmpty() )
				asQryFile 	= frmMain->_HIST_PATH + "qry_" + Now().FormatString("yyyymmddhhmmss") + "_THUMB_" + frmMain->m_asSearchPnu + ".txt";//210223//#_HIST_
			else
				asQryFile 	= frmMain->_HIST_PATH + "qry_" + Now().FormatString("yyyymmddhhmmss") + "_THUMB_" + IntToStr(frmMain->m_nActiveDoc) + ".txt";//210223//#_HIST_
			qry->SaveToFile(asQryFile.c_str());
			qry->Text = "";
			qry->Clear();
		}
	}
	else if(nType == 9)//time
	{
		if(qry != NULL)
		{
			qry->Add(_asSql + "[" + Now().FormatString("YYYY-MM-DD hh:nn:ss") + "]");
		}
	}
	else if(nType == 10)//doc08_sql_count
	{
		if(qry != NULL)
		{
			if(_asSql.Length())
			{
				qry->Add(_asSql.c_str());
				qry->Add("[" + IntToStr(_nDoc) + "]COUNT : " + IntToStr((int)frmSql->m_ResultDoc08DBInfo.size()));
			}
		}
	}
	else if(nType == 11)//doc08_his_sql_count
	{
		if(qry != NULL)
		{
			if(_asSql.Length())
			{
				qry->Add(_asSql.c_str());
				qry->Add("[" + IntToStr(_nDoc) + "]COUNT : " + IntToStr((int)e08DataAlpha->m_ResultDoc08His.size()));
			}
		}
	}
	else if(nType == 12)//doc08_owninfo_sql_count
	{
		if(qry != NULL)
		{
			if(_asSql.Length())
			{
				qry->Add(_asSql.c_str());
				qry->Add("[" + IntToStr(_nDoc) + "]COUNT : " + IntToStr((int)e08DataAlpha->m_ResultDoc08OwnInfo.size()));
			}
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmSearch::funcSpaceSearch()
{
	frmMain->funcSetWaitWindows(true);

	frmMain->funcInitSearchList();
	funcInitSearchSuccess();

	//funcSaveLog(0, 0, "");//first
	funcSaveLog(9, 0, "QUERY");

//230207//funcSetUserHistState()Param변경//
//	AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "검색");//210305//#44710//1
//	if( !asKindCode.IsEmpty() )
//		frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), frmMain->m_nActiveDoc);
	frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "검색", frmMain->m_nActiveDoc);

	//1. 선택 영역안의 지번목록 가져오기//
	//200428//영역선택의 좌표 안에 심볼로 검색하는 것이 아니라 LAND_INFO로 검색하니까 안 맞게 검색된다//frmSql->funcQrySelect_LAND_INFO();
	LAND_INFO_STRUCT tempInfo;
	frmMain->m_vSPACELANDINFO.clear();//
	int m_nRecords  = frmMain->m_vSHPPOLYCBND.size();
	for(int i = 0; i < m_nRecords; ++i)
	{
		memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));

		if(frmMain->m_pgSpaceRectSP.x < frmMain->m_vSHPPOLYCBND[i].x && frmMain->m_vSHPPOLYCBND[i].x < frmMain->m_pgSpaceRectEP.x
			&& frmMain->m_pgSpaceRectSP.y < frmMain->m_vSHPPOLYCBND[i].y && frmMain->m_vSHPPOLYCBND[i].y < frmMain->m_pgSpaceRectEP.y)
		{
			strcpy(tempInfo.LAND_CD, frmMain->m_v_READCBND[i].PNU);
			tempInfo.X = frmMain->m_vSHPPOLYCBND[i].x;
			tempInfo.Y = frmMain->m_vSHPPOLYCBND[i].y;
			frmMain->m_vSPACELANDINFO.push_back(tempInfo);
		}
	}

	for(int i = 1; i < DF_DOC_CNT; i++)//191223//원복//#TAB00DEL#<검색>은 제외하기로//사장님Req//
	{
		//200310//if(frmMain->INIINFO.B_QRYCHECK[i] && frmMain->INIINFO.B_DOCFAVOR[i])
		if(frmMain->INIINFO.B_QRYCHECK[i])
		{
			funcSpaceSearchData(i);
		}
	}

	if(frmMain->INIINFO.B_MEMO)//#MEMOSEARCH#
	{
		funcSpaceSearchData(0);
	}

	//funcSaveLog(2, 0, "");//save to file
	funcSaveLog(9, 0, "TREE");

	if(frmMain->treSystem->Items->Count == 0)//200206//
	{
		frmMain->lblJibunMent1->Caption = "검색결과가 없습니다.";
		if(frmMain->m_nActiveDoc == 0)//200526
		{
			if( !frmMain->INIUSERSETINFO.B_AUTOJIBUN )
				frmMain->lblJibunMent2->Visible = true;
			else
				frmMain->lblJibunMent2->Visible = false;
		}
		else
		{
			frmMain->lblJibunMent2->Visible = false;
		}
		frmMain->pnlJibunMent->Visible = true;
	}

	frmMain->funcSetWaitWindows(false);
	funcSetSearchFinish();
	frmMain->m_bSearching	= false;//200303
	funcSaveLog(2, 0, "");//save to file
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData(int nType)
{
	try{
		switch(nType)
		{
			case  1: 	funcSpaceSearchData1(); 	break;
			case  2: 	funcSpaceSearchData2(); 	break;
			case  3: 	funcSpaceSearchData3(); 	break;
			case  4: 	funcSpaceSearchData4(); 	break;
			case  5: 	funcSpaceSearchData5(); 	break;
			case  6: 	funcSpaceSearchData6(); 	break;
			case  7:	funcSpaceSearchData7(); 	break;
			case  8: 	funcSpaceSearchData8(); 	break;
			case  9: 	funcSpaceSearchData9(); 	break;
			case 11: 	funcSpaceSearchData11(); 	break;
			case 12: 	funcSpaceSearchData12(); 	break;
			case 14: 	funcSpaceSearchData14(); 	break;
			case 17: 	funcSpaceSearchData17(); 	break;
			case 18: 	funcSpaceSearchData18(); 	break;
			case  0: 	funcSpaceSearchDataMemo(); 	break;
			default:
				break;
		}
	}
	__finally{
		searchSuccess[nType] = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData1()
{
	DOCUMENT01_STRUCT 				tempSpaceData01;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asColumn = "distinct ROLL_NO, FRAME_NO, KWON_NO, KIND_CODE, PAGE_NO, SUBMIT_YEAR, PRCS_DATE, MEASURE_TYPE, GROUP_NO, GROUP_NO1, AF_PNU, PATH_NAME";
	asOrder  = " ORDER BY PRCS_DATE DESC, MEASURE_TYPE, PATH_NAME, KWON_NO, FRAME_NO, AF_PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "AF_PNU = '" + asItem.Trim() + "'";
		asWhere  = asWhere + " AND (KIND_CODE = '13' OR KIND_CODE = '50')";//신청서
		asSql    = "SELECT " + asColumn + " FROM TB_DOCUMENT01 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument01(asSql.c_str());

		frmMain->totalCount[1] = frmMain->totalCount[1] + frmMain->m_ResultDocument01.size();
		funcSaveLog(1, 1, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument01.size();
	AnsiString asPrcsDate1 		= "";
	AnsiString asMeasureType1 	= "";
	AnsiString asPrcsDate2 		= "";
	AnsiString asMeasureType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
			asPrcsDate1    	= frmMain->m_ResultDocument01[j-1].PRCS_DATE;
			asMeasureType1 	= frmMain->m_ResultDocument01[j-1].MEASURE_TYPE;

			asPrcsDate2 	= frmMain->m_ResultDocument01[j].PRCS_DATE;
			asMeasureType2 	= frmMain->m_ResultDocument01[j].MEASURE_TYPE;

			if(asPrcsDate1 < asPrcsDate2)
			{
				swap(frmMain->m_ResultDocument01[j-1], frmMain->m_ResultDocument01[j]);
			}
			else if(asPrcsDate1 == asPrcsDate2)
			{
				if(asMeasureType1 > asMeasureType2)
				{
					swap(frmMain->m_ResultDocument01[j-1], frmMain->m_ResultDocument01[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[1] > 0)//200926//
	{
		eTree->funcSettingTreeView(1);
		frmMain->totalCount[1] = frmMain->m_ResultDocument01.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData2()
{
	DOCUMENT02_STRUCT 				tempSpaceData02;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY ";
	if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
		asOrder = asOrder + "SURV_DAY DESC, ";
	else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
		asOrder = asOrder + "INSPCT_DAY DESC, ";
	else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
		asOrder = asOrder + "SUBMIT_DATE DESC, ";
	asOrder = asOrder + "KIND_CODE, PATH_NAME, AF_PNU, BF_PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "AF_PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT02 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument02(asSql.c_str());

		frmMain->totalCount[2] = frmMain->totalCount[2] + frmMain->m_ResultDocument02.size();
		funcSaveLog(1, 2, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument02.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
				asDate1    	= frmMain->m_ResultDocument02[j-1].SURV_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
				asDate1    	= frmMain->m_ResultDocument02[j-1].INSPCT_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
				asDate1    	= frmMain->m_ResultDocument02[j-1].SUBMIT_DATE;

			asType1 	= frmMain->m_ResultDocument02[j-1].SURV_ITEM;

			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
				asDate2    	= frmMain->m_ResultDocument02[j].SURV_DAY;
        	else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
				asDate2    	= frmMain->m_ResultDocument02[j].INSPCT_DAY;
        	else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
				asDate2    	= frmMain->m_ResultDocument02[j].SUBMIT_DATE;

			asType2 	= frmMain->m_ResultDocument02[j].SURV_ITEM;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument02[j-1], frmMain->m_ResultDocument02[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument02[j-1], frmMain->m_ResultDocument02[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[2] > 0)
	{
		eTree->funcSettingTreeView(2);
		frmMain->totalCount[2] = frmMain->m_ResultDocument02.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData3()
{
	DOCUMENT03_STRUCT 				tempSpaceData03;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY SURV_DAY DESC, PATH_NAME, AF_PNU, BF_PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "AF_PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT03 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument03(asSql.c_str());

		frmMain->totalCount[3] = frmMain->totalCount[3] + frmMain->m_ResultDocument03.size();
		funcSaveLog(1, 3, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument03.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument03[j-1].SURV_DAY;
			asType1 	= frmMain->m_ResultDocument03[j-1].KIND_CODE;

		    asDate2    	= frmMain->m_ResultDocument03[j].SURV_DAY;
			asType2 	= frmMain->m_ResultDocument03[j].KIND_CODE;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument03[j-1], frmMain->m_ResultDocument03[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument03[j-1], frmMain->m_ResultDocument03[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[3] > 0)
	{
		eTree->funcSettingTreeView(3);
		frmMain->totalCount[3] = frmMain->m_ResultDocument03.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData4()
{
	DOCUMENT04_STRUCT 				tempSpaceData04;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY REQ_DAY DESC, PATH_NAME, PNU, ROLL_NO ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT04 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument04(asSql.c_str());

		frmMain->totalCount[4] = frmMain->totalCount[4] + frmMain->m_ResultDocument04.size();
		funcSaveLog(1, 4, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument04.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument04[j-1].REQ_DAY;
			asType1 	= frmMain->m_ResultDocument04[j-1].REC_NO;

		    asDate2    	= frmMain->m_ResultDocument04[j].REQ_DAY;
			asType2 	= frmMain->m_ResultDocument04[j].REC_NO;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument04[j-1], frmMain->m_ResultDocument04[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument04[j-1], frmMain->m_ResultDocument04[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[4] > 0)
	{
		eTree->funcSettingTreeView(4);
		frmMain->totalCount[4] = frmMain->m_ResultDocument04.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData5()
{
	DOCUMENT05_STRUCT 				tempSpaceData05;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY PRCS_DATE DESC, MEASURE_TYPE, PATH_NAME, AF_PNU, BF_PNU, ROLL_NO, GROUP_NO, GROUP_NO1 ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "AF_PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT05 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument05(asSql.c_str());

		frmMain->totalCount[5] = frmMain->totalCount[5] + frmMain->m_ResultDocument05.size();
		funcSaveLog(1, 5, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument05.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument05[j-1].PRCS_DATE;
			asType1 	= frmMain->m_ResultDocument05[j-1].MEASURE_TYPE;

		    asDate2    	= frmMain->m_ResultDocument05[j].PRCS_DATE;
			asType2 	= frmMain->m_ResultDocument05[j].MEASURE_TYPE;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument05[j-1], frmMain->m_ResultDocument05[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument05[j-1], frmMain->m_ResultDocument05[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[5] > 0)
	{
		eTree->funcSettingTreeView(5);
		frmMain->totalCount[5] = frmMain->m_ResultDocument05.size();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmSearch::funcSpaceSearchData6()
{
	DOCUMENT06_STRUCT 				tempSpaceData06;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY COMP_YEAR DESC, ZONE_CODE, KIND_CODE, KWON_NO, PAGE_NO ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "AF_PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT06 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument06(asSql.c_str());

		frmMain->totalCount[6] = frmMain->totalCount[6] + frmMain->m_ResultDocument06.size();
		funcSaveLog(1, 6, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument06.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument06[j-1].COMP_YEAR;
			asType1 	= frmMain->m_ResultDocument06[j-1].ZONE_CODE;

		    asDate2    	= frmMain->m_ResultDocument06[j].COMP_YEAR;
			asType2 	= frmMain->m_ResultDocument06[j].ZONE_CODE;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument06[j-1], frmMain->m_ResultDocument06[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument06[j-1], frmMain->m_ResultDocument06[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[6] > 0)
	{
		eTree->funcSettingTreeView(6);
		frmMain->totalCount[6] = frmMain->m_ResultDocument06.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData7()
{
	DOCUMENT07_INDEX_STRUCT 				tempSpaceData07;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//
	vector<DOCUMENT07_INDEX_STRUCT> 		vSpaceData07;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//
	vSpaceData07.clear();


	int nSize 	= (int)frmMain->m_ResultDocument07Index.size();
	GPoint rectSP, rectEP;
	rectSP = frmMain->func_WorldToDevice(frmMain->m_pgSpaceRectSP);
	rectEP = frmMain->func_WorldToDevice(frmMain->m_pgSpaceRectEP);

	TRect _rctRect;
	_rctRect.Left   = rectSP.x;
	_rctRect.Top    = rectEP.y;
	_rctRect.Right  = rectEP.x;
	_rctRect.Bottom = rectSP.y;

	vSpaceData07.clear();

	for(int i = 0; i < nSize; i++)
	{
		MBR _mMBR;
		_mMBR.xmin	= frmMain->m_ResultDocument07Index[i].X - 10;
		_mMBR.ymin	= frmMain->m_ResultDocument07Index[i].Y - 10;
		_mMBR.xmax	= frmMain->m_ResultDocument07Index[i].X + 10;
		_mMBR.ymax	= frmMain->m_ResultDocument07Index[i].Y + 10;

		if(_mMBR.xmin == 0 || _mMBR.ymin == 0 || _mMBR.xmax == 0 || _mMBR.ymax == 0)
			continue;

		TRect  mbrRect, rectBuffer;
		mbrRect = frmMain->func_WorldToDevice(_mMBR);
		if(!IntersectRect(&rectBuffer, &mbrRect, &_rctRect))
			continue;


		bool bSamed	= false;
		for(int j = 0; j < (int)vSpaceData07.size(); j++)
		{
			//공간검색 영역 안에 같은 권번호가 있다면 무시//
			if( !strcmp(vSpaceData07[j].SUR, frmMain->m_ResultDocument07Index[i].SUR)
			&& !strcmp(vSpaceData07[j].SCALE, frmMain->m_ResultDocument07Index[i].SCALE)
			&& !strcmp(vSpaceData07[j].DOHO_BON, frmMain->m_ResultDocument07Index[i].DOHO_BON) )
			{
				bSamed = true;
				break;
			}
		}
		if( !bSamed )
			vSpaceData07.push_back(frmMain->m_ResultDocument07Index[i]);
	}

	AnsiString asSql 		= "";
	AnsiString asWhere 		= "";
	AnsiString asItem 		= "";
	AnsiString asColumn	 	= "";
	AnsiString asOrder 	= "";

	asColumn 	= "distinct ROLL_NO, KWON_NO, KIND_CODE, SIDOSGG, UMD, RI, SCALE, DOHO_BON, X1, Y1, X2, Y2, BASE_X, BASE_Y, RATIOX, RATIOY, PATH_NAME";
	asOrder 	= "KWON_NO, KIND_CODE, SCALE, DOHO_BON ASC";

	nSize 	= (int)vSpaceData07.size();

	for(int i = 0; i < nSize; i++)
	{
		asItem = (char*)vSpaceData07[i].SUR;
		if(asItem.Length() == 10)
			asWhere = "KWON_NO = '" + asItem.SubString(6, 5).Trim() + "' ";

		if( !asWhere.IsEmpty() )
			asWhere = asWhere + "AND ";

		asItem = (char*)vSpaceData07[i].SCALE;
		if( !asItem.IsEmpty() )
			asWhere = asWhere + "SCALE = '" + asItem.Trim() + "' ";

		if( !asWhere.IsEmpty() )
			asWhere = asWhere + "AND ";

		asItem = (char*)vSpaceData07[i].DOHO_BON;
		if( !asItem.IsEmpty() )
		{
			asWhere = asWhere + "(DOHO_BON = '" + asItem.Trim() + "' ";
			asWhere = asWhere + "OR KIND_CODE='08' OR KIND_CODE='09')";
		}

		asSql.sprintf("SELECT %s FROM TB_DOCUMENT07 WHERE %s ORDER BY %s", asColumn, asWhere, asOrder);
		frmSql->funcReadDocument07(asSql.c_str());

		frmMain->totalCount[7] = frmMain->totalCount[7] + frmMain->m_ResultDocument07.size();
		funcSaveLog(1, 7, asSql);//save to file
	}

	if(frmMain->totalCount[7] > 0)
	{
		eTree->funcSettingTreeView(7);
		frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmSearch::funcSpaceSearchData8()
{
	DOCUMENT08_STRUCT 				tempSpaceData08;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	//200624//PAGE_NO추가//문서구분 같은것이 여러장일때 같은 페이지의 앞뒤가 붙어서 나오지 않는다.
	asOrder = " ORDER BY PNU, SINGU_NAME, KIND_CODE ASC, PAGE_NO, ONOFF_CODE ASC, ISNULL(ONOFF_CODE)";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT08 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument08(asSql.c_str());

		frmMain->totalCount[8] = frmMain->totalCount[8] + frmMain->m_ResultDocument08.size();
		funcSaveLog(1, 8, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument08.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument08[j-1].PNU;
			asType1 	= frmMain->m_ResultDocument08[j-1].SINGU_NAME;

		    asDate2    	= frmMain->m_ResultDocument08[j].PNU;
			asType2 	= frmMain->m_ResultDocument08[j].SINGU_NAME;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument08[j-1], frmMain->m_ResultDocument08[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 < asType2)
				{
					swap(frmMain->m_ResultDocument08[j-1], frmMain->m_ResultDocument08[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[8] > 0)
	{
		eTree->funcSettingTreeView(8);
		frmMain->totalCount[8] = frmMain->m_ResultDocument08.size();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmSearch::funcSpaceSearchData9()
{
	DOCUMENT09_STRUCT 				tempSpaceData09;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY PATH_NAME, PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT09 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument09(asSql.c_str());

		frmMain->totalCount[9] = frmMain->totalCount[9] + frmMain->m_ResultDocument09.size();
		funcSaveLog(1, 9, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument09.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument09[j-1].BASE_YEAR;
			asType1 	= frmMain->m_ResultDocument09[j-1].BASE_MON;

		    asDate2    	= frmMain->m_ResultDocument09[j].BASE_YEAR;
			asType2 	= frmMain->m_ResultDocument09[j].BASE_MON;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument09[j-1], frmMain->m_ResultDocument09[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument09[j-1], frmMain->m_ResultDocument09[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[9] > 0)
	{
		eTree->funcSettingTreeView(9);
		frmMain->totalCount[9] = frmMain->m_ResultDocument09.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData11()
{
	DOCUMENT11_STRUCT 				tempSpaceData11;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY KWON_NO, PATH_NAME, PAGE_NO, PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT11 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument11(asSql.c_str());

		frmMain->totalCount[11] = frmMain->totalCount[11] + frmMain->m_ResultDocument11.size();
		funcSaveLog(1, 11, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument11.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument11[j-1].KWON_NO;
			asType1 	= frmMain->m_ResultDocument11[j-1].KIND_CODE;

		    asDate2    	= frmMain->m_ResultDocument11[j].KWON_NO;
			asType2 	= frmMain->m_ResultDocument11[j].KIND_CODE;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument11[j-1], frmMain->m_ResultDocument11[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument11[j-1], frmMain->m_ResultDocument11[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[11] > 0)
	{
		eTree->funcSettingTreeView(11);
		frmMain->totalCount[11] = frmMain->m_ResultDocument11.size();
	}
		eTree->funcSettingTreeView(11);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData12()
{
	DOCUMENT12_STRUCT 				tempSpaceData12;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY REQ_DAY DESC, ROLL_NO, PAGE_NO, KWON_NO, PATH_NAME, PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT12 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument12(asSql.c_str());

		frmMain->totalCount[12] = frmMain->totalCount[12] + frmMain->m_ResultDocument12.size();
		funcSaveLog(1, 12, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument12.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument12[j-1].REQ_DAY;
			asType1 	= frmMain->m_ResultDocument12[j-1].KIND_CODE;

		    asDate2    	= frmMain->m_ResultDocument12[j].REQ_DAY;
			asType2 	= frmMain->m_ResultDocument12[j].KIND_CODE;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument12[j-1], frmMain->m_ResultDocument12[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument12[j-1], frmMain->m_ResultDocument12[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[12] > 0)
	{
		eTree->funcSettingTreeView(12);
		frmMain->totalCount[12] = frmMain->m_ResultDocument12.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData14()
{
	DOCUMENT14_STRUCT 				tempSpaceData14;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY PRCS_DATE DESC, ROLL_NO, GROUP_NO, GROUP_NO1, PATH_NAME, PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT14 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument14(asSql.c_str());

		frmMain->totalCount[14] = frmMain->totalCount[14] + frmMain->m_ResultDocument14.size();
		funcSaveLog(1, 14, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument14.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument14[j-1].PRCS_DATE;
			asType1 	= frmMain->m_ResultDocument14[j-1].MEASURE_TYPE;

		    asDate2    	= frmMain->m_ResultDocument14[j].PRCS_DATE;
			asType2 	= frmMain->m_ResultDocument14[j].MEASURE_TYPE;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument14[j-1], frmMain->m_ResultDocument14[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument14[j-1], frmMain->m_ResultDocument14[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[14] > 0)
	{
		eTree->funcSettingTreeView(14);
		frmMain->totalCount[14] = frmMain->m_ResultDocument14.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData17()
{
	DOCUMENT17_STRUCT 				tempSpaceData17;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	//2. 지번목록 중 이동결의서 신청서 있는 데이터 가져오기//
	AnsiString asSql    = "";
	AnsiString asColumn	= "";
	AnsiString asWhere  = "";
	AnsiString asOrder  = "";
	AnsiString asItem = "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrder = " ORDER BY PRCS_DATE DESC, ROLL_NO, GROUP_NO, GROUP_NO1, PATH_NAME, PNU ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asWhere  = "PNU = '" + asItem.Trim() + "'";
		asSql    = "SELECT * FROM TB_DOCUMENT17 WHERE " + asWhere + asOrder;
		frmSql->funcReadDocument17(asSql.c_str());

		frmMain->totalCount[17] = frmMain->totalCount[17] + frmMain->m_ResultDocument17.size();
		funcSaveLog(1, 17, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument17.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
		    asDate1    	= frmMain->m_ResultDocument17[j-1].KWON_NO;
			asType1 	= frmMain->m_ResultDocument17[j-1].DOC_NAME;

		    asDate2    	= frmMain->m_ResultDocument17[j].KWON_NO;
			asType2 	= frmMain->m_ResultDocument17[j].DOC_NAME;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument17[j-1], frmMain->m_ResultDocument17[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument17[j-1], frmMain->m_ResultDocument17[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[17] > 0)
	{
		eTree->funcSettingTreeView(17);
		frmMain->totalCount[17] = frmMain->m_ResultDocument17.size();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::funcSpaceSearchData18()
{
	DOCUMENT18_STRUCT 				tempSpaceData18;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//
	vector<DOCUMENT18_STRUCT> 		vSpaceData18;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//
	vSpaceData18.clear();

	GPoint rectSP, rectEP;
	rectSP = frmMain->func_WorldToDevice(frmMain->m_pgSpaceRectSP);
	rectEP = frmMain->func_WorldToDevice(frmMain->m_pgSpaceRectEP);

	TRect _rctRect;
	_rctRect.Left   = rectSP.x;
	_rctRect.Top    = rectEP.y;
	_rctRect.Right  = rectEP.x;
	_rctRect.Bottom = rectSP.y;

	vSpaceData18.clear();

	int nSize 	= (int)frmMain->m_ResultDocument18All.size();

	//for(int i = 0; i < nSize; i++)
	for(int i = nSize - 1; i >= 0; i--)
	{
		MBR _mMBR;
		_mMBR.xmin	= frmMain->m_ResultDocument18All[i].X - 10;
		_mMBR.ymin	= frmMain->m_ResultDocument18All[i].Y - 10;
		_mMBR.xmax	= frmMain->m_ResultDocument18All[i].X + 10;
		_mMBR.ymax	= frmMain->m_ResultDocument18All[i].Y + 10;

		if(_mMBR.xmin == 0 || _mMBR.ymin == 0 || _mMBR.xmax == 0 || _mMBR.ymax == 0)
			continue;

		TRect  mbrRect, rectBuffer;
		mbrRect = frmMain->func_WorldToDevice(_mMBR);
		if(!IntersectRect(&rectBuffer, &mbrRect, &_rctRect))
			continue;


		bool bSamed	= false;
		for(int j = 0; j < (int)vSpaceData18.size(); j++)
		{
			//공간검색 영역 안에 같은 권번호가 있다면 무시//
			if( !strcmp(vSpaceData18[j].KWON_NO, frmMain->m_ResultDocument18All[i].KWON_NO) )
			{
				bSamed = true;
				break;
			}
		}
		if( !bSamed )
			vSpaceData18.push_back(frmMain->m_ResultDocument18All[i]);
	}

	AnsiString asSql 		= "";
	AnsiString asWhere 		= "";
	AnsiString asItem 		= "";
	AnsiString asColumn	 	= "";
	AnsiString asOrderBy 	= "";

	//201215//asColumn 	= "distinct JIGU_YEAR, JIGU_NAME, KWON_NO, KIND_CODE, GROUP_NO, PAGE_NO, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME";
	asColumn 	= "*";
	asOrderBy 	= "JIGU_YEAR DESC, JIGU_NAME, KWON_NO, KIND_CODE, PAGE_NO, DOGNPOINT, BOJOPOINT, PATH_NAME ASC";

//	frmMain->m_ResultDocument18.clear();
	nSize 	= (int)vSpaceData18.size();

	AnsiString asJiguYear1 = "";
	AnsiString asJiguName1 = "";
	AnsiString asJiguYear2 = "";
	AnsiString asJiguName2 = "";

	//sort
	for(int i = 0; i < nSize-1; i++)
	{
		for(int j = 1; j < nSize-1; j++)
		{
			asJiguYear1 = vSpaceData18[j-1].JIGU_YEAR;
			asJiguName1 = vSpaceData18[j-1].JIGU_NAME;

			asJiguYear2 = vSpaceData18[j].JIGU_YEAR;
			asJiguName2 = vSpaceData18[j].JIGU_NAME;

			if(asJiguYear1 < asJiguYear2)
			{
				swap(vSpaceData18[j-1], vSpaceData18[j]);
//				memcpy(tempSpaceData18, 	vSpaceData18[j], 	sizeof(DOCUMENT18_STRUCT));
//				memcpy(vSpaceData18[j], 	vSpaceData18[i], 	sizeof(DOCUMENT18_STRUCT));
//				memcpy(vSpaceData18[j-1], 	tempSpaceData18, 	sizeof(DOCUMENT18_STRUCT));
			}
			else if(asJiguYear1 == asJiguYear2)
			{
				if(asJiguName1 > asJiguName2)
				{
					swap(vSpaceData18[j-1], vSpaceData18[j]);
//					memcpy(tempSpaceData18, 	vSpaceData18[i], 	sizeof(DOCUMENT18_STRUCT));
//					memcpy(vSpaceData18[i], 	vSpaceData18[i-1], 	sizeof(DOCUMENT18_STRUCT));
//					memcpy(vSpaceData18[i-1], 	tempSpaceData18, 	sizeof(DOCUMENT18_STRUCT));
				}
			}
		}
	}

	for(int i = 0; i < nSize; i++)
	{
		asItem = (char*)vSpaceData18[i].KWON_NO;
		asWhere = "KWON_NO = '" + asItem.Trim() + "'";
		asSql.sprintf("SELECT %s FROM TB_DOCUMENT18 WHERE %s ORDER BY %s", asColumn, asWhere, asOrderBy);
		frmSql->funcReadDocument18(asSql.c_str());
	}


	frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();

	if(frmMain->totalCount[18] > 0)
	{
		eTree->funcSettingTreeView(18);
		frmMain->totalCount[18] = frmMain->m_ResultDocument18.size();
	}

	funcSaveLog(1, 18, asSql);//save to file
}
//---------------------------------------------------------------------------

//231020//GAGAMLAYER//
void __fastcall TfrmSearch::funcSpaceSearchData20()
{
	DOCUMENT20_STRUCT 				tempSpaceData20;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//

	AnsiString 	asSql    	= "";
	AnsiString  asColumn	= "KWON_NO, GAGAM_NO, UMDRI_CD, DOHO, DOC_NAME, KIND_CODE, PAGE_NO, SURV_DATE, SURV_ETC, PRCS_DATE, PATH_NAME";//241211//
	AnsiString 	asWhere  	= "";
	AnsiString 	asOrderBy  	= "";
	AnsiString 	asSqlSubQry = "";
	AnsiString 	asItem 		= "";
	int nCount	= frmMain->m_vSPACELANDINFO.size();

	asOrderBy = " ORDER BY YEAR, DESC, GAGAM_NO ASC";

	for(int i = 0; i < nCount; i++)
	{
		asItem   = frmMain->m_vSPACELANDINFO[i].LAND_CD;
		asSqlSubQry = "GAGAM_NO IN (SELECT GAGAM_NO FROM TB_DOCUMENT20_LANDLIST WHERE LAND_CD='" + asItem.Trim() + "') ";

		//--
		asSql = "SELECT " + asColumn + " FROM TB_DOCUMENT20 WHERE " + asSqlSubQry + asOrderBy;
		//---
		frmSql->funcReadDocument20(asSql.c_str());

		frmMain->totalCount[20] = frmMain->totalCount[20] + frmMain->m_ResultDocument20.size();
		funcSaveLog(1, 20, asSql);//save to file
	}

	//sort
	int nSize 	= (int)frmMain->m_ResultDocument20.size();
	AnsiString asDate1 		= "";
	AnsiString asType1 	= "";
	AnsiString asDate2 		= "";
	AnsiString asType2 	= "";

	for(int i = 0; i < nSize; i++)
	{
		for(int j = 1; j < nSize; j++)
		{
			asDate1    	= frmMain->m_ResultDocument20[j-1].KWON_NO;
			asType1 	= frmMain->m_ResultDocument20[j-1].GAGAM_NO;

			asDate2    	= frmMain->m_ResultDocument20[j].KWON_NO;
			asType2 	= frmMain->m_ResultDocument20[j].GAGAM_NO;

			if(asDate1 < asDate2)
			{
				swap(frmMain->m_ResultDocument20[j-1], frmMain->m_ResultDocument20[j]);
			}
			else if(asDate1 == asDate2)
			{
				if(asType1 > asType2)
				{
					swap(frmMain->m_ResultDocument20[j-1], frmMain->m_ResultDocument20[j]);
				}
			}
		}
	}

	if(frmMain->totalCount[20] > 0)
	{
		eTree->funcSettingTreeView(20);
		frmMain->totalCount[20] = frmMain->m_ResultDocument20.size();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmSearch::funcSpaceSearchDataMemo()
{
	MEMOINFO_STRUCT 				tempSpaceDataMemo;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//
	vector<MEMOINFO_STRUCT> 		vSpaceDataMemo;//공간검색 영역 안에 있는 기준점들의 권번호만 저장//
	vSpaceDataMemo.clear();

	GPoint rectSP, rectEP;
	rectSP = frmMain->func_WorldToDevice(frmMain->m_pgSpaceRectSP);
	rectEP = frmMain->func_WorldToDevice(frmMain->m_pgSpaceRectEP);

	TRect _rctRect;
	_rctRect.Left   = rectSP.x;
	_rctRect.Top    = rectEP.y;
	_rctRect.Right  = rectEP.x;
	_rctRect.Bottom = rectSP.y;

	vSpaceDataMemo.clear();

	//MEMOPOINT//메모/영역 분리//
	int nSize 	= (int)frmSql->m_vALLMEMOINFO.size();
	for(int i = 0; i < nSize; i++)
	{
		if(frmSql->m_vALLMEMOINFO[i].DATA_CNT >= 3)//메모/영역 분리//
			continue;

		MBR _mMBR;
		_mMBR.xmin	= frmSql->m_vALLMEMOINFO[i].X - 10;
		_mMBR.ymin	= frmSql->m_vALLMEMOINFO[i].Y - 10;
		_mMBR.xmax	= frmSql->m_vALLMEMOINFO[i].X + 10;
		_mMBR.ymax	= frmSql->m_vALLMEMOINFO[i].Y + 10;

		if(_mMBR.xmin == 0 || _mMBR.ymin == 0 || _mMBR.xmax == 0 || _mMBR.ymax == 0)
			continue;

		TRect  mbrRect, rectBuffer;
		mbrRect = frmMain->func_WorldToDevice(_mMBR);
		if(!IntersectRect(&rectBuffer, &mbrRect, &_rctRect))
			continue;

		vSpaceDataMemo.push_back(frmSql->m_vALLMEMOINFO[i]);
	}

	//MEMOPOLY//메모/영역 분리//
	memset(&tempSpaceDataMemo, 0x00, sizeof(MEMOINFO_STRUCT));
	nSize 	= (int)frmSql->m_vMEMOPOLY.size();
	for(int i = 0; i < nSize; i++)
	{
		MBR _mMBR;
		_mMBR.xmin	= frmSql->m_vMEMOPOLY[i].m_MBR.xmin;
		_mMBR.ymin	= frmSql->m_vMEMOPOLY[i].m_MBR.ymin;
		_mMBR.xmax	= frmSql->m_vMEMOPOLY[i].m_MBR.xmax;
		_mMBR.ymax	= frmSql->m_vMEMOPOLY[i].m_MBR.ymax;

		if(_mMBR.xmin == 0 || _mMBR.ymin == 0 || _mMBR.xmax == 0 || _mMBR.ymax == 0)
			continue;

		TRect  mbrRect, rectBuffer;
		mbrRect = frmMain->func_WorldToDevice(_mMBR);
		if(!IntersectRect(&rectBuffer, &mbrRect, &_rctRect))
			continue;

		memcpy(tempSpaceDataMemo.POI_KEY, frmSql->m_vMEMOPOLY[i].label.c_str(), sizeof(tempSpaceDataMemo.POI_KEY));

		vSpaceDataMemo.push_back(tempSpaceDataMemo);

		memset(&tempSpaceDataMemo, 0x00, sizeof(MEMOINFO_STRUCT));
	}

	AnsiString asSql 		= "";
	AnsiString asWhere 		= "";
	AnsiString asItem 		= "";
	AnsiString asColumn	 	= "";
	AnsiString asOrderBy 	= "";

	nSize 	= (int)vSpaceDataMemo.size();

	AnsiString asPoiKey1 = "";
	AnsiString asPoiKey2 = "";

	//sort
	for(int i = 0; i < nSize-1; i++)
	{
		for(int j = 1; j < nSize-1; j++)
		{
			asPoiKey1 = (char*)vSpaceDataMemo[j-1].POI_KEY;
			asPoiKey2 = (char*)vSpaceDataMemo[j].POI_KEY;
			if(asPoiKey1 > asPoiKey2)
			{
				swap(vSpaceDataMemo[j-1], vSpaceDataMemo[j]);
			}
		}
	}

	for(int i = 0; i < nSize; i++)
	{
		asItem = vSpaceDataMemo[i].POI_KEY;
		asWhere = "POI_KEY = '" + asItem.Trim() + "'";
		asSql.sprintf("SELECT * FROM %s WHERE %s", frmMain->TABLE_MEMOINFO, asWhere);
		frmSql->funcReadMemo(asSql.c_str());
	}


	frmMain->totalCount[0] = frmMain->m_ResultMemo.size();

	if(frmMain->totalCount[0] > 0)
		eTree->funcSettingTreeView(0);

	funcSaveLog(1, 0, asSql);//save to file
}
//---------------------------------------------------------------------------
