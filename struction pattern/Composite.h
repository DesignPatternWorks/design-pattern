#ifndef _COMPOSITE_H_
#define _COMPOSITE_H_

#include "common.h"
#include <memory>
// ���ģʽ
/*
1�����
1����������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ����ϣ�Composite��ģʽʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�
2�����ģʽ��Composite����С������ϳ����νṹ��ʹ�û�������϶�����ͬ����һ����������
   ���ģʽ�����ˡ�����-���塱�Ĳ�νṹ������������Ա���ϳɸ���Ķ��󣬶������ֲ����ǿ��ظ��ģ������ظ���ȥ�Ϳ��Եõ�һ���ǳ������϶���
   ����Щ��϶������������ӵ����ͬ�Ľӿڣ���������͸���ģ��÷���ȫһ�¡�
3) �����������򵥵�������ģʽ�����ģʽ���ǰ�һЩ���еĶ������Ԫ�أ�������Ϻ�����µĶ����µĶ����ṩ�ڲ�������
   ���������Ǻܷ���������ЩԪ�ػ����ڲ�����ķ��ʺͲ�����
   ����Ҳ���԰���϶�������һ�������������ṩ���ַ������ڲ��������Ԫ�ص�API������ֻ��Ҫʹ����Щ�����Ϳ��Բ�������
2�����ϣ�
1�������ʾ����Ĳ���-�����νṹ��
2��ϣ���û�������϶����뵥������Ĳ�ͬ���û���ͳһ��ʹ����Ͻṹ�е����ж���
���ô����ģʽ��Ƭ�Σ��������������������ֲ����������νṹʱ���Լ���ϣ���û����Ժ�����϶����뵥������Ĳ�ͬ��ͳһ��ʹ����Ͻṹ�е����ж���ʱ��
 ��Ӧ�ÿ������ģʽ�ˡ�

3����ɣ�
Component��
   Ϊ����еĶ��������ӿڣ�
   ���ʵ�������£�ʵ�������๲�нӿڵ�ȱʡ��Ϊ��
   ����һ���ӿ����ڷ��ʺ͹���Component���������
Leaf��
   ������б�ʾҶ�ڵ����Ҷ�ڵ�û���ӽڵ㣻
   ������ж���Ҷ�ڵ����Ϊ��
Composite��
   �������Ӳ�������Щ��������Ϊ��
   �洢�Ӳ�����
Client��
   ͨ��Component�ӿڲ�����ϲ����Ķ���  
 */

/*
** FileName      : Composite.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Composite Pattern Implementation of C++
*/


void CompositeTest();

// ����������
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
// Ҷ������࣬û��Add,Remove�Ȳ������ݣ�������ڲ����������������,GetChild ����NULL
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
	// Leaf��������ڲ�û���Ӷ��󣬹�Add,RemovewΪ��,����ȥʵ��AbstractComponent��Virtual�ӿڣ���ʹΪ��
	void Add(shared_ptr<AbstractComponent> &pAC) {};
	void Remove(shared_ptr<AbstractComponent> &pAC) {};
	shared_ptr<AbstractComponent>& GetChild(int n) {return shared_ptr<AbstractComponent>(0);}
	void Show(int nDepth) 
	{
		for(int i = 0; i < nDepth; i++)
		{
			cout << "--" << flush; // ��������� �����У�endl ����������� + ����
		}
		cout << m_strName << endl;
	};
};

