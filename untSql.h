//---------------------------------------------------------------------------

#ifndef untSqlH
#define untSqlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmSql : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations

	SQLHENV     m_hEnv;
	SQLHDBC     m_hDbc;
	SQLHSTMT    m_hStmt;
	SQLCHAR     m_InCon[255];
	SQLCHAR     m_OutCon[1024];
	SQLSMALLINT m_cbOutCon;

	//============================================================
	// Copy LMReq to SmartOneStop
	//============================================================
	SQLHENV     m_hEnvC;
	SQLHDBC     m_hDbcC;
	SQLHSTMT    m_hStmtC;
	SQLCHAR     m_InConC[255];
	SQLCHAR     m_OutConC[1024];
	SQLSMALLINT m_cbOutConC;

	//============================================================
	//LONGBLOB DOWNLOAD//
	//============================================================
	SQLHENV     m_hEnvDataSize;
	SQLHDBC     m_hDbcDataSize;
	SQLHSTMT    m_hStmtDataSize;
	SQLCHAR     m_InConDataSize[255];
	SQLCHAR     m_OutConDataSize[1024];
	SQLSMALLINT m_cbOutConDataSize;

	//============================================================
	//LONGBLOB IMAGE//201027
	//============================================================
	SQLHENV     m_hEnvImg;
	SQLHDBC     m_hDbcImg;
	SQLHSTMT    m_hStmtImg;
	SQLCHAR     m_InConImg[255];
	SQLCHAR     m_OutConImg[1024];
	SQLSMALLINT m_cbOutConImg;


	//코드 변환용
	STRUCTCODECONVERT tempCodeConvert;
	vector<STRUCTCODECONVERT> m_v_STRUCTCODECONVERTLP;

	//연속지적도 상에 보여줄 심볼정보//
	KINDOFDOC_STRUCT 			tempKINDOFSYMBOL;
	vector<KINDOFDOC_STRUCT> 	m_vKINDOFSYMBOLDATA;

	int 						m_nKindOfDocIndex;
	KINDOFDOC_STRUCT 			tempKINDOFDOC;
	vector<KINDOFDOC_STRUCT> 	m_vKINDOFDOCDATA;

	MEMOLANDKEYDATA_STRUCT 			tempMEMOLANDKEYDATA;
	vector<MEMOLANDKEYDATA_STRUCT> 	m_vMEMOLANDKEYDATA;

	MEMODATA_STRUCT 			tempMEMODATA;
	vector<MEMODATA_STRUCT> 	m_vMEMODATA;

	MEMOINFO_STRUCT 		tempBATCHMEMOINFO;
	vector<MEMOINFO_STRUCT> m_vBATCHMEMOINFO;

	MEMOINFO_STRUCT 		tempALLMEMOINFO;
	vector<MEMOINFO_STRUCT> m_vALLMEMOINFO;
	vector<MEMOINFO_STRUCT> m_vALLPHOTOINFO;
