#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

// ��Ԫģʽ
/*
1�� ���
    ���ù�������Ч��֧�ִ���ϸ���ȵĶ���
2���ص㣺�ڲ�״̬�����ⲿ״̬�������ͻ��˸ı�
�� �ڲ�״̬�洢��flyweight�У��������˶�����flyweight��������Ϣ����Щ��Ϣʹ��flyweight���Ա�����
   ���ⲿ״̬ȡ����flyweight�����������ݳ������仯����˲��ɹ����û��������ڱ�Ҫ��ʱ���ⲿ״̬���ݸ�flyweight��
�� flyweightִ��ʱ�����״̬�ض����ڲ��Ļ��ⲿ�ġ��ڲ�״̬�洢��ConcreteFlyweight����֮�У�
   ���ⲿ��������Client����洢����㡣���û�����flyweight����Ĳ���ʱ������״̬���ݸ�����
   ͬʱ���û���Ӧ��ֱ�Ӷ�ConcreteFlyweight�����ʵ��������ֻ�ܴ�FlyweightFactory����õ�ConcreteFlyweight����
   ����Ա�֤�������ʵ��ؽ��й������ڹ���һ��ʵ���������ڴ������ʵ��ʱ���Ϳ��Կ���ʹ�õ���ģʽ������ʵ��
�� ��Ԫģʽ�Ĺ�����ά����һ��ʵ���б�����б��б��������еĹ���ʵ����
   ���û�����Ԫģʽ�Ĺ��������������ʱ�����Ȳ�ѯ���ʵ������������ڶ�Ӧʵ�����򴴽�һ����������ڣ���ֱ�ӷ��ض�Ӧ��ʵ��
3��������
  һ��Ӧ�ó���ʹ���˴����Ķ���
  ��ȫ����ʹ�ô����Ķ�����ɺܴ�Ĵ洢������
  ����Ĵ����״̬���ɱ�Ϊ�ⲿ״̬��
  ���ɾ��������ⲿ״̬����ô��������Խ��ٵĹ������ȡ���ܶ������
4���ŵ㣺
  ��Ԫģʽ���Ա�������ǳ����ƶ���Ŀ�������С�˿ռ����ġ��ڳ������ʱ����ʱ��Ҫ���ɴ���ϸ���ȵ���ʵ������ʾ���ݡ�
  ����ܷ�����Щʵ�����ݳ��˼������������������ͬ�ģ�ʹ����Ԫģʽ�Ϳ��Դ���ȵؼ��ٶ����������
 */
/*
** FileName      : Flyweight.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Flyweight Pattern Implementation of C++
*/


void FlyweightAbstractTest();

// Flyweight������
class Flyweight
{
private:
	// �ڲ�״̬��Ҳ���Է���ConcreteFlyweight��
	string _intraState;
protected:
	Flyweight(string intraState) : _intraState(intraState) {};
public:
	//�����ⲿ״̬extraState
	virtual void Operate(const string& extraState) = 0;
	virtual ~Flyweight() {};
public:
	// �ڲ�״̬�ض��ӿڣ�Ҳ���Է���ConcreteFlyweight��
	string getIntraState(void)
	{
		return _intraState;
	}
};

// ����Flyweight�ľ�������
class ConcreteFlyweight : public Flyweight
{
public:
	ConcreteFlyweight(string intraState) : Flyweight(intraState) {};
public:
	virtual void Operate(const string& extraState)
	{
		cout << "concrete flyweight intraState: " <<  getIntraState() << endl; // intra state & extra state
		cout << "concrete flyweight extraState: " <<  extraState << endl;
	}
	virtual ~ConcreteFlyweight() {};
};


// �ǹ���Flyweight�ľ�������
class UnsharedConcreteFlyweight : public Flyweight
{
public:
	UnsharedConcreteFlyweight(string intraState) : Flyweight(intraState) {};
public:
	virtual void Operate(const string& extraState)
	{
		cout << "UnsharedConcrete flyweight extraState: " << extraState << endl; // only extra state
	}
	virtual ~UnsharedConcreteFlyweight() {};
};

