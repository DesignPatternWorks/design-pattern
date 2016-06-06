#ifndef  _MEMENTO_H_
#define  _MEMENTO_H_

#include "common.h"

// ����¼ģʽ
/*
1�����
	�ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڸö���֮�Ᵽ�����״̬�������Ժ�Ϳɽ��ö���ָ���ԭ�ȱ����״̬��

2�� ��ɫ��
	Memento������¼�洢ԭ����������ڲ�״̬��ԭ����������Ҫ��������¼�洢ԭ��������Щ�ڲ�״̬����ֹԭ�������������������ʱ���¼��
			����¼ʵ�����������ӿڣ�������ֻ�ܿ�������¼��խ�ӿڡ�������ֻ�ܽ�����¼���ݸ���������
			�෴��ԭ�����ܹ�����һ����ӿڣ����������ʷ��ص���ǰ״̬������������ݡ�
			����������ֻ�������ɱ���¼���Ǹ�ԭ�������ʱ�����¼���ڲ�״̬��C++ friend)��
	Originator��ԭ��������һ������¼�����Լ�¼��ǰʱ�������ڲ�״̬������ʹ�ñ���¼�ָ��ڲ�״̬��
	Caretaker�����𱣴�ñ���¼�����ǣ����ܶԱ���¼�����ݽ��в������顣
	����¼ģʽ�ǰ������·�ʽ����Э���ģ�
	��������ԭ��������һ������¼������һ��ʱ��󣬽����ͻظ�ԭ���������е�ʱ������߲��Ὣ����¼���ظ�ԭ��������Ϊԭ�������ܸ�������Ҫ�˵���ǰ��״̬��

	����¼�Ǳ����ģ�ֻ�д�������¼��ԭ�����������״̬���и�ֵ�ͼ���
3�� ���ϣ�
��	���뱣��һ��������ĳһ��ʱ�̵Ĳ��ֻ�����״̬�������Ժ���Ҫʱ�����ָܻ�����ǰ��״̬
��	���һ���ýӿ�������������ֱ�ӵõ���Щ״̬�����ᱩ¶�����ʵ��ϸ�ڲ��ƻ�����ķ�װ��

4���ص�
	��ʱ�б�Ҫ��¼һ��������ڲ�״̬��Ϊ�������û�ȡ����ȷ���Ĳ�����Ӵ����лָ���������Ҫʵ�ּ����ȡ������
	��Ҫʵ����Щ���ƣ���������Ƚ�״̬��Ϣ������ĳ�����������ܽ�����ָ���������ǰ��״̬��
	���ʵ�������״̬��Ϣ������ĳ���أ�ʹ��ԭ��ģʽ�����ڶ���ͨ����װ���䲿�ֻ����е�״̬��Ϣ��
	ʹ����״̬���ܱ�����������ʣ�Ҳ�Ͳ������ڸö���֮�Ᵽ����״̬�ˡ�
	����ԭ��ģʽ���Ƿ��ض����ȫ��״̬��Ϣ��ͬʱԭ��ģʽʹ��״̬�ܱ�����������ʣ�������Υ���˷�װ��ԭ�򣬻���������Ӧ�õĿɿ��ԺͿ���չ��
	һ������¼��һ���������洢��һ��������ĳ��˲����ڲ�״̬�������߳�Ϊ����¼��ԭ������
	����Ҫ����ԭ�����ļ���ʱ��ȡ���������ƻ���ԭ��������һ������¼��ԭ������������ǰ״̬����Ϣ��ʼ���ñ���¼��
	ֻ��ԭ������������¼�д�ȡ��Ϣ������¼�������Ķ����ǡ����ɼ����ġ�C++ friend�ؼ��ֿ���ʵ�����
*/

void MementoTest();

//״̬��Ϣ��
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

// ����¼
class Originator;
class Memento
{
private:
	MementoState m_state;
public:
	Memento(MementoState state) : m_state(state) {};
    friend class Originator; // OriginatorΪ��Ԫ�ֻ࣬��Originator���ܷ���Memento��Ա
};

// ԭ����
class Originator
{
private:
	MementoState m_state;
public:
	Originator(MementoState state) : m_state(state) {};
public:
	Memento* SaveStateToCreatedMemento()
	{
		Memento *pMemento = new Memento(m_state);  // ���ɱ���¼
		return pMemento;
	}
	void LoadStateFromMemento(Memento *pMemento)
	{
		m_state = pMemento->m_state;   // ֻ��Originator���ܷ���Memento��˽�г�Ա
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

// ����¼����
class Caretaker
{
private:
	vector<Memento*> m_vecMemento;  // vector ֧�������ȡ��list��֧��
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

	pCT->SaveMemento(pO->SaveStateToCreatedMemento()); // Caretaker ��������½��ĵ�һ��Memento
	pO->ChangeState(state2);
	pO->ShowState();

	pCT->SaveMemento(pO->SaveStateToCreatedMemento()); // Caretaker ��������½��ĵڶ���Memento
	pO->ChangeState(state3);
	pO->ShowState();

	cout << "Restore State 1: ";
	pO->LoadStateFromMemento(pCT->LoadMementoByIndex(1)); // ��Caretaker��ȡ�ڶ���Memento�����״̬
	pO->ShowState();

	cout << "Restore State 0: ";
	pO->LoadStateFromMemento(pCT->LoadMementoByIndex(0)); // ��Caretaker��ȡ��һ��Memento�����״̬
	pO->ShowState();

	SAFE_RELASE_POINTER(pO);
	SAFE_RELASE_POINTER(pCT);
}


// ��Ϸ��ɫ��״̬�������ݡ������������������ԣ�����ɫ����ʱ����������ֵ��10�㣬�������䣬��ʱ���Իָ���ɫ����֮ǰ��ĳ��״̬

// ��Ϸ��ɫ����¼
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

// ��Ϸ��ɫ(ԭ����)
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
// ��Ϸ��ɫ����¼������
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

	//ԭʼ����״̬
	GameRole  *pGR = new GameRole(50,50,50);
	pGR->ShowAttribute();

	//����һ�κ��״̬���ȱ���,����ʾ����
	pGRCT->SaveGameRoleMemento(pGR->CreateMemento());
	pGR->Attack();
	pGR->ShowAttribute();


	//�ٹ���һ�κ��״̬���ȱ���,����ʾ����
	pGRCT->SaveGameRoleMemento(pGR->CreateMemento());
	pGR->Attack();
	pGR->ShowAttribute();

	//�ָ��ڶ��ι���ǰ��״̬,����ʾ����
	cout << "Game Role Restore 1�� ";
	pGR->SetMemento(pGRCT->LoadGameRoleMementoByIndex(1));
	pGR->ShowAttribute();
	
	//�ָ���һ�ι���ǰ��״̬,����ʾ����
	cout << "Game Role Restore 0�� ";
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