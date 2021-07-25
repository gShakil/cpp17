#pragma once
#include <string>
/*
* 3 ��
c++ 17 �������� ������ �ذ�å �� �ϳ�.
�� ������� ������ ��⿡ ��� ������ ���Եǰ� ����ؼ� ��𼭵� ������ ���� �ν��Ͻ��� ���� ����
�׷��� �ش� ��ü�� ���α׷� ���۽ð� �ƴ� ù �Լ� ȣ��ÿ� �����ȴ�.
�̴� ���α׷��� ���۵� �� �߿��� ó���� �� ���� ���� ��ü�� �ʿ��� �� ������ �߻��Ѵ�. 

* 
*/
class foo 
{
public:
	static std::string& standard_string() {
		static std::string s{ "some string" };
	}

}

/*
* 2 ��
 C++17������ inline�� �ٴ´ٸ� ���� �ٸ� ��⿡ �ִ� ���� ���� ���� �ɺ��� ���Ǹ� ����� �� �ִ�.
 ��Ŀ�� ������ �ñ״�ó�� �� �������� �ɺ��� ã�Ҵµ�, �ζ������� ���ǵǾ� �ִٸ� ù ��° �ɺ��� �����ϰ�
 �ٸ� �ɺ��� ���� ���Ǹ� ���´ٰ� �ŷ��ϰ� �ȴ�.
*/
class CInlineLib
{
public:
	static const inline std::string standard_string;
	//{"some static globally avaliable string"};
	inline int ReturnnVal(int n1) { return m_nTestVal; };
protected:
	float ReturnfVal(int n1);
private:
	static inline int m_nTestVal;
	float m_fTestVal;
};
	
inline CInlineLib global_inline_lib;

/*
* 1 ��
* //�Ʒ��� ���� ����Ǿ��� �� CInclude_Ex1.cpp�� CInclude_Ex2.cpp���� #include "CInlineLib.h"�� ������ ���
* //LNK2005 ������ �Բ� �����Ͽ� �����Ѵ�.
class CInlineLib
{
public:
	static const std::string standard_string;
	//{"some static globally avaliable string"};
protected:

private:

};

CInlineLib global_inline_lib;
*/