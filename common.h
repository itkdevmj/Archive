#pragma warning(disable : 4786)
#include <vector.h>

using namespace std;



//----------------------------------------------------------
//260602//1) 공통 디버그 매크로
//OutputDebugString은 디버깅 세션에 문자열을 출력할 수 있고, IDE의 Event Log나 DebugView로 확인할 수 있습니다.
#pragma once
#include <windows.h>
#include <stdio.h>
#ifdef _DEBUG
inline void DebugTrace(const char* fmt, ...)
{
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf) - 1, fmt, ap);
    buf[sizeof(buf) - 1] = 0;
    OutputDebugStringA(buf);
    OutputDebugStringA("\r\n");
    va_end(ap);
}
#define TRACEF(...) DebugTrace(__VA_ARGS__)
#else
#define TRACEF(...)
#endif
//----------------------------------------------------------


#include "GPoint.h"
#include "SDBApiExport.h"


/* -------------------------------------------------------------------- */
/*      Shape types (nSHPType)                                          */
/* -------------------------------------------------------------------- */
#define SHPT_NULL	0
#define SHPT_POINT	1
#define SHPT_ARC	3
#define SHPT_POLYGON	5
#define SHPT_MULTIPOINT	8
#define SHPT_POINTZ	11
#define SHPT_ARCZ	13
#define SHPT_POLYGONZ	15
#define SHPT_MULTIPOINTZ 18
#define SHPT_POINTM	21
#define SHPT_ARCM	23
#define SHPT_POLYGONM	25
#define SHPT_MULTIPOINTM 28
#define SHPT_MULTIPATCH 31


/* -------------------------------------------------------------------- */
/*      palMainView Status                                              */
/* -------------------------------------------------------------------- */
#define 	DF_PANNING  					1
#define     DF_WINDOW                       2
#define     DF_RECTANGLE                    3
#define     DF_RECTPRINT                    4
#define     DF_PRINTDRAG                    5
#define		DF_STREETGAUGE					6
#define		DF_AREAGAUGE					7
#define		DF_LOOKGLASS					8
#define		DF_DOGAKLINE					9
#define		DF_OWNNAMES						10
#define		DF_SPACERECT					11//공간검색
#define		DF_DELETE_ALL					19//220217//COPY_LMREQ_TO_ONESTOP



//===============================================================================
// Encrypt 관련//
//===============================================================================
#define 	D_DOMAIN_NAME	"itKorea"
#define 	D_SERVER_IP		"108.1.167.244"
#define 	D_SERVER_PORT	9003
#define 	D_SCHEMA_NAME	"DBSEC"
#define 	D_TABLE_NAME	"REF_KEY"
#define 	D_COLUMN_NAME	"SEED_COL"




///* -------------------------------------------------------------------- */
///*                                         */
///* -------------------------------------------------------------------- */
#define    MAX_CHUNK_SIZE                2048	//1024// 잘라서보내는 최대 크기



const int 	cnLayerCount = 4;//pbRect 개수//소유자명1, 2, 도곽선, AIOCR//

#define     DF_DOC_CNT		20+1//231020//18 + 1//M

#define		DOC08_SUBBOOK_CNT	14//241204//구대장.부책.표시항목 개수//
#define		DOC08_SHAREOWN_CNT	11//241204//구대장.공유지.표시항목 개수//

#define     QRY_ARRANGE_SIZE              2048


#define     FORM_SHOW_MODE_RECORD           1
#define     FORM_SHOW_MODE_MODIFY           2


#define 	DF_NEW_RECORD 					1
#define 	DF_UPDATE_RECORD				2
#define 	DF_DELETE_RECORD				3
#define		DF_ONLY_INEDX_SET				11
#define		DF_UPDATE_CNT					12
#define		DF_UPDATE_ATTACH				14
#define 	DF_UPDATE_STATE					4//210611//
#define 	DF_DELETE_RECORD_ALL			5//210705//


#define 	DF_NON_MESSAGE 					0
#define 	DF_MESSAGE						1
#define 	DF_MESSAGE_UPDATE				2
#define 	DF_MESSAGE_DELETE				3



/* -------------------------------------------------------------------- */
/*      Minimum Bounding Rectangle                                      */
/* -------------------------------------------------------------------- */
typedef struct
{
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
}MBR;

typedef struct
{
	double	x;
	double	y;
}READPOINTS;

/* -------------------------------------------------------------------- */
/*      PoliLine & Polygon                                              */
/* -------------------------------------------------------------------- */

typedef struct{
	int m_nID;
	MBR m_MBR;
	int m_nNumParts;
	int m_nNumPoints;
	vector<int>	m_vParts;
	vector<GPoint>	m_vPoints;
	bool m_nShow;
	double x;
	double y;
	AnsiString label;
	double area;
	AnsiString labelodd;
	AnsiString labeleve;
	double angle1;
	double angle2;
	int oddx;
	int oddy;
	int evex;
	int evey;
}polyObject;

typedef struct{
	AnsiString thema;
	AnsiString korname;
	AnsiString engname1;
	AnsiString engname2;
}STRUCTCODECONVERT;

typedef struct{
	int  JIBUNINDEX;
	int  BUILDINDEX; //
	int  ROADINDEX;  //
	char EMDCD[9];
	char EMDNM[20];
	char RICD[11];
	char RINM[20];
	char BUNJI[13];
	char ROADNM[80]; //
	char LAND_CD[20];
}READJIBUN;

typedef struct{
	int  JIBUNINDEX;  //
	int  BUILDINDEX;
	int  ROADINDEX;
	char BUILDNM[200];
	char BUILDNMCHAR[200];
	char LAND_CD[20];
	char EMDNM[20];
	char RINM[20];
	char BUNJI[13]; //
	char ROADNM[80];
	char RN[50];
	char RNCHAR[50];
}READBUILD;

typedef struct{
	char RN_CD[8];    //도로명코드
	char RN[50];      //도로명
}READRN;

//지적도 - 읍면동
typedef struct{//OK
	int ID;
	char EMD_NM[20];
	char EMD_CD[9];
}READEMD;

//지적도 - 리
typedef struct{//OK
	int ID;
	char RI_NM[20];
	char RI_CD[11];
}READRI;

//지적도 - 지번
typedef struct{
	int ID;
	char PNU[20];
	char JIBUN[20];
//bCenterPoint = false//	double	centerx;//241205//#CenterPoint#//
//bCenterPoint = false//	double	centery;//241205//#CenterPoint#//
}READCBND;

//191114_LAYER_DOGWAK
/*
//지적도 - 인덱스맵
typedef struct{//OK
	int ID;
	char MAP_NAM[15];  //인덱스명
	char MAP_NUM[10];      //인덱스번호
}READINDEXMAP;
*/
typedef struct{//OK
	int ID;
	char DOM[15+1];
}READINDEXMAP;

