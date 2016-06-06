#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

// 享元模式
/*
1、 概念：
    运用共享技术有效地支持大量细粒度的对象
2、特点：内部状态共享；外部状态不共享，客户端改变
① 内部状态存储于flyweight中，它包含了独立于flyweight场景的信息，这些信息使得flyweight可以被共享。
   而外部状态取决于flyweight场景，并根据场景而变化，因此不可共享。用户对象负责在必要的时候将外部状态传递给flyweight。
② flyweight执行时所需的状态必定是内部的或外部的。内部状态存储于ConcreteFlyweight对象之中；
   而外部对象则由Client对象存储或计算。当用户调用flyweight对象的操作时，将该状态传递给它。
   同时，用户不应该直接对ConcreteFlyweight类进行实例化，而只能从FlyweightFactory对象得到ConcreteFlyweight对象，
   这可以保证对它们适当地进行共享；由于共享一个实例，所以在创建这个实例时，就可以考虑使用单例模式来进行实现
③ 享元模式的工厂类维护了一个实例列表，这个列表中保存了所有的共享实例；
   当用户从享元模式的工厂类请求共享对象时，首先查询这个实例表，如果不存在对应实例，则创建一个；如果存在，则直接返回对应的实例
3、场景：
  一个应用程序使用了大量的对象；
  完全由于使用大量的对象，造成很大的存储开销；
  对象的大多数状态都可变为外部状态；
  如果删除对象的外部状态，那么可以用相对较少的共享对象取代很多组对象
4、优点：
  享元模式可以避免大量非常相似对象的开销，减小了空间消耗。在程序设计时，有时需要生成大量细粒度的类实例来表示数据。
  如果能发现这些实例数据除了几个参数外基本都是相同的，使用享元模式就可以大幅度地减少对象的数量。
 */
/*
** FileName      : Flyweight.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Flyweight Pattern Implementation of C++
*/


void FlyweightAbstractTest();

// Flyweight抽象类
class Flyweight
{
private:
	// 内部状态，也可以放在ConcreteFlyweight中
	string _intraState;
protected:
	Flyweight(string intraState) : _intraState(intraState) {};
public:
	//操作外部状态extraState
	virtual void Operate(const string& extraState) = 0;
	virtual ~Flyweight() {};
public:
	// 内部状态回读接口，也可以放在ConcreteFlyweight中
	string getIntraState(void)
	{
		return _intraState;
	}
};

// 共享Flyweight的具体子类
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


// 非共享Flyweight的具体子类
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

// flyweight工厂类，若该对象已存在，直接返回该对象，否则新建一个对象，存入容器中，再返回
class FlyweightFactory
{
	//保存内部状态的flyweight对象容器
private:
	vector<Flyweight*> _vecFlyweight;
public:
	FlyweightFactory() {};
	// 获取可共享的flyweight，从共享pool中获取
	Flyweight* getConcreteFlyweight(const string& key)
	{
		vector<Flyweight*>::iterator it = _vecFlyweight.begin();
		for (; it != _vecFlyweight.end(); ++it)
		{
			if ((*it)->getIntraState() == key) //根据内部状态索引,若存在，直接返回该对象
			{
				return *it; 
			}
		}

		Flyweight* newFlyweight = new ConcreteFlyweight(key);
		_vecFlyweight.push_back(newFlyweight);
		return newFlyweight;           //若不存在，则创建之并存入flyweight容器，返回该对象
	}

	int getConcreteFlyweightCount(void)
	{
		return _vecFlyweight.size();
	}

	// 获取不可共享的flyweight，直接创建
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
/* 棋子、棋盘需求场景分析：
所有的五子棋房间的棋子都是一样的。唯一的不同是每个棋子在不同的房间的不同棋盘的不同位置上。
所以，对于棋子来说，我们不用放一个棋子就new一个棋子对象，只需要在需要的时候，去请求获得对应的棋子对象
如果没有，就new一个棋子对象；如果有了，就直接返回棋子对象。

这里以五子棋为例子，进行分析，当玩家在棋盘上放入第一个白色棋子时，此时由于没有白色棋子，所以就new一个白色棋子；
当另一个玩家放入第一个黑色棋子时，此时由于没有黑色棋子，所以就需要new一个黑色棋子；
当玩家再次放入一个白色棋子时，就去查询是否有已经存在的白色棋子对象，由于第一次已经new了一个白色棋子对象，
所以，现在不会再次new一个白色棋子对象，而是返回以前new的白色棋子对象；（颜色--内部状态）
对于黑色棋子，亦是同理；
获得了棋子对象，我们只需要设置棋子的不同棋盘位置即可（位置--外部状态）
*/

// 棋子位置 (extra state)
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

//棋子的颜色(intra state)
typedef enum tag_Color
{
	BLACK,
	WHITE
}COLOR;

// 抽象棋子类(Abstract Flyweight)
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

// 具体黑棋子类(Concrete Flyweight)
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

// 具体白棋子类(Concrete Flyweight)
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

// 棋子工厂类，提供生产白色、黑色棋子，并提供给棋盘类使用 (Flyweight Factory)
class PieceFactory
{
private:
	// 棋子容器（享元池）
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
		 // 若不为空，则判断vector容器里面是否有给定颜色的Piece
		for (vector<Piece*>::iterator it = m_vecPiece.begin(); 
			 it != m_vecPiece.end();
			 ++it)
		{
			if (color == (*it)->GetColor()) // 找到了给定颜色的Piece
			{
				return (*it);
			}
		}
		
		//  若未空，则new一个Piece， 并添加Piece
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
/* 分析：
① 共享的Flyweight越多，存储节约也就越多，节约量随着共享状态的增多而增大。
  当对象使用大量的内部及外部状态，并且外部状态是计算出来的而非存储的时候，节约量将达到最大。
  所以，可以使用两种方法来节约存储：用共享减少内部状态的消耗；用计算时间换取对外部状态的存储。
② 同时，在实现的时候，一定要控制好外部状态与共享对象的对应关系
  比如我在代码实现部分，在PieceBoard类中使用了一个map进行彼此之间的映射，这个映射在实际开发中需要考虑的
*/
#endif