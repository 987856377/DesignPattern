#pragma once
/*

意图：定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
主要解决：一些方法通用，却在每一个子类都重新写了这一方法。
何时使用：有一些通用的方法。
如何解决：将这些通用算法抽象出来。
关键代码：在抽象类实现，其他步骤在子类实现。
应用实例： 1、在造房子的时候，地基、走线、水管都一样，只有在建筑的后期才有加壁橱加栅栏等差异。 2、西游记里面菩萨定好的 81 难，这就是一个顶层的逻辑骨架。 3、spring 中对 Hibernate 的支持，将一些已经定好的方法封装起来，比如开启事务、获取 Session、关闭 Session 等，程序员不重复写那些已经规范好的代码，直接丢一个实体就可以保存。
优点： 1、封装不变部分，扩展可变部分。 2、提取公共代码，便于维护。 3、行为由父类控制，子类实现。
缺点：每一个不同的实现都需要一个子类来实现，导致类的个数增加，使得系统更加庞大。
使用场景： 1、有多个子类共有的方法，且逻辑相同。 2、重要的、复杂的方法，可以考虑作为模板方法。
注意事项：为防止恶意操作，一般模板方法都加上 final 关键词。

*/

// Purpose.  Template Method design pattern

// 1. Standardize the skeleton of an algorithm in a base class "template method"
// 2. Steps requiring peculiar implementations are "placeholders" in base class
// 3. Derived classes implement placeholder methods
class Base {
	void a() { cout << "a  "; }
	void c() { cout << "c  "; }
	void e() { cout << "e  "; }
	// 2. Steps requiring peculiar implementations are "placeholders" in base class
	virtual void ph1() = 0;
	virtual void ph2() = 0;
public:
	// 1. Standardize the skeleton of an algorithm in a base class "template method"
	void execute() { a();  ph1();  c();  ph2();  e(); }
};

class One : public Base {
	// 3. Derived classes implement placeholder methods
	/*virtual*/ void ph1() { cout << "b  "; }
	/*virtual*/ void ph2() { cout << "d  "; }
};

class Two : public Base {
	/*virtual*/ void ph1() { cout << "2  "; }
	/*virtual*/ void ph2() { cout << "4  "; }
};
//
//void main(void) {
//	Base* array[] = { &One(), &Two() };
//	for (int i = 0; i < 2; i++) {
//		array[i]->execute();
//		cout << '\n';
//	}
//}

// a  b  c  d  e
// a  2  c  4  e



