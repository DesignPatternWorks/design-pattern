#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "common.h"
#include <assert.h>
#include <stack>
#include <map>
#include <exception>

// 命令模式
/*
1、 概念：
   将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤消的操作
   在OOP中，一切都是对象，将请求封装成对象，符合OOP的设计思想
   当将客户的单个请求封装成对象以后，我们就可以对这个请求存储更多的信息，使请求拥有更多的能力
   命令模式同样能够把请求发送者和接收者解耦，使得命令发送者不用去关心请求将以何种方式被处理

2、角色：
Client：创建一个ConcreteCommand命令对象，并指定它的Receiver对象；
Command：声明执行操作的接口；
ConcreteCommand：定义一个接受者和行为之间的弱耦合；将一个接收者对象绑定于一个动作，之后，调用Receiver相应的操作，以实现Execute来完成相应的命令；
Invoker：要求该命令执行这个请求；Invoker通过调用Command对象的Execute操作来提交一个请求。
         如果这个命令请求是可以撤销的，ConcreteCommand就执行Execute操作之前存储当前状态以用于取消该命令请求
Receiver：知道如何实施与执行一个请求相关的操作，任何类都可能作为一个接收者，实施和执行请求的方法叫做行动方法

3、特点：
① Command模式的根本目的在于将“行为请求者”与“行为实现者”解耦，在面向对象语言中，常见的实现手段是“将行为抽象为对象”
② 实现Command接口的具体命令对象ConcreteCommand有时候根据需要可能会保存一些额外的状态信息
③ 通过使用Compmosite模式，可以将多个命令封装为一个“复合命令”MacroCommand
④ Command模式与C#中的Delegate有些类似。但两者定义行为接口的规范有所区别：Command以面向对象中的“接口-实现”来定义行为接口规范，更严格，更符合抽象原则
   Delegate以函数签名来定义行为接口规范，更灵活，但抽象能力比较弱。
⑤ 使用命令模式会导致某些系统有过多的具体命令类。某些系统可能需要几十个，几百个甚至几千个具体命令类，这会使命令模式在这样的系统里变得不实际。

4、使用场合
① 使用命令模式作为"CallBack"在面向对象系统中的替代。"CallBack"讲的便是先将一个函数登记上，然后在以后调用此函数
② 需要在不同的时间指定请求、将请求排队。一个命令对象和原先的请求发出者可以有不同的生命期
   换言之，原先的请求发出者可能已经不在了，而命令对象本身仍然是活动的。这时命令的接收者可以是在本地，也可以在网络的另外一个地址
   命令对象可以在串形化之后传送到另外一台机器上去
③ 系统需要支持命令的撤消(undo)。命令对象可以把状态存储起来，等到客户端需要撤销命令所产生的效果时，可以调用undo()方法，把命令所产生的效果撤销掉。
   命令对象还可以提供redo()方法，以供客户端在需要时，再重新实施命令效果。
④ 如果一个系统要将系统中所有的数据更新到日志里，以便在系统崩溃时，可以根据日志里读回所有的数据更新命令，重新调用Execute()方法一条一条执行这些命令
   从而恢复系统在崩溃前所做的数据更新

*/
void CommandTest();

// Receiver 接收者 ：具体命令内容的实现
class Receiver
{
public:
	void Action()
	{
		cout << "Receiver: Action!" << endl;
	}
};

// Command 抽象命令 ：定义公共接口
class Command
{
public:
	virtual void Execute() = 0;
};

// ConcreteCommand 具体命令：封装的一层
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

// Invoker 命令调用者 ：调用命令
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
	// 命令实现
	Receiver *pR = new Receiver();
	// 命令 中间层
	Command  *pC = new ConcreteCommand(pR);
	// 命令调用
	Invoker *pI  = new Invoker(pC);
	
	pI->Invoke();

	SAFE_RELASE_POINTER(pR);
	SAFE_RELASE_POINTER(pC);
	SAFE_RELASE_POINTER(pI);
}


// 带撤销功能的简单加减乘除计算器

// 命令接受者，具体的业务实现者 Adder
class  Adder
{
public:
	float add(float leftOperand, float rightoperand)
	{
		cout << leftOperand << " add " << rightoperand << endl;
		return (leftOperand + rightoperand);
	}
};

// 命令接受者，具体的业务实现者 Minuser
class Minuser
{
public:
	float minus(float leftOperand, float rightoperand)
	{
		cout << leftOperand << " minus " << rightoperand << endl;
		return (leftOperand - rightoperand);
	}
};

// 命令接受者，具体的业务实现者 Multiplater
class Multiplater
{
public:
	float multiplate(float leftOperand, float rightoperand)
	{
		cout << leftOperand << " multiplate " << rightoperand << endl;
		return  (leftOperand * rightoperand);
	}
};

// 命令接受者，具体的业务实现者 Diviser
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

// 抽象计算命令ComputerCommand
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

// 具体add计算命令
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

// 具体minus计算命令
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

// 具体multiplate计算命令
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

// 具体dive计算命令
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
// 批计算处理：计算给定的两个操作数的四种操作(+ - * /)结果的和
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
	ComputerCommand *_currentComputerCommand;  // 当前操作
	stack<ComputerCommand*> _stackUndoCommand; // 撤销操作堆栈(FILO)
	stack<ComputerCommand*> _stackRedoCommand; // 恢复撤销操作堆栈(FILO)

	typedef struct tag_computeLog
	{
		//typedef float(*pComputeFunc)(float, float);
		//pComputeFunc compute;
		ComputerCommand* cmd;
		float leftOperand;
		float rightOperand;
	}computeLog;

	list<computeLog> _listComputeLogCommand; // 执行操作记录的list
	float _computeResult;        // 计算结果
