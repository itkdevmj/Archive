//---------------------------------------------------------------------------

#ifndef untAlphaSub2H
#define untAlphaSub2H
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
#include "bsPngImageList.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmAlphaSub2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *panMain;
	TImage *IMGSCREEN2;
	TPanel *palWait;
	TShape *shpWait;
	TbsPngImageView *bsPngImageView1;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	TbsPngImageList *bsPngImageList6;
	TPanel *Panel1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall IMGSCREEN2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
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

	bool				m_bWheelZoom;//휠로 확대/축소
	double				m_dDocFactor;
	double				m_dDocFitFactor;
	TPoint  			pWheelMousePos;
	//영역지우기 후 m_DIB 변경 시 사용//
	FREE_IMAGE_FORMAT 	fiformat;
	int    				readBpp;
	//################################################################

	//문서 paintbox 기능들 - 영역선택, 면적측정, 거리재기
	int					mToolButtonState;
	MouseState 			mMouseState;

	bool				bFormShowed;//formshow시에 resize하기 때문에 funcLoadImage가 두번 호출되는 것 방지하기 위함//
	bool				bAdjusting;//음영설정 중..
	bool				bZooming;//확대축소중..

	//AlphaBlend Value//
	int 				dAlphaRate[11];
	int					m_nAlphaFactor;


	//공간정보 이동용
	TPoint startPoint, endPoint, clickPoint, _movepoint;
	bool      m_bFlags;


	double __fastcall 	funcSetImageBaseScale();
	void __fastcall 	funcFreeImage();
	void __fastcall 	funcImageViewClear();
	void __fastcall 	funcLoadImage(AnsiString _asFilename);
	void __fastcall 	funcFullView();
	void __fastcall 	func_DrawImage();
	void __fastcall 	funcRefreshView();

	void __fastcall 	funcGetImageInfo();
	int __fastcall 		funcGammaImage(double _dValue);

	void __fastcall 	funcZoomInView();
	void __fastcall 	funcZoomOutView();

	TPoint __fastcall 	funcSurveyMapToDevice(const GPoint _scrPoint);
	GPoint __fastcall 	funcDeviceToSurveyMap(const TPoint _scrPoint);

	void __fastcall 	funcSetWaitWindows(bool bSetValue);

	//확대배율 알씨처럼 조정//
	double __fastcall 	funcGetImageScale(bool _bZoomIn);//201217//

	double				m_dDegree;
	//_nType(0) : 원본각도//
	//_nType(1) : 왼쪽으로 1도씩//
	//_nType(-1) : 오른쪽으로 1도씩//
	void __fastcall 	funcRotateView(int _nType);


	__fastcall TfrmAlphaSub2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAlphaSub2 *frmAlphaSub2;
//---------------------------------------------------------------------------
#endif
