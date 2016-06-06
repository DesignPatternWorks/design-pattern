#ifndef  _TEMPLATE_H_
#define  _TEMPLATE_H_

#include "common.h"

//  ģ��ģʽ
/* 
1�����
   ����һ�������е��㷨�ĹǼܣ�����һЩ�����ӳٵ������С�
   ģ�巽��ʹ��������Բ��ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض�����

2�����ϣ�
   ģ�巽����һ�ִ��븴�õĻ����������������������Ϊ��Ҫ��������ȡ������еĹ�����Ϊ��
   ��ʹ��ģ�巽��ʱ������Ҫ��һ����ģ�巽��Ӧ��ָ����Щ�����ǿ��Ա��ض���ģ��Լ���Щ�Ǳ��뱻�ض���ġ�
   Ҫ��Ч������һ�������࣬�����д�߱�����ȷ�˽���Щ���������Ϊ�д��ض����
*/
void TemplateTest();
// �Ǽ�������
class AbstractFrameWork
{
public:    // ����Ϊpublic �ͻ��˵���
	// ģ�巽��
	void SkeletonOperator()
	{
		PrimitiveOperator1();
		PrimitiveOperator2();
		PrimitiveOperator3();
		if (isSupportPrimitiveOperator4())
		{
			PrimitiveOperator4();
		}
		PrimitiveOperator5();
	}
protected:  // ����Ϊprotected �ͻ��˲��ɼ�������ɼ�,Ҳ��������Ϊprivate(����virtual����,��ʹprivate����Ҳ�ж�̬)
	//����������ⷽ�������뱻����ʵ��
	virtual void PrimitiveOperator1() = 0;
	virtual void PrimitiveOperator2() = 0;

	// ���������ͨ��������Ĭ��ʵ�֣����Ա����า�ǣ�����������,������Ծ�����,����ʽ��ֱ�ӵ���PrimitiveOperator3,������ģ�巽��SkeletonOperato��
	//����Ǽ�virtual �������д�˸÷���
	void PrimitiveOperator3()
	{
		cout << "PrimitiveOperator3 Default Implement" << endl;
		// ��ʱ���ڿͻ���ͨ������ָ����ָ�������������(ͨ����Գ�����)����ʱ����ָ���ĸ�����������󣬵��õľ��Ǹ��෽��
		//��Ϊû��virtual,û�ж�̬,�Ǿ�̬�󶨵ģ� ��������������ķ���������Ҫ��Ծ�������̣�ͨ������ָ����ָ�������������ʽ��ֱ�ӵ��ø÷���
	}

	//����������ⷽ������Ĭ��ʵ�֣����Ա�������д
	virtual void PrimitiveOperator4()
	{
		cout << "PrimitiveOperator4 Default Implement" << endl;
	}

	// ������平�����ⷽ����Ĭ���ǿյģ�,���Ա�������д,ͨ��������д�����Ƹ��������
	virtual void PrimitiveOperator5()
	{
	}
	// ������平�����ⷽ��(����bool���ͣ�,���Ա�������д,ͨ��������д�����Ƹ��������
	virtual bool isSupportPrimitiveOperator4()
	{
		return true;
	}
};

class ConcreteImplementA : public AbstractFrameWork
{
public:
	void PrimitiveOperator1()
	{
		cout << "ConcreteImplement A Primitive Operator1" << endl;
	}
	void PrimitiveOperator2()
	{
		cout << "ConcreteImplement A Primitive Operator2" << endl;
	}
	void PrimitiveOperator3() //�����˸���Ĭ�ϵ���ͨ����PrimitiveOperator3��������Գ�����ʱ������÷���������Ч�����Ǹ���÷�����virtual
	{
		cout << "ConcreteImplement A Primitive Operator3" << endl;
	}
	void PrimitiveOperator5()  // ��д�˸���Ĭ��Ϊ�յĹ��ӷ���PrimitiveOperator5
	{
		cout << "ConcreteImplement A Primitive Operator5" << endl;
	}
};

class ConcreteImplementB : public AbstractFrameWork
{
public:
	void PrimitiveOperator1()
	{
		cout << "ConcreteImplement B Primitive Operator1" << endl;
	}
	void PrimitiveOperator2()
	{
		cout << "ConcreteImplement B Primitive Operator2" << endl;
	}
	bool isSupportPrimitiveOperator4() // ��д�˸���Ĭ�Ϸ���true�Ĺ��ӷ���isSupportPrimitiveOperator4
	{
		return false;
	}
};

