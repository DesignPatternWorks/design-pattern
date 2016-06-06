#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include "common.h"

// 单例模式
/*
其意图是保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。

有很多地方需要这样的功能模块，如系统的日志输出，GUI应用必须是单鼠标，MODEM的联接需要一条且只需要一条电话线，
操作系统只能有一个窗口管理器，一台PC连一个键盘。

单例模式有许多种实现方法，在C++中，甚至可以直接用一个全局变量做到这一点，但这样的代码显的很不优雅。 
使用全局对象能够保证方便地访问实例，但是不能保证只声明一个对象——也就是说除了一个全局实例外，仍然能创建相同类的本地实例。
*/

void SingletonTest();

class Singleton
{
private:
	int m_TestValue; //  Test Value 
	static Singleton* m_pSingleton; //声明静态的私有的唯一实例对象
private:                            //构造函数私有，防止其他类构造对象,内存释放方法③时，不需要此处
	Singleton() 
	{ 
		m_TestValue = 10;
	}
	// 内存释放方法③
	Singleton(const Singleton&) {};
	Singleton& operator = (const Singleton&) {};
	// 内存释放方法③
public:
	static Singleton* GetInstance() // 提供一个访问唯一实例对象的全局访问静态方法
	{
	  // 线程安全①： 上锁方法 
/*		if (NULL == m_pSingleton)
		{
			m_CS.Lock();
			if (NULL == m_pSingleton)
			{
				m_pSingleton = new Singleton();
			}
			m_CS.Unlock();
		}
		return m_pSingleton;
*/
		// 线程安全①： 上锁方法

		// 线程安全②： 静态变量初始化方法 
		   return m_pSingleton;
		// 线程安全②： 静态变量初始化方法 
	}
	// Test Value 
	int GetTestValue()
	{
		return m_TestValue;
	}
	void ShowTestValue()
	{
		cout << "I am a Singleton Class:Test Value is "<<  GetTestValue() << endl;
	}

private:
	// 内存释放方法②  
	 class CGarbo  //它的唯一工作就是在其析构函数中删除CSingleton的实例 ,
		            //为了访问Singleton类的private类型声明为友元，或Singleton::m_pSingleton改为Singleton::GetInstance();
	{
	public:
		~CGarbo()
		{
			if (Singleton::GetInstance())
			{
				delete Singleton::GetInstance();
			}
		}
	};
	static CGarbo m_Garbo; // 声明静态变量，如果不定义成static，Garbo就是*m_pSingleton实例的一部分，只有当这个析构的时候，Garbo才能析构。
	                      // 而本意是要用Garbo去析构前面那个实例。
	// 内存释放方法② 

	// 内存释放方法③
/*	 static Singleton* GetInstance()
	 {
		 static Singleton singleton; //局部静态变量 引用
		 return &singleton;
	 }
*/
	// 内存释放方法③ 

public:
	// 线程安全①： 上锁方法 
//	static CCriticalSection m_CS;
	// 线程安全①： 上锁方法  
};
    // 线程安全①： 上锁方法 
// Singleton *Singleton::m_pSingleton = NULL; // 定义静态变量，初始化实例对象指针为NULL
   // 线程安全①： 上锁方法 
Singleton::CGarbo Singleton::m_Garbo;  //定义静态变量，但未初始化
   // 线程安全②： 静态变量初始化方法 
Singleton *Singleton::m_pSingleton = new Singleton();
   // 线程安全②： 静态变量初始化方法 

class TaskManager
{
private:  // 私有构造函数
	TaskManager(){}
private:  // 私有的唯一实例
	static TaskManager* m_ptaskmgr;
public:  // 公有的唯一实例访问点
	static TaskManager* getInstance()
	{
		static TaskManager  taskmgr;  // 局部静态变量
		return &taskmgr;
	}
public:
	void displayProcesses()
	{
		cout << "Task Mgr Process" << endl;
	}
	void displayServices()
	{
		cout << "Task Mgr Services" << endl;
	}
};

void SingletonTest()
{
	Singleton *pS1 = Singleton::GetInstance();
	Singleton *pS2= Singleton::GetInstance();
	if (pS1 == pS2)
	{
		cout << "the same object" << endl;
	}
	else
	{
		cout << "not the same object" << endl;
	}
	pS1->ShowTestValue();
	pS2->ShowTestValue();

	TaskManager* ptm1 = TaskManager::getInstance();
	TaskManager* ptm2 = TaskManager::getInstance();

	if (ptm1 == ptm2)
	{
		cout << "Single Task Mgr" << endl;
		ptm1->displayProcesses();
		ptm1->displayServices();
	}
	else
	{
		cout << "Not Single Task Mgr" << endl;
	}
}
/* 分析：
1、用户访问唯一实例的方法只有GetInstance()成员函数。如果不通过这个函数，任何创建实例的尝试都将失败，因为类的构造函数是私有的。
GetInstance()使用懒惰初始化，也就是说它的返回值是当这个函数首次被访问时被创建的。
这是一种防弹设计——所有GetInstance()之后的调用都返回相同实例的指针、
CSingleton* p1 = CSingleton :: GetInstance();
CSingleton* p2 = p1->GetInstance();
CSingleton & ref = * CSingleton :: GetInstance();

2、对GetInstance稍加修改，这个设计模板便可以适用于可变多实例情况，如一个类允许最多五个实例：
   在GetInstance函数添加入参，根据入参决定实例化那种类型的实例

3、对唯一实例对象指针的内存释放：
必要性：
“在类中，有一些文件锁了，文件句柄，数据库连接等等，这些随着程序的关闭而不会立即关闭的资源，
必须要在程序关闭前，进行手动释放”，从这一点来看，是需要GC类这样的内部类来进行释放资源。

① 可以在程序结束时调用GetInstance()，并对返回的指针掉用delete操作
② 添加静态成员变量，因为程序在结束的时候，系统会自动析构所有的全局变量。（调用其析构函数，在其析构函数中delete操作
  事实上，系统也会析构所有的类的静态成员变量，就像这些静态成员也是全局变量一样
特点：
在单例类内部定义专有的“嵌套类”；
在单例类内定义“私有”的专门用于释放的“静态成员”；
利用程序在结束时析构全局变量的特性，选择最终的释放时机；
使用单例的代码不需要任何操作，不必关心对象的释放。
③ 使用局部静态变量
  但使用此种方法也会出现问题，当如下方法使用单例时问题来了，
  防止编译器会为类生成一个默认的构造函数，来支持类的拷贝
  解决方法：显示的声明类拷贝的构造函数，和重载 = 操作符，只声明不实现。
4、考虑线程安全
① 上锁
   此处进行了两次m_Instance == NULL的判断，是借鉴了Java的单例模式实现时，使用的所谓的“双检锁”机制。
   因为进行一次加锁和解锁是需要付出对应的代价的，而进行两次判断，性能降低
   就可以避免多次加锁与解锁操作，同时也保证了线程安全
②  静态变量初始化
   因为静态初始化在程序开始时，也就是进入主函数之前，由主线程以单线程方式完成了初始化，所以静态初始化实例保证了线程安全性。
   在性能要求比较高时，就可以使用这种方式，从而避免频繁的加锁和解锁造成的资源浪费。
*/
#endif