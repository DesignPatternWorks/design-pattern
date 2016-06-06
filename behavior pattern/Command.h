#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "common.h"
#include <assert.h>
#include <stack>
#include <map>
#include <exception>

// ����ģʽ
/*
1�� ���
   ��һ�������װΪһ�����󣬴Ӷ�ʹ����ò�ͬ������Կͻ����в��������������Ŷӻ��¼������־���Լ�֧�ֿɳ����Ĳ���
   ��OOP�У�һ�ж��Ƕ��󣬽������װ�ɶ��󣬷���OOP�����˼��
   �����ͻ��ĵ��������װ�ɶ����Ժ����ǾͿ��Զ��������洢�������Ϣ��ʹ����ӵ�и��������
   ����ģʽͬ���ܹ����������ߺͽ����߽��ʹ��������߲���ȥ���������Ժ��ַ�ʽ������

2����ɫ��
Client������һ��ConcreteCommand������󣬲�ָ������Receiver����
Command������ִ�в����Ľӿڣ�
ConcreteCommand������һ�������ߺ���Ϊ֮�������ϣ���һ�������߶������һ��������֮�󣬵���Receiver��Ӧ�Ĳ�������ʵ��Execute�������Ӧ�����
Invoker��Ҫ�������ִ���������Invokerͨ������Command�����Execute�������ύһ������
         ���������������ǿ��Գ����ģ�ConcreteCommand��ִ��Execute����֮ǰ�洢��ǰ״̬������ȡ������������
Receiver��֪�����ʵʩ��ִ��һ��������صĲ������κ��඼������Ϊһ�������ߣ�ʵʩ��ִ������ķ��������ж�����

3���ص㣺
�� Commandģʽ�ĸ���Ŀ�����ڽ�����Ϊ�����ߡ��롰��Ϊʵ���ߡ������������������У�������ʵ���ֶ��ǡ�����Ϊ����Ϊ����
�� ʵ��Command�ӿڵľ����������ConcreteCommand��ʱ�������Ҫ���ܻᱣ��һЩ�����״̬��Ϣ
�� ͨ��ʹ��Compmositeģʽ�����Խ���������װΪһ�����������MacroCommand
�� Commandģʽ��C#�е�Delegate��Щ���ơ������߶�����Ϊ�ӿڵĹ淶��������Command����������еġ��ӿ�-ʵ�֡���������Ϊ�ӿڹ淶�����ϸ񣬸����ϳ���ԭ��
   Delegate�Ժ���ǩ����������Ϊ�ӿڹ淶�����������������Ƚ�����
�� ʹ������ģʽ�ᵼ��ĳЩϵͳ�й���ľ��������ࡣĳЩϵͳ������Ҫ��ʮ�������ٸ�������ǧ�����������࣬���ʹ����ģʽ��������ϵͳ���ò�ʵ�ʡ�

4��ʹ�ó���
�� ʹ������ģʽ��Ϊ"CallBack"���������ϵͳ�е������"CallBack"���ı����Ƚ�һ�������Ǽ��ϣ�Ȼ�����Ժ���ô˺���
�� ��Ҫ�ڲ�ͬ��ʱ��ָ�����󡢽������Ŷӡ�һ����������ԭ�ȵ����󷢳��߿����в�ͬ��������
   ����֮��ԭ�ȵ����󷢳��߿����Ѿ������ˣ��������������Ȼ�ǻ�ġ���ʱ����Ľ����߿������ڱ��أ�Ҳ���������������һ����ַ
   �����������ڴ��λ�֮���͵�����һ̨������ȥ
�� ϵͳ��Ҫ֧������ĳ���(undo)�����������԰�״̬�洢�������ȵ��ͻ�����Ҫ����������������Ч��ʱ�����Ե���undo()��������������������Ч����������
   ������󻹿����ṩredo()�������Թ��ͻ�������Ҫʱ��������ʵʩ����Ч����
�� ���һ��ϵͳҪ��ϵͳ�����е����ݸ��µ���־��Ա���ϵͳ����ʱ�����Ը�����־��������е����ݸ���������µ���Execute()����һ��һ��ִ����Щ����
   �Ӷ��ָ�ϵͳ�ڱ���ǰ���������ݸ���

*/
void CommandTest();

