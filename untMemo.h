//---------------------------------------------------------------------------

#ifndef untMemoH
#define untMemoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>

#include "FreeImage.h"
#include <Graphics.hpp>
#include "GR32_RangeBars.hpp"
#include "GR32_Image.hpp"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "bsPngImageList.hpp"
#include "bsSkinCtrls.hpp"
#include <ImgList.hpp>


#define WIN32
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <math.hpp>
#include <JPEG.hpp>

//---------------------------------------------------------------------------
class TfrmMemo : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlMemo;
	TPanel *pnlMemoHeader;
	TLabel *lblMemoHeader;
	TPanel *Panel1;
	TScrollBox *ScrollBox1;
	TImage *IMGEXIT;
	TImage *IMGHEAD;
	TOpenPictureDialog *OpenPictureDialog1;
	TPanel *pnlMemoBottom;
	TPanel *pnlMemoBottomT;
	TPanel *pnlMemoBottomD;
	TImage *IMGMEMOSAVE;
	TImage *IMGMEMODELETE;
	TImage *IMGMEMOMODIFY;
	TPanel *pnlMemoFile;
	TPanel *pnlMemoFileT;
	TLabel *lblMemoFile;
	TPanel *pnlMemoFileD;
	TPanel *pnlMemoFileD1;
	TImage *IMGADDFILE;
	TPanel *pnlMemoFileD2;
	TPanel *pnlMemoFileMent;
	TPanel *pnlMemoFileMentT;
	TPanel *pnlMemoFileMentD;
	TPanel *pnlMemoMemo;
	TPanel *pnlMemoMemoT;
	TLabel *lblMemoMemo;
	TPanel *pnlMemoMemoD;
	TPanel *pnlMemoPoi;
	TPanel *pnlMemoPoiT;
	TLabel *lblMemoPoi;
	TPanel *pnlMemoPoiD;
	TEdit *edtMemoPoi;
	TPanel *pnlMemoTitle;
	TPanel *pnlMemoTitleT;
	TLabel *lblMemoTitle;
	TPanel *pnlMemoTitleD;
	TEdit *edtMemoTitle;
	TPanel *Panel2;
	TPanel *pnlMemoBottom2;
	TPanel *pnlMemoBottom2T;
	TPanel *pnlMemoBottom2D;
	TImage *IMGMEMOBG;
	TImage *IMGMEMOHIS;
	TLabel *lblTitleLen;
	TLabel *lblMemoLen;
	TMemo *edtMemoMemo;
	TCheckBox *chkOpenYN;
	TLabel *lblMemoTitleMent;
	TShape *shpBG;
	TButton *btnDownload;
	TSaveDialog *SaveDialog1;
	TPanel *palWait;
	TShape *shpWait;
	TbsPngImageView *bsPngImageView1;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	TbsPngImageList *bsPngImageList6;
	TPanel *pnlColors;
	TLabel *lblRed;
	TLabel *lblGreen;
	TLabel *lblBlue;
	TEdit *edtRed;
	TEdit *edtGreen;
	TEdit *edtBlue;
	TPanel *pnlColor;
	TColorDialog *ColorDialog1;
	TPanel *pnlColorsT;
	TLabel *lblColorsT;
	TPanel *pnlColorsD;
	TImage *btnColor;
	TLabel *Label2;
	TPanel *pnlGagam;
	TPanel *pnlGagamT;
	TLabel *lblGagamT;
	TPanel *pnlGagamD;
	TLabel *lblGagamY;
	TLabel *lblGagamX;
	TEdit *edtGagamY;
	TEdit *edtGagamX;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall IMGEXITClick(TObject *Sender);
	void __fastcall IMGMEMOSAVEMouseEnter(TObject *Sender);
	void __fastcall IMGMEMOSAVEMouseLeave(TObject *Sender);
	void __fastcall IMGMEMOSAVEClick(TObject *Sender);
	void __fastcall IMGMEMOMODIFYMouseEnter(TObject *Sender);
	void __fastcall IMGMEMOMODIFYMouseLeave(TObject *Sender);
	void __fastcall IMGMEMOMODIFYClick(TObject *Sender);
	void __fastcall IMGMEMODELETEMouseEnter(TObject *Sender);
	void __fastcall IMGMEMODELETEMouseLeave(TObject *Sender);
	void __fastcall IMGMEMODELETEClick(TObject *Sender);
	void __fastcall IMGADDFILEMouseEnter(TObject *Sender);
	void __fastcall IMGADDFILEMouseLeave(TObject *Sender);
	void __fastcall IMGADDFILEClick(TObject *Sender);
	void __fastcall edtKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtEnter(TObject *Sender);
	void __fastcall edtExit(TObject *Sender);
	void __fastcall IMGHEADMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGMEMOHISClick(TObject *Sender);
	void __fastcall edtMaxChange(TObject *Sender);
	void __fastcall btnDownloadClick(TObject *Sender);
	void __fastcall btnColorClick(TObject *Sender);
private:	// User declarations
	//---------------------------------------------------------------------------
	int  nTitleMaxLen;//maxlength : 60
	int  nMemoMaxLen;//maxlength : 200
	bool bMaxLength;//edit 글자수 제한에 사용.

	char* buffer;


public:		// User declarations

	//***************************************************************************
	SQLHENV     m_hEnvDataSize;
	SQLHDBC     m_hDbcDataSize;
	SQLHSTMT    m_hStmtDataSize;
	SQLCHAR     m_InConDataSize[255];
	SQLCHAR     m_OutConDataSize[1024];
	SQLSMALLINT m_cbOutConDataSize;


	//***************************************************************************
	AnsiString	ADDFILEPATH;
	AnsiString	ADDTHUMBPATH;
	int			THUMBNAILSIZE;
	bool		m_bMemoRegist;//true(Regist), false(Modify)
