
#pragma once

//  Ù–‘¿‡–Õ
enum OBJECT_TYPE_ID 
{
	PT_NONE	= 0,
	PT_BOOL	= 1,
	PT_COLOR,
	PT_COMBOBOX,
	PT_CURSOR,
	PT_FONT,
	PT_IMAGE,
	PT_INT,
	PT_STRING,
	PT_GROUP,
	PT_CONTROL,
	PT_WINDOW,
	PT_LAST
};

#define PROP_TYPE_BOOL_NAME						"bool"
#define PROP_TYPE_COLOR_NAME					"color"
#define PROP_TYPE_COMBOBOX_NAME					"combobox"
#define PROP_TYPE_CURSOR_NAME					"cursor"
#define PROP_TYPE_FONT_NAME						"font"
#define PROP_TYPE_IMAGE_NAME					"image"
#define PROP_TYPE_INT_NAME						"int"
#define PROP_TYPE_STRING_NAME					"string"
#define PROP_TYPE_GROUP_NAME					"group"
#define PROP_TYPE_CONTROL_NAME					"control"
#define PROP_TYPE_WINDOW_NAME					"window"

class IFeatureObject
{
public:
	IFeatureObject();
	virtual ~IFeatureObject();

	const char* GetObjectId();
	void SetObjectId(const char* pszObjId);

	const char* GetObjectType();
	void SetObjectType(const char* pszObjType);
	OBJECT_TYPE_ID GetObjectTypeId();

	const char* GetObjectName();
	void SetObjectName(const char* pszObjName);

	const char* GetObjectInfo();
	void SetObjectInfo(const char* pszObjInfo);

private:
	string m_strObjId;
	string m_strObjType;
	string m_strObjName;
	string m_strObjInfo;
};