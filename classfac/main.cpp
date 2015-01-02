// classfac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gobject.h"
#include "autoreleasepool.h"
#include "gdata.h"

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
    GAutoreleasePool * atp = (GAutoreleasePool*)GAutoreleasePool::createObject();

	TestClass* t = (TestClass*)GClassInfo::createObject("TestClassB");

	t->print();
    t->autorelease();

    GData* pdata = (GData*)GClassInfo::createObject("GData");
    pdata->setBool("b", true);
    pdata->setInt("i", 1983);

    bool b = pdata->getBool("b3");
    int i = pdata->getInt("i2");

    pdata->delField("b");

    pdata->release();

    atp->release();

	return 0;
}