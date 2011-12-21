/*

 Jabber Protocol Plugin for Miranda IM
 Copyright (C) 2002-2004  Santithorn Bunchua
 
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	
*/
#include "stdafx.h"
#include <ctype.h>
#include <stdlib.h>
#include "..\..\Inc\CUiXmlParser.h"

#pragma warning(disable:4018)
#pragma warning(disable:4996)

char* mystrdup(const char* pszSrc)
{
	if (pszSrc)
	{
		size_t sl = strlen(pszSrc);
		char* pszDest = (char*)malloc(sl+1);
		if (pszDest)
		{
			memset(pszDest, 0, sl+1);
			if (sl > 0)
				memcpy(pszDest, pszSrc, sl);
			return pszDest;
		}
	}
	return 0;
}

void JabberXmlFreeNode(XmlNode *node);
int JabberXmlDumpNode(XmlNode *node,char** str,int& nSize);
BOOL JabberXmlProcessElem(XmlState *xmlState, XmlElemType elemType, char *elemText, size_t textSize, char *elemAttr, size_t attrSize);
void JabberXmlRemoveChild(XmlNode *node, XmlNode *child);
int  JabberXmlGetAttrIndex(XmlNode* node,char* pKey);
void CopyString(char** src,char* dst,int& srcSize)
{
	if(strlen(*src)+strlen(dst) >= srcSize)
	{
		srcSize += strlen(dst)>4096?strlen(dst):4096;
		*src = (char*)realloc(*src,srcSize);
	}
	strcat(*src,dst);
}

void JabberXmlInitState(XmlState *xmlState)
{
	if (xmlState == NULL) return;
	xmlState->root.name = NULL;
	xmlState->root.depth = 0;
	xmlState->root.numAttr = 0;
	xmlState->root.maxNumAttr = 0;
	xmlState->root.attr = NULL;
	xmlState->root.numChild = 0;
	xmlState->root.maxNumChild = 0;
	xmlState->root.child = NULL;
	xmlState->root.text = NULL;
	xmlState->root.state = NODE_OPEN;
	xmlState->callback1_open = NULL;
	xmlState->callback1_close = NULL;
	xmlState->callback2_open = NULL;
	xmlState->callback2_close = NULL;
	xmlState->userdata1_open = NULL;
	xmlState->userdata1_close = NULL;
	xmlState->userdata2_open = NULL;
	xmlState->userdata2_close = NULL;
}

void JabberXmlDestroyState(XmlState *xmlState)
{
	XmlNode *node = NULL;
	
	if (xmlState == NULL)
		return;
	// Note: cannot use JabberXmlFreeNode() to free xmlState->root
	// because it will do free(xmlState->root) which is not freeable.
	node = &(xmlState->root);
	// Free all children first
	int i = 0;
	for (i=0; i<node->numChild; i++)
		JabberXmlFreeNode(node->child[i]);
	if (node->child)
		free(node->child);
	// Free all attributes
	for (i=0; i<node->numAttr; i++)
	{
		if (node->attr[i]->name)
			free(node->attr[i]->name);
		if (node->attr[i]->value)
			free(node->attr[i]->value);
		free(node->attr[i]);
	}
	if (node->attr)
		free(node->attr);
	// Free string field
	if (node->text)
		free(node->text);
	if (node->name)
		free(node->name);
}

BOOL JabberXmlSetCallback(XmlState *xmlState, int depth, XmlElemType type, XMLPROC callback, void *userdata)
{
	if (depth==1 && type==ELEM_OPEN) {
		xmlState->callback1_open = callback;
		xmlState->userdata1_open = userdata;
	}
	else if (depth==1 && type==ELEM_CLOSE) {
		xmlState->callback1_close = callback;
		xmlState->userdata1_close = userdata;
	}
	else if (depth==2 && type==ELEM_OPEN) {
		xmlState->callback2_open = callback;
		xmlState->userdata2_open = userdata;
	}
	else if (depth==2 && type==ELEM_CLOSE) {
		xmlState->callback2_close = callback;
		xmlState->userdata2_close = userdata;
	}
	else
		return FALSE;
	
	return TRUE;
}

