#pragma once
#include <string>
/*

意图：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。
主要解决：所谓备忘录模式就是在不破坏封装的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态，这样可以在以后将对象恢复到原先保存的状态。
何时使用：很多时候我们总是需要记录一个对象的内部状态，这样做的目的就是为了允许用户取消不确定或者错误的操作，能够恢复到他原先的状态，使得他有"后悔药"可吃。
如何解决：通过一个备忘录类专门存储对象状态。
关键代码：客户不与备忘录类耦合，与备忘录管理类耦合。
应用实例： 1、后悔药。 2、打游戏时的存档。 3、Windows 里的 ctri + z。 4、IE 中的后退。 4、数据库的事务管理。
优点： 1、给用户提供了一种可以恢复状态的机制，可以使用户能够比较方便地回到某个历史的状态。 2、实现了信息的封装，使得用户不需要关心状态的保存细节。
缺点：消耗资源。如果类的成员变量过多，势必会占用比较大的资源，而且每一次保存都会消耗一定的内存。
使用场景： 1、需要保存/恢复数据的相关状态场景。 2、提供一个可回滚的操作。
注意事项： 1、为了符合迪米特原则，还要增加一个管理备忘录的类。 2、为了节约内存，可使用原型模式+备忘录模式。

*/


//// Purpose.  Memento design pattern
//
//// 1. Assign the roles of "caretaker" and "originator"
//// 2. Create a "memento" class and declare the originator a friend
//// 3. Caretaker knows when to "check point" the originator
//// 4. Originator creates a memento and copies its state to the memento
//// 5. Caretaker holds on to (but cannot peek in to) the memento
//// 6. Caretaker knows when to "roll back" the originator
//// 7. Originator reinstates itself using the saved state in the memento


class Memento {                   // 2. Create a "memento" class and
	friend class Stack;            //    declare the originator a friend
	int *items, num;
	Memento(int* arr, int n) {
		items = new int[num = n];
		for (int i = 0; i < num; i++) items[i] = arr[i];
	}
public:
	~Memento() { delete items; }
};

