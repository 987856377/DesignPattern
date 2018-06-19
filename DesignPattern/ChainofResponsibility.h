#pragma once
#include <vector>
#include <ctime>
/*

��ͼ��������������������������һ���ö�������п��ܽ������󣬽���Щ�������ӳ�һ����������������������������ֱ���ж�������Ϊֹ��
��Ҫ�����ְ�����ϵĴ����߸��������󣬿ͻ�ֻ��Ҫ�������͵�ְ�����ϼ��ɣ������������Ĵ���ϸ�ں�����Ĵ��ݣ�����ְ����������ķ����ߺ�����Ĵ����߽����ˡ�
��ʱʹ�ã��ڴ�����Ϣ��ʱ���Թ��˺ܶ����
��ν�������ص��඼ʵ��ͳһ�ӿڡ�
�ؼ����룺Handler ����ۺ����Լ����� HanleRequest ���ж��Ƿ���ʣ����û�ﵽ���������´��ݣ���˭����֮ǰ set ��ȥ��
Ӧ��ʵ���� 1����¥���е�"���Ĵ���"�� 
			2��JS �е��¼�ð�ݡ� 
			3��JAVA WEB �� Apache Tomcat �� Encoding �Ĵ���Struts2 ����������jsp servlet �� Filter��
�ŵ㣺 1��������϶ȡ���������ķ����ߺͽ����߽�� 
		2�����˶���ʹ�ö�����Ҫ֪�����Ľṹ�� 
		3����ǿ������ָ��ְ�������ԡ�ͨ���ı����ڵĳ�Ա���ߵ������ǵĴ�������̬����������ɾ�����Ρ� 
		4�������µ���������ܷ��㡣
ȱ�㣺 1�����ܱ�֤����һ�������ա� 
		2��ϵͳ���ܽ��ܵ�һ��Ӱ�죬�����ڽ��д������ʱ��̫���㣬���ܻ����ѭ�����á� 
		3�����ܲ����׹۲�����ʱ���������а��ڳ���
ʹ�ó����� 1���ж��������Դ���ͬһ�����󣬾����ĸ������������������ʱ���Զ�ȷ���� 
		2���ڲ���ȷָ�������ߵ�����£����������е�һ���ύһ������ 
		3���ɶ�ָ̬��һ�����������
ע������� JAVA WEB �������ܶ�Ӧ�á�

*/

class Base {
	Base* next;                // 1. "next" pointer in the base class
public:
	Base() { next = 0; }
	void setNext(Base* n) { next = n; }
	void add(Base* n) { if (next) next->add(n); else next = n; }
	// 2. The "chain" method in the base class always delegates to the next obj
	virtual void handle(int i) { next->handle(i); }
};

class Handler1 : public Base {
public:
	/*virtual*/ void handle(int i) {
		if (rand() % 3) {       // 3. Don't handle requests 3 times out of 4
			cout << "H1 passsed " << i << "  ";
			Base::handle(i);   // 3. Delegate to the base class
		}
		else
			cout << "H1 handled " << i << "  ";
	}
};

class Handler2 : public Base {
public:
	/*virtual*/ void handle(int i) {
		if (rand() % 3) { cout << "H2 passsed " << i << "  "; Base::handle(i); }
		else cout << "H2 handled " << i << "  ";
	}
};

class Handler3 : public Base {
public:
	/*virtual*/ void handle(int i) {
		if (rand() % 3) { cout << "H3 passsed " << i << "  "; Base::handle(i); }
		else cout << "H3 handled " << i << "  ";
	}
};



