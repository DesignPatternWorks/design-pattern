#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "common.h"

// װ��ģʽ
/*
1������&���ܣ�
1����̬�ظ�һ���������һЩ�����ְ�𡣾����ӹ�����˵��װ��ģʽ������������Ϊ��
��ʱ����ϣ����ĳ��������������������һЩ����

2��װ��ģʽ�ܹ�ʵ�ֶ�̬��Ϊ������ӹ��ܣ��Ǵ�һ�������ⲿ����������ӹ��ܡ�
ͨ����������ӹ��ܣ�Ҫôֱ���޸Ķ��������Ӧ�Ĺ��ܣ�Ҫô������Ӧ����������չ���ֻ���ʹ�ö�����ϵķ�ʽ��
��Ȼ��ֱ���޸Ķ�Ӧ�������ַ�ʽ������ȡ����������������У�������ҲӦ�þ���ʹ�ö�����ϣ������Ƕ���̳�����չ�͸��ù��ܡ�
װ����ģʽ���ǻ��ڶ�����ϵķ�ʽ�����Ժ����ĸ������������Ҫ�Ĺ��ܡ�װ����ģʽ�ı��ʾ��Ƕ�̬��ϡ���̬���ֶΣ���ϲ���Ŀ�ġ�
��֮��װ��ģʽ��ͨ���Ѹ��ӵĹ��ܼ򵥻�����ɢ����Ȼ���������ڼ䣬������Ҫ����̬��ϵ�����һ��ģʽ��
��ʹ�����ǿ��Ը�ĳ��������������������һЩ���ܡ�

3��װ��ģʽ�ص���װ�Σ��Ժ��Ĺ��ܵ�װ�����ã�
���̳��ж��������չת��Ϊ���������ϣ��Ӷ�����Ҫ���������չת�޸��û�ȥ���е�����ϣ��û����������û�ȥ������
����ѧϰװ��ģʽʱ�������ص�����ˡ�װ�Ρ�����ʣ����Ƕ�֪����װ������һ�����Ĺ��������һЩ�������ܣ��Ӷ��ú��Ĺ��ܷ��Ӹ��������
�����������ĺ��Ĺ����ǲ��ܶ�ʧ�ġ�
��ͺñ����ǽ���windows shell����ʱ�������Ƕ�windows�����ǽ����˹��ܵ�װ�Σ��Ӷ�ʵ����������Ҫ��һЩװ�ι��ܣ��������յĹ��ܻ�����windows shellȥ��ɡ�
��ͺñȣ����ǵ�װ�ξ��Ǹ����Ĺ��������һ�����£�������������Ư��������

2�����ó��ϣ�
�ڲ�Ӱ���������������£��Զ�̬�ģ�͸���ķ�ʽ�������������ְ��
������Щ���Գ�����ְ��
�����ܲ�����������ķ�����������ʱ��һ������ǣ����ܴ��ڴ�����������չ��Ϊ֧��ÿһ����Ͻ��������������࣬ʹ��������Ŀ�ʱ�ը��������
��һ�������������Ϊ�ඨ�屻���أ����ඨ�岻�������������ࡣ

3�����Ž�ģʽ������
֮ǰ�Ž�ģʽ&װ��ģʽ����ᷢ�֣����߶���Ϊ�˷�ֹ���ȵļ̳У��Ӷ�������෺�ĵ������
��ô����֮�����Ҫ������ʲô�أ�
�Ž�ģʽ�Ķ����ǽ�������ʵ�ֻ����루����ϵķ�ʽ�����Ǽ̳еķ�ʽ����ʹ�����߿��Զ����仯�����Լ����������������
��������һ�������Ļ�����װ���߲�࣬�����߻�����һЩ�Ƚ���Ҫ������
1�� �Ž�ģʽ����˵�ķ��룬��ʵ��ָ���ṹ��ʵ�ַ��루���ṹ��ʵ���п��ܷ����仯ʱ����������������Ե���Ϊ���з��룻
    ��װ����ֻ�ǶԻ������Ե���Ϊ���з�ճɶ������࣬�Ӷ��ﵽ�������װ�Σ�Ҳ������չ��
	���磺�쳣����쳣������֮��Ϳ���ʹ���Ž�ģʽ��ʵ����ɣ�������ʹ��װ��ģʽ��������ƣ�
	��������쳣�Ĵ�����Ҫ������չʱ�������ֿ��Զ��쳣���������Decorator���Ӷ���Ӵ����װ�Σ��ﵽ�쳣�������չ�������һ���Ž�ģʽ��װ��ģʽ�Ĵ��䣻
2�� �Ž��е���Ϊ�Ǻ������Ϊ����Ϊ�˴�֮���޹�����ע���������Ϊ֮����û�й����ģ��ͱ����쳣���쳣����֮����û����Ϊ������һ����
    ��װ����ģʽ�е���Ϊ���пɵ����ԣ�����ֳ����Ľ����һ�����壬һ��������Ϊ��Ϻ��һ�������
*/

/*
** FileName      : Decorator.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Decorator Pattern Implementation of C++
*/

void DecoratorTest();

// ���������
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

// װ���ุ�ࣨ�ǳ��󣬼̳������,���Ž�ģʽ�Ĳ�ͬ��
class Decorator : public Component
{
private:
	Component *m_pC;          // ���Ž�ģʽ���ƣ����Ƕ������
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
	// ����һ��������װ��A�����A
	Component *pC_A = new ConcreteComponentA();
	Component *pD_AA = new ConcreteDecoratorA(pC_A,10);
	pD_AA->Operator();

