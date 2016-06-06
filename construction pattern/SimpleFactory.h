#ifndef _SIMPLE_FACTORY_H_
#define _SIMPLE_FACTORY_H_

// 简单工厂模式：
/*
一个抽象产品类，可以派生出多个具体产品类。   
一个具体工厂类，每个具体工厂类，根据传入参数不同，只能创建一个具体产品类的实例。。   

主要缺点:就是要增加新的产品类型时，就需要修改工厂类。这就违反了开放封闭原则
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