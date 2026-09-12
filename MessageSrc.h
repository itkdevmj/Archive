//---------------------------------------------------------------------------

#ifndef MessageSrcH
#define MessageSrcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "bsMessages.hpp"
#include "bsSkinCtrls.hpp"
#include "bsSkinData.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "AdvMemo.hpp"
#include "bsSkinBoxCtrls.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmMsg : public TForm
{
__published:	// IDE-managed Components
	TPanel *exPanelWarring;
	TImage *IMGWARRING;
	TImage *IMGWARRINGYES;
	TImage *IMGWARRINGNO;
	TLabel *lblWarringTitle;
	TLabel *lblWarringComment;
	TPanel *exPanelError;
	TImage *IMGERROR;
	TImage *IMGERRORYES;
	TLabel *lblErrorTitle;
	TLabel *lblErrorComment;
	TPanel *exPanelInformation;
	TImage *IMGINFORMATION;
	TImage *IMGINFORYES;
	TLabel *lblInforTitle;
	TLabel *lblInforComment;
	void __fastcall IMGWARRINGYESMouseEnter(TObject *Sender);
	void __fastcall IMGWARRINGYESMouseLeave(TObject *Sender);
	void __fastcall IMGWARRINGYESMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall IMGWARRINGNOMouseEnter(TObject *Sender);
	void __fastcall IMGWARRINGNOMouseLeave(TObject *Sender);
	void __fastcall IMGWARRINGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall IMGERRORMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall IMGINFORMATIONMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall IMGERRORYESMouseEnter(TObject *Sender);
	void __fastcall IMGERRORYESMouseLeave(TObject *Sender);
	void __fastcall IMGERRORYESMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall IMGINFORYESMouseEnter(TObject *Sender);
	void __fastcall IMGINFORYESMouseLeave(TObject *Sender);
	void __fastcall IMGINFORYESMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall IMGWARRINGNOMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	void __fastcall CreateParams(TCreateParams &Params);

	//---------------------------------------------------------------------------
	int  nMemoMaxLen;//maxlength : 200
	bool bMaxLength;//edit 글자수 제한에 사용.

public:		// User declarations
	AnsiString m_sBoxPath;
	int m_bClick;
	int m_nCallMode;
	AnsiString m_sDepartCd, m_sAcceptKey;

	AnsiString m_sConnecterId;//사용자
	AnsiString m_sConnecterDepartCd;

	void __fastcall IMGOBJECTIONSAVEdeEnabled();//저장 비활성화
	void __fastcall func_ProcessList();
	void __fastcall func_SaveObjectionData();

	void __fastcall funcProcessIMGWARRINGYES();
	void __fastcall funcProcessIMGERRORYES();
	void __fastcall funcProcessIMGINFORYES();
	void __fastcall funcProcessIMGOBJECTIONSAVE();

	void __fastcall funcMessageDlg(AnsiString Title, AnsiString Msg, int HelpCtx);

	__fastcall TfrmMsg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMsg *frmMsg;
//---------------------------------------------------------------------------
#endif
