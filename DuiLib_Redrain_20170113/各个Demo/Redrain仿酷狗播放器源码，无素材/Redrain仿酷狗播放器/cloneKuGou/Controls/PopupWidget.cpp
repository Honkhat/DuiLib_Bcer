#include "..\duilib.h"

CPopupWidget::CPopupWidget() :m_MainWndpm(NULL),m_WidgetType(UNKNOWN),m_pBtnParent(NULL)
{
}

CPopupWidget::~CPopupWidget()
{
}


LPCTSTR CPopupWidget::GetWindowClassName() const 
{ 
	return _T("PopupWdiget");
}

UINT CPopupWidget::GetClassStyle() const 
{ 
	return CS_DBLCLKS;
}

void CPopupWidget::OnFinalMessage(HWND /*hWnd*/) 
{ 
	 delete this;
}

//===================================================================
//   ������:Init()
//   ������pszXMLPath��xml�ļ���·��
//		  hWndParent:ָ�������������������ģʽ����
//		  pMainPaintManager:�������m_PaintManagerָ��������֪ͨ��������
//		  pBtnParent:��������������İ�ť�������ı䰴ť��ʾ��ֵ
//		  ptPos:������λ�õ����½ǵ�����
//		  type�������Ĵ��ڵ����ͣ�������ͻḽ���ڴ�����Ϣ��������ʱ�������������ж���ʲô���͵�С�Ҽ���������Ϣ
//		  pBtnParent���ڸı�CSliderUI��ͬʱҪ�ı任�����ڵ�CComboUI����ʾֵ��pBtnParent��������ؼ���ָ��
//===================================================================
void CPopupWidget::Init( LPCTSTR pszXMLPath, HWND hWndParent, CPaintManagerUI* pMainPaintManager, POINT ptPos, WidgetType type, CButtonUI * pBtnParent)
{  
	m_strXMLPath = pszXMLPath;
	m_MainWndpm = pMainPaintManager;
	m_WidgetType = type;
	m_pBtnParent = pBtnParent;
	Create(hWndParent, _T("PopupWdiget"), UI_WNDSTYLE_DIALOG, WS_EX_TOOLWINDOW);
	::ClientToScreen(hWndParent, &ptPos);
	//��������Ӧ����ʾ��λ�ã������Լ���������Ͽ��Ϸ�
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y - m_pm.GetClientSize().cy , 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CPopupWidget::InitWindow()
{
	m_pSlider = static_cast<CSliderUI*>(m_pm.FindControl(kWidgetSlider));

	if (m_pSlider)
	{
		if ( m_WidgetType == CHANGE_LIST_TRANS )
		{
			m_pSlider->SetMinValue(0);
			m_pSlider->SetMaxValue(255);
		//	m_pSlider->SetValue(m_pBtnParent->GetTag()* 100 / 255);
		}
		else if ( m_WidgetType == CHANGE_MAINWND_TRANS )
		{
			m_pSlider->SetMinValue(0);
			m_pSlider->SetMaxValue(150);
		//	m_pSlider->SetValue(m_pBtnParent->GetTag()* 100 / 150);
		}
		else if (m_WidgetType == CHANGE_VOLUME)
		{
			m_pSlider->SetMinValue(0);
			m_pSlider->SetMaxValue(100);
		//	m_pSlider->SetValue(m_pBtnParent->GetTag());
		}
		m_pSlider->SetValue(m_pBtnParent->GetTag());
	}
}

void CPopupWidget::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) 
	{
		if( msg.pSender->GetName() == _T("closebtn")) {
			Close(IDOK);
			return; 
		}
	}
	else if ( msg.sType == _T("valuechanged") ||  msg.sType == _T("movevaluechanged"))
	{
		if ( msg.pSender == m_pSlider)
		{
			//�޸�Ƥ�����ô������Ͽ���ı���ʾֵ����ʵ�ʵ�ֵͨ��SetTag����������
			CDuiString szValue;
			if ( m_WidgetType == CHANGE_LIST_TRANS )
			{
				szValue.SmallFormat(_T("%d%%"),m_pSlider->GetValue()* 100 / 255 );
				m_pBtnParent->SetTag(m_pSlider->GetValue());
				m_pBtnParent->SetText(szValue);
			}
			else if ( m_WidgetType == CHANGE_MAINWND_TRANS )
			{
				szValue.SmallFormat(_T("%d%%"),m_pSlider->GetValue() * 100 / 150);
				m_pBtnParent->SetTag(m_pSlider->GetValue());
				m_pBtnParent->SetText(szValue);
			}
			else if ( m_WidgetType == CHANGE_VOLUME )
			{
				//m_pBtnParent->SetTag(m_pSlider->GetValue());
			}
			//����SetTag��������������֪����ʲô���͵�С�Ҽ�����
			msg.pSender->SetTag((UINT_PTR)m_WidgetType);
			//ͨ���������CPaintManagerָ����������Ϣ��������
			m_MainWndpm->SendNotify(msg, false);
		}
	}

}

LRESULT CPopupWidget::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;

	CControlUI *pRoot = builder.Create(m_strXMLPath.GetData(), (UINT)0,  0, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	InitWindow();
	return 0;
}

LRESULT CPopupWidget::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CPopupWidget::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CPopupWidget::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CPopupWidget::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CPopupWidget::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CPopupWidget::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return HTCLIENT;
}


LRESULT CPopupWidget::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	Close();
	return 0 ;
}

LRESULT CPopupWidget::OnMouseLeave( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	Close();
	return 0 ;
}


LRESULT CPopupWidget::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_KILLFOCUS:     lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break; 
	case WM_MOUSELEAVE:	   lRes = OnMouseLeave(uMsg, wParam, lParam, bHandled); break; 
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

