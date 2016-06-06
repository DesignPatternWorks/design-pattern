#ifndef  _TEMPLATE_H_
#define  _TEMPLATE_H_

#include "common.h"

//  模板模式
/* 
1、概念：
   定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。
   模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤

2、场合：
   模板方法是一种代码复用的基本技术。它们在类库中尤为重要，它们提取了类库中的公共行为。
   在使用模板方法时，很重要的一点是模板方法应该指明哪些操作是可以被重定义的，以及哪些是必须被重定义的。
   要有效的重用一个抽象类，子类编写者必须明确了解哪些操作是设计为有待重定义的
*/
void TemplateTest();
// 骨架流程类
class AbstractFrameWork
{
public:    // 声明为public 客户端调用
	// 模板方法
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
protected:  // 声明为protected 客户端不可见，子类可见,也可以声明为private(对于virtual而言,即使private属性也有多态)
	//父类抽象虚拟方法，必须被子类实现
	virtual void PrimitiveOperator1() = 0;
	virtual void PrimitiveOperator2() = 0;

	// 父类具体普通方法，有默认实现，可以被子类覆盖（是有条件的,必须面对具体编程,且显式的直接调用PrimitiveOperator3,不能是模板方法SkeletonOperato）
	//最好是加virtual 子类就重写了该方法
	void PrimitiveOperator3()
	{
		cout << "PrimitiveOperator3 Default Implement" << endl;
		// 此时若在客户端通过基类指针来指向具体的子类对象(通过面对抽象编程)，此时不管指向哪个具体子类对象，调用的均是父类方法
		//因为没有virtual,没有多态,是静态绑定的； 若想调用子类对象的方法，必须要面对具体对象编程，通过子类指针来指向子类对象，且显式的直接调用该方法
	}

	//父类具体虚拟方法，有默认实现，可以被子类重写
	virtual void PrimitiveOperator4()
	{
		cout << "PrimitiveOperator4 Default Implement" << endl;
	}

	// 父类具体钩子虚拟方法（默认是空的）,可以被子类重写,通过子类重写来控制父类的流程
	virtual void PrimitiveOperator5()
	{
	}
	// 父类具体钩子虚拟方法(返回bool类型）,可以被子类重写,通过子类重写来控制父类的流程
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
	void PrimitiveOperator3() //覆盖了父类默认的普通方法PrimitiveOperator3，但是面对抽象编程时候子类该方法不会生效，除非父类该方法加virtual
	{
		cout << "ConcreteImplement A Primitive Operator3" << endl;
	}
	void PrimitiveOperator5()  // 重写了父类默认为空的钩子方法PrimitiveOperator5
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
	bool isSupportPrimitiveOperator4() // 重写了父类默认返回true的钩子方法isSupportPrimitiveOperator4
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
	void PrimitiveOperator3() //覆盖了父类默认的普通方法PrimitiveOperator3，但是面对抽象编程时候子类该方法不会生效，除非父类该方法加virtual
	{
		cout << "ConcreteImplement C Primitive Operator3" << endl;
	}
	void PrimitiveOperator4() //重写了父类默认的虚方法PrimitiveOperator4
	{
		cout << "ConcreteImplement C Primitive Operator4" << endl;
	}
};

void TemplateTest_General()
{
	// 面对抽象编程
	AbstractFrameWork *pCI_A = new ConcreteImplementA();
	pCI_A->SkeletonOperator();

	AbstractFrameWork *pCI_B = new ConcreteImplementB();
	pCI_B->SkeletonOperator();

	AbstractFrameWork *pCI_C = new ConcreteImplementC();
	pCI_C->SkeletonOperator();

	// 面对具体编程
	ConcreteImplementA *pC_A = new ConcreteImplementA();
	pC_A->SkeletonOperator();   // 没有覆盖父类的方法，仍然调用的是父类的PrimitiveOperator3 Default Implement
	pC_A->PrimitiveOperator3(); // 覆盖了父类的方法：ConcreteImplement A Primitive Operator3
	ConcreteImplementC *pC_C = new ConcreteImplementC();
	pC_C->SkeletonOperator();   // 没有覆盖父类的方法，仍然调用的是父类的PrimitiveOperator3 Default Implement
	pC_C->PrimitiveOperator3(); // 覆盖了父类的方法：ConcreteImplement C Primitive Operator3

	SAFE_RELASE_POINTER(pCI_A);
	SAFE_RELASE_POINTER(pCI_B);
	SAFE_RELASE_POINTER(pCI_C);
	SAFE_RELASE_POINTER(pC_A);
	SAFE_RELASE_POINTER(pC_C);
}

// 简历模板
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
	void WriteCETScore() // 必须实现，否则编译不过，不能实例化抽象类，此处为空实现
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