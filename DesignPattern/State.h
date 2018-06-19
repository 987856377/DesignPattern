#pragma once
/*

意图：允许对象在内部状态发生改变时改变它的行为，对象看起来好像修改了它的类。
主要解决：对象的行为依赖于它的状态（属性），并且可以根据它的状态改变而改变它的相关行为。
何时使用：代码中包含大量与对象状态有关的条件语句。
如何解决：将各种具体的状态类抽象出来。
关键代码：通常命令模式的接口中只有一个方法。而状态模式的接口中有一个或者多个方法。而且，状态模式的实现类的方法，一般返回值，或者是改变实例变量的值。也就是说，状态模式一般和对象的状态有关。实现类的方法有不同的功能，覆盖接口中的方法。状态模式和命令模式一样，也可以用于消除 if...else 等条件选择语句。
应用实例： 1、打篮球的时候运动员可以有正常状态、不正常状态和超常状态。 2、曾侯乙编钟中，'钟是抽象接口','钟A'等是具体状态，'曾侯乙编钟'是具体环境（Context）。
优点： 1、封装了转换规则。 2、枚举可能的状态，在枚举状态之前需要确定状态种类。 3、将所有与某个状态有关的行为放到一个类中，并且可以方便地增加新的状态，只需要改变对象状态即可改变对象的行为。 4、允许状态转换逻辑与状态对象合成一体，而不是某一个巨大的条件语句块。 5、可以让多个环境对象共享一个状态对象，从而减少系统中对象的个数。
缺点： 1、状态模式的使用必然会增加系统类和对象的个数。 2、状态模式的结构与实现都较为复杂，如果使用不当将导致程序结构和代码的混乱。 3、状态模式对"开闭原则"的支持并不太好，对于可以切换状态的状态模式，增加新的状态类需要修改那些负责状态转换的源代码，否则无法切换到新增状态，而且修改某个状态类的行为也需修改对应类的源代码。
使用场景： 1、行为随状态改变而改变的场景。 2、条件、分支语句的代替者。
注意事项：在行为受状态约束的时候使用状态模式，而且状态不超过 5 个。

*/


// Purpose.  State design pattern - an FSM with two states and
// two events (distributed transition logic - logic in the
// derived state classes)

#include <iostream>                     \ Event    on      off
using namespace std;               State \      ------ - ------ -
ON          nothing    OFF
class Machine {
	OFF           ON     nothing
		class State* current;
public:
	Machine();
	void setCurrent(State* s) { current = s; }
	void on();
	void off();
};

class State {
public:
	virtual void on(Machine* m) { cout << "   already ON\n"; }
	virtual void off(Machine* m) { cout << "   already OFF\n"; }
};

void Machine::on() { current->on(this); }
void Machine::off() { current->off(this); }

class ON : public State {
public:
	ON() { cout << "   ON-ctor "; };
	~ON() { cout << "   dtor-ON\n"; };
	void off(Machine* m);
};

class OFF : public State {
public:
	OFF() { cout << "   OFF-ctor "; };
	~OFF() { cout << "   dtor-OFF\n"; };
	void on(Machine* m) {
		cout << "   going from OFF to ON";
		m->setCurrent(new ON());
		delete this;
	}
};

void ON::off(Machine* m) {
	cout << "   going from ON to OFF";
	m->setCurrent(new OFF());
	delete this;
}

Machine::Machine() { current = new OFF();  cout << '\n'; }

void main(void) {
	void (Machine::*ptrs[])() = { Machine::off, Machine::on };
	Machine fsm;
	int num;
	while (1) {
		cout << "Enter 0/1: ";
		cin >> num;
		(fsm.*ptrs[num])();
	}
}

//    OFF-ctor
// Enter 0/1: 0
//    already OFF
// Enter 0/1: 1
//    going from OFF to ON   ON-ctor    dtor-OFF
// Enter 0/1: 1
//    already ON
// Enter 0/1: 0
//    going from ON to OFF   OFF-ctor    dtor-ON
// Enter 0/1: 1
//    going from OFF to ON   ON-ctor    dtor-OFF
// Enter 0/1: 0
//    going from ON to OFF   OFF-ctor    dtor-ON
// Enter 0/1: 0
//    already OFF
// Enter 0/1:



