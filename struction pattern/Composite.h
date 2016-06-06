#ifndef _COMPOSITE_H_
#define _COMPOSITE_H_

#include "common.h"
#include <memory>
// 组合模式
/*
1、概念：
1）将对象组合成树形结构以表示“部分-整体”的层次结构。组合（Composite）模式使得用户对单个对象和组合对象的使用具有一致性。
2）组合模式（Composite）将小对象组合成树形结构，使用户操作组合对象如同操作一个单个对象。
   组合模式定义了“部分-整体”的层次结构，基本对象可以被组合成更大的对象，而且这种操作是可重复的，不断重复下去就可以得到一个非常大的组合对象，
   但这些组合对象与基本对象拥有相同的接口，因而组合是透明的，用法完全一致。
3) 我们这样来简单的理解组合模式，组合模式就是把一些现有的对象或者元素，经过组合后组成新的对象，新的对象提供内部方法，
   可以让我们很方便的完成这些元素或者内部对象的访问和操作。
   我们也可以把组合对象理解成一个容器，容器提供各种访问其内部对象或者元素的API，我们只需要使用这些方法就可以操作它了
2、场合：
1）你想表示对象的部分-整体层次结构；
2）希望用户忽略组合对象与单个对象的不同，用户将统一地使用组合结构中的所有对象。
引用大话设计模式的片段：“当发现需求中是体现部分与整体层次结构时，以及你希望用户可以忽略组合对象与单个对象的不同，统一地使用组合结构中的所有对象时，
 就应该考虑组合模式了”

3、组成：
Component：
   为组合中的对象声明接口；
   在适当的情况下，实现所有类共有接口的缺省行为；
   声明一个接口用于访问和管理Component的子组件。
Leaf：
   在组合中表示叶节点对象，叶节点没有子节点；
   在组合中定义叶节点的行为。
Composite：
   定义有子部件的那些部件的行为；
   存储子部件。
Client：
   通过Component接口操作组合部件的对象  
 */

/*
** FileName      : Composite.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Composite Pattern Implementation of C++
*/


void CompositeTest();

// 抽象的组件类
class AbstractComponent
{
public:
	virtual ~AbstractComponent() {};
public:
	virtual void Operator() = 0;
	virtual void Add(shared_ptr<AbstractComponent> &pAC) = 0;
	virtual void Remove(shared_ptr<AbstractComponent> &pAC) = 0;
	virtual shared_ptr<AbstractComponent>& GetChild(int n) = 0;
	virtual void Show(int nDepth) = 0;
};
// 叶子组件类，没有Add,Remove等操作内容，该组件内不包含其他组件对象,GetChild 返回NULL
class Leaf : public AbstractComponent
{
private:
	string m_strName;
public:
	Leaf(string strName) : m_strName(strName) {};
	virtual ~Leaf() {};
public:
	void Operator()
	{
		cout << " I am Named" << m_strName << "Leaf Operator" << endl;
	}
	// Leaf组件对象内部没有子对象，故Add,Removew为空,必须去实现AbstractComponent的Virtual接口，即使为空
	void Add(shared_ptr<AbstractComponent> &pAC) {};
	void Remove(shared_ptr<AbstractComponent> &pAC) {};
	shared_ptr<AbstractComponent>& GetChild(int n) {return shared_ptr<AbstractComponent>(0);}
	void Show(int nDepth) 
	{
		for(int i = 0; i < nDepth; i++)
		{
			cout << "--" << flush; // 清除缓存区 不换行，endl 是清除缓冲区 + 换行
		}
		cout << m_strName << endl;
	};
};

// 组合组件类，里面包含其他组件对象
class Composite : public AbstractComponent
{
private:
	string m_strName;
	vector<shared_ptr<AbstractComponent>> m_VecComponent;
public:
	Composite(string strName): m_strName(strName) {};
	virtual ~Composite() {};
public:
	void Operator()
	{
		cout << " I am Named" << m_strName << "Composite Operator" << endl;
	}
	void Add(shared_ptr<AbstractComponent> &pAC)
	{
		m_VecComponent.push_back(pAC);
	}
	void Remove(shared_ptr<AbstractComponent> &pAC) // 删除与指定组件对象名字一样的
	{
		for (vector<shared_ptr<AbstractComponent>>::iterator it = m_VecComponent.begin();
			 it !=m_VecComponent.end();
			 ++it)
		{
			if ((*it) == pAC)
			{
				m_VecComponent.erase(it);
				break;
			}

		}
	}
	shared_ptr<AbstractComponent>& GetChild(int n)
	{
		if (n > m_VecComponent.size())
		{
			cout << "n is out of range" << endl;
			return shared_ptr<AbstractComponent>(0);
		}
		return m_VecComponent[n];
	}

