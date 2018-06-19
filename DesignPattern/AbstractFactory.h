#pragma once


/*

意图：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
主要解决：主要解决接口选择的问题。
何时使用：系统的产品有多于一个的产品族，而系统只消费其中某一族的产品。
如何解决：在一个产品族里面，定义多个产品。
关键代码：在一个工厂里聚合多个同类产品。
优点：当一个产品族中的多个对象被设计成一起工作时，它能保证客户端始终只使用同一个产品族中的对象。
缺点：产品族扩展非常困难，要增加一个系列的某一产品，既要在抽象的 Creator 里加代码，又要在具体的里面加代码。
使用场景： 1、QQ 换皮肤，一整套一起换。 2、生成不同操作系统的程序。
注意事项：产品族难扩展，产品等级易扩展。

*/
class Shape {
public:
	virtual void draw() = 0;
};

class Rectangle :public Shape {
public:
	void draw() {
		std::cout << "draw Rectangle!" << std::endl;
	}
};

class Circle :public Shape {
public:
	void draw() {
		std::cout << "draw Circle!" << std::endl;
	}
};

class Square :public Shape {
public:
	void draw() {
		std::cout << "draw Square!" << std::endl;
	}
};


class Color {
public:
	virtual void fill() = 0;
};

class Red :public Color {
public:
	void fill() {
		std::cout << "fill Red!" << std::endl;
	}
};

class Black :public Color {
public:
	void fill() {
		std::cout << "fill Black!" << std::endl;
	}
};

class Blue :public Color {
public:
	void fill() {
		std::cout << "fill Blue!" << std::endl;
	}
};

class AbstractFactory {
public:
	virtual Shape * getShape(string shape) = 0;
	virtual Color * getColor(string color) = 0;
};

class ShapeFactory : public AbstractFactory{
public:
	Shape * getShape(string shape) {
		if (shape.empty())
		{
			return NULL;
		}
		if (shape._Equal("RECTANGLE")||shape._Equal("rectangle"))
		{
			return new Rectangle;
		}
		else if (shape._Equal("CIRCLE") || shape._Equal("circle"))
		{
			return new Circle;
		}
		else if (shape._Equal("SQUARE") || shape._Equal("square"))
		{
			return new Square;
		}
		return NULL;
	}

	Color * getColor(string color) {
		return NULL;
	}
};

class ColorFactory : public AbstractFactory {
public:
	Color * getColor(string color) {
		if (color.empty())
		{
			return NULL;
		}
		if (color._Equal("RED") || color._Equal("red"))
		{
			return new Red;
		}
		else if (color._Equal("BLACK") || color._Equal("black"))
		{
			return new Black;
		}
		else if (color._Equal("BLUE") || color._Equal("blue"))
		{
			return new Blue;
		}
		return NULL;
	}

	Shape * getShape(string shape) {
		return NULL;
	}
};

class FactoryProducer {
public :
	static AbstractFactory * getFactory(string choice) {
		if (choice._Equal("SHAPE"))
		{
			return new ShapeFactory;
		}
		else if (choice._Equal("COLOR"))
		{
			return new ColorFactory;
		}
		return NULL;
	}
};