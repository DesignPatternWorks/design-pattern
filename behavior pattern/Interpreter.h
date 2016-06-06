#ifndef  _INTERPRETER_H_
#define  _INTERPRETER_H_

#include "common.h"
#include <stack>
#include <memory>

// 解释器模式

/*
1、 概念：给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子

    除了使用文法规则来定义一个语言，在解释器模式中还可以通过一种称之为抽象语法树的图形方式来直观地表示语言的构成
	可以通过终结符表达式和非终结符表达式组成复杂的语句，每个文法规则的语言实例都可以表示为一个抽象语法树，
	就是说每一条具体的语句都可以用类似抽象语法树来表示，在图中终结符表达式类的实例作为树的叶子节点，而非终结符表达式类的实例作为非叶子节点

2、 角色：
    AbstractExpression：声明一个所有具体表达式都要实现的抽象接口（或者抽象类），接口中主要是一个interpret()方法，称为解释操作。
		具体解释任务由它的各个实现类来完成，具体的解释器分别由终结符解释器TerminalExpression和非终结符解释器NonterminalExpression完成。
    TerminalExpression：实现与文法中的元素相关联的解释操作，通常一个解释器模式中只有一个终结符表达式，但有多个实例，对应不同的终结符。
		终结符一半是文法中的运算单元，比如有一个简单的公式R=R1+R2，在里面R1和R2就是终结符，对应的解析R1和R2的解释器就是终结符表达式。                                
	NonterminalExpression：文法中的每条规则对应于一个非终结符表达式，非终结符表达式一般是文法中的运算符或者其他关键字，比如公式R=R1+R2中，+就是非终结符
		解析+的解释器就是一个非终结符表达式。非终结符表达式根据逻辑的复杂程度而增加，原则上每个文法规则都对应一个非终结符表达式。
	Context：这个角色的任务一般是用来存放文法中各个终结符所对应的具体值，比如R=R1+R2，我们给R1赋值100，给R2赋值200。
		这些信息需要存放到环境角色中，很多情况下我们使用Map来充当环境角色就足够了。

3、场合：
①	有一个简单的语法规则，比如一个sql语句，如果我们需要根据sql语句进行rm转换，就可以使用解释器模式来对语句进行解释。
②	一些重复发生的问题，比如加减乘除四则运算，但是公式每次都不同，有时是a+b-c*d，有时是a*b+c-d，等等等等个，公式千变万化，
	但是都是由加减乘除四个非终结符来连接的，这时我们就可以使用解释器模式。

4、优缺点：
①	解释器是一个简单的语法分析工具，它最显著的优点就是扩展性，修改语法规则只需要修改相应的非终结符就可以了，若扩展语法，只需要增加非终结符类就可以了。
②	但是，解释器模式会引起类的膨胀，每个语法都需要产生一个非终结符表达式，语法规则比较复杂时，就可能产生大量的类文件，为维护带来非常多的麻烦。
	同时，由于采用递归调用方法，每个非终结符表达式只关心与自己相关的表达式，每个表达式需要知道最终的结果，必须通过递归方式，
	无论是面向对象的语言还是面向过程的语言，递归都是一个不推荐的方式。由于使用了大量的循环和递归，效率是一个不容忽视的问题。
	特别是用于解释一个解析复杂、冗长的语法时，效率是难以忍受的
*/
void InterpreterTest();

// Context
class Context
{
private:
	map<string, int> m_mapValue;
public:
	void AddValue(string key, int value)
	{
		m_mapValue.insert(make_pair(key, value));
	}
	int GetValue(string key)
	{
		return m_mapValue[key];
	}
};


// Abstract Expression
class AbstractExpression
{
public:
	virtual int Interpreter(Context ctx) = 0;
};

// Terminal Expression
class TerminalExpression : public AbstractExpression
{
private:
	int m_Value;
public:
	TerminalExpression(int value) : m_Value(value) {};
public:
	virtual int Interpreter(Context ctx)
	{
		return m_Value;
	}
};

// NonTerminal Expression 1: Sub ('-')
class SubNonterminalExpression : public AbstractExpression // 默认是私有继承
{
private:
	AbstractExpression *m_pLeftExpr;
	AbstractExpression *m_pRightExpr;
public:
	SubNonterminalExpression(AbstractExpression *pLeft, AbstractExpression *pRight) : m_pLeftExpr(pLeft), m_pRightExpr(pRight) {};
public:
	virtual int Interpreter(Context ctx)
	{
		return m_pLeftExpr->Interpreter(ctx) - m_pRightExpr->Interpreter(ctx);
	}
};

// NonTerminal Expression 2: Plus ('+')
class PlusNonterminalExpression : public AbstractExpression 
{
private:
	AbstractExpression *m_pLeftExpr;
	AbstractExpression *m_pRightExpr;
public:
	PlusNonterminalExpression(AbstractExpression *pLeft, AbstractExpression *pRight) : m_pLeftExpr(pLeft), m_pRightExpr(pRight) {};
public:
	virtual int Interpreter(Context ctx)
	{
		return m_pLeftExpr->Interpreter(ctx) + m_pRightExpr->Interpreter(ctx);
	}
};

