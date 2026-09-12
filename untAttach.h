//---------------------------------------------------------------------------

#ifndef untAttachH
#define untAttachH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmAttach : public TForm
{
__published:	// IDE-managed Components
	TAdvStringGrid *sgAttach;
	TPanel *pnlMain;
	TPanel *pnlAttachT;
	TPanel *pnlAttachB;
	TButton *btnUpload;
	TComboBox *cboKindCode;
	TPanel *Panel1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall sgAttachDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall sgAttachGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall btnUploadClick(TObject *Sender);
	void __fastcall cboKindCodeClick(TObject *Sender);
	void __fastcall sgAttachClickCell(TObject *Sender, int ARow, int ACol);

private:	// User declarations

	char* buffer;
	void __fastcall WMDropFiles(TWMDropFiles &message);

public:		// User declarations

	//======================================================================
	//파일드래그//
	//======================================================================
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(0x0049, TWMDropFiles, WMDropFiles);//WM_COPYGLOBALDATA
		VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles,WMDropFiles)
	END_MESSAGE_MAP(TForm);

	int m_nSelectGridIndex;//210106//



	//======================================================================
	//이미지로딩//
	//======================================================================
	Graphics::TBitmap 					*BITMAP_BTN_DEL;
	void __fastcall 					funcLoadButtonImage();
	void __fastcall 					funcDeleteButtonImage();

	//======================================================================
	//화면갱신//
	//======================================================================
	void __fastcall 					funcRefreshShow();

	//======================================================================
	//m_vLMREQ_ATTACH.index, size//
	//======================================================================
	int									m_nAttachCount;
	int									m_nAttachIndex;


	//======================================================================
	//sgAttach 그리기//
	//======================================================================
	void __fastcall 					funcCreateAttach();
	void __fastcall 					funcInitAttach();
	void __fastcall 					funcDispAttach();

	//======================================================================
	//LONGBLOB 데이터 업로드//
	//======================================================================
	bool __fastcall 					funcAttachPutBinaryData(int _nType, int _nSeqNo, AnsiString _asKindCode, AnsiString _asFileName, LONG _lFileSize);

	//======================================================================
	//파일 삭제, 열기//
	//======================================================================
	void __fastcall 					funcDeleteSelectFile(int _nIndex);
	void __fastcall 					funcDeleteAll();
	void __fastcall 					funcOpenExplorer(AnsiString _asPathName);


	//======================================================================
	//콤보리스트//
	//======================================================================
	TRect 								cboRect;//문서종류 선택 콤보박스//
	void __fastcall 					funcSetComboList();
	//void __fastcall 					sgAttachCombobox_OnClick(TObject *Sender);


	void __fastcall 					funcUpdateAttachCount();

	//======================================================================
	//콤보리스트//
	//======================================================================
	bool								bUploading;



	__fastcall TfrmAttach(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAttach *frmAttach;
//---------------------------------------------------------------------------
#endif
