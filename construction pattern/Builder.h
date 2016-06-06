#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "common.h"

// ������ģʽ

// �˴��õ��˹�������ģʽ + ������ģʽ�Ľ��\

void BuilderTest();
class AbstractProduct
{
public:
	virtual void AddPart(const char* part) = 0;
	virtual void ShowProduct() = 0;
};

class ProductA: public AbstractProduct
{
private:
	vector<const char*> m_VecPart;
public:
	void AddPart(const char *part)
	{
		m_VecPart.push_back(part);
	}
	void ShowProduct()
	{
		cout << "I am Product A!" << endl;
		for (vector<const char*>::iterator it = m_VecPart.begin(); it != m_VecPart.end(); ++it)
		{
			cout << *it << endl;
		}
	}
};

class ProductB: public AbstractProduct
{
private:
	vector<const char*> m_VecPart;
public:
	void AddPart(const char *part)
	{
		m_VecPart.push_back(part);
	}
	void ShowProduct()
	{
		cout << "I am Product B!" << endl;
		for (vector<const char*>::iterator it = m_VecPart.begin(); it != m_VecPart.end(); ++it)
		{
			cout << *it << endl;
		}
	}
};

class AbstractBuilder
{
public:
	virtual void BuilderPart1() = 0;
	virtual void BuilderPart2() = 0;
	virtual AbstractProduct* GetProduct() = 0;
};

class BuilderA: public AbstractBuilder //������ƷA�ڲ�����
{
private:
	AbstractProduct *m_pProduct;
public:
	BuilderA()
	{
		m_pProduct = new ProductA(); //������ƷA
	}
	void BuilderPart1()
	{
		m_pProduct->AddPart("A Part 1 is Completed!");
	}
	void BuilderPart2()
	{
		m_pProduct->AddPart("A Part 2 is Completed!");
	}
	AbstractProduct* GetProduct()
	{
		return m_pProduct;
	}
};

class BuilderB: public AbstractBuilder //������ƷB�ڲ�����
{
private:
	AbstractProduct *m_pProduct;
public:
	BuilderB()
	{
		m_pProduct = new ProductB(); //������ƷB
	}
	void BuilderPart1()
	{
		m_pProduct->AddPart("B Part 1 is Completed!");
	}
	void BuilderPart2()
	{
		m_pProduct->AddPart("B Part 2 is Completed!");
	}
	AbstractProduct* GetProduct()
	{
		return m_pProduct;
	}
};

class Director
{
private:
	AbstractBuilder *m_pBuilder;
public:
	Director(AbstractBuilder *pbuilder): m_pBuilder(pbuilder) {};
	void CreateProduct()      // ��װ������Ʒ
	{
		m_pBuilder->BuilderPart1();
		m_pBuilder->BuilderPart2();
	}
};

// A Simple Example Builder Man: Only Builder Mode
/*typedef enum tag_MAN_TYPE
{
	THIN_MAN,
	FAT_MAN
}MAN_TYPE;*/
class ManBuilder
{
public:
	virtual void BuilderHead() = 0;
	virtual void BuilderBody() = 0;
	virtual void BuilderHand() = 0;
	virtual void BuilderLeg() = 0;
};

class ThinBuilder: public ManBuilder
{
public:
	void BuilderHead()
	{
		cout << "Thin Builder Head" << endl;
	}
	void BuilderBody()
	{
		cout << "Thin Builder Body" << endl;
	}
	void BuilderHand()
	{
		cout << "Thin Builder Hand" << endl;
	}
	void BuilderLeg()
	{
		cout << "Thin Builder Leg" << endl;
	}
};

class FatBuilder: public ManBuilder
{
public:
	void BuilderHead()
	{
		cout << "Fat Builder Head" << endl;
	}
	void BuilderBody()
	{
		cout << "Fat Builder Body" << endl;
	}
	void BuilderHand()
	{
		cout << "Fat Builder Hand" << endl;
	}
	void BuilderLeg()
	{
		cout << "Fat Builder Leg" << endl;
	}
};

class ManDirector
{
private:
	ManBuilder *m_pBuilder;
public:
	ManDirector(ManBuilder *pBuilder): m_pBuilder(pBuilder) {};
	void CreateMan()
	{
		m_pBuilder->BuilderHead();
		m_pBuilder->BuilderBody();
		m_pBuilder->BuilderHand();
		m_pBuilder->BuilderLeg();
	}
};

void BuilderTest()
{
	AbstractBuilder *pAB = new BuilderA();  // ������ƷA
	Director *pD = new Director(pAB);
	pD->CreateProduct();       // �����߸���ͨ�� Builder ��װ��Ʒ
	AbstractProduct *pAP = pAB->GetProduct();  // �����߸��� �����Builder ��װ��Ʒ�����ṩ��ȡ��Ʒ�ӿ�
	pAP->ShowProduct();

	AbstractBuilder *pAB2 = new BuilderB();   // ������ƷB
	Director *pD2 = new Director(pAB2);
	pD2->CreateProduct();       // �����߸���ͨ�� Builder ��װ��Ʒ
	AbstractProduct *pAP2 = pAB2->GetProduct();  // �����߸��� �����Builder ��װ��Ʒ�����ṩ��ȡ��Ʒ�ӿ�
	pAP2->ShowProduct();

	delete pAB; pAB = NULL;
	delete pD; pD = NULL;
	delete pAP; pAP = NULL;

	delete pAB2; pAB2 = NULL;
	delete pD2; pD2 = NULL;
	delete pAP2; pAP2 = NULL;

	// A Example Test
	ManBuilder *pMB = new ThinBuilder();
	ManDirector MD(pMB);
	MD.CreateMan();

	ManBuilder *pMB2 = new FatBuilder();
	ManDirector MD2(pMB2);
	MD2.CreateMan();

	delete pMB; pMB = NULL;
	delete pMB2; pMB2 = NULL;
}

/* ������
1�� ������ģʽ���ɵĶ����и��ӵ��ڲ��ṹ�����ֲ����ȥ����һ�����ӵĶ��󣬷ֶ��ٲ���ȷ���ģ���ÿһ����ʵ���ǲ�ͬ�ģ����ܾ��������仯��
2�� ������������У����Ƕ��������������ɵ�Man��Product��û�г����࣬
    ���ֵ������������õ�һ�����������Ҫ�������Ӷ���Ĺ����У����Ӷ���û�ж��ٹ�ͬ���ص㣬���ѳ������ʱ��
    �����Ӷ������װ����һ�������Ƶ�ʱ��������ģʽ�Ϳ��Է��ӳ����á�
3��һ�����Ӷ������ɶ��������ɵģ�������ģʽ�ǰѸ��Ӷ���Ĵ����Ͳ����Ĵ����ֱ������ֱ���Builder���Director������ʾ��
    ��Director�������ĸ��Ӷ��󣬶�������Builder�ӿ��з�װ������δ���һ�������������Ӷ���������Щ������ɵģ���
	Ҳ����˵��Director������ν����������װ�ɲ�Ʒ������������ģʽ������ƺ�ʵ�ֽ����ˡ�
	�տ�ʼ�Ӵ�������ģʽ��ʱ�������װѽ����ߺͳ��󹤳�ģʽ�����ˡ����ڶ��ⶼ���ڴ����͵����ģʽ�����Զ���֮�����й������
	���ǽ�����ģʽע���ڶ�����ϣ�����ͬ��С�������һ������ĸ��Ӵ����
	�����󹤳�ģʽ����ڽӿڱ�̣�ֻ�Ƕ����ṩ��������Ĺ����ӿڣ����������֮��Ĵ���
*/
#endif