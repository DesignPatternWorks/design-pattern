#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "common.h"

// 装饰模式
/*
1、概念&功能：
1）动态地给一个对象添加一些额外的职责。就增加功能来说，装饰模式相比生成子类更为灵活。
有时我们希望给某个对象而不是整个类添加一些功能

2）装饰模式能够实现动态的为对象添加功能，是从一个对象外部来给对象添加功能。
通常给对象添加功能，要么直接修改对象添加相应的功能，要么派生对应的子类来扩展，抑或是使用对象组合的方式。
显然，直接修改对应的类这种方式并不可取。在面向对象的设计中，而我们也应该尽量使用对象组合，而不是对象继承来扩展和复用功能。
装饰器模式就是基于对象组合的方式，可以很灵活的给对象添加所需要的功能。装饰器模式的本质就是动态组合。动态是手段，组合才是目的。
总之，装饰模式是通过把复杂的功能简单化，分散化，然后再运行期间，根据需要来动态组合的这样一个模式。
它使得我们可以给某个对象而不是整个类添加一些功能。

3）装饰模式重点在装饰，对核心功能的装饰作用；
将继承中对子类的扩展转化为功能类的组合，从而将需要对子类的扩展转嫁给用户去进行调用组合，用户如何组合由用户去决定。
我在学习装饰模式时，就是重点分析了“装饰”这个词，我们都知道，装饰是在一个核心功能上添加一些附属功能，从而让核心功能发挥更大的作用
但是最终它的核心功能是不能丢失的。
这就好比我们进行windows shell开发时，我们是对windows的这层壳进行了功能的装饰，从而实现了我们需要的一些装饰功能，但是最终的功能还是由windows shell去完成。
这就好比，我们的装饰就是给核心功能添加了一层外衣，让它看起来更漂亮和完美

2、适用场合：
在不影响其他对象的情况下，以动态的，透明的方式给单个对象添加职责；
处理那些可以撤销的职责；
当不能采用生成子类的方法进行扩充时。一种情况是，可能存在大量独立的扩展，为支持每一种组合将产生大量的子类，使得子类数目呈爆炸性增长。
另一种情况可能是因为类定义被隐藏，或类定义不能用于生成子类。

3、与桥接模式的区别：
之前桥接模式&装饰模式；你会发现，二者都是为了防止过度的继承，从而造成子类泛滥的情况。
那么二者之间的主要区别是什么呢？
桥接模式的定义是将抽象化与实现化分离（用组合的方式而不是继承的方式），使得两者可以独立变化。可以减少派生类的增长。
如果光从这一点来看的话，和装饰者差不多，但两者还是有一些比较重要的区别：
1） 桥接模式中所说的分离，其实是指将结构与实现分离（当结构和实现有可能发生变化时）或属性与基于属性的行为进行分离；
    而装饰者只是对基于属性的行为进行封闭成独立的类，从而达到对其进行装饰，也就是扩展。
	比如：异常类和异常处理类之间就可以使用桥接模式来实现完成，而不能使用装饰模式来进行设计；
	如果对于异常的处理需要进行扩展时，我们又可以对异常处理类添加Decorator，从而添加处理的装饰，达到异常处理的扩展，这就是一个桥接模式与装饰模式的搭配；
2） 桥接中的行为是横向的行为，行为彼此之间无关联，注意这里的行为之间是没有关联的，就比如异常和异常处理之间是没有行为关联的一样；
    而装饰者模式中的行为具有可叠加性，其表现出来的结果是一个整体，一个各个行为组合后的一个结果。
*/

/*
** FileName      : Decorator.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Decorator Pattern Implementation of C++
*/

void DecoratorTest();

// 抽象组件类
class Component
{
public:
	Component() {};
public:
	virtual void Operator() = 0;
};

class ConcreteComponentA : public Component
{
public:
	ConcreteComponentA() {};
public:
	void Operator()
	{
		cout << "I am Concrete Component A" << endl;
	}
};

class ConcreteComponentB : public Component
{
public:
	ConcreteComponentB() {};
public:
	void Operator()
	{
		cout << "I am Concrete Component B" << endl;
	}
};

// 装饰类父类（非抽象，继承组件类,与桥接模式的不同）
class Decorator : public Component
{
private:
	Component *m_pC;          // 与桥接模式类似，都是对象组合
public:
	Decorator(Component *pC) : m_pC(pC) {};
	void Operator() 
	{
		if (NULL != m_pC)
		{
			m_pC->Operator();
		}
	}
};

