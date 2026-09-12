//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//#include "untFtpControl.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8070
#pragma warn -8004
//#pragma warn -8012

TfrmFtpControl *frmFtpControl;
//---------------------------------------------------------------------------
__fastcall TfrmFtpControl::TfrmFtpControl(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmFtpControl::FuncFtpConnect(int _nFTPType)//181231//FTP//
{
	m_hSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (m_hSession == NULL)
	{
		AnsiString strMsg = "현재 이미지 서버에 연결할 수 없습니다.(Open)";
		frmMsg->funcMessageDlg("이미지 연결 확인:", strMsg, 3);
		return false;
	}

	if (frmMain->INIINFO.CONSTYLE == "ACTIVE")
		m_hFtpConn= InternetConnect(m_hSession, frmMain->INIINFO.FTPIP.c_str(), frmMain->INIINFO.FTPPORT.ToInt(), frmMain->INIINFO.FTPID.c_str(), frmMain->INIINFO.FTPPW.c_str(), INTERNET_SERVICE_FTP, 0/*INTERNET_FLAG_ACTIVE*/, 0);//ACTIVE MODE
	else
		m_hFtpConn= InternetConnect(m_hSession, frmMain->INIINFO.FTPIP.c_str(), frmMain->INIINFO.FTPPORT.ToInt(), frmMain->INIINFO.FTPID.c_str(), frmMain->INIINFO.FTPPW.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE , 0);//PASSIVE MODE

	if(m_hFtpConn == NULL)
	{
		InternetCloseHandle(m_hSession);
		m_hSession = NULL;
		AnsiString strMsg = "현재 이미지 서버에 연결할 수 없습니다.(Connect)";
		frmMsg->funcMessageDlg("이미지 연결 확인:", strMsg, 3);
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmFtpControl::FuncFtpOpenFile(int _nDocNum, AnsiString _asPath, int _nDirType, char *_cDstFile)//181231//FTP//
{
	bool result = false;
	bool bSuccess = false;
	AnsiString srcFile, dstFile;
	AnsiString srcFileJGW, dstFileJGW;//190221
	AnsiString asFullPath;//190123
	AnsiString asPath;
	AnsiString asFileName;
	AnsiString asFileExt;
	int pos;

	//delete file of local temp directoy to download
	if(_nDirType == 1)//
		eFunc->funcDeleteDir(false, frmMain->TMPPATH);//201229//tmp 폴더를 삭제하고 다시 생성하니 시점차이가 생겨 오류발생//
	else if(_nDirType == 2)//print
		eFunc->funcDeleteDir(false, frmMain->PRINTPATH);//201229//tmp 폴더를 삭제하고 다시 생성하니 시점차이가 생겨 오류발생//
	//200105//THUMBNAIL은 계속 받아야하므로 개별적으로 폴더 지우지 않는다.
//	else if(_nDirType == 3)//thumbnail
//		eFunc->funcDeleteDir(frmMain->THUMBPATH);

//	AnsiString  asTarget = "";
//	asTarget.sprintf("DOCUMENT%02d", _nDocNum);
//	if (asTarget.IsEmpty())
//		asFullPath = _asPath;
//	else
//		asFullPath = StringReplace(_asPath, (asTarget + "\\"), "", TReplaceFlags()<<rfReplaceAll);

	AnsiString  asTarget = "";
	int	nPos = _asPath.Pos("\\");
	if(nPos > 0)
	{
		asTarget = _asPath.SubString(1, nPos-1);
		asFullPath = StringReplace(_asPath, (asTarget + "\\"), "", TReplaceFlags()<<rfReplaceAll);
	}
	else
	{
		asFullPath = _asPath;
	}

	asPath     	= asFullPath.UpperCase();//190123
	asPath     	= asFullPath;//190123
	asFileName  = ExtractFileName(asPath);
	asFileExt   = ExtractFileExt(asFileName);
	asPath      = ExtractFilePath(asPath);

	//190116//if(_nDocNum != 19)
	//{
		if (asPath.Pos("\\") != 1)
			asPath = "\\" + asPath;
	//}

	TReplaceFlags flags;
	flags << rfReplaceAll;
	asPath = StringReplace(asPath, "\\", "/", flags);
	asPath = asPath.SubString(1, asPath.Length() - 1);
	srcFile = asFileName;

	if (_nDirType == 1)
		dstFile = frmMain->TMPPATH;
	else if (_nDirType == 2)
		dstFile = frmMain->PRINTPATH;
	else if (_nDirType == 3)
		dstFile = frmMain->THUMBPATH;

	//Local Temp Dir
	if (!DirectoryExists(dstFile))
		CreateDir(dstFile);
	dstFile = dstFile + ExtractFileName(asFileName);
	wsprintf(_cDstFile, dstFile.c_str());

	if(m_hSession == NULL || m_hFtpConn == NULL)
	{
		if( !FuncFtpConnect(1/*FTP1*/) )
			return false;

		if(m_hSession == NULL || m_hFtpConn == NULL)
		{
			return false;
		}
	}

	//Set Dir
	AnsiString root    = "";
	if (_nDirType == 3)
		root = frmMain->INIINFO.FTPROOT + "THUMB/" + asTarget;
	else
		root = frmMain->INIINFO.FTPROOT + asTarget;

	bSuccess = FtpSetCurrentDirectory(m_hFtpConn, (root + asPath).c_str());
	if (!bSuccess)
	{
		if (_nDirType != 3)//191127
		{
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		}
		return false;
	}

	//Open File
	HINTERNET hFile;

	//201014//if (frmMain->_SIDOCODE == "44825" || frmMain->_SIDOCODE == "31710")//태안, 울주//Linux//
	//201014//192.168.123.178 지원부 데이터서버 접속//대소문자구별//
	if (/*frmMain->_SIDOCODE == "44825" ||*/ frmMain->_SIDOCODE == "31710" || m_asUPPER == "1")//태안, 울주//Linux
	{
		for(int i = 0; i < 5; i++)
		{
			AnsiString asTempPath 		= "";
			AnsiString asTempFileName 	= "";
			AnsiString asTempFileExt 	= "";
			int pos = 0;

			if (i == 0)	{//original
				asTempPath     	= asFullPath;//190123
				asTempFileName  = ExtractFileName(asTempPath);
				asTempFileExt   = ExtractFileExt(asTempFileName);
				srcFile = asTempFileName;
			}
			else if (i == 1) {//filename is upper, extension is upper
				asTempPath     	= asFullPath;//190123
				asTempFileName  = ExtractFileName(asTempPath.UpperCase());
				srcFile = asTempFileName;//upper + upper
			}
			else if (i == 2) {//filename is upper, extension is lower
				asTempPath     	= asFullPath;//190123
				asTempFileName  = ExtractFileName(asTempPath.UpperCase());
				asTempFileExt   = ExtractFileExt(asTempPath.LowerCase());
				pos = asTempFileName.Pos(".");
				if (pos > 0) {
					asTempFileName = asTempFileName.SubString(1, pos-1);
				}
				srcFile	= asTempFileName + asTempFileExt;//upper + lower
			}
			else if (i == 3) {//filename is lower, extension is upper
				asTempPath     	= asFullPath;//190123
				asTempFileName  = ExtractFileName(asTempPath.LowerCase());
				asTempFileExt   = ExtractFileExt(asTempPath.UpperCase());
				pos = asTempFileName.Pos(".");
				if (pos > 0) {
					asTempFileName = asTempFileName.SubString(1, pos-1);
				}
				srcFile	= asTempFileName + asTempFileExt;
			}
			else if (i == 4) {//filename is lower, extension is lower
				asTempPath     	= asFullPath;//190123
				asTempFileName  = ExtractFileName(asTempPath.LowerCase());
				srcFile	= asTempFileName;
			}

			hFile = FtpOpenFileA(m_hFtpConn, srcFile.c_str(), GENERIC_READ, INTERNET_FLAG_TRANSFER_BINARY, 0);
			if (hFile == NULL)
			{
				if(i == 4)//when try to open opened-file again, error sometimes. Then try to connect again in FuncFtpGetFile.
				{
					if (_nDirType != 3)//191127
					{
						AnsiString strMsg = "현재 연결된 이미지 서버에서 이미지 파일을 찾을 수 없습니다.";
						frmMsg->funcMessageDlg("이미지파일 확인:", strMsg, 3);
					}
					return false;
				}
			}
			else//file exist
				break;
		}
	}
	else//Windows 사용 시군//
	{
		hFile = FtpOpenFileA(m_hFtpConn, srcFile.c_str(), GENERIC_READ, INTERNET_FLAG_TRANSFER_BINARY, 0);
		if (hFile == NULL)
		{
			if (_nDirType != 3)//191127
			{
				AnsiString strMsg = "현재 연결된 이미지 서버에서 이미지 파일을 찾을 수 없습니다.";
				frmMsg->funcMessageDlg("이미지파일 확인:", strMsg, 3);
			}
			return false;
		}
	}

	//Download File
	BYTE Buff[65536]={0,};
	DWORD dwRead = 0;
	FILE* fp = NULL;
	int nBufCount = 0;
	//fp = fopen(dstFile.c_str(), "wb+"); //이어받기 또는 일반 다운로드 파일생성
	fp = fopen(_cDstFile, "wb+"); //이어받기 또는 일반 다운로드 파일생성
	do {
		if (InternetReadFile(hFile, Buff, 65536, &dwRead) == FALSE)//파일데이터를 읽어옴
		{
			fclose(fp);
			InternetCloseHandle(hFile);
			hFile = NULL;
			return false;
		}
		fwrite(Buff, dwRead, 1, fp);
		nBufCount++;
	} while (dwRead > 0);

	fclose(fp);
	InternetCloseHandle(hFile);
	hFile = NULL;

	//==========================================================================
	//_nDocNum = 2 -> Check if JGW file exists ---------------------------------
	//==========================================================================
	if(_nDocNum == 2)
	{
		AnsiString asTempPath 		= asFullPath;

		//Open File
		HINTERNET hFile;
		for(int i = 0; i < 5; i++)
		{
			AnsiString asTempFileName 	= "";
			AnsiString asTempFileExt 	= ".jgw";
			int pos = 0;

			if (i == 0)	{//original
				asTempFileName  = ExtractFileName(asTempPath);
				asTempFileExt   = ExtractFileExt(asTempFileExt);
			}
			else if (i == 1) {//filename is upper, extension is upper
				asTempFileName  = ExtractFileName(asTempPath.UpperCase());
				asTempFileExt   = ExtractFileExt(asTempFileExt.UpperCase());
			}
			else if (i == 2) {//filename is upper, extension is lower
				asTempFileName  = ExtractFileName(asTempPath.UpperCase());
				asTempFileExt   = ExtractFileExt(asTempFileExt.LowerCase());
			}
			else if (i == 3) {//filename is lower, extension is upper
				asTempFileName  = ExtractFileName(asTempPath.LowerCase());
				asTempFileExt   = ExtractFileExt(asTempFileExt.UpperCase());
			}
			else if (i == 4) {//filename is lower, extension is lower
				asTempFileName  = ExtractFileName(asTempPath.LowerCase());
				asTempFileExt   = ExtractFileExt(asTempFileExt.LowerCase());
			}

			pos = asTempFileName.Pos(".");
			if (pos > 0) {
				asTempFileName = asTempFileName.SubString(1, pos-1);
			}
			srcFileJGW	= asTempFileName + asTempFileExt;

			hFile = FtpOpenFileA(m_hFtpConn, srcFileJGW.c_str(), GENERIC_READ, INTERNET_FLAG_TRANSFER_BINARY, 0);
			if (hFile == NULL)
			{
				if(i == 4)//when try to open opened-file again, error sometimes. Then try to connect again in FuncFtpGetFile.
				{
					frmMain->bJGWExists = false;
				}
			}
			else//file exist
			{
				frmMain->bJGWExists = true;
				break;
			}
		}

		if(frmMain->bJGWExists)
		{
			frmMain->asTmpFileNameJGW = frmMain->ROOTPATH + "tmp\\" + ExtractFileName(srcFileJGW);

			//Download File
			BYTE Buff[65536]={0,};
			DWORD dwRead = 0;
			FILE* fp = NULL;
			int nBufCount = 0;
			//fp = fopen(dstFile.c_str(), "wb+"); //이어받기 또는 일반 다운로드 파일생성
			fp = fopen(frmMain->asTmpFileNameJGW.c_str(), "wb+"); //이어받기 또는 일반 다운로드 파일생성
			do {
				if (InternetReadFile(hFile, Buff, 65536, &dwRead) == FALSE)//파일데이터를 읽어옴
				{
					fclose(fp);
					InternetCloseHandle(hFile);
					hFile = NULL;
					return false;
				}
				fwrite(Buff, dwRead, 1, fp);
				nBufCount++;
			} while (dwRead > 0);

			fclose(fp);
			InternetCloseHandle(hFile);
			hFile = NULL;
		}
	}
	//==========================================================================


	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmFtpControl::FuncFtpGetFile(int _nDocNum, AnsiString _asPath, int _nDirType, char *_cDstFile)//181231//FTP//
{
//	//201204//TEST
//	if(frmMain->INIINFO.B_FTPUSE == false)
//	{
//		AnsiString  asSrcPathName	= "";
//		AnsiString  asDstPathName	= "";
//		AnsiString  asFileName		= "";
//
//		if(_nDirType == 1)//
//		{
//			eFunc->funcDeleteDir(frmMain->TMPPATH);
//			asDstPathName	= frmMain->TMPPATH;
//		}
//		else if(_nDirType == 2)//print
//		{
//			eFunc->funcDeleteDir(frmMain->PRINTPATH);
//			asDstPathName	= frmMain->PRINTPATH;
//		}
//
//	    if (!DirectoryExists(asDstPathName))
//		    CreateDir(asDstPathName);
//
//		asSrcPathName	= frmMain->INIINFO.FTPROOT + "\\" + _asPath;
//		asSrcPathName	= StringReplace(asSrcPathName, "/", "", TReplaceFlags() << rfReplaceAll);
//		if(FileExists(asSrcPathName))
//		{
//			asFileName	= ExtractFileName(asSrcPathName);
//			asDstPathName	= asDstPathName	+ asFileName;
//			CopyFile(asSrcPathName.c_str(), asDstPathName.c_str(), false);
//			wsprintf(_cDstFile, asDstPathName.c_str());
//		}
//
//		if(FileExists(asDstPathName))
//			return true;
//
//		return false;
//	}

	bool result = false;
	bool bSuccess = false;

	if(m_hSession == NULL || m_hFtpConn == NULL)
	{
		if( !FuncFtpConnect(1/*FTP1*/) )
			return false;

		if(m_hSession == NULL || m_hFtpConn == NULL)
		{
			return false;
		}
	}

	result = FuncFtpOpenFile(_nDocNum, _asPath, _nDirType, _cDstFile);
	if(result == false)//open failed
	{
		FuncCloseSession();//190124//한참 후에 다시 문서 오픈하면 폴더 찾을 수 없다고 나와서 Session 종료함.
		return result;
	}

	FuncCloseSession();//190124//한참 후에 다시 문서 오픈하면 폴더 찾을 수 없다고 나와서 Session 종료함.

	return true;
}
//---------------------------------------------------------------------------
//
// _nType : do not care at all
//
bool __fastcall TfrmFtpControl::FuncFtpFileUpload(int _gbn, FTP_FILE_STRUCT* _mUplaoFile, int _nType)
{
	bool bResult = false;
	bool bSuccess = false;

	HINTERNET hFile;

	AnsiString asFullPath;
	AnsiString asPath;
	AnsiString asFileName;
	AnsiString asFileExt;

	asFullPath 	= _mUplaoFile->cLocalFilePath;
	if( strcmp(_mUplaoFile->cFileName, "") == 0 )//190410
		asFileName  = ExtractFileName(asFullPath);
	else
		asFileName = _mUplaoFile->cFileName;

	asFileExt   = ExtractFileExt(asFileName);
	asPath      = ExtractFilePath(asFullPath);

	if( !FuncFtpConnect(1) )//181231//FTP//
		return false;

	if(m_hSession == NULL || m_hFtpConn == NULL)
	{
		if( !FuncFtpConnect(1) )
			return false;
	}

	AnsiString asRemoteRoot;
	//201215// 디렉토리 확인 후 생성//
	asRemoteRoot.printf("%s%s", frmMain->INIINFO.FTPROOT, _mUplaoFile->cTarget);
	bSuccess = FtpSetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str());
	if (!bSuccess) {
		// 디렉토리 생성
		bSuccess = FtpCreateDirectory(m_hFtpConn, asRemoteRoot.c_str());
		if (!bSuccess) {
			FuncCloseSession();
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 생성할 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
			return false;
		}
	}

	// 디렉토리 이동
	asRemoteRoot.printf("%s%s/%s", frmMain->INIINFO.FTPROOT, _mUplaoFile->cTarget, _mUplaoFile->cIndexPolder);
	bSuccess = FtpSetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str());
	if (!bSuccess) {
		// 디렉토리 생성
		bSuccess = FtpCreateDirectory(m_hFtpConn, asRemoteRoot.c_str());
		if (!bSuccess) {
			FuncCloseSession();
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 생성할 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
			return false;
		}

		bSuccess = FtpSetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str());
		if (!bSuccess)
		{
			FuncCloseSession();
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
			return false;
		}
	}

	//wsprintf(_mUplaoFile->cRemoteFilePath, asRemoteRoot.c_str());
	wsprintf(_mUplaoFile->cRemoteFilePath, "%s/%s", _mUplaoFile->cTarget, _mUplaoFile->cIndexPolder);

	// 현재 디렉토리 확인
	unsigned long temp_Length = INTERNET_MAX_PATH_LENGTH;
	if(!FtpGetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str(), &temp_Length) ) //현재 FTP 디렉토리 가져오기(temp_path)
	{
		FuncCloseSession();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		return false;
	}

	// 파일 오픈
	hFile = FtpOpenFileA(m_hFtpConn, asFileName.c_str(), GENERIC_WRITE, FTP_TRANSFER_TYPE_BINARY, 0);
	if (hFile == NULL)
	{
		FuncCloseSession();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 이미지 파일을 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지파일 확인:", strMsg, 3);
		return false;
	}

	wsprintf(_mUplaoFile->cFileName, asFileName.c_str());

	Wininet::INTERNET_BUFFERS        iBuf = {0};
	iBuf.dwStructSize = sizeof(Wininet::INTERNET_BUFFERS);

	//  local file open
	HANDLE hLocalFile;
	hLocalFile = CreateFile(asFullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLocalFile == INVALID_HANDLE_VALUE)
	{
		FuncCloseSession();
		AnsiString strMsg = "로컬 파일을 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
		return false;
	}

	DWORD dwFileSize;
	DWORD dwFilePos=0;
	DWORD dwRead;
	dwFileSize = GetFileSize(hLocalFile, NULL);
	iBuf.dwBufferTotal = dwFileSize;

	char buf[512];
	DWORD cnt=0;
	dwFilePos = 0;

	DWORD dwWritten = 0;
	DWORD err = 0;

	bResult = true;
	do {
		SetFilePointer(hLocalFile, dwFilePos, NULL, FILE_BEGIN);

		if (!ReadFile(hLocalFile, buf, sizeof(buf), &dwRead, NULL))
		{
			AnsiString strMsg = "로컬 파일을 로드 할 수 없습니다.";
			frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
			bResult = false;
			break;
		};

		InternetSetFilePointer(hFile, dwFilePos, NULL, FILE_BEGIN, 0 );
		if (!InternetWriteFile(hFile, buf, dwRead, &dwWritten))
		{
			err = GetLastError();
			if (err == 87) {
				bResult = true;
				break;
			}
			AnsiString strMsg = "로컬 파일 쓰기에 실패하였습니다.";
			frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
			bResult = false;
			break;
		};
		dwFilePos += dwWritten;
	}
	while (dwRead == sizeof(buf));

	CloseHandle(hLocalFile);
	InternetCloseHandle(hFile);
	hFile = NULL;

	FuncCloseSession();//181231//FTP//
	return bResult;
}
//---------------------------------------------------------------------------
//
bool __fastcall TfrmFtpControl::FuncFtpFileDownload(int _gbn, FTP_FILE_STRUCT* _mDownFile, int _nType)
{
	bool bSuccess = false;
	AnsiString asDstDir;
	AnsiString asDstFile;
	asDstFile = _mDownFile->cLocalFilePath;
	AnsiString asRemoteRoot;

	asDstFile = _mDownFile->cLocalFilePath;
	asDstDir  = ExtractFilePath(asDstFile);

	//frmFuncUnit->FuncCreateDir(asDstDir);
	AnsiString asFileName = ExtractFileName(_mDownFile->cLocalFilePath);
	if( asFileName.IsEmpty() )
		asDstFile.printf("%s%s", _mDownFile->cLocalFilePath, _mDownFile->cFileName);

	if(m_hSession == NULL || m_hFtpConn == NULL)
	{
		if( !FuncFtpConnect(1/*FTP1*/) )
		return false;
	}

	FileInfo    mTempFileInfo;
	asRemoteRoot.printf("%s%s", frmMain->INIINFO.FTPROOT, _mDownFile->cRemoteFilePath);
	bSuccess = FtpSetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str());
	if (!bSuccess) {
		FuncCloseSession();//181231//FTP//
		AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		return false;
	}

	// 현재 디렉토리 확인
	unsigned long temp_Length = INTERNET_MAX_PATH_LENGTH;
	if(!FtpGetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str(), &temp_Length) ) //현재 FTP 디렉토리 가져오기(temp_path)
	{
		FuncCloseSession();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		return false;
	}

	HINTERNET hFile;
	hFile = FtpOpenFileA(m_hFtpConn, _mDownFile->cFileName, GENERIC_READ, INTERNET_FLAG_TRANSFER_BINARY, 0);
	if (hFile == NULL)
	{
		FuncCloseSession();//181231//FTP//
		AnsiString strMsg = "현재 연결된 이미지 서버에서 이미지 파일을 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지파일 확인:", strMsg, 3);
		return false;
	}

	//check file exist//190829//그룹파일 저장 시에만 사용//
