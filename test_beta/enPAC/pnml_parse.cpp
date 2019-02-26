#include"pnml_parse.h"

/**************************Data_Structure*********************************/

rgstack::rgstack()
{
	pointer = 0;
}
bool rgstack::isEmpty()
{
	return ((pointer > 0) ? false : true);
}
void rgstack::push(int num)
{
	if (pointer >= max_incoming)
	{
		cerr << "Stack overflow! Please set \"max_incoming\" bigger!" << endl;
		exit(-1);
	}
	else
		incoming[pointer++] = num;
}
void rgstack::pop(int &num)
{
	if (pointer > 0)
	{
		num = incoming[--pointer];
	}
}

rgqueue::rgqueue()
{
	head = tail = 0;
	elemnum = 0;
//	priset = new int[max_node_num];
	vector<int> priset;
}
bool rgqueue::isEmpty()
{
	return ((head == tail) ? true : false);
}
/*
void rgqueue::EnQueue(int num)
{
	if ((tail + 1) % max_node_num == head)
	{
		cerr << "Queue overflow! please set \"max_node_num\" bigger!" << endl;
		exit(-1);
	}
	else
	{
		priset[tail] = num;
		tail = (tail + 1) % max_node_num;
	}
}

void rgqueue::DeQueue(int &num)
{
	if (head != tail)
	{
		num = priset[head];
		head = (head + 1) % max_node_num;
	}
}*/
/*****************************Data_Structure_End********************************/


/***********************************************************/
Petri::Petri()
{
	m = 0;   //��������ָ��
	n = 0;    //��Ǩ����ָ��
	arcnum = 0;  //������ָ��
}

RG::RG()
{
	node = 0;
	edge = 0;
}


void Petri::addPlace(Place p) {
	place.push_back(p);
}
void Petri::addTransition(Transition t) {
	transition.push_back(t);
}
void Petri::addArc(Arc a) {
	arc.push_back(a);
}
void Petri::readPNML(char *filename) {
	TiXmlDocument mydoc(filename);
	bool loadOK = mydoc.LoadFile();
	if (!loadOK) {
		cout << "could not load the test file" << endl;
		exit(1);
	}
	TiXmlElement *PetriElement = mydoc.RootElement();
	TiXmlElement *netElement = PetriElement->FirstChildElement();
	TiXmlElement *pageElement = netElement->FirstChildElement("page");
	for (TiXmlElement *petriElement = pageElement->FirstChildElement();//��һ����Ԫ��
		petriElement;
		petriElement = petriElement->NextSiblingElement())
	{
		if (petriElement->ValueTStr() == "place") {
			Place p;
			p.num = m;

			TiXmlAttribute *pnameElement = petriElement->FirstAttribute();
			p.name = pnameElement->Value();

			if (petriElement->FirstChildElement("initialMarking")) {
				TiXmlElement *initialMarkingElement = petriElement->FirstChildElement("initialMarking")->FirstChildElement("text");
				p.initialMarking = atoi(initialMarkingElement->GetText());
			}
		//	TiXmlElement *nameElement = petriElement->FirstChildElement("name")->FirstChildElement("text");
		//	p.name = nameElement->GetText();
			m++;
			place.push_back(p);
		}
		if (petriElement->ValueTStr() == "transition") {
			Transition t;
			t.num = n;
//			TiXmlElement *tnameElement = petriElement->FirstChildElement("name")->FirstChildElement("text");
//			t.name = tnameElement->GetText();
			
			TiXmlAttribute *tnameElement = petriElement->FirstAttribute();
			t.name = tnameElement->Value();

			n++;
			transition.push_back(t);
		}
		if (petriElement->ValueTStr() == "arc") {
			Arc a;
			TiXmlAttribute *arcAttr = petriElement->FirstAttribute();
			a.id = arcAttr->Value();
			arcAttr = arcAttr->Next();
			a.source = arcAttr->Value();
			arcAttr = arcAttr->Next();
			a.target = arcAttr->Value();
			if (petriElement->FirstChildElement("inscription")) {
				TiXmlElement *weightElement = petriElement->FirstChildElement("inscription")->FirstChildElement("text");
				a.weight = atoi(weightElement->GetText());
			}
			arcnum++;
			arc.push_back(a);
		}
	}
	for (int i = 0; i < arcnum; i++) {//����ÿһ����
		for (int j = 0; j < n; j++) {//�ͱ�Ǩ��

			if (arc[i].source==transition[j].name) {
				arc[i].sourceP = false;
				arc[i].sourceNum = transition[j].num;
			}
			if (arc[i].target==transition[j].name) {
				arc[i].targetNum = transition[j].num;
			}
		}
		for (int k = 0; k < m; k++) {//�Ϳ�����
			if (arc[i].source==place[k].name) {
				arc[i].sourceP = 1;
				arc[i].sourceNum = place[k].num;
			}
			if (arc[i].target==place[k].name) {
				arc[i].targetNum = place[k].num;
			}
		}
	}
}