class ConcreteDecoratorA : public Decorator
{
private:
	int m_AddedState;
public:
	ConcreteDecoratorA(Component *pC, int state) : Decorator(pC), m_AddedState(state) {};
	void Operator()
	{
		Decorator::Operator();
		cout << "Concrete Decorator A Added State: " << m_AddedState << endl;
	}
};

class ConcreteDecoratorB : public Decorator
{
public:
	ConcreteDecoratorB(Component *pC) : Decorator(pC){};
	void Operator()
	{
		Decorator::Operator();
		AddedOperator();
	}
	void AddedOperator()
	{
		cout << "Concrete Decorator B Added Behavior:" << endl;
	}
};

void DecoratorTest_General()
{
	// 创建一个增加了装饰A的组件A
	Component *pC_A = new ConcreteComponentA();
	Component *pD_AA = new ConcreteDecoratorA(pC_A,10);
	pD_AA->Operator();

	// 创建一个增加了装饰B的组件A
	Component *pD_BA = new ConcreteDecoratorB(pC_A);
	pD_BA->Operator();

	// 创建一个同时增加了装饰 A 和 B的组件A
	Component *pD_AB_A = new ConcreteDecoratorB(pD_AA);
	pD_AB_A->Operator();

	// 创建一个增加了装饰A的组件B
	Component *pC_B = new ConcreteComponentB();
	Component *pD_AB = new ConcreteDecoratorA(pC_B,10);
	pD_AB->Operator();

	// 创建一个增加了装饰B的组件B 
	Component *pD_BB = new ConcreteDecoratorB(pC_B);
	pD_BB->Operator();

	delete pC_A;      pC_A = NULL;
	delete pC_B;      pC_B = NULL;
	delete pD_AA;     pD_AA = NULL;
	delete pD_BA;     pD_BA = NULL;
	delete pD_AB;     pD_AB = NULL;
	delete pD_BB;     pD_BB = NULL;
	delete pD_AB_A;   pD_AB_A = NULL;

}
/* 分析
Component:定义一个对象接口，可以给这些对象动态地添加职责；
ConcreteComponent:定义一个具体的Component，继承自Component，重写了Component类的虚函数；
Decorator:维持一个指向Component对象的指针，该指针指向需要被装饰的对象；并定义一个与Component接口一致的接口；
ConcreteDecorator:向组件添加职责

1）接口的一致性；装饰对象的接口必须与它所装饰的Component的接口是一致的，因此，所有的ConcreteDecorator类必须有一个公共的父类；
   这样对于用户来说，就是统一的接口；
2）省略抽象的Decorator类；当仅需要添加一个职责时，没有必要定义抽象Decorator类。
   因为我们常常要处理，现存的类层次结构而不是设计一个新系统，这时可以把Decorator向Component转发请求的职责合并到ConcreteDecorator中；
3）保持Component类的简单性；为了保证接口的一致性，组件和装饰必须要有一个公共的Component类
   所以保持这个Component类的简单性是非常重要的，所以，这个Component类应该集中于定义接口而不是存储数据。
   对数据表示的定义应延迟到子类中，否则Component类会变得过于复杂和臃肿，因而难以大量使用。
   赋予Component类太多的功能，也使得具体的子类有一些它们它们不需要的功能大大增大；
4）Component类在Decorator模式中充当抽象接口的角色，不应该去实现具体的行为。
   而且Decorator类对于Component类应该透明，换言之Component类无需知道Decorator类，Decorator类是从外部来扩展Component类的功能；
5）Decorator类在接口上表现为“is-a”Component的继承关系，即Decorator类继承了Component类所具有的接口。
   但在实现上又表现为“has-a”Component的组合关系，即Decorator类又使用了另外一个Component类。
   我们可以使用一个或者多个Decorator对象来“装饰”一个Component对象，且装饰后的对象仍然是一个Component对象；
6）Decortor模式并非解决“多子类衍生的多继承”问题，Decorator模式的应用要点在于解决“主体类在多个方向上的扩展功能”——是为“装饰”的含义；
7）对于Decorator模式在实际中的运用可以很灵活。如果只有一个ConcreteComponent类而没有抽象的Component类，那么Decorator类可以是ConcreteComponent的一个子类。
   如果只有一个ConcreteDecorator类，那么就没有必要建立一个单独的Decorator类，而可以把Decorator和ConcreteDecorator的责任合并成一个类。
8）Decorator模式的优点是提供了比继承更加灵活的扩展，通过使用不同的具体装饰类以及这些装饰类的排列组合，可以创造出很多不同行为的组合；

*/
// A Example of Decorating Phone
/*
比如有一个手机，允许你为手机添加特性，比如增加挂件、屏幕贴膜等。
一种灵活的设计方式是，将手机嵌入到另一对象中，由这个对象完成特性的添加，我们称这个嵌入的对象为装饰。
这个装饰与它所装饰的组件接口一致，因此它对使用该组件的客户透明
*/

