#ifndef  _STRATEGY_H_
#define  _STRATEGY_H_

#include "common.h"

//策略模式
void StrategyTest();

/*
1、概念：
	定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。
	该模式使得算法可独立于使用它的客户而变化
	两种硬编码：在一个类中，如需要提供多种查找算法，可以将这些算法写到一个类中，在该类中提供多个方法，每一个方法对应一个具体的查找算法
	当然也可以将这些查找算法封装在一个统一的方法中，通过if…else…或者case等条件判断语句来进行选择
    问题解决方案：解决如何让算法和对象分开来，使得算法可以独立于使用它的客户而变化
2、 角色：
	环境类(Context):用一个ConcreteStrategy对象来配置。维护一个对Strategy对象的引用。可定义一个接口来让Strategy访问它的数据。
	抽象策略类(Strategy):定义所有支持的算法的公共接口。 Context使用这个接口来调用某ConcreteStrategy定义的算法。
	具体策略类(ConcreteStrategy):以Strategy接口实现某具体算法。
3、 范围：
	①	许多相关的类仅仅是行为有异。 “策略”提供了一种用多个行为中的一个行为来配置一个类的方法。即一个系统需要动态地在几种算法中选择一种。
	②  需要使用一个算法的不同变体。例如，你可能会定义一些反映不同的空间 /时间权衡的算法。当这些变体实现为一个算法的类层次时 ,可以使用策略模式。
	③  算法使用客户不应该知道的数据。可使用策略模式以避免暴露复杂的、与算法相关的数据结构。
	④ 一个类定义了多种行为 , 并且这些行为在这个类的操作中以多个条件语句的形式出现。将相关的条件分支移入它们各自的Strategy类中以代替这些条件语句。
4、 优缺点：
	1）优点：
	①  相关算法系列 Strategy类层次为Context定义了一系列的可供重用的算法或行为。 继承有助于析取出这些算法中的公共功能
	②  将算法封装在独立的Strategy类中使得你可以独立于其Context改变它，使它易于切换、易于理解、易于扩展。
	③  消除了一些if else条件语句
	④  实现的选择 Strategy模式可以提供相同行为的不同实现。客户可以根据不同时间 /空间权衡取舍要求从不同策略中进行选择
	2）缺点：
	①  客户端必须知道所有的策略类，并自行决定使用哪一个策略类
		本模式有一个潜在的缺点，就是一个客户要选择一个合适的Strategy就必须知道这些Strategy到底有何不同。
		此时可能不得不向客户暴露具体的实现问题。因此仅当这些不同行为变体与客户相关的行为时 , 才需要使用Strategy模式
	②   Strategy和Context之间的通信开销 ：
		无论各个ConcreteStrategy实现的算法是简单还是复杂, 它们都共享Strategy定义的接口。
		因此很可能某些 ConcreteStrategy不会都用到所有通过这个接口传递给它们的信息；简单的 ConcreteStrategy可能不使用其中的任何信息！
		这就意味着有时Context会创建和初始化一些永远不会用到的参数。如果存在这样问题 , 那么将需要在Strategy和Context之间更进行紧密的耦合
	③  策略模式将造成产生很多策略类
5、与其他模式的区别：(可以消除if else ：状态模式、策略模式、责任链模式等，根本是继承）
   ① 与状态模式：(可以认为“状态模式是完全封装且自修改的策略模式”)
	A)最重要区别：
		策略模式只是的条件选择只执行一次，而状态模式是随着实例参数（对象实例的状态）的改变不停地更改执行模式。
		换句话说，策略模式只是在对象初始化的时候更改执行模式，
		而状态模式是根据对象实例的周期时间而动态地改变对象实例的执行模式

		在状态模式中，状态的变迁是由对象的内部条件决定，外界只需关心其接口，不必关心其状态对象的创建和转化;
		而策略模式里，采取何种策略由外部条件(C)决定。

	B)	策略模式的环境类自己选择一个具体策略类，具体策略类无须关心环境类；
	而状态模式的环境类由于外在因素需要放进一个具体状态中，以便通过其方法实现状态的切换，因此环境类和状态类之间存在一种双向的关联关系。
	C）	使用策略模式时，客户端需要知道所选的具体策略是哪一个，而使用状态模式时，客户端无须关心具体状态，环境类的状态会根据用户的操作自动转换。
	D)	如果系统中某个类的对象存在多种状态，不同状态下行为有差异，而且这些状态之间可以发生转换时使用状态模式；
		如果系统中某个类的某一行为存在多种实现方式，而且这些实现方式可以互换时使用策略模式
	
	② 与工厂模式：
	工厂模式是创建型模式 ，它关注对象创建，提供创建对象的接口. 让对象的创建与具体的使用客户无关。
	策略模式是对象行为型模式 ，它关注行为和算法的封装 。它定义一系列的算法,把每一个算法封装起来, 并且使它们可相互替换。使得算法可独立于使用它的客户而变化
	
	③ 与责任链模式：
	这两个设计模式最大的区别就是状态模式是让各个状态对象自己知道其下一个处理的对象是谁。
	而职责链模式中的各个对象并不指定其下一个处理的对象到底是谁，只有在客户端才设定
	*/

