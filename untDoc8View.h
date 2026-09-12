//---------------------------------------------------------------------------

#ifndef untDoc8ViewH
#define untDoc8ViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "GR32_RangeBars.hpp"
#include <pngimage.hpp>
#include "GR32_Image.hpp"
#include <ImgList.hpp>

#include "FreeImage.h"
#include "GPoint.h"
#include <vector.h>
#include "bsPngImageList.hpp"
#include <jpeg.hpp>
#include "bsSkinCtrls.hpp"
//---------------------------------------------------------------------------
class TfrmDoc8View : public TForm
{
__published:	// IDE-managed Components
	TPanel *panMain;
	TImage *IMGSCREEN1;
	TPanel *palWait;
	TShape *shpWait;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	TbsPngImageView *bsPngImageView1;
	TbsPngImageList *bsPngImageList1;
	TTimer *Timer1;
	TButton *btnPrint;
	TCheckBox *chkAreaChange;
	TCheckBox *chkPrintOrg;
	TPanel *pnlTop;
	TImage *IMGDOC08PRINT1;
	TImage *IMGDOC08PRINT2;
	TImage *IMGDOC08UNIT;
	TPanel *pnlDoc08Print;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall IMGSCREEN1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall chkAreaChangeClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall IMGSCREEN1MouseEnter(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall IMGDOC08PRINTMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGDOC08PRINTMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGDOC08UNITClick(TObject *Sender);
	void __fastcall IMGDOC08UNITMouseEnter(TObject *Sender);

private:	// User declarations

//
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
	int 				realPosX;                     // DIB 원본의 좌상귀 x 좌표
	int 				realPosY;                     // DIB 원본의 좌상귀 y 좌표

	double				m_dDocFactor;
	double				m_dDocFitFactor;


	//영역지우기 후 m_DIB 변경 시 사용//
	FIBITMAP* 			m_DIB;
	BITMAPINFO* 		mBitMapInfo;
	FREE_IMAGE_FORMAT 	fiformat;
	AnsiString  		asPathName;
	int 				nImageWidth;
	int 				nImageHeight;
	//################################################################

	//공간정보 이동용
	TPoint startPoint, endPoint, clickPoint;
	TPoint	  			m_ptZoomWindowBR; //좌상단 점과 우하단 점..
	TPoint	  			m_ptZoomWindowLT; //좌상단 점과 우하단 점..
	bool      			m_bFlags;
	TPoint    			_movepoint;
	bool				m_bWheelZoom;//휠로 확대/축소
	TPoint  			pWheelMousePos;
	int					mToolButtonState;

	//======================================================================
	//이미지로딩//
	//======================================================================
	Graphics::TBitmap 					*BITMAP_BTN_UNIT[2];//원본<->변환(㎡)지적단위//
	Graphics::TBitmap 					*BITMAP_BTN_PRINT1[2];//한글번역본//
	Graphics::TBitmap 					*BITMAP_BTN_PRINT2[2];//원본+번역본//
	void __fastcall 					funcLoadButtonImage();
	void __fastcall 					funcDeleteButtonImage();


	//================================================================
	void __fastcall 	funcRefreshShow();
	double __fastcall 	funcSetImageBaseScale();
	void __fastcall 	funcFreeImage();
	void __fastcall 	funcImageViewClear();
	void __fastcall 	funcLoadImage(AnsiString _asFilename);
	void __fastcall 	funcFullView();
	double __fastcall 	funcGetImageScale(bool _bZoomIn);
	void __fastcall 	func_DrawImage();

	void __fastcall 	funcSetWaitWindows(bool bSetValue);

	TPoint __fastcall 	funcSurveyMapToDevice(const GPoint _scrPoint);
	GPoint __fastcall	funcDeviceToSurveyMap(const TPoint _scrPoint);	//

	AnsiString __fastcall 		funcGetPrintSetting();
	void __fastcall 	funcWriteIniData();

	//230328//한글변환Form을 직접 닫을 때 chkOwnNames을 해제하는데 그 때 frmDoc8View->Close()를 또 호출하며 반복하기에 Flag 처리//
	//한글변환Form을 직접 닫을 때, true 처리-> chkOwnNamesClick 처리 후 해제//
	bool				m_bDoc8ViewClose;


	__fastcall TfrmDoc8View(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDoc8View *frmDoc8View;
//---------------------------------------------------------------------------
#endif
