//---------------------------------------------------------------------------

#ifndef untCalculatorH
#define untCalculatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include <Graphics.hpp>
#include <oleidl.h>
#include <pngimage.hpp>

//#include "mainSrc.h"

//---------------------------------------------------------------------------
class TfrmCalculator : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlWebBrowser;
	TCppWebBrowser *WebBrowser2;
	TPanel *pnlCalculator;
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TImage *imgBG;
	TLabel *lblFormTitle;
	TImage *Image2;
	TShape *shpBG;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);

private:	// User declarations
	IOleInPlaceActiveObject *FOleInPlaceActiveObject;
	void __fastcall MyMessageHandler(TMsg &Msg, bool &Handled);

public:		// User declarations
	__fastcall TfrmCalculator(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCalculator *frmCalculator;
//---------------------------------------------------------------------------
#endif
