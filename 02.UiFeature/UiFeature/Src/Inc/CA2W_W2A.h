
#pragma once

typedef vector<char*>	CHAR_VEC;
typedef vector<WCHAR*>	WCHAR_VEC;

class CA2W_W2A
{
public:
	CA2W_W2A();
	virtual ~CA2W_W2A();

	WCHAR* WideChar(char* pszMultiByte);
	WCHAR* WideChar(const char* pszMultiByte);
	char* MultiByte(WCHAR* pszWideChar);

private:
	CHAR_VEC m_CharVec;
	WCHAR_VEC m_WcharVec;
};

#define USES_CONVERSION_F		CA2W_W2A stringcovobj;
#define A2W_F(charstr)			stringcovobj.WideChar(charstr)
#define W2A_F(wcharstr)			stringcovobj.MultiByte(wcharstr)