public:
	ComputerInvoker(ComputerCommand *cmd) : _currentComputerCommand(cmd), _computeResult(0) {};
public:
	void setComputerCommand(ComputerCommand *cmd)
	{
		_currentComputerCommand = cmd;
	}
	void invokeCompute(float operand) // 正常顺序操作
	{
		computeLog log;
		log.cmd = _currentComputerCommand;
		log.leftOperand = _computeResult;
		log.rightOperand = operand;
		_listComputeLogCommand.push_back(log);

		_computeResult = _currentComputerCommand->compute(_computeResult, operand); //执行 正常操作 
		_stackUndoCommand.push(_currentComputerCommand);  // 压入正常操作命令到 撤销操作的stack
		cout << "normal compute: result is : " << _computeResult << endl;
	}
	void invokeUncompute(float operand)  // 撤销操作
	{	
		if (_stackUndoCommand.empty())
		{
			cout << "undo command stack is empty!" << endl;
			return;
		}
		_currentComputerCommand = _stackUndoCommand.top(); // 先取 撤销操作的stack顶元素
		_stackUndoCommand.pop();      // 弹出 撤销操作的stack顶元素
		_computeResult = _currentComputerCommand->unCompute(_computeResult, operand); //执行 撤销操作
		_stackRedoCommand.push(_currentComputerCommand); // 压入撤销操作命令到 恢复操作的stack
		cout << "undo compute: result is : " << _computeResult << endl;
	}
	void invokeRecompute(float operand) // 恢复撤销操作
	{
		if (_stackRedoCommand.empty())
		{
			cout << "resume do command stack is empty!" << endl;
			return;
		}
		_currentComputerCommand = _stackRedoCommand.top();  // 先取 恢复撤销操作的stack顶元素
		_stackRedoCommand.pop();  // 弹出 恢复撤销操作的stack顶元素
		_computeResult = _currentComputerCommand->compute(_computeResult, operand); //执行 恢复撤销操作 
		_stackUndoCommand.push(_currentComputerCommand); // 压入恢复撤销操作命令到 撤销操作的stack
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


	ComputerInvoker *computeInvoke = new ComputerInvoker(addCmd); // 初始化为add 且 + 50
	computeInvoke->invokeCompute(50); // 0 + 50
	computeInvoke->setComputerCommand(minusCmd); // -20
	computeInvoke->invokeCompute(20); // (0 + 50) - 20 
	computeInvoke->setComputerCommand(multiplateCmd); // *3
	computeInvoke->invokeCompute(3); // (0 + 50 - 20) * 3
	computeInvoke->setComputerCommand(diveCmd); //  /9
	computeInvoke->invokeCompute(9); // (0 + 50 - 20) * 3 / 9
	computeInvoke->setComputerCommand(addCmd); //  + 10
	computeInvoke->invokeCompute(10); // (0 + 50 - 20) * 3 / 9 + 10 = 20

	computeInvoke->setComputerCommand(macroCmd); // 批计算处理
	computeInvoke->invokeCompute(2); // (20 + 2) + (20 - 2) + (20 * 2) + (20 / 2) = 90

	cout << "*** last normal compute result is : " << computeInvoke->getComputeResult() << " ***" << endl;

	computeInvoke->invokeLogCommand();
	cout << "*** invoke log command compute  result is " << computeInvoke->getComputeResult() << " ***" << endl;

	computeInvoke->invokeUncompute(2);  //  撤销 2的批处理
	computeInvoke->invokeUncompute(10); //  撤销 +10
	computeInvoke->invokeUncompute(9);//   撤销 /9
	computeInvoke->invokeUncompute(3); //   撤销 *3
	computeInvoke->invokeUncompute(20); //  撤销 -20
	computeInvoke->invokeUncompute(50); //  撤销 +50

	cout << "*** last undo compute result is : " << computeInvoke->getComputeResult() << " ***" << endl;

	computeInvoke->invokeRecompute(50); //  恢复撤销 +50
	computeInvoke->invokeRecompute(20); //  恢复撤销 -20
	computeInvoke->invokeRecompute(3); //   恢复撤销 *3
	computeInvoke->invokeRecompute(9); //   恢复撤销 /9
	computeInvoke->invokeRecompute(10); //  恢复撤销 +10
	computeInvoke->invokeRecompute(2);  //  恢复撤销 2的批处理

	cout << "*** last redo compute result is : " << computeInvoke->getComputeResult() << " ***" << endl;

	// 输出结果
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
// 增加宏命令功能的计算器


// 餐馆里服务员 叫厨师 做客户点的菜

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
		m_pCooker->CookRice();  //  继承的m_pCooker
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
		m_pCooker->CookBeaf();  //  继承的m_pCooker
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
	//实现者
	Cooker *pC = new Cooker();

	//命令
	CookCommand *pCRC = new CookRiceCommand(pC, "COOK RICE CMD");
	CookCommand *pCBC = new CookBeafCommand(pC, "COOK BEAF CMD");

	// 调用者
	Waiter *pW = new Waiter();

	// 添加命令到调用者的命令序列中
	pW->AddCommand(pCRC);
	pW->AddCommand(pCBC);

	// 调用命令序列中的命令
	pW->Notify();

	// 删除指定的命令，再调用命令序列中的命令
	pW->RemoveCommand("COOK RICE CMD");
	pW->Notify();

	// 释放对象
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