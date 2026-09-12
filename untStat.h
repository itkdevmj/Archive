//---------------------------------------------------------------------------

#ifndef untStatH
#define untStatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <Mask.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
#include <Dialogs.hpp>
#include "tmsAdvGridExcel.hpp"
#include "bsPngImageList.hpp"
#include "bsSkinBoxCtrls.hpp"
#include "bsSkinCtrls.hpp"
#include <DateUtils.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
//---------------------------------------------------------------------------
class TfrmStat : public TForm
{
__published:	// IDE-managed Components
	TPanel *panCenter;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *panWindowsMove;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TImage *IMGSAVELOG;
	TImage *IMGEXIT;
	TPanel *pnlFind;
	TImage *IMGFIND;
	TShape *shpBG;
	TCheckBox *chkDoc01;
	TSaveDialog *SaveDialog1;
	TAdvGridExcelIO *AdvGridExcelIO1;
	TPanel *palWait;
	TShape *shpWait;
	TbsPngImageView *bsPngImageView1;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	TLabel *lblCnt;
	TAdvStringGrid *sgStat;
	TCheckBox *chkDoc02;
	TCheckBox *chkDoc03;
	TCheckBox *chkDoc04;
	TCheckBox *chkDoc06;
	TCheckBox *chkDoc07;
	TCheckBox *chkDoc08;
	TCheckBox *chkDoc09;
	TCheckBox *chkDoc15;
	TCheckBox *chkDoc17;
	TCheckBox *chkDoc18;
	TCheckBox *chkDoc11;
	TGroupBox *gbDoc;
	TGroupBox *gbKind;
	TCheckBox *chkYearLand;
	TCheckBox *chkDocKind;
	TTimer *Timer1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet3;
	TPanel *pnlTab1;
	TPanel *pnlTab3;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TImage *IMGFIND3;
	TGroupBox *GroupBox1;
	TAdvStringGrid *sgStatDoc8;
	TRadioButton *rbView;
	TRadioButton *rbPrint;
	TGroupBox *GroupBox2;
	TDateTimePicker *edtSEndDt;
	TLabel *Label1;
	TDateTimePicker *edtSSttDt;
	TGroupBox *GroupBox3;
	TbsSkinComboBox *cboSUmd;
	TEdit *edtSUmdCd;
	TPanel *Panel1;
	TPanel *Panel9;
	TLabel *lblStatCnt;
	TAdvGridExcelIO *AdvGridExcelIO2;
	TRadioButton *rbDirect;
	TCheckBox *chkView;
	TCheckBox *chkPrint;
	TCheckBox *chkDirect;
	TRadioButton *rbUser;
	TRadioButton *rbUmd;
	TAdvStringGrid *sgStatDoc8Save;
	TTabSheet *TabSheet2;
	TPanel *pnlTab2;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *Panel12;
	TAdvStringGrid *sgStatUserDoc;
	TPanel *Panel13;
	TLabel *lblStatCnt2;
	TPanel *Panel14;
	TImage *IMGFIND2;
	TGroupBox *GroupBox4;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TGroupBox *GroupBox5;
	TLabel *Label3;
	TDateTimePicker *edtEndDt2;
	TDateTimePicker *edtSttDt2;
	TLabel *Label2;
	TAdvGridExcelIO *AdvGridExcelIO3;
	TTabSheet *TabSheet4;
	TPanel *Panel2;
	TPanel *Panel15;
	TPanel *Panel16;
	TPanel *Panel17;
	TAdvStringGrid *sgStatDoc;
	TPanel *Panel18;
	TLabel *lblStatCnt4;
	TLabel *lblUnit;
	TPanel *Panel19;
	TImage *IMGFIND4;
	TGroupBox *GroupBox6;
	TRadioButton *rbUmdPath;
	TRadioButton *rbUmdRecord;
	TAdvGridExcelIO *AdvGridExcelIO4;
	TADOConnection *ADOConnection1;
	TADOQuery *ADOQuery1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall IMGSAVELOGMouseEnter(TObject *Sender);
	void __fastcall IMGSAVELOGMouseLeave(TObject *Sender);
	void __fastcall IMGSAVELOGClick(TObject *Sender);
	void __fastcall IMGEXITMouseEnter(TObject *Sender);
	void __fastcall IMGEXITMouseLeave(TObject *Sender);
	void __fastcall IMGEXITClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall IMGFINDMouseEnter(TObject *Sender);
	void __fastcall IMGFINDMouseLeave(TObject *Sender);
	void __fastcall IMGFINDClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sgStatGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall cboSUmdChange(TObject *Sender);
	void __fastcall sgStatUserDocGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
          TVAlignment &VAlign);
	void __fastcall sgStatDocGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
          TVAlignment &VAlign);


private:	// User declarations
	vector<STAT_STRUCT> 		m_vStatDoc01;
	vector<STAT_STRUCT> 		m_vStatDoc02;
	vector<STAT_STRUCT> 		m_vStatDoc03;
	vector<STAT_STRUCT> 		m_vStatDoc04;
	vector<STAT_STRUCT> 		m_vStatDoc06;
	vector<STAT_STRUCT> 		m_vStatDoc07;
	vector<STAT_STRUCT> 		m_vStatDoc08;
	vector<STAT_STRUCT> 		m_vStatDoc09;
	vector<STAT_STRUCT> 		m_vStatDoc11;
	vector<STAT_STRUCT> 		m_vStatDoc15;
	vector<STAT_STRUCT> 		m_vStatDoc17;
	vector<STAT_STRUCT> 		m_vStatDoc18;

