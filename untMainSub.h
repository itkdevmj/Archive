//---------------------------------------------------------------------------

#ifndef untMainSubH
#define untMainSubH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class cMainSub
{
private:
public:
	cMainSub();
	~cMainSub();

	void 	 cMainSub::funcInitResultComponent();
	void     cMainSub::funcAutoSizeGridColumn(TObject *Sender, int _nCol);


	//231212//funcSetComponent2, 3, 4 Merge//
	//_nType : 1 => treSystemDblClick
	//_nType : 2 => FTP Prev/Next File Path DB Info Display //FTP 앞뒤이미지 DB속성정보//
	//_nType : 3 => PoiPopup>문서심볼클릭
	void     	cMainSub::funcSetDBInfo(int _nType);
	AnsiString 	cMainSub::funcMakeJibun(AnsiString _asPnu);





};

//---------------------------------------------------------------------------
extern cMainSub *eMainSub;
//---------------------------------------------------------------------------
#endif