void Petri::getA() {
	A.resize(n);
	for (int i = 0; i < n; i++) {
		A[i].resize(m, 0);
	}

	A1.resize(n);
	for (int i = 0; i < n; i++) {
		A1[i].resize(m, 0);
	}

	A2.resize(n);
	for (int i = 0; i < n; i++) {
		A2[i].resize(m, 0);
	}

	for (int i = 0; i < arcnum; i++) {
		if (arc[i].sourceP) {
			A[arc[i].targetNum][arc[i].sourceNum]=-arc[i].weight;
			A2[arc[i].targetNum][arc[i].sourceNum]= arc[i].weight;//�������
		}
		else{
			A[arc[i].sourceNum][arc[i].targetNum]= arc[i].weight;
			A1[arc[i].sourceNum][arc[i].targetNum]= arc[i].weight;//�������
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((A1[i][j] == 1) && (A2[i][j] == 1)) {
				A[i][j] = 2;
			}
		}
	}


}
void Petri::printA() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << A[i][j] << "  ";
		}
		cout << endl;
	}
}
void Petri::printA1() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << A1[i][j] << "  ";
		}
		cout << endl;
	}
}
string itos(int n)
{
	string val = to_string(n);
	return val;
}
void Petri::exchange(double a[], double b[]) {//����Ԫ�ػ���
	double *temp;
	temp = new double[m];
	for (int i = 0; i < m; i++) {
		temp[i] = a[i];
		a[i] = b[i];
		b[i] = temp[i];
	}
}
void Petri::sub(double a[], double b[], double k) {//����:a[]=a[]-k*b[]
	for (int i = 0; i < m; i++) {
		a[i] = a[i] - k * b[i];
	}
}

int sum(int m[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += m[i];
	}
	return sum;
}

void Petri::UpperTriangularMatrix() {
	
	double **B;
    B = new double*[n];
	for (int k = 0; k < n; k++)
	{
		B[k] = new double[m];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			B[i][j] = A[i][j];
		}
	} 
