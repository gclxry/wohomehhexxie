
#ifndef _JABBER_XML_H_
#define _JABBER_XML_H_

typedef enum enum_XmlNodeType{ ELEM_OPEN, ELEM_CLOSE, ELEM_OPENCLOSE, ELEM_TEXT } XmlElemType;
typedef enum enum_XXmlNodeType{ NODE_OPEN, NODE_CLOSE } XmlNodeType;

typedef struct tagXmlAttr {
	char *name;
	char *value;
} XmlAttr;

typedef struct tagXmlNode {
	int depth;									// depth of the current node (1=root)
	char *name;									// tag name of the current node
	int numAttr;								// number of attributes
	int maxNumAttr;								// internal use (num of slots currently allocated to attr)
	XmlAttr **attr;								// attribute list
	int numChild;								// number of direct child nodes
	int maxNumChild;							// internal use (num of slots currently allocated to child)
	struct tagXmlNode **child;					// child node list
	char *text;
	XmlNodeType state;							// internal use by parser
} XmlNode;
typedef void (*XMLPROC)(XmlNode *,void *);

typedef struct tagXmlState {
	XmlNode root;			// root is the document (depth = 0);
	// callback for depth=n element on opening/closing
	XMLPROC callback1_open;
	XMLPROC callback1_close;
	XMLPROC callback2_open;
	XMLPROC callback2_close;
	void *userdata1_open;
	void *userdata1_close;
	void *userdata2_open;
	void *userdata2_close;
} XmlState;

extern "C"  void JabberXmlInitState(XmlState *xmlState);
extern "C"  void JabberXmlDestroyState(XmlState *xmlState);
extern "C"  BOOL JabberXmlSetCallback(XmlState *xmlState, int depth, XmlElemType type, XMLPROC callback, void *userdata);
extern "C"  int JabberXmlParse(XmlState *xmlState, char *buffer, int datalen);
extern "C"  char *JabberXmlGetAttrValue(XmlNode *node, char *key);
extern "C"  int JabberXmlGetAttrCount(XmlNode *node);
extern "C"  char *JabberXmlGetAttr(XmlNode *node, int nIndex, char **ppkey);
extern "C"  XmlNode *JabberXmlGetChild(XmlNode *node, char *tag);
extern "C"  XmlNode *JabberXmlGetNthChild(XmlNode *node, char *tag, int nth);
extern "C"  XmlNode *JabberXmlGetNthChildWithoutTag(XmlNode *node, int nth);
extern "C"  XmlNode *JabberXmlGetChildWithGivenAttrValue(XmlNode *node, char *tag, char *attrKey, char *attrValue);
extern "C"  char* JabberXmlDumpAll(XmlState *xmlState);
extern "C"  XmlNode *JabberXmlCopyNode(XmlNode *node);
extern "C"  void JabberFreeDumpBuffer(char* buf);
extern "C"  void JabberXmlRemoveAttr(XmlNode* node,char* pKey);
extern "C"  void JabberXmlRemoveChild(XmlNode *node, XmlNode *child);

extern "C"  XmlNode *JabberXmlCreateNode(char *name);
extern "C"  void JabberXmlAddAttr(XmlNode *n, char *name, char *value);
extern "C"  XmlNode *JabberXmlAddChild(XmlNode *n, char *name);
extern "C"  void JabberXmlAddText(XmlNode *n, char *text);

#endif