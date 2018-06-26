#pragma once
/*

建造者模式（Builder Pattern）使用多个简单的对象一步一步构建成一个复杂的对象。
这种类型的设计模式属于创建型模式，它提供了一种创建对象的最佳方式。
一个 Builder 类会一步一步构造最终的对象。该 Builder 类是独立于其他对象的。

意图：将一个复杂的构建与其表示相分离，使得同样的构建过程可以创建不同的表示。
主要解决：主要解决在软件系统中，有时候面临着"一个复杂对象"的创建工作，其通常由各个部分的子对象用一定的算法构成；
由于需求的变化，这个复杂对象的各个部分经常面临着剧烈的变化，但是将它们组合在一起的算法却相对稳定。
何时使用：一些基本部件不会变，而其组合经常变化的时候。
如何解决：将变与不变分离开。
关键代码：建造者：创建和提供实例，导演：管理建造出来的实例的依赖关系。
应用实例： 1、JAVA 中的 StringBuilder。
优点： 1、建造者独立，易扩展。 2、便于控制细节风险。
缺点： 1、产品必须有共同点，范围有限制。 2、如内部变化复杂，会有很多的建造类。
使用场景： 1、需要生成的对象具有复杂的内部结构。 2、需要生成的对象内部属性本身相互依赖。
注意事项：与工厂模式的区别是：建造者模式更加关注与零件装配的顺序。

*/

class Car {
public:
	Car() {}

	void setColor(string color) {
		this->color = color;
	}
	void setType(string type) {
		this->type = type;
	}
	void setEngine(string engine) {
		this->engine = engine;
	}

	string getColor() {
		return this->color;
	}
	string getType() {
		return this->type;
	}
	string getEngine() {
		return this->engine;
	}

private:
	string color;
	string type;
	string engine;
};

class CarBuilder {
public:
	virtual void buildColor(string color) = 0;
	virtual void buildType(string type) = 0;
	virtual void buildEngine(string engine) = 0;
	virtual Car * buildCar() = 0;
};

class ConcretBuilder : public CarBuilder{
public:

	ConcretBuilder() {
		car = new Car();
	}

	void buildColor(string color) {
		car->setColor(color);
	}
	void buildType(string type) {
		car->setType(type);
	}
	void buildEngine(string engine) {
		car->setEngine(engine);
	}

	Car * buildCar() {
		return this->car;
	}
private:
	Car * car;
};

class CarDirector {
public:
	static Car * constructor(CarBuilder *& carBuilder) {
		
		carBuilder->buildColor("RED");
		carBuilder->buildType("BUSSINESS");
		carBuilder->buildEngine("TIGER");
		return carBuilder->buildCar();
	}
};
