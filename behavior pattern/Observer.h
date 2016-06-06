#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// �۲���ģʽ������--���ģ�
/*
1�� ���
    ���������һ��һ�Զ��������ϵ����һ�������״̬�����ı�ʱ���������������Ķ��󶼵õ�֪ͨ�����Զ����¡�
	��һ���������˱仯����ע���Ķ���ͻ�õ�֪ͨ�����ֽ���Ҳ��Ϊ����-����(publish-subscribe)��
	Ŀ����֪ͨ�ķ����ߣ�������֪ͨʱ������Ҫ֪��˭�����Ĺ۲���

2�� ��ɫ��
Subject��Ŀ�꣩
����Ŀ��֪�����Ĺ۲��ߡ��������������۲��߹۲�ͬһ��Ŀ�ꣻ
�����ṩע���ɾ���۲��߶���Ľӿڡ�
Observer���۲��ߣ�
����Ϊ��Щ��Ŀ�귢���ı�ʱ����֪ͨ�Ķ�����һ�����½ӿڡ�
ConcreteSubject������Ŀ�꣩
�������й�״̬�����ConcreteObserver����
����������״̬�����ı�ʱ�������ĸ����۲��߷���֪ͨ��
ConcreteObserver������۲��ߣ�
����ά��һ��ָ��ConcreteSubject��������ã�
�����洢�й�״̬����Щ״̬Ӧ��Ŀ���״̬����һ�£�
����ʵ��Observer�ĸ��½ӿ���ʹ����״̬��Ŀ���״̬����һ�¡�

3��ʹ�ó��ϣ�
��  ��һ������ģ�����������棬����һ��������������һ���档������߷�װ�ڶ����Ķ�������ʹ���ǿ��Ը��Զ����ĸı�͸��ã�
��  ����һ������ĸı���Ҫͬʱ�ı��������󣬶���֪�������ж��ٶ����д��ı䣻
��  ��һ���������֪ͨ�������󣬶����ֲ��ܼٶ�����������˭��Ҳ����˵���㲻ϣ����Щ�����ǽ�����ϵ�


4����ȱ�㣺
��  �۲����뱻�۲���֮����������ȵĹ�����ϵ�������ǳ�����ϵģ�����������������˵���Ƚ����׽�����չ��
��  �۲���ģʽ��һ�ֳ��õĴ������ƣ����γ�һ�������������ζԸ����۲��ߵķ������д���
    ��ͬʱ����Ҳ���ǹ۲���ģʽһ��ȱ�㣬��������ʽ���������۲��߱Ƚ϶��ʱ�����������ǱȽ����˵��ǵġ�
	���ң�����ʽ�ṹ�У��Ƚ����׳���ѭ�����õĴ������ϵͳ����
*/
void ObserverTest();

// Abstract Observer
class Observer
{
public:
	virtual void Update() = 0;
	virtual void ShowState() = 0;
};

// Abstract Subject
class Subject
{
public:
	virtual void Attach(Observer *pObserver) = 0;
	virtual void Detach(Observer *pObserver) = 0;
	virtual void Notify() = 0;
	virtual void SetState(int state) = 0;
	virtual int GetState() = 0;
};

// ConcreteSubject
class ConcreteSubject : public Subject
{
private:
	list<Observer*> m_listObserver;
	int m_State;
public:
	ConcreteSubject(): m_State(0){};
public:
	virtual void Attach(Observer *pObserver)
	{
		m_listObserver.push_back(pObserver);
	}
	virtual void Detach(Observer *pObserver)
	{
		m_listObserver.remove(pObserver);
	}
	virtual void Notify()
	{
		for (list<Observer*>::iterator it = m_listObserver.begin();
			 it != m_listObserver.end();
			 ++it)
		{
			(*it)->Update();
		}
	}
	virtual void SetState(int state)
	{
		m_State = state;
	}
	virtual int GetState()
	{
		return m_State;
	}
};

