//---------------------------------------------------------------------------

#ifndef untAboutH
#define untAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <GIFImg.hpp>
#include <MPlayer.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TPanel *panCenter;
	TMemo *memVerReleaseNote;
	TPanel *panTop;
	TLabel *lblTop;
	TBevel *Bevel1;
	TLabel *lblITKorea;
	TLabel *lblEmail;
	TLabel *lblVersion;
	TImage *Image2;
	TButton *btnClose;
	TButton *btnRelese;
	TLabel *lblBuild;
	TPanel *panWindowsMove;
	TImage *Image3;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TShape *shpBG;
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnReleseClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);

private:	// User declarations

	struct TransArray
	{
		WORD LanguageID, CharacterSet;
	};
	DWORD VerInfo, VerSize;
	HANDLE MemHandle;
	LPVOID MemPtr, BufferPtr;
	UINT BufferLength;
	TransArray *Array;
	char QueryBlock[255];
	String FFileVersion;


public:		// User declarations

	AnsiString asBuildTimeMsg;

	void __fastcall 	getExeCreationTime();
	//231015//GetFileVersion
	// this one of the methods which have errors
	String __fastcall 	GetFileVersion();
	void __fastcall 	funcGetFileVersion();


	void __fastcall funcReadReleaseFile();


	__fastcall TfrmAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
#endif