//=============================================================================
//231018//GAGAMLAYER in LandArchive//
//=============================================================================
typedef struct{
	int ID;
	char MNUM[22+1];//SSSSSUUURRYYYYPPPPPQQQ(시군구코드5+읍면동3+리2+년도4+페이지번호5+순번3)
	char REMARK[50+1];
}READGAGAM;


//기본정보...
typedef struct{
	int m_nRecords;
	int m_nShapeType;
}STANDARDSTRUCT;

typedef struct{
	AnsiString layerparent;
	AnsiString layername;
	int  showuse;
	int  showlevel;
	int  labeluse;
	int  labelscale;
	int  labelcolor;
	AnsiString labelfont;
	int  brushuse;
	int  brushcolor;
	int  lineuse;
	int  linecolor;
	int  linewidth;
	AnsiString hatchstyle;
	vector<int>	fontsize;
}CONFIGLAYER;

typedef struct{
	AnsiString code_no;
	AnsiString code_nm;
	AnsiString code_main;
}CODETABLE;

//기본속성
typedef struct{
	int SHOW_FACTOR_LIMITAREA;
	int SHOW_FACTOR_SCALE;
	int FIRST_ZOOM_FACTOR;
	//로컬 영상 사용시 최소 출력 스케일
	int LOCAL_IMGAE_VIEW_SCALE;
	//편입면적 사용여부
	int INCLUDE_AREA_USE;

	//선택된 개별지 색상
	int SELECT_GENERAL_COLOR;
	//지번선택시 사용되는 값
	int SELECT_REMARK_COLOR;
	int SELECT_REMARK_ALPHA;
	int SELECT_REMARK_WIDTH;

	//영상 출력/미출력시 지적과 지번 출력 옵션
	int USE_IMAGE_JIJUKLINECOLOR;
	int USE_IMAGE_JIBUNCOLOR;
	int UN_USE_IMAGE_JIJUKLINECOLOR;
	int UN_USE_IMAGE_JIBUNCOLOR;

	//좌표 변환용
	int SYSTEM_CONVERT_SYSTEM_0;
	int SYSTEM_CONVERT_ELLIPS_0;
	int SYSTEM_CONVERT_SYSTEM_1;
	int SYSTEM_CONVERT_ELLIPS_1;

	//카카오맵 영상 오픈 API키
	AnsiString KAKAOMAP_OPENAPI_KEY;
	//영상 이동
	int PICTURE_XMOVE;
	int PICTURE_YMOVE;
	//출력 알파값
	int IMAGE_PLUS_ALPHABLEND_VALUE;
	int IMAGE_MINUS_ALPHABLEND_VALUE;
	//로드뷰
	AnsiString DAUM;
	AnsiString NAVER;

	//선택지번 출력 설정
	int SELECT_LINE_COLOR;
	int SELECT_LINE_WIDTH;

	int PRICE_MARK_HOWTO;

	//장평
	double WIDTHRATE;

	//라벨출력 옵션
	int LABEL_ALIGNMENT;

	//항공사진 출력시 지번 색상
	int SELECT_USEJIBUN_COLOR;

	//항공사진 미 출력시 지번 색상
	int SELECT_UNUSEJIBUN_COLOR;

	//항공사진 출력시 접도구역 색상
	int FRONTAGEAREA_USEIMAGECOLOR;

	//항공사진 미 출력시 접도구역 색상
	int FRONTAGEAREA_UNUSEIMAGECOLOR;

	AnsiString  KRAS_KEY;
	AnsiString  KRAS_IP;

} MAININI_STRUCT;

//면적재기용 정보 저장 버퍼
typedef struct{
	double x;
	double y;
} AREA_STRUCT;

typedef struct{
	int gbn;  //1이 시작, 2이 계속, 3이 완료
	double x;
	double y;
	double labelx;
	double labely;
	AnsiString area;
} REALAREA_STRUCT;

//거리재기용 정보 저장 버퍼
typedef struct{
	double x;
	double y;
	double dist;
} DIST_STRUCT;

typedef struct{
	int gbn;  //1이 시작, 2이 계속, 3이 완료
	double x;
	double y;
	double labelx;
	double labely;
	AnsiString dist;
} REALDIST_STRUCT;

typedef struct{
	char    TABLE_NAME[65];
}TABLE_NAMES;

typedef struct{
	GPoint _point;//실좌표
	GPoint _coord;//경위도 좌표
	AnsiString _lat;
	AnsiString _long;
} RETURNCOORDATA;

typedef struct{
	TPoint sPoint;
	TPoint ePoint;
}DEPTH_POINT;

typedef struct{
	char LAND_KEY[20];
	char DOC01_YN[2];
	char DOC02_YN[2];
	char DOC03_YN[2];
	char DOC04_YN[2];
	char DOC05_YN[2];
	char DOC06_YN[2];
	char DOC07_YN[2];//201008//
	char DOC08_YN[2];
	char DOC09_YN[2];
	char DOC11_YN[2];
	char DOC12_YN[2];
	char DOC14_YN[2];
	char DOC17_YN[2];
	int  m_nID;
	MBR  m_MBR;
	double x;
	double y;
}KINDOFDOC_STRUCT;

//M//191105
typedef struct{
	char LAND_KEY[20];
	int  m_nID;
	MBR  m_MBR;
	double x;
	double y;
}POISPATIAL_STRUCT;

typedef struct{
	char LAND_KEY[20];
	int  SEQNO;
	char MEMO_DATA[501];
	char LAST_UPDT[31];
	char LAST_WRITER[51];
}MEMODATA_STRUCT;

typedef struct{
	char LAND_KEY[20];
}MEMOLANDKEYDATA_STRUCT;



//***************************************************************************
// about MEMO
//***************************************************************************
typedef struct{
	char 	NO[17+1];
	char 	UMD_NAME[60+1];
	char 	RI_NAME[60+1];
	char 	JIBUN_NAME[60+1];
	char 	OWN_NAME[60+1];
	char 	TITLE[100+1];
}BATCHMEMOINFO_STRUCT;

typedef struct{
	char 	POI_KEY[21+1];
	char 	POI_NAME[60+1];
	char 	TITLE[100+1];
	char 	MEMO[200+1];
	char 	OWN_NAME[60+1];
	char 	BATCH_YN[1+1];
	char 	OPEN_YN[1+1];
	char 	WRITE_ID[32+1];
	char 	WRITE_DT[20+1];
	int  	FILE_CNT;//FILE COUNT
	int  	DATA_CNT;//VECTOR COUNT
	double  X;
	double  Y;
	double	LINECOLOR;
	char	GAGAM_X[50+1];
	char	GAGAM_Y[50+1];
}MEMOINFO_STRUCT;

typedef struct{
	char 				POI_KEY[21+1];
	int  				COUNT;
	int  				SIZE;
	vector<GPoint>		VECTOR;//polyObject로 변경해야 하나?
}MEMOVECTOR_STRUCT;


typedef struct{
	bool	B_NEW;//true:local file, false:remote file
	char 	POI_KEY[21+1];
	int  	SEQ;
	int  	FILE_SIZE;
	char  	LOCAL_PATH_NAME[255+1];
	char  	REMOTE_PATH_NAME[255+1];
}MEMOFILE_STRUCT;