// ConcreteObserver
class ConcreteObserver : public Observer
{
private: 
	Subject *m_pSubject;
	int m_State;
public:
	ConcreteObserver(Subject *pSubject): m_pSubject(pSubject),m_State(0) {};//  �����Observer������Subject�����ø�Subject�ķ���Update����
public:
	virtual void Update()
	{
		m_State = m_pSubject->GetState();
	}
	virtual void ShowState()
	{
		cout << "Concrete Observer State: " << m_State << endl;;
	}
};

void ObserverTest_General()
{
	Subject *pCS = new ConcreteSubject();

	Observer *pCO1 = new ConcreteObserver(pCS);
	Observer *pCO2 = new ConcreteObserver(pCS);

	pCS->Attach(pCO1);
	pCS->Attach(pCO2);

	pCS->SetState(100);
	pCS->Notify();

	pCO1->ShowState();  // 100
	pCO2->ShowState();  // 100

	pCS->Detach(pCO2);

	pCS->SetState(200);
	pCS->Notify();

	pCO1->ShowState();  // 200
	pCO2->ShowState();  // 100

	SAFE_RELASE_POINTER(pCS);
	SAFE_RELASE_POINTER(pCO1);
	SAFE_RELASE_POINTER(pCO2);
}



// Blog and BlogObserver 
// һ��Blog�ж���۲��ߣ�һ���۲��߿��Թ۲충�Ķ��Blog��״̬

// Abstract Blog Observer
class Blog;
class BlogObserver
{
public:
	virtual void Update(Blog *pBlog)     = 0;  // Updateָ��Blog�����Message
	virtual string GetName()             = 0;
	virtual void ShowMsg()               = 0;
};

// Abstract Blog
class Blog
{
public:
	virtual void AttachBlogObserver(BlogObserver *pBlogObserver) = 0;
	virtual void DetachBlogObserver(BlogObserver *pBlogObserver) = 0;
	virtual void Notify()                                        = 0;
	virtual string GetName()                                     = 0;
	virtual void PublishMsg(string msg)                          = 0;
	virtual string GetMsg()                                      = 0;
};

// Concrete Blog: Csdn Blog
class CsdnBlog : public Blog
{
private:
	list<BlogObserver*> m_listBlogObserver;
	string m_BlogName;
	string m_msg;
public:
	CsdnBlog(string name): m_BlogName(name), m_msg("") {};
public:
	string GetName()
	{
		return m_BlogName;
	}
public:
	virtual void AttachBlogObserver(BlogObserver *pBlogObserver)
	{
		m_listBlogObserver.push_back(pBlogObserver);
		cout << "[Blog Observer]" << pBlogObserver->GetName() << " Attached To " << "[Blog]" << m_BlogName << endl;
	}
	virtual void DetachBlogObserver(BlogObserver *pBlogObserver)
	{
		m_listBlogObserver.remove(pBlogObserver);
		cout << "[Blog Observer]" << pBlogObserver->GetName() << " Detached From " << "[Blog]" << m_BlogName << endl;
	}
	virtual void Notify()
	{
		for (list<BlogObserver*>::iterator it  = m_listBlogObserver.begin();
			 it != m_listBlogObserver.end();
			 ++it)
		{
			(*it)->Update(this); // Update��Blog�����Message�����ж��ĸ�Blog�����Observer
		}
	}
	virtual void PublishMsg(string msg)
	{
		cout << m_BlogName <<  " Send Message: " << msg << endl;
		m_msg = msg;
	}
	virtual string GetMsg()
	{
		return m_msg;
	}
};

