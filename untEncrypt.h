//---------------------------------------------------------------------------

#ifndef untEncryptH
#define untEncryptH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class cEncrypt
{
private:
public:
	cEncrypt();
	~cEncrypt();

	int cEncrypt::FuncEncryptFile(char *cPath);

	int cEncrypt::SDBUnit(char *cPath);
	int cEncrypt::SDBUnit36110(char *cPath);
};

//---------------------------------------------------------------------------
extern cEncrypt *eEncrypt;
//---------------------------------------------------------------------------
#endif
