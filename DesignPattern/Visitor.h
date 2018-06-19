#pragma once
/*

意图：主要将数据结构与数据操作分离。
主要解决：稳定的数据结构和易变的操作耦合问题。
何时使用：需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，使用访问者模式将这些封装到类中。
如何解决：在被访问的类里面加一个对外提供接待访问者的接口。
关键代码：在数据基础类里面有一个方法接受访问者，将自身引用传入访问者。
应用实例：您在朋友家做客，您是访问者，朋友接受您的访问，您通过朋友的描述，然后对朋友的描述做出一个判断，这就是访问者模式。
优点： 1、符合单一职责原则。 2、优秀的扩展性。 3、灵活性。
缺点： 1、具体元素对访问者公布细节，违反了迪米特原则。 2、具体元素变更比较困难。 3、违反了依赖倒置原则，依赖了具体类，没有依赖抽象。
使用场景： 1、对象结构中对象对应的类很少改变，但经常需要在此对象结构上定义新的操作。 2、需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，也不希望在增加新操作时修改这些类。
注意事项：访问者可以对功能进行统一，可以做报表、UI、拦截器与过滤器。

*/

// 1. Add an accept(Visitor) method to the "element" hierarchy
class Element {
public:
	virtual void accept(class Visitor& v) = 0;
};

class This : public Element {
public:
	/*virtual*/ void accept(Visitor& v);
	string thiss() { return "This"; }
};

class That : public Element {
public:
	/*virtual*/ void accept(Visitor& v);
	string that() { return "That"; }
};

class TheOther : public Element {
public:
	/*virtual*/ void accept(Visitor& v);
	string theOther() { return "TheOther"; }
};

// 2. Create a "visitor" base class w/ a visit() method for every "element" type
class Visitor {
public:
	virtual void visit(This* e) = 0;
	virtual void visit(That* e) = 0;
	virtual void visit(TheOther* e) = 0;
};

/*virtual*/ void This::accept(Visitor& v) { v.visit(this); }
/*virtual*/ void That::accept(Visitor& v) { v.visit(this); }
/*virtual*/ void TheOther::accept(Visitor& v) { v.visit(this); }

// 3. Create a "visitor" derived class for each "operation" to do on "elements"
class UpVisitor : public Visitor {
	/*virtual*/ void visit(This* e) {
		cout << "do Up on " + e->thiss() << '\n';
	}
	/*virtual*/ void visit(That* e) {
		cout << "do Up on " + e->that() << '\n';
	}
	/*virtual*/ void visit(TheOther* e) {
		cout << "do Up on " + e->theOther() << '\n';
	}
};

class DownVisitor : public Visitor {
	/*virtual*/ void visit(This* e) {
		cout << "do Down on " + e->thiss() << '\n';
	}
	/*virtual*/ void visit(That* e) {
		cout << "do Down on " + e->that() << '\n';
	}
	/*virtual*/ void visit(TheOther* e) {
		cout << "do Down on " + e->theOther() << '\n';
	}
};