//	if( frmMain->m_bGroupSave && FileExists(asDstFile) )
//	{
//		if (Application->MessageBox(L"같은 이름의 파일이 존재합니다. 덮어쓰기할까요?", L"확 인", MB_YESNO) == IDNO)
//		{
//			InternetCloseHandle(hFile);
//			hFile = NULL;
//			FuncCloseSession();//181231//FTP//
//			Application->ProcessMessages();
//			return false;
//		}
//	}

	//파일 다운로드
	BYTE Buff[65536]={0,};
	DWORD dwRead = 0;
	FILE* fp = NULL;
	fp = fopen(asDstFile.c_str(), "wb+"); //이어받기 또는 일반 다운로드 파일생성
	if (fp == NULL) {
		AnsiString strMsg = "로컬 파일 생성에 오류가 발생하였습니다.";
		frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
		return false;
	}

	do
	{
		if (InternetReadFile(hFile, Buff, 65536, &dwRead) == FALSE)//파일데이터를 읽어옴
		{
			fclose(fp);
			InternetCloseHandle(hFile);
			hFile = NULL;
			FuncCloseSession();//181231//FTP//
			return false;
		}
		fwrite(Buff, dwRead, 1, fp);
	} while (dwRead > 0);

	fclose(fp);
	InternetCloseHandle(hFile);
	hFile = NULL;
	FuncCloseSession();
	//200103//메모첨부 다운로드 받다가 에러발생//Application->ProcessMessages();
	return true;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmFtpControl::FuncFtpFileDelete(int _gbn, FTP_FILE_STRUCT* _mDeleteFile)
{
	bool bSuccess = false;

	if( !FuncFtpConnect(1) )
		return false;

	if(m_hSession == NULL || m_hFtpConn == NULL)
	{
		if( !FuncFtpConnect(1) )
			return false;
	}

	// To DO
	AnsiString asRemoteRoot;
	// 디렉토리 이동
	asRemoteRoot.printf("%s%s/%s", frmMain->INIINFO.FTPROOT, _mDeleteFile->cTarget, _mDeleteFile->cIndexPolder);
	bSuccess = FtpSetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str());
	if (!bSuccess)
	{
		FuncCloseSession();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		return false;
	}

	wsprintf(_mDeleteFile->cRemoteFilePath, "%s/%s", _mDeleteFile->cTarget, _mDeleteFile->cIndexPolder);

	// 현재 디렉토리 확인
	unsigned long temp_Length = INTERNET_MAX_PATH_LENGTH;
	if(!FtpGetCurrentDirectory(m_hFtpConn, asRemoteRoot.c_str(), &temp_Length) ) //현재 FTP 디렉토리 가져오기(temp_path)
	{
    	FuncCloseSession();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		return false;
	}

	// 파일 오픈
	bSuccess = FtpDeleteFile(m_hFtpConn, _mDeleteFile->cFileName);
	if ( !bSuccess )
	{
		FuncCloseSession();
		AnsiString strMsg = "현재 연결된 서버에서 파일을 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지파일 확인:", strMsg, 3);
		return false;
	}

	FuncCloseSession();
	return bSuccess;
}
//---------------------------------------------------------------------------

