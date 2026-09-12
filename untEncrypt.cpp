//---------------------------------------------------------------------------


#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------
#pragma warn -8004
#pragma warn -8070

#pragma package(smart_init)

cEncrypt *eEncrypt;
//---------------------------------------------------------------------------
cEncrypt::cEncrypt()
{
}
//---------------------------------------------------------------------------
cEncrypt::~cEncrypt()
{
}
//---------------------------------------------------------------------------

int cEncrypt::FuncEncryptFile(char *cPath)
{
	int nRet = 0;

	if (!frmMain->INIINFO.B_ENCRYPT)
		return 0;

	Application->ProcessMessages();

//230628//TEST//DEBUG//테스트 후 원복할 것!!!//
//태안 공유지 테스트하는데, 태안 한글화입력시스템에서는 부여암호화모듈사용한 JPG를 사용하고 있고,
//지적문서에서는 원래 암호화 모듈을 사용할 예정이므로 테스트 후 반드시 원복할 것!!!//
	if (/*//210120//36110 문서 암호화가 SDBApiExportRevB.dll 모듈일때 동작//frmMain->INIINFO.SIDOCODE == "36110" ||*/
		frmMain->INIINFO.SIDOCODE == "44825" || frmMain->INIINFO.SIDOCODE == "44270")
	{
		nRet = this->SDBUnit36110(cPath);
	}
	else
	{
		nRet = this->SDBUnit(cPath);
	}

	Application->ProcessMessages();

	return nRet;
}

//---------------------------------------------------------------------------

int cEncrypt::SDBUnit(char *cPath)
{
	char cMessage[1024];
	memset(cMessage, 0, sizeof(cMessage));

	int (__stdcall* SDB_GetInstanceDomain)(const char* domainName, const char* sdbSvrIp, const unsigned short sdbSvrPort );
	char*(__stdcall* SDB_GetLastErrorMsg)();

	int (__stdcall* SDB_EncryptFile)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile);
	int (__stdcall* SDB_DecryptFile)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile);

	int (__stdcall* SDB_EncryptDPFile)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile, int dpType);
	int (__stdcall* SDB_DecryptDPFile)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile, int dpType, int hashChk);

	HINSTANCE   hinst_SDB_GetInstanceDomain;
	HINSTANCE   hinst_SDB_GetLastErrorMsg;

	HINSTANCE   hinst_SDB_EncryptFile;
	HINSTANCE   hinst_SDB_DecryptFile;

	HINSTANCE   hinst_SDB_EncryptDPFile;
	HINSTANCE   hinst_SDB_DecryptDPFile;

	AnsiString  asLibPath	= frmMain->ROOTPATH + "SDBApiExportRevB.dll";
	if( !FileExists(asLibPath) )
	{
		return -4;
	}

	hinst_SDB_GetInstanceDomain    = LoadLibrary("SDBApiExportRevB.dll");
	hinst_SDB_GetLastErrorMsg 	   = LoadLibrary("SDBApiExportRevB.dll");
	hinst_SDB_EncryptFile          = LoadLibrary("SDBApiExportRevB.dll");
	hinst_SDB_DecryptFile          = LoadLibrary("SDBApiExportRevB.dll");
	hinst_SDB_EncryptDPFile        = LoadLibrary("SDBApiExportRevB.dll");
	hinst_SDB_DecryptDPFile        = LoadLibrary("SDBApiExportRevB.dll");

	SDB_GetInstanceDomain = (int (__stdcall*)(const char* domainName, const char* sdbSvrIp, const unsigned short sdbSvrPort))GetProcAddress(hinst_SDB_GetInstanceDomain, "SDB_GetInstanceDomain");
	SDB_GetLastErrorMsg = (char* (__stdcall*)())GetProcAddress(hinst_SDB_GetLastErrorMsg, "SDB_GetLastErrorMsg");

	SDB_EncryptFile = (int (__stdcall*)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile))GetProcAddress(hinst_SDB_EncryptFile, "SDB_EncryptFile");
	SDB_DecryptFile = (int (__stdcall*)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile))GetProcAddress(hinst_SDB_DecryptFile, "SDB_DecryptFile");

	SDB_EncryptDPFile = (int (__stdcall*)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile, int dpType))GetProcAddress(hinst_SDB_EncryptDPFile, "SDB_EncryptDPFile");
	SDB_DecryptDPFile = (int (__stdcall*)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile, int dpType, int hashChk))GetProcAddress(hinst_SDB_DecryptDPFile, "SDB_DecryptDPFile");

	int nRet=0;

	try {
		if( 1 != SDB_DecryptDPFile(cPath, D_SCHEMA_NAME, D_TABLE_NAME, D_COLUMN_NAME, 1, 0, 0))
		{
			sprintf(cMessage, "%s", SDB_GetLastErrorMsg());
			//========================================================
			//210208//#IMGMODE//암호화설정(ON)&&IMGMODE(OFF)이면 열람불가//
			//태안에 암호화,비암호화문서 혼재되어 있어서 예외처리했었으나//
			//IMGMODE를 적용하면서 원래대로 기능 복원//
//			//210208//#IMGMODE//
//			if(frmMain->INI_B_IMGMODE)
			{
				if( !strcmp(cMessage, "Cannot Get Information From Config File.") )
					nRet = -2;
				else if( !strcmp(cMessage, "Failed to Decrypt_API") )
					nRet = -3;
				else
					nRet = -1;
			}
//			else
//			{
//				if( !strcmp(cMessage, "Decrypt failure: incorrect header") )//암호화 안 된 이미지//
//				{
//					nRet = 0;
//					if( !frmSql->funcSQLSelectDecryptFile() )
//						frmSql->funcSQLInsertDecryptFile(DF_NEW_RECORD);
//				}
//				else if( !strcmp(cMessage, "Cannot Get Information From Config File.") )
//					nRet = -2;
//				else if( !strcmp(cMessage, "Failed to Decrypt_API") )
//					nRet = -3;
//				else
//					nRet = -1;
//			}
		}
		else {
			sprintf(cMessage, "%s", "SDB_DecryptDPFile Success");
			nRet = 0;

			AnsiString  asPathName = StringReplace(frmMain->m_asCurrentFilePath, "\\", "/", TReplaceFlags() << rfReplaceAll);
			if( frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DECRYPTFILE WHERE PATH_NAME = '" + asPathName + "'") == 1)
				frmSql->funcSQLInsertDecryptFile(DF_DELETE_RECORD);
		}

	}
	__finally{
		sprintf(cMessage, "%s", SDB_GetLastErrorMsg());
	}

	FreeLibrary(hinst_SDB_GetInstanceDomain);
	FreeLibrary(hinst_SDB_GetLastErrorMsg);
	FreeLibrary(hinst_SDB_EncryptFile);
	FreeLibrary(hinst_SDB_DecryptFile);
	FreeLibrary(hinst_SDB_EncryptDPFile);
	FreeLibrary(hinst_SDB_DecryptDPFile);

	return nRet;

}
//---------------------------------------------------------------------------

