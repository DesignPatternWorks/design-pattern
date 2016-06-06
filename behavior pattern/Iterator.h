#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "common.h"

// 迭代器模式
/*
1、 概念：提供一种方法顺序访问一个聚合对象中各个元素，而又不需要暴露该对象的内部表示
   我们必须去将一个容器的内部结构与它的遍历进行解耦；
   就好比STL中的容器，它将容器中对象的实现和遍历很好的解耦；所以，我们就无法知道它的内部是如何组织对象数据的
2、角色：
Iterator：定义迭代器访问和遍历元素的接口；
ConcreteIterator：实现具体的迭代器；
Aggregate：定义的容器，创建相应迭代器对象的接口；
ConcreteAggregate：具体的容器实现创建相应迭代器的接口，该操作返回ConcreteIterator的一个适当的实例

3、场合：
①  访问一个聚合对象的内容而无需暴露它的内部表示；
②  支持对聚合对象的多种遍历（从前到后，从后到前）；
③  为遍历不同的聚合结构提供一个统一的接口，即支持多态迭代。

4、 作用：
①  它支持以不同的方式遍历一个聚合，甚至都可以自己定义迭代器的子类以支持新的遍历；
②  迭代器简化了聚合的接口，有了迭代器的遍历接口，聚合本身就不再需要类似的遍历接口了。这样就简化了聚合的接口；
③  在同一个聚合上可以有多个遍历，每个迭代器保持它自己的遍历状态；因此，我们可以同时进行多个遍历
*/
void IteratorTest();

// Abstract Iterator
template <typename T>  // 模板类Iterator定义，需要template <typename(class) T>
class Iterator
{
public:
	virtual void First()  = 0;
	virtual void Next()   = 0;
	virtual T* Current()  = 0;
	virtual bool IsDone() = 0;
};

// Concrete Iterator
//template <typename T>     
//class Aggregate;      // 模板类Aggregate声明，需要template <typename(class) T>
//
//template <typename T>         // 外部实现迭代器，模板类ConcreteItertor定义，需要template <typename(class) T>
//class ConcreteItertor: public Iterator<T>
//{
//private:
//	Aggregate<T> *m_pAggr;             // 与某个聚合对象联系的迭代器
//	int m_cur; 
//public:
//	ConcreteItertor(Aggregate<T> *pAggr) : m_pAggr(pAggr), m_cur(0) {}; 
//public:
//	virtual void First()
//	{
//		m_cur = 0;
//	}
//	virtual void Next()
//	{
//		if (m_cur < (m_pAggr->GetLen()))
//		{
//			m_cur++;
//		}
//	}
//	virtual T* Current()
//	{
//		if (m_cur < (m_pAggr->GetLen()))
//		{
//			return &((*m_pAggr)[m_cur]); //  重载了操作符[]
//		}
//		else
//		{
//			return NULL;
//		}
//	}
//	virtual bool IsDone()
//	{
//		return (m_cur >= (m_pAggr->GetLen()));
//	}
//};

// Abstract Aggregate
template <typename T>
class Aggregate
{
public:
	virtual Iterator<T>* CreateIterator() = 0;
	virtual T& operator[](int index) = 0;
	virtual int GetLen() = 0;
	virtual void AddItem(T t) = 0;
	virtual void RemoveItem() = 0;
	virtual void ClearItem() = 0;

};

// Concrete Aggregate : 再封装了一次vector
template <typename T>
class ConcreteAggregate : public Aggregate<T>
{
private:
	vector<T> m_vecData;
public:
	/************************************************************************/
	/* 内部迭代器实现                                                                     */
	/************************************************************************/
	template <typename T>         // 外部实现迭代器，模板类ConcreteItertor定义，需要template <typename(class) T>
	class ConcreteItertor: public Iterator<T>
	{
	private:
		Aggregate<T> *m_pAggr;             // 与某个聚合对象联系的迭代器
		int m_cur; 
	public:
		ConcreteItertor(Aggregate<T> *pAggr) : m_pAggr(pAggr), m_cur(0) {}; 
	public:
		virtual void First()
		{
			m_cur = 0;
		}
		virtual void Next()
		{
			if (m_cur < (m_pAggr->GetLen()))
			{
				m_cur++;
			}
		}
		virtual T* Current()
		{
			if (m_cur < (m_pAggr->GetLen()))
			{
				return &((*m_pAggr)[m_cur]); //  重载了操作符[]
			}
			else
			{
				return NULL;
			}
		}
		virtual bool IsDone()
		{
			return (m_cur >= (m_pAggr->GetLen()));
		}
	};
	/************************************************************************/
	/* 内部迭代器实现                                                                     */
	/************************************************************************/
public:
	void AddItem(T t)
	{
		m_vecData.push_back(t);
	}
	void RemoveItem()
	{
		m_vecData.pop_back();
	}
	void ClearItem()
	{
		m_vecData.clear();
	}
	T& operator[](int index)    // 重载[]
	{
		return m_vecData[index];
	}
	int GetLen()
	{
		return m_vecData.size();
	}
	virtual Iterator<T>* CreateIterator()
	{
		return new ConcreteItertor<T>(this); // 与当前聚合相关联的迭代器，外部实现迭代器
	}
};

