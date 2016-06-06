#ifndef _PROTOTYPE_H
#define _PROTOTYPE_H

#include "common.h"
//原型模式
/*
1、可以考虑的适用场景：
1） 当我们的对象类型不是开始就能确定的，而这个类型是在运行期确定的话，那么我们通过这个类型的对象克隆出一个新的对象比较容易一些
2） 有的时候，我们需要一个对象在某个状态下的副本，此时，我们使用原型模式是最好的选择；
    例如：一个对象，经过一段处理之后，其内部的状态发生了变化；这个时候，我们需要一个这个状态的副本，如果直接new一个新的对象的话，但是它的状态是不对的
   此时，可以使用原型模式，将原来的对象拷贝一个出来，这个对象就和之前的对象是完全一致的了；
3） 当我们处理一些比较简单的对象时，并且对象之间的区别很小，可能就几个属性不同而已
    那么就可以使用原型模式来完成，省去了创建对象时的麻烦了；
4） 有的时候，创建对象时，构造函数的参数很多，而自己又不完全的知道每个参数的意义，
    就可以使用原型模式来创建一个新的对象，不必去理会创建的过程
5） 重复地创建相似对象时可以考虑使用原型模式
2、与其他创建型模式区别：
工厂方法模式、抽象工厂模式、建造者模式和原型模式都是创建型模式。
工厂方法模式适用于生产较复杂，一个工厂生产单一的一种产品的时候；
抽象工厂模式适用于一个工厂生产多个相互依赖的产品；
建造者模式着重于复杂对象的一步一步创建，组装产品的过程，并在创建的过程中，可以控制每一个简单对象的创建；
原型模式则更强调的是从自身复制自己，创建要给和自己一模一样的对象
3、缺点：
原型模式的最大缺点是继承原型的子类都要实现Clone操作，这个是很困难的。
例如，当所考虑的类已经存在时就难以新增Clone操作。
当内部包括一些不支持拷贝或者有循环引用的对象时，实现克隆可能也会很困难
*/
void PrototypeTest();

 class AbstractPrototype
 {
 public:
	 AbstractPrototype() {};
	 virtual ~AbstractPrototype() {};
	 virtual AbstractPrototype* Clone() = 0; // 克隆接口
 };
 
 class Prototype1: public AbstractPrototype
 {
 private:
	 int m_ValueTest;
 public:
	 Prototype1(int value): m_ValueTest(value) {};
	 Prototype1(const Prototype1& rhs) // 拷贝构造函数
	 {
		 m_ValueTest = rhs.m_ValueTest;
	 }
	 Prototype1* Clone() // 返回自己类类型
	 {
		 return new Prototype1(*this); // 通过调用拷贝构造函数来Clone对象
	 }
	 void ShowValue()
	 {
		 cout << m_ValueTest << endl;
	 }
 };

 class Prototype2: public AbstractPrototype
 {
 private:
	 int m_ValueTest;     // 浅拷贝，一般的拷贝
	 char *m_pName;      // 涉及到深拷贝
 public:
	 Prototype2(int value, const char* pname)
	 {
		 m_ValueTest = value;
		 if (NULL == pname)
		 {
			 m_pName = new char[1];
			 m_pName[0] = '\0';
		 }
		 else
		 {
			 m_pName = new char[strlen(pname) + 1]; 
			 strcpy(m_pName, pname);
		 }
	 };
	 virtual ~Prototype2()
	 {
		 delete m_pName; // 释放内存
	 }
	 Prototype2(const Prototype2& rhs) // 拷贝构造函数
	 {
		 m_ValueTest = rhs.m_ValueTest;                   // 浅拷贝：只会拷贝对象中的基本的数据类型
		 m_pName = new  char[strlen(rhs.m_pName) + 1];    //深拷贝：需要手动申请内存，对于数组、容器对象、引用（指针）对象
         strcpy(m_pName, rhs.m_pName);
	 }
	 Prototype2* Clone() // 返回自己类类型
	 {
		 Prototype2 *pP2 = new Prototype2(*this);
		 pP2->m_ValueTest++; //改变了克隆的对象内部成员
		 return pP2; // 通过调用拷贝构造函数来Clone对象
	 }
	 void ShowValue()
	 {
		 cout << m_ValueTest << endl;
		 cout << m_pName << endl;
	 }
 };


 // 抽象原型
 class AbstractReport
 {
 public:
	 AbstractReport(){};
	 virtual ~AbstractReport() {};
 public:
	 virtual AbstractReport* Clone() = 0; // 抽象克隆方法
	 virtual void display(void) {}; //用来显示
	 virtual void setReportTitle(string title) {}; //用来修改title
 };