typedef struct{
	char 	POI_KEY[21+1];
	char 	MEMO[200+1];
	char 	WRITE_ID[32+1];
	char 	WRITE_DT[20+1];
	double	LINECOLOR;
	char	GAGAM_X[50+1];
	char	GAGAM_Y[50+1];
}MEMOINFOHIS_STRUCT;






//INI 설정값(기존 지적문서에서 활용하던 값들)
typedef struct {
	//190114//bool 	bShowStatsOption;
	AnsiString	SIDOCODE;
	AnsiString 	SIDONAME;
	bool 		B_FTPUSE;
	AnsiString	FTPROOT;
	AnsiString 	FTPIP;
	AnsiString 	FTPPORT;
	AnsiString 	FTPID;
	AnsiString 	FTPPW;
	AnsiString 	CONSTYLE;//constyle
	bool 		B_ENCRYPT;
	bool		B_INDEX;//인덱스사용여부//
	int			INDEX_LEVEL;//인덱스 아이콘 보여질 ZOOM 단계//
	bool		B_MEMO;//메모 사용여부//
	bool		B_PHOTO;//포토 사용여부//
	bool		B_POLY;//영역 사용여부//
	int			MEMO_LEVEL;//메모 아이콘 보여질 ZOOM 단계//
	int			DOGN_LEVEL;//도근점만 문서에서 제외//도근점 아이콘 보여질 ZOOM 단계//
	bool 		B_DOCKIND[DF_DOC_CNT];
	int			DOC_LEVEL;//문서 아이콘 보여질 ZOOM 단계//
	int			DOC_COUNT;//설정한 문서개수//
	int			DOC_SHOW;//문서심볼표시//220105//
	AnsiString  DOCKINDNAME[DF_DOC_CNT];//cButtonName[DF_DOC_CNT][128];
	bool 		B_QRYCHECK[DF_DOC_CNT];//bQryCheck[DF_DOC_CNT];
	bool  		B_DOCFAVOR[DF_DOC_CNT];//즐겨찾기//
	bool  		B_DOCPOI[DF_DOC_CNT];//문서POI//241120//#DOCPOI#//
}INI_STRUCT;

//INI 설정값(기존 지적문서에서 활용하던 값들)
typedef struct {
//241122//NotUsed//
//	int	 		NVIEWMODE;//1:지적도보기, 2:문서보기//
//	bool		B_VIEWAIR;//1:항공뷰사용, 0:항공뷰사용안함//프로그램 로딩 시 기본설정으로 할것인지 여부//
//	int	 		NSEARCHBAR;//1:검색창크게, 2:검색창작게//
	bool		B_AUTOJIBUN;//1:지번 자동변경 사용, 0:사용안함//
	bool		B_WATERMARK;//1:워터마크 사용, 0:사용안함//
	bool 		B_AUTOLOGOUT;
	int			LOGOUTTIMER;
	int			MEMORYSIZE;//nImageThresholdLen
	int			DOC02DAY;//DOC02(SUBMIT_DATE, SURV_DAY, INSPCT_DAY)
	int			AREAFONTSIZE;//201119//측정(면적거리) Label Size, Color
	int			AREAFONTCOLOR;//201119//측정(면적거리) Label Size, Color
	int			DOC01GROUP;//201221//이동결의서(그룹1만 처리(Default) / 그룹1,2 처리)
	bool		B_EXPAND;//201221//검색결과트리 설정(1:펼치기(Default), 2:닫기//
	bool		B_OWNLABEL;//220308//REQ//구대장(부책) 한글표시(자동)//
	bool		B_GAGAMLAYER;//231030//GAGAMLAYER in LandArchive//
}INI_USERSET_STRUCT;

// Doc1 토지이동결의서
typedef struct {
	TTreeNode* tNode;
	bool 	bGroupGetState;
	int 	nGroupBuffIndex;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	char 	KIND_CODE[3+1];
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	SUBMIT_YEAR[4+1];//YYYY
	char 	PRCS_DATE[8+1];//YYYYYMMDD
	char 	MEASURE_TYPE[3+1];
	int 	GROUP_NO;
	int 	GROUP_NO1;
	char 	BF_PNU[19+1];
	char 	AF_PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT01_STRUCT;


typedef struct {
	TTreeNode* tNode;
	char PAGE_NO[6+1];
	char BF_PNU[19+1];
	char AF_PNU[19+1];
}DOCUMENT01_BFAF_ADDRESS_STRUCT;

//--------------------------------------------
//Doc2 측량결과도
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	int 	FRAME_NO;
	char 	KWON_NO[5+1];//	int 	VOL_NO;
	char 	PAGE_NO[6+1];
	char 	DOHO[10+1];
	char 	DOHO_SUB[10+1];
	char 	SURV_DAY[8+1];//YYYYMMDD
	char 	SURV_NAME[70+1];
	char 	INSPCT_DAY[8+1];//YYYYMMDD
	char 	INSPCT_NAME[70+1];
	char 	SURV_YEAR[4+1];//21->4, YYYY
	char 	SURV_ITEM[3+1];
	char 	RDSCALE_CODE[15+1];//500,600,1200,수치/1200 etc.
	char 	BF_PNU[19+1];
	char 	AF_PNU[19+1];
	char 	PATH_NAME[255+1];
	char 	KIND_CODE[3+1];
	char 	SUBMIT_DATE[8+1];//YYYYMMDD
	int		POS_X;
	int 	POS_Y;
	//#DOC02_GROUP//
	int		GROUP_NO;
	int 	PRCS_NO;
}DOCUMENT02_STRUCT;

////200424//DOC02GROUP
//typedef struct {
//	TTreeNode* tNode;
//	int 	ROLL_NO;
//	int 	FRAME_NO;
//	char 	KIND_CODE[3+1];
//	char 	KWON_NO[5+1];//	int 	VOL_NO;
//	char 	PAGE_NO[6+1];
//	char 	SURV_DAY[8+1];//YYYYMMDD
//	char 	SURV_NAME[70+1];
//	char 	INSPCT_DAY[8+1];//YYYYMMDD
//	char 	INSPCT_NAME[70+1];
//	char 	SUBMIT_DATE[8+1];//YYYYMMDD
//	char 	SURV_ITEM[3+1];
//	int		GROUP_NO;
//	char 	DOHO[10+1];
//	char 	DOHO_SUB[10+1];
//	char 	RDSCALE_CODE[15+1];//500,600,1200,수치/1200 etc.
//	int		POS_X;
//	int 	POS_Y;
//	char 	BF_PNU[19+1];
//	char 	AF_PNU[19+1];
//	char 	PATH_NAME[255+1];
//}DOCUMENT02_STRUCT;