class Stack {                     // 1. Stack is the "originator"
	int  items[10], sp;
public:
	Stack() { sp = -1; }
	void     push(int in) { items[++sp] = in; }
	int      pop() { return items[sp--]; }
	bool     isEmpty() { return sp == -1; }
	// 4. Originator creates a memento and copies its state to the memento
	Memento* checkPoint() {
		return new Memento(items, sp + 1);
	}
	// 7. Originator reinstates itself using the saved state in the memento
	void rollBack(Memento* m) {
		sp = m->num - 1;
		for (int i = 0; i < m->num; i++) items[i] = m->items[i];
	}
	friend ostream& operator<< (ostream& os, const Stack& s) {
		string buf("[ ");
		for (int i = 0; i < s.sp + 1; i++) { buf += s.items[i] + 48;  buf += ' '; }
		buf += ']';
		return os << buf;                   // stack is [ 0 1 2 3 4 ]
	}
};                                     // stack is [ 0 1 2 3 4 5 6 7 8 9 ]
//									   // popping stack: 9 8 7 6 5 4 3 2 1 0
//									   // 1. main() is the "caretaker"           // stack is [ ]
//void main(void) {                       // second is [ 0 1 2 3 4 5 6 7 8 9 ]    
//	Stack s;                               // first is [ 0 1 2 3 4 ]
//	for (int i = 0; i < 5; i++) s.push(i); // popping stack: 4 3 2 1 0
//	cout << "stack is " << s << endl;
//	Memento* first = s.checkPoint();       // 3. Caretaker knows when to save
//	for (i = 5; i < 10; i++) s.push(i);    // 5. Caretaker holds on to memento
//	cout << "stack is " << s << endl;
//	Memento* second = s.checkPoint();      // 3. Caretaker knows when to save
//	cout << "popping stack: ";             // 5. Caretaker holds on to memento
//	while (!s.isEmpty()) cout << s.pop() << ' ';  cout << endl;
//	cout << "stack is " << s << endl;
//	s.rollBack(second);                  // 6. Caretaker knows when to undo
//	cout << "second is " << s << endl;
//	s.rollBack(first);                   // 6. Caretaker knows when to undo
//	cout << "first is " << s << endl;
//	cout << "popping stack: ";
//	while (!s.isEmpty()) cout << s.pop() << ' ';  cout << endl;
//	delete first;  delete second;
//}
//
//
//
//// Purpose.  Memento design pattern
//// 
//// Discussion.  A memento is an object that stores a snapshot of the
//// internal state of another object.  It can be leveraged to support
//// multi-level undo of the Command pattern.  In this example, before a
//// command is run against the Number object, Number's current state is
//// saved in Command's static memento history list, and the command itself
//// is saved in the static command history list.  Undo() simply "pops" the
//// memento history list and reinstates Number's state from the memento.
//// Redo() "pops" the command history list.  Note that Number's encapsula-
//// tion is preserved, and Memento is wide open to Number.
//
//#include <iostream.h>
//class Number;
//
//class Memento {
//public:
//	Memento(int val) { _state = val; }
//private:
//	friend class Number;  // not essential, but p287 suggests this
//	int  _state;
//};
//
//class Number {
//public:
//	Number(int value) { _value = value; }
//	void dubble() { _value = 2 * _value; }
//	void half() { _value = _value / 2; }
//	int getValue() { return _value; }
//	Memento* createMemento() { return new Memento(_value); }
//	void  reinstateMemento(Memento* mem) { _value = mem->_state; }
//private:
//	int _value;
//};
//
//class Command {
//public:
//	typedef void (Number::* Action)();
//	Command(Number* receiver, Action action) {
//		_receiver = receiver;
//		_action = action;
//	}
//	virtual void execute() {
//		_mementoList[_numCommands] = _receiver->createMemento();
//		_commandList[_numCommands] = this;
//		if (_numCommands > _highWater) _highWater = _numCommands;
//		_numCommands++;
//		(_receiver->*_action)();
//	}
//	static void undo() {
//		if (_numCommands == 0) {
//			cout << "*** Attempt to run off the end!! ***" << endl;
//			return;
//		}
//		_commandList[_numCommands - 1]->_receiver->
//			reinstateMemento(_mementoList[_numCommands - 1]);
//		_numCommands--;
//	}
//	void static redo() {
//		if (_numCommands > _highWater) {
//			cout << "*** Attempt to run off the end!! ***" << endl;
//			return;
//		}
//		(_commandList[_numCommands]->_receiver->
//			*(_commandList[_numCommands]->_action))();
//		_numCommands++;
//	}
//protected:
//	Number * _receiver;
//	Action          _action;
//	static Command* _commandList[20];
//	static Memento* _mementoList[20];
//	static int      _numCommands;
//	static int      _highWater;
//};
//
//Command* Command::_commandList[];
//Memento* Command::_mementoList[];
//int      Command::_numCommands = 0;
//int      Command::_highWater = 0;
//
//void main() {
//	int i;
//	cout << "Integer: ";
//	cin >> i;
//	Number*   object = new Number(i);
//
//	Command*  commands[3];
//	commands[1] = new Command(object, &Number::dubble);
//	commands[2] = new Command(object, &Number::half);
//
//	cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
//	cin >> i;
//
//	while (i)
//	{
//		if (i == 3)
//			Command::undo();
//		else if (i == 4)
//			Command::redo();
//		else
//			commands[i]->execute();
//		cout << "   " << object->getValue() << endl;
//		cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
//		cin >> i;
//	}
//}
//
//// Integer: 11
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 2
////    5
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 1
////    10
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 2
////    5
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
////    10
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
////    5
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
////    11
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 3
//// *** Attempt to run off the end!! ***
////    11
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
////    5
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
////    10
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
////    5
//// Exit[0], Double[1], Half[2], Undo[3], Redo[4]: 4
//// *** Attempt to run off the end!! ***
////    5