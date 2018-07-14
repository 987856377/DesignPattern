#pragma once
#include <vector>
/*

当对象间存在一对多关系时，则使用观察者模式（Observer Pattern）。比如，当一个对象被修改时，则会自动通知它的依赖对象。观察者模式属于行为型模式。

意图：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
主要解决：一个对象状态改变给其他对象通知的问题，而且要考虑到易用和低耦合，保证高度的协作。
何时使用：一个对象（目标对象）的状态发生改变，所有的依赖对象（观察者对象）都将得到通知，进行广播通知。
如何解决：使用面向对象技术，可以将这种依赖关系弱化。
关键代码：在抽象类里有一个 ArrayList 存放观察者们。
应用实例： 1、拍卖的时候，拍卖师观察最高标价，然后通知给其他竞价者竞价。 2、西游记里面悟空请求菩萨降服红孩儿，菩萨洒了一地水招来一个老乌龟，这个乌龟就是观察者，他观察菩萨洒水这个动作。
优点： 1、观察者和被观察者是抽象耦合的。 2、建立一套触发机制。
缺点： 1、如果一个被观察者对象有很多的直接和间接的观察者的话，将所有的观察者都通知到会花费很多时间。 2、如果在观察者和观察目标之间有循环依赖的话，观察目标会触发它们之间进行循环调用，可能导致系统崩溃。 3、观察者模式没有相应的机制让观察者知道所观察的目标对象是怎么发生变化的，而仅仅只是知道观察目标发生了变化。
使用场景：
一个抽象模型有两个方面，其中一个方面依赖于另一个方面。将这些方面封装在独立的对象中使它们可以各自独立地改变和复用。
一个对象的改变将导致其他一个或多个对象也发生改变，而不知道具体有多少对象将发生改变，可以降低对象之间的耦合度。
一个对象必须通知其他对象，而并不知道这些对象是谁。
需要在系统中创建一个触发链，A对象的行为将影响B对象，B对象的行为将影响C对象……，可以使用观察者模式创建一种链式触发机制。
注意事项： 1、JAVA 中已经有了对观察者模式的支持类。 2、避免循环引用。 3、如果顺序执行，某一观察者错误会导致系统卡壳，一般采用异步方式。

*/


class Subject {                      // 1. "independent" functionality
	vector<class Observer*> views;    // 3. Coupled only to "interface"
	int value;
public:
	void attach(Observer* obs) { views.push_back(obs); }
	void setVal(int val) { value = val;  notify(); }
	int  getVal() { return value; }
	void notify();
};

