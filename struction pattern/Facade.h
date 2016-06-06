#ifndef _FACADE_H_
#define _FACADE_H_

#include "common.h"

// 外观模式
/*
1、概念：
将子系统中的一组接口提供一个一致的界面，外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
子系统中的一组接口，就好比上面举得例子中的语句扫描分析，语法解析，生成中间代码，生成机器代码；
外观模式定义的一个高层接口，就好比Visual Studio的Build按钮，通过这样的一个Build按钮，让编译器更加容易使用

2、使用场合：
1） 当你要为一个复杂子系统提供一个简单接口时。子系统往往因为不断演化而变的越来越复杂。
    大多数模式使用时都会产生更多更小的类。这使得子系统更具有可重用性，也更容易对子系统进行定制，但这也给那些不需要定制子系统的用户带来一些使用上的困难。
	外观模式可以提供一个简单的缺省视图，这一视图对大多数用户来说已经足够，而那些需要更多的可定制性的用户可以越过Facade层；
2） 当客户程序与抽象类的实现部分之间存在很大的依赖性。引入Facade将这个子系统与客户以及其他的子系统分离，可以提高子系统的独立性和可移植性；
3） 当需要构建一个层次结构的子系统时，使用外观模式定义子系统中每层的入口点。
    如果子系统之间是相互依赖的，我们就可以让它们仅通过Facade进行通讯，从而简化了它们之间的依赖关系。

3、组成：
Facade:
   知道哪些子系统类负责处理请求，并且将客户的请求代理给适当的子系统对象；
SubSystem:
   实现子系统具体的功能；处理由Facade对象指派的任务；但是，SubSystem没有Facade的任何相关信息，也就是说，没有指向Facade的指针。
Client：
   通过发送请求给Facade的方式与子系统进行通信，而不直接与子系统打交道，Facade将这些消息转发给适当的子系统对象。
   尽管是子系统中的有关对象在做实际工作，但Facade模式本身也必须将它的接口转换成子系统的接口
4、优点：
1）它对客户屏蔽了子系统组件，因而减少了客户处理的对象的数目，并使得子系统使用起来更加方便；
2）它实现了子系统与客户之间的松耦合关系，而子系统内部的功能组件往往是紧耦合的；
   松耦合系统使得子系统的组件变化不会影响到它的客户。
   外观模式有助于建立层次结构系统，也有助于对对象之间的依赖关系分层。
   外观模式可以消除复杂的循环依赖关系。这一点在客户程序与子系统是分别实现的时候尤为重要
*/

/*
** FileName      : Facade.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Facade Pattern Implementation of C++
*/

class SubsystemA
{
public:
	void operateA(void)
	{
		cout << "Subsytem A operate" << endl;
	}
};

class SubsystemB
{
public:
	void operateB(void)
	{
		cout << "Subsytem B operate" << endl;
	}
};

class Facade
{
public:
	void facadeOperate(void)
	{
		SubsystemA sa;
		SubsystemB sb;
		sa.operateA();
		sb.operateB();
	}
};

void FacadeTest();

class Scanner
{
public:
	void Scan()
	{
		cout << "I am Scan SubSystem" << endl;
	}
};

class Parser
{
public:
	void Parse()
	{
		cout << "I am Parser SubSystem" << endl;
	}
};

class GenMidCode
{
public:
	void GenCode()
	{
		cout << "I am Generate Middle Code SubSytem" << endl;
	}
};

class GenMachineCode
{
public:
	void GenCode()
	{
		cout << "I am Generate Machine Code SubSystem" << endl;
	}
};

// 高层接口
class CompileFacade
{
public:
	void Compile()
	{
		Scanner scanner;
		Parser  pareser;
		GenMidCode genmidcode;
		GenMachineCode genmachinecode;

		scanner.Scan();
		pareser.Parse();
		genmidcode.GenCode();
		genmachinecode.GenCode();
	}
};

void FacadeTest()
{
	Facade facade;
	facade.facadeOperate();

	CompileFacade compilefacade;
	compilefacade.Compile();
}
/* 分析：
1） 在设计初期，应该有意识的将不同层分离，比如常用的三层架构，就是考虑在数据访问层，与业务逻辑层表示层之间，建立Facade，
    使复杂的子系统提供一个简单的接口，降低耦合性；
2） 在开发阶段，子系统往往因为不断的重构而变的越来越复杂，增加外观Facade可以提供一个简单的接口，减少它们之间的依赖；
3） 在维护阶段，可能这个系统已经非常难以维护和扩展了，此时你可以为新系统开发一个外观类，来提供设计粗糙或高度复杂的遗留代码的比较清晰简单的接口，
    让新系统与Facade对象交互，Facade与遗留代码交互所有复杂的工作
4） 对于子系统的访问，我们提供一个Facade层，而这个Facade入口，只需要一个；也就是说在使用Facade时，我们可以使用单例模式来实现Facade模式
*/
#endif