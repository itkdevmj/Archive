//---------------------------------------------------------------------------

#ifndef untMemoViewerH
#define untMemoViewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmMemoViewer : public TForm
{
__published:	// IDE-managed Components
	TPanel *panMain;
	TImage *IMGPREV;
	TImage *IMGNEXT;
	TPanel *panCenter;
	TImage *IMGVIEW;
	TImage *IMGNOIMAGE;
	TPanel *panWindowsMove;
	TImage *imgIconTitle;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TLabel *lblCount;
	TLabel *lblMemoTitle;
	TPanel *pnlIMGVIEW;
	TPanel *palMainView;
	TShape *shpBG;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall IMGPREVMouseEnter(TObject *Sender);
	void __fastcall IMGPREVMouseLeave(TObject *Sender);
	void __fastcall IMGPREVClick(TObject *Sender);
	void __fastcall IMGNEXTMouseEnter(TObject *Sender);
	void __fastcall IMGNEXTMouseLeave(TObject *Sender);
	void __fastcall IMGNEXTClick(TObject *Sender);
	void __fastcall IMGVIEWMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGVIEWMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGVIEWMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);

private:	// User declarations
public:		// User declarations

	bool	m_bFromMemo;//메모폼으로부터 왔는지..//포토는 바로 MemoViewer를 띄우기 때문에 분리//
	int		VIEWERWIDTH;
	int		VIEWERHEIGHT;


	//****************************************************************
	// FREE IMAGE
	//****************************************************************
	bool				m_bWheelZoom;//휠로 확대/축소
	double 				dDocZoomRate[10];
	int					m_nDocZoomFactor;
	int					m_nImageL;//IMGVIEW->Left
	int					m_nImageT;//IMGVIEW->Top
	int					m_nImageW;//IMGVIEW->Width
	int					m_nImageH;//IMGVIEW->Height
	int					nOriginL;//mGetImageInfo.nImageWidth : Left
	int					nOriginT;//mGetImageInfo.nImageWidth : Top
	//panning size
	int 				m_nGapX;
	int 				m_nGapY;
	int 				m_nScreenW;//mGetImageInfo.nImageWidth * mCurrScrImageInfo.dImgBaseScale = panMain->Width;
	int 				m_nScreenH;//mGetImageInfo.nImageHeight * mCurrScrImageInfo.dImgBaseScale = panMain->Height;

	TPoint  			pWheelMousePos;
	TPoint 				tpStartPoint;
	TPoint 				tpMovePoint;
	TPoint 				tpEndPoint;
	bool				bLeftDownFlag;

	GetImageInfo		mGetViewerImageInfo;
	CurrScrImageInfo	mCurrScrImageInfo;

	void 		__fastcall  funcClearForm();
	void 		__fastcall  funcViewForm();

	void __fastcall 		funcFreeImage();
	void __fastcall 		funcImageViewClear();
	void  __fastcall 		funcLoadImage(AnsiString _asFilename);
	void __fastcall 		funcFullView();
	void __fastcall     	funcRefreshView();
	void __fastcall 		funcZoomInView();
	void __fastcall 		funcZoomOutView();
	void __fastcall 		funcRotateView();
	void __fastcall 		funcInitRectView();
	double __fastcall   	funcSetImageBaseScale(int _nScreenW, int _nScreenH, int _nImageW, int _nImageH);
	void __fastcall 		funcProcessViewImage();

	__fastcall TfrmMemoViewer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemoViewer *frmMemoViewer;
//---------------------------------------------------------------------------
#endif
