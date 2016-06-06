#ifndef  _VISITOR_H_
#define  _VISITOR_H_

#include "common.h"

// ������ģʽ
/*
1�� ���
	��ʾһ��������ĳ����ṹ�еĸ�Ԫ�صĲ�������ʹ������ڲ��ı��Ԫ�����ǰ���¶�����������ЩԪ�ص��²�����
2�� ��ɫ��
	Visitor ��������߽�ɫ��Ϊ�ö���ṹ�о���Ԫ�ؽ�ɫ����һ�����ʲ����ӿڡ��ò����ӿڵ����ֺͲ�����ʶ�˷��ͷ����������������ߵľ���Ԫ�ؽ�ɫ�����������߾Ϳ���ͨ����Ԫ�ؽ�ɫ���ض��ӿ�ֱ�ӷ�������
	ConcreteVisitor.��������߽�ɫ��ʵ��Visitor�����Ľӿڡ�
	Element ����һ�����ܷ��ʲ���(accept())������һ��������(Visitor)��Ϊ������
	ConcreteElement ����Ԫ�أ�ʵ���˳���Ԫ��(Element)������Ľ��ܲ����ӿڡ�
	ObjectStructure �ṹ�����ɫ������ʹ�÷�����ģʽ�ر��Ľ�ɫ�����߱��������ԣ���ö������Ԫ�أ������ṩһ���߲�ӿ�����������߷�������Ԫ�أ�������Ҫ��������Ƴ�һ�����϶������һ���ۼ�����һ���б�����򼯺ϣ���
3���ŵ㣺
	���ϵ�һְ��ԭ�򣺷������÷�����ģʽ�ĳ����У�Ԫ��������Ҫ��װ�ڷ������еĲ����ض�����Ԫ���౾���ϵ���������ױ�Ĳ�����ʹ�÷�����ģʽһ������ϵ�һְ��ԭ����һ���棬��Ϊ����װ�Ĳ���ͨ����˵�����ױ�ģ����Ե������仯ʱ���Ϳ����ڲ��ı�Ԫ���౾���ǰ���£�ʵ�ֶԱ仯���ֵ���չ��
	��չ�����ã�Ԫ�������ͨ�����ܲ�ͬ�ķ�������ʵ�ֶԲ�ͬ��������չ��
4���ص㣺
	������ģʽ�����ݽṹ�������ڽṹ�ϵĲ�������ϣ�ʹ�ò������Ͽ�������ɵ��ݻ���
	������ģʽ���������ݽṹ����ȶ��㷨���ױ仯��ϵͳ����Ϊ������ģʽʹ���㷨�������ӱ�����ס���ϵͳ���ݽṹ�������ڱ仯���������µ����ݶ������ӽ��������ʺ�ʹ�÷�����ģʽ��
	������ģʽ���ŵ������Ӳ��������ף���Ϊ���Ӳ�����ζ�������µķ����ߡ�������ģʽ���й���Ϊ���е�һ�������߶����У���ı䲻Ӱ��ϵͳ���ݽṹ����ȱ����������µ����ݽṹ������
5�� ���ϣ�
1�� һ������ṹ�����ܶ�����������в�ͬ�Ľӿڣ����������Щ����ʵʩһЩ�������������Ĳ�����
2�� ��Ҫ��һ������ṹ�еĶ�����кܶ಻ͬ�Ĳ��Ҳ���صĲ������������������Щ��������Ⱦ����Щ������ࡣVisitorģʽʹ������Խ���صĲ����������� ������һ�����С�
3�� ���ö���ṹ���ܶ�Ӧ�ù���ʱ����Visitorģʽ��ÿ��Ӧ�ý�������Ҫ�õ��Ĳ�����
4)  �������ṹ������ٸı䣬��������Ҫ�ڴ˽ṹ�϶����µĲ������ı����ṹ����Ҫ�ض�������з����ߵĽӿڣ��������Ҫ�ܴ�Ĵ��ۡ��������ṹ�ྭ���ı䣬��ô���ܻ�������Щ���ж�����Щ�����Ϻá�
	*/

void VisitorTest();


// ��������Ԫ����
class Visitor;
class Element
{
public:
	virtual void Accept(Visitor *pv) = 0;
//	virtual void Operation()  = 0; ÿ��Ԫ�ظ������Լ��Ĳ���
};

// �����������
class ConcreteElementA;
class ConcreteElementB;
class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *pea) = 0;   // �������Լ��Ĳ�����VisitConcreteElementA ��VisitConcreteElementB���Ժϲ�һ�����������ǲ��������Ǿ����Element,������
	virtual void VisitConcreteElementB(ConcreteElementB *peb) = 0;
};


// ��������Ԫ����A
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

// ��������Ԫ����B
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

// ���������A
class ConcreteVisitorA : public Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *pea)  // VisitConcreteElementA ��VisitConcreteElementB���Ժϲ�һ������
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

// ���������B
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

//ÿ��Stadium�й�ͬ�ĳ��󷽷�DoSports

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
	//// ���ذ�
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

	//// ���ذ�
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

	//// ���ذ�
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
		//// ���ذ�
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
		//// ���ذ�
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
		//// ���ذ�
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