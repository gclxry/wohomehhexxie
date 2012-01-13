#pragma once
#include "stdafx.h"
#include "FileDialogEx.h"
#include "resource.h"
#include "AmigoImage.h"

CFileDialogEx::CFileDialogEx(BOOL bOpenFileDialog, 
                             LPCTSTR lpszDefExt, 
                             LPCTSTR lpszFileName, 
                             DWORD dwFlags, 
                             LPCTSTR lpszFilter, 
                             HWND hWndParent) 
    : CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, hWndParent)
{
    m_spPlayImageHelper = shared_ptr<CPlayImageHelper>();
}

void CFileDialogEx::OnInitDone( LPOFNOTIFY lpon )
{
    CWindow previewWnd = GetDlgItem(IDC_STC_PREVIEW);
    previewWnd.ModifyStyle(0, SS_OWNERDRAW);
}

LRESULT CFileDialogEx::OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    KillTimer(ID_EVENT_UPDATE_IMAGE);
    bHandled = FALSE;
    return 0L;
}

LRESULT CFileDialogEx::OnTimer( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    if (ID_EVENT_UPDATE_IMAGE != static_cast<int>(wParam))
    {
        bHandled = FALSE;
    } 
    else
    {
        shared_ptr<Image> spImage(m_spPlayImageHelper->NextFrame(ELAPSE_TIME_UPDATE_IMAGE));
        if (spImage.get() != NULL)
        {
            CWindow previewWnd = GetDlgItem(IDC_STC_PREVIEW);
            previewWnd.Invalidate();
        }
        bHandled = TRUE;
    }
    return 0L;
}

void CFileDialogEx::OnSelChange( LPOFNOTIFY lpon )
{
    KillTimer(ID_EVENT_UPDATE_IMAGE);
    int nLen = GetFilePath(m_filePath, MAX_PATH);
    if (nLen >=0)
    {
#ifdef new
#undef new
#endif
        shared_ptr<CAmigoImage> spAmigoImage(new CAmigoImage(shared_ptr<Image>(new Image(m_filePath))));
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif
        m_spPlayImageHelper = shared_ptr<CPlayImageHelper>(new CPlayImageHelper(spAmigoImage));
        CWindow previewWnd = GetDlgItem(IDC_STC_PREVIEW);
        previewWnd.Invalidate();
        if (m_spPlayImageHelper->GetAmigoImage()->CanPlay())
        {
            SetTimer(ID_EVENT_UPDATE_IMAGE, ELAPSE_TIME_UPDATE_IMAGE);
        }
    }
}

void CFileDialogEx::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    switch(lpDrawItemStruct->CtlType)
    {
    case ODT_STATIC:
        if (IDC_STC_PREVIEW == lpDrawItemStruct->CtlID && ODA_DRAWENTIRE == lpDrawItemStruct->itemAction)
        {
            if (m_spPlayImageHelper.get())
            {
                DrawPreviewedPicture((Bitmap*)(m_spPlayImageHelper->GetImage().get()), lpDrawItemStruct);
            }
        }
        break;
    default:
        break;
    }
}

void CFileDialogEx::DrawPreviewedPicture( LPCTSTR lpFileName, LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    Image img(lpFileName);
    DrawPreviewedPicture((Bitmap*)(&img), lpDrawItemStruct);
}

void CFileDialogEx::DrawPreviewedPicture( Bitmap* pBmp, LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    InnerDrawPreviewedPicture(lpDrawItemStruct->hDC, pBmp, lpDrawItemStruct->rcItem);
}