// Receiver ������ �������������ݵ�ʵ��
class Receiver
{
public:
	void Action()
	{
		cout << "Receiver: Action!" << endl;
	}
};

// Command �������� �����幫���ӿ�
class Command
{
public:
	virtual void Execute() = 0;
};

// ConcreteCommand ���������װ��һ��
class ConcreteCommand : public Command
{
private:
	Receiver *m_pReceiver;
public:
	ConcreteCommand(Receiver *prec) : m_pReceiver(prec) {};
public:
	void Execute()
	{
		m_pReceiver->Action();
	}
};

// Invoker ��������� ����������
class Invoker
{
private:
	Command *m_pCommand;
public:
	Invoker(Command *pcmd): m_pCommand(pcmd) {};
public:
	void Invoke()
	{
		m_pCommand->Execute();
	}
};

class CommandQueue
{
private:
	list<Command*> _listCommand;
public:
	void addCommand(Command &cmd)
	{
		_listCommand.push_back(&cmd);
	}
	void removeCommand(Command &cmd)
	{
		_listCommand.remove(&cmd);
	}
	void Execute()
	{
		for (list<Command*>::iterator it = _listCommand.begin();
			it!= _listCommand.end(); ++it)
		{
			(*it)->Execute();
		}
	}
};

class CommandQueueInvoker
{
private:
	CommandQueue *_commandQueue;
public:
	CommandQueueInvoker(CommandQueue &cmdQueue) :_commandQueue(&cmdQueue) {};
	void setCommandQueue(CommandQueue &cmdQueue)
	{
		_commandQueue = &cmdQueue;
	}
	void Invoke()
	{
		_commandQueue->Execute();
	}
};


void CommandTest_General()
{
	// ����ʵ��
	Receiver *pR = new Receiver();
	// ���� �м��
	Command  *pC = new ConcreteCommand(pR);
	// �������
	Invoker *pI  = new Invoker(pC);
	
	pI->Invoke();

	SAFE_RELASE_POINTER(pR);
	SAFE_RELASE_POINTER(pC);
	SAFE_RELASE_POINTER(pI);
}


// ���������ܵļ򵥼Ӽ��˳�������

// ��������ߣ������ҵ��ʵ���� Adder
class  Adder
{
public:
	float add(float leftOperand, float rightoperand)
	{
		cout << leftOperand << " add " << rightoperand << endl;
		return (leftOperand + rightoperand);
	}
};

// ��������ߣ������ҵ��ʵ���� Minuser
class Minuser
{
public:
	float minus(float leftOperand, float rightoperand)
	{
		cout << leftOperand << " minus " << rightoperand << endl;
		return (leftOperand - rightoperand);
	}
};

// ��������ߣ������ҵ��ʵ���� Multiplater
class Multiplater
{
public:
	float multiplate(float leftOperand, float rightoperand)
	{
		cout << leftOperand << " multiplate " << rightoperand << endl;
		return  (leftOperand * rightoperand);
	}
};

// ��������ߣ������ҵ��ʵ���� Diviser
class Diviser
{
public:
	float dive(float leftOperand, float rightoperand)
	{
		assert(0 != rightoperand);
		cout << leftOperand << " dive " << rightoperand << endl;
		return (leftOperand / rightoperand);
	}
};

// �����������ComputerCommand
class ComputerCommand
{
public:
	virtual float compute(float leftOperand, float rightOperand) = 0;
	virtual float unCompute(float leftOperand, float rightOperand) = 0;
// for Macro Command:
public:
	virtual void insertCommand(ComputerCommand *cmd) {};
	virtual void removeCommand(ComputerCommand *cmd) {};
	ComputerCommand* getCommand(int i) { return NULL; }
};

