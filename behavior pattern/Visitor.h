#ifndef  _VISITOR_H_
#define  _VISITOR_H_

#include "common.h"

// 访问者模式
/*
1、 概念：
	表示一个作用于某对象结构中的各元素的操作。它使你可以在不改变各元素类的前提下定义作用于这些元素的新操作。
2、 角色：
	Visitor 抽象访问者角色，为该对象结构中具体元素角色声明一个访问操作接口。该操作接口的名字和参数标识了发送访问请求给具体访问者的具体元素角色，这样访问者就可以通过该元素角色的特定接口直接访问它。
	ConcreteVisitor.具体访问者角色，实现Visitor声明的接口。
	Element 定义一个接受访问操作(accept())，它以一个访问者(Visitor)作为参数。
	ConcreteElement 具体元素，实现了抽象元素(Element)所定义的接受操作接口。
	ObjectStructure 结构对象角色，这是使用访问者模式必备的角色。它具备以下特性：能枚举它的元素；可以提供一个高层接口以允许访问者访问它的元素；如有需要，可以设计成一个复合对象或者一个聚集（如一个列表或无序集合）。
3、优点：
	符合单一职责原则：凡是适用访问者模式的场景中，元素类中需要封装在访问者中的操作必定是与元素类本身关系不大且是易变的操作，使用访问者模式一方面符合单一职责原则，另一方面，因为被封装的操作通常来说都是易变的，所以当发生变化时，就可以在不改变元素类本身的前提下，实现对变化部分的扩展。
	扩展性良好：元素类可以通过接受不同的访问者来实现对不同操作的扩展。
4、特点：
	访问者模式把数据结构和作用于结构上的操作解耦合，使得操作集合可相对自由地演化。
	访问者模式适用于数据结构相对稳定算法又易变化的系统。因为访问者模式使得算法操作增加变得容易。若系统数据结构对象易于变化，经常有新的数据对象增加进来，则不适合使用访问者模式。
	访问者模式的优点是增加操作很容易，因为增加操作意味着增加新的访问者。访问者模式将有关行为集中到一个访问者对象中，其改变不影响系统数据结构。其缺点就是增加新的数据结构很困难
5、 场合：
1） 一个对象结构包含很多类对象，它们有不同的接口，而你想对这些对象实施一些依赖于其具体类的操作。
2） 需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而你想避免让这些操作“污染”这些对象的类。Visitor模式使得你可以将相关的操作集中起来 定义在一个类中。
3） 当该对象结构被很多应用共享时，用Visitor模式让每个应用仅包含需要用到的操作。
4)  定义对象结构的类很少改变，但经常需要在此结构上定义新的操作。改变对象结构类需要重定义对所有访问者的接口，这可能需要很大的代价。如果对象结构类经常改变，那么可能还是在这些类中定义这些操作较好。
	*/

void VisitorTest();


// 抽象数据元素类
class Visitor;
class Element
{
public:
	virtual void Accept(Visitor *pv) = 0;
//	virtual void Operation()  = 0; 每个元素各种有自己的操作
};

// 抽象访问者类
class ConcreteElementA;
class ConcreteElementB;
class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *pea) = 0;   // 若各有自己的操作，VisitConcreteElementA 和VisitConcreteElementB可以合并一个函数，但是参数必须是具体的Element,即重载
	virtual void VisitConcreteElementB(ConcreteElementB *peb) = 0;
};


// 具体数据元素类A
class ConcreteElementA : public Element
{
public:
	virtual void Accept(Visitor *pv)
	{
		pv->VisitConcreteElementA(this);
	}
	void OperationA()  
	{
		cout << "Concrete Element A OperatorA!!!" << endl;
	}
};

// 具体数据元素类B
class ConcreteElementB : public Element
{
public:
	virtual void Accept(Visitor *pv)
	{
		pv->VisitConcreteElementB(this);
	}
	virtual void OperationB()
	{
		cout << "Concrete Element B OperatorB!!!" << endl;
	}
};

