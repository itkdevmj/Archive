//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#pragma warn -8004


cTreeSystem *eTree;
//---------------------------------------------------------------------------
cTreeSystem::cTreeSystem()
{
}
//---------------------------------------------------------------------------
cTreeSystem::~cTreeSystem()
{
}
//---------------------------------------------------------------------------

void cTreeSystem::funcSettingTreeView(int _nDocNo)
{
	int             nNodeCount = 0;
	TTreeNode       *NodeA;

	if( !frmMain->treSystem->Visible )
		frmMain->treSystem->Visible	= true;//200304//

	//200302
	frmMain->pnlJibunMent->Caption = "";
	frmMain->lblJibunMent2->Visible = false;
	frmMain->pnlJibunMent->Visible = false;

	if (_nDocNo < DF_DOC_CNT)
	{
		if(_nDocNo != 0 && !frmMain->INIINFO.B_QRYCHECK[_nDocNo] && !frmMain->INIINFO.B_DOCKIND[_nDocNo])
			return;
		if(_nDocNo == 0 && !frmMain->INIINFO.B_MEMO)
			return;
		if(frmMain->totalCount[_nDocNo] == 0)
		{
			frmMain->mSearchNode.tNodeA[_nDocNo]	= NULL;//200303//초기화//이전검색기록이 남아서 문제발생//
			return;
		}

		if(_nDocNo == 0)
			NodeA = frmMain->treSystem->Items->Add(frmMain->treSystem->Selected, "메모");
		else
			NodeA = frmMain->treSystem->Items->Add(frmMain->treSystem->Selected, frmMain->INIINFO.DOCKINDNAME[_nDocNo]);
		NodeA->ImageIndex = 1;
		frmMain->mSearchNode.tNodeA[_nDocNo] 		= NodeA;

		if(_nDocNo == 18)//191223//사장님Req//
		{
			if(frmMain->totalCount[_nDocNo] > 0)
				frmMain->INIINFO.B_QRYCHECK[18] = true;
		}
		else if(_nDocNo == 0)//#MEMOSEARCH#
		{
			frmMain->INIINFO.B_MEMO = true;
			frmMain->INIINFO.B_POLY = true;
		}

		//210223//frmSearch->funcSaveLog(9, 0, "TREE_START");

		nNodeCount = funcNodeSettingDoc(_nDocNo, nNodeCount);
		if(nNodeCount == 0)
			return;

		//=====================
		//200226//TEST//if (nNodeCount > 1)
		{
			frmMain->treSystem->Selected = frmMain->treSystem->Items->Item[0];
			frmMain->treSystem->Selected->Expanded = true;
		}
		//==========================================
		//201221//검색결과트리 설정(1:펼치기(Default), 2:닫기//
		//NodeA->Expand(bool); ==> 하위 모든 노드에도 동일한 속성을 설정한다//
		//NodeA->Expanded	= bool	==> 현재 노드에만 해당 속성을 설정한다//
		//treSystem->FullExpand(); ==> 모든 노드를 다 펼친다//
		//treSystem->FullCollapse(); ==> 모든 노드를 다 닫는다//
		NodeA->Expand(frmMain->INIUSERSETINFO.B_EXPAND);//201222//NodeA->Expanded = true;
		//==========================================

		//210223//frmSearch->funcSaveLog(9, 0, "TREE_END");
	}
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc(int _nDocNo, int _nNodeCount)
{
	int nReturnValue = 0;

	switch(_nDocNo)
	{
		case  1:			nReturnValue = funcNodeSettingDoc01(_nDocNo, _nNodeCount);			break;
		case  2:			nReturnValue = funcNodeSettingDoc02(_nDocNo, _nNodeCount);			break;
		case  3:			nReturnValue = funcNodeSettingDoc03(_nDocNo, _nNodeCount);			break;
		case  4:			nReturnValue = funcNodeSettingDoc04(_nDocNo, _nNodeCount);			break;
//			if ( frmMain->_SIDOCODOE != "44825") )//not 44825
//				nReturnValue = funcNodeSettingDoc04(_nDocNo, _nNodeCount);
//			else//44825//[TODO]
//				nReturnValue = funcNodeSettingDoc04_2(_nDocNo, _nNodeCnt);
//			break;
		case  5:			nReturnValue = funcNodeSettingDoc05(_nDocNo, _nNodeCount);			break;
		case  6:			nReturnValue = funcNodeSettingDoc06(_nDocNo, _nNodeCount);			break;
		case  7:			nReturnValue = funcNodeSettingDoc07(_nDocNo, _nNodeCount);			break;
//			if(frmIniControl->m_bMAPPOINT)//[TODO]
//				nReturnValue = funcNodeSettingDoc07_MAPPOINT(_nDocNo, _nNodeCnt);
//			else
//				nReturnValue = funcNodeSettingDoc07(_nDocNo, _nNodeCnt);
//			break;
		case  8:			nReturnValue = funcNodeSettingDoc08(_nDocNo, _nNodeCount);			break;
		case  9:			nReturnValue = funcNodeSettingDoc09(_nDocNo, _nNodeCount);			break;
//		case 10:			break;
		case 11:			nReturnValue = funcNodeSettingDoc11(_nDocNo, _nNodeCount);			break;
		case 12:			nReturnValue = funcNodeSettingDoc12(_nDocNo, _nNodeCount);			break;
		case 13:			nReturnValue = funcNodeSettingDoc13(_nDocNo, _nNodeCount);			break;
		case 14:			nReturnValue = funcNodeSettingDoc14(_nDocNo, _nNodeCount);			break;
		case 15:			nReturnValue = funcNodeSettingDoc15(_nDocNo, _nNodeCount);			break;
//		case 16:			nReturnValue = funcNodeSettingDoc16(_nDocNo, _nNodeCnt);			break;
		case 17:			nReturnValue = funcNodeSettingDoc17(_nDocNo, _nNodeCount);			break;
		case 18:			nReturnValue = funcNodeSettingDoc18(_nDocNo, _nNodeCount);			break;
		case 20:			nReturnValue = funcNodeSettingDoc20(_nDocNo, _nNodeCount);			break;//231020//GAGAMLAYER in LandArchive
		case  0:			nReturnValue = funcNodeSettingMemo(_nDocNo, _nNodeCount);			break;
		default:
			break;
	}

	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc01(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
//[TODO]이동결의서 통합검색 시 BF_PNU를 검색하지 않아서 의미없는 기능. 추후 적용하게 되면 공간검색에도 적용해야함	AnsiString 	asNodeD		= "";//231019//이동결의서.이동전지번 표시//TEST//
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asPrcsDate	= "";//PRCS_DATE
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asMsurType	= "";//MEASURE_TYPE
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;
//[TODO]이동결의서 통합검색 시 BF_PNU를 검색하지 않아서 의미없는 기능. 추후 적용하게 되면 공간검색에도 적용해야함	TTreeNode 	*NodeD = NULL;//231019//이동결의서.이동전지번 표시//TEST//

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument01.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

//231209//#BugFixed//
			asPrcsDate = (char*)frmMain->m_ResultDocument01[nIndex].PRCS_DATE;
			asKindName = eFunc->funcGetKindCodeToKindName(1, (char*)frmMain->m_ResultDocument01[nIndex].KIND_CODE);
			asMsurType = eFunc->funcGetKindCodeToKindName(101, (char*)frmMain->m_ResultDocument01[nIndex].MEASURE_TYPE);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument01.erase(frmMain->m_ResultDocument01.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument01[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument01[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument01[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument01[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument01[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument01.size(); i++)
		{
//231209//#BugFixed//
			asPrcsDate = (char*)frmMain->m_ResultDocument01[i].PRCS_DATE;
			asMsurType = eFunc->funcGetKindCodeToKindName(101, (char*)frmMain->m_ResultDocument01[i].MEASURE_TYPE);
			//
			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument01[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument01.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

//231209//#BugFixed//
			asPrcsDate = (char*)frmMain->m_ResultDocument01[nIndex].PRCS_DATE;
			asKindName = eFunc->funcGetKindCodeToKindName(1, (char*)frmMain->m_ResultDocument01[nIndex].KIND_CODE);
			asMsurType = eFunc->funcGetKindCodeToKindName(101, (char*)frmMain->m_ResultDocument01[nIndex].MEASURE_TYPE);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument01.erase(frmMain->m_ResultDocument01.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument01[nIndex]; //**
					NodeC->ImageIndex = 5;
//=============================================================================
//[TODO]이동결의서 통합검색 시 BF_PNU를 검색하지 않아서 의미없는 기능. 추후 적용하게 되면 공간검색에도 적용해야함//231019//이동결의서.이동전지번 표시//TEST//
//					asNodeD = eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument01[nIndex].BF_PNU, 1);
//					if( !asNodeD.IsEmpty() )
//					{
//						NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
//						NodeD->Data = NULL;
//						NodeD->ImageIndex = 10;
//					}
//					asNodeD = eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument01[nIndex].AF_PNU, 2);
//					if( !asNodeD.IsEmpty() )
//					{
//						NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
//						NodeD->Data = NULL;
//						NodeD->ImageIndex = 10;
//					}
//=============================================================================
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument01[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument01[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument01[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument01[nIndex]; //**
				NodeC->ImageIndex = 5;
//=============================================================================
//[TODO]이동결의서 통합검색 시 BF_PNU를 검색하지 않아서 의미없는 기능. 추후 적용하게 되면 공간검색에도 적용해야함//231019//이동결의서.이동전지번 표시//TEST//
//				asNodeD = eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument01[nIndex].BF_PNU, 1);
//				if( !asNodeD.IsEmpty() )
//				{
//					NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
//					NodeD->Data = NULL;
//					NodeD->ImageIndex = 10;
//				}
//				asNodeD = eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument01[nIndex].AF_PNU, 2);
//				if( !asNodeD.IsEmpty() )
//				{
//					NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
//					NodeD->Data = NULL;
//					NodeD->ImageIndex = 10;
//				}
//=============================================================================
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

//201012//#ALLSEARCHLABEL
int cTreeSystem::funcNodeSettingDoc02(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asLabelDay	= "";//frmMain->INIUSERSETINFO.DOC02DAY
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asSurvItem	= "";//SURV_ITEM
	AnsiString 	asDoho		= "";//201012//#ALLSEARCHLABEL
	int 		nDocCut 	= 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument02.size();

		for (int i = 0; i < nSize; i++)
		{
			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
				asLabelDay = (char*)frmMain->m_ResultDocument02[i].SURV_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
				asLabelDay = (char*)frmMain->m_ResultDocument02[i].INSPCT_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
				asLabelDay = (char*)frmMain->m_ResultDocument02[i].SUBMIT_DATE;

//231209//#BugFixed//
			asSurvItem	= eFunc->funcGetKindCodeToKindName(102, (char*)frmMain->m_ResultDocument02[i].SURV_ITEM);
			asNodeB.sprintf("%s[%s]", asLabelDay, asSurvItem);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument02[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument02.size();

		for (int i = 0; i < nSize; i++)
		{
			//200810//결의일자->측량일자 변경요청
			//(울주군청의 경우 지번이 없는 데이터가 많고, 결의일자 없는 데이터가 많아서 상세검색도 어려움이 발생하여 변경//
			//통합검색일때는 '환경설정에서 설정한 일자'로 정렬//
			//상세검색일때는 '측량일자'로 정렬//
			if(frmMain->m_nActiveDoc == 0)//byJibun
			{
				if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
					asLabelDay = (char*)frmMain->m_ResultDocument02[i].SURV_DAY;
				else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
					asLabelDay = (char*)frmMain->m_ResultDocument02[i].INSPCT_DAY;
				else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
					asLabelDay = (char*)frmMain->m_ResultDocument02[i].SUBMIT_DATE;
			}
			else
			{
				asLabelDay = (char*)frmMain->m_ResultDocument02[i].SURV_DAY;
			}

//231209//#BugFixed//
			asDoho		= (char*)frmMain->m_ResultDocument02[i].DOHO;
			asKindName	= eFunc->funcGetKindCodeToKindName(2, (char*)frmMain->m_ResultDocument02[i].KIND_CODE);
			asSurvItem  = eFunc->funcGetKindCodeToKindName(102, (char*)frmMain->m_ResultDocument02[i].SURV_ITEM);
			if(asKindName == "면적")
			{
				asNodeB.sprintf("%s[%s][면적]", asLabelDay, asSurvItem);
			}
			else
			{
				if(asDoho.IsEmpty())
					asNodeB.sprintf("%s[%s][도호:-]", asLabelDay, asSurvItem);
				else
					//220315//DOC02.DOHO에 2개의 도호정보가 있는 경우에 오류발생//44710.31021.2.651.3, 4, 5//
					asNodeB.sprintf("%s[%s][도호:%s]", asLabelDay, asSurvItem, asDoho);
			}

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument02[i]; //**
			NodeB->ImageIndex = 5;

//=============================================================================
//[TODO]Tree가 길어지기 때문에 기능적용안함. 나중에 하게되면 공간검색에도 해당 내용 기재해야함//231019//측량결과도.일자 표시//TEST//
//			asNodeC.sprintf("%s[측량]", (char*)frmMain->m_ResultDocument02[i].SURV_DAY);
//			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//			NodeC->Data = NULL;
//			NodeC->ImageIndex = 10;
//			asNodeC.sprintf("%s[검사]", (char*)frmMain->m_ResultDocument02[i].INSPCT_DAY);
//			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//			NodeC->Data = NULL;
//			NodeC->ImageIndex = 10;
//=============================================================================
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

//201021//폴더링없음-모든문서표시//
int cTreeSystem::funcNodeSettingDoc03(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asSurvDay	= "";//SURV_DAY
	AnsiString 	asInspctDay	= "";//INSPCT_DAY
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;
	AnsiString 	asKwonNo	= "";

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument03.size();

		for (int i = 0; i < nSize; i++)
		{
//231209//#BugFixed//
			asSurvDay	= (char*)frmMain->m_ResultDocument03[i].SURV_DAY;
			asInspctDay	= (char*)frmMain->m_ResultDocument03[i].INSPCT_DAY;
//231019//MODIFY
			asNodeB.sprintf("%s(%s[검사])", asSurvDay, asInspctDay);
//			if(strcmp(frmMain->m_ResultDocument03[i].SURV_DAY, "") == 0)
//				asNodeB.sprintf("측량일자없음");
//			else
//				asNodeB.sprintf("%s", frmMain->m_ResultDocument03[i].SURV_DAY);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument03[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument03.size();

		for (int i = 0; i < nSize; i++)
		{
//231209//#BugFixed//
			asSurvDay	= (char*)frmMain->m_ResultDocument03[i].SURV_DAY;
			asInspctDay	= (char*)frmMain->m_ResultDocument03[i].INSPCT_DAY;
//231019//MODIFY
			asNodeB.sprintf("%s(%s[검사])", asSurvDay, asInspctDay);
//			if(strcmp(frmMain->m_ResultDocument03[i].SURV_DAY, "") == 0)
//				asNodeB.sprintf("측량일자없음");
//			else
//				asNodeB.sprintf("%s", frmMain->m_ResultDocument03[i].SURV_DAY);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument03[i]; //**
			NodeB->ImageIndex = 5;
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

//230502//그룹핑기준 : LAW_NO//
//201020//#ALLSEARCHLABEL
int cTreeSystem::funcNodeSettingDoc04(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asLawNo 	= "";//LAW_NO
	AnsiString 	asReqYear 	= "";//REQ_YEAR
	AnsiString 	asReqDay 	= "";//REQ_DAY
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asRecNo 	= "";//REC_NO
	AnsiString 	asAprovSt 	= "";
	int 		nDocCut 	= 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument04.size();

		for (int i = 0; i < nSize; i++)
		{
			asLawNo  	= (char*)frmMain->m_ResultDocument04[i].LAW_NO;
			asReqYear   = (char*)frmMain->m_ResultDocument04[i].REQ_YEAR;//231222//Add//
			asReqDay 	= (char*)frmMain->m_ResultDocument04[i].REQ_DAY;
			asRecNo 	= (char*)frmMain->m_ResultDocument04[i].REC_NO;
			asKindName  = eFunc->funcGetKindCodeToKindName(4, (char*)frmMain->m_ResultDocument04[i].KIND_CODE);
			asAprovSt   = (char*)frmMain->m_ResultDocument04[i].APROV_STATUS;

			//231222//Add//LAW_NO 없는 지역 존재하여 추가//
			if(asLawNo == "")
			{
				if(asReqDay.Length() >= 4)
					asLawNo = asReqDay.SubString(1, 4) + "년 시행";
				else
					asLawNo = "OOOO년 시행";
			}
			if( asReqDay.IsEmpty() )
				asReqDay = "-";
			if( asRecNo.IsEmpty() )
				asRecNo = "-";

//240314//[REQ]고명재과장//동일한 '확인서'인데 문서구분으로 종목을 표시하려고 한 것 같다.//
//APPROV_STATUS에 '발급/기각/취하' 등의 종목이 있으므로 표시 요청//
//OLD//			asNodeB.sprintf("%s%s[%s][접수번호:%s]", asLawNo, asReqDay, asKindName, asRecNo);
			asNodeB.sprintf("%s%s[%s][접수:%s][%s]", asLawNo, asReqDay, asKindName, asRecNo, asAprovSt);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument04[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	//201021//특조법 상세 문서구분 검색표시 다르지 않아서 주석처리//
//	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
//	{
//		for (int i = 0; i < (int)frmMain->m_ResultDocument04.size(); i++)
//		{
//			asReqDay 	= (char*)frmMain->m_ResultDocument04[i].REQ_DAY;
//			asRecNo 	= (char*)frmMain->m_ResultDocument04[i].REC_NO;
//			asKindCode  = eFunc->funcGetKindCodeToKindName(4, (char*)frmMain->m_ResultDocument04[i].KIND_CODE);
//			if(asReqDay == "")		asReqDay = "일자";
//			if(asRecNo == "") 		asRecNo  = "접수번호";
//			if(asKindCode == "") 	asRecNo  = "문서구분";
//			asNodeB.sprintf("%s[%s][접수번호:%s]", asReqDay, asKindCode, asRecNo);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument04[i]; //**
//			NodeB->ImageIndex = 5;
//		}
//	}
	else
	{
		int		nEraseCnt	= 0;//230410//
		int		nIndex		= 0;//230410//
		int 	nSize 		= (int)frmMain->m_ResultDocument04.size();

		for (int i = 0; i < nSize; i++)
		{
/* TODO :
천안 특조법 구축, 통합검색, 그룹쿼리, 소유자명 다수 시 처리방법 모호
=> 검색결과 폴더링 구조는 추후결정 */
			nIndex = i - nEraseCnt;

			//
			asLawNo  	= (char*)frmMain->m_ResultDocument04[nIndex].LAW_NO;
			asReqYear   = (char*)frmMain->m_ResultDocument04[i].REQ_YEAR;//231222//Add//
			asReqDay 	= (char*)frmMain->m_ResultDocument04[nIndex].REQ_DAY;
			asRecNo 	= (char*)frmMain->m_ResultDocument04[nIndex].REC_NO;
			asKindName  = eFunc->funcGetKindCodeToKindName(4, (char*)frmMain->m_ResultDocument04[nIndex].KIND_CODE);
			asAprovSt   = (char*)frmMain->m_ResultDocument04[nIndex].APROV_STATUS;

			//231222//Add//LAW_NO 없는 지역 존재하여 추가//
			if(asLawNo == "")
			{
				if(asReqDay.Length() >= 4)
					asLawNo = asReqDay.SubString(1, 4) + "년 시행";
				else
					asLawNo = "OOOO년 시행";
			}
			if( asReqDay.IsEmpty() )
				asReqDay = "-";
			if( asRecNo.IsEmpty() )
				asRecNo = "-";

			if(nDocCut > 0)
			{
				asNodeB1	= asLawNo;
				if(asNodeB  == asNodeB1)//LAW_NO 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
//240314//[REQ]고명재과장//동일한 '확인서'인데 문서구분으로 종목을 표시하려고 한 것 같다.//
//APPROV_STATUS에 '발급/기각/취하' 등의 종목이 있으므로 표시 요청//
//OLD//					asNodeC1.sprintf("%s[%s][접수번호:%s][%s]", asReqDay, asKindName, asRecNo, asAprovSt);
					asNodeC1.sprintf("%s[%s][접수:%s][%s]", asReqDay, asKindName, asRecNo, asAprovSt);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument04.erase(frmMain->m_ResultDocument04.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument04[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB	= asLawNo;
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument04[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument04[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument04[i].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
//240314//[REQ]고명재과장//동일한 '확인서'인데 문서구분으로 종목을 표시하려고 한 것 같다.//
//APPROV_STATUS에 '발급/기각/취하' 등의 종목이 있으므로 표시 요청//
//OLD//				asNodeC.sprintf("%s[%s][접수번호:%s]", asReqDay, asKindName, asRecNo);
				asNodeC.sprintf("%s[%s][접수:%s][%s]", asReqDay, asKindName, asRecNo, asAprovSt);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument04[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc05(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asPrcsDate	= "";//PRCS_DATE
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asMsurType	= "";//MEASURE_TYPE
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument05.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asPrcsDate = (char*)frmMain->m_ResultDocument05[nIndex].PRCS_DATE;
			asKindName = eFunc->funcGetKindCodeToKindName(1, (char*)frmMain->m_ResultDocument05[nIndex].KIND_CODE);
			asMsurType = eFunc->funcGetKindCodeToKindName(109, (char*)frmMain->m_ResultDocument05[nIndex].MEASURE_TYPE);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument05.erase(frmMain->m_ResultDocument05.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument05[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument05[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument05[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument05[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC 	= frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument05[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument05.size(); i++)
		{
			asPrcsDate = (char*)frmMain->m_ResultDocument05[i].PRCS_DATE;
			asMsurType = eFunc->funcGetKindCodeToKindName(109, (char*)frmMain->m_ResultDocument05[i].MEASURE_TYPE);

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument05[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument05.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asPrcsDate = (char*)frmMain->m_ResultDocument05[nIndex].PRCS_DATE;
			asKindName = eFunc->funcGetKindCodeToKindName(1, (char*)frmMain->m_ResultDocument05[nIndex].KIND_CODE);
			asMsurType = eFunc->funcGetKindCodeToKindName(109, (char*)frmMain->m_ResultDocument05[nIndex].MEASURE_TYPE);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument05.erase(frmMain->m_ResultDocument05.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument05[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument05[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument05[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument05[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument05[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc06(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asPnu		= "";//201016//
	AnsiString 	asCompYear	= "";//COMP_YEAR
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asZoneName	= "";//ZONE_CODE
	int 		nDocCut 	= 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//지번정보목록에서 검색해야함//[TODO]
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument06.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asCompYear	= (char*)frmMain->m_ResultDocument06[nIndex].COMP_YEAR;
			asKindName  = eFunc->funcGetKindCodeToKindName(6, frmMain->m_ResultDocument06[nIndex].KIND_CODE);
			asZoneName  = eFunc->funcGetKindCodeToKindName(906, frmMain->m_ResultDocument06[nIndex].ZONE_CODE);
			asPnu		= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument06[nIndex].AF_PNU, 2);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asCompYear, asZoneName);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//JIGU_YEAR[JIGU_NAME] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;

					if( !asPnu.IsEmpty() )
						asNodeC1	= asNodeC1 + "(" + asPnu + ")";

					//201015//#ALLSEARCHLABEL
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument06.erase(frmMain->m_ResultDocument06.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asCompYear, asZoneName);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument06[nIndex].tNode = NodeB;

			if( strcmp((char*)frmMain->m_ResultDocument06[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;

				//201016//
				if( !asPnu.IsEmpty() )
					asNodeC	= asNodeC + "(" + asPnu + ")";

				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	//201021//환지계획서 상세 문서구분 검색표시 다르지 않아서 주석처리//
//	else if(frmSearch->m_bKindDoc)//상세검색//문서구분 선택//
//	{
////		for (int i = 0; i < (int)frmMain->m_ResultDocument06.size(); i++)
////		{
////			asNodeB.sprintf("%s[%s]", (char*)frmMain->m_ResultDocument06[i].COMP_YEAR,
////									eFunc->funcGetKindCodeToKindName(906, frmMain->m_ResultDocument06[i].ZONE_CODE));
////			nDocCut++;
////			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
////			NodeB->Data = (void*)&frmMain->m_ResultDocument06[i]; //**
////			NodeB->ImageIndex = 5;
////		}
//
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument06.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				asNodeB1.sprintf("%s[%s]", (char*)frmMain->m_ResultDocument06[nIndex].COMP_YEAR,
//										eFunc->funcGetKindCodeToKindName(906, frmMain->m_ResultDocument06[nIndex].ZONE_CODE));
//				if(asNodeB  == asNodeB1)//JIGU_YEAR[JIGU_NAME] 같고//
//				{
//					//201021//
//					asNodeC1	= "";
//					asPnu	= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument06[nIndex].AF_PNU, 2);
//					if( !asPnu.IsEmpty() )
//						asNodeC1	= asNodeC1 + "(" + asPnu + ")";
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;//
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			asNodeB.sprintf("%s[%s]", (char*)frmMain->m_ResultDocument06[nIndex].COMP_YEAR,
//									eFunc->funcGetKindCodeToKindName(906, frmMain->m_ResultDocument06[nIndex].ZONE_CODE));
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument06[nIndex].tNode = NodeB;
//
//			//201021//
//			_nNodeCount++;
//			asNodeC1	= "";
//			asPnu	= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument06[nIndex].AF_PNU, 2);
//			if( !asPnu.IsEmpty() )
//				asNodeC	= "(" + asPnu + ")";
//
//			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//			NodeC->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
//			NodeC->ImageIndex = 5;
//		}
//	}
	else//if(frmMain->m_nActiveDoc)//통합검색
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument06.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asCompYear	= (char*)frmMain->m_ResultDocument06[nIndex].COMP_YEAR;
			asKindName  = eFunc->funcGetKindCodeToKindName(6, frmMain->m_ResultDocument06[nIndex].KIND_CODE);
			asZoneName  = eFunc->funcGetKindCodeToKindName(906, frmMain->m_ResultDocument06[nIndex].ZONE_CODE);
			asPnu		= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument06[nIndex].AF_PNU, 2);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asCompYear, asZoneName);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//JIGU_YEAR[JIGU_NAME] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;

					if( !asPnu.IsEmpty() )
						asNodeC1	= asNodeC1 + "(" + asPnu + ")";
					//201015//#ALLSEARCHLABEL
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument06.erase(frmMain->m_ResultDocument06.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}

					_nNodeCount++;
					asNodeC = asNodeC1;//
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asCompYear, asZoneName);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument06[nIndex].tNode = NodeB;

			if( strcmp((char*)frmMain->m_ResultDocument06[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;

				if( !asPnu.IsEmpty() )
					asNodeC	= asNodeC + "(" + asPnu + ")";

				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument06[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}
	else

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc07(int _nDocNo, int _nNodeCount)
{
	AnsiString  asNodeB		= "";
	AnsiString  asNodeB1	= "";
	AnsiString  asNodeC		= "";
	AnsiString  asNodeC1	= "";
	AnsiString  asNodeD		= "";
	AnsiString  asNodeD1	= "";
	AnsiString 	asStr 		= "";
	AnsiString 	asKindName	= "";
	AnsiString 	asScale 	= "";
	AnsiString 	asDoho 		= "";
	AnsiString 	asPage 		= "";
	AnsiString 	asSURName	= "";//시군구+읍면동+리 코드 8자리//
	AnsiString 	asNodeLabel	= "";
	int 		nDocCut 		= 0;
	int 		nReturnValue 	= 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;
	//210309//TTreeNode 	*NodeD = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument07.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asKindName  = eFunc->funcGetKindCodeToKindName(7, (char*)frmMain->m_ResultDocument07[nIndex].KIND_CODE);
			asScale 	= (char*)frmMain->m_ResultDocument07[nIndex].SCALE;
			if(asScale != "")
				asScale.sprintf("%d00", asScale.ToInt());
			else
				asScale = "-";

			asDoho 		= (char*)frmMain->m_ResultDocument07[nIndex].DOHO_BON;
			if(asDoho != "")
				asDoho.sprintf("%d", asDoho.ToInt());
			else
				asDoho = "-";

			if(nDocCut > 0)
			{
				asSURName = (char*)frmMain->m_ResultDocument07[nIndex].UMD;
				asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].RI;
				asSURName = frmMain->INIINFO.SIDOCODE + asSURName;
				if(asSURName.Length() < 8)
				{
					frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
					nEraseCnt++;
					continue;
				}

				if(asSURName.SubString(9, 2) == "00")
					asSURName = frmSql->func_ConvertUmdCDtoNM(asSURName.SubString(1,8));//210204//#LOADING_TEST//frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1, 8));
				else
					asSURName = frmSql->func_ConvertRiCDtoNM(asSURName.SubString(1,10));//210204//#LOADING_TEST//frmMain->func_ConvertRiCDtoNM(asStr.SubString(1, 10));

				asNodeB1.sprintf("%s[%s][%s호]", asSURName, asScale, asDoho);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				//일람도, 색인표를 함께 묶어준다//
				if(asNodeB  == asNodeB1 || asStr == "일람도" || asStr == "색인표")
				{
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//문서구분 같고//
					{
						frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

//=====================================================================
//[v1.0.0.5]//230619//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
//지번없이 '토지소재'만 입력 시 검색결과에 '토지소재'폴더명이 나타나지 않는 문제 수정//
			asSURName = (char*)frmMain->m_ResultDocument07[nIndex].SIDOSGG;
			asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].UMD;
			asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//OLD//
//			asStr = (char*)frmMain->m_ResultDocument07[nIndex].UMD;
//			asStr = asStr + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//			asStr = frmMain->INIINFO.SIDOCODE + asStr;
//=====================================================================
			if(asSURName.Length() < 8)
			{
				frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
				nEraseCnt++;
				continue;
			}

			nDocCut++;
			if(asSURName.SubString(9, 2) == "00")
				asSURName = frmSql->func_ConvertUmdCDtoNM(asSURName.SubString(1,8));//210204//#LOADING_TEST//frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1, 8));
			else
				asSURName = frmSql->func_ConvertRiCDtoNM(asSURName.SubString(1,10));//210204//#LOADING_TEST//frmMain->func_ConvertRiCDtoNM(asStr.SubString(1, 10));

			asNodeB.sprintf("%s[%s][%s호]", asSURName, asScale, asDoho);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument07[nIndex].tNode = NodeB;

			_nNodeCount++;
			asNodeC = eFunc->funcGetKindCodeToKindName(7, (char*)frmMain->m_ResultDocument07[nIndex].KIND_CODE);
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
			NodeC->ImageIndex = 5;
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument07.size(); i++)
		{
			asScale	= (char*)frmMain->m_ResultDocument07[i].SCALE;
			asDoho 	= (char*)frmMain->m_ResultDocument07[i].DOHO_BON;
			if( !asScale.IsEmpty() )
			{
				if( !asDoho.IsEmpty() )
					asNodeB.sprintf("1/%d00[%d호]", asScale.ToInt(), asDoho.ToInt());
				else
					asNodeB.sprintf("1/%d00[-호]", asScale.ToInt());
			}
			else
			{
				if( !asDoho.IsEmpty() )
					asNodeB.sprintf("-[%d호]", asDoho.ToInt());
				else
					asNodeB.sprintf("-[-호]");
			}

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument07[i]; //**
			//NodeB->StateIndex = i;//200105
			NodeB->ImageIndex = 5;
		}
	}
//	else
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument07.size();
//
//		//200916//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				asStr = (char*)frmMain->m_ResultDocument07[nIndex].UMD;
//				asStr = asStr + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//				asStr = frmMain->INIINFO.SIDOCODE + asStr;
//				if(asStr.Length() < 8)
//				{
//					frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
//					nEraseCnt++;
//					continue;
//				}
//
//				if(asStr.SubString(9, 2) == "00")
//					asNodeB1 = frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1, 8));
//				else
//					asNodeB1 = frmMain->func_ConvertRiCDtoNM(asStr.SubString(1, 10));
//
//				if(asNodeB  == asNodeB1)
//				{
//					asScale = (char*)frmMain->m_ResultDocument07[nIndex].SCALE;
//					if(asScale != "")
//						asScale.sprintf("%d00", asScale.ToInt());
//					else
//						asScale = "-";
//
//					asStr = eFunc->funcGetKindCodeToKindName(7, (char*)frmMain->m_ResultDocument07[nIndex].KIND_CODE);
//					asNodeC1.sprintf("%s[%s]", asStr, asScale);
//					if(asNodeC == asNodeC1)//문서구분[축척] 같고//
//					{
//						frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//
//				}
//			}
//
//			asStr = (char*)frmMain->m_ResultDocument07[nIndex].UMD;
//			asStr = asStr + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//			asStr = frmMain->INIINFO.SIDOCODE + asStr;
//			if(asStr.Length() < 8)
//			{
//				frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
//				nEraseCnt++;
//				continue;
//			}
//
//			nDocCut++;
//			if(asStr.SubString(9, 2) == "00")
//				asNodeB = frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1, 8));
//			else
//				asNodeB = frmMain->func_ConvertRiCDtoNM(asStr.SubString(1, 10));
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument07[nIndex].tNode = NodeB;
//
//			_nNodeCount++;
//			asScale = (char*)frmMain->m_ResultDocument07[nIndex].SCALE;
//			if(asScale != "")
//				asScale.sprintf("%d00", asScale.ToInt());
//			else
//				asScale = "-";
//
//			asNodeC = eFunc->funcGetKindCodeToKindName(7, (char*)frmMain->m_ResultDocument07[nIndex].KIND_CODE);
//			asNodeC.sprintf("%s[%s]", asNodeC, asScale);
//			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//			NodeC->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
//			NodeC->ImageIndex = 5;
//		}
//	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument07.size();

		//200916//
		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asKindName  = eFunc->funcGetKindCodeToKindName(7, (char*)frmMain->m_ResultDocument07[nIndex].KIND_CODE);
			asScale 	= (char*)frmMain->m_ResultDocument07[nIndex].SCALE;
			if(asScale != "")
				asScale.sprintf("%d00", asScale.ToInt());
			else
				asScale = "-";

			asDoho 		= (char*)frmMain->m_ResultDocument07[nIndex].DOHO_BON;
			if(asDoho != "")
				asDoho.sprintf("%d", asDoho.ToInt());
			else
				asDoho = "-";

			if(nDocCut > 0)
			{
//=====================================================================
//[v1.0.0.5]//230619//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
//지번없이 '토지소재'만 입력 시 검색결과에 '토지소재'폴더명이 나타나지 않는 문제 수정//
				asSURName = (char*)frmMain->m_ResultDocument07[nIndex].SIDOSGG;
				asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].UMD;
				asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//OLD//
//				asStr = (char*)frmMain->m_ResultDocument07[nIndex].UMD;
//				asStr = asStr + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//				asStr = frmMain->INIINFO.SIDOCODE + asStr;
//=====================================================================
				if(asSURName.Length() < 8)
				{
					frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
					nEraseCnt++;
					continue;
				}

				if(asSURName.SubString(9, 2) == "00")
					asNodeB1 = frmSql->func_ConvertUmdCDtoNM(asSURName.SubString(1,8));//210204//#LOADING_TEST//frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1, 8));
				else
					asNodeB1 = frmSql->func_ConvertRiCDtoNM(asSURName.SubString(1,10));//210204//#LOADING_TEST//frmMain->func_ConvertRiCDtoNM(asStr.SubString(1, 10));

				if(asNodeB  == asNodeB1)
				{
					asNodeC1.sprintf("%s[%s][도호:%s]", asKindName, asScale, asDoho);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					//201008//44760//Req//문서구분별 삭제//
//					if(asNodeC == asNodeC1)//문서구분[축척] 같고//
//					{
//						frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;

				}
			}

//=============================================================================
//=====================================================================
//[v1.0.0.5]//230619//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
//지번없이 '토지소재'만 입력 시 검색결과에 '토지소재'폴더명이 나타나지 않는 문제 수정//
			asSURName = (char*)frmMain->m_ResultDocument07[nIndex].SIDOSGG;
			asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].UMD;
			asSURName = asSURName + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//OLD//
//			asStr = (char*)frmMain->m_ResultDocument07[nIndex].UMD;
//			asStr = asStr + (char*)frmMain->m_ResultDocument07[nIndex].RI;
//			asStr = frmMain->INIINFO.SIDOCODE + asStr;
//=====================================================================
			if(asSURName.Length() < 8)
			{
				frmMain->m_ResultDocument07.erase(frmMain->m_ResultDocument07.begin() + nIndex);
				nEraseCnt++;
				continue;
			}

			nDocCut++;
			if(asSURName.SubString(9, 2) == "00")
				asSURName = frmSql->func_ConvertUmdCDtoNM(asSURName.SubString(1,8));//210204//#LOADING_TEST//frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1, 8));
			else
				asSURName = frmSql->func_ConvertRiCDtoNM(asSURName.SubString(1,10));//210204//#LOADING_TEST//frmMain->func_ConvertRiCDtoNM(asStr.SubString(1, 10));
			asNodeB = asSURName;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument07[nIndex].tNode = NodeB;

			_nNodeCount++;
			asKindName = eFunc->funcGetKindCodeToKindName(7, (char*)frmMain->m_ResultDocument07[nIndex].KIND_CODE);
			//asNodeC.sprintf("%s[%s][도호:%s][P:%s]", asNodeC, asScale, asDoho, asPage);
			asNodeC.sprintf("%s[%s][도호:%s]", asKindName, asScale, asDoho);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument07[nIndex]; //**
			NodeC->ImageIndex = 5;
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc08(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeD		= "";
	AnsiString 	asNodeD1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString  asSinguName = "";//SINGU_NAME
	AnsiString  asKindName 	= "";//KIND_CODE
	AnsiString 	asPnu		= "";//PNU
	AnsiString 	asStr		= "";
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;
	TTreeNode 	*NodeD = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//지번정보목록에서 검색해야함//[TODO]
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument08.size();

		for (int i = 0; i < nSize; i++)
		{
			asNodeD 	= "";

			nIndex = i - nEraseCnt;

			asPnu		= eMainSub->funcMakeJibun(AnsiString(frmMain->m_ResultDocument08[nIndex].PNU));
			asSinguName = (char*)frmMain->m_ResultDocument08[nIndex].SINGU_NAME;
			asKindName  = eFunc->funcGetKindCodeToKindName(8, frmMain->m_ResultDocument08[nIndex].KIND_CODE);
			if (asSinguName != "부책")
			{
				if ( strcmp(frmMain->m_ResultDocument08[nIndex].ONOFF_CODE, "1") == 0)
					asNodeD.sprintf("%s[뒷면]", asKindName);
				else
					asNodeD.sprintf("%s[앞면]", asKindName);
			}
			else//부책//
			{
				asNodeD.sprintf("%s", asKindName);
			}
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeD	= StringReplace(asNodeD, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

			if(nDocCut > 0)
			{
				asNodeB1 = asPnu;
				if(asNodeB  == asNodeB1)//PNU 같고//
				{
					asNodeC1	= asSinguName;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					if(asNodeC  == asNodeC1)//PNU 같고//
					{
						_nNodeCount++;
						NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
						NodeD->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
						NodeD->ImageIndex = 5;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
					NodeC->ImageIndex = 4;
					frmMain->m_ResultDocument08[nIndex].tNode = NodeC;

					_nNodeCount++;
					NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
					NodeD->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
					NodeD->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asPnu;
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeB->ImageIndex = 4;

			_nNodeCount++;
			asNodeC	= asSinguName;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeC->ImageIndex = 4;
			frmMain->m_ResultDocument08[nIndex].tNode = NodeC;

			//if( strcmp((char*)frmMain->m_ResultDocument08[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
				NodeD->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
				NodeD->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분 선택//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument08.size();

		for (int i = 0; i < nSize; i++)
		{
			asNodeC 	= "";

			nIndex = i - nEraseCnt;

			asPnu		= eMainSub->funcMakeJibun(AnsiString(frmMain->m_ResultDocument08[nIndex].PNU));
			asSinguName = (char*)frmMain->m_ResultDocument08[nIndex].SINGU_NAME;
			asKindName  = eFunc->funcGetKindCodeToKindName(8, frmMain->m_ResultDocument08[nIndex].KIND_CODE);
			if (asSinguName != "부책")
			{
				if ( strcmp(frmMain->m_ResultDocument08[nIndex].ONOFF_CODE, "1") == 0)
					asNodeC.sprintf("%s[뒷면]", asKindName);
				else
					asNodeC.sprintf("%s[앞면]", asKindName);
			}
			else//부책//
			{
				asNodeC.sprintf("%s", asKindName);
            }
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);

			if(nDocCut > 0)
			{
				asNodeB1 = asPnu;
				if(asNodeB  == asNodeB1)//PNU 같고//
				{
					_nNodeCount++;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asPnu;
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeB->ImageIndex = 4;

			_nNodeCount++;
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeC->ImageIndex = 5;
		}
	}
	else if(frmSearch->m_bInputDoc)//상세검색//문서구분 선택//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument08.size();

		for (int i = 0; i < nSize; i++)
		{
			asNodeD 	= "";

			nIndex = i - nEraseCnt;

			asPnu		= eMainSub->funcMakeJibun(AnsiString(frmMain->m_ResultDocument08[nIndex].PNU));
			asSinguName = (char*)frmMain->m_ResultDocument08[nIndex].SINGU_NAME;
			asKindName  = eFunc->funcGetKindCodeToKindName(8, frmMain->m_ResultDocument08[nIndex].KIND_CODE);
			if (asSinguName != "부책")
			{
				if ( strcmp(frmMain->m_ResultDocument08[nIndex].ONOFF_CODE, "1") == 0)
					asNodeD.sprintf("%s[뒷면]", asKindName);
				else
					asNodeD.sprintf("%s[앞면]", asKindName);
			}
			else//부책//
			{
				asNodeD.sprintf("%s", asKindName);
			}
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeD	= StringReplace(asNodeD, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

			if(nDocCut > 0)
			{
				asNodeB1 = asPnu;
				if(asNodeB  == asNodeB1)//PNU 같고//
				{
					asNodeC1 = asSinguName;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					if(asNodeC  == asNodeC1)//PNU 같고//
					{
						_nNodeCount++;
						NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
						NodeD->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
						NodeD->ImageIndex = 5;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
					NodeC->ImageIndex = 4;
					frmMain->m_ResultDocument08[nIndex].tNode = NodeC;

					_nNodeCount++;
					NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
					NodeD->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
					NodeD->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asPnu;
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeB->ImageIndex = 4;

			_nNodeCount++;
			asNodeC = asSinguName;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeC->ImageIndex = 4;
			frmMain->m_ResultDocument08[nIndex].tNode = NodeC;

			//if( strcmp((char*)frmMain->m_ResultDocument08[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				NodeD = frmMain->treSystem->Items->AddChild(NodeC, asNodeD.c_str());
				NodeD->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
				NodeD->ImageIndex = 5;
			}
		}
	}
	else//if(frmMain->m_nActiveDoc)//통합검색 - 지번 표시 필요없음//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument08.size();

		//Init//
		asNodeB		= "";
		//
		for (int i = 0; i < nSize; i++)
		{
			asNodeC 	= "";

			nIndex = i - nEraseCnt;

			asPnu		= eMainSub->funcMakeJibun(AnsiString(frmMain->m_ResultDocument08[nIndex].PNU));
			asSinguName = (char*)frmMain->m_ResultDocument08[nIndex].SINGU_NAME;
			asKindName  = eFunc->funcGetKindCodeToKindName(8, frmMain->m_ResultDocument08[nIndex].KIND_CODE);
			if (asSinguName != "부책")
			{
				if ( strcmp(frmMain->m_ResultDocument08[nIndex].ONOFF_CODE, "1") == 0)
					asNodeC.sprintf("%s[뒷면]", asKindName);
				else
					asNodeC.sprintf("%s[앞면]", asKindName);
			}
			else//부책//
			{
				asNodeC.sprintf("%s", asKindName);
			}
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

			if(nDocCut > 0)
			{
				asNodeB1 = asSinguName;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB == asNodeB1)//부책 OR 카드 같고//
				{
					_nNodeCount++;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asSinguName;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeB->ImageIndex = 4;

			_nNodeCount++;
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument08[nIndex]; //**
			NodeC->ImageIndex = 5;
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------
//int cTreeSystem::funcNodeSettingDoc09(int _nDocNo, int _nNodeCount)
//{
//	AnsiString 	asNodeB		= "";
//	AnsiString 	asNodeB1	= "";
//	AnsiString 	asNodeC		= "";
//	AnsiString 	asNodeC1	= "";
//	AnsiString 	asNodeLabel	= "";
//	int 		nDocCut = 0;
//	int 		nReturnValue = 0;
//	TTreeNode 	*NodeB = NULL;
//	TTreeNode 	*NodeC = NULL;
//
//	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument09.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				asNodeB1.sprintf("%s-%s", (char*)frmMain->m_ResultDocument09[nIndex].BASE_YEAR, frmMain->m_ResultDocument09[nIndex].BASE_MON);
//				if(asNodeB  == asNodeB1)//BASE_YEAR[BASE_MON] 같고//
//				{
//					//asNodeB를 00010 PAGE로 연결//
//					asNodeC1 = eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[nIndex].KIND_CODE);
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument09.erase(frmMain->m_ResultDocument09.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument09[i]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			asNodeB.sprintf("%s-%s", (char*)frmMain->m_ResultDocument09[nIndex].BASE_YEAR, frmMain->m_ResultDocument09[nIndex].BASE_MON);
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument09[nIndex].tNode = NodeB;
//
////			if( strcmp((char*)frmMain->m_ResultDocument01[i].PAGE_NO, "00010") )//첫페이지가 아니면//
//			{
//				_nNodeCount++;
//				asNodeC = eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[nIndex].KIND_CODE);
//				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//				NodeC->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
//				NodeC->ImageIndex = 5;
//			}
//		}
//	}
//	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
//	{
//		for (int i = 0; i < (int)frmMain->m_ResultDocument09.size(); i++)
//		{
//			asNodeB.sprintf("%s-%s", (char*)frmMain->m_ResultDocument09[i].BASE_YEAR, frmMain->m_ResultDocument09[i].BASE_MON);
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument09[i]; //**
//			NodeB->ImageIndex = 5;
//		}
//	}
//	else
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument09.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				asNodeB1.sprintf("%s-%s", (char*)frmMain->m_ResultDocument09[nIndex].BASE_YEAR, frmMain->m_ResultDocument09[nIndex].BASE_MON);
//				if(asNodeB  == asNodeB1)//BASE_YEAR[BASE_MON] 같고//
//				{
//					//asNodeB를 00010 PAGE로 연결//
//					asNodeC1 = eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[nIndex].KIND_CODE);
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument09.erase(frmMain->m_ResultDocument09.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			asNodeB.sprintf("%s-%s", (char*)frmMain->m_ResultDocument09[nIndex].BASE_YEAR, frmMain->m_ResultDocument09[nIndex].BASE_MON);
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument09[nIndex].tNode = NodeB;
//
////			if( strcmp((char*)frmMain->m_ResultDocument01[i].PAGE_NO, "00010") )//첫페이지가 아니면//
//			{
//				_nNodeCount++;
//				asNodeC = eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[nIndex].KIND_CODE);
//				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//				NodeC->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
//				NodeC->ImageIndex = 5;
//			}
//		}
//	}
//
//	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
//	{
//		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
//		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
//	}
//
//	nReturnValue = nDocCut;
//	return nReturnValue;
//}
////---------------------------------------------------------------------------
//201020//#ALLSEARCHLABEL
int cTreeSystem::funcNodeSettingDoc09(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asBaseYear	= "";//BASE_YEAR
	AnsiString 	asBaseMon	= "";//BASE_MON
	AnsiString 	asPnu		= "";//PNUA//
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument09.size();

		for (int i = 0; i < nSize; i++)
		{
			asKindName	= eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[i].KIND_CODE);
			asBaseYear  = (char*)frmMain->m_ResultDocument09[i].BASE_YEAR;
			asBaseMon   = frmMain->m_ResultDocument09[i].BASE_MON;
			asPnu		= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument09[i].PNU, 0);

			if(nDocCut > 0)
			{
				asNodeB1	= asKindName;
				if(asNodeB  == asNodeB1)//KIND_CODE 같고//
				{
					asNodeC1.sprintf("%s-%s", asBaseYear, asBaseMon);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument09[i]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB	= asKindName;
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument09[i]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument09[i].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument01[i].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC.sprintf("%s-%s", asBaseYear, asBaseMon);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument09[i]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument09.size(); i++)
		{
			asKindName	= eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[i].KIND_CODE);
			asBaseYear  = (char*)frmMain->m_ResultDocument09[i].BASE_YEAR;
			asBaseMon   = frmMain->m_ResultDocument09[i].BASE_MON;

			asNodeB.sprintf("%s-%s", asBaseYear, asBaseMon);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			//201020//
			if( !asPnu.IsEmpty() )
				asNodeB	= asNodeB + "(시작지번:" + asPnu + ")";

			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument09[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument09.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asKindName	= eFunc->funcGetKindCodeToKindName(9, (char*)frmMain->m_ResultDocument09[nIndex].KIND_CODE);
			asBaseYear  = (char*)frmMain->m_ResultDocument09[nIndex].BASE_YEAR;
			asBaseMon   = frmMain->m_ResultDocument09[nIndex].BASE_MON;

			if(nDocCut > 0)
			{
				asNodeB1	= asKindName;
				if(asNodeB  == asNodeB1)//BASE_YEAR[BASE_MON] 같고//
				{
					asNodeC1.sprintf("%s-%s", asBaseYear, asBaseMon);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB	= asKindName;
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument09[i].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument01[i].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC.sprintf("%s-%s", asBaseYear, asBaseMon);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument09[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc11(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asKwonNo	= "";//KWON_NO
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument11.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asKindName	= eFunc->funcGetKindCodeToKindName(11, (char*)frmMain->m_ResultDocument11[nIndex].KIND_CODE);
			asKwonNo  	= (char*)frmMain->m_ResultDocument11[nIndex].KWON_NO;

			if(nDocCut > 0)
			{
				//===========================================================================
				//[REQ_260715_#2.DB내 권번호 변경]
				asNodeB1 = eFunc->funcGetKwonNo(asKwonNo);
				//===========================================================================
//				asNodeB1 = asKwonNo;
//				if( asNodeB1.IsEmpty() )	asNodeB1 = "0";
//				asNodeB1.sprintf("%d권", asNodeB1.ToInt());
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
//				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument11.erase(frmMain->m_ResultDocument11.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument11[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			//===========================================================================
			//[REQ_260715_#2.DB내 권번호 변경]
			asNodeB = eFunc->funcGetKwonNo(asKwonNo);
			//===========================================================================
//			asNodeB = asKwonNo;
//			if( asNodeB.IsEmpty() )	asNodeB = "0";
//			asNodeB.sprintf("%d권", asNodeB.ToInt());
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
//			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument11[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument11[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument11[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument11[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument11.size(); i++)
		{
			asKindName	= eFunc->funcGetKindCodeToKindName(11, (char*)frmMain->m_ResultDocument11[i].KIND_CODE);

			//===========================================================================
			//[REQ_260715_#2.DB내 권번호 변경]
			asNodeB = eFunc->funcGetKwonNo(asKindName);
			//===========================================================================
//			asNodeB = asKindName;
//			if( asNodeB.IsEmpty() )	asNodeB = "0";
//			asNodeB.sprintf("%d권", asNodeB.ToInt());
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
//			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument11[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument11.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asKindName	= eFunc->funcGetKindCodeToKindName(11, (char*)frmMain->m_ResultDocument11[nIndex].KIND_CODE);
			asKwonNo  	= (char*)frmMain->m_ResultDocument11[nIndex].KWON_NO;

			if(nDocCut > 0)
			{
				//===========================================================================
				//[REQ_260715_#2.DB내 권번호 변경]
				asNodeB1 = eFunc->funcGetKwonNo(asKwonNo);
				//===========================================================================
//				asNodeB1 = asKwonNo;
//				if( asNodeB1.IsEmpty() )	asNodeB1 = "0";
//				asNodeB1.sprintf("%d권", asNodeB1.ToInt());
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
//				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//KWON_NO 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument11.erase(frmMain->m_ResultDocument11.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument11[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			//===========================================================================
			//[REQ_260715_#2.DB내 권번호 변경]
			asNodeB = eFunc->funcGetKwonNo(asKwonNo);
			//===========================================================================
//			asNodeB = asKwonNo;
//			if( asNodeB.IsEmpty() )	asNodeB = "0";
//			asNodeB.sprintf("%d권", asNodeB.ToInt());
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
//			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument11[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument11[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument11[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument11[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc12(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asReqDay	= "";//REQ_DAY
	AnsiString 	asKindName	= "";//KIND_CODE
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument12.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asReqDay	= (char*)frmMain->m_ResultDocument12[nIndex].REQ_DAY;
			asKindName  = eFunc->funcGetKindCodeToKindName(12, (char*)frmMain->m_ResultDocument12[nIndex].KIND_CODE);

			if(nDocCut > 0)
			{
				asNodeB1 = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument12.erase(frmMain->m_ResultDocument12.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument12[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument12[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument12[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument12[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument12[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument12.size(); i++)
		{
			asReqDay	= (char*)frmMain->m_ResultDocument12[i].REQ_DAY;

			asNodeB = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument12[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument12.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asReqDay	= (char*)frmMain->m_ResultDocument12[nIndex].REQ_DAY;
			asKindName  = eFunc->funcGetKindCodeToKindName(12, (char*)frmMain->m_ResultDocument12[nIndex].KIND_CODE);

			if(nDocCut > 0)
			{
				asNodeB1 = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument12.erase(frmMain->m_ResultDocument12.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument12[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument12[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument12[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument12[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument12[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------


int cTreeSystem::funcNodeSettingDoc13(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asReqDay	= "";//REQ_DAY
	AnsiString 	asKindName	= "";//KIND_CODE
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument13.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asReqDay	= (char*)frmMain->m_ResultDocument13[nIndex].REQ_DAY;
			asKindName  = eFunc->funcGetKindCodeToKindName(13, (char*)frmMain->m_ResultDocument13[nIndex].KIND_CODE);

			if(nDocCut > 0)
			{
				asNodeB1 = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument13.erase(frmMain->m_ResultDocument13.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument13[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument13[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument13[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument13[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument13[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument13.size(); i++)
		{
			asReqDay	= (char*)frmMain->m_ResultDocument13[i].REQ_DAY;

			asNodeB = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument13[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
 		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument13.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asReqDay	= (char*)frmMain->m_ResultDocument13[nIndex].REQ_DAY;
			asKindName  = eFunc->funcGetKindCodeToKindName(13, (char*)frmMain->m_ResultDocument13[nIndex].KIND_CODE);

			if(nDocCut > 0)
			{
				asNodeB1 = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument13.erase(frmMain->m_ResultDocument13.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument13[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB = asReqDay;
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument13[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument13[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument13[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument13[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc14(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asPrcsDate	= "";//PRCS_DATE
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asMsurType	= "";//MEASURE_TYPE
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument14.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asPrcsDate	= (char*)frmMain->m_ResultDocument14[nIndex].PRCS_DATE;
			asKindName  = eFunc->funcGetKindCodeToKindName(1, (char*)frmMain->m_ResultDocument14[nIndex].KIND_CODE);
			asMsurType  = eFunc->funcGetKindCodeToKindName(111, (char*)frmMain->m_ResultDocument14[nIndex].MEASURE_TYPE);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument14.erase(frmMain->m_ResultDocument14.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument14[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument14[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument14[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument14[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument14[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument14.size(); i++)
		{
			asPrcsDate	= (char*)frmMain->m_ResultDocument14[i].PRCS_DATE;
			asMsurType  = eFunc->funcGetKindCodeToKindName(111, (char*)frmMain->m_ResultDocument14[i].MEASURE_TYPE);

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument14[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument14.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asPrcsDate	= (char*)frmMain->m_ResultDocument14[nIndex].PRCS_DATE;
			asKindName  = eFunc->funcGetKindCodeToKindName(1, (char*)frmMain->m_ResultDocument14[nIndex].KIND_CODE);
			asMsurType  = eFunc->funcGetKindCodeToKindName(111, (char*)frmMain->m_ResultDocument14[nIndex].MEASURE_TYPE);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument14.erase(frmMain->m_ResultDocument14.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument14[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[%s]", asPrcsDate, asMsurType);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument14[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument14[nIndex].tNode = NodeB;

//			if( strcmp((char*)frmMain->m_ResultDocument14[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument14[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

//int cTreeSystem::funcNodeSettingDoc15(int _nDocNo, int _nNodeCount)
//{
//	AnsiString 	asKwonNo	= "";
//	int			nGroupNo	= 0;
//	AnsiString 	asKwonNo1	= "";
//	int			nGroupNo1	= 0;
//
//	AnsiString 	asNodeB		= "";
//	AnsiString 	asNodeB1	= "";
//	AnsiString 	asNodeC		= "";
//	AnsiString 	asNodeC1	= "";
//	AnsiString 	asNodeLabel	= "";
//	int 		nDocCut = 0;
//	int 		nReturnValue = 0;
//	TTreeNode 	*NodeB = NULL;
//	TTreeNode 	*NodeC = NULL;
//
//	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument15.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				//200527//#9
//				asKwonNo1	= (char*)frmMain->m_ResultDocument15[nIndex].KWON_NO;
//				nGroupNo1	= frmMain->m_ResultDocument15[nIndex].GROUP_NO;
////				asNodeB1.sprintf("%s[%s][%s]", (char*)frmMain->m_ResultDocument15[nIndex].REG_NM, (char*)frmMain->m_ResultDocument15[nIndex].PRCS_DATE, (char*)frmMain->m_ResultDocument15[nIndex].REG_NO);
////				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
//				if(asKwonNo == asKwonNo1 && nGroupNo == nGroupNo1)
//				{
//					//asNodeB를 00010 PAGE로 연결//
//					asNodeC1 = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[nIndex].KIND_CODE);
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument15.erase(frmMain->m_ResultDocument15.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument15[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			//200527//#9
//			asKwonNo	= (char*)frmMain->m_ResultDocument15[nIndex].KWON_NO;
//			nGroupNo	= frmMain->m_ResultDocument15[nIndex].GROUP_NO;
//
//			asNodeB.sprintf("%s[%s][%s]", (char*)frmMain->m_ResultDocument15[nIndex].REG_NM, (char*)frmMain->m_ResultDocument15[nIndex].PRCS_DATE, (char*)frmMain->m_ResultDocument15[nIndex].REG_NO);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument15[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument15[nIndex].tNode = NodeB;
//
////			if( strcmp((char*)frmMain->m_ResultDocument15[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
//			{
//				_nNodeCount++;
//				asNodeC = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[nIndex].KIND_CODE);
//				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//				NodeC->Data = (void*)&frmMain->m_ResultDocument15[nIndex]; //**
//				NodeC->ImageIndex = 5;
//			}
//		}
//	}
//	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
//	{
//		for (int i = 0; i < (int)frmMain->m_ResultDocument15.size(); i++)
//		{
//			asNodeB.sprintf("%s[%s][%s]", (char*)frmMain->m_ResultDocument15[i].REG_NM, (char*)frmMain->m_ResultDocument15[i].PRCS_DATE, (char*)frmMain->m_ResultDocument15[i].REG_NO);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
//			NodeB->ImageIndex = 5;
//		}
//	}
//	else
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument15.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				//200527//#9
//				asKwonNo1	= (char*)frmMain->m_ResultDocument15[nIndex].KWON_NO;
//				nGroupNo1	= frmMain->m_ResultDocument15[nIndex].GROUP_NO;
////				asNodeB1.sprintf("%s[%s][%s]", (char*)frmMain->m_ResultDocument15[nIndex].REG_NM, (char*)frmMain->m_ResultDocument15[nIndex].PRCS_DATE, (char*)frmMain->m_ResultDocument15[nIndex].REG_NO);
////				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
//				if(asKwonNo == asKwonNo1 && nGroupNo == nGroupNo1)
//				{
//					//asNodeB를 00010 PAGE로 연결//
//					asNodeC1 = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[nIndex].KIND_CODE);
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument15.erase(frmMain->m_ResultDocument15.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument15[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			//200527//#9
//			asKwonNo	= (char*)frmMain->m_ResultDocument15[nIndex].KWON_NO;
//			nGroupNo	= frmMain->m_ResultDocument15[nIndex].GROUP_NO;
//
//			asNodeB.sprintf("%s[%s][%s]", (char*)frmMain->m_ResultDocument15[nIndex].REG_NM, (char*)frmMain->m_ResultDocument15[nIndex].PRCS_DATE, (char*)frmMain->m_ResultDocument15[nIndex].REG_NO);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument15[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument15[nIndex].tNode = NodeB;
//
////			if( strcmp((char*)frmMain->m_ResultDocument15[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
//			{
//				_nNodeCount++;
//				asNodeC = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[nIndex].KIND_CODE);
//				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//				NodeC->Data = (void*)&frmMain->m_ResultDocument15[nIndex]; //**
//				NodeC->ImageIndex = 5;
//			}
//		}
//	}
//
//	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
//	{
//		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
//		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
//	}
//	else
//	{
//		if ( frmMain->m_nActiveDoc != 0 )//개별검색
//		{
//			asNodeLabel.sprintf("%s [0건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo]);
//			frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
//		}
//	}
//
//	nReturnValue = nDocCut;
//	return nReturnValue;
//}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc15(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asRegNm		= "";
	AnsiString 	asPrcsDate  = "";
	AnsiString 	asRegNo		= "";
	AnsiString 	asKindNm	= "";
	AnsiString 	asKindNm1	= "";//201215//
	AnsiString 	asKwonNo	= "";
	AnsiString 	asKwonNo1	= "";//201215//
	int			nGroupNo	= 0;
	int			nGroupNo1	= 0;//201215//
	AnsiString 	asPageNo	= "";

	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument15.size();

		for (int i = 0; i < nSize; i++)
		{
			asRegNm		= (char*)frmMain->m_ResultDocument15[i].REG_NM;
			asPrcsDate	= (char*)frmMain->m_ResultDocument15[i].PRCS_DATE;
			asRegNo		= (char*)frmMain->m_ResultDocument15[i].REG_NO;
			asPageNo	= eFunc->funcGetPageNoName(15, frmMain->m_ResultDocument15[i].PAGE_NO);

			if(nDocCut > 0)
			{
				//201215//
				asKwonNo1   = (char*)frmMain->m_ResultDocument15[i].KWON_NO;
				nGroupNo1	= frmMain->m_ResultDocument15[i].GROUP_NO;
				asKindNm1    = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[i].KIND_CODE);

				//asNodeB1.sprintf("%s[%s][%s]", asRegNm, asPrcsDate, asRegNo);

				//201215//if(asNodeB == asNodeB1)
				if(asKwonNo == asKwonNo1 && nGroupNo == nGroupNo1)//201215//
				{
					if(asKindNm == asKindNm1)//201215//
						continue;

					asKindNm	= asKindNm1;//201215//

					asNodeC1.sprintf("%s[P:%s]", asKindNm1, asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			//201215//
			asKwonNo    = (char*)frmMain->m_ResultDocument15[i].KWON_NO;
			nGroupNo	= frmMain->m_ResultDocument15[i].GROUP_NO;
			asKindNm    = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[i].KIND_CODE);

			asNodeB.sprintf("%s[%s][%s]", asRegNm, asPrcsDate, asRegNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument15[i].tNode = NodeB;

			_nNodeCount++;
			asNodeC.sprintf("%s[P:%s]", asKindNm, asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
			NodeC->ImageIndex = 5;
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument15.size(); i++)
		{
			asRegNm		= (char*)frmMain->m_ResultDocument15[i].REG_NM;
			asPrcsDate	= (char*)frmMain->m_ResultDocument15[i].PRCS_DATE;
			asRegNo		= (char*)frmMain->m_ResultDocument15[i].REG_NO;

			asNodeB.sprintf("%s[%s][%s]", asRegNm, asPrcsDate, asRegNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
			NodeB->ImageIndex = 5;
		}
	}
	else
	{
		int 	nSize 		= (int)frmMain->m_ResultDocument15.size();

		for (int i = 0; i < nSize; i++)
		{
			asRegNm		= (char*)frmMain->m_ResultDocument15[i].REG_NM;
			asPrcsDate	= (char*)frmMain->m_ResultDocument15[i].PRCS_DATE;
			asRegNo		= (char*)frmMain->m_ResultDocument15[i].REG_NO;
			asPageNo	= eFunc->funcGetPageNoName(15, frmMain->m_ResultDocument15[i].PAGE_NO);

			if(nDocCut > 0)
			{
				//201215//
				asKwonNo1   = (char*)frmMain->m_ResultDocument15[i].KWON_NO;
				nGroupNo1	= frmMain->m_ResultDocument15[i].GROUP_NO;
				asKindNm1    = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[i].KIND_CODE);

				//asNodeB1.sprintf("%s[%s][%s]", asRegNm, asPrcsDate, asRegNo);

				//201215//if(asNodeB == asNodeB1)
				if(asKwonNo == asKwonNo1 && nGroupNo == nGroupNo1)//201215//
				{
					if(asKindNm == asKindNm1)//201215//
						continue;

					asKindNm	= asKindNm1;//201215//

					asNodeC1.sprintf("%s[P:%s]", asKindNm, asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC1	= StringReplace(asNodeC1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			//201215//
			asKwonNo    = (char*)frmMain->m_ResultDocument15[i].KWON_NO;
			nGroupNo	= frmMain->m_ResultDocument15[i].GROUP_NO;
			asKindNm    = eFunc->funcGetKindCodeToKindName(15, (char*)frmMain->m_ResultDocument15[i].KIND_CODE);

			asNodeB.sprintf("%s[%s][%s]", asRegNm, asPrcsDate, asRegNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument15[i].tNode = NodeB;

			_nNodeCount++;
			asNodeC.sprintf("%s[P:%s]", asKindNm, asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument15[i]; //**
			NodeC->ImageIndex = 5;
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

//int cTreeSystem::funcNodeSettingDoc17(int _nDocNo, int _nNodeCount)
//{
//	AnsiString 	asNodeB		= "";
//	AnsiString 	asNodeB1	= "";
//	AnsiString 	asNodeC		= "";
//	AnsiString 	asNodeC1	= "";
//	AnsiString 	asNodeLabel	= "";
//	int 		nDocCut = 0;
//	int 		nReturnValue = 0;
//	TTreeNode 	*NodeB = NULL;
//	TTreeNode 	*NodeC = NULL;
//
//	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument17.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				asNodeB1.sprintf("%s권", (char*)frmMain->m_ResultDocument17[nIndex].KWON_NO);
//
//				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
//				{
//					//asNodeB를 00010 PAGE로 연결//
//					asNodeC1 = (char*)frmMain->m_ResultDocument17[nIndex].DOC_NAME;
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument17.erase(frmMain->m_ResultDocument17.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument17[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			asNodeB.sprintf("%s권", (char*)frmMain->m_ResultDocument17[nIndex].KWON_NO);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument17[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument17[nIndex].tNode = NodeB;
//
////			if( strcmp((char*)frmMain->m_ResultDocument17[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
//			{
//				_nNodeCount++;
//				asNodeC = (char*)frmMain->m_ResultDocument17[nIndex].DOC_NAME;
//				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//				NodeC->Data = (void*)&frmMain->m_ResultDocument17[nIndex]; //**
//				NodeC->ImageIndex = 5;
//			}
//		}
//	}
//	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
//	{
//		for (int i = 0; i < (int)frmMain->m_ResultDocument17.size(); i++)
//		{
//			asNodeB.sprintf("%s", (char*)frmMain->m_ResultDocument17[i].KWON_NO);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
//			NodeB->ImageIndex = 5;
//		}
//	}
//	else
//	{
//		int		nEraseCnt	= 0;
//		int		nIndex		= 0;
//		int 	nSize 		= (int)frmMain->m_ResultDocument17.size();
//
//		for (int i = 0; i < nSize; i++)
//		{
//			nIndex = i - nEraseCnt;
//
//			if(nDocCut > 0)
//			{
//				asNodeB1.sprintf("%s권", (char*)frmMain->m_ResultDocument17[nIndex].KWON_NO);
//
//				if(asNodeB  == asNodeB1)//PRCS_DATE[MEASURE_TYPE] 같고//
//				{
//					//asNodeB를 00010 PAGE로 연결//
//					asNodeC1 = (char*)frmMain->m_ResultDocument17[nIndex].DOC_NAME;
//					if(asNodeC == asNodeC1)//KIND_CODE 같고//
//					{
//						frmMain->m_ResultDocument17.erase(frmMain->m_ResultDocument17.begin() + nIndex);
//						nEraseCnt++;
//						continue;
//					}
//
//					_nNodeCount++;
//					asNodeC = asNodeC1;
//					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//					NodeC->Data = (void*)&frmMain->m_ResultDocument17[nIndex]; //**
//					NodeC->ImageIndex = 5;
//					continue;
//				}
//			}
//
//			asNodeB.sprintf("%s권", (char*)frmMain->m_ResultDocument17[nIndex].KWON_NO);
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument17[nIndex]; //**
//			NodeB->ImageIndex = 4;
//			frmMain->m_ResultDocument17[nIndex].tNode = NodeB;
//
////			if( strcmp((char*)frmMain->m_ResultDocument17[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
//			{
//				_nNodeCount++;
//				asNodeC = (char*)frmMain->m_ResultDocument17[nIndex].DOC_NAME;
//				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
//				NodeC->Data = (void*)&frmMain->m_ResultDocument17[nIndex]; //**
//				NodeC->ImageIndex = 5;
//			}
//		}
//	}
//
//	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
//	{
//		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
//		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
//	}
//
//	nReturnValue = nDocCut;
//	return nReturnValue;
//}
////---------------------------------------------------------------------------

//201022//#ALLSEARCHLABEL//
int cTreeSystem::funcNodeSettingDoc17(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asKindNm	= "";
	AnsiString 	asKwonNo	= "";
	AnsiString 	asPageNo	= "";
	AnsiString 	asPnu		= "";//201016//
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument17.size(); i++)
		{
			asKindNm    = eFunc->funcGetKindCodeToKindName(17, frmMain->m_ResultDocument17[i].KIND_CODE);
			asKwonNo	= eFunc->funcGetPageNo((char*)frmMain->m_ResultDocument17[i].KWON_NO);
			asPageNo	= eFunc->funcGetPageNoName(17, frmMain->m_ResultDocument17[i].PAGE);
			asPnu		= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument17[i].PNU, 0);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[권:%s]", asKindNm, asKwonNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//KIND_CODE[KWON_NO] 같고//
				{
					asNodeC.sprintf("[P:%s]", asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					if( !asPnu.IsEmpty() )
						asNodeC	= asNodeC + "(시작지번:" + asPnu + ")";

					_nNodeCount++;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[권:%s]", asKindNm, asKwonNo);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument17[i].tNode = NodeB;

			_nNodeCount++;
			asNodeC.sprintf("[P:%s]", asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			if( !asPnu.IsEmpty() )
				asNodeC	= asNodeC + "(시작지번:" + asPnu + ")";

			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
			NodeC->ImageIndex = 5;
		}
	}
//	else if(frmSearch->m_bKindDoc)//상세검색//문서구분
//	{
//		for (int i = 0; i < (int)frmMain->m_ResultDocument17.size(); i++)
//		{
//			asNodeB.sprintf("%s", (char*)frmMain->m_ResultDocument17[i].KWON_NO);
//
//			nDocCut++;
//			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
//			NodeB->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
//			NodeB->ImageIndex = 5;
//		}
//	}
	else
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument17.size(); i++)
		{
			asKindNm    = eFunc->funcGetKindCodeToKindName(17, frmMain->m_ResultDocument17[i].KIND_CODE);
			asKwonNo	= eFunc->funcGetPageNo((char*)frmMain->m_ResultDocument17[i].KWON_NO);
			asPageNo	= eFunc->funcGetPageNoName(17, frmMain->m_ResultDocument17[i].PAGE);
			asPnu		= eFunc->funcPnuToBonbuName(frmMain->m_ResultDocument17[i].PNU, 0);

			if(nDocCut > 0)
			{
				asNodeB1.sprintf("%s[권:%s]", asKindNm, asKwonNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================

				if(asNodeB  == asNodeB1)//KIND_CODE[KWON_NO] 같고//
				{
					asNodeC.sprintf("[P:%s]", asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
					asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
					if( !asPnu.IsEmpty() )
						asNodeC	= asNodeC + "(시작지번:" + asPnu + ")";

					_nNodeCount++;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asNodeB.sprintf("%s[권:%s]", asKindNm, asKwonNo);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument17[i].tNode = NodeB;

			_nNodeCount++;
			asNodeC.sprintf("[P:%s]", asPageNo);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeC	= StringReplace(asNodeC, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			if( !asPnu.IsEmpty() )
				asNodeC	= asNodeC + "(시작지번:" + asPnu + ")";

			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument17[i]; //**
			NodeC->ImageIndex = 5;
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingDoc18(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asKwonNo	= "";
	AnsiString 	asKwonNo1	= "";
	AnsiString 	asJiguYear	= "";
	AnsiString 	asJiguName	= "";
	AnsiString 	asKindName	= "";
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	int 		nDocCut 	= 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument18.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asJiguYear 	= (char*)frmMain->m_ResultDocument18[nIndex].JIGU_YEAR;
			asJiguName 	= (char*)frmMain->m_ResultDocument18[nIndex].JIGU_NAME;
			asKindName 	= eFunc->funcGetKindCodeToKindName(18, frmMain->m_ResultDocument18[nIndex].KIND_CODE);

			if(nDocCut > 0)
			{
				asKwonNo1 	= (char*)frmMain->m_ResultDocument18[nIndex].KWON_NO;
				//===========================================================================
				//[REQ_260715_#2.DB내 권번호 변경]
				asKwonNo1 = eFunc->funcGetKwonNo(asKwonNo);
				//===========================================================================
//				if( asKwonNo1.IsEmpty() )
//					asKwonNo1.sprintf("-권");
//				else
//					asKwonNo1.sprintf("%d권", asKwonNo1.ToInt());

				if(asJiguYear.IsEmpty())
					asNodeB1.sprintf("[%s][%s]", asJiguName, asKwonNo1);
				else
					asNodeB1.sprintf("%s[%s][%s]", asJiguYear, asJiguName, asKwonNo1);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//JIGU_YEAR[JIGU_NAME][KWON_NO] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					//if( !strcfrmMain->m_ResultDocument18[nIndex].KIND_CODE, "00") )
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument18.erase(frmMain->m_ResultDocument18.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument18[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asKwonNo 	= (char*)frmMain->m_ResultDocument18[nIndex].KWON_NO;
			//===========================================================================
			//[REQ_260715_#2.DB내 권번호 변경]
			asKwonNo = eFunc->funcGetKwonNo(asKwonNo);
			//===========================================================================
//			if( asKwonNo.IsEmpty() )
//				asKwonNo.sprintf("-권");
//			else
//				asKwonNo.sprintf("%d권", asKwonNo.ToInt());

			if(asJiguYear.IsEmpty())
				asNodeB.sprintf("[%s][%s]", asJiguName, asKwonNo);
			else
				asNodeB.sprintf("%s[%s][%s]", asJiguYear, asJiguName, asKwonNo);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument18[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument18[nIndex].tNode = NodeB;

			if( strcmp((char*)frmMain->m_ResultDocument18[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument18[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}
	else if(frmSearch->m_bKindDoc)//상세검색//문서구분 선택//
	{
		for (int i = 0; i < (int)frmMain->m_ResultDocument18.size(); i++)
		{
			asJiguYear 	= (char*)frmMain->m_ResultDocument18[i].JIGU_YEAR;
			asJiguName 	= (char*)frmMain->m_ResultDocument18[i].JIGU_NAME;

			asNodeB.sprintf("%s[%s]", asJiguYear, asJiguName);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument18[i]; //**
			NodeB->ImageIndex = 5;
		}
    }
	else//if(frmMain->m_nActiveDoc)//통합검색
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument18.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asJiguYear 	= (char*)frmMain->m_ResultDocument18[nIndex].JIGU_YEAR;
			asJiguName 	= (char*)frmMain->m_ResultDocument18[nIndex].JIGU_NAME;
			asKindName 	= eFunc->funcGetKindCodeToKindName(18, frmMain->m_ResultDocument18[nIndex].KIND_CODE);

			if(nDocCut > 0)
			{
				asKwonNo1 	= (char*)frmMain->m_ResultDocument18[nIndex].KWON_NO;
				//===========================================================================
				//[REQ_260715_#2.DB내 권번호 변경]
				asKwonNo1 = eFunc->funcGetKwonNo(asKwonNo1);
				//===========================================================================
//				if( asKwonNo1.IsEmpty() )
//					asKwonNo1.sprintf("-권");
//				else
//					asKwonNo1.sprintf("%d권", asKwonNo1.ToInt());

				if(asJiguYear.IsEmpty())
					asNodeB1.sprintf("[%s][%s]", asJiguName, asKwonNo1);
				else
					asNodeB1.sprintf("%s[%s][%s]", asJiguYear, asJiguName, asKwonNo1);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
				asNodeB1	= StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
				if(asNodeB  == asNodeB1)//JIGU_YEAR[JIGU_NAME][KWON_NO] 같고//
				{
					//asNodeB를 00010 PAGE로 연결//
					//if( !strcfrmMain->m_ResultDocument18[nIndex].KIND_CODE, "00") )
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument18.erase(frmMain->m_ResultDocument18.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					_nNodeCount++;
					asNodeC = asNodeC1;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument18[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			asKwonNo 	= (char*)frmMain->m_ResultDocument18[nIndex].KWON_NO;
			//===========================================================================
			//[REQ_260715_#2.DB내 권번호 변경]
			asKwonNo1 = eFunc->funcGetKwonNo(asKwonNo1);
			//===========================================================================
//			if( asKwonNo.IsEmpty() )
//				asKwonNo.sprintf("-권");
//			else
//				asKwonNo.sprintf("%d권", asKwonNo.ToInt());

			if(asJiguYear.IsEmpty())
				asNodeB.sprintf("[%s][%s]", asJiguName, asKwonNo);
			else
				asNodeB.sprintf("%s[%s][%s]", asJiguYear, asJiguName, asKwonNo);

//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument18[nIndex]; //**
			NodeB->ImageIndex = 4;
			frmMain->m_ResultDocument18[nIndex].tNode = NodeB;

			if( strcmp((char*)frmMain->m_ResultDocument18[nIndex].PAGE_NO, "00010") )//첫페이지가 아니면//
			{
				_nNodeCount++;
				asNodeC = asKindName;
				NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
				NodeC->Data = (void*)&frmMain->m_ResultDocument18[nIndex]; //**
				NodeC->ImageIndex = 5;
			}
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = _nNodeCount;
	return nReturnValue;
}
//---------------------------------------------------------------------------

//231020//GAGAMLAYER in LandArchive //here//
int cTreeSystem::funcNodeSettingDoc20(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asNodeB		= "";
	AnsiString 	asNodeB1	= "";
	AnsiString 	asNodeC		= "";
	AnsiString 	asNodeC1	= "";
	AnsiString 	asNodeLabel	= "";
	AnsiString 	asDocName	= "";//DOC_NAME
	AnsiString 	asKindName	= "";//KIND_CODE
	AnsiString 	asPrcsDate	= "";//PRCS_DATE
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;
	TTreeNode 	*NodeC = NULL;
	AnsiString 	asKwonNo	= "";

	if( (int)frmMain->m_vSPACE.size() > 0)//공간검색//BOJOPOINT값이 있는 데이터만 검색됨//
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument20.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asDocName 	= (char*)frmMain->m_ResultDocument20[nIndex].DOC_NAME;
			asKindName  = eFunc->funcGetKindCodeToKindName(20, (char*)frmMain->m_ResultDocument20[nIndex].KIND_CODE);
			asPrcsDate  = (char*)frmMain->m_ResultDocument20[nIndex].PRCS_DATE;
			if(asPrcsDate == "")  asPrcsDate	= "-";

			if(nDocCut > 0)
			{
				//Folder Node
				asNodeB1.sprintf("[%s]%s", asPrcsDate, asDocName);//21211//
//				asNodeB1 	= asDocName;
//				asNodeB1	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
				if(asNodeB  == asNodeB1)//DOC_NAME 같고//
				{
					//File Node
					_nNodeCount++;
					asNodeC = asKindName;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument20[nIndex]; //**
					NodeC->ImageIndex = 5;
				}

			}

			//Folder Node
			asNodeB.sprintf("[%s]%s", asPrcsDate, asDocName);//21211//
//			asNodeB	= asDocName;
//			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument20[nIndex]; //**
			NodeB->ImageIndex = 4;
			//File Node
			_nNodeCount++;
			asNodeC = asKindName;
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument20[nIndex]; //**
			NodeC->ImageIndex = 5;
		}
	}
	else
	{
		int		nEraseCnt	= 0;
		int		nIndex		= 0;
		int 	nSize 		= (int)frmMain->m_ResultDocument20.size();

		for (int i = 0; i < nSize; i++)
		{
			nIndex = i - nEraseCnt;

			asDocName 	= (char*)frmMain->m_ResultDocument20[nIndex].DOC_NAME;
			asKindName  = eFunc->funcGetKindCodeToKindName(20, (char*)frmMain->m_ResultDocument20[nIndex].KIND_CODE);
			asPrcsDate  = (char*)frmMain->m_ResultDocument20[nIndex].PRCS_DATE;
			if(asPrcsDate == "")  asPrcsDate	= "-";

			if(nDocCut > 0)
			{
				//Folder Node
				asNodeB1.sprintf("[%s]%s", asPrcsDate, asDocName);//21211//
//				asNodeB1 = asDocName;
//				asNodeB1 = StringReplace(asNodeB1, "(null)", "-", TReplaceFlags() << rfReplaceAll);
				if(asNodeB  == asNodeB1)//DOC_NAME 같고//
				{
					asNodeC1 = asKindName;
					if(asNodeC == asNodeC1)//KIND_CODE 같고//
					{
						frmMain->m_ResultDocument20.erase(frmMain->m_ResultDocument20.begin() + nIndex);
						nEraseCnt++;
						continue;
					}

					//File Node
					_nNodeCount++;
					asNodeC = asKindName;
					NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
					NodeC->Data = (void*)&frmMain->m_ResultDocument20[nIndex]; //**
					NodeC->ImageIndex = 5;
					continue;
				}
			}

			//Folder Node
			asNodeB.sprintf("[%s]%s", asPrcsDate, asDocName);//21211//
//			asNodeB = asDocName;
//			asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
			nDocCut++;
			NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
			NodeB->Data = (void*)&frmMain->m_ResultDocument20[nIndex]; //**
			NodeB->ImageIndex = 4;
			//File Node
			_nNodeCount++;
			asNodeC = asKindName;
			NodeC = frmMain->treSystem->Items->AddChild(NodeB, asNodeC.c_str());
			NodeC->Data = (void*)&frmMain->m_ResultDocument20[nIndex]; //**
			NodeC->ImageIndex = 5;
		}
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("%s [%d건]", frmMain->INIINFO.DOCKINDNAME[_nDocNo], nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcNodeSettingMemo(int _nDocNo, int _nNodeCount)
{
	AnsiString 	asTitle		= "";
	AnsiString 	asPoiKey	= "";
	AnsiString 	asNodeB	= "";
	AnsiString 	asNodeLabel	= "";
	int 		nDocCut = 0;
	int 		nReturnValue = 0;
	TTreeNode 	*NodeB = NULL;

	for (int i = 0; i < (int)frmMain->m_ResultMemo.size(); i++)
	{
		asTitle		= (char*)frmMain->m_ResultMemo[i].TITLE;
		asPoiKey	= (char*)frmMain->m_ResultMemo[i].POI_KEY;
		if(asPoiKey.Length() < 8)
			asPoiKey = "-";
		else
			asPoiKey = asPoiKey.SubString(1, 8);
		asNodeB.sprintf("%s[%s]", asTitle, asPoiKey);
//=============================================================================
//v1.0.0.5//#BugFixed//AnsiString변수를 sprintf에 사용하면 NULL인경우 'null'스트링이 표시되어 아래코드 추가//
		asNodeB	= StringReplace(asNodeB, "(null)", "-", TReplaceFlags() << rfReplaceAll);
//=============================================================================
		nDocCut++;
		NodeB = frmMain->treSystem->Items->AddChild(frmMain->mSearchNode.tNodeA[_nDocNo], asNodeB.c_str());
		NodeB->Data = (void*)&frmMain->m_ResultMemo[i]; //**
		if(frmMain->m_ResultMemo[i].DATA_CNT >= 3)
			NodeB->ImageIndex = 12;
		else
			NodeB->ImageIndex = 11;
	}

	if ( (frmMain->m_nActiveDoc == 0 && nDocCut) || (frmMain->m_nActiveDoc != 0) )//231209//통합검색이면 건수 있을 때만 표시, 상세검색이면 건수 없어도 표시//
	{
		asNodeLabel.sprintf("메모 [%d건]", nDocCut);
		frmMain->mSearchNode.tNodeA[_nDocNo]->Text = asNodeLabel.c_str();
	}

	nReturnValue = nDocCut;
	return nReturnValue;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcClickNodeToDocNum(TTreeNode* t_ClickNode)
{
	TTreeNode		*TempNode = t_ClickNode;
	int	nSelDoc = 0;

	try {
	while (TempNode->Level > 0) {
	  TempNode = TempNode->Parent;
	}

	for(int i=1; i<DF_DOC_CNT; i++)//#TAB00DEL#<검색>은 제외하기로//사장님Req//
	{
		if (frmMain->mSearchNode.tNodeA[i] == TempNode)
		{
			nSelDoc = i;
			return nSelDoc;
		}
	}
	if(frmMain->INIINFO.B_MEMO)
	{
		if (frmMain->mSearchNode.tNodeA[0] == TempNode)
		{
			nSelDoc = 0;
		}
	}

	} catch (Exception &exception) {
		return nSelDoc;
	}
	return nSelDoc;
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImage(TTreeNode* t_SelectNode)
{
	frmMain->m_nLogoutTimeCount = 0;

	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
	bool bRefreshThumb	= false;
	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
		bRefreshThumb	= true;


	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	switch (nSelDoc) {
		case  1:		funcNodeToImageDoc01(t_SelectNode, bRefreshThumb);		break;
		case  2:		funcNodeToImageDoc02(t_SelectNode, bRefreshThumb);		break;
		case  3:		funcNodeToImageDoc03(t_SelectNode, bRefreshThumb);		break;
		case  4:		funcNodeToImageDoc04(t_SelectNode, bRefreshThumb);		break;
		case  5:		funcNodeToImageDoc05(t_SelectNode, bRefreshThumb);		break;
		case  6:		funcNodeToImageDoc06(t_SelectNode, bRefreshThumb);		break;
		case  7:		funcNodeToImageDoc07(t_SelectNode, bRefreshThumb);		break;
		case  8:		funcNodeToImageDoc08(t_SelectNode, bRefreshThumb);		break;
		case  9:		funcNodeToImageDoc09(t_SelectNode, bRefreshThumb);		break;
		case 11:		funcNodeToImageDoc11(t_SelectNode, bRefreshThumb);		break;
		case 12:		funcNodeToImageDoc12(t_SelectNode, bRefreshThumb);		break;
		case 13:		funcNodeToImageDoc13(t_SelectNode, bRefreshThumb);		break;
		case 14:		funcNodeToImageDoc14(t_SelectNode, bRefreshThumb);		break;
		case 15:		funcNodeToImageDoc15(t_SelectNode, bRefreshThumb);		break;
		case 17:		funcNodeToImageDoc17(t_SelectNode, bRefreshThumb);		break;
		case 18:		funcNodeToImageDoc18(t_SelectNode, bRefreshThumb);		break;
		case 20:		funcNodeToImageDoc20(t_SelectNode, bRefreshThumb);		break;//231021//GAGAMLAYER in LandArchive
		case  0:		funcNodeToImageMemo(t_SelectNode, bRefreshThumb);		break;
		default:		break;
	}


	//=====================================================
	//250514//검색결과 동일 폴더인지 확인용//이미지가 없는 경우에라도 선택한 문서 정보로 갱신//
	//=====================================================
	if(t_SelectNode->Level == 1)
		frmMain->mSelectNodeFolder	= t_SelectNode;
	else if(t_SelectNode->Level > 1)
		frmMain->mSelectNodeFolder	= t_SelectNode->Parent;
	//=====================================================

}

//---------------------------------------------------------------------------
void cTreeSystem::funcNodeToImageDoc01(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	AnsiString 	asPathName 	= "";

	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT01_STRUCT	*mDoc1Struct;
	mDoc1Struct = (DOCUMENT01_STRUCT*)t_SelectNode->Data;
	if (!mDoc1Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//=============================================================================
	//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
	//=============================================================================
	if(frmMain->m_asParamStr2 != "SYSTEM_OK_USER_B")
//	{
//		frmMain->m_nFTPPathIndex	= 0;
//		frmMain->m_vFTPPathList.clear();
//		frmMain->m_nThumbPathIndex	= 0;
//		frmMain->m_vThumbPathList.clear();
//	}
//	else
	{
		//200604//#13
		//===============================================================
		if(!bRefreshThumb)
		{
			AnsiString asKwon 	= mDoc1Struct->KWON_NO;
			if( !asKwon.IsEmpty() )
			{
				//#FTP#===========================
				frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, mDoc1Struct->GROUP_NO, mDoc1Struct->GROUP_NO1, (char*)mDoc1Struct->PATH_NAME);

				//#THUMB#===========================
	//230518//#DOC01_THUMB_GROUP//TEST//			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, mDoc1Struct->GROUP_NO, mDoc1Struct->GROUP_NO1, (char*)mDoc1Struct->PATH_NAME);
				DOCUMENT01_STRUCT	*mFolderDocStruct = (DOCUMENT01_STRUCT*)frmMain->mSelectNodeFile->Data;
				if (mFolderDocStruct)
				{
					frmSql->funcReadDocThumbPathList(nSelDoc, (char*)mFolderDocStruct->KWON_NO, mFolderDocStruct->GROUP_NO, mFolderDocStruct->GROUP_NO1, (char*)mFolderDocStruct->PATH_NAME);
				}
			}
		}
		//===============================================================
	}
	//=============================================================================

	if( frmMain->funcGetImage(mDoc1Struct->PATH_NAME, nSelDoc, 1) )
	{
		//200604//#13//if(t_SelectNode->Level > 1)//PRCS_DATE[MEASURE_TYPE]
		if(t_SelectNode->Level == 1)//PRCS_DATE[MEASURE_TYPE]
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc1Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc1Struct->AF_PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc02(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT02_STRUCT	*mDoc2Struct;
	mDoc2Struct = (DOCUMENT02_STRUCT*)t_SelectNode->Data;
	if (!mDoc2Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc2Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc2Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, mDoc2Struct->GROUP_NO, 0, (char*)mDoc2Struct->PATH_NAME);
		}
	}

	if( frmMain->funcGetImage(mDoc2Struct->PATH_NAME, nSelDoc, 1) )
	{
//260623//[측량결과도]는 DEPTH가 1이어서 ThumbIndex를 제대로 못 가져옴//
//DEPTH 관계없이 가져오기로 함//
		frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc2Struct->PATH_NAME);
		if(frmMain->m_nThumbPathIndex > -1)
		{
			frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
			frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
		}
/*		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc2Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}
*/

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc2Struct->AF_PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}

//=============================================================================
//v1.0.0.5//11305//230831//측량결과도 필지 이미지좌표(POS_X, POS_Y) 존재하여 표시//
		if(frmMain->m_asSearchPnu.Length() == 19)
		{
			if(mDoc2Struct->POS_X > 0 && mDoc2Struct->POS_Y > 0)
			{
				frmMain->currMapPoint.POS_X = mDoc2Struct->POS_X;
				frmMain->currMapPoint.POS_Y = mDoc2Struct->POS_Y;
				frmMain->lblMapPoint->Caption = eFunc->funcPnuToBonbuName(frmMain->m_asSearchPnu.c_str(), 0);
				frmMain->lblMapPoint->Width = frmMain->lblMapPoint->Caption.Length() * frmMain->lblMapPoint->Font->Size;//200227//frmIniControl->mUserSetIniInfo.ulDoc0_V5_1);
				frmMain->shpMapPoint->Width = frmMain->lblMapPoint->Width + frmMain->imgMapPointClose->Width + 4;//200227

				frmMain->lblMapPoint->Font->Color 	= clRed;
				frmMain->shpMapPoint->Pen->Color 	= clRed;

				frmMain->funcSetLabelMapPoint(true);
				frmMain->funcRedrawMapPoint();
			}
		}
//=============================================================================
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc03(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT03_STRUCT	*mDoc3Struct;
	mDoc3Struct = (DOCUMENT03_STRUCT*)t_SelectNode->Data;
	if (!mDoc3Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc3Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc3Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc3Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc3Struct->PATH_NAME, nSelDoc, 1) )
	{
//260623//[측량결과도]는 DEPTH가 1이어서 ThumbIndex를 제대로 못 가져옴//
//DEPTH 관계없이 가져오기로 함//
		frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc3Struct->PATH_NAME);
		if(frmMain->m_nThumbPathIndex > -1)
		{
			frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
			frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
		}
/*		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc3Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}
*/
		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc3Struct->AF_PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc04(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT04_STRUCT	*mDoc4Struct;
	mDoc4Struct = (DOCUMENT04_STRUCT*)t_SelectNode->Data;
	if (!mDoc4Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc4Struct->KWON_NO;
//=================================================
//230502//#DOC04_GROUP//
		AnsiString asRecNo 	= mDoc4Struct->REC_NO;
//=================================================
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc4Struct->PATH_NAME);

			//#THUMB#===========================
//=================================================
//230502//#DOC04_GROUP//
			if( !asRecNo.IsEmpty() )
				frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, asRecNo.ToInt(), 0, (char*)mDoc4Struct->PATH_NAME);
			else
//=================================================
				frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc4Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc4Struct->PATH_NAME, nSelDoc, 1) )
	{
		//201020//#ALLSEARCHLABEL
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc4Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}
		//201020//
//		if(t_SelectNode->Level == 1)//200604//#13
//		{
//			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
//		}
//		else if(t_SelectNode->Level > 1)//200604//#13//
//		{
//			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//
//
//			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc4Struct->PATH_NAME);
//			if(frmMain->m_nThumbPathIndex > -1)
//			{
//				frmMain->funcShowCurrentThumbLabel();
//			}
//		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc4Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc05(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT05_STRUCT	*mDoc5Struct;
	mDoc5Struct = (DOCUMENT05_STRUCT*)t_SelectNode->Data;
	if (!mDoc5Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc5Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, mDoc5Struct->GROUP_NO, mDoc5Struct->GROUP_NO1, (char*)mDoc5Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, mDoc5Struct->GROUP_NO, mDoc5Struct->GROUP_NO1, (char*)mDoc5Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc5Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc5Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc5Struct->AF_PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc06(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT06_STRUCT	*mDoc6Struct;
	mDoc6Struct = (DOCUMENT06_STRUCT*)t_SelectNode->Data;
	if (!mDoc6Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc6Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc6Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc6Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc6Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc6Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc6Struct->AF_PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc07(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	AnsiString 	asPathName 	= "";
	AnsiString  asKwon		= "";

	frmSearch->m_asSelectPnu = "";

	frmMain->funcSetLabelMapPoint(false);//200226

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT07_STRUCT	*mDoc7Struct;
	mDoc7Struct = (DOCUMENT07_STRUCT*)t_SelectNode->Data;
	if (!mDoc7Struct) { return;	}

	frmMain->m_asDocDBPathName = mDoc7Struct->PATH_NAME;//201014//DOC07PNU.PATH_NAME을 갖고 있어야 함. 이미지 내부에서 다른 지번 검색시 필요//
	asKwon 	= mDoc7Struct->KWON_NO;

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	//200821//지적도는 문서구분별로 항상 thumbnail이 다르다//
//	//if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//	//	bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc7Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc7Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc7Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13

			//201227//
			asPathName = (char*)mDoc7Struct->PATH_NAME;
			frmSql->funcReadDocDBInfo(nSelDoc, asKwon, asPathName);
			//---

			//#MAPPOINT#//-----------
//			if(frmMain->m_vLANDINFO.size() > 0
//			&& (strcmp(mDoc7Struct->KIND_CODE, "08") && strcmp(mDoc7Struct->KIND_CODE, "09") ) )
			if( (strcmp(mDoc7Struct->KIND_CODE, "08") && strcmp(mDoc7Struct->KIND_CODE, "09") ) )//일람도, 색인표 아닌 문서//
			{
				if(frmMain->m_vLANDINFO.size() > 0 && frmMain->m_asSearchPnu.Length() == 19)
				{
					if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
					{
						if(frmMain->_SELECTREALLANDCD.Length() == 0)
						{
							int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
							if(nJibunIndex > -1)
							{
								if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
								{
									frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
									frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
								}
							}
						}
					}
				}

				if(frmMain->m_asSearchPnu.Length() == 19)//201227//상세검색에서는 표시못함//
				{
					frmMain->funcCalcWorldToMap(false);//DB value : 지번표시
					if(frmMain->currMapPoint.POS_X > 0 && frmMain->currMapPoint.POS_Y > 0)
					{
						if(frmMain->m_bOtherJibun)
						{
							frmMain->lblMapPoint->Caption = "인근지번";
							frmMain->lblMapPoint->Width = 52;//200227
						}
						else
						{
							frmMain->lblMapPoint->Caption = eFunc->funcPnuToBonbuName(frmMain->m_asSearchPnu.c_str(), 0);
							frmMain->lblMapPoint->Width = frmMain->lblMapPoint->Caption.Length() * frmMain->lblMapPoint->Font->Size;//200227//frmIniControl->mUserSetIniInfo.ulDoc0_V5_1);
						}

						frmMain->shpMapPoint->Width = frmMain->lblMapPoint->Width + frmMain->imgMapPointClose->Width + 4;//200227

						if(frmMain->m_vLANDINFO.size() == 0 && frmSql->m_ResultDoc07DBInfo[0].REMARK == 2)
						{
							frmMain->lblMapPoint->Font->Color 	= clRed;
							frmMain->shpMapPoint->Pen->Color 	= clRed;
						}
						else
						{
							frmMain->lblMapPoint->Font->Color 	= clBlue;
							frmMain->shpMapPoint->Pen->Color 	= clBlue;
						}

						frmMain->funcSetLabelMapPoint(true);

						frmMain->funcRedrawMapPoint();
					}
				}

				//#DOGWAK#
//241108//CommonFunctions//				if(frmMain->INI_B_DOGWAK)
				{
					if( !strcmp(mDoc7Struct->SCALE, "60") )
					{
						frmMain->m_vDOGAKLINE.clear();
						frmMain->pnlDocInfo07->Visible 	= true;
						frmMain->pnlDogakLineT->Visible = true;
					}
				}
				//#DOGWAK#//-----------
			}
			//#MAPPOINT#//-----------

		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			//201227//
			asPathName = (char*)mDoc7Struct->PATH_NAME;
			frmSql->funcReadDocDBInfo(nSelDoc, asKwon, asPathName);
			//---

			//201014//
 			//#MAPPOINT#//-----------
			if( (strcmp(mDoc7Struct->KIND_CODE, "08") && strcmp(mDoc7Struct->KIND_CODE, "09") ) )//일람도, 색인표 아닌 문서//
			{
				if(frmMain->m_vLANDINFO.size() > 0 && frmMain->m_asSearchPnu.Length() == 19)
				{
					if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
					{
						if(frmMain->_SELECTREALLANDCD.Length() == 0)
						{
							int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
							if(nJibunIndex > -1)
							{
								if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
								{
									frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
									frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
								}
							}
						}
					}
				}

				if(frmMain->m_asSearchPnu.Length() == 19)//201227//상세검색에서는 표시못함//
				{
					frmMain->funcCalcWorldToMap(false);//DB value : 지번표시
					if(frmMain->currMapPoint.POS_X > 0 && frmMain->currMapPoint.POS_Y > 0)
					{
						if(frmMain->m_bOtherJibun)
						{
							frmMain->lblMapPoint->Caption = "인근지번";
							frmMain->lblMapPoint->Width = 52;//200227
						}
						else
						{
							frmMain->lblMapPoint->Caption = eFunc->funcPnuToBonbuName(frmMain->m_asSearchPnu.c_str(), 0);
							frmMain->lblMapPoint->Width = frmMain->lblMapPoint->Caption.Length() * frmMain->lblMapPoint->Font->Size;//200227//frmIniControl->mUserSetIniInfo.ulDoc0_V5_1);
						}

						frmMain->shpMapPoint->Width = frmMain->lblMapPoint->Width + frmMain->imgMapPointClose->Width + 4;//200227

						if(frmMain->m_vLANDINFO.size() == 0 && frmSql->m_ResultDoc07DBInfo[0].REMARK == 2)
						{
							frmMain->lblMapPoint->Font->Color 	= clRed;
							frmMain->shpMapPoint->Pen->Color 	= clRed;
						}
						else
						{
							frmMain->lblMapPoint->Font->Color 	= clBlue;
							frmMain->shpMapPoint->Pen->Color 	= clBlue;
						}

						frmMain->funcSetLabelMapPoint(true);

						frmMain->funcRedrawMapPoint();
					}
				}

				//#DOGWAK#
//241108//CommonFunctions//				if(frmMain->INI_B_DOGWAK)
				{
					memcpy(&frmMain->m_vDOC07TEMP, mDoc7Struct, sizeof(DOCUMENT07_STRUCT));
					if( !strcmp(mDoc7Struct->SCALE, "60") )
					{
						frmMain->m_vDOGAKLINE.clear();
						frmMain->pnlDocInfo07->Visible 	= true;
						frmMain->pnlDogakLineT->Visible = true;
					}
				}
				//#DOGWAK#//-----------
			}
			//#MAPPOINT#//-----------

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc7Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}
	}
}
//---------------------------------------------------------------------------
void cTreeSystem::funcNodeToImageDoc08(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT08_STRUCT	*mDoc8Struct;
	mDoc8Struct = (DOCUMENT08_STRUCT*)t_SelectNode->Data;
	if (!mDoc8Struct) { return;	}

	if( frmMain->m_asDocDBPathName.Length() > 0 && !strcmp(mDoc8Struct->PATH_NAME_COLOR, frmMain->m_asDocDBPathName.c_str()) )//같은 이미지이면 안 띄운다//
		return;

	if (mDoc8Struct->PATH_NAME_COLOR[0] != 0x00)
	{
		frmMain->m_bDoc8Color = true;
		frmMain->m_asDocDBPathName = mDoc8Struct->PATH_NAME_COLOR;
	}
	else
	{
		frmMain->m_bDoc8Color = false;
		frmMain->m_asDocDBPathName = mDoc8Struct->PATH_NAME;
	}

//	//200623//구대장만 썸네일 예외처리//
//	bool bRefreshThumb	= false;
////	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
////		bRefreshThumb	= true;
//
	if( frmMain->funcGetImage(frmMain->m_asDocDBPathName, nSelDoc, 1) )
	{
		//200604//#13
//		//===============================================================
//		if(!bRefreshThumb)
//		{
			//200914//구대장썸네일만 안 보이게 처리함//
			AnsiString asKwon 	= mDoc8Struct->KWON_NO;
			if( !asKwon.IsEmpty() )
			{
				//#FTP#===========================
				frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc8Struct->PATH_NAME);

//				//#THUMB#===========================
//				frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc8Struct->PATH_NAME);
			}
//		}
//		//===============================================================

		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc8Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc8Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}

		if(frmMain->INI_B_JUMINHIDE)//#JUMINHIDE#
		{
			DOCUMENT08_STRUCT   *mDoc8Struct;
			mDoc8Struct = (DOCUMENT08_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
			if (!mDoc8Struct) return;
			if(!strcmp(mDoc8Struct->SINGU_NAME, "카드") && !strcmp(mDoc8Struct->ONOFF_CODE, ""))//구대장//토지대장//앞면//주민등록 뒷자리 처리//
			{
				//200318//다시 하는 이유는?//frmMain->FuncFullView32();
				frmMain->funcInitPBControl2();
				if(!strcmp(mDoc8Struct->JUMIN_YN, "1"))
				{
					frmMain->pnlDoc8Jumin->Visible = false;
					frmMain->funcSet_mRactStateLayer1_8DB((AnsiString)mDoc8Struct->JUMIN_XY);
				}
				else
				{
					if(frmMain->palPrevNextBar->Visible)
					{
						frmMain->pnlDoc8Jumin->Left = frmMain->palPrevNextBar->Left + frmMain->palPrevNextBar->Width + frmMain->EDGEGAP;
						frmMain->pnlDoc8Jumin->Top 	= frmMain->EDGEGAP;
					}
					else
					{
						frmMain->pnlDoc8Jumin->Left = frmMain->palTempDoc->Left + frmMain->palTempDoc->Width + frmMain->EDGEGAP;
						frmMain->pnlDoc8Jumin->Top 	= frmMain->EDGEGAP;
					}
					frmMain->edtDoc8C->Text = "1";
					frmMain->edtDoc8W->Text = "90";
					frmMain->edtDoc8H->Text = "20";
					frmMain->edtDoc8G->Text = "90";
					frmMain->m_dStartRateX 	= 0.78;
					frmMain->m_dStartRateY  = 0.37;
					frmMain->pnlDoc8Jumin->Visible = true;
					//200806//처음에 비활성화//frmMain->btnDoc8JuminDraw_OnClick(frmMain->btnDoc8JuminDraw);
				}
				return;
			}
		}

		//#OWNNAMES#
		if(frmMain->INI_B_OWNNAMES && !strcmp(mDoc8Struct->SINGU_NAME, "부책") )
		{
			frmSearch->funcSaveLog(0, 0, "");//210223//TEST

			//=================================================================
			//231118//#SHAREOWN//
			AnsiString  asKindCode = (char*)mDoc8Struct->KIND_CODE;
			if(asKindCode == "11" || asKindCode == "12" || asKindCode == "15" || asKindCode == "16")//부책//
				frmMain->m_bSUBBOOK	= true;
			else//공유지연명부// if(asKindCode == "13" || asKindCode == "14" || asKindCode == "17" || asKindCode == "18")
				frmMain->m_bSUBBOOK	= false;
			//=================================================================

			//201105//
			AnsiString asKwon 		= mDoc8Struct->KWON_NO;
			if(asKwon == "") asKwon = "0";
			frmSql->funcReadDocDBInfo(8, asKwon, mDoc8Struct->PATH_NAME);

			frmMain->funcProcessDoc8OwnNames((char*)mDoc8Struct->PATH_NAME);//#OWNINFO#

			frmSearch->funcSaveLog(2, 0, "");//save to file//210223//TEST
		}
		else//220207//
		{
			frmMain->funcInitDoc08Bar(false);
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc09(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT09_STRUCT	*mDoc9Struct;
	mDoc9Struct = (DOCUMENT09_STRUCT*)t_SelectNode->Data;
	if (!mDoc9Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc9Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc9Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc9Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc9Struct->PATH_NAME, nSelDoc, 1) )
	{
		//201020//#ALLSEARCHLABEL
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13

			if(frmSearch->m_bKindDoc)//상세검색//문서구분//201020//
			{
				frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc9Struct->PATH_NAME);
				if(frmMain->m_nThumbPathIndex > -1)
				{
					frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
					frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
				}
			}
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc9Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}
		//201020//#ALLSEARCHLABEL
//		if(t_SelectNode->Level == 1)//200604//#13
//		{
//			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
//		}
//		else if(t_SelectNode->Level > 1)//200604//#13//
//		{
//			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//
//
//			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc9Struct->PATH_NAME);
//			if(frmMain->m_nThumbPathIndex > -1)
//			{
//				frmMain->funcShowCurrentThumbLabel();
//			}
//		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc9Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc11(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT11_STRUCT	*mDoc11Struct;
	mDoc11Struct = (DOCUMENT11_STRUCT*)t_SelectNode->Data;
	if (!mDoc11Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc11Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc11Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc11Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc11Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc11Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc11Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc12(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT12_STRUCT	*mDoc12Struct;
	mDoc12Struct = (DOCUMENT12_STRUCT*)t_SelectNode->Data;
	if (!mDoc12Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc12Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc12Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc12Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc12Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc12Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc12Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc13(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT13_STRUCT	*mDoc13Struct;
	mDoc13Struct = (DOCUMENT13_STRUCT*)t_SelectNode->Data;
	if (!mDoc13Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc13Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc13Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc13Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc13Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc13Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc14(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT14_STRUCT	*mDoc14Struct;
	mDoc14Struct = (DOCUMENT14_STRUCT*)t_SelectNode->Data;
	if (!mDoc14Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc14Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, mDoc14Struct->GROUP_NO, mDoc14Struct->GROUP_NO1, (char*)mDoc14Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, mDoc14Struct->GROUP_NO, mDoc14Struct->GROUP_NO1, (char*)mDoc14Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc14Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc14Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc14Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc15(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT15_STRUCT	*mDoc15Struct;
	mDoc15Struct = (DOCUMENT15_STRUCT*)t_SelectNode->Data;
	if (!mDoc15Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc15Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, mDoc15Struct->GROUP_NO, mDoc15Struct->GROUP_NO1, (char*)mDoc15Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, mDoc15Struct->GROUP_NO, mDoc15Struct->GROUP_NO1, (char*)mDoc15Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc15Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc15Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc17(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT17_STRUCT	*mDoc17Struct;
	mDoc17Struct = (DOCUMENT17_STRUCT*)t_SelectNode->Data;
	if (!mDoc17Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc17Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc17Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc17Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc17Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc17Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}

		if(frmMain->m_bJijukLoading)//210204//#LOADING_TEST//
		{
			if(frmMain->_SELECTREALLANDCD.Length() == 0)
			{
				AnsiString asPnu = (char*)mDoc17Struct->PNU;
				if(asPnu.Length() == 19)
				{
					frmSearch->m_asSelectPnu = asPnu;
					int nJibunIndex = frmMain->func_readJibunIndex(frmSearch->m_asSelectPnu) - 1;
					if(nJibunIndex > -1)
					{
						if(frmMain->m_vSHPPOLYCBND[nJibunIndex].x > 0 && frmMain->m_vSHPPOLYCBND[nJibunIndex].y > 0)
						{
							frmMain->m_geoCenterPoint.x = frmMain->m_vSHPPOLYCBND[nJibunIndex].x;
							frmMain->m_geoCenterPoint.y = frmMain->m_vSHPPOLYCBND[nJibunIndex].y;
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageDoc18(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT18_STRUCT	*mDoc18Struct;
	mDoc18Struct = (DOCUMENT18_STRUCT*)t_SelectNode->Data;
	if (!mDoc18Struct) { return;	}

//	//200604//#13//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//200604//#13
	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 	= mDoc18Struct->KWON_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc18Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc18Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc18Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)//JIGU_YEAR[JIGU_NAME]//200604//#13
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;//200604//#13

			if(mDoc18Struct->X > 0 && mDoc18Struct->Y > 0)
			{
				frmMain->m_nZoomFactor	= 9;
				frmMain->btnZoomTrackBar->Value = frmMain->m_nZoomFactor;
				frmMain->m_geoCenterPoint.x = mDoc18Struct->X;
				frmMain->m_geoCenterPoint.y = mDoc18Struct->Y;
				frmMain->m_nSelectDognIndex = funcGetDognIndex(AnsiString(mDoc18Struct->KWON_NO));
				if(frmMain->m_nSelectDognIndex > -1)
				{
					AnsiString temp = mDoc18Struct->JIGU_NAME;
					temp = temp + "도근점:" + mDoc18Struct->DOGNPOINT;
					frmMain->funcSetStatusBarMsg(4, temp);
				}
			}
		}
		else if(t_SelectNode->Level > 1)//200604//#13//
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;//200604//#13//

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc18Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;//201021//
				frmMain->funcRefreshThumb();//201021//썸네일 탭도 재구성//frmMain->funcShowCurrentThumbLabel();
			}
		}
	}
}
//---------------------------------------------------------------------------

//=============================================================================
//231021//GAGAMLAYER in LandArchive
//=============================================================================
void cTreeSystem::funcNodeToImageDoc20(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	int	nSelDoc = funcClickNodeToDocNum(t_SelectNode);

	DOCUMENT20_STRUCT	*mDoc20Struct;
	mDoc20Struct = (DOCUMENT20_STRUCT*)t_SelectNode->Data;
	if (!mDoc20Struct) { return;	}

//	//폴더명 클릭했을 때 썸네일 구성하고 이미지 클릭시는 포커스인덱스만 찾는다//
//	bool bRefreshThumb	= false;
//	if(frmMain->mSelectNodeFile == frmMain->mSelectNodeFolder)
//		bRefreshThumb	= true;

	//===============================================================
	if(!bRefreshThumb)
	{
		AnsiString asKwon 		= mDoc20Struct->KWON_NO;
		AnsiString asGagamNo 	= mDoc20Struct->GAGAM_NO;
		if( !asKwon.IsEmpty() )
		{
			//#FTP#===========================
			frmSql->funcReadDocFTPPathList(nSelDoc, asKwon, 0, 0, (char*)mDoc20Struct->PATH_NAME);

			//#THUMB#===========================
			frmSql->funcReadDocThumbPathList(nSelDoc, asKwon, asGagamNo.ToInt(), 0, (char*)mDoc20Struct->PATH_NAME);
		}
	}
	//===============================================================

	if( frmMain->funcGetImage(mDoc20Struct->PATH_NAME, nSelDoc, 1) )
	{
		if(t_SelectNode->Level == 1)
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode;

			if(frmSearch->m_bKindDoc)//상세검색//문서구분//
			{
				frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc20Struct->PATH_NAME);
				if(frmMain->m_nThumbPathIndex > -1)
				{
					frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;
					frmMain->funcRefreshThumb();
				}
			}
		}
		else if(t_SelectNode->Level > 1)
		{
			//frmMain->mSelectNodeFolder	= t_SelectNode->Parent;

			frmMain->m_nThumbPathIndex 	= eFunc->funcGetDocThumbPathListIndex(mDoc20Struct->PATH_NAME);
			if(frmMain->m_nThumbPathIndex > -1)
			{
				frmMain->m_nThumbCurrIndex	= frmMain->m_nThumbPathIndex;
				frmMain->funcRefreshThumb();
			}
		}

		AnsiString asMNUM = "";
		if((int)frmMain->m_v_READGAGAM.size() > 0)
		{
			asMNUM.sprintf("%s%s%s", (char*)mDoc20Struct->UMDRI_CD, (char*)mDoc20Struct->KWON_NO, (char*)mDoc20Struct->GAGAM_NO);
			//가감대장 선택 아이콘 표시//
			frmMain->funcGetGagamIndex(asMNUM);
		}
//=============================================================================
//241210//금산,논산,홍성 가감대장 동일 처리를 위해 변경//
//241210//선택된 가감대장에 속하는 필지목록만 가져온다. 그러면 채색하는 부분에서 전체필지 비교하여 채색할 필요 없음.//
		else
		{
			AnsiString  asKwonNo	= (char*)mDoc20Struct->KWON_NO;
			AnsiString  asGagamNo	= (char*)mDoc20Struct->GAGAM_NO;
			frmSql->funcReadGagamLandList(asKwonNo, asGagamNo);
			frmSql->funcReadGagamBaseList(asKwonNo, asGagamNo);
		}
//=============================================================================
	}
}
//---------------------------------------------------------------------------

void cTreeSystem::funcNodeToImageMemo(TTreeNode* t_SelectNode, bool bRefreshThumb)
{
	frmSearch->m_asSelectPnu = "";

	MEMOINFO_STRUCT	*mMemoStruct;
	mMemoStruct = (MEMOINFO_STRUCT*)t_SelectNode->Data;
	if (!mMemoStruct) { return;	}

	if(mMemoStruct->X > 0 && mMemoStruct->Y > 0)
	{
		frmMain->m_nZoomFactor	= 9;
		frmMain->btnZoomTrackBar->Value = frmMain->m_nZoomFactor;

		//200117//금란과장님Req//아이콘표시 위치를 center -> 영역을 Center로 변경//
		int nIndex = frmMain->funcGetPolyIndex(mMemoStruct->POI_KEY);
		if(nIndex < 0)//포인트//
		{
			if(mMemoStruct->X < 0 || mMemoStruct->Y < 0)
			{
				frmMsg->funcMessageDlg("좌표 확인:", "좌표데이터에 문제가 있어 이동할 수 없습니다.", 3);
				return;
			}
			else
			{
				frmMain->m_geoCenterPoint.x = mMemoStruct->X;
				frmMain->m_geoCenterPoint.y = mMemoStruct->Y;
			}
		}
		else
		{
			frmMain->func_DrawPolygonMemoRectCenter(nIndex);
			if(frmMain->m_pgPolygonMemoRectCenter.x < 0 || frmMain->m_pgPolygonMemoRectCenter.y < 0)
			{
				frmMsg->funcMessageDlg("좌표 확인:", "좌표데이터에 문제가 있어 이동할 수 없습니다.", 3);
				return;
			}
			else
			{
				frmMain->m_geoCenterPoint.x = frmMain->m_pgPolygonMemoRectCenter.x;
				frmMain->m_geoCenterPoint.y = frmMain->m_pgPolygonMemoRectCenter.y;
			}
		}

		frmMain->m_nSelectMemoIndex = funcGetMemoIndex(mMemoStruct->POI_KEY);

		AnsiString temp;
		temp = mMemoStruct->TITLE;
		temp = "메모제목:" + temp;
		frmMain->funcSetStatusBarMsg(4, temp);

		if(frmMain->_CURRENT_WORKMODE == "DOCUMENT")
		{
			frmMain->IMGMODECHANGEClick(frmMain->IMGMODECHANGEJIJUK);
		}
		else
		{
			//지적도, 항공뷰, 지적도+항공뷰이면 그대로 표시//
			if(frmMain->IMGSCREEN1->Visible == false) frmMain->IMGSCREEN1->Visible = true;
			frmMain->func_DrawImagePaint();//
		}
	}
}
//---------------------------------------------------------------------------

int cTreeSystem::funcGetDognIndex(AnsiString _asKwonNo)
{
	int nSelectDognIndex = -1;

	for(int i = 0; i < (int)frmMain->m_ResultDocument18All.size(); i++)
	{
		if( !strcmp(frmMain->m_ResultDocument18All[i].KWON_NO, _asKwonNo.c_str()) )
		{
			if( !strcmp(frmMain->m_ResultDocument18All[i].KIND_CODE, "01") )//문서구분-좌표계산부//
			{
				nSelectDognIndex = i;
				break;
            }
		}
	}

	return nSelectDognIndex;
}
//---------------------------------------------------------------------------

int cTreeSystem::funcGetMemoIndex(AnsiString _asPoiKey)
{
	int nSelectMemoIndex = -1;

	for(int i = 0; i < (int)frmSql->m_vALLMEMOINFO.size(); i++)
	{
		if( !strcmp(frmSql->m_vALLMEMOINFO[i].POI_KEY, _asPoiKey.c_str()) )
		{
			nSelectMemoIndex = i;
			break;
		}
	}

	return nSelectMemoIndex;
}
//---------------------------------------------------------------------------

