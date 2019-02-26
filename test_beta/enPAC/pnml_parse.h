#pragma once
#include <stdio.h>
#include <iostream>
#include<string>
#include<vector>
#include <stdlib.h>
#include<fstream>
#include<map>
#include "tinyxml.h"

using namespace std;

#define max_place_num 1000
#define max_tran_num 1000
#define max_node_num 10000

#define max_incoming 100



class rgstack
{
public:
	vector<int> incoming;
//	int incoming[max_incoming];
	int pointer;
public:
	rgstack();
	bool isEmpty();
	void push(int num);
	void pop(int &num);
};
class rgqueue
{
private:
	int *priset;
	int head;
	int tail;
	int elemnum;
public:
	rgqueue();
	void EnQueue(int num);
	void DeQueue(int &num);
	bool isEmpty();
};





struct Arc {
	string id;
	string source;
	string target;
	int sourceNum = 0;
	bool sourceP; //false����Դ�ڵ��Ǳ�Ǩ��true����Դ�ڵ��ǿ���
	int targetNum = 0;
	int weight = 1;
};

struct Place
{
	string name;
	int num = 0;
	int initialMarking = 0;
	bool sig = false;//�Ƿ�����Ҫ������������Ϊtrue
	int solution[max_place_num];//��Ҫ������Ӧ��P������
//	vector<int> solution;
	bool visited = false;//��Ϊ����Ҫ��������ǰβ�����Ƿ񱻸�ֵΪ1��(�����Է������ʱ����)
};

struct Transition
{
	string name;
	int num = 0;
};

//�ɴ�ͼ�еı߱�
typedef struct RGEdge {
	int t;                                                //����ߴ���ķ����ı�Ǩ���
	int target;                                         //�������Ŀ��ڵ��״̬���
	struct RGEdge *nextedge = NULL;   //�ñ�ָ�����һ����
}RGEdge, *PRGEdge;

string itos(int n);             //������intת����string 
int sum(int m[], int n);

class Petri
{
public:
	int m;   //��������ָ��
	int n;    //��Ǩ����ָ��
	int arcnum;  //������ָ��

	vector<Place> place;
	vector<Transition> transition;
	vector<Arc> arc;

	vector<vector<double>> A;
	vector<vector<double>> A1;
	vector<vector<double>> A2;
public:
	Petri();
	void addPlace(Place p);
	void addTransition(Transition t);
	void addArc(Arc a);
	void readPNML(char *filename);  //����Petri
	void getA();           //���ɹ�������
	void printA();         //��ӡ��������
	void printA1();
	void UpperTriangularMatrix();//��������ת���������Ǿ���
	void exchange(double a[], double b[]); //����Ԫ�ػ���
	void sub(double a[], double b[], double k);//����:a[]=a[]-k*b[]
	
};
//�ɴ�ͼ�еĶ����
typedef struct RGNode {
	string name;
	int m[max_place_num];
//	vector<int> m;                   //��״̬�洢�ı�ʶ��Ϣ
	bool flag = 0;                                  //��0����1
	int isfirable[max_tran_num];
//	vector<int> isfirable;  //�Ӹñ�ʶ�������Է����ı�Ǩ����
	int enableNum = 0;                         //�ñ�ʶ���Է����ı�Ǩ��Ŀ
	int X[max_tran_num] = {-1};//ÿ����ʶmarking��Ӧһ����̼�X
	int markX = 0;//X����Ĵ�С
	rgstack inset;
	PRGEdge firstEdge = NULL;
}RGNode, *PRGNode;

class RG
{
public:
	int node;
	int edge;
	vector<RGNode> rgnode;
//	Queue unprocessed;
	rgqueue unprocessed;
//	vector<Queue> unprocessed;
//	Queue <int> unprocessed;
//	vector<rgqueue> unprocessed;
//	rgqueue unprocessed[100];
public:
	RG();		
	void addRGNode(RGNode rg);
//	void newReachabilityTree(Petri ptnet);    //���ɿɴ�ͼ
	void PrintGraph(Petri ptnet, ofstream &outfile);//�ɴ�ͼ���ɵ��ļ���
	void standardOutput(Petri ptnet);
//	bool exist(int X[],int num);
//	void addToUnprocessed(Petri ptnet, RGNode marking);
//	void ReducingSuccessorGenerator(Petri ptnet,RGNode &marking);
	void ReachabilityTree(Petri ptnet);
};