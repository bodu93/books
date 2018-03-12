/*
 * 为类型CMyString实现赋值运算符函数
 */
#include <string.h>
#include <utility>

class CMyString {
public:
	CMyString(char* pData = NULL)
		: m_pData(new char[(pData ? strlen(pData) : 0) + 1])
	{
		m_pData[0] = '\0';
		if (pData)
			strncpy(m_pData, pData, strlen(pData) + 1);
	}

	CMyString(const CMyString& str)
		: CMyString(str.m_pData)
	{ }

	CMyString& operator=(const CMyString& str) {
		// call copy-ctor
		CMyString tmp(str);
		swap(tmp);
		return *this;
	}

	~CMyString() {
		delete[] m_pData;
	}

	void swap(CMyString& other) {
		std::swap(m_pData, other.m_pData);
	}
private:
	// null-terminated c-string
	char* m_pData;
};

int main() {
	CMyString s1("consolas");
	CMyString s2(s1);
	CMyString s3;
	s3 = s2;
	return 0;
}
