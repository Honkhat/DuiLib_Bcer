/********************************************************************
	created:	2014/11/12
	author:		Redrain
	e-mail:		redrains@qq.com
	qq:			491646717
	website:	http://blog.csdn.net/zhuhongshu?viewmode=contents
	purpose:	����Redrain�¿ṷ���ֲ��������������룬Ŀ���ǰ�������ʹ��DuiLib������ѧϰ����⣬
				���������bug�����߶Գ��������ʣ�������ϵ�Ҹ���QQ����QQȺ���Ҿ�����DuiLib QQȺ���
				��������а�����webkit�ں�����������ֲ����ࡢ�˵��ࡢ�������ܵȵ�
*********************************************************************/

#include "duilib.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	::OleInitialize(NULL);
    ::CoInitialize(NULL);
	CWkeWebkitUI::WkeWebkit_Init();

    CPaintManagerUI::SetInstance(hInstance);
	CFrameWnd *pFrame = new CFrameWnd(_T("xmls\\Main_dlg.xml"));
    pFrame->Create(NULL, _T("Redrain���ֺ�"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowModal();

	CWkeWebkitUI::WkeWebkit_Shutdown();
    delete pFrame;
    ::CoUninitialize();
	::OleUninitialize();
    return 0;
}