#define TAG_MAX_LEN 50
#define ATTR_MAX_LEN 1024
inline int _IsSpace(int c)
{
	return ((c >= 0x09 && c<= 0x0D) || (c == 0x20)) ? c:0;
}
int JabberXmlParse(XmlState *xmlState, char *buffer, int datalen)
{
	char *p = NULL, *q = NULL, *r = NULL, *eob = NULL;
	char *str = NULL;
	int num, count = 0;
	char tag[TAG_MAX_LEN];
	char attr[ATTR_MAX_LEN];
	XmlElemType elemType;
	
	eob = buffer + datalen;
	num = 0;

	// Skip leading whitespaces
	//{/hongyq 2006-01-13 
	//for (p=buffer; p<eob && isspace(*p); p++,num++);
	for (p=buffer; p<eob && _IsSpace(*p); p++,num++);
	//}/hongyq 2006-01-13
	if(*p=='<' && *(p+1)=='?')
	{
		p = strstr(p,"?>");
		if(p)
			p += 2;
	}
	while (*p != '<') p++;
	while (num < datalen)
	{
		if (*p == '<')
		{	// found starting bracket			
			//for (q=p+1; q<eob && *q!='>'; q++);
			for (q=p+1; q<eob;q++)  
			{ 
				if(*q=='\'' && count==0)
				{ 
					count++;
					continue;
				}
				if(*q=='\'' && count>0)
				{ 
					count--;
					continue;
				}
				if(*q=='>' && count==0)
					break;
			}

			if (q < eob) 
			{	// found closing bracket
				for (r=p+1; *r!='>' && *r!=' ' && *r!='\t'; r++);
				if (r-(p+1) > TAG_MAX_LEN) 
				{
					//Log("TAG_MAX_LEN too small, ignore current tag");
				}
				else 
				{
					if (*(p+1) == '/') 
					{	// closing tag
						strncpy(tag, p+2, r-(p+2));
						tag[r-(p+2)] = '\0';
						elemType = ELEM_CLOSE;
					}
					else 
					{
						if (*(r-1) == '/') 
						{	// single open/close tag
							strncpy(tag, p+1, r-(p+1)-1);
							tag[r-(p+1)-1] = '\0';
							elemType = ELEM_OPENCLOSE;
						}
						else 
						{
							strncpy(tag, p+1, r-(p+1));
							tag[r-(p+1)] = '\0';
							elemType = ELEM_OPEN;
						}
					}
					for (;r<q && (*r==' ' || *r=='\t'); r++);
					if (q-r > ATTR_MAX_LEN) 
					{
						;//Log("ATTR_MAX_LEN too small, ignore current tag");
					}
					else 
					{
						strncpy(attr, r, q-r);
						if ((q-r)>0 && attr[q-r-1]=='/') 
						{
							attr[q-r-1] = '\0';
							elemType = ELEM_OPENCLOSE;
						}
						else
							attr[q-r] = '\0';
						JabberXmlProcessElem(xmlState, elemType, tag, strlen(tag), attr, strlen(attr));
					}
				}
				num += (q-p+1);
				p = q + 1;
				if (elemType==ELEM_CLOSE || elemType==ELEM_OPENCLOSE) 
				{
					// Skip whitespaces after end tags
					for (; p<eob && _IsSpace(*p); p++,num++);
				}
			}
			else
				break;
		}
		else 
		{	// found inner text
			for (q=p+1; q<eob && *q!='<'; q++);
			if (q < eob) 
			{	// found starting bracket of the next element
				//str = (char *) malloc(q-p+1);
				//strncpy(str, p, q-p);
				//str[q-p] = '\0';
				JabberXmlProcessElem(xmlState, ELEM_TEXT, p, q-p, NULL, 0);
				//free(str);
				num += (q-p);
				p = q;
			}
			else
				break;
		}
	}	
	return num;
}

