#pragma once


/*

��ͼ���ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ
��Ҫ�������Ҫ����ӿ�ѡ������⡣
��ʱʹ�ã�ϵͳ�Ĳ�Ʒ�ж���һ���Ĳ�Ʒ�壬��ϵͳֻ��������ĳһ��Ĳ�Ʒ��
��ν������һ����Ʒ�����棬��������Ʒ��
�ؼ����룺��һ��������ۺ϶��ͬ���Ʒ��
�ŵ㣺��һ����Ʒ���еĶ��������Ƴ�һ����ʱ�����ܱ�֤�ͻ���ʼ��ֻʹ��ͬһ����Ʒ���еĶ���
ȱ�㣺��Ʒ����չ�ǳ����ѣ�Ҫ����һ��ϵ�е�ĳһ��Ʒ����Ҫ�ڳ���� Creator ��Ӵ��룬��Ҫ�ھ��������Ӵ��롣
ʹ�ó����� 1��QQ ��Ƥ����һ����һ�𻻡� 2�����ɲ�ͬ����ϵͳ�ĳ���
ע�������Ʒ������չ����Ʒ�ȼ�����չ��

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