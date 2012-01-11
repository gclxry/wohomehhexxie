
#pragma once

// 属性类型
enum OBJECT_TYPE_ID 
{
	OTID_NONE	= 0,
	OTID_BOOL	= 1,
	OTID_COLOR,
	OTID_COLOR_BASE,
	OTID_COMBOBOX,
	OTID_CURSOR,
	OTID_CURSOR_BASE,
	OTID_FONT,
	OTID_FONT_BASE,
	OTID_IMAGE,
	OTID_IMAGE_BASE,
	OTID_INT,
	OTID_STRING,
	OTID_GROUP,
	OTID_CONTROL,
	OTID_WINDOW,
	OTID_LAST
};

#define PROP_TYPE_BOOL_NAME						"bool"
#define PROP_TYPE_COLOR_NAME					"color"
#define PROP_TYPE_COLOR_BASE_NAME				"colorbase"
#define PROP_TYPE_COMBOBOX_NAME					"combobox"
#define PROP_TYPE_CURSOR_NAME					"cursor"
#define PROP_TYPE_CURSOR_BASE_NAME				"cursorbase"
#define PROP_TYPE_FONT_NAME						"font"
#define PROP_TYPE_FONT_BASE_NAME				"fontbase"
#define PROP_TYPE_IMAGE_NAME					"image"
#define PROP_TYPE_IMAGE_BASE_NAME				"imagebase"
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

	const char* GetObjectType();
	void SetObjectType(const char* pszObjType);
	OBJECT_TYPE_ID GetObjectTypeId();

	const char* GetObjectName();
	void SetObjectName(const char* pszObjName);

	const char* GetObjectInfo();
	void SetObjectInfo(const char* pszObjInfo);

	virtual void SetActivePropetry(bool bIsActive);
	virtual bool GetActivePropetry();

protected:
	// 是否为有效属性，在Builder保存属性时判断使用。
	bool m_bIsActiveProp;

private:
	string m_strObjId;
	string m_strObjType;
	string m_strObjName;
	string m_strObjInfo;
};