void JabberXmlParseAttr(XmlNode *node, char *text)
{
	char *kstart = NULL, *vstart = NULL;
	int klen, vlen;
	char *p = NULL;
	XmlAttr *a;
	
	if (node==NULL || text==NULL || strlen(text)<=0)
		return;
	
	for (p=text;;) {
		
		// Skip leading whitespaces
		for (;*p!='\0' && (*p==' ' || *p=='\t'); p++);
		if (*p == '\0')
			break;
		
		// Fetch key
		kstart = p;
		for (;*p!='\0' && *p!='=' && *p!=' ' && *p!='\t'; p++);
		klen = p-kstart;
		
		if (node->numAttr >= node->maxNumAttr) {
			node->maxNumAttr = node->numAttr + 20;
			node->attr = (XmlAttr **) realloc(node->attr, node->maxNumAttr*sizeof(XmlAttr *));
		}
		a = node->attr[node->numAttr] = (XmlAttr *) malloc(sizeof(XmlAttr));
		node->numAttr++;
		
		// Skip possible whitespaces between key and '='
		for (;*p!='\0' && (*p==' ' || *p=='\t'); p++);
		
		if (*p == '\0') {
			a->name = (char *) malloc(klen+1);
			strncpy(a->name, kstart, klen);
			a->name[klen] = '\0';
			a->value = mystrdup("");
			break;
		}
		
		if (*p != '=') {
			a->name = (char *) malloc(klen+1);
			strncpy(a->name, kstart, klen);
			a->name[klen] = '\0';
			a->value = mystrdup("");
			continue;
		}
		
		// Found '='
		p++;
		
		// Skip possible whitespaces between '=' and value
		for (;*p!='\0' && (*p==' ' || *p=='\t'); p++);
		
		if (*p == '\0') {
			a->name = (char *) malloc(klen+1);
			strncpy(a->name, kstart, klen);
			a->name[klen] = '\0';
			a->value = mystrdup("");
			break;
		}
		
		// Fetch value
		if (*p=='\'' || *p=='"') {
			p++;
			vstart = p;
			for (;*p!='\0' && *p!=*(vstart-1); p++);
			vlen = p-vstart;
			if (*p != '\0') p++;
		}
		else {
			vstart = p;
			for (;*p!='\0' && *p!=' ' && *p!='\t'; p++);
			vlen = p-vstart;
		}
		
		a->name = (char *) malloc(klen+1);
		strncpy(a->name, kstart, klen);
		a->name[klen] = '\0';
		a->value = (char *) malloc(vlen+1);
		strncpy(a->value, vstart, vlen);
		a->value[vlen] = '\0';
	}
}

