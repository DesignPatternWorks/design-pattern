#ifndef _ABSTRACT_FACTORY_H_
#define _ABSTRACT_FACTORY_H_
#include "common.h"
// ���󹤳�ģʽ
/*
���Ķ���Ϊ�ṩһ������һϵ����ػ��໥��������Ľӿڣ�
������ָ�����Ǿ������

��������Ʒ�࣬ÿ�������Ʒ�������������������Ʒ�ࡣ   
һ�����󹤳��࣬����������������幤���ࡣ   
ÿ�����幤������Դ��������صľ����Ʒ�ࣨһϵ����ز�Ʒ����ʵ��
*/

/*
1�����󹤳�ģʽ�빤������ģʽ������
���󹤳�ģʽ�ǹ�������ģʽ�������汾������������һ����ػ����໥�����Ķ���
���빤������ģʽ����������ڣ���������ģʽ��Ե���һ����Ʒ�ȼ��ṹ�������󹤳�ģʽ������ԵĶ����Ʒ�ȼ��ṹ��
�ڱ���У�ͨ��һ����Ʒ�ṹ������Ϊһ���ӿڻ��߳����࣬Ҳ����˵����������ģʽ�ṩ�����в�Ʒ����������ͬһ���ӿڻ�����࣬
�����󹤳�ģʽ���ṩ�Ĳ�Ʒ���������Բ�ͬ�Ľӿڻ�����ࡣ
�ڳ��󹤳�ģʽ�У���һ����Ʒ��ĸ����ν�Ĳ�Ʒ�壬��ָλ�ڲ�ͬ��Ʒ�ȼ��ṹ�й���������Ĳ�Ʒ��ɵļ��塣
���󹤳�ģʽ���ṩ��һϵ�в�Ʒ�����һ����Ʒ�壻
�����������ṩ��һϵ�в�Ʒ��Ϊһ���ȼ��ṹ��������Ȼ������������������˵������֮�������

2�����󹤳�ģʽ���ŵ�
���󹤳�ģʽ���˾��й�������ģʽ���ŵ��⣬����Ҫ���ŵ���ǿ���������ڲ��Բ�Ʒ�����Լ����
��ν�Ĳ�Ʒ�壬һ������ٵĶ�����һ���Ĺ��������󹤳�ģʽ�Ϳ��������ڲ��Բ�Ʒ��Ĺ�����ϵ���ж����������������ר������һ���µ��������й���

3�����󹤳�ģʽ��ȱ��
��Ʒ�����չ����һ��ʮ�ַ��������飬�����Ʒ������Ҫ����һ���µĲ�Ʒ���򼸺����еĹ����඼��Ҫ�����޸ġ�
����ʹ�ó��󹤳�ģʽʱ���Բ�Ʒ�ȼ��ṹ�Ļ����Ƿǳ���Ҫ�ġ�

4�����ó���
����Ҫ�����Ķ�����һϵ���໥�������໥�����Ĳ�Ʒ��ʱ�������ʹ�ó��󹤳�ģʽ��
˵�ĸ�����һ�㣬����һ���̳���ϵ�У���������Ŷ���ȼ��ṹ���������Ŷ�������ࣩ��
���ҷ��������ȼ��ṹ�е�ʵ����֮�������һ���Ĺ�������Լ�����Ϳ���ʹ�ó��󹤳�ģʽ����������ȼ��ṹ�е�ʵ����֮�䲻���ڹ�����Լ����
��ʹ�ö�������Ĺ������Բ�Ʒ���д������������һ�㡣
*/
void AbstractFactoryTest();

class AbstractProductA
{
public:
	virtual void ShowA() = 0;
};

class ProductA1 : public AbstractProductA
{
public:
	void ShowA()
	{
		cout << "I am Product A1" << endl;
	}
};

class ProductA2 : public AbstractProductA
{
public:
	void ShowA()
	{
		cout << "I am Product A2" << endl;
	}
};

class AbstractProductB
{
public:
	virtual void ShowB() = 0;
};

class ProductB1: public AbstractProductB
{
public:
	void ShowB()
	{
		cout << "I am Prouduct B1" << endl;
	}
};

class ProductB2: public AbstractProductB
{
public:
	void ShowB()
	{
		cout << "I am Prouduct B2" << endl;
	}
};

class AbstractFactoryAB
{
public:
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;
};

class Factory1: public AbstractFactoryAB
{
public:
	AbstractProductA* CreateProductA()
	{
		return new ProductA1();
	}
	AbstractProductB* CreateProductB()
	{
		return new ProductB1();
	}
};

class Factory2: public AbstractFactoryAB
{
public:
	AbstractProductA* CreateProductA()
	{
		return new ProductA2();
	}
	AbstractProductB* CreateProductB()
	{
		return new ProductB2();
	}
};

void AbstractFactoryTest()
{
	AbstractFactoryAB *pF1 = new Factory1();
	AbstractProductA *pPA1 = pF1->CreateProductA();
	pPA1->ShowA();
	AbstractProductB *pPB1 = pF1->CreateProductB();
	pPB1->ShowB();

	AbstractFactoryAB *pF2 = new Factory2();
	AbstractProductA *pPA2 = pF2->CreateProductA();
	pPA2->ShowA();
	AbstractProductB *pPB2 = pF2->CreateProductB();
	pPB2->ShowB();

	delete pF1; pF1 = NULL;
	delete pPA1; pPA1 = NULL;
	delete pPB1; pPB1 = NULL;
	delete pF2; pF2 = NULL;
	delete pPA2; pPA2 = NULL;
	delete pPB2; pPB2 = NULL;
}
#endif