// ����add��������
class AddCommand : public ComputerCommand
{
private:
	Adder *_adder;
public:
	AddCommand(Adder *adder) : _adder(adder) {};
public:
	virtual float compute(float leftOperand, float rightOperand)
	{
		return  _adder->add(leftOperand, rightOperand);
	}
	virtual float unCompute(float leftOperand, float rightOperand)
	{
		return  _adder->add(leftOperand, -rightOperand);
	}
};

// ����minus��������
class MinusCommand : public ComputerCommand
{
private:
	Minuser *_minuser;
public:
	MinusCommand(Minuser *minuser) : _minuser(minuser) {};
public:
	virtual float compute(float leftOperand, float rightOperand)
	{
		return  _minuser->minus(leftOperand, rightOperand);
	}
	virtual float unCompute(float leftOperand, float rightOperand)
	{
		return  _minuser->minus(leftOperand, -rightOperand);
	}
};

// ����multiplate��������
class MultiplateCommand : public ComputerCommand
{
private:
	Multiplater *_multiplater;
public:
	MultiplateCommand(Multiplater *multiplater) : _multiplater(multiplater) {};
public:
	virtual float compute(float leftOperand, float rightOperand)
	{
		return _multiplater->multiplate(leftOperand, rightOperand);		 
	}
	virtual float unCompute(float leftOperand, float rightOperand)
	{
		return  _multiplater->multiplate(leftOperand, 1 / rightOperand);
	}
};

// ����dive��������
class DiveCommand : public ComputerCommand
{
private:
	Diviser *_diviser;
public:
	DiveCommand(Diviser *diviser) : _diviser(diviser) {};
public:
	virtual float compute(float leftOperand, float rightOperand)
	{
		return  _diviser->dive(leftOperand, rightOperand);
	}
	virtual float unCompute(float leftOperand, float rightOperand)
	{
		return _diviser->dive(leftOperand, 1/rightOperand);		
	}
};

// for MacroCommand
// �����㴦��������������������������ֲ���(+ - * /)����ĺ�
class MacroCommand : public ComputerCommand
{
private:
	vector<ComputerCommand*> _vecCmd;
public:
	MacroCommand() {};
public:
	void insertCommand(ComputerCommand *cmd)
	{
		_vecCmd.push_back(cmd);
	}
	void removeCommand(ComputerCommand *cmd)
	{
		for (vector<ComputerCommand*>::iterator it = _vecCmd.begin();
			 it != _vecCmd.end(); ++it)
		{
			if (*it == cmd)
			{
				_vecCmd.erase(it);
			}
		}
	}
	ComputerCommand* getCommand(int i)
	{
		assert(i < _vecCmd.size());
		return _vecCmd[i];
	};

	float compute(float leftOperand, float rightOperand)
	{
		float result = 0;
		for (vector<ComputerCommand*>::iterator it = _vecCmd.begin();
			it != _vecCmd.end(); ++it)
		{
			result += (*it)->compute(leftOperand, rightOperand);
		}
		return result;
	}

	float unCompute(float leftOperand, float rightOperand)
	{
		float result = 0;
		for (vector<ComputerCommand*>::iterator it = _vecCmd.begin();
			it != _vecCmd.end(); ++it)
		{
			result += (*it)->unCompute(leftOperand, rightOperand);
		}
		return result;
	}
};


class ComputerInvoker
{
private:
	ComputerCommand *_currentComputerCommand;  // ��ǰ����
	stack<ComputerCommand*> _stackUndoCommand; // ����������ջ(FILO)
	stack<ComputerCommand*> _stackRedoCommand; // �ָ�����������ջ(FILO)

	typedef struct tag_computeLog
	{
		//typedef float(*pComputeFunc)(float, float);
		//pComputeFunc compute;
		ComputerCommand* cmd;
		float leftOperand;
		float rightOperand;
	}computeLog;