BOOL JabberXmlProcessElem(XmlState *xmlState, XmlElemType elemType, char *elemText, size_t textSize, char *elemAttr, size_t attrSize)
{
	XmlNode *node = NULL, *parentNode = NULL, *n = NULL;
	BOOL activateCallback = FALSE;
	char *text = NULL, *attr = NULL;
	
	if (elemText == NULL) return FALSE;

	// skip comment
	if (elemType==ELEM_OPEN && elemText[0] == '!' && elemText[1] == '-' && elemText[2] == '-') 
	{
		return TRUE;
	}
	
	// Find active node
	node = &(xmlState->root);
	parentNode = NULL;
	while (node->numChild>0 && node->child[node->numChild-1]->state==NODE_OPEN) {
		parentNode = node;
		node = node->child[node->numChild-1];
	}
	
	if (node->state != NODE_OPEN) return FALSE;
	
	//text = mystrdup(elemText);
	text = (char*)malloc(textSize+1);
	char* pS = elemText;
	char* pD = text;
	while (pS<elemText+textSize)
		*pD++ = *pS++;
	*pD = 0;
	
	if (elemAttr && elemAttr[0])
	{
		// modified by haoyongjian,from mystrdup to memcpy,because boundscheck report overrun error,but in fact,no errorss
		attr = mystrdup(elemAttr);
	}
	else
		attr = NULL;
	
	switch (elemType) {
	case ELEM_OPEN:
		if (node->numChild >= node->maxNumChild) 
		{
			if (node->numChild > 20000)
				node->maxNumChild = node->numChild + 10000;
			else if (node->numChild > 10000)
				node->maxNumChild = node->numChild + 5000;
			else if (node->numChild > 5000)
				node->maxNumChild = node->numChild + 2500;
			else
				node->maxNumChild = node->numChild + 200;
			struct tagXmlNode** pTmp = (XmlNode **) realloc(node->child, node->maxNumChild*sizeof(XmlNode *));
			if (pTmp == 0)
			{
				OutputDebugStringA("----no memory----\r\n");
				MessageBoxA(NULL, "ÄÚ´æ²»×ã", "error", MB_OK | MB_ICONERROR);
			}
			node->child = pTmp;
		}
		n = node->child[node->numChild] = (XmlNode *) malloc(sizeof(XmlNode));
		if (n)
		{
			node->numChild++;
			n->name = text;
			n->depth = node->depth + 1;
			n->state = NODE_OPEN;
			n->numChild = n->maxNumChild = 0;
			n->child = NULL;
			n->numAttr = n->maxNumAttr = 0;
			n->attr = NULL;
			JabberXmlParseAttr(n, attr);
			n->text = NULL;
			if (n->depth==1 && xmlState->callback1_open!=NULL)
				(*(xmlState->callback1_open))(n, xmlState->userdata1_open);
			if (n->depth==2 && xmlState->callback2_open!=NULL)
				(*xmlState->callback2_open)(n, xmlState->userdata2_open);
		}
		break;
	case ELEM_OPENCLOSE:
		if (node->numChild >= node->maxNumChild) 
		{
			node->maxNumChild = node->numChild + 20;
			node->child = (XmlNode **) realloc(node->child, node->maxNumChild*sizeof(XmlNode *));
		}
		n = node->child[node->numChild] = (XmlNode *) malloc(sizeof(XmlNode));
		node->numChild++;
		n->name = text;
		n->depth = node->depth + 1;
		n->state = NODE_CLOSE;
		n->numChild = n->maxNumAttr = 0;
		n->child = NULL;
		n->numAttr = n->maxNumAttr = 0;
		n->attr = NULL;
		JabberXmlParseAttr(n, attr);
		n->text = NULL;
		if (n->depth == 1 && xmlState->callback1_close!=NULL) 
		{
			(*(xmlState->callback1_close))(n, xmlState->userdata1_close);
			JabberXmlRemoveChild(node, n);
		}
		else if (n->depth == 2 && xmlState->callback2_close!=NULL) 
		{
			(*xmlState->callback2_close)(n, xmlState->userdata2_close);
			JabberXmlRemoveChild(node, n);
		}
		break;
	case ELEM_CLOSE:
		if (node->name!=NULL && !lstrcmpi(node->name, text)) 
		{
			node->state = NODE_CLOSE;
			if (node->depth==1 && xmlState->callback1_close!=NULL) 
			{
				(*(xmlState->callback1_close))(node, xmlState->userdata1_close);
				JabberXmlRemoveChild(parentNode, node);
			}
			else if (node->depth==2 && xmlState->callback2_close!=NULL) 
			{
				(*xmlState->callback2_close)(node, xmlState->userdata2_close);
				JabberXmlRemoveChild(parentNode, node);
			}
			free(text);
		}
		else 
		{
			//Log("XML: Closing </%s> without opening tag", text);
			if (text) free(text), text=0;
			if (attr) free(attr), text=0;
			return FALSE;
		}
		break;
	case ELEM_TEXT:
		node->text = text;
		break;
	default:
		if (text) free(text), text=0;
		if (attr) free(attr), attr=0;
		return FALSE;
	}
	
	if (attr) free(attr);
	
	return TRUE;
}