//// Purpose.  Chain of Responsibility and Composite
//
//// 1. Put a "next" pointer in the base class
//// 2. The "chain" method in the base class always delegates to the next object
//// 3. If the derived classes cannot handle, they delegate to the base class
//
//#include <iostream>
//#include <vector>
//#include <ctime>
//using namespace std;
//
//class Component {
//	int        value;
//	Component* next;             // 1. "next" pointer in the base class
//public:
//	Component(int v, Component* n) { value = v;  next = n; }
//	void setNext(Component* n) { next = n; }
//	virtual void traverse() { cout << value << ' '; }
//	// 2. The "chain" method in the base class always delegates to the next obj
//	virtual void volunteer() { next->volunteer(); }
//};
//
//class Primitive : public Component {
//public:
//	Primitive(int val, Component* n = 0) : Component(val, n) { }
//	/*virtual*/ void volunteer() {
//		Component::traverse();
//		// 3. Primitive objects don't handle volunteer requests 5 times out of 6
//		if (rand() * 100 % 6 != 0)
//			// 3. Delegate to the base class
//			Component::volunteer();
//	}
//};
//
//class Composite : public Component {
//	vector<Component*> children;
//public:
//	Composite(int val, Component* n = 0) : Component(val, n) { }
//	void add(Component* c) { children.push_back(c); }
//	/*virtual*/ void traverse() {
//		Component::traverse();
//		for (int i = 0; i < children.size(); i++)
//			children[i]->traverse();
//	}
//	// 3. Composite objects never handle volunteer requests
//	/*virtual*/ void volunteer() { Component::volunteer(); }
//};
//
//void main(void) {
//	srand(time(0));                             // 1
//	Primitive seven(7);                           // |
//	Primitive six(6, &seven);                     // +-- 2
//	Composite three(3, &six);                     // |   |
//	three.add(&six);  three.add(&seven);        // |   +-- 4 5
//	Primitive five(5, &three);                    // |
//	Primitive four(4, &five);                     // +-- 3
//	Composite two(2, &four);                      // |   |
//	two.add(&four);   two.add(&five);           // |   +-- 6 7
//	Composite one(1, &two);                       // |
//	Primitive nine(9, &one);                      // +-- 8 9
//	Primitive eight(8, &nine);
//	one.add(&two);  one.add(&three);  one.add(&eight);  one.add(&nine);
//	seven.setNext(&eight);
//	cout << "traverse: ";   one.traverse();   cout << '\n';
//	for (int i = 0; i < 8; i++) {
//		one.volunteer();  cout << '\n';
//	}
//}



//// Purpose.  Chain of Responsibility - links bid on job, chain assigns job
////
//// 1. Base class maintains a "next" pointer
//// 2. Each "link" does its part to handle (and/or pass on) the request
//// 3. Client "launches and leaves" each request with the chain
//// 4. The current bid and bidder are maintained in chain static members
//// 5. The last link in the chain assigns the job to the low bidder
//
//#include <iostream>
//#include <ctime>
//using namespace std;
//
//class Link {
//	int   id;
//	Link* next;                       // 1. "next" pointer
//	static int   theBid;              // 4. Current bid and bidder
//	static Link* bidder;
//public:
//	Link(int num) { id = num;  next = 0; }
//	void addLast(Link* l) {
//		if (next) next->addLast(l);  // 2. Handle and/or pass on
//		else      next = l;
//	}
//	void bid() {
//		int num = rand() % 9;
//		cout << id << '-' << num << "  ";
//		if (num < theBid) {
//			theBid = num;               // 4. Current bid and bidder
//			bidder = this;
//		}
//		if (next) next->bid();         // 2. Handle and/or pass on
//		else      bidder->execute();   // 5. The last 1 assigns the job
//	}
//	void execute() {
//		cout << id << " is executing\n";
//		theBid = 999;
//	}
//};
//int   Link::theBid = 999;            // 4. Current bid and bidder
//Link* Link::bidder = 0;
//
//void main(void) {
//	Link chain(1);
//	for (int i = 2; i < 7; i++)
//		chain.addLast(new Link(i));
//	srand(time(0));
//	for (i = 0; i < 10; i++)
//		chain.bid();                   // 3. Client "launches & leaves"
//}
