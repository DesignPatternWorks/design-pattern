#ifndef _ABSTRACT_FACTORY_H_
#define _ABSTRACT_FACTORY_H_
#include "common.h"
// 抽象工厂模式
/*
它的定义为提供一个创建一系列相关或相互依赖对象的接口，
而无需指定它们具体的类

多个抽象产品类，每个抽象产品类可以派生出多个具体产品类。   
一个抽象工厂类，可以派生出多个具体工厂类。   
每个具体工厂类可以创建多个相关的具体产品类（一系列相关产品）的实例
*/

/*
1、抽象工厂模式与工厂方法模式的区别
抽象工厂模式是工厂方法模式的升级版本，他用来创建一组相关或者相互依赖的对象。
他与工厂方法模式的区别就在于，工厂方法模式针对的是一个产品等级结构；而抽象工厂模式则是针对的多个产品等级结构。
在编程中，通常一个产品结构，表现为一个接口或者抽象类，也就是说，工厂方法模式提供的所有产品都是衍生自同一个接口或抽象类，
而抽象工厂模式所提供的产品则是衍生自不同的接口或抽象类。
在抽象工厂模式中，有一个产品族的概念：所谓的产品族，是指位于不同产品等级结构中功能相关联的产品组成的家族。
抽象工厂模式所提供的一系列产品就组成一个产品族；
而工厂方法提供的一系列产品称为一个等级结构。我们依然拿生产汽车的例子来说明他们之间的区别。

2、抽象工厂模式的优点
抽象工厂模式除了具有工厂方法模式的优点外，最主要的优点就是可以在类的内部对产品族进行约束。
所谓的产品族，一般或多或少的都存在一定的关联，抽象工厂模式就可以在类内部对产品族的关联关系进行定义和描述，而不必专门引入一个新的类来进行管理。

3、抽象工厂模式的缺点
产品族的扩展将是一件十分费力的事情，假如产品族中需要增加一个新的产品，则几乎所有的工厂类都需要进行修改。
所以使用抽象工厂模式时，对产品等级结构的划分是非常重要的。

4、适用场景
当需要创建的对象是一系列相互关联或相互依赖的产品族时，便可以使用抽象工厂模式。
说的更明白一点，就是一个继承体系中，如果存在着多个等级结构（即存在着多个抽象类），
并且分属各个等级结构中的实现类之间存在着一定的关联或者约束，就可以使用抽象工厂模式。假如各个等级结构中的实现类之间不存在关联或约束，
则使用多个独立的工厂来对产品进行创建，则更合适一点。
*/
void AbstractFactoryTest();

class AbstractProductA
{
public:
	virtual void ShowA() = 0;
};

class ProductA1 : public AbstractProductA
{
public:
	void ShowA()
	{
		cout << "I am Product A1" << endl;
	}
};

class ProductA2 : public AbstractProductA
{
public:
	void ShowA()
	{
		cout << "I am Product A2" << endl;
	}
};

class AbstractProductB
{
public:
	virtual void ShowB() = 0;
};

class ProductB1: public AbstractProductB
{
public:
	void ShowB()
	{
		cout << "I am Prouduct B1" << endl;
	}
};

class ProductB2: public AbstractProductB
{
public:
	void ShowB()
	{
		cout << "I am Prouduct B2" << endl;
	}
};

class AbstractFactoryAB
{
public:
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;
};

class Factory1: public AbstractFactoryAB
{
public:
	AbstractProductA* CreateProductA()
	{
		return new ProductA1();
	}
	AbstractProductB* CreateProductB()
	{
		return new ProductB1();
	}
};

class Factory2: public AbstractFactoryAB
{
public:
	AbstractProductA* CreateProductA()
	{
		return new ProductA2();
	}
	AbstractProductB* CreateProductB()
	{
		return new ProductB2();
	}
};

void AbstractFactoryTest()
{
	AbstractFactoryAB *pF1 = new Factory1();
	AbstractProductA *pPA1 = pF1->CreateProductA();
	pPA1->ShowA();
	AbstractProductB *pPB1 = pF1->CreateProductB();
	pPB1->ShowB();

	AbstractFactoryAB *pF2 = new Factory2();
	AbstractProductA *pPA2 = pF2->CreateProductA();
	pPA2->ShowA();
	AbstractProductB *pPB2 = pF2->CreateProductB();
	pPB2->ShowB();

	delete pF1; pF1 = NULL;
	delete pPA1; pPA1 = NULL;
	delete pPB1; pPB1 = NULL;
	delete pF2; pF2 = NULL;
	delete pPA2; pPA2 = NULL;
	delete pPB2; pPB2 = NULL;
}
#endif