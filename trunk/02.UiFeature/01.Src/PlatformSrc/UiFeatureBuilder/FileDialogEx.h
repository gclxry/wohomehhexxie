
#pragma once
#include <atltypes.h>

#define ID_EVENT_UPDATE_IMAGE 1                       //更新动画的TIMER的ID
#define ELAPSE_TIME_UPDATE_IMAGE 100                  //更新动画的时间间隔100ms

class CAmigoImage;
class CPlayImageHelper;

class CFileDialogEx : public CFileDialog
{
public:
    CFileDialogEx(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
        LPCTSTR lpszDefExt = NULL,
        LPCTSTR lpszFileName = NULL,
        DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        LPCTSTR lpszFilter = NULL,
        HWND hWndParent = NULL);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
    void OnInitDone(LPOFNOTIFY lpon);

    void OnSelChange(LPOFNOTIFY lpon);

    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    void InnerDrawPreviewedPicture( HDC hdc, Bitmap* pBmp, CRect previewRect );
    void DrawPreviewedPicture( Bitmap* pBmp, LPDRAWITEMSTRUCT lpDrawItemStruct );
    void DrawPreviewedPicture(LPCTSTR lpFileName, LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
    LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
    TCHAR m_filePath[MAX_PATH];
    shared_ptr<CPlayImageHelper> m_spPlayImageHelper;
};

class CPlayImageHelper
{
public:
    CPlayImageHelper();
    CPlayImageHelper(shared_ptr<CAmigoImage> spAmigoImage, bool bAllowPlay = true);
    virtual ~CPlayImageHelper(void);

    bool CanPlay();
    Image* NextFrame(int nInterval);
    shared_ptr<Gdiplus::Image> GetImage();
    Size GetSize(void);
    const shared_ptr<CAmigoImage> GetAmigoImage() const;

protected:
    bool InnerCanPlay();

private:
    int m_ElapsedTime;
    int m_CurrentCycle;//当前播放是第几遍
    int m_CurrentFrame;//当前播放到第几帧
    bool m_bAllowPlay; //是否允许播放（有的场景下，即使是动态GIF也不允许播放，所以要有这样一个设置）
    shared_ptr<CAmigoImage> m_spAmigoImage;
};