//	vector<vector<double>> B = A;
	double multiple;//�洢������ϵ
	int site = 0;//site������ڱ������к�
	for (int i = 0; (i < m)&&(site<n); i++) {//�������е��С�i������ڱ������к�
		if (B[site][i] == 0) {//������е�һ��Ԫ��Ϊ0������ѡһ����Ϊ��ķ�����ͬʱ���л���
			for (int j = site + 1; j < n; j++) {
				if (B[j][i] != 0) {
					exchange(B[j], B[site]);//site i
					break;
				}
			}
		}
		if (B[site][i] == 0) {//���в��ò����Ѿ�ȫ��Ϊ��,�򻯼���һ��
			continue;
		}
		else {//��������Ҫ������Ԫ�أ�����������
			for (int j = site + 1; j < n; j++) {
				multiple = B[j][i] / B[site][i];
				if (!((multiple - (int)multiple) < 1e-15 || (multiple - (int)multiple) < -0.999999999999999|| 
					-(multiple - (int)multiple) < 1e-15 || -(multiple - (int)multiple) < -0.999999999999999) )
				{//multiple ��������
					for (int k = 0; k < m; k++) {
						B[j][k] = B[j][k] * B[site][i];
					}
					multiple = B[j][i] / B[site][i];
				}
				sub(B[j], B[site], multiple);
			}
			site++;
		}
	}
	int signum = 0;//�洢��Ҫ�����ĸ���
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (B[i][j] != 0) {
				//Ѱ�ҵ�һ����Ϊ��ķ�������ͷ����������j����Ҫ��
				place[j].sig = true;
				signum++;
				break;
			}
		}
	}
	
	//��ӡsignificant��������
	//cout << "the num of significant places is:"<<signum << endl;
	/*��ӡ�����Ǿ���*/
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << B[i][j] << "  ";
		}
		cout << endl;
	}
	*/

	/*
	������Է�����
	*/
	int sum = 0;
	int x = 0;//��ǰ����õĽ�ĸ���

	int story;//�洢��ǰ��������Ӧ�Ŀ���λ��

	for (int equ = 0; equ <m-signum; equ++) {//һ��Ҫ�⼸�η���?β�����м����ͽ⼸��
		int flag = 0;
		int *solution;
		solution = new int[m];
		for (int i = 0; i < m; i++) {//һά�����ʼ��
			solution[i] = -1;
		}
//		vector<int> solution(m, -1);
		for (int i = 0; i < m; i++) {//ע��flag=0����λ��
			if (place[i].sig == false) {//����β����
				if (flag == 0 && place[i].visited == false) {//����ǵ�һ��β��������ֵΪ1
					solution[i] = 1;
					story = i;//����һ��β����i��ֵΪ1������β������ֵΪ0���������������P��������Ӧ�ڿ���story
					flag = 1;
					place[i].visited = true;
					continue;
				}
				else {//����β������ֵΪ0
					solution[i] = 0;
				}
			}
		}
		sum = 0;
		for (int j = signum - 1; j >= 0; j--) {//���¶��Ͻⷽ�̣�j��Ƿ�����������
			int ele;
			for (int find = 0; find < m; find++) {//���е�һ������Ԫ�أ���Ҫ���ı���
				if (B[j][find] != 0) {
					ele = find;
					break;
				}
			}
			for (int k = ele + 1; k < m; k++) {
				sum += B[j][k] * solution[k];
			}
			solution[ele] = -sum / B[j][ele];
		}
		for (int i = 0; i < m; i++) {
			place[story].solution[i] = solution[i];
		}
	}
}
void RG::addRGNode(RGNode rg) {
	rgnode.push_back(rg);
}
//��ʹ����̼��Ŀɴ�ͼ����
void RG::ReachabilityTree(Petri ptnet) {//PN���ɿɴ���
	vector<int> M(ptnet.m, 0);
	vector<int> M0(ptnet.m, 0);//�ɴ������ڵ㣬����ʼ��ʶ
	vector<int> M1(ptnet.m, 0);
	RGNode rgnode_temp;//��ʱ�ڵ㣬���ں�����rgnode����ӽڵ�

	//�ɴ�ͼ�ĵ�һ���ڵ㣨һ���ڵ㣺��ʼ��ʶ��
	for (int i = 0; i < ptnet.m; i++) {
		M0[i] = ptnet.place[i].initialMarking;//����initialmarking������ʼ��ʶ
		rgnode_temp.m[i] = M0[i];//��ʱ�ڵ㸳ֵ
	}
	rgnode_temp.name = "M0";
	addRGNode(rgnode_temp);//����б������ӵ�һ���ڵ�
	node++;
	//�жϽ���б��л�����û�б�ǵĽڵ�
	int newNode;
	bool exist;
	while (1)
	{
		for (int i = 0; i < node; i++)
		{
			exist = false;
			if (rgnode[i].flag == 0) {//�ҵ���ʶΪ�µĽڵ�
				exist = true;
				newNode = i;
				break;
			}
		}
		if (!exist) {//�����ڱ�ʶΪ�µĽڵ�
			break;
		}
		//��ѡ��ʶΪ�µĽڵ�newNode����ΪM
		for (int i = 0; i < ptnet.m; i++) {
			M[i] = rgnode[newNode].m[i];
		}
		//�������ڵ�
		rgnode[newNode].flag = 1;

		//if ��M�����б�Ǩ�����ܷ���
		bool enable;
		int enableNumber = 0;
		for (int i = 0; i < ptnet.n; i++)
		{//�������еı�Ǩ
			enable = true;
			for (int j = 0; j < ptnet.m; j++)
			{
				if (M[j] < ptnet.A2[i][j])
				{//��Ǩti���ܷ���
					enable = false;
					break;
				}
			}
			//��Ǩ��t0��ʼ���
			if (enable)
			{//��Ǩti���Է���
				rgnode[newNode].isfirable[enableNumber] = i;
				rgnode[newNode].enableNum++;
				enableNumber++;
			}
		}
		if (rgnode[newNode].enableNum == 0)
		{//�����Ǩ���ܷ�������������ѭ��
			continue;
		}
		//����ÿ����M�¿ɷ����ı�Ǩ
		for (int i = 0; i < rgnode[newNode].enableNum; i++)
		{
			//�ɷ�����Ǩti�ı��iΪhang
			//����M1
			for (int j = 0; j < ptnet.m; j++) {
				int hang = rgnode[newNode].isfirable[i];
				if (ptnet.A[hang][j] == 2) {
					M1[j] = M[j];
				}
				else {
					M1[j] = M[j] + ptnet.A[hang][j];
				}

			}
			RGNode G;//G�ڵ����洢M1����Ϣ
			for (int i = 0; i < ptnet.m; i++) {
				G.m[i] = M1[i];
			}
			//		G.m = M1;
			//		memcpy(G.m, M1, sizeof(int)*ptnet.m);
			//		G.inset.push(newNode);//���ﱨ���ˣ�����ʱע�͵�
					/*if (isBoundless(ptnet, &G))
					{
						cerr << "The petri net is boundless!" << endl;
						exit(-1);
					}*/
					//if����б��г��ֹ�M1
			bool repeated;
			int ii;
			bool repexist = false;
			for (ii = 0; ii < node; ii++)
			{
				repeated = true;
				for (int jj = 0; jj < ptnet.m; jj++)
				{
					if (M1[jj] != rgnode[ii].m[jj]) {
						repeated = false;
						break;
					}
				}
				//������б���ֹ�M1
				if (repeated) {
					repexist = true;
					//ii���ظ��Ľڵ�����
					PRGEdge pEdge;
					pEdge = new RGEdge;
					pEdge->nextedge = NULL;
					pEdge->t = rgnode[newNode].isfirable[i];
					pEdge->target = ii;
					//	rgnode[ii].inset.push(newNode);
					RGNode *p;
					p = &rgnode[newNode];
					pEdge->nextedge = p->firstEdge;
					p->firstEdge = pEdge;
					break;
				}
			}
			//��M1��û�г��ֹ�����״̬
			if (!repexist) {
				//�������½ڵ�M1
				G.name = "M" + itos(node);
				addRGNode(G);
				//graph.rgnode[graph.node].t = graph.rgnode[newNode].isfirable[i];//00000000
				//�����½ڵ�ӵ��ڽӱ�߱���
				RGNode *p;
				PRGEdge pEdge;
				pEdge = new RGEdge;
				pEdge->nextedge = NULL;
				pEdge->t = rgnode[newNode].isfirable[i];
				pEdge->target = node;
				p = &rgnode[newNode];
				pEdge->nextedge = p->firstEdge;
				p->firstEdge = pEdge;

				node++;
			}
		}
	}
	for (int i = 1; i < node; i++) {
		for (int j = 0; j < ptnet.m; j++) {
			if (ptnet.place[j].sig == false) {
				rgnode[i].m[j] = -100;
			}
		}
	}
}
//������׼�����ʽ
void RG::standardOutput(Petri ptnet) {
	cout << "STATE_SPACE " << "STATES " << node << endl;
	cout << "STATE_SPACE " << "TRANSITIONS " << ptnet.n << endl;
}

//�ɴ�ͼ���ɵ��ļ���
void RG::PrintGraph(Petri ptnet, ofstream &outfile)
{
	outfile << "�ɴ�ͼ�ڵ����" << node << endl;
	for (int i = 0; i < node; i++) {
		outfile << "M[" << i << "]" << "(";
		for (int j = 0; j < ptnet.m; j++) {
			outfile << rgnode[i].m[j] << " ";
		}
		outfile << ")";
		PRGEdge p;
		p = rgnode[i].firstEdge;
		for (int k = 0; k < rgnode[i].enableNum; k++) {
			outfile << "[t";
			outfile << p->t;
			outfile << "M";
			outfile << p->target;
			outfile << ",";
			p = p->nextedge;
		}
		outfile << endl;
	}
}



void evaluate(int a[], int b[], int num) {
	for (int i = 0; i < num; i++) {
		a[i] = b[i];
	}
}












/*

��������ɾ��

*/

