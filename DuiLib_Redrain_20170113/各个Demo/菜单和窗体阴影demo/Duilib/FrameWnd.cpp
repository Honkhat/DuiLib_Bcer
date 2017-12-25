#include "stdafx.h"
#include "FrameWnd.h"

CFrameWnd::CFrameWnd( LPCTSTR pszXMLPath )
	:  m_strXMLPath(pszXMLPath)
{

}

LPCTSTR CFrameWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}

CDuiString CFrameWnd::GetSkinFile()
{
	return m_strXMLPath;
}

void CFrameWnd::InitWindow()
{
	CenterWindow();
}

void CFrameWnd::Notify( TNotifyUI& msg )
{

	if( msg.sType == _T("click") ) 
	{	
		if( msg.pSender->GetName() == _T("btnMenu") ) 
		{
			CPoint point(0, 0);
			GetCursorPos(&point);
			
			CMenuWnd* pMenu = CMenuWnd::CreateMenu(NULL, _T("menutest.xml"), point, &m_PaintManager, &m_MenuCheckInfo);

			//���򿪲˵�
			//CMenuWnd* pMenu = CMenuWnd::CreateMenu(NULL, _T("menutest.xml"), point, &m_PaintManager, &m_MenuCheckInfo, eMenuAlignment_Right );
			//���ϲ�򿪲˵�
			//CMenuWnd* pMenu = CMenuWnd::CreateMenu(NULL, _T("menutest.xml"), point, &m_PaintManager, &m_MenuCheckInfo, eMenuAlignment_Right | eMenuAlignment_Bottom);

			// �Ȼ�ȡ�����Ȼ��Ϳ���ʹ��rootMenu�嵽���˵��ڵ������Ӳ˵��Ȼ�������ɾ������
			CMenuUI* rootMenu = pMenu->GetMenuUI();
			if (rootMenu != NULL)
			{
				CMenuElementUI* pNew = new CMenuElementUI;
				pNew->SetName(_T("Menu_Dynamic"));
				pNew->SetText(_T("��̬һ���˵�"));
				pNew->SetShowExplandIcon(true);
				pNew->SetIcon(_T("WebSit.png"));
				pNew->SetIconSize(16,16);


				CMenuElementUI* pSubNew = new CMenuElementUI;
				pSubNew->SetText(_T("��̬�����˵�"));
				pSubNew->SetName(_T("Menu_Dynamic"));
				pSubNew->SetIcon(_T("Virus.png"));
				pSubNew->SetIconSize(16,16);
				pNew->Add(pSubNew);
				

				rootMenu->Add(pNew);


				CMenuElementUI* pNew2 = new CMenuElementUI;
				pNew2->SetName(_T("Menu_Dynamic"));
				pNew2->SetText(_T("��̬һ���˵�2"));
				rootMenu->AddAt(pNew2,2);
			}

			// ��̬��Ӻ��������ò˵��Ĵ�С
			pMenu->ResizeMenu();
		}
		else if (msg.pSender->GetName() == _T("Menu_btn") )
		{
			DUI__Trace(_T("�㵥���˰�ť"));
		}
		
	}

	__super::Notify(msg);
}

 LRESULT CFrameWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
	 if (uMsg == WM_MENUCLICK)
	 {
		 CDuiString strMenuName = CMenuWnd::GetClickedMenuName();
		 BOOL bChecked = (BOOL)lParam;		 

		 if (strMenuName == _T("Menu_Test1")) 
		 {
			 if (bChecked)
			 {
				 MessageBox(m_hWnd, L"��ѡ��Menu_Test1", L"", 0);
			 } 
			 else
			 {
				 MessageBox(m_hWnd, L"��ȡ��Menu_Test1", L"", 0);
			 }			 
		 }
		 else if (strMenuName == _T("Menu_Test2")) 
		 {
			MessageBox(m_hWnd, L"�㵥����Menu_Test2", L"", 0);		 
		 }
		 else if (strMenuName == _T("Menu_Test3")) 
		 {
			 if (bChecked)
			 {
				 MessageBox(m_hWnd, L"��ѡ��Menu_Test3", L"", 0);
			 } 
			 else
			 {
				 MessageBox(m_hWnd, L"��ȡ��Menu_Test3", L"", 0);
			 }			 
		 }
		 else if (strMenuName == _T("Menu_Dynamic")) 
		 {
			 MessageBox(m_hWnd, L"�㵥���˶�̬��Ӳ˵�", L"", 0);		 
		 }

	 }
	 bHandled = false;
	 return 0;
 }