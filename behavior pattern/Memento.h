#ifndef  _MEMENTO_H_
#define  _MEMENTO_H_

#include "common.h"

// 备忘录模式
/*
1、概念：
	在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。

2、 角色：
	Memento：备忘录存储原发器对象的内部状态。原发器根据需要决定备忘录存储原发器的哪些内部状态；防止原发器以外的其他对象访问备忘录。
			备忘录实际上有两个接口，管理者只能看到备忘录的窄接口———它只能将备忘录传递给其他对象。
			相反，原发器能够看到一个宽接口，允许它访问返回到先前状态所需的所有数据。
			理想的情况是只允许生成备忘录的那个原发器访问本备忘录的内部状态（C++ friend)；
	Originator：原发器创建一个备忘录，用以记录当前时刻它的内部状态；我们使用备忘录恢复内部状态；
	Caretaker：负责保存好备忘录；但是，不能对备忘录的内容进行操作或检查。
	备忘录模式是按照以下方式进行协作的：
	管理器向原发器请求一个备忘录，保留一段时间后，将其送回给原发器；而有的时候管理者不会将备忘录返回给原发器，因为原发器可能根本不需要退到先前的状态。

	备忘录是被动的，只有创建备忘录的原发器会对它的状态进行赋值和检索
3、 场合：
①	必须保存一个对象在某一个时刻的部分或完整状态，这样以后需要时它才能恢复到先前的状态
②	如果一个用接口来让其它对象直接得到这些状态，将会暴露对象的实现细节并破坏对象的封装性

4、特点
	有时有必要记录一个对象的内部状态。为了允许用户取消不确定的操作或从错误中恢复过来，需要实现检查点和取消机制
	而要实现这些机制，你必须事先将状态信息保存在某处，这样才能将对象恢复到它们先前的状态。
	如何实现这个将状态信息保存在某处呢？使用原型模式？由于对象通常封装了其部分或所有的状态信息，
	使得其状态不能被其他对象访问，也就不可能在该对象之外保存其状态了。
	由于原型模式总是返回对象的全部状态信息，同时原型模式使其状态能被其它对象访问，这样就违反了封装的原则，还可能有损应用的可靠性和可扩展性
	一个备忘录是一个对象，它存储另一个对象在某个瞬间的内部状态，而后者称为备忘录的原发器。
	当需要设置原发器的检查点时，取消操作机制会向原发器请求一个备忘录。原发器用描述当前状态的信息初始化该备忘录。
	只有原发器可以向备忘录中存取信息，备忘录对其他的对象是“不可见”的。C++ friend关键字可以实现这个
*/

void MementoTest();

//状态信息类
struct MementoState
{
private:
	string m_stateinformation;
public:
	MementoState(string state): m_stateinformation(state) {};
public:
	string GetStateInform()
	{
		return m_stateinformation;
	}
};

// 备忘录
class Originator;
class Memento
{
private:
	MementoState m_state;
public:
	Memento(MementoState state) : m_state(state) {};
    friend class Originator; // Originator为友元类，只有Originator才能访问Memento成员
};

// 原发器
class Originator
{
private:
	MementoState m_state;
public:
	Originator(MementoState state) : m_state(state) {};
public:
	Memento* SaveStateToCreatedMemento()
	{
		Memento *pMemento = new Memento(m_state);  // 生成备忘录
		return pMemento;
	}
	void LoadStateFromMemento(Memento *pMemento)
	{
		m_state = pMemento->m_state;   // 只有Originator才能访问Memento的私有成员
	}
	void ChangeState(MementoState state)
	{
		m_state = state;
	}
    void ShowState()
	{
		cout << "State Information Is: " << m_state.GetStateInform() << endl;
	}
};

// 备忘录管理
class Caretaker
{
private:
	vector<Memento*> m_vecMemento;  // vector 支持随机存取，list不支持
public:
	Caretaker() {};
	virtual ~Caretaker()
	{
		for (vector<Memento*>::iterator it = m_vecMemento.begin();
			 it != m_vecMemento.end();
			 ++it)
		{
			SAFE_RELASE_POINTER(*it);		
		}
		m_vecMemento.clear();
	}
public:
	void SaveMemento(Memento *pMemento)
	{
		m_vecMemento.push_back(pMemento);
	}
	Memento* LoadMementoByIndex(int MementoIndex)
	{
		return m_vecMemento[MementoIndex];
	}
};