//--------------------------------------------
// Doc3 면적측정부
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	char 	KIND_CODE[3+1];
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	SURV_YEAR[4+1];//YYYY
	char 	SURV_DAY[8+1];//YYYYMMDD
	char 	SURV_NAME[70+1];
	char 	INSPCT_DAY[8+1];//YYYYMMDD
	char 	INSPCT_NAME[70+1];
	char 	BF_PNU[19+1];
	char 	AF_PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT03_STRUCT;

//--------------------------------------------
// Doc4 부동산특별조치법
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	char 	PAGE_NO[6+1];//181231//int 	PAGE_NO;//
	char 	KWON_NO[5+1];//	int 	VOL_NO;
	char 	REQ_YEAR[4+1];//6->5, YYYY
	char 	REQ_DAY[8+1];//21->9, YYYYMMDD
	char 	OWN_NAME[70+1];
	char 	OWN_REG_NO[14+1];
	char 	ISSUE_NO[10+1];
	char 	APROV_STATUS[10+1];
	char 	LAW_NO[70+1];
	char 	KIND_CODE[3+1];
	char 	REC_NO[8+1];
	char 	PATH_NAME[255+1];
	char 	PNU[19+1];
}DOCUMENT04_STRUCT;

//--------------------------------------------
// Doc5 공유토지분할
typedef struct {
	TTreeNode* tNode;
	bool 	bGroupGetState;
	int 	nGroupBuffIndex;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	char 	KIND_CODE[3+1];
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	SUBMIT_YEAR[4+1];//YYYY
	char 	PRCS_DATE[8+1];//YYYYMMDD
	char 	MEASURE_TYPE[3+1];
	int 	GROUP_NO;
	int 	GROUP_NO1;
	char 	BF_PNU[19+1];
	char 	AF_PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT05_STRUCT;

//--------------------------------------------
// Doc6 환지계획서//
typedef struct {
	TTreeNode* tNode;
	bool 	bGroupGetState;
	int 	nGroupBuffIndex;
	char 	KIND_CODE[3+1];
	char 	ZONE_CODE[8+1];
	char 	COMP_YEAR[4+1];//YYYY
	char 	SERIAL_NUM[5+1];
	int	 	ROLL_NO;//181231//char ROLL_NUM[8];
	char 	KWON_NO[5+1];//	char 	VOL_NUM[5+1];
	char 	PAGE_NO[6+1];
	char 	PATH_NAME[255+1];
	char 	BF_PNU[19+1];
	char 	AF_PNU[19+1];
}DOCUMENT06_STRUCT;

//--------------------------------------------
// Doc7 지적도(폐쇄지적도)
typedef struct {
	TTreeNode* tNode;
	int		ID;
	char	PATH_NAME[255+1];
	char 	KIND_CODE[3+1];
	int 	ROLL_NO;
	int 	FRAME_NO;
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char	LAND_GBN[1+1];
	char	SIDOSGG[5+1];
	char	UMD[3+1];
	char	RI[2+1];
	char	SCALE[2+1];
	char	DOHO_BON[3+1];
	char	DOHO_BU[2+1];
	double 	X1;
	double 	Y1;
	double 	X2;
	double 	Y2;
	double 	SIZE_X;
	double 	SIZE_Y;
	double 	BASE_X;
	double 	BASE_Y;
	double 	RATIOX;
	double 	RATIOY;
	int		REMARK;
}DOCUMENT07_STRUCT;

//#MAPPOINT#
typedef struct {
	int 	POS_X;
	int 	POS_Y;
}MAPPOINT_STRUCT;

typedef struct {
	char 	SUR[10+1];//SIDOSGG+UMD+RI
	char	LAND_GBN[1+1];
	char	DOHO_BON[3+1];
	char	SCALE[2+1];
	int		COUNT;
	int		X;
	int		Y;
}DOCUMENT07_INDEX_STRUCT;

//201009
//--------------------------------------------
// Doc7 지적도(폐쇄지적도) : PNU & PATH_NAME (44760Req) 연속지적도 Base여서 LAND_INFO 테이블에 없는 지번에 대한 통합검색이 어렵다.
// PNU 중복있음//
typedef struct {
	char	PNU[19+1];
	char	KIND_CODE[3+1];
	char	PATH_NAME[255+1];
	int		IMAGEX;
	int		IMAGEY;
	int		X;
	int		Y;
	int		GBN;
}DOCUMENT07_PNU_STRUCT;

//--------------------------------------------
// Doc8 구대장
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	char 	SINGU_CODE[5+1];
	char 	KIND_CODE[3+1];
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	BUILD_NAME[30+1];
	char 	BUILD_HOSU[30+1];
	char 	ONOFF_CODE[3+1];
	char 	SINGU_NAME[12+1];
	char 	PNU[19+1];
	char 	PATH_NAME[255+1];
	char 	PATH_NAME_COLOR[255+1];
	char 	JUMIN_YN[1+1];
	char 	JUMIN_XY[255+1];
	char 	OWN_NAMES[255+1];
}DOCUMENT08_STRUCT;

// Doc9 보존문서
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	char 	KIND_CODE[3+1];
	char 	BASE_YEAR[4+1];//YYYY
	char 	BASE_MON[2+1];//MM
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT09_STRUCT;

typedef struct { // Doc10 도로명문서????
	int 		id;
	AnsiString 	DOC_NUM;
	AnsiString 	KIND_CODE;
	AnsiString 	GUBUN;
	AnsiString 	PAGE_NUM;
	AnsiString 	ROAD_NAME;
	AnsiString 	IMG_FOLDER;
}ROADADDRESS_STRUCT;

// Doc11 지적경계정비대장
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	char 	KIND_CODE[3+1];
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT11_STRUCT;

// Doc12 확인서발급대장
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	char 	PAGE_NO[6+1];
	char 	KWON_NO[5+1];//	int 	VOL_NO;
	char 	REQ_YEAR[4+1];//YYYY
	char 	REQ_DAY[8+1];//YYYYMMDD
	char 	OWN_NAME[60+1];
	char 	OWN_REG_NO[14+1];
	char 	ISSUE_NO[32+1];
	char 	APROV_STATUS[255+1];
	char 	KIND_CODE[3+1];
	char 	PATH_NAME[255+1];
	char 	PNU[19+1];
}DOCUMENT12_STRUCT;

// Doc13 보증인위촉대장
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	char 	PAGE_NO[6+1];
	char 	KWON_NO[5+1];//	int 	VOL_NO;
	char 	REQ_YEAR[4+1];//YYYY
	char 	REQ_DAY[8+1];//YYYYMMDD
	char 	OWN_NAME[60+1];
	char 	OWN_REG_NO[14+1];
	char 	KIND_CODE[3+1];
	char 	PATH_NAME[255+1];
}DOCUMENT13_STRUCT;

