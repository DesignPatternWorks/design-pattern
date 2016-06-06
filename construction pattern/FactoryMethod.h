#ifndef _FACTORY_METHOD_H_
#define _FACTORY_METHOD_H_

#include "common.h"

// ��������ģʽ
/*
��ν��������ģʽ����ָ����һ�����ڴ�������Ľӿ�
���������ʵ������һ���ࡣFactory Methodʹһ�����ʵ�����ӳٵ�������

һ�������Ʒ�࣬������������������Ʒ�ࡣ   
һ�����󹤳��࣬����������������幤���ࡣ   
ÿ�����幤����ֻ�ܴ���һ�������Ʒ���ʵ����

�ŵ㣺���Ͽ���ԭ��
ȱ�㣺����һ�ֲ�Ʒ����Ҫ���һ����Ӧ�Ĺ�����
*/

/*
1�� �ŵ㣺
1������ʹ����ṹ��������Ч�ط�װ�仯���ڱ���У���Ʒ���ʵ������ʱ���ǱȽϸ��ӺͶ��ģ�ͨ������ģʽ������Ʒ��ʵ������װ������
ʹ�õ����߸���������Ĳ�Ʒ��ʵ�������̣�ֻ�������������ɵõ��Լ���Ҫ�Ĳ�Ʒ��
2���Ե��������ξ���Ĳ�Ʒ�ࡣ���ʹ�ù���ģʽ��������ֻ���Ĳ�Ʒ�ĽӿھͿ����ˣ����ھ����ʵ�֣������߸���������ġ�
��ʹ����˾����ʵ�֣��Ե�������˵û���κ�Ӱ�졣
3��������϶ȡ���Ʒ���ʵ����ͨ����˵�Ǻܸ��ӵģ�����Ҫ�����ܶ���࣬����Щ����ڵ�������˵��������֪����
���ʹ���˹���������������Ҫ���Ľ�����ʵ�����ò�Ʒ�࣬Ȼ�󽻸�������ʹ�á��Ե�������˵����Ʒ���������඼��͸����

2����������ģʽ���ĸ�Ҫ�أ�
1) �����ӿڡ������ӿ��ǹ�������ģʽ�ĺ��ģ��������ֱ�ӽ��������ṩ��Ʒ����ʵ�ʱ���У���ʱ��Ҳ��ʹ��һ������������Ϊ������߽����Ľӿڣ�
�䱾������һ���ġ�
2) ����ʵ�֡��ڱ���У�����ʵ�־������ʵ������Ʒ����ʵ����չ��;������Ҫ�ж����ֲ�Ʒ������Ҫ�ж��ٸ�����Ĺ���ʵ�֡�
3) ��Ʒ�ӿڡ���Ʒ�ӿڵ���ҪĿ���Ƕ����Ʒ�Ĺ淶�����еĲ�Ʒʵ�ֶ�������ѭ��Ʒ�ӿڶ���Ĺ淶����Ʒ�ӿ��ǵ�������Ϊ���ĵģ�
��Ʒ�ӿڶ��������ֱ�Ӿ����˵����ߴ�����ȶ��ԡ�ͬ������Ʒ�ӿ�Ҳ�����ó����������棬��Ҫע����ò�ҪΥ�������滻ԭ��
4) ��Ʒʵ�֡�ʵ�ֲ�Ʒ�ӿڵľ����࣬�����˲�Ʒ�ڿͻ����еľ�����Ϊ��

�򵥹���ģʽ����������ģʽ��Ϊ���ƣ������ǣ��򵥹���ֻ������Ҫ�أ���û�й����ӿڣ����ҵõ���Ʒ�ķ���һ���Ǿ�̬�ġ�
��Ϊû�й����ӿڣ������ڹ���ʵ�ֵ���չ�Է�������������������������ģʽ�ļ򻯰�

3�����ó�����
�����Ǽ򵥹���ģʽ����������ģʽ���ǳ��󹤳�ģʽ�����Ǿ������Ƶ����ԣ��������ǵ����ó���Ҳ�����Ƶġ�
1) ���ȣ���Ϊһ�ִ�����ģʽ�����κ���Ҫ���ɸ��Ӷ���ĵط���������ʹ�ù�������ģʽ��
��һ����Ҫע��ĵط����Ǹ��Ӷ����ʺ�ʹ�ù���ģʽ�����򵥶����ر���ֻ��Ҫͨ��new�Ϳ�����ɴ����Ķ�������ʹ�ù���ģʽ��
���ʹ�ù���ģʽ������Ҫ����һ�������࣬������ϵͳ�ĸ��Ӷȡ�
2) ��Σ�����ģʽ��һ�ֵ��͵Ľ���ģʽ�������ط����ڹ���ģʽ�б��ֵ���Ϊ���ԡ�
����������Լ���װ��Ʒ��Ҫ����������ϵʱ�����Կ���ʹ�ù���ģʽ�������󽵵Ͷ���֮�����϶ȡ�
3) �ٴΣ����ڹ���ģʽ����������ܹ��ģ�����ʵ������Ʒ��������ʵ������ɣ���չ�ԱȽϺá�
Ҳ����˵������Ҫϵͳ�бȽϺõ���չ��ʱ�����Կ��ǹ���ģʽ����ͬ�Ĳ�Ʒ�ò�ͬ��ʵ�ֹ�������װ��
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
������
���Կ�����������Ϊ����װ��������Ҫ����ʵ���������������̺���̥������Щ�������������������޹صģ�
����Υ���˵����ط�����϶�̫�ߡ����ҷǳ���������չ��
���⣬�����з����������̺���̥���ǱȽϾ���ģ���ʵ��Ӧ���У�������Щ��Ʒ�����Ҳ���ǳ���ģ�
�����߸�����֪��������װ��Ʒ������ʹ�ù��������Ļ��������ܹ����Ե����������
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
/*������
 ʹ�ù��������󣬵��ö˵���϶ȴ�󽵵��ˡ����Ҷ��ڹ�����˵���ǿ�����չ�ģ��Ժ��������װ������������ֻ��Ҫ������һ���������ʵ�־Ϳ��ԡ�
 ����������Ի����ȶ��Զ��õ��˼�������
*/
#endif