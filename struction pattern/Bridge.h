#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include "common.h"

// 桥接模式
/*
概念：
将抽象部分与它的实现部分分离，使它们都可以独立地变化
简单粗暴的说，就是抽象对外提供调用的接口；对外隐瞒实现部分，在抽象中引用实现部分，从而实现抽象对实现部分的调用，
而抽象中引用的实现部分可以在今后的开发过程中，切换成别的实现部分

优点：
当一个抽象可能有多个实现时，通常用继承来协调它们。抽象类定义对该抽象的接口，而具体的子类则用不同方式加以实现。
但是此方法有时不够灵活。继承机制将抽象部分与它的实现部分固定在一起，使得难以对抽象部分和实现部分独立的进行修改、扩充和重用。
桥接模式把依赖具体实现，提升为依赖抽象，来完成对象和变化因素之间的低耦合，提高系统的可维护性和扩展性。
桥接模式的主要目的是将一个对象的变化与其它变化隔离开，让彼此之间的耦合度最低。

场合：
①  如果不希望在抽象和它的实现部分之间有一个固定的绑定关系，也就是继承关系；
如果我们打破了这种固定的绑定关系，以后，就可以方便的在抽象部分切换不同的实现部分；
② 如果希望类的抽象以及它的实现都应该可以通过生成子类的方法加以扩充；
如果不使用桥接模式，使用继承去实现时，在抽象类中添加一个方法，则在对应的实现类中也需要做对应的改动，这种实现不符合松耦合的要求；
③ 如果要求对一个抽象的实现部分的修改对客户不产生影响，即客户的代码不需要重新编译，在后面的项目经验会说这方面；
④ 如果想对客户完全隐藏抽象的实现部分；
⑤ 如果一个对象有多个变化因素的时候，通过抽象这些变化因素，将依赖具体实现，修改为依赖抽象；
⑥ 如果某个变化因素在多个对象中共享时，可以抽象出这个变化因素，然后实现这些不同的变化因素。
*/

/*
** FileName      : Bridge.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Bridge Pattern Implementation of C++
*/

void BridgeTest();
// 抽象实现
class Implementor
{
public:
	virtual void OperatorImp() = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
	void OperatorImp()
	{
		cout << "I am Concrete OperatorImpA" << endl;
	}
};

class ConcreteImplementorB : public Implementor
{
public:
	void OperatorImp()
	{
		cout << "I am Concrete OperatorImpB" << endl;
	}
};

// 抽象类
class Abstraction
{
protected:                        // Must Be Protected 继承类要用到
	Implementor *m_pImplementor;  // 关联抽象实现类（Aggregation)
public:
	Abstraction(Implementor *pI): m_pImplementor(pI) {};
public:
	virtual void Operator() = 0;
};

class ConcreteAbstractionA : public Abstraction
{
public:
	ConcreteAbstractionA(Implementor *pI): Abstraction(pI) {};
public:
	void Operator()
	{
		cout << "Concrete AbstractionA Operation:" << endl;
		m_pImplementor->OperatorImp();
	}
};

class ConcreteAbstractionB : public Abstraction
{
public:
	ConcreteAbstractionB(Implementor *pI): Abstraction(pI) {};
public:
	void Operator()
	{
		cout << "Concrete AbstractionB Operation:" << endl;
		m_pImplementor->OperatorImp();
	}
};

void BridgeTest_Abstraction_Implementor()
{
	// ①、② 不同一具体实现ConcreteImplementorA、B，同一的具体抽象ConcreteAbstractionA
	Implementor *pI_A = new ConcreteImplementorA();
	Abstraction *pA_AA = new ConcreteAbstractionA(pI_A);
	pA_AA->Operator(); // CAA ---> CIA


	Implementor *pI_B = new ConcreteImplementorB();
	Abstraction *pA_AB = new ConcreteAbstractionA(pI_B);
	pA_AB->Operator(); // CAA --->CIB

	// ②、③ 同一具体实现ConcreteImplementorB，不同的具体抽象ConcreteAbstractionA、B
	Abstraction *pA_BB = new ConcreteAbstractionB(pI_B);
	pA_BB->Operator(); // CAB ---> CIB

	Abstraction *pA_BA = new ConcreteAbstractionB(pI_A);
	pA_BA->Operator(); // CAB --> CIA

	delete pI_A; pI_A = NULL;
	delete pI_B; pI_B = NULL;

	delete pA_AA; pA_AA = NULL;
	delete pA_AB; pA_AB = NULL;
	delete pA_BB; pA_BB = NULL;
	delete pA_BA; pA_BA = NULL;
}

