//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

TOcrThread::TOcrThread(const String& AFileName)
    : TThread(true), FFileName(AFileName)
{
	FreeOnTerminate = true;//스레드가 Execute()를 끝내면 자기 자신을 자동 해제//
}
//---------------------------------------------------------------------------

void __fastcall TOcrThread::SyncFinish()
{
	frmMain->funcSetDoc08AI(false);
	frmMain->ProcessOCRResult(responseText);
}
//---------------------------------------------------------------------------

void __fastcall TOcrThread::SyncError()
{
	frmMain->funcSetDoc08AI(false);
	ShowMessage(L"OCR 오류: " + FErrorMsg);
}
//---------------------------------------------------------------------------

void __fastcall TOcrThread::Execute()
{
    try
    {
        classAIOCR ocr;

		responseText = ocr.SendOCRImage(FFileName);

		Synchronize(SyncFinish);
	}
    catch (const Exception& e)
    {
        FErrorMsg = e.Message;
        Synchronize(SyncError);
    }
    catch (...)
    {
        FErrorMsg = L"알 수 없는 오류가 발생했습니다.";
        Synchronize(SyncError);
    }
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
