//---------------------------------------------------------------------------
// [260515]
// 설명 : 구대장 한글 번역을 위한 AI OCR API 관리
//
//---------------------------------------------------------------------------


#include <vcl.h>
#pragma hdrstop

#include <SysUtils.hpp>              // FileExists, IntToStr, Exception
#include <Classes.hpp>               // TStringStream
#include <IdHTTP.hpp>
#include <IdMultipartFormData.hpp>
//#include <IdSSLOpenSSL.hpp>
//#include <System.SysUtils.hpp>
#include <IdGlobal.hpp>        // EIdSocketError 등 Indy 예외
#include <IdException.hpp>           // EIdException
#include <IdComponent.hpp>           // Indy base exceptions
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "common.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#pragma warn -8004
#pragma warn -8021	//Handler for 'const EIdHTTPProtocolException &' hidden by previous handler for 'const EIdException &'  Full parser context
#pragma warn -8070	//Function should return a value

classAIOCR *eAIOCR;
//---------------------------------------------------------------------------
classAIOCR::classAIOCR()
{
}
//---------------------------------------------------------------------------
classAIOCR::~classAIOCR()
{
	OutputDebugStringA("~classAIOCR\n");
}
//---------------------------------------------------------------------------

//===========================================================================
// 현재 열람중인 파일 경로(임시)를 보내어 번역을 요청한다.//
// AFileName : tmp\\파일명 경로//
// return JSON File 내용(String)//
//===========================================================================
String classAIOCR::SendOCRImage(const String& AFileName)
{
//	String url = L"http://192.168.123.6:8080/ocr/image";
	String url = L"http://118.217.247.240:4880/ocr/image";
	TIdHTTP *Http = NULL;
	TIdMultiPartFormDataStream *FormData = NULL;
//    TIdSSLIOHandlerSocketOpenSSL *SSL = NULL;

	try
	{
		try{
			if (!FileExists(AFileName))
				throw Exception(L"파일이 존재하지 않습니다: " + AFileName);

			AnsiString  asJsonFile = ExtractFileName(AFileName);
			asJsonFile = ExtractFilePath(AFileName) + asJsonFile.SubString(1, asJsonFile.Pos(".")-1) + ".json";

			TStringList *slResult = new TStringList();
			Http = new TIdHTTP(NULL);
			FormData = new TIdMultiPartFormDataStream();

			Http->ReadTimeout = 60000;
			Http->ConnectTimeout = 10000;

			Http->Request->UserAgent = L"C++Builder2010 OCR Client";
			Http->Request->ContentType = L"multipart/form-data";

			FormData->AddFile(L"file", AFileName, L"application/octet-stream");

			String responseText = Http->Post(url, FormData);
			slResult->Text = responseText;
			slResult->SaveToFile(asJsonFile, TEncoding::UTF8);

			try
			{
				//ParseJsonToDoc08His(asJsonFile, frmMain->m_nPathListSeqNo);
				AnsiString outTxtPath;
				AnsiString outErrMsg;
				RunMyJsonBridge(asJsonFile, outTxtPath, outErrMsg);

				if(frmMain->m_bSUBBOOK)//부책//
					LoadJsonTextToOwnInfo(outTxtPath, frmMain->m_nPathListSeqNo);
				else//공유지연명부//
					LoadJsonTextToShareOwn(outTxtPath, frmMain->m_nPathListSeqNo);
			}
			// Indy 소켓/네트워크 오류: Exception 기반 처리
			catch (const EIdException &e)
			{
				String msg = String(e.Message);
				int wsErr = WSAGetLastError();  // Winsock 오류 코드

				String userMsg;
				if (msg.Pos("10038") > 0 || wsErr == 10038)
					userMsg = L"소켓 오류 10038: 이미 닫혔거나 유효하지 않는 소켓입니다.";
				else if (msg.Pos("10054") > 0 || wsErr == 10054)
					userMsg = L"서버와의 연결이 강제로 끊어졌습니다.";
				else if (msg.Pos("10060") > 0 || wsErr == 10060)
					userMsg = L"서버 응답 시간 초과입니다.";
				else
					userMsg = L"네트워크 오류: " + msg;

				throw Exception(L"OCR 요청 중 오류가 발생했습니다.\r\n" + userMsg);
			}
			// HTTP 프로토콜 오류
			catch (const EIdHTTPProtocolException &e)
			{
				throw Exception(L"OCR 서버 HTTP 오류\r\nStatus: " + IntToStr(e.ErrorCode) + L"\r\n" + e.ErrorMessage);
			}
			// 그 외 일반 예외
			catch (const Exception &e)
			{
				throw Exception(L"OCR 요청 실패\r\n" + e.Message);
			}

			delete slResult;
			return responseText;
		}
		__finally
		{
			delete FormData;
			delete Http;
	//        delete SSL;
		}
	}
	catch (const EIdHTTPProtocolException &e)
	{
		String err;
		err += L"OCR 서버 요청 실패\r\n";
		err += L"HTTP Status: " + IntToStr(e.ErrorCode) + L"\r\n";
		err += L"Response: " + e.ErrorMessage;
		throw Exception(err);
	}
	catch (const Exception &e)
	{
		throw Exception(L"OCR 요청 중 오류가 발생했습니다.\r\n" + e.Message);
	}

	return "";
}
//---------------------------------------------------------------------------