	list<computeLog> _listComputeLogCommand; // ִ�в�����¼��list
	float _computeResult;        // ������
public:
	ComputerInvoker(ComputerCommand *cmd) : _currentComputerCommand(cmd), _computeResult(0) {};
public:
	void setComputerCommand(ComputerCommand *cmd)
	{
		_currentComputerCommand = cmd;
	}
	void invokeCompute(float operand) // ����˳�����
	{
		computeLog log;
		log.cmd = _currentComputerCommand;
		log.leftOperand = _computeResult;
		log.rightOperand = operand;
		_listComputeLogCommand.push_back(log);

		_computeResult = _currentComputerCommand->compute(_computeResult, operand); //ִ�� �������� 
		_stackUndoCommand.push(_currentComputerCommand);  // ѹ������������� ����������stack
		cout << "normal compute: result is : " << _computeResult << endl;
	}
	void invokeUncompute(float operand)  // ��������
	{	
		if (_stackUndoCommand.empty())
		{
			cout << "undo command stack is empty!" << endl;
			return;
		}
		_currentComputerCommand = _stackUndoCommand.top(); // ��ȡ ����������stack��Ԫ��
		_stackUndoCommand.pop();      // ���� ����������stack��Ԫ��
		_computeResult = _currentComputerCommand->unCompute(_computeResult, operand); //ִ�� ��������
		_stackRedoCommand.push(_currentComputerCommand); // ѹ�볷��������� �ָ�������stack
		cout << "undo compute: result is : " << _computeResult << endl;
	}
	void invokeRecompute(float operand) // �ָ���������
	{
		if (_stackRedoCommand.empty())
		{
			cout << "resume do command stack is empty!" << endl;
			return;
		}
		_currentComputerCommand = _stackRedoCommand.top();  // ��ȡ �ָ�����������stack��Ԫ��
		_stackRedoCommand.pop();  // ���� �ָ�����������stack��Ԫ��
		_computeResult = _currentComputerCommand->compute(_computeResult, operand); //ִ�� �ָ��������� 
		_stackUndoCommand.push(_currentComputerCommand); // ѹ��ָ������������ ����������stack
		cout << "redo compute: result is : " << _computeResult << endl;
	}
	void invokeLogCommand(void)
	{
		clearComputeResult();
		for (list<computeLog>::iterator it = _listComputeLogCommand.begin();
			it != _listComputeLogCommand.end(); ++it)
		{
			_computeResult =((*it).cmd->compute((*it).leftOperand, (*it).rightOperand));
		}
	}
	float getComputeResult(void)
	{
		return _computeResult;
	}
private:
	void clearComputeResult(void) // for exec log command
	{
		_computeResult = 0;
	}
};


