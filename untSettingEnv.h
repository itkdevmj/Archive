//---------------------------------------------------------------------------

#ifndef untSettingEnvH
#define untSettingEnvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmSettingEnv : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlSettingEnv;
	TPanel *pnlBlankT1;
	TPanel *pnlTitle;
	TImage *iconPoi;
	TImage *imgSettingEnvClose;
	TLabel *lblTitle;
	TPanel *pnlUserManagement;
	TImage *iconCircle3;
	TLabel *lblUserManagement;
	TPanel *pnlRelaseList;
	TPanel *pnlLogout;
	TPanel *pnlBlankT2;
	TPanel *pnlLogoutT;
	TImage *iconCircle5;
	TLabel *lblLogout;
	TPanel *pnlLogoutD;
	TPanel *pnlLogoutB;
	TPanel *pnlSearchBar;
	TPanel *pnlSearchBarT;
	TImage *iconCircle6;
	TLabel *lblSearchBar;
	TPanel *pnlSearchBarD;
	TRadioButton *rbSearchBar1;
	TRadioButton *rbSearchBar2;
	TPanel *pnlSearchBarB;
	TComboBox *cboLogout;
	TLabel *lblDoc0_V7_lbl1;
	TEdit *edtLogoutTime;
	TPanel *pnlUserManagementT;
	TPanel *pnlRelaseListT;
	TImage *iconCircle2;
	TLabel *lblReleaseList;
	TPanel *pnlBlankB1;
	TPanel *pnlViewMode;
	TPanel *pnlViewModeT;
	TImage *iconCircle7;
	TLabel *lblViewMode;
	TPanel *pnlViewModeD;
	TRadioButton *rbViewMode1;
	TRadioButton *rbViewMode2;
	TPanel *pnlViewModeB;
	TPanel *pnlDoc02Day;
	TPanel *pnlDoc02DayT;
	TImage *iconCircle4;
	TLabel *lblDoc02Day;
	TPanel *pnlDoc02DayD;
	TPanel *pnlDoc02DayB;
	TRadioButton *rbDoc02Day1;
	TRadioButton *rbDoc02Day3;
	TRadioButton *rbDoc02Day2;
	TPanel *pnlSettingT;
	TPanel *pnlDirectT;
	TPanel *pnlSetting;
	TPanel *pnlDirect;
	TPanel *pnlAbout;
	TPanel *pnlAboutT;
	TImage *iconCircle1;
	TLabel *lblAbout;
	TImage *imgSwitch1;
	TImage *imgSwitch2;
	TPanel *pnlDirectD;
	TPanel *pnlSettingD;
	TPanel *pnlAutoJibun;
	TPanel *pnlAutoJibunT;
	TImage *iconCircle8;
	TLabel *lbllAutoJibun;
	TPanel *pnlAutoJibunD;
	TRadioButton *rbAutoJibun1;
	TRadioButton *rbAutoJibun2;
	TPanel *pnlAutoJibunB;
	TPanel *pnlMain;
	TScrollBox *ScrollBox1;
	TShape *shpBG;
	TPanel *pnlWaterMark;
	TPanel *pnlWaterMarkT;
	TImage *iconCircle9;
	TLabel *lblWaterMark;
	TPanel *pnlWaterMarkD;
	TRadioButton *rbWaterMark1;
	TRadioButton *rbWaterMark2;
	TPanel *pnlWaterMarkB;
	TPanel *pnlViewAir;
	TPanel *pnlViewAirT;
	TImage *iconCircle10;
	TLabel *lblViewAir;
	TPanel *pnlViewAirD;
	TRadioButton *rbViewAir1;
	TRadioButton *rbViewAir2;
	TPanel *pnlViewAirB;
	TPanel *pnlOwnLabel;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel2;
	TImage *iconCircle11;
	TLabel *Label2;
	TPanel *pnlAreaFont;
	TPanel *pnlAreaFontT;
	TImage *iconCircle12;
	TLabel *lblAreaFontT;
	TPanel *pnlAreaFontD;
	TPanel *lblAreaFont;
	TEdit *edtAreaFontSize;
	TSpeedButton *btnFontColor;
	TLabel *lblAreaFontColor;
	TLabel *lblAreaFontSize;
	TColorDialog *ColorDialog1;
	TPanel *pnlDoc01Group;
	TPanel *pnlDoc01GroupT;
	TImage *iconCircle13;
	TLabel *lblDoc01Group;
	TPanel *pnlDoc01GroupD;
	TPanel *pnlDoc01GroupB;
	TRadioButton *rbDoc01Group1;
	TRadioButton *rbDoc01Group2;
	TPanel *pnlExpand;
	TPanel *pnlExpandT;
	TImage *iconCircle14;
	TLabel *lblExpand;
	TPanel *pnlExpandD;
	TRadioButton *rbExpand1;
	TRadioButton *rbExpand2;
	TPanel *pnlExpandB;
	TPanel *pnlStat;
	TPanel *pnlStatT;
	TImage *iconCircle15;
	TLabel *lblStat;
	TRadioButton *rbOwnLabel1;
	TRadioButton *rbOwnLabel2;
	TPanel *pnlBlankD;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall imgSettingEnvCloseClick(TObject *Sender);
	void __fastcall lblUserManagementClick(TObject *Sender);
	void __fastcall lblReleaseListClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall pnlBlankT1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall lblAboutClick(TObject *Sender);
	void __fastcall imgSwitchClick(TObject *Sender);
	void __fastcall btnFontColorClick(TObject *Sender);
	void __fastcall ScrollBox1MouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall lblStatClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmSettingEnv(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSettingEnv *frmSettingEnv;
//---------------------------------------------------------------------------
#endif