//===========================================================================
// MyJsonBridge 프로그램 실행하기//
//===========================================================================
bool classAIOCR::RunMyJsonBridge(const AnsiString& jsonFileNameOnly, AnsiString& outTxtPath, AnsiString& outErrMsg)
{
    outErrMsg = "";
    outTxtPath = "";

	AnsiString  asDir   = frmMain->ROOTPATH;
	AnsiString  asExePath  = asDir + "MyJsonBridge.exe";
	AnsiString  asJsonPath = jsonFileNameOnly;
	AnsiString  asJsonFile = ExtractFileName(asJsonPath);
	AnsiString  asTxtPath  = frmMain->TMPPATH + asJsonFile.SubString(1, asJsonFile.Pos(".")-1) + ".txt";

	if (!FileExists(asExePath))
    {
		outErrMsg = "MyJsonBridge.exe 파일이 없습니다: " + asExePath;
        return false;
	}

    if (!FileExists(asJsonPath))
    {
        outErrMsg = "입력 JSON 파일이 없습니다: " + asJsonPath;
        return false;
	}

    // "MyJsonBridge.exe" "tempAIOCR.json" "result_protocol.txt"
    AnsiString cmdLine =
		"\"" + asExePath + "\" " +
		"\"" + asJsonPath + "\" " +
        "\"" + asTxtPath + "\"";

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    // CreateProcess는 command line 버퍼를 수정할 수 있으므로
    // 수정 가능한 char 배열을 준비
    char cmdBuf[2048];
    memset(cmdBuf, 0, sizeof(cmdBuf));
    strncpy(cmdBuf, cmdLine.c_str(), sizeof(cmdBuf) - 1);
    cmdBuf[sizeof(cmdBuf) - 1] = '\0';

    BOOL ok = CreateProcessA(
        NULL,           // lpApplicationName
        cmdBuf,         // lpCommandLine
        NULL,           // lpProcessAttributes
        NULL,           // lpThreadAttributes
        FALSE,          // bInheritHandles
        0,              // dwCreationFlags
        NULL,           // lpEnvironment
        asDir.c_str(),  // lpCurrentDirectory
        &si,            // lpStartupInfo
        &pi             // lpProcessInformation
    );

    if (!ok)
    {
        outErrMsg = "CreateProcess 실패. GetLastError=" + IntToStr((int)GetLastError());
        return false;
    }

    DWORD waitRc = WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    if (waitRc != WAIT_OBJECT_0)
    {
        outErrMsg = "MyJsonBridge 종료 대기 실패";
        return false;
    }

    if (exitCode != 0)
    {
        outErrMsg = "MyJsonBridge 비정상 종료. ExitCode=" + IntToStr((int)exitCode);
        return false;
    }

    if (!FileExists(asTxtPath))
    {
		outErrMsg = "결과 파일이 생성되지 않았습니다: " + asTxtPath;
        return false;
    }

	outTxtPath = asTxtPath;
    return true;
}
//---------------------------------------------------------------------------

void classAIOCR::CopyToFixed(char* dest, int destSize, const AnsiString& src)
{
	if (!dest || destSize <= 0) return;
	memset(dest, 0, destSize);
	strncpy(dest, src.c_str(), destSize - 1);
	dest[destSize - 1] = '\0';
}

AnsiString classAIOCR::UnescapeField(const AnsiString& s)
{
    AnsiString r;
    int i = 1;
    while (i <= s.Length())
    {
        char ch = s[i];
        if (ch == '\\' && i < s.Length())
        {
            char next = s[i + 1];
            if (next == '|')      { r += '|';  i += 2; continue; }
            else if (next == 'n') { r += "\r\n"; i += 2; continue; }
            else if (next == '\\'){ r += '\\'; i += 2; continue; }
        }
		r += ch;
        ++i;
    }
    return r;
}