// Doc14 대장관련질의서
typedef struct {
	TTreeNode* tNode;
	bool 	bGroupGetState;
	int 	nGroupBuffIndex;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	char 	KIND_CODE[3+1];
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	SUBMIT_YEAR[4+1];//YYYY
	char 	PRCS_DATE[8+1];//YYYYMMDD
	char 	MEASURE_TYPE[3+1];
	int 	GROUP_NO;
	int 	GROUP_NO1;
	char 	PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT14_STRUCT;

// Doc15 비법인등록대장
typedef struct {
	TTreeNode* tNode;
	bool 	bGroupGetState;
	int 	nGroupBuffIndex;
	int 	CINDEX;
	char 	KWON_NO[5+1];
	char 	PAGE_NO[6+1];
	char 	KIND_CODE[3+1];
	char 	PRCS_DATE[8+1];//YYYYMMDD
	char 	DOC_KIND[60+1];
	char 	REG_NM[255+1];
	char 	REG_NO[14+1];
	char 	OWN[20+1];//201211//단체,종교등 텍스트 있는 경우 깨져서 한글 10글자 기준으로 늘림//금란과장님Req
	char 	APP[2+1];
	char 	APP_NM[60+1];
	char 	APP_NO[15+1];
	char 	APP_ADDR[255+1];
	char 	APP_OFFICE[255+1];
	char 	REPS_NM[60+1];
	char 	REPS_NO[15+1];
	char 	REPS_ADDR[255+1];
	char 	PATH_NAME[255+1];
	int 	ROLL_NO;
	int 	SR_NO;
	int 	GROUP_NO;
	int 	GROUP_NO1;
}DOCUMENT15_STRUCT;

// Doc16 비법인등록코드
typedef struct {
	TTreeNode* tNode;
	int 	CINDEX;
	char 	KWON_NO[5+1];
	char 	KIND_CODE[3+1];
	char 	REG_NM[255+1];
	char 	REG_NO[15+1];
	char 	PATH_NAME[255+1];
}DOCUMENT16_STRUCT;

// Doc17 토지조서
typedef struct {
	TTreeNode* tNode;
	int 	SEQ_NUM;
	char 	KWON_NO[5+1];//	int 	VOL_NUM;
	char 	KIND_CODE[3+1];
	char 	DOC_CODE[7+1];
	char 	DOC_NAME[64+1];
	char 	PYO_PAGE[16+1];
	char 	PAGE[16+1];
	char 	DOC_DATE[16+1];
	char 	PNU[19+1];
	char 	PATH_NAME[255+1];
}DOCUMENT17_STRUCT;

// Doc18 좌표계산부
typedef struct {
	TTreeNode* tNode;
	int 	ROLL_NO;
	int 	FRAME_NO;
	int 	SR_NO;
	int 	GROUP_NO;
	char 	KIND_CODE[3+1];
	char 	KWON_NO[8+1];
	char 	PAGE_NO[6+1];
	char 	SERIAL_NO[8+1];
	char 	JIGU_NAME[100+1];
	char 	JIGU_YEAR[4+1];//YYYY
	char 	PNU[19+1];
	char 	MEASURE_DATE[8+1];//YYYYMMDD
	char 	CHECK_DATE[8+1];//YYYYMMDD
	char 	DOGNPOINT[32+1];
	char 	BOJOPOINT[32+1];
	double	X;
	double	Y;
	char 	PATH_NAME[255+1];
}DOCUMENT18_STRUCT;
//--------------------------------------------


// Doc20 가감대장//231020//
typedef struct {
	char 	KWON_NO[5+1];
	char 	GAGAM_NO[6+1];
	char 	UMDRI_CD[10+1];
	char 	DOHO[20+1];
	char 	DOC_NAME[100+1];
	char 	KIND_CODE[3+1];
	char 	PAGE_NO[6+1];
	char 	SURV_DATE[8+1];
	char 	SURV_ETC[20+1];
	char 	PRCS_DATE[8+1];
	char 	PATH_NAME[255+1];
}DOCUMENT20_STRUCT;

typedef struct{
	char   	POINT_NO[20+1];
	char   	POINT_NAME[20+1];
	double	X;
	double	Y;
	double	WORLD_X;
	double	WORLD_Y;
}DOCUMENT20_BASEPOINT_STRUCT;

typedef struct{
	char 	KWON_NO[5+1];
	char 	GAGAM_NO[20+1];
	char   	LAND_CD[19+1];
}DOCUMENT20_LANDLIST_STRUCT;

typedef struct{
	char 	KWON_NO[5+1];
	char 	GAGAM_NO[20+1];
	char   	BASEPOINT[20+1];
	double	DIFF_X;
	double	DIFF_Y;
}DOCUMENT20_BASELIST_STRUCT;

typedef struct {
	char 	KWON_NO[5+1];
	char 	GAGAM_NO[6+1];
	char 	DOC_NAME[100+1];
	char 	SURV_ETC[20+1];//측량일자비고//
	char 	PRCS_DATE[8+1];//정리(결의)일자//
	char   	LAND_CD[19+1];
}DOCUMENT20_GAGAMLIST_STRUCT;

typedef struct{
	char 	CHECK_YN[1+1];
	char 	YEAR[4+1];
}DOCUMENT20_YEAR_STRUCT;
//--------------------------------------------



typedef struct {
	char cTarget[255];
	char cFileName[255];
	char cLocalFilePath[255];
	char cRemoteFilePath[255];
	char cIndexPolder[64];
	char cFileType[32];
}FTP_FILE_STRUCT;



typedef struct {
	char task_code[8+1];//[8];
	char kind_code[6+1];//[8];
	char kind_name[46+1];//[64];
	char doc_name[100+1];//[64];
}BASENAME_STRUCT;

typedef struct {
	char zonecode[16];
	char zonename[128];
}ZONENAME_STRUCT;

// ---------------------------------------------------------------------------
// To DO Tool Button State
// ---------------------------------------------------------------------------

typedef struct _ToolButtonState {
	int nState;
}ToolButtonState;

// ---------------------------------------------------------------------------
// To DO Mouse State
// ---------------------------------------------------------------------------
typedef struct _MouseState {
	bool bLeftDownFlag;
	bool bRightDownFlag;
	TPoint tpStartPoint;
	TPoint tpMovePoint;
	TPoint tpEndPoint;
}MouseState;

typedef struct _RactState {
	bool bRactCalcFlag;
	TPoint tpRactStartPoint;
	TPoint tpRactEndPoint;
}RactState;

typedef struct _JuminRectState {
	int left;
	int top;
	int right;
	int bottom;
}JuminRectState;


typedef struct {
	TRect 	rImage;
	int 	option;
}RECT_STRUCT;


//#JUMINHIDE#
typedef struct {
	int 	nLeft;
	int 	nTop;
	int 	nWidth;
	int 	nHeight;
	int 	nGapHeight;
	int 	nCount;
}DOC8_RECT_STRUCT;


//PATH_NAME LIST
typedef struct {
	int	 DOC_NO;//TB_DOCUMENT 문서번호//
	char KWON_NO[5+1];
	char KIND_CODE[3+1];
	char PAGE_NO[6+1];
	char DOHO[6+1];//201015//
	char PATH_NAME[255+1];
	char THUMB_NAME[255+1];
	bool CHECKED;//201126//그룹저장, 그룹인쇄시 체크여부//
}DOCUMENT_PATHLIST_STRUCT;

//KIND_CODE LIST - THUMBNAIL
typedef struct {
	char KIND_CODE[3+1];
	char KIND_NAME[46+1];
}THUMBNAIL_DOCKIND_STRUCT;

//TreeView =============================================
typedef struct _SearchNode {
	TTreeNode* tbeforeSelectNode;
	TTreeNode* tSelectNode;
	TTreeNode* tNodeA[DF_DOC_CNT+1];//191226//for Memo
}SearchNode;

typedef struct _SearchInfo {
//	char cSido[8];
//	char cGunGu[8];
//	char cUmd[8];
//	char cRi[8];
//	char cGbn[8];
//	char cBonBun[8];
//	char cBuBun[8];
	char cPnu[32];
//	char cPnuOld[32];
//	char cSidoName[32];
//	char cGunGuName[32];
//	char cUmdName[32];
//	char cRiName[32];
//	char cGbnName[32];
//	char cBonName[8];
//	char cBuName[8];
//	char cOldCaption[255];
}SearchInfo;







//UserInfo =============================================
typedef struct _UserInfo {
	char cName[32];
	char cIp[32];
	char cIpDec[32];
	char cDepart[32];
	char cGrade[2+1];
	char cId[32];
	char cIdDec[32];
	char cPw[256];//210303//#USER1_PW//32->256
	char cPwDec[32];
	char cTel[32];
	char cMemo[255];
	char cFailCut[2];
	char cLoginDate[32];
	char cLogoutDate[32];
}UserInfo;

typedef struct _UserLogInfo {
	char cId[32];
	char cIdDec[32];
	char cName[32];
	char cIp[32];
	char cIpDec[32];
	char cLoginDate[32];
	char cLogoutDate[32];
}UserLogInfo;

typedef struct _UserCmdInfo {
	char cId[32];
	char cIdDec[32];
	char cName[32];
	char cPnu[32];
	char cDate[32];
}UserCmdInfo;

typedef struct _UserHistInfo {
	char 	cIp[32];
	char 	cIpDec[32];
	char 	cDepart[32];
	char 	cId[32];
	char 	cIdDec[32];
	char 	cName[32];
	char 	cLoginDate[20];
	char 	cLogoutDate[20];
	int 	nDoc;
	int 	nAction; // 1:Query,2:Modify,3:Delete,4:Print
	char 	cActionName[32]; // 1:Query,2:Modify,3:Delete,4:Print,5:View,6:New,7:FileSave,8:Stat,9:Logout,11:권한변경,12:휴면계정//
	char 	cPnu[20];
	char 	cActionDate[20];//16->20
	char 	cPathName[255];
}UserHistInfo;

//210305//#TB_COPY_DNLD//
typedef struct _UserDownloadInfo {
	int 	nSeqNo;
	char 	cId[32];
	char 	cName[64];
	int 	nDoc;
	char 	cDocName[23];
	char 	cKindName[23];
	char 	cReason[40];
	char 	cActionDate[20];
	char 	cPathName[255];
}UserDownloadInfo;


//---------------------------------------------------------------------------
// INI CONTROL - RELEASE LIST
//---------------------------------------------------------------------------
typedef struct {
	int		SEQ;
	char   	DATE[10];
	char   	VERSION[20];
	char   	CATEGORY[64];
	char   	COMMENT[255];
	int		PATH_INDEX;
} RELEASELIST_STRUCT;

typedef struct {
	int		   LIST_INDEX;
	AnsiString PATH_NAME;
} RELEASEPATHLIST_STRUCT;





//---------------------------------------------------------------------------
// DOGWAKLINE
//---------------------------------------------------------------------------
typedef struct {
	TPoint tpMapStt;
	TPoint tpMapEnd;
	GPoint gpMapStt;
	GPoint gpMapEnd;
}DOGAKLINE_STRUCT;




//---------------------------------------------------------------------------
// LAND_INFO
//---------------------------------------------------------------------------
typedef struct {
	TTreeNode* tNode;
	int		ID;
	char   	LAND_CD[19+1];
	char	SIDOSGG_CD[5+1];
	char	UMD_CD[3+1];
	char	RI_CD[2+1];
	char	LAND_GBN[2+1];
	char	BOBN[3+1];
	char	BUBN[2+1];
	double	X;
	double	Y;
}LAND_INFO_STRUCT;










//---------------------------------------------------------------------------
// PRINTER
//---------------------------------------------------------------------------
#define		fr01cm							3.77953//pixel->mm
#define		cm01in							2.54//cm->inch


typedef struct _PAPER_SIZE {
	int nWidth;
	int nHeight;
}PAPER_SIZE_STRUCT;

typedef struct _PRINT_SETTING_STRUCT {
	char cID[32+1];
//	char cPrinterName[100+1];
//	int nPaperSize;
	int nScale;
	int nPosition;
	int nDoc8Page2;
	int nDoc8Stamp;
	int nDoc7P;
	int nPreview;
}PRINT_SETTING_STRUCT;

typedef struct _Doc07CopyInfo {
	char 	cCopyDate[32];
	int 	nCopyNo;
	char 	cCopyTime[32];
	char 	cCopyUser[64];
	char 	cCopyAddress[255];
	char 	cDoHoNo[32];
	char 	cScale[16];
	char 	cCopyDateTypeA[64];
	char 	cSiGunTitel[16];
}Doc07CopyInfo;





//---------------------------------------------------------------------------
// SIDOCODE
//---------------------------------------------------------------------------
typedef struct {
	char cSidoNm[32];
	char cSggCd[32];
	char cSggNm[32];
	char cUmdCd[32];
	char cUmdNm[32];
	char cRiCd[32];
	char cRiNm[32];
}SIDONAME_STRUCT;



//==========================================================================
// 구대장_소유주명 컬럼을 갖고 있는지 확인
//==========================================================================
typedef struct {
	int		Left;
	int 	Top;
	int		Right;
	int		Bottom;
	char 	OWN_NAMES[255+1];//소유주명
}DOC08_OWN_NAMES;


typedef struct {
	int		Left;
	int 	Top;
	int		Right;
	int		Bottom;
	char 	HISTORY[1024+1];//연혁
}DOC08_HISTORY;


//typedef struct {
//	int		Left;
//	int 	Top;
//	int		Right;
//	int		Bottom;
//	char 	DATE[255+1];//변동일자
//	char 	REASON[255+1];//사고
//	char 	ADDRESS[255+1];//주소
//	char 	NAME[255+1];//소유자
//}DOC08_OWNINFO;

typedef struct {
	int		Left;
	int 	Top;
	int		Right;
	int		Bottom;
	char 	DATA[1024+1];//데이터//
}DOC08_OWNINFO;
//DOC08_OWNINFO[0]//DATE
//DOC08_OWNINFO[1]//REASON
//DOC08_OWNINFO[2]//ADDRESS
//DOC08_OWNINFO[3]//NAME

//---------------------------------------------------------------------------
// 동적생성 검색 창 관련//
//---------------------------------------------------------------------------
typedef struct {
	int		COUNT;
	int		SINDEX;
	int		EINDEX;
}DOCVECTOR_STRUCT;

typedef struct {
	int 	COUNT;//문서종류별 개수//
	DOCVECTOR_STRUCT	DOC1;
	DOCVECTOR_STRUCT	DOC7;
}DOCUMENT_VECTORINFO_STRUCT;

typedef struct{//
	int     JIBUNINDEX;//210308//#ADDRESS_DUP//
	char 	ADDRESS[255];
	char 	LAND_CD[20];
}SEARCHEDJIBUN;


typedef struct {
	char cPnuOld[32];
	char cPnuNew[32];
//v1.0.0.5//DBSync//	char cOldCaption[255]; // Minji_#00_Sejong
}SEJONG_PNU_STRUCT;


//===========================================================================
// 검색어 연관 지번 혹은 검색HISTORY를 위한 PNU 관리//
//===========================================================================
typedef struct {
	char  LAND_KEY[19+1];
}PNU_STRUCT;



//===========================================================================
// 통계보기//
//===========================================================================
typedef struct {
	char  	YEAR[4+1];//나머지 문서는 구축년도//
	char  	LAND[8+1];//지적도, 구대장//
	char  	KIND_CODE[3+1];//문서구분//
	int		COUNT;
}STAT_STRUCT;



//===========================================================================
// 구대장 연혁 & 소유자정보//
//===========================================================================
// Doc8 구대장 지번목록
typedef struct {
	int		SEQNO;
	char 	PATH_NAME[255+1];
	char 	PNU[19+1];
	char 	KIND_CODE[3+1];
	char 	FORMAT_TYPE[1+1];
	char 	NUMBER_YN[1+1];
	char 	NUMBER_ID[30+1];
	char 	NUMBER_DT[14+1];
	char 	INPUT_YN[1+1];
	char 	INPUT_ID[30+1];
	char 	INPUT_DT[14+1];
	char 	CHECK_YN[1+1];
	char 	CHECK_ID[30+1];
	char 	CHECK_DT[14+1];
	char 	DIRECT_YN[1+1];
	char 	DIRECT_ID[30+1];
	char 	DIRECT_DT[14+1];
}DOCUMENT08_PNU_STRUCT;

typedef struct {
	int		PATHLIST_SEQNO;
	int		SEQ;//순번//
	char 	JIMOK[50+1];
	char 	AREA[50+1];
	char 	VALUE1[50+1];
	char 	VALUE2[50+1];
	char 	ERA_CODE[3+1];
	char 	HIS_DATE[8+1];
	char 	HISTORY[255+1];
}DOCUMENT08_HIS_STRUCT;

//241010//삭제선 데이터 별도 테이블//
typedef struct {
	int		PATHLIST_SEQNO;
	int		SEQ;//순번//
	char 	JIMOK[1+1];
	char 	AREA[1+1];
	char 	VALUE[1+1];
}DOCUMENT08_HIS_DEL_STRUCT;

typedef struct {
	int		PATHLIST_SEQNO;
	int		SEQ;//순번//
	char 	ERA_CODE[3+1];//연대
	char 	HIS_DATE[30+1];//"%단기4255년12월31일%"//날짜//char 	HIS_DATE[8+1];//날짜
	char 	REASON[100+1];//사정
	char 	OWN_ADDRESS[255+1];//소유자주소
	char 	OWN_NAME[255+1];//소유자명
}DOCUMENT08_OWNINFO_STRUCT;

//======================================================================
//231118//#SHAREOWN#
typedef struct {
	int		PATHLIST_SEQNO;
	int		SEQ;//순번//
	char 	ERA_CODE[3+1];//연대
	char 	HIS_DATE[30+1];//"%단기4255년12월31일%"//날짜//char 	HIS_DATE[8+1];//날짜
	char 	REASON[100+1];//사고
	char 	RATIO[50+1];//소유권보합(지분율)
	char 	OWN_ADDRESS[255+1];//소유자주소
	char 	OWN_NAME[255+1];//소유자명
}DOCUMENT08_SHAREOWN_STRUCT;
//======================================================================


//=====================================================
//241107//#한글화편집#DirectTable//내역저장하기//
//=====================================================
typedef struct {
	//from TB_COPY_DOC08
	char 	ACTION_DT[19+1];
	char 	USERNAME[64+1];

	int		COPY_DOC08_SEQNO;
	int		KIND_TYPE;//1.부책, 2:공유지연명부//
	int		PATHLIST_SEQNO;
	//항목 순번//
	//[부책]1:지목,2:지적,3:과세1,4:과세2,5:연혁,6:일자,7:사고,8:주소,9:성명
	//[공유지연명부]1.일자,2.사고,3.보합,4:주소,5:성명
	//항목 순번[부책-연혁](1:지목,2:지적,3:과세1,4:과세2,5:연혁)//
	//항목 순번[부책-소유자](1:일자,2:사고,3:주소,4:성명)//
	//항목 순번[공유지](1:일자,2:사고,3:보합,4:주소,5:성명)//
	int		CONTENTS_SEQ;
	int		SEQ;//순번//
	char 	BF_DATA[255+1];
	char 	AF_DATA[255+1];
}DOCUMENT08_HISTORY_STRUCT;
//=====================================================


//230623//
typedef struct
{
	int w;
	int h;
}TScale;//가로x세로 규격//

//221209//#DOC8_OVERLAP//
typedef struct {
	GPoint	gLT;//Real Left-Top
	TPoint	tLT;//Screen Left-Top
	TScale  gWH;//Real Width-Height
	TScale  tWH;//Screen Width-Height
}DOC8_BASEPOS_STRUCT;

//231211//취소선(String)인덱스 //
////
typedef struct {
	int nSLIndex;//nSLCount.index
	int	nSttIndex;
	int nEndIndex;
}DOC8_DELETEPOS_STRUCT;

typedef struct {
	TRect	tRect;//Screen Position//221209//#DOC8_OVERLAP//
	char 	DATA[1024+1];//데이터//
}DATA_STRUCT;


typedef struct {
	int		PATHLIST_SEQNO;//순번//
	int		PNU_CHECK;//지번일치여부//
	char 	PNU_NAME[30+1];//지번명//
	char 	LEVEL[20+1];//등급//
	char 	MEMO[96+1];//적요//minji@230201, 40->96
	char 	WRITE_ID[20+1];//입력자ID//
	char 	WRITE_DT[14+1];//입력일시//
}OLDLANDDOC_INFO_STRUCT;

//---------------------------------------------------------------------------
// RETE INFO
//---------------------------------------------------------------------------
typedef struct {
	int					DOC_KIND;//0:토지대장, 1:임야대장
	int					FORMAT_TYPE;//0:A ~
	double				RATE_PNU_X;
	double				RATE_PNU_Y;
	double				RATE_MEMO_X;
	double				RATE_MEMO_Y;
	double				RATE_JIMOK_X;
	double				RATE_JIMOK_Y;
	double				RATE_AREA_X;
	double				RATE_AREA_Y;
	double				RATE_AREA1_X;
	double				RATE_AREA1_Y;
	double				RATE_VALUE1_X;
	double				RATE_VALUE1_Y;
	double				RATE_VALUE2_X;
	double				RATE_VALUE2_Y;
	double				RATE_HISTORY_X;
	double				RATE_HISTORY_Y;
	double				RATE_DATE_X;
	double				RATE_DATE_Y;
	double				RATE_REASON_X;
	double				RATE_REASON_Y;
	double				RATE_ADDRESS_X;
	double				RATE_ADDRESS_Y;
	double				RATE_NAME_X;
	double				RATE_NAME_Y;
}RATE_STRUCT;


//---------------------------------------------------------------------------
// SHARP INFO(DELETE)
//---------------------------------------------------------------------------
typedef struct {
	TPoint		tpSTT;
	TPoint		tpEND;
}SHARP_POSITION_STRUCT;

//typedef struct
//{
//	int x;
//	int y;
//	int w;
//	int h;
//}BOUNDS_STRUCT;
//================================================================

//230623
typedef struct
{
	TPoint	tPoint;
	TScale  tScale;
}BOUNDS_STRUCT;


//=========================================================================
// 읍면동//통계에서 사용//
//=========================================================================
typedef struct {
	char	UMD_CD[3+1];
	char	UMD_NM[64+1];
}UMDDATA_STRUCT;

//=========================================================================
// 읍면동+리명//통계에서 사용//
//=========================================================================
typedef struct{
	char CD[5+1];
	char NM[128+1];
}UMDRICODE_STRUCT;
//=========================================================================
// 리명//
//=========================================================================
typedef struct{
	char DATA[64+1];
}RIDATA_STRUCT;

//=========================================================================
// 통계건수 데이터// [읍면동별]
//=========================================================================
typedef struct {
	char	UMDRI_CD[5+1];
	char	DOC_KIND[1+1];//토지대장, 임야대장//
	int		COUNT;
}DOC8_STAT_STRUCT;

//=========================================================================
// 통계건수 데이터// [사용자별]
//=========================================================================
typedef struct {
	//from TB_COPY_DOC08.*, TB_OLDLANDDOC_PATHLIST.PATH_NAME
	int		SEQNO;
	char	TYPE[1+1];//1.열람, 2:인쇄, 3:편집//
	char 	ACTION_DT[19+1];//2025-07-08 12:34:56//
	char 	USERNAME[64+1];
	char 	PNU[19+1];
	int		PATHLIST_SEQNO;
	char 	PATH_NAME[255+1];
}DOC8_STAT_USER_STRUCT;

//=========================================================================
// 사용자별 문서열람 현황
//=========================================================================
typedef struct {
	char 	FT_ID[64+1];
	char 	USERNAME[64+1];
	int		FT_DOC;
	int		DOC_NO[5];//구대장,지적도,이동결의서,측량결과도,기타문서//
	int 	COUNT;
}STAT_USERDOC_STRUCT;


//=========================================================================
// SmartOneStop 데이터//
//=========================================================================
typedef struct{
	char   ACCEPT_CDKEY[21+1];
	char   STATE_CD[5+1];
	char   LAWD_CD[8+1];
	char   ACCEPT_YEAR[4+1];
	char   ACCEPT_NO[5+1];
	char   ACCEPT_SEQ[4+1];
	char   KINDOF_CD[5+1];
	char   ACCEPT_DT[8+1];
	char   REGIST_DT[8+1];
	char   PROCESS_CD[5+1];
	char   APPLI_NO[18+1];
	char   APPLI_NM[100+1];
	char   CORP_YN[1+1];//법인여부
	char   JUMIN_NO[30+1];//주민번호/법인번호
	char   APPLI_PH[50+1];
	char   APPLI_REQUST_DT[8+1];
	char   ACCEPT_ID[30+1];
	int    BF_PNU_CNT;
	int    AF_PNU_CNT;
	char   LOCATION_NM[100+1];
	char   BF_BOBN[4+1];
	char   BF_BUBN[4+1];
	char   BF_JIMOK_CD[2+1];
	double BF_AREA;
	char   AF_BOBN[4+1];
	char   AF_BUBN[4+1];
	char   AF_JIMOK_CD[2+1];
	double AF_AREA;
	char   ETC[100+1];
	char   ATTACH_YN[1+1];
	char   JIGACALC_COMPLETE_YN[1+1];
	char   JIGACALC_OBJECTION_YN[1+1];
	char   JIGA_PY_YEAR[4+1];
	double JIGA_PY;
	double JIGA_CALC;
	char   JIGA_CALC_REASON[150+1];
	char   ACQUTAX_COMPLETE_YN[1+1];
	double ACQUTAX;
}STRUCT_LANDMOVEDATA;


//===========================================================================
//221020//Get INI Data -> DB Data//지적단위, 과세단위 등 DB에 설정된 값으로 읽어오는 함수//
typedef struct {
	int		SEQNO;//순번//
	char 	CATEGORY[20+1];//종류구분//
	char 	DATA[255+1];//내용//
	char 	WRITE_ID[20+1];//입력자ID//
	char 	WRITE_DT[14+1];//입력일시//
}OLDLANDDOC_USERFAVORITES_STRUCT;
//===========================================================================



//=================================================
#include <winsock.h>
#include "mainSrc.h"
#include "untSql.h"
#include "untTreeSystem.h"
#include "untFunc.h"
#include "PrintSetting.h"
#include "untEncrypt.h"
#include "untSearch.h"
#include "untFtpControl.h"
#include "untHanja.h"
#include "untCalculator.h"
#include "untUserAdd.h"
#include "untUserLogList.h"
#include "untUserManagement.h"
#include "untAbout.h"
#include "untReleaseList.h"
#include "untSidoCode.h"
#include "untSettingEnv.h"
#include "untDoc08Data.h"
#include "untResultList.h"
#include "untResultList2.h"
#include "untAreaCalculatorTypeA.h"
#include "untCalcDate.h"
#include "untProgramClose.h"
#include "untProgramCloseQ.h"
#include "MessageSrc.h"
#include "untMemo.h"
#include "untMemoHis.h"
#include "untMemoViewer.h"
#include "untAlphaView.h"
#include "untAlphaSub.h"
#include "untAlphaView2.h"
#include "untAlphaSub2.h"
#include "untChangeMenu.h"
#include "untMemoBatch.h"
#include "untMemoRegist.h"
#include "untStat.h"
#include "untAlphaDoc8.h"
#include "untDoc8View.h"//221208//#PRINT_IMPROVE//
#include "untDoc8History.h"
#include "untMainSub.h"
#include "untPreview.h"
#include "untTempDoc.h"
#include "untAIOCR.h"
//#include "untAIOCRData.h"
#include "TOcrThread.h"
//=================================================