class Observer {                     // 2. "dependent" functionality
	Subject* model;
	int      denom;
public:
	Observer(Subject* mod, int div) {
		model = mod;  denom = div;
		// 4. Observers register themselves with the Subject
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject * getSubject() { return model; }
	int      getDivisor() { return denom; }
};

void Subject::notify() {             // 5. Publisher broadcasts
	for (int i = 0; i < views.size(); i++) views[i]->update();
}

class DivObserver : public Observer {
public:
	DivObserver(Subject* mod, int div) : Observer(mod, div) { }
	void update() {                   // 6. "Pull" information of interest
		int v = getSubject()->getVal(), d = getDivisor();
		cout << v << " div " << d << " is " << v / d << '\n';
	}
};

class ModObserver : public Observer {
public:
	ModObserver(Subject* mod, int div) : Observer(mod, div) { }
	void update() {
		int v = getSubject()->getVal(), d = getDivisor();
		cout << v << " mod " << d << " is " << v % d << '\n';
	}
};
//
//void main(void) {
//	Subject      subj;
//	DivObserver  divObs1(&subj, 4);  // 7. Client configures the number and
//	DivObserver  divObs2(&subj, 3);  //    type of Observers
//	ModObserver  modObs3(&subj, 3);
//	subj.setVal(14);
//}
//
//
//// Purpose.  Observer design pattern, class inheritance vs type inheritance
//
//// SensorSystem is the "subject".  Lighting, Gates, and Surveillance are the
//// "views".  The subject is only coupled to the "abstraction" of AlarmListener.
//
//// An object's class defines how the object is implemented.  In contrast, an
//// object's type only refers to its interface.  Class inheritance defines an
//// object's implementation in terms of another object's implementation.  Type
//// inheritance describes when an object can be used in place of another.
//// [GoF, pp13-17]
//
//#include <iostream>
//#include <vector>
//using namespace std;
//
//class AlarmListener { public: virtual void alarm() = 0; };
//
//class SensorSystem {
//	vector<AlarmListener*> listeners;
//public:
//	void attach(AlarmListener* al) { listeners.push_back(al); }
//	void soundTheAlarm() {
//		for (int i = 0; i < listeners.size(); i++)
//			listeners[i]->alarm();
//	}
//};
//
//class Lighting : public AlarmListener {
//public: /*virtual*/ void alarm() { cout << "lights up" << '\n'; }
//};
//
//class Gates : public AlarmListener {
//public: /*virtual*/ void alarm() { cout << "gates close" << '\n'; }
//};
//
//class CheckList {
//	virtual void localize() { cout << "   establish a perimeter" << '\n'; }
//	virtual void isolate() { cout << "   isolate the grid" << '\n'; }
//	virtual void identify() { cout << "   identify the source" << '\n'; }
//public:
//	void byTheNumbers() {  // Template Method design pattern
//		localize();
//		isolate();
//		identify();
//	}
//};
//// class inheri.  // type inheritance
//class Surveillance : public CheckList, public AlarmListener {
//	/*virtual*/ void isolate() { cout << "   train the cameras" << '\n'; }
//public:
//	/*virtual*/ void alarm() {
//		cout << "Surveillance - by the numbers:" << '\n';
//		byTheNumbers();
//	}
//};
//
//void main(void) {
//	SensorSystem ss;
//	ss.attach(&Gates());
//	ss.attach(&Lighting());
//	ss.attach(&Surveillance());
//	ss.soundTheAlarm();
//}
//
//// gates close
//// lights up
//// Surveillance - by the numbers:
////    establish a perimeter
////    train the cameras
////    identify the source
//
//
//
//
//// Purpose.  Observer and Mediator demo
//// 
//// Observer - 1. Sender is coupled to a Receiver interface
////            2. Receivers register with Sender
////            3. Sender broadcasts (in the blind) to all Receivers
//// 
//// Mediator - 4. Sender(s) has handle to Mediator
////            5. Mediator has handle to Receiver(s)
////            6. Sender(s) sends to Mediator
////            7. Mediator sends to Receiver(s)
//
//#include <iostream>
//#include <vector>
//using namespace std;
//void gotoxy(int, int);
//
//class Observer { public: virtual void update(int) = 0; };
//
//class Mediator {
//	vector<Observer*> groups[3];         // 1. Sender is coupled to an interface
//public:
//	enum Message { ODD, EVEN, THREE };   // 1. Sender is coupled to an interface
//	void attach(Observer* o, Message type) { groups[type].push_back(o); }
//	void disseminate(int num) {
//		if (num % 2 == 1)  // odd      // 3,7. Sender/Mediator broadcasts
//			for (int i = 0; i < groups[0].size(); i++) groups[0][i]->update(num);
//		else               // even
//			for (int i = 0; i < groups[1].size(); i++) groups[1][i]->update(num);
//		if (num % 3 == 0)  // /3
//			for (int i = 0; i < groups[2].size(); i++) groups[2][i]->update(num);
//	}
//};
//
//class OddObserver : public Observer {
//	int col, row;
//public:
//	OddObserver(Mediator& med, int c) {
//		col = c;           row = 3;
//		gotoxy(col, 1);  cout << "Odd";
//		gotoxy(col, 2);  cout << "---";
//		med.attach(this, Mediator::ODD);  // 2,5. Receivers register with Sender
//	}
//	void update(int num) { gotoxy(col, row++);  cout << num; }
//};
//
//class EvenObserver : public Observer {
//	int col, row;
//public:
//	EvenObserver(Mediator& med, int c) {
//		col = c;           row = 3;
//		gotoxy(col, 1);  cout << "/2";
//		gotoxy(col, 2);  cout << "--";
//		med.attach(this, Mediator::EVEN);
//	}
//	void update(int num) { gotoxy(col, row++);  cout << num; }
//};
//
//class ThreeObserver : public Observer {
//	int col, row;
//public:
//	ThreeObserver(Mediator& med, int c) {
//		col = c;           row = 3;
//		gotoxy(col, 1);  cout << "/3";
//		gotoxy(col, 2);  cout << "--";
//		med.attach(this, Mediator::THREE);
//	}
//	void update(int num) { gotoxy(col, row++);  cout << num; }
//};
//
//class Publisher {
//public:            // 6. Sender sends to Mediator
//	Publisher(Mediator& med) { for (int i = 1; i < 10; i++) med.disseminate(i); }
//};
//
//void main(void) {
//	Mediator   mediator;
//	OddObserver(mediator, 1);
//	EvenObserver(mediator, 11);
//	ThreeObserver(mediator, 21);
//	Publisher  producer(mediator);  // 4. Sender has handle to Mediator
//}
//
//// Odd       /2        /3
//// ---       --        --
//// 1         2         3
//// 3         4         6
//// 5         6         9
//// 7         8
//// 9
//
//
//
//
//// Purpose.  TypedMessage - embellished Observer, decoupled messaging
////
//// Messages inherit from TypedMessage<self>
//// Message listeners inherit from many Message::Handlers
//// Application tells message to publish/broadcast/notify
//// Messages are the subject (receive registrations from subscribers)
//// Subsystems are the observers (receive broadcast messages)
//// TypedMessage accomodates everything: registration, containment, and
////   notification of observers
//
//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
//
//template <class T>
//class TypedMessage {
//	static vector<Handler*> registry;
//public:
//	class Handler {
//	public:
//		Handler() { TypedMessage<T>::registerHandler(this); }
//		virtual void handleEvent(const T* t) = 0;
//	};
//	void notify() {
//		for (int i = 0; i < registry.size(); i++)
//			registry.at(i)->handleEvent((T*)this);
//	}
//	static void registerHandler(Handler* h) { registry.push_back(h); }
//};
//
//class On : public TypedMessage<On> {
//	string comment;
//public:
//	On(string str) { comment = str; }
//	void start() const { cout << "OnEvent.start - " << comment << '\n'; }
//};
//vector<TypedMessage<On>::Handler*> TypedMessage<On>::registry;
//
//class Off : public TypedMessage<Off> {
//	string comment;
//public:
//	Off(string str) { comment = str; }
//	void stop() const { cout << "OffEvent.stop - " << comment << '\n'; }
//};
//vector<TypedMessage<Off>::Handler*> TypedMessage<Off>::registry;
//
//class MasterConsole : public On::Handler, public Off::Handler {
//public:
//	void handleEvent(const On* msg) {
//		cout << "MasterConsole - ";  msg->start();
//	}
//	void handleEvent(const Off* msg) {
//		cout << "MasterConsole - ";  msg->stop();
//	}
//};
//
//class PowerMonitor : public On::Handler {
//public:
//	void handleEvent(const On* msg) {
//		cout << "PowerMonitor - ";  msg->start();
//	}
//};
//
//void main(void) {
//	MasterConsole  mc;
//	PowerMonitor   pm;
//	On oneEvent("lights");  Off thrEvent("elevators");
//	On twoEvent("hvac");    Off fouEvent("frontDoor");
//	oneEvent.notify();  twoEvent.notify();
//	thrEvent.notify();  fouEvent.notify();
//}
//
//// MasterConsole - OnEvent.start - lights
//// PowerMonitor - OnEvent.start - lights
//// MasterConsole - OnEvent.start - hvac
//// PowerMonitor - OnEvent.start - hvac
// MasterConsole - OffEvent.stop - elevators
// MasterConsole - OffEvent.stop - frontDoor
