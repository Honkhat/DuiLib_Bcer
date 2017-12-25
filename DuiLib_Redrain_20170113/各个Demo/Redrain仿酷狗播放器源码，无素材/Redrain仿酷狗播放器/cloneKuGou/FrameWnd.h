#pragma once

#include "DropTargetEx.h"
#ifdef _DEBUG
#       pragma comment(lib, "../Common/lib/UiLib_ud.lib")
#else
#       pragma comment(lib, "../Common/lib/UiLib_u.lib")
#endif

class CFrameWnd: public WindowImplBase
{
public:
	explicit CFrameWnd(LPCTSTR pszXMLPath);

	LPCTSTR GetWindowClassName() const;
	CDuiString GetSkinFile();
	CDuiString GetSkinFolder();
// 	UILIB_RESOURCETYPE GetResourceType() const;
// 	LPCTSTR GetResourceID() const;

     void InitWindow();
     void Notify(TNotifyUI& msg);

	 CControlUI* CreateControl(LPCTSTR pstrClassName);
	 LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	 CPaintManagerUI* GetMainWndPaintManager();

	 void SetListTrans(int nValue);
	 int  GetListTrans() const;
	 void SetIsSkinTrans(bool bTrans);
	 bool GetIsSkinTrans() const;
	 void SetSkinTrans(int nValue);
	 int  GetSkinTrans() const;
	 void SetBkColor(DWORD dwBackColor);
	 DWORD GetBkColor() const;
	 void SetBkImage(CDuiString strBkImage);
	 LPCTSTR GetBkImage();
	 void LoadDefaultState();

	 //�������Żص�����
	 static void player_proc(CMusicPlayer* pPlayer,PLAY_MSG msg,WPARAM wParam,LPARAM lParam,void* arg);
	 static MEDIA* PlayNextMedia(CMusicPlayer* pPlayer);
	 static MEDIA* PlayPrevMedia(CMusicPlayer* pPlayer);
	 static MEDIA* PlayRandomMedia(CMusicPlayer* pPlayer);

	 //��Ҫ���ڻ�ȡ�����б�ķ�Χ���ж��϶�ʱ��ͼ����ʽ
	 bool GetLeftListPos(RECT & rc) const;

	 //��Ӵ��忪��ʱ�Ķ�������Ч��,���Ժ��ֶ�����Ч��wke�����ݣ�Ҫôע��OnPlayAnimation�ĵ��ã�Ҫô��wke��SetUrl��������
	 void OnPlayAnimation();

	 void OnSelectChanged( TNotifyUI &msg );
	 void OnShowMenu( TNotifyUI &msg );
	 static void OnDropFiles(CFrameWnd *pMainWnd, HDROP hDrop);

	 void AddMusicsToGroup(CMusicListUI* pMusicList, LPCTSTR szGroupName, 
		 vector<CDuiString>& fileNames, CDuiString szLogoPath = kDefaultLogoPath1,
		 bool bCheckExist = true, bool bAutoRefreshIndex = true);
	 TStreamTime GetMusicLenght(CDuiString &MusicPath);
	 MEDIA* GetCurMedia();
	 CMusicListUI* GetMusicList();
	 void SetLoopState(LOOP_STATE state);
	 LOOP_STATE GetLoopState();
	 void SetPlayBtnState(bool bIsPlay);

	 UINT MessageBox( LPCTSTR lpText, UINT uIcon = MB_ICONWARNING , LPCTSTR lpCaption = _T("��ʾ"),UINT uType = MB_OK );

private:
	CDuiString		m_strXMLPath;
	CDropTargetEx	m_DropTarget;	//ʹ����֧���ϷŲ���
	CWndShadow		m_WndShadow;	//������Ӱ��Ĭ�ϲ�û��ʹ��
	CDuiString		m_strBkImage;   //���������ֿ�ʱ����ԭ���ı�����Ϣ�����ָ�

	//���ֿ��Ʋ���
	CMusicPlayer	m_MusicPlayer;	
	MEDIA			*m_pCurMedia;
	ZPlay			*m_pZplayer;		 //������ָ��,�����������ֳ���
	CButtonUI		*m_pBtnMusicPlay;
	CButtonUI		*m_pBtnMusicPause;
	CButtonUI		*m_pBtnMusicLrc;
	CButtonUI		*m_pBtnAddMusic;
	CButtonUI		*m_pBtnMusicSound;
	CButtonUI		*m_pBtnMusicLoop;
	CLabelUI		*m_pLblPlayTime;
	CLabelUI		*m_pLblTotalTime;
	CSliderUI		*m_pSliderPlayProcess;
	CLabelUI		*m_pLblMainWndTitile;  //������ı��⣬����������ʱӦ�ø�Ϊ���ֵ�����
		

	//�Ҳ������
	CButtonUI				*m_pBtnGoBack;
	CButtonUI				*m_pBtnRefresh;
	CTabLayoutUI			*m_pTabTop;


	//���󲼾�
	CVerticalLayoutUI		*m_pBackGround;
	CHorizontalLayoutUI		*m_pWndTitle;
	CVerticalLayoutUI		*m_pMainTitleRight;
	CVerticalLayoutUI		*m_pMainMusicBank;
	CHorizontalLayoutUI		*m_pMainShowRight;
	CHorizontalLayoutUI		*m_pMainStatus;
	CLabelUI				*m_pLblBottomInfo;


	//���Tab���ؼ�
	CVerticalLayoutUI		*m_pLeftTabBk;
	CVerticalLayoutUI		*m_pLeftTabListBk;
	CAnimationTabLayoutUI	*m_pTabLeft;
	CMusicListUI			*m_pMusicList;
	CMusicListUI			*m_pRadioList;
	CMusicListUI			*m_pLocaltion;
	CMusicListUI			*m_pDownload;
	CTileLayoutUI			*m_pMoreList;


	//wke������ؼ�
	CWkeWebkitUI	*m_pWke;

	map<CDuiString,bool> m_MenuCheckInfo;	//����˵���������Ϣ,Ӧ��Ϊÿ���˵�������һ��map,������ֻ����ѭ����ʽ�˵��Ĺ���
	map<CDuiString,bool> m_MenuLoopCheckInfo;

	int				m_nListTrans;
	bool			m_bSkinTrans;
	int				m_nSkinTrans;
};