#ifndef  _INTERPRETER_H_
#define  _INTERPRETER_H_

#include "common.h"
#include <stack>
#include <memory>

// ������ģʽ

/*
1�� �������һ�����ԣ����������ķ���һ�ֱ�ʾ��������һ�������������������ʹ�øñ�ʾ�����������еľ���

    ����ʹ���ķ�����������һ�����ԣ��ڽ�����ģʽ�л�����ͨ��һ�ֳ�֮Ϊ�����﷨����ͼ�η�ʽ��ֱ�۵ر�ʾ���ԵĹ���
	����ͨ���ս�����ʽ�ͷ��ս�����ʽ��ɸ��ӵ���䣬ÿ���ķ����������ʵ�������Ա�ʾΪһ�������﷨����
	����˵ÿһ���������䶼���������Ƴ����﷨������ʾ����ͼ���ս�����ʽ���ʵ����Ϊ����Ҷ�ӽڵ㣬�����ս�����ʽ���ʵ����Ϊ��Ҷ�ӽڵ�

2�� ��ɫ��
    AbstractExpression������һ�����о�����ʽ��Ҫʵ�ֵĳ���ӿڣ����߳����ࣩ���ӿ�����Ҫ��һ��interpret()��������Ϊ���Ͳ�����
		����������������ĸ���ʵ��������ɣ�����Ľ������ֱ����ս��������TerminalExpression�ͷ��ս��������NonterminalExpression��ɡ�
    TerminalExpression��ʵ�����ķ��е�Ԫ��������Ľ��Ͳ�����ͨ��һ��������ģʽ��ֻ��һ���ս�����ʽ�����ж��ʵ������Ӧ��ͬ���ս����
		�ս��һ�����ķ��е����㵥Ԫ��������һ���򵥵Ĺ�ʽR=R1+R2��������R1��R2�����ս������Ӧ�Ľ���R1��R2�Ľ����������ս�����ʽ��                                
	NonterminalExpression���ķ��е�ÿ�������Ӧ��һ�����ս�����ʽ�����ս�����ʽһ�����ķ��е���������������ؼ��֣����繫ʽR=R1+R2�У�+���Ƿ��ս��
		����+�Ľ���������һ�����ս�����ʽ�����ս�����ʽ�����߼��ĸ��ӳ̶ȶ����ӣ�ԭ����ÿ���ķ����򶼶�Ӧһ�����ս�����ʽ��
	Context�������ɫ������һ������������ķ��и����ս������Ӧ�ľ���ֵ������R=R1+R2�����Ǹ�R1��ֵ100����R2��ֵ200��
		��Щ��Ϣ��Ҫ��ŵ�������ɫ�У��ܶ����������ʹ��Map���䵱������ɫ���㹻�ˡ�

3�����ϣ�
��	��һ���򵥵��﷨���򣬱���һ��sql��䣬���������Ҫ����sql������rmת�����Ϳ���ʹ�ý�����ģʽ���������н��͡�
��	һЩ�ظ����������⣬����Ӽ��˳��������㣬���ǹ�ʽÿ�ζ���ͬ����ʱ��a+b-c*d����ʱ��a*b+c-d���ȵȵȵȸ�����ʽǧ���򻯣�
	���Ƕ����ɼӼ��˳��ĸ����ս�������ӵģ���ʱ���ǾͿ���ʹ�ý�����ģʽ��

4����ȱ�㣺
��	��������һ���򵥵��﷨�������ߣ������������ŵ������չ�ԣ��޸��﷨����ֻ��Ҫ�޸���Ӧ�ķ��ս���Ϳ����ˣ�����չ�﷨��ֻ��Ҫ���ӷ��ս����Ϳ����ˡ�
��	���ǣ�������ģʽ������������ͣ�ÿ���﷨����Ҫ����һ�����ս�����ʽ���﷨����Ƚϸ���ʱ���Ϳ��ܲ������������ļ���Ϊά�������ǳ�����鷳��
	ͬʱ�����ڲ��õݹ���÷�����ÿ�����ս�����ʽֻ�������Լ���صı��ʽ��ÿ�����ʽ��Ҫ֪�����յĽ��������ͨ���ݹ鷽ʽ��
	�����������������Ի���������̵����ԣ��ݹ鶼��һ�����Ƽ��ķ�ʽ������ʹ���˴�����ѭ���͵ݹ飬Ч����һ�����ݺ��ӵ����⡣
	�ر������ڽ���һ���������ӡ��߳����﷨ʱ��Ч�����������ܵ�
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
class SubNonterminalExpression : public AbstractExpression // Ĭ����˽�м̳�
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

	AbstractExpression *pPNE = new PlusNonterminalExpression(pTE1, pTE2); //pPNE�� PTE1->Interpreter() + pTE2->Intepreter()
	AbstractExpression *pSNE = new SubNonterminalExpression(pPNE, pTE3); // pSNE�� PNE->Interpreter() - pTE3->Intepreter()
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

// �����ս�����ʽ����Ӣ�ĵķ������Ϊ����
class DirectionExpression : public AbstractControlExpression
{
public:
	DirectionExpression(string direction) : _direction(direction) {};
	string interpreter(void)
	{
		if (_direction.compare("up"))
		{
			return "����";
		}
		else if (_direction.compare("down"))
		{
			return "����";
		}
		else if (_direction.compare("left"))
		{
			return "����";
		}
		else if (_direction.compare("right"))
		{
			return "����";
		}
		else
		{
			return "��Ч������";
		}
	}
private:
	string _direction;
};

// �����ս�����ʽ����Ӣ�ĵĶ�������Ϊ����
class ActionExpression : public AbstractControlExpression
{
public:
	ActionExpression(string action) : _action(action) {};
	string interpreter(void)
	{
		if (_action.compare("run"))
		{
			return "�����ƶ�";
		}
		else if (_action.compare("move"))
		{
			return "�ƶ�";
		}
		else
		{
			return "��Ч������";
		}
	}
private:
	string _action;
};

// �����ս�����ʽ
class DistanceExpression : public AbstractControlExpression
{
public:
	DistanceExpression(string distance) : _distance(distance) {};
	string interpreter(void)
	{
		return _distance + "����";
	}
private:
	string _distance;
};

// �򵥾��ӷ��ս�����ʽ
class SimpleSentenceExpression : public AbstractControlExpression
{
public:
	SimpleSentenceExpression(AbstractControlExpression *direction, AbstractControlExpression *action, AbstractControlExpression *distance):
		_direction(direction), _action(action), _distance(distance) {};
public:
	string interpreter(void)
	{
		return (_direction->interpreter() + _action->interpreter() + _distance->interpreter()); //�����ս����interpreter
	}
private:
	AbstractControlExpression *_direction;
	AbstractControlExpression *_action;
	AbstractControlExpression *_distance;
};

// And���ӷ��ս�����ʽ
class AndSentenceExpression : public AbstractControlExpression
{
public:
	AndSentenceExpression(AbstractControlExpression *leftSentence, AbstractControlExpression* rightSentence):
		_leftSentence(leftSentence), _rightSentence(rightSentence) {};
public:
	string interpreter(void)
	{
		return (_leftSentence->interpreter() + "����" + _rightSentence->interpreter());
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