	// ����һ��������װ��B�����A
	Component *pD_BA = new ConcreteDecoratorB(pC_A);
	pD_BA->Operator();

	// ����һ��ͬʱ������װ�� A �� B�����A
	Component *pD_AB_A = new ConcreteDecoratorB(pD_AA);
	pD_AB_A->Operator();

	// ����һ��������װ��A�����B
	Component *pC_B = new ConcreteComponentB();
	Component *pD_AB = new ConcreteDecoratorA(pC_B,10);
	pD_AB->Operator();

	// ����һ��������װ��B�����B 
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
/* ����
Component:����һ������ӿڣ����Ը���Щ����̬�����ְ��
ConcreteComponent:����һ�������Component���̳���Component����д��Component����麯����
Decorator:ά��һ��ָ��Component�����ָ�룬��ָ��ָ����Ҫ��װ�εĶ��󣻲�����һ����Component�ӿ�һ�µĽӿڣ�
ConcreteDecorator:��������ְ��

1���ӿڵ�һ���ԣ�װ�ζ���Ľӿڱ���������װ�ε�Component�Ľӿ���һ�µģ���ˣ����е�ConcreteDecorator�������һ�������ĸ��ࣻ
   ���������û���˵������ͳһ�Ľӿڣ�
2��ʡ�Գ����Decorator�ࣻ������Ҫ���һ��ְ��ʱ��û�б�Ҫ�������Decorator�ࡣ
   ��Ϊ���ǳ���Ҫ�����ִ�����νṹ���������һ����ϵͳ����ʱ���԰�Decorator��Componentת�������ְ��ϲ���ConcreteDecorator�У�
3������Component��ļ��ԣ�Ϊ�˱�֤�ӿڵ�һ���ԣ������װ�α���Ҫ��һ��������Component��
   ���Ա������Component��ļ����Ƿǳ���Ҫ�ģ����ԣ����Component��Ӧ�ü����ڶ���ӿڶ����Ǵ洢���ݡ�
   �����ݱ�ʾ�Ķ���Ӧ�ӳٵ������У�����Component����ù��ڸ��Ӻ�ӷ�ף�������Դ���ʹ�á�
   ����Component��̫��Ĺ��ܣ�Ҳʹ�þ����������һЩ�������ǲ���Ҫ�Ĺ��ܴ������
4��Component����Decoratorģʽ�г䵱����ӿڵĽ�ɫ����Ӧ��ȥʵ�־������Ϊ��
   ����Decorator�����Component��Ӧ��͸��������֮Component������֪��Decorator�࣬Decorator���Ǵ��ⲿ����չComponent��Ĺ��ܣ�
5��Decorator���ڽӿ��ϱ���Ϊ��is-a��Component�ļ̳й�ϵ����Decorator��̳���Component�������еĽӿڡ�
   ����ʵ�����ֱ���Ϊ��has-a��Component����Ϲ�ϵ����Decorator����ʹ��������һ��Component�ࡣ
   ���ǿ���ʹ��һ�����߶��Decorator��������װ�Ρ�һ��Component������װ�κ�Ķ�����Ȼ��һ��Component����
6��Decortorģʽ���ǽ���������������Ķ�̳С����⣬Decoratorģʽ��Ӧ��Ҫ�����ڽ�����������ڶ�������ϵ���չ���ܡ�������Ϊ��װ�Ρ��ĺ��壻
7������Decoratorģʽ��ʵ���е����ÿ��Ժ������ֻ��һ��ConcreteComponent���û�г����Component�࣬��ôDecorator�������ConcreteComponent��һ�����ࡣ
   ���ֻ��һ��ConcreteDecorator�࣬��ô��û�б�Ҫ����һ��������Decorator�࣬�����԰�Decorator��ConcreteDecorator�����κϲ���һ���ࡣ
8��Decoratorģʽ���ŵ����ṩ�˱ȼ̳и���������չ��ͨ��ʹ�ò�ͬ�ľ���װ�����Լ���Щװ�����������ϣ����Դ�����ܶ಻ͬ��Ϊ����ϣ�

*/
// A Example of Decorating Phone
/*
������һ���ֻ���������Ϊ�ֻ�������ԣ��������ӹҼ�����Ļ��Ĥ�ȡ�
һ��������Ʒ�ʽ�ǣ����ֻ�Ƕ�뵽��һ�����У����������������Ե���ӣ����ǳ����Ƕ��Ķ���Ϊװ�Ρ�
���װ��������װ�ε�����ӿ�һ�£��������ʹ�ø�����Ŀͻ�͸��
*/

//�����ֻ���
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

// �ֻ�װ����(�ǳ��󣬸���,�̳�Phone��
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

// ����������װ����
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

// ���ӹҼ���װ����
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
	// װ��������Nokia�ֻ�
	Phone *pP_Nokia = new NokiaPhone();
	Phone *pD_Pendant_Nokia = new DecoratorPhoneA(pP_Nokia);
	pD_Pendant_Nokia->ShowPhone();

	// װ������,�͹Ҽ���Nokia�ֻ�
	Phone *pD_Pendant_ScnPrt_Nokia = new DecoratorPhoneB(pD_Pendant_Nokia);
	pD_Pendant_ScnPrt_Nokia->ShowPhone();

	// װ�˹Ҽ���Nokia�ֻ�
	Phone *pD_ScnPrt_Nokia = new DecoratorPhoneB(pP_Nokia);
	pD_ScnPrt_Nokia->ShowPhone();

	// װ������,�͹Ҽ���Apple�ֻ�
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