int cEncrypt::SDBUnit36110(char *cPath)
{
	char cMessage[1024];
	memset(cMessage, 0, sizeof(cMessage));

	int (__stdcall* SDB_GetInstanceDomain)(const char* domainName, const char* sdbSvrIp, const unsigned short sdbSvrPort );
	char*(__stdcall* SDB_GetLastErrorMsg)();

	int (__stdcall* SDB_EncryptFile)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile);
	int (__stdcall* SDB_DecryptFile)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile);

	HINSTANCE   hinst_SDB_GetInstanceDomain;
	HINSTANCE   hinst_SDB_GetLastErrorMsg;

	HINSTANCE   hinst_SDB_EncryptFile;
	HINSTANCE   hinst_SDB_DecryptFile;

	//201224//
	AnsiString  asLibPath	= frmMain->ROOTPATH + "SDBApiExport.dll";
	if( !FileExists(asLibPath) )
	{
		return -4;
	}

	hinst_SDB_GetInstanceDomain    = LoadLibrary("SDBApiExport.dll");
	hinst_SDB_GetLastErrorMsg 	   = LoadLibrary("SDBApiExport.dll");
	hinst_SDB_EncryptFile          = LoadLibrary("SDBApiExport.dll");
	hinst_SDB_DecryptFile          = LoadLibrary("SDBApiExport.dll");

	SDB_GetInstanceDomain = (int (__stdcall*)(const char* domainName, const char* sdbSvrIp, const unsigned short sdbSvrPort))GetProcAddress(hinst_SDB_GetInstanceDomain, "SDB_GetInstanceDomain");
	SDB_GetLastErrorMsg = (char* (__stdcall*)())GetProcAddress(hinst_SDB_GetLastErrorMsg, "SDB_GetLastErrorMsg");

	SDB_EncryptFile = (int (__stdcall*)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile))GetProcAddress(hinst_SDB_EncryptFile, "SDB_EncryptFile");
	SDB_DecryptFile = (int (__stdcall*)(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile))GetProcAddress(hinst_SDB_DecryptFile, "SDB_DecryptFile");

	int nRet=0;

	try {
		if( 1 != SDB_DecryptFile(cPath,D_SCHEMA_NAME, D_TABLE_NAME, D_COLUMN_NAME, 0))
		{
			sprintf(cMessage, "%s", SDB_GetLastErrorMsg());
			//========================================================
			//210208//#IMGMODE//암호화설정(ON)&&IMGMODE(OFF)이면 열람불가//
			//태안에 암호화,비암호화문서 혼재되어 있어서 예외처리했었으나//
			//IMGMODE를 적용하면서 원래대로 기능 복원//
//			//210208//#IMGMODE//
//			if(frmMain->INI_B_IMGMODE)
			{
				if( !strcmp(cMessage, "Cannot Get Information From Config File.") )
					nRet = -2;
				else if( !strcmp(cMessage, "Failed to Decrypt_API") )
					nRet = -3;
				else
					nRet = -1;
			}
//			else
//			{
//				if( !strcmp(cMessage, "Decrypt failure: incorrect header") )//암호화 안 된 이미지//
//					nRet = 0;
//				else if( !strcmp(cMessage, "Cannot Get Information From Config File.") )
//					nRet = -2;
//				else if( !strcmp(cMessage, "Failed to Decrypt_API") )
//					nRet = -3;
//				else
//					nRet = -1;
//			}
		}
		else {
			sprintf(cMessage, "%s", "SDB_DecryptFile Success");
			nRet = 0;
		}

	}
	__finally{
		sprintf(cMessage, "%s", SDB_GetLastErrorMsg());

	}

	FreeLibrary(hinst_SDB_GetInstanceDomain);
	FreeLibrary(hinst_SDB_GetLastErrorMsg);
	FreeLibrary(hinst_SDB_EncryptFile);
	FreeLibrary(hinst_SDB_DecryptFile);

	return nRet;
}
//---------------------------------------------------------------------------

