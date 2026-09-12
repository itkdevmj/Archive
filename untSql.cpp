//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004

TfrmSql *frmSql;
//---------------------------------------------------------------------------
__fastcall TfrmSql::TfrmSql(TComponent* Owner)
	: TForm(Owner)
{
	m_hStmt = NULL;
	m_hDbc  = NULL;
	m_hEnv  = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

bool __fastcall TfrmSql::func_QryProcess(AnsiString qry)
{
	bool result = true;
	SQLRETURN ret = SQLExecDirect(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		result = false;
	}
	return result;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmSql::func_QryProcessC(AnsiString qry)
{
	bool result = true;
	SQLRETURN ret = SQLExecDirect(m_hStmtC,(SQLCHAR *)qry.c_str(),SQL_NTS);
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		result = false;
	}
	return result;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmSql::func_SetSeqNoQryProcess(AnsiString qry)
{
	bool result = true;
	SQLRETURN ret = SQLExecDirect(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		result = false;
	}
	else
	{
		ret = SQLPrepare(m_hStmt, (SQLCHAR *)"commit;", SQL_NTS);
		ret = SQLExecute(m_hStmt);
	}

	return result;
}
//---------------------------------------------------------------------------


void __fastcall TfrmSql::func_readConfigData()
{
	/*2018.02.22*/if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[15][50];
	SQLINTEGER m_nVal[15];

	for(int i=0; i<15; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;

//231018//GAGAMLAYER in LandArchive//	mSqlQry = "SELECT * FROM TB_SPATIALCONFIG WHERE LAYERGBN = 'LP' ORDER BY LAYERPARENT,LAYERNAME ASC";
	mSqlQry = "SELECT * FROM TB_SPATIALCONFIG ORDER BY LAYERPARENT,LAYERNAME ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString result[15];
	char temp[50];
	frmMain->m_vCONFIGLP.clear();
	CONFIGLAYER _configList;
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<15; i++){
			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
			result[i] = "";
		}
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<15; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				result[i] = temp;
			}

			_configList.layerparent = result[1];
			_configList.layername   = result[2];
			_configList.showuse     = result[3].ToInt() ;
			_configList.showlevel   = result[4].ToInt() ;
			_configList.labeluse    = result[5].ToInt() ;
			_configList.labelscale  = result[6].ToInt() ;
			_configList.labelcolor  = result[7].ToInt() ;
			_configList.labelfont   = result[8];
			_configList.brushuse    = result[9].ToInt() ;
			_configList.brushcolor  = result[10].ToInt() ;
			_configList.lineuse     = result[11].ToInt() ;
			_configList.linecolor   = result[12].ToInt() ;
			_configList.linewidth   = result[13].ToInt() ;
			_configList.hatchstyle  = result[14].UpperCase() ;
			_configList.fontsize.clear();
			if(_configList.layername == "기준점")
			{
				_configList.showuse 	= frmMain->INIINFO.B_QRYCHECK[18];
				_configList.showlevel 	= frmMain->INIINFO.DOGN_LEVEL;
				_configList.labelscale 	= _configList.showlevel;
			}
			//리경계, 읍면동경계, 인덱스500, 600, 1000, 1200, 3000, 6000, 지적도, 추가 순임을 기억하자//
			frmMain->m_vCONFIGLP.push_back(_configList);

			for(int i=0; i<15; i++){
				memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
				result[i] = "";
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}


	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//지적도 폰트
	int size = frmMain->m_vCONFIGLP.size();
	AnsiString layername;
	for(int i=0; i<size; i++){
		layername = frmMain->m_vCONFIGLP[i].layername;
		SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, m_cVal[0]  , sizeof(m_cVal[0]) , &m_nVal[0]);

		mSqlQry = "SELECT SIZE FROM TB_SPATIALFONTSIZE WHERE LAYERNAME='" + layername.Trim() + "' ORDER BY SCALE ASC";

		ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
		ret = SQLExecute(m_hStmt);

		if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
			// 뒷정리
			SQLCloseCursor(m_hStmt);
		}
		else{
			memset(m_cVal[0],0x00,sizeof(m_cVal[0]));
			result[0] = "";
			while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[0], sizeof( temp ));
				result[0] = temp;

				frmMain->m_vCONFIGLP[i].fontsize.push_back(result[0].ToInt());

				memset(m_cVal[0],0x00,sizeof(m_cVal[0]));
				result[0] = "";
			};
			if(m_hStmt) SQLCloseCursor(m_hStmt);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readMainIni()
{
	/*2018.02.22*/if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[3][50];
	SQLINTEGER m_nVal[3];

	for(int i=0; i<3; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;

	mSqlQry = "SELECT * FROM TB_SPATIALMAIN";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString result[3];
	char temp[50];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<3; i++){
			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
			result[i] = "";
		}
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			memset(&tempCodeConvert, 0x00, sizeof(STRUCTCODECONVERT));
			for(int i=0; i<3; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				result[i] = temp;
			}

			if(result[2] == "") result[2] = "0";

			//OK KAKAOMAP OpenAPI Key
			else if(result[0] == "KAKAOMAP_OPENAPI_KEY" && result[1] == "KEY")                  frmMain->m_MAININI.KAKAOMAP_OPENAPI_KEY         = result[2];

			//로컬 영상 사용시 최소 출력 스케일
			else if(result[0] == "ETC_OPTION" && result[1] == "LOCAL_IMGAE_VIEW_SCALE")         frmMain->m_MAININI.LOCAL_IMGAE_VIEW_SCALE       = result[2].ToInt();
			//편입면적 사용여부
			else if(result[0] == "ETC_OPTION" && result[1] == "INCLUDE_AREA_USE")               frmMain->m_MAININI.INCLUDE_AREA_USE             = result[2].ToInt();

			//OK 출력시 알파값
			else if(result[0] == "IMAGEOVERLAP" && result[1] == "IMAGE_PLUS_ALPHABLEND_VALUE")  frmMain->m_MAININI.IMAGE_PLUS_ALPHABLEND_VALUE  = result[2].ToInt();
			else if(result[0] == "IMAGEOVERLAP" && result[1] == "IMAGE_MINUS_ALPHABLEND_VALUE") frmMain->m_MAININI.IMAGE_MINUS_ALPHABLEND_VALUE = result[2].ToInt();

			//영상출력시와 미출력시의 지번 출력 옵션
			else if(result[0] == "JIBUN_OPTION" && result[1] == "USE_IMAGE_JIJUKLINECOLOR")     frmMain->m_MAININI.USE_IMAGE_JIJUKLINECOLOR     = result[2].ToInt();
			else if(result[0] == "JIBUN_OPTION" && result[1] == "USE_IMAGE_JIBUNCOLOR")  	    frmMain->m_MAININI.USE_IMAGE_JIBUNCOLOR         = result[2].ToInt();
			else if(result[0] == "JIBUN_OPTION" && result[1] == "UN_USE_IMAGE_JIJUKLINECOLOR")  frmMain->m_MAININI.UN_USE_IMAGE_JIJUKLINECOLOR  = result[2].ToInt();
			else if(result[0] == "JIBUN_OPTION" && result[1] == "UN_USE_IMAGE_JIBUNCOLOR")      frmMain->m_MAININI.UN_USE_IMAGE_JIBUNCOLOR      = result[2].ToInt();

			//영상 출력시 이동 좌표
			else if(result[0] == "PICTURE MOVE" && result[1] == "X")                            frmMain->m_MAININI.PICTURE_XMOVE                = result[2].ToInt();
			else if(result[0] == "PICTURE MOVE" && result[1] == "Y")                            frmMain->m_MAININI.PICTURE_YMOVE                = result[2].ToInt();

			//OK 로드뷰 출력관련
			else if(result[0] == "ROADVIEW" && result[1] == "NAVER")                            frmMain->m_MAININI.NAVER                        = result[2];
			else if(result[0] == "ROADVIEW" && result[1] == "DAUM")                             frmMain->m_MAININI.DAUM                         = result[2];


			//선택된 개별주택 색상
			else if(result[0] == "SELECT_OPTION" && result[1] == "GENERAL_COLOR")               frmMain->m_MAININI.SELECT_GENERAL_COLOR         = result[2].ToInt();

			//지번선택시 사용되는 값
			else if(result[0] == "SELECT_OPTION" && result[1] == "REMARK_COLOR")                frmMain->m_MAININI.SELECT_REMARK_COLOR          = result[2].ToInt();
			else if(result[0] == "SELECT_OPTION" && result[1] == "REMARK_ALPHA")                frmMain->m_MAININI.SELECT_REMARK_ALPHA          = result[2].ToInt();
			else if(result[0] == "SELECT_OPTION" && result[1] == "REMARK_WIDTH")                frmMain->m_MAININI.SELECT_REMARK_WIDTH          = result[2].ToInt();
			else if(result[0] == "SELECT_OPTION" && result[1] == "LINE_COLOR")                  frmMain->m_MAININI.SELECT_LINE_COLOR            = result[2].ToInt();
			else if(result[0] == "SELECT_OPTION" && result[1] == "LINE_WIDTH")                  frmMain->m_MAININI.SELECT_LINE_WIDTH            = result[2].ToInt();

			else if(result[0] == "SELECT_OPTION" && result[1] == "USEJIBUN_COLOR")              frmMain->m_MAININI.SELECT_USEJIBUN_COLOR        = result[2].ToInt();
			else if(result[0] == "SELECT_OPTION" && result[1] == "UNUSEJIBUN_COLOR")            frmMain->m_MAININI.SELECT_UNUSEJIBUN_COLOR      = result[2].ToInt();

			//기본 출력 옵션
			else if(result[0] == "SHOW_FACTOR_OPTION" && result[1] == "LIMITAREA")              frmMain->m_MAININI.SHOW_FACTOR_LIMITAREA        = result[2].ToInt();
			else if(result[0] == "SHOW_FACTOR_OPTION" && result[1] == "SCALE")                  frmMain->m_MAININI.SHOW_FACTOR_SCALE            = result[2].ToInt();

			//좌표변환용
			else if(result[0] == "SYSTEM CONVERT" && result[1] == "ELLIPS_0")                   frmMain->m_MAININI.SYSTEM_CONVERT_ELLIPS_0      = result[2].ToInt();
			else if(result[0] == "SYSTEM CONVERT" && result[1] == "ELLIPS_1")                   frmMain->m_MAININI.SYSTEM_CONVERT_ELLIPS_1      = result[2].ToInt();
			else if(result[0] == "SYSTEM CONVERT" && result[1] == "SYSTEM_0")                   frmMain->m_MAININI.SYSTEM_CONVERT_SYSTEM_0      = result[2].ToInt();
			else if(result[0] == "SYSTEM CONVERT" && result[1] == "SYSTEM_1")                   frmMain->m_MAININI.SYSTEM_CONVERT_SYSTEM_1      = result[2].ToInt();

			//기본출력 옵션
			else if(result[0] == "ZOOM_SCALE_INFORMATION" && result[1] == "FIRST_ZOOM_FACTOR")  frmMain->m_MAININI.FIRST_ZOOM_FACTOR            = result[2].ToInt();

			//가격표시 옵션
			else if(result[0] == "PRICE_MARK_OPTION" && result[1] == "MARK_HOWTO"){
				frmMain->m_MAININI.PRICE_MARK_HOWTO             = result[2].ToInt();
				/*
				if(frmMain->m_MAININI.PRICE_MARK_HOWTO == 0)      palViewInfo->Width = 150;
				else if(frmMain->m_MAININI.PRICE_MARK_HOWTO == 1) palViewInfo->Width = 350;
				else if(frmMain->m_MAININI.PRICE_MARK_HOWTO == 2) palViewInfo->Width = 250;
				*/
			}
			//장평
			else if(result[0] == "FONTVIEW_OPTION" && result[1] == "WIDTH_RATE")                frmMain->m_MAININI.WIDTHRATE                    = result[2].ToDouble();

			//라벨출력 옵션
			else if(result[0] == "ETC_OPTION" && result[1] == "LABEL_ALIGNMENT")                frmMain->m_MAININI.LABEL_ALIGNMENT              = result[2].ToDouble();

			//항공사진 출력시 접도구역 색상
			else if(result[0] == "FRONTAGEAREA" && result[1] == "USE_IMAGE_COLOR")              frmMain->m_MAININI.FRONTAGEAREA_USEIMAGECOLOR   = result[2].ToInt();
			//항공사진 미 출력시 접도구역 색상
			else if(result[0] == "FRONTAGEAREA" && result[1] == "UN_USE_IMAGE_COLOR")           frmMain->m_MAININI.FRONTAGEAREA_UNUSEIMAGECOLOR = result[2].ToInt();

			//=============================================================================
			//240321//INItoDB//
			else if(result[0] == "KRAS_CONNECT" && result[1] == "KEY")
			{
				if( result[2].IsEmpty() )
					frmMain->INI_B_KRAS = false;
				else
					frmMain->m_MAININI.KRAS_KEY	= result[2];//241217//frmMain->func_Decoder(result[2]);
			}
			else if(result[0] == "KRAS_CONNECT" && result[1] == "IP")
			{
				if( result[2].IsEmpty() )
					frmMain->INI_B_KRAS = false;
				else
					frmMain->m_MAININI.KRAS_IP	= result[2];//241217//frmMain->func_Decoder(result[2]);
			}
			else if(result[0] == "ETC_OPTION" && result[1] == "READ_INTERVAL")
			{
				frmMain->readinterval 	= result[2].ToInt();
				frmMain->readinterval	= frmMain->readinterval + 20;
			}
			else if(result[0] == "JIBUN_OPTION" && result[1] == "JIBUN_DOUBLE_LINE")	frmMain->m_bJibunDblLine 	= (result[2] == "1" ? true:false);
			//=============================================================================

			for(int i=0; i<3; i++){
				memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
				result[i] = "";
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readCodeConvert()
{
	/*2018.02.22*/if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[4][50];
	SQLINTEGER m_nVal[4];

	for(int i=0; i<4; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;

//231018//GAGAMLAYER in LandArchive//	mSqlQry = "SELECT * FROM TB_SPATIALCODECONVERT WHERE LAYERGBN='LP'";
	mSqlQry = "SELECT * FROM TB_SPATIALCODECONVERT";//231018//GAGAMLAYER in LandArchive//

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString result[4];
	char temp[50];

	m_v_STRUCTCODECONVERTLP.clear();

	AnsiString mapRoot = frmMain->ROOTPATH + "MAP\\" + frmMain->_SIDOCODE + "\\";
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<4; i++){
			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
			result[i] = "";
		}
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			memset(&tempCodeConvert, 0x00, sizeof(STRUCTCODECONVERT));
			for(int i=0; i<4; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				result[i] = temp;
			}
			tempCodeConvert.thema    = result[0];
			tempCodeConvert.korname  = result[1];
			tempCodeConvert.engname1 = result[2];
			tempCodeConvert.engname2 = result[3];

			AnsiString fname = mapRoot + tempCodeConvert.korname + ".HMF";
			if(FileExists(fname)){
				m_v_STRUCTCODECONVERTLP.push_back(tempCodeConvert);
			}
			memset(&tempCodeConvert, 0x00, sizeof(STRUCTCODECONVERT));

			for(int i=0; i<4; i++){
				memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
				result[i] = "";
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSQLReadCount(AnsiString _qry)
{
	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	SQLRETURN 	ret;
	SQLINTEGER 	m_nVal[1];
	int			nVal;
	AnsiString  asSqlQry		= _qry;
	int 		nReturnValue 	= 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	SQLBindCol(m_hStmt, 1,  SQL_C_LONG, &nVal, sizeof(nVal) , &m_nVal[0]);
	//
	ret    	= SQLPrepare(m_hStmt, (SQLCHAR*)asSqlQry.c_str(), SQL_NTS);
	ret		= SQLExecute(m_hStmt);

	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return false;
	}

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		nReturnValue = nVal;
		break;
	};

	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	return nReturnValue;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmSql::func_readLandcd(AnsiString _qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString result = "";

	SQLCHAR m_cVal[5];
	SQLINTEGER m_nVal;

	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, m_cVal, sizeof(m_cVal), &m_nVal);

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)_qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	char tempCValue[5];
	int size;
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		memset(m_cVal,0x00,sizeof(m_cVal));
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			memset(tempCValue, 0x00, sizeof(tempCValue) );
			memcpy(tempCValue, m_cVal, sizeof(tempCValue));
			result = tempCValue;
			memset(m_cVal,0x00,sizeof(m_cVal));
			break;
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	return result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TfrmSql::func_ConvertSidoCDtoNM(AnsiString _sidosggcd)
{
	/*2018.02.22*/if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[2][30];
	SQLINTEGER m_nVal[2];

	for(int i=0; i<2; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;
	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT DISTINCT SIDO_NM, SGG_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + _sidosggcd.Trim() + "'";
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT DISTINCT SIDO_NM, SGG_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + _sidosggcd.Trim() + "'";
//=============================================================================
	else
		mSqlQry = "SELECT DISTINCT SIDO_NM, SGG_NM FROM SIDO_CODE WHERE SIDOSGG_CD ='" + _sidosggcd.Trim() + "'";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString readData[2];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<2; i++) readData[i] = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<2; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				readData[i] = (char*)temp;
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString result = "";
	result = readData[0] +  " " + readData[1];

	return result;
}
//---------------------------------------------------------------------------

//210204//#LOADING_TEST//
AnsiString __fastcall TfrmSql::func_ConvertUmdCDtoNM(AnsiString _umdcd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[1][30];
	SQLINTEGER m_nVal[1];
	AnsiString  asSqlWhere	= "";

	for(int i=0; i<1; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	asSqlWhere	= "SIDOSGG_CD ='" + _umdcd.SubString(1, 5).Trim() + "'";
	asSqlWhere	= asSqlWhere + " AND UMD_CD ='" + _umdcd.SubString(6, 3).Trim() + "'";

	AnsiString mSqlQry;
	SQLRETURN ret;
	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT UMD_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE " + asSqlWhere;
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT UMD_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE " + asSqlWhere;
//=============================================================================
	else
		mSqlQry = "SELECT UMD_NM FROM SIDO_CODE WHERE " + asSqlWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString readData[1];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<1; i++) readData[i] = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<1; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				readData[i] = (char*)temp;
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString result = "";
	result = readData[0];

	return result;
}
//---------------------------------------------------------------------------

//210204//#LOADING_TEST//
AnsiString __fastcall TfrmSql::func_ConvertRiCDtoNM(AnsiString _ricd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[1][30];
	SQLINTEGER m_nVal[1];
	AnsiString  asSqlWhere	= "";

	for(int i=0; i<1; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	asSqlWhere	= "SIDOSGG_CD ='" + _ricd.SubString(1, 5).Trim() + "'";
	asSqlWhere	= asSqlWhere + " AND UMD_CD ='" + _ricd.SubString(6, 3).Trim() + "'";
	asSqlWhere	= asSqlWhere + " AND RI_CD ='" + _ricd.SubString(9, 2).Trim() + "'";

	AnsiString mSqlQry;
	SQLRETURN ret;
	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT RI_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE " + asSqlWhere;
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT RI_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE " + asSqlWhere;
//=============================================================================
	else
		mSqlQry = "SELECT RI_NM FROM SIDO_CODE WHERE " + asSqlWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString readData[1];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<1; i++) readData[i] = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<1; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				readData[i] = (char*)temp;
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString result = "";
	result = readData[0];

	return result;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmSql::func_ConvertAddressToEmdRicd(AnsiString _nm)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[7][30];
	SQLINTEGER m_nVal[7];

	for(int i=0; i<7; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;
	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT * FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (SGG_NM = '" + _nm + "' OR UMD_NM = '" + _nm + "' OR RI_NM = '" + _nm + "')";
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT * FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (SGG_NM = '" + _nm + "' OR UMD_NM = '" + _nm + "' OR RI_NM = '" + _nm + "')";
//=============================================================================
	else
		mSqlQry = "SELECT * FROM SIDO_CODE WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (SGG_NM = '" + _nm + "' OR UMD_NM = '" + _nm + "' OR RI_NM = '" + _nm + "')";
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString readData[7];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<7; i++) readData[i] = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<7; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				readData[i] = (char*)temp;
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString result = "";
	result = readData[0] + readData[1] + readData[2];
	return result;
}
//---------------------------------------------------------------------------
//M
AnsiString __fastcall TfrmSql::func_ConvertAddressToEmdcd(AnsiString _nm)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[7][30];
	SQLINTEGER m_nVal[7];
	SIDONAME_STRUCT tempUMDNAME;
	AnsiString		asLandKey	= "";//200228

	for(int i=0; i<7; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;
	//mSqlQry = "SELECT * FROM SIDO_CODE WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (SGG_NM = '" + _nm + "' OR UMD_NM = '" + _nm + "' OR RI_NM = '" + _nm + "')";
	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT * FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (UMD_NM LIKE '" + _nm + "%' OR RI_NM LIKE '" + _nm + "%')";
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT * FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (SGG_NM = '" + _nm + "' OR UMD_NM = '" + _nm + "' OR RI_NM = '" + _nm + "')";
//=============================================================================
	else
		mSqlQry = "SELECT * FROM SIDO_CODE WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' AND (UMD_NM LIKE '" + _nm + "%' OR RI_NM LIKE '" + _nm + "%')";
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	frmMain->m_vSIDOCODE_PNULIST.clear();
//	frmMain->m_vSearchPnuList.clear();

	AnsiString readData[7];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<7; i++) readData[i] = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<7; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				readData[i] = (char*)temp;
			}

			//200227
			memset(&tempUMDNAME, 0, sizeof(tempUMDNAME));
			wsprintf(tempUMDNAME.cSggCd, readData[0].c_str(), readData[0].Length());
			wsprintf(tempUMDNAME.cUmdCd, readData[1].c_str(), readData[1].Length());
			wsprintf(tempUMDNAME.cRiCd,  readData[2].c_str(), readData[2].Length());
			wsprintf(tempUMDNAME.cSggNm, "%s", readData[4]);
			wsprintf(tempUMDNAME.cUmdNm, "%s", readData[5]);
			wsprintf(tempUMDNAME.cRiNm,  "%s", readData[6]);
			frmMain->m_vSIDOCODE_PNULIST.push_back(tempUMDNAME);

//			asLandKey = readData[0] + readData[1] + readData[2]
//			frmMain->m_vSearchPnuList
			//200227//[TODO]해당하는 목록 구성하기//
			//지금은 1개 찾으면 빠져나간다//
			break;//1개 찾으면 일단 나간다//[TODO]
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString result = "";

	if(frmMain->m_vSIDOCODE_PNULIST.size() > 0)
	{
		if( readData[6].Pos(_nm) > 0 )//200227//검색어가 본함수(emd 찾기)에서 찾았지만, 리명칭과 같을 때//
			result = readData[0] + readData[1] + readData[2];
		else
			result = readData[0] + readData[1];
	}

	return result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TfrmSql::func_ConvertAddressToRicd(AnsiString _sggumdcd, AnsiString _nm)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[7][30];
	SQLINTEGER m_nVal[7];

	for(int i=0; i<7; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;
	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT * FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + _sggumdcd.SubString(1, 5).Trim() + "' AND UMD_CD = '" + _sggumdcd.SubString(6, 3).Trim() + "' AND RI_NM = '" + _nm + "'";
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT * FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " WHERE SIDOSGG_CD ='" + _sggumdcd.SubString(1, 5).Trim() + "' AND UMD_CD = '" + _sggumdcd.SubString(6, 3).Trim() + "' AND RI_NM = '" + _nm + "'";
//=============================================================================
	else
		mSqlQry = "SELECT * FROM SIDO_CODE WHERE SIDOSGG_CD ='" + _sggumdcd.SubString(1, 5).Trim() + "' AND UMD_CD = '" + _sggumdcd.SubString(6, 3).Trim() + "' AND RI_NM = '" + _nm + "'";
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString readData[7];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<7; i++) readData[i] = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<7; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				readData[i] = (char*)temp;
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString result = "";
	result = readData[2];//readData[0] + readData[1] + readData[2];
	return result;
}
//---------------------------------------------------------------------------
//200910
AnsiString __fastcall TfrmSql::func_ConvertAddressToLandcd(AnsiString _address, bool _bBubn)
{
	AnsiString  asAddress = "";
	AnsiString  asUMDRICd = "";
	AnsiString  asUMDRINm = "";
	AnsiString  asEmdNm = "";
	AnsiString  asEmdCd = "";
	AnsiString  asRiNm  = "";
	AnsiString  asRiCd  = "00";
	AnsiString  asBobn  = "0";
	AnsiString  asBubn  = "0";
	AnsiString  asStr   = "";
	AnsiString  asGbn   = "산";
	int 		nGbn 	= 1;
	int			nJibunPos 	= 0;
	int			iPos 	= 0;
	int			nLen 	= 0;

	_address = StringReplace(_address, "  ", " ", TReplaceFlags() << rfReplaceAll);
	asAddress = _address;
	//전체공백제거//
	asAddress = StringReplace(asAddress, " ", "", TReplaceFlags() << rfReplaceAll);

	//200331//리명부터 찾는다//읍면동부터 찾으니 '부여읍' 때문에 '부여두리1'을 제대로 못 찾는다.
	nJibunPos	= frmMain->funcGetJibunPos(asAddress);
	if(nJibunPos > 1)//지번존재//
	{
		if(asAddress.SubString(nJibunPos-1, 2) == "산")
		{
			nGbn = 2;
			asStr = asAddress.SubString(1, nJibunPos-2);
		}
		else
			asStr	= asAddress.SubString(1, nJibunPos);

		asUMDRICd	= eFunc->funcFindUMDRINmToCd(asStr);

		if( !asUMDRICd.IsEmpty() )
		{
			asUMDRINm	= eFunc->funcUMDRICdToNm(asUMDRICd);
			asAddress	= asAddress.Delete(1, nJibunPos);
		}
		else
		{
			//210201//
			if(frmMain->_SIDOCODE == "36110")
			{
				if(asStr.Pos("세종시") == 0)
					asStr	= "세종시" + asStr;

				asUMDRICd	= eFunc->funcFindUMDRINmToCd(asStr);
				if( !asUMDRICd.IsEmpty() )
				{
					asUMDRINm	= eFunc->funcUMDRICdToNm(asUMDRICd);
					asAddress	= asAddress.Delete(1, nJibunPos);
				}
			}

			if(nGbn == 2)
			{
				nGbn = 1;
				asStr	= asStr + asGbn;
				asUMDRICd	= eFunc->funcFindUMDRINmToCd(asStr);

				if( !asUMDRICd.IsEmpty() )
				{
					asUMDRINm	= eFunc->funcUMDRICdToNm(asUMDRICd);
					asAddress	= asAddress.Delete(1, nJibunPos);
				}
				else
					return "";
			}
			else
				return "";
		}
	}

	iPos 	= asAddress.Pos("-");

	//=========================================================================
	//240321//(부번없이)'본번-' 까지만 입력
	//=========================================================================
	if(iPos == asAddress.Length())
	{
		asAddress = StringReplace(asAddress, "-", "", TReplaceFlags() << rfReplaceAll);
	}
	//=========================================================================

	if(iPos > 0 )
	{
		asBobn = asAddress.SubString(1, iPos-1);
		if( !eFunc->IsNumberString(asBobn) )
			return "";

		asBubn = asAddress.SubString(iPos+1, asAddress.Length()-iPos);
		if(asBubn.IsEmpty())	asBubn = "0";//240321//(부번없이)'본번-' 까지만 입력
		if( !eFunc->IsNumberString(asBubn) )
			return "";
	}
	else
	{
		asBobn = asAddress;
		if( !eFunc->IsNumberString(asBobn) )
			return "";
	}

//=============================================================================
//v1.0.0.6//230731//중복된 코드라 위치이동//
	if(frmMain->_SIDOCODE == "36110")//210108//#SEJONG_PNU
		asStr.sprintf("%s%d%04d%04d", asUMDRICd, nGbn, asBobn.ToInt(), asBubn.ToInt());
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->_SIDOCODE == "11305")
		asStr.sprintf("%s%d%04d%04d", asUMDRICd, nGbn, asBobn.ToInt(), asBubn.ToInt());
//=============================================================================
	else
		asStr.sprintf("%s%s%d%04d%04d", frmMain->_SIDOCODE, asUMDRICd, nGbn, asBobn.ToInt(), asBubn.ToInt());
//=============================================================================


	if( asStr.Length() != 19 )
		asStr = "";

	return asStr;
}
//---------------------------------------------------------------------------
//AnsiString __fastcall TfrmSql::func_ConvertAddressToLandcd(AnsiString _address, bool _bBubn)
//{
//	AnsiString  asEmdNm = "";
//	AnsiString  asEmdCd = "";
//	AnsiString  asRiNm  = "";
//	AnsiString  asRiCd  = "00";
//	AnsiString  asBobn  = "0";
//	AnsiString  asBubn  = "0";
//	AnsiString  asStr   = "";
//	AnsiString  asGbn   = "산";
//	int 		nGbn 	= 1;
//	int			iPos 	= 0;
//	int			nLen 	= 0;
//
//	_address = StringReplace(_address, "  ", " ", TReplaceFlags() << rfReplaceAll);
//	asStr = _address;
//
//	//200331//리명부터 찾는다//읍면동부터 찾으니 '부여읍' 때문에 '부여두리1'을 제대로 못 찾는다.
//	iPos	= frmMain->funcGetJibunPos(_address);
//	if(iPos > 1)//지번존재//
//	{
//		int aPos = _address.Pos(" ");
////		if(aPos == 0 && _address.SubString(1, aPos-1).Pos(" ") == 0)
////		{
////			AnsiString asStr = _address.SubString(1, aPos-1);
////			aPos = asStr.Pos(" ");
////			if(aPos > 1)//읍면동+리+지번 모두 존재//저 아래에서 처리한다//
////
////		}
//
//		if(aPos == 0)//띄워쓰기 없거나, 읍면동 없이 리+지번만 있을 때////200423
//		{
//			asRiNm 	= _address.SubString(1, iPos);
//			asRiNm  = StringReplace(asRiNm, " ", "", TReplaceFlags() << rfReplaceAll);
//			asRiCd 	= eFunc->funcRINameToPnu4(asRiNm);
//			if( asRiCd.Length() == 10 )//읍면동, 리 존재//
//			{
//				asEmdCd	= asRiCd.SubString(1, 8);
//				asEmdNm = eFunc->funcUMDCdToNm(asEmdCd);
//				asRiNm  = eFunc->funcUMDCdToNm(asRiCd);
//				asRiCd  = asRiCd.SubString(9, 2);
//				asStr  	= _address.Delete(1, iPos);
//			}
//			else//혹시 '산'지번인가?//
//			{
//				int nPos = _address.Pos("산");
//				if(nPos > 0)//'산'지번인가?
//				{
//					AnsiString asTemp = _address.SubString(nPos+2, _address.Length()-(nPos+1));
//					int aPos = asTemp.Pos("산");
//					if(aPos > 0)//'산'이 또 있나?//'은산산2' -> '은산면 은산리 산 2'
//					{
//						asRiNm 	= _address.SubString(1, nPos+aPos);
//						asRiCd 	= eFunc->funcRINameToPnu4(asRiNm);
//						if( asRiCd.Length() == 10 )//읍면동, 리 존재하는 '산'지번임//
//						{
//							asEmdCd	= asRiCd.SubString(1, 8);
//							asEmdNm = eFunc->funcUMDCdToNm(asEmdCd);
//							asRiNm  = eFunc->funcUMDCdToNm(asRiCd);
//							asRiCd  = asRiCd.SubString(9, 2);
//							asStr  	= _address.Delete(1, nPos+aPos);
//							nGbn 	= 2;
//						}
//					}
//					else//'산'이 1개임?//'모산2' -> '규암면 모리 산 2'
//					{
//						asRiNm 	= _address.SubString(1, nPos-1);
//						asRiCd 	= eFunc->funcRINameToPnu4(asRiNm);
//						if( asRiCd.Length() == 10 )//읍면동, 리 존재하는 '산'지번임//
//						{
//							asEmdCd	= asRiCd.SubString(1, 8);
//							asEmdNm = eFunc->funcUMDCdToNm(asEmdCd);
//							asRiNm  = eFunc->funcUMDCdToNm(asRiCd);
//							asRiCd  = asRiCd.SubString(9, 2);
//							asStr  	= _address.Delete(1, nPos-1);
//							nGbn 	= 2;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	if(asEmdCd.IsEmpty() && asRiCd.IsEmpty())
//	{
//		iPos = _address.Pos(" ");
//		if(iPos > 1)//읍면동 존재//
//		{
//			asEmdNm 	= _address.SubString(1, iPos-1);
//			asEmdCd 	= eFunc->funcUMDNameToPnu(asEmdNm);
//			if( asEmdCd.IsEmpty() )
//				asEmdCd  = eFunc->funcUMDNameToPnu2(asEmdNm);
//
//			if( !asEmdCd.IsEmpty() )//읍면동 존재//
//				asStr  		= asStr.Delete(1, iPos);
//		}
//	}
//
//
//	if( asEmdCd.IsEmpty() )//한글자씩 찾아야 함//
//	{
//		int	nLen = asStr.Length();
//		for(int i = 2; i < nLen; i++)
//		{
//			if( (asStr.c_str()[i] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
//			{
//				i++;
//				asEmdNm		= asStr.SubString(1, i+1);
//				asEmdCd 	= eFunc->funcUMDNameToPnu(asEmdNm);
//				if( asEmdCd.IsEmpty() )
//				{
//					asEmdCd  = eFunc->funcUMDNameToPnu2(asEmdNm);
//					if( asEmdCd.IsEmpty() )
//						continue;
//				}
//				else//found
//				{
////					asStr   = StringReplace(asStr, funcUMDCdToNm(asEmdCd), "", TReplaceFlags() << rfReplaceAll);
////					asStr   = StringReplace(asStr, funcUMDCdToNm(asEmdCd), "", TReplaceFlags() << rfReplaceAll);
//					AnsiString asTmp = "";//200423
//					AnsiString asEmdNm1 = "";//200423
//					asEmdNm1	= eFunc->funcUMDCdToNm(asEmdCd);
//					asTmp 	= asStr.SubString(1, asEmdNm.Length());
//					if(asStr.Pos(asEmdNm1) == 0)//'금암'제거//
//						asStr 	= asStr.Delete(1, asEmdNm.Length());
//					else//'금암동'제거//
//						asStr 	= asStr.Delete(1, asEmdNm1.Length());
//
//					if(asEmdNm1.SubString(asEmdNm1.Length()-1, 2) == "동")//"금암3", "금암동3"
//					{
//						asRiCd = "00";
//                        //200603//금암동 산1 검색못해서 적용//
//						iPos = asStr.Pos("산");
//						if(iPos > 0)//'산'제거//
//						{
//							nGbn 	= 2;
//							asStr  	= asStr.Delete(1, iPos+1);
//						}
//
//						//
//						asStr	= asStr.Trim();
//						iPos 	= asStr.Pos("-");
//						if(iPos > 0)
//						{
//							asBobn = asStr.SubString(1, iPos- 1);
//							if( !eFunc->IsNumberString(asBobn) )
//								return "";
//
//							asBubn = asStr.SubString(iPos+1, asStr.Length()-iPos);
//							if( !eFunc->IsNumberString(asBubn) )
//								return "";
//
//							asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//						}
//						else
//						{
//							asBobn = asStr;
//							if( !eFunc->IsNumberString(asBobn) )
//								return "";
//
//							if( asBobn.IsEmpty() )//'금암동'만 검색 시//
//							{
//								asStr.sprintf("%08d%02d", asEmdCd.ToInt(), asRiCd.ToInt());
//								return asStr;
//							}
//
//							asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//						}
//
//						if( asStr.Trim().IsEmpty() )//지번정보 있는지//
//							asStr = asStr.Trim();
//
//						return asStr;
//                        //
//					}
//					else
//					{
//						int aPos = asStr.Pos(" ");
//						if(aPos == 1)
//							asStr = asStr.SubString(2, asStr.Length() - 1);
//
//						asRiNm 	= asStr;
//						nLen 	= asRiNm.Length();
//
//						iPos	= frmMain->funcGetJibunPos(asRiNm);
//						for(int j = iPos-2; j >= 0; j--)
//						{
//							if( (asRiNm.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
//							{
//								asRiNm = asRiNm.SubString(1, j+2);
//								asRiCd  = eFunc->funcRINameToPnu(asEmdCd, asEmdNm, asRiNm);
//								if( asRiCd.IsEmpty() )
//									asRiCd  = eFunc->funcRINameToPnu2(asEmdCd, asEmdNm, asRiNm);
//
//								if( asRiCd.IsEmpty() )
//									continue;
//								else
//								{
//									asStr = asStr.Delete(1, j+2);
//									break;
//								}
//							}
//						}
//
//						if(asRiCd.IsEmpty())//읍면동명을 잘못 잘랐네//
//						{
//							asStr = asStr.Delete(1, 2);
//						}
//					}
//					break;
//				}
//			}
//		}
//
//		if( asEmdCd.IsEmpty() )//읍면동 없이 '리'명만//
//		{
//			AnsiString asCode = "";
//			iPos = asStr.Pos(" ");
//			if(iPos > 4)
//			{//func_ConvertAddressToEmdcd
//				asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos-1));
//				if(asCode == "")//2글자 넣었는데 못찾음//
//				{
//					int iPos2 = asStr.Pos("산산");//"반산산1"
//					if(iPos2 > 2)//"반산산1"
//					{
//						asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos2+1));
//						if(asCode != "")//"반산"까지 자른다//
//							asStr = asStr.Delete(1, iPos2+1);
//					}
//					else//'산'확인// 지명이 1글자일 수 있음//
//					{
//						iPos2 = asStr.Pos("산");
//						if(iPos2 > 2)//'산'확인// 지명이 1글자일 수 있음//
//						{
//							asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos2-1));
//							if(asCode != "")//"반산"까지 자른다//
//								asStr = asStr.Delete(1, iPos2-1);
//						}
//                    }
//					if(asCode == "")
//						return "";
//				}
//				else
//				{
//					asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos-1));
//					asStr = asStr.Delete(1, iPos-1);
//				}
//			}
//			else
//			{
//				iPos	= frmMain->funcGetJibunPos(asStr);
//				if(iPos > 4)//func_ConvertAddressToEmdcd//2글자 이상일때//
//				{
//					asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos-1));
//					if(asCode == "")//2글자 넣었는데 못찾음//
//					{
//						int iPos2 = asStr.Pos("산");
//						if(iPos2 > 2)//'산'확인// 지명이 1글자일 수 있음//
//						{
//							asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos2-1));
//						}
//						if(asCode == "")
//							return "";
//					}
//					else
//					{
//						asCode = func_ConvertAddressToEmdcd(asStr.SubString(1, iPos-1));
//					}
//					asStr = asStr.Delete(1, iPos-1);
//				}
//			}
//
//			asEmdCd = asCode.SubString(1, 8);
//			if(asCode.Length() == 10)
//				asRiCd = asCode.SubString(9, 2);
//		}
//	}
//
//	//200331
//	if(asRiCd == "00")
//	{
//		asRiCd  = eFunc->funcRINameToPnu3(asEmdCd, asEmdNm);
//		if( asRiCd.IsEmpty() )
//        	asRiCd == "00";
//    }
//
//	if( asRiCd.IsEmpty() || asRiCd == "00")
//	{
//		iPos 		= asStr.Pos(" ");
//		if(iPos > 1)//리 존재//
//		{
//			asRiNm = asStr.SubString(1, iPos-1);
//			asRiCd  = eFunc->funcRINameToPnu(asEmdCd, asEmdNm, asRiNm);
//			if( asRiCd.IsEmpty() )
//				asRiCd  = eFunc->funcRINameToPnu2(asEmdCd, asEmdNm, asRiNm);
//
//			if( !asRiCd.IsEmpty() )
//				asStr  		= asStr.Delete(1, iPos);
//		}
//		else//한글자씩 찾기//
//		{
//			iPos	= frmMain->funcGetJibunPos(asStr);
//			if(iPos > 1)//지번데이터 존재//
//			{
//				asRiNm 	= asStr.SubString(1, iPos);
//				nLen = asRiNm.Length();
//
//				for(int j = 2; j < nLen; j++)
//				{
//					if( (asRiNm.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
//					{
//						j++;
//						asRiNm = asRiNm.SubString(1, j+1);
//						asRiCd  = eFunc->funcRINameToPnu(asEmdCd, asEmdNm, asRiNm);
//						if( asRiCd.IsEmpty() )
//							asRiCd  = eFunc->funcRINameToPnu2(asEmdCd, asEmdNm, asRiNm);
//
//						if( asRiCd.IsEmpty() )
//							continue;
//						else
//						{
//							asStr = asStr.Delete(1, j+1);
//							break;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	if( !asEmdCd.IsEmpty() && !asRiCd.IsEmpty() )
//	{
//		if(asStr.SubString(1, 2) == "리" || asStr.SubString(1, 2) == "동")
//		{
//        	asStr  = asStr.Delete(1, 2);
//		}
//	}
//
//	if( !asEmdCd.IsEmpty() && asRiCd.IsEmpty() )//"규암산1" --> "규암면 규암리 산1"//규암이 읍면동에도, 리에도 있는데 읍면동에서 찾고 리를 못 찾음//
//	{
//		asRiNm  = asEmdNm;
//		asRiCd  = eFunc->funcRINameToPnu(asEmdCd, asEmdNm, asRiNm);
//		if(asRiCd.IsEmpty())	asRiCd = "00";
//    }
//
//	iPos = asStr.Pos("산");
//	if(iPos > 0)//'산'제거//
//	{
//		nGbn 	= 2;
//		asStr  	= asStr.Delete(1, iPos+1);
//	}
//
//	iPos = asStr.Pos(" ");
//	if( iPos > 0)
//	{
//		asStr 	= asStr.Delete(1, iPos);
//	}
//
////	for(int i = 0; i < asStr.Length(); i++)
////	{
////		if(asStr[i]<'0' || asStr[i]>'9')
////		{
////			if( (asStr.c_str()[i] & 0x80) == 0x80 )
////				i++;
////			continue;
////		}
////		else
////		{
////			asStr 	= asStr.Delete(1, i);
////			break;
////		}
////	}
//
//	if(asStr.IsEmpty())
//		return "";
//
//	asStr	= asStr.Trim();
//	iPos 	= asStr.Pos("-");
//	if(iPos > 0)
//	{
//		asBobn = asStr.SubString(1, iPos- 1);
//		if( !eFunc->IsNumberString(asBobn) )
//			return "";
//
//		asBubn = asStr.SubString(iPos+1, asStr.Length()-iPos);
//		if( !eFunc->IsNumberString(asBubn) )
//			return "";
//
//		asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//	}
//	else
//	{
//		asBobn = asStr;
//		if( !eFunc->IsNumberString(asBobn) )
//			return "";
//
//		asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//	}
//
//	if( asStr.Trim().IsEmpty() )//지번정보 있는지//
//        asStr = asStr.Trim();
//
//	return asStr;
//}
////---------------------------------------------------------------------------

//AnsiString __fastcall TfrmSql::func_ConvertAddressToLandcd(AnsiString _address, bool _bBubn)
//{
//	AnsiString asEmdNm = "";
//	AnsiString asEmdCd = "";
//	AnsiString asRiNm  = "";
//	AnsiString asRiCd  = "00";
//	AnsiString asBobn  = "0";
//	AnsiString asBubn  = "0";
//	AnsiString asStr   = "";
//	AnsiString asGbn   = " 산 ";
//	int 		nGbn = 1;
//	int			iPos2;
//
//	_address = StringReplace(_address, "  ", " ", TReplaceFlags() << rfReplaceAll);
//
//	int	nLen = _address.Length();
//	iPos2 = _address.Pos(" ");
//	if(iPos2 > 0)
//	{
//		asEmdNm		= _address.SubString(1, iPos2);
//		asEmdCd  	= eFunc->funcEMDNameToPnu(asEmdNm);
//		if( !asEmdCd.IsEmpty() )
//		{
//			_address	= _address.Delete(1, iPos2+1);
//			iPos2 = _address.Pos(" ");
//			if(iPos2 > 0)
//			{
//				asRiNm		= _address.SubString(1, iPos2);
//				asRiCd  	= eFunc->funcRINameToPnu(asEmdNm, asEmdCd, asRiNm);
//				if( !asRiCd.IsEmpty() )
//				{
//				}
//				nLen = _address.Length();
//
//				for(int i = 0; i < nLen; i++)
//				{
//					if( (_address.c_str()[i] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
//					{
//						i++;
//						asRiNm 		= _address.SubString(1, i+1);
//						asRiCd  	= eFunc->funcRINameToPnu(asRiNm);
//						if( !asRiCd.IsEmpty() )
//						{
//							_address	= _address.Delete(1, i+1);
//						}
//					}
//				}
//			}
//		}
//
//	}
//
//
//
//	int iPos	= frmMain->funcGetJibunPos(_address);
//	if(iPos > 1)//지번데이터 존재//
//	{
//		//iPos2 = _address.Pos(" 산 ");
//		//iPos2 = _address.AnsiCompare(asGbn);
//		iPos2 = _address.Pos("산");
//		if(iPos2 > 1)
//		{
//			iPos2 = _address.Pos(" 산");
//			if(iPos2 > 1)
//			{
//				nGbn = 2;
//				asEmdNm = _address.SubString(1,iPos2-1);
//				iPos2 = asEmdNm.Pos(" ");
//				if(iPos2 > 1)//리 존재//
//				{
//					asStr = asEmdNm.SubString(1, iPos2-1);
//					asRiNm  = asEmdNm.Delete(1, iPos2);
//					asRiNm  = asRiNm.Trim();
//					asEmdNm = asStr;
//					asEmdCd = func_ConvertAddressToEmdcd(frmMain->INIINFO.SIDOCODE, asEmdNm);
//					if(asEmdCd.Length() != 8)
//						return "";
//
//					if( !asRiNm.IsEmpty() )
//					{
//						asRiCd  = func_ConvertAddressToRicd(asEmdCd, asRiNm);
//						if(asRiCd.Length() != 2)
//							return "";
//					}
//				}
//				else
//				{
//					asEmdCd = func_ConvertAddressToEmdcd(frmMain->INIINFO.SIDOCODE, asEmdNm);
//				}
//			}
//			else
//			{
//				iPos2 = _address.Pos(" ");
//				if(iPos2 > 1)
//				{
//					asEmdNm = _address.SubString(1,iPos2-1);
//					asEmdCd = eFunc->funcUMDNameToPnu(asEmdNm);
//					if(asEmdCd.Length() != 8)
//						return "";
//
//					asRiNm  = _address.Delete(1, iPos2);
//					asRiNm  = asRiNm.Trim();
//					AnsiString asStr = "";
//					int	nLen = asRiNm.Length();
//					for(int i = 0; i < nLen; i++)
//					{
//						if( (asRiNm.c_str()[i] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
//						{
//							i++;
//							asStr = asRiNm.SubString(1, i+1);
//							asRiCd  = eFunc->funcRINameToPnu(asEmdNm, asEmdCd, asRiNm);
//							if( !asRiCd.IsEmpty() )
//							{
////								asStr  = asRiNm.Delete(1, i+1);
////								iPos = asStr.Pos("-");
////								if(iPos > 0)
////								{
////									asBobn = asStr.SubString(1, iPos- 1);
////									if( !eFunc->IsNumberString(asBobn) )
////										return "";
////
////									asBubn = asStr.SubString(iPos+1, asStr.Length()-iPos);
////									if( !eFunc->IsNumberString(asBubn) )
////										return "";
////
////									asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
////								}
////								else
////								{
////									asBobn = asStr;
////									if( !eFunc->IsNumberString(asBobn) )
////										return "";
////
////									asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
////								}
//								break;
//                            }
//						}
//						if(asRiCd.Length() != 2)
//							return "";
//					}
//				}
//			}
//		}
//		else
//		{
//			asEmdNm = _address.SubString(1,iPos-1);
//			iPos2 = asEmdNm.Pos(" ");
//			if(iPos2 > 1)//리 존재//
//			{
//				asStr   = asEmdNm.SubString(1, iPos2-1);
//				asRiNm  = asEmdNm.Delete(1, iPos2);
//				asRiNm  = asRiNm.Trim();
//				asEmdNm = asStr;
//				asEmdCd = func_ConvertAddressToEmdcd(frmMain->INIINFO.SIDOCODE, asEmdNm);
//				if(asEmdCd.Length() < 8)
//					return "";
//
//				if( !asRiNm.IsEmpty() )
//				{
//					asRiCd  = func_ConvertAddressToRicd(asEmdCd, asRiNm);
//					if(asRiCd.Length() != 2)
//						return "";
//				}
//			}
//			else
//			{
//				asEmdCd = func_ConvertAddressToEmdcd(frmMain->INIINFO.SIDOCODE, asEmdNm);
//				if(asEmdCd.Length() < 8)
//					return "";
//				if(asEmdCd.Length() == 10)//200227
//				{
//					asRiCd  = asEmdCd.SubString(9, 2);
//					asEmdCd = asEmdCd.SubString(1, 8);
//				}
//			}
//		}
//
//		asStr   = _address.SubString(iPos+1,_address.Length()-iPos);
//		asStr   = asStr.Trim();
//		iPos = asStr.Pos("-");
//		if(iPos > 0)
//		{
//			asBobn = asStr.SubString(1, iPos- 1);
//			if( !eFunc->IsNumberString(asBobn) )
//				return "";
//
//			asBubn = asStr.SubString(iPos+1, asStr.Length()-iPos);
//			if( !eFunc->IsNumberString(asBubn) )
//				return "";
//
//			asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//		}
//		else
//		{
//			asBobn = asStr;
//			if( !eFunc->IsNumberString(asBobn) )
//				return "";
//
//			asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//			//200106//부번없으면 0으로 채워야지//
////			if(_bBubn)
////				asStr.sprintf("%03d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
////			else
////				asStr.sprintf("%03d%02d%d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt());
//		}
//	}
//	else
//	{
//		iPos2 = _address.Pos(" ");
//		if(iPos2 > 1)//리 존재//
//		{
//			asEmdNm = _address;//.SubString(1, iPos2-1);
//			asStr   = asEmdNm.SubString(1, iPos2-1);
//			asRiNm  = asEmdNm.Delete(1, iPos2);
//			asRiNm  = asRiNm.Trim();
//			asEmdNm = asStr;
//			asEmdCd = func_ConvertAddressToEmdcd(frmMain->INIINFO.SIDOCODE, asEmdNm);
//			if(asEmdCd.Length() < 8)
//				return "";
//
//			if( !asRiNm.IsEmpty() )
//			{
//				asRiCd  = func_ConvertAddressToRicd(asEmdCd, asRiNm);
//				if(asRiCd.Length() != 2)
//					return "";
//			}
//		}
//		else
//		{
//			asEmdCd = func_ConvertAddressToEmdcd(frmMain->INIINFO.SIDOCODE, asEmdNm);
//			if(asEmdCd.Length() < 8)
//				return "";
//			if(asEmdCd.Length() == 10)//200227
//			{
//				asRiCd  = asEmdCd.SubString(9, 2);
//				asEmdCd = asEmdCd.SubString(1, 8);
//			}
//		}
//
//		asStr.sprintf("%08d%02d%d%04d%04d", asEmdCd.ToInt(), asRiCd.ToInt(), nGbn, asBobn.ToInt(), asBubn.ToInt());
//	}
//
//	if( asStr.Trim().IsEmpty() )//지번정보 있는지//
//        asStr = asStr.Trim();
//
//	return asStr;
//}
////---------------------------------------------------------------------------
//M//191113//읍면동 혹은 리 정보만 입력했을 때 해당 지역의 첫 번째 지번을 검색하는 함수//
AnsiString __fastcall TfrmSql::func_FindFirstLandcd(AnsiString _landcd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[1][30];
	SQLINTEGER m_nVal[1];

	SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, m_cVal[0]  , sizeof(m_cVal[0]) , &m_nVal[0]);

	AnsiString result = "";
	AnsiString mSqlQry;
	SQLRETURN ret;
	mSqlQry = "SELECT MIN(LAND_CD) FROM LAND_INFO WHERE LAND_CD LIKE '" + _landcd.Trim() + "%'";
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString readData = "";
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			memset(temp, 0x00, sizeof(temp) );
			memcpy(temp, m_cVal[0], sizeof( temp ));
			result = (char*)temp;
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	return result;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readKindofSymbol()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER m_nVal[14];//201008//

	memset(&tempKINDOFSYMBOL, 0x00, sizeof(KINDOFDOC_STRUCT));
	int nIndex = 1;
	AnsiString sidocd, sidonm;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.LAND_KEY , sizeof(tempKINDOFSYMBOL.LAND_KEY) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC01_YN , sizeof(tempKINDOFSYMBOL.DOC01_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC02_YN , sizeof(tempKINDOFSYMBOL.DOC02_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC03_YN , sizeof(tempKINDOFSYMBOL.DOC03_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC04_YN , sizeof(tempKINDOFSYMBOL.DOC04_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC05_YN , sizeof(tempKINDOFSYMBOL.DOC05_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC06_YN , sizeof(tempKINDOFSYMBOL.DOC06_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC07_YN , sizeof(tempKINDOFSYMBOL.DOC07_YN) , &m_nVal[nIndex-1]); nIndex++;//201008//
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC08_YN , sizeof(tempKINDOFSYMBOL.DOC08_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC09_YN , sizeof(tempKINDOFSYMBOL.DOC09_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC11_YN , sizeof(tempKINDOFSYMBOL.DOC11_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC12_YN , sizeof(tempKINDOFSYMBOL.DOC12_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC14_YN , sizeof(tempKINDOFSYMBOL.DOC14_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFSYMBOL.DOC17_YN , sizeof(tempKINDOFSYMBOL.DOC17_YN) , &m_nVal[nIndex-1]); nIndex++;

	AnsiString mSqlQry;

	mSqlQry = "SELECT * FROM TB_KINDOFSYMBOL ORDER BY LAND_KEY ASC";

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	m_vKINDOFSYMBOLDATA.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		memset(&tempKINDOFSYMBOL, 0x00, sizeof(KINDOFDOC_STRUCT));
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			m_vKINDOFSYMBOLDATA.push_back(tempKINDOFSYMBOL);

			memset(&tempKINDOFSYMBOL, 0x00, sizeof(KINDOFDOC_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readKindofDocData(AnsiString _asLandCd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER m_nVal[14];//201008//

	memset(&tempKINDOFDOC, 0x00, sizeof(KINDOFDOC_STRUCT));
	int nIndex = 1;
	AnsiString sidocd, sidonm;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.LAND_KEY , sizeof(tempKINDOFDOC.LAND_KEY) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC01_YN , sizeof(tempKINDOFDOC.DOC01_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC02_YN , sizeof(tempKINDOFDOC.DOC02_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC03_YN , sizeof(tempKINDOFDOC.DOC03_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC04_YN , sizeof(tempKINDOFDOC.DOC04_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC05_YN , sizeof(tempKINDOFDOC.DOC05_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC06_YN , sizeof(tempKINDOFDOC.DOC06_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC07_YN , sizeof(tempKINDOFDOC.DOC07_YN) , &m_nVal[nIndex-1]); nIndex++;//201008//
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC08_YN , sizeof(tempKINDOFDOC.DOC08_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC09_YN , sizeof(tempKINDOFDOC.DOC09_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC11_YN , sizeof(tempKINDOFDOC.DOC11_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC12_YN , sizeof(tempKINDOFDOC.DOC12_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC14_YN , sizeof(tempKINDOFDOC.DOC14_YN) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempKINDOFDOC.DOC17_YN , sizeof(tempKINDOFDOC.DOC17_YN) , &m_nVal[nIndex-1]); nIndex++;

	AnsiString asSqlQry	= "";
	AnsiString asWhere	= "";

	asWhere	= "LAND_KEY = '" + _asLandCd.Trim() + "'";

	asSqlQry = "SELECT * FROM TB_KINDOFDOC WHERE " + asWhere + " ORDER BY LAND_KEY ASC";

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	m_vKINDOFDOCDATA.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		memset(&tempKINDOFDOC, 0x00, sizeof(KINDOFDOC_STRUCT));
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			m_vKINDOFDOCDATA.push_back(tempKINDOFDOC);

			memset(&tempKINDOFDOC, 0x00, sizeof(KINDOFDOC_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readMemoLandkeyData()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER m_nVal[1];

	memset(&tempMEMOLANDKEYDATA, 0x00, sizeof(MEMOLANDKEYDATA_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempMEMOLANDKEYDATA.LAND_KEY , sizeof(tempMEMOLANDKEYDATA.LAND_KEY) , &m_nVal[nIndex-1]); nIndex++;

	AnsiString mSqlQry;

	mSqlQry = "SELECT LAND_KEY FROM TB_MEMODATA ORDER BY LAND_KEY ASC";

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	m_vMEMOLANDKEYDATA.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		memset(&tempMEMOLANDKEYDATA, 0x00, sizeof(MEMOLANDKEYDATA_STRUCT));
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			m_vMEMOLANDKEYDATA.push_back(tempMEMOLANDKEYDATA);
			memset(&tempMEMOLANDKEYDATA, 0x00, sizeof(MEMOLANDKEYDATA_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readSelectMemoData(AnsiString _landcd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER m_nVal[5];

	memset(&tempMEMODATA, 0x00, sizeof(MEMODATA_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempMEMODATA.LAND_KEY    , sizeof(tempMEMODATA.LAND_KEY)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempMEMODATA.SEQNO      , sizeof(tempMEMODATA.SEQNO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempMEMODATA.MEMO_DATA   , sizeof(tempMEMODATA.MEMO_DATA)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempMEMODATA.LAST_UPDT   , sizeof(tempMEMODATA.LAST_UPDT)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempMEMODATA.LAST_WRITER , sizeof(tempMEMODATA.LAST_WRITER) , &m_nVal[nIndex-1]); nIndex++;

	AnsiString mSqlQry;

	mSqlQry = "SELECT * FROM TB_MEMODATA WHERE LAND_KEY='" + _landcd.Trim() + "' ORDER BY SEQNO DESC";

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	m_vMEMODATA.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		memset(&tempMEMODATA, 0x00, sizeof(MEMODATA_STRUCT));
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			m_vMEMODATA.push_back(tempMEMODATA);
			memset(&tempMEMODATA, 0x00, sizeof(MEMODATA_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::func_readReferenceCode()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	frmMain->m_vDATA_BASECODE.clear();
	frmMain->m_vDATA_ZONECODE.clear();

	SQLCHAR m_cVal[4][255+1];
	SQLINTEGER m_nVal[4];//10];
	AnsiString mSqlQry;
	SQLRETURN ret;
	AnsiString result[10];
	char min_cValue[255+1];
	AnsiString codediv;

    ////////////////////////////////////////
	BASENAME_STRUCT mTempBaseName;
	memset(&mTempBaseName, 0, sizeof(mTempBaseName));

	ZONENAME_STRUCT mTempZoneName;
	memset(&mTempZoneName, 0, sizeof(mTempZoneName));
//
	int nIndex = 1;

	memset(m_nVal, 0, sizeof(m_nVal));
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempBaseName.task_code     , sizeof(mTempBaseName.task_code)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempBaseName.kind_code     , sizeof(mTempBaseName.kind_code)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempBaseName.kind_name     , sizeof(mTempBaseName.kind_name)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempBaseName.doc_name      , sizeof(mTempBaseName.doc_name)        , &m_nVal[nIndex-1]); nIndex++;

//	if(frmIniControl->m_nODBCHowTo == 3 && !strcmp(frmIniControl->mIniStruct.cSidoCode, "31710") )
//		mSqlQry = "SELECT CONVERT(TASK_CODE, 'KO16KSC5601', 'KO16MSWIN949'), CONVERT(KIND_CODE, 'KO16KSC5601', 'KO16MSWIN949'), CONVERT(KIND_NAME, 'KO16KSC5601', 'KO16MSWIN949'), CONVERT(DOC_NAME, 'KO16KSC5601', 'KO16MSWIN949') FROM CD_KIND ORDER BY TASK_CODE, KIND_CODE ASC";
//	else
		mSqlQry = "SELECT TASK_CODE, KIND_CODE, KIND_NAME, DOC_NAME FROM CD_KIND ORDER BY TASK_CODE, KIND_CODE ASC";

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)mSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if ((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) )
	{
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		memset(&mTempBaseName, 0, sizeof(mTempBaseName));
		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			frmMain->m_vDATA_BASECODE.push_back(mTempBaseName);
			memset(&mTempBaseName, 0, sizeof(mTempBaseName));

		};

		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	//////////////////////
	nIndex = 1;
	memset(m_nVal, 0, sizeof(m_nVal));
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempZoneName.zonecode     , sizeof(mTempZoneName.zonecode)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempZoneName.zonename     , sizeof(mTempZoneName.zonename)       , &m_nVal[nIndex-1]); nIndex++;

	mSqlQry = "";
	mSqlQry = "SELECT ZONE_CODE, ZONE_NAME FROM ZONE_CODE ORDER BY ZONE_CODE ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		//180920//return하면 다른 코드들을 볼러올 수 없다.//return;
		//frmMsg->funcMessageDlg("정보부재알림:", "ZONE_CODE를 불러올 수 없습니다.", 3);
	}
	else{
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			frmMain->m_vDATA_ZONECODE.push_back(mTempZoneName);
			memset(&mTempZoneName, 0, sizeof(mTempZoneName));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	//======================================
	frmMain->cboKindDoc1->Items->Clear();
	//=============================================================================
	//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
	//=============================================================================
	if(frmMain->m_asParamStr2 != "SYSTEM_OK_USER_B")
		frmMain->cboKindDoc1->Items->Add("전체");
	frmMain->m_BASECODE_001_DOC1.clear();
	//======================================
	frmMain->cboInputDoc1->Items->Clear();
	frmMain->cboInputDoc1->Items->Add("전체");
	frmMain->m_BASECODE_101_DOC1.clear();
	//======================================
	frmMain->cboKindDoc7->Items->Clear();
	frmMain->cboKindDoc7->Items->Add(L"전체");
	frmMain->m_BASECODE_007_DOC7.clear();
	//======================================
	frmMain->cboScaleDoc7->Items->Clear();
	frmMain->cboScaleDoc7->Items->Add(L"전체");
	frmMain->m_vDATA_BASECODE_SCALERESULT.clear();
	//======================================
//	frmMain->cboKindDoc2->Items->Clear();
//	frmMain->cboKindDoc2->Items->Add(L"전체");
//	frmMain->cboKindDoc3->Items->Clear();
//	frmMain->cboKindDoc3->Items->Add(L"전체");
	frmMain->m_BASECODE_002_DOC2.clear();
	frmMain->m_BASECODE_003_DOC3.clear();
	//======================================
	frmMain->cboInputDoc2->Items->Clear();
	frmMain->cboInputDoc2->Items->Add(L"전체");
	frmMain->m_BASECODE_102_DOC2.clear();
	//======================================
	frmMain->cboKindDoc4->Items->Clear();
	frmMain->cboKindDoc4->Items->Add(L"전체");
	frmMain->m_BASECODE_004_DOC4.clear();
	//======================================
	frmMain->cboInputDoc5->Items->Clear();
	frmMain->cboInputDoc5->Items->Add(L"전체");
	frmMain->m_BASECODE_109_DOC5.clear();
	//======================================
	frmMain->cboKindDoc6->Items->Clear();
	frmMain->cboKindDoc6->Items->Add(L"전체");
	frmMain->m_BASECODE_006_DOC6.clear();
	//======================================
	frmMain->cboKindDoc8->Items->Clear();
//231226//[구대장.문서구분]에서는 '전체'제거// 	frmMain->cboKindDoc8->Items->Add(L"전체");
	frmMain->m_BASECODE_008_DOC8.clear();
	//======================================
	frmMain->cboInputDoc8->Items->Clear();
	frmMain->cboInputDoc8->Items->Add(L"전체");
	frmMain->m_BASECODE_108_DOC8.clear();
	//======================================
	frmMain->cboKindDoc9->Items->Clear();
	frmMain->cboKindDoc9->Items->Add(L"전체");
	frmMain->m_BASECODE_009_DOC9.clear();
	//======================================
	frmMain->cboKindDoc11->Items->Clear();
	frmMain->cboKindDoc11->Items->Add(L"전체");
	frmMain->m_BASECODE_011_DOC11.clear();
	//======================================
//	frmMain->cboKindDoc12->Items->Clear();
//	frmMain->cboKindDoc12->Items->Add(L"전체");
	frmMain->m_BASECODE_012_DOC12.clear();
	//======================================
	frmMain->cboKindDoc13->Items->Clear();
	frmMain->cboKindDoc13->Items->Add(L"전체");
	frmMain->m_BASECODE_042_DOC13.clear();
	//======================================
	frmMain->cboInputDoc14->Items->Clear();
	frmMain->cboInputDoc14->Items->Add(L"전체");
	frmMain->m_BASECODE_111_DOC14.clear();
	//======================================
	frmMain->m_BASECODE_015_DOC15.clear();
	//======================================
	//190225//cd_kind에 017이 없음. 007(지적도)와 같다고 판단함//
	frmMain->cboKindDoc17->Items->Clear();
	frmMain->cboKindDoc17->Items->Add(L"전체");
	frmMain->m_BASECODE_017_DOC17.clear();
	//======================================
	frmMain->cboKindDoc18->Items->Clear();
	frmMain->cboKindDoc18->Items->Add(L"전체");
	frmMain->m_BASECODE_018_DOC18.clear();
//=============================================================================
//231020//GAGAMLAYER in LandArchive //here//
//=============================================================================
	frmMain->cboKindDoc20->Items->Clear();
	frmMain->cboKindDoc20->Items->Add(L"전체");
	frmMain->m_BASECODE_020_DOC20.clear();
	//======================================
	frmMain->m_vDATA_BASECODE_SCALERESULT.clear();
	//210303//#503//사용자별 행위구분//
	//======================================
	frmUserLogList->cboAct->Items->Clear();
	frmUserLogList->cboAct->Items->Add(L"전체");
	frmUserLogList->cboGrade->Items->Clear();
	frmUserLogList->cboGrade->Items->Add(L"전체");
	//======================================
	frmMain->m_vDATA_BASECODE_503.clear();
	//======================================
	frmMain->m_BASECODE_801_DOC8.clear();

	for(int i=0; i<(int)frmMain->m_vDATA_BASECODE.size(); i++)
	{
		//======================================
		if(strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "001") == 0)
		{
			//=============================================================================
			//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
			//=============================================================================
			//ORG//frmMain->cboKindDoc1->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
			if(frmMain->m_asParamStr2 != "SYSTEM_OK_USER_B")
			{
				frmMain->m_BASECODE_001_DOC1.push_back(frmMain->m_vDATA_BASECODE[i]);
				frmMain->cboKindDoc1->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
			}
			else
			{
				if( !strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "조서") )
				{
					frmMain->m_BASECODE_001_DOC1.push_back(frmMain->m_vDATA_BASECODE[i]);
					frmMain->cboKindDoc1->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
				}
			}
			//=============================================================================
//			if(frmMain->INI_B_01ATTACH)
//			{
//				//frm01Attach->cboKindCode->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
//			}
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "101") == 0)
		{
			frmMain->m_BASECODE_101_DOC1.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboInputDoc1->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "007") == 0)
		{
			frmMain->m_BASECODE_007_DOC7.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc7->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		AnsiString  asStr	= "";//201119//사용자설정축척//
		int _index = 0;
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "502") == 0)
		{
			if(strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "수치") != 0)
			{
				frmMain->m_vDATA_BASECODE_SCALERESULT.push_back(frmMain->m_vDATA_BASECODE[i]);
				frmMain->cboScaleDoc7->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);

				//201119//사용자설정축척//
				TMenuItem	*mnuItem	= new TMenuItem(frmMain->PopupMenu2);
				mnuItem->AutoHotkeys       = maManual;
				mnuItem->AutoLineReduction = maManual;

				asStr	= (char*)frmMain->m_vDATA_BASECODE[i].kind_name;
				asStr	= StringReplace(asStr, "1:", "", TReplaceFlags() << rfReplaceAll);
				mnuItem->Caption	= asStr;
				mnuItem->Checked	= false;
				mnuItem->OnClick	= frmMain->mnuScaleClick;
				frmMain->PopupMenu2->Items->Add(mnuItem);
				frmMain->PopupMenu2->Items->Tag = _index;
				_index++;
				//delete mnuItem;
				//mnuItem	= NULL;
			}
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "002") == 0)
		{
			frmMain->m_BASECODE_002_DOC2.push_back(frmMain->m_vDATA_BASECODE[i]);
//			frmMain->cboKindDoc2->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
//			frmMain->cboKindDoc3->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "102") == 0)
		{
			frmMain->m_BASECODE_102_DOC2.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboInputDoc2->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "004") == 0)
		{
			frmMain->m_BASECODE_004_DOC4.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc4->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "109") == 0)
		{
			frmMain->m_BASECODE_109_DOC5.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboInputDoc5->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "006") == 0)
		{
			frmMain->m_BASECODE_006_DOC6.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc6->Items->Add( frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "008") == 0)
		{
			frmMain->m_BASECODE_008_DOC8.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc8->Items->Add( frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "108") == 0)
		{
			frmMain->m_BASECODE_108_DOC8.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboInputDoc8->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "009") == 0)
		{
			frmMain->m_BASECODE_009_DOC9.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc9->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "011") == 0)
		{
			frmMain->m_BASECODE_011_DOC11.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc11->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "012") == 0)
		{
			frmMain->m_BASECODE_012_DOC12.push_back(frmMain->m_vDATA_BASECODE[i]);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "004") == 0)
		{
			if (strcmp(frmMain->m_vDATA_BASECODE[i].kind_code, "42") == 0)
			{
				frmMain->m_BASECODE_042_DOC13.push_back(frmMain->m_vDATA_BASECODE[i]);//190225
				frmMain->cboKindDoc13->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
			}
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "111") == 0)
		{
			frmMain->m_BASECODE_111_DOC14.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboInputDoc14->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "015") == 0)
		{
			frmMain->m_BASECODE_015_DOC15.push_back(frmMain->m_vDATA_BASECODE[i]);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "017") == 0)
		{
			frmMain->m_BASECODE_017_DOC17.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc17->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
 		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "018") == 0)
		{
			frmMain->m_BASECODE_018_DOC18.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc18->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "020") == 0)//231020//GAGAMLAYER in LandArchive
		{
			frmMain->m_BASECODE_020_DOC20.push_back(frmMain->m_vDATA_BASECODE[i]);
			frmMain->cboKindDoc20->Items->Add(frmMain->m_vDATA_BASECODE[i].kind_name);
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "502") == 0)
		{
			if(strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "수치") != 0)
			{
				frmMain->m_vDATA_BASECODE_SCALERESULT.push_back(frmMain->m_vDATA_BASECODE[i]);
			}
		}
		//======================================
		if (strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "503") == 0)
		{
			frmMain->m_vDATA_BASECODE_503.push_back(frmMain->m_vDATA_BASECODE[i]);
			if( !strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "권한변경")
			 || !strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "휴면계정")
			 || !strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "삭제계정") )
			{
				frmUserLogList->cboGrade->Items->Add((char*)frmMain->m_vDATA_BASECODE[i].kind_name);
			}
			else if( strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "로그인시각")
			 && strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "로그아웃시각")
			 && strcmp(frmMain->m_vDATA_BASECODE[i].kind_name, "파일저장") )
			{
				frmUserLogList->cboAct->Items->Add((char*)frmMain->m_vDATA_BASECODE[i].kind_name);
			}
		}
		//======================================
		if(strcmp(frmMain->m_vDATA_BASECODE[i].task_code, "801") == 0)
		{
			frmMain->m_BASECODE_801_DOC8.push_back(frmMain->m_vDATA_BASECODE[i]);
		}
		//======================================
	}

	//======================================
	if((int)frmMain->m_BASECODE_001_DOC1.size() > 0)
		frmMain->cboKindDoc1->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_101_DOC1.size() > 0)
		frmMain->cboInputDoc1->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_007_DOC7.size() > 0)
		frmMain->cboKindDoc7->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_vDATA_BASECODE_SCALERESULT.size() > 0)
		frmMain->cboScaleDoc7->ItemIndex = 0;
	//======================================
//	if((int)frmMain->m_BASECODE_002_DOC2.size() > 0)
//	{
//		frmMain->cboKindDoc2->ItemIndex = 0;
//		frmMain->cboKindDoc3->ItemIndex = 0;
//	}
	//======================================
	if((int)frmMain->m_BASECODE_102_DOC2.size() > 0)
		frmMain->cboInputDoc2->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_004_DOC4.size() > 0)
		frmMain->cboKindDoc4->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_109_DOC5.size() > 0)
		frmMain->cboInputDoc5->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_006_DOC6.size() > 0)
		frmMain->cboKindDoc6->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_008_DOC8.size() > 0)
		frmMain->cboKindDoc8->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_108_DOC8.size() > 0)
		frmMain->cboInputDoc8->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_009_DOC9.size() > 0)
		frmMain->cboKindDoc9->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_011_DOC11.size() > 0)
		frmMain->cboKindDoc11->ItemIndex = 0;
	//======================================
//	if((int)frmMain->m_BASECODE_012_DOC12.size() > 0)
//		frmMain->cboKindDoc12->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_042_DOC13.size() > 0)
		frmMain->cboKindDoc13->ItemIndex = 1;
	//======================================
	if((int)frmMain->m_BASECODE_111_DOC14.size() > 0)
		frmMain->cboInputDoc14->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_017_DOC17.size() > 0)
		frmMain->cboKindDoc17->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_018_DOC18.size() > 0)
		frmMain->cboKindDoc18->ItemIndex = 0;
	//======================================
	if((int)frmMain->m_BASECODE_020_DOC20.size() > 0)//231020//GAGAMLAYER in LandArchive
		frmMain->cboKindDoc20->ItemIndex = 0;
	//======================================
	if(frmUserLogList->cboAct->Items->Count > 0)
		frmUserLogList->cboAct->ItemIndex = 0;
	if(frmUserLogList->cboGrade->Items->Count > 0)
		frmUserLogList->cboGrade->ItemIndex = 0;
	//======================================
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::func_readSidoCode()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR 		m_cVal[6][32];
	SQLINTEGER 		m_nVal[6];
	AnsiString 		mSqlQry;
	SQLRETURN 		ret;
	AnsiString 		asResult[6];
	char 			min_cValue[32];

	SIDONAME_STRUCT tempUMDNAME;

	AnsiString      asSidoType;
	AnsiString      asOrderBy;
	AnsiString      asUmdNm;
	AnsiString      asRiNm;
	AnsiString      asUmdNmBck;
	AnsiString      asRiNmBck;
	int				nPos = -1;


	for (int i=0; i<6; i++)
		SQLBindCol(m_hStmt, i+1, SQL_C_CHAR, m_cVal[i], sizeof(m_cVal[i]), &m_nVal[i]);

	asSidoType = frmMain->INIINFO.SIDOCODE;
	//200220//mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE WHERE SIDOSGG_CD LIKE '" + asSidoType.Trim() + "%' ORDER BY SIDOSGG_CD " + asOrderBy.Trim() + ", UMD_CD, RI_CD ASC";
	if (asSidoType == "36110")
	{
		mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " ORDER BY SIDOSGG_CD, UMD_CD, RI_CD ASC";
	}
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(asSidoType == "11305")
	{
		mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + " ORDER BY SIDOSGG_CD, UMD_CD, RI_CD ASC";
	}
//=============================================================================
	else
	{
		if (asSidoType == "44133")
			asOrderBy = " DESC";

		mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE WHERE SIDOSGG_CD LIKE '" + asSidoType.Trim() + "%' ORDER BY SIDOSGG_CD " + asOrderBy.Trim() + ", UMD_CD, RI_CD ASC";
	}

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)mSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	frmMain->m_vDATA_SIDOCODE.clear();
	frmStat->m_vUMDRICODE.clear();//220204//#STAT_DOC8

	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA)) {
		SQLCloseCursor(m_hStmt);
		AnsiString strMsg = "SIDO CODE 읽기 오류 입니다.";
		frmMsg->funcMessageDlg("DB 부재 알림:", strMsg, 2);
		return -1;
	}

	for (int i=0; i<6; i++) {
		memset(m_cVal[i], 0x00, sizeof(m_cVal[i]));
		asResult[i] = "";
	}

	while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		for (int i=0; i<6; i++) {
			memset(min_cValue, 0x00, sizeof(min_cValue));
			memcpy(min_cValue, m_cVal[i], sizeof(min_cValue));
			asResult[i] = min_cValue;
		}

		memset(&tempUMDNAME, 0, sizeof(tempUMDNAME));
		wsprintf(tempUMDNAME.cSggCd, asResult[0].c_str(), asResult[0].Length());
		wsprintf(tempUMDNAME.cUmdCd, asResult[1].c_str(), asResult[1].Length());
		wsprintf(tempUMDNAME.cRiCd,  asResult[2].c_str(), asResult[2].Length());
		wsprintf(tempUMDNAME.cSggNm, "%s", asResult[3]);
		wsprintf(tempUMDNAME.cUmdNm, "%s", asResult[4]);
		wsprintf(tempUMDNAME.cRiNm, "%s", asResult[5]);

		if (memcmp(tempUMDNAME.cSggCd, "44130", 5) == 0 || memcmp(tempUMDNAME.cSggCd, "31000", 5) == 0)
		{}
		else {
			//====================================================================
			//220204//#STAT_DOC8//
			AnsiString      asUmdCd	= "";
			AnsiString      asRiCd	= "";
			AnsiString      asUmdNm	= "";
			AnsiString      asRiNm	= "";
			UMDRICODE_STRUCT 			tempUMDRICODE;

			memset(&tempUMDRICODE, 0x00, sizeof(UMDRICODE_STRUCT));

			asUmdCd	= (char*)tempUMDNAME.cUmdCd;
			asRiCd	= (char*)tempUMDNAME.cRiCd;
			asUmdNm	= (char*)tempUMDNAME.cUmdNm;
			asRiNm	= (char*)tempUMDNAME.cRiNm;

			if( (asRiCd == "00" && asUmdCd.SubString(1, 1) == "1")
				|| (asRiCd != "00" && asUmdCd.SubString(1, 1) != "1") )
			{
				strcpy(tempUMDRICODE.CD, (asUmdCd + asRiCd).c_str());
				strcpy(tempUMDRICODE.NM, (asUmdNm + " " + asRiNm).c_str());
				frmStat->m_vUMDRICODE.push_back(tempUMDRICODE);
			}
			//====================================================================

			frmMain->m_vDATA_SIDOCODE.push_back(tempUMDNAME);

			//200226//
			asUmdNm	= (char*)tempUMDNAME.cUmdNm;
			asRiNm	= (char*)tempUMDNAME.cRiNm;
			asUmdNmBck	= asUmdNm;//200910//
			asRiNmBck   = asRiNm;//200910//

			//
			if( !asUmdNm.IsEmpty() )
			{
				frmMain->m_vSIDOCODE_CMP1.push_back(tempUMDNAME);//200910//
				frmMain->m_vSIDOCODE_DATA1.push_back(tempUMDNAME);//200910//

				if(asUmdNm.Trim().SubString(asUmdNm.Trim().Length()-1, 2) == "읍")
				{
					asUmdNm = asUmdNm.SubString(1, asUmdNm.Trim().Length()-2);
				}
				else
				{
					if(asUmdNm.Trim().SubString(asUmdNm.Trim().Length()-1, 2) == "면")
					{
						asUmdNm = asUmdNm.SubString(1, asUmdNm.Trim().Length()-2);
					}
					else
					{
						if(asUmdNm.Trim().SubString(asUmdNm.Trim().Length()-1, 2) == "동")
						{
							asUmdNm = asUmdNm.SubString(1, asUmdNm.Trim().Length()-2);
						}
					}
				}

				//
				if( !asRiNm.IsEmpty() )
				{
					if(asRiNm.Trim().SubString(asRiNm.Trim().Length()-1, 2) == "리")
					{
						asRiNm = asRiNm.SubString(1, asRiNm.Trim().Length()-2);
					}

					//===================================================================
					//200910
					//읍면동 만 제거//
					memcpy(tempUMDNAME.cUmdNm, asUmdNm.c_str(), sizeof(tempUMDNAME.cUmdNm));
					frmMain->m_vSIDOCODE_DATA3.push_back(tempUMDNAME);

					//읍면동, 리 모두 제거//
					memcpy(tempUMDNAME.cRiNm, asRiNm.c_str(), sizeof(tempUMDNAME.cRiNm));
					frmMain->m_vSIDOCODE_DATA2.push_back(tempUMDNAME);

					//리 만 제거//
					memcpy(tempUMDNAME.cUmdNm, asUmdNmBck.c_str(), sizeof(tempUMDNAME.cUmdNm));
					frmMain->m_vSIDOCODE_DATA4.push_back(tempUMDNAME);

					//읍면동 데이터는 안 갖고 있고, 리명만 갖고 있음//
					memcpy(tempUMDNAME.cUmdNm, "", sizeof(tempUMDNAME.cUmdNm));
					memcpy(tempUMDNAME.cRiNm, asRiNmBck.c_str(), sizeof(tempUMDNAME.cRiNm));
					frmMain->m_vSIDOCODE_DATA5.push_back(tempUMDNAME);
					//===================================================================
				}

				//읍면동, 리 모두 제거//
				memcpy(tempUMDNAME.cRiNm, asRiNm.c_str(), sizeof(tempUMDNAME.cRiNm));
				frmMain->m_vSIDOCODE_CMP2.push_back(tempUMDNAME);
			}
		}

		for(int i=0; i<6; i++){
			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
			asResult[i] = "";
		}
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//JDM
	if (frmMain->m_vDATA_SIDOCODE.size() < 1)
		return -1;

	return 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument01(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[12];
	SQLRETURN ret;
	DOCUMENT01_STRUCT 				tempDocument01;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));
	int nIndex = 1;

	//distinct ROLL_NO, FRAME_NO, KIND_CODE, KWON_NO, PAGE_NO, SUBMIT_YEAR, PRCS_DATE, MEASURE_TYPE, GROUP_NO, GROUP_NO1, AF_PNU, PATH_NAME
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.ROLL_NO       , sizeof(tempDocument01.ROLL_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.FRAME_NO      , sizeof(tempDocument01.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
	//M//191114//SR_NO, BF_PNU 제외//SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.SR_NO         , sizeof(tempDocument01.SR_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.KWON_NO        , sizeof(tempDocument01.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.KIND_CODE      , sizeof(tempDocument01.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PAGE_NO        , sizeof(tempDocument01.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.SUBMIT_YEAR    , sizeof(tempDocument01.SUBMIT_YEAR)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PRCS_DATE      , sizeof(tempDocument01.PRCS_DATE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.MEASURE_TYPE   , sizeof(tempDocument01.MEASURE_TYPE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.GROUP_NO      , sizeof(tempDocument01.GROUP_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.GROUP_NO1     , sizeof(tempDocument01.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;
	//M//191114//SR_NO, BF_PNU 제외//SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.BF_PNU   	  , sizeof(tempDocument01.BF_PNU)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.AF_PNU      	  , sizeof(tempDocument01.AF_PNU)      		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PATH_NAME      , sizeof(tempDocument01.PATH_NAME)      	, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument01.clear();

	memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));

	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument01.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument01.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument01.size(); i++)
		{
			if( !strcmp(tempDocument01.PATH_NAME, frmMain->m_ResultDocument01[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//200313//
			if( 	 !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
				  && !strcmp(tempDocument01.PRCS_DATE, frmMain->m_ResultDocument01[i].PRCS_DATE)
				  && !strcmp(tempDocument01.MEASURE_TYPE, frmMain->m_ResultDocument01[i].MEASURE_TYPE)
				  && !strcmp(tempDocument01.KIND_CODE, frmMain->m_ResultDocument01[i].KIND_CODE))
			{
				bSamePathName = true;
				break;
			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument01.push_back(tempDocument01);
		memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//=============================================================================
	//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
	//=============================================================================
	if(frmMain->m_asParamStr2 != "SYSTEM_OK_USER_B")
	{
	//	//210302//#DOC01GROUP_TEST
		int nCount = 0;
		for(int i = 0; i < (int)frmMain->m_ResultDocument01.size(); i++)
		{
			nCount = funcSelReadDoc01Group(i);
			i += nCount;
		}
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSelReadDoc01Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[11];
	SQLRETURN ret;
	DOCUMENT01_STRUCT 				tempDocument01;

	AnsiString asSql  = "";
	AnsiString asSqlA = "";
	AnsiString asSqlB = "";
	AnsiString asSqlC = "";
	AnsiString asSqlD = "";
	AnsiString asSqlE = "";
	AnsiString asSqlF = "";
	AnsiString asSqlG = "";
	AnsiString asCol  = "";
	AnsiString asOrderBy = "";
	int nIndex = 1;
	int nCount = 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.ROLL_NO, 		sizeof(tempDocument01.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.KWON_NO, 		sizeof(tempDocument01.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.KIND_CODE, 		sizeof(tempDocument01.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PAGE_NO, 		sizeof(tempDocument01.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PRCS_DATE, 		sizeof(tempDocument01.PRCS_DATE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.GROUP_NO, 		sizeof(tempDocument01.GROUP_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.GROUP_NO1, 	sizeof(tempDocument01.GROUP_NO1), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.MEASURE_TYPE, 	sizeof(tempDocument01.MEASURE_TYPE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.BF_PNU, 		sizeof(tempDocument01.BF_PNU), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.AF_PNU, 		sizeof(tempDocument01.AF_PNU), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PATH_NAME, 		sizeof(tempDocument01.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;

	asCol  = "distinct ROLL_NO, KWON_NO, KIND_CODE, PAGE_NO, PRCS_DATE, GROUP_NO, GROUP_NO1, MEASURE_TYPE, BF_PNU, AF_PNU, PATH_NAME";
	//191210//문서구분별 중복을 없애라고 하심//사장님Req//
	AnsiString asTemp = (char*)frmMain->m_ResultDocument01[_nIndex].KWON_NO;

	asSqlA = " WHERE KWON_NO = '" + asTemp + "'";
	asSqlB = " AND GROUP_NO = " + IntToStr(frmMain->m_ResultDocument01[_nIndex].GROUP_NO);//그룹1만 처리//

	//201221//그룹1,2 처리//
	if(frmMain->INIUSERSETINFO.DOC01GROUP == 2)
	{
		asSqlC =  " AND (GROUP_NO1 = " + IntToStr(frmMain->m_ResultDocument01[_nIndex].GROUP_NO1) + " OR KIND_CODE = '12' OR GROUP_NO1 = 1)";
	}
	//210303//그룹1처리//
//	else//210218//GROUP_NO가 같은 모든 데이터 검색이므로 결의서를 특정하면 구비서류등이 나오지 않음.//4413136025104950002//
//	//210108//결의서 또는 구비서류 또는 GROUP_NO1=1 인 데이터는 항상 검색//
//	{
//		asSqlC =  " AND (KIND_CODE = '12' OR GROUP_NO1 = 1)";
//	}

	asSqlD = " AND PRCS_DATE = '" + AnsiString(frmMain->m_ResultDocument01[_nIndex].PRCS_DATE) + "'";
	asSqlE = " AND MEASURE_TYPE = '" + AnsiString(frmMain->m_ResultDocument01[_nIndex].MEASURE_TYPE) + "'";
	asSqlF = " AND (KIND_CODE != '13' AND KIND_CODE != '50')";

	asOrderBy = " ORDER BY KWON_NO, KIND_CODE, PAGE_NO, GROUP_NO, GROUP_NO1 ASC";//190212

	asSql = "SELECT " + asCol + " FROM TB_DOCUMENT01" + asSqlA + asSqlB + asSqlC + asSqlD +  asSqlE + asSqlF + asOrderBy;


	frmSearch->funcSaveLog(1, 1, asSql);//save to file//200427


	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}
	else {
		memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));

		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			bSamePathName = false;
			asPathName = (char*)tempDocument01.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument01.PATH_NAME, asPathName.c_str());

			for(int i = 0; i < (int)frmMain->m_ResultDocument01.size(); i++)
			{
				if( !strcmp(tempDocument01.PATH_NAME, frmMain->m_ResultDocument01[i].PATH_NAME) )
				{
					bSamePathName = true;
					break;
				}
				//201022//필터링 해제//
//				//200313//
//				if(  	 !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//					  && !strcmp(tempDocument01.PRCS_DATE, frmMain->m_ResultDocument01[i].PRCS_DATE)
//					  && !strcmp(tempDocument01.MEASURE_TYPE, frmMain->m_ResultDocument01[i].MEASURE_TYPE)
//					  && !strcmp(tempDocument01.KIND_CODE, frmMain->m_ResultDocument01[i].KIND_CODE))
//				{
//					bSamePathName = true;
//					break;
//				}
			}
			if( !bSamePathName )
			{
				nCount++;
				frmMain->m_ResultDocument01.insert(frmMain->m_ResultDocument01.begin() + (_nIndex + nCount), tempDocument01);
			}
			memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument02(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asLabelDay1		= "";
	AnsiString  asLabelDay2		= "";
	AnsiString  asPathName		= "";
	bool		bSamePathName 	= false;
	SQLRETURN ret;
	SQLINTEGER m_nVal[22];
	DOCUMENT02_STRUCT 				tempDocument02;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument02, 0x00, sizeof(DOCUMENT02_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.ROLL_NO        , sizeof(tempDocument02.ROLL_NO)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.FRAME_NO       , sizeof(tempDocument02.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.KWON_NO         , sizeof(tempDocument02.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.PAGE_NO         , sizeof(tempDocument02.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.DOHO            , sizeof(tempDocument02.DOHO)           , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.DOHO_SUB        , sizeof(tempDocument02.DOHO_SUB)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_DAY        , sizeof(tempDocument02.SURV_DAY)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_NAME       , sizeof(tempDocument02.SURV_NAME)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.INSPCT_DAY      , sizeof(tempDocument02.INSPCT_DAY)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.INSPCT_NAME     , sizeof(tempDocument02.INSPCT_NAME)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_YEAR       , sizeof(tempDocument02.SURV_YEAR)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_ITEM       , sizeof(tempDocument02.SURV_ITEM)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.RDSCALE_CODE    , sizeof(tempDocument02.RDSCALE_CODE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.BF_PNU   	    , sizeof(tempDocument02.BF_PNU)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.AF_PNU      	, sizeof(tempDocument02.AF_PNU)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.PATH_NAME       , sizeof(tempDocument02.PATH_NAME)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.KIND_CODE       , sizeof(tempDocument02.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SUBMIT_DATE     , sizeof(tempDocument02.SUBMIT_DATE)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.POS_X   	    , sizeof(tempDocument02.POS_X)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.POS_Y  	    , sizeof(tempDocument02.POS_Y)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.GROUP_NO   	, sizeof(tempDocument02.GROUP_NO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.PRCS_NO  	    , sizeof(tempDocument02.PRCS_NO)      	, &m_nVal[nIndex-1]); nIndex++;
//	//200424//DOC02GROUP
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.ROLL_NO        , sizeof(tempDocument02.ROLL_NO)		, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.FRAME_NO       , sizeof(tempDocument02.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.KIND_CODE       , sizeof(tempDocument02.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.KWON_NO         , sizeof(tempDocument02.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.PAGE_NO         , sizeof(tempDocument02.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_DAY        , sizeof(tempDocument02.SURV_DAY)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_NAME       , sizeof(tempDocument02.SURV_NAME)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.INSPCT_DAY      , sizeof(tempDocument02.INSPCT_DAY)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.INSPCT_NAME     , sizeof(tempDocument02.INSPCT_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SUBMIT_DATE     , sizeof(tempDocument02.SUBMIT_DATE)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_ITEM       , sizeof(tempDocument02.SURV_ITEM)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.GROUP_NO       , sizeof(tempDocument02.GROUP_NO)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.DOHO            , sizeof(tempDocument02.DOHO)           , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.DOHO_SUB        , sizeof(tempDocument02.DOHO_SUB)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.RDSCALE_CODE    , sizeof(tempDocument02.RDSCALE_CODE)   , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.POS_X   	    , sizeof(tempDocument02.POS_X)   		, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.POS_Y  	    , sizeof(tempDocument02.POS_Y)      	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.BF_PNU   	    , sizeof(tempDocument02.BF_PNU)   		, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.AF_PNU      	, sizeof(tempDocument02.AF_PNU)      	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.PATH_NAME       , sizeof(tempDocument02.PATH_NAME)      , &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument02.clear();

	memset(&tempDocument02, 0x00, sizeof(DOCUMENT02_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument02.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument02.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument02.size(); i++)
		{
			if( !strcmp(tempDocument02.PATH_NAME, frmMain->m_ResultDocument02[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}

			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
				asLabelDay1 = (char*)frmMain->m_ResultDocument02[i].SURV_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
				asLabelDay1 = (char*)frmMain->m_ResultDocument02[i].INSPCT_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
				asLabelDay1 = (char*)frmMain->m_ResultDocument02[i].SUBMIT_DATE;

			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
				asLabelDay2 = (char*)tempDocument02.SURV_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
				asLabelDay2 = (char*)tempDocument02.INSPCT_DAY;
			else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
				asLabelDay2 = (char*)tempDocument02.SUBMIT_DATE;

			//201012//#ALLSEARCHLABEL
//			if(  	 asLabelDay2 == asLabelDay1
//				  && !strcmp(tempDocument02.SURV_ITEM, frmMain->m_ResultDocument02[i].SURV_ITEM)
//				  && !strcmp(tempDocument02.KIND_CODE, frmMain->m_ResultDocument02[i].KIND_CODE))
////			//200424//DOC02GROUP
////			if(  	 asLabelDay2 == asLabelDay1
////				  && !strcmp(tempDocument02.SURV_ITEM, frmMain->m_ResultDocument02[i].SURV_ITEM)
////				  && !strcmp(tempDocument02.KIND_CODE, frmMain->m_ResultDocument02[i].KIND_CODE)
////				  && tempDocument02.GROUP_NO == frmMain->m_ResultDocument02[i].GROUP_NO)
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument02.push_back(tempDocument02);
		memset(&tempDocument02, 0x00, sizeof(DOCUMENT02_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

//	//200424//DOC02GROUP
//	int nCount = 0;
//	for(int i = 0; i < (int)frmMain->m_ResultDocument02.size(); i++)
//	{
//		if(i < (int)frmMain->m_ResultDocument02.size() - 1)
//		{
//			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
//				asLabelDay1 = (char*)frmMain->m_ResultDocument02[i].SURV_DAY;
//			else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
//				asLabelDay1 = (char*)frmMain->m_ResultDocument02[i].INSPCT_DAY;
//			else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
//				asLabelDay1 = (char*)frmMain->m_ResultDocument02[i].SUBMIT_DATE;
//
//			if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
//				asLabelDay2 = (char*)frmMain->m_ResultDocument02[i+1].SURV_DAY;
//			else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
//				asLabelDay2 = (char*)frmMain->m_ResultDocument02[i+1].INSPCT_DAY;
//			else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
//				asLabelDay2 = (char*)frmMain->m_ResultDocument02[i+1].SUBMIT_DATE;
//
//			//Next Vector과 일자&&종목&&GROUP_NO//같으면 Skip
//			//측량, 면적 문서가 먼저 검색되고 측량 문서에서 Group 검색을 하니까 측량, 면적 중간에 구비서류가 들어가서 아래와 같이 처리//
//			if(  	 asLabelDay2 == asLabelDay1
//				  && !strcmp(frmMain->m_ResultDocument02[i].SURV_ITEM, frmMain->m_ResultDocument02[i+1].SURV_ITEM)
//				  && frmMain->m_ResultDocument02[i].GROUP_NO == frmMain->m_ResultDocument02[i+1].GROUP_NO)
//			{
//				continue;
//			}
//		}
//
//		nCount = funcSelReadDoc02Group(i);
//		i += nCount;
//	}


	//=============================================================================
	//260723//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
	//=============================================================================
	if(frmMain->m_asParamStr2 != "SYSTEM_OK_USER_B")
	{
		int nCount = 0;
		for(int i = 0; i < (int)frmMain->m_ResultDocument02.size(); i++)
		{
			nCount = funcSelReadDoc02Group(i);
			i += nCount;
		}
	}

}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSelReadDoc02Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	DOCUMENT02_STRUCT 				tempDocument02;

	AnsiString asSql  = "";
	AnsiString asSqlA = "";
	AnsiString asSqlB = "";
	AnsiString asSqlC = "";
	AnsiString asSqlD = "";
	AnsiString asSqlE = "";
	AnsiString asSqlF = "";
	AnsiString asSqlG = "";
	AnsiString asCol  = "";
	AnsiString asOrderBy = "";
	int nIndex = 1;
	int nCount = 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument02, 0x00, sizeof(DOCUMENT02_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.ROLL_NO, 		sizeof(tempDocument02.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.KWON_NO, 		sizeof(tempDocument02.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.KIND_CODE, 		sizeof(tempDocument02.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.PAGE_NO, 		sizeof(tempDocument02.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_DAY, 		sizeof(tempDocument02.SURV_DAY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.INSPCT_DAY, 	sizeof(tempDocument02.INSPCT_DAY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SUBMIT_DATE, 	sizeof(tempDocument02.SUBMIT_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.SURV_ITEM, 	    sizeof(tempDocument02.SURV_ITEM), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument02.GROUP_NO, 		sizeof(tempDocument02.GROUP_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.DOHO, 	        sizeof(tempDocument02.DOHO), 	        &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.RDSCALE_CODE, 	sizeof(tempDocument02.RDSCALE_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.BF_PNU, 		sizeof(tempDocument02.BF_PNU), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.AF_PNU, 		sizeof(tempDocument02.AF_PNU), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument02.PATH_NAME, 		sizeof(tempDocument02.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;

	asCol  = "distinct ROLL_NO, KWON_NO, KIND_CODE, PAGE_NO, SURV_DAY, INSPCT_DAY, SUBMIT_DATE, SURV_ITEM, GROUP_NO, DOHO, RDSCALE_CODE, BF_PNU, AF_PNU, PATH_NAME";
	//191210//문서구분별 중복을 없애라고 하심//사장님Req//
	AnsiString asTemp = (char*)frmMain->m_ResultDocument02[_nIndex].KWON_NO;
	asSqlA = " WHERE KWON_NO = '" + asTemp + "'";
	asSqlB = " AND GROUP_NO = " + IntToStr(frmMain->m_ResultDocument02[_nIndex].GROUP_NO);
	asSqlE = " AND SUBMIT_DATE = '" + AnsiString(frmMain->m_ResultDocument02[_nIndex].SUBMIT_DATE) + "'";
	asSqlF = " AND SURV_ITEM = '" + AnsiString(frmMain->m_ResultDocument02[_nIndex].SURV_ITEM) + "'";
	asSqlG = " AND AF_PNU = ''";//KIND_CODE != '01' AND KIND_CODE != '02'";

	asOrderBy = " ORDER BY ";
	if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
		asOrderBy = asOrderBy + "SURV_DAY DESC, ";
	else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
		asOrderBy = asOrderBy + "INSPCT_DAY DESC, ";
	else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
		asOrderBy = asOrderBy + "SUBMIT_DATE DESC, ";
	asOrderBy = asOrderBy + "KIND_CODE, PATH_NAME, AF_PNU, BF_PNU ASC";

	asSql = "SELECT " + asCol + " FROM TB_DOCUMENT02" + asSqlA + asSqlB + asSqlC + asSqlD +  asSqlE + asSqlF + asSqlG + asOrderBy;


	frmSearch->funcSaveLog(1, 2, asSql);//save to file//200427


	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}
	else {
		memset(&tempDocument02, 0x00, sizeof(DOCUMENT02_STRUCT));

		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			bSamePathName = false;
			asPathName = (char*)tempDocument02.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument02.PATH_NAME, asPathName.c_str());

			for(int i = 0; i < (int)frmMain->m_ResultDocument02.size(); i++)
			{
				if( !strcmp(tempDocument02.PATH_NAME, frmMain->m_ResultDocument02[i].PATH_NAME) )
				{
					bSamePathName = true;
					break;
				}
				//201022//필터링 해제//
				//200313//
//				if(  	 !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//					  && !strcmp(tempDocument02.SUBMIT_DATE, frmMain->m_ResultDocument02[i].SUBMIT_DATE)
//					  && !strcmp(tempDocument02.SURV_ITEM, frmMain->m_ResultDocument02[i].SURV_ITEM)
//					  && !strcmp(tempDocument02.KIND_CODE, frmMain->m_ResultDocument02[i].KIND_CODE)
//					  && tempDocument02.GROUP_NO == frmMain->m_ResultDocument02[i].GROUP_NO)
//				{
//					bSamePathName = true;
//					break;
//				}
			}
			if( !bSamePathName )
			{
				nCount++;
				frmMain->m_ResultDocument02.insert(frmMain->m_ResultDocument02.begin() + (_nIndex + nCount), tempDocument02);
			}
			memset(&tempDocument02, 0x00, sizeof(DOCUMENT02_STRUCT));
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------


void __fastcall TfrmSql::funcReadDocument03(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName		 = "";
	bool		bSamePathName = false;
	SQLRETURN ret;
	SQLINTEGER m_nVal[14];
	DOCUMENT03_STRUCT 				tempDocument03;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument03, 0x00, sizeof(DOCUMENT03_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument03.ROLL_NO        , sizeof(tempDocument03.ROLL_NO)			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument03.FRAME_NO       , sizeof(tempDocument03.FRAME_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument03.SR_NO          , sizeof(tempDocument03.SR_NO)          	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.KIND_CODE       , sizeof(tempDocument03.KIND_CODE)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.KWON_NO         , sizeof(tempDocument03.KWON_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.PAGE_NO         , sizeof(tempDocument03.PAGE_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.SURV_YEAR       , sizeof(tempDocument03.SURV_YEAR)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.SURV_DAY        , sizeof(tempDocument03.SURV_DAY)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.SURV_NAME       , sizeof(tempDocument03.SURV_NAME)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.INSPCT_DAY      , sizeof(tempDocument03.INSPCT_DAY)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.INSPCT_NAME     , sizeof(tempDocument03.INSPCT_NAME)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.BF_PNU   	     , sizeof(tempDocument03.BF_PNU)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.AF_PNU      	 , sizeof(tempDocument03.AF_PNU)      		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument03.PATH_NAME       , sizeof(tempDocument03.PATH_NAME)       	, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument03.clear();

	memset(&tempDocument03, 0x00, sizeof(DOCUMENT03_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument03.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument03.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument03.size(); i++)
		{
			if( !strcmp(tempDocument03.PATH_NAME, frmMain->m_ResultDocument03[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument03.push_back(tempDocument03);
		memset(&tempDocument03, 0x00, sizeof(DOCUMENT03_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument04(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName		 = "";
	bool		bSamePathName = false;
	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	DOCUMENT04_STRUCT 				tempDocument04;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument04.ROLL_NO        , sizeof(tempDocument04.ROLL_NO)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PAGE_NO         , sizeof(tempDocument04.PAGE_NO)         	, &m_nVal[nIndex-1]); nIndex++;
	//181231//SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument04.PAGE_NO      , sizeof(tempDocument04.PAGE_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.KWON_NO         , sizeof(tempDocument04.KWON_NO)			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REQ_YEAR        , sizeof(tempDocument04.REQ_YEAR)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REQ_DAY         , sizeof(tempDocument04.REQ_DAY)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.OWN_NAME        , sizeof(tempDocument04.OWN_NAME)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.OWN_REG_NO      , sizeof(tempDocument04.OWN_REG_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.ISSUE_NO        , sizeof(tempDocument04.ISSUE_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.APROV_STATUS    , sizeof(tempDocument04.APROV_STATUS)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.LAW_NO          , sizeof(tempDocument04.LAW_NO)          	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.KIND_CODE       , sizeof(tempDocument04.KIND_CODE)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REC_NO          , sizeof(tempDocument04.REC_NO)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PATH_NAME       , sizeof(tempDocument04.PATH_NAME)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PNU             , sizeof(tempDocument04.PNU)       		, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument04.clear();

	memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument04.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument04.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument04.size(); i++)
		{
			if( !strcmp(tempDocument04.PATH_NAME, frmMain->m_ResultDocument04[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201015//#ALLSEARCHLABEL
//			//200313//
//			if(    !strcmp(tempDocument04.REQ_DAY, frmMain->m_ResultDocument04[i].REQ_DAY)
//				&& !strcmp(tempDocument04.REC_NO, frmMain->m_ResultDocument04[i].REC_NO))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument04.push_back(tempDocument04);
		memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

//======================================================
//230420//그룹검색이 필요했는데, LAW_NO, REQ_DAY, REC_NO 기준으로 폴더링하면 필요 없다//
////230403//#ADD_FUNC_DOC04_44130//
	AnsiString  asStr = "";
	int nCount = 0;//230502//그룹핑기준 : LAW_NO//
	for(int i = 0; i < (int)frmMain->m_ResultDocument04.size(); i++)
	{
		//REC_NO 데이터가 비어있지 않은 것만 추가적으로 찾기//
		asStr = (char*)frmMain->m_ResultDocument04[i].REC_NO;
		if( !asStr.IsEmpty() )
		{
			nCount = funcSelReadDoc04Group(i);
			i += nCount;//230502//그룹핑기준 : LAW_NO//
		}
	}
//======================================================
}
//---------------------------------------------------------------------------

//230403//#ADD_FUNC_DOC04_44130//KIND_CODE 별 한 개의 문서만 표시//
int __fastcall TfrmSql::funcSelReadDoc04Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlQry  = "";
	AnsiString  asColumn  = "";
	AnsiString 	asWhere	  = "";
	AnsiString  asOrderBy = "LAW_NO DESC, REQ_DAY DESC, REC_NO, KIND_CODE, PATH_NAME, PNU, ROLL_NO ASC";
	AnsiString 	asStr	  = "";
	AnsiString  asRecNo		= "";
	AnsiString  asKwonNo	= "";
	AnsiString  asPathName	= "";
	AnsiString  asKindCode	= "";
	bool		bSameData   = false;
	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	DOCUMENT04_STRUCT 				tempDocument04;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
	int nIndex = 1;
	int nCount = 0;//230502//그룹핑기준 : LAW_NO//

	//asColumn  = "distinct ROLL_NO, KWON_NO, OWN_NAME, KIND_CODE, REC_NO, PATH_NAME";
	asColumn  = "*";
	//REC_NO 찾기//
	asRecNo = (char*)frmMain->m_ResultDocument04[_nIndex].REC_NO;
	asKwonNo = (char*)frmMain->m_ResultDocument04[_nIndex].KWON_NO;
//230503//	asWhere = asWhere + "(REC_NO LIKE '%/" + asStr + "/%' OR REC_NO = '" + asStr + "')";
	asWhere = asWhere + "(KWON_NO='" + asKwonNo + "' AND REC_NO = '" + asRecNo + "')";
	//REQ_DAY//
	asStr = (char*)frmMain->m_ResultDocument04[_nIndex].REQ_DAY;
	asWhere = asWhere + " AND REQ_DAY = '" + asStr + "'";

	//[TODO]이건 고려할 필요가 있음//OWN_NAME 찾기//
	/* TODO :
천안 특조법 구축, 통합검색, 그룹쿼리, 소유자명 다수 시 처리방법 모호
=> 관련하여 통합검색에서는 REC_NO만 그룹쿼리하는 것으로 진행 */
//	asStr = (char*)frmMain->m_ResultDocument04[_nIndex].OWN_NAME;
//	if( !asStr.IsEmpty() )
//		asWhere = asWhere + " OWN_NAME LIKE '%/" + asStr + "/%'";

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument04.ROLL_NO        , sizeof(tempDocument04.ROLL_NO)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PAGE_NO         , sizeof(tempDocument04.PAGE_NO)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.KWON_NO         , sizeof(tempDocument04.KWON_NO)			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REQ_YEAR        , sizeof(tempDocument04.REQ_YEAR)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REQ_DAY         , sizeof(tempDocument04.REQ_DAY)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.OWN_NAME        , sizeof(tempDocument04.OWN_NAME)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.OWN_REG_NO      , sizeof(tempDocument04.OWN_REG_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.ISSUE_NO        , sizeof(tempDocument04.ISSUE_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.APROV_STATUS    , sizeof(tempDocument04.APROV_STATUS)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.LAW_NO          , sizeof(tempDocument04.LAW_NO)          	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.KIND_CODE       , sizeof(tempDocument04.KIND_CODE)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REC_NO          , sizeof(tempDocument04.REC_NO)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PATH_NAME       , sizeof(tempDocument04.PATH_NAME)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PNU             , sizeof(tempDocument04.PNU)       		, &m_nVal[nIndex-1]); nIndex++;

	asSqlQry.sprintf("SELECT %s FROM TB_DOCUMENT04 WHERE %s ORDER BY %s", asColumn, asWhere, asOrderBy);
	//
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}

	memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSameData = false;
		//
		asRecNo = (char*)tempDocument04.REC_NO;
		strcpy(tempDocument04.REC_NO, asRecNo.c_str());
		//
		asKindCode = (char*)tempDocument04.KIND_CODE;
		strcpy(tempDocument04.KIND_CODE, asKindCode.c_str());
		//
		asPathName = (char*)tempDocument04.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument04.PATH_NAME, asPathName.c_str());
		//
		for(int i = 0; i < (int)frmMain->m_ResultDocument04.size(); i++)
		{
//230502//천안시 특조법//			if( !strcmp(tempDocument04.KIND_CODE, frmMain->m_ResultDocument04[i].KIND_CODE) )
			if( !strcmp(tempDocument04.LAW_NO, frmMain->m_ResultDocument04[i].LAW_NO)
			&& !strcmp(tempDocument04.KIND_CODE, frmMain->m_ResultDocument04[i].KIND_CODE)//230502//그룹핑기준 : LAW_NO//
			&& !strcmp(tempDocument04.REC_NO, frmMain->m_ResultDocument04[i].REC_NO) )//230502//그룹핑기준 : LAW_NO//
			{
				bSameData = true;
				break;
			}
			else if( !strcmp(tempDocument04.PATH_NAME, frmMain->m_ResultDocument04[i].PATH_NAME) )
			{
				bSameData = true;
				break;
			}
		}


		if( !bSameData )
		{
			nCount++;
			frmMain->m_ResultDocument04.insert(frmMain->m_ResultDocument04.begin() + (_nIndex + nCount), tempDocument04);
		}
		memset(&tempDocument04, 0x00, sizeof(DOCUMENT01_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;//230502//그룹핑기준 : LAW_NO//
}
//---------------------------------------------------------------------------


////230403//#ADD_FUNC_DOC04_44130//
//void __fastcall TfrmSql::funcSelReadDoc04Group(int _nIndex)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	AnsiString  asSqlQry  = "";
//	AnsiString  asColumn  = "";
//	AnsiString 	asWhere	  = "";
//	AnsiString  asOrderBy = "ROLL_NO, KWON_NO, OWN_NAME, KIND_CODE, REC_NO, PATH_NAME";
//	AnsiString 	asStr	  = "";
//	AnsiString  asPathName		= "";
//	bool		bSamePathName = false;
//	SQLINTEGER m_nVal[14];
//	SQLRETURN ret;
//	DOCUMENT04_STRUCT 				tempDocument04;
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
//	int nIndex = 1;
//
//	//asColumn  = "distinct ROLL_NO, KWON_NO, OWN_NAME, KIND_CODE, REC_NO, PATH_NAME";
//	asColumn  = "*";
//	//REC_NO 찾기//
//	asStr = (char*)frmMain->m_ResultDocument04[_nIndex].REC_NO;
//	asWhere = asWhere + " REC_NO LIKE '%/" + asStr + "/%'";
//
//	//[TODO]이건 고려할 필요가 있음//OWN_NAME 찾기//
//	/* TODO :
//천안 특조법 구축, 통합검색, 그룹쿼리, 소유자명 다수 시 처리방법 모호
//=> 관련하여 통합검색에서는 REC_NO만 그룹쿼리하는 것으로 진행 */
////	asStr = (char*)frmMain->m_ResultDocument04[_nIndex].OWN_NAME;
////	if( !asStr.IsEmpty() )
////		asWhere = asWhere + " OWN_NAME LIKE '%/" + asStr + "/%'";
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument04.ROLL_NO        , sizeof(tempDocument04.ROLL_NO)         	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PAGE_NO         , sizeof(tempDocument04.PAGE_NO)         	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.KWON_NO         , sizeof(tempDocument04.KWON_NO)			, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REQ_YEAR        , sizeof(tempDocument04.REQ_YEAR)        	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REQ_DAY         , sizeof(tempDocument04.REQ_DAY)         	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.OWN_NAME        , sizeof(tempDocument04.OWN_NAME)        	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.OWN_REG_NO      , sizeof(tempDocument04.OWN_REG_NO)      	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.ISSUE_NO        , sizeof(tempDocument04.ISSUE_NO)        	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.APROV_STATUS    , sizeof(tempDocument04.APROV_STATUS)    	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.LAW_NO          , sizeof(tempDocument04.LAW_NO)          	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.KIND_CODE       , sizeof(tempDocument04.KIND_CODE)      	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.REC_NO          , sizeof(tempDocument04.REC_NO)       	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PATH_NAME       , sizeof(tempDocument04.PATH_NAME)       	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument04.PNU             , sizeof(tempDocument04.PNU)       		, &m_nVal[nIndex-1]); nIndex++;
//
//	asSqlQry.sprintf("SELECT %s FROM TB_DOCUMENT04 WHERE %s ORDER BY %s", asColumn, asWhere, asOrderBy);
//	//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	memset(&tempDocument04, 0x00, sizeof(DOCUMENT04_STRUCT));
//	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
//	{
//		bSamePathName = false;
//		asPathName = (char*)tempDocument04.PATH_NAME;
//		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//		strcpy(tempDocument04.PATH_NAME, asPathName.c_str());
//
//		for(int i = 0; i < (int)frmMain->m_ResultDocument04.size(); i++)
//		{
//			if( !strcmp(tempDocument04.PATH_NAME, frmMain->m_ResultDocument04[i].PATH_NAME) )
//			{
//				bSamePathName = true;
//				break;
//			}
//		}
//		if( !bSamePathName )
//		{
//			frmMain->m_ResultDocument04.push_back(tempDocument04);
//		}
//		memset(&tempDocument04, 0x00, sizeof(DOCUMENT01_STRUCT));
//	};
//
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//}
////---------------------------------------------------------------------------


void __fastcall TfrmSql::funcReadDocument05(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName		 = "";
	bool		bSamePathName = false;
	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	DOCUMENT05_STRUCT 				tempDocument05;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument05, 0x00, sizeof(DOCUMENT05_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.ROLL_NO       , sizeof(tempDocument05.ROLL_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.FRAME_NO      , sizeof(tempDocument05.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.SR_NO         , sizeof(tempDocument05.SR_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.KIND_CODE      , sizeof(tempDocument05.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.KWON_NO        , sizeof(tempDocument05.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.PAGE_NO        , sizeof(tempDocument05.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.SUBMIT_YEAR    , sizeof(tempDocument05.SUBMIT_YEAR)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.PRCS_DATE      , sizeof(tempDocument05.PRCS_DATE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.MEASURE_TYPE   , sizeof(tempDocument05.MEASURE_TYPE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.GROUP_NO      , sizeof(tempDocument05.GROUP_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.GROUP_NO1     , sizeof(tempDocument05.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.BF_PNU   	  , sizeof(tempDocument05.BF_PNU)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.AF_PNU      	  , sizeof(tempDocument05.AF_PNU)      		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.PATH_NAME      , sizeof(tempDocument05.PATH_NAME)      	, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument05.clear();

	memset(&tempDocument05, 0x00, sizeof(DOCUMENT05_STRUCT));

	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument05.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument05.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument05.size(); i++)
		{
			if( !strcmp(tempDocument05.PATH_NAME, frmMain->m_ResultDocument05[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//200313//
			if(    !frmSearch->m_bKindDoc//상세검색//문서구분
				&& !strcmp(tempDocument05.PRCS_DATE, frmMain->m_ResultDocument05[i].PRCS_DATE)
				&& !strcmp(tempDocument05.MEASURE_TYPE, frmMain->m_ResultDocument05[i].MEASURE_TYPE)
				&& !strcmp(tempDocument05.KIND_CODE, frmMain->m_ResultDocument05[i].KIND_CODE))
			{
				bSamePathName = true;
				break;
			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument05.push_back(tempDocument05);
		memset(&tempDocument05, 0x00, sizeof(DOCUMENT05_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	int nCount = 0;
	for(int i = 0; i < (int)frmMain->m_ResultDocument05.size(); i++)
	{
		nCount = funcSelReadDoc05Group(i);
		i += nCount;
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSelReadDoc05Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[11];
	SQLRETURN ret;
	DOCUMENT05_STRUCT 				tempDocument05;

	AnsiString asSql  = "";
	AnsiString asSqlA = "";
	AnsiString asSqlB = "";
	AnsiString asSqlC = "";
	AnsiString asSqlD = "";
	AnsiString asSqlE = "";
	AnsiString asSqlF = "";
	AnsiString asCol = "";
	AnsiString asOrderBy = "";
	int nIndex = 1;
	int nCount = 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument05, 0x00, sizeof(DOCUMENT05_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.ROLL_NO   , sizeof(tempDocument05.ROLL_NO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.KWON_NO   	, sizeof(tempDocument05.KWON_NO)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.PAGE_NO   	, sizeof(tempDocument05.PAGE_NO)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.PRCS_DATE	, sizeof(tempDocument05.PRCS_DATE)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.GROUP_NO  , sizeof(tempDocument05.GROUP_NO)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument05.GROUP_NO1 , sizeof(tempDocument05.GROUP_NO1) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.KIND_CODE  , sizeof(tempDocument05.KIND_CODE) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.MEASURE_TYPE, sizeof(tempDocument05.MEASURE_TYPE) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.BF_PNU, sizeof(tempDocument05.BF_PNU) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.AF_PNU, sizeof(tempDocument05.AF_PNU) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument05.PATH_NAME  , sizeof(tempDocument05.PATH_NAME) , &m_nVal[nIndex-1]); nIndex++;

	asCol  = " ROLL_NO, KWON_NO, PAGE_NO, PRCS_DATE, GROUP_NO, GROUP_NO1, KIND_CODE, MEASURE_TYPE, BF_PNU, AF_PNU, PATH_NAME";
	AnsiString asTemp = (char*)frmMain->m_ResultDocument05[_nIndex].KWON_NO;
	asSqlA = " WHERE KWON_NO = '" + asTemp + "'";
	asSqlB = " AND GROUP_NO = " + IntToStr(frmMain->m_ResultDocument05[_nIndex].GROUP_NO);
	asSqlC = " AND GROUP_NO1 = " + IntToStr(frmMain->m_ResultDocument05[_nIndex].GROUP_NO1);
	asSqlD = " AND PRCS_DATE = '" + AnsiString(frmMain->m_ResultDocument05[_nIndex].PRCS_DATE) + "'";
	asSqlE = " AND MEASURE_TYPE = '" + AnsiString(frmMain->m_ResultDocument05[_nIndex].MEASURE_TYPE) + "'";
	asSqlF = " AND KIND_CODE <> '10' AND KIND_CODE <> '13' AND KIND_CODE <> '50'";
	//asOrderBy = " ORDER BY ROLL_NO, GROUP_NO, GROUP_NO1, PAGE_NO ASC";
	asOrderBy = " ORDER BY KWON_NO, GROUP_NO, GROUP_NO1, PAGE_NO ASC";

	asSql = "SELECT" + asCol + " FROM TB_DOCUMENT05" + asSqlA + asSqlB + asSqlC + asSqlD + asSqlE + asSqlF + asOrderBy;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}
	else {
		memset(&tempDocument05, 0x00, sizeof(DOCUMENT05_STRUCT));

		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			bSamePathName = false;
			asPathName = (char*)tempDocument05.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument05.PATH_NAME, asPathName.c_str());

			for(int i = 0; i < (int)frmMain->m_ResultDocument05.size(); i++)
			{
				if( !strcmp(tempDocument05.PATH_NAME, frmMain->m_ResultDocument05[i].PATH_NAME) )
				{
					bSamePathName = true;
					break;
				}
				//200313//
				if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
					&& !strcmp(tempDocument05.PRCS_DATE, frmMain->m_ResultDocument05[i].PRCS_DATE)
					&& !strcmp(tempDocument05.MEASURE_TYPE, frmMain->m_ResultDocument05[i].MEASURE_TYPE)
					&& !strcmp(tempDocument05.KIND_CODE, frmMain->m_ResultDocument05[i].KIND_CODE))
				{
					bSamePathName = true;
					break;
				}
			}
			if( !bSamePathName )
			{
				nCount++;
				frmMain->m_ResultDocument05.insert(frmMain->m_ResultDocument05.begin() + (_nIndex + nCount), tempDocument05);
			}
			memset(&tempDocument05, 0x00, sizeof(DOCUMENT05_STRUCT));
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument06(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

 	AnsiString  asPathName		 = "";
	bool		bSamePathName = false;
	SQLINTEGER m_nVal[10];
	SQLRETURN ret;
	DOCUMENT06_STRUCT 				tempDocument06;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument06, 0x00, sizeof(DOCUMENT06_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.KIND_CODE      , sizeof(tempDocument06.KIND_CODE)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.ZONE_CODE    , sizeof(tempDocument06.ZONE_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.COMP_YEAR    , sizeof(tempDocument06.COMP_YEAR)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.SERIAL_NUM   , sizeof(tempDocument06.SERIAL_NUM) 		, &m_nVal[nIndex-1]); nIndex++;
	//181231//SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.ROLL_NUM   , sizeof(tempDocument06.ROLL_NUM)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument06.ROLL_NO     , sizeof(tempDocument06.ROLL_NO)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.KWON_NO      , sizeof(tempDocument06.KWON_NO)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.PAGE_NO      , sizeof(tempDocument06.PAGE_NO)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.PATH_NAME    , sizeof(tempDocument06.PATH_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.BF_PNU       , sizeof(tempDocument06.BF_PNU)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.AF_PNU       , sizeof(tempDocument06.AF_PNU)     		, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument06.clear();

	memset(&tempDocument06, 0x00, sizeof(DOCUMENT06_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument06.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument06.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument06.size(); i++)
		{
			if( !strcmp(tempDocument06.PATH_NAME, frmMain->m_ResultDocument06[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201015//#ALLSEARCHLABEL
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument06.COMP_YEAR, frmMain->m_ResultDocument06[i].COMP_YEAR)
//				&& !strcmp(tempDocument06.ZONE_CODE, frmMain->m_ResultDocument06[i].ZONE_CODE)
//				&& !strcmp(tempDocument06.KIND_CODE, frmMain->m_ResultDocument06[i].KIND_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument06.push_back(tempDocument06);
		memset(&tempDocument06, 0x00, sizeof(DOCUMENT06_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	int nCount = 0;
	for(int i = 0; i < (int)frmMain->m_ResultDocument06.size(); i++)
	{
		nCount = funcSelReadDoc06Group(i);
		i += nCount;
    }
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSelReadDoc06Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[10];
	SQLRETURN ret;
	DOCUMENT06_STRUCT 				tempDocument06;

	AnsiString asSql  = "";
	AnsiString asSqlA = "";
	AnsiString asSqlB = "";
	AnsiString asSqlC = "";
	AnsiString asOrderBy = "";
	int nIndex = 1;
	int nCount = 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument06, 0x00, sizeof(DOCUMENT06_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.KIND_CODE   	, sizeof(tempDocument06.KIND_CODE)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.ZONE_CODE   	, sizeof(tempDocument06.ZONE_CODE)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.COMP_YEAR		, sizeof(tempDocument06.COMP_YEAR)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.SERIAL_NUM  	, sizeof(tempDocument06.SERIAL_NUM)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument06.ROLL_NO 		, sizeof(tempDocument06.ROLL_NO) 		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.KWON_NO 		, sizeof(tempDocument06.KWON_NO) 		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.PAGE_NO  		, sizeof(tempDocument06.PAGE_NO) 		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.PATH_NAME		, sizeof(tempDocument06.PATH_NAME) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.BF_PNU		, sizeof(tempDocument06.BF_PNU) 		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument06.AF_PNU		, sizeof(tempDocument06.AF_PNU) 		, &m_nVal[nIndex-1]); nIndex++;

	asSqlA = " WHERE ZONE_CODE = '" + AnsiString(frmMain->m_ResultDocument06[_nIndex].ZONE_CODE) + "'";
	asSqlB = " AND SERIAL_NUM = '" + AnsiString(frmMain->m_ResultDocument06[_nIndex].SERIAL_NUM) + "'";
	asSqlC = " AND COMP_YEAR = '" + AnsiString(frmMain->m_ResultDocument06[_nIndex].COMP_YEAR) + "'";
	asOrderBy = " ORDER BY COMP_YEAR, ZONE_CODE, SERIAL_NUM, ROLL_NO, VOL_NUM, PAGE_NO, BF_PNU, AF_PNU, PATH_NAME ASC";

	asSql = "SELECT * FROM TB_DOCUMENT06" + asSqlA + asSqlB + asSqlC + asOrderBy;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}
	else {
		memset(&tempDocument06, 0x00, sizeof(DOCUMENT06_STRUCT));

		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			bSamePathName = false;
			asPathName = (char*)tempDocument06.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument06.PATH_NAME, asPathName.c_str());

			for(int i = 0; i < (int)frmMain->m_ResultDocument06.size(); i++)
			{
				if( !strcmp(tempDocument06.PATH_NAME, frmMain->m_ResultDocument06[i].PATH_NAME) )
				{
					bSamePathName = true;
					break;
				}
				//201022//필터링 해제//
//				//200313//
//				if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//					&& !strcmp(tempDocument06.COMP_YEAR, frmMain->m_ResultDocument06[i].COMP_YEAR)
//					&& !strcmp(tempDocument06.ZONE_CODE, frmMain->m_ResultDocument06[i].ZONE_CODE)
//					&& !strcmp(tempDocument06.KIND_CODE, frmMain->m_ResultDocument06[i].KIND_CODE))
//				{
//					bSamePathName = true;
//					break;
//				}
			}
			if( !bSamePathName )
			{
				nCount++;
				frmMain->m_ResultDocument06.insert(frmMain->m_ResultDocument06.begin() + (_nIndex + nCount), tempDocument06);
			}
			memset(&tempDocument06, 0x00, sizeof(DOCUMENT06_STRUCT));
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------

//void __fastcall TfrmSql::funcReadDocument07(AnsiString qry)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	AnsiString  asPathName  = "";
//	SQLRETURN ret;
//	SQLINTEGER m_nVal[24];
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&frmMain->tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
//	int nIndex = 1;
//
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.PATH_NAME, 		sizeof(frmMain->tempDocument07.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.KIND_CODE, 		sizeof(frmMain->tempDocument07.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&frmMain->tempDocument07.ROLL_NO, 		sizeof(frmMain->tempDocument07.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&frmMain->tempDocument07.FRAME_NO, 		sizeof(frmMain->tempDocument07.FRAME_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.KWON_NO, 		sizeof(frmMain->tempDocument07.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.PAGE_NO, 		sizeof(frmMain->tempDocument07.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.LAND_GBN, 		sizeof(frmMain->tempDocument07.LAND_GBN), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.SIDOSGG, 		sizeof(frmMain->tempDocument07.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.UMD, 			sizeof(frmMain->tempDocument07.UMD), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.RI, 				sizeof(frmMain->tempDocument07.RI), 				&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.SCALE, 			sizeof(frmMain->tempDocument07.SCALE), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.DOHO_BON, 		sizeof(frmMain->tempDocument07.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07.DOHO_BU, 		sizeof(frmMain->tempDocument07.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.X1, 			sizeof(frmMain->tempDocument07.X1), 				&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.Y1, 			sizeof(frmMain->tempDocument07.Y1), 				&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.X2, 			sizeof(frmMain->tempDocument07.X2), 				&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.Y2, 			sizeof(frmMain->tempDocument07.Y2), 				&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.SIZE_X, 		sizeof(frmMain->tempDocument07.SIZE_X), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.SIZE_Y, 		sizeof(frmMain->tempDocument07.SIZE_Y), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.BASE_X, 		sizeof(frmMain->tempDocument07.BASE_X), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.BASE_Y, 		sizeof(frmMain->tempDocument07.BASE_Y), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.RATIOX, 		sizeof(frmMain->tempDocument07.RATIOX), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&frmMain->tempDocument07.RATIOY, 		sizeof(frmMain->tempDocument07.RATIOY), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&frmMain->tempDocument07.REMARK, 		sizeof(frmMain->tempDocument07.REMARK), 			&m_nVal[nIndex-1]); nIndex++;
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	//191104//in funcClearResultVector()//frmMain->m_ResultDocument07.clear();
//
//	memset(&frmMain->tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
//	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
//		asPathName = (char*)frmMain->tempDocument07.PATH_NAME;
//		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//		strcpy(frmMain->tempDocument07.PATH_NAME, asPathName.c_str());
//
//		bool bSamed	= false;
//		for(int i = 0; i < (int)frmMain->m_ResultDocument07.size(); i++)
//		{
//			//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
//			if( !strcmp(frmMain->m_ResultDocument07[i].PATH_NAME, frmMain->tempDocument07.PATH_NAME) )
//			{
//				bSamed = true;
//				break;
//			}
//		}
//		if( !bSamed )
//		{
//			frmMain->m_ResultDocument07.push_back(frmMain->tempDocument07);
//			memset(&frmMain->tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
//		}
//	};
//
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//}
////---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument07(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName  = "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[19];
	DOCUMENT07_STRUCT 				tempDocument07;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDocument07.ROLL_NO, 		sizeof(tempDocument07.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.KWON_NO, 		sizeof(tempDocument07.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.KIND_CODE, 		sizeof(tempDocument07.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.SIDOSGG, 		sizeof(tempDocument07.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.UMD, 			sizeof(tempDocument07.UMD), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.RI, 				sizeof(tempDocument07.RI), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.SCALE, 			sizeof(tempDocument07.SCALE), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.DOHO_BON, 		sizeof(tempDocument07.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.X1, 			sizeof(tempDocument07.X1), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.Y1, 			sizeof(tempDocument07.Y1), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.X2, 			sizeof(tempDocument07.X2), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.Y2, 			sizeof(tempDocument07.Y2), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.SIZE_X, 		sizeof(tempDocument07.SIZE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.SIZE_Y, 		sizeof(tempDocument07.SIZE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.BASE_X, 		sizeof(tempDocument07.BASE_X), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.BASE_Y, 		sizeof(tempDocument07.BASE_Y), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.RATIOX, 		sizeof(tempDocument07.RATIOX), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDocument07.RATIOY, 		sizeof(tempDocument07.RATIOY), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDocument07.PATH_NAME, 		sizeof(tempDocument07.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument07.clear();

	//200925//일반,산구분하여 문서구분 필터링//
	AnsiString  asStr	= "";
	int			nLandGbn	= 0;//일반(true), 산(false)
	if(frmMain->m_asSearchPnu.Length() == 19)//일반/산 구분//문서 필터링//
	{
		if(frmMain->m_asSearchPnu.SubString(11, 1) == "2")
			nLandGbn = 2;//산지번//
		else if(frmMain->m_asSearchPnu.SubString(11, 1) == "1")
			nLandGbn = 1;//일반지번//
	}

	memset(&tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		asPathName = (char*)tempDocument07.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument07.PATH_NAME, asPathName.c_str());

		bool bSamed	= false;
		for(int i = 0; i < (int)frmMain->m_ResultDocument07.size(); i++)
		{
			//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
			if( !strcmp(frmMain->m_ResultDocument07[i].PATH_NAME, tempDocument07.PATH_NAME) )
			{
				bSamed = true;
				break;
			}
		}

		//200925//일반,산구분하여 문서구분 필터링//
		asStr = eFunc->funcGetKindCodeToKindName(7, (char*)tempDocument07.KIND_CODE);
		if(nLandGbn == 1 && asStr.Pos("임야") > 0)//일반//
		{
			continue;
		}
		else if(nLandGbn == 2 && asStr.Pos("임야") == 0)//산//
		{
			continue;
		}

		if( !bSamed )
		{
			frmMain->m_ResultDocument07.push_back(tempDocument07);
			memset(&tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
		}
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//void __fastcall TfrmSql::funcSelReadDoc07Doho(DOCUMENT07_STRUCT mSelDohoDoc7)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	int nStartIndex = 0;
//
//	SQLINTEGER m_nVal[15];
//	SQLRETURN ret;
//
//	AnsiString asSql  		= "";
//	AnsiString asTbl 		= "TB_DOCUMENT07";
//	AnsiString asWhere 		= "";
//	AnsiString asOrderBy 	= "";
//	int nIndex = 1;
//	DOCUMENT07_STRUCT	tempDoc07Doho;
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempDoc07Doho, 0x00, sizeof(DOCUMENT07_STRUCT));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.ROLL_NO     , sizeof(tempDoc07Doho.ROLL_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.FRAME_NO    , sizeof(tempDoc07Doho.FRAME_NO)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.SR_NO       , sizeof(tempDoc07Doho.SR_NO)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.KIND_CODE    , sizeof(tempDoc07Doho.KIND_CODE)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.KIND_NAME    , sizeof(tempDoc07Doho.KIND_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.HJDON_NAME   , sizeof(tempDoc07Doho.HJDON_NAME)   , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.POS_X       , sizeof(tempDoc07Doho.POS_X)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.POS_Y       , sizeof(tempDoc07Doho.POS_Y)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.KWON_NO      , sizeof(tempDoc07Doho.KWON_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.PAGE_NO      , sizeof(tempDoc07Doho.PAGE_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.DOHO         , sizeof(tempDoc07Doho.DOHO)         , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.DOHO_SUB     , sizeof(tempDoc07Doho.DOHO_SUB)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.SCALE        , sizeof(tempDoc07Doho.SCALE)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.PNU    	   , sizeof(tempDoc07Doho.PNU)    	    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.PATH_NAME    , sizeof(tempDoc07Doho.PATH_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//
//	AnsiString asTemp = (char*)mSelDohoDoc7.KWON_NO;
//	asWhere = asWhere + "KWON_NO = '" + asTemp + "'";
//	//191010//검색된 도호의 권번호가 같은 일람도&색인표 검색//
//	asWhere = asWhere + " AND (KIND_CODE = '08' OR KIND_CODE = '09')";
////	asWhere = asWhere + " AND FRAME_NO = " + IntToStr(mSelDohoDoc7.FRAME_NO);
////	asWhere = asWhere + " AND KIND_CODE = '" + AnsiString(mSelDohoDoc7.KIND_CODE) + "'";
////	asWhere = asWhere + " AND DOHO = '" + AnsiString(mSelDohoDoc7.DOHO) + "'";
////	asWhere = asWhere + " AND DOHO_SUB = '" + AnsiString(mSelDohoDoc7.DOHO_SUB) + "'";
//
//	//asOrderBy = "ROLL_NO, FRAME_NO, PATH_NAME, PNU ASC";
//	asOrderBy = "KWON_NO, FRAME_NO, PATH_NAME, PNU ASC";
//
//	asSql.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", asTbl, asWhere, asOrderBy);
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//	else {
//		memset(&tempDoc07Doho, 0x00, sizeof(DOCUMENT07_STRUCT));
//
//		nStartIndex = m_ResultDocument07Doho.size();
//
//		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
//		{
//			frmMain->m_ResultDocument07Doho.push_back(tempDoc07Doho);
//			memset(&tempDoc07Doho, 0x00, sizeof(DOCUMENT07_STRUCT));
//		};
//		if(m_hStmt) SQLCloseCursor(m_hStmt);
//	}
//
//	if (frmMain->m_ResultDocument07Doho.size() != 0 )
//		frmMain->m_ResultDocument07Doho[frmMain->m_ResultDocument07Doho.size()-1].nDohoBuffIndex = nStartIndex;
//
//	frmMain->totalCount[7] = frmMain->m_ResultDocument07Doho.size();
//	frmSearch->funcSaveLog(0, 0, "");//first
//	frmSearch->funcSaveLog(1, 1, asSql);//query
//	frmSearch->funcSaveLog(3, 0, "");//save to file
//}
////---------------------------------------------------------------------------
////190617//MapPoint 검색에서 일람도/색인표(도호번호 없음) 검색을 위한 그룹query
//void __fastcall TfrmSql::funcSelReadDoc07Etc(DOCUMENT07_STRUCT mSelDohoDoc7)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	int nStartIndex = 0;
//
//	SQLINTEGER m_nVal[15];
//	SQLRETURN ret;
//
//	AnsiString asSql  		= "";
//	AnsiString asTbl 		= "TB_DOCUMENT07";
//	AnsiString asWhere 		= "";
//	AnsiString asOrderBy 	= "";
//	AnsiString asPnu	 	= mSelDohoDoc7.PNU;
//	AnsiString asScale	 	= mSelDohoDoc7.SCALE;
//	AnsiString asPathName 	= mSelDohoDoc7.PATH_NAME;
//	int nIndex = 1;
//	DOCUMENT07_STRUCT	tempDoc07Doho;
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempDoc07Doho, 0x00, sizeof(DOCUMENT07_STRUCT));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.ROLL_NO     , sizeof(tempDoc07Doho.ROLL_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.FRAME_NO    , sizeof(tempDoc07Doho.FRAME_NO)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.SR_NO       , sizeof(tempDoc07Doho.SR_NO)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.KIND_CODE    , sizeof(tempDoc07Doho.KIND_CODE)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.KIND_NAME    , sizeof(tempDoc07Doho.KIND_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.HJDON_NAME   , sizeof(tempDoc07Doho.HJDON_NAME)   , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.POS_X       , sizeof(tempDoc07Doho.POS_X)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc07Doho.POS_Y       , sizeof(tempDoc07Doho.POS_Y)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.KWON_NO      , sizeof(tempDoc07Doho.KWON_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.PAGE_NO      , sizeof(tempDoc07Doho.PAGE_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.DOHO         , sizeof(tempDoc07Doho.DOHO)         , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.DOHO_SUB     , sizeof(tempDoc07Doho.DOHO_SUB)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.SCALE        , sizeof(tempDoc07Doho.SCALE)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.PNU    	   , sizeof(tempDoc07Doho.PNU)    	    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc07Doho.PATH_NAME    , sizeof(tempDoc07Doho.PATH_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//
//	asPathName = ExtractFilePath(asPathName);
//
//	AnsiString asTemp = (char*)mSelDohoDoc7.KWON_NO;
//	asWhere = asWhere + "KWON_NO = '" + asTemp + "'";
//	if(asPnu.Length() >= 10)
//		asWhere = asWhere + " AND PNU LIKE '" + asPnu.SubString(1, 10) + "%'";
//	asWhere = asWhere + " AND (KIND_CODE = '" + frmFuncUnit->funcGetKindCode("007", "일람도") + "' OR KIND_CODE = '" + frmFuncUnit->funcGetKindCode("007", "색인표") + "')";
//	asWhere = asWhere + " AND DOHO = '0'";
//	asWhere = asWhere + " AND SCALE = '" + asScale + "'";
//	asWhere = asWhere + " AND PATH_NAME LIKE '" + asPathName + "%'";
//
//	//asOrderBy = "ROLL_NO, FRAME_NO, PATH_NAME, PNU ASC";
//	asOrderBy = "KWON_NO, FRAME_NO, PATH_NAME, PNU ASC";
//
//	asSql.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", asTbl, asWhere, asOrderBy);
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//	else {
//		memset(&tempDoc07Doho, 0x00, sizeof(DOCUMENT07_STRUCT));
//
//		nStartIndex = m_ResultDocument07Doho.size();
//
//		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
//		{
//			m_ResultDocument07Doho.push_back(tempDoc07Doho);
//			m_ResultDocument07Doho[m_ResultDocument07Doho.size()-1].nDohoBuffIndex = nStartIndex;
//
//			memset(&tempDoc07Doho, 0x00, sizeof(DOCUMENT07_STRUCT));
//		};
//		if(m_hStmt) SQLCloseCursor(m_hStmt);
//	}
//
////	if (m_ResultDocument07Doho.size() != 0 )
//
//	frmMain->totalCount[7] = frmSqlControl->m_ResultDocument07Doho.size();
//	frmSearch->funcSaveLog(0, 0, "");//first
//	frmSearch->funcSaveLog(1, 1, asSql);//query
//	frmSearch->funcSaveLog(3, 0, "");//save to file
//}
////---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument08(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName		 = "";
	AnsiString  asPathNameColor  = "";
	bool		bSamePathName = false;
	SQLRETURN ret;
	AnsiString temp, result;
	DOCUMENT08_STRUCT 				tempDocument08;

	if(frmMain->INI_B_JUMINHIDE && frmMain->INI_B_OWNNAMES)//#JUMINHIDE#//#OWNNAMES#
	{
		SQLINTEGER m_nVal[17];

		memset(m_nVal, 0x00, sizeof(m_nVal));
		memset(&tempDocument08, 0x00, sizeof(DOCUMENT08_STRUCT));
		int nIndex = 1;

		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.ROLL_NO    	, sizeof(tempDocument08.ROLL_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.FRAME_NO   	, sizeof(tempDocument08.FRAME_NO)    		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.SR_NO      	, sizeof(tempDocument08.SR_NO)       		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_CODE  	, sizeof(tempDocument08.SINGU_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KIND_CODE   	, sizeof(tempDocument08.KIND_CODE)   		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KWON_NO     	, sizeof(tempDocument08.KWON_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PAGE_NO     	, sizeof(tempDocument08.PAGE_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_NAME  	, sizeof(tempDocument08.BUILD_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_HOSU  	, sizeof(tempDocument08.BUILD_HOSU)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.ONOFF_CODE  	, sizeof(tempDocument08.ONOFF_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_NAME  	, sizeof(tempDocument08.SINGU_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PNU 		   	, sizeof(tempDocument08.PNU) 				, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME   	, sizeof(tempDocument08.PATH_NAME) 			, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME_COLOR , sizeof(tempDocument08.PATH_NAME_COLOR) 	, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.JUMIN_YN   		, sizeof(tempDocument08.JUMIN_YN) 			, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.JUMIN_XY	   	, sizeof(tempDocument08.JUMIN_XY) 			, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.OWN_NAMES   	, sizeof(tempDocument08.OWN_NAMES) 			, &m_nVal[nIndex-1]); nIndex++;
	}
	else if(frmMain->INI_B_JUMINHIDE && !frmMain->INI_B_OWNNAMES)//#JUMINHIDE#
	{
		SQLINTEGER m_nVal[16];

		memset(m_nVal, 0x00, sizeof(m_nVal));
		memset(&tempDocument08, 0x00, sizeof(DOCUMENT08_STRUCT));
		int nIndex = 1;

		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.ROLL_NO    	, sizeof(tempDocument08.ROLL_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.FRAME_NO   	, sizeof(tempDocument08.FRAME_NO)    		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.SR_NO      	, sizeof(tempDocument08.SR_NO)       		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_CODE  	, sizeof(tempDocument08.SINGU_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KIND_CODE   	, sizeof(tempDocument08.KIND_CODE)   		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KWON_NO     	, sizeof(tempDocument08.KWON_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PAGE_NO     	, sizeof(tempDocument08.PAGE_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_NAME  	, sizeof(tempDocument08.BUILD_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_HOSU  	, sizeof(tempDocument08.BUILD_HOSU)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.ONOFF_CODE  	, sizeof(tempDocument08.ONOFF_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_NAME  	, sizeof(tempDocument08.SINGU_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PNU 		   	, sizeof(tempDocument08.PNU) 				, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME   	, sizeof(tempDocument08.PATH_NAME) 			, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME_COLOR , sizeof(tempDocument08.PATH_NAME_COLOR) 	, &m_nVal[nIndex-1]); nIndex++;
	}
	else if(!frmMain->INI_B_JUMINHIDE && frmMain->INI_B_OWNNAMES)//#OWNNAMES#
	{
		SQLINTEGER m_nVal[15];

		memset(m_nVal, 0x00, sizeof(m_nVal));
		memset(&tempDocument08, 0x00, sizeof(DOCUMENT08_STRUCT));
		int nIndex = 1;

		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.ROLL_NO    	, sizeof(tempDocument08.ROLL_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.FRAME_NO   	, sizeof(tempDocument08.FRAME_NO)    		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.SR_NO      	, sizeof(tempDocument08.SR_NO)       		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_CODE  	, sizeof(tempDocument08.SINGU_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KIND_CODE   	, sizeof(tempDocument08.KIND_CODE)   		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KWON_NO     	, sizeof(tempDocument08.KWON_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PAGE_NO     	, sizeof(tempDocument08.PAGE_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_NAME  	, sizeof(tempDocument08.BUILD_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_HOSU  	, sizeof(tempDocument08.BUILD_HOSU)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.ONOFF_CODE  	, sizeof(tempDocument08.ONOFF_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_NAME  	, sizeof(tempDocument08.SINGU_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PNU 		   	, sizeof(tempDocument08.PNU) 				, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME   	, sizeof(tempDocument08.PATH_NAME) 			, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME_COLOR , sizeof(tempDocument08.PATH_NAME_COLOR) 	, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.OWN_NAMES   	, sizeof(tempDocument08.OWN_NAMES) 			, &m_nVal[nIndex-1]); nIndex++;
	}
	else
	{
		SQLINTEGER m_nVal[14];

		memset(m_nVal, 0x00, sizeof(m_nVal));
		memset(&tempDocument08, 0x00, sizeof(DOCUMENT08_STRUCT));
		int nIndex = 1;

		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.ROLL_NO    	, sizeof(tempDocument08.ROLL_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.FRAME_NO   	, sizeof(tempDocument08.FRAME_NO)    		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08.SR_NO      	, sizeof(tempDocument08.SR_NO)       		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_CODE  	, sizeof(tempDocument08.SINGU_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KIND_CODE   	, sizeof(tempDocument08.KIND_CODE)   		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.KWON_NO     	, sizeof(tempDocument08.KWON_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PAGE_NO     	, sizeof(tempDocument08.PAGE_NO)     		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_NAME  	, sizeof(tempDocument08.BUILD_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.BUILD_HOSU  	, sizeof(tempDocument08.BUILD_HOSU)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.ONOFF_CODE  	, sizeof(tempDocument08.ONOFF_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.SINGU_NAME  	, sizeof(tempDocument08.SINGU_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PNU 		   	, sizeof(tempDocument08.PNU) 				, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME   	, sizeof(tempDocument08.PATH_NAME) 			, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08.PATH_NAME_COLOR , sizeof(tempDocument08.PATH_NAME_COLOR) 	, &m_nVal[nIndex-1]); nIndex++;
	}

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument08.clear();

	memset(&tempDocument08, 0x00, sizeof(DOCUMENT08_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;

		if( strcmp((char*)tempDocument08.PATH_NAME, "") != 0)//231206//
		{
			asPathName = (char*)tempDocument08.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument08.PATH_NAME, asPathName.c_str());
		}

		if( strcmp((char*)tempDocument08.PATH_NAME_COLOR, "") != 0)//231206//
		{
			asPathNameColor = (char*)tempDocument08.PATH_NAME_COLOR;
			asPathNameColor = StringReplace(asPathNameColor, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument08.PATH_NAME_COLOR, asPathNameColor.c_str());
		}

		for(int i = 0; i < (int)frmMain->m_ResultDocument08.size(); i++)
		{
			if( !strcmp(tempDocument08.PATH_NAME, frmMain->m_ResultDocument08[i].PATH_NAME)
			 && !strcmp(tempDocument08.PATH_NAME_COLOR, frmMain->m_ResultDocument08[i].PATH_NAME_COLOR) )
			{
				bSamePathName = true;
				break;
			}

			//201015//#ALLSEARCHLABEL
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument08.SINGU_NAME, frmMain->m_ResultDocument08[i].SINGU_NAME)
//				&& !strcmp(tempDocument08.KIND_CODE, frmMain->m_ResultDocument08[i].KIND_CODE)
//				&& !strcmp(tempDocument08.ONOFF_CODE, frmMain->m_ResultDocument08[i].ONOFF_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument08.push_back(tempDocument08);
		memset(&tempDocument08, 0x00, sizeof(DOCUMENT08_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument09(char *cQry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName		 = "";
	bool		bSamePathName = false;
	SQLINTEGER m_nVal[8];
	SQLRETURN ret;
	DOCUMENT09_STRUCT 				tempDocument09;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument09, 0x00, sizeof(DOCUMENT09_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument09.ROLL_NO    	, sizeof(tempDocument09.ROLL_NO)	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.KIND_CODE  		, sizeof(tempDocument09.KIND_CODE)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.BASE_YEAR    	, sizeof(tempDocument09.BASE_YEAR)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.BASE_MON     	, sizeof(tempDocument09.BASE_MON)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.KWON_NO      	, sizeof(tempDocument09.KWON_NO)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.PAGE_NO   		, sizeof(tempDocument09.PAGE_NO)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.PNU   			, sizeof(tempDocument09.PNU)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument09.PATH_NAME    	, sizeof(tempDocument09.PATH_NAME)  , &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)cQry,SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument09.clear();

	memset(&tempDocument09, 0x00, sizeof(DOCUMENT09_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument09.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument09.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument09.size(); i++)
		{
			if( !strcmp(tempDocument09.PATH_NAME, frmMain->m_ResultDocument09[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201022//필터링 해제//
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument09.BASE_YEAR, frmMain->m_ResultDocument09[i].BASE_YEAR)
//				&& !strcmp(tempDocument09.BASE_MON, frmMain->m_ResultDocument09[i].BASE_MON)
//				&& !strcmp(tempDocument09.KIND_CODE, frmMain->m_ResultDocument09[i].KIND_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument09.push_back(tempDocument09);
		memset(&tempDocument09, 0x00, sizeof(DOCUMENT09_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::func_readRoadNameList(AnsiString qry)
{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	SQLCHAR m_cVal[7][255];
//	SQLINTEGER m_nVal[7];
//	AnsiString mSqlQry;
//	SQLRETURN ret;
//	AnsiString result[7];
//	char min_cValue[255];
//
//	for(int i=0; i<7; i++){
//		SQLBindCol(m_hStmt, i+1, SQL_C_CHAR, m_cVal[i], sizeof(m_cVal[i]), &m_nVal[i]);
//	}
//
//	mSqlQry = qry;
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	int size = m_vDATA_TEMPROADADDRESS.size();
//
//	AnsiString doc_num = "";
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//
//		SQLCloseCursor(m_hStmt);
//	}
//	else{
//		m_vDATA_ROADADDRESSRESULT.clear();
//
//		for(int i=0; i<7; i++){
//			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
//			result[i] = "";
//		}
//		doc_num = "";
//		int index = 0;
//		while(SQLFetch(m_hStmt)!=SQL_NO_DATA){
//			for(int i=0; i<7; i++){
//				memset(min_cValue, 0x00, sizeof(min_cValue));
//				memcpy(min_cValue, m_cVal[i], sizeof( min_cValue));
//				result[i] = min_cValue;
//			}
//
//			tempROADADDRESS.id         = result[0].ToInt();
//			tempROADADDRESS.DOC_NUM    = result[1];
//			tempROADADDRESS.KIND_CODE    = result[2];
//			tempROADADDRESS.GUBUN      = result[3];
//			tempROADADDRESS.PAGE_NUM   = result[4];
//			tempROADADDRESS.ROAD_NAME  = result[5];
//			tempROADADDRESS.IMG_FOLDER = result[6];
//			doc_num                    = tempROADADDRESS.DOC_NUM;
//
//			if(size > 0){
//				for(int i=index; i<size; i++){
//					if(doc_num == m_vDATA_TEMPROADADDRESS[i].DOC_NUM){
//						m_vDATA_ROADADDRESSRESULT.push_back(m_vDATA_TEMPROADADDRESS[i]);
//						index++;
//					}
//				}
//			}
//			m_vDATA_ROADADDRESSRESULT.push_back(tempROADADDRESS);
//
//			for(int i=0; i<7; i++){
//				memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
//				result[i] = "";
//			}
//		};
//		if(m_hStmt) SQLCloseCursor(m_hStmt);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument11(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[8];
	SQLRETURN ret;
	AnsiString temp, result;
	DOCUMENT11_STRUCT 				tempDocument11;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument11, 0x00, sizeof(DOCUMENT11_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument11.ROLL_NO    , sizeof(tempDocument11.ROLL_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument11.FRAME_NO   , sizeof(tempDocument11.FRAME_NO)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument11.SR_NO      , sizeof(tempDocument11.SR_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument11.KIND_CODE   , sizeof(tempDocument11.KIND_CODE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument11.KWON_NO     , sizeof(tempDocument11.KWON_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument11.PAGE_NO     , sizeof(tempDocument11.PAGE_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument11.PNU 		, sizeof(tempDocument11.PNU) 		 , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument11.PATH_NAME   , sizeof(tempDocument11.PATH_NAME) 	 , &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument11.clear();

	memset(&tempDocument11, 0x00, sizeof(DOCUMENT11_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument11.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument11.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument11.size(); i++)
		{
			if( !strcmp(tempDocument11.PATH_NAME, frmMain->m_ResultDocument11[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201022//필터링 해제//
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument11.KWON_NO, frmMain->m_ResultDocument11[i].KWON_NO)
//				&& !strcmp(tempDocument11.KIND_CODE, frmMain->m_ResultDocument11[i].KIND_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument11.push_back(tempDocument11);
		memset(&tempDocument11, 0x00, sizeof(DOCUMENT11_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument12(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[12];
	SQLRETURN ret;
	DOCUMENT12_STRUCT 				tempDocument12;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument12, 0x00, sizeof(DOCUMENT12_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument12.ROLL_NO      , sizeof(tempDocument12.ROLL_NO)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.PAGE_NO       , sizeof(tempDocument12.PAGE_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.KWON_NO       , sizeof(tempDocument12.KWON_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.REQ_YEAR      , sizeof(tempDocument12.REQ_YEAR)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.REQ_DAY       , sizeof(tempDocument12.REQ_DAY)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.OWN_NAME      , sizeof(tempDocument12.OWN_NAME)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.OWN_REG_NO    , sizeof(tempDocument12.OWN_REG_NO)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.ISSUE_NO      , sizeof(tempDocument12.ISSUE_NO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.APROV_STATUS  , sizeof(tempDocument12.APROV_STATUS) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.KIND_CODE     , sizeof(tempDocument12.KIND_CODE)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.PATH_NAME     , sizeof(tempDocument12.PATH_NAME)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument12.PNU   	      , sizeof(tempDocument12.PNU)   		, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument12.clear();

	memset(&tempDocument12, 0x00, sizeof(DOCUMENT12_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument12.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument12.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument12.size(); i++)
		{
			if( !strcmp(tempDocument12.PATH_NAME, frmMain->m_ResultDocument12[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201022//필터링 해제//
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument12.REQ_DAY, frmMain->m_ResultDocument12[i].REQ_DAY)
//				&& !strcmp(tempDocument12.KIND_CODE, frmMain->m_ResultDocument12[i].KIND_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument12.push_back(tempDocument12);
		memset(&tempDocument12, 0x00, sizeof(DOCUMENT12_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument13(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[9];
	SQLRETURN ret;
	DOCUMENT13_STRUCT 				tempDocument13;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument13, 0x00, sizeof(DOCUMENT13_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument13.ROLL_NO		, sizeof(tempDocument13.ROLL_NO)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.PAGE_NO      	, sizeof(tempDocument13.PAGE_NO)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.KWON_NO      	, sizeof(tempDocument13.KWON_NO)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.REQ_YEAR     	, sizeof(tempDocument13.REQ_YEAR)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.REQ_DAY      	, sizeof(tempDocument13.REQ_DAY)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.OWN_NAME     	, sizeof(tempDocument13.OWN_NAME)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.OWN_REG_NO   	, sizeof(tempDocument13.OWN_REG_NO) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.KIND_CODE       , sizeof(tempDocument13.KIND_CODE)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument13.PATH_NAME    	, sizeof(tempDocument13.PATH_NAME)  	, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument13.clear();

	memset(&tempDocument13, 0x00, sizeof(DOCUMENT13_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument13.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument13.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument13.size(); i++)
		{
			if( !strcmp(tempDocument13.PATH_NAME, frmMain->m_ResultDocument13[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201022//필터링 해제//
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument13.REQ_DAY, frmMain->m_ResultDocument13[i].REQ_DAY)
//				&& !strcmp(tempDocument13.KIND_CODE, frmMain->m_ResultDocument13[i].KIND_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument13.push_back(tempDocument13);
		memset(&tempDocument13, 0x00, sizeof(DOCUMENT13_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument14(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[13];
	SQLRETURN ret;
	DOCUMENT14_STRUCT 				tempDocument14;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument14, 0x00, sizeof(DOCUMENT14_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.ROLL_NO      , sizeof(tempDocument14.ROLL_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.FRAME_NO     , sizeof(tempDocument14.FRAME_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.SR_NO        , sizeof(tempDocument14.SR_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.KIND_CODE     , sizeof(tempDocument14.KIND_CODE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.KWON_NO       , sizeof(tempDocument14.KWON_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PAGE_NO       , sizeof(tempDocument14.PAGE_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.SUBMIT_YEAR   , sizeof(tempDocument14.SUBMIT_YEAR)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PRCS_DATE     , sizeof(tempDocument14.PRCS_DATE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.MEASURE_TYPE  , sizeof(tempDocument14.MEASURE_TYPE)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.GROUP_NO     , sizeof(tempDocument14.GROUP_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.GROUP_NO1    , sizeof(tempDocument14.GROUP_NO1)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PNU   	 	  , sizeof(tempDocument14.PNU)           , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PATH_NAME     , sizeof(tempDocument14.PATH_NAME)     , &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument14.clear();

	memset(&tempDocument14, 0x00, sizeof(DOCUMENT14_STRUCT));

	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument14.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument14.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument14.size(); i++)
		{
			if( !strcmp(tempDocument14.PATH_NAME, frmMain->m_ResultDocument14[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201022//필터링 해제//
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument14.PRCS_DATE, frmMain->m_ResultDocument14[i].PRCS_DATE)
//				&& !strcmp(tempDocument14.MEASURE_TYPE, frmMain->m_ResultDocument14[i].MEASURE_TYPE)
//				&& !strcmp(tempDocument14.KIND_CODE, frmMain->m_ResultDocument14[i].KIND_CODE))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument14.push_back(tempDocument14);
		memset(&tempDocument14, 0x00, sizeof(DOCUMENT14_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	int nCount = 0;
	for(int i = 0; i < (int)frmMain->m_ResultDocument14.size(); i++)
	{
		nCount = funcSelReadDoc14Group(i);
		i += nCount;
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSelReadDoc14Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[13];
	SQLRETURN ret;
	DOCUMENT14_STRUCT 				tempDocument14;

	AnsiString asSql  = "";
	AnsiString asSqlA = "";
	AnsiString asSqlB = "";
	AnsiString asSqlC = "";
	AnsiString asSqlD = "";
	AnsiString asSqlE = "";
	AnsiString asSqlF = "";
	AnsiString asCol = "";
	AnsiString asOrderBy = "";
	int nIndex = 1;
	int nCount = 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument14, 0x00, sizeof(DOCUMENT14_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.ROLL_NO      , sizeof(tempDocument14.ROLL_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.FRAME_NO     , sizeof(tempDocument14.FRAME_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.SR_NO        , sizeof(tempDocument14.SR_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.KIND_CODE     , sizeof(tempDocument14.KIND_CODE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.KWON_NO       , sizeof(tempDocument14.KWON_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PAGE_NO       , sizeof(tempDocument14.PAGE_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.SUBMIT_YEAR   , sizeof(tempDocument14.SUBMIT_YEAR)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PRCS_DATE     , sizeof(tempDocument14.PRCS_DATE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.MEASURE_TYPE  , sizeof(tempDocument14.MEASURE_TYPE)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.GROUP_NO     , sizeof(tempDocument14.GROUP_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument14.GROUP_NO1    , sizeof(tempDocument14.GROUP_NO1)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PNU   	 	  , sizeof(tempDocument14.PNU)           , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument14.PATH_NAME     , sizeof(tempDocument14.PATH_NAME)     , &m_nVal[nIndex-1]); nIndex++;

	//asCol  = " ROLL_NO, PAGE_NO, GROUP_NO, GROUP_NO1, KIND_CODE, PATH_NAME";
	//asCol  = " KWON_NO, PAGE_NO, GROUP_NO, GROUP_NO1, KIND_CODE, PATH_NAME";
	AnsiString asTemp = (char*)frmMain->m_ResultDocument14[_nIndex].KWON_NO;
	asSqlA = " WHERE KWON_NO = '" + asTemp + "'";
	asSqlB = " AND GROUP_NO = " + IntToStr(frmMain->m_ResultDocument14[_nIndex].GROUP_NO);
	asSqlC = " AND GROUP_NO1 = " + IntToStr(frmMain->m_ResultDocument14[_nIndex].GROUP_NO1);
	asSqlD = " AND KIND_CODE <> '10' AND KIND_CODE <> '13' AND KIND_CODE <> '50'";
	asSqlE = " AND PRCS_DATE = '" + AnsiString(frmMain->m_ResultDocument14[_nIndex].PRCS_DATE) + "'";
	asSqlF = " AND MEASURE_TYPE = '" + AnsiString(frmMain->m_ResultDocument14[_nIndex].MEASURE_TYPE) + "'";
	//asOrderBy = " ORDER BY ROLL_NO, GROUP_NO, GROUP_NO1, PAGE_NO ASC";
	asOrderBy = " ORDER BY KWON_NO, GROUP_NO, GROUP_NO1, PAGE_NO ASC";

	//asSql  = "SELECT" + asCol + " FROM TB_DOCUMENT14" + asSqlA + asSqlB + asSqlC + asSqlD + asSqlE + asSqlF + asOrderBy;
	asSql  = "SELECT * FROM TB_DOCUMENT14" + asSqlA + asSqlB + asSqlC + asSqlD + asSqlE + asSqlF + asOrderBy;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}
	else {
		memset(&tempDocument14, 0x00, sizeof(DOCUMENT14_STRUCT));
		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			bSamePathName = false;
			asPathName = (char*)tempDocument14.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument14.PATH_NAME, asPathName.c_str());

			for(int i = 0; i < (int)frmMain->m_ResultDocument14.size(); i++)
			{
				if( !strcmp(tempDocument14.PATH_NAME, frmMain->m_ResultDocument14[i].PATH_NAME) )
				{
					bSamePathName = true;
					break;
				}
				//201022//필터링 해제//
//				//200313//
//				if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//					&& !strcmp(tempDocument14.PRCS_DATE, frmMain->m_ResultDocument14[i].PRCS_DATE)
//					&& !strcmp(tempDocument14.MEASURE_TYPE, frmMain->m_ResultDocument14[i].MEASURE_TYPE)
//					&& !strcmp(tempDocument14.KIND_CODE, frmMain->m_ResultDocument14[i].KIND_CODE))
//				{
//					bSamePathName = true;
//					break;
//				}
			}
			if( !bSamePathName )
			{
				nCount++;
				frmMain->m_ResultDocument14.insert(frmMain->m_ResultDocument14.begin() + (_nIndex + nCount), tempDocument14);
			}
			memset(&tempDocument14, 0x00, sizeof(DOCUMENT14_STRUCT));
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument15(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asPathName		 = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[22];//22->21, PAGE_NO QUERY 안함//
	SQLRETURN ret;
	DOCUMENT15_STRUCT 				tempDocument15;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument15, 0x00, sizeof(DOCUMENT15_STRUCT));
	int nIndex = 1;

	//200526//#5//PAGE_NO주석해제//
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.CINDEX			, sizeof(tempDocument15.CINDEX)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.KWON_NO     	, sizeof(tempDocument15.KWON_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.PAGE_NO     	, sizeof(tempDocument15.PAGE_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.KIND_CODE      	, sizeof(tempDocument15.KIND_CODE)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.PRCS_DATE     	, sizeof(tempDocument15.PRCS_DATE)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.DOC_KIND        , sizeof(tempDocument15.DOC_KIND)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REG_NM       	, sizeof(tempDocument15.REG_NM)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REG_NO     	    , sizeof(tempDocument15.REG_NO)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.OWN      		, sizeof(tempDocument15.OWN)   			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP     		, sizeof(tempDocument15.APP)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_NM     		, sizeof(tempDocument15.APP_NM)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_NO     		, sizeof(tempDocument15.APP_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_ADDR       	, sizeof(tempDocument15.APP_ADDR)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_OFFICE     	, sizeof(tempDocument15.APP_OFFICE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REPS_NM       	, sizeof(tempDocument15.REPS_NM)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REPS_NO       	, sizeof(tempDocument15.REPS_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REPS_ADDR     	, sizeof(tempDocument15.REPS_ADDR)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.PATH_NAME     	, sizeof(tempDocument15.PATH_NAME)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.ROLL_NO     	, sizeof(tempDocument15.ROLL_NO)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.SR_NO     		, sizeof(tempDocument15.SR_NO)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.GROUP_NO     	, sizeof(tempDocument15.GROUP_NO)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.GROUP_NO1     	, sizeof(tempDocument15.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument15.clear();

	memset(&tempDocument15, 0x00, sizeof(DOCUMENT15_STRUCT));

	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument15.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument15.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument15.size(); i++)
		{
			if( !strcmp(tempDocument15.PATH_NAME, frmMain->m_ResultDocument15[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}

			//201022//필터링 해제//
//			//200313//
////			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
////				&& !strcmp(tempDocument15.REG_NM, frmMain->m_ResultDocument15[i].REG_NM)
////				&& !strcmp(tempDocument15.PRCS_DATE, frmMain->m_ResultDocument15[i].PRCS_DATE)
////				&& !strcmp(tempDocument15.REG_NO, frmMain->m_ResultDocument15[i].REG_NO)
////				&& tempDocument15.GROUP_NO == frmMain->m_ResultDocument15[i].GROUP_NO)
//			//200528//#9
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument15.KWON_NO, frmMain->m_ResultDocument15[i].KWON_NO)
//				&& tempDocument15.GROUP_NO == frmMain->m_ResultDocument15[i].GROUP_NO)
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument15.push_back(tempDocument15);
		memset(&tempDocument15, 0x00, sizeof(DOCUMENT15_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	int nCount = 0;
	for(int i = 0; i < (int)frmMain->m_ResultDocument15.size(); i++)
	{
		//201215//same KWON_NO, GROUP_NO 이면서 다음 데이터가 "신청서"이면 "결의서"는 건너뛴다.//
		if(i < (int)frmMain->m_ResultDocument15.size() - 1
			&& !strcmp(frmMain->m_ResultDocument15[i].KWON_NO, frmMain->m_ResultDocument15[i+1].KWON_NO)
			&& !strcmp(frmMain->m_ResultDocument15[i+1].KIND_CODE, "03")
			&& frmMain->m_ResultDocument15[i].GROUP_NO == frmMain->m_ResultDocument15[i+1].GROUP_NO)
			continue;

		nCount = funcSelReadDoc15Group(i);
		i += nCount;
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSelReadDoc15Group(int _nIndex)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[22];
	SQLRETURN ret;
	DOCUMENT15_STRUCT 				tempDocument15;

	AnsiString asSql  = "";
	AnsiString asSqlA = "";
	AnsiString asSqlB = "";
	AnsiString asSqlC = "";
	AnsiString asSqlD = "";
	AnsiString asCol  = "";
	AnsiString asOrderBy = "";
	AnsiString asKwonNo = "";
	int nIndex = 1;
	int nCount = 0;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument15, 0x00, sizeof(DOCUMENT15_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.CINDEX			, sizeof(tempDocument15.CINDEX)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.KWON_NO     	, sizeof(tempDocument15.KWON_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.PAGE_NO     	, sizeof(tempDocument15.PAGE_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.KIND_CODE      	, sizeof(tempDocument15.KIND_CODE)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.PRCS_DATE     	, sizeof(tempDocument15.PRCS_DATE)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.DOC_KIND        , sizeof(tempDocument15.DOC_KIND)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REG_NM       	, sizeof(tempDocument15.REG_NM)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REG_NO     	    , sizeof(tempDocument15.REG_NO)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.OWN      		, sizeof(tempDocument15.OWN)   			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP     		, sizeof(tempDocument15.APP)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_NM     		, sizeof(tempDocument15.APP_NM)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_NO     		, sizeof(tempDocument15.APP_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_ADDR       	, sizeof(tempDocument15.APP_ADDR)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.APP_OFFICE     	, sizeof(tempDocument15.APP_OFFICE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REPS_NM       	, sizeof(tempDocument15.REPS_NM)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REPS_NO       	, sizeof(tempDocument15.REPS_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.REPS_ADDR     	, sizeof(tempDocument15.REPS_ADDR)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument15.PATH_NAME     	, sizeof(tempDocument15.PATH_NAME)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.ROLL_NO     	, sizeof(tempDocument15.ROLL_NO)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.SR_NO     		, sizeof(tempDocument15.SR_NO)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.GROUP_NO     	, sizeof(tempDocument15.GROUP_NO)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument15.GROUP_NO1     	, sizeof(tempDocument15.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;

	//201105//asCol = " CINDEX, KWON_NO, KIND_CODE, DOC_KIND, ROLL_NO, GROUP_NO, GROUP_NO1, PATH_NAME";

	asKwonNo = (char*)frmMain->m_ResultDocument15[_nIndex].KWON_NO;
	if( !asKwonNo.IsEmpty() )
		asSqlA = " KWON_NO = '" + asKwonNo + "'";

//=======================================================================
//v1.0.0.5//REQ//FLOW(JOB_NO:473)//ADD_DOC15_KIND_CODE_05//
	asSqlB = " KIND_CODE <> '02' AND KIND_CODE <> '03' AND KIND_CODE <> '05' AND KIND_CODE <> '09' AND KIND_CODE <> '50'";
	if( !asSqlA.IsEmpty() )
		asSqlB = " AND " + asSqlB;
//OLD//
//	//200527//#8//명재씨Req//비법인에 '결의서' 기본 검색문서로 추가//
//	if( asSqlA.IsEmpty() )
//		asSqlB = " KIND_CODE <> '02' AND KIND_CODE <> '03' AND KIND_CODE <> '09' AND KIND_CODE <> '50'";
//	else
//		asSqlB = " AND KIND_CODE <> '02' AND KIND_CODE <> '03' AND KIND_CODE <> '09' AND KIND_CODE <> '50'";
//=======================================================================

	asSqlC = " AND GROUP_NO = " + IntToStr(frmMain->m_ResultDocument15[_nIndex].GROUP_NO);
	asSqlD = " AND (GROUP_NO1 = " + IntToStr(frmMain->m_ResultDocument15[_nIndex].GROUP_NO1) + " OR GROUP_NO1 = 1)";

	asOrderBy = " ORDER BY KWON_NO, KIND_CODE ASC";

	//201105//asSql = "SELECT" + asCol + " FROM TB_DOCUMENT15 WHERE" + asSqlA + asSqlB + asSqlC + asSqlD + asOrderBy;
	asSql = "SELECT * FROM TB_DOCUMENT15 WHERE" + asSqlA + asSqlB + asSqlC + asSqlD + asOrderBy;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return 0;
	}
	else {
		memset(&tempDocument15, 0x00, sizeof(DOCUMENT15_STRUCT));

		while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			bSamePathName = false;
			asPathName = (char*)tempDocument15.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDocument15.PATH_NAME, asPathName.c_str());

			for(int i = 0; i < (int)frmMain->m_ResultDocument15.size(); i++)
			{
				if( !strcmp(tempDocument15.PATH_NAME, frmMain->m_ResultDocument15[i].PATH_NAME) )
				{
					bSamePathName = true;
					break;
				}

				//201022//필터링 해제//
//				//200313//
////				if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
////					&& !strcmp(tempDocument15.REG_NM, frmMain->m_ResultDocument15[i].REG_NM)
////					&& !strcmp(tempDocument15.PRCS_DATE, frmMain->m_ResultDocument15[i].PRCS_DATE)
////					&& !strcmp(tempDocument15.REG_NO, frmMain->m_ResultDocument15[i].REG_NO))
//				//200528//#9
//				if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//					&& !strcmp(tempDocument15.KWON_NO, frmMain->m_ResultDocument15[i].KWON_NO)
//					&& !strcmp(tempDocument15.KIND_CODE, frmMain->m_ResultDocument15[i].KIND_CODE)
//					&& tempDocument15.GROUP_NO == frmMain->m_ResultDocument15[i].GROUP_NO)
//				{
//					bSamePathName = true;
//					break;
//				}
			}
			if( !bSamePathName )
			{
				nCount++;
				frmMain->m_ResultDocument15.insert(frmMain->m_ResultDocument15.begin() + (_nIndex + nCount), tempDocument15);
			}
			memset(&tempDocument15, 0x00, sizeof(DOCUMENT15_STRUCT));
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument16(AnsiString qry)
{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	SQLINTEGER m_nVal[6];
//	SQLRETURN ret;
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//
//	memset(&frmMain->tempDocument16, 0x00, sizeof(DOCUMENT16_STRUCT));
//	int nIndex = 1;
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &frmMain->tempDocument16.CINDEX      , sizeof(frmMain->tempDocument16.CINDEX)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument16.KIND_CODE     , sizeof(frmMain->tempDocument16.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument16.KIND_CODE        , sizeof(frmMain->tempDocument16.KIND_CODE)         , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument16.REG_NM       , sizeof(frmMain->tempDocument16.REG_NM)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument16.REG_NO     , sizeof(frmMain->tempDocument16.REG_NO)   , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument16.PATH_NAME      , sizeof(frmMain->tempDocument16.PATH_NAME)   , &m_nVal[nIndex-1]); nIndex++;
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	frmMain->m_ResultDocument16.clear();
//
//	memset(&frmMain->tempDocument16, 0x00, sizeof(DOCUMENT16_STRUCT));
//	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
//	{
//		frmMain->m_ResultDocument16.push_back(frmMain->tempDocument16);
//		memset(&frmMain->tempDocument16, 0x00, sizeof(DOCUMENT16_STRUCT));
//	};
//
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument17(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asPathName 	  = "";
	bool		bSamePathName = false;

	SQLINTEGER m_nVal[10];
	SQLRETURN ret;
	DOCUMENT17_STRUCT 				tempDocument17;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument17, 0x00, sizeof(DOCUMENT17_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument17.SEQ_NUM  		, sizeof(tempDocument17.SEQ_NUM)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.KWON_NO     	, sizeof(tempDocument17.KWON_NO)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.KIND_CODE      , sizeof(tempDocument17.KIND_CODE)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.DOC_CODE     	, sizeof(tempDocument17.DOC_CODE)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.DOC_NAME     	, sizeof(tempDocument17.DOC_NAME)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.PYO_PAGE     	, sizeof(tempDocument17.PYO_PAGE)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.PAGE     		, sizeof(tempDocument17.PAGE)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.DOC_DATE     	, sizeof(tempDocument17.DOC_DATE)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.PNU     		, sizeof(tempDocument17.PNU)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument17.PATH_NAME    	, sizeof(tempDocument17.PATH_NAME)  	, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	//191104//in funcClearResultVector()//frmMain->m_ResultDocument17.clear();

	memset(&tempDocument17, 0x00, sizeof(DOCUMENT17_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		bSamePathName = false;
		asPathName = (char*)tempDocument17.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument17.PATH_NAME, asPathName.c_str());

		for(int i = 0; i < (int)frmMain->m_ResultDocument17.size(); i++)
		{
			if( !strcmp(tempDocument17.PATH_NAME, frmMain->m_ResultDocument17[i].PATH_NAME) )
			{
				bSamePathName = true;
				break;
			}
			//201022//필터링 해제//
//			//200313//
//			if(    !frmSearch->m_bKindDoc//상세검색//문서구분 아니고//
//				&& !strcmp(tempDocument17.KWON_NO, frmMain->m_ResultDocument17[i].KWON_NO)
//				&& !strcmp(tempDocument17.DOC_NAME, frmMain->m_ResultDocument17[i].DOC_NAME))
//			{
//				bSamePathName = true;
//				break;
//			}
		}
		if( !bSamePathName )
			frmMain->m_ResultDocument17.push_back(tempDocument17);
		memset(&tempDocument17, 0x00, sizeof(DOCUMENT17_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------


//===========================================================================
// #좌표계산부#
//===========================================================================
void __fastcall TfrmSql::funcReadDocument18All()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[12][255];
	SQLINTEGER 	m_nVal[12];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "TB_DOCUMENT18";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 		= "";
	AnsiString 	asPathName 	= "";
	DOCUMENT18_STRUCT tempDoc18;
	int nIndex = 1;

	frmMain->m_ResultDocument18All.clear();
	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.ROLL_NO, 		sizeof(tempDoc18.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.GROUP_NO, 		sizeof(tempDoc18.GROUP_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KIND_CODE, 		sizeof(tempDoc18.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KWON_NO, 			sizeof(tempDoc18.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PAGE_NO, 			sizeof(tempDoc18.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_NAME, 		sizeof(tempDoc18.JIGU_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_YEAR, 		sizeof(tempDoc18.JIGU_YEAR), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.MEASURE_DATE, 	sizeof(tempDoc18.MEASURE_DATE), &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.CHECK_DATE, 		sizeof(tempDoc18.CHECK_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.DOGNPOINT, 		sizeof(tempDoc18.DOGNPOINT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.BOJOPOINT, 		sizeof(tempDoc18.BOJOPOINT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PATH_NAME, 		sizeof(tempDoc18.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;

	//Where condition
	asSqlQry.sprintf("SELECT ROLL_NO, GROUP_NO, KIND_CODE, KWON_NO, PAGE_NO, JIGU_NAME, JIGU_YEAR, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME FROM %s", asSqlTbl);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		AnsiString asPoint	 = "";
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			asPoint = (char*)tempDoc18.BOJOPOINT;

			if(asPoint != ""){
				int iPos = asPoint.Pos("_");
				if(iPos > 1){//숫자없이 "_"만 들어가는 경우에 대한 처리//
					tempDoc18.X = asPoint.SubString(1, iPos-1).ToDouble();
					asPoint.Delete(1,iPos);
					if(asPoint != "") tempDoc18.Y = asPoint.ToDouble();
					else tempDoc18.Y = 0;
				}
				else{
					tempDoc18.X = 0;
					tempDoc18.Y = 0;
				}
			}
			else{
				tempDoc18.X = 0;
				tempDoc18.Y = 0;
			}
			asPathName = (char*)tempDoc18.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDoc18.PATH_NAME, asPathName.c_str());

			frmMain->m_ResultDocument18All.push_back(tempDoc18);
			memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------

//void __fastcall TfrmSql::funcReadDocument18(AnsiString qry)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	SQLCHAR    	m_cVal[11][255];
//	SQLINTEGER 	m_nVal[11];
//	SQLRETURN 	ret;
//	AnsiString 	asSqlTbl	= "TB_DOCUMENT18";
//	AnsiString 	asSqlWhere 	= "";
//	AnsiString  asSqlQry	= "";
//	AnsiString 	asCol 		= "";
//	AnsiString 	asPathName 	= "";
//	DOCUMENT18_STRUCT tempDoc18;
//	int nIndex = 1;
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));
//
////asColumn = "distinct JIGU_YEAR, JIGU_NAME, KWON_NO, KIND_CODE, GROUP_NO, PAGE_NO, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME";
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_YEAR, 		sizeof(tempDoc18.JIGU_YEAR), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_NAME, 		sizeof(tempDoc18.JIGU_NAME), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KWON_NO, 			sizeof(tempDoc18.KWON_NO), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KIND_CODE, 		sizeof(tempDoc18.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.GROUP_NO, 		sizeof(tempDoc18.GROUP_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PAGE_NO, 			sizeof(tempDoc18.PAGE_NO), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.MEASURE_DATE, 	sizeof(tempDoc18.MEASURE_DATE), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.CHECK_DATE, 		sizeof(tempDoc18.CHECK_DATE), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.DOGNPOINT, 		sizeof(tempDoc18.DOGNPOINT), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.BOJOPOINT, 		sizeof(tempDoc18.BOJOPOINT), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PATH_NAME, 		sizeof(tempDoc18.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;
//
//	ret = SQLPrepare(m_hStmt, (SQLCHAR *)qry.c_str(), SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//	else {
//		AnsiString asPoint	 = "";
//		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
//		{
//			if( !strcmp(tempDoc18.KIND_CODE, "00") )//첫페이지 찾기 위해서 00010
//				strcpy(tempDoc18.KIND_CODE, "14");//구비서류
//
//			asPoint = (char*)tempDoc18.BOJOPOINT;
//
//			if(asPoint != ""){
//				int iPos = asPoint.Pos("_");
//				if(iPos > 0){
//					tempDoc18.X = asPoint.SubString(1, iPos-1).ToDouble();
//					asPoint.Delete(1,iPos);
//					if(asPoint != "") tempDoc18.Y = asPoint.ToDouble();
//					else tempDoc18.Y = 0;
//				}
//				else{
//					tempDoc18.X = 0;
//					tempDoc18.Y = 0;
//				}
//			}
//			else{
//				tempDoc18.X = 0;
//				tempDoc18.Y = 0;
//			}
//			asPathName = (char*)tempDoc18.PATH_NAME;
//			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//			strcpy(tempDoc18.PATH_NAME, asPathName.c_str());
//
//			bool bSamed	= false;
//			for(int i = 0; i < (int)frmMain->m_ResultDocument18.size(); i++)
//			{
//				//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
//				if( !strcmp(frmMain->m_ResultDocument18[i].PATH_NAME, tempDoc18.PATH_NAME) )
//				{
//					bSamed = true;
//					break;
//				}
//			}
//
//			if( !bSamed )
//				frmMain->m_ResultDocument18.push_back(tempDoc18);
//			memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));
//		};
//		if(m_hStmt) SQLCloseCursor(m_hStmt);
//	}
//}
////---------------------------------------------------------------------------

//201105//
void __fastcall TfrmSql::funcReadDocument18(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[16][255];
	SQLINTEGER 	m_nVal[16];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "TB_DOCUMENT18";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 		= "";
	AnsiString 	asPathName 	= "";
	DOCUMENT18_STRUCT tempDoc18;
	int nIndex = 1;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));

//asColumn = "distinct JIGU_YEAR, JIGU_NAME, KWON_NO, KIND_CODE, GROUP_NO, PAGE_NO, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME";
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.ROLL_NO, 		sizeof(tempDoc18.ROLL_NO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.FRAME_NO, 		sizeof(tempDoc18.FRAME_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.SR_NO, 			sizeof(tempDoc18.SR_NO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.GROUP_NO, 		sizeof(tempDoc18.GROUP_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KIND_CODE, 		sizeof(tempDoc18.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KWON_NO, 			sizeof(tempDoc18.KWON_NO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PAGE_NO, 			sizeof(tempDoc18.PAGE_NO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.SERIAL_NO, 		sizeof(tempDoc18.SERIAL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_NAME, 		sizeof(tempDoc18.JIGU_NAME), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_YEAR, 		sizeof(tempDoc18.JIGU_YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PNU, 				sizeof(tempDoc18.PNU), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.MEASURE_DATE, 	sizeof(tempDoc18.MEASURE_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.CHECK_DATE, 		sizeof(tempDoc18.CHECK_DATE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.DOGNPOINT, 		sizeof(tempDoc18.DOGNPOINT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.BOJOPOINT, 		sizeof(tempDoc18.BOJOPOINT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PATH_NAME, 		sizeof(tempDoc18.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)qry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		AnsiString asPoint	 = "";
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			if( !strcmp(tempDoc18.KIND_CODE, "00") )//첫페이지 찾기 위해서 00010
				strcpy(tempDoc18.KIND_CODE, "14");//구비서류

			asPoint = (char*)tempDoc18.BOJOPOINT;

			if(asPoint != ""){
				int iPos = asPoint.Pos("_");
				if(iPos > 0){
					tempDoc18.X = asPoint.SubString(1, iPos-1).ToDouble();
					asPoint.Delete(1,iPos);
					if(asPoint != "") tempDoc18.Y = asPoint.ToDouble();
					else tempDoc18.Y = 0;
				}
				else{
					tempDoc18.X = 0;
					tempDoc18.Y = 0;
				}
			}
			else{
				tempDoc18.X = 0;
				tempDoc18.Y = 0;
			}
			asPathName = (char*)tempDoc18.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDoc18.PATH_NAME, asPathName.c_str());

			bool bSamed	= false;
			for(int i = 0; i < (int)frmMain->m_ResultDocument18.size(); i++)
			{
				//파일명이 같은게 검색이 되면 무시//
				if( !strcmp(frmMain->m_ResultDocument18[i].PATH_NAME, tempDoc18.PATH_NAME) )
				{
					bSamed = true;
					break;
				}
			}

			if( !bSamed )
				frmMain->m_ResultDocument18.push_back(tempDoc18);
			memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------


//==================================================================
//231020//GAGAMLAYER in LandArchive
//==================================================================
void __fastcall TfrmSql::funcReadDocument20(AnsiString _asSqlQry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[11][255];
	SQLINTEGER 	m_nVal[11];
	SQLRETURN 	ret;
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 		= "";
	AnsiString 	asPathName 	= "";
	DOCUMENT20_STRUCT tempDoc20;
	int nIndex = 1;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc20, 0x00, sizeof(DOCUMENT20_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.KWON_NO, 			sizeof(tempDoc20.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.GAGAM_NO, 		sizeof(tempDoc20.GAGAM_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.UMDRI_CD, 		sizeof(tempDoc20.UMDRI_CD), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.DOHO, 			sizeof(tempDoc20.DOHO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.DOC_NAME, 		sizeof(tempDoc20.DOC_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.KIND_CODE, 		sizeof(tempDoc20.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.PAGE_NO, 			sizeof(tempDoc20.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.SURV_DATE, 		sizeof(tempDoc20.SURV_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.SURV_ETC, 		sizeof(tempDoc20.SURV_ETC), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.PRCS_DATE, 		sizeof(tempDoc20.PRCS_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.PATH_NAME, 		sizeof(tempDoc20.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)_asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			asPathName = (char*)tempDoc20.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDoc20.PATH_NAME, asPathName.c_str());
			frmMain->m_ResultDocument20.push_back(tempDoc20);
			memset(&tempDoc20, 0x00, sizeof(DOCUMENT20_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmSql::funcSidoCodeLikeQuery(AnsiString _asKeyWord)
{
	frmMain->m_vPNU_SIDOCODE.clear();

	SQLCHAR m_cVal[6][32];
	SQLINTEGER m_nVal[32];
	AnsiString mSqlQry = "";
	AnsiString asWhereSql = "";
	SQLRETURN ret;
	AnsiString codediv;

	SIDONAME_STRUCT mTempSidoName;
	memset(&mTempSidoName, 0, sizeof(mTempSidoName));

	int nIndex = 1;
	memset(m_nVal, 0, sizeof(m_nVal));
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSidoName.cSggCd   , sizeof(mTempSidoName.cSggCd)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSidoName.cSggNm   , sizeof(mTempSidoName.cSggNm)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSidoName.cUmdCd   , sizeof(mTempSidoName.cUmdCd)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSidoName.cUmdNm   , sizeof(mTempSidoName.cUmdNm)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSidoName.cRiCd    , sizeof(mTempSidoName.cRiCd)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSidoName.cRiNm    , sizeof(mTempSidoName.cRiNm)       , &m_nVal[nIndex-1]); nIndex++;

	asWhereSql = " WHERE SGG_NM LIKE '%" + _asKeyWord + "%' ";
	asWhereSql = asWhereSql + "AND UMD_NM LIKE '%" + _asKeyWord + "%' ";
	asWhereSql = asWhereSql + "AND RI_NM LIKE '%" + _asKeyWord + "%' ";

	if(frmMain->INIINFO.SIDOCODE == "36110")//2101016//#SEJONG
		mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + asWhereSql + "ORDER BY SIDOSGG_CD, UMD_CD, RI_CD ASC";
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->INIINFO.SIDOCODE == "11305")
		mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE_" + frmMain->INIINFO.SIDOCODE + asWhereSql + "ORDER BY SIDOSGG_CD, UMD_CD, RI_CD ASC";
//=============================================================================
	else
		mSqlQry = "SELECT DISTINCT SIDOSGG_CD, UMD_CD, RI_CD, SGG_NM, UMD_NM, RI_NM FROM SIDO_CODE" + asWhereSql + "ORDER BY SIDOSGG_CD, UMD_CD, RI_CD ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		frmMsg->funcMessageDlg("정보부재알림:", "SIDO_CODE를 불러올 수 없습니다.", 3);
		return;
	}
	else{
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			frmMain->m_vPNU_SIDOCODE.push_back(mTempSidoName);
			memset(&mTempSidoName, 0, sizeof(mTempSidoName));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmSql::funcGetUmdRiCd(AnsiString _asUmdRiNm)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asTable		= "SIDO_CODE";
	AnsiString  asSqlQry 	= "";
	AnsiString  asColumn 	= "DISTINCT UMD_CD, RI_CD";
	AnsiString  asWhere 	= "";
	SQLRETURN 	ret;

	SQLCHAR m_cVal[2][30];
	SQLINTEGER m_nVal[2];

	for(int i=0; i<2; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	//---
	asWhere		= " WHERE SIDOSGG_CD='" + frmMain->_SIDOCODE + "' AND CONCAT(UMD_NM, ' ', RI_NM) = '" + _asUmdRiNm + "'";
	//---
	asSqlQry 	= "SELECT " + asColumn + " FROM " + asTable + asWhere;
	//---
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);
	//---
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return "";
	}

	//---
	AnsiString readData[2];
	char temp[30];

	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		for(int i=0; i<2; i++) readData[i] = "";

		for(int i=0; i<2; i++){
			memset(temp, 0x00, sizeof(temp) );
			memcpy(temp, m_cVal[i], sizeof( temp ));
			readData[i] = (char*)temp;
		}
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString asUmdRiCd = "";
	asUmdRiCd = readData[0] + readData[1];

	return asUmdRiCd;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmSql::funcGetUmdRiNm(AnsiString _asUmdRiCd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asTable		= "SIDO_CODE";
	AnsiString  asSqlQry 	= "";
	AnsiString  asColumn 	= "DISTINCT UMD_NM, RI_NM";
	AnsiString  asWhere 	= "";
	SQLRETURN 	ret;

	SQLCHAR m_cVal[2][30];
	SQLINTEGER m_nVal[2];

	for(int i=0; i<2; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	//---
	asWhere		= " WHERE SIDOSGG_CD='" + frmMain->_SIDOCODE + "' AND CONCAT(UMD_NM, ' ', RI_NM) = '" + _asUmdRiCd + "'";
	//---
	asSqlQry 	= "SELECT " + asColumn + " FROM " + asTable + asWhere;
	//---
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);
	//---
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return "";
	}

	//---
	AnsiString readData[2];
	char temp[30];

	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		for(int i=0; i<2; i++) readData[i] = "";

		for(int i=0; i<2; i++){
			memset(temp, 0x00, sizeof(temp) );
			memcpy(temp, m_cVal[i], sizeof( temp ));
			readData[i] = (char*)temp;
		}
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString asUmdRiNm = "";
	asUmdRiNm = readData[0] + readData[1];

	return asUmdRiNm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcZoneCodeLikeQuery(AnsiString _asKeyWord)
{
	frmMain->m_vDOC6_ZONECODE.clear();

	SQLCHAR m_cVal[2][50];
	SQLINTEGER m_nVal[10];
	AnsiString mSqlQry;
	AnsiString asWhereSql = "";
	SQLRETURN ret;
	AnsiString result[10];
	char min_cValue[50];
	AnsiString codediv;

	ZONENAME_STRUCT mTempZoneName;
	memset(&mTempZoneName, 0, sizeof(mTempZoneName));

	int nIndex = 1;
	memset(m_nVal, 0, sizeof(m_nVal));
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempZoneName.zonecode     , sizeof(mTempZoneName.zonecode)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempZoneName.zonename     , sizeof(mTempZoneName.zonename)       , &m_nVal[nIndex-1]); nIndex++;

	asWhereSql = "WHERE ZONE_NAME LIKE '%" + _asKeyWord + "%' ";
	mSqlQry = "";
	mSqlQry = "SELECT ZONE_CODE, ZONE_NAME FROM ZONE_CODE " + asWhereSql + "ORDER BY ZONE_CODE ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		frmMsg->funcMessageDlg("정보부재알림:", "ZONE_CODE를 불러올 수 없습니다.", 3);
		return;
	}
	else{
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
		{
			frmMain->m_vDOC6_ZONECODE.push_back(mTempZoneName);
			memset(&mTempZoneName, 0, sizeof(mTempZoneName));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------

//191122
void __fastcall TfrmSql::funcReadDocument07Index()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlQry  = "";
	SQLRETURN ret;

	memset(&frmMain->tempDocument07index, 0x00, sizeof(DOCUMENT07_INDEX_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[7];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07index.SUR, 		sizeof(frmMain->tempDocument07index.SUR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07index.LAND_GBN, 	sizeof(frmMain->tempDocument07index.LAND_GBN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07index.DOHO_BON, 	sizeof(frmMain->tempDocument07index.DOHO_BON), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	frmMain->tempDocument07index.SCALE, 		sizeof(frmMain->tempDocument07index.SCALE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&frmMain->tempDocument07index.COUNT, 	sizeof(frmMain->tempDocument07index.COUNT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&frmMain->tempDocument07index.X, 		sizeof(frmMain->tempDocument07index.X), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&frmMain->tempDocument07index.Y, 		sizeof(frmMain->tempDocument07index.Y), 			&m_nVal[nIndex-1]); nIndex++;

	asSqlQry = "SELECT * FROM TB_DOCUMENT07_INDEX ORDER BY SUR, GBN, DOHO_BON, SCALE";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_ResultDocument07Index.clear();

	memset(&frmMain->tempDocument07index, 0x00, sizeof(DOCUMENT07_INDEX_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_ResultDocument07Index.push_back(frmMain->tempDocument07index);
		memset(&frmMain->tempDocument07index, 0x00, sizeof(DOCUMENT07_INDEX_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------


//191116//TB_DOCUMENT07의 모든 데이터를 갖고 있자//
void __fastcall TfrmSql::funcReadDocument07()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[24][255];
	SQLINTEGER 	m_nVal[24];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "TB_DOCUMENT07";
	AnsiString 	asSqlWhere 	= "";
	AnsiString 	asSqlOrder 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 	= "";
	AnsiString  asPathName = "";
	DOCUMENT07_STRUCT tempDoc;
	int nIndex = 1;

	frmMain->m_vDOCUMENT07FILEINFO.clear();
	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(DOCUMENT07_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.PATH_NAME, 		sizeof(tempDoc.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 		sizeof(tempDoc.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.ROLL_NO, 		sizeof(tempDoc.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.FRAME_NO, 		sizeof(tempDoc.FRAME_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KWON_NO, 		sizeof(tempDoc.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.PAGE_NO, 		sizeof(tempDoc.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.LAND_GBN, 		sizeof(tempDoc.LAND_GBN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.SIDOSGG, 		sizeof(tempDoc.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.UMD, 			sizeof(tempDoc.UMD), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.RI, 			sizeof(tempDoc.RI), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.SCALE, 			sizeof(tempDoc.SCALE), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.DOHO_BON, 		sizeof(tempDoc.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.DOHO_BU, 		sizeof(tempDoc.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.X1, 			sizeof(tempDoc.X1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.Y1, 			sizeof(tempDoc.Y1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.X2, 			sizeof(tempDoc.X2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.Y2, 			sizeof(tempDoc.Y2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.SIZE_X, 		sizeof(tempDoc.SIZE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.SIZE_Y, 		sizeof(tempDoc.SIZE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.BASE_X, 		sizeof(tempDoc.BASE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.BASE_Y, 		sizeof(tempDoc.BASE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.RATIOX, 		sizeof(tempDoc.RATIOX), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc.RATIOY, 		sizeof(tempDoc.RATIOY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.REMARK, 		sizeof(tempDoc.REMARK), 		&m_nVal[nIndex-1]); nIndex++;

	asSqlOrder	= "ORDER BY SIDOSGG, UMD, RI, LAND_GBN, SCALE, DOHO_BON, KIND_CODE ASC";

	asSqlQry.sprintf("SELECT * FROM %s %s", asSqlTbl, asSqlOrder);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			asPathName = (char*)tempDoc.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempDoc.PATH_NAME, asPathName.c_str());
			frmMain->m_vDOCUMENT07FILEINFO.push_back(tempDoc);
			memset(&tempDoc, 0x00, sizeof(DOCUMENT07_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------


//===========================================================================
// #MAPPOINT
//===========================================================================
//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
//_asDetailQry 추가//
void __fastcall TfrmSql::funcQrySelect_DOCUMENT07_MAPPOINT(bool _bSub, int _nIndex, AnsiString _asDetailQry)
//OLD//void __fastcall TfrmSql::funcQrySelect_DOCUMENT07_MAPPOINT(bool _bSub, int _nIndex)
//=============================================================================
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[24][255];
	SQLINTEGER 	m_nVal[24];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "TB_DOCUMENT07";
	AnsiString 	asSqlWhere 	= "";
	AnsiString 	asSqlOrder 	= "KIND_CODE, SCALE ASC";//200916//"PATH_NAME ASC";
	AnsiString  asSqlQry	= "";
	AnsiString  asPathName	= "";
	AnsiString  asLandCd	= "";//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG//
	int 		nX          = 0;
	int 		nY          = 0;
	DOCUMENT07_STRUCT tempInfo;
	int nIndex = 1;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempInfo, 0x00, sizeof(DOCUMENT07_STRUCT));

	if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
		frmMain->m_ResultDocument07_SUB.clear();

	if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	{
		asLandCd	= (char*)frmMain->m_vLANDINFO_SUB[0].LAND_CD;//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG//
		nX          = frmMain->m_vLANDINFO_SUB[0].X;
		nY          = frmMain->m_vLANDINFO_SUB[0].Y;
	}
	else
	{
		asLandCd	= (char*)frmMain->m_vLANDINFO[_nIndex].LAND_CD;//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG//
		nX          = frmMain->m_vLANDINFO[_nIndex].X;
		nY          = frmMain->m_vLANDINFO[_nIndex].Y;
	}

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.PATH_NAME, 	sizeof(tempInfo.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.KIND_CODE, 	sizeof(tempInfo.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempInfo.ROLL_NO, 		sizeof(tempInfo.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempInfo.FRAME_NO, 	sizeof(tempInfo.FRAME_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.KWON_NO, 		sizeof(tempInfo.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.PAGE_NO, 		sizeof(tempInfo.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.LAND_GBN, 		sizeof(tempInfo.LAND_GBN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.SIDOSGG, 		sizeof(tempInfo.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.UMD, 			sizeof(tempInfo.UMD), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.RI, 			sizeof(tempInfo.RI), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.SCALE, 		sizeof(tempInfo.SCALE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.DOHO_BON, 		sizeof(tempInfo.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.DOHO_BU, 		sizeof(tempInfo.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X1, 			sizeof(tempInfo.X1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y1, 			sizeof(tempInfo.Y1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X2, 			sizeof(tempInfo.X2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y2, 			sizeof(tempInfo.Y2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.SIZE_X, 		sizeof(tempInfo.SIZE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.SIZE_Y, 		sizeof(tempInfo.SIZE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.BASE_X, 		sizeof(tempInfo.BASE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.BASE_Y, 		sizeof(tempInfo.BASE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.RATIOX, 		sizeof(tempInfo.RATIOX), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.RATIOY, 		sizeof(tempInfo.RATIOY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempInfo.REMARK, 		sizeof(tempInfo.REMARK), 		&m_nVal[nIndex-1]); nIndex++;

	//Where condition
	asSqlWhere = asSqlWhere + "X1 <= " + nX + " AND " + nX + " <= X2";
	asSqlWhere = asSqlWhere + " AND Y1 <= " + nY + " AND " + nY + " <= Y2";
//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
	asSqlWhere = asSqlWhere + " AND SIDOSGG = '" + asLandCd.SubString(1,5) + "'";
	asSqlWhere = asSqlWhere + " AND UMD = '" + asLandCd.SubString(6,3) + "'";
	asSqlWhere = asSqlWhere + " AND RI = '" + asLandCd.SubString(9,2) + "'";
//OLD//
//	asSqlWhere = asSqlWhere + " AND SIDOSGG = '" + frmMain->m_asSearchPnu.SubString(1,5) + "'";
//	asSqlWhere = asSqlWhere + " AND UMD = '" + frmMain->m_asSearchPnu.SubString(6,3) + "'";
//	asSqlWhere = asSqlWhere + " AND RI = '" + frmMain->m_asSearchPnu.SubString(9,2) + "'";
//=============================================================================
//	asSqlWhere = asSqlWhere + " AND DOHO_BOB = '" + _asDoho + "'";
//	asSqlWhere = asSqlWhere + " AND SCALE = '" + _asScale + "'";
	if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	{
		asPathName	= StringReplace(frmMain->m_asCurrentFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);
		asSqlWhere = asSqlWhere + " AND PATH_NAME = '" + asPathName + "'";
	}


//=============================================================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG(Old LAND_CD)//
	if( !_asDetailQry.IsEmpty() )
		asSqlWhere = asSqlWhere + _asDetailQry;//asSqlPNU이 중복되어 제거하고 " AND "가 이미 붙어 있어 여기에서는 필요없다.
//=============================================================================

	asSqlQry.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", asSqlTbl, asSqlWhere, asSqlOrder);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
//=========================================
//v1.0.0.5//DOC07_JIBUN_DISPLAY_FOR_SEJONG//
		//200925//일반,산구분하여 문서구분 필터링//
		AnsiString  asStr	= "";
		int			nLandGbn	= 0;//일반(true), 산(false)
		if(asLandCd.Length() == 19)//일반/산 구분//문서 필터링//
		{
			if(asLandCd.SubString(11, 1) == "2")
				nLandGbn = 2;//산지번//
			else if(asLandCd.SubString(11, 1) == "1")
				nLandGbn = 1;//일반지번//
		}
//OLD//
//		//200925//일반,산구분하여 문서구분 필터링//
//		AnsiString  asStr	= "";
//		int			nLandGbn	= 0;//일반(true), 산(false)
//		if(frmMain->m_asSearchPnu.Length() == 19)//일반/산 구분//문서 필터링//
//		{
//			if(frmMain->m_asSearchPnu.SubString(11, 1) == "2")
//				nLandGbn = 2;//산지번//
//			else if(frmMain->m_asSearchPnu.SubString(11, 1) == "1")
//				nLandGbn = 1;//일반지번//
//		}
//=========================================

		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
			{
				asPathName = (char*)tempInfo.PATH_NAME;
				asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
				strcpy(tempInfo.PATH_NAME, asPathName.c_str());

				bool bSamed	= false;
				for(int i = 0; i < (int)frmMain->m_ResultDocument07_SUB.size(); i++)
				{
					//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
					if( !strcmp(frmMain->m_ResultDocument07_SUB[i].PATH_NAME, tempInfo.PATH_NAME) )
					{
						bSamed = true;
						break;
					}
				}

				//200925//일반,산구분하여 문서구분 필터링//
				asStr = eFunc->funcGetKindCodeToKindName(7, (char*)tempInfo.KIND_CODE);
				if(nLandGbn == 1 && asStr.Pos("임야") > 0)//일반//
				{
					continue;
				}
				else if(nLandGbn == 2 && asStr.Pos("임야") == 0)//산//
				{
					continue;
				}

				if( !bSamed ){
					frmMain->m_ResultDocument07_SUB.push_back(tempInfo);
					frmSearch->m_sDoc07DohoCheck = (char*)tempInfo.DOHO_BON;
				}
			}
			else
			{
				asPathName = (char*)tempInfo.PATH_NAME;
				asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
				strcpy(tempInfo.PATH_NAME, asPathName.c_str());

				bool bSamed	= false;
				for(int i = 0; i < (int)frmMain->m_ResultDocument07.size(); i++)
				{
					//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
					if( !strcmp(frmMain->m_ResultDocument07[i].PATH_NAME, tempInfo.PATH_NAME) )
					{
						bSamed = true;
						break;
					}
				}

				//200925//일반,산구분하여 문서구분 필터링//
				asStr = eFunc->funcGetKindCodeToKindName(7, (char*)tempInfo.KIND_CODE);
				if(nLandGbn == 1 && asStr.Pos("임야") > 0)//일반//
				{
					continue;
				}
				else if(nLandGbn == 2 && asStr.Pos("임야") == 0)//산//
				{
					continue;
				}

				if( !bSamed ){
					frmMain->m_ResultDocument07.push_back(tempInfo);
					frmSearch->m_sDoc07DohoCheck = (char*)tempInfo.DOHO_BON;
				}
			}
			memset(&tempInfo, 0x00, sizeof(DOCUMENT07_STRUCT));
		};
	}
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//201227//in frmSearch
//	//
//	frmMain->totalCount[7] = frmMain->m_ResultDocument07.size();
//
//	if(frmMain->totalCount[7] > 0)
//		eTree->funcSettingTreeView(7);
//
//	frmSearch->funcSaveLog(1, 7, asSqlQry);//save to file
}
//---------------------------------------------------------------------------
//201227////201008//
//void __fastcall TfrmSql::funcQrySelect_DOCUMENT07_KINDOFDOC(AnsiString _asPathName)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	SQLCHAR    	m_cVal[24][255];
//	SQLINTEGER 	m_nVal[24];
//	SQLRETURN 	ret;
//	AnsiString 	asSqlTbl	= "TB_DOCUMENT07";
//	AnsiString 	asSqlWhere 	= "";
//	AnsiString 	asSqlOrder 	= "KIND_CODE, SCALE ASC";//200916//"PATH_NAME ASC";
//	AnsiString  asSqlQry	= "";
//	AnsiString  asPathName	= "";
//	DOCUMENT07_STRUCT tempInfo;
//	int nIndex = 1;
//
//	_asPathName = StringReplace(_asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);//201014//
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempInfo, 0x00, sizeof(DOCUMENT07_STRUCT));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.PATH_NAME, 	sizeof(tempInfo.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.KIND_CODE, 	sizeof(tempInfo.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempInfo.ROLL_NO, 		sizeof(tempInfo.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempInfo.FRAME_NO, 	sizeof(tempInfo.FRAME_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.KWON_NO, 		sizeof(tempInfo.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.PAGE_NO, 		sizeof(tempInfo.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.LAND_GBN, 		sizeof(tempInfo.LAND_GBN), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.SIDOSGG, 		sizeof(tempInfo.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.UMD, 			sizeof(tempInfo.UMD), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.RI, 			sizeof(tempInfo.RI), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.SCALE, 		sizeof(tempInfo.SCALE), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.DOHO_BON, 		sizeof(tempInfo.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.DOHO_BU, 		sizeof(tempInfo.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X1, 			sizeof(tempInfo.X1), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y1, 			sizeof(tempInfo.Y1), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X2, 			sizeof(tempInfo.X2), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y2, 			sizeof(tempInfo.Y2), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.SIZE_X, 		sizeof(tempInfo.SIZE_X), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.SIZE_Y, 		sizeof(tempInfo.SIZE_Y), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.BASE_X, 		sizeof(tempInfo.BASE_X), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.BASE_Y, 		sizeof(tempInfo.BASE_Y), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.RATIOX, 		sizeof(tempInfo.RATIOX), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.RATIOY, 		sizeof(tempInfo.RATIOY), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempInfo.REMARK, 		sizeof(tempInfo.REMARK), 		&m_nVal[nIndex-1]); nIndex++;
//
//	//Where condition
//	asSqlWhere = asSqlWhere + " PATH_NAME = '" + _asPathName + "'";
//	asSqlQry.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", asSqlTbl, asSqlWhere, asSqlOrder);
//
//	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//	else {
//		//200925//일반,산구분하여 문서구분 필터링//
//		AnsiString  asStr	= "";
//		int			nLandGbn	= 0;//일반(true), 산(false)
//		if(frmMain->m_asSearchPnu.Length() == 19)//일반/산 구분//문서 필터링//
//		{
//			if(frmMain->m_asSearchPnu.SubString(11, 1) == "2")
//				nLandGbn = 2;//산지번//
//			else if(frmMain->m_asSearchPnu.SubString(11, 1) == "1")
//				nLandGbn = 1;//일반지번//
//		}
//
//		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
//		{
//			asPathName = (char*)tempInfo.PATH_NAME;
//			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//			strcpy(tempInfo.PATH_NAME, asPathName.c_str());
//
//			bool bSamed	= false;
//			for(int i = 0; i < (int)frmMain->m_ResultDocument07.size(); i++)
//			{
//				//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
//				if( !strcmp(frmMain->m_ResultDocument07[i].PATH_NAME, tempInfo.PATH_NAME) )
//				{
//					bSamed = true;
//					break;
//				}
//			}
//
//			//200925//일반,산구분하여 문서구분 필터링//
//			asStr = eFunc->funcGetKindCodeToKindName(7, (char*)tempInfo.KIND_CODE);
//			if(nLandGbn == 1 && asStr.Pos("임야") > 0)//일반//
//			{
//				continue;
//			}
//			else if(nLandGbn == 2 && asStr.Pos("임야") == 0)//산//
//			{
//				continue;
//			}
//
//			if( !bSamed ){
//				frmMain->m_ResultDocument07.push_back(tempInfo);
//				frmSearch->m_sDoc07DohoCheck = (char*)tempInfo.DOHO_BON;
//			}
//			memset(&tempInfo, 0x00, sizeof(DOCUMENT07_STRUCT));
//		};
//	}
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//}
//---------------------------------------------------------------------------

//void __fastcall TfrmSql::funcQrySelect_DOCUMENT07_PNU(AnsiString _asPnu)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	SQLCHAR    	m_cVal[8][255];
//	SQLINTEGER 	m_nVal[8];
//	SQLRETURN 	ret;
//	AnsiString 	asSqlTbl	= "TB_DOCUMENT07_PNU";
//	AnsiString 	asSqlWhere 	= "";
//	AnsiString 	asSqlOrder 	= "";
//	AnsiString  asSqlQry	= "";
//	AnsiString 	asCol 		= "";
//	AnsiString  asPathName	= "";//201014//
//	DOCUMENT07_PNU_STRUCT tempDoc07Pnu;
//	int nIndex = 1;
//
//	frmMain->m_vDOC07PNU.clear();
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempDoc07Pnu, 0x00, sizeof(DOCUMENT07_PNU_STRUCT));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07Pnu.PNU, 			sizeof(tempDoc07Pnu.PNU), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07Pnu.KIND_CODE, 	sizeof(tempDoc07Pnu.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07Pnu.PATH_NAME, 	sizeof(tempDoc07Pnu.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07Pnu.IMAGEX, 		sizeof(tempDoc07Pnu.IMAGEX), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07Pnu.IMAGEY, 		sizeof(tempDoc07Pnu.IMAGEY), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07Pnu.X, 			sizeof(tempDoc07Pnu.X), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07Pnu.Y, 			sizeof(tempDoc07Pnu.Y), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07Pnu.GBN, 			sizeof(tempDoc07Pnu.GBN), 			&m_nVal[nIndex-1]); nIndex++;
//
//	//Where condition
//	asSqlWhere = asSqlWhere + "PNU = '" + _asPnu + "'";
//	asSqlOrder = asSqlOrder + "KIND_CODE ASC";
//	asSqlQry.sprintf("SELECT * FROM %s WHERE %s ORDER BY %s", asSqlTbl, asSqlWhere, asSqlOrder);
//
//	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//	else {
//		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
//		{
//			//201014//
//			asPathName = (char*)tempDoc07Pnu.PATH_NAME;
//			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//			strcpy(tempDoc07Pnu.PATH_NAME, asPathName.c_str());
//			frmMain->m_vDOC07PNU.push_back(tempDoc07Pnu);
//			memset(&tempDoc07Pnu, 0x00, sizeof(DOCUMENT07_PNU_STRUCT));
//		};
//		if(m_hStmt) SQLCloseCursor(m_hStmt);
//	}
//}
////---------------------------------------------------------------------------
//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
void __fastcall TfrmSql::funcQrySelect_DOCUMENT07_PNU(bool _bSub, AnsiString _asPnu)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[12][255];
	SQLINTEGER 	m_nVal[12];
	SQLRETURN 	ret;
	AnsiString 	asSqlTblA	= "TB_DOCUMENT07 A";
	AnsiString 	asSqlTblB	= "";
	AnsiString 	asSqlWhere 	= "";
	AnsiString 	asSqlOrder 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 		= "";
	AnsiString  asPathName	= "";//201014//
	DOCUMENT07_STRUCT tempInfo;
	int nIndex = 1;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempInfo, 0x00, sizeof(DOCUMENT07_STRUCT));

	if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
		frmMain->m_ResultDocument07_SUB.clear();
	else
		frmMain->m_ResultDocument07.clear();

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.PATH_NAME, 	sizeof(tempInfo.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.KIND_CODE, 	sizeof(tempInfo.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.KWON_NO, 		sizeof(tempInfo.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.LAND_GBN, 		sizeof(tempInfo.LAND_GBN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.SIDOSGG, 		sizeof(tempInfo.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.UMD, 			sizeof(tempInfo.UMD), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.RI, 			sizeof(tempInfo.RI), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.SCALE, 		sizeof(tempInfo.SCALE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.DOHO_BON, 		sizeof(tempInfo.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.DOHO_BU, 		sizeof(tempInfo.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.BASE_X, 		sizeof(tempInfo.BASE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.BASE_Y, 		sizeof(tempInfo.BASE_Y), 		&m_nVal[nIndex-1]); nIndex++;

	if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	{
		asPathName	= StringReplace(frmMain->m_asCurrentFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);
		asSqlTblB	= "(SELECT PATH_NAME, IMAGEX, IMAGEY FROM TB_DOCUMENT07_PNU WHERE PNU = '" + _asPnu + "' AND PATH_NAME='" + asPathName + "' AND IMAGEX > 0 AND IMAGEY > 0) B";
	}
	else
	{
		asSqlTblB	= "(SELECT PATH_NAME, IMAGEX, IMAGEY FROM TB_DOCUMENT07_PNU WHERE PNU = '" + _asPnu + "' AND IMAGEX > 0 AND IMAGEY > 0) B";
	}

	asCol	= "A.PATH_NAME, A.KIND_CODE, A.KWON_NO, A.LAND_GBN, A.SIDOSGG, A.UMD, A.RI, A.SCALE, A.DOHO_BON, A.DOHO_BU, B.IMAGEX, B.IMAGEY";
	//Where condition
	asSqlWhere = asSqlWhere + "A.PATH_NAME = B.PATH_NAME";
	asSqlOrder = asSqlOrder + "KIND_CODE, DOHO_BON ASC";//201230//
	asSqlQry.sprintf("SELECT %s FROM %s, %s WHERE %s ORDER BY %s", asCol, asSqlTblA, asSqlTblB, asSqlWhere, asSqlOrder);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		//200925//일반,산구분하여 문서구분 필터링//
		AnsiString  asStr	= "";
		int			nLandGbn	= 0;//일반(true), 산(false)
		if(frmMain->m_asSearchPnu.Length() == 19)//일반/산 구분//문서 필터링//
		{
			if(frmMain->m_asSearchPnu.SubString(11, 1) == "2")
				nLandGbn = 2;//산지번//
			else if(frmMain->m_asSearchPnu.SubString(11, 1) == "1")
				nLandGbn = 1;//일반지번//
		}

		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			asPathName = (char*)tempInfo.PATH_NAME;
			asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
			strcpy(tempInfo.PATH_NAME, asPathName.c_str());

			bool bSamed	= false;
			for(int i = 0; i < (int)frmMain->m_ResultDocument07_SUB.size(); i++)
			{
				//기존검색되어 frmMain->m_ResultDocument07에 있는 것과 파일명이 같은게 검색이 되면 무시//
				if( !strcmp(frmMain->m_ResultDocument07_SUB[i].PATH_NAME, tempInfo.PATH_NAME) )
				{
					bSamed = true;
					break;
				}
			}

			//200925//일반,산구분하여 문서구분 필터링//
			asStr = eFunc->funcGetKindCodeToKindName(7, (char*)tempInfo.KIND_CODE);
			if(nLandGbn == 1 && asStr.Pos("임야") > 0)//일반//
			{
				continue;
			}
			else if(nLandGbn == 2 && asStr.Pos("임야") == 0)//산//
			{
				continue;
			}

			if( !bSamed )
			{
				tempInfo.REMARK = 2;
				if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
					frmMain->m_ResultDocument07_SUB.push_back(tempInfo);
				else
					frmMain->m_ResultDocument07.push_back(tempInfo);
			}
			memset(&tempInfo, 0x00, sizeof(DOCUMENT07_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------
//201014//
int __fastcall TfrmSql::funcGetIndexDOCUMENT07PNU(AnsiString _asPathName)
{
	int nIndex = -1;

	for(int i = 0; i < (int)frmMain->m_vDOC07PNU.size(); i++)
	{
		if( !strcmp(frmMain->m_vDOC07PNU[i].PATH_NAME, _asPathName.c_str()) )
		{
			nIndex = i;
			break;
        }
	}

	return nIndex;
}
//---------------------------------------------------------------------------
//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
void __fastcall TfrmSql::funcQrySelect_LAND_INFO_MAPPOINT(bool _bSub, AnsiString _asPnu)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[3][255];
	SQLINTEGER 	m_nVal[3];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "LAND_INFO";
	AnsiString 	asSqlWhere 	= "";
	AnsiString 	asSqlOrder 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 	= "";
	LAND_INFO_STRUCT tempInfo;
	int nIndex = 1;

	//191125//totalsearch호출하는위치로 옮김//frmMain->m_vLANDINFO.clear();
	if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
		frmMain->m_vLANDINFO_SUB.clear();

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.LAND_CD, 	sizeof(tempInfo.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X, 	    sizeof(tempInfo.X), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y, 	    sizeof(tempInfo.Y), 		&m_nVal[nIndex-1]); nIndex++;

	//Where condition
	asSqlWhere = asSqlWhere + "LAND_CD LIKE '" + _asPnu + "%'";
	asSqlOrder = asSqlOrder + "LAND_CD";
	asSqlQry.sprintf("SELECT LAND_CD, X, Y FROM %s WHERE %s ORDER BY %s", asSqlTbl, asSqlWhere, asSqlOrder);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			if(_bSub)//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
				frmMain->m_vLANDINFO_SUB.push_back(tempInfo);
			else
				frmMain->m_vLANDINFO.push_back(tempInfo);
			memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSql::funcQrySelect_LAND_INFO_MAPPOINT_PREPNU(AnsiString _asPnu)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[3][255];
	SQLINTEGER 	m_nVal[3];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "LAND_INFO";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 		= "";
	AnsiString  asSqlSub	= "";
	AnsiString  asSubWhere	= "";
	LAND_INFO_STRUCT tempInfo;
	int nIndex = 1;

	frmMain->m_vLANDINFO.clear();
	frmMain->m_vLANDINFO_SUB.clear();//201227//

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.LAND_CD, 	sizeof(tempInfo.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X, 	    sizeof(tempInfo.X), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y, 	    sizeof(tempInfo.Y), 		&m_nVal[nIndex-1]); nIndex++;

	//SubSql
	asSubWhere = "WHERE LAND_CD < '" + _asPnu + "' ";
	asSubWhere = asSubWhere + " AND LAND_CD LIKE '" + _asPnu.SubString(1, 10) + "%' ";//same umd+ri
	asSqlWhere = "LAND_CD = (SELECT MAX(LAND_CD) FROM LAND_INFO " + asSubWhere + ")";

	//Where condition
	asSqlQry.sprintf("SELECT LAND_CD, X, Y FROM %s WHERE %s", asSqlTbl, asSqlWhere);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	//백남수... 혹시 몰라서
	frmSearch->m_bDoc07Check     = false;
	frmSearch->m_sDoc07DohoCheck = "";
	//////////////////
	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			frmMain->m_vLANDINFO.push_back(tempInfo);
			memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));
			//백남수
			frmSearch->m_bDoc07Check = true;
			///////////////
		};
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//nType 1 : BASE_X, BASE_Y update
//nType 2 : RATIOX, RATIOY update
bool __fastcall TfrmSql::funcQryInsert_DOCUMENT07_BASEXY(int _nType, double _nX, double _nY)
{
	AnsiString 	asSqlTbl 	= "TB_DOCUMENT07";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asPathName 	= "";

	char cCol[4][20] = {"BASE_X", "BASE_Y", "RATIOX", "RATIOY"};

	//Query Column
	if(_nType == 1)
	{
		asSqlCol = asSqlCol + cCol[0] 	+ " = " + _nX + ",";
		asSqlCol = asSqlCol + cCol[1] 	+ " = " + _nY;
	}
	else
	{
		asSqlCol = asSqlCol + cCol[2] 	+ " = " + _nX + ",";
		asSqlCol = asSqlCol + cCol[3] 	+ " = " + _nY;
	}

	asPathName = frmMain->m_asCurrentFilePath;
	asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);

	//Where condition
	asSqlWhere = asSqlWhere + "PATH_NAME = '" + asPathName + "'" ;//
	asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadMemo(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  	asStr     	= "";
	AnsiString  	asSqlQry  	= "";
	bool			bSameTitle 	= false;
	AnsiString      asTitle	  	= "";
	SQLRETURN 		ret;
	MEMOINFO_STRUCT tempMemo;

	memset(&tempMemo, 0x00, sizeof(MEMOINFO_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[16];//210429//#GAGAM44150
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.POI_KEY, 		sizeof(tempMemo.POI_KEY), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.POI_NAME, 		sizeof(tempMemo.POI_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.TITLE, 		sizeof(tempMemo.TITLE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.MEMO, 			sizeof(tempMemo.MEMO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.OWN_NAME, 		sizeof(tempMemo.OWN_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.BATCH_YN, 		sizeof(tempMemo.BATCH_YN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.OPEN_YN, 		sizeof(tempMemo.OPEN_YN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.WRITE_ID, 		sizeof(tempMemo.WRITE_ID), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.WRITE_DT, 		sizeof(tempMemo.WRITE_DT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempMemo.FILE_CNT, 	sizeof(tempMemo.FILE_CNT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempMemo.DATA_CNT, 	sizeof(tempMemo.DATA_CNT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempMemo.X, 			sizeof(tempMemo.X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempMemo.Y, 			sizeof(tempMemo.Y), 		&m_nVal[nIndex-1]); nIndex++;
	//210429//#GAGAM44150
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempMemo.LINECOLOR, 	sizeof(tempMemo.LINECOLOR), &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.GAGAM_X, 		sizeof(tempMemo.GAGAM_X), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempMemo.GAGAM_Y, 		sizeof(tempMemo.GAGAM_Y), 	&m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)qry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempMemo, 0x00, sizeof(MEMOINFO_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		//해당 시군 MBR 안에 있는 데이터만 가져온다//
		//241125//frmMain->m_bJijukLoading is false 상태에서는 m_MBR값이 없어 비교 불가하므로//
		//관련하여 멘트를 처리하자.
		try{
			if( frmMain->m_MBR.xmin == 0 && frmMain->m_MBR.xmax == 0 && frmMain->m_MBR.ymin == 0 && frmMain->m_MBR.ymax == 0 )
			{
				frmMsg->funcMessageDlg("알림:", "공간메모 데이터가 존재합니다. \n[우측 상단] 지적도를 클릭하여 로딩 후 다시 검색해주세요.", 3);
				if(frmMsg->m_bClick == 0)//No
				{
					SQLCloseCursor(m_hStmt);
					return;
				}
			}
		}
		__finally{
			if(tempMemo.X >= frmMain->m_MBR.xmin && tempMemo.X <= frmMain->m_MBR.xmax
			&& tempMemo.Y >= frmMain->m_MBR.ymin && tempMemo.Y <= frmMain->m_MBR.ymax)
			{
				bSameTitle = false;
				asTitle = (char*)tempMemo.TITLE;
				strcpy(tempMemo.TITLE, asTitle.c_str());

				for(int i = 0; i < (int)frmMain->m_ResultMemo.size(); i++)
				{
					if( !strcmp(tempMemo.TITLE, frmMain->m_ResultMemo[i].TITLE) )
					{
						bSameTitle = true;
						break;
					}
				}
				if( !bSameTitle )
					frmMain->m_ResultMemo.push_back(tempMemo);
			}
			memset(&tempMemo, 0x00, sizeof(MEMOINFO_STRUCT));
		}
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocumentMemoBatch(AnsiString _asKeyword)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     = "";
	AnsiString  asSqlQry  = "";
	AnsiString  asWhere   = "";
	SQLRETURN   ret;

	memset(&tempBATCHMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[13];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.POI_KEY, 		sizeof(tempBATCHMEMOINFO.POI_KEY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.POI_NAME, 	sizeof(tempBATCHMEMOINFO.POI_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.TITLE, 		sizeof(tempBATCHMEMOINFO.TITLE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.MEMO, 		sizeof(tempBATCHMEMOINFO.MEMO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.OWN_NAME, 	sizeof(tempBATCHMEMOINFO.OWN_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.BATCH_YN, 	sizeof(tempBATCHMEMOINFO.BATCH_YN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.OPEN_YN, 		sizeof(tempBATCHMEMOINFO.OPEN_YN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.WRITE_ID, 	sizeof(tempBATCHMEMOINFO.WRITE_ID), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempBATCHMEMOINFO.WRITE_DT, 	sizeof(tempBATCHMEMOINFO.WRITE_DT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempBATCHMEMOINFO.FILE_CNT, 	sizeof(tempBATCHMEMOINFO.FILE_CNT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempBATCHMEMOINFO.DATA_CNT, 	sizeof(tempBATCHMEMOINFO.DATA_CNT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempBATCHMEMOINFO.X, 			sizeof(tempBATCHMEMOINFO.X), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempBATCHMEMOINFO.Y, 			sizeof(tempBATCHMEMOINFO.Y), 			&m_nVal[nIndex-1]); nIndex++;

	//200113//asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOINFO + " ORDER BY POI_KEY";
	if( !_asKeyword.IsEmpty() )
		asWhere = " AND TITLE LIKE '%" + _asKeyword.Trim() + "%' ";
	asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOINFO + " WHERE BATCH_YN='Y' " + asWhere + "ORDER BY POI_KEY";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	m_vBATCHMEMOINFO.clear();

	memset(&tempBATCHMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		m_vBATCHMEMOINFO.push_back(tempBATCHMEMOINFO);
		memset(&tempBATCHMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------
//191129
void __fastcall TfrmSql::funcReadDocumentMemoAll()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     = "";
	AnsiString  asSqlQry  = "";
	SQLRETURN ret;

	memset(&tempALLMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[16];//201109//13->16
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.POI_KEY, 		sizeof(tempALLMEMOINFO.POI_KEY), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.POI_NAME, 		sizeof(tempALLMEMOINFO.POI_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.TITLE, 			sizeof(tempALLMEMOINFO.TITLE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.MEMO, 			sizeof(tempALLMEMOINFO.MEMO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.OWN_NAME, 		sizeof(tempALLMEMOINFO.OWN_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.BATCH_YN, 		sizeof(tempALLMEMOINFO.BATCH_YN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.OPEN_YN, 		sizeof(tempALLMEMOINFO.OPEN_YN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.WRITE_ID, 		sizeof(tempALLMEMOINFO.WRITE_ID), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.WRITE_DT, 		sizeof(tempALLMEMOINFO.WRITE_DT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempALLMEMOINFO.FILE_CNT, 		sizeof(tempALLMEMOINFO.FILE_CNT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempALLMEMOINFO.DATA_CNT, 		sizeof(tempALLMEMOINFO.DATA_CNT), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempALLMEMOINFO.X, 			sizeof(tempALLMEMOINFO.X), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempALLMEMOINFO.Y, 			sizeof(tempALLMEMOINFO.Y), 			&m_nVal[nIndex-1]); nIndex++;
	//201109//
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempALLMEMOINFO.LINECOLOR, 	sizeof(tempALLMEMOINFO.LINECOLOR), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.GAGAM_X, 		sizeof(tempALLMEMOINFO.GAGAM_X), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLMEMOINFO.GAGAM_Y, 		sizeof(tempALLMEMOINFO.GAGAM_Y), 	&m_nVal[nIndex-1]); nIndex++;
	//---

	//200113//asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOINFO + " ORDER BY POI_KEY";
	asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOINFO + " WHERE OPEN_YN='Y' OR (OPEN_YN='N' AND WRITE_ID = '" + frmMain->m_asCurrentId.Trim() + "') ORDER BY POI_KEY";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	m_vALLMEMOINFO.clear();
	m_vALLPHOTOINFO.clear();

	memset(&tempALLMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		if(tempALLMEMOINFO.FILE_CNT > 0)//포토//
		{
			m_vALLPHOTOINFO.push_back(tempALLMEMOINFO);
		}
		asStr = (char*)tempALLMEMOINFO.MEMO;
		//200114//일괄등록시에는 <메모>를 입력하지 않는다//그리고 메모/포토에서 메모/영역으로 변경되었기 때문에 메모없어도 주석척리하지 않음//
		//200114//if( !asStr.IsEmpty() )//메모
		{
			m_vALLMEMOINFO.push_back(tempALLMEMOINFO);
		}
		memset(&tempALLMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//TB_MEMO_VECTOR
void __fastcall TfrmSql::funcReadDocumentMemoVector(AnsiString _asPoiKey)
{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	AnsiString  asStr     = "";
//	AnsiString  asWhere	  = "";
//	AnsiString  asSqlQry  = "";
//	SQLRETURN ret;
//	int 	nCount = 0;
//
//	memset(&tMemoPoly, 0x00, sizeof(polyObject));
//	memset(&tempALLVECTORINFO, 0x00, sizeof(MEMOVECTOR_STRUCT));
//	int nIndex = 1;
//
//	SQLINTEGER m_nVal[5];
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempALLVECTORINFO.POI_KEY, 		sizeof(tempALLVECTORINFO.POI_KEY), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempALLVECTORINFO.COUNT, 		sizeof(tempALLVECTORINFO.COUNT), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempALLVECTORINFO.SIZE, 		sizeof(tempALLVECTORINFO.SIZE), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_BINARY,  tempALLVECTORINFO.VECTOR, 		sizeof(tempALLVECTORINFO.X), 		&m_nVal[nIndex-1]); nIndex++;
//
//	asWhere  = "WHERE POI_KEY = '" + _asPoiKey.Trim() + "' ";
//	asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOVECTOR + " + asWhere + "ORDER BY POI_KEY, SEQ";
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	GPoint gPoint;
//	MBR    mMBR;
//
//	mMBR.xmin	= 999999;
//	mMBR.ymin	= 999999;
//	mMBR.xmax	= 0;
//	mMBR.ymax	= 0;
//
//	memset(&tempALLVECTORINFO, 0x00, sizeof(MEMOVECTOR_STRUCT));
//	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
//		gPoint.x = tempALLVECTORINFO.X;
//		gPoint.y = tempALLVECTORINFO.Y;
//		tMemoPoly.m_vPoints.push_back(gPoint);
//
//		if(gPoint.x < mMBR.xmin)	mMBR.xmin = gPoint.x;
//		if(gPoint.x > mMBR.xmax)	mMBR.xmax = gPoint.x;
//		if(gPoint.y < mMBR.ymin)	mMBR.ymin = gPoint.y;
//		if(gPoint.y > mMBR.ymax)	mMBR.ymax = gPoint.y;
//
//		memset(&tempALLVECTORINFO, 0x00, sizeof(MEMOVECTOR_STRUCT));
//	};
//
//	tMemoPoly.m_nNumPoints 	= tMemoPoly.m_vPoints.size();
//	tMemoPoly.m_MBR        	= mMBR;
//	tMemoPoly.m_nID         = m_vMEMOPOLY.size();
//	tMemoPoly.m_nShow		= 1;
//	tMemoPoly.label			= _asPoiKey;//frmSql->m_vALLMEMOINFO[i].POI_KEY;
//	m_vMEMOPOLY.push_back(tMemoPoly);
//	//m_vMEMOPOLY.area			= func_DrawMemoRectAreaValue();
//	//m_vMEMOPOLY.x				= m_pgMemoRectCenter = ptCenter;
//	//m_vMEMOPOLY.y				= m_pgMemoRectCenter = ptCenter;
//
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocThumbPathList(int _nDocNo, AnsiString _asKwonNo, int _nGroupNo, int _nGroupNo1, AnsiString _asPath)
{
	frmMain->funcInitThumb();//200808//

	if(frmPreview->Showing)//250429//
		frmPreview->funcInitThumb();


	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//181227//AnsiString mSqlQry;
	SQLRETURN ret;
	AnsiString asSql 		= "";
	AnsiString asTable 		= "";
	AnsiString asCol  		= "";
	AnsiString asColumn		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPathName 	= _asPath;
	DOCUMENT_PATHLIST_STRUCT	tempPathList;

	asTable.sprintf("TB_DOCUMENT%02d", _nDocNo);
	//201015//
	if(_nDocNo == 2)
		asColumn = "KIND_CODE, PAGE_NO, DOHO, PATH_NAME";
	else if(_nDocNo == 7)
		asColumn = "KIND_CODE, PAGE_NO, DOHO_BON, PATH_NAME";
	else
		asColumn = "KIND_CODE, PAGE_NO, PATH_NAME";

	asCol = "DISTINCT " + asColumn;

	frmMain->m_vThumbPathList.clear();

	//201015//
	if(_nDocNo != 2 && _nDocNo != 7)
	{
		SQLINTEGER m_nVal[3];

		memset(m_nVal, 0x00, sizeof(m_nVal));
		memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));

		SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, tempPathList.KIND_CODE       , sizeof(tempPathList.KIND_CODE)       , &m_nVal[0]);
		SQLBindCol(m_hStmt, 2,  SQL_C_CHAR, tempPathList.PAGE_NO         , sizeof(tempPathList.PAGE_NO)         , &m_nVal[1]);
		SQLBindCol(m_hStmt, 3,  SQL_C_CHAR, tempPathList.PATH_NAME       , sizeof(tempPathList.PATH_NAME)       , &m_nVal[2]);
	}
	else
	{
		SQLINTEGER m_nVal[4];

		memset(m_nVal, 0x00, sizeof(m_nVal));
		memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));

		SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, tempPathList.KIND_CODE       , sizeof(tempPathList.KIND_CODE)       , &m_nVal[0]);
		SQLBindCol(m_hStmt, 2,  SQL_C_CHAR, tempPathList.PAGE_NO         , sizeof(tempPathList.PAGE_NO)         , &m_nVal[1]);
		SQLBindCol(m_hStmt, 3,  SQL_C_CHAR, tempPathList.DOHO            , sizeof(tempPathList.DOHO)            , &m_nVal[2]);
		SQLBindCol(m_hStmt, 4,  SQL_C_CHAR, tempPathList.PATH_NAME       , sizeof(tempPathList.PATH_NAME)       , &m_nVal[3]);
	}

	if(_nDocNo == 1)
	{
		asOrderBy = "PATH_NAME ASC";//M//191110
		if( !_asKwonNo.IsEmpty() )
			asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);
		if( !asWhere.IsEmpty() )
			asWhere = asWhere + " AND";

		//201221//이동결의서(그룹1만 처리(Default) / 그룹1,2 처리)
		if(frmMain->INIUSERSETINFO.DOC01GROUP == 1)
		{
			asWhere = asWhere + " GROUP_NO = " + IntToStr(_nGroupNo);
		}
		else
		{
//230518//#DOC01_THUMB_GROUP//
//OLD//
//			asWhere = asWhere + " ((GROUP_NO = " + IntToStr(_nGroupNo) + " AND GROUP_NO1 = " + IntToStr(_nGroupNo1) + ")";
//			asWhere = asWhere + " OR (GROUP_NO = " + IntToStr(_nGroupNo) + " AND KIND_CODE='12')";
//			asWhere = asWhere + " OR (GROUP_NO = " + IntToStr(_nGroupNo) + " AND GROUP_NO1 = 777))";//200326//구비서류가 그룹2의 1, 2, 3번 데이터 모두에 보여줘야 할 때//명재씨Req//
//NEW//
			asWhere = asWhere + " GROUP_NO = " + IntToStr(_nGroupNo) + " AND";
			asWhere = asWhere + " (GROUP_NO1 = " + IntToStr(_nGroupNo1) + " OR KIND_CODE='12' OR GROUP_NO1 = 777)";//200326//구비서류가 그룹2의 1, 2, 3번 데이터 모두에 보여줘야 할 때//명재씨Req//
		}

		asWhere = asWhere + " AND PATH_NAME IS NOT NULL";
	}
	else if((_nDocNo >= 2 && _nDocNo <= 4) || _nDocNo == 6 || (_nDocNo >=8 && _nDocNo <= 13) || _nDocNo == 17)
	{
		asOrderBy = "PATH_NAME ASC";//M//191110
		if( !_asKwonNo.IsEmpty() )
			asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);
		if( !asWhere.IsEmpty() )
			asWhere = asWhere + " AND ";

//=================================================
//[REQ_260715]1.DB 구조 변경//#DOC02_GROUP//
		if(_nDocNo == 2)
		{
			if( _nGroupNo > 0 )
			{
				asWhere.sprintf("GROUP_NO = %d", _nGroupNo);
				asWhere = asWhere + " AND ";
			}
		}
//=================================================
//230502//#DOC04_GROUP//
		else if(_nDocNo == 4)
		{
			if( _nGroupNo > 0 )
			{
				asWhere.sprintf("REC_NO = '%d'", _nGroupNo);
				asWhere = asWhere + " AND ";
			}
        }
//=================================================

		asPathName	= ExtractFilePath(asPathName);
		asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);
		//asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() +"'";
		asWhere = asWhere + "PATH_NAME LIKE '" + asPathName.Trim() +"%'";
	}
	else if(_nDocNo == 7)
	{
		asOrderBy = "PATH_NAME ASC";
		if( !_asKwonNo.IsEmpty() )
			asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);
		if( !asWhere.IsEmpty() )
			asWhere = asWhere + " AND ";
		asPathName	= ExtractFilePath(asPathName);
		asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);
		//asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() +"'";
		asWhere = asWhere + "PATH_NAME LIKE '" + asPathName.Trim() +"%'";
	}
	else if(_nDocNo == 5 || _nDocNo == 14 || _nDocNo == 15)
	{
		asOrderBy = "PATH_NAME ASC";
		if( !_asKwonNo.IsEmpty() )
			asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);
		if( !asWhere.IsEmpty() )
			asWhere = asWhere + " AND";
		asWhere = asWhere + " GROUP_NO = " + _nGroupNo;
		asWhere = asWhere + " AND (GROUP_NO1 = " + _nGroupNo1 + " OR GROUP_NO1 = 1)";
		asWhere = asWhere + " AND PATH_NAME IS NOT NULL";
	}
	else if(_nDocNo == 18)//좌표계산부//
	{
		asOrderBy = "PATH_NAME ASC";//M//191110
		if( !_asKwonNo.IsEmpty() )
			asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);

		if(_nGroupNo != 0)
		{
			if( asWhere.IsEmpty() )
				asWhere = asWhere + "GROUP_NO = " + _nGroupNo;
			else
				asWhere = asWhere + " AND GROUP_NO = " + _nGroupNo;
		}
		asPathName	= ExtractFilePath(asPathName);
		asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);
		if( asWhere.IsEmpty() )
			asWhere = asWhere + "PATH_NAME LIKE '" + asPathName.Trim() +"%'";
			//asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() +"'";
		else
			asWhere = asWhere + " AND PATH_NAME LIKE '" + asPathName.Trim() +"%'";
			//asWhere = asWhere + " AND SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() +"'";
	}
	else if(_nDocNo == 20)//가감대장//250326//[BugFixed]
	{
		asOrderBy = "PATH_NAME ASC";
		if( !_asKwonNo.IsEmpty() )
			asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);

		if(_nGroupNo != 0)
		{
			AnsiString  asGagamNo	= "";
			asGagamNo.sprintf("%05d", _nGroupNo);
			if( !asWhere.IsEmpty() )	asWhere += " AND ";
			asWhere += "GAGAM_NO = '" + asGagamNo + "'";
		}
		asPathName	= ExtractFilePath(asPathName);
		asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);
		if( asWhere.IsEmpty() )
			asWhere = asWhere + "PATH_NAME LIKE '" + asPathName.Trim() +"%'";
		else
			asWhere = asWhere + " AND PATH_NAME LIKE '" + asPathName.Trim() +"%'";
	}

	if(_nDocNo ==8)//[조건추가]구대장 PNU//200304
	{
		if( !asWhere.IsEmpty() )
			asWhere = asWhere + " AND PNU = '" + frmMain->m_asSearchPnu + "'";
	}

	asSql.sprintf("SELECT %s FROM %s WHERE %s ORDER BY %s", asCol, asTable, asWhere, asOrderBy);

	frmSearch->funcSaveLog(0, 0, "");

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempPathList.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempPathList.PATH_NAME, asPathName.c_str());

		if(memcmp(_asPath.c_str(), tempPathList.PATH_NAME, strlen(tempPathList.PATH_NAME)) == 0)//same path_name
			frmMain->m_nThumbPathIndex = frmMain->m_vThumbPathList.size();//current count = current image index

		strcpy(tempPathList.KWON_NO, _asKwonNo.c_str());//200301

		frmMain->m_vThumbPathList.push_back(tempPathList);
		memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));
	};

	frmSearch->funcSaveLog(7, 1, asSql);

	if(frmMain->m_vThumbPathList.size() == 1)//자기자신파일만 있다면 thumbnail 보여줄 필요 없음//
	{
		frmMain->m_vThumbPathList.clear();
		frmMain->m_vThumbDocKind.clear();
	}


    //250430//썸네일 문서구분 가져오기//
	//SELECT KIND_CODE, KIND_NAME FROM cd_kind WHERE TASK_CODE='002' AND KIND_CODE IN (SELECT DISTINCT KIND_CODE FROM tb_document02 WHERE PATH_NAME LIKE 'DOCUMENT02/G0420%' GROUP BY KIND_CODE);
	AnsiString  asSqlQry2	= "";
	AnsiString  asTaskCode	= "";
	asTaskCode.sprintf("TASK_CODE = '%03d'", _nDocNo);
	asSqlQry2 = "SELECT KIND_CODE, KIND_NAME FROM CD_KIND WHERE " + asTaskCode + " AND KIND_CODE IN (SELECT DISTINCT KIND_CODE FROM " + asTable + " WHERE " + asWhere + " GROUP BY KIND_CODE)";
	funcReadThumbDocKindList(asSqlQry2);



	//	frmMain->m_nThumbPathIndex = eFunc->funcGetDocThumbPathListIndex(_asPath);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//220208//44200.33024(호산리 산20)검색 > 폐쇄임야도&지적원도 클릭하면 Error발생하는 문제 수정//
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if(frmMain->m_vThumbPathList.size() > 0 && frmMain->m_nThumbPathIndex > -1)//220208/if(frmMain->m_nThumbPathIndex > -1)
	{
		frmMain->funcProcessThumb();
		frmMain->funcShowCurrentThumbLabel();
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------


//250429//[Add]미리보기-필터링//
void __fastcall TfrmSql::funcReadThumbDocKindList(AnsiString _asSqlQry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLRETURN ret;
	THUMBNAIL_DOCKIND_STRUCT	tempDocKind;
	SQLINTEGER m_nVal[2];

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocKind, 0x00, sizeof(THUMBNAIL_DOCKIND_STRUCT));

	SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, tempDocKind.KIND_CODE	, sizeof(tempDocKind.KIND_CODE)		, &m_nVal[0]);
	SQLBindCol(m_hStmt, 2,  SQL_C_CHAR, tempDocKind.KIND_NAME	, sizeof(tempDocKind.KIND_NAME)     , &m_nVal[1]);

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)_asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	frmPreview->cboPreviewDocKind->Items->Clear();//Name//
	frmPreview->cboPreviewDocKind2->Items->Clear();//Code//
	frmPreview->cboPreviewDocKind->Items->Add("전체");
	frmPreview->cboPreviewDocKind2->Items->Add("");

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDocKind, 0x00, sizeof(THUMBNAIL_DOCKIND_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		frmPreview->cboPreviewDocKind->Items->Add(tempDocKind.KIND_NAME);
		frmPreview->cboPreviewDocKind2->Items->Add(tempDocKind.KIND_CODE);
		memset(&tempDocKind, 0x00, sizeof(THUMBNAIL_DOCKIND_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//250515//문서구분이 1개라 해도 그냥 표시- 데이터 유동적으로 콤보박스를 표시하고 안하고를 결정하면 UI 일관성을 위해//
//	if(frmPreview->cboPreviewDocKind->Items->Count == 2)
//		frmPreview->cboPreviewDocKind->Items->Clear();//Name//
//	else
		frmPreview->cboPreviewDocKind->ItemIndex = 0;
}
//---------------------------------------------------------------------------





void __fastcall TfrmSql::funcReadDocFTPPathList(int _nDocNo, AnsiString _asKwonNo, int _nGroupNo, int _nGroupNo1, AnsiString _asPath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER m_nVal[3];
	//181227//AnsiString mSqlQry;
	SQLRETURN ret;
	AnsiString asSql 		= "";
	AnsiString asTable 		= "";
	AnsiString asCol  		= "";
	AnsiString asColumn		= "";
	AnsiString asWhere      = "";
	AnsiString asOrderBy 	= "";
	AnsiString asPathName 	= _asPath;
	DOCUMENT_PATHLIST_STRUCT	tempPathList;

	asTable.sprintf("TB_DOCUMENT%02d", _nDocNo);
	asColumn = "KIND_CODE, PAGE_NO, PATH_NAME";

	asCol = "DISTINCT " + asColumn;

	frmMain->funcInitPrevNext();

	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, tempPathList.KIND_CODE       , sizeof(tempPathList.KIND_CODE)       , &m_nVal[0]);
	SQLBindCol(m_hStmt, 2,  SQL_C_CHAR, tempPathList.PAGE_NO         , sizeof(tempPathList.PAGE_NO)         , &m_nVal[1]);
	SQLBindCol(m_hStmt, 3,  SQL_C_CHAR, tempPathList.PATH_NAME       , sizeof(tempPathList.PATH_NAME)       , &m_nVal[2]);

	asOrderBy = "PATH_NAME ASC";//M//191110

	asWhere.sprintf("KWON_NO = '%s'", _asKwonNo);
	asWhere = asWhere + " AND PATH_NAME IS NOT NULL";

	asPathName	= ExtractFilePath(asPathName);
	asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);
	asWhere = asWhere + " AND PATH_NAME LIKE '" + asPathName.Trim() +"%'";

	asSql.sprintf("SELECT %s FROM %s WHERE %s ORDER BY %s", asCol, asTable, asWhere, asOrderBy);
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		memcpy(tempPathList.KWON_NO, _asKwonNo.c_str(), sizeof(tempPathList.KWON_NO));//200301
		strcpy(tempPathList.PATH_NAME, eFunc->funcGetDBtoLocalPath((char*)tempPathList.PATH_NAME).c_str());
//		asPathName = (char*)tempPathList.PATH_NAME;
//		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//		strcpy(tempPathList.PATH_NAME, asPathName.c_str());
		frmMain->m_vFTPPathList.push_back(tempPathList);
		memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));
	};

	if(frmMain->m_vFTPPathList.size() == 1)//자기자신파일만 있다면 이전/다음 보여줄 필요 없음//
		frmMain->m_vFTPPathList.clear();

	frmMain->m_nFTPPathIndex = eFunc->funcGetDocFTPPathListIndex(_asPath);
	//260625//TEST//frmMain->funcInitPrevNextBar((frmMain->m_nFTPPathIndex > -1) ? (true):(false));
	frmMain->m_bVisiblePrevNextBar = (frmMain->m_nFTPPathIndex > -1) ? (true):(false);
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//200204//notused//
//void __fastcall TfrmSql::funcReadDoc07PathList(AnsiString _asPathName)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	SQLINTEGER m_nVal[2];
//	SQLRETURN ret;
//	AnsiString asSql 		= "";
//	AnsiString asTable 		= "TB_DOCUMENT07";
//	AnsiString asCol  		= "ROLL_NO, PATH_NAME";
//	AnsiString asWhere      = "";
//	AnsiString asOrderBy 	= "PATH_NAME ASC";
//	AnsiString asPathName   = "";
//	AnsiString asSqlSub 	= "";
//	DOCUMENT_PATHLIST_STRUCT	tempPathList;
//
//	frmMain->m_ResultDocPathList.clear();
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//
//	SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, tempPathList.KWON_NO         , sizeof(tempPathList.KWON_NO)         , &m_nVal[0]);
//	SQLBindCol(m_hStmt, 2,  SQL_C_CHAR, tempPathList.PATH_NAME       , sizeof(tempPathList.PATH_NAME)       , &m_nVal[1]);
//
//
//	asPathName = ExtractFilePath(_asPathName);
//	asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);
//	asWhere = asWhere + "PATH_NAME LIKE '" + asPathName.Trim() +"%'";
//
//	asSql.sprintf("SELECT %s FROM %s WHERE %s ORDER BY %s", asCol, asTable, asWhere, asPathName, asOrderBy);
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));
//	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
//	{
//		if(memcmp(_asPathName.c_str(), tempPathList.PATH_NAME, strlen(tempPathList.PATH_NAME)) == 0)//same path_name
//			frmMain->m_ResultDocPathIndex = frmMain->m_ResultDocPathList.size();//current count = current image index
//
//		frmMain->m_ResultDocPathList.push_back(tempPathList);//doc07
//		memset(&tempPathList, 0x00, sizeof(DOCUMENT_PATHLIST_STRUCT));
//	};
//
//	frmMain->funcSetPrevNextBar();
//
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//}
////---------------------------------------------------------------------------

void __fastcall TfrmSql::funcQrySelect_LAND_INFO()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[3][255];
	SQLINTEGER 	m_nVal[3];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "LAND_INFO";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asCol 	= "";
	LAND_INFO_STRUCT tempInfo;
	int nIndex = 1;

	frmMain->m_vSPACELANDINFO.clear();//

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempInfo.LAND_CD, 	sizeof(tempInfo.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.X, 	    sizeof(tempInfo.X), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempInfo.Y, 	    sizeof(tempInfo.Y), 		&m_nVal[nIndex-1]); nIndex++;

	//Where condition
	asSqlWhere = asSqlWhere + " " + frmMain->m_pgSpaceRectSP.x + " < X AND X < " + frmMain->m_pgSpaceRectEP.x;
	asSqlWhere = asSqlWhere + " AND " + frmMain->m_pgSpaceRectSP.y + " < Y AND Y < " + frmMain->m_pgSpaceRectEP.y;
	asSqlQry.sprintf("SELECT LAND_CD, X, Y FROM %s WHERE %s", asSqlTbl, asSqlWhere);

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}
	else {
		while (SQLFetch(m_hStmt) != SQL_NO_DATA)
		{
			frmMain->m_vSPACELANDINFO.push_back(tempInfo);
			memset(&tempInfo, 0x00, sizeof(LAND_INFO_STRUCT));
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcSelectPnuDoc01(AnsiString qry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	frmMain->m_SelectPnuDoc01.clear();

	AnsiString asPathName = "";
	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	DOCUMENT01_STRUCT	tempDocument01;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));
	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.ROLL_NO       , sizeof(tempDocument01.ROLL_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.FRAME_NO      , sizeof(tempDocument01.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.SR_NO         , sizeof(tempDocument01.SR_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.KIND_CODE      , sizeof(tempDocument01.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.KWON_NO        , sizeof(tempDocument01.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PAGE_NO        , sizeof(tempDocument01.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.SUBMIT_YEAR    , sizeof(tempDocument01.SUBMIT_YEAR)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PRCS_DATE      , sizeof(tempDocument01.PRCS_DATE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.MEASURE_TYPE   , sizeof(tempDocument01.MEASURE_TYPE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.GROUP_NO      , sizeof(tempDocument01.GROUP_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument01.GROUP_NO1     , sizeof(tempDocument01.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.BF_PNU   	   , sizeof(tempDocument01.BF_PNU)   	   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.AF_PNU         , sizeof(tempDocument01.AF_PNU)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument01.PATH_NAME      , sizeof(tempDocument01.PATH_NAME)      , &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDocument01.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument01.PATH_NAME, asPathName.c_str());

		frmMain->m_SelectPnuDoc01.push_back(tempDocument01);
		memset(&tempDocument01, 0x00, sizeof(DOCUMENT01_STRUCT));
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//void __fastcall TfrmSql::funcSelectPnuDoc07(AnsiString qry)
//{
//	m_SelectPnuDoc07.clear();
//
//	SQLRETURN ret;
//
//	memset(&frmMain->tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
//	int nIndex = 1;
//
//	SQLINTEGER m_nVal[15];
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &frmMain->tempDocument07.ROLL_NO     , sizeof(frmMain->tempDocument07.ROLL_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &frmMain->tempDocument07.FRAME_NO    , sizeof(frmMain->tempDocument07.FRAME_NO)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &frmMain->tempDocument07.SR_NO       , sizeof(frmMain->tempDocument07.SR_NO)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.KIND_CODE    , sizeof(frmMain->tempDocument07.KIND_CODE)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.KIND_NAME    , sizeof(frmMain->tempDocument07.KIND_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.HJDON_NAME   , sizeof(frmMain->tempDocument07.HJDON_NAME)   , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &frmMain->tempDocument07.POS_X       , sizeof(frmMain->tempDocument07.POS_X)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &frmMain->tempDocument07.POS_Y       , sizeof(frmMain->tempDocument07.POS_Y)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.KWON_NO      , sizeof(frmMain->tempDocument07.KWON_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.PAGE_NO      , sizeof(frmMain->tempDocument07.PAGE_NO)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.DOHO         , sizeof(frmMain->tempDocument07.DOHO)         , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.DOHO_SUB     , sizeof(frmMain->tempDocument07.DOHO_SUB)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.SCALE        , sizeof(frmMain->tempDocument07.SCALE)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.PNU    		, sizeof(frmMain->tempDocument07.PNU)    	  , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, frmMain->tempDocument07.PATH_NAME    , sizeof(frmMain->tempDocument07.PATH_NAME)    , &m_nVal[nIndex-1]); nIndex++;
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)qry.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	memset(&frmMain->tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
//	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
//		m_SelectPnuDoc07.push_back(frmMain->tempDocument07);
//		memset(&frmMain->tempDocument07, 0x00, sizeof(DOCUMENT07_STRUCT));
//	};
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//}
////---------------------------------------------------------------------------

//***************************************************************************
// Thumbnail 이미지의 DB 정보//
//***************************************************************************
void __fastcall TfrmSql::funcReadDocDBInfo(int _nDocNo, AnsiString _asKwon, AnsiString _asFilePath)
{
	switch(_nDocNo)
	{
		case  1:		funcReadDoc01DBInfo(_asKwon, _asFilePath);		break;
		case  2:		funcReadDoc02DBInfo(_asKwon, _asFilePath);		break;
		case  3:		funcReadDoc03DBInfo(_asKwon, _asFilePath);		break;
		case  4:		funcReadDoc04DBInfo(_asKwon, _asFilePath);		break;
		case  5:		funcReadDoc05DBInfo(_asKwon, _asFilePath);		break;
		case  6:		funcReadDoc06DBInfo(_asKwon, _asFilePath);		break;
		case  7:		funcReadDoc07DBInfo(_asKwon, _asFilePath);		break;
		case  8:		funcReadDoc08DBInfo(_asKwon, _asFilePath);		break;
		case  9:		funcReadDoc09DBInfo(_asKwon, _asFilePath);		break;
		case 11:		funcReadDoc11DBInfo(_asKwon, _asFilePath);		break;
		case 12:		funcReadDoc12DBInfo(_asKwon, _asFilePath);		break;
		case 13:		funcReadDoc13DBInfo(_asKwon, _asFilePath);		break;
		case 14:		funcReadDoc14DBInfo(_asKwon, _asFilePath);		break;
		case 15:		funcReadDoc15DBInfo(_asKwon, _asFilePath);		break;
		case 17:		funcReadDoc17DBInfo(_asKwon, _asFilePath);		break;
		case 18:		funcReadDoc18DBInfo(_asKwon, _asFilePath);		break;
		case 20:		funcReadDoc20DBInfo(_asKwon, _asFilePath);		break;//231021//GAGAMLAYER in LandArchive
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc01DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc01DBInfo.clear();
	m_ResultDoc01DBCount = 0;

	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT01 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT01_STRUCT 		tempDoc01;
	int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc01, 0x00, sizeof(DOCUMENT01_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc01.ROLL_NO       , sizeof(tempDoc01.ROLL_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc01.FRAME_NO      , sizeof(tempDoc01.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc01.SR_NO         , sizeof(tempDoc01.SR_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.KIND_CODE      , sizeof(tempDoc01.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.KWON_NO        , sizeof(tempDoc01.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.PAGE_NO        , sizeof(tempDoc01.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.SUBMIT_YEAR    , sizeof(tempDoc01.SUBMIT_YEAR)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.PRCS_DATE      , sizeof(tempDoc01.PRCS_DATE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.MEASURE_TYPE   , sizeof(tempDoc01.MEASURE_TYPE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc01.GROUP_NO      , sizeof(tempDoc01.GROUP_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc01.GROUP_NO1     , sizeof(tempDoc01.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.BF_PNU   	  , sizeof(tempDoc01.BF_PNU)   		 , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.AF_PNU      	  , sizeof(tempDoc01.AF_PNU)      	 , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc01.PATH_NAME      , sizeof(tempDoc01.PATH_NAME)      , &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc01, 0x00, sizeof(DOCUMENT01_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc01.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc01.PATH_NAME, asPathName.c_str());
		m_ResultDoc01DBInfo.push_back(tempDoc01);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc02DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc02DBInfo.clear();
	m_ResultDoc02DBCount = 0;

	SQLINTEGER m_nVal[22];//#DOC02_GROUP
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT02 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT02_STRUCT 		tempDoc02;
	int nIndex              = 1;
 	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc02, 0x00, sizeof(DOCUMENT02_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.ROLL_NO			, sizeof(tempDoc02.ROLL_NO)			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.FRAME_NO       	, sizeof(tempDoc02.FRAME_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.KWON_NO         	, sizeof(tempDoc02.KWON_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.PAGE_NO         	, sizeof(tempDoc02.PAGE_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.DOHO            	, sizeof(tempDoc02.DOHO)            , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.DOHO_SUB        	, sizeof(tempDoc02.DOHO_SUB)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_DAY        	, sizeof(tempDoc02.SURV_DAY)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_NAME       	, sizeof(tempDoc02.SURV_NAME)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.INSPCT_DAY      	, sizeof(tempDoc02.INSPCT_DAY)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.INSPCT_NAME     	, sizeof(tempDoc02.INSPCT_NAME)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_YEAR       	, sizeof(tempDoc02.SURV_YEAR)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_ITEM       	, sizeof(tempDoc02.SURV_ITEM)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.RDSCALE_CODE    	, sizeof(tempDoc02.RDSCALE_CODE)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.BF_PNU   	   	, sizeof(tempDoc02.BF_PNU)   	   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.AF_PNU      	   	, sizeof(tempDoc02.AF_PNU)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.PATH_NAME       	, sizeof(tempDoc02.PATH_NAME)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.KIND_CODE       	, sizeof(tempDoc02.KIND_CODE)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SUBMIT_DATE     	, sizeof(tempDoc02.SUBMIT_DATE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.POS_X        	, sizeof(tempDoc02.POS_X)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.POS_Y       	, sizeof(tempDoc02.POS_Y)        	, &m_nVal[nIndex-1]); nIndex++;
	//#DOC02_GROUP//
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.GROUP_NO        , sizeof(tempDoc02.PRCS_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.PRCS_NO       	, sizeof(tempDoc02.PRCS_NO)        	, &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc02, 0x00, sizeof(DOCUMENT02_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc02.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc02.PATH_NAME, asPathName.c_str());
		m_ResultDoc02DBInfo.push_back(tempDoc02);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//200424//DOC02GROUP
//void __fastcall TfrmSql::funcReadDoc02DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
//{
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//
//	m_ResultDoc02DBInfo.clear();
//	m_ResultDoc02DBCount = 0;
//
//	SQLINTEGER m_nVal[20];
//	SQLRETURN ret;
//	AnsiString asSql        = "";
//	AnsiString asTable      = "TB_DOCUMENT02 ";
//	AnsiString asWhere      = "WHERE ";
//	DOCUMENT02_STRUCT 		tempDoc02;
//	int nIndex              = 1;
// 	AnsiString asPathName   = "";
//
//	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);
//
//	memset(m_nVal, 0x00, sizeof(m_nVal));
//	memset(&tempDoc02, 0x00, sizeof(DOCUMENT02_STRUCT));
//
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.ROLL_NO			, sizeof(tempDoc02.ROLL_NO)			, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.FRAME_NO       	, sizeof(tempDoc02.FRAME_NO)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.KIND_CODE       	, sizeof(tempDoc02.KIND_CODE)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.KWON_NO         	, sizeof(tempDoc02.KWON_NO)         , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.PAGE_NO         	, sizeof(tempDoc02.PAGE_NO)         , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_DAY        	, sizeof(tempDoc02.SURV_DAY)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_NAME       	, sizeof(tempDoc02.SURV_NAME)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.INSPCT_DAY      	, sizeof(tempDoc02.INSPCT_DAY)      , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.INSPCT_NAME     	, sizeof(tempDoc02.INSPCT_NAME)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SUBMIT_DATE     	, sizeof(tempDoc02.SUBMIT_DATE)     , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.SURV_ITEM       	, sizeof(tempDoc02.SURV_ITEM)       , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.GROUP_NO       	, sizeof(tempDoc02.GROUP_NO)		, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.DOHO            	, sizeof(tempDoc02.DOHO)            , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.DOHO_SUB        	, sizeof(tempDoc02.DOHO_SUB)        , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.RDSCALE_CODE    	, sizeof(tempDoc02.RDSCALE_CODE)    , &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.POS_X        	, sizeof(tempDoc02.POS_X)         	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc02.POS_Y       	, sizeof(tempDoc02.POS_Y)        	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.BF_PNU   	   	, sizeof(tempDoc02.BF_PNU)   	   	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.AF_PNU      	   	, sizeof(tempDoc02.AF_PNU)      	, &m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc02.PATH_NAME       	, sizeof(tempDoc02.PATH_NAME)       , &m_nVal[nIndex-1]); nIndex++;
//
//	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
//	asSql = "SELECT * FROM " + asTable + asWhere;
//
//	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
//	ret = SQLExecute(m_hStmt);
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
//	{
//		SQLCloseCursor(m_hStmt);
//		return;
//	}
//
//	memset(&tempDoc02, 0x00, sizeof(DOCUMENT02_STRUCT));
//	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
//	{
//		asPathName = (char*)tempDoc02.PATH_NAME;
//		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
//		strcpy(tempDoc02.PATH_NAME, asPathName.c_str());
//		m_ResultDoc02DBInfo.push_back(tempDoc02);
//		break;//200205//DBInfo에 1개만 넣는다//
//	};
//	if(m_hStmt) SQLCloseCursor(m_hStmt);
//}
////---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc03DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc03DBInfo.clear();
	m_ResultDoc03DBCount = 0;

	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT03 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT03_STRUCT 		tempDoc03;
	int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc03, 0x00, sizeof(DOCUMENT03_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc03.ROLL_NO        , sizeof(tempDoc03.ROLL_NO)			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc03.FRAME_NO       , sizeof(tempDoc03.FRAME_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc03.SR_NO          , sizeof(tempDoc03.SR_NO)          	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.KIND_CODE       , sizeof(tempDoc03.KIND_CODE)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.KWON_NO         , sizeof(tempDoc03.KWON_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.PAGE_NO         , sizeof(tempDoc03.PAGE_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.SURV_YEAR       , sizeof(tempDoc03.SURV_YEAR)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.SURV_DAY        , sizeof(tempDoc03.SURV_DAY)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.SURV_NAME       , sizeof(tempDoc03.SURV_NAME)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.INSPCT_DAY      , sizeof(tempDoc03.INSPCT_DAY)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.INSPCT_NAME     , sizeof(tempDoc03.INSPCT_NAME)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.BF_PNU   	   , sizeof(tempDoc03.BF_PNU)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.AF_PNU      	   , sizeof(tempDoc03.AF_PNU)      		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc03.PATH_NAME       , sizeof(tempDoc03.PATH_NAME)       	, &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc03, 0x00, sizeof(DOCUMENT03_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc03.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc03.PATH_NAME, asPathName.c_str());
		m_ResultDoc03DBInfo.push_back(tempDoc03);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc04DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc04DBInfo.clear();
	m_ResultDoc04DBCount = 0;

	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT04 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT04_STRUCT 		tempDoc04;
	int nIndex              = 1;
 	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc04, 0x00, sizeof(DOCUMENT04_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc04.ROLL_NO        , sizeof(tempDoc04.ROLL_NO)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.PAGE_NO         , sizeof(tempDoc04.PAGE_NO)         	, &m_nVal[nIndex-1]); nIndex++;
	//181231//SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc04.PAGE_NO      , sizeof(tempDoc04.PAGE_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.KWON_NO         , sizeof(tempDoc04.KWON_NO)			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.REQ_YEAR        , sizeof(tempDoc04.REQ_YEAR)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.REQ_DAY         , sizeof(tempDoc04.REQ_DAY)         	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.OWN_NAME        , sizeof(tempDoc04.OWN_NAME)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.OWN_REG_NO      , sizeof(tempDoc04.OWN_REG_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.ISSUE_NO        , sizeof(tempDoc04.ISSUE_NO)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.APROV_STATUS    , sizeof(tempDoc04.APROV_STATUS)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.LAW_NO          , sizeof(tempDoc04.LAW_NO)          	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.KIND_CODE       , sizeof(tempDoc04.KIND_CODE)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.REC_NO          , sizeof(tempDoc04.REC_NO)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.PATH_NAME       , sizeof(tempDoc04.PATH_NAME)       	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc04.PNU             , sizeof(tempDoc04.PNU)       		, &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc04, 0x00, sizeof(DOCUMENT04_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc04.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc04.PATH_NAME, asPathName.c_str());
		m_ResultDoc04DBInfo.push_back(tempDoc04);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc05DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc05DBInfo.clear();
	m_ResultDoc05DBCount = 0;

	SQLINTEGER m_nVal[14];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT05 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT05_STRUCT 		tempDoc05;
	int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc05, 0x00, sizeof(DOCUMENT05_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc05.ROLL_NO       , sizeof(tempDoc05.ROLL_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc05.FRAME_NO      , sizeof(tempDoc05.FRAME_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc05.SR_NO         , sizeof(tempDoc05.SR_NO)          , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.KIND_CODE      , sizeof(tempDoc05.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.KWON_NO        , sizeof(tempDoc05.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.PAGE_NO        , sizeof(tempDoc05.PAGE_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.SUBMIT_YEAR    , sizeof(tempDoc05.SUBMIT_YEAR)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.PRCS_DATE      , sizeof(tempDoc05.PRCS_DATE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.MEASURE_TYPE   , sizeof(tempDoc05.MEASURE_TYPE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc05.GROUP_NO      , sizeof(tempDoc05.GROUP_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc05.GROUP_NO1     , sizeof(tempDoc05.GROUP_NO1)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.BF_PNU   	  , sizeof(tempDoc05.BF_PNU)   		 , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.AF_PNU      	  , sizeof(tempDoc05.AF_PNU)      	 , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc05.PATH_NAME      , sizeof(tempDoc05.PATH_NAME)      , &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc05, 0x00, sizeof(DOCUMENT05_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc05.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc05.PATH_NAME, asPathName.c_str());
		m_ResultDoc05DBInfo.push_back(tempDoc05);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc06DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc06DBInfo.clear();
	m_ResultDoc06DBCount = 0;

	SQLINTEGER m_nVal[10];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT06 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT06_STRUCT 		tempDoc06;
	int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc06, 0x00, sizeof(DOCUMENT06_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.KIND_CODE    , sizeof(tempDoc06.KIND_CODE)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.ZONE_CODE    , sizeof(tempDoc06.ZONE_CODE)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.COMP_YEAR    , sizeof(tempDoc06.COMP_YEAR)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.SERIAL_NUM   , sizeof(tempDoc06.SERIAL_NUM) 		, &m_nVal[nIndex-1]); nIndex++;
	//181231//SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.ROLL_NUM   , sizeof(tempDoc06.ROLL_NUM)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc06.ROLL_NO     , sizeof(tempDoc06.ROLL_NO)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.KWON_NO      , sizeof(tempDoc06.KWON_NO)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.PAGE_NO      , sizeof(tempDoc06.PAGE_NO)    		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.PATH_NAME    , sizeof(tempDoc06.PATH_NAME)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.BF_PNU       , sizeof(tempDoc06.BF_PNU)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc06.AF_PNU       , sizeof(tempDoc06.AF_PNU)     		, &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc06, 0x00, sizeof(DOCUMENT06_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc06.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc06.PATH_NAME, asPathName.c_str());
		m_ResultDoc06DBInfo.push_back(tempDoc06);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc07DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	//TB_DOCUMENT07_PNU부터 체크한다//
	funcReadDoc07PnuDBInfo(_asKwon, _asFilePath);
	if(m_ResultDoc07DBInfo.size() > 0)
		return;

    //없으면 TB_DOCUMENT07을 체크한다//
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc07DBInfo.clear();
	m_ResultDoc07DBCount = 0;

	SQLINTEGER m_nVal[24];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT07 ";
	AnsiString asWhere      = "WHERE ";
	AnsiString asPathName	= "";
	DOCUMENT07_STRUCT 		tempDoc07;
	int nIndex              = 1;

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc07, 0x00, sizeof(DOCUMENT07_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.PATH_NAME, 		sizeof(tempDoc07.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.KIND_CODE, 		sizeof(tempDoc07.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07.ROLL_NO, 		sizeof(tempDoc07.ROLL_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07.FRAME_NO, 		sizeof(tempDoc07.FRAME_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.KWON_NO, 			sizeof(tempDoc07.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.PAGE_NO, 			sizeof(tempDoc07.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.LAND_GBN, 		sizeof(tempDoc07.LAND_GBN), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.SIDOSGG, 			sizeof(tempDoc07.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.UMD, 				sizeof(tempDoc07.UMD), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.RI, 				sizeof(tempDoc07.RI), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.SCALE, 			sizeof(tempDoc07.SCALE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.DOHO_BON, 		sizeof(tempDoc07.DOHO_BON), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.DOHO_BU, 			sizeof(tempDoc07.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.X1, 				sizeof(tempDoc07.X1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.Y1, 				sizeof(tempDoc07.Y1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.X2, 				sizeof(tempDoc07.X2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.Y2, 				sizeof(tempDoc07.Y2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.SIZE_X, 			sizeof(tempDoc07.SIZE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.SIZE_Y, 			sizeof(tempDoc07.SIZE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.BASE_X, 			sizeof(tempDoc07.BASE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.BASE_Y, 			sizeof(tempDoc07.BASE_Y), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.RATIOX, 			sizeof(tempDoc07.RATIOX), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.RATIOY, 			sizeof(tempDoc07.RATIOY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc07.REMARK, 			sizeof(tempDoc07.REMARK), 		&m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) )
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc07, 0x00, sizeof(DOCUMENT07_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc07.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc07.PATH_NAME, asPathName.c_str());
		m_ResultDoc07DBInfo.push_back(tempDoc07);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------
//201227//
void __fastcall TfrmSql::funcReadDoc07PnuDBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc07DBInfo.clear();
	m_ResultDoc07DBCount = 0;

	SQLCHAR    	m_cVal[12][255];
	SQLINTEGER 	m_nVal[12];
	SQLRETURN 	ret;
	AnsiString 	asSqlTblA	= "TB_DOCUMENT07 A";
	AnsiString 	asSqlTblB	= "";
	AnsiString 	asSqlWhere 	= "";
	AnsiString 	asSqlOrder 	= "";
	AnsiString  asSql		= "";
	AnsiString 	asCol 		= "";
	AnsiString  asPathName	= "";//201014//
	DOCUMENT07_STRUCT tempDoc07;
	int nIndex = 1;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc07, 0x00, sizeof(DOCUMENT07_STRUCT));

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.PATH_NAME, 	sizeof(tempDoc07.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.KIND_CODE, 	sizeof(tempDoc07.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.KWON_NO, 		sizeof(tempDoc07.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.LAND_GBN, 		sizeof(tempDoc07.LAND_GBN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.SIDOSGG, 		sizeof(tempDoc07.SIDOSGG), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.UMD, 			sizeof(tempDoc07.UMD), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.RI, 			sizeof(tempDoc07.RI), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.SCALE, 		sizeof(tempDoc07.SCALE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.DOHO_BON, 		sizeof(tempDoc07.DOHO_BON), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc07.DOHO_BU, 		sizeof(tempDoc07.DOHO_BU), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.BASE_X, 		sizeof(tempDoc07.BASE_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempDoc07.BASE_Y, 		sizeof(tempDoc07.BASE_Y), 		&m_nVal[nIndex-1]); nIndex++;

	asSqlTblB	= "(SELECT PATH_NAME, IMAGEX, IMAGEY FROM TB_DOCUMENT07_PNU WHERE PNU = '" + frmMain->m_asSearchPnu + "' AND PATH_NAME = '" + _asFilePath + "' AND IMAGEX > 0 AND IMAGEY > 0) B";
	asCol	= "A.PATH_NAME, A.KIND_CODE, A.KWON_NO, A.LAND_GBN, A.SIDOSGG, A.UMD, A.RI, A.SCALE, A.DOHO_BON, A.DOHO_BU, B.IMAGEX, B.IMAGEY";
	//Where condition
	asSqlWhere = asSqlWhere + "A.PATH_NAME = B.PATH_NAME";
	asSqlOrder = asSqlOrder + "KIND_CODE ASC";
	asSql.sprintf("SELECT %s FROM %s, %s WHERE %s ORDER BY %s", asCol, asSqlTblA, asSqlTblB, asSqlWhere, asSqlOrder);

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) )
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc07, 0x00, sizeof(DOCUMENT07_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc07.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc07.PATH_NAME, asPathName.c_str());
		tempDoc07.REMARK = 2;
		m_ResultDoc07DBInfo.push_back(tempDoc07);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc08DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc08DBInfo.clear();
	m_ResultDoc08DBCount = 0;

	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT08 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT08_STRUCT 		tempDoc08;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	if(frmMain->INI_B_OWNNAMES)//#OWNNAMES#
	{
    	SQLINTEGER m_nVal[15];
    	memset(m_nVal, 0x00, sizeof(m_nVal));
    	memset(&tempDoc08, 0x00, sizeof(DOCUMENT08_STRUCT));
    	int nIndex              = 1;

		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc08.ROLL_NO          , sizeof(tempDoc08.ROLL_NO)            , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc08.FRAME_NO         , sizeof(tempDoc08.FRAME_NO)           , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc08.SR_NO            , sizeof(tempDoc08.SR_NO)              , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.SINGU_CODE        , sizeof(tempDoc08.SINGU_CODE)         , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.KIND_CODE         , sizeof(tempDoc08.KIND_CODE)          , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.KWON_NO           , sizeof(tempDoc08.KWON_NO)            , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PAGE_NO           , sizeof(tempDoc08.PAGE_NO)            , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.BUILD_NAME        , sizeof(tempDoc08.BUILD_NAME)         , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.BUILD_HOSU        , sizeof(tempDoc08.BUILD_HOSU)         , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.ONOFF_CODE        , sizeof(tempDoc08.ONOFF_CODE)         , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.SINGU_NAME        , sizeof(tempDoc08.SINGU_NAME)         , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PNU 		         , sizeof(tempDoc08.PNU) 		        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PATH_NAME         , sizeof(tempDoc08.PATH_NAME) 	        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PATH_NAME_COLOR   , sizeof(tempDoc08.PATH_NAME_COLOR)    , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.OWN_NAMES         , sizeof(tempDoc08.OWN_NAMES) 	        , &m_nVal[nIndex-1]); nIndex++;
	}
	else
	{
    	SQLINTEGER m_nVal[14];
    	memset(m_nVal, 0x00, sizeof(m_nVal));
    	memset(&tempDoc08, 0x00, sizeof(DOCUMENT08_STRUCT));
    	int nIndex              = 1;

		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc08.ROLL_NO           , sizeof(tempDoc08.ROLL_NO)           , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc08.FRAME_NO          , sizeof(tempDoc08.FRAME_NO)          , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc08.SR_NO             , sizeof(tempDoc08.SR_NO)             , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.SINGU_CODE         , sizeof(tempDoc08.SINGU_CODE)        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.KIND_CODE          , sizeof(tempDoc08.KIND_CODE)         , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.KWON_NO            , sizeof(tempDoc08.KWON_NO)           , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PAGE_NO            , sizeof(tempDoc08.PAGE_NO)           , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.BUILD_NAME         , sizeof(tempDoc08.BUILD_NAME)        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.BUILD_HOSU         , sizeof(tempDoc08.BUILD_HOSU)        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.ONOFF_CODE         , sizeof(tempDoc08.ONOFF_CODE)        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.SINGU_NAME         , sizeof(tempDoc08.SINGU_NAME)        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PNU 		          , sizeof(tempDoc08.PNU) 		        , &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PATH_NAME          , sizeof(tempDoc08.PATH_NAME)     	, &m_nVal[nIndex-1]); nIndex++;
		SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc08.PATH_NAME_COLOR    , sizeof(tempDoc08.PATH_NAME_COLOR) 	, &m_nVal[nIndex-1]); nIndex++;
	}

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc08, 0x00, sizeof(DOCUMENT08_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc08.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc08.PATH_NAME, asPathName.c_str());
		m_ResultDoc08DBInfo.push_back(tempDoc08);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);


	frmSearch->funcSaveLog(10, 0, asSql);//save data//210223//TEST//
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc09DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc09DBInfo.clear();
	m_ResultDoc09DBCount = 0;

   	SQLINTEGER m_nVal[15];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT09 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT09_STRUCT 		tempDoc09;
    int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc09, 0x00, sizeof(DOCUMENT09_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc09.ROLL_NO    	    , sizeof(tempDoc09.ROLL_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.KIND_CODE  		, sizeof(tempDoc09.KIND_CODE)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.BASE_YEAR    	, sizeof(tempDoc09.BASE_YEAR)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.BASE_MON     	, sizeof(tempDoc09.BASE_MON)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.KWON_NO      	, sizeof(tempDoc09.KWON_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.PAGE_NO   		, sizeof(tempDoc09.PAGE_NO)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.PNU   			, sizeof(tempDoc09.PNU)  		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc09.PATH_NAME    	, sizeof(tempDoc09.PATH_NAME)   , &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc09, 0x00, sizeof(DOCUMENT09_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc09.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc09.PATH_NAME, asPathName.c_str());
		m_ResultDoc09DBInfo.push_back(tempDoc09);
 		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc11DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc11DBInfo.clear();
	m_ResultDoc11DBCount = 0;

   	SQLINTEGER m_nVal[8];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT11 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT11_STRUCT 		tempDoc11;
    int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc11, 0x00, sizeof(DOCUMENT11_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc11.ROLL_NO    , sizeof(tempDoc11.ROLL_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc11.FRAME_NO   , sizeof(tempDoc11.FRAME_NO)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc11.SR_NO      , sizeof(tempDoc11.SR_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc11.KIND_CODE   , sizeof(tempDoc11.KIND_CODE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc11.KWON_NO     , sizeof(tempDoc11.KWON_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc11.PAGE_NO     , sizeof(tempDoc11.PAGE_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc11.PNU 		   , sizeof(tempDoc11.PNU) 		   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc11.PATH_NAME   , sizeof(tempDoc11.PATH_NAME)   , &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	//TEST
	//왜 PATH_NAME을 넣으면 검색결과가 없는 걸까? ㅠㅠ//
	//asSql = "SELECT * FROM tb_document01 WHERE KWON_NO='0075' AND GROUP_NO=21";//PATH_NAME = 'DOCUMENT01\\L0075\\L007500110.jpg'";
	//asSql = "SELECT * FROM tb_document01 WHERE PATH_NAME='DOCUMENT01\L0075\L007500110.JPG'";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

//	memset(&tempDoc11, 0x00, sizeof(DOCUMENT11_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc11.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc11.PATH_NAME, asPathName.c_str());
		m_ResultDoc11DBInfo.push_back(tempDoc11);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc12DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc12DBInfo.clear();
	m_ResultDoc12DBCount = 0;

   	SQLINTEGER m_nVal[12];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT12 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT12_STRUCT 		tempDoc12;
	int nIndex              = 1;
 	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc12, 0x00, sizeof(DOCUMENT12_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc12.ROLL_NO      , sizeof(tempDoc12.ROLL_NO)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.PAGE_NO       , sizeof(tempDoc12.PAGE_NO)      	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.KWON_NO       , sizeof(tempDoc12.KWON_NO)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.REQ_YEAR      , sizeof(tempDoc12.REQ_YEAR)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.REQ_DAY       , sizeof(tempDoc12.REQ_DAY)        , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.OWN_NAME      , sizeof(tempDoc12.OWN_NAME)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.OWN_REG_NO    , sizeof(tempDoc12.OWN_REG_NO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.ISSUE_NO      , sizeof(tempDoc12.ISSUE_NO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.APROV_STATUS  , sizeof(tempDoc12.APROV_STATUS)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.KIND_CODE     , sizeof(tempDoc12.KIND_CODE)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.PATH_NAME     , sizeof(tempDoc12.PATH_NAME)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc12.PNU   	     , sizeof(tempDoc12.PNU)   		    , &m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc12, 0x00, sizeof(DOCUMENT12_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc12.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc12.PATH_NAME, asPathName.c_str());
		m_ResultDoc12DBInfo.push_back(tempDoc12);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc13DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc13DBInfo.clear();
	m_ResultDoc13DBCount = 0;

   	SQLINTEGER m_nVal[9];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT13 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT13_STRUCT 		tempDoc13;
    int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc13, 0x00, sizeof(DOCUMENT13_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc13.ROLL_NO			, sizeof(tempDoc13.ROLL_NO)		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.PAGE_NO      	, sizeof(tempDoc13.PAGE_NO)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.KWON_NO      	, sizeof(tempDoc13.KWON_NO)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.REQ_YEAR     	, sizeof(tempDoc13.REQ_YEAR)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.REQ_DAY      	, sizeof(tempDoc13.REQ_DAY)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.OWN_NAME     	, sizeof(tempDoc13.OWN_NAME)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.OWN_REG_NO   	, sizeof(tempDoc13.OWN_REG_NO) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.KIND_CODE      	, sizeof(tempDoc13.KIND_CODE)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc13.PATH_NAME    	, sizeof(tempDoc13.PATH_NAME)  	, &m_nVal[nIndex-1]); nIndex++;

//M//191114//KWON_NO가 필요한지??//	asWhere = asWhere + "KWON_NO = '" + _asKwon + "' AND PATH_NAME = '" + _asFilePath.Trim() + "' ";
	asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc13, 0x00, sizeof(DOCUMENT13_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc13.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc13.PATH_NAME, asPathName.c_str());
		m_ResultDoc13DBInfo.push_back(tempDoc13);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc14DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc14DBInfo.clear();
	m_ResultDoc14DBCount = 0;

   	SQLINTEGER m_nVal[13];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT14 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT14_STRUCT 		tempDoc14;
    int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc14, 0x00, sizeof(DOCUMENT14_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc14.ROLL_NO      , sizeof(tempDoc14.ROLL_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc14.FRAME_NO     , sizeof(tempDoc14.FRAME_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc14.SR_NO        , sizeof(tempDoc14.SR_NO)         , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.KIND_CODE     , sizeof(tempDoc14.KIND_CODE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.KWON_NO       , sizeof(tempDoc14.KWON_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.PAGE_NO       , sizeof(tempDoc14.PAGE_NO)       , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.SUBMIT_YEAR   , sizeof(tempDoc14.SUBMIT_YEAR)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.PRCS_DATE     , sizeof(tempDoc14.PRCS_DATE)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.MEASURE_TYPE  , sizeof(tempDoc14.MEASURE_TYPE)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc14.GROUP_NO     , sizeof(tempDoc14.GROUP_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc14.GROUP_NO1    , sizeof(tempDoc14.GROUP_NO1)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.PNU   	 	 , sizeof(tempDoc14.PNU)           , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc14.PATH_NAME   	 , sizeof(tempDoc14.PATH_NAME)     , &m_nVal[nIndex-1]); nIndex++;

//M//191114//KWON_NO가 필요한지??//	asWhere = asWhere + "KWON_NO = '" + _asKwon + "' AND PATH_NAME = '" + _asFilePath.Trim() + "' ";
	asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc14, 0x00, sizeof(DOCUMENT14_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc14.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc14.PATH_NAME, asPathName.c_str());
		m_ResultDoc14DBInfo.push_back(tempDoc14);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc15DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc15DBInfo.clear();
	m_ResultDoc15DBCount = 0;

   	SQLINTEGER m_nVal[21];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT15 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT15_STRUCT 		tempDoc15;
    int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc15, 0x00, sizeof(DOCUMENT15_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc15.CINDEX		, sizeof(tempDoc15.CINDEX)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.KWON_NO     	, sizeof(tempDoc15.KWON_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.KIND_CODE    , sizeof(tempDoc15.KIND_CODE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.PRCS_DATE    , sizeof(tempDoc15.PRCS_DATE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.DOC_KIND     , sizeof(tempDoc15.DOC_KIND)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.REG_NM       , sizeof(tempDoc15.REG_NM)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.REG_NO     	, sizeof(tempDoc15.REG_NO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.OWN      	, sizeof(tempDoc15.OWN)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.APP     		, sizeof(tempDoc15.APP)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.APP_NM     	, sizeof(tempDoc15.APP_NM)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.APP_NO     	, sizeof(tempDoc15.APP_NO)      , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.APP_ADDR     , sizeof(tempDoc15.APP_ADDR)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.APP_OFFICE   , sizeof(tempDoc15.APP_OFFICE)  , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.REPS_NM      , sizeof(tempDoc15.REPS_NM)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.REPS_NO      , sizeof(tempDoc15.REPS_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.REPS_ADDR    , sizeof(tempDoc15.REPS_ADDR)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc15.PATH_NAME    , sizeof(tempDoc15.PATH_NAME)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc15.ROLL_NO     , sizeof(tempDoc15.ROLL_NO)     , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc15.SR_NO     	, sizeof(tempDoc15.SR_NO)     	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc15.GROUP_NO    , sizeof(tempDoc15.GROUP_NO)    , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc15.GROUP_NO1   , sizeof(tempDoc15.GROUP_NO1)   , &m_nVal[nIndex-1]); nIndex++;

//M//191114//KWON_NO가 필요한지??//	asWhere = asWhere + "KWON_NO = '" + _asKwon + "' AND PATH_NAME = '" + _asFilePath.Trim() + "' ";
	asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc15, 0x00, sizeof(DOCUMENT15_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc15.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc15.PATH_NAME, asPathName.c_str());
		m_ResultDoc15DBInfo.push_back(tempDoc15);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc17DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc17DBInfo.clear();
	m_ResultDoc17DBCount = 0;

   	SQLINTEGER m_nVal[10];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT17 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT17_STRUCT 		tempDoc17;
    int nIndex              = 1;
	AnsiString asPathName   = "";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc17, 0x00, sizeof(DOCUMENT17_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDoc17.SEQ_NUM  		, sizeof(tempDoc17.SEQ_NUM)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.KWON_NO     		, sizeof(tempDoc17.KWON_NO)    	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.KIND_CODE     	, sizeof(tempDoc17.KIND_CODE)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.DOC_CODE     	, sizeof(tempDoc17.DOC_CODE)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.DOC_NAME     	, sizeof(tempDoc17.DOC_NAME)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.PYO_PAGE     	, sizeof(tempDoc17.PYO_PAGE)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.PAGE     		, sizeof(tempDoc17.PAGE)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.DOC_DATE     	, sizeof(tempDoc17.DOC_DATE)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.PNU     			, sizeof(tempDoc17.PNU)        	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDoc17.PATH_NAME    	, sizeof(tempDoc17.PATH_NAME)  	, &m_nVal[nIndex-1]); nIndex++;

//M//191114//KWON_NO가 필요한지??//	asWhere = asWhere + "KWON_NO = '" + _asKwon + "' AND PATH_NAME = '" + _asFilePath.Trim() + "' ";
	asWhere = asWhere + "SUBSTRING(PATH_NAME, 1, " + asPathName.Length() + ") = '" + asPathName.Trim() + "' ";
	asSql = "SELECT * FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc17, 0x00, sizeof(DOCUMENT17_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc17.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc17.PATH_NAME, asPathName.c_str());
		m_ResultDoc17DBInfo.push_back(tempDoc17);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDoc18DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc18DBInfo.clear();
	m_ResultDoc18DBCount = 0;

   	SQLINTEGER m_nVal[11];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT18 ";
	AnsiString asWhere      = "WHERE ";
	DOCUMENT18_STRUCT 		tempDoc18;
    int nIndex              = 1;
	AnsiString asPathName   = "";
	AnsiString asColumn   	= "";

	asColumn 	= "distinct JIGU_YEAR, JIGU_NAME, KWON_NO, KIND_CODE, GROUP_NO, PAGE_NO, MEASURE_DATE, CHECK_DATE, DOGNPOINT, BOJOPOINT, PATH_NAME";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_YEAR, 		sizeof(tempDoc18.JIGU_YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.JIGU_NAME, 		sizeof(tempDoc18.JIGU_NAME), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KWON_NO, 			sizeof(tempDoc18.KWON_NO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.KIND_CODE, 		sizeof(tempDoc18.KIND_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc18.GROUP_NO, 		sizeof(tempDoc18.GROUP_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PAGE_NO, 			sizeof(tempDoc18.PAGE_NO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.MEASURE_DATE, 	sizeof(tempDoc18.MEASURE_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.CHECK_DATE, 		sizeof(tempDoc18.CHECK_DATE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.DOGNPOINT, 		sizeof(tempDoc18.DOGNPOINT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.BOJOPOINT, 		sizeof(tempDoc18.BOJOPOINT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc18.PATH_NAME, 		sizeof(tempDoc18.PATH_NAME), 		&m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT " + asColumn + " FROM " + asTable + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc18, 0x00, sizeof(DOCUMENT18_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc18.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc18.PATH_NAME, asPathName.c_str());
		m_ResultDoc18DBInfo.push_back(tempDoc18);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//=============================================================================
//231030//GAGAMLAYER in LandArchive//
//=============================================================================
void __fastcall TfrmSql::funcReadDoc20DBInfo(AnsiString _asKwon, AnsiString _asFilePath)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	m_ResultDoc20DBInfo.clear();
	m_ResultDoc20DBCount = 0;

   	SQLINTEGER m_nVal[11];
	SQLRETURN ret;
	AnsiString asSql        = "";
	AnsiString asTable      = "TB_DOCUMENT20 ";
	AnsiString asWhere      = "";
	DOCUMENT20_STRUCT 		tempDoc20;
    int nIndex              = 1;
	AnsiString asPathName   = "";
	AnsiString  asColumn	= "KWON_NO, GAGAM_NO, UMDRI_CD, DOHO, DOC_NAME, KIND_CODE, PAGE_NO, SURV_DATE, SURV_ETC, PRCS_DATE, PATH_NAME";//241211//
//	AnsiString  asColumn	= "";
//	asColumn 	= "*";

	_asFilePath = StringReplace(_asFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc20, 0x00, sizeof(DOCUMENT20_STRUCT));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.KWON_NO, 			sizeof(tempDoc20.KWON_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.GAGAM_NO, 		sizeof(tempDoc20.GAGAM_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.UMDRI_CD, 		sizeof(tempDoc20.UMDRI_CD), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.DOHO, 			sizeof(tempDoc20.DOHO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.DOC_NAME, 		sizeof(tempDoc20.DOC_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.KIND_CODE, 		sizeof(tempDoc20.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.PAGE_NO, 			sizeof(tempDoc20.PAGE_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.SURV_DATE, 		sizeof(tempDoc20.SURV_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.SURV_ETC, 		sizeof(tempDoc20.SURV_ETC), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.PRCS_DATE, 		sizeof(tempDoc20.PRCS_DATE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc20.PATH_NAME, 		sizeof(tempDoc20.PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;

    //
	asWhere = "PATH_NAME = '" + _asFilePath + "' ";
	asSql = "SELECT " + asColumn + " FROM " + asTable + " WHERE " + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSql.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc20, 0x00, sizeof(DOCUMENT20_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDoc20.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDoc20.PATH_NAME, asPathName.c_str());
		m_ResultDoc20DBInfo.push_back(tempDoc20);
		break;//200205//DBInfo에 1개만 넣는다//
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------


//===========================================================================
//===========================================================================
void __fastcall TfrmSql::funcSQLUpdateSpatialConfig(AnsiString _asLayerName, int _nShowUse)
{
//일괄적용
//	AnsiString 	asSqlQry;
//
//	m_MAININI.USE_IMAGE_JIJUKLINECOLOR    = (int)shpUSEIMAGEJIJUKLINECOLOR->Brush->Color;
//	asSqlQry = "UPDATE TB_SPATIALCONFIG SET SHOW_USE=" + IntToStr(_nShowUse) + " WHERE LAYERNAME LIKE '" + _asLayerName.Trim() + "%'";
//	func_QryProcess(asSqlQry);
//
//	asSqlQry = "COMMIT;";
//	func_QryProcess(asSqlQry);

//개별적용
	AnsiString 	asSqlQry;
	frmMain->m_MAININI.USE_IMAGE_JIJUKLINECOLOR    = (int)frmMain->shpUSEIMAGEJIJUKLINECOLOR->Brush->Color;
	asSqlQry = "UPDATE TB_SPATIALCONFIG SET SHOW_USE=" + IntToStr(_nShowUse) + " WHERE LAYERNAME = '" + _asLayerName.Trim() + "'";
	//asSqlQry = "UPDATE TB_SPATIALCONFIG SET SHOW_USE=" + IntToStr(_nShowUse) + ", LABEL_USE=" + IntToStr(_nLabelUse) + " WHERE LAYERNAME = '" + _asLayerName.Trim() + "'";
	func_QryProcess(asSqlQry);

	asSqlQry = "COMMIT;";
	func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------










//231118//#CODE_UNITY#//아래 함수 통합//
//funcSQLCheckTable(TB_COPY_DNLD)
//funcSQLCheckTable(TB_COPY_DOC08)
//funcSQLCheckTable(TB_DOCUMENT20)
//funcSQLCheckTable(TB_DOCUMENT08, JUMIN_XY)
//funcSQLCheckTable(TB_DOCUMENT08, OWN_NAMES)
//funcSQLCheckTable(TB_DOCUMENT08_HIS)
//funcSQLCheckTable(TB_DOCUMENT08_OWNINFO)
//funcSQLCheckTable(TB_DOCUMENT08_SHAREOWN)
//funcSQLCheckTable(TABLE_MEMOINFO)
//funcSQLCheckTable(TB_DOCUMENT08_HIS_DIRECT)
//funcSQLCheckTable(TB_DOCUMENT08_OWNINFO_DIRECT)
//funcSQLCheckTable(TB_DOCUMENT08_SHAREOWN_DIRECT)
//=============================================================================
// INFORMATION_SCHEMA.COLUMNS 에 조건에 해당하는 TABLE, COLUMN 존재 여부 확인//
//=============================================================================
bool __fastcall TfrmSql::funcSQLCheckTable(AnsiString _asTable, AnsiString _asColumn)
{
	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	SQLRETURN 	ret;
	SQLINTEGER 	m_nVal[1];
	int			nVal;
	AnsiString 	asSqlQry	= "";
	AnsiString 	asWhere		= "";
	bool		bReturn 	= false;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	SQLBindCol(m_hStmt, 1,  SQL_C_LONG, &nVal, sizeof(nVal) , &m_nVal[0]);

	//
	asWhere		= "WHERE TABLE_SCHEMA = '" + frmMain->_DATABASE_ + "'";//TABLE_SCHEMA
	asWhere		+= " AND TABLE_NAME = '" + _asTable + "'";//TABLE_NAME
	if( !_asColumn.IsEmpty() )
		asWhere	+= " AND COLUMN_NAME ='" + _asColumn + "'";//COLUMN_NAME
	//
	asSqlQry	= "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS " + asWhere;
    //
	ret    	= SQLPrepare(m_hStmt, (SQLCHAR*)asSqlQry.c_str(), SQL_NTS);
	ret		= SQLExecute(m_hStmt);

	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return false;
	}

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		bReturn = (nVal >= 1) ? (true) : (false);
	};

	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	return bReturn;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmSql::funcQryInsertDoc8OwnNames(AnsiString _asDBStr)
{
	AnsiString 	asSqlTbl 	= "TB_DOCUMENT08";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asPathName	= "";

	int nColCount = 3;
	char cCol[3][20] = {"PATH_NAME", "PATH_NAME_COLOR", "OWN_NAMES"};

	//Query Column
	asSqlCol = asSqlCol + cCol[2] 	+ " = '" + _asDBStr + "'";

	asPathName = StringReplace(frmMain->m_asDocDBPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);

	//Where condition
	if(frmMain->m_bDoc8Color)//PATH_NAME_COLOR
		asSqlWhere = asSqlWhere + cCol[1] + " = '" + asPathName + "'" ;//
	else//PATH_NAME
		asSqlWhere = asSqlWhere + cCol[0] + " = '" + asPathName + "'" ;//

	asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------





//201112//구대장 상세검색에서 소유자명 찾기//
bool __fastcall TfrmSql::funcSQLCountDocument08OwnInfoName(AnsiString _asSqlQry)
{
	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	//select count(*) from all_tables where table_name = '테이블 명';
	SQLRETURN 	ret;
	SQLINTEGER 	m_nVal[1];
	int			nVal;
	bool		bReturn = false;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	SQLBindCol(m_hStmt, 1,  SQL_C_LONG, &nVal, sizeof(nVal) , &m_nVal[0]);

	ret    	= SQLPrepare(m_hStmt, (SQLCHAR*)_asSqlQry.c_str(), SQL_NTS);
	ret		= SQLExecute(m_hStmt);

	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return false;
	}

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		bReturn = (nVal > 0) ? (true) : (false);
	};

	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	return bReturn;
}
//---------------------------------------------------------------------------

//===========================================================================
// READ TB_OLDLANDDOC_INFO//#OWNINFO#
//===========================================================================
void __fastcall TfrmSql::funcSQLReadOldLandDocInfo()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER 	m_nVal[7];
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= "TB_OLDLANDDOC_INFO";
	AnsiString 	asSqlQry	= "";
	AnsiString 	asWhere		= "";
	OLDLANDDOC_INFO_STRUCT 	tempData;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempData, 0, sizeof(OLDLANDDOC_INFO_STRUCT));

	int nIndex = 1;
	SQLBindCol(m_hStmt, nIndex, SQL_C_LONG, &tempData.PATHLIST_SEQNO, 	sizeof(tempData.PATHLIST_SEQNO), 	&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_LONG, &tempData.PNU_CHECK, 		sizeof(tempData.PNU_CHECK), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.PNU_NAME, 			sizeof(tempData.PNU_NAME), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.LEVEL, 			sizeof(tempData.LEVEL), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.MEMO, 				sizeof(tempData.MEMO), 				&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.WRITE_ID, 			sizeof(tempData.WRITE_ID), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.WRITE_DT, 			sizeof(tempData.WRITE_DT), 			&m_nVal[nIndex - 1]);		nIndex++;

	asWhere		= " WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo);
	asSqlQry	= "SELECT * FROM " + asSqlTbl + asWhere;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	//===========================================================
	if( !frmMain->m_bAIOCR )
		e08DataAlpha->m_vOldLandDocInfo.clear();
	else
		e08DataAIOCR->m_vOldLandDocInfo.clear();
	//===========================================================

	memset(&tempData, 0, sizeof(tempData));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		//===========================================================
		if( !frmMain->m_bAIOCR )
			e08DataAlpha->m_vOldLandDocInfo.push_back(tempData);
		else
			e08DataAIOCR->m_vOldLandDocInfo.push_back(tempData);
		//===========================================================
		memset(&tempData, 0, sizeof(OLDLANDDOC_INFO_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadDocument08Pnu(AnsiString _asPathName)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlQry	 = "";
	SQLRETURN 	ret;
	AnsiString  asPathName	 = "";
	DOCUMENT08_PNU_STRUCT 				tempDocument08Pnu;

	SQLINTEGER m_nVal[14];

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDocument08Pnu, 0x00, sizeof(DOCUMENT08_PNU_STRUCT));
	int nIndex = 1;

	_asPathName = StringReplace(_asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, &tempDocument08Pnu.SEQNO    	, sizeof(tempDocument08Pnu.SEQNO)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.PATH_NAME    , sizeof(tempDocument08Pnu.PATH_NAME)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.PNU 		   	, sizeof(tempDocument08Pnu.PNU) 		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.KIND_CODE 	, sizeof(tempDocument08Pnu.KIND_CODE) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.FORMAT_TYPE 	, sizeof(tempDocument08Pnu.FORMAT_TYPE) , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.INPUT_YN 	, sizeof(tempDocument08Pnu.INPUT_YN) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.INPUT_ID 	, sizeof(tempDocument08Pnu.INPUT_ID) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.INPUT_DT 	, sizeof(tempDocument08Pnu.INPUT_DT) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.CHECK_YN 	, sizeof(tempDocument08Pnu.CHECK_YN) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.CHECK_ID 	, sizeof(tempDocument08Pnu.CHECK_ID) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.CHECK_DT 	, sizeof(tempDocument08Pnu.CHECK_DT) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.DIRECT_YN 	, sizeof(tempDocument08Pnu.DIRECT_YN) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.DIRECT_ID 	, sizeof(tempDocument08Pnu.DIRECT_ID) 	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, tempDocument08Pnu.DIRECT_DT 	, sizeof(tempDocument08Pnu.DIRECT_DT) 	, &m_nVal[nIndex-1]); nIndex++;

	asSqlQry	= "SELECT * FROM TB_OLDLANDDOC_PATHLIST WHERE PATH_NAME='" + _asPathName + "'";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_ResultDocument08Pnu.clear();

	memset(&tempDocument08Pnu, 0x00, sizeof(DOCUMENT08_PNU_STRUCT));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		asPathName = (char*)tempDocument08Pnu.PATH_NAME;
		asPathName = StringReplace(asPathName, "/", "\\", TReplaceFlags() << rfReplaceAll);
		strcpy(tempDocument08Pnu.PATH_NAME, asPathName.c_str());

		frmMain->m_ResultDocument08Pnu.push_back(tempDocument08Pnu);
		memset(&tempDocument08Pnu, 0x00, sizeof(DOCUMENT08_PNU_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//#OWNINFO#//200604//변경
void __fastcall TfrmSql::funcReadDocument08His()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlTbl  	= "TB_DOCUMENT08_HIS";
	AnsiString  asSqlQry  	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asDate		= "";
	SQLRETURN ret;
	DOCUMENT08_HIS_STRUCT		tempDoc08His;//구대장 연혁//

	memset(&tempDoc08His, 0x00, sizeof(DOCUMENT08_HIS_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[9];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	//260611//AIOCR//
	if(frmMain->m_bAIOCR)
	{
		asSqlTbl  	= "TB_DOCUMENT08_AIOCR_HIS";
	}
	else
	{
		//=========================================================================
		//241030//#구대장한글편집#DirectTable//
		//=========================================================================
		if( !strcmp(frmMain->m_ResultDocument08Pnu[0].DIRECT_YN, "1") )
			asSqlTbl  	= "TB_DOCUMENT08_HIS_DIRECT";
		//=========================================================================
	}

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08His.PATHLIST_SEQNO, 	sizeof(tempDoc08His.PATHLIST_SEQNO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08His.SEQ, 				sizeof(tempDoc08His.SEQ), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.JIMOK, 			sizeof(tempDoc08His.JIMOK), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.AREA, 				sizeof(tempDoc08His.AREA), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.VALUE1, 			sizeof(tempDoc08His.VALUE1), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.VALUE2, 			sizeof(tempDoc08His.VALUE2), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.ERA_CODE, 			sizeof(tempDoc08His.ERA_CODE), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.HIS_DATE, 			sizeof(tempDoc08His.HIS_DATE), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.HISTORY, 			sizeof(tempDoc08His.HISTORY), 			&m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
	asSqlQry = "SELECT * FROM " + asSqlTbl + " WHERE " + asWhere + "ORDER BY SEQ";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	if( !frmMain->m_bAIOCR )
		e08DataAlpha->m_ResultDoc08His.clear();
	else
		e08DataAIOCR->m_ResultDoc08His.clear();

	memset(&tempDoc08His, 0x00, sizeof(DOCUMENT08_HIS_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		//===========================================================
		if( !frmMain->m_bAIOCR )
			e08DataAlpha->m_ResultDoc08His.push_back(tempDoc08His);
		else
			e08DataAIOCR->m_ResultDoc08His.push_back(tempDoc08His);
		//===========================================================
		memset(&tempDoc08His, 0x00, sizeof(DOCUMENT08_HIS_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//===========================================================
	if( !frmMain->m_bAIOCR )
	{
		funcReadDocument08HisDel();//241011//구대장 연혁(삭제선)//
		e08DataAlpha->funcProcessDataHis();
	}
	else
	{
		e08DataAIOCR->funcProcessDataHis();
	}
	//===========================================================
}
//---------------------------------------------------------------------------


//#OWNINFO#//241011//지목,지적=>삭제선 관련 별도 테이블 분리(JIMOK, AREA '1' 인 경우 삭제선 표시, 그 외 미표시)//
void __fastcall TfrmSql::funcReadDocument08HisDel()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlTbl  	= "TB_DOCUMENT08_HIS_DEL";
	AnsiString  asSqlQry  	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asDate		= "";
	AnsiString  asAllSharp	= "#";
	SQLRETURN ret;
	DOCUMENT08_HIS_DEL_STRUCT		tempDoc08His;//구대장 연혁(삭제선)//

	memset(&tempDoc08His, 0x00, sizeof(DOCUMENT08_HIS_DEL_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[5];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08His.PATHLIST_SEQNO, 	sizeof(tempDoc08His.PATHLIST_SEQNO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08His.SEQ, 				sizeof(tempDoc08His.SEQ), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.JIMOK, 			sizeof(tempDoc08His.JIMOK), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.AREA, 				sizeof(tempDoc08His.AREA), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08His.VALUE, 			sizeof(tempDoc08His.VALUE), 			&m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
	asSqlQry = "SELECT * FROM " + asSqlTbl + " WHERE " + asWhere + "ORDER BY SEQ";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&tempDoc08His, 0x00, sizeof(DOCUMENT08_HIS_DEL_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		if(tempDoc08His.SEQ != 0 && tempDoc08His.SEQ <= (int)e08DataAlpha->m_ResultDoc08His.size())
		{
			AnsiString  asTemp	= "";
			int			nSEQ	= tempDoc08His.SEQ;
			if( !strcmp(tempDoc08His.JIMOK, "1") )//삭제선(지목)//
			{
				asTemp	= (char*)e08DataAlpha->m_ResultDoc08His[nSEQ-1].JIMOK;
				asTemp	= asAllSharp + asTemp;
				strcpy(e08DataAlpha->m_ResultDoc08His[nSEQ-1].JIMOK, asTemp.c_str());
			}
			if( !strcmp(tempDoc08His.AREA, "1") )//삭제선(지적)//
			{
				asTemp	= (char*)e08DataAlpha->m_ResultDoc08His[nSEQ-1].AREA;
				asTemp	= asAllSharp + asTemp;
				strcpy(e08DataAlpha->m_ResultDoc08His[nSEQ-1].AREA, asTemp.c_str());
			}
			if( !strcmp(tempDoc08His.VALUE, "1") )//삭제선(과세등급)//
			{
				asTemp	= (char*)e08DataAlpha->m_ResultDoc08His[nSEQ-1].VALUE1;
				asTemp	= asAllSharp + asTemp;
				strcpy(e08DataAlpha->m_ResultDoc08His[nSEQ-1].VALUE1, asTemp.c_str());
			}
		}
		memset(&tempDoc08His, 0x00, sizeof(DOCUMENT08_HIS_DEL_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//#OWNINFO#//구대장 소유자정보//
void __fastcall TfrmSql::funcReadDocument08OwnInfo()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlTbl  = "TB_DOCUMENT08_OWNINFO";
	AnsiString  asSqlQry  = "";
	AnsiString  asWhere   = "";
	SQLRETURN ret;
	DOCUMENT08_OWNINFO_STRUCT	tempDoc08OwnInfo;//구대장 소유자정보//

    //---
	memset(&tempDoc08OwnInfo, 0x00, sizeof(DOCUMENT08_OWNINFO_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[7];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	//260611//AIOCR//
	if(frmMain->m_bAIOCR)
	{
		asSqlTbl  	= "TB_DOCUMENT08_AIOCR_OWNINFO";
	}
	else
	{
		//=========================================================================
		//241030//#구대장한글편집#DirectTable//
		//=========================================================================
		if( !strcmp(frmMain->m_ResultDocument08Pnu[0].DIRECT_YN, "1") )
			asSqlTbl  	= "TB_DOCUMENT08_OWNINFO_DIRECT";
		//=========================================================================
	}

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08OwnInfo.PATHLIST_SEQNO, 	sizeof(tempDoc08OwnInfo.PATHLIST_SEQNO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08OwnInfo.SEQ, 				sizeof(tempDoc08OwnInfo.SEQ), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08OwnInfo.ERA_CODE, 			sizeof(tempDoc08OwnInfo.ERA_CODE), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08OwnInfo.HIS_DATE, 			sizeof(tempDoc08OwnInfo.HIS_DATE), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08OwnInfo.REASON, 			sizeof(tempDoc08OwnInfo.REASON), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08OwnInfo.OWN_ADDRESS, 		sizeof(tempDoc08OwnInfo.OWN_ADDRESS), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08OwnInfo.OWN_NAME, 			sizeof(tempDoc08OwnInfo.OWN_NAME), 			&m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
	asSqlQry = "SELECT * FROM " + asSqlTbl + " WHERE " + asWhere + "ORDER BY SEQ";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	if( !frmMain->m_bAIOCR )
		e08DataAlpha->m_ResultDoc08OwnInfo.clear();
	else
		e08DataAIOCR->m_ResultDoc08OwnInfo.clear();

	memset(&tempDoc08OwnInfo, 0x00, sizeof(DOCUMENT08_OWNINFO_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		//===========================================================
		if( !frmMain->m_bAIOCR )
			e08DataAlpha->m_ResultDoc08OwnInfo.push_back(tempDoc08OwnInfo);
		else
			e08DataAIOCR->m_ResultDoc08OwnInfo.push_back(tempDoc08OwnInfo);
		//===========================================================
		memset(&tempDoc08OwnInfo, 0x00, sizeof(DOCUMENT08_OWNINFO_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//===========================================================
	if( !frmMain->m_bAIOCR )
		e08DataAlpha->funcProcessDataOwnInfo();
	else
		e08DataAIOCR->funcProcessDataOwnInfo();
	//===========================================================

	frmSearch->funcSaveLog(12, 0, asSqlQry);//save data//210223//TEST//
}
//---------------------------------------------------------------------------

//======================================================================
//v1.0.0.1//#SHAREOWN#
//구대장 공유지연명부 소유자정보//
void __fastcall TfrmSql::funcReadDocument08ShareOwn()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlTbl  = "TB_DOCUMENT08_SHAREOWN";
	AnsiString  asSqlQry  = "";
	AnsiString  asWhere   = "";
	SQLRETURN ret;
	DOCUMENT08_SHAREOWN_STRUCT	tempDoc08ShareOwn;//구대장 소유자정보//

	//---
	memset(&tempDoc08ShareOwn, 0x00, sizeof(DOCUMENT08_SHAREOWN_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[8];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	//260611//AIOCR//
	if(frmMain->m_bAIOCR)
	{
		asSqlTbl  	= "TB_DOCUMENT08_AIOCR_SHAREOWN";
	}
	else
	{
		//=========================================================================
		//241030//#구대장한글편집#DirectTable//
		//=========================================================================
		if( !strcmp(frmMain->m_ResultDocument08Pnu[0].DIRECT_YN, "1") )
			asSqlTbl  	= "TB_DOCUMENT08_SHAREOWN_DIRECT";
		//=========================================================================
	}

	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08ShareOwn.PATHLIST_SEQNO, 	sizeof(tempDoc08ShareOwn.PATHLIST_SEQNO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc08ShareOwn.SEQ, 			sizeof(tempDoc08ShareOwn.SEQ), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08ShareOwn.ERA_CODE, 		sizeof(tempDoc08ShareOwn.ERA_CODE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08ShareOwn.HIS_DATE, 		sizeof(tempDoc08ShareOwn.HIS_DATE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08ShareOwn.REASON, 			sizeof(tempDoc08ShareOwn.REASON), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08ShareOwn.RATIO, 			sizeof(tempDoc08ShareOwn.RATIO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08ShareOwn.OWN_ADDRESS, 		sizeof(tempDoc08ShareOwn.OWN_ADDRESS), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc08ShareOwn.OWN_NAME, 		sizeof(tempDoc08ShareOwn.OWN_NAME), 		&m_nVal[nIndex-1]); nIndex++;

	asWhere = asWhere + "PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
	asSqlQry = "SELECT * FROM " + asSqlTbl + " WHERE " + asWhere + "ORDER BY SEQ";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	if( !frmMain->m_bAIOCR )
		e08DataAlpha->m_ResultDoc08His.clear();
	else
		e08DataAIOCR->m_ResultDoc08ShareOwn.clear();

	memset(&tempDoc08ShareOwn, 0x00, sizeof(DOCUMENT08_SHAREOWN_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		//===========================================================
		if( !frmMain->m_bAIOCR )
			e08DataAlpha->m_ResultDoc08ShareOwn.push_back(tempDoc08ShareOwn);
		else
			e08DataAIOCR->m_ResultDoc08ShareOwn.push_back(tempDoc08ShareOwn);
		//===========================================================
		memset(&tempDoc08ShareOwn, 0x00, sizeof(DOCUMENT08_SHAREOWN_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//===========================================================
	if( !frmMain->m_bAIOCR )
		e08DataAlpha->funcProcessDataShareOwn();
	else
		e08DataAIOCR->funcProcessDataShareOwn();
	//===========================================================
}
//---------------------------------------------------------------------------

//===========================================================================
// WRITE TB_OLDLANDDOC_INFO//
// _nType : INSERT, UPDATE, DELETE
// _nDataGroup : 입력, 검수, 감독 테이블
//===========================================================================
bool __fastcall TfrmSql::funcSQLWriteOldLandDocInfo(int _nType)
{
	AnsiString 	asSqlTbl 	= "TB_OLDLANDDOC_INFO";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asSqlWhere	= "";
	AnsiString  asNow		= Now().FormatString("YYYYMMDDHHNNSS");
	AnsiString  asStr		= "";

	int nColCount = 7;
	char cCol[7][20] = {"PATHLIST_SEQNO", "PNU_CHECK", "PNU_NAME", "LEVEL", "MEMO", "WRITE_ID", "WRITE_DT"};

	//---
	if(_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 0; i < nColCount; i++)
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}


		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO
		asSqlVal = asSqlVal + ", " + (frmResultList->chkJibunOK->Checked ? IntToStr(1) : IntToStr(0));//PNU_CHECK
		asSqlVal = asSqlVal + ", '" + frmResultList->edtPnu->Text + "'";//PNU_NAME
		asSqlVal = asSqlVal + ", '" + frmResultList->edtLevel->Text + "'";//LEVEL
		asStr	= frmResultList->edtMemo->Text;
		if(frmResultList->edtDoho->Text.Length() > 0)
		{
			if(frmAlphaDoc8->m_nDOCKIND == 0)
				asStr	= asStr + "(지적도제" + frmResultList->edtDoho->Text + "호)";
			else if(frmAlphaDoc8->m_nDOCKIND == 1)
				asStr	= asStr + "(임야도제" + frmResultList->edtDoho->Text + "호)";
		}
		asSqlVal = asSqlVal + ", '" + asStr + "'";//MEMO
		asSqlVal = asSqlVal + ", '" + frmMain->m_asCurrentId + "'";//WRITE_ID
		asSqlVal = asSqlVal + ", '" + asNow + "'";//WRITE_DT

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES (%s)", asSqlTbl, asSqlCol, asSqlVal);
	}
	else if(_nType == DF_UPDATE_RECORD)//UPDATE
	{
		asSqlCol = asSqlCol + cCol[1] + " = " + (frmResultList->chkJibunOK->Checked ? IntToStr(1) : IntToStr(0)) + ", ";
		asSqlCol = asSqlCol + cCol[2] + " = '" + frmResultList->edtPnu->Text + "', ";
		asSqlCol = asSqlCol + cCol[3] + " = '" + frmResultList->edtLevel->Text + "', ";
		asStr	= frmResultList->edtMemo->Text;
		if(frmResultList->edtDoho->Text.Length() > 0)
		{
			if(frmAlphaDoc8->m_nDOCKIND == 0)
				asStr	= asStr + "(지적도제" + frmResultList->edtDoho->Text + "호)";
			else if(frmAlphaDoc8->m_nDOCKIND == 1)
				asStr	= asStr + "(임야도제" + frmResultList->edtDoho->Text + "호)";
		}
		asSqlCol = asSqlCol + cCol[4] + " = '" + asStr + "'";

		asSqlWhere = asSqlWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);
	}
	//210705//TB_OLDLANDDOC_INFO는 DELETE > INSERT 하면 일별 입력개수에 영향이 미치므로 하지 않는다//
//	else if(_nType == DF_DELETE_RECORD)//DELETE
//	{
//		asSqlWhere = asSqlWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO
//
//		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);
//	}

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//===========================================================================
// Update TB_OLDLANDDOC_PATHLIST//
//===========================================================================
bool __fastcall TfrmSql::funcSQLUpdateOldLandDocPathlist()
{
	AnsiString 	asSqlTbl 	= "TB_OLDLANDDOC_PATHLIST";
	AnsiString 	asSqlCol 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asSqlWhere	= "";
	AnsiString  asNow		= Now().FormatString("YYYYMMDDHHNNSS");

	//260611//AIOCR//
	if(frmMain->m_bAIOCR)
	{
		strcpy(frmMain->m_ResultDocument08Pnu[0].INPUT_YN, "1");
		strcpy(frmMain->m_ResultDocument08Pnu[0].INPUT_ID, "1");
		asSqlCol = "INPUT_YN='1', INPUT_ID='" + frmMain->m_asCurrentId + "', INPUT_DT='" + asNow + "'";
	}
	else
	{
		strcpy(frmMain->m_ResultDocument08Pnu[0].DIRECT_YN, "1");
		strcpy(frmMain->m_ResultDocument08Pnu[0].DIRECT_ID, "1");
		asSqlCol = "DIRECT_YN='1', DIRECT_ID='" + frmMain->m_asCurrentId + "', DIRECT_DT='" + asNow + "'";
	}

	asSqlWhere = "SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO

	asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//#OWNINFO#
//===========================================================================
// WRITE TB_DOCUMENT08_HIS//
// _nType : INSERT, UPDATE, DELETE
//===========================================================================
bool __fastcall TfrmSql::funcWriteHistory(int _nType, int _nCol)
{
	AnsiString 	asSqlTbl 	= "";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asPathName	= "";
	AnsiString  asStr		= "";

	int nColCount = 9;
	char cCol[9][20] = {"PATHLIST_SEQNO", "SEQ", "JIMOK", "AREA", "VALUE1", "VALUE2", "ERA_CODE", "HIS_DATE", "HISTORY"};

	//260528//AIOCR//
	if( !frmMain->m_bAIOCR )//기구축 번역본 편집//
		asSqlTbl 	= "TB_DOCUMENT08_HIS_DIRECT";//241030//#구대장한글화편집#DirectTable//(지적문서 내에서 한글화 편집은 관리자만 저장)//
	else//AIOCR 번역본 편집//
		asSqlTbl 	= "TB_DOCUMENT08_AIOCR_HIS";

	//---
	if(_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 0; i < nColCount; i++)
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}

		asSqlVal = asSqlVal + "(";
		//210605//asSqlVal = asSqlVal + "'" + asPathName + "', ";
		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo) + ", ";//210605//
		asSqlVal = asSqlVal + IntToStr(frmResultList->sgHistory->ColCount - 1 - _nCol) + ", ";

		asStr	= frmResultList->sgHistory->Cells[_nCol][0];
		if(asStr == "-")	asStr	= "";
		asStr	= StringReplace(asStr, "#", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][1];
		if(asStr == "-")	asStr	= "";
		asStr	= StringReplace(asStr, "#", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][2];
		if(asStr == "-")	asStr	= "";
		asStr	= StringReplace(asStr, "#", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][3];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asSqlVal = asSqlVal + "'', ";
		asSqlVal = asSqlVal + "'', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][4];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + "'" + asStr + "')";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlVal);
	}
	else if(_nType == DF_UPDATE_RECORD)//UPDATE
	{
		//210605//asWhere  = asWhere + cCol[0] + " = '" + asPathName + "' ";
		asWhere  = asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
		asWhere  = asWhere + "AND " + cCol[1] 	+ " = " + IntToStr(frmResultList->sgHistory->ColCount - 1 - _nCol);

		asStr	= frmResultList->sgHistory->Cells[_nCol][0];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[2] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][1];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[3] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][2];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[4] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][3];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[5] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgHistory->Cells[_nCol][4];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[8] + " = '" + asStr + "'";

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlVal, asWhere);
	}
	else if(_nType == DF_DELETE_RECORD)//DELETE
	{
		//210605//asWhere	= asWhere + cCol[0] + " = '" + asPathName + "' ";
		asWhere	= asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
		asWhere = asWhere + "AND " + cCol[1] 	+ " = " + IntToStr(_nCol + 1);

		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}
	//210705//
	else if(_nType == DF_DELETE_RECORD_ALL)//DELETE_ALL
	{
		asWhere	= asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}

	frmResultList->m_asQryToSave	= asSqlQry;//210617//
	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//#OWNINFO#
//===========================================================================
// WRITE TB_DOCUMENT08_OWNINFO//
// _nType : INSERT, UPDATE, DELETE
//===========================================================================
bool __fastcall TfrmSql::funcWriteOwnInfo(int _nType, int _nCol)
{
	AnsiString 	asSqlTbl 	= "";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asWhere 	= "";
	AnsiString  asSqlQry	= "";
	//210605//AnsiString  asPathName	= "";
	AnsiString  asStr		= "";
	int			nRow		= 0;

	int nColCount = 7;
	char cCol[7][20] = {"PATHLIST_SEQNO", "SEQ", "ERA_CODE", "HIS_DATE", "REASON", "OWN_ADDRESS", "OWN_NAME"};

	//260528//AIOCR//
	if( !frmMain->m_bAIOCR )//기구축 번역본 편집//
		asSqlTbl 	= "TB_DOCUMENT08_OWNINFO_DIRECT";//241030//#구대장한글화편집#DirectTable//(지적문서 내에서 한글화 편집은 관리자만 저장)//
	else//AIOCR 번역본 편집//
		asSqlTbl 	= "TB_DOCUMENT08_AIOCR_OWNINFO";

	//---
	if(_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 0; i < nColCount; i++)
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}

		asSqlVal = asSqlVal + "(";
		//210605//asSqlVal = asSqlVal + "'" + asPathName + "', ";
		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo) + ", ";//210605//
		asSqlVal = asSqlVal + IntToStr(frmResultList->sgOwnInfo->ColCount - 1 - _nCol) + ", ";

		//[TODO]서기변환//
//		asStr = frmResultList->sgOwnInfo->Cells[_nCol][1];
//		asStr = frmMain->funcChangeDateStrFormatDate(asStr.c_str());
		asSqlVal = asSqlVal + "'', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][0];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][1];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][2];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][3];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + "'" + asStr + "')";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlVal);
	}
	else if(_nType == DF_UPDATE_RECORD)//UPDATE
	{
		//210605//asWhere  = asWhere + cCol[0] + " = '" + asPathName + "' ";
		asWhere  = asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
		asWhere  = asWhere + "AND " + cCol[1] 	+ " = " + IntToStr(frmResultList->sgOwnInfo->ColCount - 1 - _nCol);

		//[TODO]서기변환//
		nRow	= 0;
//		asStr = frmResultList->sgOwnInfo->Cells[_nCol][1];
//		asStr = frmMain->funcChangeDateStrFormatDate(asStr.c_str());

		asSqlVal = asSqlVal + cCol[2] + " = '', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][nRow++];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[3] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][nRow++];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[4] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][nRow++];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[5] + " = '" + asStr + "', ";
		asStr	= frmResultList->sgOwnInfo->Cells[_nCol][nRow++];
		if(asStr == "-")	asStr	= "";
		asSqlVal = asSqlVal + cCol[6] + " = '" + asStr + "'";

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlVal, asWhere);
	}
	else if(_nType == DF_DELETE_RECORD)//DELETE
	{
		//210605//asWhere = asWhere + cCol[0] + " = '" + asPathName + "' ";
		asWhere = asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";
		asWhere	= asWhere + "AND " + cCol[1] 	+ " = " + IntToStr(_nCol + 1);
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}
	//210705//
	else if(_nType == DF_DELETE_RECORD_ALL)//DELETE_ALL
	{
		asWhere	= asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}

	frmResultList->m_asQryToSave	= asSqlQry;//210617//
	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcReadSejongPnu(char *cQry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);//v1.0.0.5//Bug Fixed.//
	//if(m_hStmt) SQLCloseCursor(m_hStmt);

	frmMain->mvResultSejongPnu.clear();

	SEJONG_PNU_STRUCT mTempSejongPnu;
	memset(&mTempSejongPnu, 0x00, sizeof(SEJONG_PNU_STRUCT));

	SQLINTEGER m_nVal[2];//v1.0.0.5//DBSync//3->2//SQLINTEGER m_nVal[3];//Minji_#00_Sejong//org//3
	SQLRETURN ret;

	memset(m_nVal, 0x00, sizeof(m_nVal));

	int nIndex = 1;

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSejongPnu.cPnuOld  		, sizeof(mTempSejongPnu.cPnuOld)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSejongPnu.cPnuNew 		, sizeof(mTempSejongPnu.cPnuNew)   		, &m_nVal[nIndex-1]); nIndex++;
	//v1.0.0.5//DBSync//SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, mTempSejongPnu.cOldCaption 	, sizeof(mTempSejongPnu.cOldCaption)   	, &m_nVal[nIndex-1]); nIndex++;

	ret = SQLPrepare(m_hStmt, (SQLCHAR *)cQry, SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if ((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	memset(&mTempSejongPnu, 0x00, sizeof(SEJONG_PNU_STRUCT));
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		frmMain->mvResultSejongPnu.push_back(mTempSejongPnu);
		memset(&mTempSejongPnu, 0x00, sizeof(SEJONG_PNU_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcSQLInsertLandInfo()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asSqlTbl 	= "LAND_INFO";
	AnsiString  asSqlQry	= "";
	AnsiString  asSqlCol	= "";
	AnsiString  asSqlValues	= "";
	int nColCount = 4;
	char cCol[4][20] = {"LAND_CD", "X", "Y", "YEAR"};

	AnsiString asLandCd	= "";
	AnsiString asYear  	= "2019";
	double X = 0;
	double Y = 0;

	for(int i = 0; i < nColCount; i++)
	{
		asSqlCol = asSqlCol + cCol[i];
		if(i != nColCount - 1)
			asSqlCol = asSqlCol + ", ";
	}

	for(int i = 0; i < (int)frmMain->m_vSHPPOLYCBND.size() ; i++)
	{
		asSqlQry 	= "";
		asSqlValues = "";

		asSqlValues = asSqlValues + "('" + frmMain->m_v_READCBND[i].PNU + "', ";
		asSqlValues = asSqlValues + frmMain->m_vSHPPOLYCBND[i].x + ", ";
		asSqlValues = asSqlValues + frmMain->m_vSHPPOLYCBND[i].y + ", ";
		asSqlValues = asSqlValues + "'" + asYear + "')";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlValues);

		func_QryProcess(asSqlQry);
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcQryInsertDoc8Jumin(AnsiString _asDBStr)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString 	asSqlTbl 	= "TB_DOCUMENT08";
	AnsiString  asSqlQry	= "";
	AnsiString  asSqlCol	= "";
	AnsiString 	asSqlWhere 	= "";
	AnsiString  asSqlValues	= "";
	int nColCount = 4;
	char cCol[4][20] = {"PNU", "PATH_NAME", "JUMIN_YN", "JUMIN_XY"};
	AnsiString  asPathName	= StringReplace(frmMain->m_asDocDBPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);

	//Query Column
	asSqlCol = asSqlCol + cCol[2] 	+ " = '1',";// + 1 		+ ", ";
	asSqlCol = asSqlCol + cCol[3] 	+ " = '" + _asDBStr + "'";

	//Where condition
	AnsiString asCol = cCol[0];
	asSqlWhere = asSqlWhere + cCol[0] + " = '" + frmMain->m_asSearchPnu + "'" ;//
	asSqlWhere = asSqlWhere + " AND " + cCol[1] + " = '" + asPathName + "'" ;

	asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);

	if(func_QryProcess(asSqlQry))
	{
		DOCUMENT08_STRUCT	*mDoc8Struct = (DOCUMENT08_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
		strcpy(mDoc8Struct->JUMIN_YN, "1");
		strcpy(mDoc8Struct->JUMIN_XY, _asDBStr.c_str());
	}

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------


//===========================================================================
// 비암호화 문서 암호화 처리 후 로그기록 - 테이블 생성
//===========================================================================
void __fastcall TfrmSql::funcSQLCreateTableDecryptFile()
{
	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	AnsiString asSql 	= "";
	AnsiString asSqlCol = "";
	AnsiString asSqlTbl = "TB_DECRYPTFILE";

	//
	asSqlCol = asSqlCol + "(DOC_NO        		INT			     NOT NULL,"; //문서번호//
	asSqlCol = asSqlCol + "PATH_NAME	        VARCHAR(255)     NOT NULL)"; //파일경로명//
	asSqlCol = asSqlCol + " ENGINE=MyISAM ROW_FORMAT=DYNAMIC CHARSET=utf8 COLLATE=utf8_general_ci;";

	asSql.sprintf("CREATE TABLE IF NOT EXISTS %s.%s %s", frmMain->_DATABASE_, asSqlTbl, asSqlCol);

	//241125//
	if ( !func_QryProcess(asSql) ) {
		String sMsg = L"TABLE " + (String)asSqlTbl + L" 생성하지 못했습니다.";
		frmMsg->funcMessageDlg("알림:", sMsg.w_str(), 2);
	}
	if (m_hStmt)		SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

int __fastcall TfrmSql::funcSQLInsertDecryptFile(int _nType)
{
	AnsiString 	asSqlTbl 	= "TB_DECRYPTFILE";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
	AnsiString 	asSqlValues	= "";
	AnsiString  asSqlQry	= "";
	AnsiString 	asPathName 	= "";

	char cCol[2][20] = {"DOC_NO", "PATH_NAME"};

	//Query Column
	asPathName = frmMain->m_asCurrentFilePath;
	asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);

	if(_nType == DF_NEW_RECORD)
	{
		asSqlCol 	= asSqlCol + cCol[0] + ", " + cCol[1];
		asSqlValues = asSqlValues + IntToStr(frmMain->m_nViewDocNo) + ", '" + asPathName + "'";
		//
		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES (%s)", asSqlTbl, asSqlCol, asSqlValues);
	}
	else if(_nType == DF_DELETE_RECORD)
	{
		//Where condition
		asSqlWhere = asSqlWhere + "PATH_NAME = '" + asPathName + "'" ;
        //
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);
	}

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//231118//#CODE_UNITY#//1~5, 11, 12, 14 => moved to funcSQLCheckTable//
//210220//TABLE or COLUMN or DATA 확인//
int __fastcall TfrmSql::funcExistsDBTableColumnData(int _nType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[17+1];
	SQLINTEGER 	m_nVal;
	AnsiString 	asSqlTbl	= "";
	AnsiString  asSqlQry  	= "";
	AnsiString  asWhere  	= "";
	char 		min_cValue[16+1];
	AnsiString  result 		= "";
	int			nCount		= 0;

	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, m_cVal, sizeof(m_cVal), &m_nVal);

//======================================
//230207//funcSetUserHistState()Param변경//
	if(_nType == 6)
	{
		asSqlTbl	= "CD_KIND";
		asWhere		= "TASK_CODE='503' AND LENGTH(KIND_CODE)=1";
	}
	else if(_nType == 7)//210303//#TB_COPY_DNLD
	{
		asSqlTbl	= "CD_KIND";
		asWhere		= "TASK_CODE='503'";
	}
	else if(_nType == 9)//220215//COPY_LMREQ_DATA//
	{
		asSqlTbl	= "CD_KIND";
		asWhere		= "TASK_CODE='905' AND DOC_NAME = ''";
	}
	else if(_nType == 10)//220215//COPY_LMREQ_DATA//
	{
		asSqlTbl	= "CD_KIND";
		asWhere		= "TASK_CODE='905' AND KIND_CODE='03'";
	}
	else if(_nType == 13)//231020//GAGAMLAYER in LandArchive
	{
		asSqlTbl	= "CD_KIND";
		asWhere		= "TASK_CODE='020'";
	}
	//====================================================

	asSqlQry.sprintf("SELECT COUNT(*) FROM %s WHERE %s", asSqlTbl, asWhere);

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
		return 0;
	}

	memset(m_cVal,0x00,sizeof(m_cVal));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		memset(min_cValue, 0x00, sizeof(min_cValue));
		memcpy(min_cValue, m_cVal, sizeof( min_cValue));
		result = min_cValue;
		if(!result.IsEmpty())
			nCount = result.ToInt();
		break;
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nCount;
}
//---------------------------------------------------------------------------

//210220//TABLE or COLUMN or DATA 정리//
int __fastcall TfrmSql::funcChangeDBTableColumnData(int _nType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//SQLQuery
	AnsiString  asSqlQry	    = "";

	//Column Name
	if(_nType == 4)//210303//#USER1_PW
		asSqlQry.sprintf("ALTER TABLE TB_USER1 CHANGE FT_PW VARCHAR(256) NULL DEFAULT NULL COMMENT '비밀번호암호화'");
	else if(_nType == 5)//210303//#USER1_PW
		asSqlQry.sprintf("UPDATE TB_USER1 SET FT_PW=SHA2(FT_PW, 256)");
//======================================
//230207//funcSetUserHistState()Param변경//
//	else if(_nType == 6)//210303//#503
//		asSqlQry.sprintf("UPDATE CD_KIND SET KIND_CODE=SUBSTR(KIND_CODE, 2, 1) WHERE TASK_CODE='503' AND KIND_CODE LIKE '0%'");
	else if(_nType == 6)//210303//#503
		asSqlQry.sprintf("UPDATE CD_KIND SET KIND_CODE=LAPD(KIND_CODE, 2, '0') WHERE TASK_CODE='503' AND KIND_CODE NOT LIKE '0%'");
//======================================
	else if(_nType == 7)//210303//#503
		asSqlQry.sprintf("DELETE FROM CD_KIND WHERE TASK_CODE='503'");
	else if(_nType == 8)//210401//#DAUM_OPENAPI_KEY//
		asSqlQry.sprintf("UPDATE TB_SPATIALMAIN SET USE_VALUE='e96aa296ff3674b0e53808c9bef68a4e' WHERE USE_GBN='KAKAOMAP_OPENAPI_KEY'");
	else if(_nType == 9)//220215//COPY_LMREQ_DATA//
		asSqlQry.sprintf("UPDATE CD_KIND SET DOC_NAME = '토지이동신청_처리구분' WHERE TASK_CODE = '905' AND DOC_NAME = ''");
	else if(_nType == 10)//220215//COPY_LMREQ_DATA//
		asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('905', '03', '처리완료', '토지이동신청_처리구분') ");
	else if(_nType == 13)//221128//#DOC08_MEMO_SIZE//
		asSqlQry.sprintf("ALTER TABLE TB_OLDLANDDOC_INFO MODIFY MEMO VARCHAR(96) DEFAULT NULL COMMENT '적요'");
	//====================================================
	//230214//TB_COPY_DOC08.ACTION_DT 14로 되어 있는 경우가 존재하여 체크하여 변경//
	else if(_nType == 14)//230214//TB_COPY_DOC08.ACTION_DT//
		asSqlQry.sprintf("ALTER TABLE TB_COPY_DOC08 MODIFY ACTION_DT VARCHAR(19) DEFAULT NULL COMMENT '열람/인쇄시각'");
	//====================================================
//v1.0.0.5//230620//로드뷰주소변경//
	else if(_nType == 17)
		asSqlQry.sprintf("UPDATE TB_SPATIALMAIN SET USE_VALUE='roadview.itkor.co.kr/naver' WHERE USE_GBN='ROADVIEW' AND USE_NAME='NAVER'");
	else if(_nType == 18)
		asSqlQry.sprintf("UPDATE TB_SPATIALMAIN SET USE_VALUE='roadview.itkor.co.kr/loadview_kakao1' WHERE USE_GBN='ROADVIEW' AND USE_NAME='DAUM'");
//=============================================================================
//231030//GAGAMLAYER in LandArchive//
//=============================================================================
	else if(_nType == 19)
		asSqlQry.sprintf("INSERT INTO TB_SPATIALCODECONVERT VALUES ('ETC','가감대장','ETC_GAGAM_LAYER','ETC_GAGAM_LAYER')");
	else if(_nType == 20)
		asSqlQry.sprintf("INSERT INTO TB_SPATIALCONFIG VALUES ('ETC', '가감대장', '가감대장', 1, 5, 1, 5, 255, '나눔고딕', 0, 0, 1, 0, 0, 'SOLID')");
//=============================================================================

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------
//210401//TABLE or COLUMN or DATA 확인//
int __fastcall TfrmSql::funcCheckDBTableColumnData(int _nType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR    	m_cVal[50+1];
	SQLINTEGER 	m_nVal;
	AnsiString 	asSqlTbl	= "";
	AnsiString 	asSqlCol	= "";
	AnsiString  asSqlQry  	= "";
	AnsiString  asWhere  	= "";
	char 		min_cValue[50+1];
	AnsiString  result 		= "";
	int			nResult		= 0;

	SQLBindCol(m_hStmt, 1, SQL_C_CHAR, m_cVal, sizeof(m_cVal), &m_nVal);

	if(_nType == 8)//#DAUM_OPENAPI_KEY//
	{
		asSqlTbl	= "TB_SPATIALMAIN";
		asSqlCol    = "USE_VALUE";
		asWhere		= "USE_GBN = 'KAKAOMAP_OPENAPI_KEY'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	//====================================================
	else if(_nType == 13)//221128//#DOC08_MEMO_SIZE//
	{
		asSqlTbl	= "INFORMATION_SCHEMA.columns";
		asSqlCol    = "CHARACTER_MAXIMUM_LENGTH";
		asWhere		= "table_name='TB_OLDLANDDOC_INFO' and column_name='MEMO'";
		asWhere		= asWhere + " AND table_schema='" + frmMain->_DATABASE_ + "'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	//====================================================
	//230214//TB_COPY_DOC08.ACTION_DT 14로 되어 있는 경우가 존재하여 체크하여 변경//
	else if(_nType == 14)//230214//TB_COPY_DOC08.ACTION_DT//
	{
		asSqlTbl	= "INFORMATION_SCHEMA.columns";
		asSqlCol    = "CHARACTER_MAXIMUM_LENGTH";
		asWhere		= "table_name='TB_COPY_DOC08' and column_name='ACTION_DT'";
		asWhere		= asWhere + " AND table_schema='" + frmMain->_DATABASE_ + "'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	//====================================================
//v1.0.0.5//230620//로드뷰주소변경//
	else if(_nType == 17)
	{
		asSqlTbl	= "TB_SPATIALMAIN";
		asSqlCol    = "USE_VALUE";
		asWhere		= "USE_GBN='ROADVIEW' AND USE_NAME='NAVER'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	else if(_nType == 18)
	{
		asSqlTbl	= "TB_SPATIALMAIN";
		asSqlCol    = "USE_VALUE";
		asWhere		= "USE_GBN='ROADVIEW' AND USE_NAME='DAUM'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	//====================================================
//=============================================================================
//231030//GAGAMLAYER in LandArchive//
//=============================================================================
	else if(_nType == 19)//TB_SPATIALCODECONVERT//
	{
		asSqlTbl	= "TB_SPATIALCODECONVERT";
		asSqlCol    = "COUNT(*)";
		asWhere		= "LAYERGBN = 'ETC' AND KOREANAME='가감대장'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	else if(_nType == 20)//TB_SPATIALCONFIG//
	{
		asSqlTbl	= "TB_SPATIALCONFIG";
		asSqlCol    = "COUNT(*)";
		asWhere		= "LAYERGBN = 'ETC' AND LAYERPARENT='가감대장'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	//====================================================
	//260611//AIOCR//기구축DB 테이블 여부 확인//m_bAIOCR//
	else if(_nType == 21)//TB_DOCUMENT08_HIS//
	{
		asSqlTbl	= "INFORMATION_SCHEMA.tables";
		asSqlCol    = "table_rows";
		asWhere		= "table_name='TB_DOCUMENT08_HIS'";
		asWhere		= asWhere + " AND table_schema='" + frmMain->_DATABASE_ + "'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	else if(_nType == 22)//TB_DOCUMENT08_OWNINFO//
	{
		asSqlTbl	= "INFORMATION_SCHEMA.tables";
		asSqlCol    = "table_rows";
		asWhere		= "table_name='TB_DOCUMENT08_OWNINFO'";
		asWhere		= asWhere + " AND table_schema='" + frmMain->_DATABASE_ + "'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	else if(_nType == 23)//TB_DOCUMENT08_SHAREOWN//
	{
		asSqlTbl	= "INFORMATION_SCHEMA.tables";
		asSqlCol    = "table_rows";
		asWhere		= "table_name='TB_DOCUMENT08_SHAREOWN'";
		asWhere		= asWhere + " AND table_schema='" + frmMain->_DATABASE_ + "'";
		asSqlQry.sprintf("SELECT %s FROM %s WHERE %s", asSqlCol, asSqlTbl, asWhere);
	}
	//====================================================

	SQLRETURN ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
		return 0;
	}

	memset(m_cVal,0x00,sizeof(m_cVal));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		memset(min_cValue, 0x00, sizeof(min_cValue));
		memcpy(min_cValue, m_cVal, sizeof( min_cValue));
		result = min_cValue;
		if(_nType == 8)//#DAUM_OPENAPI_KEY//
		{
			if(result == "5e65e32947339585675a1e6220271bcd")
				nResult = 1;
		}
		else if(_nType == 13)//221128//#DOC08_MEMO_SIZE//40->96
		{
			if(!result.IsEmpty())
				nResult = result.ToInt();
		}
//====================================================
//v1.0.0.5//230620//로드뷰주소변경//
		else if(_nType == 17)
		{
			if(result == "roadview.itkor.co.kr/naver")
				nResult = 1;
		}
		else if(_nType == 18)
		{
			if(result == "roadview.itkor.co.kr/loadview_kakao1")
				nResult = 1;
		}
//====================================================
//=============================================================================
//231030//GAGAMLAYER in LandArchive//
//=============================================================================
		else if(_nType == 19)//TB_SPATIALCODECONVERT//
		{
			if(!result.IsEmpty())
				nResult = result.ToInt();
        }
		else if(_nType == 20)//TB_SPATIALCONFIG//
		{
			if(!result.IsEmpty())
				nResult = result.ToInt();
        }
		//====================================================
		//260702//AIOCR//기구축DB 테이블 여부 확인//m_bAIOCR//
		//====================================================
		else if(_nType == 21)//TB_DOCUMENT08_HIS//
		{
			if(!result.IsEmpty())
				nResult = result.ToInt();
		}
		else if(_nType == 22)//TB_DOCUMENT08_OWNINFO//
		{
			if(!result.IsEmpty())
				nResult = result.ToInt();
		}
		else if(_nType == 23)//TB_DOCUMENT08_SHAREOWN//
		{
			if(!result.IsEmpty())
				nResult = result.ToInt();
		}
		//====================================================
		break;
	};
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	return nResult;
}
//---------------------------------------------------------------------------

//231030//Param 추가//210303//#503//DATA INSERT//
void __fastcall TfrmSql::funcInsertDBDataCdKind(int _nType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//SQLQuery
	AnsiString  asSqlQry	    = "";

//231030//Simply//
	if(_nType == 503)
	{
		asSqlQry = "INSERT INTO CD_KIND VALUES ";
		asSqlQry += "('503','00','로그인시각','사용자별 행위구분'),";
		asSqlQry += "('503','01','검색','사용자별 행위구분'),";
		asSqlQry += "('503','02','수정','사용자별 행위구분'),";
		asSqlQry += "('503','03','삭제','사용자별 행위구분'),";
		asSqlQry += "('503','04','인쇄','사용자별 행위구분'),";
		asSqlQry += "('503','05','문서열람','사용자별 행위구분'),";
		asSqlQry += "('503','06','등록','사용자별 행위구분'),";
		asSqlQry += "('503','07','파일저장','사용자별 행위구분'),";
		asSqlQry += "('503','08','통계','사용자별 행위구분'),";
		asSqlQry += "('503','09','로그아웃시각','사용자별 행위구분'),";
		asSqlQry += "('503','10','사용승인','사용자별 행위구분'),";
		asSqlQry += "('503','11','권한변경','사용자별 행위구분'),";
		asSqlQry += "('503','12','휴면계정','사용자별 행위구분'),";
		asSqlQry += "('503','13','비밀번호변경','사용자별 행위구분'),";
		asSqlQry += "('503','14','삭제계정','사용자별 행위구분'),";
		asSqlQry += "('503','15','비밀번호초기화','사용자별 행위구분');";
	}
	else if(_nType == 20)
	{
		asSqlQry = "INSERT INTO CD_KIND VALUES ";
		asSqlQry += "('020', '01', '가감대장', '가감대장'),";
		asSqlQry += "('020', '02', '가감도면', '가감대장'),";
		asSqlQry += "('020', '03', '구비서류', '가감대장');";
	}
	//========================
	//Common
	func_QryProcess(asSqlQry);
	//========================

//OLD//
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','00','로그인시각','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','01','검색','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','02','수정','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','03','삭제','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','04','인쇄','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','05','문서열람','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','06','등록','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','07','파일저장','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','08','통계','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','09','로그아웃시각','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	//231012//10누락//
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','10','사용승인','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','11','권한변경','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','12','휴면계정','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','13','비밀번호변경','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	//210323//
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','14','삭제계정','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
//	//210331//
//	asSqlQry.sprintf("INSERT INTO CD_KIND VALUES ('503','15','비밀번호초기화','사용자별 행위구분')");
//	func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSql::funcInsertDBDataTbSpatialFontsize(int _nType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//SQLQuery
	AnsiString  asSqlQry	    = "";

	if(_nType == 1)//231030//GAGAMLAYER in LandArchive//
	{
		asSqlQry = "INSERT INTO TB_SPATIALFONTSIZE VALUES ";
		asSqlQry += "('가감대장', 1, 11),";
		asSqlQry += "('가감대장', 2, 12),";
		asSqlQry += "('가감대장', 3, 13),";
		asSqlQry += "('가감대장', 4, 14),";
		asSqlQry += "('가감대장', 5, 15),";
		asSqlQry += "('가감대장', 6, 16),";
		asSqlQry += "('가감대장', 7, 17),";
		asSqlQry += "('가감대장', 8, 18),";
		asSqlQry += "('가감대장', 9, 19),";
		asSqlQry += "('가감대장', 10, 20);";
	}
	func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//==================================================
//파일저장 다운로드사유 데이터 관리 테이블 생성//210303//#TB_COPY_DNLD
//==================================================
void __fastcall TfrmSql::funcSQLCreateTbCopyDnld()
{
	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	SQLRETURN sRet;
	AnsiString asSql 	= "";
	AnsiString asSqlCol = "";

	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	// main query
	asSqlCol = asSqlCol + "(SEQNO INT(11) NOT NULL AUTO_INCREMENT COMMENT 'SEQNO',";
	asSqlCol = asSqlCol + "FT_ID VARCHAR(32) NULL DEFAULT NULL COMMENT '사용자ID',";
	asSqlCol = asSqlCol + "FT_NAME VARCHAR(64) NULL DEFAULT NULL COMMENT '사용자명',";
	asSqlCol = asSqlCol + "FT_DOC INT NULL DEFAULT NULL COMMENT '문서번호',";
	asSqlCol = asSqlCol + "FT_KINDNAME VARCHAR(23) NULL DEFAULT NULL COMMENT '문서구분명',";
	asSqlCol = asSqlCol + "FT_REASON VARCHAR(40) NULL DEFAULT NULL COMMENT '사유',";
	asSqlCol = asSqlCol + "FT_ACTIONDATE VARCHAR(20) NULL DEFAULT NULL COMMENT '다운로드 시각',";
	asSqlCol = asSqlCol + "FT_PATHNAME VARCHAR(255) NULL DEFAULT NULL COMMENT '파일경로명',";
	asSqlCol = asSqlCol + "PRIMARY KEY (SEQNO))";
	asSqlCol = asSqlCol + " ENGINE=MyISAM ROW_FORMAT=DYNAMIC CHARSET=utf8 COLLATE=utf8_general_ci;";

	asSql.sprintf("CREATE TABLE %s.%s %s", frmMain->_DATABASE_, "TB_COPY_DNLD", asSqlCol);

	sRet = SQLPrepare(m_hStmt, (SQLCHAR*)asSql.c_str(), SQL_NTS);
	sRet = SQLExecute(m_hStmt);

	if (sRet != SQL_SUCCESS) {
		SQLCloseCursor(m_hStmt);
		return;
	}

	if (m_hStmt)		SQLCloseCursor(m_hStmt);
}
// ---------------------------------------------------------------------------

//==================================================
//파일저장 다운로드사유 데이터 관리 테이블 생성//210303//#TB_COPY_DNLD
//==================================================
int __fastcall TfrmSql::funcSQLWriteTbCopyDnld(int _nType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//SQLQuery
	AnsiString 	asSqlTbl 	    = "TB_COPY_DNLD";
	AnsiString 	asSqlCol 	    = "";
	AnsiString 	asSqlVal 	    = "";
	AnsiString 	asSqlWhere 	    = "";
	AnsiString  asSqlQry	    = "";

	//Column Name
	int nColCount = 8;
	char cCol[8][20] = {"SEQNO", "FT_ID", "FT_NAME", "FT_DOC", "FT_KINDNAME", "FT_REASON", "FT_ACTIONDATE", "FT_PATHNAME"};

	//Inputed Data
	AnsiString 	asUserId 		= frmMain->m_asCurrentId;
	AnsiString 	asUserName 		= frmMain->m_asCurrentNm;
	AnsiString 	asKindName 		= frmMain->m_asDownloadKindName;
	AnsiString 	asReason 		= frmMain->edtDownloadReason->Text;
	AnsiString 	asActionDt 		= Now().FormatString("yyyy-mm-dd hh:mm:ss");
	AnsiString 	asPathName 		= frmMain->m_asCurrentFilePath;
	AnsiString  asStr 			= "";
	int nDocNum	= eTree->funcClickNodeToDocNum(frmMain->mSearchNode.tSelectNode);

	//데이터 예외처리는 이 함수 호출전에 이미 하고 들어옴//
	asPathName = StringReplace(asPathName, "\\", "/", TReplaceFlags() << rfReplaceAll);

	if (_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 1; i < nColCount; i++)//SEQNO제외//
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}

		asSqlVal = asSqlVal + "(";
		asSqlVal = asSqlVal + "'" + asUserId + "', ";
		asSqlVal = asSqlVal + "'" + asUserName + "', ";
		asSqlVal = asSqlVal + IntToStr(nDocNum) + ", ";
		asSqlVal = asSqlVal + "'" + asKindName + "', ";
		asSqlVal = asSqlVal + "'" + asReason + "', ";
		asSqlVal = asSqlVal + "'" + asActionDt + "', ";
		asSqlVal = asSqlVal + "'" + asPathName + "');";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlVal);
	}

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//==================================================
//구대장 한글화 문서 열람 및 인쇄 데이터 관리 테이블 생성//220121//#TB_COPY_DOC08
//==================================================
void __fastcall TfrmSql::funcSQLCreateTbCopyDoc08()
{
	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	SQLRETURN sRet;
	AnsiString asSql 	= "";
	AnsiString asSqlCol = "";

	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	// main query
	asSqlCol = asSqlCol + "(SEQNO INT(11) NOT NULL AUTO_INCREMENT COMMENT 'SEQNO',";
	asSqlCol = asSqlCol + "TYPE VARCHAR(1) NULL DEFAULT NULL COMMENT '1:열람, 2:인쇄',";
	asSqlCol = asSqlCol + "ACTION_DT VARCHAR(19) NULL DEFAULT NULL COMMENT '열람/인쇄시각',";
	asSqlCol = asSqlCol + "USERNAME VARCHAR(64) NULL DEFAULT NULL COMMENT '사용자명',";
	asSqlCol = asSqlCol + "PNU VARCHAR(19) NULL DEFAULT NULL COMMENT 'PNU 19자리',";
	asSqlCol = asSqlCol + "PATHLIST_SEQNO INT(11) NULL DEFAULT NULL COMMENT 'TB_OLDLANDDOC_PATHLIST.SEQNO',";
	asSqlCol = asSqlCol + "PRIMARY KEY (SEQNO))";
	asSqlCol = asSqlCol + " ENGINE=MyISAM ROW_FORMAT=DYNAMIC CHARSET=utf8 COLLATE=utf8_general_ci;";

	asSql.sprintf("CREATE TABLE %s.%s %s", frmMain->_DATABASE_, "TB_COPY_DOC08", asSqlCol);

	sRet = SQLPrepare(m_hStmt, (SQLCHAR*)asSql.c_str(), SQL_NTS);
	sRet = SQLExecute(m_hStmt);

	if (sRet != SQL_SUCCESS) {
		SQLCloseCursor(m_hStmt);
		return;
	}

	if (m_hStmt)		SQLCloseCursor(m_hStmt);
}
// ---------------------------------------------------------------------------

//==================================================
//구대장 한글화 문서 열람 및 인쇄 데이터 관리 테이블 생성//220121//#TB_COPY_DOC08
//return value : current seqno
//==================================================
int __fastcall TfrmSql::funcSQLWriteTbCopyDoc08(int _nType, int _nActionType)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	//SQLQuery
	AnsiString 	asSqlTbl 	    = "TB_COPY_DOC08";
	AnsiString 	asSqlCol 	    = "";
	AnsiString 	asSqlVal 	    = "";
	AnsiString 	asSqlWhere 	    = "";
	AnsiString  asSqlQry	    = "";
	int			nSEQNO			= 0;

	//Column Name
	int nColCount = 6;
	char cCol[6][20] = {"SEQNO", "TYPE", "ACTION_DT", "USERNAME", "PNU", "PATHLIST_SEQNO"};

	//Inputed Data
	AnsiString 	asUserName 		= frmMain->m_asCurrentNm;
	AnsiString 	asKindName 		= frmMain->m_asDownloadKindName;
	AnsiString 	asReason 		= frmMain->edtDownloadReason->Text;
	AnsiString 	asActionDt 		= Now().FormatString("yyyy-mm-dd hh:mm:ss");

	if (_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 1; i < nColCount; i++)//SEQNO제외//
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}

		asSqlVal = asSqlVal + "(";
		asSqlVal = asSqlVal + IntToStr(_nActionType) + ", ";
		asSqlVal = asSqlVal + "'" + asActionDt + "', ";
		asSqlVal = asSqlVal + "'" + asUserName + "', ";
		asSqlVal = asSqlVal + "'" + frmMain->m_asLandCd + "', ";//250709//m_asSearchPnu => m_asLandCd
		asSqlVal = asSqlVal + "'" + frmMain->m_nPathListSeqNo + "');";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlVal);


		//250708//DEBUG//TB_COPY_DOC08 저장 시 PNU 없는 필지들 발생//
		//구대장열람 > 이전/다음이미지 열람 시 Pnu 가져오지 않음//
		//구대장상세검색 > 열람 시 Pnu 가져오지 않음//

		if(frmMain->m_asLandCd.Length() != 19)
			int a = 1;


	}

	//return func_QryProcess(asSqlQry);
	if(func_QryProcess(asSqlQry) && _nActionType == 3)
	{
		asSqlWhere	= "TYPE = '" + IntToStr(_nActionType) + "' ";
		asSqlWhere	+= "AND ACTION_DT = '" + asActionDt + "' ";
		asSqlWhere	+= "AND USERNAME = '" + asUserName + "'";

		asSqlQry.sprintf("SELECT SEQNO FROM %s WHERE %s", asSqlTbl, asSqlWhere);

		nSEQNO	= funcSQLReadCount(asSqlQry);
	}

	return nSEQNO;
}
//---------------------------------------------------------------------------

//221020//Get INI Data -> DB Data//지적단위, 과세단위 등 DB에 설정된 값으로 읽어오는 함수//
//===========================================================================
// READ TB_OLDLANDDOC_USERFAVORTIES
//===========================================================================
void __fastcall TfrmSql::funcSQLReadOldLandDocUserFavoritesAll()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLINTEGER 	m_nVal[5];
	SQLRETURN 	ret;
	AnsiString 	asSqlQry	= "";
	AnsiString 	asWhere		= "";
	AnsiString 	asOrderBy	= "";//220119//
	OLDLANDDOC_USERFAVORITES_STRUCT 	tempData;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempData, 0, sizeof(OLDLANDDOC_USERFAVORITES_STRUCT));

	int nIndex = 1;
	SQLBindCol(m_hStmt, nIndex, SQL_C_LONG, &tempData.SEQNO, 		sizeof(tempData.SEQNO), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.CATEGORY, 		sizeof(tempData.CATEGORY), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.DATA, 			sizeof(tempData.DATA), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.WRITE_ID, 		sizeof(tempData.WRITE_ID), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(m_hStmt, nIndex, SQL_C_CHAR, tempData.WRITE_DT, 		sizeof(tempData.WRITE_DT), 		&m_nVal[nIndex - 1]);		nIndex++;

	asOrderBy	= " ORDER BY CATEGORY, SEQ ASC";
	asWhere		= " WHERE WRITE_ID=''";
	asSqlQry	= "SELECT * FROM TB_OLDLANDDOC_USERFAVORITES" + asWhere + asOrderBy;

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vAREAUNIT.clear();//220119//
	frmMain->m_vVALUEUNIT.clear();//220119//
	frmMain->m_vVALUE2UNIT.clear();//220119//
	frmMain->m_vREASONDATA.clear();//220119//

	memset(&tempData, 0, sizeof(tempData));
	while(SQLFetch(m_hStmt)!=SQL_NO_DATA)
	{
		if( !strcmp(tempData.CATEGORY, "지적") )
			frmMain->m_vAREAUNIT.push_back(tempData);
		else if( !strcmp(tempData.CATEGORY, "과세") )
			frmMain->m_vVALUEUNIT.push_back(tempData);
		else if( !strcmp(tempData.CATEGORY, "과세2") )
			frmMain->m_vVALUE2UNIT.push_back(tempData);
		else if( !strcmp(tempData.CATEGORY, "사고개행") )
			frmMain->m_vREASONDATA.push_back(tempData);
		memset(&tempData, 0, sizeof(OLDLANDDOC_USERFAVORITES_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//==========================================================================
// 가감대장 TB_DOCUMENT20_LANDLIST.GAGAM_NO
//==========================================================================
bool __fastcall TfrmSql::funcSQLGetGagamNoFromLandCd(AnsiString _asLandCd)
{
	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	AnsiString 	asSqlQry = "";
	SQLRETURN 	ret;
	SQLINTEGER 	m_nVal[1];
	int			nVal;
	bool		bReturn = false;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	SQLBindCol(m_hStmt, 1,  SQL_C_LONG, &nVal, sizeof(nVal) , &m_nVal[0]);

	asSqlQry	= "SELECT GAGAM_NO FROM TB_DOCUMENT20_LANDLIST WHERE LAND_CD = '" + _asLandCd + "'";

	ret    	= SQLPrepare(m_hStmt, (SQLCHAR*)asSqlQry.c_str(), SQL_NTS);
	ret		= SQLExecute(m_hStmt);

	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(m_hStmt);
		return false;
	}

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		bReturn = (nVal >= 1) ? (true) : (false);
	};

	if (m_hStmt)	SQLCloseCursor(m_hStmt);

	return bReturn;
}
//---------------------------------------------------------------------------

//=============================================================================
//231030//GAGAMLAYER in LandArchive//가감대장 기준점 좌표 자료 가져오기//
//=============================================================================
void __fastcall TfrmSql::funcReadGagamBasePoint()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     = "";
	AnsiString  asSqlQry  = "";
	SQLINTEGER 	m_nVal[6];
	SQLRETURN 	ret;
	DOCUMENT20_BASEPOINT_STRUCT		tempData;
	int nIndex = 1;

	memset(&tempData, 0x00, sizeof(DOCUMENT20_BASEPOINT_STRUCT));
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	&tempData.POINT_NO, 	sizeof(tempData.POINT_NO), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.POINT_NAME, 	sizeof(tempData.POINT_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempData.X, 			sizeof(tempData.X), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempData.Y, 			sizeof(tempData.Y), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempData.WORLD_X, 		sizeof(tempData.WORLD_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempData.WORLD_Y, 		sizeof(tempData.WORLD_X), 		&m_nVal[nIndex-1]); nIndex++;
	//---

	//asSqlQry = "SELECT * FROM TB_DOCUMENT20_BASEPOINT ORDER BY POINT_NO ASC";
	asSqlQry = "SELECT * FROM TB_DOCUMENT20_BASEPOINT ORDER BY POINT_NAME ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vGAGAMBASEPOINT.clear();

	memset(&tempData, 0x00, sizeof(DOCUMENT20_BASEPOINT_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_vGAGAMBASEPOINT.push_back(tempData);
		memset(&tempData, 0x00, sizeof(DOCUMENT20_BASEPOINT_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//=============================================================================
//241211//가감대장 심볼 표시//
//=============================================================================
void __fastcall TfrmSql::funcReadGagamList()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     	= "";
	AnsiString  asSqlQry  	= "";
	AnsiString  asTable	  	= "TB_DOCUMENT20";
	AnsiString  asWhere   	= "";
	AnsiString  asColumn  	= "KWON_NO, GAGAM_NO, DOC_NAME, SURV_ETC, PRCS_DATE, LAND_CD";
	AnsiString  asOrderBy 	= "ORDER BY LAND_CD ASC";
	SQLRETURN ret;
	DOCUMENT20_GAGAMLIST_STRUCT 	tempData;

	memset(&tempData, 0x00, sizeof(DOCUMENT20_GAGAMLIST_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[6];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.KWON_NO, 	sizeof(tempData.KWON_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.GAGAM_NO, 	sizeof(tempData.GAGAM_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.DOC_NAME, 	sizeof(tempData.DOC_NAME), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.SURV_ETC,  sizeof(tempData.SURV_ETC),  &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.PRCS_DATE, sizeof(tempData.PRCS_DATE), &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.LAND_CD, 	sizeof(tempData.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;

	//---
	asSqlQry.sprintf("SELECT DISTINCT %s FROM %s GROUP BY %s %s", asColumn, asTable, asColumn, asOrderBy);

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vGAGAMLIST.clear();

	memset(&tempData, 0x00, sizeof(DOCUMENT20_GAGAMLIST_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_vGAGAMLIST.push_back(tempData);
		memset(&tempData, 0x00, sizeof(DOCUMENT20_GAGAMLIST_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//=============================================================================
//241217//가감대 필지목록(전체)-중복제거//
//=============================================================================
void __fastcall TfrmSql::funcReadGagamLandListAll()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlQry  = "";
	SQLRETURN ret;
	DOCUMENT20_LANDLIST_STRUCT 	tempData;

	memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[1];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.LAND_CD, 	sizeof(tempData.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;
	//---

	asSqlQry 	= "SELECT DISTINCT LAND_CD FROM TB_DOCUMENT20_LANDLIST GROUP BY LAND_CD ORDER BY LAND_CD ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vGAGAMLANDLISTALL.clear();

	memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_vGAGAMLANDLISTALL.push_back(tempData);
		memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//=============================================================================
//241220//공간 > 심볼 > 현재 선택한 필지를 기준으로 모든 가감대장 지번목록 자료 가져오기//
//=============================================================================
void __fastcall TfrmSql::funcReadGagamLandList2(AnsiString _asLandCd)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     = "";
	AnsiString  asSqlQry  = "";
	AnsiString  asTable   = "TB_DOCUMENT20_LANDLIST";
	AnsiString  asColumn  = "KWON_NO, GAGAM_NO";
	AnsiString  asFromB   = "";
	AnsiString  asWhere   = "";
	AnsiString  asOrderBy = "ORDER BY A.LAND_CD ASC";
	SQLRETURN ret;
	DOCUMENT20_LANDLIST_STRUCT 	tempData;

	memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[1];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.LAND_CD, 	sizeof(tempData.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;

	//---
	asFromB.sprintf("SELECT DISTINCT %s FROM %s WHERE LAND_CD='%s' GROUP BY %s", asColumn, asTable, _asLandCd, asColumn);
	asSqlQry.sprintf("SELECT DISTINCT A.LAND_CD FROM %s A INNER JOIN (%s) B ON A.KWON_NO=B.KWON_NO AND A.GAGAM_NO=B.GAGAM_NO %s", asTable, asFromB, asOrderBy);

	//
	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vGAGAMLANDLIST.clear();

	memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_vGAGAMLANDLIST.push_back(tempData);
		memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//=============================================================================
//241210//선택된 가감대장에 속하는 필지목록만 가져온다. 그러면 채색하는 부분에서 전체필지 비교하여 채색할 필요 없음.//
//231031//GAGAMLAYER in LandArchive//가감대장 지번목록 자료 가져오기//
//=============================================================================
void __fastcall TfrmSql::funcReadGagamLandList(AnsiString _asKwonNo, AnsiString _asGagamNo)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     = "";
	AnsiString  asSqlQry  = "";
	AnsiString  asWhere   = "";
	SQLRETURN ret;
	DOCUMENT20_LANDLIST_STRUCT 	tempData;

	memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[3];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.KWON_NO, 	sizeof(tempData.KWON_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.GAGAM_NO, 	sizeof(tempData.GAGAM_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.LAND_CD, 	sizeof(tempData.LAND_CD), 	&m_nVal[nIndex-1]); nIndex++;
	//---

	asWhere		= "WHERE KWON_NO='" + _asKwonNo + "' AND GAGAM_NO=" + _asGagamNo;
	asSqlQry 	= "SELECT * FROM TB_DOCUMENT20_LANDLIST " + asWhere + " ORDER BY LAND_CD ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vGAGAMLANDLIST.clear();

	memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_vGAGAMLANDLIST.push_back(tempData);
		memset(&tempData, 0x00, sizeof(DOCUMENT20_LANDLIST_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//=============================================================================
//241210//선택된 가감대장에 속하는 기준점목록만 가져온다.//
//231031//GAGAMLAYER in LandArchive//가감대장 기준점목록 자료 가져오기//
//=============================================================================
void __fastcall TfrmSql::funcReadGagamBaseList(AnsiString _asKwonNo, AnsiString _asGagamNo)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asStr     = "";
	AnsiString  asSqlQry  = "";
	AnsiString  asWhere   = "";
	SQLRETURN ret;
	DOCUMENT20_BASELIST_STRUCT 	tempData;

	memset(&tempData, 0x00, sizeof(DOCUMENT20_BASELIST_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[5];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.KWON_NO, 	sizeof(tempData.KWON_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.GAGAM_NO, 	sizeof(tempData.GAGAM_NO), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempData.BASEPOINT, sizeof(tempData.BASEPOINT), &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempData.DIFF_X, 	sizeof(tempData.DIFF_X), &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempData.DIFF_Y, 	sizeof(tempData.DIFF_Y), &m_nVal[nIndex-1]); nIndex++;
	//---

	asWhere		= "WHERE KWON_NO='" + _asKwonNo + "' AND GAGAM_NO=" + _asGagamNo;
	asSqlQry 	= "SELECT KWON_NO, GAGAM_NO, BASEPOINT, DIFF_X, DIFF_Y FROM TB_DOCUMENT20_BASELIST " + asWhere + " ORDER BY BASEPOINT ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	frmMain->m_vGAGAMBASELIST.clear();

	memset(&tempData, 0x00, sizeof(DOCUMENT20_BASELIST_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		frmMain->m_vGAGAMBASELIST.push_back(tempData);
		memset(&tempData, 0x00, sizeof(DOCUMENT20_BASELIST_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);


}
//---------------------------------------------------------------------------


//=================================================================
//240321//INItoDB
//=================================================================
void __fastcall TfrmSql::func_readConfigIni()
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[3][50];
	SQLINTEGER m_nVal[3];

	for(int i=0; i<3; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString mSqlQry;
	SQLRETURN ret;

	mSqlQry = "SELECT * FROM TB_CONFIGINI ORDER BY USE_GBN ASC";

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)mSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString result[3];
	char temp[50];

	//=====================================================
	//241120//#DOCPOI#//울진군팀장님[REQ]//문서POI-사용자별 설정으로 표시//처음에는 설정정보 없으므로 Default는 QRYCHECK Value//
	//=====================================================
	frmChangeMenu->m_nChkPoiCnt		= 0;
	frmChangeMenu->m_nChkPoiDocNo	= -1;


	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i=0; i<3; i++){
			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
			result[i] = "";
		}
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i=0; i<3; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				result[i] = temp;
			}

			if(result[2] == "") result[2] = "0";
			else if(result[0] == "FTP")
			{
				if(result[1] == "IP")				frmMain->INIINFO.FTPIP 		= frmMain->func_Decoder(result[2]);
				else if(result[1] == "PORT")		frmMain->INIINFO.FTPPORT 	= frmMain->func_Decoder(result[2]);
				else if(result[1] == "ID")			frmMain->INIINFO.FTPID 		= frmMain->func_Decoder(result[2]);
				else if(result[1] == "PW")			frmMain->INIINFO.FTPPW 		= frmMain->func_Decoder(result[2]);
				else if(result[1] == "CONSTYLE")	frmMain->INIINFO.CONSTYLE 	= result[2];
				else if(result[1] == "ROOT")		frmMain->INIINFO.FTPROOT 	= result[2];
				else if(result[1] == "ENCRYPT")		frmMain->INIINFO.B_ENCRYPT 	= (result[2] == "1" ? true:false);
				else if(result[1] == "UPPER")		frmFtpControl->m_asUPPER 	= result[2];
			}
			else if(result[0] == "INDEX")
			{
				if(result[1] == "SHOW")				frmMain->INIINFO.B_INDEX 		= (result[2] == "1" ? true:false);
				else if(result[1] == "LEVEL")		frmMain->INIINFO.INDEX_LEVEL 	= result[2].ToInt();
			}
			else if(result[0] == "MEMO")
			{
				if(result[1] == "MEMOLAYER")		frmMain->INIINFO.B_MEMO 	= (result[2] == "1" ? true:false);
				else if(result[1] == "PHOTOLAYER")	frmMain->INIINFO.B_PHOTO 	= (result[2] == "1" ? true:false);
				else if(result[1] == "POLYLAYER")	frmMain->INIINFO.B_POLY 	= (result[2] == "1" ? true:false);
				else if(result[1] == "LEVEL")		frmMain->INIINFO.MEMO_LEVEL = (result[2].IsEmpty() ? 6 : result[2].ToInt());
			}
			else if(result[0] == "DOGN")
			{
				if(result[1] == "LEVEL")	frmMain->INIINFO.DOGN_LEVEL = (result[2].IsEmpty() ? 6 : result[2].ToInt());
			}
			else if(result[0] == "DOCKINDNAME")
			{
				frmMain->INIINFO.DOCKINDNAME[result[2].ToInt()] = result[1];
			}
			else if(result[0] == "DOC_KIND")//DOCKIND로 하면 DOCKINDNAME보다 먼저 조회되서 DOCKINDNAME와 매칭을 못 시킨다//
			{
				if(result[1] == "LEVEL")		frmMain->INIINFO.DOC_LEVEL 	= (result[2].IsEmpty() ? 7 : result[2].ToInt());
				else if(result[1] == "SHOW")	frmMain->INIINFO.DOC_SHOW 	= result[2].ToInt();

				bool bFound = false;

				for(int i = 1; i < DF_DOC_CNT && !bFound; i++)
				{
					if(result[1] == frmMain->INIINFO.DOCKINDNAME[i])
					{
						frmMain->INIINFO.B_DOCKIND[i] 	= (result[2] == "1" ? true:false);
						frmMain->INIINFO.B_QRYCHECK[i] 	= frmMain->USERINI->ReadInteger("QUERY_CHECK", frmMain->INIINFO.DOCKINDNAME[i], 0);
						frmMain->INIINFO.B_DOCFAVOR[i] 	= frmMain->USERINI->ReadInteger("DOCFAVORITE", frmMain->INIINFO.DOCKINDNAME[i], 0);

						//=====================================================
						//241120//#DOCPOI#//울진군팀장님[REQ]//문서POI-사용자별 설정으로 표시//처음에는 설정정보 없으므로 Default는 QRYCHECK Value//
						//=====================================================
						if(i < DF_DOC_CNT)//241211//[DOC20_YN]-1/*가감대장 제외*/)
							frmMain->INIINFO.B_DOCPOI[i] 	= frmMain->USERINI->ReadInteger("DOCPOI", frmMain->INIINFO.DOCKINDNAME[i], false);
						if(frmMain->INIINFO.B_DOCKIND[i])
						{
							if(frmMain->INIINFO.B_DOCPOI[i] && (i != 11 && i != 15 && i != 18))//PNU 컬럼 없는 문서 제외(TB_KINDOFSYMBOL 참고)//
							{
								frmChangeMenu->m_nChkPoiCnt++;
								if(frmChangeMenu->m_nChkPoiCnt == 1)
									frmChangeMenu->m_nChkPoiDocNo	= i;
								else
									frmChangeMenu->m_nChkPoiDocNo	= -1;
							}
						}
						else
						{
							frmMain->INIINFO.B_DOCPOI[i]	= false;//문서설정 없으면 poi도 해제//
                        }
						//=====================================================

						if( !frmMain->INIINFO.B_DOCKIND[i] && frmMain->INIINFO.B_QRYCHECK[i])
							frmMain->INIINFO.B_QRYCHECK[i] = false;//
						if(frmMain->INIINFO.B_QRYCHECK[i])
							frmMain->INIINFO.DOC_COUNT++;//
						if( !frmMain->INIINFO.B_QRYCHECK[i] && frmMain->INIINFO.B_DOCFAVOR[i])
							frmMain->INIINFO.B_DOCFAVOR[i] = false;
						bFound = true;
					}
				}
			}
			else if(result[0] == "FUNCTIONS")
			{
				if(result[1] == "KRAS")				frmMain->INI_B_KRAS 		= (result[2] == "1" ? true:false);

//241108//CommonFunctions//
//				else if(result[1] == "DOGWAK")		frmMain->INI_B_DOGWAK 		= result[2].ToInt();
//				else if(result[1] == "MAPPOINT")	frmMain->INI_B_MAPPOINT 	= result[2].ToInt();//지적도-지번표시//
//				else if(result[1] == "SETMAPPOINT")	frmMain->INI_B_SETMAPPOINT 	= result[2].ToInt();//지적도 BASE_XY 설정//
//				else if(result[1] == "ROADVIEW")	frmMain->INI_B_ROADVIEW 	= (result[2] == "1" ? true:false);

				else if(result[1] == "THUMB_EXT")
				{
					if(result[2].IsEmpty())	frmMain->INI_AS_THUMBEXT	=  "JPG";
					else					frmMain->INI_AS_THUMBEXT = result[2];
				}
			}

			//240326//Add
			if(frmMain->INIINFO.B_ENCRYPT)
				frmMain->funcSetXDBPath();

			for(int i=0; i<3; i++){
				memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
				result[i] = "";
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}


	//=========================================================================
	//250515//사용하지 않는 INI Key 제거//
	//=========================================================================
	AnsiString asValue = "";
	asValue = frmMain->USERINI->ReadString("QUERY_CHECK", "토지이동결의서", "");
	if(asValue.IsEmpty())	frmMain->USERINI->DeleteKey("QUERY_CHECK", "토지이동결의서");
	asValue = frmMain->USERINI->ReadString("QUERY_CHECK", "공시지가보존문서", "");
	if(asValue.IsEmpty())	frmMain->USERINI->DeleteKey("QUERY_CHECK", "공시지가보존문서");
	asValue = frmMain->USERINI->ReadString("DOCFAVORITE", "토지이동결의서", "");
	if(asValue.IsEmpty())	frmMain->USERINI->DeleteKey("DOCFAVORITE", "토지이동결의서");
	asValue = frmMain->USERINI->ReadString("DOCFAVORITE", "공시지가보존문서", "");
	if(asValue.IsEmpty())	frmMain->USERINI->DeleteKey("DOCFAVORITE", "공시지가보존문서");
	asValue = frmMain->USERINI->ReadString("USER_CONFIG", "LOGIN", "");
	if(asValue.IsEmpty())	frmMain->USERINI->DeleteKey("USER_CONFIG", "LOGIN");
	//=========================================================================

}
//---------------------------------------------------------------------------





//=============================================================================
//240322//[Add]카드대장.개인정보.MASKING.최소사용자 권한//
//특정조건에 만족하는 특정컬럼 값만 임시적으로 가져오기 위한 함수//
//=============================================================================
AnsiString __fastcall TfrmSql::funcSQLColumnData(AnsiString _asSqlQry)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[1][255+1];
	SQLINTEGER m_nVal[1];
	SQLRETURN ret;

	SQLBindCol(m_hStmt, 1,  SQL_C_CHAR, m_cVal[0]  , sizeof(m_cVal[0]) , &m_nVal[0]);

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)_asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString resultData;
	char temp[255+1];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		resultData = "";

		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			memset(temp, 0x00, sizeof(temp) );
			memcpy(temp, m_cVal[0], sizeof( temp ));
			resultData = (char*)temp;
			break;
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	return resultData;
}
//---------------------------------------------------------------------------

//=============================================================================
//v1.0.0.1//#SHAREOWN#//
//===========================================================================
//===========================================================================
// WRITE TB_OLDLANDDOC_INFO// ==> 공유지연명부//
// _nType : INSERT, UPDATE, DELETE
//===========================================================================
bool __fastcall TfrmSql::funcSQLWriteOldLandDocInfo2(int _nType)
{
	AnsiString 	asSqlTbl 	= "TB_OLDLANDDOC_INFO";
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asSqlWhere	= "";
	AnsiString  asNow		= Now().FormatString("YYYYMMDDHHNNSS");
	AnsiString  asStr		= "";

	int nColCount = 7;
	char cCol[7][20] = {"PATHLIST_SEQNO", "PNU_CHECK", "PNU_NAME", "LEVEL", "MEMO", "WRITE_ID", "WRITE_DT"};

	//---
	if(_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 0; i < nColCount; i++)
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}


		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO
		asSqlVal = asSqlVal + ", " + (frmResultList2->chkJibunOK->Checked ? IntToStr(1) : IntToStr(0));//PNU_CHECK
		asSqlVal = asSqlVal + ", '" + frmResultList2->edtPnu->Text + "'";//PNU_NAME
		asSqlVal = asSqlVal + ", '" + frmResultList2->edtLevel->Text + "'";//LEVEL
		asStr	= frmResultList2->edtMemo->Text;
		if(frmResultList2->edtDoho->Text.Length() > 0)
		{
			if(frmAlphaDoc8->m_nDOCKIND == 0)
				asStr	= asStr + "(지적도제" + frmResultList2->edtDoho->Text + "호)";
			else if(frmAlphaDoc8->m_nDOCKIND == 1)
				asStr	= asStr + "(임야도제" + frmResultList2->edtDoho->Text + "호)";
		}
		asSqlVal = asSqlVal + ", '" + asStr + "'";//MEMO
		asSqlVal = asSqlVal + ", '" + frmMain->m_asCurrentId + "'";//WRITE_ID
		asSqlVal = asSqlVal + ", '" + asNow + "'";//WRITE_DT

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES (%s)", asSqlTbl, asSqlCol, asSqlVal);
	}
	else if(_nType == DF_UPDATE_RECORD)//UPDATE
	{
		asSqlCol = asSqlCol + cCol[1] + " = " + (frmResultList2->chkJibunOK->Checked ? IntToStr(1) : IntToStr(0)) + ", ";
		asSqlCol = asSqlCol + cCol[2] + " = '" + frmResultList2->edtPnu->Text + "', ";
		asSqlCol = asSqlCol + cCol[3] + " = '" + frmResultList2->edtLevel->Text + "', ";
		asStr	= frmResultList2->edtMemo->Text;
		if(frmResultList2->edtDoho->Text.Length() > 0)
		{
			if(frmAlphaDoc8->m_nDOCKIND == 0)
				asStr	= asStr + "(지적도제" + frmResultList2->edtDoho->Text + "호)";
			else if(frmAlphaDoc8->m_nDOCKIND == 1)
				asStr	= asStr + "(임야도제" + frmResultList2->edtDoho->Text + "호)";
		}
		asSqlCol = asSqlCol + cCol[4] + " = '" + asStr + "'";
		asSqlWhere = asSqlWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);
	}
	//210705//TB_OLDLANDDOC_INFO는 DELETE > INSERT 하면 일별 입력개수에 영향이 미치므로 하지 않는다//
//	else if(_nType == DF_DELETE_RECORD)//DELETE
//	{
//		asSqlWhere = asSqlWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);//PATHLIST_SEQNO
//
//		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);
//	}

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//=============================================================================
//v1.0.0.1//#SHAREOWN#//
//===========================================================================
// WRITE TB_DOCUMENT08_SHAREOWN//
// _nType : INSERT, UPDATE, DELETE
//===========================================================================
bool __fastcall TfrmSql::funcWriteShareOwn(int _nType, int _nCol/*Input(Vector).Idx*/)
{
	AnsiString 	asSqlTbl 	= "TB_DOCUMENT08_SHAREOWN_DIRECT";//241030//#구대장한글화편집#DirectTable//(지적문서 내에서 한글화 편집은 관리자만 저장)//
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asWhere 	= "";
	AnsiString  asSqlQry	= "";
	//210605//AnsiString  asPathName	= "";
	AnsiString  asStr		= "";
	int			nRow		= 0;
	int 		nSeq		= 0;
	int			nColIndex   = -1;/*Grid.Idx*/
	TAdvStringGrid *sgShareOwn = new TAdvStringGrid(this);

//[TODO]//TEST//
	if(_nCol < 0)
	{
		int a = -1;
    }


	int nColCount = 8;
	char cCol[8][20] = {"PATHLIST_SEQNO", "SEQ", "ERA_CODE", "HIS_DATE", "REASON", "RATIO", "OWN_ADDRESS", "OWN_NAME"};

	//260528//AIOCR//
	if( !frmMain->m_bAIOCR )//기구축 번역본 편집//
		asSqlTbl 	= "TB_DOCUMENT08_SHAREOWN_DIRECT";//241030//#구대장한글화편집#DirectTable//(지적문서 내에서 한글화 편집은 관리자만 저장)//
	else//AIOCR 번역본 편집//
		asSqlTbl 	= "TB_DOCUMENT08_AIOCR_SHAREOWN";

	//Grid1, 2의 Index 가져오기//
	if(_nType == DF_NEW_RECORD || _nType == DF_UPDATE_RECORD)//INSERT or UPDATE
	{
		nSeq = _nCol + 1;

		//---Grid1, 2 와 컬럼 지정//
		//Grid1.Right//[Grid1.idx:13~23][db.seq:11~1]
		if( _nCol < frmResultList2->m_nRightCount )
		{
			sgShareOwn = frmResultList2->sgShareOwn1;
			nColIndex = (frmResultList2->m_nPageCount-1) - _nCol/*Input(Vector).Idx*/;
		}
		//Grid2.Right//[Grid2.idx:13~23][db.seq:22~12]
		else if( _nCol >= frmResultList2->m_nRightCount && _nCol < frmResultList2->m_nRightCount*2)
		{
			sgShareOwn = frmResultList2->sgShareOwn2;
			nColIndex = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nRightCount - _nCol/*Input(Vector).Idx*/;
		}
		//Grid1.Left//[Grid1.idx:0~12][db.seq:35~23]
		else if( _nCol >= frmResultList2->m_nRightCount*2 && _nCol < frmResultList2->m_nRightCount + frmResultList2->m_nPageCount )
		{
			sgShareOwn = frmResultList2->sgShareOwn1;
			nColIndex = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nRightCount - _nCol/*Input(Vector).Idx*/;
		}
		//Grid2.Left//[Grid2.idx:0~12][db.seq:48~36]
		else
		{
			sgShareOwn = frmResultList2->sgShareOwn2;
			nColIndex = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nPageCount - _nCol/*Input(Vector).Idx*/;
		}

		if(nColIndex < 0 || nColIndex > sgShareOwn->ColCount - 1)
		{
			int a = 1;
		}
	}

	//---
	if(_nType == DF_NEW_RECORD)//INSERT
	{
		for(int i = 0; i < nColCount; i++)
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}

		asSqlVal = asSqlVal + "(";
		//210605//asSqlVal = asSqlVal + "'" + asPathName + "', ";
		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo) + ", ";//210605//
		asSqlVal = asSqlVal + IntToStr(nSeq) + ", ";

		//[TODO]서기변환//
//		asStr = sgShareOwn->Cells[_nCol][1];
//		asStr = frmMain->funcChangeDateStrFormatDate(asStr.c_str());
		asSqlVal = asSqlVal + "'', ";
		asStr	= sgShareOwn->Cells[nColIndex][0];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][1];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][2];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][3];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][4];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + "'" + asStr + "')";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlVal);
	}
	else if(_nType == DF_UPDATE_RECORD)//UPDATE
	{
		//210605//asWhere  = asWhere + cCol[0] + " = '" + asPathName + "' ";
		asWhere  = asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";//210605//
		asWhere  = asWhere + "AND " + cCol[1] 	+ " = " + IntToStr(sgShareOwn->ColCount - 1 - _nCol);

		//[TODO]서기변환//
		nRow	= 0;
//		asStr = sgShareOwn->Cells[nColIndex][1];
//		asStr = frmMain->funcChangeDateStrFormatDate(asStr.c_str());

		asSqlVal = asSqlVal + cCol[2] + " = '', ";
		asStr	= sgShareOwn->Cells[nColIndex][nRow++];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + cCol[3] + " = '" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][nRow++];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + cCol[4] + " = '" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][nRow++];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + cCol[5] + " = '" + asStr + "', ";
		asStr	= sgShareOwn->Cells[nColIndex][nRow++];
		if(asStr == "-")	asStr	= "";
		if(asStr == "빈칸")	asStr	= "";
		asStr = StringReplace(asStr, "'", "", TReplaceFlags() << rfReplaceAll);
		asSqlVal = asSqlVal + cCol[6] + " = '" + asStr + "'";

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlVal, asWhere);
	}
	else if(_nType == DF_DELETE_RECORD)//DELETE
	{
		//210605//asWhere = asWhere + cCol[0] + " = '" + asPathName + "' ";
		asWhere = asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo) + " ";
		asWhere	= asWhere + "AND " + cCol[1] 	+ " = " + IntToStr(_nCol + 1);
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}
	//210705//
	else if(_nType == DF_DELETE_RECORD_ALL)//DELETE_ALL
	{
		asWhere	= asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}

	frmResultList2->m_asQryToSave	= asSqlQry;//210617//

	sgShareOwn = NULL;
	delete sgShareOwn;

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------
//=============================================================================





//=========================================================================
//241030//#구대장한글편집#DirectTable//
//=========================================================================
void __fastcall TfrmSql::funcSQLCreate_TB_DOCUMENT08_DIRECT()
{
	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	SQLRETURN 	sRet;
	AnsiString 	asSqlQry 	= "";

	//=========================================================================
	//260528//AIOCR//
	//=========================================================================
	AnsiString  asExecFile = frmMain->ROOTPATH + "MyJsonBridge.exe";
	if(FileExists(asExecFile))
	{
		//------------------------------
		//TB_DOCUMENT08_HIS_DIRECT
		//------------------------------
		asSqlQry	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_AIOCR_HIS` LIKE `TB_DOCUMENT08_HIS`";
		func_QryProcess(asSqlQry);
		if (m_hStmt)		SQLCloseCursor(m_hStmt);

		//------------------------------
		//TB_DOCUMENT08_OWNINFO_DIRECT
		//------------------------------
		asSqlQry	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_AIOCR_OWNINFO` LIKE `TB_DOCUMENT08_OWNINFO`";
		func_QryProcess(asSqlQry);
		if (m_hStmt)		SQLCloseCursor(m_hStmt);

		//------------------------------
		//TB_DOCUMENT08_SHAREOWN_DIRECT
		//------------------------------
		asSqlQry	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_AIOCR_SHAREOWN` LIKE `TB_DOCUMENT08_SHAREOWN`";
		func_QryProcess(asSqlQry);
		if (m_hStmt)		SQLCloseCursor(m_hStmt);
	}
	else
	{
		//------------------------------
		//TB_DOCUMENT08_HIS_DIRECT
		//------------------------------
		asSqlQry	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_HIS_DIRECT` LIKE `TB_DOCUMENT08_HIS`";
		func_QryProcess(asSqlQry);
		if (m_hStmt)		SQLCloseCursor(m_hStmt);

		//------------------------------
		//TB_DOCUMENT08_OWNINFO_DIRECT
		//------------------------------
		asSqlQry	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_OWNINFO_DIRECT` LIKE `TB_DOCUMENT08_OWNINFO`";
		func_QryProcess(asSqlQry);
		if (m_hStmt)		SQLCloseCursor(m_hStmt);

		//------------------------------
		//TB_DOCUMENT08_SHAREOWN_DIRECT
		//------------------------------
		asSqlQry	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_SHAREOWN_DIRECT` LIKE `TB_DOCUMENT08_SHAREOWN`";
		func_QryProcess(asSqlQry);
		if (m_hStmt)		SQLCloseCursor(m_hStmt);
	}
}
// ---------------------------------------------------------------------------

//===========================================================================
// 한글화 DB/AIOCR 데이터 변경 로그기록 - 테이블 생성
//_bAIOCR			=> true:AIOCR데이터정정, false:DB데이터정정//
//===========================================================================
void __fastcall TfrmSql::funcSQLCreateTableDoc08History()
{
	if (m_hStmt)		SQLCloseCursor(m_hStmt);

	AnsiString asSql 	= "";
	AnsiString asSqlCol = "";
	AnsiString asSqlTbl = "TB_DOCUMENT08_DIRECT_HISTORY";//감독관 [기 구축 DB] 내용 변경//

	//
	asSqlCol = asSqlCol + "	(`COPY_DOC08_SEQNO` INT(11) NOT NULL,";
	asSqlCol = asSqlCol + "	`KIND_TYPE` INT(11) NOT NULL COMMENT '1.부책,2:공유지연명부',";
	asSqlCol = asSqlCol + "	`PATHLIST_SEQNO` INT(11) NOT NULL,";
	asSqlCol = asSqlCol + "	`CONTENTS_SEQ` INT(11) NULL DEFAULT NULL COMMENT '[부책]1:지목,2:지적,3:과세1,4:과세2,5:연혁,6:일자,7:사고,8:주소,9:성명 [공유지연명부]1.일자,2.사고,3.보합,4:주소,5:성명',";
	asSqlCol = asSqlCol + "	`SEQ` INT(11) NULL DEFAULT NULL,";
	asSqlCol = asSqlCol + "	`BF_DATA` VARCHAR(255) NULL DEFAULT NULL COLLATE 'utf8_general_ci',";
	asSqlCol = asSqlCol + "	`AF_DATA` VARCHAR(255) NULL DEFAULT NULL COLLATE 'utf8_general_ci',";
	asSqlCol = asSqlCol + "	INDEX `IDX_HIS` (`COPY_DOC08_SEQNO`, `PATHLIST_SEQNO`, `SEQ`) USING BTREE";
	asSqlCol = asSqlCol + ") COLLATE='utf8_general_ci' ENGINE=MyISAM ROW_FORMAT=DYNAMIC;";

	asSql.sprintf("CREATE TABLE IF NOT EXISTS %s.%s %s", frmMain->_DATABASE_, asSqlTbl, asSqlCol);

	//241125//
	if ( !func_QryProcess(asSql) ) {
		String sMsg = L"TABLE " + (String)asSqlTbl + L" 생성하지 못했습니다.";
		frmMsg->funcMessageDlg("알림:", sMsg.w_str(), 2);
	}
	else
	{
		//------------------------------
		//TB_DOCUMENT08_AIOCR_HISTORY
		//------------------------------
		if (m_hStmt)		SQLCloseCursor(m_hStmt);
		asSql	= "CREATE TABLE IF NOT EXISTS `TB_DOCUMENT08_AIOCR_HISTORY` LIKE `TB_DOCUMENT08_DIRECT_HISTORY`";
		func_QryProcess(asSql);
	}

	if (m_hStmt)		SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------


//==========================================================================
//241107//#한글화편집#DirectTable//내역저장하기//
//==========================================================================
//===========================================================================
// WRITE TB_DOCUMENT08 Direct History//
// _nCopyDoc08Seq 	=> TB_COPY_DOC08.SEQ
// _nKindType		=> 1.부책, 2:공유지연명부
//_bAIOCR			=> true:AIOCR데이터정정, false:DB데이터정정//
//===========================================================================
void __fastcall TfrmSql::funcWriteDoc08_History(int _nCopyDoc08Seq, int _nKindType, bool _bAIOCR)
{
	AnsiString 	asSqlTbl 	= "TB_DOCUMENT08_DIRECT_HISTORY";//감독관 [기 구축 DB] 내용 변경//
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asPathName	= "";
	AnsiString  asStr		= "";

	int nColCount = 7;
	char cCol[7][20] = {"COPY_DOC08_SEQNO", "KIND_TYPE", "PATHLIST_SEQNO", "CONTENTS_SEQ", "SEQ", "BF_DATA", "AF_DATA"};

	if(_bAIOCR)//감독관 [AIOCR] 내용 변경//
		asSqlTbl = "TB_DOCUMENT08_AIOCR_HISTORY";

	//---
	for(int i = 0; i < (int)e08DataAlpha->m_ResultDoc08_History.size(); i++)
	{
		asSqlVal = "(";
		asSqlVal = asSqlVal + IntToStr(_nCopyDoc08Seq) + ", ";
		asSqlVal = asSqlVal + IntToStr(_nKindType) + ", ";
		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo) + ", ";
		asSqlVal = asSqlVal + IntToStr(e08DataAlpha->m_ResultDoc08_History[i].CONTENTS_SEQ) + ", ";
		asSqlVal = asSqlVal + IntToStr(e08DataAlpha->m_ResultDoc08_History[i].SEQ) + ", ";
		asStr	= e08DataAlpha->m_ResultDoc08_History[i].BF_DATA;
		asSqlVal = asSqlVal + "'" + asStr + "', ";
		asStr	= e08DataAlpha->m_ResultDoc08_History[i].AF_DATA;
		asSqlVal = asSqlVal + "'" + asStr + "')";

		asSqlQry.sprintf("INSERT INTO %s VALUES %s", asSqlTbl, asSqlVal);

		func_QryProcess(asSqlQry);
	}
}
//---------------------------------------------------------------------------

//==========================================================================
//241107//#한글화편집#DirectTable//내역가져오기//
//_bAIOCR			=> true:AIOCR데이터정정, false:DB데이터정정//
//==========================================================================
void __fastcall TfrmSql::funcReadDocument08_History(bool _bAIOCR)//int _nCopyDoc08Seq)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	AnsiString  asSqlTbl = "TB_DOCUMENT08_DIRECT_HISTORY";//감독관 [기 구축 DB] 내용 변경//
	if(_bAIOCR)//감독관 AIOCR 내용 변경//
		asSqlTbl = "TB_DOCUMENT08_AIOCR_HISTORY";

	AnsiString  asSqlTblA  	= "(SELECT * FROM " + asSqlTbl + " WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo) + ")";
	AnsiString  asSqlTblB  	= "(SELECT * FROM TB_COPY_DOC08 WHERE TYPE = 3 AND PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo) + ")";
	AnsiString  asSqlQry  	= "";
	AnsiString  asSqlCol 	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asOrderBy  	= "ORDER BY B.SEQNO, A.CONTENTS_SEQ, A.SEQ";
	SQLRETURN ret;
	DOCUMENT08_HISTORY_STRUCT	tempHistory;//구대장 소유자정보//



	/*
	SELECT B.ACTION_DT, B.USERNAME, A.CONTENTS_SEQ, A.SEQ, A.BF_DATA, A.AF_DATA
	FROM
	(SELECT * FROM TB_DOCUMENT08_DIRECT_HISTORY WHERE PATHLIST_SEQNO = " + frmMain->m_nPathListSeqNo + ") A,
	(SELECT * FROM TB_COPY_DOC08 WHERE TYPE = 3 AND PATHLIST_SEQNO = " + frmMain->m_nPathListSeqNo + ") B
	WHERE A.COPY_DOC08_SEQNO=B.SEQNO
	ORDER BY B.SEQNO, A.CONTENTS_SEQ, A.SEQ
	*/

	//---
	memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));
	int nIndex = 1;

	SQLINTEGER m_nVal[7];
	memset(m_nVal, 0x00, sizeof(m_nVal));

	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempHistory.ACTION_DT, 			sizeof(tempHistory.ACTION_DT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempHistory.USERNAME, 			sizeof(tempHistory.USERNAME), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempHistory.KIND_TYPE, 		sizeof(tempHistory.KIND_TYPE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempHistory.CONTENTS_SEQ, 		sizeof(tempHistory.CONTENTS_SEQ), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_LONG, 	&tempHistory.SEQ, 				sizeof(tempHistory.SEQ), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempHistory.BF_DATA, 			sizeof(tempHistory.BF_DATA), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(m_hStmt, nIndex,  SQL_C_CHAR, 	tempHistory.AF_DATA, 			sizeof(tempHistory.AF_DATA), 		&m_nVal[nIndex-1]); nIndex++;

	asSqlCol	= "B.ACTION_DT, B.USERNAME, A.KIND_TYPE, A.CONTENTS_SEQ, A.SEQ, A.BF_DATA, A.AF_DATA";
	asWhere		= "A.COPY_DOC08_SEQNO=B.SEQNO";
	asSqlQry.sprintf("SELECT %s FROM %s A, %s B WHERE %s %s", asSqlCol, asSqlTblA, asSqlTblB, asWhere, asOrderBy);

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(m_hStmt);
		return;
	}

	e08DataAlpha->m_ResultDoc08_HistoryStat.clear();

	memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));
	while (SQLFetch(m_hStmt)!=SQL_NO_DATA) {
		e08DataAlpha->m_ResultDoc08_HistoryStat.push_back(tempHistory);
		memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));
	};

	if(m_hStmt) SQLCloseCursor(m_hStmt);
}
//---------------------------------------------------------------------------

//===========================================================================
// WRITE TB_DOCUMENT08_HIS_DEL//
// _nType : INSERT, DELETE_ALL
//===========================================================================
bool __fastcall TfrmSql::funcWriteHistoryDel(int _nType, int _nCol)
{
	AnsiString 	asSqlTbl 	= "TB_DOCUMENT08_HIS_DEL";//241030//#구대장한글화편집#DirectTable//(지적문서 내에서 한글화 편집은 관리자만 저장)//
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asWhere 	= "";
	AnsiString  asSqlQry	= "";
	AnsiString  asStr		= "";
	AnsiString  asJimok		= "";
	AnsiString  asArea		= "";
	AnsiString  asValue		= "";

	int nColCount = 5;
	char cCol[5][20] = {"PATHLIST_SEQNO", "SEQ", "JIMOK", "AREA", "VALUE"};

	//---
	if(_nType == DF_NEW_RECORD)//INSERT
	{
		asJimok	= frmResultList->sgHistory->Cells[_nCol][0];
		if(asJimok == "-")	asJimok	= "";
		asArea	= frmResultList->sgHistory->Cells[_nCol][1];
		if(asArea == "-")	asArea	= "";
		asValue	= frmResultList->sgHistory->Cells[_nCol][2];
		if(asValue == "-")	asValue	= "";

		if(asJimok.IsEmpty() && asArea.IsEmpty() && asValue.IsEmpty())//삭제선 없으면 레코드 저장하지 않음.
			return false;

		for(int i = 0; i < nColCount; i++)
		{
			asSqlCol = asSqlCol + cCol[i];
			if(i != nColCount - 1)
				asSqlCol = asSqlCol + ", ";
		}

		asSqlVal = asSqlVal + "(";
		asSqlVal = asSqlVal + IntToStr(frmMain->m_nPathListSeqNo) + ", ";
		asSqlVal = asSqlVal + IntToStr(frmResultList->sgHistory->ColCount - 1 - _nCol) + ", ";

		asStr	= frmResultList->sgHistory->Cells[_nCol][0];
		if(asStr.SubString(1, 1) == "#")	asSqlVal += "'1', ";
		else                            	asSqlVal += "'', ";

		asStr	= frmResultList->sgHistory->Cells[_nCol][1];
		if(asStr.SubString(1, 1) == "#")	asSqlVal += "'1', ";
		else                            	asSqlVal += "'', ";

		asStr	= frmResultList->sgHistory->Cells[_nCol][2];
		if(asStr.SubString(1, 1) == "#")	asSqlVal += "'1')";
		else                            	asSqlVal += "'')";

		asSqlQry.sprintf("INSERT INTO %s (%s) VALUES %s", asSqlTbl, asSqlCol, asSqlVal);
	}
	else if(_nType == DF_DELETE_RECORD_ALL)//DELETE_ALL
	{
		asWhere	= asWhere + cCol[0] + " = " + IntToStr(frmMain->m_nPathListSeqNo);
		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asWhere);
	}

	return func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

//===========================================================================
// DELETE FROM AIOCR TEST DB DATA
//===========================================================================
void __fastcall TfrmSql::funcInitAIOCRData()
{
	AnsiString  asSqlQry = "";

	asSqlQry = "DELETE FROM TB_DOCUMENT08_AIOCR_HIS";
	func_QryProcess(asSqlQry);
	asSqlQry = "DELETE FROM TB_DOCUMENT08_AIOCR_OWNINFO";
	func_QryProcess(asSqlQry);
	asSqlQry = "DELETE FROM TB_DOCUMENT08_AIOCR_SHAREOWN";
	func_QryProcess(asSqlQry);
	asSqlQry = "DELETE FROM TB_OLDLANDDOC_INFO";
	func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmSql::funcSQLReadLandMoveInfo(AnsiString _asPnu)
{
	if(m_hStmt) SQLCloseCursor(m_hStmt);

	SQLCHAR m_cVal[12][50+1];
	SQLINTEGER m_nVal[12];

	for(int i=0; i<12; i++){
		SQLBindCol(m_hStmt, i+1,  SQL_C_CHAR, m_cVal[i]  , sizeof(m_cVal[i]) , &m_nVal[i]);
	}

	AnsiString  asTable  = "LANDMOVE_INFO";
	AnsiString  asSqlQry = "";
	AnsiString  asSubQry = "(SELECT DISTINCT G_SEQ FROM " + asTable + " WHERE BF_PNU='" + _asPnu + "' OR AF_PNU='" + _asPnu + "') B";
	AnsiString  asOrderBy = "ORDER BY A.REG_DT, FIELD(A.RSN, '20', '40', '30'), A.BF_PNU, A.AF_PNU";
	SQLRETURN ret;

	asSqlQry.sprintf("SELECT A.* FROM %s A JOIN %s ON A.G_SEQ=B.G_SEQ %s", asTable, asSubQry, asOrderBy);

	ret = SQLPrepare(m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmt);

	AnsiString result[12];
	char temp[50+1];
	TStringList *csvList = new TStringList();

	csvList->Clear();
	csvList->Text = "g_seq,idx,bf_pnu,af_pnu,rsn,reg_dt,bf_jimok,bf_area,af_jimok,af_area";
//	csvList->Add(csvList->Text);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmt);
	}
	else{
		for(int i = 0; i < 12; i++){
			memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
			result[i] = "";
		}
		while(SQLFetch(m_hStmt)!=SQL_NO_DATA) {
			for(int i = 0; i < 12; i++){
				memset(temp, 0x00, sizeof(temp) );
				memcpy(temp, m_cVal[i], sizeof( temp ));
				result[i] = temp;
			}

			AnsiString rowText = result[0];
			for(int i = 1; i < 12; i++)
			{
			  rowText += ("," + result[i]);
			}
			csvList->Add(rowText);

			for(int i = 0; i < 12; i++){
				memset(m_cVal[i],0x00,sizeof(m_cVal[i]));
				result[i] = "";
			}
		};
		if(m_hStmt) SQLCloseCursor(m_hStmt);
	}

	AnsiString  savePath = frmMain->DBPATH + _asPnu + ".csv";
	if(csvList->Count > 1)
	{
		csvList->SaveToFile(savePath, TEncoding::UTF8);
	}

	return savePath;
}
//---------------------------------------------------------------------------