void CommandTest_Compute()
{
	Adder *adder = new Adder();
	ComputerCommand *addCmd = new AddCommand(adder);
	Minuser *minuser = new Minuser();
	ComputerCommand *minusCmd = new MinusCommand(minuser);
	Multiplater *multiplater = new Multiplater();
	ComputerCommand *multiplateCmd = new MultiplateCommand(multiplater);
	Diviser *diviser = new Diviser();
	ComputerCommand *diveCmd = new DiveCommand(diviser);
	
	ComputerCommand *macroCmd = new MacroCommand();
	macroCmd->insertCommand(addCmd);
	macroCmd->insertCommand(minusCmd);
	macroCmd->insertCommand(multiplateCmd);
	macroCmd->insertCommand(diveCmd);


	ComputerInvoker *computeInvoke = new ComputerInvoker(addCmd); // ��ʼ��Ϊadd �� + 50
	computeInvoke->invokeCompute(50); // 0 + 50
	computeInvoke->setComputerCommand(minusCmd); // -20
	computeInvoke->invokeCompute(20); // (0 + 50) - 20 
	computeInvoke->setComputerCommand(multiplateCmd); // *3
	computeInvoke->invokeCompute(3); // (0 + 50 - 20) * 3
	computeInvoke->setComputerCommand(diveCmd); //  /9
	computeInvoke->invokeCompute(9); // (0 + 50 - 20) * 3 / 9
	computeInvoke->setComputerCommand(addCmd); //  + 10
	computeInvoke->invokeCompute(10); // (0 + 50 - 20) * 3 / 9 + 10 = 20

	computeInvoke->setComputerCommand(macroCmd); // �����㴦��
	computeInvoke->invokeCompute(2); // (20 + 2) + (20 - 2) + (20 * 2) + (20 / 2) = 90

	cout << "*** last normal compute result is : " << computeInvoke->getComputeResult() << " ***" << endl;

	computeInvoke->invokeLogCommand();
	cout << "*** invoke log command compute  result is " << computeInvoke->getComputeResult() << " ***" << endl;

	computeInvoke->invokeUncompute(2);  //  ���� 2��������
	computeInvoke->invokeUncompute(10); //  ���� +10
	computeInvoke->invokeUncompute(9);//   ���� /9
	computeInvoke->invokeUncompute(3); //   ���� *3
	computeInvoke->invokeUncompute(20); //  ���� -20
	computeInvoke->invokeUncompute(50); //  ���� +50

	cout << "*** last undo compute result is : " << computeInvoke->getComputeResult() << " ***" << endl;

	computeInvoke->invokeRecompute(50); //  �ָ����� +50
	computeInvoke->invokeRecompute(20); //  �ָ����� -20
	computeInvoke->invokeRecompute(3); //   �ָ����� *3
	computeInvoke->invokeRecompute(9); //   �ָ����� /9
	computeInvoke->invokeRecompute(10); //  �ָ����� +10
	computeInvoke->invokeRecompute(2);  //  �ָ����� 2��������

	cout << "*** last redo compute result is : " << computeInvoke->getComputeResult() << " ***" << endl;

	// ������
	float finalResult = computeInvoke->getComputeResult();
	cout << "*** final compute result is " << finalResult << " ***" << endl;

	SAFE_RELASE_POINTER(adder);
	SAFE_RELASE_POINTER(minuser);
	SAFE_RELASE_POINTER(multiplater);
	SAFE_RELASE_POINTER(diviser);

	SAFE_RELASE_POINTER(addCmd);
	SAFE_RELASE_POINTER(minusCmd);
	SAFE_RELASE_POINTER(multiplateCmd);
	SAFE_RELASE_POINTER(diveCmd);
	SAFE_RELASE_POINTER(macroCmd);

	SAFE_RELASE_POINTER(computeInvoke);
}
// ���Ӻ�����ܵļ�����


// �͹������Ա �г�ʦ ���ͻ���Ĳ�

// Cooker (Receiver)
class Cooker
{
public:
	void CookRice()
	{
		cout << "Cook Rice !!!" << endl;
	}
	void CookBeaf()
	{
		cout << "Cook Beaf !!!" << endl;
	}
};

// CookCommand (Commad)
class CookCommand
{
protected:
	Cooker *m_pCooker;
	string m_CmdName;
public:
	string GetName() {return m_CmdName;}
public:
	CookCommand(Cooker* pcooker, string name) : m_pCooker(pcooker), m_CmdName(name) {};
public:
	virtual void Execute() = 0;
};

// CookRiceCommand (ConcreteCommand 1)
class  CookRiceCommand : public CookCommand
{
public:
	CookRiceCommand(Cooker *pcooker, string name) : CookCommand(pcooker, name) {};
public:
	void Execute()
	{
	    cout << "Execute Command (" << m_CmdName <<" ):" << endl;
		m_pCooker->CookRice();  //  �̳е�m_pCooker
	}
};

// CookBeafCommand (ConcreteCommand 2)
class  CookBeafCommand : public CookCommand
{
public:
	CookBeafCommand(Cooker *pcooker, string name) : CookCommand(pcooker, name) {};
public:
	void Execute()
	{
		cout << "Execute Command (" << m_CmdName <<" ):" << endl;
		m_pCooker->CookBeaf();  //  �̳е�m_pCooker
	}
};

