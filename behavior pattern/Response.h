#ifndef  _RESPONSE_H_
#define  _RESPONSE_H_

#include "common.h"


// 责任链模式
/*
1、 概念：
		使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，直到有一个对象处理它为止

2、 角色：
	Handler：定义了一个处理请求的接口；其它类如果需要处理相同的请求，可以实现该接口就好了；
	ConcreteHandler：处理它所负责的请求，如果可处理该请求，就处理掉这个请求；否则将该请求转发给它的下一个可以处理该请求的对象
					所以它必须能访问它的下一个可以处理同样请求的对象
	Client：向处理对象提出具体的请求。
	当客户提交一个请求时，请求沿着一条链传递，直至有一个ConcreteHandler对象负责处理它或丢弃

3、 场合：
	①  有多个的对象可以处理一个请求，由哪个对象处理该请求是在运行时刻自动确定的
	②  如果想在不明确指定接收者的情况下，向多个对象中的一个提交一个请求
	③  可以处理一个请求的对象集合应被动态指定
	④  假如使用if…else…语句来组织一个责任链时感到力不从心，代码看上去很糟糕时，就可以使用责任链模式

4、 优缺点：
	①  降低耦合度；职责链模式使得一个对象不用知道是哪一个对象处理它的请求。对象仅需要知道该请求会被正确的处理
		接收者和发送者都没有对方的明确的信息，且链中的对象不需要知道链的结构
	②  增强了给对象指派职责的灵活性；当在对象中分派职责时，职责链给你更多的灵活性
		你可以通过在运行时对该链进行动态的增加或修改来增加或改变处理一个请求的那些职责
	③  不保证被接受，既然一个请求没有明确的接收者，那么就不能保证它一定会被处理；该请求可能一直到链的末端都得不到处理
		一个请求也可能因该链没有被正确配置而得不到处理
	④  责任链模式与if…else…相比，他的耦合性要低一些，因为它把条件判定都分散到了各个处理类中，并且这些处理类的优先处理顺序可以随意设定
		责任链模式也有缺点，这与if…else…语句的缺点是一样的，那就是在找到正确的处理类之前，所有的判定条件都要被执行一遍
		当责任链比较长时，性能问题比较严重
*/


void ResponseTest();

// Abstract Handler
class Handler
{
protected:
	Handler *m_pHandler;
	int     m_nState;
public:
	Handler(Handler *pHandler) : m_pHandler(pHandler) {};
public:
	virtual void HandlerRequest(int nState) = 0;
};

// Concrete Handler A
class ConcreteHandlerA : public Handler
{
public:
	ConcreteHandlerA(Handler *pHandler) : Handler(pHandler) {};
public:
	virtual void HandlerRequest(int nState)
	{
		if (nState < 10)
		{
			cout << "Concrete Handler A Do The Request !!!" << "State: " << nState << endl;
			return;
		}
		// >10 的情况下一个ConcreteHandler处理
		if (NULL_POINTER(m_pHandler))
		{
			cout << "No Handler Do The Request !!!" << "State: " << nState << endl;
			return;
		}
		m_pHandler->HandlerRequest(nState);
	}
};

// Concrete Handler B
class ConcreteHandlerB : public Handler
{
public:
	ConcreteHandlerB(Handler *pHandler) : Handler(pHandler) {};
public:
	virtual void HandlerRequest(int nState)
	{
		if (nState < 20)
		{
			cout << "Concrete Handler B Do The Request !!!" << "State: " << nState << endl;
			return;
		}
		// >20 的情况下一个ConcreteHandler处理
		if (NULL_POINTER(m_pHandler))
		{
			cout << "No Handler Do The Request !!!" << "State: " << nState << endl;
			return;
		}
		m_pHandler->HandlerRequest(nState);
	}
};

