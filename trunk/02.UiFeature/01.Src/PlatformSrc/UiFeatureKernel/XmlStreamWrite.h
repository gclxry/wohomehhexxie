// XmlStreamWrite.h: interface for the CXmlStreamWrite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLSTREAMWRITE_H__B4821692_AE63_40DA_9BFA_16BA533FD5A0__INCLUDED_)
#define AFX_XMLSTREAMWRITE_H__B4821692_AE63_40DA_9BFA_16BA533FD5A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

/*
	本类只实现了简单的xml流的生成，单根节点模式，节点名称不能超过60个字节
	新创建的节点自动成为当前节点的子节点，新建节点变为当前节点
	可以使用\root\parent\child绝对路径方式创建节点
	只能一层一层的创建节点，不支持一次创建多层节点
*/

#include <string>
#include <list>
#include <vector>
using namespace std;
typedef pair<string,string> STRPAIR;
static const char SCH = '"';
class CNode
{
public:
	CNode(const char* pszName)
	{
		const char* p = 0, *pN = pszName;
		do
		{
			p = strchr(pN, '\\');
			if (p == 0) break;
			pN = p+1;
			if (*pN == 0) break;
		} while(p);
		m_sName = pN;
	}
	virtual ~CNode()
	{
		for (vector<CNode*>::iterator it = m_vctChild.begin(); it != m_vctChild.end(); it++)
			delete (*it);
	}
	void SetText(const char* pszText){m_sText=pszText;}
	void AddChild(CNode* pNode){m_vctChild.push_back(pNode);}
	void AddAttribute(const char* pszName, const char* pszVal){m_lstAttribute.push_back(STRPAIR(pszName, pszVal));}
	CNode* SearchPath(CNode* pParent, const char* pszPathName)
	{
		if (pszPathName[0] == 0) 
			return pParent;
		const char* p = strchr(pszPathName, '\\');
		if (!p)
			return pParent;
		char szPath[64] = { 0 };
		strncpy_s(szPath, 64, pszPathName, p-pszPathName);
		for (vector<CNode*>::iterator it = m_vctChild.begin(); it != m_vctChild.end(); it++)
		{
			if (_stricmp((*it)->m_sName.c_str(), szPath) == 0)
				return (*it)->SearchPath((*it), p+1);
		}
		return pParent;
	}
	string ToXmlString()
	{
		string sRet = "<";
		sRet += m_sName;
		if (m_lstAttribute.size() > 0)
		{
			for (list<STRPAIR>::iterator it = m_lstAttribute.begin(); it != m_lstAttribute.end(); it++)
			{
				sRet += " ";
				sRet += it->first;
				sRet += "=";
				sRet += SCH;
				sRet += it->second;
				sRet += SCH;
			}
		}
		if (m_vctChild.size() == 0)
		{
			if (m_sText.length() == 0)
				sRet += " />";
			else
			{
				sRet += ">";
				sRet += m_sText;
				sRet += "</";
				sRet += m_sName;
				sRet += ">";
			}
		}
		else 
		{
			sRet += ">";
			for (vector<CNode*>::iterator it = m_vctChild.begin(); it != m_vctChild.end(); it++)
				sRet += (*it)->ToXmlString();
			if (m_sText.length() > 0)
				sRet += m_sText;
			sRet += "</";
			sRet += m_sName;
			sRet += ">";
		}
		return sRet;
	}
private:
	string m_sName;
	string m_sText;
	vector<CNode*> m_vctChild;
	list<STRPAIR> m_lstAttribute;
};

class CXmlStreamWrite  
{
public:
	CXmlStreamWrite() : m_pRoot(0), m_pActive(0){}
	virtual ~CXmlStreamWrite(){if (m_pRoot) delete m_pRoot;}
	CNode* CreateNode(const char* pszName)
	{
		CNode* pNode = new CNode(pszName);
		if (pNode == NULL)
			return NULL;

		CNode* pActive = SearchPath(pszName);
		if (pActive)
			pActive->AddChild(pNode);
		else if (m_pRoot == 0)
			m_pRoot = pNode;

		m_pActive = pNode;
		return m_pActive;
	}

	CNode* CreateNode(CNode *pParentNode, const char* pszName)
	{
		CNode* pNode = new CNode(pszName);
		if (pNode == NULL)
			return NULL;

		if (pParentNode != NULL)
			pParentNode->AddChild(pNode);
		else if (m_pRoot == NULL)
			m_pRoot = pNode;

		m_pActive = pNode;
		return m_pActive;
	}

	CNode* SearchPath(const char* pszPathName)
	{
		if (m_pRoot == 0)
			return 0;
		if (pszPathName[0] == '\\')
		{
			if (pszPathName[1] == 0)
				return 0;
			const char* pNext = strchr(pszPathName+1, '\\');
			if (pNext == 0)
				return 0;
			return m_pRoot->SearchPath(m_pRoot, pNext+1);
		}
		else
			return m_pActive->SearchPath(m_pActive, pszPathName);
	}
	string ToXmlString()
	{
		if (m_pRoot)
			return m_pRoot->ToXmlString();
		return "";
	}
private:
	CNode* m_pRoot;
	CNode* m_pActive;
};

#endif // !defined(AFX_XMLSTREAMWRITE_H__B4821692_AE63_40DA_9BFA_16BA533FD5A0__INCLUDED_)