// Waiter (Invoker)
class Waiter
{
private:
	vector<CookCommand*> m_CookCommandVector;
public:
	void AddCommand(CookCommand *pCookCommand)
	{
		cout << "Add Command: " << pCookCommand->GetName() << endl;
		m_CookCommandVector.push_back(pCookCommand);
	}

	bool RemoveCommand(string CommandName)	
	{
		for (vector<CookCommand*>::iterator it = m_CookCommandVector.begin();
			it != m_CookCommandVector.end();
			++it)
		{
			if (CommandName == ((*it)->GetName()))
			{
				delete (*it);
				*it = NULL;
				m_CookCommandVector.erase(it);
			    cout << "Remove Command (" << CommandName <<" ):" << endl;
				return true;
			}
		}
	    cout << "Not Found Command (" << CommandName <<" ):" << endl;
		return false;
	}

	void RemoveAllCommand()
	{
		for (vector<CookCommand*>::iterator it = m_CookCommandVector.begin();
			 it != m_CookCommandVector.end();
			 ++it)
		{
			if (!NULL_POINTER(*it))
			{
				delete (*it);
				*it = NULL;
			}
		}
		m_CookCommandVector.clear();
	}

	void Notify()      // Invoke Command in Vector Sequencely
	{
		for (vector<CookCommand*>::iterator it = m_CookCommandVector.begin();
			it != m_CookCommandVector.end();
			++it)
		{
			if (!NULL_POINTER(*it))
			{
				(*it)->Execute();
			}
		}
	}
};

void CommandTest_Cook()
{
	//ʵ����
	Cooker *pC = new Cooker();

	//����
	CookCommand *pCRC = new CookRiceCommand(pC, "COOK RICE CMD");
	CookCommand *pCBC = new CookBeafCommand(pC, "COOK BEAF CMD");

	// ������
	Waiter *pW = new Waiter();

	// �����������ߵ�����������
	pW->AddCommand(pCRC);
	pW->AddCommand(pCBC);

	// �������������е�����
	pW->Notify();

	// ɾ��ָ��������ٵ������������е�����
	pW->RemoveCommand("COOK RICE CMD");
	pW->Notify();

	// �ͷŶ���
	pW->RemoveAllCommand();
	SAFE_RELASE_POINTER(pC);
	SAFE_RELASE_POINTER(pW);
}

// receiver

class Document
{
private:
	string _name;
public:
	Document(string name) :_name(name) {};
public:
	void open(void)
	{
		cout << "open document " << _name << endl;
	}
	void edit(void)
	{
		cout << "edit document " << _name << endl;
	}
	void save(void)
	{
		cout << "save document " << _name << endl;
	}
	void close(void)
	{
		cout << "close document " << _name << endl;
	}
	void unedit(void)
	{
		cout << "unedit document " << _name << endl;
	}
	void unsave(void)
	{
		cout << "unsave document " << _name << endl;
	}
	string getName(void)
	{
		return _name;
	}
};

class Application
{
private:
	list<Document*> _listDoc;
	string _appName;
public:
	Application(string name): _appName(name) {};
	virtual ~Application() 
	{
		for (list<Document*>::iterator it = _listDoc.begin();
			it != _listDoc.end(); ++it)
		{
			delete *it;
			*it = NULL;
		}
	}
public:
	bool isExitDocByName(string name)
	{
		for (list<Document*>::iterator it = _listDoc.begin();
			 it != _listDoc.end(); ++it)
		{
			if (0 == ((*it)->getName().compare(name)))
			{
				return true;
			}
		}
		return false;
	}

