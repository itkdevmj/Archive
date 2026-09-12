//---------------------------------------------------------------------------

#ifndef untAIOCRDataH
#define untAIOCRDataH
//---------------------------------------------------------------------------
class classAIOCRData
{
private:
public:
	classAIOCRData();
	~classAIOCRData();

	//======================================================================
	//frmAlphaDoc8사용//vector<OLDLANDDOC_INFO_STRUCT> 				m_vOldLandDocInfo;//구대장 한글화 기본정보//
	vector<DOCUMENT08_HIS_STRUCT> 				m_ResultDoc08His;//구대장 연혁//
	vector<DOCUMENT08_OWNINFO_STRUCT> 			m_ResultDoc08OwnInfo;//구대장 소유자정보//
	vector<DOCUMENT08_SHAREOWN_STRUCT> 			m_ResultDoc08ShareOwn;//구대장 공유지연명부//
//#한글화편집#DirectTable//
	vector<DOCUMENT08_HISTORY_STRUCT> 			m_ResultDoc08_History;//구대장(관리자편집_내역)[저장용]//
	vector<DOCUMENT08_HISTORY_STRUCT> 			m_ResultDoc08_HistoryStat;//구대장(관리자편집_내역)[통계용]//

	//======================================================================
	int							m_nHistoryCount;//m_vHISTORY.size()
	int							m_nOwnInfoCount;//m_vOWNINFONAME.size()
	int							m_nShareOwnCount;//m_vSHAREOWNNAME.size()//#SHAREOWN#
	//======================================================================

	AnsiString 					m_asLand;
	AnsiString 					m_asJibun;
	AnsiString 					m_asLevel;
	AnsiString 					m_asMemo;
	AnsiString					m_asCaution;
	//
	vector<DATA_STRUCT>			m_vLAND;
	vector<DATA_STRUCT>			m_vJIBUN;
	vector<DATA_STRUCT>			m_vLEVEL;
	vector<DATA_STRUCT>			m_vMEMO;
	vector<DATA_STRUCT>			m_vCAUTION;

	vector<DATA_STRUCT>			m_vJIMOK;
	vector<DATA_STRUCT>			m_vAREA;
	vector<DATA_STRUCT>			m_vAREA1;
	vector<DATA_STRUCT>			m_vVALUE1;
	vector<DATA_STRUCT>			m_vVALUE2;
	vector<DATA_STRUCT>			m_vHISTORY;
	AnsiString 					m_asJimok;
	AnsiString 					m_asArea;
	AnsiString 					m_asArea1;
	AnsiString 					m_asValue1;
	AnsiString 					m_asValue2;
	AnsiString 					m_asHistory;
	//
	vector<DATA_STRUCT>			m_vOWNINFODATE;
	vector<DATA_STRUCT>			m_vOWNINFOREASON;
	vector<DATA_STRUCT>			m_vOWNINFOADDRESS;
	vector<DATA_STRUCT>			m_vOWNINFONAME;
	AnsiString 					m_asOwnInfoDate;
	AnsiString 					m_asOwnInfoReason;
	AnsiString 					m_asOwnInfoAddress;
	AnsiString 					m_asOwnInfoName;
	//======================================================================
	//#SHAREOWN#
	vector<DATA_STRUCT>			m_vSHAREOWNDATE;
	vector<DATA_STRUCT>			m_vSHAREOWNREASON;
	vector<DATA_STRUCT>			m_vSHAREOWNRATIO;
	vector<DATA_STRUCT>			m_vSHAREOWNADDRESS;
	vector<DATA_STRUCT>			m_vSHAREOWNNAME;
	vector<DATA_STRUCT>			m_vSHARECOMMENT;
	AnsiString 					m_asShareOwnDate;
	AnsiString 					m_asShareOwnReason;
	AnsiString 					m_asShareOwnRatio;
	AnsiString 					m_asShareOwnAddress;
	AnsiString 					m_asShareOwnName;
	//======================================================================

	//======================================================================
	void __fastcall funcReadDocument08His();
	void __fastcall funcReadDocument08OwnInfo();
	void __fastcall funcReadDocument08ShareOwn();

	//======================================================================
	// AIOCR 번역 데이터를 표시//
	//======================================================================
	//열람화면//한글표시 이동거리//
	//[0]:Land,[1]:Jibun,[2]:Memo
	//[3~7]:History
	//[8-11]:OwnInfo
	//[12]:Caution
	TPoint						m_nDoc8MouseGap[DOC08_SUBBOOK_CNT];
	DOC8_BASEPOS_STRUCT         m_bpDoc8OwnInfo[DOC08_SUBBOOK_CNT];
	void __fastcall 			funcGetDoc8ViewBoundary();
	void __fastcall 			funcSetDoc8ViewBoundary();
	int __fastcall 				funcGetStartW(int _nType, int _nIndex, int _nCount, int _nTextW);
	int __fastcall 				funcGetStartH(int _nType, int _nIndex, int _nCount, int _nTextH);
	//======================================================================
	void __fastcall 			funcRedrawOwnInfo();

	//=================================================================
	//공유지연명부//
	//=================================================================
	//[0]:Land,[1]:Jibun,[2]:Memo
	//[3~7]:ShareOwn
	//[8]:Caution
	//[9]:Comment
	TPoint						m_nDoc8MouseGapShare[DOC08_SHAREOWN_CNT];
	DOC8_BASEPOS_STRUCT         m_bpDoc8ShareOwn[DOC08_SHAREOWN_CNT];
	int							m_nTopBottomGap;//OVERLAP.공유지연명부.윗칸/아랫칸 높이 차이//
	void __fastcall 			funcGetDoc8ViewBoundaryShare();
	void __fastcall 			funcSetDoc8ViewBoundaryShare();
	//======================================================================
	void __fastcall 			funcRedrawShareOwn();
	void __fastcall 			funcInitShareOwn();
	void __fastcall 			funcDeleteShareOwn();
	void __fastcall 			funcGetShareOwn();
	//=================================================================
	TStringList 				*m_slShareOwnData[DOC08_SHAREOWN_CNT][52];//Cell > Line Data//241203//#등급#추가//
	TStringList 				*m_slShareOwnData2[DOC08_SHAREOWN_CNT][52];//Cell > Line Height (nSumHeight)//241203//#등급#추가//
	vector<DOC8_DELETEPOS_STRUCT>	m_vShareOwnDeletePos[DOC08_SHAREOWN_CNT][52];//241203//#등급#추가//
	void __fastcall 			funcGetStringListShareOwn();
	vector<SHARP_POSITION_STRUCT>	m_vSharpPos;
	int							m_nSharpWidthOverlap;//부분삭제(취소선) 두께//
	void __fastcall 			funcSetSharpPosition(int nSTTx, int nSTTy, int nENDx, int nENDy);
	void __fastcall 			funcRedrawStringListShareOwn();
	void __fastcall 			funcInitStringListShareOwn();
	void __fastcall 			funcDeleteStringListShareOwn();

};
//---------------------------------------------------------------------------
extern classAIOCRData *eAIOCRData;
#endif
