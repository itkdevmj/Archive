//---------------------------------------------------------------------------

#ifndef untFuncH
#define untFuncH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class cFunc
{
private:
public:
	cFunc();
	~cFunc();

	//210107//다른 파일에서 해당 변수를 호출하면 문제발생//bool 		cFunc::m_bAlreadyShowMsg;

	AnsiString 	cFunc::funcGetPageNo(AnsiString _asPage);
	int 		cFunc::funcGetDocThumbPathListIndex(AnsiString _asPathName);
	int 		cFunc::funcGetDocFTPPathListIndex(AnsiString _asPathName);
	bool 		cFunc::funcCheckQueryCondition(int _nDocNo);
	bool 		cFunc::funcCheckQueryCondition36110(int _nDocNo);
	void 		cFunc::funcCheckDateCondition(int _nDocNo);

	int 		cFunc::funcGetKindCodeToKindIndex(int _nType, char *_cKindCode);
	AnsiString  cFunc::funcGetKindCodeToKindName(int _nType, char *_cKindCode);
	AnsiString  cFunc::funcGetKindNameToKindCode(int _nType, char *_cKindName);
	int  		cFunc::funcGetKindNameToKindIndex(int _nType, char *_cKindName);
	AnsiString  cFunc::funcGetPageNoName(int nDocNo, char *_cPageNo);
	AnsiString  cFunc::funcGetKindCode(AnsiString _asTaskCode, AnsiString _asKindName);

	void 		cFunc::funcDeleteDir(bool _bDelDir, AnsiString _asDir);
	void 		cFunc::DeleteFileinDir(AnsiString Dir);
	void 		cFunc::GetDirView(AnsiString Dir);//201203//
	bool 		cFunc::IsNumberString(AnsiString str);//숫자만 있는지 체크//
	bool 		cFunc::IsAreaString(AnsiString str);//소수점 하나만 포함하는지 체크//
	bool 		cFunc::funcCheckDate(String _sDate);
	bool 		cFunc::funcCheckDate2(int nType, String _sDate);
	bool 		cFunc::funcCheckMonth(String _sDate);


	AnsiString 	cFunc::funcPnuToBonbuName(AnsiString _asPnu, int _nType);
	AnsiString 	cFunc::funcPnuToUMDRIName(char* _cPnu, bool _bSggName);//읍면동+리 명 얻기
	AnsiString 	cFunc::funcPnuToRIName(char* _cPnu);//리 명 + 지번정보 얻기
	AnsiString  cFunc::funcPnuToSGGName(char* _cPnu);
	AnsiString  cFunc::funcPnuToBonbuName2(AnsiString _asPnu, int _nType);

	bool 		cFunc::funcPnuToSejongPnu(int _nDocNo);
	//검색어 입력 시마다 해당하는 읍면동, 리 찾기//
	void 		cFunc::funcUMDRINameToPnu(AnsiString _asUMDRINm);

	AnsiString 	cFunc::funcUMDRICdToNm(AnsiString _asCode);//200910
	AnsiString  cFunc::funcUMDCdToNm(AnsiString _asCode);

	AnsiString  cFunc::funcUMDNameToPnu(AnsiString _asUMDNm);
	AnsiString  cFunc::funcUMDNameToPnu2(AnsiString _asUMDNm);

	AnsiString  cFunc::funcRICdToNm(AnsiString _asCode);
	AnsiString  cFunc::funcRINameToPnu(AnsiString _asUMDCd, AnsiString _asUMDNm, AnsiString _asRINm);
	AnsiString  cFunc::funcRINameToPnu2(AnsiString _asUMDCd, AnsiString _asUMDNm, AnsiString _asRINm);
	//200331//리 없이 읍면동명만 입력했을 때 첫번째 리를 반환해준다//'은산1' -> '은산면 1'
	AnsiString  cFunc::funcRINameToPnu3(AnsiString _asUMDCd, AnsiString _asUMDNm);
	AnsiString  cFunc::funcRINameToPnu4(AnsiString _asRINm);

	int 		cFunc::funcDocToScale(TTreeNode* t_ClickNode);
	int 		cFunc::funcCheckImageScale();


	TPoint      cFunc::funcSurveyMapToDevice(const GPoint _scrPoint);
	GPoint  	cFunc::funcDeviceToSurveyMap(const TPoint _scrPoint);	//
	GPoint 		cFunc::funcBitMapImageToCm(const TPoint _tpImageLength, mBitmapHeader *mBitMapHeader, int _nType);
	TPoint 		cFunc::funcCmToBitMapImage(const GPoint _gpLength, mBitmapHeader *mBitMapHeader, int _nScale);//190417//dogwak_pos -> image_pos
	GPoint 		cFunc::funcMapPointToMeter(const GPoint _gpMapPoint);
	int 		cFunc::funcGetPixelFormat(int _nBitCount);


	//========================================================================
	//1. YYYY-MM-DD
	//2. YYYY-MM-DD HH:NN:SS
	//3. YYYY년 MM월 DD일//
	AnsiString 	cFunc::funcChangeDateFormatString(int _nType, char* _cDateStr);
	AnsiString  cFunc::funcChangeDateNumberFormatDate(AnsiString _asDate);//#OWNINFO#
    //YYYY년 MM월 DD일 -> YYYYMMDD//
	AnsiString cFunc::funcChangeDateStrFormatDate(AnsiString _asDate);
	//_nType : 1 (㎡), 2 (평), 3(정단무보)
	AnsiString  cFunc::funcChangeAreaFormatStr(int _nType, AnsiString _asArea);//#OWNINFO#
	//구대장 연대환산용//
	bool 		cFunc::funcCheckDate(AnsiString _asEraCode, AnsiString _asDate);


	//========================================================================
    void 		cFunc::funcCreateDir(String _sDirName);


	int 		cFunc::func_GetLength(AnsiString path);

	//========================================================================
	AnsiString 	cFunc::funcFindUMDRINmToCd(AnsiString _asUMDRINm);//200910//


	//========================================================================
	//음력변환
	TDateTime cFunc::funcChangeSolarToLunar(TDateTime _solarDt);
	//양력변환
	TDateTime cFunc::funcChangeLunarToSolar(TDateTime _lunarDt);


	//========================================================================
	//구대장한글화 DB 원본 후처리 중 반복적인 StringReplace 함수 처리//
	AnsiString cFunc::funcStringReplaceDoc08(AnsiString _asStr);
	//========================================================================

	//===========================================================================
	// 중복코드 함수처리 : PATH_NAME (DB Path -> Local Path)
	//===========================================================================
	AnsiString cFunc::funcGetDBtoLocalPath(AnsiString _asPathName);

	//===========================================================================
	//[REQ_260715_#2.DB내 권번호 변경]
	// 권번호(KWON_NO) 처리
	// (과거) 숫자 4자리//
	// (현재) 영문 + 숫자4자리(울산 울주군)//
	//===========================================================================
	AnsiString cFunc::funcGetKwonNo(AnsiString _asKwonNo);


//---------------------------------------------------------------------------

};

//---------------------------------------------------------------------------
extern cFunc *eFunc;
//---------------------------------------------------------------------------
#endif