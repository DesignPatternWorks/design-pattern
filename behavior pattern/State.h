#ifndef  _STATE_H_
#define  _STATE_H_

#include "common.h"

// ״̬ģʽ
/*
1�����
	����һ�����������ڲ�״̬�ı�ʱ�ı�������Ϊ�����������ƺ��޸��������ࡣ
	״̬ģʽ���ص�����״̬ת�����ܶ�ʱ�򣬶���һ�������״̬�����Ƕ���������������һ��״̬�����ԣ����״̬���Լ�¼�Ŷ���ľ���״̬��
	����״̬�Ĳ�ͬʹ�÷�֧�ṹ��ִ�в�ͬ�Ĺ��ܣ����д��ڴ����Ľṹ���Ƶķ�֧��䣬�������ά������⡣
	״̬ģʽ�����˷�֧��䣬���񹤳�ģʽ�����˼򵥹���ģʽ�ķ�֧���һ������״̬�����ɢ������״̬������ȥ��ÿ�����༯�д���һ��״̬
2����ɫ��
	Context������ͻ��˸���Ȥ�Ľӿڣ�����ά��һ��ConcreteState�����ʵ�������ʵ�����嵱ǰ״̬��
	State������һ���ӿ��Է�װ��Context��һ���ض�״̬��ص���Ϊ��
	ConcreteState subclasses��ÿһ������ʵ��һ����Context��һ��״̬��ص���Ϊ��

	����֮���Э���������£�
	Context����״̬��ص�����ί�и���ǰ��ConcreteState������
	Context���Խ�������Ϊһ���������ݸ�����������״̬������ʹ��״̬�����ڱ�Ҫʱ���Է���Context��
	Context�ǿͻ�ʹ�õ���Ҫ�ӿڡ��ͻ�����״̬����������һ��Context��һ��һ��Context������ϣ����Ŀͻ�������Ҫֱ����״̬����򽻵���
3��ʹ�ó��ϣ�
��	һ���������Ϊȡ��������״̬������������������ʱ�̸���״̬�ı�������Ϊ��
��	һ�������к����Ӵ�Ķ��֧��������䣬����Щ��֧�����ڸö����״̬�����״̬ͨ����һ������ö�ٳ�����ʾ��
	ͨ���ж������������һ��ͬ�������ṹ��Stateģʽ��ÿһ��������֧����һ�����������С�
	��ʹ������Ը��ݶ������������������״̬��Ϊһ��������һ������Բ���������������������仯��
*/
void StateTest();


class StateContext;
// Abstract State
class State
{
public:
	virtual void Handle(StateContext *pSC) = 0;
};


// State Context
class StateContext
{
private:
	State *m_pState;
	int  m_value;
public:
	StateContext(State *pState, int value) : m_pState(pState), m_value(value) {};
public:
	void Request()
	{
		if (!NULL_POINTER(m_pState))
		{
			m_pState->Handle(this);
		}
	}
	void SetState(State *pState)
	{
		m_pState = pState;
	}
	State* GetState(void)
	{
		return m_pState;
	}
public:
	int GetValue(void)
	{
		return m_value;
	}
	void SetValue(int value)
	{
		m_value = value;
	}
};



// Concrete State A
class ConcreteStateA : public State
{
public:
	virtual void Handle(StateContext *pSC)
	{
		cout << "value is " << pSC->GetValue() << endl;
		cout << "Concrete State A Handle!!!" << endl;
	}
};

// Concrete State B
class ConcreteStateB : public State
{
public:
	virtual void Handle(StateContext *pSC)
	{
		cout << "value is " << pSC->GetValue() << endl;
		cout << "Concrete State B Handle!!!" << endl;
	}
};

// Concrete State C
class ConcreteStateC : public State
{
public:
	virtual void Handle(StateContext *pSC)
	{
		cout << "value is " << pSC->GetValue() << endl;
		cout << "Concrete State C Handle!!!" << endl;
	}
};

void StateTest_General()
{
	State *pStateA = new ConcreteStateA();
	State *pStateB = new ConcreteStateB();

	StateContext *pSC = new StateContext(pStateA, 10); // ����ע��ConcreteStateAA
	pSC->Request();

	// �ڿͻ��˸�����������Ϣ����״̬ѡ���л�
	if (pSC->GetValue() <= 10)
	{
		pSC->SetState(pStateB);
	}
	else
	{
		pSC->SetState(pStateA);
	}
	pSC->Request();

	SAFE_RELASE_POINTER(pStateA);
	SAFE_RELASE_POINTER(pStateB);
	SAFE_RELASE_POINTER(pSC);
}

// �Ľ��棺��״̬�ı仯�ŵ�StateContext�ڲ�����ÿ�ε���һ��Request��״̬Ǩ��һ��

class StateEx
{
public:
	virtual void Handle() = 0;
};

