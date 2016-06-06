#ifndef  _PROXY_H_
#define  _PROXY_H_
#include "common.h"
// 代理模式
/*
1、概念：
为其他对象提供一种代理以控制对这个对象的访问
分为四类：远程代理，虚代理，保护代理和智能引用
1）远程代理为一个对象在不同的地址空间提供局部代理；
2）虚代理根据需求创建开销很大的对象；
3）保护代理控制原始对象的访问；保护代理用于对象应该有不同的访问权限的时候；
4）智能引用取代了简单的指针，它在访问对象时执行一些附加操作，它的典型用途包括：
   对指向实际对象的引用计数，这样当该对象没有引用时，可以自动释放它
2、与Adapter & Decorator 区别：
1）适配器Adapter为它所适配的对象提供了一个不同的接口。相反，代理提供了与它的实体相同的接口。
   然而，用于访问保护的代理可能会拒绝执行实体会执行的操作，因此，它的接口实际上可能只是实体接口的一个子集。
2）尽管Decorator的实现部分与代理相似，但Decorator的目的不一样。
   Decorator为对象添加一个或多个功能，而代理则控制对对象的访问。
*/

/*
** FileName      : Proxy.h
** Author        : Frank Tly
** Date          : 2015/7/22
** Description   : Proxy Pattern Implementation of C++
*/
void ProxyTest();

// Base Common Interface of RealSubject & Proxy
class Subject
{
public:
	Subject() {};
	virtual ~Subject() {};
public:
	virtual void Request() = 0;
};

// RealSubject
class RealSubject : public Subject
{
public:
	RealSubject() {};
	virtual ~RealSubject() {};
public:
	void Request()
	{
		cout << "Real Subject Request !" << endl;
	}
};

// Proxy
class Proxy : public Subject
{
private:
	Subject *m_pRealSubject;
public:
	Proxy(Subject *pSubject) : m_pRealSubject(pSubject) {};
	virtual ~Proxy() {};
public:
	void Request()
	{
		if (NULL != m_pRealSubject)
		{
			cout << "Proxy Request !" << endl;
			m_pRealSubject->Request();
		}

	}
};

void ProxyTest_General()
{
	Subject *pRS = new RealSubject();
	Subject *pPS = new Proxy(pRS);
	pPS->Request();

	if (NULL != pRS)
	{
		delete pRS; pRS = NULL;
	}
	if (NULL != pPS)
	{
		delete pPS; pPS = NULL;
	}
}

// C++ STL智能指针（auto_ptr)的实现Smart_Ptr;
/*
 Smart_Ptr 类就是一个代理，客户只需操作Smart_Ptr的对象，而不需要与被代理的指针m_ptr打交道
*/
template <class T>
class Smart_Ptr
{
private:
	T* m_ptr;
public:
	// Construction 
	explicit Smart_Ptr(T* ptr = 0) : m_ptr(ptr) {};  // forbide yin shi convert
public:
	~Smart_Ptr()
	{
		reset();
	}
public:
	// Copy Construction  
	Smart_Ptr(Smart_Ptr &rhs) : m_ptr(rhs.release()) {}; // not const input para , for its m_ptr changed