//	bool		m_bMemoSaved;//저장완료상태인지 확인//
//	bool		m_bMemoNew;//메모보기상태에서 메모추가누르면 팝업처리하기 위함//
	bool		m_bMemoChange;
	AnsiString  m_asSelectPoiKey;//frmMain에서 선택한 메모아이콘의 POI_KEY 정보//
	int 		m_nSelectMemoIndex;//frmMain에서 선택한 메모아이콘의 m_vALLMEMOINFO.index 정보//
	AnsiString  m_asSelectLandCd;//frmMain에서 선택한 메모아이콘의 POI_KEY 정보//

	MEMOINFO_STRUCT					tempMEMOINFO;
	vector<MEMOINFO_STRUCT> 		m_vMEMOINFO;
//	MEMOVECTOR_STRUCT				tempMEMOVECTOR;
	vector<MEMOVECTOR_STRUCT> 		m_vMEMOVECTOR;
	MEMOFILE_STRUCT					tempMEMOFILE;
	vector<MEMOFILE_STRUCT> 		m_vMEMOFILE;
	MEMOINFOHIS_STRUCT				tempMEMOINFOHIS;
	vector<MEMOINFOHIS_STRUCT> 		m_vMEMOINFOHIS;

    GPoint						m_gpMemoPoint;
	AnsiString 					m_asPoiKey;
	int							m_nFileSeq;//뷰모드일때, 가장 큰 file의 seq를 갖고 있기 위함//
	AnsiString 					m_asTempPoiKey;//blob 저장용//
	AnsiString 					m_asSaveFileDir;//메모 첨부 다운로드 선택한 파일저장 폴더 갖고 있기//200829//


	GetImageInfo				mGetImageInfo;

	Graphics::TBitmap 			*BITMAP_BTN_ADDFILE[2];
	Graphics::TBitmap 			*BITMAP_BTN_MEMOSAVE[2];
	Graphics::TBitmap 			*BITMAP_BTN_MEMOMODIFY[2];
	Graphics::TBitmap 			*BITMAP_BTN_MEMODELETE[2];
	Graphics::TBitmap 			*BITMAP_BTN_MEMOCLOSE[2];
	Graphics::TBitmap 			*BITMAP_BTN_MEMOHIS;
	Graphics::TBitmap 			*BITMAP_BTN_DELETE;

	void 		__fastcall 		funcSetWaitWindows(bool bSetValue);
	void 		__fastcall  	funcLoadButtonImage();
	void 		__fastcall  	funcDeleteButtonImage();




	__int64 	__fastcall funcGetLocalFileSize(AnsiString _asPathName);
	AnsiString 	__fastcall funcUploadFile(int _nIndex);
	AnsiString 	__fastcall funcDownloadFile(int _nIndex);
	bool 		__fastcall funcDeleteFile(int _nIndex);

	//***************************************************************************
	// 선택한 파일의 THUMBNAIL을 보여주는 기능 -  동적 생성
	//***************************************************************************
	TList 		*pnlThumbList;
	TList 		*imgThumbList;
	TList 		*chkSelectList;
	TList 		*imgDeleteList;
	int			m_nThumbIndex;//
	int			m_nThumbCount;//Thumbnail 개수//
	int			m_nVectorIndex;//
	int			m_nVectorCount;//Vector 개수//
	void 		__fastcall funcCreateListThumb();
	void 		__fastcall funcDeleteListThumb();
	void 		__fastcall funcMakeDCThumb(AnsiString _asFileName);
	void 		__fastcall funcFreeImage();
	void 		__fastcall funcImageViewClear();
	AnsiString 	__fastcall funcLoadImageThumb(AnsiString _asFilename);
	void 		__fastcall imgThumbDC_onClick(TObject *Sender);
	void 		__fastcall imgDeleteDC_onClick(TObject *Sender);

	void 		__fastcall funcClearForm();
	void 		__fastcall funcViewForm();
	void 		__fastcall funcRefreshForm();
	void 		__fastcall funcReadMemoInfo(AnsiString _asPoiKey);
	void 		__fastcall funcReadMemoVector(AnsiString _asPoiKey);
	void 		__fastcall funcReadMemoFile(AnsiString _asPoiKey);
	void 		__fastcall funcReadMemoInfoHis(AnsiString _asPoiKey);
	bool 		__fastcall funcWriteMemoInfo(int _nType, int _nIndex);
	bool 		__fastcall funcWriteMemoVector(int _nType, int _nIndex);
	bool 		__fastcall funcWriteMemoFile(int _nType, int _nIndex);
	bool        __fastcall funcWriteMemoInfoHistory(int _nIndex);//#MOMOHISTORY#

	int         __fastcall funcReadMaxSeq(AnsiString _asPoiKey);

	bool 		__fastcall funcCheckSameData();

	void 		__fastcall funcWriteFileVectorLog();
	bool 		__fastcall funcPutBinaryData(AnsiString _asFileName, int _nCount, LONG _lFileSize);
	//파일용량구하기
	__int64 	__fastcall GetLocalFileSize(AnsiString _asFileName);

	void 		__fastcall funcReadFileVectorLog(AnsiString _asPoiKey);
	int 		__fastcall funcGetBinaryData(AnsiString _filename);
	int 		__fastcall func_readDataLength(AnsiString _qry);

	__fastcall TfrmMemo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemo *frmMemo;
//---------------------------------------------------------------------------
#endif
