#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "common.h"

// 中介者模式
/*
1、 概念：
    用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互

2、角色：
	Mediator：中介者，它定义了一个接口用于与各个Colleague对象通信
	ConcreteMediator：具体的中介者，它通过协调各Colleague对象实现协作行为；并了解和维护它的各个Colleague
	Colleague：同事类，每一个同事类都知道它的中介者对象；
    ConcreteColleague类：具体同事类，实现抽象同事类中的方法。每一个同时类需要知道中介者对象；
	每个具体同事类只需要了解自己的行为，而不需要了解其他同事类的情况 

	每一个同时对象在需要与其他的同事通信的时候，而是与它的中介者通信它们之间是按照以下方式进行协作的：
	同事向一个中介者对象发送和接收请求。中介者在各同事间适当地转发请求以实现协作行为

3、场合：
①  一组对象以定义良好但是复杂的方式进行通信。产生的相互依赖关系结构混乱且难以理解；
②  一个对象引用其他很多对象并且直接与这些对象通信，导致难以复用该对象；
③  想定制一个分布在多个类中的行为，而又不想生成太多的子类

4、优缺点：
①  减少了子类生成，Mediator将原本分布于多个对象间的行为集中在一起。改变这些行为只需生成Meditator的子类即可。
    这样各个Colleague类可被重用；
②  它将各Colleague解耦，Mediator有利于各Colleague间的松耦合。你可以独立的改变和复用各Colleague类和Mediator类；
③  它简化了对象协议，用Mediator和Colleague间的一对多的交互来代替多对多的交互。一对多的关系更容易理解、维护和扩展；
④  它对对象如何协作进行了抽象，将中介作为一个独立的概念并将其封装在一个对象中，使你将注意力从对象各自本身的行为转移到它们之间的交互上来。
    这有助于弄清楚一个系统中的对象是如何交互的；
⑤ 它使控制集中化，中介者模式将交互的复杂性变为中介者的复杂性。因为中介者封装了协议，它可能变得比任一个Colleague都复杂
   这可能使得中介者自身成为一个难于维护的庞然大物。
*/

void MediatorTest();

// Abstract Mediator 
class Colleague;
class Mediator
{
protected:
	list<Colleague*> m_listColleague;
public:
	virtual void AttachColleague(Colleague* pColleague)     = 0;
	virtual void Notify(Colleague *pColleague, string msg)  = 0;
};

// Abstract Colleague
class Colleague
{
protected:
	Mediator* m_pMediator;
	string m_Name;
public:
	Colleague(Mediator* pMediator, string name): m_pMediator(pMediator),m_Name(name) {};
public:
	virtual void SendMsg(string msg) = 0;
	virtual void RecvMsg(string msg) = 0;
	virtual string GetName()         = 0;
};


// Concrete Mediator
class ConcreteMediator : public Mediator
{
public:
	virtual void AttachColleague(Colleague* pColleague)
	{
		m_listColleague.push_back(pColleague);
	}
// 指定的Colleague pColleague发送消息（通过Mediator），其他的Colleague接受消息
	virtual void Notify(Colleague *pColleague, string msg) 
	{
		for (list<Colleague*>::iterator it = m_listColleague.begin();
			it != m_listColleague.end();
			++it)
		{
			if ((*it) != pColleague)
			{
				(*it)->RecvMsg(msg);
			}
		}
	}
};


// Concrete Colleague A
class ConcreteColleagueA : public Colleague
{
public:
	ConcreteColleagueA(Mediator* pMediator, string name): Colleague(pMediator, name) {};
public:
	virtual void SendMsg(string msg)
	{
		cout << m_Name << "[CCA] Send Msg: "<< msg << endl;
		m_pMediator->Notify(this, msg);
	}
	virtual void RecvMsg(string msg)
	{
		cout << m_Name << "[CCA] Recv Msg: "<< msg << endl;
	}
public:
	virtual string GetName()
	{
		return m_Name;
	}
};

// Concrete Colleague B
class ConcreteColleagueB : public Colleague
{
public:
	ConcreteColleagueB(Mediator* pMediator, string name): Colleague(pMediator, name) {};
public:
	virtual void SendMsg(string msg)
	{
		cout << m_Name << "[CCB] Send Msg: "<< msg << endl;
		m_pMediator->Notify(this, msg);
	}
	virtual void RecvMsg(string msg)
	{
		cout << m_Name << "[CCB] Recv Msg: "<< msg << endl;
	}
public:
	virtual string GetName()
	{
		return m_Name;
	}
};

