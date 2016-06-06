#ifndef _PROTOTYPE_H
#define _PROTOTYPE_H

#include "common.h"
//ԭ��ģʽ
/*
1�����Կ��ǵ����ó�����
1�� �����ǵĶ������Ͳ��ǿ�ʼ����ȷ���ģ��������������������ȷ���Ļ�����ô����ͨ��������͵Ķ����¡��һ���µĶ���Ƚ�����һЩ
2�� �е�ʱ��������Ҫһ��������ĳ��״̬�µĸ�������ʱ������ʹ��ԭ��ģʽ����õ�ѡ��
    ���磺һ�����󣬾���һ�δ���֮�����ڲ���״̬�����˱仯�����ʱ��������Ҫһ�����״̬�ĸ��������ֱ��newһ���µĶ���Ļ�����������״̬�ǲ��Ե�
   ��ʱ������ʹ��ԭ��ģʽ����ԭ���Ķ��󿽱�һ���������������ͺ�֮ǰ�Ķ�������ȫһ�µ��ˣ�
3�� �����Ǵ���һЩ�Ƚϼ򵥵Ķ���ʱ�����Ҷ���֮��������С�����ܾͼ������Բ�ͬ����
    ��ô�Ϳ���ʹ��ԭ��ģʽ����ɣ�ʡȥ�˴�������ʱ���鷳�ˣ�
4�� �е�ʱ�򣬴�������ʱ�����캯���Ĳ����ܶ࣬���Լ��ֲ���ȫ��֪��ÿ�����������壬
    �Ϳ���ʹ��ԭ��ģʽ������һ���µĶ��󣬲���ȥ��ᴴ���Ĺ���
5�� �ظ��ش������ƶ���ʱ���Կ���ʹ��ԭ��ģʽ
2��������������ģʽ����
��������ģʽ�����󹤳�ģʽ��������ģʽ��ԭ��ģʽ���Ǵ�����ģʽ��
��������ģʽ�����������ϸ��ӣ�һ������������һ��һ�ֲ�Ʒ��ʱ��
���󹤳�ģʽ������һ��������������໥�����Ĳ�Ʒ��
������ģʽ�����ڸ��Ӷ����һ��һ����������װ��Ʒ�Ĺ��̣����ڴ����Ĺ����У����Կ���ÿһ���򵥶���Ĵ�����
ԭ��ģʽ���ǿ�����Ǵ��������Լ�������Ҫ�����Լ�һģһ���Ķ���
3��ȱ�㣺
ԭ��ģʽ�����ȱ���Ǽ̳�ԭ�͵����඼Ҫʵ��Clone����������Ǻ����ѵġ�
���磬�������ǵ����Ѿ�����ʱ����������Clone������
���ڲ�����һЩ��֧�ֿ���������ѭ�����õĶ���ʱ��ʵ�ֿ�¡����Ҳ�������
*/
void PrototypeTest();

 class AbstractPrototype
 {
 public:
	 AbstractPrototype() {};
	 virtual ~AbstractPrototype() {};
	 virtual AbstractPrototype* Clone() = 0; // ��¡�ӿ�
 };
 
 class Prototype1: public AbstractPrototype
 {
 private:
	 int m_ValueTest;
 public:
	 Prototype1(int value): m_ValueTest(value) {};
	 Prototype1(const Prototype1& rhs) // �������캯��
	 {
		 m_ValueTest = rhs.m_ValueTest;
	 }
	 Prototype1* Clone() // �����Լ�������
	 {
		 return new Prototype1(*this); // ͨ�����ÿ������캯����Clone����
	 }
	 void ShowValue()
	 {
		 cout << m_ValueTest << endl;
	 }
 };

 class Prototype2: public AbstractPrototype
 {
 private:
	 int m_ValueTest;     // ǳ������һ��Ŀ���
	 char *m_pName;      // �漰�����
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
		 delete m_pName; // �ͷ��ڴ�
	 }
	 Prototype2(const Prototype2& rhs) // �������캯��
	 {
		 m_ValueTest = rhs.m_ValueTest;                   // ǳ������ֻ�´�������еĻ�������������
		 m_pName = new  char[strlen(rhs.m_pName) + 1];    //�������Ҫ�ֶ������ڴ棬�������顢�����������ã�ָ�룩����
         strcpy(m_pName, rhs.m_pName);
	 }
	 Prototype2* Clone() // �����Լ�������
	 {
		 Prototype2 *pP2 = new Prototype2(*this);
		 pP2->m_ValueTest++; //�ı��˿�¡�Ķ����ڲ���Ա
		 return pP2; // ͨ�����ÿ������캯����Clone����
	 }
	 void ShowValue()
	 {
		 cout << m_ValueTest << endl;
		 cout << m_pName << endl;
	 }
 };


 // ����ԭ��
 class AbstractReport
 {
 public:
	 AbstractReport(){};
	 virtual ~AbstractReport() {};
 public:
	 virtual AbstractReport* Clone() = 0; // �����¡����
	 virtual void display(void) {}; //������ʾ
	 virtual void setReportTitle(string title) {}; //�����޸�title
 };

// �ܱ�����ԭ��
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
	WeeklyReport(WeeklyReport &rhs) //�������캯����ǳ���� + ���
	{
		_reportTitle = rhs._reportTitle; 
		_weekNo = rhs._weekNo;
		_name =  rhs._name;
		_description = rhs._description;
		_accessory = new char[strlen(rhs._accessory) + 1]; // ���
		memmove(_accessory, rhs._accessory, (strlen(rhs._accessory) + 1));
	}
	
	WeeklyReport* Clone() // ��¡�ӿ�
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

// �±�����ԭ��
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
	MonthlyReport(MonthlyReport &rhs) //�������캯����ǳ���� + ���
	{
		_reportTitle = rhs._reportTitle; 
		_monthNo = rhs._monthNo;
		_name =  rhs._name;
		_description = rhs._description;
		_accessory = new char[strlen(rhs._accessory) + 1]; // ���
		memmove(_accessory, rhs._accessory, (strlen(rhs._accessory) + 1));
	}

	MonthlyReport* Clone() // ��¡�ӿ�
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
	// �����µ�report
	void addReport(string name, AbstractReport* report)
	{
		reportMap.insert(make_pair(name, report));
	}
	AbstractReport* getReport(string name) // ����һ��report����
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
	 Prototype1 *pP1= new Prototype1(10); // ���������͵���ָ�룬������û�з���ShowValue
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

 /*������
 1��Prototype1���Prototype2��̳���AbstractPrototype�࣬��ʵ��Clone�ӿڣ�ʵ�ֿ�¡����Ĳ�����
 ͬʱ����Prototype1���Prototype2������Ҫ��дĬ�ϵĸ���(���������캯������Clone�������ã�Clone����ͨ�����ڲ�������д�ĸ��ƹ��캯��ʵ�ֵġ�
 �ں����ı�������У����ĳ������Ҫʵ��Clone���ܣ���ֻ��Ҫ�̳�Prototype�࣬Ȼ����д�Լ���Ĭ�ϸ��ƹ��캯���ͺ���
 2��������Clone�����һ�����ƵĶ����Ժ���Ҫ�ı�����״̬��
 ��ʱ�Ϳ�����Ҫ��Prototype�������һ��Initialize������ר�����ڳ�ʼ����¡����
 3��Clone���ڲ����õ��Ǹ��ƹ��캯�������˴����漰����ƺ�ǳ���Ƶ�����
 */
#endif