#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#include "common.h"
//适配器模式
/*
必要性：
将一个类的接口转换成客户希望的另外一个接口。
适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
好比日本现在就只提供110V的电压，而我的电脑就需要220V的电压，那怎么办啦？
适配器就是干这活的，在不兼容的东西之间搭建一座桥梁，让二者能很好的兼容在一起工作

优点：
降低了去实现一个功能点的难度，可以对现有的类进行包装，就可以进行使用了；
提高了项目质量，现有的类一般都是经过测试的，使用了适配器模式之后，不需要对旧的类进行全面的覆盖测试；
总的来说，提高了效率，降低了成本

场合：
使用一个已经存在的类，如果它的接口和你实际要求的不一致时，可以考虑使用适配器模式；
要在调用者和功能提供者双方都不太容易修改的时候再使用适配器模式，而不是一有不同时就使用它。
*/

/*
** FileName      : Adapter.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Adapter Pattern Implementation of C++
*/

// Class Adapter
class Target
{
public:
	virtual void Request()
	{
		cout << "Target Request" << endl;
	}
};

class Adaptee
{
public:
	void SpecialRequest()
	{
		cout << "Adaptee Special Request" << endl;
	}
};

class Adapter: public Target, public Adaptee
{
public:
	void Request()          // Override Target's Request()
	{
		SpecialRequest();
		cout << "Adapter Request" << endl;
	}
};

// Object Adapter
class Target_Obj
{
public:
	Target_Obj() {};
	virtual ~Target_Obj() {};
public:
	virtual void Request()
	{
		cout << "Target_Obj Request" << endl;
	}
};

class Adaptee_Obj
{
public:
	void SpecialRequest()
	{
		cout << "Adaptee_Obj Special Request" << endl;
	}
};

class Adapter_Obj: public Target_Obj
{
private:
	Adaptee_Obj *m_pAdaptee;
public:
	Adapter_Obj() 
	{
		m_pAdaptee = new Adaptee_Obj();
	}
	virtual ~Adapter_Obj()
	{
		if (NULL != m_pAdaptee)
		{
			delete m_pAdaptee;
			m_pAdaptee = NULL;
		}
	}
public:
	void Request()
	{
		if(NULL == m_pAdaptee)
		{
			cout << "new Adaptee Failed!" << endl;
			return;
		}
		m_pAdaptee->SpecialRequest();
		cout << "Adapter_Obj Request" << endl;
	}
};

void AdapterTest_General()
{
	// Class Adapter Test
	Target *pT = new Adapter();
	pT->Request();

	delete pT; pT = NULL;

	// Object Adapter Test
	Target_Obj *pTO = new Adapter_Obj();
	pTO->Request();

	delete pTO; pTO = NULL;	

}
//Example: STL 的 Queue & Stack (Sequence)实现：
// Target: Sequence 
// Adaptee: Deque
// Adapter: Queue & Stack

//双端队列
class Deque
{
public:
	void push_back(int x) { cout<<"Deque push_back"<<endl; }
	void push_front(int x) { cout<<"Deque push_front"<<endl; }
	void pop_back() { cout<<"Deque pop_back"<<endl; }
	void pop_front() { cout<<"Deque pop_front"<<endl; }
};

//顺序容器
class Sequence
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

//栈
class Stack: public Sequence
{
public:
	void push(int x) 
	{ 
		deque.push_back(x); 
		cout << "Stack push" << endl;
	}
	void pop() 
	{
		deque.pop_back(); 
		cout << "Stack pop" << endl;
	}
private:
	Deque deque; //双端队列
};

//队列
class Queue: public Sequence
{
public:
	void push(int x)
	{ 
		deque.push_back(x);
		cout << "Queue push" << endl;
	}
	void pop() 
	{
		deque.pop_front(); 
		cout << "Queue pop" << endl;
	}
private:
	Deque deque; //双端队列
};

// Adaptee socket
class USASocket
{
	// USA socket;
public:
	int provideUSAVolt(void)
	{
		return 110;
	}
};

// Target socket
class CHNSocket
{
	// China socket;
public:
	virtual int provideChinaVolt(void) = 0;
};

//  socket Adapter
class SocketAdapter : public CHNSocket
{
private:
	USASocket* _usaSocket;
public:
	SocketAdapter(USASocket *socket):_usaSocket(socket) {};
public:
	int provideChinaVolt(void)
	{
		if (NULL != _usaSocket)
		{
			return _usaSocket->provideUSAVolt() * 2; // convert usa volt ---> chn volt
		}
		return 0;
	}
};

void AdapterTest_Socket()
{
	// Socket Adapter Test:
	USASocket *s1 = new USASocket();
	SocketAdapter *s2 = new SocketAdapter(s1);

	cout << "before convert volt is: " << s1->provideUSAVolt()   << endl;
	cout << "after convert volt is: "  << s2->provideChinaVolt() << endl;
	delete s1; delete s2;
}

void AdapterTest_STL()
{
	// STL Sequence Obj Test
	Sequence *s1 = new Stack();
	Sequence *s2 = new Queue();
	s1->push(1); s1->pop();
	s2->push(1); s2->pop();
	delete s1; delete s2;
}

void AdapterTest()
{
	cout << "*********** AdapterTest_General: *************" << endl;
	AdapterTest_General();
	cout << "*********** AdapterTest_STL: *************" << endl;
	AdapterTest_STL();
	cout << "*********** AdapterTest_Socket: *************" << endl;
	AdapterTest_Socket();
}



/*  分析：
类适配器有以下特点：
由于Adapter直接继承自Adaptee类，所以，在Adapter类中可以对Adaptee类的方法进行重定义
如果在Adaptee中添加了一个抽象方法，那么Adapter也要进行相应的改动，这样就带来高耦合
如果Adaptee还有其它子类，而在Adapter中想调用Adaptee其它子类的方法时，使用类适配器是无法做到的

对象适配器有以下特点：
有的时候，你会发现，不是很容易去构造一个Adaptee类型的对象
当Adaptee中添加新的抽象方法时，Adapter类不需要做任何调整，也能正确的进行动作
可以使用多态的方式在Adapter类中调用Adaptee类子类的方法
由于对象适配器的耦合度比较低，所以在很多的书中都建议使用对象适配器。在我们实际项目中，也是如此，能使用对象组合的方式，就不使用多继承的方式
*/
#endif