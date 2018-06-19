#pragma once
#include <vector>
#include <ctime>
/*

意图：避免请求发送者与接收者耦合在一起，让多个对象都有可能接收请求，将这些对象连接成一条链，并且沿着这条链传递请求，直到有对象处理它为止。
主要解决：职责链上的处理者负责处理请求，客户只需要将请求发送到职责链上即可，无须关心请求的处理细节和请求的传递，所以职责链将请求的发送者和请求的处理者解耦了。
何时使用：在处理消息的时候以过滤很多道。
如何解决：拦截的类都实现统一接口。
关键代码：Handler 里面聚合它自己，在 HanleRequest 里判断是否合适，如果没达到条件则向下传递，向谁传递之前 set 进去。
应用实例： 1、红楼梦中的"击鼓传花"。 
			2、JS 中的事件冒泡。 
			3、JAVA WEB 中 Apache Tomcat 对 Encoding 的处理，Struts2 的拦截器，jsp servlet 的 Filter。
优点： 1、降低耦合度。它将请求的发送者和接收者解耦。 
		2、简化了对象。使得对象不需要知道链的结构。 
		3、增强给对象指派职责的灵活性。通过改变链内的成员或者调动它们的次序，允许动态地新增或者删除责任。 
		4、增加新的请求处理类很方便。
缺点： 1、不能保证请求一定被接收。 
		2、系统性能将受到一定影响，而且在进行代码调试时不太方便，可能会造成循环调用。 
		3、可能不容易观察运行时的特征，有碍于除错。
使用场景： 1、有多个对象可以处理同一个请求，具体哪个对象处理该请求由运行时刻自动确定。 
		2、在不明确指定接收者的情况下，向多个对象中的一个提交一个请求。 
		3、可动态指定一组对象处理请求。
注意事项：在 JAVA WEB 中遇到很多应用。

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