//	MEMOVECTOR_STRUCT tempALLVECTORINFO;
//	vector<MEMOVECTOR_STRUCT> m_vALLVECTORINFO;

	polyObject 				tMemoPoly;
	vector<polyObject> 		m_vMEMOPOLY;//영역있는 메모들의 POLYGON을 그려주기 위함//


	//***************************************************************************
	// Thumbnail 이미지의 DB 정보//
	//***************************************************************************
	vector<DOCUMENT01_STRUCT> 		m_ResultDoc01DBInfo;
	vector<DOCUMENT02_STRUCT> 		m_ResultDoc02DBInfo;
	vector<DOCUMENT03_STRUCT> 		m_ResultDoc03DBInfo;
	vector<DOCUMENT04_STRUCT> 		m_ResultDoc04DBInfo;
	vector<DOCUMENT05_STRUCT> 		m_ResultDoc05DBInfo;
	vector<DOCUMENT06_STRUCT> 		m_ResultDoc06DBInfo;
	vector<DOCUMENT07_STRUCT> 		m_ResultDoc07DBInfo;
	vector<DOCUMENT08_STRUCT> 		m_ResultDoc08DBInfo;
	vector<DOCUMENT09_STRUCT> 		m_ResultDoc09DBInfo;
	vector<DOCUMENT11_STRUCT> 		m_ResultDoc11DBInfo;
	vector<DOCUMENT12_STRUCT> 		m_ResultDoc12DBInfo;
	vector<DOCUMENT13_STRUCT> 		m_ResultDoc13DBInfo;
	vector<DOCUMENT14_STRUCT> 		m_ResultDoc14DBInfo;
	vector<DOCUMENT15_STRUCT> 		m_ResultDoc15DBInfo;
	vector<DOCUMENT17_STRUCT> 		m_ResultDoc17DBInfo;
	vector<DOCUMENT18_STRUCT> 		m_ResultDoc18DBInfo;
	vector<DOCUMENT20_STRUCT> 		m_ResultDoc20DBInfo;//231030//GAGAMLAYER in LandArchive//
	int								m_ResultDoc01DBCount;
	int								m_ResultDoc02DBCount;
	int								m_ResultDoc03DBCount;
	int								m_ResultDoc04DBCount;
	int								m_ResultDoc05DBCount;
	int								m_ResultDoc06DBCount;
	int								m_ResultDoc07DBCount;
	int								m_ResultDoc08DBCount;
	int								m_ResultDoc09DBCount;
	int								m_ResultDoc11DBCount;
	int								m_ResultDoc12DBCount;
	int								m_ResultDoc13DBCount;
	int								m_ResultDoc14DBCount;
	int								m_ResultDoc15DBCount;
	int								m_ResultDoc17DBCount;
	int								m_ResultDoc18DBCount;
	int								m_ResultDoc20DBCount;//231030//GAGAMLAYER in LandArchive//

	//===========================================================================
	SearchNode	mOptionsSearchNode;
	void funcSettingOptionsTreeView();

	bool __fastcall func_QryProcess(AnsiString qry);
	bool __fastcall func_QryProcessC(AnsiString qry);//220214//COPY_LMREQ_TO_SMARTONESTOP
	bool __fastcall func_SetSeqNoQryProcess(AnsiString qry);

	//기본 DB자료 읽기
	void __fastcall func_readConfigData();
	void __fastcall func_readMainIni();
	void __fastcall func_readCodeConvert();
	int __fastcall 	funcSQLReadCount(AnsiString _qry);//개수 또는 int value 1개를 반환//
	AnsiString __fastcall func_readLandcd(AnsiString _qry);
	AnsiString __fastcall func_ConvertSidoCDtoNM(AnsiString _sidosggcd);
	AnsiString __fastcall func_ConvertUmdCDtoNM(AnsiString _umdcd);//210204//#LOADING_TEST//
	AnsiString __fastcall func_ConvertRiCDtoNM(AnsiString _ricd);//210204//#LOADING_TEST//
	AnsiString __fastcall func_ConvertAddressToEmdRicd(AnsiString _nm);
	AnsiString __fastcall func_ConvertAddressToEmdcd(AnsiString _nm);
	AnsiString __fastcall func_ConvertAddressToRicd(AnsiString _sggumdcd, AnsiString _nm);
	AnsiString __fastcall func_ConvertAddressToLandcd(AnsiString _address, bool _bBubn);//부번을 채울것인지//
	AnsiString __fastcall func_FindFirstLandcd(AnsiString _landcd);
	void __fastcall func_readKindofSymbol();//연속지적도상에 표현할 수 있는 지번만 심볼정보를 갖고 있는다//
	void __fastcall func_readKindofDocData(AnsiString _asLandCd);//검색지번에 해당하는 데이터만 검색한다//
	void __fastcall func_readMemoLandkeyData();
	void __fastcall func_readSelectMemoData(AnsiString _landcd);
	void __fastcall func_readReferenceCode();
	int __fastcall  func_readSidoCode();

	void __fastcall funcReadDocument01(AnsiString qry);
	int  __fastcall funcSelReadDoc01Group(int _nIndex);//200313//TEST//
	//200313//TEST//void __fastcall funcSelReadDoc01Group(DOCUMENT01_STRUCT mSelGroupDoc1);
	void __fastcall funcReadDocument02(AnsiString qry);
	int  __fastcall funcSelReadDoc02Group(int _nIndex);
	void __fastcall funcReadDocument03(AnsiString qry);
	void __fastcall funcReadDocument04(AnsiString qry);
	//230403//#ADD_FUNC_DOC04_44130//
	int __fastcall funcSelReadDoc04Group(int _nIndex);//230502//그룹핑기준 : LAW_NO//
	void __fastcall funcReadDocument05(AnsiString qry);
	int  __fastcall funcSelReadDoc05Group(int _nIndex);
	void __fastcall funcReadDocument06(AnsiString qry);
	int  __fastcall funcSelReadDoc06Group(int _nIndex);
	void __fastcall funcReadDocument07(AnsiString qry);