//
//// Purpose.  State design pattern - an FSM with two states and two events
//// (distributed transition logic - logic in the derived state classes)
//
//// State\Event     Suck up money      Drive through
////
//// RedLight          you're a            you're   
////                    victim,             dead,
////                 maybe change       change to RED
////                   to GREEN
////
//// GreenLight        you're an         you're free
////                     idiot           but you're
////                                  still a victim,
////                                   change to RED
//
//#include <iostream>
//#include <ctime>
//using namespace std;
//
//class FSM {
//	class State* current;
//public:
//	FSM();
//	void setCurrent(State* s) { current = s; }
//	void suckUpMoney(int);
//	void carDrivesThrough();
//};
//
//class State {
//	int total;
//protected:
//	int getTotal() { return total; }
//public:
//	State() { total = 0; }
//	virtual void suckUpMoney(int in, FSM* fsm) {
//		total += in;
//		cout << "total is " << total << '\n';
//	}
//	virtual void carDrivesThrough(FSM* fsm) = 0;
//};
//
//class GreenLight : public State {
//public:
//	GreenLight() { cout << "GREEN light\n"; }
//	void suckUpMoney(int in, FSM* fsm) {
//		cout << "      You're an idiot, ";
//		State::suckUpMoney(in, fsm);
//	}
//	void carDrivesThrough(FSM* fsm);
//};
//
//class RedLight : public State {
//public:
//	RedLight() { cout << "RED light\n"; }
//	void suckUpMoney(int in, FSM* fsm) {
//		cout << "      ";
//		State::suckUpMoney(in, fsm);
//		if (getTotal() >= 50) {
//			fsm->setCurrent(new GreenLight);
//			delete this;
//		}
//	}
//	void carDrivesThrough(FSM* fsm) {
//		cout << "Sirens!!  Heat-seeking missile!!  Confiscate net worth!!\n";
//		fsm->setCurrent(new RedLight);
//		delete this;
//	}
//};
//
//FSM::FSM() {
//	current = new RedLight();
//}
//void FSM::suckUpMoney(int in) {
//	current->suckUpMoney(in, this);
//}
//void FSM::carDrivesThrough() {
//	current->carDrivesThrough(this);
//}
//void GreenLight::carDrivesThrough(FSM* fsm) {
//	cout << "Good-bye sucker!!\n";
//	fsm->setCurrent(new RedLight);
//	delete this;
//}
//
//int getCoin() {
//	static int choices[3] = { 5, 10, 25 };
//	return choices[rand() % 3];
//}
//
//void main(void) {
//	srand(time(0));
//	FSM fsm;
//	int ans;
//	while (true) {
//		cout << "   Shell out (1), Drive thru (2), Exit (0): ";
//		cin >> ans;
//		if (ans == 1) fsm.suckUpMoney(getCoin());
//		else if (ans == 2) fsm.carDrivesThrough();
//		else break;
//	}
//}
//
//
//
//// Purpose.  State demo (centralized transition logic - logic in the FSM)
//// 
//// Discussion.  Who defines the state transitions?  The State pattern does not
//// specify which participant defines the criteria for state transitions.  The
//// logic can be implemented entirely in the Context (FSM).  It is generally
//// more flexible and appropriate, however, to let the State subclasses them-
//// selves specify their successor state and when to make the transition.  This
//// requires adding an interface to the Context that lets State objects set the
//// Context's current state explicitly.  A disadvantage of decentralization is
//// that State subclasses will be coupled to other sibling subclasses. [GOF308]
//
//#include <iostream.h>
//
//class FSMstate {
//public:
//	virtual void on() { cout << "undefined combo" << endl; }
//	virtual void off() { cout << "undefined combo" << endl; }
//	virtual void ack() { cout << "undefined combo" << endl; }
//};
//
//class FSM {
//public:
//	FSM();
//	void on() { states[current]->on();  current = next[current][0]; }
//	void off() { states[current]->off(); current = next[current][1]; }
//	void ack() { states[current]->ack(); current = next[current][2]; }
//private:
//	FSMstate * states[3];
//	int        current;
//	int        next[3][3];
//};
//
//class A : public FSMstate {
//public:
//	void on() { cout << "A, on ==> A" << endl; }
//	void off() { cout << "A, off ==> B" << endl; }
//	void ack() { cout << "A, ack ==> C" << endl; }
//};
//class B : public FSMstate {
//public:
//	void off() { cout << "B, off ==> A" << endl; }
//	void ack() { cout << "B, ack ==> C" << endl; }
//};
//class C : public FSMstate {
//public:
//	void ack() { cout << "C, ack ==> B" << endl; }
//};
//
//FSM::FSM() {
//	states[0] = new A; states[1] = new B; states[2] = new C;
//	current = 1;
//	next[0][0] = 0; next[0][1] = 1; next[0][2] = 2;
//	next[1][0] = 1; next[1][1] = 0; next[1][2] = 2;
//	next[2][0] = 2; next[2][1] = 2; next[2][2] = 1;
//}
//
//enum     Message { On, Off, Ack };
//Message  messageArray[10] = { On,Off,Off,Ack,Ack,Ack,Ack,On,Off,Off };
//
//void main(void) {
//	FSM  fsm;
//	for (int i = 0; i < 10; i++) {
//		if (messageArray[i] == On)        fsm.on();
//		else if (messageArray[i] == Off)  fsm.off();
//		else if (messageArray[i] == Ack)  fsm.ack();
//	}
//}
//
//// undefined combo           // B, ack ==> C
//// B, off ==> A              // C, ack ==> B
//// A, off ==> B              // undefined combo
//// B, ack ==> C              // B, off ==> A
//// C, ack ==> B              // A, off ==> B