void classAIOCR::SplitProtocolLine(const AnsiString& line, std::vector<AnsiString>& outFields)
{
    outFields.clear();
    AnsiString token;
    bool escape = false;

    for (int i = 1; i <= line.Length(); ++i)
    {
        char ch = line[i];

        if (escape)
        {
            token += '\\';
            token += ch;
            escape = false;
            continue;
        }

        if (ch == '\\')
        {
            escape = true;
            continue;
        }

        if (ch == '|')
        {
            outFields.push_back(UnescapeField(token));
            token = "";
        }
        else
        {
            token += ch;
        }
    }

    outFields.push_back(UnescapeField(token));
}

//===========================================================================
// 파싱한 Json 결과 Text를 Vector에 저장하기//
//===========================================================================
bool classAIOCR::LoadJsonTextToOwnInfo(const AnsiString& fileName, int pathlistSeqNo)
{
	//초기화//
	e08DataAIOCR->m_vOldLandDocInfo.clear();
	e08DataAIOCR->m_ResultDoc08His.clear();
	e08DataAIOCR->m_ResultDoc08OwnInfo.clear();

	if (!FileExists(fileName))
		return false;
	//
	TStringList* sl = new TStringList;
	try
	{
		sl->LoadFromFile(fileName);

		for (int i = 0; i < sl->Count; ++i)
		{
			AnsiString line = Trim(sl->Strings[i]);
			if (line.IsEmpty())
				continue;

			std::vector<AnsiString> f;
			SplitProtocolLine(line, f);

			if (f.size() == 0)
				continue;

			if (f[0] == "ETC")
			{
				// 형식: Y|col|jimok|jijeok|gwase1|gwase2|yeonhyeok
				if (f.size() < 7) continue;

				OLDLANDDOC_INFO_STRUCT row;
				memset(&row, 0, sizeof(row));

				e08DataAIOCR->m_asLand = f[1];
				e08DataAIOCR->m_asJibun = f[3];
				e08DataAIOCR->m_asLevel = f[5];
				e08DataAIOCR->m_asMemo = f[7];

				CopyToFixed(row.PNU_NAME,  sizeof(row.PNU_NAME),  f[3]);
				CopyToFixed(row.LEVEL,  sizeof(row.LEVEL),  f[5]);
				CopyToFixed(row.MEMO, sizeof(row.MEMO), f[7]);

				e08DataAIOCR->m_vOldLandDocInfo.push_back(row);
			}
			else if (f[0] == "Y")
			{
				// 형식: Y|col|jimok|jijeok|gwase1|gwase2|yeonhyeok
				if (f.size() < 7) continue;

				DOCUMENT08_HIS_STRUCT row;
				memset(&row, 0, sizeof(row));

				row.PATHLIST_SEQNO = pathlistSeqNo;
				row.SEQ = StrToIntDef(f[1], 0);

				CopyToFixed(row.JIMOK,   sizeof(row.JIMOK),   f[2]);
				CopyToFixed(row.AREA,    sizeof(row.AREA),    f[3]);
				//260529//[TODO]//#ReqToCode1System//'기준수확량' 앞뒤 [] 문자 제거 요청하기//
				f[4] = StringReplace(f[4], "[", "", TReplaceFlags() << rfReplaceAll);
				f[4] = StringReplace(f[4], "]", "", TReplaceFlags() << rfReplaceAll);
				CopyToFixed(row.VALUE1,  sizeof(row.VALUE1),  f[4]);
				CopyToFixed(row.VALUE2,  sizeof(row.VALUE2),  f[5]);
				CopyToFixed(row.HISTORY, sizeof(row.HISTORY), f[6]);

//				AnsiString eraCode, hisDate;
//				ParseHistoryDate(f[6], eraCode, hisDate);
//				CopyToFixed(row.ERA_CODE, sizeof(row.ERA_CODE), eraCode);
//				CopyToFixed(row.HIS_DATE, sizeof(row.HIS_DATE), hisDate);

				e08DataAIOCR->m_ResultDoc08His.push_back(row);
			}
			else if (f[0] == "S")
			{
				// 형식: S|col|date|sago|bohap|juso|name
				if (f.size() < 7) continue;

				DOCUMENT08_OWNINFO_STRUCT row;
				memset(&row, 0, sizeof(row));

				row.PATHLIST_SEQNO = pathlistSeqNo;
				row.SEQ = StrToIntDef(f[1], 0);

//				AnsiString eraCode, hisDate;
//				ParseOwnerDate(f[2], eraCode, hisDate);
//				CopyToFixed(row.ERA_CODE,    sizeof(row.ERA_CODE),    eraCode);
				CopyToFixed(row.HIS_DATE,    sizeof(row.HIS_DATE),    f[2]);
				CopyToFixed(row.REASON,      sizeof(row.REASON),      f[3]);
				CopyToFixed(row.OWN_ADDRESS, sizeof(row.OWN_ADDRESS), f[5]);
				CopyToFixed(row.OWN_NAME,    sizeof(row.OWN_NAME),    f[6]);

				e08DataAIOCR->m_ResultDoc08OwnInfo.push_back(row);
			}
		}

		return true;
	}
	__finally
	{
		delete sl;
	}
}
//---------------------------------------------------------------------------