	void Show(int nDepth)
	{
		// 显示当前组合对象自己的名字信息
		for (int i = 0; i< nDepth; i++)
		{
			cout << "--" << flush;
		}
		cout << m_strName << endl;

		// 显示当前组合对象容器内部包含的子对象的名字信息
		for (vector<shared_ptr<AbstractComponent>>::iterator it = m_VecComponent.begin();
			 it != m_VecComponent.end();
			 ++it)
		{
			(*it)->Show(nDepth + 2);
		}
	}
};

void CompositeTest_General()
{
	// 创建根节点
	shared_ptr<AbstractComponent>pAC_Root(new Composite("Root"));
	//创建并添加两个根节点的叶子节点A，B
	shared_ptr<AbstractComponent>pAC_Leaf_Root_A(new Leaf("Leaf A"));
	pAC_Root->Add(pAC_Leaf_Root_A);

	shared_ptr<AbstractComponent>pAC_Leaf_Root_B(new Leaf("Leaf B"));
	pAC_Root->Add(pAC_Leaf_Root_B);

	//创建并添加一个根节点的组合节点A,该组合节点内包含两个Leaf节点A,B
	shared_ptr<AbstractComponent>pAC_Sub_Composite(new Composite("Sub Composite A"));
	pAC_Root->Add(pAC_Sub_Composite);

	// 创建并添加该组合节点内部包含的两个Leaf节点
	shared_ptr<AbstractComponent>pAC_Leaf_Sub_A(new Leaf("Sub Composite Leaf A"));
	pAC_Sub_Composite->Add(pAC_Leaf_Sub_A);

	shared_ptr<AbstractComponent>pAC_Leaf_Sub_B(new Leaf("Sub Composite Leaf B"));
	pAC_Sub_Composite->Add(pAC_Leaf_Sub_B);

	//创建并添加根节点的另一个组合节点A2,该组合节点内包含两个Leaf节点A2,B2
	shared_ptr<AbstractComponent>pAC_Sub_Composite2(new Composite("Sub Composite A2"));
	pAC_Root->Add(pAC_Sub_Composite2);

	// 创建并添加该组合节点内部包含的两个Leaf节点
	shared_ptr<AbstractComponent>pAC_Leaf_Sub_A2(new Leaf("Sub Composite Leaf A2"));
	pAC_Sub_Composite2->Add(pAC_Leaf_Sub_A2);

	shared_ptr<AbstractComponent>pAC_Leaf_Sub_B2(new Leaf("Sub Composite Leaf B2"));
	pAC_Sub_Composite2->Add(pAC_Leaf_Sub_B2);

	// 显示Root下所有组合节点和Leaf节点
	cout << "Before Remove pAC_Leaf_Sub_B2:" << endl <<endl;
	pAC_Root->Show(0); 

	// 删除组合节点A2
	cout << "After Remove pAC_Leaf_Sub_B2:" << endl << endl;
	pAC_Sub_Composite2->Remove(pAC_Leaf_Sub_B2);
	pAC_Root->Show(0);
	//只需要释放根节点，其他节点在根节点的析构函数内释放掉了
}
/* 分析：
1）Composite的关键之一在于一个抽象类，它既可以代表Leaf，又可以代表Composite；
    所以在实际实现时，应该最大化Component接口，Component类应为Leaf和Composite类尽可能多定义一些公共操作。
	Component类通常为这些操作提供缺省的实现，而Leaf和Composite子类可以对它们进行重定义；
2）Component是否应该实现一个Component列表，在上面的代码中，我是在Composite中维护的列表，
   由于在Leaf中，不可能存在子Composite，所以在Composite中维护了一个Component列表，这样就减少了内存的浪费；
3）内存的释放；由于存在树形结构，当父节点都被销毁时，所有的子节点也必须被销毁，
   所以，我是在析构函数中对维护的Component列表进行统一销毁，这样就可以免去客户端频繁销毁子节点的困扰；
4）由于在Component接口提供了最大化的接口定义，导致一些操作对于Leaf节点来说并不适用，
   比如：Leaf节点并不能进行Add和Remove操作，由于Composite模式屏蔽了部分与整体的区别
   为了防止客户对Leaf进行非法的Add和Remove操作，所以，在实际开发过程中，进行Add和Remove操作时，需要进行对应的判断，判断当前节点是否为Composite

 */