// A Example of Computer's OS Installation
/* 问题描述：考虑装操作系统，有多种配置的计算机，同样也有多款操作系统。
如何运用桥接模式呢？可以将操作系统和计算机分别抽象出来，让它们各自发展，减少它们的耦合度
*/
// 抽象实现类
class OS
{
public:
	virtual void InstallOs_Impl() = 0;
};

class LinuxOS : public OS
{
public:
	void InstallOs_Impl()
	{
		cout << "Install Linux OS Implementor" << endl;
	}
};

class WindowsOS : public OS
{
public:
	void InstallOs_Impl()
	{
		cout << "Install Windows OS Implementor" << endl;
	}
};

//抽象类
class Computer
{
protected:
	OS *m_pOs;
public:
	Computer(OS *pOS): m_pOs(pOS) {};
public:
	virtual void InstallOs() = 0;
};

class DellComputer : public Computer
{
public:
	DellComputer(OS *pOS) : Computer(pOS) {};
public:
	void InstallOs()
	{
		cout << "Dell Computer: " << endl;
		m_pOs->InstallOs_Impl();
	}
};

class AcerComputer : public Computer
{
public:
	AcerComputer(OS *pOS): Computer(pOS) {};
public:
	void InstallOs()
	{
		cout << "Acer Computer: " << endl;
		m_pOs->InstallOs_Impl();
	}
};

void BridgeTest_Computer_OS()
{
	// 安装Linux OS 的 Dell电脑
	OS *pOS_Linux = new LinuxOS();
	Computer *pC_Dell_Linux = new DellComputer(pOS_Linux);
	pC_Dell_Linux->InstallOs();

	// 安装 Windows OS 的 Dell电脑
	OS *pOS_Windows = new WindowsOS();
	Computer *pC_Dell_Windows = new DellComputer(pOS_Windows);
	pC_Dell_Windows->InstallOs();

	// 安装 Linux OS 的 Acer电脑
	Computer *pC_Acer_Linux = new AcerComputer(pOS_Linux);
	pC_Acer_Linux->InstallOs();

	//安装 Windows OS 的 Acer电脑
	Computer *pC_Acer_Windows = new AcerComputer(pOS_Windows);
	pC_Acer_Windows->InstallOs();

	delete pOS_Linux;       pOS_Linux = NULL;
	delete pOS_Windows;     pOS_Windows = NULL;
	delete pC_Dell_Linux;   pC_Dell_Linux = NULL;
	delete pC_Dell_Windows; pC_Dell_Windows = NULL;
	delete pC_Acer_Linux;   pC_Acer_Linux = NULL;
	delete pC_Acer_Windows; pC_Acer_Windows = NULL;
}
// A Example of Shape's Color Painting
/*问题描述：现在要去画一个图形，图形有长方形、圆形和扇形等等；
而图形又可以加上不同的颜色，然后，我们就可以画出红色的长方形，绿色的长方形；红色的圆形，绿色的圆形等等。
而这种图形的形状在变化，图形的颜色也在变化，当使用代码去实现时，如何面对这种多方面的变化呢？这就要说到今天的桥接模式了
*/

// 抽象实现类
class AbstractColor
{
public:
	virtual void Paint_Impl() = 0;
};

class RedColor : public AbstractColor
{
public:
	void Paint_Impl()
	{
		cout << "Paint Red" << endl;
	}
};

class WhiteColor : public AbstractColor
{
public:
	void Paint_Impl()
	{
		cout << "Paint White" << endl;
	}
};

// 抽象类
class Shape
{
protected:
	AbstractColor *m_pC;
public:
	Shape(AbstractColor *pC) : m_pC(pC) {};
public:
	virtual void Paint() = 0;
};

class RectangleShape : public Shape
{
public:
	RectangleShape(AbstractColor *pC) : Shape(pC) {};
public:
	void Paint()
	{
		cout << "Rectangle Shape:" <<endl;
		m_pC->Paint_Impl();
	}
};

