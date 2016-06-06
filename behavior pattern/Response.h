#ifndef  _RESPONSE_H_
#define  _RESPONSE_H_

#include "common.h"


// ������ģʽ
/*
1�� ���
		ʹ��������л��ᴦ�����󣬴Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ������Щ��������һ������ֱ����һ����������Ϊֹ

2�� ��ɫ��
	Handler��������һ����������Ľӿڣ������������Ҫ������ͬ�����󣬿���ʵ�ָýӿھͺ��ˣ�
	ConcreteHandler�����������������������ɴ�������󣬾ʹ����������󣻷��򽫸�����ת����������һ�����Դ��������Ķ���
					�����������ܷ���������һ�����Դ���ͬ������Ķ���
	Client���������������������
	���ͻ��ύһ������ʱ����������һ�������ݣ�ֱ����һ��ConcreteHandler��������������

3�� ���ϣ�
	��  �ж���Ķ�����Դ���һ���������ĸ��������������������ʱ���Զ�ȷ����
	��  ������ڲ���ȷָ�������ߵ�����£����������е�һ���ύһ������
	��  ���Դ���һ������Ķ��󼯺�Ӧ����ָ̬��
	��  ����ʹ��if��else���������֯һ��������ʱ�е��������ģ����뿴��ȥ�����ʱ���Ϳ���ʹ��������ģʽ

4�� ��ȱ�㣺
	��  ������϶ȣ�ְ����ģʽʹ��һ��������֪������һ���������������󡣶������Ҫ֪��������ᱻ��ȷ�Ĵ���
		�����ߺͷ����߶�û�жԷ�����ȷ����Ϣ�������еĶ�����Ҫ֪�����Ľṹ
	��  ��ǿ�˸�����ָ��ְ�������ԣ����ڶ����з���ְ��ʱ��ְ�����������������
		�����ͨ��������ʱ�Ը������ж�̬�����ӻ��޸������ӻ�ı䴦��һ���������Щְ��
	��  ����֤�����ܣ���Ȼһ������û����ȷ�Ľ����ߣ���ô�Ͳ��ܱ�֤��һ���ᱻ�������������һֱ������ĩ�˶��ò�������
		һ������Ҳ���������û�б���ȷ���ö��ò�������
	��  ������ģʽ��if��else����ȣ����������Ҫ��һЩ����Ϊ���������ж�����ɢ���˸����������У�������Щ����������ȴ���˳����������趨
		������ģʽҲ��ȱ�㣬����if��else������ȱ����һ���ģ��Ǿ������ҵ���ȷ�Ĵ�����֮ǰ�����е��ж�������Ҫ��ִ��һ��
		���������Ƚϳ�ʱ����������Ƚ�����
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
		// >10 �������һ��ConcreteHandler����
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
		// >20 �������һ��ConcreteHandler����
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
		// >30 �������һ��ConcreteHandler����
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
	Handler *pCHA = new ConcreteHandlerA(pCHB); //ָ��ÿһ��Handler����һ��Handler 

	// ��Concrete Handler A ��ʼ���´���
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
	// ��������
	HoliadyHandler *pD = new Director("john");
	HoliadyHandler *pM = new Minister("bob");
	HoliadyHandler *pS = new SectionChief("bill");

	//����������
	pS->setHandler(pM);
	pM->setHandler(pD);
	pD->setHandler(NULL);

	// ����
	HolidayRequest request1("dragon boat festival", 1);
	HolidayRequest request2("mid-autumn festival", 2);
	HolidayRequest request3("spring festival", 3);
	HolidayRequest request4("spring festival", 4);

	//��������
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