// A Composite Example of Company
/*
问题描述：
一个公司的组织结构图:总部下面有多个子公司，同时总部也有各个部门，子公司下面有多个部门*/
// 抽象公司类
class Company
{
private:
	string m_strName;
public:
	Company(string strName) : m_strName(strName) {};
	virtual ~Company() {};
public:
	virtual void Add(Company *pC) = 0;
	virtual void Remove(Company *pC) = 0;
	virtual string GetName()
	{
		return m_strName;
	}
	virtual void Show(int nDepth) = 0;
};
// 叶子节点1---金融部门
class FinanceDepartment : public Company
{
public:
	FinanceDepartment(string strName) : Company(strName) {};
	virtual ~FinanceDepartment() {};
public:
	void Add(Company *pC) {};
	void Remove(Company *pC) {};
	void Show(int nDepth)
	{
		for (int i = 0; i < nDepth; i++)
		{
			cout << "---" << flush;
		}
		cout << GetName() << endl;
	}
};
// 叶子节点2-- HR部门
class HRDepartment : public Company
{
public:
	HRDepartment(string strName) : Company(strName) {};
	virtual ~HRDepartment() {};
public:
	void Add(Company *pC) {};
	void Remove(Company *pC) {};
	void Show(int nDepth)
	{
		for (int i = 0; i < nDepth; i++)
		{
			cout << "---" << flush;
		}
		cout << GetName() << endl;
	}
};
// 组合公司
class CompositeCompany : public Company
{
private:
	list<Company*> m__ListCompany;
public:
	CompositeCompany(string strName) : Company(strName) {};
	virtual ~CompositeCompany() 
	{
		for (list<Company*>::iterator it = m__ListCompany.begin();
			it != m__ListCompany.end();
			++it)
		{
			if (NULL != (*it))
			{
				delete *it;
				*it = NULL;
			}
			m__ListCompany.erase(it);
		}
	};
public:
	void Add(Company *pC) 
	{
		m__ListCompany.push_back(pC);
	};
	void Remove(Company *pC) 
	{
		for (list<Company*>::iterator it = m__ListCompany.begin();
			 it != m__ListCompany.end();
			 ++it) //  ++it 不是it++
		{
			if ((*it)->GetName() == pC->GetName())
			{
				delete *it;
				*it = NULL;
				m__ListCompany.erase(it); // 防止erase之后迭代器失效
				break;
			}

		}
	};
	void Show(int nDepth)
	{
		for (int i = 0; i < nDepth; i++)
		{
			cout << "---" << flush;
		}
		cout << GetName() << endl;
		for (list<Company*>::iterator it = m__ListCompany.begin();
			 it != m__ListCompany.end();
			 ++it)
		{
			if (NULL != (*it))
			{
				(*it)->Show(nDepth + 2);
			}
		}
	}
};



void CompositeTest_Company()
{
	Company *pC_TopCpy = new CompositeCompany("Top Company"); //  why Company company（）构造会出问题？

	Company *pC_Finance = new FinanceDepartment("Company Finance Dept");
	Company *pC_HR      = new HRDepartment("Company HR Dept");

	pC_TopCpy->Add(pC_Finance);
	pC_TopCpy->Add(pC_HR);

	Company *pC_SubCpy = new CompositeCompany("Sub Company");
	Company *pC_Sub_HR = new HRDepartment("Sub Company HR Dept");
	pC_SubCpy->Add(pC_Finance);
	pC_SubCpy->Add(pC_HR);
	pC_SubCpy->Add(pC_Sub_HR);

	pC_TopCpy->Add(pC_SubCpy);
	cout << "Before Remove Sub Company HR Dept" << endl;

	pC_TopCpy->Show(0);

	cout << "After Remove Sub Company HR Dept" << endl;
	pC_SubCpy->Remove(pC_Sub_HR);
	pC_TopCpy->Show(0);
}

void CompositeTest()
{
	cout << "*********** CompositeTest_General: *************" << endl;
	CompositeTest_General();
	cout << "*********** CompositeTest_Company: *************" << endl;
	CompositeTest_Company();
}
#endif