// 具体访问者A
class ConcreteVisitorA : public Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *pea)  // VisitConcreteElementA 和VisitConcreteElementB可以合并一个函数
	{
		cout << "Concrete Visitor A:" << endl;
		pea->OperationA();
	}
	virtual void VisitConcreteElementB(ConcreteElementB *peb)
	{
		cout << "Concrete Visitor A:" << endl;
		peb->OperationB();
	}
};

// 具体访问者B
class ConcreteVisitorB : public Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *pea)
	{
		cout << "Concrete Visitor B:" << endl;
		pea->OperationA();
	}
	virtual void VisitConcreteElementB(ConcreteElementB *peb)
	{
		cout << "Concrete Visitor B:" << endl;
		peb->OperationB();
	}
};

class ObjectStructure
{
private:
	list<Element*> m_ListElement;
public:
	void Attach(Element *pe)
	{
		m_ListElement.push_back(pe);
	}

	void Detach(Element *pe)
	{
		list<Element*> ::iterator it = find(m_ListElement.begin(), m_ListElement.end(), pe);
		if (it != m_ListElement.end())
		{
			m_ListElement.erase(it);
		}
	}

	void Accept(Visitor *pv)
	{
		for (list<Element*> ::iterator it = m_ListElement.begin();
			 it != m_ListElement.end();
			 ++it)
		{
			(*it)->Accept(pv);
		}
	}
};


void VisitorTest_General()
{
	ObjectStructure *pOS = new ObjectStructure();

	Element *pEA = new ConcreteElementA();
	Element *pEB = new ConcreteElementB();

	pOS->Attach(pEA);
	pOS->Attach(pEB);

	Visitor *pVA = new ConcreteVisitorA();
	Visitor *pVB = new ConcreteVisitorB();

	pOS->Accept(pVA);
	pOS->Accept(pVB);

	cout << "After Detach ConcretElement A:" << endl;

	pOS->Detach(pEA);
	pOS->Accept(pVA);
	pOS->Accept(pVB);

	pOS->Detach(pEB);

	SAFE_RELASE_POINTER(pOS);
	SAFE_RELASE_POINTER(pEA);
	SAFE_RELASE_POINTER(pEB);
	SAFE_RELASE_POINTER(pVA);
	SAFE_RELASE_POINTER(pVB);
}

//每个Stadium有共同的抽象方法DoSports

// Abstract Element
class SportsLover;
class Stadium
{
public:
	virtual void Accept(SportsLover *pSL) = 0;
	virtual void DoSports() = 0;
};

class BadmintonStadium;
class PingpongStadium;
class BascketballStadium;

// Abstract Visitor
class SportsLover
{
public:
 
	virtual void VisitBadmintonStadium(BadmintonStadium *pS) = 0;
	virtual void VisitPingpongStadium(PingpongStadium *pS) = 0;
	virtual void VisitBasketballStadium(BascketballStadium *pS) = 0;
	//// 重载版
	//virtual void Visit(BadmintonStadium *pS) = 0;
	//virtual void Visit(PingpongStadium *pS) = 0;
	//virtual void Visit(BascketballStadium *pS) = 0;
};

// Stduent Visitor
class Students : public SportsLover
{
public:

	virtual void VisitBadmintonStadium(BadmintonStadium *pS)
	{
		cout << "students visit: ";
		//pS->DoSports();
	}
	virtual void VisitPingpongStadium(PingpongStadium *pS)
	{
		cout << "students visit: ";
		//pS->DoSports();
	}
	virtual void VisitBasketballStadium(BascketballStadium *pS)
	{
		cout << "students visit: ";
		//pS->DoSports();
	}

	//// 重载版
	//virtual void Visit(BadmintonStadium *pS)
	//{
	//	cout << "students visit: " << endl;
	//	pS->DoSports();
	//}
	//virtual void Visit(PingpongStadium *pS)
	//{
	//	cout << "students visit: " << endl;
	//	pS->DoSports();
	//}
	//virtual void Visit(BascketballStadium *pS)
	//{
	//	cout << "students visit: " << endl;
	//	pS->DoSports();
	//}
};

