//---------------------------------------------------------------------------

#ifndef untTreeSystemH
#define untTreeSystemH
//---------------------------------------------------------------------------
class cTreeSystem
{
private:
public:
	cTreeSystem();
	~cTreeSystem();

	void cTreeSystem::funcSettingTreeView(int _nDocNo);
	int  cTreeSystem::funcNodeSettingDoc(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc01(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc02(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc03(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc04(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc05(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc06(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc07(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc08(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc09(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc11(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc12(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc13(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc14(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc15(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc17(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc18(int _nDocNo, int _nNodeCount);
	int  cTreeSystem::funcNodeSettingDoc20(int _nDocNo, int _nNodeCount);//231021//GAGAMLAYER in LandArchive
	int  cTreeSystem::funcNodeSettingMemo(int _nDocNo, int _nNodeCount);

	int  cTreeSystem::funcClickNodeToDocNum(TTreeNode* t_ClickNode);

	void cTreeSystem::funcNodeToImage(TTreeNode* t_SelectNode);
	void cTreeSystem::funcNodeToImageDoc01(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc02(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc03(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc04(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc05(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc06(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc07(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc08(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc09(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc11(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc12(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc13(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc14(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc15(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc17(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc18(TTreeNode* t_SelectNode, bool bRefreshThumb);
	void cTreeSystem::funcNodeToImageDoc20(TTreeNode* t_SelectNode, bool bRefreshThumb);//231021//GAGAMLAYER in LandArchive
	void cTreeSystem::funcNodeToImageMemo(TTreeNode* t_SelectNode, bool bRefreshThumb);

	//tresystem에서 선택한 지구명의 권번호와 동일한 좌표계산부 index를 가져와야 항공뷰를 그릴 때 color 변경할 수 있다.
	int  cTreeSystem::funcGetDognIndex(AnsiString _asKwonNo);
	int  cTreeSystem::funcGetMemoIndex(AnsiString _asPoiKey);


};
//---------------------------------------------------------------------------
extern cTreeSystem *eTree;
#endif
