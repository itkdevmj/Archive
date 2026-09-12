//---------------------------------------------------------------------------

#ifndef untProgramCloseQH
#define untProgramCloseQH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmProgramCloseQ : public TForm
{
__published:	// IDE-managed Components
	TImage *imgBG;
	TSpeedButton *btnClose;
	TImage *IMGYES;
	TImage *IMGCANCEL;
	TLabel *CountLabel;
	TLabel *CountMessageLabel;
	TTimer *Timer1;
	TPanel *panCenter;
	TPanel *panWindowsMove;
	TImage *imgIconTitle;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall IMGYESMouseEnter(TObject *Sender);
	void __fastcall IMGYESMouseLeave(TObject *Sender);
	void __fastcall IMGYESClick(TObject *Sender);
	void __fastcall IMGCANCELMouseEnter(TObject *Sender);
	void __fastcall IMGCANCELMouseLeave(TObject *Sender);
	void __fastcall IMGCANCELClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
    int m_bCount;

	//IMAGES
	Graphics::TBitmap *BITMAP_BTN_YES[2];
	Graphics::TBitmap *BITMAP_BTN_CANCEL[2];
	Graphics::TBitmap *BITMAP_BG[2];//210806//

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();


	__fastcall TfrmProgramCloseQ(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProgramCloseQ *frmProgramCloseQ;
//---------------------------------------------------------------------------
#endif
