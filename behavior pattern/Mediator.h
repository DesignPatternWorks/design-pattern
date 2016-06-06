#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "common.h"

// �н���ģʽ
/*
1�� ���
    ��һ���н��������װһϵ�еĶ��󽻻����н���ʹ��������Ҫ��ʽ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮��Ľ���

2����ɫ��
	Mediator���н��ߣ���������һ���ӿ����������Colleague����ͨ��
	ConcreteMediator��������н��ߣ���ͨ��Э����Colleague����ʵ��Э����Ϊ�����˽��ά�����ĸ���Colleague
	Colleague��ͬ���࣬ÿһ��ͬ���඼֪�������н��߶���
    ConcreteColleague�ࣺ����ͬ���࣬ʵ�ֳ���ͬ�����еķ�����ÿһ��ͬʱ����Ҫ֪���н��߶���
	ÿ������ͬ����ֻ��Ҫ�˽��Լ�����Ϊ��������Ҫ�˽�����ͬ�������� 

	ÿһ��ͬʱ��������Ҫ��������ͬ��ͨ�ŵ�ʱ�򣬶����������н���ͨ������֮���ǰ������·�ʽ����Э���ģ�
	ͬ����һ���н��߶����ͺͽ��������н����ڸ�ͬ�¼��ʵ���ת��������ʵ��Э����Ϊ

3�����ϣ�
��  һ������Զ������õ��Ǹ��ӵķ�ʽ����ͨ�š��������໥������ϵ�ṹ������������⣻
��  һ���������������ܶ������ֱ������Щ����ͨ�ţ��������Ը��øö���
��  �붨��һ���ֲ��ڶ�����е���Ϊ�����ֲ�������̫�������

4����ȱ�㣺
��  �������������ɣ�Mediator��ԭ���ֲ��ڶ����������Ϊ������һ�𡣸ı���Щ��Ϊֻ������Meditator�����༴�ɡ�
    ��������Colleague��ɱ����ã�
��  ������Colleague���Mediator�����ڸ�Colleague�������ϡ�����Զ����ĸı�͸��ø�Colleague���Mediator�ࣻ
��  �����˶���Э�飬��Mediator��Colleague���һ�Զ�Ľ����������Զ�Ľ�����һ�Զ�Ĺ�ϵ��������⡢ά������չ��
��  ���Զ������Э�������˳��󣬽��н���Ϊһ�������ĸ�������װ��һ�������У�ʹ�㽫ע�����Ӷ�����Ա������Ϊת�Ƶ�����֮��Ľ���������
    ��������Ū���һ��ϵͳ�еĶ�������ν����ģ�
�� ��ʹ���Ƽ��л����н���ģʽ�������ĸ����Ա�Ϊ�н��ߵĸ����ԡ���Ϊ�н��߷�װ��Э�飬�����ܱ�ñ���һ��Colleague������
   �����ʹ���н��������Ϊһ������ά������Ȼ���
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
// ָ����Colleague pColleague������Ϣ��ͨ��Mediator����������Colleague������Ϣ
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


// ҵ�����ⷿ�н� �����
/*
ҵ����ί���н鷢���ⷿ��Ϣ
���: �鿴�н���ⷿ��Ϣ������ͨ���н鷢���Լ���������Ϣ
*/

// �����ⷿ�н���
class AbstractHousePerson;
class AbstractHouseMediator
{
protected:
	list<AbstractHousePerson*> m_listHousePerson;
public:
	virtual void SendHouseMsg(AbstractHousePerson *pAHP, string msg) = 0;
	virtual void AddHousePerson(AbstractHousePerson *pAHP) = 0;
};

// �������������ࣨ�������ݳ�������ҵ�������������������)
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

// ����н飺�����ⷿ�н�
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