//	void __fastcall funcSelReadDoc07Doho(DOCUMENT07_STRUCT mSelDohoDoc7);
//	void __fastcall funcSelReadDoc07Etc(DOCUMENT07_STRUCT mSelDohoDoc7);
	void __fastcall funcReadDocument08(AnsiString qry);
	void __fastcall funcReadDocument09(char *cQry);
	void __fastcall func_readRoadNameList(AnsiString qry);
	void __fastcall funcReadDocument11(AnsiString qry);
	void __fastcall funcReadDocument12(AnsiString qry);
	void __fastcall funcReadDocument13(AnsiString qry);
	void __fastcall funcReadDocument14(AnsiString qry);
	int  __fastcall funcSelReadDoc14Group(int _nIndex);
	void __fastcall funcReadDocument15(AnsiString qry);
	int  __fastcall funcSelReadDoc15Group(int _nIndex);
	void __fastcall funcReadDocument16(AnsiString qry);
	void __fastcall funcReadDocument17(AnsiString qry);

	//===========================================================================
	// #좌표계산부#
	//===========================================================================
	void __fastcall funcReadDocument18All();
	void __fastcall funcReadDocument18(AnsiString qry);

	//==================================================================
	//231020//GAGAMLAYER in LandArchive
	//==================================================================
	void __fastcall funcReadDocument20(AnsiString _asSqlQry);

	void __fastcall funcReadDocument07Index();
	void __fastcall funcReadDocument07();
//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
	void __fastcall funcQrySelect_DOCUMENT07_MAPPOINT(bool _bSub, int _nIndex, AnsiString _asDetailQry);//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
