
// UiFeatureBuilderDoc.h : CUiFeatureBuilderDoc ��Ľӿ�
//


#pragma once


class CUiFeatureBuilderDoc : public CDocument
{
protected: // �������л�����
	CUiFeatureBuilderDoc();
	DECLARE_DYNCREATE(CUiFeatureBuilderDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CUiFeatureBuilderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSave();
};


