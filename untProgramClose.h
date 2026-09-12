//---------------------------------------------------------------------------

#ifndef untProgramCloseH
#define untProgramCloseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <GIFImg.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmProgramClose : public TForm
{
__published:	// IDE-managed Components
	TImage *imgBG;
	TLabel *lbl_State;
	TLabel *Label1;
	TLabel *lbl_ThreadState;
	TLabel *lbl_ThreadState_2;
	TLabel *lbl_ThreadState_3;
	TLabel *lbl_ThreadState_4;
	TLabel *lbl_ThreadState_5;
	TTimer *tmr_ProgramClose;
	TTimer *tmr_StopThreadCheck;
	TSpeedButton *btnClose;
	TPanel *panWindowsMove;
	TImage *imgIconTitle;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TPanel *panCenter;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall tmr_ProgramCloseTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmProgramClose(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProgramClose *frmProgramClose;
//---------------------------------------------------------------------------
#endif
