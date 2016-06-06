#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// 观察者模式（发布--订阅）
/*
1、 概念：
    定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
	当一个对象发生了变化，关注它的对象就会得到通知；这种交互也称为发布-订阅(publish-subscribe)。
	目标是通知的发布者，它发出通知时并不需要知道谁是它的观察者

2、 角色：
Subject（目标）
——目标知道它的观察者。可以有任意多个观察者观察同一个目标；
——提供注册和删除观察者对象的接口。
Observer（观察者）
——为那些在目标发生改变时需获得通知的对象定义一个更新接口。
ConcreteSubject（具体目标）
——将有关状态存入各ConcreteObserver对象；
——当它的状态发生改变时，向它的各个观察者发出通知。
ConcreteObserver（具体观察者）
——维护一个指向ConcreteSubject对象的引用；
——存储有关状态，这些状态应与目标的状态保持一致；
——实现Observer的更新接口以使自身状态与目标的状态保持一致。

3、使用场合：
①  当一个抽象模型有两个方面，其中一个方面依赖于另一方面。将这二者封装在独立的对象中以使它们可以各自独立的改变和复用；
②  当对一个对象的改变需要同时改变其它对象，而不知道具体有多少对象有待改变；
③  当一个对象必须通知其它对象，而它又不能假定其它对象是谁；也就是说，你不希望这些对象是紧密耦合的


4、优缺点：
①  观察者与被观察者之间是属于轻度的关联关系，并且是抽象耦合的，这样，对于两者来说都比较容易进行扩展。
②  观察者模式是一种常用的触发机制，它形成一条触发链，依次对各个观察者的方法进行处理。
    但同时，这也算是观察者模式一个缺点，由于是链式触发，当观察者比较多的时候，性能问题是比较令人担忧的。
	并且，在链式结构中，比较容易出现循环引用的错误，造成系统假死
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
	ConcreteObserver(Subject *pSubject): m_pSubject(pSubject),m_State(0) {};//  具体的Observer关联的Subject，调用该Subject的方法Update（）
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
// 一个Blog有多个观察者，一个观察者可以观察订阅多个Blog的状态

// Abstract Blog Observer
class Blog;
class BlogObserver
{
public:
	virtual void Update(Blog *pBlog)     = 0;  // Update指定Blog对象的Message
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
			(*it)->Update(this); // Update本Blog对象的Message到所有订阅该Blog对象的Observer
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
	map<Blog*, string> m_mapBlog_Msg;  // 保存订阅的Blog及对应的消息
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
				(*it).second = pBlog->GetMsg(); // 找到了直接替换跟新Msg
				return;
			}	 
		}
		// 未找到，则插入到map
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
			 ++it)       // 显示所有list中的Message
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

	// 第一个Blog：Tly Blog发布并通知跟新消息到A，B，C Observer
	pCsdn_Tly->PublishMsg("I am Tly");
	pCsdn_Tly->Notify();
    
	// 依次显示A,B,C Observer订阅的所有Blog（此时均只有Tly)的信息
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	pCsdn_Frank->AttachBlogObserver(pBgOb_A);
	pCsdn_Frank->AttachBlogObserver(pBgOb_B);

	// 另外一个Blog：Frank Blog发布并通知跟新消息到A，B Observer
	pCsdn_Frank->PublishMsg("I am Frank");
	pCsdn_Frank->Notify();
	
	// 依次显示A,B,C Observer订阅的所有Blog（此时有A,B有Tly、Frank,C只有Tly)的信息
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	// A 取消订阅了Tly, Tly 重新发布消息到B,C Observer
	pCsdn_Tly->DetachBlogObserver(pBgOb_A);
	pCsdn_Tly->PublishMsg("I am Tly Two");
	pCsdn_Tly->Notify();

	// 依次显示A,B,C Observer订阅的所有Blog的信息
	pBgOb_A->ShowMsg();
	pBgOb_B->ShowMsg();
	pBgOb_C->ShowMsg();

	// A 取消订阅了Frank，Frank 重新发布消息到B Observer
	pCsdn_Frank->DetachBlogObserver(pBgOb_A);
	pCsdn_Frank->PublishMsg("I am Frank Two");
	pCsdn_Frank->Notify();

	// 依次显示A,B,C Observer订阅的所有Blog的信息
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