// Concrete State A
class ConcreteStateExA : public StateEx
{
public:
	virtual void Handle()
	{
		cout << "Concrete State Ex A Handle!!!" << endl;
	}
};

class ConcreteStateExB : public StateEx
{
public:
	virtual void Handle()
	{
		cout << "Concrete State Ex B Handle!!!" << endl;
	}
};

class StateContextEx
{
private:
	StateEx    *m_pCurrentState;
	ConcreteStateExA *m_pStateA;
	ConcreteStateExB *m_pStateB;
	int m_value;
public:
	StateContextEx(int value = 10)
	{
		m_pStateA = new ConcreteStateExA();
		m_pStateB = new ConcreteStateExB();
		m_pCurrentState = m_pStateA; // ��ʼ��Ϊ״̬A
		m_value = value;
	}
	virtual ~StateContextEx()
	{
		SAFE_RELASE_POINTER(m_pStateA);
		SAFE_RELASE_POINTER(m_pStateB);
	}
public:
	void SetState(StateEx *pState)
	{
		m_pCurrentState = pState;
	}
	void SetValue(int value)
	{
		m_value = value;
	}
	int GetValue(void)
	{
		return m_value;
	}
public:
	void Request()
	{
		if (GetValue() < 10)
		{
			SetState(m_pStateA);
		}
		else
		{
			SetState(m_pStateB);
		}
		m_pCurrentState->Handle(); 
	}
};



//// Concrete State A
//class ConcreteStateA : public State
//{
//public:
//	virtual void Handle(StateContext *pSC)
//	{
//		if (pSC->GetValue() < 10)
//		{
//			cout << "Concrete State A Handle!!!" << endl;
//		}
//		else if(pSC->GetValue() < 20)
//		{
//			pSC->SetState(new ConcreteStateB);
//			pSC->GetState()->Handle(pSC);
//		}
//		else
//		{
//			pSC->SetState(new ConcreteStateC);
//			pSC->GetState()->Handle(pSC);
//		}
//	}
//};
//
//// Concrete State B
//class ConcreteStateB : public State
//{
//public:
//	virtual void Handle(StateContext *pSC)
//	{
//		if (pSC->GetValue() < 10)
//		{
//			pSC->SetState(new ConcreteStateA);
//			pSC->GetState()->Handle(pSC);
//		}
//		else if (pSC->GetValue() < 20)
//		{
//			cout << "Concrete State B Handle!!!" << endl;
//		}
//		else
//		{
//			pSC->SetState(new ConcreteStateC);
//			pSC->GetState()->Handle(pSC);
//		}
//	}
//};
//
//// Concrete State C
//class ConcreteStateC : public State
//{
//public:
//	virtual void Handle(StateContext *pSC)
//	{
//		if (pSC->GetValue() < 10)
//		{
//			pSC->SetState(new ConcreteStateA);
//			pSC->GetState()->Handle(pSC);
//		}
//		else if (pSC->GetValue() < 20)
//		{
//			pSC->SetState(new ConcreteStateB);
//			pSC->GetState()->Handle(pSC);
//		}
//		else
//		{
//			cout << "Concrete State C Handle!!!" << endl;
//		}
//	}
//};


void StateTest_GeneralEx()
{
	StateContextEx *pSCEx = new StateContextEx(5);
	pSCEx->Request();

	pSCEx->SetValue(20);
	pSCEx->Request();

	SAFE_RELASE_POINTER(pSCEx);
}

// ս����Ϊǰ���С����ڣ���ͬʱ�ڵĻ����Ǹ���ʱ������ƽ��еģ��Ҳ�ͬʱ�ڵ���Ϊ��һ��
#define  PREPHASE_DAY_MAX 8
#define  METAPHASE_DAY_MAX 20
// Abstract War State ,Singleton 
class War;

class WarState
{
public:
	virtual void Run(War *pWar) = 0;
};

// War  (State Context)
class War
{
private:
	WarState *m_pWarState;
	int m_ElapsedDays;
public:
	War(WarState *pWarState) : m_pWarState(pWarState), m_ElapsedDays(0) {};
public:
	int GetElapsedDays()
	{
		return m_ElapsedDays;
	}
	void SetElapsedDays(int days)
	{
		m_ElapsedDays = days;
	}
	void SetWarState(WarState *pWarState)
	{
		m_pWarState = pWarState;
	}
	WarState* GetWarState()
	{
		return m_pWarState;
	}
	void RunWar()
	{
		m_pWarState->Run(this);
	}
	//void RunWar() //  ���������ฺ��״̬ѡ���ת��
	//{
	//	if (GetElapsedDays() < PREPHASE_DAY_MAX)
	//	{
	//		m_pWarState = PrephaseWarState::Instance();
	//	}
	//	else if (GetElapsedDays() < METAPHASE_DAY_MAX)
	//	{
	//		m_pWarState = MetaphaseWarState::Instance();
	//	}
	//	else
	//	{
	//		m_pWarState = AnaphaseWarState::Instance();
	//	}
	//	m_pWarState->Run(); // ���贫��contxt
	//}
};

