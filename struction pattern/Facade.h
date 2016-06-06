#ifndef _FACADE_H_
#define _FACADE_H_

#include "common.h"

// ���ģʽ
/*
1�����
����ϵͳ�е�һ��ӿ��ṩһ��һ�µĽ��棬���ģʽ������һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ��������ʹ�á�
��ϵͳ�е�һ��ӿڣ��ͺñ�����ٵ������е����ɨ��������﷨�����������м���룬���ɻ������룻
���ģʽ�����һ���߲�ӿڣ��ͺñ�Visual Studio��Build��ť��ͨ��������һ��Build��ť���ñ�������������ʹ��

2��ʹ�ó��ϣ�
1�� ����ҪΪһ��������ϵͳ�ṩһ���򵥽ӿ�ʱ����ϵͳ������Ϊ�����ݻ������Խ��Խ���ӡ�
    �����ģʽʹ��ʱ������������С���ࡣ��ʹ����ϵͳ�����п������ԣ�Ҳ�����׶���ϵͳ���ж��ƣ�����Ҳ����Щ����Ҫ������ϵͳ���û�����һЩʹ���ϵ����ѡ�
	���ģʽ�����ṩһ���򵥵�ȱʡ��ͼ����һ��ͼ�Դ�����û���˵�Ѿ��㹻������Щ��Ҫ����Ŀɶ����Ե��û�����Խ��Facade�㣻
2�� ���ͻ�������������ʵ�ֲ���֮����ںܴ�������ԡ�����Facade�������ϵͳ��ͻ��Լ���������ϵͳ���룬���������ϵͳ�Ķ����ԺͿ���ֲ�ԣ�
3�� ����Ҫ����һ����νṹ����ϵͳʱ��ʹ�����ģʽ������ϵͳ��ÿ�����ڵ㡣
    �����ϵͳ֮�����໥�����ģ����ǾͿ��������ǽ�ͨ��Facade����ͨѶ���Ӷ���������֮���������ϵ��

3����ɣ�
Facade:
   ֪����Щ��ϵͳ�ฺ�������󣬲��ҽ��ͻ������������ʵ�����ϵͳ����
SubSystem:
   ʵ����ϵͳ����Ĺ��ܣ�������Facade����ָ�ɵ����񣻵��ǣ�SubSystemû��Facade���κ������Ϣ��Ҳ����˵��û��ָ��Facade��ָ�롣
Client��
   ͨ�����������Facade�ķ�ʽ����ϵͳ����ͨ�ţ�����ֱ������ϵͳ�򽻵���Facade����Щ��Ϣת�����ʵ�����ϵͳ����
   ��������ϵͳ�е��йض�������ʵ�ʹ�������Facadeģʽ����Ҳ���뽫���Ľӿ�ת������ϵͳ�Ľӿ�
4���ŵ㣺
1�����Կͻ���������ϵͳ�������������˿ͻ�����Ķ������Ŀ����ʹ����ϵͳʹ���������ӷ��㣻
2����ʵ������ϵͳ��ͻ�֮�������Ϲ�ϵ������ϵͳ�ڲ��Ĺ�����������ǽ���ϵģ�
   �����ϵͳʹ����ϵͳ������仯����Ӱ�쵽���Ŀͻ���
   ���ģʽ�����ڽ�����νṹϵͳ��Ҳ�����ڶԶ���֮���������ϵ�ֲ㡣
   ���ģʽ�����������ӵ�ѭ��������ϵ����һ���ڿͻ���������ϵͳ�Ƿֱ�ʵ�ֵ�ʱ����Ϊ��Ҫ
*/

/*
** FileName      : Facade.h
** Author        : Frank Tly
** Date          : 2015/7/19
** Description   : Facade Pattern Implementation of C++
*/

class SubsystemA
{
public:
	void operateA(void)
	{
		cout << "Subsytem A operate" << endl;
	}
};

class SubsystemB
{
public:
	void operateB(void)
	{
		cout << "Subsytem B operate" << endl;
	}
};

class Facade
{
public:
	void facadeOperate(void)
	{
		SubsystemA sa;
		SubsystemB sb;
		sa.operateA();
		sb.operateB();
	}
};

void FacadeTest();

class Scanner
{
public:
	void Scan()
	{
		cout << "I am Scan SubSystem" << endl;
	}
};

class Parser
{
public:
	void Parse()
	{
		cout << "I am Parser SubSystem" << endl;
	}
};

class GenMidCode
{
public:
	void GenCode()
	{
		cout << "I am Generate Middle Code SubSytem" << endl;
	}
};

class GenMachineCode
{
public:
	void GenCode()
	{
		cout << "I am Generate Machine Code SubSystem" << endl;
	}
};

// �߲�ӿ�
class CompileFacade
{
public:
	void Compile()
	{
		Scanner scanner;
		Parser  pareser;
		GenMidCode genmidcode;
		GenMachineCode genmachinecode;

		scanner.Scan();
		pareser.Parse();
		genmidcode.GenCode();
		genmachinecode.GenCode();
	}
};

void FacadeTest()
{
	Facade facade;
	facade.facadeOperate();

	CompileFacade compilefacade;
	compilefacade.Compile();
}
/* ������
1�� ����Ƴ��ڣ�Ӧ������ʶ�Ľ���ͬ����룬���糣�õ�����ܹ������ǿ��������ݷ��ʲ㣬��ҵ���߼����ʾ��֮�䣬����Facade��
    ʹ���ӵ���ϵͳ�ṩһ���򵥵Ľӿڣ���������ԣ�
2�� �ڿ����׶Σ���ϵͳ������Ϊ���ϵ��ع������Խ��Խ���ӣ��������Facade�����ṩһ���򵥵Ľӿڣ���������֮���������
3�� ��ά���׶Σ��������ϵͳ�Ѿ��ǳ�����ά������չ�ˣ���ʱ�����Ϊ��ϵͳ����һ������࣬���ṩ��ƴֲڻ�߶ȸ��ӵ���������ıȽ������򵥵Ľӿڣ�
    ����ϵͳ��Facade���󽻻���Facade���������뽻�����и��ӵĹ���
4�� ������ϵͳ�ķ��ʣ������ṩһ��Facade�㣬�����Facade��ڣ�ֻ��Ҫһ����Ҳ����˵��ʹ��Facadeʱ�����ǿ���ʹ�õ���ģʽ��ʵ��Facadeģʽ
*/
#endif