#pragma once
#include <vector>
/*

����ģʽ��Command Pattern����һ���������������ģʽ����������Ϊ��ģʽ���������������ʽ�����ڶ����У����������ö���
���ö���Ѱ�ҿ��Դ��������ĺ��ʵĶ��󣬲��Ѹ��������Ӧ�Ķ��󣬸ö���ִ�����

��ͼ����һ�������װ��һ�����󣬴Ӷ�ʹ�������ò�ͬ������Կͻ����в�������
��Ҫ����������ϵͳ�У���Ϊ����������Ϊʵ����ͨ����һ�ֽ���ϵĹ�ϵ��
		��ĳЩ���ϣ�������Ҫ����Ϊ���м�¼������������������ȴ���ʱ�������޷������仯�Ľ���ϵ���ƾͲ�̫���ʡ�
��ʱʹ�ã���ĳЩ���ϣ�����Ҫ����Ϊ����"��¼������/����������"�ȴ���
			�����޷������仯�Ľ�����ǲ����ʵġ�����������£���ν�"��Ϊ������"��"��Ϊʵ����"���
			��һ����Ϊ����Ϊ���󣬿���ʵ�ֶ���֮�������ϡ�
��ν����ͨ�������ߵ��ý�����ִ�����˳�򣺵����ߡ������ߡ����
�ؼ����룺����������ɫ��1��received ����������ִ�ж��� 
		2��Command 3��invoker ʹ�������������
Ӧ��ʵ����struts 1 �е� action ���Ŀ����� ActionServlet ֻ��һ�����൱�� Invoker��
			��ģ�Ͳ��������Ų�ͬ��Ӧ���в�ͬ��ģ���࣬�൱�ھ���� Command��
�ŵ㣺 1��������ϵͳ��϶ȡ� 2���µ�������Ժ�������ӵ�ϵͳ��ȥ��
ȱ�㣺ʹ������ģʽ���ܻᵼ��ĳЩϵͳ�й���ľ��������ࡣ
ʹ�ó�������Ϊ������ĵط�������ʹ������ģʽ�����磺 1��GUI ��ÿһ����ť����һ����� 2��ģ�� CMD��
ע�����ϵͳ��Ҫ֧������ĳ���(Undo)�����ͻָ�(Redo)������Ҳ���Կ���ʹ������ģʽ��������ģʽ����չ��

*/


// Purpose.  Command design pattern

// 1. Create a class that encapsulates some number of the following:
//       a "receiver" object
//       the method to invoke 
//       the arguments to pass
// 2. Instantiate an object for each "callback"
// 3. Pass each object to its future "sender"
// 4. When the sender is ready to callback to the receiver, it calls execute()

class Person;

class Command {                // 1. Create a class that encapsulates an object
	Person*  object;            //    and a member function
	void (Person::*method)();   // a pointer to a member function (the attribute's name is "method")
public:                           
	Command(Person* obj = 0, void (Person::*meth)() = 0) {
		object = obj;            // the argument's name is "meth"
		method = meth;
	}
	void execute() {
		(object->*method)();     // invoke the method on the object
	}
};

class Person {
	string   name;
	Command  cmd;               // cmd is a "black box", it is a method invocation promoted to "full object status"
public:                            
	Person(string n, Command c) : cmd(c) {
		name = n;
	}
	void talk() {                // "this" is the sender, cmd has the receiver
		std::cout << name.data() << " is talking" << std::endl;
		cmd.execute();           // ask the "black box" to callback the receiver
	}
	void passOn() {
		std::cout << name.data() << " is passing on" << std::endl;
		cmd.execute();           // 4. When the sender is ready to callback to the receiver, it calls execute()
	}                               
	void gossip() {
		std::cout << name.data() << " is gossiping" << std::endl;
		cmd.execute();
	}
	void listen() {
		std::cout << name.data() << " is listening" << std::endl;
	}
};