//void main(void) {
//	Element* list[] = { new This(), new That(), new TheOther() };
//	UpVisitor    up;             // 4. Client creates
//	DownVisitor  down;           //    "visitor" objects
//	for (int i = 0; i < 3; i++)    //    and passes each
//		list[i]->accept(up);    //    to accept() calls
//	for (i = 0; i < 3; i++)
//		list[i]->accept(down);
//}
//
//// do Up on This                // do Down on This
//// do Up on That                // do Down on That
//// do Up on TheOther            // do Down on TheOther
//
//
//
//
//// Purpose.  Visitor - recovering lost type information
//// 
//// Motivation.  "My Component classes do not know that Composites exist.
//// They provide no help for navigating Composites, nor any help for
//// altering the contents of a Composite.  This is because I would like the
//// base class (and all its derivatives) to be reusable in contexts that do
//// not require Composites.  When given a base class pointer, if I
//// absolutely need to know whether or not it is a Composite, I will use
//// dynamic_cast() to figure this out.  In those cases where dynamic_cast()
//// is too expensive, I will use a Visitor." [Robert Martin]
//
//#include <iostream>
//#include <vector>
//using namespace std;
//
//class Visitor {
//public:
//	virtual void visit(class Primitive*, class Component*) = 0;
//	virtual void visit(class Composite*, Component*) = 0;
//};
//
//class Component {
//	int value;
//public:
//	Component(int val) { value = val; }
//	virtual void traverse() { cout << value << " "; }
//	// Having add() here sacrifices safety, but it supports transparency
//	// virtual void add( Component* ) { }
//	virtual void accept(Visitor&, Component*) = 0;
//};
//
//class Primitive : public Component {
//public:
//	Primitive(int val) : Component(val) { }
//	/*virtual*/ void accept(Visitor& v, Component* c) { v.visit(this, c); }
//};
//
//class Composite : public Component {
//	vector<Component*> children;
//public:
//	Composite(int val) : Component(val) { }
//	void add(Component* ele) { children.push_back(ele); }
//	/*virtual*/ void accept(Visitor& v, Component* c) { v.visit(this, c); }
//	/*virtual*/ void traverse() {
//		Component::traverse();
//		for (int i = 0; i < children.size(); i++)
//			children[i]->traverse();
//	}
//};
//
//class AddVisitor : public Visitor {
//public:
//	/*virtual*/ void visit(Primitive*, Component*) {/* does not make sense */ }
//	/*virtual*/ void visit(Composite* node, Component* c) { node->add(c); }
//};
//
//void main(void) {
//	Component*  nodes[3];
//	// The type of Composite* is "lost" when the object is assigned to a
//	// Component*
//	nodes[0] = new Composite(1);
//	nodes[1] = new Composite(2);
//	nodes[2] = new Composite(3);
//
//	// If add() were in class Component, this would work
//	//    nodes[0]->add( nodes[1] );
//	// If it is NOT in Component, and only in Composite,  you get the error -
//	//    no member function `Component::add(Component *)' defined
//
//	// Instead of sacrificing safety, we use a Visitor to support add()
//	AddVisitor  addVisitor;
//	nodes[0]->accept(addVisitor, nodes[1]);
//	nodes[0]->accept(addVisitor, nodes[2]);
//	nodes[0]->accept(addVisitor, new Primitive(4));
//	nodes[1]->accept(addVisitor, new Primitive(5));
//	nodes[1]->accept(addVisitor, new Primitive(6));
//	nodes[2]->accept(addVisitor, new Primitive(7));
//
//	for (int i = 0; i < 3; i++) {
//		nodes[i]->traverse();
//		cout << endl;
//	}
//}
//
//// 1 2 5 6 3 7 4 
//// 2 5 6 
//// 3 7 
//
//
//
//
//// Purpose.  Combining Visitor with Composite's recursive traversal
//
//#include <iostream>
//#include <vector>
//using namespace std;
//
//class Visitor {
//public:
//	virtual void visit(class Leaf* e) = 0;
//	virtual void visit(class Composite* e) = 0;
//};
//
//class Component {
//public:
//	virtual void traverse() = 0;
//	virtual void accept(class Visitor& v) = 0;
//};
//
//class Leaf : public Component {
//	int value;
//public:
//	Leaf(int val) { value = val; }
//	/*virtual*/ void traverse() { cout << value << ' '; }
//	/*virtual*/ void accept(class Visitor& v) { v.visit(this); }
//	int getValue() { return value; }
//};
//
//class Composite : public Component {
//	char value;
//	vector<Component*> children;
//	static char next;
//public:
//	Composite() { value = next++; }
//	void add(Component* ele) { children.push_back(ele); }
//	/*virtual*/ void traverse() {
//		cout << value << ' ';
//		for (int i = 0; i < children.size(); i++)
//			children[i]->traverse();
//	}
//	/*virtual*/ void accept(class Visitor& v) {
//		v.visit(this);
//		// accept() has been embellished to include the logic in traverse()
//		for (int i = 0; i < children.size(); i++)
//			children[i]->accept(v);
//	}
//	char getValue() { return value; }
//};
//char Composite::next = 'a';
//
//class TransformVisitor : public Visitor {
//public:
//	/*virtual*/ void visit(Leaf* e) { cout << e->getValue() + 100 << ' '; }
//	/*virtual*/ void visit(Composite* e) { cout << (char)(e->getValue() - 32) << ' '; }
//};
//
//void main(void) {
//	Composite containers[4];
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 3; j++)
//			containers[i].add(new Leaf(i * 3 + j));
//	for (i = 1; i < 4; i++) containers[0].add(&(containers[i]));
//
//	containers[0].traverse();   cout << endl;
//
//	TransformVisitor tv;
//	// don't need an "iteration" capability with this design
//	containers[0].accept(tv);   cout << endl;
//}
//
//// a 0 1 2 b 3 4 5 c 6 7 8 d 9 10 11
//// A 100 101 102 B 103 104 105 C 106 107 108 D 109 110 111
//
//
//
//
//// Purpose.  Undesireable design - double dispatch - doing the right thing based
//// on the type of two objects
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//class Request { public: virtual string getType() = 0; };
//
//class R1 : public Request {
//public:
//	/*virtual*/ string getType() { return "One"; }
//	void reqOneMethod(class P1*);
//	void reqOneMethod(class P2*);
//};
//class R2 : public Request {
//public:
//	/*virtual*/ string getType() { return "Two"; }
//	void reqTwoMethod(P1*);
//	void reqTwoMethod(P2*);
//};
//
//class Processor { public: virtual void handle(class Request*) = 0; };
//
//class P1 : public Processor {
//public:
//	/*virtual*/ void handle(class Request* req) {
//		if (req->getType() == string("One"))      ((R1*)req)->reqOneMethod(this);
//		else if (req->getType() == string("Two")) ((R2*)req)->reqTwoMethod(this);
//	}
//	void procOneMethod() { cout << "processor one handling "; }
//};
//class P2 : public Processor {
//public:
//	/*virtual*/ void handle(class Request* req) {
//		if (req->getType() == string("One"))      ((R1*)req)->reqOneMethod(this);
//		else if (req->getType() == string("Two")) ((R2*)req)->reqTwoMethod(this);
//	}
//	void procTwoMethod() { cout << "processor two handling "; }
//};
//
//void R1::reqOneMethod(P1* p) { p->procOneMethod(); cout << "request one\n"; }
//void R1::reqOneMethod(P2* p) { p->procTwoMethod(); cout << "request one\n"; }
//void R2::reqTwoMethod(P1* p) { p->procOneMethod(); cout << "request two\n"; }
//void R2::reqTwoMethod(P2* p) { p->procTwoMethod(); cout << "request two\n"; }
//
//void main(void) {
//	Processor* handlers[] = { new P1(), new P2() };
//	Request*   commands[] = { new R1(), new R2() };
//	for (int i = 0; i < 2; i++)
//		for (int j = 0; j < 2; j++)
//			handlers[i]->handle(commands[j]);
//}
//
//// processor one handling request one
//// processor one handling request two
//// processor two handling request one
//// processor two handling request two
//
//
//
//
//// Purpose.  Visitor - double dispatch - doing the right thing based on the
//// type of two objects
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//class Request {
//public:
//	// second dispatch - the "visit()" method
//	virtual void execute(class P1*) = 0;
//	virtual void execute(class P2*) = 0;
//};
//class R1 : public Request {
//public:
//	/*virtual*/ void execute(P1*);
//	/*virtual*/ void execute(P2*);
//};
//class R2 : public Request {
//public:
//	/*virtual*/ void execute(P1*);
//	/*virtual*/ void execute(P2*);
//};
//
//class Processor {
//public:
//	// first dispatch - the "accept()" method
//	virtual void handle(class Request*) = 0;
//};
//class P1 : public Processor {
//public:
//	/*virtual*/ void handle(Request* req) { req->execute(this); }
//	void procOneMethod() { cout << "processor one handling "; }
//};
//class P2 : public Processor {
//public:
//	/*virtual*/ void handle(Request* req) { req->execute(this); }
//	void procTwoMethod() { cout << "processor two handling "; }
//};
//
///*virtual*/ void R1::execute(P1* p) { p->procOneMethod(); cout << "request one\n"; }
///*virtual*/ void R1::execute(P2* p) { p->procTwoMethod(); cout << "request one\n"; }
///*virtual*/ void R2::execute(P1* p) { p->procOneMethod(); cout << "request two\n"; }
///*virtual*/ void R2::execute(P2* p) { p->procTwoMethod(); cout << "request two\n"; }
//
//void main(void) {
//	Processor* handlers[] = { new P1(), new P2() };
//	Request*   commands[] = { new R1(), new R2() };
//	for (int i = 0; i < 2; i++)
//		for (int j = 0; j < 2; j++)
//			handlers[i]->handle(commands[j]);
//}
//
//// processor one handling request one
//// processor one handling request two
//// processor two handling request one
//// processor two handling request two
//
//
//
//
//// Purpose.  Acyclic Visitor design pattern [PLOPD vol 3, p93]
////
//// Problem.  In GOF Visitor, Element depends on Visitor, Visitor depends on
//// all Element derivatives, and Element derivatives depend on Element; this is
//// cyclic dependency.  Additionally, adding an Element derivative requires the
//// entire Visitor hierarchy to change.  "These problems can be solved by using
//// multiple inheritance and dynamic_cast()."
////
//// Solution.  Element derived classes are only coupled to Visitor base class.
//// Visitor derived classes are only coupled to the Element derived classes that
//// they choose to be coupled to.  If a new Element derived class is added,
//// Visitor derived classes can update themselves if, and when, they choose.
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//class Element {
//public:
//	virtual void accept(class Visitor& v) = 0;
//};
//
//class This : public Element {
//public:
//	/*virtual*/ void accept(Visitor& v);
//	string thiss() { return "This"; }
//};
//
//class That : public Element {
//public:
//	/*virtual*/ void accept(Visitor& v);
//	string that() { return "That"; }
//};
//
//class TheOther : public Element {
//public:
//	/*virtual*/ void accept(Visitor& v);
//	string theOther() { return "TheOther"; }
//};
//
//class Visitor {
//public:
//	virtual ~Visitor() { };
//};
//class ThisVisitor {
//public:
//	virtual void visit(This* e) = 0;
//};
//class ThatVisitor {
//public:
//	virtual void visit(That* e) = 0;
//};
//class TheOtherVisitor {
//public:
//	virtual void visit(TheOther* e) = 0;
//};
//
///*virtual*/ void This::accept(Visitor& v) {
//	ThisVisitor* tv = dynamic_cast<ThisVisitor*>(&v);
//	if (tv) tv->visit(this);
//	else cout << "the visitor was not accepted\n";
//}
///*virtual*/ void That::accept(Visitor& v) {
//	ThatVisitor* tv = dynamic_cast<ThatVisitor*>(&v);
//	if (tv) tv->visit(this);
//	else cout << "the visitor was not accepted\n";
//}
///*virtual*/ void TheOther::accept(Visitor& v) {
//	TheOtherVisitor* tv = dynamic_cast<TheOtherVisitor*>(&v);
//	if (tv) tv->visit(this);
//	else cout << "the visitor was not accepted\n";
//}
//
//class UpVisitor : public Visitor, public ThisVisitor, public ThatVisitor,
//	public TheOtherVisitor {
//	/*virtual*/ void visit(This* e) {
//		cout << "do Up on " + e->thiss() << '\n';
//	}
//	/*virtual*/ void visit(That* e) {
//		cout << "do Up on " + e->that() << '\n';
//	}
//	/*virtual*/ void visit(TheOther* e) {
//		cout << "do Up on " + e->theOther() << '\n';
//	}
//};
//
//class DownVisitor : public Visitor, public ThisVisitor, public ThatVisitor,
//	public TheOtherVisitor {
//	/*virtual*/ void visit(This* e) {
//		cout << "do Down on " + e->thiss() << '\n';
//	}
//	/*virtual*/ void visit(That* e) {
//		cout << "do Down on " + e->that() << '\n';
//	}
//	/*virtual*/ void visit(TheOther* e) {
//		cout << "do Down on " + e->theOther() << '\n';
//	}
//};
//
//void main(void) {
//	Element* list[] = { new This(), new That(), new TheOther() };
//	UpVisitor    up;             // 4. Client creates
//	DownVisitor  down;           //    "visitor" objects
//	for (int i = 0; i < 3; i++)    //    and passes each
//		list[i]->accept(up);    //    to accept() calls
//	for (i = 0; i < 3; i++)
//		list[i]->accept(down);
//}
//
//// do Up on This                // do Down on This
//// do Up on That                // do Down on That
//// do Up on TheOther            // do Down on TheOther
//
//
//
//
//// Purpose.  Double dispatch (within a single hierarchy)
////
//// Discussion.  We would like to declare a function like:
////    void process( virtual Base* object1, virtual Base* object2 )
//// that does the right thing based on the type of 2 objects that come from
//// a single inheritance hierarchy.  The only problem is that the keyword
//// "virtual" may not be used to request dynamic binding for an object being
//// passed as an argument.  C++ will only "discriminate" the type of an object
//// being messaged, not the type of an object being passed.  So in order for
//// the type of 2 objects to be discriminated, each object must be the
//// receiver of a virtual function call.  Here, when process1() is called on
//// the first object, its type becomes "known" at runtime, but the type of
//// the second is still UNknown.  process2() is then called on the second
//// object, and the identity (and type) of the first object is passed as an
//// argument.  Flow of control has now been vectored to the spot where the
//// type (and identity) of both objects are known.
//
//#include <iostream>
//using namespace std;
//
//class Base {
//public:
//	virtual void process1(Base&) = 0;
//	virtual void process2(class A&) = 0;
//	virtual void process2(class B&) = 0;
//	virtual void process2(class C&) = 0;
//};
//
//class A : public Base {
//public:
//	/*virtual*/ void process1(Base& second) { second.process2(*this); }
//	/*virtual*/ void process2(class A& first) {
//		cout << "first is A, second is A\n";
//	}
//	/*virtual*/ void process2(class B& first) {
//		cout << "first is B, second is A\n";
//	}
//	/*virtual*/ void process2(class C& first) {
//		cout << "first is C, second is A\n";
//	}
//};
//
//class B : public Base {
//public:
//	/*virtual*/ void process1(Base& second) { second.process2(*this); }
//	/*virtual*/ void process2(class A& first) {
//		cout << "first is A, second is B\n";
//	}
//	/*virtual*/ void process2(class B& first) {
//		cout << "first is B, second is B\n";
//	}
//	/*virtual*/ void process2(class C& first) {
//		cout << "first is C, second is B\n";
//	}
//};
//
//class C : public Base {
//public:
//	/*virtual*/ void process1(Base& second) { second.process2(*this); }
//	/*virtual*/ void process2(class A& first) {
//		cout << "first is A, second is C\n";
//	}
//	/*virtual*/ void process2(class B& first) {
//		cout << "first is B, second is C\n";
//	}
//	/*virtual*/ void process2(class C& first) {
//		cout << "first is C, second is C\n";
//	}
//};
//
//void main(void) {
//	Base* array[] = { &A(), &B(), &C() };
//	for (int i = 0; i < 3; i++)
//		for (int j = 0; j < 3; j++)
//			array[i]->process1(*array[j]);
//}
//
//// first is A, second is A
//// first is A, second is B
//// first is A, second is C
//// first is B, second is A
//// first is B, second is B
//// first is B, second is C
//// first is C, second is A
//// first is C, second is B
//// first is C, second is C
//
//
//
//
//// Purpose.  Triple dispatch (within a single hierarchy)
//// 
//// Discussion.  It would be nice if C++ supported creating a function like:
//// "processCombine( virtual Binary& first, virtual Binary& second, virtual
//// Binary& third )".  While not directly supported, we can simulate this kind
//// of capability by: calling combine() on the first object to resolve its
//// type, then calling combine() on the second object to resolve its type,
//// then calling combine() on the third object to resolve its type.  We
//// "remember" the type information we have "discriminated" at each stage by
//// juggling the three objects through 2 increasingly type-specific parameter
//// slots.
//
//#include <iostream>
//using namespace std;
//
//class Zero;
//class One;
//
//class Binary {
//public:
//	// First dispatch
//	virtual void combine(Binary& second, Binary& third) = 0;
//
//	// Second dispatch
//	virtual void combine(Binary& third, Zero& first) = 0;
//	virtual void combine(Binary& third, One&  first) = 0;
//
//	// Third dispatch
//	virtual void combine(Zero& first, Zero& second) = 0;
//	virtual void combine(Zero& first, One&  second) = 0;
//	virtual void combine(One& first, Zero& second) = 0;
//	virtual void combine(One& first, One&  second) = 0;
//};
//
//class Zero : public Binary {
//public:
//	void combine(Binary& second, Binary& third) {
//		second.combine(third, *this);
//	}
//
//	void combine(Binary& third, Zero& first) {
//		third.combine(first, *this);
//	}
//	void combine(Binary& third, One& first) {
//		third.combine(first, *this);
//	}
//
//	void combine(Zero& first, Zero& second);
//	void combine(Zero& first, One&  second);
//	void combine(One&  first, Zero& second);
//	void combine(One&  first, One&  second);
//
//	void doZero() { cout << "0  "; }
//};
//
//class One : public Binary {
//public:
//	void combine(Binary& second, Binary& third) {
//		second.combine(third, *this);
//	}
//
//	void combine(Binary& third, Zero& first) {
//		third.combine(first, *this);
//	}
//	void combine(Binary& third, One& first) {
//		third.combine(first, *this);
//	}
//
//	void combine(Zero& first, Zero& second);
//	void combine(Zero& first, One&  second);
//	void combine(One&  first, Zero& second);
//	void combine(One&  first, One&  second);
//
//	void doOne() { cout << "1  "; }
//};
//
//void Zero::combine(Zero& first, Zero& second) {
//	first.doZero();  second.doZero();  doZero();  cout << endl;
//}
//void Zero::combine(Zero& first, One&  second) {
//	first.doZero();  second.doOne();   doZero();  cout << endl;
//}
//void Zero::combine(One&  first, Zero& second) {
//	first.doOne();   second.doZero();  doZero();  cout << endl;
//}
//void Zero::combine(One&  first, One&  second) {
//	first.doOne();   second.doOne();   doZero();  cout << endl;
//}
//
//void One::combine(Zero& first, Zero& second) {
//	first.doZero();  second.doZero();  doOne();  cout << endl;
//}
//void One::combine(Zero& first, One&  second) {
//	first.doZero();  second.doOne();   doOne();  cout << endl;
//}
//void One::combine(One&  first, Zero& second) {
//	first.doOne();   second.doZero();  doOne();  cout << endl;
//}
//void One::combine(One&  first, One&  second) {
//	first.doOne();   second.doOne();   doOne();  cout << endl;
//}
//
//void processCombine(Binary& first, Binary& second, Binary& third) {
//	first.combine(second, third);
//}
//
//void main(void) {
//	Binary*  list[2] = { &Zero(), &One() };
//
//	// Run through permutations
//	for (int i = 0; i < 2; i++)
//		for (int j = 0; j < 2; j++)
//			for (int k = 0; k < 2; k++)
//				processCombine(*list[i], *list[j], *list[k]);
//}
//
//// 0  0  0  
//// 0  0  1  
//// 0  1  0  
//// 0  1  1  
//// 1  0  0  
//// 1  0  1  
//// 1  1  0  
//// 1  1  1  