void IteratorTest_General()
{
	// 创建聚合对象
	Aggregate<int> *pA = new ConcreteAggregate<int>;
	pA->AddItem(1);
	pA->AddItem(2);
	pA->AddItem(3);
	pA->AddItem(4);

	// 创建迭代器
	Iterator<int> *pI = pA->CreateIterator(); // 可以再次创建

	//遍历迭代器
	for (pI->First(); !pI->IsDone(); pI->Next())
	{
		cout << "Item: " << *(pI->Current()) << endl;
	}

	SAFE_RELASE_POINTER(pA);
	SAFE_RELASE_POINTER(pI); // 手动释放创建的迭代器
}

// Vector & Array  Sequence Iterator

// Abstract Sequence Iterator
template <class T>
class SequenceIterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual T& currentItem() = 0;
	virtual bool isdone() = 0;
};

// Concrete Array Iterator
template <class T>
class Array;

template <class T>
class ArrayIterator : public SequenceIterator<T>
{
private:
	Array<T> *m_pArray;
	int m_curpos;
public:
	ArrayIterator(Array<T> *pArray): m_pArray(pArray) {}; //与具体的聚合对象关联的迭代器
public:
	virtual void first()
	{
		m_curpos = 0;
	}
	virtual void next()
	{
		m_curpos++;
	}
	virtual T& currentItem()
	{
		return (*m_pArray)[m_curpos];
	}
	virtual bool isdone()
	{
		return (m_curpos >= (m_pArray->GetSize()));
	}
};

// Concrete List Iterator
template <class T>
class List;

template <class T>

//  a typedef template is illegal
/*typedef struct tag_Node
{
	T Value;
	tag_Node *pNext;
}Node;  
 可以用using C++11
*/
struct Node
{
	T Value;
	Node<T> *pNext;
};
//List的结点

template <class T>
class ListIterator : public SequenceIterator<T>
{
private:
	List<T>   *m_pList;
	Node<T>   *m_pcurNode;
public:
	ListIterator(List<T> *m_List): m_pList(m_List) {}; //与具体的聚合对象关联的迭代器
public:
	virtual void first()
	{
		m_pcurNode = m_pList->GetHeader();
	}
	virtual void next()
	{
		m_pcurNode = m_pcurNode->pNext;
	}
	virtual T& currentItem()
	{
		return m_pcurNode->Value;
	}
	virtual bool isdone()
	{
		return (m_pcurNode == m_pList->GetTailerPast());
	}
};

// Abstract Sequence
template <typename T>
class Sequence
{
	virtual SequenceIterator<T>* CreateIterator() = 0;
	virtual int  GetSize() = 0;
	virtual void PushBack(T t) = 0;
	virtual T&   PopBack() = 0;
	virtual void Clear() = 0;;
};

// Concrete Sequence : Array
template <typename T>
#define ARRAY_MAX_SIZE 100
class Array : public Sequence<T>    // []只有
{
private:
	T m_data[ARRAY_MAX_SIZE];
	int m_count;
public:
	Array()
	{
		memset(m_data, 0, sizeof(T)* ARRAY_MAX_SIZE);
		m_count = 0;
	}
public:
	virtual SequenceIterator<T>* CreateIterator()
	{
		return new ArrayIterator<T>(this);
	}
	virtual int GetSize()
	{
		return m_count;
	}
	virtual void PushBack(T t)
	{
		if (m_count >= ARRAY_MAX_SIZE)
		{
			cout << "Array Is Full" << endl;
			return;
		}
		m_data[m_count++] = t;
		if (m_count >= ARRAY_MAX_SIZE) // 最后一次PUSH之后，初始化curindex = ARRAY_MAX_SIZE - 1;
		{
			m_count = ARRAY_MAX_SIZE - 1;
		}
	}
	virtual T& PopBack()
	{
		T res = 0;
		if (m_count < 0)
		{
			cout << "Array Is Empty" << endl;
			return res;
		}
		res = m_data[--m_count];
		m_data[m_count] = 0;
		if (m_count < 0) // 最后一次POP之后，初始化curindex = 0;
		{
			m_count = 0;
		}
		return res;
	}
	virtual void Clear()
	{
		memset(m_data, 0, sizeof(T)* ARRAY_MAX_SIZE);
		m_count = 0;		
	}
public:  // Array 特有的方法
	T& operator[](int index)
	{
		T res = 0;
		if ((index < 0) || (index >= ARRAY_MAX_SIZE))
		{
			cout << "Index Is Out Of Array Range" << endl;
			return res;
		}
		res = m_data[index];
		return res;
	}
};