int JabberXmlGetAttrCount(XmlNode *node)
{
	if (node==NULL || node->numAttr<=0)
		return 0;
	return node->numAttr;
}

char *JabberXmlGetAttr(XmlNode *node, int nIndex, char **ppkey)
{
	if (node==NULL || node->numAttr<=0 || ppkey==NULL)
		return NULL;
	if (nIndex<node->numAttr) {
		*ppkey = node->attr[nIndex]->name;
		return node->attr[nIndex]->value;
	}
	return NULL;
}

char *JabberXmlGetAttrValue(XmlNode *node, char *key)
{
	int i;
	
	if (node==NULL || node->numAttr<=0 || key==NULL || strlen(key)<=0)
		return NULL;
	for (i=0; i<node->numAttr; i++) {
		if (node->attr[i]->name && !lstrcmpi(key, node->attr[i]->name))
			return node->attr[i]->value;
	}
	return NULL;
}

XmlNode *JabberXmlGetChild(XmlNode *node, char *tag)
{
	return JabberXmlGetNthChild(node, tag, 1);
}

XmlNode *JabberXmlGetNthChild(XmlNode *node, char *tag, int nth)
{
	int i, num;
	
	if (node==NULL || node->numChild<=0 || tag==NULL || strlen(tag)<=0 || nth<1)
		return NULL;
	num = 1;
	for (i=0; i<node->numChild; i++) {
		if (node->child[i]->name && !lstrcmpi(tag, node->child[i]->name)) {
			if (num == nth) {
				return node->child[i];
			}
			num++;
		}
	}
	return NULL;
}

XmlNode *JabberXmlGetNthChildWithoutTag(XmlNode *node, int nth)
{
	if (node==NULL || node->numChild<=0)
		return NULL;
	
	return node->child[nth];
}

XmlNode *JabberXmlGetChildWithGivenAttrValue(XmlNode *node, char *tag, char *attrKey, char *attrValue)
{
	int i;
	char *str = NULL;
	
	if (node==NULL || node->numChild<=0 || tag==NULL || strlen(tag)<=0 || attrKey==NULL || strlen(attrKey)<=0 || attrValue==NULL || strlen(attrValue)<=0)
		return NULL;
	for (i=0; i<node->numChild; i++) {
		if (node->child[i]->name && !lstrcmpi(tag, node->child[i]->name)) {
			if ((str=JabberXmlGetAttrValue(node->child[i], attrKey)) != NULL)
				if (!lstrcmpi(str, attrValue))
					return node->child[i];
		}
	}
	return NULL;
}