//抽象手机类
class Phone
{
public:
	virtual void ShowPhone() = 0;
};

class NokiaPhone : public Phone
{
public:
	void ShowPhone()
	{
		cout << "I am Nokia Phone" << endl;
	}
};

class ApplePhone : public Phone
{
public:
	void ShowPhone()
	{
		cout << "I am Apple Phone" << endl;
	}
};

// 手机装饰类(非抽象，父类,继承Phone）
class DecoratorPhone : public Phone
{
private:
	Phone *m_pPhone;
public:
	DecoratorPhone(Phone *pP) : m_pPhone(pP) {};
public:
	virtual void ShowPhone()
	{
		if (NULL != m_pPhone)
		{
			m_pPhone->ShowPhone();
		}
	}
};

// 增加屏保的装饰类
class DecoratorPhoneA : public DecoratorPhone
{
public:
	DecoratorPhoneA(Phone *pP) : DecoratorPhone(pP) {};
public:
	void ShowPhone()
	{
		DecoratorPhone::ShowPhone();
		AddDecoratorA();
	}
	void AddDecoratorA()
	{
		cout << "Add Decorator Phone of Screen Protection" << endl;
	}
};

// 增加挂件的装饰类
class DecoratorPhoneB : public DecoratorPhone 
{
public:
	DecoratorPhoneB(Phone *pP) : DecoratorPhone(pP) {};
public:
	void ShowPhone()
	{
		DecoratorPhone::ShowPhone();
		AddDecoratorB();
	}
	void AddDecoratorB()
	{
		cout << "Add Decorator Phone of Pendant " << endl;
	}
};

void DecoratorTest_Phone()
{
	// 装了屏保的Nokia手机
	Phone *pP_Nokia = new NokiaPhone();
	Phone *pD_Pendant_Nokia = new DecoratorPhoneA(pP_Nokia);
	pD_Pendant_Nokia->ShowPhone();

	// 装了屏保,和挂件的Nokia手机
	Phone *pD_Pendant_ScnPrt_Nokia = new DecoratorPhoneB(pD_Pendant_Nokia);
	pD_Pendant_ScnPrt_Nokia->ShowPhone();

	// 装了挂件的Nokia手机
	Phone *pD_ScnPrt_Nokia = new DecoratorPhoneB(pP_Nokia);
	pD_ScnPrt_Nokia->ShowPhone();

	// 装了屏保,和挂件的Apple手机
	Phone *pP_Apple = new ApplePhone();
	Phone *pD_Pendant_Apple = new DecoratorPhoneA(pP_Apple);
	Phone *pD_Pendant_ScnPrt_Apple = new DecoratorPhoneB(pD_Pendant_Apple);
	pD_Pendant_ScnPrt_Apple->ShowPhone();

	delete pP_Nokia;                       pP_Nokia = NULL;
	delete pP_Apple;                       pP_Apple = NULL;
	delete pD_Pendant_Nokia;               pD_Pendant_Nokia = NULL;
	delete pD_ScnPrt_Nokia;                pD_ScnPrt_Nokia = NULL;
	delete pD_Pendant_ScnPrt_Nokia;        pD_Pendant_ScnPrt_Nokia = NULL;
	delete pD_Pendant_Apple;               pD_Pendant_Apple = NULL;
	delete pD_Pendant_ScnPrt_Apple;        pD_Pendant_ScnPrt_Apple = NULL;
}
void DecoratorTest()
{
	cout << "*********** DecoratorTest_General: *************" << endl;
	DecoratorTest_General();
	cout << "*********** DecoratorTest_Phone: *************" << endl;
	DecoratorTest_Phone();
}
#endif