// Concrete Sequence : List
template <typename T>
class List : public Sequence<T> //->只有
{
private:
	Node<T> *m_pHead;
	Node<T> *m_pTail;
	int   m_Count;
public:
	List()
	{
		m_pHead = NULL;
		m_pTail = NULL;
		m_Count = 0;
	}
	virtual ~List()
	{
		Clear();
	}
public:
	virtual SequenceIterator<T>* CreateIterator()
	{
		return new ListIterator<T>(this);
	}
	virtual int GetSize()
	{
		return m_Count;
	}
	virtual void PushBack(T t)
	{
		Node<T> *pNewNode = new Node<T>;
		pNewNode->Value = t;
		pNewNode->pNext = NULL;

		if (NULL_POINTER(m_pHead)) // 空的List
		{
			m_pHead = m_pTail = pNewNode;
		}
		else
		{
			m_pTail->pNext = pNewNode;
			m_pTail = pNewNode;
		}
		++m_Count;
	}
	virtual T& PopBack()
	{
		T res = 0;
		if (NULL_POINTER(m_pHead))
		{
			cout << "List Is Empty" << endl;
			return res;
		}

		Node<T> *pTmp = m_pHead;
		while (pTmp->pNext != m_pTail && (m_pHead != m_pTail)) // 找出m_pTail的前面一个结点，即pTmp->pNext = m_pTail
		{
			pTmp = pTmp->pNext;
		}

		res = m_pTail->Value;  // 最后一个是m_pTail
		if (m_pHead == m_pTail)
		{
			m_pHead =  NULL; // m_pHead 防止指针悬挂，野指针
		}
        SAFE_RELASE_POINTER(m_pTail);
		m_pTail = pTmp;
		m_pTail->pNext = NULL; // 最后一个结点的pNext = NULL,便于删除的时候判断
		pTmp    = NULL;
		--m_Count;

		return res;
	}
	virtual void Clear()
	{
		Node<T> *pTmp = m_pHead;
		while (!NULL_POINTER(pTmp))
		{
			m_pHead = pTmp->pNext;
			SAFE_RELASE_POINTER(pTmp);
			pTmp = m_pHead;
		}
	}

public: // List 特有的方法
	Node<T>* GetHeader()
	{
		return m_pHead;
	}
	Node<T>* GetTailerPast()
	{
		if (NULL_POINTER(m_pTail))
		{
			return NULL;
		}
		return m_pTail->pNext;
	}
};


void IteratorTest_Sequence()
{
	cout << "Before Array Pop Back:" << endl;
	Array<int> *pA = new Array<int>;
	pA->PushBack(10);
	pA->PushBack(20);
	pA->PushBack(30);
	pA->PushBack(40);
	SequenceIterator<int> *pIA = pA->CreateIterator();
	for (pIA->first(); !pIA->isdone(); pIA->next())
	{
		cout << "Array: " << pIA->currentItem() << endl;
	}

	cout << "After Array Pop Back:" << endl;
	int arrayPopRes = pA->PopBack();
	cout << "Array Pop Result is: " << arrayPopRes << endl;
	for (pIA->first(); !pIA->isdone(); pIA->next())
	{
		cout << "Array: " << pIA->currentItem() << endl;
	}

	cout << "Before List Pop Back:" << endl;
	List<int> *pL = new List<int>;
	pL->PushBack(100);
	pL->PushBack(200);
	pL->PushBack(300);
	pL->PushBack(400);
	SequenceIterator<int> *pIL = pL->CreateIterator();
	for (pIL->first(); !pIL->isdone(); pIL->next())
	{
		cout << "List: " << pIL->currentItem() << endl;
	}

	cout << "After List Pop Back:" << endl;
	int listPopRes = pL->PopBack();
	cout << "List Pop Result is: " << listPopRes << endl;
	for (pIL->first(); !pIL->isdone(); pIL->next())
	{
		cout << "List: " << pIL->currentItem() << endl;
	}

	SAFE_RELASE_POINTER(pA);
	SAFE_RELASE_POINTER(pIA);

	SAFE_RELASE_POINTER(pL);
	SAFE_RELASE_POINTER(pIL);
}
void IteratorTest()
{
	cout << "*********** IteratorTest_General: *************" << endl;
	IteratorTest_General();
	cout << "*********** IteratorTest_Sequence: *************" << endl;
	IteratorTest_Sequence();
}
#endif