bool classAIOCR::LoadJsonTextToShareOwn(const AnsiString& fileName, int pathlistSeqNo)
{
	//초기화//
	e08DataAIOCR->m_vOldLandDocInfo.clear();
	e08DataAIOCR->m_ResultDoc08ShareOwn.clear();

	if (!FileExists(fileName))
		return false;
	//
	TStringList* sl = new TStringList;
	try
	{
		sl->LoadFromFile(fileName);

		int nSkipCnt = 0;
		for (int i = 0; i < sl->Count; ++i)
		{
			AnsiString line = Trim(sl->Strings[i]);
			if (line.IsEmpty())
				continue;

			std::vector<AnsiString> f;
			SplitProtocolLine(line, f);

			if (f.size() == 0)
				continue;

			if (f[0] == "ETC")
			{
				// 형식: Y|col|jimok|jijeok|gwase1|gwase2|yeonhyeok
				if (f.size() < 7) continue;

				OLDLANDDOC_INFO_STRUCT row;
				memset(&row, 0, sizeof(row));

				e08DataAIOCR->m_asLand = f[1];
				e08DataAIOCR->m_asJibun = f[3];
				e08DataAIOCR->m_asLevel = f[5];
				e08DataAIOCR->m_asMemo = f[7];

				CopyToFixed(row.PNU_NAME,  sizeof(row.PNU_NAME),  f[3]);
				CopyToFixed(row.LEVEL,  sizeof(row.LEVEL),  f[5]);
				CopyToFixed(row.MEMO, sizeof(row.MEMO), f[7]);

				e08DataAIOCR->m_vOldLandDocInfo.push_back(row);
			}
			else if (f[0] == "S")
			{
				// 형식: S|col|date|sago|bohap|juso|name
				if (f.size() < 7) continue;

				DOCUMENT08_SHAREOWN_STRUCT row;
				memset(&row, 0, sizeof(row));

				row.PATHLIST_SEQNO = pathlistSeqNo;

				//공유지연명부-[TODO]서식지에 따라 한 라인에 12, 13까지 존재할 수 있어서//
				//12, 13, 25, 26을 없으면 공란으로 두었다.
				//그리는 곳에서 위 INDEX 데이터를 SKIP 하므로, 여기서도 공간으로 채운다//
				if(i == 14 || i == 25)
				{
					row.SEQ = StrToIntDef(f[1], 0) + nSkipCnt;
					e08DataAIOCR->m_ResultDoc08ShareOwn.push_back(row);
					nSkipCnt++;
					row.SEQ = StrToIntDef(f[1], 0) + nSkipCnt;
					e08DataAIOCR->m_ResultDoc08ShareOwn.push_back(row);
					nSkipCnt++;
				}

				{
					row.SEQ = StrToIntDef(f[1], 0) + nSkipCnt;
	//				AnsiString eraCode, hisDate;
	//				ParseOwnerDate(f[2], eraCode, hisDate);
	//				CopyToFixed(row.ERA_CODE,    sizeof(row.ERA_CODE),    eraCode);
					CopyToFixed(row.HIS_DATE,    sizeof(row.HIS_DATE),    f[2]);
					CopyToFixed(row.REASON,      sizeof(row.REASON),      f[3]);
					CopyToFixed(row.RATIO,       sizeof(row.RATIO),       f[4]);
					CopyToFixed(row.OWN_ADDRESS, sizeof(row.OWN_ADDRESS), f[5]);
					CopyToFixed(row.OWN_NAME,    sizeof(row.OWN_NAME),    f[6]);
					e08DataAIOCR->m_ResultDoc08ShareOwn.push_back(row);
				}
			}
		}

		return true;
	}
	__finally
	{
		delete sl;
	}
}
//---------------------------------------------------------------------------

