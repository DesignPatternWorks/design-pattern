#ifndef  _STATE_H_
#define  _STATE_H_

#include "common.h"

// 状态模式
/*
1、概念：
	允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类。
	状态模式的重点在于状态转换，很多时候，对于一个对象的状态，我们都是让这个对象包含一个状态的属性，这个状态属性记录着对象的具体状态，
	根据状态的不同使用分支结构来执行不同的功能，类中存在大量的结构类似的分支语句，变得难以维护和理解。
	状态模式消除了分支语句，就像工厂模式消除了简单工厂模式的分支语句一样，将状态处理分散到各个状态子类中去，每个子类集中处理一种状态
2、角色：
	Context：定义客户端感兴趣的接口，并且维护一个ConcreteState子类的实例，这个实例定义当前状态；
	State：定义一个接口以封装与Context的一个特定状态相关的行为；
	ConcreteState subclasses：每一个子类实现一个与Context的一个状态相关的行为。

	它们之间的协作步骤如下：
	Context将与状态相关的请求委托给当前的ConcreteState对象处理；
	Context可以将自身作为一个参数传递给处理该请求的状态对象。这使得状态对象在必要时可以访问Context；
	Context是客户使用的主要接口。客户可用状态对象来配置一个Context，一旦一个Context配置完毕，它的客户不再需要直接与状态对象打交道；
3、使用场合：
①	一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为；
②	一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态。这个状态通常用一个或多个枚举常量表示。
	通常有多个操作包含这一相同的条件结构。State模式将每一个条件分支放入一个独立的类中。
	这使得你可以根据对象自身的情况将对象的状态作为一个对象，这一对象可以不依赖于其它对象而独立变化。
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

	StateContext *pSC = new StateContext(pStateA, 10); // 构造注入ConcreteStateAA
	pSC->Request();

	// 在客户端根据上下文信息进行状态选择切换
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

// 改进版：把状态的变化放到StateContext内部处理，每次调用一次Request，状态迁移一次

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
		m_pCurrentState = m_pStateA; // 初始化为状态A
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

// 战争分为前、中、后期，不同时期的划分是根据时间的推移进行的，且不同时期的行为不一样
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
	//void RunWar() //  环境变量类负责状态选择和转换
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
	//	m_pWarState->Run(); // 无需传入contxt
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
	virtual void Run(War *pWar)    //  各个具体状态内部负责状态的选择和转换
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
	virtual void Run(War *pWar) //  各个具体状态内部负责状态的选择和转换
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