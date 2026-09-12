//---------------------------------------------------------------------------

#ifndef untFtpControlH
#define untFtpControlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//#include "common.h"
#include "mainSrc.h"

//---------------------------------------------------------------------------

typedef struct{
	char cFileName[255];
	char cPathName[255];
	char cFullPath[255];
} FileInfo;

typedef struct{
	int nCurrentIndex;
	vector<FileInfo> mvFileInfo;
} FTPFILELIST;

class TfrmFtpControl : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations


	HINTERNET m_hSession;
	HINTERNET m_hFtpConn;

	AnsiString		m_asUPPER;//PATH_NAME 찾을 때 기본 UPPER를 한다. FTP 178 접근 시 대소문자 구별하여 기능 넣음.//DB는 대문자, FTP는 소문자로 되어 있었음.


	bool __fastcall FuncFtpConnect(int _nFTPType);
	bool __fastcall FuncFtpOpenFile(int _nDocNum, AnsiString _asPath, int _nDirType, char *_cDstFile);
	bool __fastcall FuncFtpGetFile(int _nDocNum, AnsiString _asPath, int _nDirType, char *_cDstFile);

	bool __fastcall FuncFtpFileUpload(int _gbn, FTP_FILE_STRUCT* _mUplaoFile, int _nType);
	bool __fastcall FuncFtpFileDownload(int _gbn, FTP_FILE_STRUCT* _mDownFile, int _nType);
	bool __fastcall FuncFtpFileDelete(int _gbn, FTP_FILE_STRUCT* _mDeleteFile);


	//250428//_bAll (True) : 전체 미리보기, (False) : 페이지단위로 보기
	bool __fastcall FuncFtpGetFileThumb(bool _bAll);
	void __fastcall FuncFtpOpenFileThumb();
	void __fastcall FuncFtpOpenFileThumbAll();//250428//[Add]전체 미리보기(REQ)

	bool TfrmFtpControl::funcCheckFtpNetworkInfo();

	void __fastcall FuncCloseSession();


	//==========================================================================
	// COPY_LMREQ_TO_ONESTOP
	//==========================================================================
	AnsiString	ONESTOP_FTPROOT;
	AnsiString 	ONESTOP_FTPIP;
	AnsiString 	ONESTOP_FTPPORT;
	AnsiString 	ONESTOP_FTPID;
	AnsiString 	ONESTOP_FTPPW;
	AnsiString 	ONESTOP_CONSTYLE;//constyle
	AnsiString  ONESTOP_UPPER;//

	HINTERNET m_hSessionOneStop;
	HINTERNET m_hFtpConnOneStop;
	bool __fastcall FuncFtpConnectOneStop();
	void __fastcall FuncCloseSessionOneStop();
	bool __fastcall FuncFtpFileUploadOneStop(int _gbn, FTP_FILE_STRUCT* _mUplaoFile, int _nType);


	__fastcall TfrmFtpControl(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFtpControl *frmFtpControl;
//---------------------------------------------------------------------------
#endif
