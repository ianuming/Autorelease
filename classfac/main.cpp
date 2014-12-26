// classfac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gobject.h"

class TestClass : public GObject
{
	DECLARE_GDYNAMIC_CLASS(TestClass)	// ��̬������һЩ����RTTI�ĳ�Ա
public:
	void print()
	{
		printf("Class Name is: %s \n", _classInfo.getClassName());
	}
};

IMPLEMENT_GDYNAMIC_CLASS(TestClass, GObject)	// ��̬��ʵ��һЩ����RTTI�ĳ�Ա

class TestClassB : public TestClass
{
	DECLARE_GDYNAMIC_CLASS(TestClassB)
};

IMPLEMENT_GDYNAMIC_CLASS(TestClassB, TestClass)

int main()
{
	TestClass* t = (TestClass*)GClassInfo::createObject("TestClassB");
	t->print();

	return 0;
}