char* JabberXmlDumpAll(XmlState *xmlState)
{
	XmlNode *root = NULL;
	int i;
	
	//Log("XML: DUMPALL: ------------------------");
	root = &(xmlState->root);
	if (root->numChild <= 0)
	{
		//Log("XML: DUMPALL: NULL");
		return NULL;
	}
	else {
		char* buf = (char*)malloc(4096);
		strcpy(buf,"");
		int nSize = 4096;
		CopyString(&buf,"<?xml version=\"1.0\" encoding=\"gb2312\" ?>\r\n",nSize);
		for (i=0; i<root->numChild; i++)
			JabberXmlDumpNode(root->child[i],&buf,nSize);
		return buf;
	}
	//Log("XML: DUMPALL: ------------------------");
}
#define NODE_SPACE "  "
int JabberXmlDumpNode(XmlNode *node,char** str,int& nSize)
{
	int i;
	
	if (node == NULL)
	{
		//Log("XML: DUMP: NULL");
		return strlen(*str);
	}
	
	for (i=0; i<node->depth-1; i++)
		CopyString(str, NODE_SPACE,nSize);
	CopyString(str, "<",nSize);
	if (node->name)
		CopyString(str, node->name,nSize);
	else
		CopyString(str, "(NULL)",nSize);
	for (i=0; i<node->numAttr; i++)
	{
		CopyString(str, " ",nSize);
		if (node->attr[i]->name)
			CopyString(str, node->attr[i]->name,nSize);
		else
			CopyString(str, "(NULL)",nSize);
		CopyString(str, "=",nSize);
		if (node->attr[i]->value)
		{
			CopyString(str, "'",nSize);
			CopyString(str, node->attr[i]->value,nSize);
			CopyString(str, "'",nSize);
		}
	}
	if (node->text || node->numChild>0)
	{
		CopyString(str, ">\r\n",nSize);
		if (node->text)
		{
			char* p = node->text;
			while(_IsSpace(*p)) p++;
			for (i=0; i<node->depth-1; i++)
				CopyString(str, NODE_SPACE,nSize);
			CopyString(str,p,nSize);

		}
		if (node->numChild > 0)
		{
			//Log("XML: DUMP: %s", str);
			for (i=0; i<node->numChild; i++)
				JabberXmlDumpNode(node->child[i],str,nSize);
			for (i=0; i<node->depth-1; i++)
				CopyString(str, NODE_SPACE,nSize);
		}
//		if (node->state != NODE_OPEN)
		{
			CopyString(str, "</",nSize);
			CopyString(str, node->name,nSize);
			CopyString(str, ">\r\n",nSize);
		}
	}
	else
	{
//		if (node->state != NODE_OPEN)
			CopyString(str, "/>\r\n",nSize);
	}
	
	//Log("XML: DUMP: %s", str);
	return strlen(*str);
}
void JabberFreeDumpBuffer(char* buf)
{
	if(buf)
		free(buf);
}

void JabberXmlRemoveChild(XmlNode *node, XmlNode *child)
{
	int i;
	
	if (node==NULL || child==NULL || node->numChild<=0) return;
	for (i=0; i<node->numChild; i++)
	{
		if (node->child[i] == child)
			break;
	}
	if (i < node->numChild)
	{
		for (++i; i<node->numChild; i++)
			node->child[i-1] = node->child[i];
		node->numChild--;
		JabberXmlFreeNode(child);
	}
}

void JabberXmlFreeNode(XmlNode *node)
{
	int i = 0;
	
	if (node == NULL) 
		return;
	// Free all children first
	for (i=0; i<node->numChild; i++)
		JabberXmlFreeNode(node->child[i]);
	if (node->child) 
	{
		free(node->child);
		node->child = 0;
	}
	// Free all attributes
	for (i=0; i<node->numAttr; i++)
	{
		if (node->attr[i])
		{
			if (node->attr[i]->name) 
			{
				free(node->attr[i]->name);
				node->attr[i]->name = 0;
			}
			if (node->attr[i]->value) 
			{
				free(node->attr[i]->value);
				node->attr[i]->value = 0;
			}
			free(node->attr[i]);
			node->attr[i] = 0;
		}
	}
	if (node->attr) 
	{
		free(node->attr);
		node->attr = 0;
	}
	// Free string field
	if (node->text)
	{
		free(node->text);
		node->text = 0;
	}
	if (node->name) 
	{
		free(node->name);
		node->name = 0;
	}
	// Free the node itself
	free(node);
	node = 0;
}