void MediatorTest_General()
{
	Mediator *pM = new ConcreteMediator();

	Colleague *pCA  = new ConcreteColleagueA(pM, "Monitor1");
	Colleague *pCA2 = new ConcreteColleagueA(pM, "Monitor2");
	Colleague *pCB  = new ConcreteColleagueB(pM, "Student1");
	Colleague *pCB2 = new ConcreteColleagueB(pM, "Student2");

	pM->AttachColleague(pCA);
	pM->AttachColleague(pCA2);
	pM->AttachColleague(pCB);
	pM->AttachColleague(pCB2);

	// Monitor 1 Send Msg
	pCA->SendMsg("Hello Everyone I am Monitor 1 ");

	// Monitor 2 Send Msg
	pCA2->SendMsg("Hello Everyone I am Monitor 2 ");

	// Student 2 Send Msg
	pCB->SendMsg("Hello Everyone I am Student 1");

	SAFE_RELASE_POINTER(pM);
	SAFE_RELASE_POINTER(pCA);
	SAFE_RELASE_POINTER(pCA2);
	SAFE_RELASE_POINTER(pCB);
	SAFE_RELASE_POINTER(pCB2);
};


// 业主、租房中介 、租客
/*
业主：委托中介发布租房消息
租客: 查看中介的租房消息，并且通过中介发布自己的求租消息
*/

// 抽象租房中介类
class AbstractHousePerson;
class AbstractHouseMediator
{
protected:
	list<AbstractHousePerson*> m_listHousePerson;
public:
	virtual void SendHouseMsg(AbstractHousePerson *pAHP, string msg) = 0;
	virtual void AddHousePerson(AbstractHousePerson *pAHP) = 0;
};

// 抽象房屋需求人类（包括房屋出租需求业主、房屋租入需求租客)
class AbstractHousePerson
{
protected:
	AbstractHouseMediator* m_pHouseMediator;
public:
	AbstractHousePerson(AbstractHouseMediator *pAHM) : m_pHouseMediator(pAHM) {};
public:
	virtual void SendHouseMessage(string msg) = 0;
	virtual void RecvHouseMessage(string msg) = 0;
};

// 万达中介：具体租房中介
class WanDaHouseMediator : public AbstractHouseMediator
{
public:
	virtual void SendHouseMsg(AbstractHousePerson *pAHP, string msg)
	{
		for (list<AbstractHousePerson*>::iterator it = m_listHousePerson.begin();
			 it != m_listHousePerson.end();
			 ++it)
		{
			if ((*it) != pAHP)
			{
				(*it)->RecvHouseMessage(msg);
			}
		}
	}

	virtual void AddHousePerson(AbstractHousePerson* pAHP)
	{
		m_listHousePerson.push_back(pAHP);
	}
};

// 业主：房屋出租需求人
class HouseLord : public AbstractHousePerson
{
public:
	HouseLord(AbstractHouseMediator *pAHM) : AbstractHousePerson(pAHM) {};
public:
	virtual void SendHouseMessage(string msg)
	{
		cout << "House Lord Send House Msg: " << msg <<endl;
		m_pHouseMediator->SendHouseMsg(this, msg);  // 房东通过中介发送出租房消息，并且通知给所有其他的租房者、房东
	}
	virtual void RecvHouseMessage(string msg)
	{
		cout << "House Lord Recv Msg By Mediator: " << msg << endl;
	}
};
// 租客： 房屋租入需求人
class HouseRenter : public AbstractHousePerson
{
public:
	HouseRenter(AbstractHouseMediator *pAHM) : AbstractHousePerson(pAHM) {};
public:
	virtual void SendHouseMessage(string msg)
	{
		cout << "House Renter Send House Msg: " << msg << endl;
		m_pHouseMediator->SendHouseMsg(this, msg); //  租房者通过中介发送求租房消息，并且通知给所有其他的租房者、房东
	}
	virtual void RecvHouseMessage(string msg)
	{
		cout << "House Renter Recv Msg By Mediator: " << msg << endl;
	}
};
void MediatorTest_HouseRenter()
{
	AbstractHouseMediator *pWDHM = new WanDaHouseMediator();

	AbstractHousePerson   *pLd = new HouseLord(pWDHM);
	AbstractHousePerson   *pRr = new HouseRenter(pWDHM);

	pWDHM->AddHousePerson(pLd);
	pWDHM->AddHousePerson(pRr);

	pLd->SendHouseMessage("Hello I Have A House For Rent, Anyone Who Needs Contact Me Please!\n");
	pRr->SendHouseMessage("Hello I Need A House to Live, Anyone Who Has Contact Me Please!\n");

	SAFE_RELASE_POINTER(pWDHM);
	SAFE_RELASE_POINTER(pLd);
	SAFE_RELASE_POINTER(pRr);
};