bool TfrmFtpControl::funcCheckFtpNetworkInfo()
{
	bool bValue = false;

	if (frmMain->INIINFO.FTPIP != "" && frmMain->INIINFO.FTPID != "" && frmMain->INIINFO.FTPPW != "" && frmMain->INIINFO.FTPPORT != "")
	{
		bValue = true;
	}

	return bValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmFtpControl::FormClose(TObject *Sender, TCloseAction &Action)//181231//FTP//
{
	//FuncCloseSession();
}
//---------------------------------------------------------------------------
void __fastcall TfrmFtpControl::FuncCloseSession()//181231//FTP//
{
	if(m_hFtpConn != NULL)
	{
		InternetCloseHandle(m_hFtpConn);//세션 종료
		m_hFtpConn = NULL;
	}
	if(m_hSession != NULL)
	{
		InternetCloseHandle(m_hSession);//세션 종료
		m_hSession = NULL;
	}
}
//---------------------------------------------------------------------------

//250428//_bAll (True) : 전체 미리보기, (False) : 페이지단위로 보기
bool __fastcall TfrmFtpControl::FuncFtpGetFileThumb(bool _bAll)
{
	bool result = false;
	bool bSuccess = false;

	if(m_hSession == NULL || m_hFtpConn == NULL)
	{
		if( !FuncFtpConnect(1/*FTP1*/) )
			return false;
	}

	if(_bAll)
		FuncFtpOpenFileThumbAll();
	else
		FuncFtpOpenFileThumb();

	FuncCloseSession();//190124//한참 후에 다시 문서 오픈하면 폴더 찾을 수 없다고 나와서 Session 종료함.

	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmFtpControl::FuncFtpOpenFileThumb()
{
	bool 		result 				= false;
	bool 		bSuccess 			= false;
	AnsiString  root    			= "";
	AnsiString 	asRemotePathName    = "";
	AnsiString 	asLocalPathName 	= "";
	AnsiString 	asRemoteTargetDir   = "";
	AnsiString 	asFileName          = "";
	AnsiString 	asFileExt 	        = "";

	if(frmMain->INI_AS_THUMBEXT	== "JPG")
		asFileExt 	= ".jpg";
	else
		asFileExt 	= ".bmp";

	for(int i = frmMain->m_nThumbSttIdx; i < frmMain->m_nThumbSttIdx + frmMain->m_nThumbDownCnt; i++)
	{
		//Remote PathName
		asRemotePathName = (char *)frmMain->m_vThumbPathList[i].PATH_NAME;
		//Common Only FileName
		asFileName = ExtractFileName(asRemotePathName);
		asFileName	= asFileName.SubString(1, asFileName.Pos(".")-1) + asFileExt;
		//Local PathName
		asLocalPathName = frmMain->THUMBPATH + asFileName;

		if(FileExists(asLocalPathName))//download 받지 않은 thumbnail 만 받는다//
		{
			frmMain->m_nThumbDownloadedCnt++;//201014//
			continue;
		}

		//Remote Dir
   		asRemoteTargetDir = ExtractFilePath(asRemotePathName);

		asRemoteTargetDir = StringReplace(asRemoteTargetDir, "\\", "/", TReplaceFlags() << rfReplaceAll);
    	asRemoteTargetDir = asRemoteTargetDir.SubString(1, asRemoteTargetDir.Length() - 1);

    	//Change Dir
		root = frmMain->INIINFO.FTPROOT + "THUMB/" + asRemoteTargetDir;
		bSuccess = FtpSetCurrentDirectory(m_hFtpConn, root.c_str());
		if(!bSuccess)
			continue;

    	//Open File
		HINTERNET hFile;
		hFile = FtpOpenFileA(m_hFtpConn, asFileName.c_str(), GENERIC_READ, INTERNET_FLAG_TRANSFER_BINARY, 0);
    	if (hFile == NULL)
		{
			frmMain->m_nThumbDownloadedCnt++;//201201//
			continue;
		}

    	//Download File
		BYTE Buff[65536]={0,};
    	DWORD dwRead = 0;
    	FILE* fp = NULL;
    	int nBufCount = 0;
    	fp = fopen(asLocalPathName.c_str(), "wb+"); //이어받기 또는 일반 다운로드 파일생성
    	do {
    		if (InternetReadFile(hFile, Buff, 65536, &dwRead) == FALSE)//파일데이터를 읽어옴
    		{
    			fclose(fp);
    			InternetCloseHandle(hFile);
    			hFile = NULL;
    			continue;
    		}
			fwrite(Buff, dwRead, 1, fp);
    		nBufCount++;
    	} while (dwRead > 0);

    	fclose(fp);
    	InternetCloseHandle(hFile);
		hFile = NULL;

		frmMain->m_nThumbDownloadedCnt++;//201014//
	}
	//==========================================================================
}
//---------------------------------------------------------------------------

//250428//[Add]전체 미리보기(REQ)
void __fastcall TfrmFtpControl::FuncFtpOpenFileThumbAll()
{
	bool 		result 				= false;
	bool 		bSuccess 			= false;
	AnsiString  root    			= "";
	AnsiString 	asRemotePathName    = "";
	AnsiString 	asLocalPathName 	= "";
	AnsiString 	asRemoteTargetDir   = "";
	AnsiString 	asFileName          = "";
	AnsiString 	asFileExt 	        = "";

	if(frmMain->INI_AS_THUMBEXT	== "JPG")
		asFileExt 	= ".jpg";
	else
		asFileExt 	= ".bmp";

	for(int i = 0; i < (int)frmMain->m_vThumbPathList.size(); i++)
	{
		//Remote PathName
		asRemotePathName = (char *)frmMain->m_vThumbPathList[i].PATH_NAME;
		//Common Only FileName
		asFileName = ExtractFileName(asRemotePathName);
		asFileName	= asFileName.SubString(1, asFileName.Pos(".")-1) + asFileExt;
		//Local PathName
		asLocalPathName = frmMain->THUMBPATH + asFileName;

		if(FileExists(asLocalPathName))//download 받지 않은 thumbnail 만 받는다//
		{
			frmMain->m_nThumbDownloadedCnt++;//201014//
			continue;
		}

		//Remote Dir
   		asRemoteTargetDir = ExtractFilePath(asRemotePathName);

		asRemoteTargetDir = StringReplace(asRemoteTargetDir, "\\", "/", TReplaceFlags() << rfReplaceAll);
    	asRemoteTargetDir = asRemoteTargetDir.SubString(1, asRemoteTargetDir.Length() - 1);

    	//Change Dir
		root = frmMain->INIINFO.FTPROOT + "THUMB/" + asRemoteTargetDir;
		bSuccess = FtpSetCurrentDirectory(m_hFtpConn, root.c_str());
		if(!bSuccess)
			continue;

    	//Open File
		HINTERNET hFile;
		hFile = FtpOpenFileA(m_hFtpConn, asFileName.c_str(), GENERIC_READ, INTERNET_FLAG_TRANSFER_BINARY, 0);
    	if (hFile == NULL)
		{
			frmMain->m_nThumbDownloadedCnt++;//201201//
			continue;
		}

    	//Download File
		BYTE Buff[65536]={0,};
    	DWORD dwRead = 0;
    	FILE* fp = NULL;
    	int nBufCount = 0;
    	fp = fopen(asLocalPathName.c_str(), "wb+"); //이어받기 또는 일반 다운로드 파일생성
    	do {
    		if (InternetReadFile(hFile, Buff, 65536, &dwRead) == FALSE)//파일데이터를 읽어옴
    		{
    			fclose(fp);
    			InternetCloseHandle(hFile);
    			hFile = NULL;
    			continue;
    		}
			fwrite(Buff, dwRead, 1, fp);
    		nBufCount++;
    	} while (dwRead > 0);

    	fclose(fp);
    	InternetCloseHandle(hFile);
		hFile = NULL;

		frmMain->m_nThumbDownloadedCnt++;//201014//
	}
	//==========================================================================
}
//---------------------------------------------------------------------------

//==========================================================================
// COPY_LMREQ_TO_ONESTOP
//==========================================================================
bool __fastcall TfrmFtpControl::FuncFtpConnectOneStop()
{
	ONESTOP_FTPROOT		= frmMain->SIDOINI->ReadString(L"ONESTOP_FTP", L"ROOT", L"/");
	ONESTOP_FTPIP		= frmMain->SIDOINI->ReadString(L"ONESTOP_FTP", L"IP", L"");
	ONESTOP_FTPIP		= frmMain->func_Decoder(ONESTOP_FTPIP);
	ONESTOP_FTPPORT		= frmMain->SIDOINI->ReadString(L"ONESTOP_FTP", L"PORT", L"");//21
	ONESTOP_FTPPORT		= frmMain->func_Decoder(ONESTOP_FTPPORT);
	ONESTOP_FTPID		= frmMain->SIDOINI->ReadString(L"ONESTOP_FTP", L"ID", L"");
	ONESTOP_FTPID		= frmMain->func_Decoder(ONESTOP_FTPID);
	ONESTOP_FTPPW		= frmMain->SIDOINI->ReadString(L"ONESTOP_FTP", L"PW", L"");
	ONESTOP_FTPPW		= frmMain->func_Decoder(ONESTOP_FTPPW);
	ONESTOP_CONSTYLE	= frmMain->SIDOINI->ReadString("ONESTOP_FTP", "CONSTYLE", "ACTIVE");
	ONESTOP_UPPER		= frmMain->SIDOINI->ReadString(L"ONESTOP_FTP", L"UPPER", L"1");

	m_hSessionOneStop = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (m_hSessionOneStop == NULL)
	{
		AnsiString strMsg = "현재 이미지 서버에 연결할 수 없습니다.(Open)";
		frmMsg->funcMessageDlg("이미지 연결 확인:", strMsg, 3);
		return false;
	}

	if (ONESTOP_CONSTYLE == "ACTIVE")
		m_hFtpConnOneStop = InternetConnect(m_hSessionOneStop, ONESTOP_FTPIP.c_str(), ONESTOP_FTPPORT.ToInt(), ONESTOP_FTPID.c_str(), ONESTOP_FTPPW.c_str(), INTERNET_SERVICE_FTP, 0/*INTERNET_FLAG_ACTIVE*/, 0);//ACTIVE MODE
	else
		m_hFtpConnOneStop = InternetConnect(m_hSessionOneStop, ONESTOP_FTPIP.c_str(), ONESTOP_FTPPORT.ToInt(), ONESTOP_FTPID.c_str(), ONESTOP_FTPPW.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE , 0);//PASSIVE MODE

	if(m_hFtpConnOneStop == NULL)
	{
		InternetCloseHandle(m_hSessionOneStop);
		m_hSessionOneStop = NULL;
		AnsiString strMsg = "현재 이미지 서버에 연결할 수 없습니다.(Connect)";
		frmMsg->funcMessageDlg("이미지 연결 확인:", strMsg, 3);
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmFtpControl::FuncCloseSessionOneStop()
{
	if(m_hFtpConnOneStop != NULL)
	{
		InternetCloseHandle(m_hFtpConnOneStop);//세션 종료
		m_hFtpConnOneStop = NULL;
	}
	if(m_hSessionOneStop != NULL)
	{
		InternetCloseHandle(m_hSessionOneStop);//세션 종료
		m_hSessionOneStop = NULL;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TfrmFtpControl::FuncFtpFileUploadOneStop(int _gbn, FTP_FILE_STRUCT* _mUplaoFile, int _nType)
{
	bool bResult = false;
	bool bSuccess = false;

	HINTERNET hFile;

	AnsiString asFullPath;
	AnsiString asPath;
	AnsiString asFileName;
	AnsiString asFileExt;

	asFullPath 	= _mUplaoFile->cLocalFilePath;
	if( strcmp(_mUplaoFile->cFileName, "") == 0 )
		asFileName  = ExtractFileName(asFullPath);
	else
		asFileName = _mUplaoFile->cFileName;

	asFileExt   = ExtractFileExt(asFileName);
	asPath      = ExtractFilePath(asFullPath);

	if( !FuncFtpConnectOneStop() )
		return false;

	if(m_hSessionOneStop == NULL || m_hFtpConnOneStop == NULL)
	{
		if( !FuncFtpConnectOneStop() )
			return false;
	}

	AnsiString asRemoteRoot;
	//201215// 디렉토리 확인 후 생성//
	asRemoteRoot.printf("%s%s", ONESTOP_FTPROOT, _mUplaoFile->cTarget);
	bSuccess = FtpSetCurrentDirectory(m_hFtpConnOneStop, asRemoteRoot.c_str());
	if (!bSuccess) {
		// 디렉토리 생성
		bSuccess = FtpCreateDirectory(m_hFtpConnOneStop, asRemoteRoot.c_str());
		if (!bSuccess) {
			FuncCloseSessionOneStop();
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 생성할 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
			return false;
		}
	}

	// 디렉토리 이동
	asRemoteRoot.printf("%s%s/%s", ONESTOP_FTPROOT, _mUplaoFile->cTarget, _mUplaoFile->cIndexPolder);
	bSuccess = FtpSetCurrentDirectory(m_hFtpConnOneStop, asRemoteRoot.c_str());
	if (!bSuccess) {
		// 디렉토리 생성
		bSuccess = FtpCreateDirectory(m_hFtpConnOneStop, asRemoteRoot.c_str());
		if (!bSuccess) {
			FuncCloseSessionOneStop();
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 생성할 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
			return false;
		}

		bSuccess = FtpSetCurrentDirectory(m_hFtpConnOneStop, asRemoteRoot.c_str());
		if (!bSuccess)
		{
			FuncCloseSessionOneStop();
			AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
			frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
			return false;
		}
	}

	//wsprintf(_mUplaoFile->cRemoteFilePath, asRemoteRoot.c_str());
	wsprintf(_mUplaoFile->cRemoteFilePath, "%s/%s", _mUplaoFile->cTarget, _mUplaoFile->cIndexPolder);

	// 현재 디렉토리 확인
	unsigned long temp_Length = INTERNET_MAX_PATH_LENGTH;
	if(!FtpGetCurrentDirectory(m_hFtpConnOneStop, asRemoteRoot.c_str(), &temp_Length) ) //현재 FTP 디렉토리 가져오기(temp_path)
	{
		FuncCloseSessionOneStop();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 지정된 폴더를 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지 경로 확인:", strMsg, 3);
		return false;
	}

	// 파일 오픈
	hFile = FtpOpenFileA(m_hFtpConnOneStop, asFileName.c_str(), GENERIC_WRITE, FTP_TRANSFER_TYPE_BINARY, 0);
	if (hFile == NULL)
	{
		FuncCloseSessionOneStop();
		AnsiString strMsg = "현재 연결된 이미지 서버에서 이미지 파일을 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("이미지파일 확인:", strMsg, 3);
		return false;
	}

	wsprintf(_mUplaoFile->cFileName, asFileName.c_str());

	Wininet::INTERNET_BUFFERS        iBuf = {0};
	iBuf.dwStructSize = sizeof(Wininet::INTERNET_BUFFERS);

	//  local file open
	HANDLE hLocalFile;
	hLocalFile = CreateFile(asFullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hLocalFile == INVALID_HANDLE_VALUE)
	{
		FuncCloseSessionOneStop();
		AnsiString strMsg = "로컬 파일을 찾을 수 없습니다.";
		frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
		return false;
	}

	DWORD dwFileSize;
	DWORD dwFilePos=0;
	DWORD dwRead;
	dwFileSize = GetFileSize(hLocalFile, NULL);
	iBuf.dwBufferTotal = dwFileSize;

	char buf[512];
	DWORD cnt=0;
	dwFilePos = 0;

	DWORD dwWritten = 0;
	DWORD err = 0;

	bResult = true;
	do {
		SetFilePointer(hLocalFile, dwFilePos, NULL, FILE_BEGIN);

		if (!ReadFile(hLocalFile, buf, sizeof(buf), &dwRead, NULL))
		{
			AnsiString strMsg = "로컬 파일을 로드 할 수 없습니다.";
			frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
			bResult = false;
			break;
		};

		InternetSetFilePointer(hFile, dwFilePos, NULL, FILE_BEGIN, 0 );
		if (!InternetWriteFile(hFile, buf, dwRead, &dwWritten))
		{
			err = GetLastError();
			if (err == 87) {
				bResult = true;
				break;
			}
			AnsiString strMsg = "로컬 파일 쓰기에 실패하였습니다.";
			frmMsg->funcMessageDlg("Local File 확인:", strMsg, 3);
			bResult = false;
			break;
		};
		dwFilePos += dwWritten;
	}
	while (dwRead == sizeof(buf));

	CloseHandle(hLocalFile);
	InternetCloseHandle(hFile);
	hFile = NULL;

	FuncCloseSessionOneStop();//181231//FTP//
	return bResult;
}
//---------------------------------------------------------------------------
