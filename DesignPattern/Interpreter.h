#pragma once
/*

意图：给定一个语言，定义它的文法表示，并定义一个解释器，这个解释器使用该标识来解释语言中的句子。
主要解决：对于一些固定文法构建一个解释句子的解释器。
何时使用：如果一种特定类型的问题发生的频率足够高，那么可能就值得将该问题的各个实例表述为一个简单语言中的句子。这样就可以构建一个解释器，该解释器通过解释这些句子来解决该问题。
如何解决：构件语法树，定义终结符与非终结符。
关键代码：构件环境类，包含解释器之外的一些全局信息，一般是 HashMap。
应用实例：编译器、运算表达式计算。
优点： 1、可扩展性比较好，灵活。 2、增加了新的解释表达式的方式。 3、易于实现简单文法。
缺点： 1、可利用场景比较少。 2、对于复杂的文法比较难维护。 3、解释器模式会引起类膨胀。 4、解释器模式采用递归调用方法。
使用场景： 1、可以将一个需要解释执行的语言中的句子表示为一个抽象语法树。 2、一些重复出现的问题可以用一种简单的语言来进行表达。 3、一个简单语法需要解释的场景。
注意事项：可利用场景比较少，JAVA 中如果碰到可以用 expression4J 代替。

*/

class Thousand;  class Hundred;  class Ten;  class One;

class RNInterpreter {
public:
	RNInterpreter();		  // ctor for client
	RNInterpreter(int) { }  // ctor for subclasses, avoids infinite loop
	int interpret(char*);	  // interpret() for client
	virtual void interpret(char* input, int& total) {	// for internal use
		int  index;  index = 0;
		if (!strncmp(input, nine(), 2)) {
			total += 9 * multiplier();
			index += 2;
		}
		else if (!strncmp(input, four(), 2)) {
			total += 4 * multiplier();
			index += 2;
		}
		else {
			if (input[0] == five()) {
				total += 5 * multiplier();
				index = 1;
			}
			else index = 0;
			for (int end = index + 3; index < end; index++)
				if (input[index] == one())
					total += 1 * multiplier();
				else break;
		}
		strcpy(input, &(input[index]));
	}	// remove leading chars processed
protected:  // cannot be pure virtual because client asks for instance
	virtual char  one() { }		virtual char* four() { }
	virtual char  five() { }		virtual char* nine() { }
	virtual int   multiplier() { }
private:
	RNInterpreter * thousands;			RNInterpreter*  hundreds;
	RNInterpreter*  tens;				RNInterpreter*  ones;
};

class Thousand : public RNInterpreter {
public:  // provide 1-arg ctor to avoid infinite loop in base class ctor
	Thousand(int) : RNInterpreter(1) { }
protected:
	char  one() { return 'M'; }	char* four() { return ""; }
	char  five() { return '\0'; }	char* nine() { return ""; }
	int   multiplier() { return 1000; }
};

class Hundred : public RNInterpreter {
public:
	Hundred(int) : RNInterpreter(1) { }
protected:
	char  one() { return 'C'; }	char* four() { return "CD"; }
	char  five() { return 'D'; }	char* nine() { return "CM"; }
	int   multiplier() { return 100; }
};

class Ten : public RNInterpreter {
public:
	Ten(int) : RNInterpreter(1) { }
protected:
	char  one() { return 'X'; }	char* four() { return "XL"; }
	char  five() { return 'L'; }	char* nine() { return "XC"; }
	int   multiplier() { return 10; }
};

class One : public RNInterpreter {
public:
	One(int) : RNInterpreter(1) { }
protected:
	char  one() { return 'I'; }	char* four() { return "IV"; }
	char  five() { return 'V'; }	char* nine() { return "IX"; }
	int   multiplier() { return 1; }
};

RNInterpreter::RNInterpreter() {  // use 1-arg ctor to avoid infinite loop
	thousands = new Thousand(1);		hundreds = new Hundred(1);
	tens = new Ten(1);				ones = new One(1);
}

int RNInterpreter::interpret(char* input) {
	int  total;  total = 0;
	thousands->interpret(input, total);
	hundreds->interpret(input, total);
	tens->interpret(input, total);
	ones->interpret(input, total);
	if (strcmp(input, ""))	// if input was invalid, return 0
		return 0;
	return total;
}
