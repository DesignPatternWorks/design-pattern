#ifndef _FACTORY_METHOD_H_
#define _FACTORY_METHOD_H_

#include "common.h"

// 工厂方法模式
/*
所谓工厂方法模式，是指定义一个用于创建对象的接口
让子类决定实例化哪一个类。Factory Method使一个类的实例化延迟到其子类

一个抽象产品类，可以派生出多个具体产品类。   
一个抽象工厂类，可以派生出多个具体工厂类。   
每个具体工厂类只能创建一个具体产品类的实例。

优点：符合开闭原则
缺点：增加一种产品，就要添加一个相应的工厂类
*/

/*
1、 优点：
1）可以使代码结构清晰，有效地封装变化。在编程中，产品类的实例化有时候是比较复杂和多变的，通过工厂模式，将产品的实例化封装起来，
使得调用者根本无需关心产品的实例化过程，只需依赖工厂即可得到自己想要的产品。
2）对调用者屏蔽具体的产品类。如果使用工厂模式，调用者只关心产品的接口就可以了，至于具体的实现，调用者根本无需关心。
即使变更了具体的实现，对调用者来说没有任何影响。
3）降低耦合度。产品类的实例化通常来说是很复杂的，它需要依赖很多的类，而这些类对于调用者来说根本无需知道，
如果使用了工厂方法，我们需要做的仅仅是实例化好产品类，然后交给调用者使用。对调用者来说，产品所依赖的类都是透明的

2、工厂方法模式有四个要素：
1) 工厂接口。工厂接口是工厂方法模式的核心，与调用者直接交互用来提供产品。在实际编程中，有时候也会使用一个抽象类来作为与调用者交互的接口，
其本质上是一样的。
2) 工厂实现。在编程中，工厂实现决定如何实例化产品，是实现扩展的途径，需要有多少种产品，就需要有多少个具体的工厂实现。
3) 产品接口。产品接口的主要目的是定义产品的规范，所有的产品实现都必须遵循产品接口定义的规范。产品接口是调用者最为关心的，
产品接口定义的优劣直接决定了调用者代码的稳定性。同样，产品接口也可以用抽象类来代替，但要注意最好不要违反里氏替换原则。
4) 产品实现。实现产品接口的具体类，决定了产品在客户端中的具体行为。

简单工厂模式跟工厂方法模式极为相似，区别是：简单工厂只有三个要素，他没有工厂接口，并且得到产品的方法一般是静态的。
因为没有工厂接口，所以在工厂实现的扩展性方面稍弱，可以算所工厂方法模式的简化版

3、适用场景：
不管是简单工厂模式，工厂方法模式还是抽象工厂模式，他们具有类似的特性，所以他们的适用场景也是类似的。
1) 首先，作为一种创建类模式，在任何需要生成复杂对象的地方，都可以使用工厂方法模式。
有一点需要注意的地方就是复杂对象适合使用工厂模式，而简单对象，特别是只需要通过new就可以完成创建的对象，无需使用工厂模式。
如果使用工厂模式，就需要引入一个工厂类，会增加系统的复杂度。
2) 其次，工厂模式是一种典型的解耦模式，迪米特法则在工厂模式中表现的尤为明显。
假如调用者自己组装产品需要增加依赖关系时，可以考虑使用工厂模式。将会大大降低对象之间的耦合度。
3) 再次，由于工厂模式是依靠抽象架构的，它把实例化产品的任务交由实现类完成，扩展性比较好。
也就是说，当需要系统有比较好的扩展性时，可以考虑工厂模式，不同的产品用不同的实现工厂来组装。
*/

void FactoryMethodTest();

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

class AbstractFactory
{
public:
	virtual AbstractProduct* CreateProduct() = 0;
};

class FactoryA: public AbstractFactory
{
public:
	AbstractProduct* CreateProduct()
	{
		return new ProductA();
	}
};

class FactoryB: public AbstractFactory
{
public:
	AbstractProduct* CreateProduct()
	{
		return new ProductB();
	}
};

void FactoryMethodTest()
{
	AbstractFactory *pFA = new FactoryA();
	AbstractProduct *pPA = pFA->CreateProduct();
	pPA->Show();

	AbstractFactory *pFB = new FactoryB();
	AbstractProduct *pPB= pFB->CreateProduct();
	pPB->Show();

	delete pFA; pFA = NULL;
	delete pPA; pPA = NULL;
	delete pFB; pFB = NULL;
	delete pPB; pPB = NULL;
}

// A Example

class Engine 
{
public:
	void Show()
	{
		cout << "I am Engine" << endl;
	}
};
class Underpan 
{
public:
	void Show()
	{
		cout << "I am Underpan" << endl;
	}
};
class Wheel 
{
public:
	void Show()
	{
		cout << "I am Wheel" << endl;
	}
};
class AbstractCar
{
public:
	virtual void Show() = 0;
};

class Car: public AbstractCar
{
private:
	Engine   *m_pE;
	Underpan *m_pU;
	Wheel *m_pW;
public:
	Car(Engine *pE, Underpan *pU, Wheel *pW):m_pE(pE), m_pU(pU), m_pW(pW) {};
	virtual ~Car()
	{
		if (m_pE)
		{
			delete m_pE; m_pE = NULL;
		}
		if (m_pU)
		{
			delete m_pU; m_pU = NULL;
		}
		if (m_pW)
		{
			delete m_pW; m_pW = NULL;
		}
	};
	void Show()
	{
		m_pE->Show();
		m_pU->Show();
		m_pW->Show();
	}
};

// Not Use Design Pattern
class ClientBad
{
public:
	void Run()
	{
		Engine *pE = new Engine();
		Underpan *pU = new Underpan();
		Wheel *pW = new Wheel();

		Car *pC = new Car(pE, pU, pW);
		pC->Show();
		delete pC; pC = NULL;
	}
};
/*
分析：
可以看到，调用者为了组装汽车还需要另外实例化发动机、底盘和轮胎，而这些汽车的组件是与调用者无关的，
严重违反了迪米特法则，耦合度太高。并且非常不利于扩展。
另外，本例中发动机、底盘和轮胎还是比较具体的，在实际应用中，可能这些产品的组件也都是抽象的，
调用者根本不知道怎样组装产品。假如使用工厂方法的话，整个架构就显得清晰了许多
*/

// Modifty to Use Factory Method 
class AbstractCarFactory
{
public:
	virtual AbstractCar* CreateCar() = 0;
};

class Factory: public AbstractCarFactory
{
public: 
	AbstractCar* CreateCar()
	{
		Engine *pE = new Engine();
		Underpan *pU = new Underpan();
		Wheel *pW = new Wheel();	
		return new Car(pE, pU, pW);
	}
};

class ClientGood
{
public:
	void Run()
	{
		AbstractCarFactory *pACF = new Factory();
		AbstractCar* pAC = pACF->CreateCar();
		pAC->Show();
		delete pACF; pACF = NULL;
		delete pAC;  pAC = NULL;
	}
}; 
/*分析：
 使用工厂方法后，调用端的耦合度大大降低了。并且对于工厂来说，是可以扩展的，以后如果想组装其他的汽车，只需要再增加一个工厂类的实现就可以。
 无论是灵活性还是稳定性都得到了极大的提高
*/
#endif