// ҵ�������ݳ���������
class HouseLord : public AbstractHousePerson
{
public:
	HouseLord(AbstractHouseMediator *pAHM) : AbstractHousePerson(pAHM) {};
public:
	virtual void SendHouseMessage(string msg)
	{
		cout << "House Lord Send House Msg: " << msg <<endl;
		m_pHouseMediator->SendHouseMsg(this, msg);  // ����ͨ���н鷢�ͳ��ⷿ��Ϣ������֪ͨ�������������ⷿ�ߡ�����
	}
	virtual void RecvHouseMessage(string msg)
	{
		cout << "House Lord Recv Msg By Mediator: " << msg << endl;
	}
};
// ��ͣ� ��������������
class HouseRenter : public AbstractHousePerson
{
public:
	HouseRenter(AbstractHouseMediator *pAHM) : AbstractHousePerson(pAHM) {};
public:
	virtual void SendHouseMessage(string msg)
	{
		cout << "House Renter Send House Msg: " << msg << endl;
		m_pHouseMediator->SendHouseMsg(this, msg); //  �ⷿ��ͨ���н鷢�����ⷿ��Ϣ������֪ͨ�������������ⷿ�ߡ�����
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
	list<IMColleague*> _listColleague; // ����ʹ��
public:
	virtual void attachColleague(IMColleague* colleague) // ����ͬ�¶������಻��Ҫ��д
	{
		_listColleague.push_back(colleague);
	}
	virtual void notify(IMColleague* sender, string msg) = 0;
};

// instance message abstract colleage class: IMColleague
class IMColleague
{
protected:
	IMGroup *_groupMediator; // ����ʹ��
public:
	IMColleague(IMGroup *mediator) : _groupMediator(mediator) {}; //����ע���н��߶���
public:
	virtual void setIMGroup(IMGroup *mediator) //�ͻ����ֶ�ע���н��߶������಻��Ҫ��д
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
				(*it)->recvMsg(msg); // ��������ͬ����Ľ�����Ϣ������ͨ���н��ߣ�Ⱥ����֪ͨ����ͬ�½�����Ϣ
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
				(*it)->recvMsg(msg); // ��������ͬ����Ľ�����Ϣ������ͨ���н��ߣ�Ⱥ����֪ͨ����ͬ�½�����Ϣ
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
		_groupMediator->notify(this, msg); //  �����н��߶���֪ͨ����ͬ��
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
		_groupMediator->notify(this, msg); //  �����н��߶���֪ͨ����ͬ��
	}
	void recvMsg(string msg)
	{
		cout << "Relative IM Colleage recv msg: " << msg << endl;
	}
};

void MediatorTest_IMCommunication()
{
	IMGroup *weixin_mediator = new WeiXinIMGroup();

	// ��ʼ������im_friend_a,im_friend_b,im_relativeͬ������н���Ϊweixin
	IMColleague *im_friend_a = new FriendIMColleage(weixin_mediator);
	IMColleague *im_friend_b = new FriendIMColleage(weixin_mediator);
	IMColleague *im_relative = new RelativeIMColleage(weixin_mediator);

	// ��im_friend_a,im_friend_b,im_relative���뵽weixin_mediator��list�У�
	weixin_mediator->attachColleague(im_friend_a);
	weixin_mediator->attachColleague(im_friend_b);
	weixin_mediator->attachColleague(im_relative);

	im_relative->sendMsg("happy new year!!!"); // im_friend_a��im_friend_b�����յ�

	// ��������im_friend_a,im_relativeͬ������н���Ϊqq,��im_friend_b�н�����Ϊweixin
	IMGroup *qq_mediator = new QQIMGroup();
	im_friend_a->setIMGroup(qq_mediator);
	im_relative->setIMGroup(qq_mediator);

	// ��im_friend_a,im_relative���뵽qq_mediator��list�У�
	qq_mediator->attachColleague(im_friend_a);
	qq_mediator->attachColleague(im_relative);
	im_relative->sendMsg("happy birthday!!!");  // ֻ��im_friend_a���յ�
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