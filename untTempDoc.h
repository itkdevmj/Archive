//---------------------------------------------------------------------------

#ifndef untTempDocH
#define untTempDocH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "bsPngImageList.hpp"

#include "FreeImage.h"
#include <Graphics.hpp>
#include "GR32_RangeBars.hpp"
#include "GR32_Image.hpp"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "bsPngImageList.hpp"
#include "bsSkinCtrls.hpp"
#include <ImgList.hpp>
#include <jpeg.hpp>


#define WIN32
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <math.hpp>
#include <JPEG.hpp>
//---------------------------------------------------------------------------
class TfrmTempDoc : public TForm
{
__published:	// IDE-managed Components
	TPanel *panWindowsMove;
	TLabel *lblFormTitle;
	TPanel *pnlClose;
	TImage *btnCloseTypeB;
	TPanel *palWait;
	TShape *shpWait;
	TbsPngImageView *bsPngImageView1;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	TLabel *lblDownloadCnt;
	TShape *Shape1;
	TPanel *pnlMain;
	TTimer *Timer1;
	TLabel *lblCount;
	TLabel *Label1;
	TPanel *pnlPreview;
	TScrollBox *ScrollBox1;
	TPanel *pnlTempDoc;
	TImage *IMGSCREEN1;
	TImage *IMGNOIMAGE;
	TImage *IMGNEXT;
	TImage *IMGPREV;
	TPanel *pnlPrev;
	TPanel *pnlNext;
	TShape *Shape2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall IMGPREVClick(TObject *Sender);
	void __fastcall IMGPREVMouseEnter(TObject *Sender);
	void __fastcall IMGPREVMouseLeave(TObject *Sender);
	void __fastcall IMGNEXTClick(TObject *Sender);
	void __fastcall IMGNEXTMouseEnter(TObject *Sender);
	void __fastcall IMGNEXTMouseLeave(TObject *Sender);
private:	// User declarations
public:		// User declarations


	//****************************************************************
	// FREE IMAGE
	//****************************************************************
	//################################################################
	HDC 				memDCDoc;
	HDC 				pDCDoc;
	HGDIOBJ 			pObjDoc;
	HBRUSH 				hbrDoc;
	HBITMAP 			hMembitmapDoc;
	HBITMAP 			hOldBitmapDoc;
	int    				readImageWidth;
	int    				readImageHeight;
	int					realLeft, realTop;
	int 				m_nSrcCenterX, m_nSrcCenterY;
	int 				m_nSrcWidth, m_nSrcHeight;
	double  			dScaleGap;
	int 				realPosX;                     // DIB ¿øº»ÀÇ ÁÂ»ó±Í x ÁÂÇ¥
	int 				realPosY;                     // DIB ¿øº»ÀÇ ÁÂ»ó±Í y ÁÂÇ¥

	double				m_dDocFactor;
	double				m_dDocFitFactor;


	//¿µ¿ªÁö¿ì±â ÈÄ m_DIB º¯°æ ½Ã »ç¿ë//
	FIBITMAP* 			m_DIB;
	BITMAPINFO* 		mBitMapInfo;
	FREE_IMAGE_FORMAT 	fiformat;
	AnsiString  		asPathName;
	int 				nImageWidth;
	int 				nImageHeight;
	//################################################################


	TList 		*pnlDocList;
	TList 		*imgDocList;
	TList 		*lblDocList;

	AnsiString								m_asCurrentFilePath;
	int										m_nTmpDocIndex;
	int										m_nTmpDocCount;
	vector<DOCUMENT_PATHLIST_STRUCT> 		m_vTmpDocList;

	GetImageInfo mGetImageInfo;

	void 		__fastcall funcSetWaitWindows(bool bSetValue);
	void 		__fastcall funcRefreshShow();

	//Control Thumbnail Image
	void 		__fastcall funcProcessTempDoc();
	void 		__fastcall funcGotoPageTempDoc();
	void 		__fastcall funcCreateListTempDoc();
	void 		__fastcall funcDeleteListTempDoc();
	void 		__fastcall funcMakeDynamicTempDoc(int _nIndex, int _nVectorIdx);
	void 		__fastcall funcShowCurrentLabel();
	AnsiString 	__fastcall funcLoadImageTempDoc(AnsiString _asFilename);
	void 		__fastcall TfrmTempDoc::imgTempDocDC_onClick(TObject *Sender);
	void 		__fastcall funcInitTempDoc();
	int 		__fastcall funcGetIndexList(AnsiString _asFilePath);
	AnsiString	__fastcall funcGetLocalFilePath(AnsiString _asDBFilePath);
	bool 		__fastcall funcExistTempList(AnsiString _asFilePath);

	//Control Main Image
	double 		__fastcall funcSetImageBaseScale();
	void 		__fastcall funcFreeImage();
	void 		__fastcall funcImageViewClear();
	void 		__fastcall funcLoadImage(AnsiString _asFilename);
	void 		__fastcall funcFullView();
	double 		__fastcall funcGetImageScale(bool _bZoomIn);
	void 		__fastcall func_DrawImage();
	void 		__fastcall funcProcessViewImage();

	void 		__fastcall funcSetPrevNextImage();


	__fastcall TfrmTempDoc(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTempDoc *frmTempDoc;
//---------------------------------------------------------------------------
#endif
