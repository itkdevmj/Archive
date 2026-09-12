//---------------------------------------------------------------------------

#ifndef untHanjaH
#define untHanjaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>

//#include "mainSrc.h"

//---------------------------------------------------------------------------
class TfrmHanja : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlHanja;
	TImage *imgBG;
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TPanel *pnlWebBrowser;
	TCppWebBrowser *WebBrowser;
	TImage *Image3;
	TLabel *lblFormTitle;
	TShape *shpBG;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormDeactivate(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmHanja(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmHanja *frmHanja;
//---------------------------------------------------------------------------
#endif
