#pragma once
/*

��ͼ������������ڲ�״̬�����ı�ʱ�ı�������Ϊ���������������޸��������ࡣ
��Ҫ������������Ϊ����������״̬�����ԣ������ҿ��Ը�������״̬�ı���ı����������Ϊ��
��ʱʹ�ã������а������������״̬�йص�������䡣
��ν���������־����״̬����������
�ؼ����룺ͨ������ģʽ�Ľӿ���ֻ��һ����������״̬ģʽ�Ľӿ�����һ�����߶�����������ң�״̬ģʽ��ʵ����ķ�����һ�㷵��ֵ�������Ǹı�ʵ��������ֵ��Ҳ����˵��״̬ģʽһ��Ͷ����״̬�йء�ʵ����ķ����в�ͬ�Ĺ��ܣ����ǽӿ��еķ�����״̬ģʽ������ģʽһ����Ҳ������������ if...else ������ѡ����䡣
Ӧ��ʵ���� 1���������ʱ���˶�Ա����������״̬��������״̬�ͳ���״̬�� 2�������ұ����У�'���ǳ���ӿ�','��A'���Ǿ���״̬��'�����ұ���'�Ǿ��廷����Context����
�ŵ㣺 1����װ��ת������ 2��ö�ٿ��ܵ�״̬����ö��״̬֮ǰ��Ҫȷ��״̬���ࡣ 3����������ĳ��״̬�йص���Ϊ�ŵ�һ�����У����ҿ��Է���������µ�״̬��ֻ��Ҫ�ı����״̬���ɸı�������Ϊ�� 4������״̬ת���߼���״̬����ϳ�һ�壬������ĳһ���޴���������顣 5�������ö������������һ��״̬���󣬴Ӷ�����ϵͳ�ж���ĸ�����
ȱ�㣺 1��״̬ģʽ��ʹ�ñ�Ȼ������ϵͳ��Ͷ���ĸ����� 2��״̬ģʽ�Ľṹ��ʵ�ֶ���Ϊ���ӣ����ʹ�ò��������³���ṹ�ʹ���Ļ��ҡ� 3��״̬ģʽ��"����ԭ��"��֧�ֲ���̫�ã����ڿ����л�״̬��״̬ģʽ�������µ�״̬����Ҫ�޸���Щ����״̬ת����Դ���룬�����޷��л�������״̬�������޸�ĳ��״̬�����ΪҲ���޸Ķ�Ӧ���Դ���롣
ʹ�ó����� 1����Ϊ��״̬�ı���ı�ĳ����� 2����������֧���Ĵ����ߡ�
ע���������Ϊ��״̬Լ����ʱ��ʹ��״̬ģʽ������״̬������ 5 ����

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