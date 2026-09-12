//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

#include "FileCtrl.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma warn -8004


cFunc *eFunc;
//---------------------------------------------------------------------------
cFunc::cFunc()
{
}
//---------------------------------------------------------------------------
cFunc::~cFunc()
{
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcGetPageNo(AnsiString _asPage)
{
	AnsiString asReturnPage = _asPage;

	if( !_asPage.IsEmpty() && IsNumberString(_asPage) )
	{
		asReturnPage = IntToStr(_asPage.ToInt());
	}

	return asReturnPage;
}
//---------------------------------------------------------------------------

int cFunc::funcGetDocThumbPathListIndex(AnsiString _asPathName)
{
	AnsiString asStr = "";
	int nIndex = -1;

	for(int i = 0; i < (int)frmMain->m_vThumbPathList.size(); i++)
	{
		asStr = frmMain->m_vThumbPathList[i].PATH_NAME;
		if( _asPathName == asStr)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
//---------------------------------------------------------------------------

int cFunc::funcGetDocFTPPathListIndex(AnsiString _asPathName)
{
	AnsiString asStr = "";
	int nIndex = -1;

	for(int i = 0; i < (int)frmMain->m_vFTPPathList.size(); i++)
	{
		asStr = frmMain->m_vFTPPathList[i].PATH_NAME;
		if( _asPathName == asStr)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
//---------------------------------------------------------------------------

bool cFunc::funcCheckQueryCondition(int _nDocNo)
{
	//210115//#SEJONG_PNU
	if (frmMain->m_asSearchPnu.Length() != 19 && frmMain->_SIDOCODE == "36110" && frmMain->m_asSearchPnu.SubString(1, 5) != frmMain->_SIDOCODE)
	{
		return funcCheckQueryCondition36110(_nDocNo);
	}

	bool	bMsgInfo	= false;
	switch(_nDocNo)
	{
		case 1:
			if(frmMain->cboInputDoc1->ItemIndex <= 0
			 && frmMain->dtStartDayDoc1->Text == "    -  -  " && frmMain->dtEndDayDoc1->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "이동종목, 결의일자 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc1->SetFocus();//210215//
				return false;
			}
			break;
		case 2:
			if(frmMain->cboInputDoc2->ItemIndex <= 0 && frmMain->edtDohoDoc2->Text.Trim().Length() == 0
			 && frmMain->dtStartDayDoc2->Text == "    -  -  " && frmMain->dtEndDayDoc2->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "측량종목, 문서구분, 도호, 결의일자 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc2->SetFocus();//210215//
				return false;
			}
			break;
		case 3:
			if(frmMain->dtStartDayDoc3->Text == "    -  -  " && frmMain->dtEndDayDoc3->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "측량일자를 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;
				frmMain->dtStartDayDoc3->SetFocus();//210215//
				return false;
			}
			break;
		case 4:
//230502//천안시 특조법//				if(frmMain->cboKindDoc4->ItemIndex <= 0 && frmMain->edtRecNoDoc4->Text.Trim().Length() == 0 && frmMain->edtKwonNoDoc4->Text.Trim().Length() == 0)//190404
			if(frmMain->cboKindDoc4->ItemIndex <= 0 && frmMain->edtRecNoDoc4->Text.Trim().Length() == 0
			 && frmMain->edtKwonNoDoc4->Text.Trim().Length() == 0 && frmMain->edtNamesDoc4->Text.Trim().Length() == 0)//230502//천안시 특조법//
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 성명, 접수번호, 권번호 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc4->SetFocus();//210215//
				return false;
			}
			break;
		case 5:
			if(frmMain->cboInputDoc5->ItemIndex <= 0
			 && frmMain->dtStartDayDoc5->Text == "    -  -  " && frmMain->dtEndDayDoc5->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서종목, 결의일자 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->dtStartDayDoc5->SetFocus();//210215//
				return false;
			}
			break;
		case 6:
			if(frmMain->edtZoneNmDoc6->Text.Trim().Length() == 0 && frmMain->cboKindDoc6->ItemIndex <= 0 && frmMain->edtKwonNoDoc6->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "지구명, 문서구분, 롤 No 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtZoneNmDoc6->SetFocus();//210215//
				return false;
			}
			break;
		case 7:
//			if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty() || (frmMain->cboKindDoc7->ItemIndex <= 0 && frmMain->edtDohoDoc7->Text.Trim().Length() == 0 && frmMain->cboScaleDoc7->ItemIndex <= 0))
//			{
//				frmMsg->funcMessageDlg("최소선택알림:", "종이지적도 상세검색에서는 토지소재는 필수이고, 검색항목 중 한 가지 이상을 선택해주세요.", 3);
//				frmMain->m_bExceptingMainViewFocus	= true;//210215//
//				frmMain->cboKindDoc7->SetFocus();//210215//
//				return false;
//			}
			if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty())//241202//[REQ]아산시 이현종J요청//
			{
				frmMsg->funcMessageDlg("최소선택알림:", "종이지적도 상세검색에서는 토지소재를 필히 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc7->SetFocus();//210215//
				return false;
			}
			break;
		case 8:
//241202//구대장 상세검색 조건 정리
//231226//[구대장.문서구분]에서는 '전체'제거//
//260616//NotUsed//			if(frmMain->INI_B_OWNINFO)
			{
				if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty() || (frmMain->cboInputDoc8->ItemIndex <= 0 && frmMain->cboKindDoc8->ItemIndex == -1 && frmMain->edtNamesDoc8->Text.Length() == 0 && frmMain->edtNamesDoc8->Text.Trim().IsEmpty()) )
				{
					bMsgInfo	= true;
				}
			}
//260616//NotUsed//
/*			else
			{
				if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty() || (frmMain->cboInputDoc8->ItemIndex <= 0 && frmMain->cboKindDoc8->ItemIndex == -1 && frmMain->edtNamesDoc8->Text.Length() == 0) )
				{
					bMsgInfo	= true;
				}
			}
*/

			if(bMsgInfo)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "구대장 상세검색에서는 토지소재는 필수이고, 검색항목 중 한 가지 이상을 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc8->SetFocus();//210215//
				return false;
			}
			break;
		case 9:
			if(frmMain->cboKindDoc9->ItemIndex <= 0 && frmMain->edtYearDoc9->Text.Trim().Length() == 0 && frmMain->edtMonDoc9->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 기준년도, 기준월 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc9->SetFocus();//210215//
				return false;
			}
			break;
		case 11:
			if(frmMain->cboKindDoc11->ItemIndex <= 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분을 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc11->SetFocus();//210215//
				return false;
			}
			break;
		case 12:
			if(frmMain->edtDate12->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "등록일자를 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtDate12->SetFocus();//210215//
				return false;
			}
			break;
		case 13:
			if(frmMain->cboKindDoc13->ItemIndex <= 0 && frmMain->edtReqNoDoc13->Text.Trim().Length() == 0 && frmMain->edtOwnNmDoc13->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 신청자명, 신청번호, 롤단위 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc13->SetFocus();//210215//
				return false;
			}
			break;
		case 14:
			if(frmMain->cboInputDoc14->ItemIndex <= 0 && frmMain->edtKwonNoDoc14->Text.Trim().Length() == 0
			 && frmMain->dtStartDayDoc14->Text == "    -  -  " && frmMain->dtEndDayDoc14->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서종목, 롤단위, 결의일자 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc14->SetFocus();//210215//
				return false;
			}
			break;
		case 15:
			if(frmMain->edtRegNmDoc15->Text.Trim().Length() == 0 && frmMain->edtRegNoDoc15->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서번호, 등록명, 등록번호 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtRegNmDoc15->SetFocus();//210215//
				return false;
			}
			break;
		case 17:
			if(frmMain->cboKindDoc17->ItemIndex <= 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분을 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc17->SetFocus();//210215//
				return false;
			}
			break;
		case 18:
			if(frmMain->edtJigu18->Text.Trim() == "" && frmMain->edtDogn18->Text.Trim() != "" && IsNumberString( AnsiString(frmMain->edtDogn18->Text.Trim()) ) )
			{
				frmMsg->funcMessageDlg("데이터 입력 확인:", "도근명칭이 아닌 숫자만 입력하는 경우에는 지구명도 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtDogn18->SetFocus();
				return false;
			}
			if(frmMain->edtJigu18->Text.Trim().Length() == 0 && frmMain->edtDogn18->Text.Trim().Length() == 0
			 && frmMain->edtX18->Text.Trim().Length() == 0 && frmMain->edtY18->Text.Trim().Length() == 0
			 && frmMain->dtStartDayDoc18->Text == "    -  -  " && frmMain->dtEndDayDoc18->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "지구명, 도근점번호, 좌표, 검사일자  중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtJigu18->SetFocus();//210215//
				return false;
			}
			break;
//=============================================================================
//231021//GAGAMLAYER in LandArchive //here//
//=============================================================================
		case 20:
			if(frmMain->cboKindDoc20->ItemIndex < 1 && frmMain->edtYearDoc20->Text.Trim() == "" && frmMain->edtDocName20->Text.Trim() == "")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "상세검색 옵션 중 한 가지 이상 입력해주세요.", 3);
				frmMain->cboKindDoc20->SetFocus();
				return false;
			}
			break;
//=============================================================================
	}

	frmMain->m_bExceptingMainViewFocus	= false;//210215//
	return true;
}
//---------------------------------------------------------------------------

//210115//#SEJONG_PNU
bool cFunc::funcCheckQueryCondition36110(int _nDocNo)
{
	bool	bMsgInfo	= false;
	switch(_nDocNo)
	{
		case 1:
			if(frmMain->cboInputDoc1->ItemIndex <= 0
			 && frmMain->dtStartDayDoc1->Text == "    -  -  " && frmMain->dtEndDayDoc1->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "이동종목, 결의일자, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc1->SetFocus();//210215//
				return false;
			}
			break;
		case 2:
			if(frmMain->cboInputDoc2->ItemIndex <= 0 && frmMain->edtDohoDoc2->Text.Trim().Length() == 0
			 && frmMain->dtStartDayDoc2->Text == "    -  -  " && frmMain->dtEndDayDoc2->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "측량종목, 문서구분, 도호, 결의일자, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc2->SetFocus();//210215//
				return false;
			}
			break;
		case 3:
			if(frmMain->dtStartDayDoc3->Text == "    -  -  " && frmMain->dtEndDayDoc3->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "측량일자, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->dtStartDayDoc3->SetFocus();//210215//
				return false;
			}
			break;
		case 4:
//230502//천안시 특조법//if(frmMain->cboKindDoc4->ItemIndex <= 0 && frmMain->edtRecNoDoc4->Text.Trim().Length() == 0 && frmMain->edtKwonNoDoc4->Text.Trim().Length() == 0)//190404
			if(frmMain->cboKindDoc4->ItemIndex <= 0 && frmMain->edtRecNoDoc4->Text.Trim().Length() == 0
			&& frmMain->edtKwonNoDoc4->Text.Trim().Length() == 0 && frmMain->edtNamesDoc4->Text.Trim().Length() == 0)//230502//천안시 특조법//
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 성명, 접수번호, 권번호 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc4->SetFocus();//210215//
				return false;
			}
			break;
		case 5:
			if(frmMain->cboInputDoc5->ItemIndex <= 0
			 && frmMain->dtStartDayDoc5->Text == "    -  -  " && frmMain->dtEndDayDoc5->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서종목, 결의일자, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc5->SetFocus();//210215//
				return false;
			}
			break;
		case 6:
			if(frmMain->edtZoneNmDoc6->Text.Trim().Length() == 0 && frmMain->cboKindDoc6->ItemIndex <= 0 && frmMain->edtKwonNoDoc6->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "지구명, 문서구분, 롤 No, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtZoneNmDoc6->SetFocus();//210215//
				return false;
			}
			break;
		case 7:
//			if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty() || (frmMain->cboKindDoc7->ItemIndex <= 0 && frmMain->edtDohoDoc7->Text.Trim().Length() == 0 && frmMain->cboScaleDoc7->ItemIndex <= 0))
//			{
//				frmMsg->funcMessageDlg("최소선택알림:", "종이지적도 상세검색에서는 토지소재는 필수이고, 검색항목 중 한 가지 이상을 선택해주세요.", 3);
//				frmMain->m_bExceptingMainViewFocus	= true;//210215//
//				frmMain->cboKindDoc7->SetFocus();//210215//
//				return false;
//			}
			if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty())//241202//[REQ]아산시 이현종J요청//
			{
				frmMsg->funcMessageDlg("최소선택알림:", "종이지적도 상세검색에서는 토지소재를 필히 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc7->SetFocus();//210215//
				return false;
			}
			break;
		case 8:
//241202//구대장 상세검색 조건 정리
//231226//[구대장.문서구분]에서는 '전체'제거//
//260616//NotUsed//			if(frmMain->INI_B_OWNINFO)
			{
				if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty() || (frmMain->cboInputDoc8->ItemIndex <= 0 && frmMain->cboKindDoc8->ItemIndex == -1 && frmMain->edtNamesDoc8->Text.Length() == 0 && frmMain->edtNamesDoc8->Text.Trim().IsEmpty()) )
				{
					bMsgInfo	= true;
				}
			}
//260616//NotUsed//
/*			else
			{
				if(frmMain->edtUmdRiCd->Text.Trim().IsEmpty() || (frmMain->cboInputDoc8->ItemIndex <= 0 && frmMain->cboKindDoc8->ItemIndex == -1 && frmMain->edtNamesDoc8->Text.Length() == 0) )
				{
					bMsgInfo	= true;
				}
			}
*/

			if(bMsgInfo)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "구대장 상세검색에서는 토지소재는 필수이고, 검색항목 중 한 가지 이상을 선택해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc8->SetFocus();//210215//
				return false;
			}
			break;
		case 9:
			if(frmMain->cboKindDoc9->ItemIndex <= 0 && frmMain->edtYearDoc9->Text.Trim().Length() == 0 && frmMain->edtMonDoc9->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 기준년도, 기준월, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc9->SetFocus();//210215//
				return false;
			}
			break;
		case 11:
			if(frmMain->cboKindDoc11->ItemIndex <= 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc11->SetFocus();//210215//
				return false;
			}
			break;
		case 12:
			if(frmMain->edtDate12->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "등록일자, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtDate12->SetFocus();//210215//
				return false;
			}
			break;
		case 13:
			if(frmMain->cboKindDoc13->ItemIndex <= 0 && frmMain->edtReqNoDoc13->Text.Trim().Length() == 0 && frmMain->edtOwnNmDoc13->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 신청자명, 신청번호, 롤단위 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc13->SetFocus();//210215//
				return false;
			}
			break;
		case 14:
			if(frmMain->cboInputDoc14->ItemIndex <= 0 && frmMain->edtKwonNoDoc14->Text.Trim().Length() == 0
			 && frmMain->dtStartDayDoc14->Text == "    -  -  " && frmMain->dtEndDayDoc14->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서종목, 롤단위, 결의일자, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboInputDoc14->SetFocus();//210215//
				return false;
			}
			break;
		case 15:
			if(frmMain->edtRegNmDoc15->Text.Trim().Length() == 0 && frmMain->edtRegNoDoc15->Text.Trim().Length() == 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서번호, 등록명, 등록번호 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtRegNmDoc15->SetFocus();//210215//
				return false;
			}
			break;
		case 17:
			if(frmMain->cboKindDoc17->ItemIndex <= 0)
			{
				frmMsg->funcMessageDlg("최소선택알림:", "문서구분, 지번(토지소재) 중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->cboKindDoc17->SetFocus();//210215//
				return false;
			}
			break;
		case 18:
			if(frmMain->edtJigu18->Text.Trim() == "" && frmMain->edtDogn18->Text.Trim() != "" && IsNumberString( AnsiString(frmMain->edtDogn18->Text.Trim()) ) )
			{
				frmMsg->funcMessageDlg("데이터 입력 확인:", "도근명칭이 아닌 숫자만 입력하는 경우에는 지구명도 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtDogn18->SetFocus();
				return false;
			}
			if(frmMain->edtJigu18->Text.Trim().Length() == 0 && frmMain->edtDogn18->Text.Trim().Length() == 0
			 && frmMain->edtX18->Text.Trim().Length() == 0 && frmMain->edtY18->Text.Trim().Length() == 0
			 && frmMain->dtStartDayDoc18->Text == "    -  -  " && frmMain->dtEndDayDoc18->Text == "    -  -  ")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "지구명, 도근점번호, 좌표, 검사일자  중 한 가지 이상 입력해주세요.", 3);
				frmMain->m_bExceptingMainViewFocus	= true;//210215//
				frmMain->edtJigu18->SetFocus();//210215//
				return false;
			}
			break;
