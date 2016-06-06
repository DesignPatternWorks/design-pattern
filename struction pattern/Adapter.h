#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#include "common.h"
//������ģʽ
/*
��Ҫ�ԣ�
��һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿڡ�
������ģʽʹ��ԭ�����ڽӿڲ����ݶ�����һ��������Щ�����һ������
�ñ��ձ����ھ�ֻ�ṩ110V�ĵ�ѹ�����ҵĵ��Ծ���Ҫ220V�ĵ�ѹ������ô������
���������Ǹ����ģ��ڲ����ݵĶ���֮��һ���������ö����ܺܺõļ�����һ����

�ŵ㣺
������ȥʵ��һ�����ܵ���Ѷȣ����Զ����е�����а�װ���Ϳ��Խ���ʹ���ˣ�
�������Ŀ���������е���һ�㶼�Ǿ������Եģ�ʹ����������ģʽ֮�󣬲���Ҫ�Ծɵ������ȫ��ĸ��ǲ��ԣ�
�ܵ���˵�������Ч�ʣ������˳ɱ�

���ϣ�
ʹ��һ���Ѿ����ڵ��࣬������Ľӿں���ʵ��Ҫ��Ĳ�һ��ʱ�����Կ���ʹ��������ģʽ��
Ҫ�ڵ����ߺ͹����ṩ��˫������̫�����޸ĵ�ʱ����ʹ��������ģʽ��������һ�в�ͬʱ��ʹ������
*/

/*
** FileName      : Adapter.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Adapter Pattern Implementation of C++
*/

// Class Adapter
class Target
{
public:
	virtual void Request()
	{
		cout << "Target Request" << endl;
	}
};

class Adaptee
{
public:
	void SpecialRequest()
	{
		cout << "Adaptee Special Request" << endl;
	}
};

class Adapter: public Target, public Adaptee
{
public:
	void Request()          // Override Target's Request()
	{
		SpecialRequest();
		cout << "Adapter Request" << endl;
	}
};

// Object Adapter
class Target_Obj
{
public:
	Target_Obj() {};
	virtual ~Target_Obj() {};
public:
	virtual void Request()
	{
		cout << "Target_Obj Request" << endl;
	}
};

class Adaptee_Obj
{
public:
	void SpecialRequest()
	{
		cout << "Adaptee_Obj Special Request" << endl;
	}
};

class Adapter_Obj: public Target_Obj
{
private:
	Adaptee_Obj *m_pAdaptee;
public:
	Adapter_Obj() 
	{
		m_pAdaptee = new Adaptee_Obj();
	}
	virtual ~Adapter_Obj()
	{
		if (NULL != m_pAdaptee)
		{
			delete m_pAdaptee;
			m_pAdaptee = NULL;
		}
	}
public:
	void Request()
	{
		if(NULL == m_pAdaptee)
		{
			cout << "new Adaptee Failed!" << endl;
			return;
		}
		m_pAdaptee->SpecialRequest();
		cout << "Adapter_Obj Request" << endl;
	}
};

void AdapterTest_General()
{
	// Class Adapter Test
	Target *pT = new Adapter();
	pT->Request();

	delete pT; pT = NULL;

	// Object Adapter Test
	Target_Obj *pTO = new Adapter_Obj();
	pTO->Request();

	delete pTO; pTO = NULL;	

}
//Example: STL �� Queue & Stack (Sequence)ʵ�֣�
// Target: Sequence 
// Adaptee: Deque
// Adapter: Queue & Stack

//˫�˶���
class Deque
{
public:
	void push_back(int x) { cout<<"Deque push_back"<<endl; }
	void push_front(int x) { cout<<"Deque push_front"<<endl; }
	void pop_back() { cout<<"Deque pop_back"<<endl; }
	void pop_front() { cout<<"Deque pop_front"<<endl; }
};

//˳������
class Sequence
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

//ջ
class Stack: public Sequence
{
public:
	void push(int x) 
	{ 
		deque.push_back(x); 
		cout << "Stack push" << endl;
	}
	void pop() 
	{
		deque.pop_back(); 
		cout << "Stack pop" << endl;
	}
private:
	Deque deque; //˫�˶���
};

//����
class Queue: public Sequence
{
public:
	void push(int x)
	{ 
		deque.push_back(x);
		cout << "Queue push" << endl;
	}
	void pop() 
	{
		deque.pop_front(); 
		cout << "Queue pop" << endl;
	}
private:
	Deque deque; //˫�˶���
};

// Adaptee socket
class USASocket
{
	// USA socket;
public:
	int provideUSAVolt(void)
	{
		return 110;
	}
};

// Target socket
class CHNSocket
{
	// China socket;
public:
	virtual int provideChinaVolt(void) = 0;
};

//  socket Adapter
class SocketAdapter : public CHNSocket
{
private:
	USASocket* _usaSocket;
public:
	SocketAdapter(USASocket *socket):_usaSocket(socket) {};
public:
	int provideChinaVolt(void)
	{
		if (NULL != _usaSocket)
		{
			return _usaSocket->provideUSAVolt() * 2; // convert usa volt ---> chn volt
		}
		return 0;
	}
};

void AdapterTest_Socket()
{
	// Socket Adapter Test:
	USASocket *s1 = new USASocket();
	SocketAdapter *s2 = new SocketAdapter(s1);

	cout << "before convert volt is: " << s1->provideUSAVolt()   << endl;
	cout << "after convert volt is: "  << s2->provideChinaVolt() << endl;
	delete s1; delete s2;
}

void AdapterTest_STL()
{
	// STL Sequence Obj Test
	Sequence *s1 = new Stack();
	Sequence *s2 = new Queue();
	s1->push(1); s1->pop();
	s2->push(1); s2->pop();
	delete s1; delete s2;
}

void AdapterTest()
{
	cout << "*********** AdapterTest_General: *************" << endl;
	AdapterTest_General();
	cout << "*********** AdapterTest_STL: *************" << endl;
	AdapterTest_STL();
	cout << "*********** AdapterTest_Socket: *************" << endl;
	AdapterTest_Socket();
}



/*  ������
���������������ص㣺
����Adapterֱ�Ӽ̳���Adaptee�࣬���ԣ���Adapter���п��Զ�Adaptee��ķ��������ض���
�����Adaptee�������һ�����󷽷�����ôAdapterҲҪ������Ӧ�ĸĶ��������ʹ��������
���Adaptee�����������࣬����Adapter�������Adaptee��������ķ���ʱ��ʹ�������������޷�������

�����������������ص㣺
�е�ʱ����ᷢ�֣����Ǻ�����ȥ����һ��Adaptee���͵Ķ���
��Adaptee������µĳ��󷽷�ʱ��Adapter�಻��Ҫ���κε�����Ҳ����ȷ�Ľ��ж���
����ʹ�ö�̬�ķ�ʽ��Adapter���е���Adaptee������ķ���
���ڶ�������������϶ȱȽϵͣ������ںܶ�����ж�����ʹ�ö�����������������ʵ����Ŀ�У�Ҳ����ˣ���ʹ�ö�����ϵķ�ʽ���Ͳ�ʹ�ö�̳еķ�ʽ
*/
#endif