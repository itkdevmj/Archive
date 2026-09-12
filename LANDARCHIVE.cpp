//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("untMemo.cpp", frmMemo);
USEFORM("untCalcDate.cpp", frmCalcDate);
USEFORM("MessageSrc.cpp", frmMsg);
USEFORM("untResultList.cpp", frmResultList);
USEFORM("untMemoViewer.cpp", frmMemoViewer);
USEFORM("untChangeMenu.cpp", frmChangeMenu);
USEFORM("untMemoRegist.cpp", frmMemoRegist);
USEFORM("untAlphaView2.cpp", frmAlphaView2);
USEFORM("untSearch.cpp", frmSearch);
USEFORM("untAbout.cpp", frmAbout);
USEFORM("untReleaseList.cpp", frmReleaseList);
USEFORM("untAlphaSub2.cpp", frmAlphaSub2);
USEFORM("untSql.cpp", frmSql);
USEFORM("mainSrc.cpp", frmMain);
USEFORM("untSettingEnv.cpp", frmSettingEnv);
USEFORM("untPreview.cpp", frmPreview);
USEFORM("untResultList2.cpp", frmResultList2);
USEFORM("untMemoBatch.cpp", frmMemoBatch);
USEFORM("untUserManagement.cpp", frmUserManagement);
USEFORM("PrintSetting.cpp", frmPrintSetting);
USEFORM("untUserLogList.cpp", frmUserLogList);
USEFORM("untAreaCalculatorTypeA.cpp", frmAreaCalculatorTypeA);
USEFORM("untDoc8History.cpp", frmDoc8History);
USEFORM("untAlphaView.cpp", frmAlphaView);
USEFORM("untAlphaDoc8.cpp", frmAlphaDoc8);
USEFORM("untCalculator.cpp", frmCalculator);
USEFORM("untStat.cpp", frmStat);
USEFORM("untAlphaSub.cpp", frmAlphaSub);
USEFORM("untMemoHis.cpp", frmMemoHis);
USEFORM("untProgramCloseQ.cpp", frmProgramCloseQ);
USEFORM("untFtpControl.cpp", frmFtpControl);
USEFORM("untHanja.cpp", frmHanja);
USEFORM("untProgramClose.cpp", frmProgramClose);
USEFORM("untSidoCode.cpp", frmSidoCode);
USEFORM("untUserAdd.cpp", frmUserAdd);
USEFORM("untDoc8View.cpp", frmDoc8View);
USEFORM("untTempDoc.cpp", frmTempDoc);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	HANDLE  hMutex = NULL;
	hMutex = CreateMutex(NULL, false, "REALNAME_LANDARCHIVE");
	if (GetLastError() == ERROR_ALREADY_EXISTS){
		//MessageDlg("프로그램이 구동중입니다.", mtInformation, TMsgDlgButtons() << mbOK, 0);
		Application->Terminate();
		return 0;
	}

	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "지적문서통합관리시스템";
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmSql), &frmSql);
		Application->CreateForm(__classid(TfrmAbout), &frmAbout);
		Application->CreateForm(__classid(TfrmSearch), &frmSearch);
		Application->CreateForm(__classid(TfrmFtpControl), &frmFtpControl);
		Application->CreateForm(__classid(TfrmHanja), &frmHanja);
		Application->CreateForm(__classid(TfrmCalculator), &frmCalculator);
		Application->CreateForm(__classid(TfrmUserAdd), &frmUserAdd);
		Application->CreateForm(__classid(TfrmUserLogList), &frmUserLogList);
		Application->CreateForm(__classid(TfrmUserManagement), &frmUserManagement);
		Application->CreateForm(__classid(TfrmReleaseList), &frmReleaseList);
		Application->CreateForm(__classid(TfrmPrintSetting), &frmPrintSetting);
		Application->CreateForm(__classid(TfrmSidoCode), &frmSidoCode);
		Application->CreateForm(__classid(TfrmSettingEnv), &frmSettingEnv);
		Application->CreateForm(__classid(TfrmResultList), &frmResultList);
		Application->CreateForm(__classid(TfrmResultList2), &frmResultList2);
		Application->CreateForm(__classid(TfrmAreaCalculatorTypeA), &frmAreaCalculatorTypeA);
		Application->CreateForm(__classid(TfrmCalcDate), &frmCalcDate);
		Application->CreateForm(__classid(TfrmProgramClose), &frmProgramClose);
		Application->CreateForm(__classid(TfrmProgramCloseQ), &frmProgramCloseQ);
		Application->CreateForm(__classid(TfrmMsg), &frmMsg);
		Application->CreateForm(__classid(TfrmMemo), &frmMemo);
		Application->CreateForm(__classid(TfrmMemoHis), &frmMemoHis);
		Application->CreateForm(__classid(TfrmMemoViewer), &frmMemoViewer);
		Application->CreateForm(__classid(TfrmChangeMenu), &frmChangeMenu);
		Application->CreateForm(__classid(TfrmAlphaView), &frmAlphaView);
		Application->CreateForm(__classid(TfrmAlphaSub), &frmAlphaSub);
		Application->CreateForm(__classid(TfrmAlphaView2), &frmAlphaView2);
		Application->CreateForm(__classid(TfrmAlphaSub2), &frmAlphaSub2);
		Application->CreateForm(__classid(TfrmMemoBatch), &frmMemoBatch);
		Application->CreateForm(__classid(TfrmMemoRegist), &frmMemoRegist);
		Application->CreateForm(__classid(TfrmStat), &frmStat);
		Application->CreateForm(__classid(TfrmAlphaDoc8), &frmAlphaDoc8);
		Application->CreateForm(__classid(TfrmDoc8View), &frmDoc8View);
		Application->CreateForm(__classid(TfrmDoc8History), &frmDoc8History);
		Application->CreateForm(__classid(TfrmPreview), &frmPreview);
		Application->CreateForm(__classid(TfrmTempDoc), &frmTempDoc);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}

	if (hMutex) // 뮤텍스 종료
		CloseHandle(hMutex);

	return 0;
}
//---------------------------------------------------------------------------