// flyweight�����࣬���ö����Ѵ��ڣ�ֱ�ӷ��ظö��󣬷����½�һ�����󣬴��������У��ٷ���
class FlyweightFactory
{
	//�����ڲ�״̬��flyweight��������
private:
	vector<Flyweight*> _vecFlyweight;
public:
	FlyweightFactory() {};
	// ��ȡ�ɹ����flyweight���ӹ���pool�л�ȡ
	Flyweight* getConcreteFlyweight(const string& key)
	{
		vector<Flyweight*>::iterator it = _vecFlyweight.begin();
		for (; it != _vecFlyweight.end(); ++it)
		{
			if ((*it)->getIntraState() == key) //�����ڲ�״̬����,�����ڣ�ֱ�ӷ��ظö���
			{
				return *it; 
			}
		}

		Flyweight* newFlyweight = new ConcreteFlyweight(key);
		_vecFlyweight.push_back(newFlyweight);
		return newFlyweight;           //�������ڣ��򴴽�֮������flyweight���������ظö���
	}

	int getConcreteFlyweightCount(void)
	{
		return _vecFlyweight.size();
	}

	// ��ȡ���ɹ����flyweight��ֱ�Ӵ���
	Flyweight* getUnsharedConcreteFlyweight(const string& key)
	{
		return new UnsharedConcreteFlyweight(key);
	}
};

void FlyweightAbstractTest()
{
	// factory
	FlyweightFactory *factory = new FlyweightFactory();

	//shared flyweight
	Flyweight *concreteFlyweight = factory->getConcreteFlyweight("shared intra state");
	Flyweight *concreteFlyweight2 = factory->getConcreteFlyweight("shared intra state"); // the same, return obj directly																						 // extra state
	const string extraState1 = "extra1";
	const string extraState2 = "extra2";
	concreteFlyweight->Operate(extraState1);
	concreteFlyweight2->Operate(extraState2);
	cout << "flyweight container size :" << factory->getConcreteFlyweightCount() << endl;

	//unshared flyweight
	const string extraState3 = "extra3";
	Flyweight *unsharedConcreteFlyweight = factory->getUnsharedConcreteFlyweight("no shared intra state");
	unsharedConcreteFlyweight->Operate(extraState3);
}

void FlyweightPieceTest();
/* ���ӡ��������󳡾�������
���е������巿������Ӷ���һ���ġ�Ψһ�Ĳ�ͬ��ÿ�������ڲ�ͬ�ķ���Ĳ�ͬ���̵Ĳ�ͬλ���ϡ�
���ԣ�����������˵�����ǲ��÷�һ�����Ӿ�newһ�����Ӷ���ֻ��Ҫ����Ҫ��ʱ��ȥ�����ö�Ӧ�����Ӷ���
���û�У���newһ�����Ӷ���������ˣ���ֱ�ӷ������Ӷ���

������������Ϊ���ӣ����з�����������������Ϸ����һ����ɫ����ʱ����ʱ����û�а�ɫ���ӣ����Ծ�newһ����ɫ���ӣ�
����һ����ҷ����һ����ɫ����ʱ����ʱ����û�к�ɫ���ӣ����Ծ���Ҫnewһ����ɫ���ӣ�
������ٴη���һ����ɫ����ʱ����ȥ��ѯ�Ƿ����Ѿ����ڵİ�ɫ���Ӷ������ڵ�һ���Ѿ�new��һ����ɫ���Ӷ���
���ԣ����ڲ����ٴ�newһ����ɫ���Ӷ��󣬶��Ƿ�����ǰnew�İ�ɫ���Ӷ��󣻣���ɫ--�ڲ�״̬��
���ں�ɫ���ӣ�����ͬ��
��������Ӷ�������ֻ��Ҫ�������ӵĲ�ͬ����λ�ü��ɣ�λ��--�ⲿ״̬��
*/

// ����λ�� (extra state)
class Position 
{
private:
	int x;
	int y;
public:
	Position(int a, int b): x(a), y(b) {};
	virtual ~Position() {};

	int getX(void)
	{
		return x;
	}
	int getY(void)
	{
		return y;
	}
};

//���ӵ���ɫ(intra state)
typedef enum tag_Color
{
	BLACK,
	WHITE
}COLOR;

// ����������(Abstract Flyweight)
class Piece
{
protected:
	COLOR    m_Color;  // intra state
public:
	Piece(COLOR color): m_Color(color) {}; // only color 
	virtual ~Piece() {};
public:
	virtual COLOR GetColor()  // intra state
	{
		return m_Color;
	}

	virtual void DrawPiece(Position &pos) = 0; // operate(extra state)
};