// Concrete Handler C
class ConcreteHandlerC : public Handler
{
public:
	ConcreteHandlerC(Handler *pHandler) : Handler(pHandler) {};
public:
	virtual void HandlerRequest(int nState)
	{
		if (nState < 30)
		{
			cout << "Concrete Handler C Do The Request !!!" << "State: " << nState << endl;
			return;
		}
		// >30 的情况下一个ConcreteHandler处理
		if (NULL_POINTER(m_pHandler))
		{
			cout << "No Handler Do The Request !!!" << "State: " << nState << endl;
			return;
		}
		m_pHandler->HandlerRequest(nState);
	}
};

void ResponseTest_General()
{
	Handler *pCHC = new ConcreteHandlerC(NULL);
	Handler *pCHB = new ConcreteHandlerB(pCHC);
	Handler *pCHA = new ConcreteHandlerA(pCHB); //指明每一个Handler的下一个Handler 

	// 从Concrete Handler A 开始往下处理
	pCHA->HandlerRequest(5);
	pCHA->HandlerRequest(15);
	pCHA->HandlerRequest(25);
	pCHA->HandlerRequest(35);


	SAFE_RELASE_POINTER(pCHA);
	SAFE_RELASE_POINTER(pCHB);
	SAFE_RELASE_POINTER(pCHC);
}


// Manager Accept The Request of Adding Salary

// Abstract Handler : Manager
class Manager
{
protected:
	Manager *m_pManager;
public:
	Manager(Manager *pManager) : m_pManager(pManager) {};
public:
	virtual void DealSalaryRequest(int nSalary) = 0;
};

// Concrete Handler 1 : CommonManager
class CommonManager : public Manager
{
public:
	CommonManager(Manager *pManager) : Manager(pManager) {};
public:
	virtual void DealSalaryRequest(int nSalary)
	{
		if (nSalary < 300)
		{
			cout << "Common Manager Accept The Request Of Adding Salary: " << nSalary << endl;
			return;
		}
		if (NULL_POINTER(m_pManager))
		{
			cout << "No Manager Accept The Request Of Adding Salary: " << nSalary << endl;
			return;
		}
		cout << "Common Manager Have No Right to Accept The Request Of Adding Salary, Transmit To Majordomo : " << nSalary << endl;
		m_pManager->DealSalaryRequest(nSalary);
	}
};

// Concrete Handler 2 : Majordomo
class Majordomo : public Manager
{
public:
	Majordomo(Manager *pManager) : Manager(pManager) {};
public:
	virtual void DealSalaryRequest(int nSalary)
	{
		if (nSalary < 500)
		{
			cout << "Majordomo Accept The Request Of Adding Salary: " << nSalary << endl;
			return;
		}
		if (NULL_POINTER(m_pManager))
		{
			cout << "No Manager Accept The Request Of Adding Salary: " << nSalary << endl;
			return;
		}
		cout << "Majordomo Have No Right to Accept The Request Of Adding Salary, Transmit To General Manager : " << nSalary << endl;
		m_pManager->DealSalaryRequest(nSalary);
	}
};

// Concrete Handler 1 : GeneralManager
class GeneralManager : public Manager
{
public:
	GeneralManager(Manager *pManager) : Manager(pManager) {};
public:
	virtual void DealSalaryRequest(int nSalary)
	{
		if (nSalary < 1000)
		{
			cout << "General Manager Accept The Request Of Adding Salary: " << nSalary << endl;
			return;
		}
		if (NULL_POINTER(m_pManager))
		{
			cout << "General Manger Refuse The Request Of Adding Salary: " << nSalary << endl;
			return;
		}
	}
};

class HolidayRequest
{
private:
	string _type;
	int    _days;
public:
	HolidayRequest(string type, int days) : _type(type), _days(days) {};
public:
	string getType(void)
	{
		return _type;
	}
	int getDays(void)
	{
		return _days;
	}
};


