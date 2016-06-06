#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include "common.h"

// �Ž�ģʽ
/*
���
�����󲿷�������ʵ�ֲ��ַ��룬ʹ���Ƕ����Զ����ر仯
�򵥴ֱ���˵�����ǳ�������ṩ���õĽӿڣ���������ʵ�ֲ��֣��ڳ���������ʵ�ֲ��֣��Ӷ�ʵ�ֳ����ʵ�ֲ��ֵĵ��ã�
�����������õ�ʵ�ֲ��ֿ����ڽ��Ŀ��������У��л��ɱ��ʵ�ֲ���

�ŵ㣺
��һ����������ж��ʵ��ʱ��ͨ���ü̳���Э�����ǡ������ඨ��Ըó���Ľӿڣ���������������ò�ͬ��ʽ����ʵ�֡�
���Ǵ˷�����ʱ�������̳л��ƽ����󲿷�������ʵ�ֲ��̶ֹ���һ��ʹ�����ԶԳ��󲿷ֺ�ʵ�ֲ��ֶ����Ľ����޸ġ���������á�
�Ž�ģʽ����������ʵ�֣�����Ϊ������������ɶ���ͱ仯����֮��ĵ���ϣ����ϵͳ�Ŀ�ά���Ժ���չ�ԡ�
�Ž�ģʽ����ҪĿ���ǽ�һ������ı仯�������仯���뿪���ñ˴�֮�����϶���͡�

���ϣ�
��  �����ϣ���ڳ��������ʵ�ֲ���֮����һ���̶��İ󶨹�ϵ��Ҳ���Ǽ̳й�ϵ��
������Ǵ��������̶ֹ��İ󶨹�ϵ���Ժ󣬾Ϳ��Է�����ڳ��󲿷��л���ͬ��ʵ�ֲ��֣�
�� ���ϣ����ĳ����Լ�����ʵ�ֶ�Ӧ�ÿ���ͨ����������ķ����������䣻
�����ʹ���Ž�ģʽ��ʹ�ü̳�ȥʵ��ʱ���ڳ����������һ�����������ڶ�Ӧ��ʵ������Ҳ��Ҫ����Ӧ�ĸĶ�������ʵ�ֲ���������ϵ�Ҫ��
�� ���Ҫ���һ�������ʵ�ֲ��ֵ��޸ĶԿͻ�������Ӱ�죬���ͻ��Ĵ��벻��Ҫ���±��룬�ں������Ŀ�����˵�ⷽ�棻
�� �����Կͻ���ȫ���س����ʵ�ֲ��֣�
�� ���һ�������ж���仯���ص�ʱ��ͨ��������Щ�仯���أ�����������ʵ�֣��޸�Ϊ��������
�� ���ĳ���仯�����ڶ�������й���ʱ�����Գ��������仯���أ�Ȼ��ʵ����Щ��ͬ�ı仯���ء�
*/

/*
** FileName      : Bridge.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Bridge Pattern Implementation of C++
*/

void BridgeTest();
// ����ʵ��
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

// ������
class Abstraction
{
protected:                        // Must Be Protected �̳���Ҫ�õ�
	Implementor *m_pImplementor;  // ��������ʵ���ࣨAggregation)
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
	// �١��� ��ͬһ����ʵ��ConcreteImplementorA��B��ͬһ�ľ������ConcreteAbstractionA
	Implementor *pI_A = new ConcreteImplementorA();
	Abstraction *pA_AA = new ConcreteAbstractionA(pI_A);
	pA_AA->Operator(); // CAA ---> CIA


	Implementor *pI_B = new ConcreteImplementorB();
	Abstraction *pA_AB = new ConcreteAbstractionA(pI_B);
	pA_AB->Operator(); // CAA --->CIB

	// �ڡ��� ͬһ����ʵ��ConcreteImplementorB����ͬ�ľ������ConcreteAbstractionA��B
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
/* ��������������װ����ϵͳ���ж������õļ������ͬ��Ҳ�ж�����ϵͳ��
��������Ž�ģʽ�أ����Խ�����ϵͳ�ͼ�����ֱ��������������Ǹ��Է�չ���������ǵ���϶�
*/
// ����ʵ����
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

//������
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
	// ��װLinux OS �� Dell����
	OS *pOS_Linux = new LinuxOS();
	Computer *pC_Dell_Linux = new DellComputer(pOS_Linux);
	pC_Dell_Linux->InstallOs();

	// ��װ Windows OS �� Dell����
	OS *pOS_Windows = new WindowsOS();
	Computer *pC_Dell_Windows = new DellComputer(pOS_Windows);
	pC_Dell_Windows->InstallOs();

	// ��װ Linux OS �� Acer����
	Computer *pC_Acer_Linux = new AcerComputer(pOS_Linux);
	pC_Acer_Linux->InstallOs();

	//��װ Windows OS �� Acer����
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
/*��������������Ҫȥ��һ��ͼ�Σ�ͼ���г����Ρ�Բ�κ����εȵȣ�
��ͼ���ֿ��Լ��ϲ�ͬ����ɫ��Ȼ�����ǾͿ��Ի�����ɫ�ĳ����Σ���ɫ�ĳ����Σ���ɫ��Բ�Σ���ɫ��Բ�εȵȡ�
������ͼ�ε���״�ڱ仯��ͼ�ε���ɫҲ�ڱ仯����ʹ�ô���ȥʵ��ʱ�����������ֶ෽��ı仯�أ����Ҫ˵��������Ž�ģʽ��
*/

// ����ʵ����
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

// ������
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
	// ���ƺ�ɫ������
	AbstractColor *pC_Red = new RedColor();
	Shape *pS_Rect_Red = new RectangleShape(pC_Red);
	pS_Rect_Red->Paint();

	// ���ư�ɫ������
	AbstractColor *pC_White  = new WhiteColor();
	Shape *pS_Rect_White = new RectangleShape(pC_White);
	pS_Rect_White->Paint();

	// ���ƺ�ɫԲ��
	Shape *pS_Circle_Red = new CircleShape(pC_Red);
	pS_Circle_Red->Paint();

	// ���ư�ɫԲ��
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