// AnaphaseWarState
class AnaphaseWarState : public WarState
{
private:
	static AnaphaseWarState *m_pWarState;
	class Garbage
	{
	public:
		virtual ~Garbage()
		{
			if (NULL_POINTER(AnaphaseWarState::Instance()))
			{
				delete AnaphaseWarState::Instance();
			}
		}
	};
	static Garbage g;
private:
	AnaphaseWarState() {};
	AnaphaseWarState(const AnaphaseWarState&) {};
	AnaphaseWarState& operator = (const AnaphaseWarState) {};
public:
	static AnaphaseWarState* Instance()
	{
		if (NULL_POINTER(m_pWarState))
		{
			m_pWarState = new AnaphaseWarState();
		}
		return m_pWarState;
	}
public:
	virtual void Run(War *pWar)
	{
		cout << "Now The War Is On Anaphase State, Anaphase dota heroes become the protagonist, War is coming to end" << "[time = " << pWar->GetElapsedDays()<< "]" << endl;
	}
};
AnaphaseWarState* AnaphaseWarState::m_pWarState = NULL;


// Metaphase War State
class MetaphaseWarState : public WarState
{
private:
	static MetaphaseWarState *m_pWarState;
	class Garbage
	{
	public:
		virtual ~Garbage()
		{
			if (NULL_POINTER(MetaphaseWarState::Instance()))
			{
				delete MetaphaseWarState::Instance();
			}
		}
	};
	static Garbage g;
private:
	MetaphaseWarState() {};
	MetaphaseWarState(const MetaphaseWarState&) {};
	MetaphaseWarState& operator = (const MetaphaseWarState) {};
public:
	static MetaphaseWarState* Instance()
	{
		if (NULL_POINTER(m_pWarState))
		{
			m_pWarState = new MetaphaseWarState();
		}
		return m_pWarState;
	}
public:
	virtual void Run(War *pWar)    //  ��������״̬�ڲ�����״̬��ѡ���ת��
	{
		if (pWar->GetElapsedDays() <= METAPHASE_DAY_MAX)
		{
			cout << "Now The War Is On Metaphase State, Anaphase and Prephase dota heroes both become the protagonist, War is on hot" << "[time = " << pWar->GetElapsedDays()<< "]" << endl;
		}
		else
		{
			pWar->SetWarState(AnaphaseWarState::Instance());
			pWar->GetWarState()->Run(pWar);
		}
	}
};
MetaphaseWarState* MetaphaseWarState::m_pWarState = NULL;

// Prephase War State
class PrephaseWarState : public WarState
{
private:
	static PrephaseWarState *m_pWarState;
	class Garbage
	{
	public:
		virtual ~Garbage()
		{
			if (NULL_POINTER(PrephaseWarState::Instance()))
			{
				delete PrephaseWarState::Instance();
			}
		}
	};
	static Garbage g;
private:
	PrephaseWarState() {};
	PrephaseWarState(const PrephaseWarState&) {};
	PrephaseWarState& operator = (const PrephaseWarState) {};
public:
	static PrephaseWarState* Instance()
	{
		if (NULL_POINTER(m_pWarState))
		{
			m_pWarState = new PrephaseWarState();
		}
		return m_pWarState;
	}
public:
	virtual void Run(War *pWar) //  ��������״̬�ڲ�����״̬��ѡ���ת��
	{
		if (pWar->GetElapsedDays() <= PREPHASE_DAY_MAX)
		{
			cout << "Now The War Is On Prephase State, Prephase dota heroes become the protagonist, War is coming to begin" << "[time = " << pWar->GetElapsedDays()<< "]" << endl;
		}
		else
		{
			pWar->SetWarState(MetaphaseWarState::Instance());
			pWar->GetWarState()->Run(pWar);
		}
	}
};
PrephaseWarState* PrephaseWarState::m_pWarState = NULL;



void StateTest_War()
{
	War *pW = new War(PrephaseWarState::Instance());

	for (int ElapsedDays = 0; ElapsedDays < 30; ElapsedDays+=4)
	{
		pW->SetElapsedDays(ElapsedDays);
		pW->RunWar();
	}

	SAFE_RELASE_POINTER(pW);
}

void StateTest()
{
	cout << "*********** StateTest_General: *************" << endl;
	StateTest_General();
	cout << "*********** StateTest_General_Ex: *************" << endl;
	StateTest_GeneralEx();
	cout << "*********** StateTest_War: *************" << endl;
	StateTest_War();
}
#endif