//=============================================================================
//231021//GAGAMLAYER in LandArchive //here//
//=============================================================================
		case 20:
			if(frmMain->cboKindDoc20->ItemIndex < 1 && frmMain->edtYearDoc20->Text.Trim() == "" && frmMain->edtDocName20->Text.Trim() != "")
			{
				frmMsg->funcMessageDlg("최소선택알림:", "상세검색 옵션 중 한 가지 이상 입력해주세요.", 3);
				frmMain->cboKindDoc20->SetFocus();
				return false;
			}
			break;
//=============================================================================
	}

	frmMain->m_bExceptingMainViewFocus	= true;//210215//
	return true;
}
//---------------------------------------------------------------------------
void cFunc::funcCheckDateCondition(int _nDocNo)
{
	switch(_nDocNo)
	{
		case 1:
			if(frmMain->dtStartDayDoc1->Focused())
				frmMain->edtDate_OnExit(frmMain->dtStartDayDoc1);
			break;
		case 2:
			if(frmMain->dtStartDayDoc2->Focused())
				frmMain->edtDate_OnExit(frmMain->dtStartDayDoc2);
			break;
		case 3:
			if(frmMain->dtStartDayDoc3->Focused())
				frmMain->edtDate_OnExit(frmMain->dtStartDayDoc3);
			break;
		case 5:
			if(frmMain->dtStartDayDoc5->Focused())
				frmMain->edtDate_OnExit(frmMain->dtStartDayDoc5);
			break;
		case 14:
			if(frmMain->dtStartDayDoc14->Focused())
				frmMain->edtDate_OnExit(frmMain->dtStartDayDoc14);
			break;
		case 18:
			if(frmMain->dtStartDayDoc18->Focused())
				frmMain->edtDate_OnExit(frmMain->dtStartDayDoc18);
			break;
	}
}
//---------------------------------------------------------------------------