// 周报具体原型
class WeeklyReport : public AbstractReport
{
private:
	string _reportTitle;
	int _weekNo;
	string _name;
	string _description;
	char* _accessory;
public:
	WeeklyReport(string title, int no, string name, string description, \
		const char* accessory): _reportTitle(title), _weekNo(no), _name(name), _description(description)
	{
		if (NULL == accessory)
		{
			_accessory  = new char[0];
			_accessory[0] = '\0';
		}
		else
		{
			_accessory = new char[strlen(accessory) + 1];
			strcpy(_accessory, accessory);
		}
	}
	virtual ~WeeklyReport()
	{
		if (NULL != _accessory)
		{
			delete _accessory;
			_accessory = NULL;
		}
	}
public:
	WeeklyReport(WeeklyReport &rhs) //拷贝构造函数，浅拷贝 + 深拷贝
	{
		_reportTitle = rhs._reportTitle; 
		_weekNo = rhs._weekNo;
		_name =  rhs._name;
		_description = rhs._description;
		_accessory = new char[strlen(rhs._accessory) + 1]; // 深拷贝
		memmove(_accessory, rhs._accessory, (strlen(rhs._accessory) + 1));
	}
	
	WeeklyReport* Clone() // 克隆接口
	{
		WeeklyReport *report = new WeeklyReport(*this);
		return report;
	}

	void setReportTitle(string reportTitle)
	{
		_reportTitle = reportTitle;
	}
	void setWeekNo(int weekNo)
	{
		_weekNo = weekNo;
	}
	void setDescription(string reportDescription)
	{
		_description = reportDescription;
	}
	void display(void)
	{
		cout << "weekly report title: " << _reportTitle << endl;
		cout << "weekly no: " << _weekNo << endl;
		cout << "reporter: " << _name << endl;
		cout << "description: " << _description  <<endl;
		cout << "accessory: " << _accessory  <<endl;
	}
};

// 月报具体原型
class MonthlyReport : public AbstractReport
{
private:
	string _reportTitle;
	int _monthNo;
	string _name;
	string _description;
	char* _accessory;
public:
	MonthlyReport(string title, int no, string name, string description, \
		const char* accessory): _reportTitle(title), _monthNo(no), _name(name), _description(description)
	{
		if (NULL == accessory)
		{
			_accessory  = new char[0];
			_accessory[0] = '\0';
		}
		else
		{
			_accessory = new char[strlen(accessory) + 1];
			strcpy(_accessory, accessory);
		}
	}
	virtual ~MonthlyReport()
	{
		if (NULL != _accessory)
		{
			delete _accessory;
			_accessory = NULL;
		}
	}
public:
	MonthlyReport(MonthlyReport &rhs) //拷贝构造函数，浅拷贝 + 深拷贝
	{
		_reportTitle = rhs._reportTitle; 
		_monthNo = rhs._monthNo;
		_name =  rhs._name;
		_description = rhs._description;
		_accessory = new char[strlen(rhs._accessory) + 1]; // 深拷贝
		memmove(_accessory, rhs._accessory, (strlen(rhs._accessory) + 1));
	}

	MonthlyReport* Clone() // 克隆接口
	{
		MonthlyReport *report = new MonthlyReport(*this);
		return report;
	}