	Document* getDocByName(string name)
	{
		for (list<Document*>::iterator it = _listDoc.begin();
			it != _listDoc.end(); ++it)
		{
			if (0 == ((*it)->getName().compare(name)))
			{
				return *it;
			}
		}

		// if not exit , new one & add & return it
		Document *doc = new Document(name);
		addDoc(doc);
		return doc;
	}
	string getName(void)
	{
		return _appName;
	}
private:
	void addDoc(Document* doc)
	{
		_listDoc.push_back(doc);
	}

};


// command
class DocCommand
{
public:
	DocCommand() {};
	virtual ~DocCommand() {};
public:
	virtual void execute(void) = 0;
	virtual void unexecute(void) = 0;
	virtual void addDocCommand(DocCommand* doc) {};
	virtual void removeDocCommand(DocCommand* doc) {};
	virtual Document* getCurrentOpenDoc(void) { return NULL; }
};

class OpenDocCommand : public DocCommand
{
public:
	OpenDocCommand(Application *app) : _app(app), _currentOpenDoc(NULL), _response("") {};
public:
	void execute(void)
	{
		askUser();
		if (!_response.empty())
		{
			_currentOpenDoc = _app->getDocByName(_response);
			if (NULL != _currentOpenDoc)
			{
				_currentOpenDoc->open();
			}
		}
	}
	void unexecute(void)
	{
		cout << "can not unexecute open operate!!!" << endl;
	}

private:
	void askUser() 
	{
		char confirm;
		cout << "please input a name for the doc: " << endl;
		cin  >> _response;
		cout << "you have enter a doc named: " << _response << endl;
		cout << "confirm? (Y/N)" << endl;
		cin  >> confirm;
		switch (confirm)
		{
			case 'y':
			case 'Y':
				break;
			case 'N':
			case 'n':
			default:
				_response = "";
				break;
		}
	};
public:
	Document* getCurrentOpenDoc(void)
	{
		return _currentOpenDoc;
	}
private:
	Application *_app;
	Document *_currentOpenDoc;
	string _response;
};

class EditDocCommand : public DocCommand
{
public:
	EditDocCommand(Document* doc) : _doc(doc) {};
public:
	void execute(void)
	{
		if (NULL != _doc)
		{
			_doc->edit();
		}
	}
	void unexecute(void)
	{
		if (NULL != _doc)
		{
			_doc->unedit();
		}
	}
	Document* getCurrentOpenDoc(void)
	{
		return _doc;
	}
private:
	Document *_doc;
};


class SaveDocCommand : public DocCommand
{
public:
	SaveDocCommand(Document* doc) : _doc(doc) {};
public:
	void execute(void)
	{
		if (NULL != _doc)
		{
			_doc->save();
		}
	}
	void unexecute(void)
	{
		if (NULL != _doc)
		{
			_doc->unsave();
		}
	}
	Document* getCurrentOpenDoc(void)
	{
		return _doc;
	}
private:
	Document *_doc;
};

class CloseDocCommand : public DocCommand
{
public:
	CloseDocCommand(Document* doc) : _doc(doc) {};
public:
	void execute(void)
	{
		if (NULL != _doc)
		{
			_doc->close();
		}
	}
	void unexecute(void)
	{
		cout << "can not unexecute close operate!!!" << endl;
	}
	Document* getCurrentOpenDoc(void)
	{
		return _doc;
	}
private:
	Document *_doc;
};

class MacroDocCommand : public DocCommand
{
public:
	MacroDocCommand() {};
public:
	void execute(void)
	{
		for (list<DocCommand*>::iterator it = _listDoc.begin();
			it != _listDoc.end(); ++it)
		{
			(*it)->execute();
		}
	}
	void unexecute(void)
	{
		for (list<DocCommand*>::iterator it = _listDoc.begin();
			it != _listDoc.end(); ++it)
		{
			(*it)->unexecute();
		}
	}
public:
	void addDocCommand(DocCommand* doc)
	{
		_listDoc.push_back(doc);
	}
	void removeDocCommand(DocCommand* doc)
	{
		_listDoc.remove(doc);
	}
private:
	list<DocCommand*> _listDoc;
};

