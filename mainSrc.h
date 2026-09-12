//---------------------------------------------------------------------------

#ifndef mainSrcH
#define mainSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>

#include "bsSkinData.hpp"
#include "BusinessSkinForm.hpp"
#include "bsMessages.hpp"
#include "bsribbon.hpp"
#include "bsSkinCtrls.hpp"
#include "bsPngImageList.hpp"
#include "bsSkinMenus.hpp"
#include <Menus.hpp>
#include "bsSkinBoxCtrls.hpp"
//#include "bsSkinGrids.hpp"
#include <Mask.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include "bsSkinTabs.hpp"
#include "bsColorCtrls.hpp"
#include "IdBaseComponent.hpp"
#include "IdCoder.hpp"
#include "IdCoder3to4.hpp"
#include "IdCoderMIME.hpp"
#include "AdvCheckTreeView.hpp"
#include <Dialogs.hpp>
#include <ActnList.hpp>

//GR
#include "FreeImage.h"
#include <Graphics.hpp>
#include "GR32_RangeBars.hpp"
#include "GR32_Image.hpp"
#include <MPlayer.hpp>
#include <GIFImg.hpp>
//#include <Graphics.hpp>
//#include <GR32_Resamplers.hpp>
//#include <GR32_Filters.hpp>
//#include "GR32_Image.hpp"
//#include "GR32_ExtImage.hpp"
//#include "GR32_RangeBars.hpp"


#define WIN32
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <math.hpp>
#include <JPEG.hpp>
#include <vector.h>
#include <inifiles.hpp>
#include <mmsystem.h>
#include <registry.hpp>

#include "GPoint.h"
//#include "common.h"

#include "time.h"//210308//#LOADING_TEST

typedef struct _MTGAHEADER
{
	BYTE     IDLength;
	BYTE     ColorMapType;
	BYTE     ImageType;
	short    CMapStart;
	short    CMapLength;
	BYTE     CMapDepth;
	short    XOffset;
	short    YOffset;
	short    Width;
	short    Height;
	BYTE     PixelDepth;
	BYTE     ImageDescriptor;
}   MTGA_Header;






//****************************************************************
// FREE IMAGE
//****************************************************************
typedef struct _mBitmapHeader {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}mBitmapHeader;

typedef struct _GetImageInfo {
	FIBITMAP* m_DIB;
	BITMAPINFO* mBitMapInfo;
	mBitmapHeader mBitMapHeadInfo;
	FREE_IMAGE_FORMAT 	fiformat;

	Graphics::TBitmap *bmpSource32;

	AnsiString  asPathName;
	int 		nImageWidth;
	int 		nImageHeight;

	int 		nBPP;
	int 		nDBScale;
	int 		nInputScale;
}GetImageInfo;

