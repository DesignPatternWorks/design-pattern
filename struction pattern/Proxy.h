#ifndef  _PROXY_H_
#define  _PROXY_H_
#include "common.h"
// ����ģʽ
/*
1�����
Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ���
��Ϊ���ࣺԶ�̴�������������������������
1��Զ�̴���Ϊһ�������ڲ�ͬ�ĵ�ַ�ռ��ṩ�ֲ�����
2�������������󴴽������ܴ�Ķ���
3�������������ԭʼ����ķ��ʣ������������ڶ���Ӧ���в�ͬ�ķ���Ȩ�޵�ʱ��
4����������ȡ���˼򵥵�ָ�룬���ڷ��ʶ���ʱִ��һЩ���Ӳ��������ĵ�����;������
   ��ָ��ʵ�ʶ�������ü������������ö���û������ʱ�������Զ��ͷ���
2����Adapter & Decorator ����
1��������AdapterΪ��������Ķ����ṩ��һ����ͬ�Ľӿڡ��෴�������ṩ��������ʵ����ͬ�Ľӿڡ�
   Ȼ�������ڷ��ʱ����Ĵ�����ܻ�ܾ�ִ��ʵ���ִ�еĲ�������ˣ����Ľӿ�ʵ���Ͽ���ֻ��ʵ��ӿڵ�һ���Ӽ���
2������Decorator��ʵ�ֲ�����������ƣ���Decorator��Ŀ�Ĳ�һ����
   DecoratorΪ�������һ���������ܣ�����������ƶԶ���ķ��ʡ�
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

// C++ STL����ָ�루auto_ptr)��ʵ��Smart_Ptr;
/*
 Smart_Ptr �����һ�������ͻ�ֻ�����Smart_Ptr�Ķ��󣬶�����Ҫ�뱻�����ָ��m_ptr�򽻵�
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
	T* operator ->() const // ���Ա����Ϊconst ����ֹ�������Ա
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
������
auto_ptr�ĳ��֣���Ҫ��Ϊ�˽�������쳣�׳�ʱ������Դй©�������⡣
�������������Դ�ھֲ�������ʱ���䣬�ھֲ���������ʱ�ͷš�
������ʹ�ں���ִ�й���ʱ�����쳣�˳���Ҳ����Ϊ�쳣�ܱ�֤�ֲ����������Ӷ���֤��Դ���ͷš�

1) ��Ϊauto_ptr������ʱ��϶���ɾ������ӵ�е��Ǹ������������Ǿ�Ҫע���ˣ�һ���ܲ�һ���ӣ�����auto_ptr����ͬʱӵ��ͬһ��������������
int* p = new int(0);
auto_ptr<int> ap1(p);
auto_ptr<int> ap2(p);
��Ϊap1��ap2����Ϊָ��p�ǹ����ܵģ�������ʱ����ͼɾ��p,������ɾ��ͬһ���������Ϊ��C++��׼����δ����ġ��������Ǳ����ֹ����ʹ��auto_ptr.
2) �������������÷���
int* pa = new int[10];
auto_ptr<int> ap(pa);
��Ϊauto_ptr������������ɾ��ָ���õ���delete,������delete [],�������ǲ�Ӧ����auto_ptr������һ������ָ�롣
3) ���캯����explicit�ؼ�����Ч��ֹ��һ�����㡱ָ����ʽת����auto_ptr���͡�
4) ��ΪC++��֤ɾ��һ����ָ���ǰ�ȫ�ģ�����������û�б�Ҫ����������д�ɣ�
5��auto_ptrֻ��һ�ּ򵥵�����ָ�룬��������������Ҫʹ����������ָ�룬����share_ptr��
6��auto_ptr������Ϊ��������STL�����е�Ԫ�ؾ���Ҫ֧�ֿ�������ֵ�Ȳ��������������auto_ptr�ᴫ������Ȩ����ôsource��sinkԪ��֮��Ͳ��ȼ���
*/
void Proxy_Test_SmartPtr()
{
// UD-SmartPtr Test:
	int *p =  new int(10);
//	Smart_Ptr<int> sp_int_1(p); //  ����int(10)����ָ��Ĵ���sp_int
	Smart_Ptr<int> sp_int_2(p);  // sp_int_1 ʧȥp����Ȩ
    Smart_Ptr<int> sp_int_3 = sp_int_2; //  sp_int_1,2 ��ʧȥp����Ȩ
	Smart_Ptr<int> sp_int_4(sp_int_3); //  sp_int_1,2,3 ��ʧȥp����Ȩ
//	cout << "User Defined Smart_Ptr: sp_int1 value is " << *sp_int_1 << endl;
//	cout << "User Defined Smart_Ptr: sp_int2 value is " << *sp_int_2 << endl;
//	cout << "User Defined Smart_Ptr: sp_int3 value is " << *sp_int_3 << endl;
	cout << "User Defined Smart_Ptr: sp_int4 value is " << *sp_int_4 << endl;

// STL-AutoPtr Test:
	string *p2 = new string("Hello");   
	auto_ptr<string> ap_string_1(p2);;  // STL ��׼�� auto_ptr
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