//// Purpose.  Simple and "macro" commands
//// 
//// Discussion.  Encapsulate a request as an object.  SimpleCommand
//// maintains a binding between a receiver object and an action stored as a
//// pointer to a member function.  MacroCommand maintains a sequence of
//// Commands.  No explicit receiver is required because the subcommands
//// already define their receiver.  MacroCommand may contain MacroCommands.
//
//class Number {
//public:
//	void dubble(int& value) { value *= 2; }
//};
//
//class Command { public: virtual void execute(int&) = 0; };
//
//class SimpleCommand : public Command {
//	typedef void (Number::* Action)(int&);
//	Number* receiver;
//	Action  action;
//public:
//	SimpleCommand(Number* rec, Action act) {
//		receiver = rec;
//		action = act;
//	}
//	/*virtual*/ void execute(int& num) { (receiver->*action)(num); }
//};
//
//class MacroCommand : public Command {
//	vector<Command*> list;
//public:
//	void add(Command* cmd) { list.push_back(cmd); }
//	/*virtual*/ void execute(int& num) {
//		for (int i = 0; i < list.size(); i++)
//			list[i]->execute(num);
//	}
//};
//
//void main(void) {
//	Number object;
//	Command* commands[3];
//	commands[0] = &SimpleCommand(&object, &Number::dubble);
//
//	MacroCommand two;
//	two.add(commands[0]);   two.add(commands[0]);
//	commands[1] = &two;
//
//	MacroCommand four;
//	four.add(&two);   four.add(&two);
//	commands[2] = &four;
//
//	int num, index;
//	while (true) {
//		cout << "Enter number selection (0=2x 1=4x 2=16x): ";
//		cin >> num >> index;
//		commands[index]->execute(num);
//		cout << "   " << num << '\n';
//	}
//}
//
//// Enter number selection (0=2x 1=4x 2=16x): 3 0
////    6
//// Enter number selection (0=2x 1=4x 2=16x): 3 1
////    12
//// Enter number selection (0=2x 1=4x 2=16x): 3 2
////    48
//// Enter number selection (0=2x 1=4x 2=16x): 4 0
////    8
//// Enter number selection (0=2x 1=4x 2=16x): 4 1
////    16
//// Enter number selection (0=2x 1=4x 2=16x): 4 2
////    64
//
//
//
//
//// Purpose.  Command design pattern and inheritance
////
//// Discussion.  The Command pattern promotes a deferred method invocation to
//// full object status.  Each Command object is a "black box" - it is opaque to
//// its holder/user.  Here, a portfolio's heterogeneous collection of financial
//// instruments is being treated homogeneously, because, they all inherit from
//// a common base class, and, they all have a "convert to currency" method with
//// a common signature.
//
//class Instrument { public: virtual ~Instrument() { } };
//
//class IOU : public Instrument {
//	int amount;
//public:
//	IOU(int in) { amount = in; }
//	int payUp() { return amount; }
//};
//
//class Check : public Instrument {
//	int amount;
//public:
//	Check(int in) { amount = in; }
//	int cash() { return amount; }
//};
//
//class Stock : public Instrument {
//	int amount;
//public:
//	Stock(int in) { amount = in; }
//	int redeem() { return amount; }
//};
//
//class Command {
//public:
//	typedef int (Instrument::*Action)();
//	Command(Instrument* o, Action m) {
//		object = o;
//		method = m;
//	}
//	int execute() { return (object->*method)(); }
//private:
//	Instrument * object;
//	Action      method;
//};
//
//void main(void) {
//	Command* portfolio[] = {  // old C cast, or new RTTI is required
//		&Command(&IOU(100),   (int(Instrument::*)())&IOU::payUp),
//		&Command(&Check(200), static_cast<int(Instrument::*)()>(&Check::cash)),
//		&Command(&Stock(300), static_cast<int(Instrument::*)()>(&Stock::redeem)) };
//	for (int netWorth = 0, i = 0; i < 3; i++)
//		netWorth += portfolio[i]->execute();
//	cout << "net worth is now " << netWorth << '\n';
//}
//
//// net worth is now 600
//
//
//
//
//// Purpose.  Command design pattern and class template
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//class A {
//	int divisor;
//public:
//	A(int div) { divisor = div; }
//	int divide(int in) { return in / divisor; }
//	int modulus(int in) { return in % divisor; }
//};
//
//class B {
//	string str;
//public:
//	B(string s) { str = s; }
//	string prepend(string in) { return in + str; }
//	string postpend(string in) { return str + in; }
//};
//
//template <typename CLS, typename ARG>
//class Command {
//public:
//	typedef ARG(CLS::*Action)(ARG);
//	Command(CLS* o, Action m, ARG a) {
//		object = o;
//		method = m;
//		argument = a;
//	}
//	ARG execute() { return (object->*method)(argument); }
//private:
//	CLS * object;
//	Action method;
//	ARG    argument;
//};
//
//void main(void) {
//	Command<A, int>* list1[4] = {
//		&Command<A,int>(&A(3), &A::divide,  16),
//		&Command<A,int>(&A(3), &A::modulus, 16),
//		&Command<A,int>(&A(4), &A::divide,  16),
//		&Command<A,int>(&A(4), &A::modulus, 16) };
//	for (int i = 0; i < 4; i++)
//		cout << "numbers are " << list1[i]->execute() << '\n';
//
//	B obj("abc");
//	Command<B, string>* list2[4] = {
//		new Command<B,string>(&obj, &B::prepend,  "123"),
//		new Command<B,string>(&obj, &B::prepend,  "xyz"),
//		new Command<B,string>(&obj, &B::postpend, "123"),
//		new Command<B,string>(&obj, &B::postpend, "xyz") };
//	for (i = 0; i < 4; i++)
//		cout << "strings are " << list2[i]->execute() << '\n';
//}
//
//// numbers are 5
//// numbers are 1
//// numbers are 4
//// numbers are 0
//// strings are 123abc
//// strings are xyzabc
//// strings are abc123
//// strings are abcxyz
//
//
//
//
//// Purpose.  Command/Adapter design pattern (External Polymorphism demo)
//
//// 1. Specify the new desired interface
//// 2. Design a "wrapper" class that can "impedance match" the old to the new
//// 3. The client uses (is coupled to) the new interface
//// 4. The wrapper/adapter "maps" to the legacy implementation
//
//#include <iostream.h>
//
//class ExecuteInterface {
//public:                  // 1. Specify the new i/f
//	virtual ~ExecuteInterface() { }
//	virtual void execute() = 0;
//};
//
//template <class TYPE>                             // 2. Design a "wrapper" or
//class ExecuteAdapter : public ExecuteInterface {  //    "adapter" class
//public:
//	ExecuteAdapter(TYPE* o, void (TYPE::*m)()) { object = o;  method = m; }
//	~ExecuteAdapter() { delete object; }
//	// 4. The adapter/wrapper "maps" the new to the legacy implementation
//	void execute()             /* the new */ { (object->*method)(); }
//private:
//	TYPE * object;                                  // ptr-to-object attribute
//	void (TYPE::*method)();    /* the old */       // ptr-to-member-function
//};                                                //   attribute
//
//												  // The old: three totally incompatible classes    // no common base class,
//class Fea {
//public:                               // no hope of polymorphism
//	~Fea() { cout << "Fea::dtor" << endl; }
//	void doThis() { cout << "Fea::doThis()" << endl; }
//};
//
//class Feye {
//public:
//	~Feye() { cout << "Feye::dtor" << endl; }
//	void doThat() { cout << "Feye::doThat()" << endl; }
//};
//
//class Pheau {
//public:
//	~Pheau() { cout << "Pheau::dtor" << endl; }
//	void doTheOther() { cout << "Pheau::doTheOther()" << endl; }
//};
//
///* the new is returned */ ExecuteInterface** initialize() {
//	ExecuteInterface** array = new ExecuteInterface*[3]; /* the old is below */
//	array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doThis);
//	array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doThat);
//	array[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::doTheOther);
//	return array;
//}
//
//void main(void) {
//	ExecuteInterface** objects = initialize();
//
//	for (int i = 0; i < 3; i++) objects[i]->execute();  // 3. Client uses the new
//														//    (polymporphism)
//	for (i = 0; i < 3; i++) delete objects[i];
//	delete objects;
//}
//
//// Fea::doThis()
//// Feye::doThat()
//// Pheau::doTheOther()
//// Fea::dtor
//// Feye::dtor
//// Pheau::dtor
//
//
//
//
//// Purpose.  Command design pattern demo
//// 
//// Discussion.  Encapsulate a request as an object.  SimpleCommand
//// maintains a binding between a receiver object and an action stored as a
//// pointer to a member function.  MacroCommand maintains a sequence of
//// Commands.  No explicit receiver is required because the subcommands
//// already define their receiver.  MacroCommand may contain MacroCommands.
//
//#include <iostream.h>
//
//class Number {
//public:
//	Number(int value) { _value = _copy = value; }
//	int  getValue() { return _value; }
//	void increment() { _copy = _value++; }
//	void decrement() { _copy = _value--; }
//	void restore() { _value = _copy; }
//	void dubble() { _copy = _value;  _value = 2 * _value; }
//	void half() { _copy = _value;  _value = _value / 2; }
//	void square() { _copy = _value;  _value = _value * _value; }
//private:
//	int _value;
//	int _copy;
//};
//
//
//class Command {
//public:
//	virtual void execute() = 0;
//	virtual void add(Command*) { }
//protected:
//	Command() { }
//};
//
//class SimpleCommand : public Command {
//public:
//	typedef void (Number::* Action)();
//	SimpleCommand(Number* receiver, Action action) {
//		_receiver = receiver;
//		_action = action;
//	}
//	virtual void execute() { (_receiver->*_action)(); }
//protected:
//	Number * _receiver;
//	Action  _action;
//};
//
//class MacroCommand : public Command {
//public:
//	MacroCommand() { _numCommands = 0; }
//	void add(Command* cmd) { _list[_numCommands++] = cmd; }
//	virtual void execute();
//private:
//	Command * _list[10];
//	int      _numCommands;
//};
//
//void MacroCommand::execute() {
//	for (int i = 0; i < _numCommands; i++)
//		_list[i]->execute();
//}
//
//void main() {
//	int i;
//	cout << "Integer: ";
//	cin >> i;
//	Number*   object = new Number(i);
//
//	Command*  commands[9];
//	commands[1] = new SimpleCommand(object, &Number::increment);
//	commands[2] = new SimpleCommand(object, &Number::decrement);
//	commands[3] = new SimpleCommand(object, &Number::dubble);
//	commands[4] = new SimpleCommand(object, &Number::half);
//	commands[5] = new SimpleCommand(object, &Number::square);
//	commands[6] = new SimpleCommand(object, &Number::restore);
//	commands[7] = new MacroCommand;
//	commands[7]->add(commands[1]);
//	commands[7]->add(commands[3]);
//	commands[7]->add(commands[5]);
//	commands[8] = new MacroCommand;
//	commands[8]->add(commands[7]);
//	commands[8]->add(commands[7]);
//
//	cout << "Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], "
//		<< "Undo[6], do3[7] do6[8]: ";
//	cin >> i;
//
//	while (i)
//	{
//		commands[i]->execute();
//		cout << "   " << object->getValue() << endl;
//		cout << "Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], "
//			<< "Undo[6], do3[7] do6[8]: ";
//		cin >> i;
//	}
//}
//
//// Integer: 4
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 1
////    5
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 3
////    10
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 2
////    9
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 4
////    4
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 5
////    16
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 6
////    4
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 6
////    4
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 7
////    100
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 6
////    10
//// Exit[0], ++[1], --[2], x2[3], Half[4], Square[5], Undo[6], do3[7] do6[8]: 8
////    940900