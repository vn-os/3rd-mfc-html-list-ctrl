#pragma once

/**
 * @refer to #include "framework.h"
 */
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "HTML-List-Control/HTMLListCtrl.h"

#include <functional>

class HTMLListCtrl : public CHTMLListCtrl
{
  DECLARE_DYNAMIC(HTMLListCtrl)

public:
  typedef std::function<void(UINT, NM_HTMLLISTCTRL*, LRESULT*)> FnNotify;

  HTMLListCtrl(CDialog* pParent = nullptr);
  virtual ~HTMLListCtrl();

  void Create(CWnd* pParent, UINT ID, UINT Flags = HTMLLIST_STYLE_GRIDLINES | HTMLLIST_STYLE_CHECKBOX | HTMLLIST_STYLE_IMAGES);
  void Update();
  void Add(const CString& Line, LPVOID pData = NULL, BOOL Checked = TRUE, UINT nStyle = HTML_TEXT, UINT nHeight = AUTO);
  void Notify(const FnNotify fncb);

protected:
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnHTMLList_SelectionChanged(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnHTMLList_LButtonDown(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnHTMLList_LButtonDBLClick(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnHTMLList_RButtonDown(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnHTMLList_CheckStateChanged(NMHDR* pNMHDR, LRESULT*);
  DECLARE_MESSAGE_MAP()

private:
  UINT  m_HolderID;
  CWnd* m_pParentWnd;
  FnNotify m_fnNotify;
};
