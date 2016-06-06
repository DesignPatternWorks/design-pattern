#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "common.h"

// ������ģʽ
/*
1�� ����ṩһ�ַ���˳�����һ���ۺ϶����и���Ԫ�أ����ֲ���Ҫ��¶�ö�����ڲ���ʾ
   ���Ǳ���ȥ��һ���������ڲ��ṹ�����ı������н��
   �ͺñ�STL�е����������������ж����ʵ�ֺͱ����ܺõĽ�����ԣ����Ǿ��޷�֪�������ڲ��������֯�������ݵ�
2����ɫ��
Iterator��������������ʺͱ���Ԫ�صĽӿڣ�
ConcreteIterator��ʵ�־���ĵ�������
Aggregate�������������������Ӧ����������Ľӿڣ�
ConcreteAggregate�����������ʵ�ִ�����Ӧ�������Ľӿڣ��ò�������ConcreteIterator��һ���ʵ���ʵ��

3�����ϣ�
��  ����һ���ۺ϶�������ݶ����豩¶�����ڲ���ʾ��
��  ֧�ֶԾۺ϶���Ķ��ֱ�������ǰ���󣬴Ӻ�ǰ����
��  Ϊ������ͬ�ľۺϽṹ�ṩһ��ͳһ�Ľӿڣ���֧�ֶ�̬������

4�� ���ã�
��  ��֧���Բ�ͬ�ķ�ʽ����һ���ۺϣ������������Լ������������������֧���µı�����
��  ���������˾ۺϵĽӿڣ����˵������ı����ӿڣ��ۺϱ���Ͳ�����Ҫ���Ƶı����ӿ��ˡ������ͼ��˾ۺϵĽӿڣ�
��  ��ͬһ���ۺ��Ͽ����ж��������ÿ���������������Լ��ı���״̬����ˣ����ǿ���ͬʱ���ж������
*/
void IteratorTest();

// Abstract Iterator
template <typename T>  // ģ����Iterator���壬��Ҫtemplate <typename(class) T>
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
//class Aggregate;      // ģ����Aggregate��������Ҫtemplate <typename(class) T>
//
//template <typename T>         // �ⲿʵ�ֵ�������ģ����ConcreteItertor���壬��Ҫtemplate <typename(class) T>
//class ConcreteItertor: public Iterator<T>
//{
//private:
//	Aggregate<T> *m_pAggr;             // ��ĳ���ۺ϶�����ϵ�ĵ�����
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
//			return &((*m_pAggr)[m_cur]); //  �����˲�����[]
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

// Concrete Aggregate : �ٷ�װ��һ��vector
template <typename T>
class ConcreteAggregate : public Aggregate<T>
{
private:
	vector<T> m_vecData;
public:
	/************************************************************************/
	/* �ڲ�������ʵ��                                                                     */
	/************************************************************************/
	template <typename T>         // �ⲿʵ�ֵ�������ģ����ConcreteItertor���壬��Ҫtemplate <typename(class) T>
	class ConcreteItertor: public Iterator<T>
	{
	private:
		Aggregate<T> *m_pAggr;             // ��ĳ���ۺ϶�����ϵ�ĵ�����
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
				return &((*m_pAggr)[m_cur]); //  �����˲�����[]
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
	/* �ڲ�������ʵ��                                                                     */
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
	T& operator[](int index)    // ����[]
	{
		return m_vecData[index];
	}
	int GetLen()
	{
		return m_vecData.size();
	}
	virtual Iterator<T>* CreateIterator()
	{
		return new ConcreteItertor<T>(this); // �뵱ǰ�ۺ�������ĵ��������ⲿʵ�ֵ�����
	}
};

void IteratorTest_General()
{
	// �����ۺ϶���
	Aggregate<int> *pA = new ConcreteAggregate<int>;
	pA->AddItem(1);
	pA->AddItem(2);
	pA->AddItem(3);
	pA->AddItem(4);

	// ����������
	Iterator<int> *pI = pA->CreateIterator(); // �����ٴδ���

	//����������
	for (pI->First(); !pI->IsDone(); pI->Next())
	{
		cout << "Item: " << *(pI->Current()) << endl;
	}

	SAFE_RELASE_POINTER(pA);
	SAFE_RELASE_POINTER(pI); // �ֶ��ͷŴ����ĵ�����
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
	ArrayIterator(Array<T> *pArray): m_pArray(pArray) {}; //�����ľۺ϶�������ĵ�����
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
 ������using C++11
*/
struct Node
{
	T Value;
	Node<T> *pNext;
};
//List�Ľ��

template <class T>
class ListIterator : public SequenceIterator<T>
{
private:
	List<T>   *m_pList;
	Node<T>   *m_pcurNode;
public:
	ListIterator(List<T> *m_List): m_pList(m_List) {}; //�����ľۺ϶�������ĵ�����
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
class Array : public Sequence<T>    // []ֻ��
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
		if (m_count >= ARRAY_MAX_SIZE) // ���һ��PUSH֮�󣬳�ʼ��curindex = ARRAY_MAX_SIZE - 1;
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
		if (m_count < 0) // ���һ��POP֮�󣬳�ʼ��curindex = 0;
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
public:  // Array ���еķ���
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
class List : public Sequence<T> //->ֻ��
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

		if (NULL_POINTER(m_pHead)) // �յ�List
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
		while (pTmp->pNext != m_pTail && (m_pHead != m_pTail)) // �ҳ�m_pTail��ǰ��һ����㣬��pTmp->pNext = m_pTail
		{
			pTmp = pTmp->pNext;
		}

		res = m_pTail->Value;  // ���һ����m_pTail
		if (m_pHead == m_pTail)
		{
			m_pHead =  NULL; // m_pHead ��ָֹ�����ң�Ұָ��
		}
        SAFE_RELASE_POINTER(m_pTail);
		m_pTail = pTmp;
		m_pTail->pNext = NULL; // ���һ������pNext = NULL,����ɾ����ʱ���ж�
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

public: // List ���еķ���
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