XmlNode *JabberXmlCopyNode(XmlNode *node)
{
	XmlNode *n = NULL;
	int i;
	
	if (node == NULL) return NULL;
	n = (XmlNode *) malloc(sizeof(XmlNode));
	// Copy attributes
	if (node->numAttr > 0) {
		n->attr = (XmlAttr **) malloc(node->numAttr*sizeof(XmlAttr *));
		for (i=0; i<node->numAttr; i++) {
			n->attr[i] = (XmlAttr *) malloc(sizeof(XmlAttr));
			if (node->attr[i]->name) n->attr[i]->name = mystrdup(node->attr[i]->name);
			else n->attr[i]->name = NULL;
			if (node->attr[i]->value) n->attr[i]->value = mystrdup(node->attr[i]->value);
			else n->attr[i]->value = NULL;
		}
	}
	else
		n->attr = NULL;
	// Recursively copy children
	if (node->numChild > 0) {
		n->child = (XmlNode **) malloc(node->numChild*sizeof(XmlNode *));
		for (i=0; i<node->numChild; i++)
			n->child[i] = JabberXmlCopyNode(node->child[i]);
	}
	else
		n->child = NULL;
	// Copy other fields
	n->numAttr = node->numAttr;
	n->maxNumAttr = node->numAttr;
	n->numChild = node->numChild;
	n->maxNumChild = node->numChild;
	n->depth = node->depth;
	n->state = node->state;
	n->name = (node->name)?mystrdup(node->name):NULL;
	n->text = (node->text)?mystrdup(node->text):NULL;
	
	return n;
}

XmlNode *JabberXmlCreateNode(char *name)
{
	XmlNode *n = NULL;
	
	if (name == NULL)
		return NULL;
	
	n = (XmlNode *) malloc(sizeof(XmlNode));
	memset(n, 0, sizeof(XmlNode));
	n->name = mystrdup(name);
	return n;
}

void JabberXmlAddAttr(XmlNode *n, char *name, char *value)
{
	int i;
	
	if (n==NULL || name==NULL || value==NULL)
		return;
	i = JabberXmlGetAttrIndex(n,name);
	if(i<0)
	{
		i = n->numAttr;
		(n->numAttr)++;
		n->attr = (XmlAttr **) realloc(n->attr, sizeof(XmlAttr *) * n->numAttr);
		n->attr[i] = (XmlAttr *) malloc(sizeof(XmlAttr));
		memset(n->attr[i],0,sizeof(XmlAttr));

	}
	if(n->attr[i]->name) free(n->attr[i]->name);
	if(n->attr[i]->value) free(n->attr[i]->value);
	n->attr[i]->name = mystrdup(name);
	n->attr[i]->value = mystrdup(value);
}

XmlNode *JabberXmlAddChild(XmlNode *n, char *name)
{
	int i;
	
	if (n==NULL || name==NULL)
		return NULL;
	
	i = n->numChild;
	n->numChild++;
	n->child = (XmlNode **) realloc(n->child, sizeof(XmlNode *) * n->numChild);
	n->child[i] = (XmlNode *) malloc(sizeof(XmlNode));
	memset(n->child[i], 0, sizeof(XmlNode));
	n->child[i]->name = mystrdup(name);
	n->child[i]->depth = n->depth+1;
	return n->child[i];
}

void JabberXmlAddText(XmlNode *n, char *text)
{
	if (n!=NULL && text!=NULL) {
		if (n->text) free(n->text);
		n->text = mystrdup(text);
	}
}
int  JabberXmlGetAttrIndex(XmlNode* node,char* pKey)
{
	if(!node)
		return -1;
	for (int i=0;i<node->numAttr;i++)
	{
		if(strcmpi(node->attr[i]->name,pKey)==0)
			return i;
	}
	return -1;
}
void JabberXmlRemoveAttr(XmlNode* node,char* pKey)
{
	int i = JabberXmlGetAttrIndex(node,pKey);
	if(i >= 0)
	{
		if(node->attr[i]->value) free(node->attr[i]->value);
		if(node->attr[i]->name) free(node->attr[i]->name);
		free(node->attr[i]);
		for(++i;i<node->numAttr;i++)
		{
			node->attr[i-1] = node->attr[i];
		}
		node->numAttr--;
	}
}