// �����������(Concrete Flyweight)
class BlackPiece : public Piece
{
public:
	BlackPiece() : Piece(BLACK) {};
	virtual ~BlackPiece() {};
public:
	void DrawPiece(Position &pos)
	{
		cout << "Draw A Black Piece, Position is:" << "X:" << pos.getX() << " Y:" << pos.getY() << endl;
	}
};

// �����������(Concrete Flyweight)
class WhitePiece : public Piece
{
public:
	WhitePiece() : Piece(WHITE) {};
	virtual ~WhitePiece() {};
public:
	void DrawPiece(Position &pos)
	{
		cout << "Draw A White Piece, Position is:" << "X:" << pos.getX() << " Y:" << pos.getY() << endl;
	}
};

// ���ӹ����࣬�ṩ������ɫ����ɫ���ӣ����ṩ��������ʹ�� (Flyweight Factory)
class PieceFactory
{
private:
	// ������������Ԫ�أ�
	vector<Piece*> m_vecPiece;
public:
	PieceFactory() {};
	virtual ~PieceFactory()
	{
		for (vector<Piece*>::iterator it = m_vecPiece.begin();
			 it != m_vecPiece.end();
			 ++it)
		{
			if (NULL != (*it))
			{
				delete *it;
				*it = NULL;
			}
		}
	}
private:
	Piece* CreateAndAddPiece(COLOR color)
	{
		Piece *pRes;

		if (WHITE ==  color)
		{
			pRes = new WhitePiece();
		}
		else if (BLACK == color)
		{
			pRes = new BlackPiece();
		}
		m_vecPiece.push_back(pRes);

		return pRes;
	}
public:
	Piece* GetPiece(COLOR color)
	{
		 // ����Ϊ�գ����ж�vector���������Ƿ��и�����ɫ��Piece
		for (vector<Piece*>::iterator it = m_vecPiece.begin(); 
			 it != m_vecPiece.end();
			 ++it)
		{
			if (color == (*it)->GetColor()) // �ҵ��˸�����ɫ��Piece
			{
				return (*it);
			}
		}
		
		//  ��δ�գ���newһ��Piece�� �����Piece
		return CreateAndAddPiece(color);
	}
};


void FlyweightPieceTest()
{
	PieceFactory *pPF = new PieceFactory();

	// Player 1 get a white piece from the pieces bowl
	Piece       *pWP_1 = pPF->GetPiece(WHITE);
	pWP_1->DrawPiece(Position(1,10)); // new a white piece, set pos = 1,10

	// Player 2 get a black piece from the pieces bowl
	Piece       *pBP_1 = pPF->GetPiece(BLACK); // new a black piece , set pos = 1,20
	pBP_1->DrawPiece(Position(1,20)); 

	// Player 1 get a white piece from the pieces bowl
	Piece       *pWP_2 = pPF->GetPiece(WHITE); // get the existing white piece, but set pos = 2,10
	pWP_2->DrawPiece(Position(2,10));

	// Player 2 get a black piece from the pieces bowl
	Piece       *pBP_2 = pPF->GetPiece(BLACK); // get the existing a black piece , but set pos = 2,20
	pBP_2->DrawPiece(Position(2,20));

	if (NULL != pPF)
	{
		delete pPF; pPF = NULL;
	}
}

void FlyweightTest();

void FlyweightTest()
{
	cout << "**************Flyweight Abstract Test***************" << endl;
	FlyweightAbstractTest();
	cout << "**************Flyweight Piece Test***************" << endl;
	FlyweightPieceTest();
}
/* ������
�� �����FlyweightԽ�࣬�洢��ԼҲ��Խ�࣬��Լ�����Ź���״̬�����������
  ������ʹ�ô������ڲ����ⲿ״̬�������ⲿ״̬�Ǽ�������Ķ��Ǵ洢��ʱ�򣬽�Լ�����ﵽ���
  ���ԣ�����ʹ�����ַ�������Լ�洢���ù�������ڲ�״̬�����ģ��ü���ʱ�任ȡ���ⲿ״̬�Ĵ洢��
�� ͬʱ����ʵ�ֵ�ʱ��һ��Ҫ���ƺ��ⲿ״̬�빲�����Ķ�Ӧ��ϵ
  �������ڴ���ʵ�ֲ��֣���PieceBoard����ʹ����һ��map���б˴�֮���ӳ�䣬���ӳ����ʵ�ʿ�������Ҫ���ǵ�
*/
#endif