//OLD//	void __fastcall funcQrySelect_DOCUMENT07_MAPPOINT(bool _bSub, int _nIndex);//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
//=============================================================================
	//201227//void __fastcall funcQrySelect_DOCUMENT07_KINDOFDOC(AnsiString _asPathName);//201008//
	void __fastcall funcQrySelect_DOCUMENT07_PNU(bool _bSub, AnsiString _asPnu);//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	int __fastcall 	funcGetIndexDOCUMENT07PNU(AnsiString _asPathName);//201014//
	void __fastcall funcQrySelect_LAND_INFO_MAPPOINT(bool _bSub, AnsiString _asPnu);//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	void __fastcall funcQrySelect_LAND_INFO_MAPPOINT_PREPNU(AnsiString _asPnu);
	bool __fastcall funcQryInsert_DOCUMENT07_BASEXY(int _nType, double _nX, double _nY);
	void __fastcall funcSidoCodeLikeQuery(AnsiString _asKeyWord);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//220211//COPY_LMREQ_DATA//
	AnsiString __fastcall funcGetUmdRiCd(AnsiString _asUmdRiNm);
	AnsiString __fastcall funcGetUmdRiNm(AnsiString _asUmdRiCd);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	void __fastcall funcZoneCodeLikeQuery(AnsiString _asKeyWord);
	void __fastcall funcReadMemo(AnsiString qry);//메모 검색//

	void __fastcall funcReadDocumentMemoBatch(AnsiString _asKeyword);
	void __fastcall funcReadDocumentMemoAll(); //모든 메모 데이터//
	void __fastcall funcReadDocumentMemoVector(AnsiString _asPoiKey);
	void __fastcall funcReadDocThumbPathList(int _nDocNo, AnsiString _asKwonNo, int _nGroupNo, int _nGroupNo1, AnsiString _asPath);
	//250429//[Add]미리보기-필터링//
	void __fastcall funcReadThumbDocKindList(AnsiString _asSqlQry);
	void __fastcall funcReadDocFTPPathList(int _nDocNo, AnsiString _asKwonNo, int _nGroupNo, int _nGroupNo1, AnsiString _asPath);
	void __fastcall funcReadDoc07PathList(AnsiString _asPathName);
	void __fastcall funcQrySelect_LAND_INFO();

	void __fastcall funcSelectPnuDoc01(AnsiString qry);

	//==========================================================================
	// Thumbnail 이미지의 DB 정보//
	//==========================================================================
	void __fastcall funcReadDocDBInfo(int _nDocNo, AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc01DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc02DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc03DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc04DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc05DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc06DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc07DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc07PnuDBInfo(AnsiString _asKwon, AnsiString _asFilePath);//201227//
	void __fastcall funcReadDoc08DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc09DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc11DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc12DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc13DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc14DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc15DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc17DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc18DBInfo(AnsiString _asKwon, AnsiString _asFilePath);
	void __fastcall funcReadDoc20DBInfo(AnsiString _asKwon, AnsiString _asFilePath);//231021//GAGAMLAYER in LandArchive
	//---------------------------------------------------------------------------


	//==========================================================================
	// 지적도 설정 정보//
	//==========================================================================
	void __fastcall funcSQLUpdateSpatialConfig(AnsiString _asLayerName, int _nShowUse);
	void __fastcall funcQryInsertDoc8Jumin(AnsiString _asDBStr);

	//231118//#CODE_UNITY#//
	//=============================================================================
	// INFORMATION_SCHEMA.COLUMNS 에 조건에 해당하는 TABLE, COLUMN 존재 여부 확인//
	//=============================================================================
	bool __fastcall funcSQLCheckTable(AnsiString _asTable, AnsiString _asColumn);

	//==========================================================================
	// 구대장_소유주명 정보를 변경//#OWNNAMES#44270#
	//==========================================================================
	bool __fastcall funcQryInsertDoc8OwnNames(AnsiString _asDBStr);
	//==========================================================================
	// 구대장_[연혁][소유자정보] 테이블명을 갖고 있는지 확인//#OWNINFO#44760#
	//==========================================================================
	bool __fastcall funcSQLCountDocument08OwnInfoName(AnsiString _asSqlQry);//201112//
	//==========================================================================
	// 구대장_[연혁][소유자정보] 데이터 읽기//#OWNINFO#
	//==========================================================================
	void __fastcall funcSQLReadOldLandDocInfo();
	void __fastcall funcReadDocument08Pnu(AnsiString _asPathName);
	void __fastcall funcReadDocument08His();
	void __fastcall funcReadDocument08HisDel();//241011//구대장 연혁(삭제선)//
	void __fastcall funcReadDocument08OwnInfo();
//======================================================================
//231118//#SHAREOWN#
//구대장 공유지연명부 소유자정보//
	void __fastcall funcReadDocument08ShareOwn();
//======================================================================
	//==========================================================================
	// 구대장_[연혁][소유자정보] 데이터 쓰기//#OWNINFO#
	//==========================================================================
	bool __fastcall funcSQLWriteOldLandDocInfo(int _nType);// WRITE TB_OLDLANDDOC_INFO//
	bool __fastcall funcSQLUpdateOldLandDocPathlist();// Update TB_OLDLANDDOC_PATHLIST//
	bool __fastcall funcWriteHistory(int _nType, int _nRow);
	bool __fastcall funcWriteOwnInfo(int _nType, int _nRow);
	//==========================================================================
	// 구대장_[소유자정보] 데이터 쓰기//#OWNINFO# => 공유지연명부//
	//==========================================================================
	//각 테이블에서 데이터 개수를 확인 후에 어떤 테이블에 Write하는지 결정하기 위해 체크//
	bool __fastcall funcSQLWriteOldLandDocInfo2(int _nType);// WRITE TB_OLDLANDDOC_INFO//
	bool __fastcall funcWriteShareOwn(int _nType, int _nCol);
//===========================================================================




	//============================================================
	void 		__fastcall funcReadSejongPnu(char *cQry);
//v1.0.0.5//NotUsed//	void 		__fastcall funcReadSejongOldCaption(char *cQry);


	//===========================================================================
	// m_vSHPPOLYCBND를 기준으로 LAND_INFO 생성하기//
	//===========================================================================
	void 		__fastcall funcSQLInsertLandInfo();


	//===========================================================================
	// ENCRYPT == 1 시군에서 비암호화문서정보 DB에 저장한다//
	//===========================================================================
	void 		__fastcall funcSQLCreateTableDecryptFile();
	int 		__fastcall funcSQLInsertDecryptFile(int _nType);


	//==============================================
	//	파일 binary data upload
	//==============================================
	char* buffer;
	int __fastcall 					funcSQLMaxSeqNoLMReqAttach();
	void __fastcall 				funcDownloadAttach();
	void __fastcall 				funcDownloadFileAttach(int _nIndex);//TB_ATTACH.RESOURCE_DATA DOWNLOAD//
	int __fastcall 					funcReadDataLength(AnsiString _asSqlQry);
	void __fastcall 				funcSQLReadTbAttach();//파일첨부//



	//210220
	//==============================================
	int __fastcall 					funcExistsDBTableColumnData(int _nType);//TABLE OR COLUMN 확인//
	int __fastcall 					funcChangeDBTableColumnData(int _nType);//TABLE OR COLUMN 정리//
	int __fastcall 					funcCheckDBTableColumnData(int _nType);//TABLE OR COLUMN or DATA 확인//

	//==================================================
	//파일저장 다운로드사유 데이터 관리 테이블 생성//210303//#TB_COPY_DNLD
	//==================================================
	void __fastcall 				funcSQLCreateTbCopyDnld();
	int __fastcall 					funcSQLWriteTbCopyDnld(int _nType);

	void __fastcall 				funcSQLCreateTbCopyDoc08();
	int __fastcall 					funcSQLWriteTbCopyDoc08(int _nType, int _nActionType);//return value : current seqno

	//231030//Param 추가//210303//#503//DATA INSERT//
	void __fastcall 				funcInsertDBDataCdKind(int _nType);//funcInsertDBDataCdKind503();

	void __fastcall 				funcInsertDBDataTbSpatialFontsize(int _nType);//231030//GAGAMLAYER in LandArchive//

	//===========================================================================
	//221020//Get INI Data -> DB Data//지적단위, 과세단위 등 DB에 설정된 값으로 읽어오는 함수//
	void __fastcall 				funcSQLReadOldLandDocUserFavoritesAll();// READ TB_OLDLANDDOC_USERFAVORTIES
	//===========================================================================


	//==========================================================================
	// 가감대장 TB_DOCUMENT20_LANDLIST.GAGAM_NO
	//==========================================================================
	bool __fastcall 			funcSQLGetGagamNoFromLandCd(AnsiString _asLandCd);

	//=============================================================================
	//231030//GAGAMLAYER in LandArchive//가감대장 기준점 좌표 자료 가져오기//
	//=============================================================================
	void __fastcall 			funcReadGagamBasePoint();
	//=============================================================================
	//241211//가감대장 심볼 표시//
	//=============================================================================
	void __fastcall 			funcReadGagamList();
	//=============================================================================
	//241217//가감대 필지목록(전체)-중복제거//
	//=============================================================================
	void __fastcall 			funcReadGagamLandListAll();
	//=============================================================================
	//241220//공간 > 심볼 > 현재 선택한 필지를 기준으로 모든 가감대장 지번목록 자료 가져오기//
	//=============================================================================
	void __fastcall 			funcReadGagamLandList2(AnsiString _asLandCd);
	//=============================================================================
	//231031//GAGAMLAYER in LandArchive//가감대장 지번목록 자료 가져오기//
	//=============================================================================
	void __fastcall 			funcReadGagamLandList(AnsiString _asKwonNo, AnsiString _asGagamNo);
	//=============================================================================
	//231031//GAGAMLAYER in LandArchive//가감대장 기준점목록 자료 가져오기//
	//=============================================================================
	void __fastcall 			funcReadGagamBaseList(AnsiString _asKwonNo, AnsiString _asGagamNo);


	//=================================================================
	//240321//INItoDB
	//=================================================================
	void __fastcall 			func_readConfigIni();


	//=============================================================================
	//240322//[Add]카드대장.개인정보.MASKING.최소사용자 권한//
	//특정조건에 만족하는 특정컬럼 값만 임시적으로 가져오기 위한 함수//
	//=============================================================================
	AnsiString __fastcall 		funcSQLColumnData(AnsiString _asSqlQry);


	//=========================================================================
	//241030//#구대장한글편집#DirectTable//
	//=========================================================================
	void __fastcall 			funcSQLCreate_TB_DOCUMENT08_DIRECT();
	//===========================================================================
	// 한글화 DB/AIOCR 데이터 변경 로그기록 - 테이블 생성
	//_bAIOCR			=> true:AIOCR데이터정정, false:DB데이터정정//
	//===========================================================================
	void __fastcall 			funcSQLCreateTableDoc08History();

	//==========================================================================
	//241107//#한글화편집#DirectTable//내역저장하기//
	//==========================================================================
	//===========================================================================
	// WRITE TB_DOCUMENT08 Direct History//
	// _nCopyDoc08Seq 	=> TB_COPY_DOC08.SEQ
	// _nKindType		=> 1.부책,2:공유지연명부
	//_bAIOCR			=> true:AIOCR데이터정정, false:DB데이터정정//
	//===========================================================================
	void __fastcall funcWriteDoc08_History(int _nCopyDoc08Seq, int _nKindType, bool _bAIOCR);
	//==========================================================================
	//241107//#한글화편집#DirectTable//내역가져오기//
	//_bAIOCR			=> true:AIOCR데이터정정, false:DB데이터정정//
	//==========================================================================
	void __fastcall funcReadDocument08_History(bool _bAIOCR);//int _nCopyDoc08Seq);

	//===========================================================================
	// WRITE TB_DOCUMENT08_HIS_DEL//연혁 삭제선 정보 저장//
	// _nType : INSERT, DELETE_ALL
	//===========================================================================
	bool __fastcall funcWriteHistoryDel(int _nType, int _nCol);


	//===========================================================================
	// DELETE FROM AIOCR TEST DB DATA
	//===========================================================================
	void __fastcall funcInitAIOCRData();

	//===========================================================================
	// Get LMFS DB Data
	//===========================================================================
	AnsiString __fastcall funcSQLReadLandMoveInfo(AnsiString _asPnu);


	__fastcall TfrmSql(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSql *frmSql;
//---------------------------------------------------------------------------
#endif