void CFileDialogEx::InnerDrawPreviewedPicture( HDC hdc, Bitmap* pBmp, CRect previewRect )
{
    if (!pBmp)
    {
        return;
    }
    HDC hMemoryDC = ::CreateCompatibleDC(hdc);
    HBITMAP hMemoryBmp = ::CreateCompatibleBitmap(hdc, previewRect.Width(), previewRect.Height());
    ::SelectObject(hMemoryDC, hMemoryBmp);
    {
        Graphics g(hMemoryDC);
        SolidBrush brsh(Color(0xec, 0xe9, 0xd8));
        Rect rc(previewRect.left, previewRect.top, previewRect.Width(), previewRect.Height());
        g.FillRectangle(&brsh, rc);
        //计算Image缩放后的尺寸、居中绘制坐标
        float staticRatio = float(previewRect.Width()) / float(previewRect.Height());
        float imgRatio = float(pBmp->GetWidth()) / float(pBmp->GetHeight());
        float newWidth = pBmp->GetWidth();
        float newHeight = pBmp->GetHeight();
        PointF newPos(previewRect.left + float((previewRect.Width() - newWidth)) / 2,
            previewRect.top + float((previewRect.Height() - newHeight)) / 2);
        if (staticRatio > imgRatio)
        {
            if (pBmp->GetHeight() >= previewRect.Height())
            {
                newHeight = previewRect.Height();
                newWidth = imgRatio * newHeight;
                newPos.X = previewRect.left + float((previewRect.Width() - newWidth)) / 2;
                newPos.Y = previewRect.top;
            }
        } 
        else if (staticRatio == imgRatio)
        {
            if (pBmp->GetHeight() > previewRect.Height())
            {
                newHeight = previewRect.Height();
                newWidth = previewRect.Width();
                newPos.X = previewRect.left;
                newPos.Y = previewRect.top;
            }
        }
        else
        {
            if (pBmp->GetWidth() > previewRect.Width())
            {
                newWidth = previewRect.Width();
                newHeight = newWidth / imgRatio;
                newPos.X = previewRect.left;
                newPos.Y = previewRect.top + float((previewRect.Height() - newHeight)) / 2;
            }
        }
        g.SetInterpolationMode(InterpolationModeNearestNeighbor);
        g.DrawImage(pBmp, newPos.X, newPos.Y, newWidth, newHeight);
    }
    ::BitBlt(hdc, previewRect.left, previewRect.top, previewRect.Width(), previewRect.Height(), hMemoryDC, 0, 0, SRCCOPY);
    ::DeleteObject(hMemoryBmp);
    ::DeleteDC(hMemoryDC);
}

#pragma region CPlayImageHelper
CPlayImageHelper::CPlayImageHelper()
{
    m_ElapsedTime = 0;
    m_CurrentCycle = 0;
    m_CurrentFrame = 0;
    m_bAllowPlay = true;
    m_spAmigoImage = shared_ptr<CAmigoImage>();
}

CPlayImageHelper::CPlayImageHelper( shared_ptr<CAmigoImage> spAmigoImage, bool bAllowPlay /*= true*/ )
{
    m_ElapsedTime = 0;
    m_CurrentCycle = 0;
    m_CurrentFrame = 0;
    m_spAmigoImage = spAmigoImage;
    m_bAllowPlay = bAllowPlay;
}

CPlayImageHelper::~CPlayImageHelper( void )
{

}

bool CPlayImageHelper::CanPlay()
{
    return m_bAllowPlay && InnerCanPlay();
}

Image* CPlayImageHelper::NextFrame( int nInterval )
{
    if(m_spAmigoImage.get() != NULL)
    {
        m_ElapsedTime += nInterval;
        return m_spAmigoImage->NextFrame(m_ElapsedTime, m_CurrentFrame, m_CurrentCycle);
    }
    return NULL;
}

shared_ptr<Gdiplus::Image> CPlayImageHelper::GetImage()
{
    return m_spAmigoImage->GetImage();
}

Size CPlayImageHelper::GetSize( void )
{
    Size imgSize(0, 0);
    shared_ptr<Gdiplus::Image> spImage = GetImage();
    if (spImage.get())
    {
        imgSize.Width = spImage->GetWidth();
        imgSize.Height = spImage->GetHeight();
    }
    return imgSize;
}

const shared_ptr<CAmigoImage> CPlayImageHelper::GetAmigoImage() const
{
    return m_spAmigoImage;
}

bool CPlayImageHelper::InnerCanPlay()
{
    if(m_spAmigoImage.get() != NULL)
    {
        if(m_spAmigoImage->IsCyclePlay())
        {
            return true;
        }
        else
        {
            return (m_spAmigoImage->CanPlay() && (m_CurrentCycle < m_spAmigoImage->GetCycleCount()));
        }
    }
    else
    {
        return false;
    }
}
#pragma endregion