void MementoTest_General()
{
	Caretaker *pCT = new Caretaker();
	MementoState state1("First Step");
	MementoState state2("Second Step");
	MementoState state3("Third Step");

	Originator *pO = new Originator(state1);
	pO->ShowState();

	pCT->SaveMemento(pO->SaveStateToCreatedMemento()); // Caretaker 管理添加新建的第一个Memento
	pO->ChangeState(state2);
	pO->ShowState();

	pCT->SaveMemento(pO->SaveStateToCreatedMemento()); // Caretaker 管理添加新建的第二个Memento
	pO->ChangeState(state3);
	pO->ShowState();

	cout << "Restore State 1: ";
	pO->LoadStateFromMemento(pCT->LoadMementoByIndex(1)); // 从Caretaker中取第二个Memento保存的状态
	pO->ShowState();

	cout << "Restore State 0: ";
	pO->LoadStateFromMemento(pCT->LoadMementoByIndex(0)); // 从Caretaker中取第一个Memento保存的状态
	pO->ShowState();

	SAFE_RELASE_POINTER(pO);
	SAFE_RELASE_POINTER(pCT);
}


// 游戏角色：状态包括敏捷、力量、智力三种属性；当角色攻击时，力量属性值少10点，其他不变，随时可以恢复角色攻击之前的某个状态

// 游戏角色备忘录
class GameRole;
class GameRoleMemento
{
private:
	int m_RoleAgileValue;
	int m_RolePowerValue;
	int m_RoleIntelligenceValue;
public:
	GameRoleMemento(int agile, int powr, int intelligence)
		: m_RoleAgileValue(agile), m_RolePowerValue(powr), m_RoleIntelligenceValue(intelligence) {};
	friend class GameRole;
};

// 游戏角色(原发器)
class GameRole
{
private:
	int m_RoleAgileValue;
	int m_RolePowerValue;
	int m_RoleIntelligenceValue;
public:
	GameRole(int agile, int powr, int intelligence)
		: m_RoleAgileValue(agile), m_RolePowerValue(powr), m_RoleIntelligenceValue(intelligence) {};
public:
	GameRoleMemento* CreateMemento()
	{
		return new GameRoleMemento(m_RoleAgileValue, m_RolePowerValue, m_RoleIntelligenceValue);
	}
	void SetMemento(GameRoleMemento *pGameRoleMemento)
	{
		m_RoleAgileValue = pGameRoleMemento->m_RoleAgileValue;
		m_RolePowerValue = pGameRoleMemento->m_RolePowerValue;
		m_RoleIntelligenceValue = pGameRoleMemento->m_RoleIntelligenceValue;
	}
	void Attack()
	{
		m_RolePowerValue-= 10;
	}
	void ShowAttribute()
	{
		cout << "Hero Attribution: [Agile]:" << m_RoleAgileValue << " [Power]:" << m_RolePowerValue << 
		" [Intelligence]:" << m_RoleIntelligenceValue << endl;
	}
};
// 游戏角色备忘录管理者
class GameRoleCaretaker
{
private:
	vector<GameRoleMemento*> m_vecGameRoleMemento;
public:
	GameRoleCaretaker() {};
	virtual ~GameRoleCaretaker()
	{
		for (vector<GameRoleMemento*>::iterator it = m_vecGameRoleMemento.begin();
			 it != m_vecGameRoleMemento.end();
			 ++it)
		{
			SAFE_RELASE_POINTER(*it);
		}
		m_vecGameRoleMemento.clear();
	}
public:
	void SaveGameRoleMemento(GameRoleMemento *pGRM)
	{
		m_vecGameRoleMemento.push_back(pGRM);
	}
	GameRoleMemento* LoadGameRoleMementoByIndex(int GameRoleMementoIndex)
	{
		return m_vecGameRoleMemento[GameRoleMementoIndex];
	}
};
void MementoTest_GameRole()
{
	GameRoleCaretaker *pGRCT = new GameRoleCaretaker();

	//原始属性状态
	GameRole  *pGR = new GameRole(50,50,50);
	pGR->ShowAttribute();

	//攻击一次后的状态，先保存,并显示属性
	pGRCT->SaveGameRoleMemento(pGR->CreateMemento());
	pGR->Attack();
	pGR->ShowAttribute();


	//再攻击一次后的状态，先保存,并显示属性
	pGRCT->SaveGameRoleMemento(pGR->CreateMemento());
	pGR->Attack();
	pGR->ShowAttribute();

	//恢复第二次攻击前的状态,并显示属性
	cout << "Game Role Restore 1： ";
	pGR->SetMemento(pGRCT->LoadGameRoleMementoByIndex(1));
	pGR->ShowAttribute();
	
	//恢复第一次攻击前的状态,并显示属性
	cout << "Game Role Restore 0： ";
	pGR->SetMemento(pGRCT->LoadGameRoleMementoByIndex(0));
	pGR->ShowAttribute();

	SAFE_RELASE_POINTER(pGRCT);
	SAFE_RELASE_POINTER(pGR);
}
void MementoTest()
{
	cout << "*********** MementoTest_General: *************" << endl;
	MementoTest_General();
	cout << "*********** MementoTest_GameRole: *************" << endl;
	MementoTest_GameRole();
}
#endif