#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "common.h"

// 建造者模式

// 此处用到了工厂方法模式 + 建造者模式的结合\

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

class BuilderA: public AbstractBuilder //构建产品A内部部分
{
private:
	AbstractProduct *m_pProduct;
public:
	BuilderA()
	{
		m_pProduct = new ProductA(); //构建产品A
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

class BuilderB: public AbstractBuilder //构建产品B内部部分
{
private:
	AbstractProduct *m_pProduct;
public:
	BuilderB()
	{
		m_pProduct = new ProductB(); //构建产品B
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
	void CreateProduct()      // 组装整个产品
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
	AbstractBuilder *pAB = new BuilderA();  // 构建产品A
	Director *pD = new Director(pAB);
	pD->CreateProduct();       // 引导者负责通过 Builder 组装产品
	AbstractProduct *pAP = pAB->GetProduct();  // 建造者负责 具体的Builder 组装产品，并提供获取产品接口
	pAP->ShowProduct();

	AbstractBuilder *pAB2 = new BuilderB();   // 构建产品B
	Director *pD2 = new Director(pAB2);
	pD2->CreateProduct();       // 引导者负责通过 Builder 组装产品
	AbstractProduct *pAP2 = pAB2->GetProduct();  // 建造者负责 具体的Builder 组装产品，并提供获取产品接口
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

/* 分析：
1、 建造者模式生成的对象有复杂的内部结构，将分步骤的去构建一个复杂的对象，分多少步是确定的，而每一步的实现是不同的，可能经常发生变化；
2、 在上面的例子中，我们都看到了最终生成的Man和Product都没有抽象类，
    这又导出建造者适用的一种情况，当需要创建复杂对象的过程中，复杂对象没有多少共同的特点，很难抽象出来时，
    而复杂对象的组装又有一定的相似点时，建造者模式就可以发挥出作用。
3、一个复杂对象是由多个部件组成的，建造者模式是把复杂对象的创建和部件的创建分别开来，分别用Builder类和Director类来表示。
    用Director构建最后的复杂对象，而在上面Builder接口中封装的是如何创建一个个部件（复杂对象是由这些部件组成的），
	也就是说，Director负责如何将部件最后组装成产品。这样建造者模式就让设计和实现解耦了。
	刚开始接触建造者模式的时候，最容易把建造者和抽象工厂模式混淆了。由于而这都属于创建型的设计模式，所以二者之间是有公共点的
	但是建造者模式注重于对象组合，即不同的小对象组成一个整体的复杂大对象
	而抽象工厂模式针对于接口编程，只是对外提供创建对象的工厂接口，不负责对象之后的处理
*/
#endif