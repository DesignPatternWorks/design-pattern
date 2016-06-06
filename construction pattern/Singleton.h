#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include "common.h"

// ����ģʽ
/*
����ͼ�Ǳ�֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㣬��ʵ�������г���ģ�鹲��

�кܶ�ط���Ҫ�����Ĺ���ģ�飬��ϵͳ����־�����GUIӦ�ñ����ǵ���꣬MODEM��������Ҫһ����ֻ��Ҫһ���绰�ߣ�
����ϵͳֻ����һ�����ڹ�������һ̨PC��һ�����̡�

����ģʽ�������ʵ�ַ�������C++�У���������ֱ����һ��ȫ�ֱ���������һ�㣬�������Ĵ����Եĺܲ����š� 
ʹ��ȫ�ֶ����ܹ���֤����ط���ʵ�������ǲ��ܱ�ֻ֤����һ�����󡪡�Ҳ����˵����һ��ȫ��ʵ���⣬��Ȼ�ܴ�����ͬ��ı���ʵ����
*/

void SingletonTest();

class Singleton
{
private:
	int m_TestValue; //  Test Value 
	static Singleton* m_pSingleton; //������̬��˽�е�Ψһʵ������
private:                            //���캯��˽�У���ֹ�����๹�����,�ڴ��ͷŷ�����ʱ������Ҫ�˴�
	Singleton() 
	{ 
		m_TestValue = 10;
	}
	// �ڴ��ͷŷ�����
	Singleton(const Singleton&) {};
	Singleton& operator = (const Singleton&) {};
	// �ڴ��ͷŷ�����
public:
	static Singleton* GetInstance() // �ṩһ������Ψһʵ�������ȫ�ַ��ʾ�̬����
	{
	  // �̰߳�ȫ�٣� �������� 
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
		// �̰߳�ȫ�٣� ��������

		// �̰߳�ȫ�ڣ� ��̬������ʼ������ 
		   return m_pSingleton;
		// �̰߳�ȫ�ڣ� ��̬������ʼ������ 
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
	// �ڴ��ͷŷ�����  
	 class CGarbo  //����Ψһ����������������������ɾ��CSingleton��ʵ�� ,
		            //Ϊ�˷���Singleton���private��������Ϊ��Ԫ����Singleton::m_pSingleton��ΪSingleton::GetInstance();
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
	static CGarbo m_Garbo; // ������̬����������������static��Garbo����*m_pSingletonʵ����һ���֣�ֻ�е����������ʱ��Garbo����������
	                      // ��������Ҫ��Garboȥ����ǰ���Ǹ�ʵ����
	// �ڴ��ͷŷ����� 

	// �ڴ��ͷŷ�����
/*	 static Singleton* GetInstance()
	 {
		 static Singleton singleton; //�ֲ���̬���� ����
		 return &singleton;
	 }
*/
	// �ڴ��ͷŷ����� 

public:
	// �̰߳�ȫ�٣� �������� 
//	static CCriticalSection m_CS;
	// �̰߳�ȫ�٣� ��������  
};
    // �̰߳�ȫ�٣� �������� 
// Singleton *Singleton::m_pSingleton = NULL; // ���徲̬��������ʼ��ʵ������ָ��ΪNULL
   // �̰߳�ȫ�٣� �������� 
Singleton::CGarbo Singleton::m_Garbo;  //���徲̬��������δ��ʼ��
   // �̰߳�ȫ�ڣ� ��̬������ʼ������ 
Singleton *Singleton::m_pSingleton = new Singleton();
   // �̰߳�ȫ�ڣ� ��̬������ʼ������ 

class TaskManager
{
private:  // ˽�й��캯��
	TaskManager(){}
private:  // ˽�е�Ψһʵ��
	static TaskManager* m_ptaskmgr;
public:  // ���е�Ψһʵ�����ʵ�
	static TaskManager* getInstance()
	{
		static TaskManager  taskmgr;  // �ֲ���̬����
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
/* ������
1���û�����Ψһʵ���ķ���ֻ��GetInstance()��Ա�����������ͨ������������κδ���ʵ���ĳ��Զ���ʧ�ܣ���Ϊ��Ĺ��캯����˽�еġ�
GetInstance()ʹ�������ʼ����Ҳ����˵���ķ���ֵ�ǵ���������״α�����ʱ�������ġ�
����һ�ַ�����ơ�������GetInstance()֮��ĵ��ö�������ͬʵ����ָ�롢
CSingleton* p1 = CSingleton :: GetInstance();
CSingleton* p2 = p1->GetInstance();
CSingleton & ref = * CSingleton :: GetInstance();

2����GetInstance�Լ��޸ģ�������ģ�����������ڿɱ��ʵ���������һ��������������ʵ����
   ��GetInstance���������Σ�������ξ���ʵ�����������͵�ʵ��

3����Ψһʵ������ָ����ڴ��ͷţ�
��Ҫ�ԣ�
�������У���һЩ�ļ����ˣ��ļ���������ݿ����ӵȵȣ���Щ���ų���Ĺرն����������رյ���Դ��
����Ҫ�ڳ���ر�ǰ�������ֶ��ͷš�������һ������������ҪGC���������ڲ����������ͷ���Դ��

�� �����ڳ������ʱ����GetInstance()�����Է��ص�ָ�����delete����
�� ��Ӿ�̬��Ա��������Ϊ�����ڽ�����ʱ��ϵͳ���Զ��������е�ȫ�ֱ�������������������������������������delete����
  ��ʵ�ϣ�ϵͳҲ���������е���ľ�̬��Ա������������Щ��̬��ԱҲ��ȫ�ֱ���һ��
�ص㣺
�ڵ������ڲ�����ר�еġ�Ƕ���ࡱ��
�ڵ������ڶ��塰˽�С���ר�������ͷŵġ���̬��Ա����
���ó����ڽ���ʱ����ȫ�ֱ��������ԣ�ѡ�����յ��ͷ�ʱ����
ʹ�õ����Ĵ��벻��Ҫ�κβ��������ع��Ķ�����ͷš�
�� ʹ�þֲ���̬����
  ��ʹ�ô��ַ���Ҳ��������⣬�����·���ʹ�õ���ʱ�������ˣ�
  ��ֹ��������Ϊ������һ��Ĭ�ϵĹ��캯������֧����Ŀ���
  �����������ʾ�������࿽���Ĺ��캯���������� = ��������ֻ������ʵ�֡�
4�������̰߳�ȫ
�� ����
   �˴�����������m_Instance == NULL���жϣ��ǽ����Java�ĵ���ģʽʵ��ʱ��ʹ�õ���ν�ġ�˫���������ơ�
   ��Ϊ����һ�μ����ͽ�������Ҫ������Ӧ�Ĵ��۵ģ������������жϣ����ܽ���
   �Ϳ��Ա����μ��������������ͬʱҲ��֤���̰߳�ȫ
��  ��̬������ʼ��
   ��Ϊ��̬��ʼ���ڳ���ʼʱ��Ҳ���ǽ���������֮ǰ�������߳��Ե��̷߳�ʽ����˳�ʼ�������Ծ�̬��ʼ��ʵ����֤���̰߳�ȫ�ԡ�
   ������Ҫ��Ƚϸ�ʱ���Ϳ���ʹ�����ַ�ʽ���Ӷ�����Ƶ���ļ����ͽ�����ɵ���Դ�˷ѡ�
*/
#endif