// Teacher Visitor
class Teachers : public SportsLover
{
public:

	virtual void VisitBadmintonStadium(BadmintonStadium *pS)
	{
		cout << "teachers visit: ";
		//pS->DoSports();
	}
	virtual void VisitPingpongStadium(PingpongStadium *pS)
	{
		cout << "teachers visit: ";
		//pS->DoSports();
	}
	virtual void VisitBasketballStadium(BascketballStadium *pS)
	{
		cout << "teachers visit: ";
		//pS->DoSports();
	}

	//// 重载版
	//virtual void Visit(BadmintonStadium *pS)
	//{
	//	cout << "teachers visit: " << endl;
	//	pS->DoSports();
	//}
	//virtual void Visit(PingpongStadium *pS)
	//{
	//	cout << "teachers visit: " << endl;
	//	pS->DoSports();
	//}
	//virtual void Visit(BascketballStadium *pS)
	//{
	//	cout << "teachers visit: " << endl;
	//	pS->DoSports();
	//}
};

// BadmintonStadium
class BadmintonStadium : public Stadium
{
public:
	virtual void Accept(SportsLover *pSL)
	{
		pSL->VisitBadmintonStadium(this);
		//// 重载版
		//pSL->Visit(this);
	}
	virtual void DoSports()
	{
		cout << "Doing Badminton Sport" << endl;
	}
};

// PingpongStadium
class PingpongStadium : public Stadium
{
public:
	virtual void Accept(SportsLover *pSL)
	{
		pSL->VisitPingpongStadium(this);
		//// 重载版
		//pSL->Visit(this);
	}
	virtual void DoSports()
	{
		cout << "Doing Ping Pong Sport" << endl;
	}
};

class BascketballStadium : public Stadium
{
public:
	virtual void Accept(SportsLover *pSL)
	{
		pSL->VisitBasketballStadium(this);
		//// 重载版
		//pSL->Visit(this);
	}
	virtual void DoSports()
	{
		cout << "Doing Bascket ball Sport" << endl;
	}
};

class StadiumContainer
{
private:
	vector<Stadium*> m_VectorStadium;
public:
	void Attach(Stadium *ps)
	{
		m_VectorStadium.push_back(ps);
	}
	void Detach(Stadium *ps)
	{
		vector<Stadium*> :: iterator it  = find(m_VectorStadium.begin(), m_VectorStadium.end(), ps);
		if (it != m_VectorStadium.end())
		{
			m_VectorStadium.erase(it);
		}
	}
	void Accept(SportsLover *pSL)
	{
		for (vector<Stadium*> :: iterator it  = m_VectorStadium.begin();
			 it != m_VectorStadium.end();
			 ++it)
		{
			(*it)->Accept(pSL);
		}
	}
};

void VisitorTest_Sports()
{
	StadiumContainer *pSC = new StadiumContainer();

	BadmintonStadium   *pBS = new BadmintonStadium();
	PingpongStadium    *pPS = new PingpongStadium();
	BascketballStadium *pBkS = new BascketballStadium();

	pSC->Attach(pBS);
	pSC->Attach(pPS);
	pSC->Attach(pBkS);

	SportsLover  *pSS = new Students();
	SportsLover  *pST = new Teachers();

	pSC->Accept(pSS);
	pSC->Accept(pST);

	cout << "Detach Ping Pong Stadium !!!" << endl;
	pSC->Detach(pPS);

	pSC->Accept(pSS);
	pSC->Accept(pST);

	SAFE_RELASE_POINTER(pSC);
	SAFE_RELASE_POINTER(pBS);
	SAFE_RELASE_POINTER(pBkS);
	SAFE_RELASE_POINTER(pPS);
	SAFE_RELASE_POINTER(pSS);
	SAFE_RELASE_POINTER(pST);
}

void VisitorTest()
{
	cout << "*********** VisitorTest_General: *************" << endl;
	VisitorTest_General();
	cout << "*********** VisitorTest_Sports: *************" << endl;
	VisitorTest_Sports();
}
#endif