// �������࣬������������������
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
	void Remove(shared_ptr<AbstractComponent> &pAC) // ɾ����ָ�������������һ����
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
		// ��ʾ��ǰ��϶����Լ���������Ϣ
		for (int i = 0; i< nDepth; i++)
		{
			cout << "--" << flush;
		}
		cout << m_strName << endl;

		// ��ʾ��ǰ��϶��������ڲ��������Ӷ����������Ϣ
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
	// �������ڵ�
	shared_ptr<AbstractComponent>pAC_Root(new Composite("Root"));
	//����������������ڵ��Ҷ�ӽڵ�A��B
	shared_ptr<AbstractComponent>pAC_Leaf_Root_A(new Leaf("Leaf A"));
	pAC_Root->Add(pAC_Leaf_Root_A);

	shared_ptr<AbstractComponent>pAC_Leaf_Root_B(new Leaf("Leaf B"));
	pAC_Root->Add(pAC_Leaf_Root_B);

	//���������һ�����ڵ����Ͻڵ�A,����Ͻڵ��ڰ�������Leaf�ڵ�A,B
	shared_ptr<AbstractComponent>pAC_Sub_Composite(new Composite("Sub Composite A"));
	pAC_Root->Add(pAC_Sub_Composite);

	// ��������Ӹ���Ͻڵ��ڲ�����������Leaf�ڵ�
	shared_ptr<AbstractComponent>pAC_Leaf_Sub_A(new Leaf("Sub Composite Leaf A"));
	pAC_Sub_Composite->Add(pAC_Leaf_Sub_A);

	shared_ptr<AbstractComponent>pAC_Leaf_Sub_B(new Leaf("Sub Composite Leaf B"));
	pAC_Sub_Composite->Add(pAC_Leaf_Sub_B);

	//��������Ӹ��ڵ����һ����Ͻڵ�A2,����Ͻڵ��ڰ�������Leaf�ڵ�A2,B2
	shared_ptr<AbstractComponent>pAC_Sub_Composite2(new Composite("Sub Composite A2"));
	pAC_Root->Add(pAC_Sub_Composite2);

	// ��������Ӹ���Ͻڵ��ڲ�����������Leaf�ڵ�
	shared_ptr<AbstractComponent>pAC_Leaf_Sub_A2(new Leaf("Sub Composite Leaf A2"));
	pAC_Sub_Composite2->Add(pAC_Leaf_Sub_A2);

	shared_ptr<AbstractComponent>pAC_Leaf_Sub_B2(new Leaf("Sub Composite Leaf B2"));
	pAC_Sub_Composite2->Add(pAC_Leaf_Sub_B2);

	// ��ʾRoot��������Ͻڵ��Leaf�ڵ�
	cout << "Before Remove pAC_Leaf_Sub_B2:" << endl <<endl;
	pAC_Root->Show(0); 

	// ɾ����Ͻڵ�A2
	cout << "After Remove pAC_Leaf_Sub_B2:" << endl << endl;
	pAC_Sub_Composite2->Remove(pAC_Leaf_Sub_B2);
	pAC_Root->Show(0);
	//ֻ��Ҫ�ͷŸ��ڵ㣬�����ڵ��ڸ��ڵ�������������ͷŵ���
}
/* ������
1��Composite�Ĺؼ�֮һ����һ�������࣬���ȿ��Դ���Leaf���ֿ��Դ���Composite��
    ������ʵ��ʵ��ʱ��Ӧ�����Component�ӿڣ�Component��ӦΪLeaf��Composite�ྡ���ܶඨ��һЩ����������
	Component��ͨ��Ϊ��Щ�����ṩȱʡ��ʵ�֣���Leaf��Composite������Զ����ǽ����ض��壻
2��Component�Ƿ�Ӧ��ʵ��һ��Component�б�������Ĵ����У�������Composite��ά�����б�
   ������Leaf�У������ܴ�����Composite��������Composite��ά����һ��Component�б������ͼ������ڴ���˷ѣ�
3���ڴ���ͷţ����ڴ������νṹ�������ڵ㶼������ʱ�����е��ӽڵ�Ҳ���뱻���٣�
   ���ԣ����������������ж�ά����Component�б����ͳһ���٣������Ϳ�����ȥ�ͻ���Ƶ�������ӽڵ�����ţ�
4��������Component�ӿ��ṩ����󻯵Ľӿڶ��壬����һЩ��������Leaf�ڵ���˵�������ã�
   ���磺Leaf�ڵ㲢���ܽ���Add��Remove����������Compositeģʽ�����˲��������������
   Ϊ�˷�ֹ�ͻ���Leaf���зǷ���Add��Remove���������ԣ���ʵ�ʿ��������У�����Add��Remove����ʱ����Ҫ���ж�Ӧ���жϣ��жϵ�ǰ�ڵ��Ƿ�ΪComposite

 */
// A Composite Example of Company
/*
����������
һ����˾����֯�ṹͼ:�ܲ������ж���ӹ�˾��ͬʱ�ܲ�Ҳ�и������ţ��ӹ�˾�����ж������*/
// ����˾��
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
// Ҷ�ӽڵ�1---���ڲ���
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
// Ҷ�ӽڵ�2-- HR����
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
// ��Ϲ�˾
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
			 ++it) //  ++it ����it++
		{
			if ((*it)->GetName() == pC->GetName())
			{
				delete *it;
				*it = NULL;
				m__ListCompany.erase(it); // ��ֹerase֮�������ʧЧ
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
	Company *pC_TopCpy = new CompositeCompany("Top Company"); //  why Company company�������������⣿

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