// Concrete Blog Observer
class ConcreteBlogObserver : public BlogObserver
{
private:
	map<Blog*, string> m_mapBlog_Msg;  // ���涩�ĵ�Blog����Ӧ����Ϣ
	string m_BlogObserverName;
public:
	ConcreteBlogObserver(string name): m_BlogObserverName(name) {};
public:
	string GetName()
	{
		return m_BlogObserverName;
	}
public:
	virtual void Update(Blog *pBlog)
	{
		cout << "[Blog Observer]" << m_BlogObserverName << " Update Message: " << pBlog->GetMsg() << " From [Blog]" << pBlog->GetName() << endl;

		map<Blog*, string>::iterator it = m_mapBlog_Msg.begin();
		for (;
			 it != m_mapBlog_Msg.end();
			 ++it)
		{
			if (((*it).first)->GetName() == pBlog->GetName())
			{
				(*it).second = pBlog->GetMsg(); // �ҵ���ֱ���滻����Msg
				return;
			}	 
		}
		// δ�ҵ�������뵽map
		if (it == m_mapBlog_Msg.end())
		{
			m_mapBlog_Msg.insert(make_pair(pBlog, pBlog->GetMsg()));
			cout << "[Blog Observer]" << m_BlogObserverName << " Add a New " << "[Blog]" << pBlog->GetName() << endl;
		}	
	}

	virtual void ShowMsg()
	{
		cout << "\nShow All Blog Message:" << endl;
		for (map<Blog*,string>::iterator it = m_mapBlog_Msg.begin();
			 it != m_mapBlog_Msg.end();
			 ++it)       // ��ʾ����list�е�Message
		{
			cout << "[Blog Observer]" << m_BlogObserverName << " Message: " << (*it).second << " From [Blog]" << ((*it).first)->GetName() << "\n" << endl;
		}	
		cout << "\n" << endl;
	}
};
void ObserverTest_Blog()
{
	Blog *pCsdn_Tly = new CsdnBlog("Tly_Bloger");
	Blog *pCsdn_Frank = new CsdnBlog("Frank Bloger");

	BlogObserver *pBgOb_A = new ConcreteBlogObserver("A");
	BlogObserver *pBgOb_B = new ConcreteBlogObserver("B");
	BlogObserver *pBgOb_C = new ConcreteBlogObserver("C");

	pCsdn_Tly->AttachBlogObserver(pBgOb_A);
	pCsdn_Tly->AttachBlogObserver(pBgOb_B);
	pCsdn_Tly->AttachBlogObserver(pBgOb_C);

	// ��һ��Blog��Tly Blog������֪ͨ������Ϣ��A��B��C Observer
	pCsdn_Tly->PublishMsg("I am Tly");
	pCsdn_Tly->Notify();
    
	// ������ʾA,B,C Observer���ĵ�����Blog����ʱ��ֻ��Tly)����Ϣ
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	pCsdn_Frank->AttachBlogObserver(pBgOb_A);
	pCsdn_Frank->AttachBlogObserver(pBgOb_B);

	// ����һ��Blog��Frank Blog������֪ͨ������Ϣ��A��B Observer
	pCsdn_Frank->PublishMsg("I am Frank");
	pCsdn_Frank->Notify();
	
	// ������ʾA,B,C Observer���ĵ�����Blog����ʱ��A,B��Tly��Frank,Cֻ��Tly)����Ϣ
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	// A ȡ��������Tly, Tly ���·�����Ϣ��B,C Observer
	pCsdn_Tly->DetachBlogObserver(pBgOb_A);
	pCsdn_Tly->PublishMsg("I am Tly Two");
	pCsdn_Tly->Notify();

	// ������ʾA,B,C Observer���ĵ�����Blog����Ϣ
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	// A ȡ��������Frank��Frank ���·�����Ϣ��B Observer
	pCsdn_Frank->DetachBlogObserver(pBgOb_A);
	pCsdn_Frank->PublishMsg("I am Frank Two");
	pCsdn_Frank->Notify();

	// ������ʾA,B,C Observer���ĵ�����Blog����Ϣ
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	SAFE_RELASE_POINTER(pBgOb_A);
	SAFE_RELASE_POINTER(pBgOb_B);
	SAFE_RELASE_POINTER(pBgOb_C);
	SAFE_RELASE_POINTER(pCsdn_Tly);
	SAFE_RELASE_POINTER(pCsdn_Frank);
}
void ObserverTest()
{
	cout << "*********** ObserverTest_General: *************" << endl;
	ObserverTest_General();
	cout << "*********** TemplateTest_Blog: *************" << endl;
	ObserverTest_Blog();
}
#endif