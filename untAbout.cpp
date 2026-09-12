//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
	: TForm(Owner)
{
	//======================================================================
	//241204//#전주#중앙정보테크//
	//======================================================================
	if(frmMain->_SKINCOLOR_ > 0)
	{
		int R	= GetRValue(frmMain->_SKINCOLOR_);
		int G	= GetGValue(frmMain->_SKINCOLOR_);
		int B	= GetBValue(frmMain->_SKINCOLOR_);

		//shpBG->Pen->Color//
		this->shpBG->Pen->Color				= (TColor)RGB(R, G, B);
		//shpWait->Pen->Color//
		//panWindowsMove->Color//
		this->panWindowsMove->Color			= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
	if (dynamic_cast<TGIFImage *>(Image2->Picture->Graphic)!=NULL)
		((TGIFImage *)Image2->Picture->Graphic)->Animate = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::FormShow(TObject *Sender)
{
	frmAbout->Height = 150;

	//Minji_#00_About
	getExeCreationTime();
	lblBuild->Caption = asBuildTimeMsg;

	//231015//GetFileVersion
	funcGetFileVersion();
	AnsiString  asStr	= frmMain->SIDOINI->ReadString("INFO", "VERSION", "");
	if( asStr.IsEmpty() )
		lblVersion->Caption = "Version " + FFileVersion;
	else
		lblVersion->Caption = "Version " + asStr;


//	if (DF_DBGMODE == 2) {
//		lblBuild->Caption = lblBuild->Caption + L" View";
//    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::btnCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
//Minji_#00_About
void __fastcall TfrmAbout::getExeCreationTime()
{
    TSearchRec sr;
	AnsiString asPath = frmMain->ROOTPATH + "LandArchive.exe";
    int nRet = FindFirst(asPath, faDirectory, sr);

    if(nRet == 0) {
		_FILETIME ftLoacl;
        SYSTEMTIME stTime;

        //FileTimeToLocalFileTime(&sr.FindData.ftCreationTime, &ftLoacl);
		//FileTimeToLocalFileTime(&sr.FindData.ftLastAccessTime, &ftLoacl);
		FileTimeToLocalFileTime(&sr.FindData.ftLastWriteTime, &ftLoacl);
		FileTimeToSystemTime(&ftLoacl, &stTime);

		asBuildTimeMsg.printf("%04d%02d%02d.%02d%02d%02d.%03d",   stTime.wYear,
                                                                stTime.wMonth,
                                                                stTime.wDay,
                                                                stTime.wHour,
                                                                stTime.wMinute,
                                                                stTime.wSecond,
                                                                stTime.wMilliseconds);

		//TDateTime dtTime = SystemTimeToDateTime(stTime);

        FindClose(sr);
    }
}
//---------------------------------------------------------------------------

//231015//GetFileVersion
// this one of the methods which have errors
String __fastcall TfrmAbout::GetFileVersion(void)
{
	String Result ;
	BufferPtr = NULL ;

	// Get the product version.
	wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\FileVersion",
					Array[0].LanguageID, Array[0].CharacterSet);
	VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);

	if(BufferPtr) Result = (char *)BufferPtr;

	return(Result);
}
//---------------------------------------------------

//231015//GetFileVersion
void __fastcall TfrmAbout::funcGetFileVersion()
{
	VerSize = GetFileVersionInfoSize(AnsiString(Application->ExeName).c_str(), &VerInfo);
	if (VerSize > 0) {
		MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
		MemPtr = GlobalLock(MemHandle);
		GetFileVersionInfo(AnsiString(Application->ExeName).c_str(), VerInfo, VerSize, MemPtr);
		VerQueryValue(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr,
								&BufferLength);
		Array = (TransArray *)BufferPtr;

		FFileVersion = GetFileVersion();
	}
}
//---------------------------------------------------

void __fastcall TfrmAbout::btnReleseClick(TObject *Sender)
{

	if (frmAbout->Height == 150)
		frmAbout->Height = 420;
	else
		frmAbout->Height = 150;

	memVerReleaseNote->Clear();//v1.0.0.9//250114//

	funcReadReleaseFile();

/*	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"프로그램명 : 지적문서통합관리시스템");
	memVerReleaseNote->Lines->Add(L"개발담당자 : ITKorea(itkinfo@daum.net, 070-7525-8077)");
	memVerReleaseNote->Lines->Add(L"자세한 문의 사항은 기재된 연락처로 문의 바랍니다.");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"[Build 20150921.1011]");
	memVerReleaseNote->Lines->Add(L"계정 추가 등급 오류 수정");
	memVerReleaseNote->Lines->Add(L"프린트 BIT 모드 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"[Build 20160721.0020]");
	memVerReleaseNote->Lines->Add(L"비법인등록대장 검색조건 추가");
	memVerReleaseNote->Lines->Add(L"비법인등록코드 이미지 처리 오류수정");
	memVerReleaseNote->Lines->Add(L"좌표계산부 문서 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"[Build 20160727.1631]");
	memVerReleaseNote->Lines->Add(L"이동지 결의서 그룹처리 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"[Build 20161203.1221]");
	memVerReleaseNote->Lines->Add(L"공시지가 보존문서 추가");
	memVerReleaseNote->Lines->Add(L"세종시 구지번 변환기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"[Build 20170102.0037]");
	memVerReleaseNote->Lines->Add(L"부분확대 기능 추가");
	memVerReleaseNote->Lines->Add(L"축척정보 수동입력 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"[Build 20170109.2103]");
	memVerReleaseNote->Lines->Add(L"감마조절 기능 추가");
	memVerReleaseNote->Lines->Add(L"주소코드 검색기능 추가");
	memVerReleaseNote->Lines->Add(L"최소운용자등급 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.4.1 [Build 20170115.2313]");
	memVerReleaseNote->Lines->Add(L"태안군청 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.4.2 [Build 20170118.2119]");
	memVerReleaseNote->Lines->Add(L"태안군청 구대장 기본문서 컬러문서로 설정");
	memVerReleaseNote->Lines->Add(L"태안군 주소코드 검색 오류 수정");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.4.3 [Build 20170204.0552]");
	memVerReleaseNote->Lines->Add(L"측량결과도 권번호 항목을 VOL_NO로 수정");
	memVerReleaseNote->Lines->Add(L"Tip 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.5.2 [Build 20170207.2205]");
	memVerReleaseNote->Lines->Add(L"이미지 연산방식 변경");
	memVerReleaseNote->Lines->Add(L"이미지 연산메모리의 환경설정 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.5.3 [Build 20170210.0018]");
	memVerReleaseNote->Lines->Add(L"폐쇄지적등본 발급 영역 설정 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.5.4 [Build 20170213.1258]");
	memVerReleaseNote->Lines->Add(L"폐쇄지적등본 발급 영역 넓이 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.5.5 [Build 20170222.1127]");
	memVerReleaseNote->Lines->Add(L"부번 미입력시 검색 방법 지정 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.5.6 [Build 20170315.0530]");
	memVerReleaseNote->Lines->Add(L"검색결과창의 노드 처리 방식 지정 기능 추가");
	memVerReleaseNote->Lines->Add(L"연대환산기능내 텍스트 오류 수정");
	memVerReleaseNote->Lines->Add(L"그룹내 동일 주소 처리 방식 지정 기능 추가");
	memVerReleaseNote->Lines->Add(L"이미지 연산메모리 설정 기본값 4000으로 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER1.5.7 [Build 20170328.2017]");
	memVerReleaseNote->Lines->Add(L"당진시청 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.5.8 [Build 20170328.2308]");
	memVerReleaseNote->Lines->Add(L"이동결의서 그룹 처리 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.5.9 [Build 20170410.1424]");
	memVerReleaseNote->Lines->Add(L"돋보기 위치 오류 수정");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.0 [Build 20170419.1340]");
	memVerReleaseNote->Lines->Add(L"MSSQL 연결 수용");
	memVerReleaseNote->Lines->Add(L"이동결의서 PATH_NAME 정렬 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.1 [Build 20170425.1617]");
	memVerReleaseNote->Lines->Add(L"검색, 지번초기화, 지적도보기 버튼 수정");
	memVerReleaseNote->Lines->Add(L"폐쇄지적도 축척검색 수정");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.4 [Build 20170517.0948]");
	memVerReleaseNote->Lines->Add(L"측량결과도 축척 정보 미입력시 오류 수정");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.5 [Build 20170517.1529]");
	memVerReleaseNote->Lines->Add(L"구대장 컬러 이미지 누락시 흑백이미지로 자동 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.6 [Build 20170518.0945]");
	memVerReleaseNote->Lines->Add(L"페이지 앞뒤 페이지 이동 오류 수정");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.7 [Build 20170518.0945]");
	memVerReleaseNote->Lines->Add(L"이동지 집계표 정리 방식 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.8 [Build 20170704.1647]");
	memVerReleaseNote->Lines->Add(L"측량결과도 문서구분 추가");
	memVerReleaseNote->Lines->Add(L"지적도 문서구분 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.6.9 [Build 20170707.1102]");
	memVerReleaseNote->Lines->Add(L"세종시 지적도 검색 방법 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.7.0 [Build 20170717.1815]");
	memVerReleaseNote->Lines->Add(L"당진시 구대장 기본문서(컬러)로 변경");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.7.1 [Build 20170830.1444]");
	memVerReleaseNote->Lines->Add(L"서북구청 측정기능 폰트 설정 기능 추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.7.2 [Build 20170830.1633]");
	memVerReleaseNote->Lines->Add(L"서북구청 측량 KIND CODE 기본 측량으로 처리");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.8.7 [Build 20180417.0956]");
	memVerReleaseNote->Lines->Add(L"환경설정에 검색조건옵션추가 & FTP경로 ROOTDIR 기본설정");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.8.7 [Build 20180611.0911]");
	memVerReleaseNote->Lines->Add(L"FTP 서버정보 2 기능추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.8.7 [Build 20180629.1000]");
	memVerReleaseNote->Lines->Add(L"자동로그아웃 기능추가");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.8.8 [Build 20180813.1000]");
	memVerReleaseNote->Lines->Add(L"토지이동 기능추가 & 출력/음영조정기능 개선");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.9.0 [Build 20181119.0921]");
	memVerReleaseNote->Lines->Add(L"지적불부합지 UI 변경 및 기능개선");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.9.3 [Build 20190507.1000]");
	memVerReleaseNote->Lines->Add(L"프린트 기능 개선");

	memVerReleaseNote->Lines->Add(L"");
	memVerReleaseNote->Lines->Add(L"VER 1.9.4 [Build 20190612.1024]");
	memVerReleaseNote->Lines->Add(L"지적도 지번 표시 기능개선");
*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::funcReadReleaseFile()
{
	FILE *pFile;
	AnsiString fname = frmMain->ROOTPATH + "_ReleaseNotes_.txt";
	if(FileExists(fname))
	{
		pFile = fopen(fname.c_str(),"rb");
		if(pFile != NULL)
		{
			char strTemp[255];
			char *pStr;

			while( !feof(pFile) )
			{
				pStr = fgets( strTemp, sizeof(strTemp), pFile);
				//memVerReleaseNote->Lines->Add( pStr );
				memVerReleaseNote->Lines->Append( pStr );
            }
        }
		fclose( pFile );
	}

	/*
  pFile = fopen ( "myfile.bin" , "rb" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  // the whole file is now loaded in the memory buffer.

  // terminate
  fclose (pFile);
  free (buffer);
  return 0;
	*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