class HoliadyHandler
{
protected:
	HoliadyHandler *_handler;
public:
	HoliadyHandler() : _handler(NULL) {};
public:
	void setHandler(HoliadyHandler *handler)
	{
		_handler = handler;
	}
public:
	virtual void HandleHolidayRequest(HolidayRequest &request) = 0;
};

// Sectin Chief Handler
class SectionChief : public HoliadyHandler
{
private:
	string _name;
public:
	SectionChief(string name) : _name(name) {};
public:
	void HandleHolidayRequest(HolidayRequest &request)
	{
		if (request.getDays() <= 1)
		{
			cout << "Section chief " << _name << " approve your " << request.getDays() << " days for " << request.getType() << " request !" << endl;
		}
		else
		{
			if (NULL_POINTER(_handler))
			{
				cout << "No holiday handler is assigned !" << endl;
			}
			else
			{
				_handler->HandleHolidayRequest(request);
			}
			
		}
	}
};

// Minister Handler
class Minister : public HoliadyHandler
{
private:
	string _name;
public:
	Minister(string name) : _name(name) {};
public:
	void HandleHolidayRequest(HolidayRequest &request)
	{
		if (request.getDays() <= 3)
		{
			cout << "Minister " << _name << " approve your " << request.getDays() << " days for " << request.getType() << " request !" << endl;
		}
		else
		{
			if (NULL_POINTER(_handler))
			{
				cout << "No holiday handler is assigned !" << endl;
			}
			else
			{
				_handler->HandleHolidayRequest(request);
			}

		}
	}
};

// Director Handler
class Director : public HoliadyHandler
{
private:
	string _name;
public:
	Director(string name) : _name(name) {};
public:
	void HandleHolidayRequest(HolidayRequest &request)
	{
		if (request.getDays() > 3)
		{
			cout << "Director " << _name << " approve your " << request.getDays() << " days for " << request.getType() <<  " request !" << endl;
		}
		else
		{
			if (NULL_POINTER(_handler))
			{
				cout << "No holiday handler is assigned !" << endl;
			}
			else
			{
				_handler->HandleHolidayRequest(request);
			}

		}
	}
};

void ResponseTest_Holiday()
{
	// 请求处理者
	HoliadyHandler *pD = new Director("john");
	HoliadyHandler *pM = new Minister("bob");
	HoliadyHandler *pS = new SectionChief("bill");

	//设置责任链
	pS->setHandler(pM);
	pM->setHandler(pD);
	pD->setHandler(NULL);

	// 请求
	HolidayRequest request1("dragon boat festival", 1);
	HolidayRequest request2("mid-autumn festival", 2);
	HolidayRequest request3("spring festival", 3);
	HolidayRequest request4("spring festival", 4);

	//处理请求
	pS->HandleHolidayRequest(request1);
	pS->HandleHolidayRequest(request2);
	pS->HandleHolidayRequest(request3);
	pS->HandleHolidayRequest(request4);

	SAFE_RELASE_POINTER(pD);
	SAFE_RELASE_POINTER(pM);
	SAFE_RELASE_POINTER(pS);
}


void ResponseTest_Manager()
{
	Manager *pGM = new GeneralManager(NULL);
	Manager *pMD = new Majordomo(pGM);
	Manager *pCM = new CommonManager(pMD);

	pCM->DealSalaryRequest(200);
	pCM->DealSalaryRequest(400);
	pCM->DealSalaryRequest(600);
	pCM->DealSalaryRequest(1200);

	SAFE_RELASE_POINTER(pGM);
	SAFE_RELASE_POINTER(pMD);
	SAFE_RELASE_POINTER(pCM);
}

void ResponseTest()
{
	cout << "*********** ResponseTest_General: *************" << endl;
	ResponseTest_General();
	cout << "*********** ResponseTest_Manager: *************" << endl;
	ResponseTest_Manager();
	cout << "*********** ResponseTest_Holiday: *************" << endl;
	ResponseTest_Holiday();
}
#endif