// Abstract Strategy
class Strategy
{
public:
	virtual void AlgorithmInterface() = 0;
};

// Concrete Strategy A
class ConcreteStrategyA : public Strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout << " I am Concrete Strategy A" << endl;
	}
};

// Concrete Strategy B
class ConcreteStrategyB : public Strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout << " I am Concrete Strategy B" << endl;
	}
};

// Concrete Strategy C
class ConcreteStrategyC : public Strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout << " I am Concrete Strategy C" << endl;
	}
};
// Context
class StrategyContext
{
private:
	Strategy *m_pStrategy;
public:
	StrategyContext(Strategy *pS) : m_pStrategy(pS) {};  // 构造静态注入策略对象
	virtual ~StrategyContext() 
	{
		SAFE_RELASE_POINTER(m_pStrategy);
	}
public:
	void SetStrategy(Strategy *pS)   // 动态注入策略对象
	{
		SAFE_RELASE_POINTER(m_pStrategy);// 释放之前申请的对象
		m_pStrategy = pS;
	}
public:
	void ContextInterface()
	{
		if (!NULL_POINTER(m_pStrategy))
		{
			m_pStrategy->AlgorithmInterface();
		}
	}
};

void StrategyTest_General()
{
	Strategy *pCSA = new ConcreteStrategyA();
	Strategy *pCSB = new ConcreteStrategyB();
	Strategy *pCSC = new ConcreteStrategyC();

	StrategyContext *pSContext = new StrategyContext(pCSA);
	pSContext->ContextInterface();

	pSContext->SetStrategy(pCSB);
	pSContext->ContextInterface();

	pSContext->SetStrategy(pCSC);
	pSContext->ContextInterface();

	SAFE_RELASE_POINTER(pSContext);
}

template <typename T>
class StrategyContextEx
{
public:
	void ContextInterface(void)
	{
		_strategy.AlgorithmInterface();
	}
private:
	T _strategy;
};

//把具体的Strategy作为一个模板参数将一个Strategy和它的Context静态地绑定在一起
typedef StrategyContextEx<ConcreteStrategyA> StrategyContextA;
typedef StrategyContextEx<ConcreteStrategyB> StrategyContextB;
typedef StrategyContextEx<ConcreteStrategyC> StrategyContextC;

void StrategyTest_GeneralTemplateEx()
{
	StrategyContextA SC_A;
	SC_A.ContextInterface();

	StrategyContextB SC_B;
	SC_B.ContextInterface();	
	
	StrategyContextC SC_C;
	SC_C.ContextInterface();
}

// Use Factory Pattern to Produce Concrete Strategy

// Abstract Strategy Factory
class StrategyAbstractFactory
{
public:
	virtual Strategy* CreateStrategy() = 0;
};

// Concrete Strategy Factory A
class StrategyFactoryA : public StrategyAbstractFactory
{
public:
	virtual Strategy* CreateStrategy()
	{
		return new ConcreteStrategyA();
	}
};

// Concrete Strategy Factory B
class StrategyFactoryB : public StrategyAbstractFactory
{
public:
	virtual Strategy* CreateStrategy()
	{
		return new ConcreteStrategyB();
	}
};

// Concrete Strategy Factory C
class StrategyFactoryC : public StrategyAbstractFactory
{
public:
	virtual Strategy* CreateStrategy()
	{
		return new ConcreteStrategyC();
	}
};

void StrategyTest_GeneralEx()
{
	StrategyAbstractFactory *pSFA = new StrategyFactoryA();
	Strategy *pSA = pSFA->CreateStrategy();

	StrategyAbstractFactory *pSFB = new StrategyFactoryB();
	Strategy *pSB = pSFB->CreateStrategy();

	StrategyAbstractFactory *pSFC = new StrategyFactoryC();
	Strategy *pSC = pSFC->CreateStrategy();

	StrategyContext *pSContext =new StrategyContext(pSA);
	pSContext->ContextInterface();

	pSContext->SetStrategy(pSB);
	pSContext->ContextInterface();

	pSContext->SetStrategy(pSC);
	pSContext->ContextInterface();

	SAFE_RELASE_POINTER(pSFA);
	SAFE_RELASE_POINTER(pSFB);
	SAFE_RELASE_POINTER(pSFC);
	SAFE_RELASE_POINTER(pSContext);
}


template <class T>
class StrategyFactoryBase
{
public:
	T* CreateStrategy(void)
	{
		return new T;
	}
};

typedef StrategyFactoryBase<ConcreteStrategyA>  StrategyFactoryTemplateA;
typedef StrategyFactoryBase<ConcreteStrategyB>  StrategyFactoryTemplateB;
typedef StrategyFactoryBase<ConcreteStrategyC>  StrategyFactoryTemplateC;