typedef struct _CurrScrImageInfo {
	double dImgBaseScale;
	int nScreenWidth;
	int nScreenHeight;
	int nImageWidth;
	int nImageHeight;
	int nImageShortenWidth;
	int nImageShortenHeight;
	double dScaleRateWidth;
	double dScaleRateHeight;
	double dShortenScaleRateWidth;
	double dShortenScaleRateHeight;
}CurrScrImageInfo;

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TbsBusinessSkinForm *bsBusinessSkinForm1;
	TbsSkinData *bsSkinData1;
	TbsCompressedSkinList *bsCompressedSkinList1;
	TbsSkinMessage *bsSkinMessage1;
	TbsSkinData *bsSkinData2;
	TbsSkinPanel *palClient;
	TbsPngImageList *bsPngImageList1;
	TbsPngImageList *bsPngImageList2;
	TbsPngImageList *bsPngImageList5;
	TbsPngImageList *bsPngImageList4;
	TPanel *panelBrowser;
	TCppWebBrowser *CppWebBrowser1;
	TTimer *Timer1;
	TbsPngImageView *bsPngImageView1;
	TImageList *IList1;
	TbsSkinColorDialog *bsSkinColorDialog1;
	TbsPngImageList *bsPngImageList7;
	TImageList *ImageList1;
	TbsPngImageList *bsPngImageList3;
	TSaveDialog *SaveDialog1;
	TTimer *reLoadviewTimer;
	TbsSkinPanel *palMiniSearchBar;
	TbsSkinPanel *palViewOption;
	TbsSkinGroupBox *bsSkinGroupBox6;
	TbsSkinCheckBox *cbViewHybrid;
	TbsSkinCheckBox *cbViewRoad;
	TbsSkinGroupBox *bsSkinGroupBox8;
	TShape *shpUSEIMAGEJIJUKLINECOLOR;
	TShape *shpUSEIMAGEJIBUNCOLOR;
	TbsSkinLabel *bsSkinLabel5;
	TbsSkinLabel *bsSkinLabel6;
	TbsSkinGroupBox *bsSkinGroupBox7;
	TShape *shpUNUSEIMAGEJIBUNCOLOR;
	TShape *shpUNUSEIMAGEJIJUKLINECOLOR;
	TbsSkinLabel *bsSkinLabel9;
	TbsSkinLabel *bsSkinLabel10;
	TbsSkinGroupBox *bsSkinGroupBox9;
	TShape *shpSELECTREMARKCOLOR;
	TShape *shpSELECTUSEJIBUNCOLOR;
	TShape *shpSELECTUNUSEJIBUNCOLOR;
	TbsSkinLabel *bsSkinLabel11;
	TbsSkinLabel *bsSkinLabel12;
	TbsSkinEdit *edtLineWidth;
	TbsSkinCheckBox *cbLabelAlignment;
	TbsSkinLabel *bsSkinLabel4;
	TbsSkinLabel *bsSkinLabel7;
	TbsSkinCheckBox *cbSelectJibunSolid;
	TImage *IMGMINISEARCHBARBG;
	TEdit *edtMiniSearchText;
	TbsSkinPanel *palDocControlBar;
	TImage *IMGBASECONTROLBARBG;
	TImage *IMGDOCSAVEFILE;
	TImage *IMGDOCPRINT;
	TImage *IMGDOCROTATE;
	TImage *IMGDOCRECTCLEAR;
	TImage *IMGDOCADJUST;
	TImage *IMGDOCCONV;
	TbsSkinPanel *palZoomControlBar;
	TImage *IMGZOOMCONTROLBARBG;
	TImage *IMGZOOMIN;
	TImage *IMGZOOMOUT;
	TbsSkinPanel *palSpatialControlBar;
	TImage *IMGSPATIALCONTROLBARBG;
	TImage *IMGSPATIALCONTROLAREA;
	TImage *IMGSPATIALCONTROLDIST;
	TImage *IMGSPATIALCONTROLCANCEL;
	TImage *IMGMODECHANGEDOC;
	TImage *IMGMODECHANGEJIJUK;
	TActionList *ActionList1;
	TAction *Action1;
	TbsPngImageList *bsPngImageList6;
	TPanel *pnlSearchBar;
	TPanel *pnlDetailDoc01;
	TPanel *palMainSearchBar;
	TImage *imgSearchBarBg;
	TImage *imgDetailDoc01;
	TPanel *pnlSearchList;
	TbsSkinStatusPanel *bsSkinStatusPanel;
	TImage *IMGTAB00;
	TImage *IMGTAB01;
	TImage *IMGTAB02;
	TEdit *edtMainSearchText;
	TComboBox *cboInputDoc1;
	TComboBox *cboKindDoc1;
	TMaskEdit *dtStartDayDoc1;
	TMaskEdit *dtEndDayDoc1;
	TComboBox *cboGbn;
	TEdit *edtBobn;
	TEdit *edtBubn;
	TPanel *pnlDetailCommon;
	TImage *imgDetailCommon;
	TEdit *edtUmdRiCd;
	TEdit *edtUmdRiNm;
	TPopupMenu *PopupMenu1;
	TMenuItem *NMemoRegist;
	TMenuItem *NMemoView;
	TMenuItem *NDoc01;
	TMenuItem *NS1;
	TMenuItem *NDoc07;
	TImage *btnSettingEnv;
	TImageList *imgImageList1;
	TImageList *imgTreeImage;
	TImage *btnCodeSearch;
	TImage *btnQSearch;
	TImage *imgCal1_1;
	TImage *imgCal1_2;
	TMonthCalendar *CalendarDoc1;
	TMonthCalendar *CalendarDoc2;
	TbsSkinPanel *palSpaceControlBar;
	TImage *IMGSPACE;
	TPanel *pnlDocInfo;
	TAdvStringGrid *sgResult2;
	TbsSkinPanel *palPrevNextBar;
	TImage *IMGPREV;
	TImage *IMGNEXT;
	TImage *IMGPREVNEXTBARBG;
	TImage *IMGCODEFIND;
	TImage *IMGFIND;
	TImage *IMGLAYER;
	TPanel *palLayerSet;
	TImage *IMGLAYERSETBG;
	TImage *IMGLAYERAIR;
	TCheckBox *chkIndex500;
	TCheckBox *chkIndex600;
	TCheckBox *chkIndex1000;
	TCheckBox *chkIndex6000;
	TCheckBox *chkIndex1200;
	TCheckBox *chkIndex3000;
	TCheckBox *chkIndexLabel;
	TPanel *pnlEtc;
	TLabel *lblEtc1;
	TLabel *lblEtc2;
	TTimer *LogoutTimerCount;
	TImage *IMGLAYERMEMO;
	TImage *IMGLAYERDOC;
	TImage *IMGLAYERLEGAL;
	TPanel *Panel2;
	TPanel *Panel3;
	TImage *IMGLAYERDOGN;
	TLabel *lbl500;
	TPanel *Panel4;
	TLabel *lbl600;
	TLabel *lbl1000;
	TLabel *lbl1200;
	TLabel *lbl3000;
	TLabel *lbl6000;
	TbsSkinPanel *palMode;
	TbsSkinPanel *palLayer;
	TbsSkinPanel *palMemoPoint;
	TImage *IMGMEMOPOLY;
	TPageControl *pgDetail;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TPanel *pnlDetailDoc04;
	TImage *imgDetailDoc04;
	TComboBox *cboKindDoc4;
	TEdit *edtRecNoDoc4;
	TEdit *edtKwonNoDoc4;
	TPanel *pnlDetailDoc05;
	TImage *imgDetailDoc05;
	TImage *imgCal5_1;
	TImage *imgCal5_2;
	TComboBox *cboInputDoc5;
	TMaskEdit *dtStartDayDoc5;
	TMaskEdit *dtEndDayDoc5;
	TPanel *pnlDetailDoc06;
	TImage *imgDetailDoc06;
	TComboBox *cboKindDoc6;
	TEdit *edtZoneNmDoc6;
	TEdit *edtKwonNoDoc6;
	TTabSheet *TabSheet7;
	TImage *IMGTAB04;
	TImage *IMGTABSET;
	TImage *IMGTAB05;
	TImage *IMGTAB18;
	TTabSheet *TabSheet8;
	TPanel *pnlDetailDoc08;
	TImage *imgDetailDoc08;
	TComboBox *cboInputDoc8;
	TEdit *edtNamesDoc8;
	TComboBox *cboKindDoc8;
	TPanel *pnlDetailDoc07;
	TImage *imgDetailDoc07;
	TComboBox *cboKindDoc7;
	TEdit *edtDohoDoc7;
	TComboBox *cboScaleDoc7;
	TPanel *pnlDetailDoc02;
	TImage *imgDetailDoc02;
	TImage *imgCal2_1;
	TImage *imgCal2_2;
	TComboBox *cboInputDoc2;
	TMaskEdit *dtStartDayDoc2;
	TMaskEdit *dtEndDayDoc2;
	TEdit *edtDohoDoc2;
	TTabSheet *TabSheet18;
	TPanel *pnlDetailDoc18;
	TImage *imgDetailDoc18;
	TImage *imgCal18_1;
	TImage *imgCal18_2;
	TEdit *edtX18;
	TEdit *edtY18;
	TEdit *edtJigu18;
	TMaskEdit *dtEndDayDoc18;
	TMaskEdit *dtStartDayDoc18;
	TEdit *edtDogn18;
	TImage *btnQSearch18;
	TCheckBox *chkIndexAll;
	TbsSkinPanel *palMemoPoly;
	TImage *IMGMEMOPOINT;
	TImage *IMGZOOMBAR;
	TComboBox *cboKindDoc18;
	TbsSkinTrackBar *btnZoomTrackBar;
	TTreeView *treSystem;
	TImageList *ImageList2;
	TImageList *ImageList3;
	TTabSheet *TabSheet9;
	TTabSheet *TabSheet15;
	TTabSheet *TabSheet11;
	TTabSheet *TabSheet12;
	TTabSheet *TabSheet13;
	TTabSheet *TabSheet14;
	TTabSheet *TabSheet17;
	TPanel *pnlDetailDoc09;
	TImage *imgDetailDoc09;
	TComboBox *cboKindDoc9;
	TEdit *edtYearDoc9;
	TEdit *edtMonDoc9;
	TPanel *pnlDetailDoc11;
	TImage *imgDetailDoc11;
	TComboBox *cboKindDoc11;
	TPanel *pnlDetailDoc17;
	TImage *imgDetailDoc17;
	TComboBox *cboKindDoc17;
	TPanel *pnlDetailDoc15;
	TImage *imgDetailDoc15;
	TEdit *edtRegNmDoc15;
	TEdit *edtRegNoDoc15;
	TPanel *pnlDetailDoc14;
	TImage *imgDetailDoc14;
	TImage *imgCal14_1;
	TImage *imgCal14_2;
	TComboBox *cboInputDoc14;
	TMaskEdit *dtStartDayDoc14;
	TMaskEdit *dtEndDayDoc14;
	TEdit *edtKwonNoDoc14;
	TPanel *pnlDetailDoc13;
	TImage *imgDetailDoc13;
	TComboBox *cboKindDoc13;
	TEdit *edtOwnNmDoc13;
	TEdit *edtReqNoDoc13;
	TPanel *pnlDetailDoc12;
	TImage *imgDetailDoc12;
	TEdit *edtDate12;
	TImage *IMGTAB14;
	TImage *IMGTAB15;
	TImage *IMGTAB17;
	TImage *IMGLAYERPHOTO;
	TImage *IMGLAYERPOLY;
	TPageControl *pgDocInfo;
	TTabSheet *TabDocInfo;
	TPanel *pnlDogakLineT;
	TCheckBox *chkDogakLine;
	TAction *Action2;
	TAction *Action3;
	TImage *btnRegist;
	TPanel *pnlDetailDoc03;
	TImage *imgDetailDoc03;
	TImage *imgCal3_1;
	TImage *imgCal3_2;
	TMaskEdit *dtStartDayDoc3;
	TMaskEdit *dtEndDayDoc3;
	TImage *IMGTAB03;
	TImage *btnQSearch13;
	TImage *btnQSearch15;
	TLabel *lblHelp;
	TMemo *memoSejong;
	TPanel *pnlPnuList;
	TAdvStringGrid *sgPnuHist;
	TAdvStringGrid *sgPnuList;
	TPanel *pnlHistTitle;
	TLabel *lblHistZero;
	TPanel *pnlHistOff;
	TLabel *lblHistOff;
	TLabel *lblHistDel;
	TImage *btnManual;
	TImage *imgITKlogo;
	TMemo *Memo1;
	TImage *IMGLAYERHYBRID;
	TbsSkinPanel *palRegist;
	TImage *IMGREGIST;
	TPanel *palRegistSet;
	TPanel *pnlRegistSetD;
	TPanel *pnlRegistLMReq;
	TImage *btnLMReq;
	TPanel *pnlRegist02Attach;
	TImage *btn02Attach;
	TPanel *pnlRegist01Attach;
	TImage *btn01Attach;
	TPanel *pnlPoiInfo;
	TPanel *pnlPoiInfoD;
	TPanel *pnlPoiSymbol1;
	TPanel *pnlPoiDoc01;
	TImage *imgPoiDoc01;
	TLabel *lblPoiDoc01;
	TPanel *pnlPoiDoc02;
	TImage *imgPoiDoc02;
	TLabel *lblPoiDoc02;
	TPanel *pnlPoiDoc03;
	TImage *imgPoiDoc03;
	TLabel *lblPoiDoc03;
	TPanel *pnlPoiDoc04;
	TImage *imgPoiDoc04;
	TLabel *lblPoiDoc04;
	TPanel *pnlPoiDoc06;
	TImage *imgPoiDoc06;
	TLabel *lblPoiDoc06;
	TPanel *pnlPoiDoc08;
	TImage *imgPoiDoc08;
	TLabel *lblPoiDoc08;
	TPanel *pnlPoiDoc09;
	TImage *imgPoiDoc09;
	TLabel *lblPoiDoc09;
	TPanel *pnlPoiDoc17;
	TImage *imgPoiDoc17;
	TLabel *lblPoiDoc17;
	TPanel *pnlPoiInfoT;
	TLabel *lblPoiJibun;
	TPanel *pnlPoiDocFind;
	TImage *imgPopupFind;
	TLabel *lblPopupFind;
	TImage *IMGHEAD;
	TImage *IMGHEAD2;
	TImage *IMGPOI;
	TbsSkinPanel *palPoi;
	TImage *IMGREGISTSETTITLE;
	TbsSkinPanel *palRoadView;
	TImage *IMGROADVIEW;
	TImage *btnSettingEnv2;
	TPanel *pnlSystem;
	TImage *btnCloseTypeB;
	TImage *btnMax;
	TImage *btnMin;
	TPanel *pnlDocInfo07;
	TPanel *pnlDoc07Jibun;
	TLabel *lblDoc07Jibun;
	TComboBox *cboDoc07Gbn;
	TEdit *edtDoc07Bobn;
	TLabel *lblDoc07Dash;
	TEdit *edtDoc07Bubn;
	TButton *btnQueryDoc07Jibun;
	TShape *shpPoiInfo;
	TShape *shpRegistSet;
	TPanel *palWait;
	TShape *shpWait;
	TPanel *pnlWaitT;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TStatusBar *StatusBar1;
	TStatusBar *StatusBar2;
	TShape *shpPnuList;
	TLabel *Label1;
	TbsSkinPanel *palMainView;
	TImage *IMGSCREEN1;
	TPaintBox *PBCONTROL1;
	TImage *IMGCOMMONTIP;
	TPaintBox *PBDOGN;
	TPaintBox *PBSPACE;
	TImage *ICONMEMOPOINT;
	TImage *IMGDOCUMENTTIP;
	TLabel *lblHelpDrag;
	TImage *ICONMEMOPOLY;
	TImage *MEMOPOINTHELP;
	TImage *MEMOPOLYHELP;
	TbsSkinPanel *palConvBar;
	TImage *IMGCONVBG;
	TImage *IMGCONVHANJA;
	TImage *IMGCONVCALCDATE;
	TImage *IMGCONVCALCAREA;
	TImage *IMGCONVCALCULATOR;
	TPanel *palAdjustBar;
	TImage *imgAdjustBg;
	TPanel *pnlImgDocView;
	TImage *imgMapPointClose;
	TLabel *lblMapPoint;
	TPaintBox *pbRect3;
	TShape *shpMapPoint;
	TImage *IMGSCREEN2;
	TImage *IMGLOGO;
	TPanel *pnlMapPoint;
	TImage32 *IMGDOCTIP32;
	TPanel *pnlSPREAD;
	TImage *IMGSPREAD;
	TImage32 *IMGCOMTIP32;
	TPanel *pnlDoc8Jumin;
	TLabel *lblDoc8W;
	TLabel *lblDoc8H;
	TLabel *lblDoc8G;
	TLabel *lblDoc8C;
	TShape *shpDoc8Jumin;
	TButton *btnDoc8JuminDraw;
	TCheckBox *chkDoc8JuminHide;
	TButton *btnDoc8JuminSave;
	TEdit *edtDoc8W;
	TEdit *edtDoc8H;
	TEdit *edtDoc8G;
	TEdit *edtDoc8C;
	TPanel *pnlDetailCommonBlank;
	TImage *imgSrcBck;
	TPaintBox *PBCONTROL2;
	TPanel *pnlPreview;
	TScrollBox *ScrollBox1;
	TShape *shpThumb;
	TbsSkinStatusBar *pnlPreviewStatus;
	TbsSkinStatusPanel *previewStatusBar;
	TPanel *pnlPreviewPage;
	TLabel *lblPage1;
	TLabel *lblPage2;
	TLabel *lblPage3;
	TButton *btnPrev;
	TButton *btnNext;
	TbsSkinPanel *palOrg;
	TImage *IMGORG;
	TPanel *pnlDocInfo08;
	TCheckBox *chkResultList;
	TCheckBox *chkOwnNames;
	TImage *imgMover;
	TPanel *pnlPoiDoc07;
	TImage *imgPoiDoc07;
	TLabel *lblPoiDoc07;
	TLabel *Label2;
	TPopupMenu *PopupMenu2;
	TPopupMenu *PopupMenu3;
	TMenuItem *mnuLeftGroupPrint;
	TMenuItem *mnuLeftGroupSave;
	TPanel *pnlPrinterList;
	TPanel *pnlPrinterListT;
	TGroupBox *gbPrinters;
	TLabel *Label3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Edit1;
	TEdit *Edit2;
	TGroupBox *GroupBox3;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TComboBox *cboPrinterList;
	TLabel *lblPrinterListClose;
	TPanel *pnlPreviewGoto;
	TLabel *Label4;
	TEdit *edtGoto;
	TButton *btnGoto;
	TPanel *pnlAllThumb;
	TButton *btnPreviewAct;
	TCheckBox *chkAllThumb;
	TLabel *lblDownloadCnt;
	TButton *btnGroupPrint;
	TLabel *lblAdjust1;
	TLabel *lblAdjust2;
	TLabel *lblAdjust3;
	TbsSkinTrackBar *bsAdjust1;
	TbsSkinTrackBar *bsAdjust2;
	TbsSkinTrackBar *bsAdjust3;
	TGaugeBar *bsAdjust1_;
	TGaugeBar *bsAdjust2_;
	TGaugeBar *bsAdjust3_;
	TImage *IMGTAB06;
	TImage *IMGTAB07;
	TImage *IMGTAB08;
	TImage *IMGTAB09;
	TImage *IMGTAB11;
	TImage *IMGTAB12;
	TImage *IMGTAB13;
	TPanel *pnlDownloadReason;
	TPanel *pnlDownloadReasonT;
	TLabel *lblDownloadReasonClose;
	TButton *btnDownloadReasonSave;
	TEdit *edtDownloadReason;
	TShape *shpDownloadReason;
	TShape *shpPrinterList;
	TPanel *pnlJibunMent;
	TLabel *lblJibunMent1;
	TLabel *lblJibunMent2;
	TPanel *panelback1;
	TImage *IMGSCREEN3;
	TPaintBox *PBCONTROL3;
	TPaintBox *pbMentInfor;
	TPaintBox *pbWarningInfor;
	TCppWebBrowser *SiteViewBrowser;
	TPaintBox *pbRect1;
	TPaintBox *pbRect2;
	TCheckBox *chkDoc8Overlap;
	TbsSkinPanel *palDoc08Bar;
	TImage *IMGDOC08OVERLAP;
	TImage *IMGDOC08OWNNAMES;
	TImage *IMGDOC08BARBG;
	TImage *imgDoc08Mover;
	TEdit *edtNamesDoc4;
	TComboBox *cboOwnNamesDoc8;
	TTabSheet *TabSheet20;
	TPanel *pnlDetailDoc20;
	TImage *imgDetailDoc20;
	TComboBox *cboKindDoc20;
	TEdit *edtYearDoc20;
	TEdit *edtDocName20;
	TImage *IMGTAB20;
	TImage *IMGLAYERGAGAM;
	TImage *IMGTABDETAIL;
	TbsSkinPanel *palDoc08Bar1;
	TShape *Shape1;
	TImage *IMGDOC08EDIT;
	TImage *imgDoc08AIBar;
	TImage *imgDoc08AIBg;
	TTimer *tmrDoc08AI;
	TPanel *pnlPoiDoc20;
	TImage *imgPoiDoc20;
	TLabel *lblPoiDoc20;
	TPanel *pnlAllPreview;
	TMemo *Memo2;
	TAction *Action4;
	TMemo *Memo3;
	TPaintBox *pbRect4;
	TImage *imgDoc08Mover4;
	TCheckBox *cbOverlapAI;
	TCheckBox *cbOverlapDB;
	TbsSkinPanel *palDocZoomBar;
	TImage *IMGDOCZOOMBG;
	TImage *IMGDOCZOOMIN;
	TImage *IMGDOCZOOMOUT;
	TImage *IMGTEMPDOC;
	TPanel *palTempDoc;
	TPanel *palTempList;
	TImage *IMGTEMPLIST;
	TbsSkinPanel *palLMFS;
	TImage *IMGLMFS;
	TImage *imgDoc08AIGif;
	TTimer *TimerLMFS;
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);
	void __fastcall IMGSCREEN1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall IMGSCREEN1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall palClientResize(TObject *Sender);
	void __fastcall PBCONTROL1DblClick(TObject *Sender);
	void __fastcall PBCONTROL1Paint(TObject *Sender);
	void __fastcall sgResultGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
          TVAlignment &VAlign);
	void __fastcall shpUSEIMAGEJIJUKLINECOLORMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall shpUSEIMAGEJIBUNCOLORMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall shpUNUSEIMAGEJIJUKLINECOLORMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall shpUNUSEIMAGEJIBUNCOLORMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall shpSELECTREMARKCOLORMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall cbViewHybridClick(TObject *Sender);
	void __fastcall cbViewRoadClick(TObject *Sender);
	void __fastcall bsSkinTabSheet6Show(TObject *Sender);
	void __fastcall bsSkinTabSheet7Show(TObject *Sender);
	void __fastcall bsSkinTabSheet8Show(TObject *Sender);
	void __fastcall bsSkinTabSheet9Show(TObject *Sender);
	void __fastcall shpSELECTUSEJIBUNCOLORMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall shpSELECTUNUSEJIBUNCOLORMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall cbSelectJibunSolidClick(TObject *Sender);
	void __fastcall palViewOptionMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall edtLineWidthKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbLabelAlignmentClick(TObject *Sender);
	void __fastcall edtMiniSearchTextKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall IMGMINISEARCHBARBGMouseEnter(TObject *Sender);
	void __fastcall IMGMINISEARCHBARBGMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall IMGMINISEARCHBARBGMouseLeave(TObject *Sender);
	void __fastcall IMGDOCMouseEnter(TObject *Sender);
	void __fastcall IMGDOCMouseLeave(TObject *Sender);
	void __fastcall IMGDOCClick(TObject *Sender);
	void __fastcall IMGCONVMouseEnter(TObject *Sender);
	void __fastcall IMGCONVMouseLeave(TObject *Sender);
	void __fastcall IMGCONVClick(TObject *Sender);
	void __fastcall IMGZOOMMouseEnter(TObject *Sender);
	void __fastcall IMGZOOMClick(TObject *Sender);
	void __fastcall IMGSPATIALCONTROLClick(TObject *Sender);
	void __fastcall IMGSPATIALCONTROLMouseEnter(TObject *Sender);
	void __fastcall IMGSPATIALCONTROLMouseLeave(TObject *Sender);
	void __fastcall btnZoomTrackBarLastChange(TObject *Sender);
	void __fastcall IMGMODECHANGEClick(TObject *Sender);
	void __fastcall IMGLAYERClick(TObject *Sender);
	void __fastcall IMGLAYERMouseEnter(TObject *Sender);
	void __fastcall IMGLAYERMouseLeave(TObject *Sender);
	void __fastcall IMGLAYERSETClick(TObject *Sender);
	void __fastcall IMGSPREADClick(TObject *Sender);
	void __fastcall IMGSPREADMouseEnter(TObject *Sender);
	void __fastcall IMGSPREADMouseLeave(TObject *Sender);
	void __fastcall Action1Execute(TObject *Sender);
	void __fastcall edtMainSearchText1Enter(TObject *Sender);
	void __fastcall imgPoiDocClick(TObject *Sender);
	void __fastcall imgPoiInfoCloseClick(TObject *Sender);
	void __fastcall edtMainSearchTextEnter(TObject *Sender);
	void __fastcall edtMiniSearchTextExit(TObject *Sender);
	void __fastcall edtMiniSearchTextEnter(TObject *Sender);
	void __fastcall edtMainSearchTextKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtMainSearchTextKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall IMGTABMouseEnter(TObject *Sender);
	void __fastcall IMGTABMouseLeave(TObject *Sender);
	void __fastcall IMGTABClick(TObject *Sender);

	void __fastcall tbRectangleCancelClick(TObject *Sender);
	void __fastcall PBSPACEMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBSPACEMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall PBSPACEMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBSPACEPaint(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall IMGSCREEN2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

	void __fastcall NDoc01Click(TObject *Sender);
	void __fastcall NDoc07Click(TObject *Sender);
	void __fastcall NMemoViewClick(TObject *Sender);
	void __fastcall NMemoRegistClick(TObject *Sender);
	void __fastcall imgSearchBarBgMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall imgSearchBarBgMouseEnter(TObject *Sender);
	void __fastcall imgSearchBarBgMouseLeave(TObject *Sender);
	void __fastcall btnSettingEnvClick(TObject *Sender);
	void __fastcall btnSettingEnvMouseEnter(TObject *Sender);
	void __fastcall btnSettingEnvMouseLeave(TObject *Sender);
	void __fastcall btnQSearchClick(TObject *Sender);
	void __fastcall imgCalClick(TObject *Sender);
	void __fastcall CalendarDocDblClick(TObject *Sender);
	void __fastcall CalendarDocMouseLeave(TObject *Sender);
	void __fastcall IMGSPACEClick(TObject *Sender);
	void __fastcall IMGSPACEMouseEnter(TObject *Sender);
	void __fastcall IMGSPACEMouseLeave(TObject *Sender);

	void __fastcall IMGNEXTClick(TObject *Sender);
	void __fastcall IMGPREVClick(TObject *Sender);
	void __fastcall IMGPREVNEXTMouseEnter(TObject *Sender);
	void __fastcall IMGPREVNEXTMouseLeave(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall panWindowsMoveMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall panWindowsMoveDblClick(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall chkIndexClick(TObject *Sender);
	void __fastcall btnMinClick(TObject *Sender);
	void __fastcall btnMaxClick(TObject *Sender);
	void __fastcall edtBonBuKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall IMGFINDClick(TObject *Sender);
	void __fastcall IMGFINDMouseEnter(TObject *Sender);
	void __fastcall IMGFINDMouseLeave(TObject *Sender);
	void __fastcall IMGCODEFINDClick(TObject *Sender);
	void __fastcall IMGCODEFINDMouseEnter(TObject *Sender);
	void __fastcall IMGCODEFINDMouseLeave(TObject *Sender);
	void __fastcall LogoutTimerCountTimer(TObject *Sender);
	void __fastcall doc01KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc02KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc03KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc04KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc05KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc06KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc07KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc08KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc09KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc11KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc12KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc13KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc14KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc15KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc17KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc18KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall doc20KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtUmdRiCdExit(TObject *Sender);
	void __fastcall edtUmdRiCdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall IMGSCREEN2DblClick(TObject *Sender);
	void __fastcall PBDOGNPaint(TObject *Sender);
	void __fastcall IMGSCREEN1Click(TObject *Sender);
	void __fastcall IMGMEMOPOINTClick(TObject *Sender);
	void __fastcall IMGMEMOPOINTMouseEnter(TObject *Sender);
	void __fastcall IMGMEMOPOINTMouseLeave(TObject *Sender);
//	void __fastcall IMGTABPREVClick(TObject *Sender);
//	void __fastcall IMGTABNEXTClick(TObject *Sender);
//	void __fastcall IMGTABPREVMouseEnter(TObject *Sender);
//	void __fastcall IMGTABPREVMouseLeave(TObject *Sender);
//	void __fastcall IMGTABNEXTMouseEnter(TObject *Sender);
//	void __fastcall IMGTABNEXTMouseLeave(TObject *Sender);
	void __fastcall IMGCHANGEMENUClick(TObject *Sender);
	void __fastcall edtHangeulEnter(TObject *Sender);
	void __fastcall edtXY18Enter(TObject *Sender);
	void __fastcall IMGMEMOPOLYMouseEnter(TObject *Sender);
	void __fastcall IMGMEMOPOLYMouseLeave(TObject *Sender);
	void __fastcall IMGMEMOPOLYClick(TObject *Sender);
	void __fastcall chkIndexAllClick(TObject *Sender);
	void __fastcall pgDetailChange(TObject *Sender);
	void __fastcall IMGZOOMCONTROLBARBGClick(TObject *Sender);
	void __fastcall IMGZOOMCONTROLBARBGMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnQSearch18MouseEnter(TObject *Sender);
	void __fastcall btnQSearch18MouseLeave(TObject *Sender);
	void __fastcall btnZoomTrackBarMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGADJUSTBARMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGADJUSTBARMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall treSystemClick(TObject *Sender);
	void __fastcall treSystemDblClick(TObject *Sender);
	void __fastcall treSystemExpanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
	void __fastcall treSystemMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall treSystemEnter(TObject *Sender);
	void __fastcall treSystemMouseEnter(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall IMGSEARCHTEXTClick(TObject *Sender);
	void __fastcall edtMainSearchTextChange(TObject *Sender);
	void __fastcall edtMainSearchTextExit(TObject *Sender);
//	void __fastcall sgResult4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, Grids::TGridDrawState State);
//	void __fastcall chkOwnNamesClick(TObject *Sender);
//	void __fastcall sgResult4SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
//	void __fastcall sgResult4DblClick(TObject *Sender);
//	void __fastcall sgResult4SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
//	void __fastcall sgResult4GetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
//	void __fastcall sgResult4KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
//	void __fastcall imgSaveOwnNamesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
//	void __fastcall imgSaveOwnNamesMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall pbRect3MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall pbRect3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pbRect3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall pbRect3Paint(TObject *Sender);
	void __fastcall edtDate_OnExit(TObject *Sender);
	void __fastcall edtDate_OnClick(TObject *Sender);
	void __fastcall Action2Execute(TObject *Sender);
	void __fastcall Action3Execute(TObject *Sender);
	void __fastcall IMGPREVIEWSHOWMouseEnter(TObject *Sender);
	void __fastcall IMGPREVIEWSHOWMouseLeave(TObject *Sender);
	void __fastcall IMGPREVIEWSHOWClick(TObject *Sender);
	void __fastcall chkDogakLineClick(TObject *Sender);
	void __fastcall palClientMouseEnter(TObject *Sender);
	void __fastcall btnRegistClick(TObject *Sender);
	void __fastcall imgPopupFindMouseEnter(TObject *Sender);
	void __fastcall imgPopupFindMouseLeave(TObject *Sender);
	void __fastcall imgPopupFindClick(TObject *Sender);
	void __fastcall lblHistOffClick(TObject *Sender);
	void __fastcall lblHistDelClick(TObject *Sender);

	void __fastcall sgPnuListClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgPnuListGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
		  TVAlignment &VAlign);
	void __fastcall sgPnuHistClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgPnuHistGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
		  TVAlignment &VAlign);
	void __fastcall sgPnuListDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall imgMapPointCloseClick(TObject *Sender);
	void __fastcall btnManualMouseEnter(TObject *Sender);
	void __fastcall btnManualMouseLeave(TObject *Sender);
	void __fastcall btnManualClick(TObject *Sender);
	void __fastcall edtMainSearchTextClick(TObject *Sender);
	void __fastcall Memo1DblClick(TObject *Sender);
	void __fastcall sgPnuListClick(TObject *Sender);
	void __fastcall sgPnuListKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall IMGREGISTMouseEnter(TObject *Sender);
	void __fastcall IMGREGISTMouseLeave(TObject *Sender);
	void __fastcall IMGREGISTClick(TObject *Sender);
	void __fastcall btnLMReqMouseEnter(TObject *Sender);
	void __fastcall btnLMReqMouseLeave(TObject *Sender);
	void __fastcall btnLMReqClick(TObject *Sender);
	void __fastcall btn01AttachMouseEnter(TObject *Sender);
	void __fastcall btn01AttachMouseLeave(TObject *Sender);
	void __fastcall btn01AttachClick(TObject *Sender);
	void __fastcall btn02AttachMouseEnter(TObject *Sender);
	void __fastcall btn02AttachMouseLeave(TObject *Sender);
	void __fastcall btn02AttachClick(TObject *Sender);
	void __fastcall IMGPOIClick(TObject *Sender);
	void __fastcall IMGROADVIEWClick(TObject *Sender);
	void __fastcall IMGPOIMouseEnter(TObject *Sender);
	void __fastcall IMGTIPMouseLeave(TObject *Sender);
	void __fastcall pnlSearchListClick(TObject *Sender);

	void __fastcall chkDoc8JuminHide_OnClick(TObject *Sender);
	void __fastcall btnDoc8JuminDraw_OnClick(TObject *Sender);
	void __fastcall btnDoc8JuminSave_OnClick(TObject *Sender);
	void __fastcall edtDoc8_OnExit(TObject *Sender);
	void __fastcall edtMiniSearchTextChange(TObject *Sender);
	void __fastcall edtMiniSearchTextClick(TObject *Sender);
	void __fastcall edtMiniSearchTextKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall pnlImgDocViewMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall btnQueryDoc07JibunClick(TObject *Sender);
	void __fastcall pnlDoc07JibunKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtDoc07Enter(TObject *Sender);
	void __fastcall StatusBar1DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
          const TRect &Rect);
	void __fastcall lblPoiDocClick(TObject *Sender);
	void __fastcall pnlPoiDocClick(TObject *Sender);
	void __fastcall sgResult2ClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall btnQSearch7Click(TObject *Sender);
	void __fastcall PBCONTROL2DbLClick(TObject *Sender);
	void __fastcall PBCONTROL2Paint(TObject *Sender);

	void __fastcall btnPrevClick(TObject *Sender);
	void __fastcall btnNextClick(TObject *Sender);
	void __fastcall btnGotoClick(TObject *Sender);
	void __fastcall lblPreviewPageClick(TObject *Sender);
	void __fastcall edtGotoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall IMGDOCZOOMMouseEnter(TObject *Sender);
	void __fastcall IMGDOCZOOMClick(TObject *Sender);
	void __fastcall IMGORGClick(TObject *Sender);
	void __fastcall IMGORGMouseEnter(TObject *Sender);
	void __fastcall IMGORGMouseLeave(TObject *Sender);
	void __fastcall chkResultListClick(TObject *Sender);
	void __fastcall chkOwnNamesClick(TObject *Sender);
	void __fastcall lblPopupFindClick(TObject *Sender);
	void __fastcall lblRemoteCallClick(TObject *Sender);
	void __fastcall cboInputDoc8Change(TObject *Sender);
	void __fastcall cboKindDoc8Change(TObject *Sender);
	void __fastcall mnuLeftOnePrintClick(TObject *Sender);
	void __fastcall mnuLeftGroupPrintClick(TObject *Sender);
	void __fastcall mnuLeftGroupSaveClick(TObject *Sender);
	void __fastcall lblPrinterListCloseClick(TObject *Sender);
	void __fastcall btnPreviewActClick(TObject *Sender);
	void __fastcall btnGroupPrintClick(TObject *Sender);
	void __fastcall chkAllThumbMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall cboGbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ScrollBox1MouseEnter(TObject *Sender);
	void __fastcall ScrollBox1MouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall palClientMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall palClientMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall palMainSearchBarMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall palMainSearchBarMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall StatusBar1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StatusBar1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall StatusBar2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StatusBar2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall bsAdjustLastChange(TObject *Sender);
	void __fastcall bsAdjustMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall bsAdjust1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall palMainViewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall palMainViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnlSearchListMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall pnlSearchListMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall treSystemMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnlImgDocViewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall pnlSearchBarMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall pnlSearchBarMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imgSearchBarBgMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnlPreviewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnlPreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGHEAD2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall btnDownloadReasonSaveClick(TObject *Sender);
	void __fastcall edtDownloadReasonExit(TObject *Sender);
	void __fastcall edtDownloadReasonKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lblDownloadReasonCloseClick(TObject *Sender);
	//void __fastcall sgTreeDblClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall reLoadviewTimerTimer(TObject *Sender);
	void __fastcall IMGSCREEN3MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL3DblClick(TObject *Sender);
	void __fastcall PBCONTROL3MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL3Paint(TObject *Sender);
	void __fastcall pbMentInforPaint(TObject *Sender);
	void __fastcall pbWarningInforPaint(TObject *Sender);
	void __fastcall IMGSCREEN4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall IMGSCREEN4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL4DblClick(TObject *Sender);
	void __fastcall PBCONTROL4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall PBCONTROL4Paint(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall chkAreaChangeClick(TObject *Sender);
	void __fastcall pbRect2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall pbRect2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pbRect2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall pbRect2Paint(TObject *Sender);
	void __fastcall chkDoc8OverlapClick(TObject *Sender);
	void __fastcall IMGDOC08Click(TObject *Sender);
	void __fastcall dtStartDayDoc1MouseLeave(TObject *Sender);
	void __fastcall IMGTABDETAILClick(TObject *Sender);
	void __fastcall edtMainSearchTextMouseEnter(TObject *Sender);
	void __fastcall imgSearchBarBgClick(TObject *Sender);
	void __fastcall tmrDoc08AITimer(TObject *Sender);
	void __fastcall pnlAllPreviewClick(TObject *Sender);
	void __fastcall cboPreviewDocKindClick(TObject *Sender);
	void __fastcall Action4Execute(TObject *Sender);
	void __fastcall pbRect4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall pbRect4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pbRect4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall pbRect4Paint(TObject *Sender);
	void __fastcall IMGTEMPDOCClick(TObject *Sender);
	void __fastcall IMGTEMPDOCMouseEnter(TObject *Sender);
	void __fastcall IMGTEMPDOCMouseLeave(TObject *Sender);
	void __fastcall IMGTEMPLISTClick(TObject *Sender);
	void __fastcall IMGLMFSClick(TObject *Sender);
	void __fastcall TimerLMFSTimer(TObject *Sender);


private:	// User declarations
	bool					m_bPaintCompleted;//231121//only frmMain//
	//LMFS
	HANDLE hProcessB;//[토지이동흐름도] ArchiveLMFS.exe 프로그램의 핸들을 보관할 전역 멤버 변수//
	HWND hWindowB;   //[토지이동흐름도] ArchiveLMFS.exe프로그램의 윈도우 핸들 추가

	// 특정 프로세스 ID로 윈도우 핸들을 찾기 위한 도우미 함수들
	static BOOL CALLBACK FindWindowByPID(HWND hwnd, LPARAM lParam);
	HWND GetWindowHandleFromProcess(HANDLE hProcess);

public:		// User declarations

	AnsiString _DATABASE_;
	AnsiString _DBIP_;//DBIP = FTPIP
	AnsiString _DBPORT_;
	AnsiString _DBID_;
	AnsiString _DBPW_;
	BOOL 	__fastcall func_DBMSConnect();
	void 	__fastcall func_DBMSDisconnect();

	//============================================================
	// 220214//COPY_LMREQ_TO_SMARTONESTOP
	//============================================================
	bool		m_bONESTOPDBMSConnected;
	AnsiString _ONESTOP_DATABASE_;
	AnsiString _ONESTOP_DBIP_;//DBIP = FTPIP
	AnsiString _ONESTOP_DBPORT_;
	AnsiString _ONESTOP_DBID_;
	AnsiString _ONESTOP_DBPW_;
	BOOL 	__fastcall func_DBMSConnectC();
	void 	__fastcall func_DBMSDisconnectC();

	ULONG_PTR gdp_token_;

	AnsiString ROOTPATH, RESPATH, IMAGEMAINPATH, IMAGEMEMOPATH, IMAGEMENUPATH, IMAGEPOIPATH, IMAGEUIPATH;
	AnsiString TMPPATH, THUMBPATH, PRINTPATH, DOWNLOADPATH, TEMPPATH;
	AnsiString TMPDOCPATH, TMPTHUMBPATH;//TEMPDOCPATH, TEMPTHUMBPATH
	AnsiString _HIST_PATH;//210223//#_HIST_
	AnsiString LOGPATH;//220428//#LOG_EXCEPT//
	AnsiString DBPATH;//LMFS
	//=======================================
	//221202//LMREQ//CREATE_DIR
	AnsiString LMREQ_SIGN_PATH;
	AnsiString LMREQ_IDSCAN_PATH;
	AnsiString LMREQ_IMAGES_PATH;
	//=======================================

	//공용사용 가능 함수모음
	TIniFile 	*SIDOINI;
	TIniFile 	*_iniPrintSetting;
	TIniFile 	*USERSETINI;//사용자 환경설정//
	TIniFile 	*USERINI;//로그인하는 사용자정보//
	TIniFile    *PRINTDOC07INI;//지적도등본양식출력용//
	TIniFile    *PRINTDOC19INI;//JDM출력양식//
	TIniFile    *PREVIEWINI;//LMREQ출력내용//
	//TIniFile *CONVERTINI;
	TIniFile    *CONFIGDOC8INI;//211205//구대장 연혁 & 소유자정보//

	AnsiString 	_SIDOCODE;
	AnsiString 	_SIDONAME;


	INI_STRUCT			INIINFO;//M/191107
	void __fastcall 	funcGetIniInfo();//M//191107//CONFIG.INI에 있는 INI_STRUCT 정보를 가져온다//
	void __fastcall 	funcSetXDBPath();
	void __fastcall 	funcGetLoginUserInfo();//M//191107//CONFIG.INI에 있는 INI_STRUCT 정보를 가져온다//
	AnsiString			m_asCurrentId;//M//191107//UserInfo Id
	AnsiString			m_asCurrentNm;//UserInfo Name
	INI_USERSET_STRUCT	INIUSERSETINFO;//M/191118
	void __fastcall 	funcGetIniUserSetInfo();//M//191118//USERSET.INI에 있는 INI_USERSET_STRUCT 정보를 가져온다//
	void __fastcall 	funcSetIniUserSetInfo();
	//INIINFO기본설정 외의 설정들//
	bool				INI_B_SETMAPPOINT;//#SETMAPPOINT#
	bool				INI_B_MAPPOINT;//#MAPPOINT#
	bool				INI_B_DOGWAK;//#DOGWAKLINE#
	bool				INI_B_JUMINHIDE;//#JUMINHIDE#
	bool				INI_B_OWNNAMES;//#OWNAMES#
//260616//NotUsed//	bool				INI_B_OWNINFO;//#OWNINFO#
	bool				INI_B_KRAS;//KRAS//
	bool				INI_B_LMREQ;//LMREQ//토지이동신청서//
	bool				INI_B_01ATTACH;//#01ATTACH#
	bool				INI_B_02ATTACH;//#02ATTACH#
	bool				INI_B_GAGAM;//DOCUMENT20 존재 시//

	AnsiString 			INI_AS_THUMBEXT;//#THUMB_EXT#//Thumbnail 확장자//
	bool				INI_B_IMGMODE;//210208//#IMGMODE//비암호화 문서를 암호화/복호화/업로드 기능//
	bool				INI_B_ROADVIEW;//210428//#ROADVIEW//

	AnsiString 			m_asParamStr1;
	AnsiString 			m_asParamStr2;


	//---------------------------------------------------------------------------
	// 테스트 관련//[TODO]
	//---------------------------------------------------------------------------
	bool	m_bDEBUG;
	bool	m_bMSG;
	bool	m_bGAGAMREGIST;//가감대장등록 시, 다른 메모와 구별된 테이블에 등록하기 위함//


	// MEMO - DB TABLE NAME
	AnsiString TABLE_MEMOINFO, TABLE_MEMOFILE, TABLE_MEMOVECTOR, TABLE_MEMOINFOHIS, FTP_DIR_MEMO;

	TABLE_NAMES m_t_TABLENAMES;

	//메세지박스 출력
	int __fastcall func_MessageDlg( const AnsiString Msg, Dialogs::TMsgDlgType DlgType, Dialogs::TMsgDlgButtons Buttons, int HelpCtx);

	//지도 출력용
	//공간정보 출력 옵션
	bool currentModeShow1; //지적도
	bool currentModeShow8; //항공사진

	//==================================================================
	//210427//#ROADVIEW//
	bool currentModeShow3; //로드뷰//210427//
	//로드뷰, VWORLD 연계
	bool siteview, roadviewclick, onepointcheck;
	void __fastcall func_reRoadView();
	double prevCurrentX, prevCurrentY;
	AnsiString roadviewUrl;
	void __fastcall func_readRoadviewUrl();
	void __fastcall func_ConfigPlayBack();
	void __fastcall func_DrawMentInfor();
	void __fastcall func_DrawWarningInfor();
	//==================================================================

	BLENDFUNCTION bf;
	double daumscalemapping[10];

	TStringList *strDaumHtml[5];
	TStringList *urlHtml;

	//200315
	TStringList *strDaumHtml2[3];
	TStringList *urlHtml2;

	MBR m_MBR;
	enum ManipulMode {None=0, ZoomIn, ZoomOut, ZoomWindow, Panning, Selector, StreetGauge, AreaGauge, SpaceRect, RectSelect, MemoRect, MemoPoint, Dogwak, OwnNames} m_eManipulationMode;  //화면 컨트롤 기능
	ManipulMode                 m_eManipulationModeBck;//200731

	double	  m_lfRatio;	    // ratio between screen & map
	double	  m_lfZoomFactor;   // Screen zoom factor
	int       m_nZoomFactor;
	GPoint	  m_geoCenterPoint; // geoCenter Point
	TPoint	  m_ptCenterPoint;  // screen Center point
	TPoint	  m_ptZoomWindowBR; //좌상단 점과 우하단 점..
	TPoint	  m_ptZoomWindowLT; //좌상단 점과 우하단 점..
	bool      m_bFlags;
	TPoint    _movepoint;
	//230920//Ratio에 맞는 Zoom Level을 찾기//
	void __fastcall funcGetFitZoomFactor(double _dRatio);


	READJIBUN tempReadJibun;
	vector<READJIBUN> m_v_READJIBUN;

	//지적도 - 읍면동
	READEMD tempReadEmd;
	vector<READEMD> m_v_READEMD;
	//지적도 - 리
	READRI tempReadRi;
	vector<READRI> m_v_READRI;
	//지적도 - 지번
	READCBND tempReadCbnd;
	vector<READCBND> m_v_READCBND;
	//191114_LAYER_DOGWAK
	//지적도-인덱스맵
	READINDEXMAP tempReadIdx0500;
	READINDEXMAP tempReadIdx0600;
	READINDEXMAP tempReadIdx1000;
	READINDEXMAP tempReadIdx1200;
	READINDEXMAP tempReadIdx3000;
	READINDEXMAP tempReadIdx6000;

	vector<READINDEXMAP> m_v_READIDX0500;
	vector<READINDEXMAP> m_v_READIDX0600;
	vector<READINDEXMAP> m_v_READIDX1000;
	vector<READINDEXMAP> m_v_READIDX1200;
	vector<READINDEXMAP> m_v_READIDX3000;
	vector<READINDEXMAP> m_v_READIDX6000;
	//230919//#INDEXMAP//Vector.index 찾기//
	int __fastcall funcGetIndexMapVectorIndex(AnsiString _asDom);

//=============================================================================
//231018//GAGAMLAYER in LandArchive//
//=============================================================================
	READGAGAM tempReadGagam;
	vector<READGAGAM> m_v_READGAGAM;

    //

	STANDARDSTRUCT m_STANDARDEMD;
	STANDARDSTRUCT m_STANDARDRI;
	STANDARDSTRUCT m_STANDARDCBND;
    //191114_LAYER_DOGWAK
	STANDARDSTRUCT m_STANDARDIDX0500;
	STANDARDSTRUCT m_STANDARDIDX0600;
	STANDARDSTRUCT m_STANDARDIDX1000;
	STANDARDSTRUCT m_STANDARDIDX1200;
	STANDARDSTRUCT m_STANDARDIDX3000;
	STANDARDSTRUCT m_STANDARDIDX6000;
	//
	STANDARDSTRUCT m_STANDARDGAGAM;//231018//GAGAMLAYER in LandArchive//

	polyObject SHPPoly;
	//공간정보-지적도
	vector<polyObject> m_vSHPPOLYEMD;
	vector<polyObject> m_vSHPPOLYRI;
	vector<polyObject> m_vSHPPOLYCBND;
	//191114_LAYER_DOGWAK
	vector<polyObject> m_vSHPPOLYIDX0500;
	vector<polyObject> m_vSHPPOLYIDX0600;
	vector<polyObject> m_vSHPPOLYIDX1000;
	vector<polyObject> m_vSHPPOLYIDX1200;
	vector<polyObject> m_vSHPPOLYIDX3000;
	vector<polyObject> m_vSHPPOLYIDX6000;
	//
	vector<polyObject> m_vSHPPOLYGAGAM;//가감대장//231018//GAGAMLAYER in LandArchive//

	vector<CONFIGLAYER> m_vCONFIGLP;

	vector<CODETABLE> m_vCODETABLE;

	MAININI_STRUCT m_MAININI;

	REALAREA_STRUCT tempREALAREA;
	vector<REALAREA_STRUCT> m_vREALAREA;
	AREA_STRUCT tempAREA;
	vector<AREA_STRUCT> m_vAREA;

	DIST_STRUCT tempDIST;
	vector<DIST_STRUCT> m_vDIST;
	REALDIST_STRUCT tempREALDIST;
	vector<REALDIST_STRUCT> m_vREALDIST;

	//메모영역설정용//191129
	REALAREA_STRUCT tempMEMORECT;
	vector<REALAREA_STRUCT> m_vMEMORECT;

	//공간파일 관련
	void __fastcall func_readSpatialDataFile();//공간파일 읽기..
	void __fastcall func_clearRealData();

	void __fastcall func_readRealData(AnsiString theme, AnsiString layer, AnsiString fname);
	void __fastcall func_readPolyData(AnsiString layer, int nRecords, FILE *readfile, int _shapeType);
	void __fastcall func_readPointData(AnsiString layer, int nRecords, FILE *readfile);

	//중심 및 면적 계산용
	double __fastcall func_Area2(GPoint a, GPoint b, GPoint c);
	GPoint __fastcall func_FindCG(vector<GPoint>& vPoint, double *area);
	GPoint __fastcall func_Centroid3(GPoint a, GPoint b, GPoint c);
	AnsiString __fastcall func_CodeTableIndexAlloc(AnsiString layer);

	void __fastcall func_DrawImagePaint();

	void __fastcall _2DEngineObject_pnsFunc_DrawSelectCbnd(int gbn, HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageCbndPolygon(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageCbndLabel(HDC _pDC, HDC _pDCEtc, TRect _rect);
	//=============================================================
	//241211//심볼표시 분리//
	//=============================================================
	void __fastcall func_DrawPaintImageCbndSymbol(HDC _pDC, HDC _pDCEtc, TRect _rect);

	void __fastcall _2DEngineObject_pnsFunc_DrawSelectEmd(int gbn, HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageEmd(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall _2DEngineObject_pnsFunc_DrawSelectRi(int gbn, HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageRi(HDC _pDC, HDC _pDCEtc, TRect _rect);
	//191114_LAYER_DOGWAK
	void __fastcall func_DrawPaintImageIdx0500(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageIdx0600(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageIdx1000(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageIdx1200(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageIdx3000(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall func_DrawPaintImageIdx6000(HDC _pDC, HDC _pDCEtc, TRect _rect);
	//
//=============================================================================
//가감대장//231018//GAGAMLAYER in LandArchive//
//=============================================================================
	bool	m_bGagamIconClicked;//기준점클릭(true)과 문서뷰에서 항공뷰로 이동시 해당 가감지구로 이동하는 것(false)과 구별하기 위함//
	vector<DOCUMENT20_STRUCT> 				m_ResultDocument20;
	void __fastcall 						func_DrawPaintImageGagam(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall 						func_DrawPaintImageSelectGagam(HDC _pDC, HDC _pDCEtc, TRect _rect);
	void __fastcall 						funcGetGagamIndex(AnsiString _asMNUM);
	//231114//m_vSelectedGagamID 벡터에서 현재 선택된 가감대장 레이어.index가 있는 경우 표시를 위한 선택여부를 반환한다//
	//241127//NotUsed//bool __fastcall 						funcGetSelectedGagamIndex(int _nIndex);
	vector<DOCUMENT20_BASEPOINT_STRUCT> 	m_vGAGAMBASEPOINT;//가감대장 기준점//
	vector<DOCUMENT20_BASELIST_STRUCT>		m_vGAGAMBASELIST;//241210//가감대장 선택 기준점목록//TB_DOCUMENT20_BASELIST(KWON_NO, GAGAM_NO 일치)
	void __fastcall 						funcReadGagamBasePoint();
	void __fastcall 						func_DrawPaintImageBasePoint(HDC _pDC, HDC _pDCEtc, TRect _rect);
	vector<DOCUMENT20_LANDLIST_STRUCT>		m_vGAGAMLANDLISTALL;//가감대장 지번목록(전체)//
	void __fastcall 						func_DrawPaintImageGagamLandListAll(HDC _pDC, HDC _pDCEtc, TRect _rect);
	vector<DOCUMENT20_LANDLIST_STRUCT>		m_vGAGAMLANDLIST;//가감대장 지번목록(선택)//
	void __fastcall 						func_DrawPaintImageGagamLandList(HDC _pDC, HDC _pDCEtc, TRect _rect);
	//=============================================================================
	vector<DOCUMENT20_GAGAMLIST_STRUCT>		m_vGAGAMLIST;//가감대장 심볼용//
	int __fastcall 							funcGetIndexGagamList(AnsiString _landcd);
	//TB_DOCUMENT20_LANDLIST의 모든 데이터(m_vGAGAMLANDLIST)에서 원하는 지번 INDEX 찾기//
	int __fastcall 							funcGetIndexGagamLandListAll(AnsiString _landcd);
	//TB_DOCUMENT20_LANDLIST의 선택 가감대장 필지(m_vGAGAMLANDLIST)에서 원하는 지번 INDEX 찾기//
	int __fastcall 							funcGetIndexGagamLandList(AnsiString _landcd);
	//TB_DOCUMENT20_BASELIST의 모든 데이터(m_vGAGAMBASELIST)에서 원하는 지번 INDEX 찾기//
	int __fastcall 							funcGetIndexGagamBaseList(AnsiString _pointName);
	//=============================================================================
	vector<DOCUMENT20_YEAR_STRUCT>			m_vGAGAMYEAR;//가감대장 구축년도 목록//

	//241218//선택가감대장과 기준과의 거리 표시//#GAGAM_DISTANCE#//
	DEPTH_POINT m_tPOINT;
//=============================================================================



	TRect func_WorldToDevice(const MBR& _mbr);//화면좌표와 공간좌표와의 변환용
	TPoint func_WorldToDevice(const GPoint& _GPoint);
	int __fastcall func_ConfigIndexAlloc(int index, AnsiString layer, AnsiString layerparent);
	int __fastcall func_ConfigIndexAlloc(AnsiString layer, AnsiString layerparent);

	HDC         memDC1;
	HDC         pDraw1;
	HBITMAP     hMembitmap1;
	HBITMAP     hOldBitmap1;
	HBRUSH      hbr;

	HDC         memDC1Etc;
	HDC         pDraw1Etc;
	HBITMAP     hMembitmap1Etc;
	HBITMAP     hOldBitmap1Etc;

	HDC         memDC2;
	HDC         pDraw2;
	HBITMAP     hMembitmap2;
	HBITMAP     hOldBitmap2;

	HDC         memDC2Etc;
	HDC         pDraw2Etc;
	HBITMAP     hMembitmap2Etc;
	HBITMAP     hOldBitmap2Etc;

	int readinterval;
	int mShowLPCount;

	vector<int> m_vSelectedID;   // selected ID
	//210308//NOTUSED//vector<int> m_vSelectStationPoleID;
	//공간정보 이동용
	TPoint startPoint, endPoint, clickPoint;

	vector<int> m_vSelectedEMDID;   // selected EMD ID//M//191113
	vector<int> m_vSelectedRIID;   // selected RI ID//M//191113

	//면적재기, 거리재기용
	bool pbControl1DblClick;
	bool m_bControlFlags;
	TPoint m_ptStreetGaugeSP, m_ptStreetGaugeLP;
	GPoint m_pgStreetGaugeSP, m_pgStreetGaugeLP;

	TPoint m_ptAreaGaugeSP, m_ptAreaGaugeLP, m_ptCenter;
	GPoint m_pgAreaGaugeSP, m_pgAreaGaugeLP;
	GPoint func_DeviceToWorld(const TPoint& _point);
	MBR func_DeviceToWorld(const TRect& _rect);
	AnsiString __fastcall func_DrawAreaValue();
	AnsiString __fastcall func_DrawMemoRectAreaValue();//191129
	void       __fastcall func_DrawPolygonMemoRectCenter(int _nIndex);//이미 완료된 메모 Polygon의 중심점//
	void __fastcall funcPbControl1Draw();

	//메모영역설정//
	TPoint m_ptMemoRectSP, m_ptMemoRectLP, m_ptMemoRectCenter;
	GPoint m_pgMemoRectSP, m_pgMemoRectLP, m_pgMemoRectCenter/*영역중심점-하려했으나, 맨마지막포인트로 변경하라고 하심*/;
	GPoint m_pgPolygonMemoRectCenter;//200117//검색결과 메모 선택 시, X,Y값이 아닌 POLYGON의 중심좌표를 지적도 CENTER로 보여달라는 요청에 의해 추가//

	int __fastcall _2DEngineObject_pnsFunc_Track(GPoint point,TRect rect);
	enum      hit_status    {hitNone, hitPoint, hitCurve, hitPolygon};
	enum      object_status {stateNone, stateCreate, stateSelect, stateDragCurve, stateDraCGPoint};
	hit_status _2DEngineObject_pnsFunc_HitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);
	bool __fastcall _2DEngineObject_pnsFunc_PtInPolygon(vector<GPoint>& _vPoint, GPoint _GPoint);
	object_status	m_eStatus;
	typedef   vector<GPoint> POINT_LIST;

	//지도 출력을 위한 초기화
	void __fastcall func_InitialMapRelation();//지도 출력을 위한 초기화 작업
	void __fastcall func_daumKeySet(); //다음키에 의한 설정
	void __fastcall func_daumKeySet2(); //다음키에 의한 설정//200315

	HBITMAP __fastcall func_Load32bppTga(const char * pFileName, bool bPreMultiply);
	HBITMAP hDestBmp;
	MTGA_Header header;
	BYTE * pPixel;
	void * pBits;
	DWORD dwRead;
	int HSIZE;

	void __fastcall func_execHtmlDaum();//다음지도 연동
	bool			m_bROADVIEW;
	void __fastcall func_execHtmlDaumRoadView();//다음로드뷰 연동//

	GPoint _CoorP;
	//좌표변환용
	void __fastcall func_CalcCoorNS();
	double r_major;
	double r_minor;
	double scale_factor;
	double lon_center;
	double lat_origin;
	double false_northing;
	double false_easting;
	double e0;
	double e1;
	double e2;
	double e3;
	double e;
	double es;
	double esp;
	double ml0;
	double ind;

	double major_0;
	double minor_0;
	double major_1;
	double minor_1;

	double SF_1,SF_2,SF_3,SF_4,SF_5,SF_6;
	double LonCen_1,LonCen_2,LonCen_3,LonCen_4,LonCen_5,LonCen_6;
	double LatCen_1,LatCen_2,LatCen_3,LatCen_4,LatCen_5,LatCen_6;
	double FN_1,FN_2,FN_3,FN_4,FN_5,FN_6;
	double FE_1,FE_2,FE_3,FE_4,FE_5,FE_6;

	double __fastcall Cube(double x);
	double __fastcall Quad(double x);
	double __fastcall e0fn(double x);
	double __fastcall e1fn(double x);
	double __fastcall e2fn(double x);
	double __fastcall e3fn(double x);
	double __fastcall e4fn(double x);
	double __fastcall mlfn(double e0, double e1, double e2, double e3, double phi);
	double __fastcall acos1(double x);
	double __fastcall asin1(double x);
	double __fastcall asinz1(double con);
	void __fastcall d2dms(double *Lon, double *Lat, int *LonMin, double *LonSec, int *LatMin, double *LatSec);
	void __fastcall tmfor(double Lon, double Lat, double *x, double *y);
	void __fastcall DatumTrans(double input_a, double input_b, double input_Phi, double input_Lamda, double input_H, double output_a, double output_b, double *output_Phi, double *output_Lamda, double *output_H, float delta_X, float delta_Y, float delta_Z);
	void __fastcall tmint(double r_maj, double r_min, double scale_fact, double center_lon, double center_lat, double false_east, double false_north);
	void __fastcall tminv(double x, double y, double *Lon, double *Lat);
	void __fastcall conv(double lon_temp, double lat_temp, double h, int _gbn);


	//timer1 종료 후에 해야할 준비작업들//
	void __fastcall 	funcReadyFormShow();//191126


	//다음항공사진용
	AnsiString latitudeNS,longitudeNS;
	RETURNCOORDATA _coorData;

	//코드를 주소로 변환
	AnsiString __fastcall func_ConvertLandcdToAddress(AnsiString _landcd);
	AnsiString __fastcall func_ConvertEmdCDtoNM(AnsiString selectemdcd);
	AnsiString __fastcall func_ConvertRiCDtoNM(AnsiString selectricd);

	int __fastcall func_readEMDIndex(AnsiString _landcd);//M//191113
	int __fastcall func_readRIIndex(AnsiString _landcd);//M//191113

    int m_nReadJibunIndex;//현 shape에 존재하는 지번인덱스//
	int __fastcall func_readJibunIndex(AnsiString _landcd);
	int __fastcall func_readNaverJibunIndex(AnsiString _landcd);

	//마우스 휠 이벤트 처리용
	bool wheelevent;
	AnsiString _SELECTREALLANDCD;

	BOOL PROGRAM_START;
	int __fastcall func_widthRateCalc(int fsize);

	void __fastcall func_DeleteFileAll(AnsiString _path);
	void __fastcall	func_SelectFileDel(AnsiString _fname);

	void __fastcall func_readBaseOption();
	void __fastcall func_vectorClear();

	int __fastcall func_calcCharLength(AnsiString strline);

	AnsiString __fastcall func_readLandcd(AnsiString _qry);

	int __fastcall func_CenterTrack(GPoint point,TRect rect);

	void __fastcall func_readPropertyData(AnsiString _landcd);

	void __fastcall func_CalcCoorNS(double _lat, double _lon, int _gbn);

	bool m_bJibunDblLine;

	AnsiString __fastcall func_ConvertLandcdToFullAddress(AnsiString _landcd);

	AnsiString _CURRENT_PARAMETER;
	bool __fastcall func_IsWow64Process();

	//암호및 복호화
	int __fastcall func_base64_encode(char *text, int numBytes, char **encodedText);
	AnsiString __fastcall func_Encoder(AnsiString _data);
	int __fastcall func_base64_decode(char *text, unsigned char *dst, int numBytes );
	AnsiString __fastcall func_Decoder(AnsiString _data );


	void __fastcall funcInitSearchList();//검색시 초기화할 내용들//
	bool __fastcall funcCheckFindKeyword(TObject *Sender);
	bool __fastcall funcCheckFindMemo(TObject *Sender);//통합검색-메모//지번 여부 확인 전에 먼저 찾는다//
	void __fastcall func_JibunUnifiedSearch(AnsiString _text, AnsiString _landcd);

	AnsiString _CURRENT_WORKMODE;
	AnsiString _CURRENT_DOCWORKMODE;
	AnsiString _CURRENT_COMWORKMODE;
	AnsiString _CURRENT_CHGMODEWORK;


	vector<int> m_vSelectedSymbolID;   // selected Symbol ID
	int __fastcall func_readKindOfSymbolIndex(AnsiString _landcd);
	//210309//#LOADING_TEST//int  __fastcall func_readKindofSymbolCount(AnsiString _landcd);
	int  __fastcall func_readKindofSymbolCount(int _nIndex);
	bool __fastcall func_readKindofDocYN(AnsiString _landcd, int _nDocNo);
	//문서아이콘//
	//#m_vKINDOFSYMBOLDATA#//191123
	int								m_nSelectSymbolIndex;
	//#INDEXICON#//191123
	int							m_nSelectDocAllIndex;
	POISPATIAL_STRUCT 			tempDOCALLICON;
	vector<POISPATIAL_STRUCT> 	m_vDOCALLICON;

	//메모아이콘//
	int __fastcall 					funcGetMemoIndex(AnsiString _label);
	//포토아이콘//
	int __fastcall 					funcGetPhotoIndex(AnsiString _label);
	//메모 영역 아이콘 인덱스//
	int __fastcall 					funcGetPolyIndex(AnsiString _label);
	//#INDEXICON#
	int								m_nSelectDoc07Index;
	POISPATIAL_STRUCT 				tempDOC07INDEXICON;
	vector<POISPATIAL_STRUCT> 		m_vDOC07INDEXICON;

	int  __fastcall func_POISelectTrack(GPoint point,TRect rect);
	hit_status func_POIHitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);
	bool __fastcall func_PtInRect(const GPoint& _geoInputPoint, const GPoint& _geoRectCenter);
	bool __fastcall func_PtInRectMemo(const GPoint& _geoInputPoint, const GPoint& _geoRectCenter);
	bool __fastcall func_PtInPolygonMemo(vector<GPoint>& _vPoint, GPoint _GPoint);
	bool __fastcall func_PtInRectPhoto(const GPoint& _geoInputPoint, const GPoint& _geoRectCenter);
	bool __fastcall func_PtInRectDogn(const GPoint& _geoInputPoint, const GPoint& _geoRectCenter);//191204//도근점 이미지 안에 들어왔는지 확인//

	//#m_vKINDOFSYMBOLDATA#//문서 아이콘 클릭//
	int  __fastcall func_ICONSymbolSelectTrack(GPoint point,TRect rect);
	hit_status func_ICONSymbolHitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);

	//#INDEXICON#//폐쇄지적도 인덱스 아이콘 클릭//
	int  __fastcall func_ICON07SelectTrack(GPoint point,TRect rect);
	hit_status func_ICON07HitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);
	AnsiString __fastcall func_ConvertIndexCDtoNM(AnsiString selectcd);

	//#MEMOICON#//메모 아이콘 클릭//
	int					m_nSelectMemoIndex;
	AnsiString 			m_asTempMemoPoiKey;
	int  __fastcall 	func_ICONMemoSelectTrack(GPoint point,TRect rect);
	hit_status 			func_ICONMemoHitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);

	//#PHOTOICON#//포토 아이콘 클릭//
	int					m_nSelectPhotoIndex;
	int  __fastcall 	func_ICONPhotoSelectTrack(GPoint point,TRect rect);
	hit_status 			func_ICONPhotoHitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);

	//#DOGNICON#//도근점 아이콘 클릭//
	//선택된 도근점과 동일한 도근점이 뒤에 또 있으면 선택된 도근점 이미지가 가려진다//
	//선택된 도근점과 동일한 권번호의 index들을 저장해두었다가 나중에 그린다//
	vector<int> 		m_nSelectDognID;   // selected ID
	int					m_nSelectDognIndex;
	int  __fastcall 	func_ICONDognSelectTrack(GPoint point,TRect rect);
	hit_status 			func_ICONDognHitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);

//=============================================================================
//231031//GAGAMLAYER in LandArchive//
//=============================================================================
	int					m_nGagamShowLevel;//가감대장.HMF 표시 레벨(from DB Value)//
//NotUsed//	int			 		m_nSelectGagamID;//selected ID
//NotUsed//	vector<int> 		m_vSelectedGagamID;   // selected Gagam ID
	int					m_nSelectGagamIndex;
	int  __fastcall 	func_ICONGagamSelectTrack(GPoint point,TRect rect);
	hit_status 			func_ICONGagamHitTest(GPoint _gPoint, TRect _rctScreen, int& _ID, int& _PointID);


	int				m_nMemoSaveType;//DF_NEW_RECORD, DF_UPDATE_RECORD
	AnsiString 		m_asSelectLandMemo;//선택한 지번의 메모를 DB에서 가져와서 잠시 갖고 있는다//
	AnsiString 		m_asSelectLandCd;
	int 			m_nKindofSelectIndex;
	int 			m_nMemoLandkeySelectIndex;

	void __fastcall func_readMemoLandkeyData();
	int __fastcall func_readMemoLandkeyDataIndex(AnsiString _landcd);

	void __fastcall funcSettingPopupMenu();//M

	//****************************************************************
	//좌표계산부
	//****************************************************************
	int 						m_nDocument18SelectIndex;
	DOCUMENT18_STRUCT 			tempDOCUMENT18DATA;
	vector<DOCUMENT18_STRUCT> 	m_vDOCUMENT18DATA;

	//****************************************************************
	//검색창 관련//
	//****************************************************************
	SearchNode	mSearchNode;
	TTreeNode*  mSelectNodeFolder;//200604//
	TTreeNode*  mSelectNodeFile;//200604//

	bool		m_bSearching;//검색중//
	int 		m_nActiveDoc;     			////통합검색(0), 문서별 번호
	int			m_nViewDocNo;//현재 로드하려는 이미지 문서 번호
	int			m_nPOIViewDocNo;//지적도POI클릭문서번호. 검색 후 -1 처리할 것//241116//
	AnsiString 	m_asSearchPnu;
	AnsiString  m_asSearchText;//검색어//
	int 		totalCount[DF_DOC_CNT];

	//통합검색지번 기억//통검>상검(07)>상검(08)이동하면
	//m_asSearchPnu가 초기화되어 상검에서 토지소재를 변경하면 통검토지소재를 못 가져온다//
	AnsiString 	m_asSearchPnuDoc0;//210104//


	AnsiString	m_asCurrentFilePath;

	vector<DOCUMENT_VECTORINFO_STRUCT>		m_vRESULT;//검색결과의 여러지번정보가 하나의 VECTOR에 들어가게 되므로 각각을 기억하기 위함.

	vector<BASENAME_STRUCT> 		m_vDATA_BASECODE;
	vector<BASENAME_STRUCT> 		m_BASECODE_101_DOC1;
	vector<BASENAME_STRUCT> 		m_BASECODE_001_DOC1;
	vector<BASENAME_STRUCT> 		m_BASECODE_002_DOC2;
	vector<BASENAME_STRUCT> 		m_BASECODE_102_DOC2;

	vector<BASENAME_STRUCT> 		m_BASECODE_003_DOC3;
	vector<BASENAME_STRUCT> 		m_BASECODE_004_DOC4;
	vector<BASENAME_STRUCT> 		m_BASECODE_109_DOC5;
	vector<BASENAME_STRUCT> 		m_BASECODE_006_DOC6;
	vector<BASENAME_STRUCT> 		m_BASECODE_007_DOC7;
	vector<BASENAME_STRUCT> 		m_BASECODE_008_DOC8;
	vector<BASENAME_STRUCT> 		m_BASECODE_108_DOC8;
	vector<BASENAME_STRUCT> 		m_BASECODE_009_DOC9;
	vector<BASENAME_STRUCT> 		m_BASECODE_011_DOC11;
	vector<BASENAME_STRUCT> 		m_BASECODE_012_DOC12;
	vector<BASENAME_STRUCT> 		m_BASECODE_042_DOC13;//TASK_CODE:004 && KIND_CODE:042
	vector<BASENAME_STRUCT> 		m_BASECODE_111_DOC14;
	vector<BASENAME_STRUCT> 		m_BASECODE_015_DOC15;
	vector<BASENAME_STRUCT> 		m_BASECODE_017_DOC17;
	vector<BASENAME_STRUCT> 		m_BASECODE_018_DOC18;
	vector<BASENAME_STRUCT> 		m_BASECODE_020_DOC20;//231020//GAGAMLAYER//
	vector<SIDONAME_STRUCT> 		m_vPNU_SIDOCODE;//메인검색에 해당되는 읍면동, 리 명 정보 데이터//
	vector<ZONENAME_STRUCT> 		m_vDATA_ZONECODE;//환지계획서 ZONE_CODE
	vector<ZONENAME_STRUCT> 		m_vDOC6_ZONECODE;//환지계획서 상세검색 시 지구명 like 검색에 필요.
	vector<BASENAME_STRUCT> 		m_vDATA_BASECODE_SCALERESULT;
	vector<BASENAME_STRUCT> 		m_vDATA_BASECODE_503;//210303//#503//사용자별 행위구분//

	vector<BASENAME_STRUCT> 		m_BASECODE_801_DOC8;//연대코드//

	//SQL =====================================================
	vector<DOCUMENT01_STRUCT> 		m_ResultDocument01;
	vector<DOCUMENT02_STRUCT> 		m_ResultDocument02;
	vector<DOCUMENT03_STRUCT> 		m_ResultDocument03;
	vector<DOCUMENT04_STRUCT> 		m_ResultDocument04;
	vector<DOCUMENT05_STRUCT> 		m_ResultDocument05;
	vector<DOCUMENT06_STRUCT> 		m_ResultDocument06;
	vector<DOCUMENT07_STRUCT> 		m_ResultDocument07;
	vector<DOCUMENT07_STRUCT> 		m_ResultDocument07_SUB;//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	vector<DOCUMENT07_STRUCT> 		m_ResultDocument07Doho;
	vector<DOCUMENT08_STRUCT> 		m_ResultDocument08;
	vector<DOCUMENT09_STRUCT> 		m_ResultDocument09;

	vector<DOCUMENT11_STRUCT> 		m_ResultDocument11;
	vector<DOCUMENT12_STRUCT> 		m_ResultDocument12;
	vector<DOCUMENT13_STRUCT> 		m_ResultDocument13;
	vector<DOCUMENT14_STRUCT> 		m_ResultDocument14;
	vector<DOCUMENT15_STRUCT> 		m_ResultDocument15;
	vector<DOCUMENT16_STRUCT> 		m_ResultDocument16;
	vector<DOCUMENT17_STRUCT> 		m_ResultDocument17; 			//토지조서

	vector<MEMOINFO_STRUCT>			m_ResultMemo;//메모 검색//

	DOCUMENT01_STRUCT				mSelGroupDoc1;
	DOCUMENT05_STRUCT				mSelGroupDoc5;
	DOCUMENT06_STRUCT				mSelGroupDoc6;
	DOCUMENT07_STRUCT				mSelDohoDoc7;
	DOCUMENT14_STRUCT				mSelGroupDoc14;
	DOCUMENT15_STRUCT				mSelGroupDoc15;

	int								m_nNodeIndexInDoc;//Doc안에서의 Index//

	//=======================================================================
	vector<SEJONG_PNU_STRUCT> 		mvResultSejongPnu;

	//===========================================================================
	// 폐쇄지적도 아이콘 표시//
	//===========================================================================
	//TB_DOCUMENT07의 기본 데이터를 인덱스 좌표 의뢰 없이 내가 만든다//1회성//이 함수는 호출하는 부분이 막혀 있어야 한다.
	void __fastcall 	funcSQLInsertDoc07(int _nScaleType, int _nIndex);//1회성//
	DOCUMENT07_INDEX_STRUCT			tempDocument07index;//지적도 도호정보
	vector<DOCUMENT07_INDEX_STRUCT> m_ResultDocument07Index;//지적도 도호정보
	TList 				*lblDoc07IndexList;
	int                 m_nDoc07IndexList;
    void __fastcall     funcSQLUpdateXYDoc07Index(AnsiString _label, double _X, double _Y);
	int  __fastcall 	funcGetDoc07Index(AnsiString _label);
	void __fastcall 	func_DrawPaintImageDoc07IndexLabel(HDC _pDC, HDC _pDCEtc, TRect _rect);

	//===========================================================================
	// 좌표계산부 아이콘 표시//
	//===========================================================================
	//DOCUMENT18_STRUCT               tempDocument18;
	vector<DOCUMENT18_STRUCT> 		m_ResultDocument18All;
	vector<DOCUMENT18_STRUCT> 		m_ResultDocument18;
	void __fastcall 	func_DrawPaintImageDoc18Label(HDC _pDC, HDC _pDCEtc, TRect _rect);

	//===========================================================================
	// 메모 아이콘 표시//
	//===========================================================================
	void __fastcall 	func_DrawPaintImageMemo(HDC _pDC, HDC _pDCEtc, TRect _rect);

	//===========================================================================
	// 포토 아이콘 표시//
	//===========================================================================
	void __fastcall 	func_DrawPaintImagePhoto(HDC _pDC, HDC _pDCEtc, TRect _rect);

	//===========================================================================
	// 영역 표시//
	//===========================================================================
	void __fastcall 	func_DrawPaintImagePoly(HDC _pDC, HDC _pDCEtc, TRect _rect);

	//****************************************************************
	//이미지 관련//
	//****************************************************************
	Graphics::TBitmap *BITMAP_BTN_TABDOC[DF_DOC_CNT][2];
	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	//======================================================================
	//241015//#전주#중앙정보테크//
	//======================================================================
	void __fastcall funcSettingTheOtherSgg();
	void __fastcall func_GetBGResource();


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
	AnsiString 			m_asLoadImageFileName;
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
	void __fastcall 	func_DrawImage();
	void __fastcall 	funcRefreshView();

	//Graphics::TBitmap  	*bmpLoad;
	//TJPEGImage  			*jpgLoad;
	//Graphics::TBitmap  	*saveBitmap;

	bool				m_bWheelZoom;//휠로 확대/축소
	//200814//double 				dDocZoomRate[30];
	//200814//int					m_nDocZoomFactor;
	TPoint  			pWheelMousePos;
	GetImageInfo		mGetImageInfo;
	//영역지우기 후 m_DIB 변경 시 사용//

	bool                m_bCloseProcess;//종료관련//

	//################################################################

	//NOTUSED//double				m_dZoomRate;
	void __fastcall 	funcSetWaitWindows(bool bSetValue);
	void __fastcall 	funcSetWaitWindowsForm(bool bSetValue);
	bool __fastcall		funcGetImage(AnsiString _asPath, int _nDocNum, int _nDirType);
	void __fastcall 	funcReadFileList(AnsiString _asPath);
	void __fastcall 	funcFreeImage();
	void __fastcall 	funcImageViewClear();
	void __fastcall 	funcLoadImage(AnsiString _asFilename);
	void __fastcall 	funcFreeImageGetMetaValue();//250514//FreeImage_GetMetadata//
	void __fastcall 	funcFullView();
	//201217//이미지 확대 범위가 조금 작았으면 좋겠다//
	//44230Req//지적원도 1단계에서 2단계 갈때 너무 훅 커진다//
	//그래서 알씨 줌 크기를 반영//10%,20%,30%,50%,70%,100%,150%,200%,300%,500%,700%,1000%,2000%,3000%,5000%
	//우리는 제한이 없으니까 1000% 이후로는 500%씩 커지게 하자//
	double __fastcall 	funcGetImageScale(bool _bZoomIn);
	//0719//void __fastcall     funcRefreshView();
	//0719//void __fastcall 	funcZoomInView();
	//0719//void __fastcall 	funcZoomOutView();
	void __fastcall 	funcRotateView();
	void __fastcall 	funcInitRectView();

	//##############################################################
	double __fastcall   funcSetImageBaseScale();

	//문서 툴바 기능들//
	AnsiString 			m_asPrinterName;//프로그램 종료시까지 선택한 프린터이름 갖고 있기//
	AnsiString 			m_asSaveFileDir;//프로그램 종료시까지 선택한 파일저장 폴더 갖고 있기//
	void __fastcall 	funcSaveFile();
	bool __fastcall 	funcDrawWaterMark(FREE_IMAGE_FORMAT _fiformat, AnsiString _asDstFile);
	void __fastcall 	funcSaveFileTif(AnsiString _asTmpFile, AnsiString _asDstFile);
	void __fastcall 	funcSaveFileJpg(AnsiString _asDstFile);

	//문서 paintbox 기능들 - 영역선택, 면적측정, 거리재기
	int					mToolButtonState;
	int				    mToolButtonStateBck;
	MouseState 			mMouseState;
	MouseState 			mMouseStateLayer1;//#OWNNAMES#
	MouseState 			mMouseStateLayer3;//#DOGWAK#
	MouseState 			mMouseStateLayer4;//#SPCERECT#

	//영역선택을 위한//
	RactState   		mRactState;
//	RactState   		mRactStateLayer1;//#OWNNAMES#
//	RactState  			mRactStateLayer3;//#DOGWAK#
//	RactState   		mRactStateLayer4;//#SPCERECT#

	bool 		   		bPrintDrag;

	TPaintBox 			*tcmpPaintBox[cnLayerCount+1];
	int __fastcall 		funcActDeactPaintBox(int _nIndex, bool _bState);


	// To DO 면적재기
	BLENDFUNCTION 			flagbf;//투명
	BLENDFUNCTION 			roadbf;//투명//210428//#ROADVIEW

	//###########################################################################
	//---------------------------------------------------------------------------
	// 거리재기/면적측정//
	//---------------------------------------------------------------------------
	bool pbControl2DblClick;
	//m_bControlFlags 사용//bool m_bControl2Flags;
	TPoint m_ptStreetGauge2SP, m_ptStreetGauge2LP;

	TPoint m_ptAreaGauge2SP, m_ptAreaGauge2LP, m_ptCenter2;
	AnsiString __fastcall 		func_DrawAreaValue2();
	void __fastcall 			funcPbControl2Draw();

	vector<REALAREA_STRUCT> 	m_vREALAREA2;
	vector<AREA_STRUCT> 		m_vAREA2;
	bool						m_bIngArea;

	vector<DIST_STRUCT> 		m_vDIST2;
	vector<REALDIST_STRUCT> 	m_vREALDIST2;
	bool						m_bIngDist;

	RECT_STRUCT 				tempRECT;
	vector<RECT_STRUCT> 		m_vRECT;
	RECT_STRUCT 				tempREALRECT;
	vector<RECT_STRUCT> 		m_vREALRECT;
	bool						m_bIngRect;
	//MouseState 					mMouseStateRect;//#RECTSEL#
	//RactState   				mRactStateRect;//#RECTSEL#

	//---------------------------------------------------------------------------
	void __fastcall 			funcInitPBControl2();
	void __fastcall 			funcInitControlRect();
	void __fastcall 			funcInitControlArea();
	void __fastcall 			funcInitControlDist();
	//---------------------------------------------------------------------------
	//###########################################################################

	//area/realarea
	TList *imgRECTClearList;
	TList *imgRECTCancelList;
	int   nRECTIconCount;
	int   nMoveStatus;

	RECT_STRUCT 			tempSPACE;
	vector<RECT_STRUCT> 	m_vSPACE;


	void __fastcall 		funcDeleteRectangle();
	void __fastcall 		funcDeleteAreaGauge();
	void __fastcall 		funcDeleteStreetGauge();

	void __fastcall 		funcCreateRectIcon(TPoint _tpIconPoint, int WIDTH);
	void __fastcall 		funcDeleteRectIcon();
	void __fastcall 		funcMoveRectIcon(int _nIndex, TPoint _tpIconPoint, int WIDTH);
	void __fastcall 		TfrmMain::imgClear_OnClick(TObject *Sender);
	void __fastcall 		TfrmMain::imgCancel_OnClick(TObject *Sender);


	void __fastcall 		func_SelectRectangle();
	void __fastcall 		func_GaugeArea();//면적측정
	void __fastcall 		func_GaugeStreet();//거리측정

	void __fastcall 		func_GaugeAreaCancel();//면적측정 취소
	void __fastcall 		func_GaugeStreetCancel();//거리측정 취소
	void __fastcall 		func_SelectRectangleOneCancel(int _nTag);//영역선택 취소
	void __fastcall 		func_SelectRectangleOneClear(int _nTag); //영역지우기
	void __fastcall 		func_SelectRectangleCancel();//영역선택 취소
	void __fastcall 		func_SelectRectangleClear(); //영역지우기
	void __fastcall 		funcControlRect();
	void __fastcall 		funcControlArea();
	void __fastcall 		funcControlDist();


//	//공간검색  =====================================================
	bool 					mSpaceRectFlags;
	void __fastcall 		funcDrawRectangleLayer4();
	GPoint 					m_pgSpaceRectSP, m_pgSpaceRectEP;
	vector<LAND_INFO_STRUCT> 	m_vSPACELANDINFO;




	//***************************************************************************
	// 시도코드//
	//***************************************************************************
	vector<SIDONAME_STRUCT> m_vDATA_SIDOCODE;
	int __fastcall func_readSidoCode();

	//통합검색어 입력 시, 공백없이 혹은 읍면동리를 제대로 입력안했을때에도 검색어를 찾기 위한 비교//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_CMP1;//읍,면,동,리 명칭 그대로//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_CMP2;//읍,면, 동,리 명칭 제거// 염치읍->염치, 대호지면->대호지//
	//200910//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_DATA1;//읍면동,리 명칭 그대로//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_DATA2;//읍면동,리 명칭 제거// 염치읍->염치, 온천동->온천//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_DATA3;//읍면동 명칭 제거//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_DATA4;//리 명칭 제거// 온천동->온천, 홍산리->홍산//
	vector<SIDONAME_STRUCT> m_vSIDOCODE_DATA5;//읍면동 없고, 리 명칭에서 '리'명칭 제거// 온천동->온천, 홍산리->홍산//

	vector<SIDONAME_STRUCT> m_vSIDOCODE_PNULIST;
	vector<SIDONAME_STRUCT> m_vSIDOCODE_PNUHIST;
	vector<SIDONAME_STRUCT>	m_vPnuList;//검색어에 해당하는 지번목록//최대 10개//

	//===========================================================================

	//***************************************************************************
	// GUI 관련 고정값 설정//
	//***************************************************************************
	int		EDGEGAP;//12
    int		THUMBNAILSIZE;//120

	//***************************************************************************
	// 같은 KWON_NO 파일을 FTP에서 가져오기 위함//
	//***************************************************************************
	vector<DOCUMENT01_STRUCT> 		m_SelectPnuDoc01;
	vector<DOCUMENT07_STRUCT> 		m_SelectPnuDoc07;



	//***************************************************************************
	// 팝업//
	//***************************************************************************
	int m_nPopupL;
	int m_nPopupT;

	//***************************************************************************
	// 검색 문서 바로가기 Panel
	//***************************************************************************
	TList 		*pnlMainList;
	TList 		*imgDocMainList;
	TList 		*lblDocMainList;
	TList 		*pnlSubList;
	TList 		*imgDocSubList;
	TList 		*lblDocSubList;
	int			m_nDocMainIndex;//pnlDocKindMain->FocusedIndex
	int			m_nMainCount;
	int			m_nSubCount;
	void __fastcall funcCreateListMain();
	void __fastcall funcCreateListSub();
	void __fastcall funcDeleteComponentsMain();
	void __fastcall funcDeleteComponentsSub();
	void __fastcall funcMakeCreateMain(int _nCnt);
	void __fastcall funcMakeCreateSub(int _nCnt);
	void __fastcall TfrmMain::imgDocMainDCMouseEnter(TObject *Sender);
	void __fastcall TfrmMain::imgDocMainDCMouseLeave(TObject *Sender);
	void __fastcall TfrmMain::imgDocSubDCMouseEnter(TObject *Sender);
	void __fastcall TfrmMain::imgDocSubDCMouseLeave(TObject *Sender);

	//***************************************************************************
	//
	// 검색결과 문서와 같은 DOC_KIND 문서가 있는 경우,
	// 해당 문서의 THUMBNAIL을 보여주는 기능 -  동적 생성
	//
	//***************************************************************************
	vector<DOCUMENT_PATHLIST_STRUCT> 		m_vFTPPathList;
	int										m_nFTPPathIndex;

	vector<THUMBNAIL_DOCKIND_STRUCT> 		m_vThumbDocKind;//미리보기 필터링//
	vector<DOCUMENT_PATHLIST_STRUCT> 		m_vThumbPathList;
	int										m_nThumbPathIndex;//검색된 이미지 index
	int										m_nThumbCurrIndex;//현재 포커스된 index
	void __fastcall 						funcInitPrevNext();
	void __fastcall 						funcSetPrevNextBar();

	//동적생성 관련//
	TList 		*pnlThumbList;
	TList 		*imgThumbList;
	TList 		*lblThumbList;
	TList 		*chkThumbList;//201126//
	int			m_nThumbListIndex;//
	int			m_nThumbCount;//Thumbnail 개수//
	int			m_nThumbHeight;//Thumbnail 높이//가로이미지, 세로이미지 높이가 달라서//
	int			m_nPerThumbCnt;//
	int			m_nThumbSttIdx;//FTP에서 다운로드 받을 시작인덱스//
	int			m_nThumbDownCnt;//FTP에서 다운로드 받을 개수//
	int			m_nThumbDownloadedCnt;//FTP에서 다운로드 받은 파일 개수//201014//
	int 		m_nPageCount;
	int 		m_nCurrPage;
	int 		m_nTotalTab;
	int 		m_nCurrTab;

	bool		m_bThumbChecked;//201126//
	int			m_nDownloadCnt;//201201//그룹저장 시 다운로드체크한 파일 수//

	void 		__fastcall funcCreateListThumb();
	void 		__fastcall funcDeleteComponentsThumb();
	void 		__fastcall funcMakeDynamicThumbnail(int _nIndex);
	void 		__fastcall funcShowCurrentThumbLabel();
	AnsiString 	__fastcall funcLoadImageThumb(AnsiString _asFilename);
	void 		__fastcall TfrmMain::chkThumbDC_onMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);//201130//
	void 		__fastcall TfrmMain::imgThumbDC_onClick(TObject *Sender);
	void 		__fastcall funcInitThumb();
	void 		__fastcall funcSetLabelPage();
	void 		__fastcall funcProcessThumb();
	void 		__fastcall funcRefreshThumb();//201021//동일그룹의 다른 노드 이미지 선택 시 썸네일 페이지도 이동하기 위함//
	void        __fastcall funcGotoPageThumb();

	bool    				m_bGroupSave;//201126//그룹인쇄//
	void 		__fastcall  funcFastReportOpen(char *_cParameters, int _nType);//201126//그룹인쇄//
	TStringList 			*m_sPrinterList;//201128//moved to here//
	TPrinter 				*m_pPrinter;
	void 		__fastcall 	funcWritePrintData();
    void 		__fastcall  funcGetPrinterList();

	//***************************************************************************
	// 환경설정//
	//***************************************************************************
	bool	m_bSettingBtn;

	//
	//***************************************************************************
	// 환경설정 > 자동로그아웃//#LogoutTimer
	//***************************************************************************
	int 					m_nLogoutTimeCount;
	int 					m_nMaxLogoutTimeCount;
	int 					m_LastLogoutCount;//종료 15초전 알림//
	virtual void __fastcall WndProc(TMessage &Message);
	void __fastcall 		AppDeactivate(TObject *Sender);
	void __fastcall 		funcExecLogin();//LogoutTime 종료 후 login.exe 실행//
	AnsiString 				m_sCurrentActiveMode;
	TPoint 					m_pDiffPoint, m_pStartPoint, m_pCheckPoint;


	//***************************************************************************
	// 검색결과//
	//***************************************************************************
	SEARCHEDJIBUN tempSEARCHEDJibun;
	vector<SEARCHEDJIBUN> m_v_SEARCHEDJIBUN;


	//***************************************************************************
	// Thumbnail 이미지의 DB 정보//
	//***************************************************************************
	void __fastcall 	funcReadDocDBInfo(int _nDocNo, AnsiString _asKwonNo, AnsiString _asFilePath);
	void __fastcall 	funcReadDoc01DBInfo(AnsiString _asKwonNo, AnsiString _asFilePath);
	void __fastcall 	funcReadDoc07DBInfo(AnsiString _asKwonNo, AnsiString _asFilePath);




	//---------------------------------------------------------------------------
	// 기존 MAPPOINT와 다른 구조의 DOCUMENT07_FIL_INFO 혼합형태//
	//---------------------------------------------------------------------------
	//191116
	vector<DOCUMENT07_STRUCT> 	m_vDOCUMENT07FILEINFO;

	//---------------------------------------------------------------------------
	//
	// MAPPOINT
	//
	//---------------------------------------------------------------------------
	int 	m_nAngleCount;
	TPoint  tpScreenBasePoint;//Screen XY (Base Dogak)

	bool	m_bOtherJibun;//지적도의 경우, 근처 지번을 검색했는지 여부
	MAPPOINT_STRUCT 			currMapPoint;
	vector<LAND_INFO_STRUCT> 	m_vLANDINFO;
	void __fastcall funcCalcWorldToMap(bool _bSub);//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	//201227//void __fastcall funcCalcWorldToMap2(bool _bFromThumb);//201014//
	void __fastcall funcRedrawMapPoint();
	void __fastcall funcRotateMapPoint();

	int								m_nDoc07PnuIndex;//201014//
	vector<DOCUMENT07_PNU_STRUCT> 	m_vDOC07PNU;//201009//

	//201227//_bSub:열람 이미지 내의 다른 지번 검색 시 사용//
	vector<LAND_INFO_STRUCT> 	m_vLANDINFO_SUB;


	//---------------------------------------------------------------------------
	//
	// 공통 함수들//
	//
	//---------------------------------------------------------------------------
	//
	int  __fastcall funcGetJibunPos(AnsiString str);
	bool __fastcall funcCheckAddressData(AnsiString str);//지번검색란에 한글, 숫자, - 외에 입력 안 받음//

	//---------------------------------------------------------------------------
	// 음영조정
	//---------------------------------------------------------------------------
	bool	m_bAdjustFromEdit;
	int		m_nAdjustMiddle;//음영조정단계 중간값//10
	int 	m_nAdjustValue1;
	int 	m_nAdjustValue2;
	int 	m_nAdjustValue3;
	bool	m_bAdjustIng1;//Brightness
	bool	m_bAdjustIng2;//Contrast
	bool	m_bAdjustIng3;//Gamma
	bool	m_bAdjustReject;//음영조정 내의 다른 기능을 선택하면 적용할지 여부 묻고 다른 기능의 적용에 들어갈때 TrackBar의 포지션을 기본값으로 설정한다//
//	int		m_nBaseValue1;//이전에 설정했던 값을 기준으로 한다. 5->8, 다음번 들어갈때, 8을 기준으로 해야 한다//
//	int		m_nBaseValue2;//이전에 설정했던 값을 기준으로 한다. 5->8, 다음번 들어갈때, 8을 기준으로 해야 한다//
//	int		m_nBaseValue3;//이전에 설정했던 값을 기준으로 한다. 5->8, 다음번 들어갈때, 8을 기준으로 해야 한다//
	TPoint 	m_pAdjustSPoint, m_pAdjustMPoint, m_pAdjustEPoint, m_pAdjustDPoint;
	void __fastcall funcProcessAdjustBar(int _nTag);
	int  __fastcall funcBrightnessImage(int _nValue);
	int  __fastcall funcContrastImage(int _nValue);
	int  __fastcall funcGammaImage(double _dValue);


	//191114_LAYER_DOGWAK
	void __fastcall funcSetColorCheckIndex();
//	void __fastcall funcSetCheckIndexLayer(bool _bVisible);
	void __fastcall funcSQLUpdateSpatialConfig(AnsiString _asLayerName, int _nShowUse);


	void __fastcall funcSetLabelMapPoint(bool _bVisible);

	void __fastcall funcSetModeLayer(bool _bLayer);
	//BITMAP_BTN_TABPREV
//231118//NotUsed//	int				m_nTABINDEX;
	int				m_nTABCOUNT;
	void __fastcall funcSetTabButtons();
	void __fastcall funcInitDetailCommon(bool _bVisible);
	void __fastcall funcInitIMGTAB01();
	void __fastcall funcInitIMGTAB02();
	void __fastcall funcInitIMGTAB03();
	void __fastcall funcInitIMGTAB04();
	void __fastcall funcInitIMGTAB05();
	void __fastcall funcInitIMGTAB06();
	void __fastcall funcInitIMGTAB07();
	void __fastcall funcInitIMGTAB08();
	void __fastcall funcInitIMGTAB09();
	void __fastcall funcInitIMGTAB11();
	void __fastcall funcInitIMGTAB12();
	void __fastcall funcInitIMGTAB13();
	void __fastcall funcInitIMGTAB14();
	void __fastcall funcInitIMGTAB15();
	void __fastcall funcInitIMGTAB17();
	void __fastcall funcInitIMGTAB18();
	void __fastcall funcInitIMGTAB20();//231020//GAGAMLAYER in LandArchive

	//===========================================================================
	// 문서별 상세검색 예외처리// 상세검색 읍면동코드 혹은 지번 입력의 공통 기능//
	//===========================================================================
	void __fastcall funcDetailCommonKeyPress();//210104//


	bool	m_bCondition;

	//===========================================================================
	// 도근점 paintbox //NotUsed//
	//===========================================================================
	void __fastcall funcDrawPbDogeun();


	//좌표계산부 상세검색//
	bool		bDotFlag;

	void 	__fastcall funcSetZoomBarPos(bool _bDocView);

	bool	m_bChkIndexAll;//인덱스 전체 선택 여부//

	bool	m_bDognIconClicked;//기준점클릭(true)과 문서뷰에서 항공뷰로 이동시 해당 기준점으로 이동하는 것(false)과 구별하기 위함//



	//===========================================================================
	// about TreeSystem
	//===========================================================================
	void __fastcall funcInitAdjustBar();
	//===========================================================================



	//===========================================================================
	// PoiPopup관련//
	//===========================================================================
	void __fastcall TfrmMain::funcSetPoiIntoPopup(int _nIndex, int _X, int _Y);


	bool	m_bIngIMGDOCCONTROL;//문서툴바 내에서 포커스 옮겨갈때, enter > leave들어와서 해제되기 때문에//


	//===========================================================================
	// ArchiveLMFS에서 넘겨받은 검색 지번, PNU를 처리//
	//===========================================================================
	void __fastcall WMCopyData(TWMCopyData &Msg);
	//===========================================================================
	// Form 이동관련//
	//===========================================================================
	//form caption moving
	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_MOVING, TMessage, WMMOVING)
		MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, WMCopyData)
	END_MESSAGE_MAP(TForm)

	void __fastcall WMMOVING(TMessage & msg);
	void __fastcall funcMovingForm();

	//===========================================================================
	// Alpha관련//
	//===========================================================================
	bool				m_bAlphaBlend;
	void __fastcall 	func_Trans();



	AnsiString  m_asDocDBPathName;//Doc2, Doc7

	//===========================================================================
	// 토지대장_주민번호삭제 영역정보 갖고 있는지 확인//#JUMINHIDE#
	//===========================================================================
	JuminRectState 				mRactStateLayer1_8Data[16];
	RactState   				mRactStateLayer1_8[7];//구대장_주민번호_영역선택
	bool						m_bJuminRactCalcFlag;//구대장_주민번호_영역선택된 것이 있는지//일반 영역선택과 주민번호 영역선택과 구별하기 위함//
	int							mPbRect1_8_Moved_Width;//구대장_영역선택_움직인 Width
	int							mPbRect1_8_Moved_Height;//구대장_영역선택_움직인 Height
	DOC8_RECT_STRUCT 			mDoc8Rect;
	double						m_dStartRateX;
	double						m_dStartRateY;
	void 		__fastcall  	funcDrawRectangleLayer1_8();
	void 		__fastcall 		funcSet_mRactStateLayer1_8Redraw();
	void 		__fastcall 		funcSet_mRactStateLayer1_8DB(AnsiString _asJuminXY);
	AnsiString 	__fastcall 		funcSetDoc8JuminXY();
	void 		__fastcall 		funcCreateMoverIcon(int X, int Y);
	void 		__fastcall  	TfrmMain::imgMover_OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void 		__fastcall  	TfrmMain::imgMover_OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void 		__fastcall  	TfrmMain::imgMover_OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void 		__fastcall 		funcInitJuminHide();

	bool						m_bDoc8Color;
	//---------------------------------------------------------------------------
	int							m_nPathListSeqNo;//TB_OLDLANDDOC_PATHLIST.SEQNO
	AnsiString					m_asDBDocPathName;
	AnsiString					m_asLandCd;
	AnsiString					m_asLandNm;
	AnsiString					m_asOldLandCd;//210630//
	AnsiString					m_asFormatType;//231118//#SHAREOWN#//부책은 관계없으나, 공유지연명부는 A, B 포맷이 존재하므로 DB값 저장하여 사용//
	//---------------------------------------------------------------------------



	//===========================================================================
	//지적도-도곽선 표시//#DOGWAK#
	//===========================================================================
	int		m_nMovedW;
	int		m_nMovedH;
	int 	m_nDogakCount;//5
	bool 	mDogakLineFlags;
	DOCUMENT07_STRUCT 		 	m_vDOC07TEMP;//도곽좌표 그리기 위해 현재 선택된 node의 값을 복사해서 갖고 있게 함.
	vector<DOGAKLINE_STRUCT> 	m_vDOGAKLINE;
	void __fastcall func_DogakLine();
	void __fastcall funcDogakLinePaint();
	void __fastcall funcMakeDogakLine();
	void __fastcall funcRotateDogakLine();
	void __fastcall funcDeleteDogakLine();




	//===========================================================================
	void __fastcall     funcSetDocControlBar();

	//===========================================================================
	void __fastcall 	func_DrawPaintIMGSPREAD();//IMGSPREAD

	//===========================================================================
	void __fastcall 	funcClosePanel();//각종 sub panel close

	//===========================================================================
	void __fastcall 	funcOpenFile(AnsiString _asFileName);//도움말 파일 열기//

	//===========================================================================
	int		m_nPreviewWidth;


	//==========================================================================
	// 검색어 리스트 및 검색지번 히스토리 //
	//==========================================================================
	//210308//#ADDRESS_DUP//vector<PNU_STRUCT>		m_vSearchPnuList;//검색어에 해당하는 지번목록//최대 5개//
	//210308//#ADDRESS_DUP//vector<PNU_STRUCT>		m_vSearchPnuHist;//검색했던 지번//최대 5개//
	vector<SEARCHEDJIBUN>	m_vSearchPnuList;//검색했던 지번//최대 5개////210308//#ADDRESS_DUP//
	vector<SEARCHEDJIBUN>	m_vSearchPnuHist;//검색했던 지번//최대 5개////210308//#ADDRESS_DUP//

	bool					m_bPnuHistON;//검색지번기록 표시/미표시//
	bool					m_bStopSearch;//검색된 읍면동+리 목록에서 선택해서 edtMainSearchText에 표시할때 또 검색 못하게 막기 위함//
	void 		__fastcall  funcInitPnuList();
	void 		__fastcall  funcInitPnuHist();
	void 		__fastcall  funcDispPnuList();
	void 		__fastcall  funcDispPnuHist();
	void 		__fastcall  funcSetPnlPnuList(bool _bVisible);
	void 		__fastcall  funcSelectSGPnuList(int _nIndex);




	//==========================================================================
	// component 초기화 관련 //
	//==========================================================================
	void 		__fastcall 	funcSetMainViewBar();
	//241205//DOCUMENT VIEW//
	void 		__fastcall 	funcSetDocumentView(bool _bDocControl, /*bool _bDoc08, */bool _bPrevNext, bool _bLogo);
//	void 		__fastcall  funcInitPBRect();
	bool					m_bVisiblePrevNextBar;
	void 		__fastcall  funcInitPrevNextBar(bool _bVisible);
	bool					m_bVisibleDoc08Bar;
	void 		__fastcall  funcInitDoc08Bar(bool _bVisible);//minji@230308//#DOC08_INFO_ICON
	void 		__fastcall  funcInitDocControlBar(bool _bVisible);
	void 		__fastcall 	funcInitLogo(bool _bVisible);
	//241205//우측 상단 [문서]-[지적도] 이미지 표시 설정//(문서:True, 지적도:False)
	void 		__fastcall 	funcSetImageModeChange(bool _bDoc);
	//241205//[레이어] 이미지 표시 설정//
	void 		__fastcall 	funcSetImageLayer(TObject *Sender, bool _bVisible, bool _bSet);
	void 		__fastcall  funcSetPreview(bool _bVisible);

	void 		__fastcall  funcInitSpatialControlBar();
	//231212//[지적도] 클릭했을 때 표시되는 아이콘 정리//
	void 		__fastcall  funcInitSpatialBar(bool _bVisible);
	//#ICONPOI#상단//
	void 		__fastcall  funcSetPalPoi();
	//지적도에 검색지번 없을 때 검색결과 있으면 문서 바로 표시한다//
	void 		__fastcall  funcOpenDocumentTresystem(int _nIndex);


	//===========================================================================
	//종료 시 외부프로그램 종료하기//
	void __fastcall funcCloseExternalProgram();


	//JGW =====================================================
	LONG 				biXPelsPerMeterJGW;
	LONG 				biYPelsPerMeterJGW;
	bool				bJGWExists;//Doc02 file has a JGW
	AnsiString  		asTmpFileNameJGW;
	void __fastcall		funcReadInfoFileJGW(int _nScale, AnsiString _asFileName);


	//===========================================================================
	//속성정보에 표시하는 부가 기능 초기화//
	void __fastcall funcInitResultListEtc();
	void __fastcall funcInitDogakLine();
	void __fastcall funcInitPnlDocInfo07();


	//===========================================================================
	//저장 & 인쇄 워터마크//
	Graphics::TBitmap *IMGWATERMARK;//사용자/부서명(YYYY.MM.DD hh:nn:ss) 텍스트//
	//void __fastcall funcPaintWaterMark();//사용자/부서명(YYYY.MM.DD hh:nn:ss) 텍스트//



	//===========================================================================
	DWORD startTickCount;
	DWORD currentTickCount;
	DWORD startTickCount1;
	DWORD currentTickCount1;


	GetImageInfo mGetImageInfo1;
	GetImageInfo mGetImageInfo2;
	void __fastcall funcOpenAlphaImage1();
	void __fastcall funcOpenAlphaImage2();

	//===========================================================================
	int __fastcall func_FindFirst2MinDistanceIndex(vector<GPoint>& _vPoint, GPoint _GPoint);
	int __fastcall func_FindSecond2MinDistanceIndex(vector<GPoint>& _vPoint, GPoint _GPoint, int _findex);


	//===========================================================================
	FIBITMAP* m_DIBClone;


	//===========================================================================
	int					m_nTempScale;//201119//사용자설정축척//
	void __fastcall 	mnuScaleClick(TObject *Sender);	//201119//


	//===========================================================================
	int currentWidth, currentHeight;//201223//#FORMMAX
	void __fastcall 	funcSetMaxScreen();



	//===========================================================================
	bool 				m_bAlreadyShowMsg;//210107//#SEJONGPNU//변환지번 없다고 팝업처리 1회만 하려고//
	AnsiString          m_asSejongOldPnu;//210107//#SEJONGPNU//frmSidoCode에서 지번적용에서 입력한 PNU
	//4473037034를 선택했지만 검색어에 시도명이 빠지면서 현재 존재하는 세종시의 읍면동+리를 찾아서 TB_SEJONG_PNU에서 못찾는다//

	//===========================================================================
	int					m_bPreventResize;//210204//



	//***************************************************************************
	//
	// 비암호화 문서 암호화/복호화/업로드 기능//
	//
	//***************************************************************************
	//===========================================================================
	AnsiString 					m_asEncLocalPathName;
	AnsiString 					m_asEncDBPathName;
	LONG 						m_lFileSize;
	char* 						m_pImage;

	int __fastcall 				funcGetFileBuffer(bool _bEncrypt);
	void __fastcall 			funcEncryptFile();
	void __fastcall 			funcDecryptFile();
	//JPEG
	int __fastcall 				funcEncryptJpgDimensions();
	int __fastcall 				funcDecryptJpgDimensions();
	//TIFF
	int __fastcall 				funcEncryptTifDimensions();
	int __fastcall 				funcDecryptTifDimensions();
	//BMP
	int __fastcall 				funcEncryptBmpDimensions();
	int __fastcall 				funcDecryptBmpDimensions();
	//FTP Upload
	void __fastcall 			funcUploadFile(AnsiString _asFilePathEnc);

	//==============================================
	bool						m_bExceptingMainViewFocus;
	//210215//TEdit 포커스 상태에서 <임시저장>을 누르면 포커스된 Edit의 Exit함수를 호출한다//
	//Exit 함수 내에서 예외가 발생하는 경우(동일지번, 날짜오류 등) 처리 못하고 그냥 저장되어 함수로 만들어서 사용한다//
	bool __fastcall 			funcExitDate(TObject *Sender);


	//210303//#TB_COPY_DNLD
	AnsiString					m_asDownloadKindName;
	void __fastcall 			funcSetPnlDownloadReason(bool _bVisible);

	//=========================================================
	//210204//#LOADING_TEST//
	bool						m_bJijukLoading;
	clock_t						m_cStart, m_cFinish;
//	int							m_nSGTreeIndex, m_nSGTreeCount;
//	void __fastcall             funcCreateSGTree();
//	void __fastcall             funcInitSGTree();
//	int __fastcall              funcDispSGTree01();
//	int __fastcall              funcDispSGTree02();
//	int __fastcall              funcDispSGTree03();
//	int __fastcall              funcDispSGTree04();
//	int __fastcall              funcDispSGTree05();
//	int __fastcall              funcDispSGTree06();
//	int __fastcall              funcDispSGTree07();
//	int __fastcall              funcDispSGTree08();
//	int __fastcall              funcDispSGTree09();
//	int __fastcall              funcDispSGTree11();
//	int __fastcall              funcDispSGTree12();
//	int __fastcall              funcDispSGTree13();
//	int __fastcall              funcDispSGTree14();
//	int __fastcall              funcDispSGTree15();
//	int __fastcall              funcDispSGTree17();
//	int __fastcall              funcDispSGTree18();
//	int __fastcall              funcDispSGTree00();
	//=========================================================


	//=========================================================
	// 구대장 연혁 & 소유자정보//
	//=========================================================
	AnsiString					m_asFontName;//공통//한글속성 표시 폰트명//210708//
	int							m_nBonbuType;//본번과 부번 사이의 구별자(1:Default)
	int							m_nAreaPoint;//지적숫자값 정수만 표시(0:Default), 1(소수1자리표시)
	int							m_nSharpWidthPrint;//부분삭제(취소선) 두께//
	int							m_nSharpWidthOverlap;//부분삭제(취소선) 두께//
	int							m_nEmptyBgColor;//'빈칸' 배경색 지정(Default : 128)
	//220119//Get INI Data -> DB Data
//	vector<AnsiString>			m_vAreaUnit;//211201//
//	vector<AnsiString>			m_vValueUnit;//211201//
//	vector<AnsiString>			m_vValue2Unit;//211201//
//	vector<AnsiString>			m_vReasonData;//211201//
	vector<DOCUMENT08_PNU_STRUCT> 	m_ResultDocument08Pnu;
	void __fastcall 			funcGetDoc8Ini();
	void __fastcall 			funcProcessDoc8OwnNames(AnsiString _asPathName);
	//=========================================================

    //220104//논산>공시지가 문서에 블럭지번이 포함된 관계로//
	//<공시지가 상세검색>, <공시지가 상세검색 시도코드검색> ==> 블럭지번을 포함한 지번구분 리스트를 구성한다//
	void __fastcall 				funcSetComboGbn(int _nKind, int _nType);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//220428//#LOG_EXCEPT//
	TStringList *qryErr;
	TStringList *qryLog;
	bool exceptionSuccess;
	bool g_InExceptionHandler;
	void  __fastcall AppException( System:: TObject*  Sender,  Sysutils:: Exception*  E);
	String __fastcall GetComputerNameString();
	String __fastcall GetUserNameString();
	String __fastcall BuildExceptionText(Exception *E);
	String __fastcall SaveTextLog(const String& text);
	String __fastcall SaveExceptionScreenshot();
	void __fastcall SendCrashMail(const String& body, const String& fileName);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	//===========================================================================
	//221020//Get INI Data -> DB Data//지적단위, 과세단위 등 DB에 설정된 값으로 읽어오는 함수//
	vector<OLDLANDDOC_USERFAVORITES_STRUCT>			m_vAREAUNIT;//지적단위 데이터//
	vector<OLDLANDDOC_USERFAVORITES_STRUCT>			m_vVALUEUNIT;//과세1단위 데이터//
	vector<OLDLANDDOC_USERFAVORITES_STRUCT>			m_vVALUE2UNIT;//과세2단위 데이터//
	vector<OLDLANDDOC_USERFAVORITES_STRUCT>			m_vREASONDATA;//사고 데이터//
	//===========================================================================

	//===========================================================================
	//221209//#DOC8_OVERLAP//
	int							m_nFontSize;//열람화면//한글표시 폰트크기//funcGetFontScale에서 ini 값 다시 확인//
	int							bpMiddleW;//열람화면//한글표시 중간-간격//
	bool  						bOwnNamesMove;//소유주명 mover를 움직이고 있는 상태인지//
	bool						m_bPaintRefresh;
	void __fastcall 			funcGetDoc8BasicFont();
	void __fastcall 			funcGetDoc8FontSize();

	bool  						m_bSUBBOOK;//231118//#SHAREOWN//'부책'인지 '공유지연명부'인지 여부 -> frmAlphaDoc8, frmDoc8View에서 사용//

	//=============================================================================
	//240321//[Add]카드대장.개인정보.MASKING.최소사용자 권한//
	//=============================================================================
	vector<RECT_STRUCT> 		m_vMASKINGRECT;
	void __fastcall 			funcDrawMaskingRect(bool _bFront);
	bool						B_MASKING;//DOC8.카드대장.개인정보.MASKING.최소사용자 권한//
	int							MASKING_ALPHA;//0 ~ 255//fromLandArchive_#SGGCD#.ini//
	BLENDFUNCTION 				maskingbf;//투명
	Graphics::TBitmap 			*IMGMASKING;
	//#PI_RATE, PI_RATE
	double						m_dPIFrontLeftRate;
	double						m_dPIFrontTopRate;
	double						m_dPIFrontRightRate;
	double						m_dPIFrontBottomRate;
	double						m_dPIBackLeftRate;
	double						m_dPIBackTopRate;
	double						m_dPIBackRightRate;
	double						m_dPIBackBottomRate;
	//=============================================================================
	//240321//[Add]카드대장.개인정보.MASKING.최소사용자 권한//
	//=============================================================================
	bool 					B_CAPTURE;
	//카드대장 확인해서 B_MASKING 설정하는 함수//
	void __fastcall 		funcCheckCardMasking(AnsiString _asPathName);
	//카드대장.앞면 확인하는 함수//
	bool __fastcall 		funcCheckCardFront(AnsiString _asPathName);
	//=============================================================================

	//=====================================================================
	//241101//#구대장한글화편집#AI
	//=====================================================================
	bool					m_bAIOCR;//260611//AIOCR 기능(NO DB DATA, TB_DOCUMENT08_HIS, OWNINFO 테이블 부재로 확인)
	int 					m_nAIOCRTimerValue;
	void __fastcall			funcSetDoc08AI(bool _bVisible);
	void __fastcall 		ProcessOCRResult(const String& responseText);


	//=============================================================================
	//231118//통합검색 버튼 <-> 상세검색 버튼//
	//=============================================================================
	void __fastcall 			funcSetTotalDetailQueryButtons(int _nTag);


	//======================================================================
	//241204//#전주#중앙정보테크//
	//======================================================================
	int _SKINCOLOR_;//16750131//
	int _SKINCOLOR2_;//16760962//


	//======================================================================
	//260617//기능별 함수처리//
	//======================================================================
	void __fastcall funcSetBasicDirectory();
	void __fastcall funcSetINIFiles();
	void __fastcall funcSetLogoutTimer();
	void __fastcall funcControlMainProgramRes();
	void __fastcall funcSetErrFiles();
	void __fastcall funcFreeINIFiles();
	void __fastcall funcFreeMapRelation();
	void __fastcall funcFreeExternalFiles();
	void __fastcall funcFreeErrFiles();
	void __fastcall funcFreeBasicResource();


	//======================================================================
	//260618//버튼이미지 관리방식 변경//
	//======================================================================
	enum ImgSystemBtnMode {Min, Max, Mid, Close22, Close20, Close12, SystemCnt} m_eImgSystemBtnMode;//시스템 제어 버튼//
	enum ImgBGMode {BGLayer, BGRegist, BGMainFind, BGChangeMenu, BGCnt} m_eImgBGMode;//패널 배경//
	enum ImgModeBtnMode {DocMode, JijukMode, ModeCnt} m_eImgModeBtnMode;//문서-지적도 버튼//
	enum ImgTabMode {TabPrev, TabNext, TabDetail, TabFind, TabFind18, TabImgFile, PopupFind, Manual, RoadView, QFind, QDot, IconPoi, Arrow, TabCnt} m_eImgTabMode;//검색화면 상세검색 등 탭//
	enum ImgPoiMode {PoiBg1, PoiBg2, PoiSymDoc01, PoiSymDoc02, PoiSymDoc03, PoiSymDoc04, PoiSymDoc06, PoiSymDoc07, PoiSymDoc08, PoiSymDoc09, PoiSymDoc17, PoiSymDoc20, PoiCnt} m_eImgPoiBtnMode;//POI//
	enum ImgIconMode {Icon, IconCircle, Icon04, SettingEnv, ArchiveLogo, ITKLogo, IconMemoPoint, IconMemoPoly, Poi18, IconCnt} m_eImgIconMode;//ICON//
	enum ImgDocBtnMode {SaveFile, Print, Rotate, RectClear, Conv, Adjust, DocZoomIn, DocZoomOut, DocCnt} m_eImgDocBtnMode;//문서열람화면 버튼//
	enum ImgConvBtnMode {Hanja, CalcDate, CalcArea, Calcuator, ConvCnt} m_eImgConvBtnMode;  //문서-편의기능 버튼//
	enum ImgSpreadBtnMode {LeftArrow1, LeftArrow2, RightArrow1, RightArrow2, SpreadCnt} m_eImgSpreadBtnMode;//검색화면 표시여부 버튼//
	enum ImgSpatialBtnMode {SpatialZoomIn, SpatialZoomOut, Area, Dist, Cancel, SpatialCnt} m_eImgSpatialBtnMode;//공간화면 버튼//
	enum ImgLayerBtnMode {LayerIcon, LayerAir, LayerLegal, LayerDoc, LayerDogn, LayerMemo, LayerPhoto, LayerPoly, LayerHybrid, LayerGagam, DocZoomOrg, Space, SMemoPoint, SMemoPoly, LayerCnt} m_eImgLayerBtnMode;//레이어 제어 버튼//
	enum ImgRegistBtnMode {RegistIcon, RegistLMReq, Regist01Attach, Regist02Attach, RegistCnt} m_eImgRegistBtnMode;//등록-외부프로그램 제어 버튼//
	enum ImgDoc08BtnMode {Overlap, Doc08View, Doc08Edit1, Doc08Edit2, AIOCR1, AIOCR2, Mover1, Mover2, Doc08Cnt} m_eImgDoc08BtnMode;//구대장한글화 버튼//
	enum ImgHelpBtnMode {TipZoomIn, TipZoomOut, TipSaveFile, TipPrint, TipRotate, TipRectSelect, TipRectClear, TipAdjust, TipConv, TipHanja, TipCalcDate, TipCalcArea, TipCalculator, TipArea, TipDist, TipCancel, TipOrg, TipPrev, TipNext, TipPoi, TipSpace, TipPoint, TipPoly, TipPointHelp, TipPolyHelp, HelpCnt} m_eImgHelpBtnMode;//ToolTip 버튼//
	enum ImgTGAMode {TgaArea, TgaStreet, TgaStamp, TgaRoadFlag, TgaDoc8Jimok, TgaDoc8Value, TgaMasking, TgaCnt} m_eImgTGAMode;//TAGA Files//
	enum ImgButtonsMode {TempDoc, TempDocUn, TempList, BtnPrev, BtnNext, BtnLMFS, ButtonCnt} m_eImgButtonsMode;//A Pair of Buttons Files//
	enum ImgEtcMode {NoImage, NoImage120, EtcCnt} m_eImgEtcMode;//ETC//

	Graphics::TBitmap *BITMAP_BTN_SYSTEM[SystemCnt];//
	Graphics::TBitmap *BITMAP_BTN_BG[BGCnt];//
	Graphics::TBitmap *BITMAP_BTN_MODE[2][ModeCnt];//
	Graphics::TBitmap *BITMAP_BTN_TAB[2][TabCnt];//
	Graphics::TBitmap *BITMAP_BTN_POI[PoiCnt];//
	Graphics::TBitmap *BITMAP_BTN_ICON[IconCnt];//
	Graphics::TBitmap *BITMAP_BTN_DOC[DocCnt];//
	Graphics::TBitmap *BITMAP_BTN_CONV[ConvCnt];//
	Graphics::TBitmap *BITMAP_BTN_SPREAD[SpreadCnt];//
	Graphics::TBitmap *BITMAP_BTN_SPATIAL[SpatialCnt];//
	Graphics::TBitmap *BITMAP_BTN_LAYER[2][LayerCnt];//
	Graphics::TBitmap *BITMAP_BTN_REGIST[2][RegistCnt];//
	Graphics::TBitmap *BITMAP_BTN_DOC08[Doc08Cnt];//
	Graphics::TBitmap *BITMAP_BTN_HELP[HelpCnt];//
	Graphics::TBitmap *BITMAP_BTN_TGA[TgaCnt];//
	Graphics::TBitmap *BITMAP_BTN_BUTTONS[2][ButtonCnt];//
	Graphics::TBitmap *BITMAP_BTN_ETC[EtcCnt];//

	//=====================================================================
	// 버튼 이미지 초기화//
	//=====================================================================
	void __fastcall 	funcFreeEachButtonImage(TObject *Sender);

	//===========================================================================
	// 중복코드 함수처리 : 메인화면 하단 상태바 메시지 출력//
	//===========================================================================
	void __fastcall 	funcSetStatusBarMsg(int _nIndex, AnsiString _asMsg);

	//===========================================================================
	// ArchiveLMFS 호출 => 검색 지번, PNU 전송//
	//===========================================================================
	void __fastcall 	SendPnuToArchiveLMFS(const String &APnu, const String &AJibun);
	//===========================================================================
	// ArchiveLMFS 프로그램 첫 실행 => 검색 지번, PNU 전송//
	// Send SearchPnu To ArchiveLMFS : [통합검색]지번 보내기//
	//===========================================================================
	bool __fastcall 	funcExeArchiveLMFS();
	void __fastcall 	funcSetLMFSButton(bool _bUsing);

	//---------------------------------------------------------------------------
	//#CODE_CLEANUP//DB 변경사항에 대한 확인 및 처리//
	//---------------------------------------------------------------------------
	bool __fastcall 	funcCheckDBUpgrade();

	bool __fastcall 	funcPlayAIOCRWaiting(bool _bPlay);


	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
