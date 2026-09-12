//---------------------------------------------------------------------------

#ifndef untAIOCRH
#define untAIOCRH
//---------------------------------------------------------------------------
class classAIOCR
{
private:
public:
	classAIOCR();
	~classAIOCR();

	//===========================================================================
	// 현재 열람중인 파일 경로(임시)를 보내어 번역을 요청한다.//
	// AFileName : tmp\\파일명 경로//
	// return JSON File 내용(String)//
	//===========================================================================
	String classAIOCR::SendOCRImage(const String& AFileName);

	//===========================================================================
	// 지정한 크기만큼 Json Text 복사하기//
	//===========================================================================
	void classAIOCR::SafeStrCopy(char* dest, int destSize, const AnsiString& src);

	//===========================================================================
	// JSON 파일 열기
	// return : 파일 내용 text
	//===========================================================================
	AnsiString classAIOCR::LoadJsonFileText(const String& fileName);

	void classAIOCR::CopyToFixed(char* dest, int destSize, const AnsiString& src);
	AnsiString classAIOCR::UnescapeField(const AnsiString& s);
	void classAIOCR::SplitProtocolLine(const AnsiString& line, std::vector<AnsiString>& outFields);
	//===========================================================================
	// MyJsonBridge 프로그램 실행하기//
	//===========================================================================
	bool classAIOCR::RunMyJsonBridge(const AnsiString& jsonFileNameOnly, AnsiString& outTxtPath, AnsiString& outErrMsg);

	//===========================================================================
	// 파싱한 Json 결과 Text를 Vector에 저장하기//
	//===========================================================================
	bool classAIOCR::LoadJsonTextToOwnInfo(const AnsiString& fileName, int pathlistSeqNo);//부책//
	bool classAIOCR::LoadJsonTextToShareOwn(const AnsiString& fileName, int pathlistSeqNo);//공유지연명부//
};
//---------------------------------------------------------------------------
extern classAIOCR *eAIOCR;
#endif
