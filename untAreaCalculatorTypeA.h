//---------------------------------------------------------------------------

#ifndef untAreaCalculatorTypeAH
#define untAreaCalculatorTypeAH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmAreaCalculatorTypeA : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *btnCalcA;
	TEdit *edtValue;
	TComboBox *cboType;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TStaticText *StaticText3;
	TStaticText *StaticText4;
	TStaticText *StaticText5;
	TStaticText *StaticText6;
	TImage *imgBg;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TSpeedButton *btnCalcB;
	TEdit *Edit5;
	TEdit *Edit6;
	TImage *btnChange1;
	TImage *btnChange2;
	TImage *btnCloseTypeB;
	TPanel *panWindowsMove;
	TLabel *Label1;
	TImage *Image3;
	void __fastcall cboTypeChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCalcAClick(TObject *Sender);
	void __fastcall edtValueKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnCalcBClick(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmAreaCalculatorTypeA(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAreaCalculatorTypeA *frmAreaCalculatorTypeA;
//---------------------------------------------------------------------------
#endif