public:		// User declarations

	void __fastcall 	funcSetWaitWindows(bool bSetValue);

	//IMAGES
	Graphics::TBitmap *BITMAP_BTN_SAVELOG[2];
	Graphics::TBitmap *BITMAP_BTN_EXIT[2];
	Graphics::TBitmap *BITMAP_BTN_FIND[2];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	//####################################################
	// 통계보기//
	//####################################################
	int				m_nDocCount;
	int				m_nStatRowCount;
	void __fastcall funcInitStat();
	void __fastcall funcDispStat();
	void __fastcall funcReadStat();

	void __fastcall funcReadStatDoc01();
	void __fastcall funcReadStatDoc02();
	void __fastcall funcReadStatDoc03();
	void __fastcall funcReadStatDoc04();
	void __fastcall funcReadStatDoc06();
	void __fastcall funcReadStatDoc07();
	void __fastcall funcReadStatDoc08();
	void __fastcall funcReadStatDoc09();
	void __fastcall funcReadStatDoc11();
	void __fastcall funcReadStatDoc15();
	void __fastcall funcReadStatDoc17();
	void __fastcall funcReadStatDoc18();

	void __fastcall funcSetComboDoc();

	void __fastcall funcReadStatDoc01_2();
	void __fastcall funcReadStatDoc02_2();
	void __fastcall funcReadStatDoc03_2();
	void __fastcall funcReadStatDoc04_2();
	void __fastcall funcReadStatDoc06_2();
	void __fastcall funcReadStatDoc07_2();
	void __fastcall funcReadStatDoc08_2();
	void __fastcall funcReadStatDoc09_2();
	void __fastcall funcReadStatDoc11_2();
	void __fastcall funcReadStatDoc15_2();
	void __fastcall funcReadStatDoc17_2();
	void __fastcall funcReadStatDoc18_2();

	bool __fastcall funcCheckCountComboDoc();

	void __fastcall funcReadStatDoc01_3();
	void __fastcall funcReadStatDoc02_3();
	void __fastcall funcReadStatDoc03_3();
	void __fastcall funcReadStatDoc04_3();
	void __fastcall funcReadStatDoc06_3();
	void __fastcall funcReadStatDoc07_3();
	void __fastcall funcReadStatDoc08_3();
	void __fastcall funcReadStatDoc09_3();
	void __fastcall funcReadStatDoc11_3();
	void __fastcall funcReadStatDoc15_3();
	void __fastcall funcReadStatDoc17_3();
	void __fastcall funcReadStatDoc18_3();


	//####################################################
	// 구대장 열람/인쇄 통계보기//
	//####################################################
	int				m_nStatDoc8RowCount;
	void __fastcall funcInitTabStatDoc8();
	void __fastcall funcCreateStatDoc8();
	void __fastcall funcInitStatDoc8();
	void __fastcall funcDispStatDoc8();
	void __fastcall funcReadStatDoc8();
	void __fastcall funcChangeSUmd();
    void __fastcall funcReadUmdData();

	UMDRICODE_STRUCT            tempSIDOCODE;
	vector<UMDRICODE_STRUCT> 	m_vUMDRICODE;//통계데이터//#STAT
	vector<RIDATA_STRUCT> 		m_vRIDATA;//통계데이터//#STAT
	vector<DOC8_STAT_STRUCT>	m_vStat;


	//===========================================================================
	//250708//[기능개선]구대장한글화 통계(+사용자별)
	//===========================================================================
	void __fastcall funcCreateStatDoc8_User();
	void __fastcall funcInitStatDoc8_User();
	void __fastcall funcDispStatDoc8_User();
	vector<DOC8_STAT_USER_STRUCT>	m_vStatUser;
	void __fastcall funcReadStatDoc8_User();


	//===========================================================================
	//250710//[기능개선]사용자별 문서열람 현황
	//===========================================================================
	int				m_nStatUserDocRowCount;
	void __fastcall funcInitTabStatUserDoc();
	void __fastcall funcCreateStatUserDoc();
	void __fastcall funcInitStatUserDoc();
	void __fastcall funcDispStatUserDoc();
	vector<STAT_USERDOC_STRUCT>	m_vStatUserDoc;
	void __fastcall funcReadStatUserDoc();

	//===========================================================================
	//250711//[기능개선]읍면동별 구축통계
	//===========================================================================
	int 			m_nTargetDoc;
	int				m_nStatDocRowCount;
	vector<UMDDATA_STRUCT> 	m_vUMD;//통계데이터//#STAT
	//읍면동별 구축통계 - 리스트 초기화, 해제//
	void __fastcall funcInitStringList(bool _bSet);
	TStringList *m_slUmdCode[DF_DOC_CNT];//구대장,지적도,이동결의서,측량결과도,기타문서//
	TStringList *m_slUmdCnt[DF_DOC_CNT];//구대장,지적도,이동결의서,측량결과도,기타문서//
	void __fastcall funcCreateStatDoc();
	void __fastcall funcInitStatDoc();
	void __fastcall funcDispStatDoc();
	void __fastcall funcReadStatDoc(int _nDocNo);



	__fastcall TfrmStat(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStat *frmStat;
//---------------------------------------------------------------------------
#endif
