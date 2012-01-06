
/*
本类只实现了简单的xml流的生成，单根节点模式，节点名称不能超过60个字节
新创建的节点自动成为当前节点的子节点，新建节点变为当前节点
可以使用\root\parent\child绝对路径方式创建节点
只能一层一层的创建节点，不支持一次创建多层节点
*/

#ifndef __CUIXMLWRITE_H__
#define __CUIXMLWRITE_H__

#pragma warning(disable:4786)

#include <string>
#include <list>
#include <vector>
using namespace std;
typedef pair<string,string> STRPAIR;
static const char SCH = '"';

class CUiXmlWriteNode
{
public:
	CUiXmlWriteNode(const char* pszName)
	{
		const char* p = 0, *pN = pszName;
		do
		{
			p = strchr(pN, '\\');
			if (p == 0) break;
			pN = p+1;
			if (*pN == 0) break;
		} while (p);
		m_sName = pN;
	}
	virtual ~CUiXmlWriteNode()
	{
		for (vector<CUiXmlWriteNode*>::iterator it = m_vctChild.begin(); it != m_vctChild.end(); it++)
			delete (*it);
	}
	void SetText(const char* pszText){m_sText=pszText;}
	void AddChild(CUiXmlWriteNode* pNode){m_vctChild.push_back(pNode);}
	void AddAttribute(const char* pszName, const char* pszVal){m_lstAttribute.push_back(STRPAIR(pszName, pszVal));}
	CUiXmlWriteNode* SearchPath(CUiXmlWriteNode* pParent, const char* pszPathName)
	{
		if (pszPathName[0] == 0) 
			return pParent;
		const char* p = strchr(pszPathName, '\\');
		if (!p)
			return pParent;
		char szPath[64] = { 0 };
		strncpy_s(szPath, 64, pszPathName, p-pszPathName);
		for (vector<CUiXmlWriteNode*>::iterator it = m_vctChild.begin(); it != m_vctChild.end(); it++)
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
				sRet += "/>\n";
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
			for (vector<CUiXmlWriteNode*>::iterator it = m_vctChild.begin(); it != m_vctChild.end(); it++)
				sRet += (*it)->ToXmlString();
			if (m_sText.length() > 0)
				sRet += m_sText;
			sRet += "</";
			sRet += m_sName;
			sRet += ">\n";
		}
		return sRet;
	}
private:
	string m_sName;
	string m_sText;
	vector<CUiXmlWriteNode*> m_vctChild;
	list<STRPAIR> m_lstAttribute;
};

class CUiXmlWrite  
{
public:
	CUiXmlWrite() : m_pRoot(0), m_pActive(0){}
	virtual ~CUiXmlWrite(){if (m_pRoot) delete m_pRoot;}
	CUiXmlWriteNode* CreateNode(const char* pszName)
	{
		CUiXmlWriteNode* pNode = new CUiXmlWriteNode(pszName);
		if (pNode == NULL)
			return NULL;

		CUiXmlWriteNode* pActive = SearchPath(pszName);
		if (pActive)
			pActive->AddChild(pNode);
		else if (m_pRoot == 0)
			m_pRoot = pNode;

		m_pActive = pNode;
		return m_pActive;
	}

	CUiXmlWriteNode* CreateNode(CUiXmlWriteNode *pParentNode, const char* pszName)
	{
		CUiXmlWriteNode* pNode = new CUiXmlWriteNode(pszName);
		if (pNode == NULL)
			return NULL;

		if (pParentNode != NULL)
			pParentNode->AddChild(pNode);
		else if (m_pRoot == NULL)
			m_pRoot = pNode;

		m_pActive = pNode;
		return m_pActive;
	}

	CUiXmlWriteNode* SearchPath(const char* pszPathName)
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
	CUiXmlWriteNode* m_pRoot;
	CUiXmlWriteNode* m_pActive;
};

#endif // __CUIXMLWRITE_H__
