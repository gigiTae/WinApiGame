#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"
CPathMgr::CPathMgr()
	: m_szContentPath{}
	, m_szRelativePath{}
{}
CPathMgr::~CPathMgr()
{
}


void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);
	
	int iLen = (int)wcslen(m_szContentPath);
	// 상위 폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;
	
	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen -iAbsLen);

	return strRelativePath;
}

// 커밋
