#ifndef _SIMPLE_FACTORY_H_
#define _SIMPLE_FACTORY_H_

// �򵥹���ģʽ��
/*
һ�������Ʒ�࣬������������������Ʒ�ࡣ   
һ�����幤���࣬ÿ�����幤���࣬���ݴ��������ͬ��ֻ�ܴ���һ�������Ʒ���ʵ������   

��Ҫȱ��:����Ҫ�����µĲ�Ʒ����ʱ������Ҫ�޸Ĺ����ࡣ���Υ���˿��ŷ��ԭ��
*/
#include "common.h"

void SimpleFactoryTest();

class AbstractProduct
{
public:
	virtual void Show() = 0;
};

class ProductA: public AbstractProduct
{
public:
	void Show()
	{
		cout << "I am Product A" << endl;
	}
};

class ProductB: public AbstractProduct
{
public:
	void Show()
	{
		cout << "I am Product B" << endl;
	}
};

class SimpleFactory
{
public:
	static AbstractProduct* CreateProduct(int ProductType)
	{
		switch (ProductType)
		{
		case 1:
			return new ProductA();
			break;
		case 2:
			return new ProductB();
			break;
		default:
			return NULL;
			break;
		}
	}
};

void SimpleFactoryTest()
{
	AbstractProduct *pPA = SimpleFactory::CreateProduct(1);
	pPA->Show();
	AbstractProduct *pPB = SimpleFactory::CreateProduct(2);
	pPB->Show();

	delete pPA; pPA = NULL;
	delete pPB; pPB = NULL;
};

#endif