class CircleShape : public Shape
{
public:
	CircleShape(AbstractColor *pC) : Shape(pC) {};
public:
	void Paint()
	{
		cout << "Circle Shape:" <<endl;
		m_pC->Paint_Impl();
	}
};

void BridgeTest_Shape_Color()
{
	// 绘制红色长方形
	AbstractColor *pC_Red = new RedColor();
	Shape *pS_Rect_Red = new RectangleShape(pC_Red);
	pS_Rect_Red->Paint();

	// 绘制白色长方形
	AbstractColor *pC_White  = new WhiteColor();
	Shape *pS_Rect_White = new RectangleShape(pC_White);
	pS_Rect_White->Paint();

	// 绘制红色圆形
	Shape *pS_Circle_Red = new CircleShape(pC_Red);
	pS_Circle_Red->Paint();

	// 绘制白色圆形
	Shape *pS_Circle_White = new CircleShape(pC_White);
	pS_Circle_White->Paint();

	delete pC_Red;          pC_Red = NULL;
	delete pC_White;        pC_White = NULL;
	delete pS_Rect_Red;     pS_Rect_Red = NULL;
	delete pS_Rect_White;   pS_Rect_White = NULL;
	delete pS_Circle_Red;   pS_Circle_Red = NULL;
	delete pS_Circle_White; pS_Circle_White = NULL;
};



// Color
class Color
{
public:
	virtual void doPaint() = 0;
};

// Red 
class Red : public Color
{
public:
	void doPaint()
	{
		cout << "Red Color" << endl;
	}
};
// Green
class Green : public Color
{
public:
	void doPaint()
	{
		cout << "Green Color" << endl;
	}
};

// Black 
class Black : public Color
{
public:
	void doPaint()
	{
		cout << "Black Color" << endl;
	}
};


// Pen
class Pen
{
protected:
	Color *m_pColor;
public:
	Pen(Color *color): m_pColor(color){};
public:
	virtual void Draw() = 0;
};

// HugePen
class HugePen : public Pen
{
public:
	HugePen(Color *color) : Pen(color){};
public:
	void Draw()
	{
		cout << "Huge Pen Draw And Use The Kind Of ";
		m_pColor->doPaint();
	}
};

//Middle Pen
class MiddlePen : public Pen
{
public:
	MiddlePen(Color *color): Pen(color){};
public:
	void Draw()
	{
		cout << "Middle Pen Draw And Use The Kind Of ";
		m_pColor->doPaint();
	}
};

// Small Pen
class SmallPen : public Pen
{
public:
	SmallPen(Color *color): Pen(color){};
public:
	void Draw()
	{
		cout << "Small Pen Draw And Use The Kind Of ";
		m_pColor->doPaint();
	}
};


void BridgeTest_Pen_Color()
{
	// Huge Red Pen
	Color *pR = new Red();
	Pen   *pRed_HugePen = new HugePen(pR);
	pRed_HugePen->Draw();

	// Huge Green Pen
	Color *pG = new Green();
	Pen   *pGreen_HugePen = new HugePen(pG);
	pGreen_HugePen->Draw();

	// Middle Green Pen
	Pen   *pGreen_MidPen = new MiddlePen(pG);
	pGreen_MidPen->Draw();

	// Small Black Pen
	Color *pB = new Black();
	Pen   *pBlack_SmallPen = new SmallPen(pB);
	pBlack_SmallPen->Draw();


	delete pR; pR = NULL;
	delete pG; pG = NULL;
	delete pB; pB = NULL;

	delete pRed_HugePen; pRed_HugePen = NULL;
	delete pGreen_HugePen; pGreen_HugePen = NULL;
	delete pGreen_MidPen;  pGreen_MidPen = NULL;
	delete pBlack_SmallPen; pBlack_SmallPen = NULL;
}

void BridgeTest()
{
	cout << "*********** BridgeTest_Abstraction_Implementor: *************" << endl;
	BridgeTest_Abstraction_Implementor();

	cout << "*********** BridgeTest_Computer_OS: *************" << endl;
	BridgeTest_Computer_OS();

	cout << "*********** BridgeTest_Shape_Color: *************" << endl;
	BridgeTest_Shape_Color();

	cout << "*********** BridgeTest_Pen_Color: *************" << endl;
	BridgeTest_Pen_Color();
};

#endif