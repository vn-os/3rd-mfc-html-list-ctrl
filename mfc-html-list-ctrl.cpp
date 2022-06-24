#include "mfc-html-list-ctrl.h"

#include <cassert>

IMPLEMENT_DYNAMIC(HTMLListCtrl, CHTMLListCtrl)

BEGIN_MESSAGE_MAP(HTMLListCtrl, CHTMLListCtrl)
  ON_WM_KILLFOCUS()
  ON_NOTIFY_REFLECT(HTMLLIST_SELECTIONCHANGED, OnHTMLList_SelectionChanged)
  ON_NOTIFY_REFLECT(HTMLLIST_LBUTTONDOWN, OnHTMLList_LButtonDown)
  ON_NOTIFY_REFLECT(HTMLLIST_LBUTTONDBLCLICK, OnHTMLList_LButtonDBLClick)
  ON_NOTIFY_REFLECT(HTMLLIST_RBUTTONDOWN, OnHTMLList_RButtonDown)
  ON_NOTIFY_REFLECT(HTMLLIST_ITEMCHECKED, OnHTMLList_CheckStateChanged)
END_MESSAGE_MAP()

HTMLListCtrl::HTMLListCtrl(CDialog* pParent)
  : CHTMLListCtrl(), m_pParentWnd(pParent), m_HolderID(0), m_fnNotify(nullptr)
{
}

HTMLListCtrl::~HTMLListCtrl()
{
}

void HTMLListCtrl::Create(CWnd* pParent, UINT ID, UINT Flags)
{
  m_pParentWnd = pParent;
  m_HolderID = ID;

  auto pHolderCtrl = m_pParentWnd->GetDlgItem(m_HolderID);
  assert(pHolderCtrl != nullptr);

  CRect rect;
  pHolderCtrl->GetWindowRect(&rect);
  m_pParentWnd->ScreenToClient(rect);

  __super::Create(m_pParentWnd, rect, ID);
  __super::SetExtendedStyle(Flags);
}

void HTMLListCtrl::Update()
{
  auto pHolderCtrl = m_pParentWnd->GetDlgItem(m_HolderID);
  assert(pHolderCtrl != nullptr);

  CRect rect;
  pHolderCtrl->GetWindowRect(&rect);
  m_pParentWnd->ScreenToClient(&rect);

  this->SetWindowPos(
    nullptr, rect.left, rect.top, rect.Width(), rect.Height(),
    SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void HTMLListCtrl::Add(const CString& Line, LPVOID pData, BOOL Checked, UINT nStyle, UINT nHeight)
{
  int idx = this->InsertItem(Line, 0, nStyle, nHeight);
  this->SetItemData(idx, LPARAM(pData));
  this->SetItemCheck(idx, Checked ? BST_CHECKED : BST_UNCHECKED);
}

void HTMLListCtrl::Notify(const FnNotify fnNotify)
{
  m_fnNotify = fnNotify;
}

void HTMLListCtrl::OnKillFocus(CWnd* pNewWnd)
{
  __super::OnKillFocus(pNewWnd);

  this->SendSelectionChangeNotification(NONE_SELECTED);
}

void HTMLListCtrl::OnHTMLList_SelectionChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
  if (m_fnNotify != nullptr)
  {
    m_fnNotify(HTMLLIST_SELECTIONCHANGED, reinterpret_cast<NM_HTMLLISTCTRL*>(pNMHDR), pResult);
  }
}

void HTMLListCtrl::OnHTMLList_CheckStateChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
  if (m_fnNotify != nullptr)
  {
    m_fnNotify(HTMLLIST_ITEMCHECKED, reinterpret_cast<NM_HTMLLISTCTRL*>(pNMHDR), pResult);
  }
}

void HTMLListCtrl::OnHTMLList_LButtonDBLClick(NMHDR* pNMHDR, LRESULT* pResult)
{
  if (m_fnNotify != nullptr)
  {
    m_fnNotify(HTMLLIST_LBUTTONDBLCLICK, reinterpret_cast<NM_HTMLLISTCTRL*>(pNMHDR), pResult);
  }
}

void HTMLListCtrl::OnHTMLList_LButtonDown(NMHDR* pNMHDR, LRESULT* pResult)
{
  if (m_fnNotify != nullptr)
  {
    m_fnNotify(HTMLLIST_LBUTTONDOWN, reinterpret_cast<NM_HTMLLISTCTRL*>(pNMHDR), pResult);
  }
}

void HTMLListCtrl::OnHTMLList_RButtonDown(NMHDR* pNMHDR, LRESULT* pResult)
{
  if (m_fnNotify != nullptr)
  {
    m_fnNotify(HTMLLIST_RBUTTONDOWN, reinterpret_cast<NM_HTMLLISTCTRL*>(pNMHDR), pResult);
  }
}
