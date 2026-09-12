//---------------------------------------------------------------------------

#ifndef untAlphaDoc8H
#define untAlphaDoc8H
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
//---------------------------------------------------------------------------
class TfrmAlphaDoc8 : public TForm
{
__published:	// IDE-managed Components
	TPanel *panMain;
	TImage *IMGSCREEN2;
	TPaintBox *pbRect2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
	//230925
	bool					m_bPaintCompleted;

//
public:		// User declarations

	//==================================================================
	classDOC08Data			*eData;

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
	int 				nImageWidth;
	int 				nImageHeight;
	AnsiString 			m_asBGFilePath;//인쇄 배경 서식//

	//################################################################

	double __fastcall 	funcSetImageBaseScale();
	void __fastcall 	funcFreeImage();
	void __fastcall 	funcImageViewClear();
	void __fastcall 	funcLoadImage(AnsiString _asFilename);
	void __fastcall 	funcFullView();
	void __fastcall 	func_DrawImage();

//======================================================================

	void __fastcall 			funcSetCharPosition();

	//=====================================================================================
	void __fastcall 			funcRefreshShow();//210712//

	AnsiString              	m_asSavedFileName;//221208//#PRINT_IMPROVE//
	AnsiString              	m_asSavedFileName1;//221208//#PRINT_IMPROVE//
	AnsiString              	m_asSavedFileName2;//221208//#PRINT_IMPROVE//

	int						m_nDOCKIND;//0:토지대장, 1:임야대장//
	bool					m_bAreaChange;//0:평,1:㎡//

	//================================================================
	vector<SHARP_POSITION_STRUCT>	m_vSharpPos;
	int 					m_nHLeft;//1163;//1164;
	int 					m_nOLeft;//1205;
	int 					m_nHTop;
	int 					m_nOTop;
	int 					m_nHWidth;
	int 					m_nOWidth;
	int						m_nNumberL;//숫자 Left GAP//221208//#PRINT_IMPROVE//
	int						m_nTopBottomGap;//231118//#SHAREOWN//
	//내부설정(Hard-Coding)//
	int						m_nFontSize;//A3 이미지에서 사용할 폰트크기(42)//
	int						m_nMiddleWidth;//A3 이미지에서 사용할 한글표시 중간-간격//
	//================================================================


	//=================================================================
	//부책//
	//=================================================================
	BOUNDS_STRUCT     		m_bsAlphaDoc8[13];//230623//
	void __fastcall 	   	funcGetPrintViewBoundary();
	void __fastcall 		funcMakeViewImageA3();
	void __fastcall 		funcRedrawOwnInfo();
	//=================================================================
	//공유지연명부//
	//=================================================================
	BOUNDS_STRUCT     		m_bsAlphaDoc8Share[10];
	void __fastcall 		funcGetPrintViewBoundaryShare();
	void __fastcall 		funcMakeViewImageA3Share();
	void __fastcall 		funcRedrawShareOwn();
	//=================================================================


	//231103//공유지연명부 한글폼 입력 위치가 제각각이므로 함수에서 처리//
	int __fastcall 			funcGetStartW(int _nType, int _nIndex, int _nCount, int _nTextW);
	int __fastcall 			funcGetStartH(int _nType, int _nIndex, int _nCount, int _nTextW);



	__fastcall TfrmAlphaDoc8(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAlphaDoc8 *frmAlphaDoc8;
//---------------------------------------------------------------------------
#endif
