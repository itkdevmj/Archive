//---------------------------------------------------------------------------

#ifndef untSearchH
#define untSearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//#include "common.h"
//#include "mainSrc.h"

//---------------------------------------------------------------------------
class TfrmSearch : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations

public:		// User declarations

	TStringList *qry;

	AnsiString  m_asSelectPnu;
	AnsiString  m_asOldCaption;//#SEJONGPNU
	AnsiString  asQryFile;
	bool 		searchSuccess[DF_DOC_CNT];
	bool		m_bKindDoc;//상세검색 시 문서구분을 선택했는지//검색결과 표시를 달리할 때 사용//
	bool		m_bInputDoc;//상세검색 시 문서종류 선택했는지//검색결과 표시를 달리할 때 사용//구대장-부책/카드//


	void __fastcall	TfrmSearch::funcSetSearchFinish();//int _nIndex);

	//==========================================================================
	// 통합&상세검색//
	//==========================================================================
	void __fastcall TfrmSearch::funcInitSearchSuccess();
	void __fastcall TfrmSearch::funcClearResultVector();
	void __fastcall TfrmSearch::funcSearch();
	void __fastcall TfrmSearch::funcSearchSelect(int nType);
	void __fastcall TfrmSearch::funcTotalSearchJibun();
	void __fastcall TfrmSearch::funcTotalSearchKeyword();
	void __fastcall TfrmSearch::func_Search1();
	void __fastcall TfrmSearch::func_Search2();
	void __fastcall TfrmSearch::func_Search3();
	void __fastcall TfrmSearch::func_Search4();
	void __fastcall TfrmSearch::func_Search5();
	void __fastcall TfrmSearch::func_Search6();
	void __fastcall TfrmSearch::func_Search7();
	void __fastcall TfrmSearch::func_Search8();
	void __fastcall TfrmSearch::func_Search9();
	void __fastcall TfrmSearch::func_Search10();
	void __fastcall TfrmSearch::func_Search11();
	void __fastcall TfrmSearch::func_Search12();
	void __fastcall TfrmSearch::func_Search13();
	void __fastcall TfrmSearch::func_Search14();
	void __fastcall TfrmSearch::func_Search15();
	void __fastcall TfrmSearch::func_Search16();
	void __fastcall TfrmSearch::func_Search17();
	void __fastcall TfrmSearch::func_Search18();
	void __fastcall TfrmSearch::func_Search20();//231020//GAGAMLAYER//
	void __fastcall TfrmSearch::func_SearchMemo();


	void __fastcall TfrmSearch::funcSaveLog(int nType, int _nDoc, AnsiString _asSql);



	//==========================================================================
	// 영역검색//
	//==========================================================================
	void __fastcall TfrmSearch::funcSpaceSearch();
	void __fastcall TfrmSearch::funcSpaceSearchData(int nType);
	void __fastcall TfrmSearch::funcSpaceSearchData1();
	void __fastcall TfrmSearch::funcSpaceSearchData2();
	void __fastcall TfrmSearch::funcSpaceSearchData3();
	void __fastcall TfrmSearch::funcSpaceSearchData4();
	void __fastcall TfrmSearch::funcSpaceSearchData5();
	void __fastcall TfrmSearch::funcSpaceSearchData6();
	void __fastcall TfrmSearch::funcSpaceSearchData7();
	void __fastcall TfrmSearch::funcSpaceSearchData8();
	void __fastcall TfrmSearch::funcSpaceSearchData9();
	void __fastcall TfrmSearch::funcSpaceSearchData11();
	void __fastcall TfrmSearch::funcSpaceSearchData12();
	void __fastcall TfrmSearch::funcSpaceSearchData14();
	void __fastcall TfrmSearch::funcSpaceSearchData17();
	void __fastcall TfrmSearch::funcSpaceSearchData18();
	void __fastcall TfrmSearch::funcSpaceSearchData20();//231020//GAGAMLAYER//
	void __fastcall TfrmSearch::funcSpaceSearchDataMemo();

	bool m_bDoc07Check;
	AnsiString m_sDoc07DohoCheck;


	__fastcall TfrmSearch(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSearch *frmSearch;
//---------------------------------------------------------------------------
#endif