	void setReportTitle(string reportTitle)
	{
		_reportTitle = reportTitle;
	}
	void setWeekNo(int monthNo)
	{
		_monthNo = monthNo;
	}
	void setDescription(string reportDescription)
	{
		_description = reportDescription;
	}
	void display(void)
	{
		cout << "monthly report title: " << _reportTitle <<endl;
		cout << "monthly no: " << _monthNo <<endl;
		cout << "reporter: " << _name <<endl;
		cout << "description: " << _description <<endl;
		cout << "accessory: " << _accessory <<endl;
	}
};

// Report Manager
class ReportManager
{
private:
	map<string, AbstractReport*> reportMap;
private:
	ReportManager(){};
	ReportManager(const ReportManager &rhs) {};
	ReportManager& operator = (const ReportManager &rhs) {};
public:
	static ReportManager* getInstance(void)
	{
		static ReportManager reportMgr;
		return &reportMgr;
	}
public:
	// 增加新的report
	void addReport(string name, AbstractReport* report)
	{
		reportMap.insert(make_pair(name, report));
	}
	AbstractReport* getReport(string name) // 返回一个report副本
	{
		for (map<string, AbstractReport*>::iterator it = reportMap.begin(); \
			 it  != reportMap.end(); ++it)
		{
			if (it->first == name)
			{
				return (it->second)->Clone();
			}
		}

		return NULL;
	}
};


 void PrototypeTest()
 {
	 Prototype1 *pP1= new Prototype1(10); // 返回子类型的类指针，抽象类没有方法ShowValue
	 Prototype1 *pPcopy= pP1->Clone();
	 pP1->ShowValue();      //  10
	 pPcopy->ShowValue();   // 10

	 Prototype2 *pP2= new Prototype2(20, "Tly");
	 Prototype2 *pPcopy2= pP2->Clone();
	 pP2->ShowValue();        // 20, "Tly"
	 pPcopy2->ShowValue();    // 21  "Tly"

	 ReportManager *rm = ReportManager::getInstance();

	 WeeklyReport  *wr =new WeeklyReport ("design model", 1, "tly", "design domain object model","no accessory");
	 MonthlyReport *mr =new MonthlyReport("complete design all model", 3, "tly", "complte design all domain object model","month accessory");
	 
	 cout << "$$$$$$$$$$origin$$$$$$$$$$" << endl;
	 wr->display();
	 mr->display();

	 rm->addReport("week", wr);
	 rm->addReport("month", mr);

	 AbstractReport *wrCopy = rm->getReport("week");
	 AbstractReport *mrCopy = rm->getReport("month");

	 cout << "$$$$$$$$$$copy$$$$$$$$$$" << endl;
	 wrCopy->setReportTitle("change weekly report title");
	 wrCopy->display();
	 mrCopy->display();

	 delete wr; wr = NULL;
	 delete mr; mr = NULL;
	 delete wrCopy; wrCopy = NULL;
	 delete mrCopy; mrCopy = NULL;

	 delete pP1; pP1 = NULL;
	 delete pPcopy; pPcopy = NULL;
	 delete pP2; pP2 = NULL;
	 delete pPcopy2; pPcopy2 = NULL;
 }

 /*分析：
 1、Prototype1类和Prototype2类继承自AbstractPrototype类，并实现Clone接口，实现克隆自身的操作；
 同时，在Prototype1类和Prototype2类中需要重写默认的复制(拷贝）构造函数，供Clone函数调用，Clone就是通过在内部调用重写的复制构造函数实现的。
 在后续的编码过程中，如果某个类需要实现Clone功能，就只需要继承Prototype类，然后重写自己的默认复制构造函数就好了
 2、当调用Clone获得了一个复制的对象以后，需要改变对象的状态，
 此时就可能需要在Prototype类中添加一个Initialize操作，专门用于初始化克隆对象
 3、Clone的内部调用的是复制构造函数，而此处又涉及到深复制和浅复制的问题
 */
#endif