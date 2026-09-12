//---------------------------------------------------------------------------

#ifndef untPreviewH
#define untPreviewH
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


#define WIN32
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <math.hpp>
#include <JPEG.hpp>
//---------------------------------------------------------------------------
class TfrmPreview : public TForm
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
	TScrollBox *ScrollBox1;
	TShape *Shape1;
	TPanel *pnlMain;
	TTimer *Timer1;
	TComboBox *cboPreviewDocKind;
	TComboBox *cboPreviewDocKind2;
	TLabel *lblCount;
	TLabel *Label1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall cboPreviewDocKindClick(TObject *Sender);
private:	// User declarations
public:		// User declarations

	Graphics::TBitmap *IMGNOIMAGETHUMB;
	TList 		*pnlThumbList;
	TList 		*imgThumbList;
	TList 		*lblThumbList;


	GetImageInfo mGetImageInfo;

	void 		__fastcall funcSetWaitWindows(bool bSetValue);
	void 		__fastcall funcProcessThumb();
	void 		__fastcall funcGotoPageThumb();
	void 		__fastcall funcCreateListThumb();
	void 		__fastcall funcDeleteComponentsThumb();
	void 		__fastcall funcMakeDynamicThumbnail(int _nIndex, int _nVectorIdx);
	void 		__fastcall funcShowCurrentThumbLabel();
	AnsiString 	__fastcall funcLoadImageThumb(AnsiString _asFilename);

	void 		__fastcall TfrmPreview::imgThumbDC_onClick(TObject *Sender);
	void 		__fastcall funcInitThumb();


	__fastcall TfrmPreview(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPreview *frmPreview;
//---------------------------------------------------------------------------
#endif