class ConcreteImplementC : public AbstractFrameWork
{
public:
	void PrimitiveOperator1()
	{
		cout << "ConcreteImplement C Primitive Operator1" << endl;
	}
	void PrimitiveOperator2()
	{
		cout << "ConcreteImplement C Primitive Operator2" << endl;
	}
	void PrimitiveOperator3() //�����˸���Ĭ�ϵ���ͨ����PrimitiveOperator3��������Գ�����ʱ������÷���������Ч�����Ǹ���÷�����virtual
	{
		cout << "ConcreteImplement C Primitive Operator3" << endl;
	}
	void PrimitiveOperator4() //��д�˸���Ĭ�ϵ��鷽��PrimitiveOperator4
	{
		cout << "ConcreteImplement C Primitive Operator4" << endl;
	}
};

void TemplateTest_General()
{
	// ��Գ�����
	AbstractFrameWork *pCI_A = new ConcreteImplementA();
	pCI_A->SkeletonOperator();

	AbstractFrameWork *pCI_B = new ConcreteImplementB();
	pCI_B->SkeletonOperator();

	AbstractFrameWork *pCI_C = new ConcreteImplementC();
	pCI_C->SkeletonOperator();

	// ��Ծ�����
	ConcreteImplementA *pC_A = new ConcreteImplementA();
	pC_A->SkeletonOperator();   // û�и��Ǹ���ķ�������Ȼ���õ��Ǹ����PrimitiveOperator3 Default Implement
	pC_A->PrimitiveOperator3(); // �����˸���ķ�����ConcreteImplement A Primitive Operator3
	ConcreteImplementC *pC_C = new ConcreteImplementC();
	pC_C->SkeletonOperator();   // û�и��Ǹ���ķ�������Ȼ���õ��Ǹ����PrimitiveOperator3 Default Implement
	pC_C->PrimitiveOperator3(); // �����˸���ķ�����ConcreteImplement C Primitive Operator3

	SAFE_RELASE_POINTER(pCI_A);
	SAFE_RELASE_POINTER(pCI_B);
	SAFE_RELASE_POINTER(pCI_C);
	SAFE_RELASE_POINTER(pC_A);
	SAFE_RELASE_POINTER(pC_C);
}

// ����ģ��
class Resume
{
public:   // public
	void WriteResume()
	{
		WritePersonalInfo();
		WriteEnducationExp();
		WriteWorkExp();
		if (isNotEnglishMajor())
		{
			WriteCETScore();
		}
		WritePublishedPaper();
	}
protected:  // protected
	virtual void WritePersonalInfo()  = 0;
	virtual void WriteEnducationExp() = 0;
	virtual void WriteWorkExp()       = 0;
	virtual bool isNotEnglishMajor()
	{
		return true;
	}
	virtual void WriteCETScore() = 0;
	virtual void WritePublishedPaper()
	{
	}
};

class ResumeA : public Resume
{
public:
	void WritePersonalInfo()
	{
		cout << "My Name is A" << endl;
	}
	void WriteEnducationExp()
	{
		cout <<"I Graduated from HUST" << endl;
	}
	void WriteWorkExp()
	{
		cout << "I Worked in ZTE" << endl;
	}
	void WriteCETScore()
	{
		cout << "CET4 is 600 score" << endl;
	}
};

class ResumeB : public Resume
{
public:
	void WritePersonalInfo()
	{
		cout << "My Name is B" << endl;
	}
	void WriteEnducationExp()
	{
		cout <<"I Graduated from WuHan University" << endl;
	}
	void WriteWorkExp()
	{
		cout << "I Worked in HW" << endl;
	}
	bool isNotEnglishMajor()
	{
		return false;
	}
	void WriteCETScore() // ����ʵ�֣�������벻��������ʵ���������࣬�˴�Ϊ��ʵ��
	{
	}
	void WritePublishedPaper()
	{
		cout << "I have published a paper about program learning " << endl;
	}
};

void TemplateTest_Resume()
{
	Resume *pR_A = new ResumeA();
	pR_A->WriteResume();

	Resume *pR_B = new ResumeB();
	pR_B->WriteResume();

	SAFE_RELASE_POINTER(pR_A);
	SAFE_RELASE_POINTER(pR_B);
}
void TemplateTest()
{
	cout << "*********** AdapterTest_General: *************" << endl;
	TemplateTest_General();
	cout << "*********** TemplateTest_Resume: *************" << endl;
	TemplateTest_Resume();
}

#endif