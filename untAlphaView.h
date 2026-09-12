//---------------------------------------------------------------------------

#ifndef untAlphaViewH
#define untAlphaViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include "GR32_RangeBars.hpp"
#include <Graphics.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmAlphaView : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlTool;
	TPanel *pnlAlpha;
	TGaugeBar *gbAlpha;
	TPanel *pnlInfo;
	TPanel *pnlGamma;
	TGaugeBar *gbGamma;
	TPanel *pnlView;
	TLabel *Label1;
	TLabel *lblAlphaV;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *lblGammaV;
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TLabel *lblAlphaT;
	TLabel *Label3;
	TLabel *Label2;
	TButton *btnZoomIn;
	TButton *btnZoomOut;
	TButton *btnOrg;
	TButton *btnRotateL;
	TButton *btnRotateR;
	TButton *btnRotate0;
	TOpenDialog *OpenDialog1;
	TEdit *edtAngle;
	TButton *btnRotateSet;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall gbGammaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall gbAlphaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnOrgClick(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall imgResizeClick(TObject *Sender);
	void __fastcall btnZoomInClick(TObject *Sender);
	void __fastcall btnZoomOutClick(TObject *Sender);
	void __fastcall btnRotateClick(TObject *Sender);
	void __fastcall edtAngleKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtAngleChange(TObject *Sender);
	void __fastcall btnRotateSetClick(TObject *Sender);

private:	// User declarations
	bool	_bMinusFlag;

public:		// User declarations

	//form caption moving
	BEGIN_MESSAGE_MAP
	   MESSAGE_HANDLER(WM_MOVING, TMessage, WMMOVING)
	END_MESSAGE_MAP(TForm)

	void __fastcall WMMOVING(TMessage & msg);

    tagPOINT tpPosition;

	int 			m_nAlphaValue;
	int 			m_nGammaValue;
	AnsiString 		m_asTitleName;

	void __fastcall funcProcessAlpha();
	void __fastcall funcProcessGamma();

	void __fastcall func_Trans();

	void __fastcall funcSetOrg();

	__fastcall TfrmAlphaView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAlphaView *frmAlphaView;
//---------------------------------------------------------------------------
#endif