//
//	// Purpose. Template Method design pattern
//
//	// 1. Standardize the skeleton of an algorithm in a base class "template method"
//	// 2. Steps requiring peculiar implementations are "placeholders" in base class
//	// 3. Derived classes implement placeholder methods
//
//#include <iostream>
//#include <string>
//	using namespace std;
//
//	class StandardAlgorithm {
//		// 3. Steps requiring peculiar implementations are "placeholders" in base class
//		virtual string preprocess(char*) = 0;
//		virtual bool   validate(char) = 0;
//	public:
//		// 1. Standardize the skeleton of algorithm in base class "template method"
//		string process(char* in) {
//			string str = preprocess(in);
//			for (int i = 0; i < str.size(); i++)
//				if (!validate(str[i])) return "not valid";
//			return str;
//		}
//	};
//
//	class Alphabetic : public StandardAlgorithm {
//		/*virtual*/ string preprocess(char* in) {
//			string s(in);
//			for (int i = 0; i < s.size(); i++)
//				if (s[i] >= 'A' && s[i] <= 'Z' || s[i] == ' ') /* empty */;
//				else if (s[i] >= 'a' && s[i] <= 'z')           s[i] = s[i] - 32;
//				else                                           s[i] = '_';
//				return s;
//		}
//		/*virtual*/ bool validate(char ch) {
//			if (ch >= 'A' && ch <= 'Z' || ch == ' ') return true;
//			else return false;
//		}
//	};
//
//	class Numeric : public StandardAlgorithm {
//		/*virtual*/ string preprocess(char* in) { return in; }
//		/*virtual*/ bool validate(char ch) {
//			if (ch >= '0' && ch <= '9') return true;
//			else return false;
//		}
//	};
//
//	void main(void) {
//		StandardAlgorithm* types[] = { &Alphabetic(), &Numeric() };
//		char buf[20];
//		while (true) {
//			cout << "Input: ";
//			cin.getline(buf, 20);
//			if (!strcmp(buf, "quit")) break;
//			for (int i = 0; i < 2; i++)
//				cout << "   " << types[i]->process(buf) << '\n';
//		}
//	}
//
//	// Input: Hello World
//	//    HELLO WORLD
//	//    not valid
//	// Input: 12345
//	//    not valid
//	//    12345
//	// Input: 4.2e3
//	//    not valid
//	//    not valid
//	// Input: quit
//
//
//
//
//	// Purpose. Template Method design pattern
//
//	// 1. Standardize the skeleton of an algorithm in a base class "template" method
//	// 2. Common implementations of individual steps are defined in the base class
//	// 3. Steps requiring peculiar implementations are "placeholders" in base class
//	// 4. Derived classes can override placeholder methods
//	// 5. Derived classes can override implemented methods
//	// 6. Derived classes can override and "call back to" base class methods
//
//#include <iostream>
//	using namespace std;
//
//	class A {
//	public:
//		// 1. Standardize the skeleton of an algorithm in a "template" method
//		void findSolution() {
//			stepOne();
//			stepTwo();
//			stepThr();
//			stepFor();
//		}
//	protected:
//		virtual void stepFor() { cout << "A.stepFor" << '\n'; }
//	private:
//		// 2. Common implementations of individual steps are defined in base class
//		void stepOne() { cout << "A.stepOne" << '\n'; }
//		// 3. Steps requiring peculiar impls are "placeholders" in the base class
//		virtual void stepTwo() = 0;
//		virtual void stepThr() = 0;
//	};
//
//	class B : public A {
//		// 4. Derived classes can override placeholder methods
//		// 1. Standardize the skeleton of an algorithm in a "template" method
//		/*virtual*/ void stepThr() {
//			step3_1();
//			step3_2();
//			step3_3();
//		}
//		// 2. Common implementations of individual steps are defined in base class
//		void step3_1() { cout << "B.step3_1" << '\n'; }
//		// 3. Steps requiring peculiar impls are "placeholders" in the base class
//		virtual void step3_2() = 0;
//		void step3_3() { cout << "B.step3_3" << '\n'; }
//	};
//
//	class C : public B {
//		// 4. Derived classes can override placeholder methods
//		/*virtual*/ void stepTwo() { cout << "C.stepTwo" << '\n'; }
//		void step3_2() { cout << "C.step3_2" << '\n'; }
//		// 5. Derived classes can override implemented methods
//		// 6. Derived classes can override and "call back to" base class methods
//		/*virtual*/ void stepFor() {
//			cout << "C.stepFor" << '\n';
//			A::stepFor();
//		}
//	};
//
//	void main(void) {
//		C algorithm;
//		algorithm.findSolution();
//	}
//
//	// A.stepOne
//	// C.stepTwo
//	// B.step3_1
//	// C.step3_2
//	// B.step3_3
//	// C.stepFor
//	// A.stepFor
//
//
//
//
//	// Purpose.  Template Method design pattern demo.
//	// 
//	// Discussion.  The "template method" establishes the steps to be
//	// performed.  All standard, or invariant, steps have their implementation
//	// provided by the abstract base class.  All variable steps are not
//	// defined in the base class, but must be defined by concrete derived
//	// classes.  "stepFour" below is an embellishment on the design pattern
//	// where the base class provides a default implementation, and then the
//	// derived class may extend that method by: overriding the method,
//	// "calling-back" to the base class to leverage its implementation, and
//	// then adding its own peculiar behavior.
//
//#include <iostream.h>
//
//	class IncompleteAlgorithm {
//	public:
//		void doIt() {       // this is the Template Method
//			stepOne();       // invariant, standard
//			stepTwo();       // invariant, standard
//			stepThree();     // variable,  supplied by subclass
//			stepFour();
//		}    // variable,  default provided
//	private:
//		void stepOne() {
//			cout << "IncompleteAlgorithm::stepOne" << endl;
//		}
//		void stepTwo() {
//			cout << "IncompleteAlgorithm::stepTwo" << endl;
//		}
//		virtual void stepThree() = 0;
//	protected:
//		virtual void stepFour() {
//			cout << "IncompleteAlgorithm::stepFour" << endl;
//		}
//	};
//
//	class FillInTheTemplate : public IncompleteAlgorithm {
//		/* virtual */ void stepThree() {
//			cout << "FillInTheTemplate::stepThree" << endl;
//		}
//		/* virtual */ void stepFour() {
//			IncompleteAlgorithm::stepFour();
//			cout << "FillInTheTemplate::stepFour" << endl;
//		}
//	};
//
//	void main() {
//		FillInTheTemplate  theThingToDo;
//		theThingToDo.doIt();
//	}
//
//	// IncompleteAlgorithm::stepOne
//	// IncompleteAlgorithm::stepTwo
//	// FillInTheTemplate::stepThree
//	// IncompleteAlgorithm::stepFour
//	// FillInTheTemplate::stepFour
//
//
//
//
//	// Purpose.  Template Method design pattern demo
//	//
//	// romanNumeral ::= {thousands} {hundreds} {tens} {ones}
//	// thousands, hundreds, tens, ones ::= nine | four | {five} {one} {one} {one}
//	// nine ::= "CM" | "XC" | "IX"
//	// four ::= "CD" | "XL" | "IV"
//	// five ::= 'D' | 'L' | 'V'
//	// one  ::= 'M' | 'C' | 'X' | 'I'
//
//#include <iostream>
//#include <string>
//	using namespace std;
//	class Thousand;  class Hundred;  class Ten;  class One;
//
//	class RNInterpreter {
//	public:
//		static int interpret(string input);
//		void interpret(string& input, int& total) {               // Template Method
//			int index = 0;
//			if (input.substr(0, 2) == nine()) {
//				total += 9 * multiplier();
//				index += 2;
//			}
//			else if (input.substr(0, 2) == four()) {
//				total += 4 * multiplier();
//				index += 2;
//			}
//			else {
//				if (input[0] == five()) {
//					total += 5 * multiplier();
//					index = 1;
//				}
//				for (int end = index + 3; index < end; index++)
//					if (input[index] == one())
//						total += 1 * multiplier();
//					else break;
//			}
//			// remove all leading chars processed
//			input.replace(0, index, "");
//		}
//	private:
//		virtual char one() = 0;   virtual string four() = 0;  // placeholders
//		virtual char five() = 0;   virtual string nine() = 0;  // placeholders
//		virtual int  multiplier() = 0;                               // placeholders
//		static Thousand thousands;       static Hundred hundreds;
//		static Ten      tens;            static One     ones;
//	};
//
//	class Thousand : public RNInterpreter {
//		char  one() { return 'M'; }    string four() { return ""; }
//		char  five() { return '\0'; }   string nine() { return ""; }
//		int   multiplier() { return 1000; }
//	};
//	class Hundred : public RNInterpreter {
//		char  one() { return 'C'; }   string four() { return "CD"; }
//		char  five() { return 'D'; }   string nine() { return "CM"; }
//		int   multiplier() { return 100; }
//	};
//	class Ten : public RNInterpreter {
//		char  one() { return 'X'; }   string four() { return "XL"; }
//		char  five() { return 'L'; }   string nine() { return "XC"; }
//		int   multiplier() { return 10; }
//	};
//	class One : public RNInterpreter {
//		char  one() { return 'I'; }   string four() { return "IV"; }
//		char  five() { return 'V'; }   string nine() { return "IX"; }
//		int   multiplier() { return 1; }
//	};
//
//	Thousand RNInterpreter::thousands;
//	Hundred  RNInterpreter::hundreds;
//	Ten      RNInterpreter::tens;
//	One      RNInterpreter::ones;
//
//	/*static*/ int RNInterpreter::interpret(string input) {
//		int total = 0;
//		thousands.interpret(input, total);
//		hundreds.interpret(input, total);
//		tens.interpret(input, total);
//		ones.interpret(input, total);
//		// if any input remains, the input was invalid, return 0
//		if (input != "") return 0;
//		return total;
//	}
//
//	void main(void) {
//		string  input;
//		cout << "Enter Roman Numeral: ";
//		while (cin >> input) {
//			cout << "   interpretation is " << RNInterpreter::interpret(input) << endl;
//			cout << "Enter Roman Numeral: ";
//		}
//	}
//
//	// Enter Roman Numeral: MCMXCVI
//	//    interpretation is 1996
//	// Enter Roman Numeral: MMMCMXCIX
//	//    interpretation is 3999
//	// Enter Roman Numeral: MMMM
//	//    interpretation is 0
//	// Enter Roman Numeral: MDCLXVIIII
//	//    interpretation is 0
//	// Enter Roman Numeral: CXCX
//	//    interpretation is 0
//	// Enter Roman Numeral: MDCLXVI
//	//    interpretation is 1666
//	// Enter Roman Numeral: DCCCLXXXVIII
//	//    interpretation is 888