void InterpreterTest_Computaion()
{
	Context ctx;
	ctx.AddValue("x", 5);
	ctx.AddValue("y", 8);
	ctx.AddValue("z", 7);
    
	// Create Terminal Expression 
	AbstractExpression *pTE1 = new TerminalExpression(ctx.GetValue("x"));
	AbstractExpression *pTE2 = new TerminalExpression(ctx.GetValue("y"));
	AbstractExpression *pTE3 = new TerminalExpression(ctx.GetValue("z"));

	AbstractExpression *pPNE = new PlusNonterminalExpression(pTE1, pTE2); //pPNE： PTE1->Interpreter() + pTE2->Intepreter()
	AbstractExpression *pSNE = new SubNonterminalExpression(pPNE, pTE3); // pSNE： PNE->Interpreter() - pTE3->Intepreter()
	AbstractExpression *pPNE2 = new PlusNonterminalExpression(pSNE, pPNE); //pPNE2: PSNE->Interpreter() + pPNE->Intepreter()

	cout << "The Final Result of Express : x(5) + y(8) is " << pPNE->Interpreter(ctx) << endl;
	cout << "The Final Result of Express : x(5) + y(8) - z(7)  is " << pSNE->Interpreter(ctx) << endl;
	cout << "The Final Result of Express : x(5) + y(8) - z(7) + x(5) + y(8) is " << pPNE2->Interpreter(ctx) << endl;

	SAFE_RELASE_POINTER(pTE1);
	SAFE_RELASE_POINTER(pTE2);
	SAFE_RELASE_POINTER(pTE3);
	SAFE_RELASE_POINTER(pPNE);
	SAFE_RELASE_POINTER(pSNE);
	SAFE_RELASE_POINTER(pPNE2);
}



/*
 *	down move 5
 */
void stringSplit(string &src, string &delim, vector<string>& des)
{
	size_t last = 0;
	size_t pos = src.find_first_of(delim, last);
	while (pos != string::npos)
	{
		des.push_back(src.substr(last, pos-last));
		last = pos + 1;
		pos = src.find_first_of(delim, last);
	}
	// last token;
	des.push_back(src.substr(last, pos - last));
}

// abstract expr
class AbstractControlExpression
{
public:
	virtual string interpreter(void) = 0;
};

// 方向终结符表达式：把英文的方向解释为中文
class DirectionExpression : public AbstractControlExpression
{
public:
	DirectionExpression(string direction) : _direction(direction) {};
	string interpreter(void)
	{
		if (_direction.compare("up"))
		{
			return "向上";
		}
		else if (_direction.compare("down"))
		{
			return "向下";
		}
		else if (_direction.compare("left"))
		{
			return "向左";
		}
		else if (_direction.compare("right"))
		{
			return "向右";
		}
		else
		{
			return "无效的命令";
		}
	}
private:
	string _direction;
};

// 动作终结符表达式：把英文的动作解释为中文
class ActionExpression : public AbstractControlExpression
{
public:
	ActionExpression(string action) : _action(action) {};
	string interpreter(void)
	{
		if (_action.compare("run"))
		{
			return "快速移动";
		}
		else if (_action.compare("move"))
		{
			return "移动";
		}
		else
		{
			return "无效的命令";
		}
	}
private:
	string _action;
};

// 距离终结符表达式
class DistanceExpression : public AbstractControlExpression
{
public:
	DistanceExpression(string distance) : _distance(distance) {};
	string interpreter(void)
	{
		return _distance + "厘米";
	}
private:
	string _distance;
};

// 简单句子非终结符表达式
class SimpleSentenceExpression : public AbstractControlExpression
{
public:
	SimpleSentenceExpression(AbstractControlExpression *direction, AbstractControlExpression *action, AbstractControlExpression *distance):
		_direction(direction), _action(action), _distance(distance) {};
public:
	string interpreter(void)
	{
		return (_direction->interpreter() + _action->interpreter() + _distance->interpreter()); //调用终结符的interpreter
	}
private:
	AbstractControlExpression *_direction;
	AbstractControlExpression *_action;
	AbstractControlExpression *_distance;
};

// And句子非终结符表达式
class AndSentenceExpression : public AbstractControlExpression
{
public:
	AndSentenceExpression(AbstractControlExpression *leftSentence, AbstractControlExpression* rightSentence):
		_leftSentence(leftSentence), _rightSentence(rightSentence) {};
public:
	string interpreter(void)
	{
		return (_leftSentence->interpreter() + "并且" + _rightSentence->interpreter());
	}
private:
	AbstractControlExpression *_leftSentence;
	AbstractControlExpression *_rightSentence;
};

//Robot Control Test
void InterpreterTest_RobotControl(void)
{
	string finalRes;
	AbstractControlExpression *direction = new DirectionExpression("down");
	AbstractControlExpression *action = new ActionExpression("move");
	AbstractControlExpression *distance = new DistanceExpression("100");

	AbstractControlExpression *simple_sentence = new SimpleSentenceExpression(direction, action, distance);

	AbstractControlExpression *direction2 = new DirectionExpression("up");
	AbstractControlExpression *action2 = new ActionExpression("run");
	AbstractControlExpression *simple_sentence2 = new SimpleSentenceExpression(direction2, action2, distance);

	AbstractControlExpression *complex_sentence = new AndSentenceExpression(simple_sentence, simple_sentence2);
	finalRes = complex_sentence->interpreter();
	cout << finalRes << endl;

	SAFE_RELASE_POINTER(direction);
	SAFE_RELASE_POINTER(action);
	SAFE_RELASE_POINTER(distance);
	SAFE_RELASE_POINTER(simple_sentence);

	SAFE_RELASE_POINTER(direction2);
	SAFE_RELASE_POINTER(action2);
	SAFE_RELASE_POINTER(simple_sentence2);
	SAFE_RELASE_POINTER(complex_sentence);
}
void InterpreterTest()
{
	cout << "*********** InterpreterTest_Computaion: *************" << endl;
	InterpreterTest_Computaion();
	cout << "*********** InterpreterTest_RobotControl: *************" << endl;
	InterpreterTest_RobotControl();
}
#endif