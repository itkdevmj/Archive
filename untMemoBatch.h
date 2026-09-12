//---------------------------------------------------------------------------

#ifndef untMemoBatchH
#define untMemoBatchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include "bsSkinBoxCtrls.hpp"
#include <Dialogs.hpp>
#include <Mask.hpp>
#include "tmsAdvGridExcel.hpp"
#include "bsPngImageList.hpp"
#include "bsSkinCtrls.hpp"
//---------------------------------------------------------------------------
class TfrmMemoBatch : public TForm
{
__published:	// IDE-managed Components
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TImage *Image2;
	TPanel *panCenter;
	TLabel *lblFormTitle;
	TMemo *Memo1;
	TFileOpenDialog *FileOpenDialog1;
	TImage *IMGREGIST;
	TAdvStringGrid *sgResult;
	TbsSkinEdit *edtFind;
	TImage *IMGFIND;
	TImage *IMGDELETE;
	TAdvGridExcelIO *AdvGridExcelIO1;
	TLabel *lblFind;
	TLabel *lblCount;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TbsSkinExPanel *palWait;
	TbsSkinStdLabel *bsSkinStdLabel1;
	TbsSkinStdLabel *bsSkinStdLabel2;
	TbsPngImageView *bsPngImageView1;
	TLabel *Label1;
	TShape *shpBG;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall IMGREGISTMouseEnter(TObject *Sender);
	void __fastcall IMGREGISTMouseLeave(TObject *Sender);
	void __fastcall IMGREGISTClick(TObject *Sender);
	void __fastcall edtHangeul_OnEnter(TObject *Sender);
	void __fastcall edtFindKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall IMGFINDMouseEnter(TObject *Sender);
	void __fastcall IMGFINDMouseLeave(TObject *Sender);
	void __fastcall IMGFINDClick(TObject *Sender);
	void __fastcall IMGDELETEMouseEnter(TObject *Sender);
	void __fastcall IMGDELETEMouseLeave(TObject *Sender);
	void __fastcall IMGDELETEClick(TObject *Sender);
	void __fastcall sgResultGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
          TVAlignment &VAlign);
	void __fastcall sgResultClickCell(TObject *Sender, int ARow, int ACol);

private:	// User declarations

	TIniFile 	*_iniList;

public:		// User declarations

	BATCHMEMOINFO_STRUCT 			tempRawExcelData;//¿¢¼¿ÀÚ·á ¿øº»
	vector<BATCHMEMOINFO_STRUCT> 	m_vRAWEXCELDATA;

	MEMOINFO_STRUCT					tTempMemoInfo;
	vector<MEMOINFO_STRUCT>			m_vTEMPMEMOINFO;
	MEMOVECTOR_STRUCT				tTempMemoVector;
	vector<MEMOVECTOR_STRUCT>		m_vTEMPMEMOVECTOR;

	int								m_nDelCount;//¼±ÅÃ°Ç¼ö//

	//IMAGES
	Graphics::TBitmap *BITMAP_BTN_FIND[2];
	Graphics::TBitmap *BITMAP_BTN_DELETE[2];
	Graphics::TBitmap *BITMAP_BTN_REGIST[2];

	void __fastcall funcSetWaitWindows(bool bSetValue);
	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();


	void __fastcall func_readExcelToWriteDB(AnsiString sFileName);
    bool __fastcall funcCheckRawExcelData();

	void __fastcall funcInitStringGrid();
	void __fastcall funcDispStringGrid();

	void __fastcall funcWriteFileVectorLog(int _nIndex);

    void __fastcall funcReadKeywordMemoInfo(AnsiString _asKeyword);
    void __fastcall funcDeleteMemoInfo();

	__fastcall TfrmMemoBatch(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemoBatch *frmMemoBatch;
//---------------------------------------------------------------------------
#endif