void StrategyTest_GeneralFactoryTemplateEx()
{
	StrategyFactoryTemplateA SFT_A;
	Strategy *pSA = SFT_A.CreateStrategy();

	StrategyFactoryTemplateB SFT_B;
	Strategy *pSB = SFT_B.CreateStrategy();

	StrategyFactoryTemplateC SFT_C;
	Strategy *pSC = SFT_C.CreateStrategy();

	StrategyContext *pSContext = new StrategyContext(pSA);
	pSContext->ContextInterface();

	pSContext->SetStrategy(pSB);
	pSContext->ContextInterface();

	pSContext->SetStrategy(pSC);
	pSContext->ContextInterface();

	SAFE_RELASE_POINTER(pSContext);
}

// Travel Strategy

// Abstract Travel Strategy
class TravelStrategy
{
public:
	virtual void Travel() = 0;
};

// Concrete Travel Strategy : Car Strategy
class CarStrategy : public TravelStrategy
{
private:
	static CarStrategy *m_pStrategy;
	class Garbage
	{
		~Garbage()
		{
			if (!NULL_POINTER(CarStrategy::GetInstance()))
			{
				delete CarStrategy::GetInstance();
			}
		}
	};
	static Garbage g;
public:
	static CarStrategy* GetInstance()
	{
		if (NULL_POINTER(m_pStrategy))
		{
			m_pStrategy =  new CarStrategy();
		}

		return m_pStrategy;
	}
private:
	CarStrategy() {};
	CarStrategy(const CarStrategy&) {};
	CarStrategy& operator = (const CarStrategy&) {};
public:
	virtual void Travel()
	{
		cout << "Select The Way of Car For Traveling" << endl;
	}
};
CarStrategy* CarStrategy::m_pStrategy = NULL;

// Concrete Travel Strategy : Airplane Strategy
class AirplaneStrategy : public TravelStrategy
{
private:
	static AirplaneStrategy *m_pStrategy;
	class Garbage
	{
		~Garbage()
		{
			if (!NULL_POINTER(AirplaneStrategy::GetInstance()))
			{
				delete AirplaneStrategy::GetInstance();
			}
		}
	};
	static Garbage g;
public:
	static AirplaneStrategy* GetInstance()
	{
		if (NULL_POINTER(m_pStrategy))
		{
			m_pStrategy =  new AirplaneStrategy();
		}

		return m_pStrategy;
	}
private:
	AirplaneStrategy() {};
	AirplaneStrategy(const AirplaneStrategy&) {};
	AirplaneStrategy& operator = (const AirplaneStrategy&) {};
public:
	virtual void Travel()
	{
		cout << "Select The Way of Airplane For Traveling" << endl;
	}
};
AirplaneStrategy* AirplaneStrategy::m_pStrategy = NULL;

// Concrete Travel Strategy : Train Strategy
class TrainStrategy : public TravelStrategy
{
private:
	static TrainStrategy *m_pStrategy;
	class Garbage
	{
		~Garbage()
		{
			if (!NULL_POINTER(TrainStrategy::GetInstance()))
			{
				delete TrainStrategy::GetInstance();
			}
		}
	};
	static Garbage g;
public:
	static TrainStrategy* GetInstance()
	{
		if (NULL_POINTER(m_pStrategy))
		{
			m_pStrategy =  new TrainStrategy();
		}

		return m_pStrategy;
	}
private:
	TrainStrategy() {};
	TrainStrategy(const TrainStrategy&) {};
	TrainStrategy& operator = (const TrainStrategy&) {};
public:
	virtual void Travel()
	{
		cout << "Select The Way of Train For Traveling" << endl;
	}
};
TrainStrategy* TrainStrategy::m_pStrategy = NULL;


// Travel Context : Person
class Person
{
private:
	TravelStrategy *m_pTravelStrategy;
public:
	Person(TravelStrategy *pTS) : m_pTravelStrategy(pTS) {};
public:
	void SetTravelStrategy(TravelStrategy *pTS) // 有Garbage类，不需要手动释放ConcreteTravelStrategy对象了
	{
		m_pTravelStrategy = pTS;
	}
public:
	void Travel()
	{
		m_pTravelStrategy->Travel();
	}
};
void StrategyTest_Travel()
{
	Person *pPerson = new Person(CarStrategy::GetInstance());
	pPerson->Travel();

	pPerson->SetTravelStrategy(AirplaneStrategy::GetInstance());
	pPerson->Travel();

	pPerson->SetTravelStrategy(TrainStrategy::GetInstance());
	pPerson->Travel();

	SAFE_RELASE_POINTER(pPerson);
}
void StrategyTest()
{
	cout << "*********** StrategyTest_General: *************" << endl;
	StrategyTest_General();
	cout << "*********** StrategyTest_General_Ex: *************" << endl;
	StrategyTest_GeneralEx();
	cout << "*********** StrategyTest_GeneralTemplateEx: *************" << endl;
	StrategyTest_GeneralTemplateEx();
	cout << "*********** StrategyTest_GeneralFactoryTemplateEx: *************" << endl;
	StrategyTest_GeneralFactoryTemplateEx();
	cout << "*********** StrategyTest_Travel: *************" << endl;
	StrategyTest_Travel();
}

#endif