// invoker
class Writer
{
public:
	Writer(string name) : _name(name) {};
	virtual ~Writer()
	{
		for (list<DocCommandLog*>::iterator it = _listHistoryCmdLog.begin();
			it != _listHistoryCmdLog.end(); ++it)
		{
			delete *it;
			*it = NULL;
		}
	}
public:
	class DocCommandLog
	{
	public:
		DocCommand *docCmd;
		bool isexecute;
	};

	void setDocCommand(DocCommand *cmd)
	{
		_currentCmd = cmd;
	}
	void doWork(void)
	{
		_currentCmd->execute();

		DocCommandLog *cmdLog = new DocCommandLog();
		cmdLog->docCmd = _currentCmd;
		cmdLog->isexecute = true;
		_listHistoryCmdLog.push_back(cmdLog);
	}
	void undoWork(void)
	{
		_currentCmd->unexecute();

		DocCommandLog *cmdLog = new DocCommandLog();
		cmdLog->docCmd = _currentCmd;
		cmdLog->isexecute = false;
		_listHistoryCmdLog.push_back(cmdLog);
	}
	void batWorkByHistoryCmdLog(void)
	{
		for (list<DocCommandLog*>::iterator it = _listHistoryCmdLog.begin();
			it != _listHistoryCmdLog.end(); ++it)
		{
			if ((*it)->isexecute)
			{
				(*it)->docCmd->execute();
			}
			else
			{
				(*it)->docCmd->unexecute();
			}
		}
	}
public:
	string getName(void)
	{
		return _name;
	}
private:
	string _name;
	DocCommand *_currentCmd;
	list<DocCommandLog*> _listHistoryCmdLog;
};


void CommandTest_Doc()
{
	Application *app = new Application("VS 2015");
	cout << "app name is : " << app->getName() << endl;
	Writer *writer = new Writer("tly");
	cout << "writer name is: " << writer->getName() << endl;
	
	// 1. open doc
	DocCommand *openCmd = new OpenDocCommand(app);
	writer->setDocCommand(openCmd);
	writer->doWork();

	Document *currentOpenDoc = openCmd->getCurrentOpenDoc();

	if (NULL == currentOpenDoc)
	{
		cout << "not open any doc !!!" << endl;
		SAFE_RELASE_POINTER(openCmd);
		SAFE_RELASE_POINTER(writer);
		SAFE_RELASE_POINTER(app);
		return;
	}
	// 2. edit doc
	DocCommand *editCmd = new EditDocCommand(currentOpenDoc);
	writer->setDocCommand(editCmd);
	writer->doWork();
	// 3. unedit doc
	writer->undoWork();

	// 4. save & close doc
	DocCommand *macroCmd = new MacroDocCommand();
	DocCommand *saveCmd = new SaveDocCommand(currentOpenDoc);
	macroCmd->addDocCommand(saveCmd);
	DocCommand *closeCmd = new CloseDocCommand(currentOpenDoc);
	macroCmd->addDocCommand(closeCmd);
	writer->setDocCommand(macroCmd);
	writer->doWork();

	// 5. bat just doc operate:
	cout << "bat history log: " << endl;
	writer->batWorkByHistoryCmdLog();

	SAFE_RELASE_POINTER(openCmd);
	SAFE_RELASE_POINTER(editCmd);
	SAFE_RELASE_POINTER(saveCmd);
	SAFE_RELASE_POINTER(closeCmd);
	SAFE_RELASE_POINTER(macroCmd);
	SAFE_RELASE_POINTER(writer);
	SAFE_RELASE_POINTER(app);
}
void CommandTest()
{
	cout << "*********** CommandTest_General: *************" << endl;
	CommandTest_General();
	cout << "*********** CommandTest_Cook: *************" << endl;
	CommandTest_Cook();
	cout << "*********** CommandTest_Compute: *************" << endl;
	CommandTest_Compute();
	cout << "*********** CommandTest_Doc: *************" << endl;
	CommandTest_Doc();
}

#endif