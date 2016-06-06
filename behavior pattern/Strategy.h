#ifndef  _STRATEGY_H_
#define  _STRATEGY_H_

#include "common.h"

//����ģʽ
void StrategyTest();

/*
1�����
	����һϵ�е��㷨��������һ������װ����������ʹ���ǿ��໥�滻��
	��ģʽʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯
	����Ӳ���룺��һ�����У�����Ҫ�ṩ���ֲ����㷨�����Խ���Щ�㷨д��һ�����У��ڸ������ṩ���������ÿһ��������Ӧһ������Ĳ����㷨
	��ȻҲ���Խ���Щ�����㷨��װ��һ��ͳһ�ķ����У�ͨ��if��else������case�������ж����������ѡ��
    ���������������������㷨�Ͷ���ֿ�����ʹ���㷨���Զ�����ʹ�����Ŀͻ����仯
2�� ��ɫ��
	������(Context):��һ��ConcreteStrategy���������á�ά��һ����Strategy��������á��ɶ���һ���ӿ�����Strategy�����������ݡ�
	���������(Strategy):��������֧�ֵ��㷨�Ĺ����ӿڡ� Contextʹ������ӿ�������ĳConcreteStrategy������㷨��
	���������(ConcreteStrategy):��Strategy�ӿ�ʵ��ĳ�����㷨��
3�� ��Χ��
	��	�����ص����������Ϊ���졣 �����ԡ��ṩ��һ���ö����Ϊ�е�һ����Ϊ������һ����ķ�������һ��ϵͳ��Ҫ��̬���ڼ����㷨��ѡ��һ�֡�
	��  ��Ҫʹ��һ���㷨�Ĳ�ͬ���塣���磬����ܻᶨ��һЩ��ӳ��ͬ�Ŀռ� /ʱ��Ȩ����㷨������Щ����ʵ��Ϊһ���㷨������ʱ ,����ʹ�ò���ģʽ��
	��  �㷨ʹ�ÿͻ���Ӧ��֪�������ݡ���ʹ�ò���ģʽ�Ա��Ⱪ¶���ӵġ����㷨��ص����ݽṹ��
	�� һ���ඨ���˶�����Ϊ , ������Щ��Ϊ�������Ĳ������Զ������������ʽ���֡�����ص�������֧�������Ǹ��Ե�Strategy�����Դ�����Щ������䡣
4�� ��ȱ�㣺
	1���ŵ㣺
	��  ����㷨ϵ�� Strategy����ΪContext������һϵ�еĿɹ����õ��㷨����Ϊ�� �̳���������ȡ����Щ�㷨�еĹ�������
	��  ���㷨��װ�ڶ�����Strategy����ʹ������Զ�������Context�ı�����ʹ�������л���������⡢������չ��
	��  ������һЩif else�������
	��  ʵ�ֵ�ѡ�� Strategyģʽ�����ṩ��ͬ��Ϊ�Ĳ�ͬʵ�֡��ͻ����Ը��ݲ�ͬʱ�� /�ռ�Ȩ��ȡ��Ҫ��Ӳ�ͬ�����н���ѡ��
	2��ȱ�㣺
	��  �ͻ��˱���֪�����еĲ����࣬�����о���ʹ����һ��������
		��ģʽ��һ��Ǳ�ڵ�ȱ�㣬����һ���ͻ�Ҫѡ��һ�����ʵ�Strategy�ͱ���֪����ЩStrategy�����кβ�ͬ��
		��ʱ���ܲ��ò���ͻ���¶�����ʵ�����⡣��˽�����Щ��ͬ��Ϊ������ͻ���ص���Ϊʱ , ����Ҫʹ��Strategyģʽ
	��   Strategy��Context֮���ͨ�ſ��� ��
		���۸���ConcreteStrategyʵ�ֵ��㷨�Ǽ򵥻��Ǹ���, ���Ƕ�����Strategy����Ľӿڡ�
		��˺ܿ���ĳЩ ConcreteStrategy���ᶼ�õ�����ͨ������ӿڴ��ݸ����ǵ���Ϣ���򵥵� ConcreteStrategy���ܲ�ʹ�����е��κ���Ϣ��
		�����ζ����ʱContext�ᴴ���ͳ�ʼ��һЩ��Զ�����õ��Ĳ�������������������� , ��ô����Ҫ��Strategy��Context֮������н��ܵ����
	��  ����ģʽ����ɲ����ܶ������
5��������ģʽ������(��������if else ��״̬ģʽ������ģʽ��������ģʽ�ȣ������Ǽ̳У�
   �� ��״̬ģʽ��(������Ϊ��״̬ģʽ����ȫ��װ�����޸ĵĲ���ģʽ��)
	A)����Ҫ����
		����ģʽֻ�ǵ�����ѡ��ִֻ��һ�Σ���״̬ģʽ������ʵ������������ʵ����״̬���ĸı䲻ͣ�ظ���ִ��ģʽ��
		���仰˵������ģʽֻ���ڶ����ʼ����ʱ�����ִ��ģʽ��
		��״̬ģʽ�Ǹ��ݶ���ʵ��������ʱ�����̬�ظı����ʵ����ִ��ģʽ

		��״̬ģʽ�У�״̬�ı�Ǩ���ɶ�����ڲ��������������ֻ�������ӿڣ����ع�����״̬����Ĵ�����ת��;
		������ģʽ���ȡ���ֲ������ⲿ����(C)������

	B)	����ģʽ�Ļ������Լ�ѡ��һ����������࣬���������������Ļ����ࣻ
	��״̬ģʽ�Ļ�������������������Ҫ�Ž�һ������״̬�У��Ա�ͨ���䷽��ʵ��״̬���л�����˻������״̬��֮�����һ��˫��Ĺ�����ϵ��
	C��	ʹ�ò���ģʽʱ���ͻ�����Ҫ֪����ѡ�ľ����������һ������ʹ��״̬ģʽʱ���ͻ���������ľ���״̬���������״̬������û��Ĳ����Զ�ת����
	D)	���ϵͳ��ĳ����Ķ�����ڶ���״̬����ͬ״̬����Ϊ�в��죬������Щ״̬֮����Է���ת��ʱʹ��״̬ģʽ��
		���ϵͳ��ĳ�����ĳһ��Ϊ���ڶ���ʵ�ַ�ʽ��������Щʵ�ַ�ʽ���Ի���ʱʹ�ò���ģʽ
	
	�� �빤��ģʽ��
	����ģʽ�Ǵ�����ģʽ ������ע���󴴽����ṩ��������Ľӿ�. �ö���Ĵ���������ʹ�ÿͻ��޹ء�
	����ģʽ�Ƕ�����Ϊ��ģʽ ������ע��Ϊ���㷨�ķ�װ ��������һϵ�е��㷨,��ÿһ���㷨��װ����, ����ʹ���ǿ��໥�滻��ʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯
	
	�� ��������ģʽ��
	���������ģʽ�����������״̬ģʽ���ø���״̬�����Լ�֪������һ������Ķ�����˭��
	��ְ����ģʽ�еĸ������󲢲�ָ������һ������Ķ��󵽵���˭��ֻ���ڿͻ��˲��趨
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
	StrategyContext(Strategy *pS) : m_pStrategy(pS) {};  // ���쾲̬ע����Զ���
	virtual ~StrategyContext() 
	{
		SAFE_RELASE_POINTER(m_pStrategy);
	}
public:
	void SetStrategy(Strategy *pS)   // ��̬ע����Զ���
	{
		SAFE_RELASE_POINTER(m_pStrategy);// �ͷ�֮ǰ����Ķ���
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

//�Ѿ����Strategy��Ϊһ��ģ�������һ��Strategy������Context��̬�ذ���һ��
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
	void SetTravelStrategy(TravelStrategy *pTS) // ��Garbage�࣬����Ҫ�ֶ��ͷ�ConcreteTravelStrategy������
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