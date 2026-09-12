#ifndef _SDBAPIEXPORT_H_
#define _SDBAPIEXPORT_H_


#ifdef __cplusplus
extern "C" {
#endif	/*	__cplusplus	*/


#ifndef DLLEXPORT
#	if defined(WIN32)||defined(_WIN32)
#		ifdef _USRDLL
#			define DLLEXPORT __declspec(dllexport)
#		else
#			define DLLEXPORT __declspec(dllimport)
#		endif	/*	_USRDLL	*/
#	else
#			define DLLEXPORT
#	endif	/*	WIN32	*/
#endif	/*	DLLEXPORT	*/


#ifndef PPVOID
#define PPVOID void**
#endif

#ifndef HAVE_SDLOGLEVEL
#define HAVE_SDLOGLEVEL
	typedef enum 
	{
		SDLOGLEVEL_DEBUG = 1,
		SDLOGLEVEL_ERROR = 2,
		SDLOGLEVEL_CRIT	= 3
	}SDLOGLEVEL;
#endif
#ifndef HAVE_SDFILEDPTYPE
#define HAVE_SDFILEDPTYPE
	typedef enum 
	{
		SDFILEDPTYPE_NONE = 0,		//이중암복호화 체크 안함
		SDFILEDPTYPE_T1 = 1,		//이중암복호화 체크 시 원본파일이 암복호화 되어있을 경우 성공 리턴
		SDFILEDPTYPE_T2 = 2,		//이중암복호화 체크 시 원본파일이 암복호화 되어있을 경우 성공 리턴 및 대상파일에 파일이 없을 경우 파일 복사
		SDFILEDPTYPE_FAIL = 3		//이중암복호화 체크 시 원본파일이 암복호화 되어있을 경우 실패 리턴
	}SDFILEDPTYPE;
#endif

#ifndef HAVE_DUPLICATE_TYPE
#define HAVE_DUPLICATE_TYPE
	typedef enum
	{
		SDB_DP_NONE = 0,
		SDB_DP_RETURN = 1,
		SDB_DP_EXCEPTION=2
	}SD_DUP_TYPE;

#endif

/* FILE ENCRYPT RETURN CODE IN API */
#define SDB_ENCRYPT_FILE_OK			0
#define SDB_ENCRYPT_FILE_MODIFY		1
#define SDB_NOT_ENCRYPT_FILE		2
#define SDB_READ_FILE_ERR			3
#define SDB_FILE_NOT_FOUND			4


	/* Instance Init */
	/* Return Value 0 : SUCCESS, -1 : FAIL(0 보다 작은 값) */
	DLLEXPORT int SDB_GetInstance(const char* dbIp, const unsigned short dbPort, const char* sdbSvrIp, const unsigned short sdbSvrPort );
	DLLEXPORT int SDB_GetInstanceHA(const char* dbIp, const unsigned short dbPort, 
		const char* sdbSvrIp1, const unsigned short sdbSvrPort1,
		const char* sdbSvrIp2, const unsigned short sdbSvrPort2);
	DLLEXPORT int SDB_GetInstanceDomain(const char* domainName, const char* sdbSvrIp, const unsigned short sdbSvrPort );
	DLLEXPORT int SDB_GetInstanceDomainHA(const char* domainName, 
		const char* sdbSvrIp1, const unsigned short sdbSvrPort1,
		const char* sdbSvrIp2, const unsigned short sdbSvrPort2 );

	/* 기능 함수 */
	/* Base Function */
	DLLEXPORT char* SDB_Encrypt(const char* owner, const char* table, const char* column, char* pData, int pDataLen);
	DLLEXPORT char* SDB_Decrypt(const char* owner, const char* table, const char* column, char* eData, int eDataLen);

	/* KDB Version */
	DLLEXPORT char* SDB_EncryptNormal(char* pData);
	DLLEXPORT char* SDB_DecryptNormal(char* eData);
	/* KDB Version */
	DLLEXPORT char* SDB_EncryptJumin(char* pData);
	DLLEXPORT char* SDB_DecryptJumin(char* eData);

	/* Return Value uOut Length */
	/* Parameter Add Data Length */
	DLLEXPORT int SDB_Encrypt2(const char* owner, const char* table, const char* column, char* pData, int pDataLen, char* uOut);
	DLLEXPORT int SDB_Decrypt2(const char* owner, const char* table, const char* column, char* eData, int pDataLen, char* uOut);

	/* Auto Length Check */
	DLLEXPORT int SDB_Encrypt3(const char* owner, const char* table, const char* column, char* pData, char* uOut);
	DLLEXPORT int SDB_Decrypt3(const char* owner, const char* table, const char* column, char* eData, char* uOut);

	/* Auto Length Check */
	DLLEXPORT int SDB_EncryptDP(const char* owner, const char* table, const char* column, char* pData, char* uOut,int dpType);
	DLLEXPORT int SDB_DecryptDP(const char* owner, const char* table, const char* column, char* eData, char* uOut,int dpType);

	/* Parameter Add Data Length */
	DLLEXPORT int SDB_EncryptDP2(const char* owner, const char* table, const char* column, char* pData, int pDataLen, char* uOut,int dpType);	
	DLLEXPORT int SDB_DecryptDP2(const char* owner, const char* table, const char* column, char* eData, int eDataLen, char* uOut,int dpType);

	/* Use Config File -------------------------------------------------------------------------------------------------------------*/
	/* Auto Length Check */
	DLLEXPORT int SDB_EncryptDP3(const char* owner, const char* table, const char* column, char* pData, char* uOut);
	DLLEXPORT int SDB_DecryptDP3(const char* owner, const char* table, const char* column, char* eData, char* uOut);

	/* Parameter Add Data Length */
	DLLEXPORT int SDB_EncryptDP4(const char* owner, const char* table, const char* column, char* pData, int pDataLen, char* uOut);	
	DLLEXPORT int SDB_DecryptDP4(const char* owner, const char* table, const char* column, char* eData, int eDataLen, char* uOut);
	/* ---------------- -------------------------------------------------------------------------------------------------------------*/

	/* Extenstion Function : NULL Encrypt method */
	DLLEXPORT char* SDB_DecryptEx(const char* sKeyName, char* eData, int eDataLen, int nullChk);
	DLLEXPORT char* SDB_EncryptEx(const char* sKeyName, char* pData, int pDataLen, int nullChk);

	DLLEXPORT int SDB_EncryptEx2(const char* sKeyName, char* pData, int pDataLen, int nullChk, char* uOut);
	DLLEXPORT int SDB_DecryptEx2(const char* sKeyName, char* eData, int eDataLen, int nullChk, char* uOut);

	/* Extenstion Function SHA alg */
	DLLEXPORT int SDB_GetInstanceSha();
	DLLEXPORT int SDB_doDigest(char* pData, int pDataLen, char* outData);
	DLLEXPORT int SDB_doDigest256(char* pData, int pDataLen, char* output);
	DLLEXPORT char* SDB_EncryptSha256(char* pData);
	DLLEXPORT char* SDB_EncryptSha256_T1(char* pData);


	DLLEXPORT void SDB_Clear();
	DLLEXPORT char* SDB_GetLastErrorMsg();
	DLLEXPORT int SDB_GetLastError(char* msg);
	DLLEXPORT void SDB_SetLogging(const char* filename, int logLevel);

	DLLEXPORT void SDB_AuditInit(const char* filename);
	DLLEXPORT void SDB_DoAudit(const char* STC, const char* operators, int result, const char* reason);

	DLLEXPORT int SDB_GetLastErrorCode();
	DLLEXPORT int SDB_IsValidKey(const char* owner, const char* table, const char* column);


	/*DLEXPORT void SDBApi_SetLicensePath(char* path);*/

	/* moon's 121018 : memory free */
	DLLEXPORT void SDB_Free_UString(unsigned char* pdata);
	/* moon'e */

	/* Return Value 0 : FAIL, 1 : SUCCESS */
	DLLEXPORT int SDB_EncryptFile(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile);
	DLLEXPORT int SDB_DecryptFile(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile);

	DLLEXPORT int SDB_EncryptFileEx(const char* srcFilePath, const char* dstFilePath, const char* srcBackupDirPath,
		const char* owner, const char* table, const char* column, int delBackupFile);
	DLLEXPORT int SDB_DecryptFileEx(const char* srcFilePath, const char* dstFilePath, const char* srcBackupDirPath,
		const char* owner, const char* table, const char* column, int delBackupFile);


	/* Return Value 0 : ENCRIPTED FILE, 1 : NOT ENCRYPT FILE 2: Modified File 3: HEADER READ ERROR 4: FILE NOT FOUND */
	DLLEXPORT int SDB_IsEncFile(const char* path);

	/* Return Value 0 : FAIL, 1 : SUCCESS 2: Modified Enc File */
	DLLEXPORT int SDB_EncryptDPFile(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile, int dpType);
	DLLEXPORT int SDB_DecryptDPFile(const char* srcFilePath, const char* owner, const char* table, const char* column, int delBackupFile, int dpType, int hashChk);

	DLLEXPORT int SDB_EncryptDPFileEx(const char* srcFilePath, const char* dstFilePath, const char* srcBackupDirPath,
		const char* owner, const char* table, const char* column, int delBackupFile, int dpType);
	DLLEXPORT int SDB_DecryptDPFileEx(const char* srcFilePath, const char* dstFilePath, const char* srcBackupDirPath,
		const char* owner, const char* table, const char* column, int delBackupFile, int dpType, int hashChk);

	/* samsung encrypt & decrypt by configFil option. */ 
	DLLEXPORT int SDB_EncryptFileCEV(const char* srcFilePath
					, const char* dstFilePath
					, const char* owner
					, const char* table
					, const char* column);

	DLLEXPORT int SDB_DecryptFileCEV(const char* srcFilePath
					, const char* dstFilePath
					, const char* owner
					, const char* table
					, const char* column); 
	/* Lob Data Encrypt only Police Agency */ 
	DLLEXPORT int SDB_EncryptLob(const char *KN, char *plainData, int pDataLen, char* uOut);
	DLLEXPORT int SDB_EncryptLobEx(const char *KN, char *plainData, int pDataLen, int dpType, char* uOut);
	DLLEXPORT int SDB_EncryptLobExCEV(const char *KN, char *plainData, int pDataLen, char* uOut);

	DLLEXPORT int SDB_DecryptLob(const char *KN, char *eData, int eDataLen, char* uOut);
	DLLEXPORT int SDB_DecryptLobEx(const char *KN, char *eData, int eDataLen, int dpType, char* uOut);
    DLLEXPORT int SDB_DecryptLobExCEV(const char *KN, char *eData, int eDataLen, char* uOut);

#ifdef __cplusplus
}
#endif	/*	__cplusplus	*/
#endif	/*	_SDBAPI_H_	*/