int cFunc::funcGetKindCodeToKindIndex(int _nType, char *_cKindCode)
{
	int	nIndex = -1;

	switch (_nType) {
		case 1:
			for (int j=0; j<(int)frmMain->m_BASECODE_001_DOC1.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_001_DOC1[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 2:
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_002_DOC2[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 3:
			for (int j=0; j<(int)frmMain->m_BASECODE_003_DOC3.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_003_DOC3[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 4:
			for (int j=0; j<(int)frmMain->m_BASECODE_004_DOC4.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_004_DOC4[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 6:
			for (int j=0; j<(int)frmMain->m_BASECODE_006_DOC6.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_006_DOC6[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 7:
			for (int j=0; j<(int)frmMain->m_BASECODE_007_DOC7.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_007_DOC7[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 8:
			for (int j=0; j<(int)frmMain->m_BASECODE_008_DOC8.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_008_DOC8[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 9:
			for (int j=0; j<(int)frmMain->m_BASECODE_009_DOC9.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_009_DOC9[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 11:
			for (int j=0; j<(int)frmMain->m_BASECODE_011_DOC11.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_011_DOC11[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 12:
			for (int j=0; j<(int)frmMain->m_BASECODE_012_DOC12.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_012_DOC12[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 13:
			for (int j=0; j<(int)frmMain->m_BASECODE_042_DOC13.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_042_DOC13[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 15:
			for (int j=0; j<(int)frmMain->m_BASECODE_015_DOC15.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_015_DOC15[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 17:
			for (int j=0; j<(int)frmMain->m_BASECODE_017_DOC17.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_017_DOC17[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 18:
			for (int j=0; j<(int)frmMain->m_BASECODE_018_DOC18.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_018_DOC18[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
//=============================================================================
//231021//GAGAMLAYER in LandArchive //here//
//=============================================================================
		case 20:
			for (int j=0; j<(int)frmMain->m_BASECODE_020_DOC20.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_020_DOC20[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
//=============================================================================
		case 101:
			for (int j=0; j<(int)frmMain->m_BASECODE_101_DOC1.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_101_DOC1[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 102:
			for (int j=0; j<(int)frmMain->m_BASECODE_102_DOC2.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_102_DOC2[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;

		case 109:
			for (int j=0; j<(int)frmMain->m_BASECODE_109_DOC5.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_109_DOC5[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 111:
			for (int j=0; j<(int)frmMain->m_BASECODE_111_DOC14.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_111_DOC14[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 502:
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_SCALERESULT.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_vDATA_BASECODE_SCALERESULT[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 503://210303//#503
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_503.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_vDATA_BASECODE_503[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 801://200608
			for (int j=0; j<(int)frmMain->m_BASECODE_801_DOC8.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_801_DOC8[j].kind_code) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 906:
			for (int j=0; j<(int)frmMain->m_vDATA_ZONECODE.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_vDATA_ZONECODE[j].zonecode) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;


		default:
			break;
	}
	return nIndex;

}
//---------------------------------------------------------------------------
AnsiString cFunc::funcGetKindCodeToKindName(int _nType, char *_cKindCode)
{
	AnsiString asStr = "기타";//201015//금란과장님Req//"...";
//	AnsiString aaStr = "***";
//	AnsiString bbStr = "***";
	AnsiString ntype = _nType;

	switch (_nType) {
		case 1:
			for (int j=0; j<(int)frmMain->m_BASECODE_001_DOC1.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_001_DOC1[j].kind_code) == 0)
				{

					asStr = frmMain->m_BASECODE_001_DOC1[j].kind_name;
					break;
				}
			}
			break;
		case 2:
			asStr = "측량";
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_002_DOC2[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_002_DOC2[j].kind_name;
					break;
				}
			}
			break;
		case 3:
			asStr = "면적";
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_002_DOC2[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_002_DOC2[j].kind_name;
					break;
				}
			}
			break;
		case 4:
			for (int j=0; j<(int)frmMain->m_BASECODE_004_DOC4.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_004_DOC4[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_004_DOC4[j].kind_name;
					break;
				}
			}
			break;
		case 6:
			for (int j=0; j<(int)frmMain->m_BASECODE_006_DOC6.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_006_DOC6[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_006_DOC6[j].kind_name;
					break;
				}
			}
			break;
		case 7:
			for (int j=0; j<(int)frmMain->m_BASECODE_007_DOC7.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_007_DOC7[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_007_DOC7[j].kind_name;
					break;
				}
			}
			break;
		case 8:
			for (int j=0; j<(int)frmMain->m_BASECODE_008_DOC8.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_008_DOC8[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_008_DOC8[j].kind_name;
					break;
				}
			}
			break;
		case 9:
			for (int j=0; j<(int)frmMain->m_BASECODE_009_DOC9.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_009_DOC9[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_009_DOC9[j].kind_name;
					break;
				}
			}
			break;
		case 11:
			for (int j=0; j<(int)frmMain->m_BASECODE_011_DOC11.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_011_DOC11[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_011_DOC11[j].kind_name;
					break;
				}
			}
			break;
		case 12:
			for (int j=0; j<(int)frmMain->m_BASECODE_012_DOC12.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_012_DOC12[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_012_DOC12[j].kind_name;
					break;
				}
			}
			break;
		case 13:
			for (int j=0; j<(int)frmMain->m_BASECODE_042_DOC13.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_042_DOC13[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_042_DOC13[j].kind_name;
					break;
				}
			}
			break;
		case 15:
			for (int j=0; j<(int)frmMain->m_BASECODE_015_DOC15.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_015_DOC15[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_015_DOC15[j].kind_name;
					break;
				}
			}
			break;
		case 17:
			for (int j=0; j<(int)frmMain->m_BASECODE_017_DOC17.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_017_DOC17[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_017_DOC17[j].kind_name;
					break;
				}
			}
			break;
		case 18:
			for (int j=0; j<(int)frmMain->m_BASECODE_018_DOC18.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_018_DOC18[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_018_DOC18[j].kind_name;
					break;
				}
			}
			break;
//=============================================================================
//231021//GAGAMLAYER in LandArchive //here//
//=============================================================================
		case 20:
			for (int j=0; j<(int)frmMain->m_BASECODE_020_DOC20.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_020_DOC20[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_020_DOC20[j].kind_name;
					break;
				}
			}
			break;
//=============================================================================
		case 101:
			for (int j=0; j<(int)frmMain->m_BASECODE_101_DOC1.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_101_DOC1[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_101_DOC1[j].kind_name;
					break;
				}
			}
			break;
		case 102:
			for (int j=0; j<(int)frmMain->m_BASECODE_102_DOC2.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_102_DOC2[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_102_DOC2[j].kind_name;
					break;
				}
			}
			break;
		case 109:
			for (int j=0; j<(int)frmMain->m_BASECODE_109_DOC5.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_109_DOC5[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_109_DOC5[j].kind_name;
					break;
				}
			}
			break;
		case 111:
			for (int j=0; j<(int)frmMain->m_BASECODE_111_DOC14.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_111_DOC14[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_111_DOC14[j].kind_name;
					break;
				}
			}
			break;
		case 502:
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_SCALERESULT.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_vDATA_BASECODE_SCALERESULT[j].kind_code) == 0)
				{
					asStr = frmMain->m_vDATA_BASECODE_SCALERESULT[j].kind_name;
					break;
				}
			}
			break;
		case 503://210303//#503
			asStr	= "";
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_503.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_vDATA_BASECODE_503[j].kind_code) == 0)
				{
					asStr = frmMain->m_vDATA_BASECODE_503[j].kind_name;
					break;
				}
			}
			break;
		case 801://200608
			asStr	= "";
			for (int j=0; j<(int)frmMain->m_BASECODE_801_DOC8.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_BASECODE_801_DOC8[j].kind_code) == 0)
				{
					asStr = frmMain->m_BASECODE_801_DOC8[j].kind_name;
					break;
				}
			}
			break;
		case 906://ZONE_CODE
			for (int j=0; j<(int)frmMain->m_vDATA_ZONECODE.size(); j++)
			{
				if (strcmp(_cKindCode, frmMain->m_vDATA_ZONECODE[j].zonecode) == 0)
				{
					asStr = frmMain->m_vDATA_ZONECODE[j].zonename;
					break;
				}
			}
			if(asStr.IsEmpty())//200226
				asStr = "-";
			break;
		default:
			break;
	}
	return asStr;
}
//---------------------------------------------------------------------------
//===========================================================================
// KIND_NAME으로 KIND_CODE 찾기//
//===========================================================================
AnsiString cFunc::funcGetKindNameToKindCode(int _nType, char *_cKindName)
{
	AnsiString asStr = "";

	switch (_nType) {
		case 1:
			for (int j=0; j<(int)frmMain->m_BASECODE_001_DOC1.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_001_DOC1[j].kind_name) == 0)
				{

					asStr = frmMain->m_BASECODE_001_DOC1[j].kind_code;
					break;
				}
			}
			break;
		case 2:
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_002_DOC2[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_002_DOC2[j].kind_code;
					break;
				}
			}
			break;
		case 3:
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_002_DOC2[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_002_DOC2[j].kind_code;
					break;
				}
			}
			break;
		case 4:
			for (int j=0; j<(int)frmMain->m_BASECODE_004_DOC4.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_004_DOC4[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_004_DOC4[j].kind_code;
					break;
				}
			}
			break;
		case 6:
			for (int j=0; j<(int)frmMain->m_BASECODE_006_DOC6.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_006_DOC6[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_006_DOC6[j].kind_code;
					break;
				}
			}
			break;
		case 7:
			for (int j=0; j<(int)frmMain->m_BASECODE_007_DOC7.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_007_DOC7[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_007_DOC7[j].kind_code;
					break;
				}
			}
			break;
		case 8:
			for (int j=0; j<(int)frmMain->m_BASECODE_008_DOC8.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_008_DOC8[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_008_DOC8[j].kind_code;
					break;
				}
			}
			break;
		case 9:
			for (int j=0; j<(int)frmMain->m_BASECODE_009_DOC9.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_009_DOC9[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_009_DOC9[j].kind_code;
					break;
				}
			}
			break;
		case 11:
			for (int j=0; j<(int)frmMain->m_BASECODE_011_DOC11.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_011_DOC11[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_011_DOC11[j].kind_code;
					break;
				}
			}
			break;
		case 12:
			for (int j=0; j<(int)frmMain->m_BASECODE_012_DOC12.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_012_DOC12[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_012_DOC12[j].kind_code;
					break;
				}
			}
			break;
		case 13:
			for (int j=0; j<(int)frmMain->m_BASECODE_042_DOC13.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_042_DOC13[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_042_DOC13[j].kind_code;
					break;
				}
			}
			break;
		case 15:
			for (int j=0; j<(int)frmMain->m_BASECODE_015_DOC15.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_015_DOC15[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_015_DOC15[j].kind_code;
					break;
				}
			}
			break;
		case 17:
			for (int j=0; j<(int)frmMain->m_BASECODE_017_DOC17.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_017_DOC17[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_017_DOC17[j].kind_code;
					break;
				}
			}
			break;
		case 18:
			for (int j=0; j<(int)frmMain->m_BASECODE_018_DOC18.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_018_DOC18[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_018_DOC18[j].kind_code;
					break;
				}
			}
			break;
//=============================================================================
//231021//GAGAMLAYER in LandArchive //here//
//=============================================================================
		case 20:
			for (int j=0; j<(int)frmMain->m_BASECODE_020_DOC20.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_020_DOC20[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_020_DOC20[j].kind_code;
					break;
				}
			}
			break;
//=============================================================================
		case 101:
			for (int j=0; j<(int)frmMain->m_BASECODE_101_DOC1.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_101_DOC1[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_101_DOC1[j].kind_code;
					break;
				}
			}
			break;
		case 102:
			for (int j=0; j<(int)frmMain->m_BASECODE_102_DOC2.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_102_DOC2[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_102_DOC2[j].kind_code;
					break;
				}
			}
			break;
		case 109:
			for (int j=0; j<(int)frmMain->m_BASECODE_109_DOC5.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_109_DOC5[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_109_DOC5[j].kind_code;
					break;
				}
			}
			break;
		case 111:
			for (int j=0; j<(int)frmMain->m_BASECODE_111_DOC14.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_111_DOC14[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_111_DOC14[j].kind_code;
					break;
				}
			}
			break;
		case 502:
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_SCALERESULT.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_vDATA_BASECODE_SCALERESULT[j].kind_name) == 0)
				{
					asStr = frmMain->m_vDATA_BASECODE_SCALERESULT[j].kind_code;
					break;
				}
			}
			break;
		case 503://210303//#503
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_503.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_vDATA_BASECODE_503[j].kind_name) == 0)
				{
					asStr = frmMain->m_vDATA_BASECODE_503[j].kind_code;
					break;
				}
			}
			break;
		case 801:
			for (int j=0; j<(int)frmMain->m_BASECODE_801_DOC8.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_801_DOC8[j].kind_name) == 0)
				{
					asStr = frmMain->m_BASECODE_801_DOC8[j].kind_code;
					break;
				}
			}
			break;
		case 906://ZONE_CODE
			for (int j=0; j<(int)frmMain->m_vDATA_ZONECODE.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_vDATA_ZONECODE[j].zonename) == 0)
				{
					asStr = frmMain->m_vDATA_ZONECODE[j].zonecode;
					break;
				}
			}
			break;
		default:
			break;
	}
	return asStr;
}
//---------------------------------------------------------------------------
//201214//
int cFunc::funcGetKindNameToKindIndex(int _nType, char *_cKindName)
{
	int	nIndex = -1;

	switch (_nType) {
		case 1:
			for (int j=0; j<(int)frmMain->m_BASECODE_001_DOC1.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_001_DOC1[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 2:
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_002_DOC2[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 3:
			for (int j=0; j<(int)frmMain->m_BASECODE_002_DOC2.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_002_DOC2[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 4:
			for (int j=0; j<(int)frmMain->m_BASECODE_004_DOC4.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_004_DOC4[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 6:
			for (int j=0; j<(int)frmMain->m_BASECODE_006_DOC6.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_006_DOC6[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 7:
			for (int j=0; j<(int)frmMain->m_BASECODE_007_DOC7.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_007_DOC7[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 8:
			for (int j=0; j<(int)frmMain->m_BASECODE_008_DOC8.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_008_DOC8[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 9:
			for (int j=0; j<(int)frmMain->m_BASECODE_009_DOC9.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_009_DOC9[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 11:
			for (int j=0; j<(int)frmMain->m_BASECODE_011_DOC11.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_011_DOC11[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 12:
			for (int j=0; j<(int)frmMain->m_BASECODE_012_DOC12.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_012_DOC12[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 13:
			for (int j=0; j<(int)frmMain->m_BASECODE_042_DOC13.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_042_DOC13[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 15:
			for (int j=0; j<(int)frmMain->m_BASECODE_015_DOC15.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_015_DOC15[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 17:
			for (int j=0; j<(int)frmMain->m_BASECODE_017_DOC17.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_017_DOC17[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 18:
			for (int j=0; j<(int)frmMain->m_BASECODE_018_DOC18.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_018_DOC18[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
//=============================================================================
//231021//GAGAMLAYER in LandArchive
//=============================================================================
		case 20:
			for (int j=0; j<(int)frmMain->m_BASECODE_020_DOC20.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_020_DOC20[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
//=============================================================================
		case 101:
			for (int j=0; j<(int)frmMain->m_BASECODE_101_DOC1.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_101_DOC1[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 102:
			for (int j=0; j<(int)frmMain->m_BASECODE_102_DOC2.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_102_DOC2[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 109:
			for (int j=0; j<(int)frmMain->m_BASECODE_109_DOC5.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_109_DOC5[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 111:
			for (int j=0; j<(int)frmMain->m_BASECODE_111_DOC14.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_111_DOC14[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 502:
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_SCALERESULT.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_vDATA_BASECODE_SCALERESULT[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 503://210303//#503
			for (int j=0; j<(int)frmMain->m_vDATA_BASECODE_503.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_vDATA_BASECODE_503[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 801:
			for (int j=0; j<(int)frmMain->m_BASECODE_801_DOC8.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_BASECODE_801_DOC8[j].kind_name) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		case 906://ZONE_CODE
			for (int j=0; j<(int)frmMain->m_vDATA_ZONECODE.size(); j++)
			{
				if (strcmp(_cKindName, frmMain->m_vDATA_ZONECODE[j].zonename) == 0)
				{
					nIndex = j;
					break;
				}
			}
			break;
		default:
			break;
	}
	return nIndex;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcGetPageNoName(int nDocNo, char *_cPageNo)
{
	AnsiString asPageNo = _cPageNo;
	AnsiString asStr    = "";

	int nLen = asPageNo.Length();

	if( !IsNumberString(asPageNo) )
	{
		asPageNo	= asPageNo.SubString(2, nLen - 1);//Doc15, 맨 앞자리 영문인 경우가 있다//
		if( !IsNumberString(asPageNo) )
			return asStr;

		nLen	= asPageNo.Length();
	}

	//Page가 안나오는 시군의 문서는 DB에서 맞춤 작업을 해줘야 함. 더이상 프로그램 수정하지 않기!!!
	if(nLen >= 2)
	{
		int nFront = StrToInt(asPageNo.SubString(1,nLen-1));
		int nBack  = StrToInt(asPageNo.SubString(nLen,1));
		if(nBack == 0)
			asStr.sprintf("%d", nFront);
		else
			asStr.sprintf("%d-%d", nFront, nBack);
	}

	return asStr;
}

//---------------------------------------------------------------------------

AnsiString cFunc::funcGetKindCode(AnsiString _asTaskCode, AnsiString _asKindName)
{
	AnsiString asKindCode = "";

	if(_asTaskCode == "007")//지적도 Task_Code
	{
		for(int i = 0; i < (int)frmMain->m_BASECODE_007_DOC7.size(); i++)
		{
			if(strcmp(frmMain->m_BASECODE_007_DOC7[i].kind_name, _asKindName.c_str()) == 0)
			{
				asKindCode = frmMain->m_BASECODE_007_DOC7[i].kind_code;
				break;
			}
		}
	}

	//
	//[TODO] 다른 코드들도 추가
	//

	return asKindCode;
}
//---------------------------------------------------------------------------

void cFunc::funcDeleteDir(bool _bDelDir, AnsiString _asDir)
{
	if(!DirectoryExists(_asDir))
		return;

	if(_asDir.SubString(_asDir.Length(), 1) == "\\")
		_asDir = _asDir.SubString(1, _asDir.Length()-1);

	DeleteFileinDir(_asDir);

	if(_bDelDir)//201214//
		RemoveDirectory(_asDir.c_str());
}
//---------------------------------------------------------------------------
void cFunc::DeleteFileinDir(AnsiString Dir)
{
	TSearchRec sr;
	AnsiString iDir; //GetDirView()내에서만 사용할 패스변수 선언
	int iAttributes 	= 0;
	int nIndex 			= 0;
	DWORD dwFileSize 	= 0;
	char cFileSize[255];
	AnsiString asPathName = "";

	iAttributes |= faReadOnly * 0; //파일 옵션
	iAttributes |= faHidden * 0;
	iAttributes |= faSysFile * 0;
//	iAttributes |= faVolumeID * 0;
	iAttributes |= faDirectory * 0;
	iAttributes |= faArchive * 0;
	iAttributes |= faAnyFile * 1;

	iDir = Dir; //인자로 받아온 패스를 iDir에 저장
	int len=iDir.Length();
	if(iDir[len]=='\\')   //iDir의 마지막 문자가 '\\'인지 아닌지
		iDir += "*.*";
	else
		iDir += "\\*.*";


	if (FindFirst(iDir, iAttributes, sr) == 0) //찾는 파일이 있으면..
	{
		do{
			if ((sr.Attr & faDirectory) == 0)//찾은 파일이 디렉토리가 아니면..
			{
				asPathName = Dir + "\\" + sr.Name;
				DeleteFile(asPathName);
			}
			else{
				if (sr.Name != "." && sr.Name != ".."){ // ".", ".." 두 디렉토리는 출력에서 제외시킴
					AnsiString subDir;
					subDir = Dir;
					subDir = subDir+"\\";
					subDir += sr.Name;
					DeleteFileinDir(subDir);
					RemoveDirectory(subDir.c_str());
				}
			}
		}while(FindNext(sr) == 0); //다음 파일찾기, 다음찾은 파일이 없을때까지 do-while문 반복
	}
	FindClose(sr);
}
//---------------------------------------------------------------------------
//201203//
void cFunc::GetDirView(AnsiString Dir)
{
	TSearchRec sr;
	AnsiString iDir; //GetDirView()내에서만 사용할 패스변수 선언
	int iAttributes 	= 0;
	int nIndex 			= 0;
	DWORD dwFileSize 	= 0;
	char cFileSize[255];
	String	asTgtDir	= "";
	int			  nPos 	= 0;
	AnsiString  asExt	= ".jpg";

	AnsiString asFilePath = "";
	AnsiString asOrgFilePath	= "";

	iAttributes |= faReadOnly * 0; //파일 옵션
	iAttributes |= faHidden * 0;
	iAttributes |= faSysFile * 0;
//	iAttributes |= faVolumeID * 0;
	iAttributes |= faDirectory * 0;
	iAttributes |= faArchive * 0;
	iAttributes |= faAnyFile * 1;

	iDir = Dir; //인자로 받아온 패스를 iDir에 저장
	int len=iDir.Length();
	if(iDir[len]=='\\')   //iDir의 마지막 문자가 '\\'인지 아닌지
		iDir += "*.*";
	else
		iDir += "\\*.*";


	if (FindFirst(iDir, iAttributes, sr) == 0) //찾는 파일이 있으면..
	{
		do{
			if ((sr.Attr & faDirectory) == 0)//찾은 파일이 디렉토리가 아니면..
			{
				asFilePath = Dir + "\\" + sr.Name;

				if(asFilePath.UpperCase().Pos(".JPG") == 0)
					continue;

				if(asFilePath.UpperCase().Pos("F") == 0)
				{
					asOrgFilePath	= frmMain->ROOTPATH + "Images\\upper.jpg";
					CopyFile(asFilePath.c_str(), asOrgFilePath.c_str(), false);
				}
				else if(asFilePath.UpperCase().Pos("B") == 0)
				{
					asOrgFilePath	= frmMain->ROOTPATH + "Images\\bottom.jpg";
					CopyFile(asFilePath.c_str(), asOrgFilePath.c_str(), false);
				}
			}
			else{
				if (sr.Name != "." && sr.Name != ".."){ // ".", ".." 두 디렉토리는 출력에서 제외시킴
					AnsiString subDir;
					subDir = Dir;
					subDir = subDir+"\\";
					subDir += sr.Name;
					GetDirView(subDir);
				}
			}
		}while(FindNext(sr) == 0); //다음 파일찾기, 다음찾은 파일이 없을때까지 do-while문 반복
	}

	FindClose(sr);
}
//---------------------------------------------------------------------------


bool cFunc::IsNumberString(AnsiString str)
{
	if(str.IsEmpty())//260615//
		return false;

    char *s=str.c_str();
    if(*s=='-' ||*s=='+')s++;
	while(*s)
    {
        if(*s<'0' || *s>'9')return false;
          s++;
    }
    return true;
}
//---------------------------------------------------------------------------

bool cFunc::IsAreaString(AnsiString str)
{
	bool bDot = false;
    char *s=str.c_str();
    if(*s=='-' ||*s=='+')s++;
	while(*s)
	{
		if( *s == '.')
		{
			if( !bDot )
			{
				bDot = true;
				s++;
				continue;
			}
			else
				return false;
		}
		if(*s<'0' || *s>'9')return false;
          s++;
    }
    return true;
}
//---------------------------------------------------------------------------

bool cFunc::funcCheckDate(String _sDate)
{
	AnsiString asDate = _sDate;

	asDate	= StringReplace(asDate, " ", "", TReplaceFlags() << rfReplaceAll);//210108//

	if(asDate.Length() != 10)
		return false;

	int nYear = asDate.SubString(1, 4).ToInt();
	int nMonth = asDate.SubString(6, 2).ToInt();
	int nDay = asDate.SubString(9, 2).ToInt();

	if(nYear < 1900 || nYear > 2100)
		return false;
	if(nMonth < 1 || nMonth > 12)
		return false;
   	if ((nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth ==
			8 || nMonth == 10 || nMonth == 12) && (nDay < 1 || nDay > 31))
		return false;
	if ((nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11) &&
		(nDay < 1 || nDay > 30))
		return false;
	if (nMonth == 2 && nYear % 4 && (nDay < 1 || nDay > 28))
		return false;
	if (nMonth == 2 && !(nYear % 4) && (nDay < 1 || nDay > 29)) // 2월 윤달
		return false;

	return true;
}
//---------------------------------------------------------------------------

bool cFunc::funcCheckDate2(int nType, String _sDate)
{
	AnsiString asDate 	= _sDate;
	AnsiString asStr	= "";

	asDate = StringReplace(asDate, "-", "", TReplaceFlags() << rfReplaceAll);

	int nYear 	= 0;
	int nMonth 	= 0;
	int nDay 	= 0;

	if(nType == 1)//YYYY
	{
		if(asDate.Length() < 4)
			return false;

		nYear = asDate.SubString(1, 4).ToInt();
		if(nYear < 1900 || nYear > 2100)
			return false;
	}
	else if(nType == 2)//YYYYMM
	{
		if(asDate.Length() < 6)
			return false;

		asStr = asDate.SubString(1, 4);
		asStr = StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
		nYear = asStr.ToInt();
		if(nYear < 1900 || nYear > 2100)
			return false;

		asStr = asDate.SubString(5, 2);
		asStr = StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
		nMonth = asStr.ToInt();
		if(nMonth < 1 || nMonth > 12)
			return false;
	}
	else if(nType == 3)//YYYYMMDD
	{
		if(asDate.Length() < 8)
			return false;

		asStr = asDate.SubString(1, 4);
		asStr = StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
		nYear = asStr.ToInt();
		if(nYear < 1900 || nYear > 2100)
			return false;

		asStr = asDate.SubString(5, 2);
		asStr = StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
		nMonth = asStr.ToInt();
		if(nMonth < 1 || nMonth > 12)
			return false;

		asStr = asDate.SubString(7, 2);
		asStr = StringReplace(asStr, " ", "", TReplaceFlags() << rfReplaceAll);
		nDay = asStr.ToInt();
		if ((nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth ==
				8 || nMonth == 10 || nMonth == 12) && (nDay < 1 || nDay > 31))
			return false;
		if ((nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11) &&
			(nDay < 1 || nDay > 30))
			return false;
		if (nMonth == 2 && nYear % 4 && (nDay < 1 || nDay > 28))
			return false;
		if (nMonth == 2 && !(nYear % 4) && (nDay < 1 || nDay > 29)) // 2월 윤달
			return false;
	}

	return true;
}
//---------------------------------------------------------------------------


bool cFunc::funcCheckMonth(String _sDate)
{
	AnsiString asDate = _sDate;
	if(asDate.Length() != 7)
		return false;

	int nYear = asDate.SubString(1, 4).ToInt();
	int nMonth = asDate.SubString(6, 2).ToInt();

	if(nYear < 1900 || nYear > 2100)
		return false;
	if(nMonth < 1 || nMonth > 12)
		return false;

	return true;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcPnuToBonbuName(AnsiString _asPnu, int _nType)
{
	AnsiString asGbn;
	AnsiString asBon;
	AnsiString asBu;
	AnsiString asStr = "";

	char cInput[32];

	if(_asPnu.Length() != 19)//201016//
		return asStr;

	asGbn = _asPnu.SubString(11, 1);
	asBon = _asPnu.SubString((19-8+1), 4);
	asBu = _asPnu.SubString((19-4+1), 4);
	if (asBon.IsEmpty()) asBon = "0";
	//200306//부번없으면 텍스트채우지말것//if (asBu.IsEmpty()) asBu = "0";

	if (asBu.IsEmpty() || asBu.ToInt() == 0)
	{
		if (asGbn == "2")
		{
			if(_nType == 0)
				asStr.printf("산 %d", StrToInt(asBon));
			else if(_nType == 1)
				asStr.printf("산 %d<이동전>", StrToInt(asBon));
			else if(_nType == 2)
				asStr.printf("산 %d<이동후>", StrToInt(asBon));
		}
		else
		{
			if(_nType == 0)
				asStr.printf("%d", StrToInt(asBon));
			else if(_nType == 1)
				asStr.printf("%d<이동전>", StrToInt(asBon));
			else if(_nType == 2)
				asStr.printf("%d<이동후>", StrToInt(asBon));
		}
	}
	else
	{
		if (asGbn == "2")
		{
			if(_nType == 0)
				asStr.printf("산 %d-%d", StrToInt(asBon), StrToInt(asBu));
			else if(_nType == 1)
				asStr.printf("산 %d-%d<이동전>", StrToInt(asBon), StrToInt(asBu));
			else if(_nType == 2)
				asStr.printf("산 %d-%d<이동후>", StrToInt(asBon), StrToInt(asBu));
		}
		else
		{
			if(_nType == 0)
				asStr.printf("%d-%d", StrToInt(asBon), StrToInt(asBu));
			else if(_nType == 1)
				asStr.printf("%d-%d<이동전>", StrToInt(asBon), StrToInt(asBu));
			else if(_nType == 2)
				asStr.printf("%d-%d<이동후>", StrToInt(asBon), StrToInt(asBu));
		}
	}

	return asStr;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcPnuToBonbuName2(AnsiString _asPnu, int _nType)
{
	AnsiString asPnu;
	AnsiString asGbn;
	AnsiString asBon;
	AnsiString asBu;
	AnsiString asStr = "";

	char cInput[32];

	if (_asPnu.Length() == 19)
	{
		asGbn = _asPnu.SubString(11, 1);
		asBon = _asPnu.SubString((19-8+1), 4);
		asBu  = _asPnu.SubString((19-4+1), 4);
		if (asBon.IsEmpty()) asBon = "0";
		if (asBu.IsEmpty()) asBu = "0";

		AnsiString asResult = "";

		if(_nType == 3)
		{
			asResult = funcPnuToUMDRIName(_asPnu.c_str(), true);
			_nType = 0;
		}
		else
		{
			asResult = funcPnuToUMDRIName(_asPnu.c_str(), false);
		}

		if (asBu.IsEmpty() || asBu.ToInt() == 0)
		{
			if (asGbn == "2")
			{
				if(_nType == 0)
					asStr.printf("%s 산 %d", asResult, StrToInt(asBon));
				else if(_nType == 1)
					asStr.printf("%s 산 %d[이동전]", asResult, StrToInt(asBon));
				else if(_nType == 2)
					asStr.printf("%s 산 %d-[이동후]", asResult, StrToInt(asBon));
				else if(_nType == 4)//190429//Doc02Attach
					asStr.printf("산 %d", StrToInt(asBon));
			}
			else
			{
				if(_nType == 0)
					asStr.printf("%s %d", asResult, StrToInt(asBon));
				else if(_nType == 1)
					asStr.printf("%s %d[이동전]", asResult, StrToInt(asBon));
				else if(_nType == 2)
					asStr.printf("%s %d[이동후]", asResult, StrToInt(asBon));
				else if(_nType == 4)//190429//Doc02Attach
					asStr.printf("%d", StrToInt(asBon));
			}
		}
		else
		{
			if (asGbn == "2")
			{
				if(_nType == 0)
					asStr.printf("%s 산 %d-%d", asResult, StrToInt(asBon), StrToInt(asBu));
				else if(_nType == 1)
					asStr.printf("%s 산 %d-%d[이동전]", asResult, StrToInt(asBon), StrToInt(asBu));
				else if(_nType == 2)
					asStr.printf("%s 산 %d-%d[이동후]", asResult, StrToInt(asBon), StrToInt(asBu));
				else if(_nType == 4)//190429//Doc02Attach
					asStr.printf("산 %d-%d", StrToInt(asBon), StrToInt(asBu));
			}
			else
			{
				if(_nType == 0)
					asStr.printf("%s %d-%d", asResult, StrToInt(asBon), StrToInt(asBu));
				else if(_nType == 1)
					asStr.printf("%s %d-%d[이동전]", asResult, StrToInt(asBon), StrToInt(asBu));
				else if(_nType == 2)
					asStr.printf("%s %d-%d[이동후]", asResult, StrToInt(asBon), StrToInt(asBu));
				else if(_nType == 4)//190429//Doc02Attach
					asStr.printf("%d-%d", StrToInt(asBon), StrToInt(asBu));
			}
		}
	}

	return asStr;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcPnuToSGGName(char* _cPnu)
{
	AnsiString asPnu    = "";
	AnsiString asSggCd  = "";
	AnsiString asSggCd_ = "";
	AnsiString asStr    = "";

	asPnu   = _cPnu;
	asSggCd = asPnu.SubString(1, 5);

	for (int i=0; i<(int)frmMain->m_vDATA_SIDOCODE.size(); i++)
	{
		asSggCd_ = frmMain->m_vDATA_SIDOCODE[i].cSggCd;

		if (asSggCd == asSggCd_)
		{
			asStr.printf("%s", frmMain->m_vDATA_SIDOCODE[i].cSggNm);
			break;
		}
	}

	return asStr;
}

//---------------------------------------------------------------------------
AnsiString cFunc::funcPnuToUMDRIName(char* _cPnu, bool _bSggName)
{
	AnsiString asCodeA;
	AnsiString asPnu;
	AnsiString asSggCd;
	AnsiString asUmdCd;
	AnsiString asRiCd;
	AnsiString asBon;
	AnsiString asBu;
	AnsiString asGbn = "";//181017
	AnsiString asStr = "";

	char cInput[32];

	asPnu = _cPnu;

	if (asPnu.Length() == 5)
	{
		asSggCd = frmMain->_SIDOCODE;
		asUmdCd = asPnu.SubString(1, 3);
		asRiCd  = asPnu.SubString(4, 2);
	}
	else
	{
		asSggCd = asPnu.SubString((19-19+1), 5);
		asUmdCd = asPnu.SubString((19-14+1), 3);
		asRiCd  = asPnu.SubString((19-11+1), 2);
	}

	AnsiString asSggCd_;
	AnsiString asUmdCd_;
	AnsiString asRiCd_;

	for (int i = 0; i < (int)frmMain->m_vDATA_SIDOCODE.size(); i++)
	{
		asSggCd_ = frmMain->m_vDATA_SIDOCODE[i].cSggCd;
		asUmdCd_ = frmMain->m_vDATA_SIDOCODE[i].cUmdCd;
		asRiCd_  = frmMain->m_vDATA_SIDOCODE[i].cRiCd;

		if (asSggCd != asSggCd_)
			continue;

		if (asUmdCd != asUmdCd_)
			continue;

		if (asRiCd != asRiCd_)
			continue;

		if(_bSggName)
			asStr.printf("%s %s %s", frmMain->m_vDATA_SIDOCODE[i].cSggNm, frmMain->m_vDATA_SIDOCODE[i].cUmdNm, frmMain->m_vDATA_SIDOCODE[i].cRiNm);
		else
			asStr.printf("%s %s", frmMain->m_vDATA_SIDOCODE[i].cUmdNm, frmMain->m_vDATA_SIDOCODE[i].cRiNm);
		break;
	}

	return asStr;
}

//---------------------------------------------------------------------------
AnsiString cFunc::funcPnuToRIName(char* _cPnu)
{
	AnsiString asCodeA;
	AnsiString asPnu;
	AnsiString asSggCd;
	AnsiString asUmdCd;
	AnsiString asRiCd;
	AnsiString asBon;
	AnsiString asBu;
	AnsiString asGbn 	= "";
	AnsiString asStr 	= "";
	AnsiString asJibun 	= "";

	asPnu = _cPnu;

	if(asPnu.Length() == 5)
	{
		asSggCd = frmMain->_SIDOCODE;
		asUmdCd = asPnu.SubString(1, 3);
		asRiCd  = asPnu.SubString(4, 2);
	}
	else if(asPnu.Length() ==19)
	{
		asSggCd = asPnu.SubString((19-19+1), 5);
		asUmdCd = asPnu.SubString((19-14+1), 3);
		asRiCd  = asPnu.SubString((19-11+1), 2);
		asBon   = asPnu.SubString((19-8+1), 4);
		asBu    = asPnu.SubString((19-4+1), 4);

		asGbn = asPnu.SubString((19-9+1), 1);//181017
		if (asGbn == "2")
		{
			if(asBu == "0000")
				asJibun.sprintf("산%d", StrToInt(asBon));
			else
				asJibun.sprintf("산%d-%d", StrToInt(asBon), StrToInt(asBu));
		}
		else
		{
			if(asBu == "0000")
				asJibun.sprintf("%d", StrToInt(asBon));
			else
				asJibun.sprintf("%d-%d", StrToInt(asBon), StrToInt(asBu));
		}
	}
	else
	{
		return "";
    }

	AnsiString asSggCd_;
	AnsiString asUmdCd_;
	AnsiString asRiCd_;

	for (int i = 0; i < (int)frmMain->m_vDATA_SIDOCODE.size(); i++)
	{
		asSggCd_ = frmMain->m_vDATA_SIDOCODE[i].cSggCd;
		asUmdCd_ = frmMain->m_vDATA_SIDOCODE[i].cUmdCd;
		asRiCd_  = frmMain->m_vDATA_SIDOCODE[i].cRiCd;

		if (asSggCd != asSggCd_)
			continue;

		if (asUmdCd != asUmdCd_)
			continue;

		if (asRiCd != asRiCd_)
			continue;

		asStr.printf("%s %s", frmMain->m_vDATA_SIDOCODE[i].cRiNm, asJibun);
		break;
	}

	return asStr;
}

//---------------------------------------------------------------------------

bool cFunc::funcPnuToSejongPnu(int _nDocNo)
{
	char cSql[2048];
	memset(cSql, 0, sizeof(cSql));
	sprintf(cSql, "SELECT DISTINCT * FROM TB_SEJONG_PNU WHERE FD_PNU_OLD='%s'", frmMain->m_asSearchPnu);

	frmSql->funcReadSejongPnu(cSql);

	int nSearchedIndex = frmMain->mvResultSejongPnu.size();

	if (nSearchedIndex == 0)
	{
		if (_nDocNo == 7)
		{
			return true;
		}
		if(!frmMain->m_bAlreadyShowMsg)//181016
		{
			frmMsg->funcMessageDlg("알림:", L"구주소에 따른 변환값이 존재하지 않습니다.", 3);
			if(_nDocNo == 0)//통합검색
				frmMain->m_bAlreadyShowMsg = true;
		}
		return false;
	}

//v1.0.0.5//DBSync//	frmSearch->m_asOldCaption 	= (char*)frmMain->mvResultSejongPnu[0].cOldCaption;
	frmMain->m_asSearchPnu 		= (char*)frmMain->mvResultSejongPnu[0].cPnuNew;
	frmMain->m_asSejongOldPnu	= (char*)frmMain->mvResultSejongPnu[0].cPnuOld;
	return true;
}
//---------------------------------------------------------------------------

void cFunc::funcUMDRINameToPnu(AnsiString _asUMDRINm)
{
	AnsiString 	asUMDRINm	= "";
	AnsiString 	asUMDRICd	= "";
	SEARCHEDJIBUN	tempJibun;//210308//#ADDRESS_DUP//
	int 		nPos = -1;

	memset(&tempJibun, 0x00, sizeof(SEARCHEDJIBUN));//210308//#ADDRESS_DUP//
	frmMain->m_vSearchPnuList.clear();

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		asUMDRINm.printf("%s%s", frmMain->m_vSIDOCODE_CMP1[i].cUmdNm, frmMain->m_vSIDOCODE_CMP1[i].cRiNm);
		asUMDRICd.printf("%s%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP1[i].cUmdCd, frmMain->m_vSIDOCODE_CMP1[i].cRiCd);

		nPos = asUMDRINm.Pos(_asUMDRINm);
		if (nPos > 0)
		{
			//210308//#ADDRESS_DUP//
			memset(&tempJibun, 0x00, sizeof(SEARCHEDJIBUN));
			tempJibun.JIBUNINDEX	= -1;
			memcpy(tempJibun.LAND_CD, asUMDRICd.c_str(), sizeof(tempJibun.LAND_CD));
			memcpy(tempJibun.ADDRESS, asUMDRINm.c_str(), sizeof(tempJibun.ADDRESS));
			frmMain->m_vSearchPnuList.push_back(tempJibun);
		}
		else
		{
			asUMDRINm.printf("%s%s", frmMain->m_vSIDOCODE_CMP2[i].cUmdNm, frmMain->m_vSIDOCODE_CMP2[i].cRiNm);
			asUMDRICd.printf("%s%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP2[i].cUmdCd, frmMain->m_vSIDOCODE_CMP2[i].cRiCd);

			nPos = asUMDRINm.Pos(_asUMDRINm);
			if (nPos > 0)
			{
				//210308//#ADDRESS_DUP//
				memset(&tempJibun, 0x00, sizeof(SEARCHEDJIBUN));
				tempJibun.JIBUNINDEX	= -1;
				memcpy(tempJibun.LAND_CD, asUMDRICd.c_str(), sizeof(tempJibun.LAND_CD));
				memcpy(tempJibun.ADDRESS, asUMDRINm.c_str(), sizeof(tempJibun.ADDRESS));
				frmMain->m_vSearchPnuList.push_back(tempJibun);
			}
		}

		//260716//TEST//5개 제한을 걸지 않는다면//
		//if((int)frmMain->m_vSearchPnuList.size() >= 5)//최대5개까지만//[TODO]
		//break;
	}
}
//---------------------------------------------------------------------------
//200910
AnsiString cFunc::funcUMDRICdToNm(AnsiString _asCode)
{
	AnsiString 	asName	= "";
	AnsiString 	asCode	= "";
	int 		nPos = -1;

	//210108#SEJONG_PNU
	if(frmMain->_SIDOCODE == "36110" || frmMain->INIINFO.SIDOCODE == "11305")//v1.0.0.6//11305//강북구//조건추가//
	{
		for (int i = 0; i < (int)frmMain->m_vDATA_SIDOCODE.size(); i++)
		{
			asCode.printf("%s%s%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd, frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);

			nPos = asCode.Pos(_asCode);
			if (nPos > 0)
			{
				asName.printf("%s%s%s", frmMain->m_vDATA_SIDOCODE[i].cSggNm, frmMain->m_vDATA_SIDOCODE[i].cUmdNm, frmMain->m_vDATA_SIDOCODE[i].cRiNm);
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)frmMain->m_vDATA_SIDOCODE.size(); i++)
		{
			asCode.printf("%s%s", frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);

			nPos = asCode.Pos(_asCode);
			if (nPos > 0)
			{
				asName.printf("%s%s", frmMain->m_vDATA_SIDOCODE[i].cUmdNm, frmMain->m_vDATA_SIDOCODE[i].cRiNm);
				break;
			}
		}
	}

	return asName;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcUMDCdToNm(AnsiString _asCode)
{
	AnsiString 	asName	= "";
	AnsiString 	asCode	= "";
	int 		nPos = -1;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		asCode.printf("%s%s", frmMain->m_vSIDOCODE_CMP1[i].cSggCd, frmMain->m_vSIDOCODE_CMP1[i].cUmdCd);

		nPos = asCode.Pos(_asCode);
		if (nPos > 0)
		{
			asName.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cUmdNm);
			break;
		}
	}

	return asName;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcUMDNameToPnu(AnsiString _asUMDNm)
{
	AnsiString 	asUMDNm	= "";
	AnsiString 	asUMDCd	= "";
	int 		nPos 	= -1;
	bool		bFound	= false;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		asUMDNm.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cUmdNm);

		if(asUMDNm == _asUMDNm)
		{
			asUMDCd.printf("%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP1[i].cUmdCd);
			bFound	= true;
			break;
		}
	}

	if( !bFound )//일치하는 읍면동명을 못 찾음//
	{
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
		{
			asUMDNm.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cUmdNm);

			nPos = asUMDNm.Pos(_asUMDNm);
			if (nPos > 0)
			{
				asUMDCd.printf("%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP1[i].cUmdCd);
				break;
			}
		}
	}

	return asUMDCd;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcUMDNameToPnu2(AnsiString _asUMDNm)
{
	AnsiString 	asUMDNm	= "";
	AnsiString 	asUMDCd	= "";
	int 		nPos = -1;
	bool		bFound	= false;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP2.size(); i++)
	{
		asUMDNm.printf("%s", frmMain->m_vSIDOCODE_CMP2[i].cUmdNm);

		if(asUMDNm == _asUMDNm)
		{
			asUMDCd.printf("%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP2[i].cUmdCd);
			bFound	= true;
			break;
		}
	}

	if( !bFound )//일치하는 읍면동명을 못 찾음//
	{
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP2.size(); i++)
		{
			asUMDNm.printf("%s", frmMain->m_vSIDOCODE_CMP2[i].cUmdNm);

			nPos = asUMDNm.Pos(_asUMDNm);
			if (nPos > 0)
			{
				asUMDCd.printf("%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP2[i].cUmdCd);
				break;
			}
		}
	}

	return asUMDCd;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcRICdToNm(AnsiString _asCode)
{
	AnsiString 	asName	= "";
	AnsiString 	asCode	= "";
	int 		nPos = -1;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		asCode.printf("%s%s%s", frmMain->m_vSIDOCODE_CMP1[i].cSggCd, frmMain->m_vSIDOCODE_CMP1[i].cUmdCd, frmMain->m_vSIDOCODE_CMP1[i].cRiCd);

		nPos = asCode.Pos(_asCode);
		if (nPos > 0)
		{
			asName.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cRiNm);
			break;
		}
	}

	return asName;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcRINameToPnu(AnsiString _asUMDCd, AnsiString _asUMDNm, AnsiString _asRINm)
{
	AnsiString 	asRINm	= "";
	AnsiString 	asRICd	= "";
	int 		nPos = -1;
	bool		bFound	= false;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		if(_asUMDCd.SubString(6, 3) == (char*)frmMain->m_vSIDOCODE_CMP1[i].cUmdCd)
		{
			asRINm.printf("%s%s", _asUMDNm, frmMain->m_vSIDOCODE_CMP1[i].cRiNm);

			if(asRINm == _asUMDNm + _asRINm)
			{
				asRICd.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cRiCd);
				bFound	= true;
				break;
			}
		}
	}

	if( !bFound )//일치하는 읍면동+리명을 못 찾음//
	{
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
		{
			if(_asUMDCd.SubString(6, 3) == (char*)frmMain->m_vSIDOCODE_CMP1[i].cUmdCd)
			{
				asRINm.printf("%s%s", _asUMDNm, frmMain->m_vSIDOCODE_CMP1[i].cRiNm);

				nPos = asRINm.Pos(_asUMDNm + _asRINm);
				if (nPos > 0)
				{
					asRICd.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cRiCd);
					break;
				}
			}
		}
	}

	return asRICd;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcRINameToPnu2(AnsiString _asUMDCd, AnsiString _asUMDNm, AnsiString _asRINm)
{
	AnsiString 	asRINm	= "";
	AnsiString 	asRICd	= "";
	int 		nPos = -1;
	bool		bFound	= false;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP2.size(); i++)
	{
		if(_asUMDCd.SubString(6, 3) == (char*)frmMain->m_vSIDOCODE_CMP2[i].cUmdCd)
		{
			asRINm.printf("%s%s", _asUMDNm, frmMain->m_vSIDOCODE_CMP2[i].cRiNm);

			if(asRINm == _asUMDNm + _asRINm)
			{
				asRICd.printf("%s", frmMain->m_vSIDOCODE_CMP2[i].cRiCd);
				bFound	= true;
				break;
			}
		}
	}

	if( !bFound )//일치하는 읍면동+리명을 못 찾음//
	{
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP2.size(); i++)
		{
			if(_asUMDCd.SubString(6, 3) == (char*)frmMain->m_vSIDOCODE_CMP2[i].cUmdCd)
			{
				asRINm.printf("%s%s", _asUMDNm, frmMain->m_vSIDOCODE_CMP2[i].cRiNm);

				nPos = asRINm.Pos(_asUMDNm + _asRINm);
				if (nPos > 0)
				{
					asRICd.printf("%s", frmMain->m_vSIDOCODE_CMP2[i].cRiCd);
					break;
				}
			}
		}
	}

	return asRICd;
}
//---------------------------------------------------------------------------
//200331//리 없이 읍면동명만 입력했을 때 첫번째 리를 반환해준다//'은산1' -> '은산면 1'
AnsiString cFunc::funcRINameToPnu3(AnsiString _asUMDCd, AnsiString _asUMDNm)
{
	AnsiString 	asRINm	= "";
	AnsiString 	asRICd	= "";
	int 		nPos = -1;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		if(_asUMDCd.SubString(6, 3) == (char*)frmMain->m_vSIDOCODE_CMP1[i].cUmdCd && (char*)frmMain->m_vSIDOCODE_CMP1[i].cRiCd != "00")
		{
			asRICd.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cRiCd);
			break;
		}
	}

	return asRICd;
}
//---------------------------------------------------------------------------
//200331//'부여두리1' -> 읍면동에 있는 '부여'부터 찾아서 '부여두리'를 없는 지번이라 하기에
//지번 앞에 한 단어만 있다면 '리'명부터 일치하는게 있는지 찾는다//
AnsiString cFunc::funcRINameToPnu4(AnsiString _asRINm)
{
	AnsiString 	asRINm	= "";
	AnsiString 	asRICd	= "";
	int 		nPos = -1;

	for (int i = 0; i < (int)frmMain->m_vSIDOCODE_CMP1.size(); i++)
	{
		asRINm.printf("%s", frmMain->m_vSIDOCODE_CMP1[i].cRiNm);

		nPos = asRINm.Pos(_asRINm);
		if (nPos > 0)
		{
			asRICd.printf("%s%s%s", frmMain->_SIDOCODE, frmMain->m_vSIDOCODE_CMP1[i].cUmdCd, frmMain->m_vSIDOCODE_CMP1[i].cRiCd);
			break;
		}
	}

	return asRICd;
}
//---------------------------------------------------------------------------


int cFunc::funcDocToScale(TTreeNode* t_ClickNode)
{
	AnsiString asScale = "";
	int	nScale = -1;

	switch(eTree->funcClickNodeToDocNum(frmMain->mSearchNode.tSelectNode))
	{
		case 2:
			DOCUMENT02_STRUCT	*mDoc2Struct;
			mDoc2Struct = (DOCUMENT02_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
			if (!mDoc2Struct) { return -1; }

			try {

				if (mDoc2Struct->RDSCALE_CODE[0] == 0x00) {
					asScale = 1;
				} else {
					asScale = mDoc2Struct->RDSCALE_CODE;
				}

				asScale = asScale.SubString((asScale.Pos("/")+1), asScale.Length());
				asScale = asScale.SubString((asScale.Pos(":")+1), asScale.Length());

				nScale = asScale.ToInt() * 100;//200420
			}
			catch (Exception &exception)
			{
				nScale = 0;
				throw Exception("");
			}

			break;
		case 7:
			DOCUMENT07_STRUCT	*mDoc7Struct;
//190905//44760//검색된 문서별 축척정보를 가져와야 하는데 맨처음 데이터의 정보만 갖고 와서 면적계산에 문제 발생!!!
//			if(frmIniControl->m_bMAPPOINT)
//			{
//				mDoc7Struct = (DOCUMENT07_STRUCT*)&frmSqlControl->m_ResultDocument07[0];
//			}
//			else
			{
				mDoc7Struct = (DOCUMENT07_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
			}
			if (!mDoc7Struct) { return -1; }

			asScale = mDoc7Struct->SCALE;
			if (asScale.IsEmpty())
				return -1;

			asScale = asScale.SubString((asScale.Pos("/")+1), asScale.Length());
			asScale = asScale.SubString((asScale.Pos(":")+1), asScale.Length());

			try {
				nScale = asScale.ToInt() * 100;
			}
			catch (Exception &exception)
			{
				nScale = 0;
				throw Exception("");
			}
			break;
		default:
			nScale = 0;
			break;

	}
	return nScale;
}
//---------------------------------------------------------------------------

int cFunc::funcCheckImageScale()
{
	int nReturnValue = 0;
	AnsiString asInputScale = "0";

	wchar_t wcScaleValue[32];

	//200325//[TODO]
//	if (frmIniControl->mUserSetIniInfo.nDoc0_V1 == 2) {
//		if (frmIniControl->mUserSetIniInfo.nDoc0_V1_1 > 0)
//		{
//			memset(&wcScaleValue, 0, sizeof(wcScaleValue));
//			swprintf(wcScaleValue, L"현재 축척정보는 수동입력 모드입니다. 입력값:%d", frmIniControl->mUserSetIniInfo.nDoc0_V1_1);
//			ShowMessage(wcScaleValue);
//		} else if (frmIniControl->mUserSetIniInfo.nDoc0_V1_1 == 0) {
//			ShowMessage(L"축척에 대한 입력값을 0이 아닌값으로 변경 하십시요.");
//		}
//		return frmIniControl->mUserSetIniInfo.nDoc0_V1_1;
//	}

	if (frmMain->mGetImageInfo.nDBScale > 0)
		return frmMain->mGetImageInfo.nDBScale;

	asInputScale = InputBox(L"축척정보 입력", L"DB에 축척정보가 존재하지 않습니다. \n\r축척정보을 수동으로 입력하여 주세요.", L"0");

	try {
		nReturnValue = asInputScale.ToInt();
		frmMain->mGetImageInfo.nInputScale = nReturnValue;
		return nReturnValue;
	}
	catch (Exception &exception) {
		frmMain->mGetImageInfo.nDBScale = 0;
		throw Exception("입력 오류입니다.");
	}
}

//---------------------------------------------------------------------------



TPoint cFunc::funcSurveyMapToDevice(const GPoint _gPoint)
{
	TPoint tPoint;

	tPoint.x = (double)(_gPoint.x + frmMain->realLeft) * frmMain->m_dDocFactor;
	tPoint.y = (double)(_gPoint.y - frmMain->realTop) * frmMain->m_dDocFactor;

	return tPoint;
}
//---------------------------------------------------------------------------

GPoint cFunc::funcDeviceToSurveyMap(const TPoint _scrPoint)
{
	GPoint gPoint;

	gPoint.x = (double)_scrPoint.x / frmMain->m_dDocFactor - frmMain->realLeft;
	gPoint.y = (double)_scrPoint.y / frmMain->m_dDocFactor + frmMain->realTop;

	return gPoint;
}
//---------------------------------------------------------------------------

GPoint cFunc::funcBitMapImageToCm(const TPoint _tpImageLength, mBitmapHeader *mBitMapHeader, int _nType)
{
	GPoint gpLength;

	if (_nType == 1) {
		gpLength.x = (double)_tpImageLength.x / ((double)mBitMapHeader->biXPelsPerMeter / 100);
		gpLength.y = (double)_tpImageLength.y / ((double)mBitMapHeader->biYPelsPerMeter / 100);
	} else {
		gpLength.x = (double)_tpImageLength.x / ((double)mBitMapHeader->biXPelsPerMeter);
		gpLength.y = (double)_tpImageLength.y / ((double)mBitMapHeader->biYPelsPerMeter);
	}

	return gpLength;
}
//---------------------------------------------------------------------------
//190417//dogwak_pos -> image_pos
TPoint cFunc::funcCmToBitMapImage(const GPoint _gpLength, mBitmapHeader *mBitMapHeader, int _nScale)
{
	TPoint tpImageLength;
//190905/어떤 테스트인지 모르겠으나, 아래 코드를 살려두면 tif 1/6000 면적 계산시 오류발생
//도곽선 그릴 때에도 문제 발생.
	//TEST
//	mBitMapHeader->biXPelsPerMeter = 11811;
//	mBitMapHeader->biYPelsPerMeter = 11811;

	//44760.250.28.725(부여군청) 폐쇄지적도 위치 문제 발생 (96dpi 일때만 조정)
	if(mBitMapHeader->biXPelsPerMeter == 2835 && mBitMapHeader->biYPelsPerMeter == 2835)
	{
		mBitMapHeader->biXPelsPerMeter = 11811;
		mBitMapHeader->biYPelsPerMeter = 11811;
	}

	tpImageLength.x = (double)_gpLength.x * ((double)mBitMapHeader->biXPelsPerMeter / 1000);
	tpImageLength.y = (double)_gpLength.y * ((double)mBitMapHeader->biYPelsPerMeter / 1000);

	tpImageLength.x = (int)((double)tpImageLength.x / ((double)_nScale / (double)1000));//1:1000 기준
	tpImageLength.y = (int)((double)tpImageLength.y / ((double)_nScale / (double)1000));//1:1000 기준

	return tpImageLength;
}
//---------------------------------------------------------------------------
GPoint cFunc::funcMapPointToMeter(const GPoint _gpMapPoint)
{
	GPoint gpLength;

	if(frmMain->bJGWExists)
	{
		gpLength.x = _gpMapPoint.x / ((double)frmMain->biXPelsPerMeterJGW / 100);
		gpLength.y = _gpMapPoint.y / ((double)frmMain->biYPelsPerMeterJGW / 100);
	}
	else
	{
		gpLength.x = _gpMapPoint.x / ((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biXPelsPerMeter / 100);
		gpLength.y = _gpMapPoint.y / ((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biYPelsPerMeter / 100);
	}

	gpLength.x = gpLength.x * (frmMain->mGetImageInfo.nInputScale / 100);
	gpLength.y = gpLength.y * (frmMain->mGetImageInfo.nInputScale / 100);

	return gpLength;
}

//---------------------------------------------------------------------------

int cFunc::funcGetPixelFormat(int _nBitCount)
{
	switch(_nBitCount)
	{
		case 1:
			return pf1bit;
		case 4:
			return pf4bit;
		case 8:
			return pf8bit;
		case 15:
			return pf15bit;
		case 16:
			return pf16bit;
		case 24:
			return pf24bit;
		case 32:
			return pf32bit;
		default:
			return pf24bit;
	}
}
//---------------------------------------------------------------------------

//========================================================================
//1. YYYY-MM-DD
//2. YYYY-MM-DD HH:NN:SS
//3. YYYY년 MM월 DD일//
AnsiString cFunc::funcChangeDateFormatString(int _nType, char* _cDateStr)
{
	AnsiString asStr = (char*)_cDateStr;

	if(_nType == 1)//YYYY-MM-DD
	{
		if(asStr.Length() == 8)
			asStr = asStr.SubString(1,4) + "-" + asStr.SubString(5,2) + "-" + asStr.SubString(7,2);
	}
	else if(_nType == 2)//YYYY-MM-DD HH:NN:SS
	{
		if(asStr.Length() == 14)
			asStr = asStr.SubString(1,4) + "-" + asStr.SubString(5,2) + "-" + asStr.SubString(7,2) + " " + asStr.SubString(9,2) + ":" + asStr.SubString(11,2) + ":" + asStr.SubString(13,2);
	}
	else if(_nType == 3)//YYYY년 MM월 DD일//
	{
		asStr	= StringReplace(asStr, "-", "", TReplaceFlags() << rfReplaceAll);

		if(asStr.Length() >= 8)
			asStr = IntToStr(asStr.SubString(1,4).ToInt()) + "년" + IntToStr(asStr.SubString(5,2).ToInt()) + "월" + IntToStr(asStr.SubString(7,2).ToInt()) + "일";

		//====================================================
		//211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
		asStr	= StringReplace(asStr, "9999", "    ", TReplaceFlags() << rfReplaceAll);
		asStr	= StringReplace(asStr, "99", " ", TReplaceFlags() << rfReplaceAll);
		//====================================================

		//====================================================
		//230203//비어있는 경우가 아닌 판독이 어려운 경우 //
		asStr	= StringReplace(asStr, "8888", "□", TReplaceFlags() << rfReplaceAll);
		asStr	= StringReplace(asStr, "88", "□", TReplaceFlags() << rfReplaceAll);
		//====================================================
	}

	return asStr;
}
//---------------------------------------------------------------------------

//#OWNINFO#
AnsiString cFunc::funcChangeDateNumberFormatDate(AnsiString _asDate)
{
	if(_asDate.IsEmpty())
		return "";

	AnsiString 	asHisDate 	= "";
	AnsiString 	asStr	 	= "";
	AnsiString 	asEra		= "";
	AnsiString 	asYear		= "";
	AnsiString 	asMonth		= "";
	AnsiString 	asDay		= "";
	AnsiString 	asDate		= _asDate;
	AnsiString  asNow		= Now().FormatString("YYYY");
	int 		nPos		= 0;
	int			nEraType	= 0;
	int			nYear		= 0;
	int			nMonth		= 0;
	int			nDay		= 0;
	int			nYear1		= 0;
	int			nNow		= asNow.ToInt();

	//---
	asDate	= StringReplace(asDate, " ", "", TReplaceFlags() << rfReplaceAll);
	//---
	//Era
	nPos	= asDate.Pos(".");//Era
	if(nPos == 0)
		return "";
	asStr	= asDate.SubString(1, nPos-1);
	asDate	= asDate.Delete(1, nPos);
	if(asStr.IsEmpty() || !IsNumberString(asStr))
		return "Error";
	nEraType	= asStr.ToInt();//1:단기,2:명치,3:대정,4:소화//
	if(nEraType < 1 || nEraType > 5)
		return "Error";
	//---
	//Year
	nPos	= asDate.Pos(".");//Year
	if(nPos == 0)
		return "Error";
	asStr	= asDate.SubString(1, nPos-1);
	asDate	= asDate.Delete(1, nPos);
	if(asStr.IsEmpty() || !IsNumberString(asStr))
		return "Error";
	nYear	= asStr.ToInt();
	//================================================================
	if(nEraType == 1 && (nYear < 4230 || nYear > nNow + 2333))//단기//
		return "Error";
	else if(nEraType == 2 && nYear > 46)//명치//
		return "Error";
	else if(nEraType == 3 && nYear > 15)//대정//
		return "Error";
	else if(nEraType == 4 && nYear > 64)//소화//
		return "Error";
	//---
	if(nEraType == 1)//단기//
		nYear1	= nYear - 2333;
	else if(nEraType == 2)//명치//
		nYear1	= nYear + 1867;
	else if(nEraType == 3)//대정//
		nYear1	= nYear + 1911;
	else if(nEraType == 4)//소화//
		nYear1	= nYear + 1925;
	else if(nEraType == 5)//서기//
		nYear1	= nYear;
	//---
	if(nYear1 < 1897 || nYear1 > nNow)
		return "Error";
	//---
	if(nEraType == 1)
		asEra	= "단기";
	else if(nEraType == 2)
		asEra	= "명치";
	else if(nEraType == 3)
		asEra	= "대정";
	else if(nEraType == 4)
		asEra	= "소화";
	//================================================================

	//---
	//Month
	nPos	= asDate.Pos(".");//Month
	if(nPos == 0)
		return "Error";
	asStr	= asDate.SubString(1, nPos-1);
	asDate	= asDate.Delete(1, nPos);
	if(asStr.IsEmpty() || !IsNumberString(asStr))
		return "Error";
	nMonth	= asStr.ToInt();
	//---
	if(nMonth < 1 || nMonth > 12)
		return "Error";
	//Day
	asStr	= asDate;
	if(asStr.IsEmpty() || !IsNumberString(asStr))
		return "Error";
	nDay	= asStr.ToInt();
	//---
   	if ((nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth ==
			8 || nMonth == 10 || nMonth == 12) && (nDay < 1 || nDay > 31))
		return "Error";
	if ((nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11) &&
		(nDay < 1 || nDay > 30))
		return "Error";
	if (nMonth == 2 && nYear1 % 4 && (nDay < 1 || nDay > 28))
		return "Error";
	if (nMonth == 2 && !(nYear1 % 4) && (nDay < 1 || nDay > 29)) // 2월 윤달
		return "Error";
	//---
	asYear.sprintf("%d년", nYear);
	asMonth.sprintf("%d월", nMonth);
	asDay.sprintf("%d일", nDay);

	//================================================================
	//concatenate
	_asDate	= asEra + asYear + asMonth + asDay;
	//================================================================

	return _asDate;
}
//---------------------------------------------------------------------------

//#OWNINFO#
AnsiString cFunc::funcChangeDateStrFormatDate(AnsiString _asDate)
{
	if(_asDate.IsEmpty())
		return "";

	AnsiString 	asHisDate 	= "";
	AnsiString 	asStr	 	= "";
	AnsiString 	asYear		= "";
	AnsiString 	asMonth		= "";
	AnsiString 	asDay		= "";
	AnsiString  asNow		= Now().FormatString("YYYY");
	int 		nPos		= 0;
	int			nEraType	= 0;
	int			nYear		= 0;
	int			nNow		= asNow.ToInt();

	//---
	_asDate	= StringReplace(_asDate, " ", "", TReplaceFlags() << rfReplaceAll);
	//---
	nPos	= _asDate.AnsiPos("단기");
	if(nPos > 0)
	{
		nEraType	= 0;
		_asDate		= StringReplace(_asDate, "단기", "", TReplaceFlags() << rfReplaceAll);
	}
	else
	{
		nPos	= _asDate.AnsiPos("명치");
		if(nPos > 0)
		{
			nEraType	= 1;
			_asDate		= StringReplace(_asDate, "명치", "", TReplaceFlags() << rfReplaceAll);
		}
		else
		{
			nPos	= _asDate.AnsiPos("대정");
			if(nPos > 0)
			{
				nEraType	= 2;
				_asDate		= StringReplace(_asDate, "대정", "", TReplaceFlags() << rfReplaceAll);
			}
			else
			{
				nPos	= _asDate.AnsiPos("소화");
				if(nPos > 0)
				{
					nEraType	= 3;
					_asDate		= StringReplace(_asDate, "소화", "", TReplaceFlags() << rfReplaceAll);
				}
				else
				{
					nPos	= _asDate.AnsiPos("서기");
					if(nPos > 0)
					{
						nEraType	= 4;
						_asDate		= StringReplace(_asDate, "서기", "", TReplaceFlags() << rfReplaceAll);
					}
					else
						nEraType	= 4;
				}
			}
		}
	}

	//220826//년월일에 %(취소선 표시) 처리가 있는 경우, 날짜 체크를 제대로 안해서 수정//
	// %(취소선 표시) 처리가 있는 경우, 년도정보나 월일정보가 없는 경우 예외로 빠져버려서 아래와 같이 처리//
	bool 		bAllSharp	= false;
	int 		nPos1	= 0;
	int 		nPos2	= 0;
	AnsiString  asWorkData	= "";

	nPos1	= _asDate.Pos("%");
	if(nPos1 > 0)
	{
		asWorkData	= _asDate.SubString(nPos1+1, _asDate.Length()-nPos);
		nPos2	= asWorkData.Pos("%");
		if(nPos1 == 1 && nPos2 == _asDate.Length()-1)//정상//맨 앞과 맨 끝에 %가 있는 경우//첫 번째 %를 제거했으므로 마지막%는 원본길이보다 1작다//
		{
			bAllSharp	= true;
			_asDate	= StringReplace(_asDate, "%", "", TReplaceFlags() << rfReplaceAll);
		}
		else//부분삭제가 있다는 건데... 금란차장은 년월일에 부분삭제 처리는 안한다고 했음.
		{
//			//문제가 있음..//처리 고민하지 않기//
//			if(nPos2 < _asDate.Length() && nPos2 == 0)//종결이 없다는 뜻//
//			{
//
//			}
		}
	}

	//년도//
	nPos	= _asDate.AnsiPos("년");
	if(nPos > 0)
	{
		//220826//년월일에 %(취소선표시)가 있으면 날짜 오류가 있어도 체킹을 못하기에 아래 기능 추가//
		asStr   = _asDate.SubString(1, nPos-1);
		if( !IsNumberString(asStr) && asStr != "□")//230203//□ 표시 추가//if( !IsNumberString(asStr) )
			return "";

		//====================================================
		//230203//비어있는 경우가 아닌 판독이 어려운 경우 //
		if(asStr == "□")
		{
			asYear	= "8888";
		}
		else
		//====================================================
		{
			nYear	= StrToInt(asStr);

			if(nEraType == 0 && (nYear < 4230 || nYear > nNow + 2333))//단기//
				return "Error";
			else if(nEraType == 1 && nYear > 46)//명치//
				return "Error";
			else if(nEraType == 2 && nYear > 15)//대정//
				return "Error";
			else if(nEraType == 3 && nYear > 64)//소화//
				return "Error";

			if(nEraType == 0)//단기//
				nYear	-= 2333;
			else if(nEraType == 1)//명치//
				nYear	+= 1867;
			else if(nEraType == 2)//대정//
				nYear	+= 1911;
			else if(nEraType == 3)//소화//
				nYear	+= 1925;

			if(nYear < 1897 || nYear > nNow)
				return "Error";

			asYear.sprintf("%04d", nYear);//StrToInt(asStr));
		}
		_asDate	= _asDate.Delete(1, nPos+1);
	}
	else
	{
		asYear	= "9999";
	}
		//월//
	nPos	= _asDate.AnsiPos("월");
	if(nPos > 0)
	{
		asStr   = _asDate.SubString(1, nPos-1);
		if( !IsNumberString(asStr) && asStr != "□")//230203//□ 표시 추가//if( !IsNumberString(asStr))
			return "Error";

		//====================================================
		//230203//비어있는 경우가 아닌 판독이 어려운 경우 //
		if(asStr == "□")
		{
			asMonth	= "88";
		}
		else
		//====================================================
		{
			asMonth.sprintf("%02d", StrToInt(asStr));
		}
		_asDate	= _asDate.Delete(1, nPos+1);
	}
	else
	{
		asMonth	= "99";
	}
			//일//
	nPos	= _asDate.AnsiPos("일");
	if(nPos > 0)
	{
		asStr   = _asDate.SubString(1, nPos-1);
		if( !IsNumberString(asStr) && asStr != "□")//230203//□ 표시 추가//if( !IsNumberString(asStr) )
			return "Error";

		//====================================================
		//230203//비어있는 경우가 아닌 판독이 어려운 경우 //
		if(asStr == "□")
		{
			asDay	= "88";
		}
		else
		//====================================================
		{
			if( !IsNumberString(asStr) && asStr != "□" )//260615//
				return "Error";
			asDay.sprintf("%02d", StrToInt(asStr));
		}
	}
	else
	{
		asDay	= "99";
	}

	//concatenate
	_asDate	= asYear + asMonth + asDay;

	if(bAllSharp)//220826//년월일에 %(취소선 표시) 처리가 있는 경우, 날짜 체크를 제대로 안해서 수정//
		_asDate	= "%" + _asDate + "%";

	return _asDate;
}
//---------------------------------------------------------------------------

//#OWNINFO#
//_nType : 1 (㎡), 2 (평), 3(정단무보)
AnsiString cFunc::funcChangeAreaFormatStr(int _nType, AnsiString _asArea)
{
	if(_asArea.IsEmpty())
		return "";

	AnsiString 	asReturn 		= "";
	AnsiString 	asStr	 		= "";
	AnsiString 	asArea			= _asArea;
	double 		dCalcValueA1 	= 0;
	double 		dCalcValueA2 	= 0;
	double 		dCalcValueA3 	= 0;
	double 		dCalcValueA4 	= 0;
	double 		dCalcValueA9 	= 0;
	double 		dCalcValueA8 	= 0;
	double 		dCalcValueSum 	= 0;
	int 		nPos			= 0;
	vector<AnsiString>	vDATA;
	int			nSize			= 0;
	int			nAreaUnitType	= 0;//평(1), 홉(2), 작(3), 정단무보(4), 단위없음(5)//

	if(_asArea == "-")//220124//
    	return "";

	//---
	asArea	= StringReplace(asArea, " ", "", TReplaceFlags() << rfReplaceAll);
	//211201//#12//지적단위변환//
	asArea	= StringReplace(asArea, "#", "", TReplaceFlags() << rfReplaceAll);
	asArea	= StringReplace(asArea, "%", "", TReplaceFlags() << rfReplaceAll);

	//====================================================================================================
	if(_nType == 1)//㎡//
	{
		//지적단위 확인//
//=============================================================================
//v1.0.0.1//230727//임야대장 : 평방미터, ㎡ 단위가 붙은 경우 제대로 표시되도록 추가//
		if(asArea.AnsiPos("평방미터"))
		{
			nPos	= asArea.AnsiPos("평방미터");
			asArea	= asArea.SubString(1, nPos-1);
			if(IsAreaString(asArea))
			{
				//211230//정수만표시//안수환J요청//asReturn	= FormatFloat("###,##0.###", (double)(asArea.ToDouble() * 3.305785));
				asReturn	= FormatFloat("###,##0", (double)asArea.ToDouble());
			}
			return asReturn;
		}
		else if(asArea.AnsiPos("㎡"))
		{
			nPos	= asArea.AnsiPos("㎡");
			asArea	= asArea.SubString(1, nPos-1);
			if(IsAreaString(asArea))
			{
				//211230//정수만표시//안수환J요청//asReturn	= FormatFloat("###,##0.###", (double)(asArea.ToDouble() * 3.305785));
				asReturn	= FormatFloat("###,##0", (double)asArea.ToDouble());
			}
			return asReturn;
		}
//=============================================================================
		else if(asArea.AnsiPos("평"))
		{
			nAreaUnitType = 1;
			nPos = asArea.AnsiPos("평");
		}
		else if(asArea.AnsiPos("홉"))
		{
			nAreaUnitType = 2;
			nPos = asArea.AnsiPos("홉");
		}
		else if(asArea.AnsiPos("작"))
		{
			nAreaUnitType = 3;
			nPos = asArea.AnsiPos("작");
		}
		else if(asArea.AnsiPos("정") || asArea.AnsiPos("단") || asArea.AnsiPos("무") || asArea.AnsiPos("보"))
		{
			nAreaUnitType = 4;
		}
		else
		{
			nAreaUnitType = 5;
		}

		//
		if(nPos > 0 && nAreaUnitType < 4)//평,홉,작//
		{
			asArea	= asArea.SubString(1, nPos-1);
			if(IsAreaString(asArea))
			{
				//230213//다른시군에서는소수1자리표시요청하여 옵션으로 처리
				//211230//정수만표시//안수환J요청//asReturn	= FormatFloat("###,##0.###", (double)(asArea.ToDouble() * 3.305785));
				double dArea	= 0.0;
				if(nAreaUnitType == 1)
					dArea	= (double)(asArea.ToDouble() * 3.305785);
				else if(nAreaUnitType == 2)
					dArea	= (double)(asArea.ToDouble() * 0.3305785);
				else if(nAreaUnitType == 3)
					dArea	= (double)(asArea.ToDouble() * 0.03305785);

				if( frmMain->m_nAreaPoint == 0)
					asReturn	= FormatFloat("###,##0", dArea);
				else if( frmMain->m_nAreaPoint == 1)//소수1자리-있으면 표시 없으면 정수만 표시//
					asReturn	= FormatFloat("###,##0.#", dArea);
			}
		}
		else if(nAreaUnitType == 5)//단위 없을 때//211201//
		{
			if(IsAreaString(asArea))//220825//chkAreaChange->Checked 상태에서는 이 구문이 없어서 천단위(,)표시 안되어서 추가//
			{
				//230213//다른시군에서는소수1자리표시요청하여 옵션으로 처리
				//211230//정수만표시//안수환J요청//asReturn	= FormatFloat("###,##0.###", (double)(asArea.ToDouble() * 3.305785));
				if( frmMain->m_nAreaPoint == 0)
					asReturn	= FormatFloat("###,##0", (double)asArea.ToDouble());
				else if( frmMain->m_nAreaPoint == 1)//소수1자리-있으면 표시 없으면 정수만 표시//
					asReturn	= FormatFloat("###,##0.#", (double)asArea.ToDouble());
			}
		}
	}
	//====================================================================================================
	else if(_nType == 3)//3.1205 -> 정단무보//
	{
		//=====================
		//이미 '정단무보'라는 문자가 있다면 입력값 그대로//
		if(asArea.AnsiPos("정") > 0 || asArea.AnsiPos("단") > 0 || asArea.AnsiPos("무") > 0 || asArea.AnsiPos("보") > 0)
			return _asArea;
		//=====================
		//토지대장일 때는 입력값 그대로//
		if(frmAlphaDoc8->m_nDOCKIND == 0)
			return _asArea;
		//220503//%18%_0.0100 -> 18에는 취소선이 생기지만, 0.0100 변환을 못한다.
		//220503//44150.330.35.2.10.2//
		//지적'%18%_0.0100' 처리하는데, 18정에 취소선 표시가 되지 않아서 확인해보니//
		//위의 조건들이 아니면 여기서 처리를 안하고 있어 아래와 같이 처리//
		if(asArea.Pos(".") == 0)//210705//'평'이라서 '.'없이 숫자만 입력하는 경우에는 입력 그대로 처리//
		{
			if(asArea.AnsiPos("㎡") == 0)
			{
				//211201//#13//숫자없는 데이터만 들어왔을 때//
				if(IsNumberString(_asArea))
					return _asArea + "정";
				else
					return _asArea;
			}
		}
		else
		{
			asArea = _asArea;
		}

		//==================================================================
		// MultiLine 처리//
		//==================================================================
		//Vector 구성//
		vDATA.clear();
		nPos	= asArea.Pos("_");
		while(nPos > 0)
		{
			if(nPos < asArea.Length())
			{
				asStr	= asArea.SubString(1, nPos-1);
				asArea	= asArea.Delete(1, nPos);
				vDATA.push_back(asStr);
				nPos	= asArea.Pos("_");
			}
		}
		if( !asArea.IsEmpty() )
			vDATA.push_back(asArea);

		//각 Vector 데이터 확인//
		nSize	= vDATA.size();
		for(int i = 0; i < nSize; i++)
		{
			bool	bPercent	= false;//220503//#ERR//bring here//44150.330.35.2.10.2
			bool	bSharp		= false;//230212//임야대장//정단무보에서도 전체삭제(#), 부분삭제(%%) 구별//
			bool	bSquare		= false;//230213//㎡//

			asArea	= vDATA[i];

			if(asArea.SubString(1, 1) == "%" && asArea.SubString(asArea.Length(), 1) == "%")
			{
				asArea		= StringReplace(asArea, "%", "", TReplaceFlags() << rfReplaceAll);
				bPercent	= true;
			}
			//====================================
			//230203//임야대장.지적에 # 에러 발생하여 추가//
			if(asArea.SubString(1,1) == "#")
			{
				asArea	= StringReplace(asArea, "#", "", TReplaceFlags() << rfReplaceAll);
				bSharp 	= true;
			}
			//====================================
			//230213//임야대장.지적에 ㎡ 데이터 존재//
			if(asArea.SubString(1,1) == "㎡")
			{
				asArea	= StringReplace(asArea, "㎡", "", TReplaceFlags() << rfReplaceAll);
				bSquare 	= true;
			}
			//====================================

			if(i > 0)
				asReturn	= asReturn + "_";

			//
			//230212//조건추가//#.7600(OK)인데, #0.7600(Not OK)인 상황이라 조건추가하여 수정//
			if( !bSquare )
			{
				nPos	= asArea.AnsiPos(".");
				if(nPos > 0)
				{
					asStr	= asArea.SubString(1, nPos-1);
					if( !asStr.IsEmpty() && asStr != "0")
						asStr	= asStr + "정";
					if(asStr == "0")
						asStr = "";
					asArea	= asArea.Delete(1, nPos);
				}
				else//'단무보' 없는 '정'
				{
					//=========================================================
					//250219//[ErrFixed]//구대장한글화.임야.지적 [1.6600_1 / .3300_2800] => 오류//
					asStr	= asArea;
					asArea	= "";
					//=========================================================

					asStr	= asStr + "정";
				}

				if(asArea.Length() == 4)//'정'을 제거한 후 '단무보'
				{
					if(asArea.SubString(1,1) != "0")
						asStr	= asStr + asArea.SubString(1,1) + "단";
					if(asArea.SubString(2,1) != "0")
						asStr	= asStr + asArea.SubString(2,1) + "무";
					if(asArea.SubString(3,2) != "00")
						asStr	= asStr + IntToStr(asArea.SubString(3,2).ToInt()) + "보";
				}

				if(bPercent)
					asReturn	= asReturn + "%" + asStr + "%";
				else if(bSharp)
					asReturn	= asReturn + "#" + asStr;
				else
					asReturn	= asReturn + asStr;
			}
			else
			{
				if(bPercent)
					asReturn	= asReturn + "%" + asArea + "㎡%";
				else if(bSharp)
					asReturn	= asReturn + "#" + asArea + "㎡";
				else
					asReturn	= asReturn + asArea;
			}

			if(asArea.IsEmpty())//220427//#ERR//bring here//44150.330.35.2.10.2
				continue;
		}
	}

	//===========================================================
	//공통//정단무보//
	//===========================================================
	if( (_nType == 1 && nAreaUnitType == 4)//정단무보 -> ㎡
	 || (_nType == 2) )//정단무보 -> 평//
	{
		AnsiString  asUnit	= "";
		int 		nUnitLvl	= 0;
		while( !asArea.IsEmpty() )
		{
			nUnitLvl++;
			if(nUnitLvl == 1)
				asUnit	= "정";
			else if(nUnitLvl == 2)
				asUnit	= "단";
			else if(nUnitLvl == 3)
				asUnit	= "무";
			else if(nUnitLvl == 4)
				asUnit	= "보";
			//
			nPos	= asArea.AnsiPos(asUnit);
			if(nPos == 0)
			{
				if(nUnitLvl == 1)
					dCalcValueA1	= 0.0;
				else if(nUnitLvl == 2)
					dCalcValueA2	= 0.0;
				else if(nUnitLvl == 3)
					dCalcValueA3	= 0.0;
				else if(nUnitLvl == 4)
					dCalcValueA4	= 0.0;
			}
			else
			{
				asStr	= asArea.SubString(1, nPos-1);
				if(asStr.IsEmpty() || !IsNumberString(asStr))
					return "Error";

				if(nUnitLvl == 1)
					dCalcValueA1	= asStr.ToDouble();
				else if(nUnitLvl == 2)
					dCalcValueA2	= asStr.ToDouble();
				else if(nUnitLvl == 3)
					dCalcValueA3	= asStr.ToDouble();
				else if(nUnitLvl == 4)
					dCalcValueA4	= asStr.ToDouble();
				asArea	= asArea.Delete(1, nPos+1);//한글2Bytes//
			}
		}
		//
		dCalcValueSum = dCalcValueA1 + dCalcValueA2 * 0.1 + dCalcValueA3 * 0.01;
		dCalcValueA9 = dCalcValueSum * 3000 + dCalcValueA4;
		dCalcValueSum = dCalcValueA9 * 3.3057851239669442148;

		//===========================================================
		//230213//다른시군에서는소수1자리표시요청하여 옵션으로 처리
		//211230//정수만표시//안수환J요청//
		if(_nType == 1 && nAreaUnitType == 4)//정단무보 -> ㎡//
		{
			if( frmMain->m_nAreaPoint == 0)
				asReturn	= FormatFloat("###,##0", dCalcValueSum);
			else if( frmMain->m_nAreaPoint == 1)//소수1자리-있으면 표시 없으면 정수만 표시//
				asReturn	= FormatFloat("###,##0.#", dCalcValueSum);
		}
		else if(_nType == 2 && nAreaUnitType == 4)//정단무보 -> 평//
		{
			if( frmMain->m_nAreaPoint == 0)
				asReturn	= FormatFloat("###,##0", dCalcValueA9);
			else if( frmMain->m_nAreaPoint == 1)//소수1자리-있으면 표시 없으면 정수만 표시//
				asReturn	= FormatFloat("###,##0.#", dCalcValueA9);
		}
	}

	return asReturn;
}
//---------------------------------------------------------------------------

bool cFunc::funcCheckDate(AnsiString _asEraCode, AnsiString _asDate)
{
	if(_asDate.Length() != 8 || _asDate == "00000000" || _asDate.SubString(1, 4) == "0000")
		return false;

	AnsiString 	asHisDate 	= "";
	int 		nYear		= 0;
	int 		nMonth		= 0;
	int 		nDay		= 0;

	nYear 	= _asDate.SubString(1, 4).ToInt();
	nMonth 	= _asDate.SubString(5, 2).ToInt();
	nDay 	= _asDate.SubString(7, 2).ToInt();

	if(_asEraCode == "01")			nYear = nYear + 1896;
	else if(_asEraCode == "02")		nYear = nYear + 1867;
	else if(_asEraCode == "03")		nYear = nYear + 1911;
	else if(_asEraCode == "04")		nYear = nYear + 1925;
	else if(_asEraCode == "05")		nYear = nYear - 2333;
	else if(_asEraCode == "06")		nYear = nYear - 544;
	else if(_asEraCode == "07")		nYear = nYear - 7197;
	else if(_asEraCode == "08")		nYear = nYear;

	asHisDate.sprintf("%04d%02d%02d", nYear, nMonth, nDay);

	if(nYear < 1800 || nYear > 2100)
		return false;
	if(nMonth < 1 || nMonth > 12)
		return false;
   	if ((nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth ==
			8 || nMonth == 10 || nMonth == 12) && (nDay < 1 || nDay > 31))
		return false;
	if ((nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11) &&
		(nDay < 1 || nDay > 30))
		return false;
	if (nMonth == 2 && nYear % 4 && (nDay < 1 || nDay > 28))
		return false;
	if (nMonth == 2 && !(nYear % 4) && (nDay < 1 || nDay > 29)) // 2월 윤달
		return false;

	return true;
}
//---------------------------------------------------------------------------

void cFunc::funcCreateDir(String _sDirName)
{
	if (DirectoryExists(_sDirName) == false)
	{
		if (CreateDir(_sDirName) == false)
			throw Exception("Cannot Create Directory. [code:08161020]");
	}
}
//---------------------------------------------------------------------------

int cFunc::func_GetLength(AnsiString path)
{
	FILE *tempFile;
	tempFile = fopen(path.c_str(), "rb");

	fseek(tempFile, 0, SEEK_CUR);
	fseek(tempFile, 0, SEEK_END);
	int filesize = ::ftell(tempFile);
	fclose(tempFile);
	return filesize;
}
//---------------------------------------------------------------------------
//200910//
AnsiString cFunc::funcFindUMDRINmToCd(AnsiString _asUMDRINm)
{
	AnsiString 	asUMDRINm	= "";
	AnsiString 	asUMDRICd	= "";
	AnsiString 	asRiNm		= "";
	bool        bFound  	= false;

	//210108#SEJONG_PNU
	if(frmMain->_SIDOCODE == "36110" || frmMain->_SIDOCODE == "11305")//v1.0.0.6//11305//강북구//조건추가//
	{
		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA1.size(); i++)
		{
			asUMDRINm.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA1[i].cSggNm, frmMain->m_vSIDOCODE_DATA1[i].cUmdNm, frmMain->m_vSIDOCODE_DATA1[i].cRiNm);

			if (asUMDRINm.Pos(_asUMDRINm) > 0)//210201//
			{
				asUMDRICd.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA1[i].cSggCd, frmMain->m_vSIDOCODE_DATA1[i].cUmdCd, frmMain->m_vSIDOCODE_DATA1[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA2.size(); i++)
		{
			asUMDRINm.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA2[i].cSggNm, frmMain->m_vSIDOCODE_DATA2[i].cUmdNm, frmMain->m_vSIDOCODE_DATA2[i].cRiNm);

			if (asUMDRINm.Pos(_asUMDRINm) > 0)//210201//
			{
				asUMDRICd.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA2[i].cSggCd, frmMain->m_vSIDOCODE_DATA2[i].cUmdCd, frmMain->m_vSIDOCODE_DATA2[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA3.size(); i++)
		{
			asUMDRINm.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA3[i].cSggNm, frmMain->m_vSIDOCODE_DATA3[i].cUmdNm, frmMain->m_vSIDOCODE_DATA3[i].cRiNm);

			if (asUMDRINm.Pos(_asUMDRINm) > 0)//210201//
			{
				asUMDRICd.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA3[i].cSggCd, frmMain->m_vSIDOCODE_DATA3[i].cUmdCd, frmMain->m_vSIDOCODE_DATA3[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA4.size(); i++)
		{
			asUMDRINm.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA4[i].cSggNm, frmMain->m_vSIDOCODE_DATA4[i].cUmdNm, frmMain->m_vSIDOCODE_DATA4[i].cRiNm);

			if (asUMDRINm.Pos(_asUMDRINm) > 0)//210201//
			{
				asUMDRICd.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA4[i].cSggCd, frmMain->m_vSIDOCODE_DATA4[i].cUmdCd, frmMain->m_vSIDOCODE_DATA4[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA5.size(); i++)
		{
			asRiNm.printf("%s", frmMain->m_vSIDOCODE_DATA5[i].cRiNm);
			if(asRiNm.Trim().SubString(asRiNm.Trim().Length()-1, 2) == "리")
				asRiNm = asRiNm.SubString(1, asRiNm.Trim().Length()-2);

			asUMDRINm.printf("%s", frmMain->m_vSIDOCODE_DATA5[i].cRiNm);

			if (asUMDRINm.Pos(_asUMDRINm) > 0)//210201//
			{
				asUMDRICd.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA5[i].cSggCd, frmMain->m_vSIDOCODE_DATA5[i].cUmdCd, frmMain->m_vSIDOCODE_DATA5[i].cRiCd);
				bFound  = true;
				break;
			}
			else
			{
				if (asRiNm.Pos(_asUMDRINm) > 0)//210201//
				{
					asUMDRICd.printf("%s%s%s", frmMain->m_vSIDOCODE_DATA5[i].cSggCd, frmMain->m_vSIDOCODE_DATA5[i].cUmdCd, frmMain->m_vSIDOCODE_DATA5[i].cRiCd);
					bFound  = true;
					break;
				}
			}
		}
		if(bFound)
			goto result;
	}
	else
	{
		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA1.size(); i++)
		{
			asUMDRINm.printf("%s%s", frmMain->m_vSIDOCODE_DATA1[i].cUmdNm, frmMain->m_vSIDOCODE_DATA1[i].cRiNm);

			if (_asUMDRINm == asUMDRINm)
			{
				asUMDRICd.printf("%s%s", frmMain->m_vSIDOCODE_DATA1[i].cUmdCd, frmMain->m_vSIDOCODE_DATA1[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA2.size(); i++)
		{
			asUMDRINm.printf("%s%s", frmMain->m_vSIDOCODE_DATA2[i].cUmdNm, frmMain->m_vSIDOCODE_DATA2[i].cRiNm);

			if (_asUMDRINm == asUMDRINm)
			{
				asUMDRICd.printf("%s%s", frmMain->m_vSIDOCODE_DATA2[i].cUmdCd, frmMain->m_vSIDOCODE_DATA2[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;


		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA3.size(); i++)
		{
			asUMDRINm.printf("%s%s", frmMain->m_vSIDOCODE_DATA3[i].cUmdNm, frmMain->m_vSIDOCODE_DATA3[i].cRiNm);

			if (_asUMDRINm == asUMDRINm)
			{
				asUMDRICd.printf("%s%s", frmMain->m_vSIDOCODE_DATA3[i].cUmdCd, frmMain->m_vSIDOCODE_DATA3[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA4.size(); i++)
		{
			asUMDRINm.printf("%s%s", frmMain->m_vSIDOCODE_DATA4[i].cUmdNm, frmMain->m_vSIDOCODE_DATA4[i].cRiNm);

			if (_asUMDRINm == asUMDRINm)
			{
				asUMDRICd.printf("%s%s", frmMain->m_vSIDOCODE_DATA4[i].cUmdCd, frmMain->m_vSIDOCODE_DATA4[i].cRiCd);
				bFound  = true;
				break;
			}
		}
		if(bFound)
			goto result;

		//
		for (int i = 0; i < (int)frmMain->m_vSIDOCODE_DATA5.size(); i++)
		{
			asRiNm.printf("%s", frmMain->m_vSIDOCODE_DATA5[i].cRiNm);
			if(asRiNm.Trim().SubString(asRiNm.Trim().Length()-1, 2) == "리")
				asRiNm = asRiNm.SubString(1, asRiNm.Trim().Length()-2);

			asUMDRINm.printf("%s", frmMain->m_vSIDOCODE_DATA5[i].cRiNm);

			if (_asUMDRINm == asUMDRINm)
			{
				asUMDRICd.printf("%s%s", frmMain->m_vSIDOCODE_DATA5[i].cUmdCd, frmMain->m_vSIDOCODE_DATA5[i].cRiCd);
				bFound  = true;
				break;
			}
			else
			{
				if (_asUMDRINm == asRiNm)
				{
					asUMDRICd.printf("%s%s", frmMain->m_vSIDOCODE_DATA5[i].cUmdCd, frmMain->m_vSIDOCODE_DATA5[i].cRiCd);
					bFound  = true;
					break;
				}
			}
		}
		if(bFound)
			goto result;
	}

result:
	return asUMDRICd;
}
//---------------------------------------------------------------------------

////공휴일체크//
//int cFunc::funcCheckComHoliday(TDateTime _solarDt)
//{
//	AnsiString asDate	= _solarDt.FormatString("MMDD");
//	AnsiString asLunar;
//	int nPeriod	= 0;
//	int day	= 0;
//
//	lunarDt	= funcChangeSolarToLunar((_solarDt + nPeriod)->Date);
//	asLunar	= lunarDt.FormatString("MMDD");
//
//	//타겟일자가 공휴일이면 하루를 더한다//
//	if( asDate == "0301" || asDate	== "0606" || asDate	== "0815"
//	 || asDate	== "1003" || asDate	== "1009" || asDate	== "1225")
//	{
//		nPeriod = 1;
//	}
//	//대체공휴일은 설날, 추석날, 어린이날//
//	else if( asDate	== "0505" )
//	{
//		nPeriod = 1;
//
//		//대체공휴일//
//		day = _solarDt->Date.DayOfWeek();
//		if (day == 6)//토요일
//			nPeriod	+= 2;
//		if (day == 7)//일요일
//			nPeriod	+= 1;
//	}
//	//음력일자 확인//
//	else if(asLunar == "0101" || asLunar == "0815")
//	{
//		nPeriod = 2;
//
//		//대체공휴일//
//		day = (lunarDt)->Date.DayOfWeek();
//		if (day == 6 || day == 7)//토요일, 일요일
//			nPeriod	+= 1;
//	}
//	else if(asLunar == "0814")
//	{
//		nPeriod = 3;
//
//		//대체공휴일//
//		day = (lunarDt)->Date.DayOfWeek();
//		if (day == 6 || day == 7)//토요일, 일요일
//			nPeriod	+= 1;
//	}
//	else if(asLunar == "0102" || asLunar == "0816")
//	{
//		nPeriod = 1;
//
//		//대체공휴일//
//		day = (lunarDt)->Date.DayOfWeek();
//		if (day == 6 || day == 7)//토요일, 일요일
//			nPeriod	+= 1;
//	}
//	else if(asLunar == "0408")
//	{
//		nPeriod = 1;
//	}
//
//	// 처리기간
//	day = (_solarDt + nPeriod)->Date.DayOfWeek();
//	if (day == 6)//토요일
//		nPeriod	+= 2;
//	if (day == 7)//일요일
//		nPeriod	+= 1;
//
//	return lunarDt;
//}
////---------------------------------------------------------------------------

//음력변환
TDateTime cFunc::funcChangeSolarToLunar(TDateTime _solarDt)
{
	unsigned short pYear,pMonth,pDay;
	TDateTime	lunarDt;

//	_solarDt.DecodeDate(&pYear,&pMonth,&pDay);
//	_solarDt->isLeap	= alse;
//	_solarDt->solYear	= pYear;
//	_solarDt->solMonth	= pMonth;
//	_solarDt->solDay	= pDay;
//	_solarDt->isLeap	= true;
//	_solarDt->Solar2Lunar();
//	lunarDt = TDateTime(_solarDt->lunYear, _solarDt->lunMonth, _solarDt->lunDay);

	return lunarDt;
}
//---------------------------------------------------------------------------
//양력변환
TDateTime cFunc::funcChangeLunarToSolar(TDateTime _lunarDt)
{
    unsigned short pYear,pMonth,pDay;
	TDateTime	solarDt;

//	_lunarDt.DecodeDate(&pYear,&pMonth,&pDay);
//	_lunarDt->isLeap	= false;
//	_lunarDt->lunYear	= pYear;
//	_lunarDt->lunMonth	= pMonth;
//	_lunarDt->lunDay	= pDay;
//	_lunarDt->isLeap	= true;
//	_lunarDt->Lunar2Solar();
//	solarDt = TDateTime(_lunarDt->solYear, _lunarDt->solMonth, _lunarDt->solDay);

	return solarDt;
}
//---------------------------------------------------------------------------

AnsiString cFunc::funcStringReplaceDoc08(AnsiString _asStr)
{
	AnsiString  asData;

	asData	= StringReplace(_asStr, " ", "", TReplaceFlags() << rfReplaceAll);
	asData	= StringReplace(_asStr, "-", "|", TReplaceFlags() << rfReplaceAll);
	asData	= StringReplace(_asStr, "(", "", TReplaceFlags() << rfReplaceAll);
	asData	= StringReplace(_asStr, ")", "", TReplaceFlags() << rfReplaceAll);

	return asData;
}
//---------------------------------------------------------------------------

//===========================================================================
// 중복코드 함수처리 : PATH_NAME (DB Path -> Local Path)
//===========================================================================
AnsiString cFunc::funcGetDBtoLocalPath(AnsiString _asPathName)
{
	AnsiString  asPathName = _asPathName;
	asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
	return asPathName;
}
//---------------------------------------------------------------------------

//===========================================================================
//[REQ_260715_#2.DB내 권번호 변경]
// 권번호(KWON_NO) 처리
// (과거) 숫자 4자리//
// (현재) 영문 + 숫자4자리(울산 울주군)//
//===========================================================================
AnsiString cFunc::funcGetKwonNo(AnsiString _asKwonNo)
{
	AnsiString  asKwonNo = _asKwonNo;
	if( asKwonNo.IsEmpty() )	asKwonNo = "-권";

	if(IsNumberString(_asKwonNo))
	{
		asKwonNo.sprintf("%d권", _asKwonNo.ToInt());
	}
	else if(_asKwonNo.Length() == 5)
	{
		asKwonNo.sprintf("%s%d권", _asKwonNo.SubString(1, 1), _asKwonNo.SubString(2, _asKwonNo.Length()-1).ToInt());
	}

	asKwonNo	= StringReplace(asKwonNo, "(null)", "-", TReplaceFlags() << rfReplaceAll);
	return asKwonNo;
}
//---------------------------------------------------------------------------