	//Assignment
	Smart_Ptr& operator = (Smart_Ptr &rhs)
	{
		reset(rhs.release());
		return *this;
	}
public:
	T* operator ->() const // 类成员函数为const ，防止更改类成员
	{
		return m_ptr;
	}
	T& operator *() const
	{
		return *m_ptr;
	}
	T* get() const
	{
		return m_ptr;
	}
	// Release Ownership
	T* release()
	{
		T* tmp(m_ptr); // tmp = m_ptr;
		m_ptr = 0;
		return tmp;
	}
	// Reset Ownership: copy ptr to m_ptr,
	void reset(T* ptr = 0) 
	{
		if (m_ptr != ptr)
		{
			delete m_ptr;
			m_ptr = ptr;
		}
	}
};
/* C++ aut_ptr
设计理念：
auto_ptr的出现，主要是为了解决“被异常抛出时发生资源泄漏”的问题。
即如果我们让资源在局部对象构造时分配，在局部对象析构时释放。
这样即使在函数执行过程时发生异常退出，也会因为异常能保证局部对象被析构从而保证资源被释放。

1) 因为auto_ptr析构的时候肯定会删除他所拥有的那个对象，所有我们就要注意了，一个萝卜一个坑，两个auto_ptr不能同时拥有同一个对象。像这样：
int* p = new int(0);
auto_ptr<int> ap1(p);
auto_ptr<int> ap2(p);
因为ap1与ap2都认为指针p是归它管的，在析构时都试图删除p,　两次删除同一个对象的行为在C++标准中是未定义的。所以我们必须防止这样使用auto_ptr.
2) 考虑下面这种用法：
int* pa = new int[10];
auto_ptr<int> ap(pa);
因为auto_ptr的析构函数中删除指针用的是delete,而不是delete [],所以我们不应该用auto_ptr来管理一个数组指针。
3) 构造函数的explicit关键词有效阻止从一个“裸”指针隐式转换成auto_ptr类型。
4) 因为C++保证删除一个空指针是安全的，　所以我们没有必要把析构函数写成：
5）auto_ptr只是一种简单的智能指针，如有特殊需求，需要使用其他智能指针，比如share_ptr。
6）auto_ptr不能作为容器对象，STL容器中的元素经常要支持拷贝，赋值等操作，在这过程中auto_ptr会传递所有权，那么source与sink元素之间就不等价了
*/
void Proxy_Test_SmartPtr()
{
// UD-SmartPtr Test:
	int *p =  new int(10);
//	Smart_Ptr<int> sp_int_1(p); //  构造int(10)返回指针的代理sp_int
	Smart_Ptr<int> sp_int_2(p);  // sp_int_1 失去p控制权
    Smart_Ptr<int> sp_int_3 = sp_int_2; //  sp_int_1,2 均失去p控制权
	Smart_Ptr<int> sp_int_4(sp_int_3); //  sp_int_1,2,3 均失去p控制权
//	cout << "User Defined Smart_Ptr: sp_int1 value is " << *sp_int_1 << endl;
//	cout << "User Defined Smart_Ptr: sp_int2 value is " << *sp_int_2 << endl;
//	cout << "User Defined Smart_Ptr: sp_int3 value is " << *sp_int_3 << endl;
	cout << "User Defined Smart_Ptr: sp_int4 value is " << *sp_int_4 << endl;

// STL-AutoPtr Test:
	string *p2 = new string("Hello");   
	auto_ptr<string> ap_string_1(p2);;  // STL 标准库 auto_ptr
	cout << "STL Smart_Ptr: ap_string_1 value is " << *ap_string_1 << endl;
};


// Abstract rent class 
class AbstractRenter
{
public:
	virtual void rent(void) = 0;
};

// real renter == house owner
class RealRenter : public AbstractRenter
{
public:
	void rent(void)
	{
		cout << "i have a house to rent, please contact me if you need!" << endl;
	}
};

// proxy renter == house proxy
class ProxyRenter : public AbstractRenter
{
private:
	RealRenter _renter;
public:
	ProxyRenter(RealRenter &renter) : _renter(renter) {};
public:
	void rent(void)
	{
		validId();
		_renter.rent();
		logHouseUser();
	}
private:
	void validId(void)
	{
		cout << "please valid your identification" << endl;
	}
	void logHouseUser(void)
	{
		cout << "log the house user information" << endl;
	}
};

void Proxy_Test_Renter(void)
{
	RealRenter  realRenter;
	ProxyRenter proxyRenter(realRenter);
	AbstractRenter &pR = proxyRenter;
	pR.rent();
}

void ProxyTest()
{
	cout << "*********** ProxyTest_General: *************" << endl;
	ProxyTest_General();

	cout << "*********** Proxy_Test_SmartPtr: *************" << endl;
	Proxy_Test_SmartPtr();

	cout << "*********** Proxy_Test_Renter: *************" << endl;
	Proxy_Test_Renter();
}

#endif