class IMColleague;
// instance message abstract mediator class: IMGroup
class IMGroup
{
protected:
	list<IMColleague*> _listColleague; // 子类使用
public:
	virtual void attachColleague(IMColleague* colleague) // 关联同事对象，子类不需要重写
	{
		_listColleague.push_back(colleague);
	}
	virtual void notify(IMColleague* sender, string msg) = 0;
};

// instance message abstract colleage class: IMColleague
class IMColleague
{
protected:
	IMGroup *_groupMediator; // 子类使用
public:
	IMColleague(IMGroup *mediator) : _groupMediator(mediator) {}; //构造注入中介者对象
public:
	virtual void setIMGroup(IMGroup *mediator) //客户端手动注入中介者对象，子类不需要重写
	{ 
		_groupMediator = mediator;
	}
public:
	virtual void sendMsg(string msg) = 0; //dependon method
	virtual void recvMsg(string msg) = 0; // self method
};

// instance message weixin mediator class: WeiXinIMGroup
class WeiXinIMGroup : public IMGroup
{
public:
	virtual void notify(IMColleague* sender, string msg)
	{
		for (list<IMColleague*>::iterator it = _listColleague.begin();
			 it != _listColleague.end(); ++it)
		{
			if (sender != *it)
			{
				cout << "[Wei Xin Notify:] ";
				(*it)->recvMsg(msg); // 调用其他同事类的接收消息方法，通过中介者（群）来通知其他同事接收消息
			}
		}
	}
};

// instance message qq mediator class: QQIMGroup
class QQIMGroup : public IMGroup
{
public:
	virtual void notify(IMColleague* sender, string msg)
	{
		for (list<IMColleague*>::iterator it = _listColleague.begin();
			it != _listColleague.end(); ++it)
		{
			if (sender != *it)
			{
				cout << "[QQ Notify:] ";
				(*it)->recvMsg(msg); // 调用其他同事类的接收消息方法，通过中介者（群）来通知其他同事接收消息
			}
		}
	}
};

// instance message friend colleage class: FriendIMColleage
class FriendIMColleage : public IMColleague
{
public:
	FriendIMColleage(IMGroup *mediator) : IMColleague(mediator) {};
public:
	void sendMsg(string msg)
	{
		cout << "Friend IM Colleage send msg: " << msg << endl;
		_groupMediator->notify(this, msg); //  调用中介者对象通知其他同事
	}
	void recvMsg(string msg)
	{
		cout << "Friend IM Colleage recv msg: " << msg << endl;
	}
};

// instance message friend colleage class: RelativeIMColleage
class RelativeIMColleage : public IMColleague
{
public:
	RelativeIMColleage(IMGroup *mediator) : IMColleague(mediator) {};
public:
	void sendMsg(string msg)
	{
		cout << "Relative IM Colleage send msg: " << msg << endl;
		_groupMediator->notify(this, msg); //  调用中介者对象通知其他同事
	}
	void recvMsg(string msg)
	{
		cout << "Relative IM Colleage recv msg: " << msg << endl;
	}
};

void MediatorTest_IMCommunication()
{
	IMGroup *weixin_mediator = new WeiXinIMGroup();

	// 初始化设置im_friend_a,im_friend_b,im_relative同事类的中介者为weixin
	IMColleague *im_friend_a = new FriendIMColleage(weixin_mediator);
	IMColleague *im_friend_b = new FriendIMColleage(weixin_mediator);
	IMColleague *im_relative = new RelativeIMColleage(weixin_mediator);

	// 将im_friend_a,im_friend_b,im_relative加入到weixin_mediator的list中：
	weixin_mediator->attachColleague(im_friend_a);
	weixin_mediator->attachColleague(im_friend_b);
	weixin_mediator->attachColleague(im_relative);

	im_relative->sendMsg("happy new year!!!"); // im_friend_a、im_friend_b均能收到

	// 重新设置im_friend_a,im_relative同事类的中介者为qq,而im_friend_b中介者仍为weixin
	IMGroup *qq_mediator = new QQIMGroup();
	im_friend_a->setIMGroup(qq_mediator);
	im_relative->setIMGroup(qq_mediator);

	// 将im_friend_a,im_relative加入到qq_mediator的list中：
	qq_mediator->attachColleague(im_friend_a);
	qq_mediator->attachColleague(im_relative);
	im_relative->sendMsg("happy birthday!!!");  // 只有im_friend_a能收到
};


void MediatorTest()
{
	cout << "*********** MediatorTest_General: *************" << endl;
	MediatorTest_General();
	cout << "*********** MediatorTest_HouseRenter: *************" << endl;
	MediatorTest_HouseRenter();
	cout << "*********** MediatorTest_IMCommunication: *************" << endl;
	MediatorTest_IMCommunication();
}
#endif