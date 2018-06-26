#pragma once
/*

原型模式（Prototype Pattern）是用于创建重复的对象，同时又能保证性能。
这种类型的设计模式属于创建型模式，它提供了一种创建对象的最佳方式。
这种模式是实现了一个原型接口，该接口用于创建当前对象的克隆。当直接创建对象的代价比较大时，则采用这种模式。
例如，一个对象需要在一个高代价的数据库操作之后被创建。
我们可以缓存该对象，在下一个请求时返回它的克隆，在需要的时候更新数据库，以此来减少数据库调用。

意图：用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
主要解决：在运行期建立和删除原型。
何时使用： 1、当一个系统应该独立于它的产品创建，构成和表示时。 
			2、当要实例化的类是在运行时刻指定时，例如，通过动态装载。 
			3、为了避免创建一个与产品类层次平行的工厂类层次时。 
			4、当一个类的实例只能有几个不同状态组合中的一种时。建立相应数目的原型并克隆它们可能比每次用合适的状态手工实例化该类更方便一些。
如何解决：利用已有的一个原型对象，快速地生成和原型对象一样的实例。
关键代码： 1、实现克隆操作，在 JAVA 继承 Cloneable，重写 clone()，在 .NET 中可以使用 Object 类的 MemberwiseClone() 方法来实现对象的浅拷贝或通过序列化的方式来实现深拷贝。 
			2、原型模式同样用于隔离类对象的使用者和具体类型（易变类）之间的耦合关系，它同样要求这些"易变类"拥有稳定的接口。
应用实例： 1、细胞分裂。 2、JAVA 中的 Object clone() 方法。
优点： 1、性能提高。 2、逃避构造函数的约束。
缺点： 1、配备克隆方法需要对类的功能进行通盘考虑，这对于全新的类不是很难，但对于已有的类不一定很容易，特别当一个类引用不支持串行化的间接对象，或者引用含有循环结构的时候。 
		2、必须实现 Cloneable 接口。
注意事项：与通过对一个类进行实例化来构造新对象不同的是，原型模式是通过拷贝一个现有对象生成新对象的。浅拷贝实现 Cloneable，重写，深拷贝是通过实现 Serializable 读取二进制流。

*/

class Prototype
{
protected:
	Prototype();
public:
	virtual Prototype* Clone() const = 0;
	virtual ~Prototype();
};


class ConcretePrototype1 : public Prototype
{
public:
	ConcretePrototype1();
	~ConcretePrototype1();
	ConcretePrototype1(const ConcretePrototype1&);
	virtual Prototype* Clone() const;
};


class ConcretePrototype2 :public Prototype
{
public:
	ConcretePrototype2();
	~ConcretePrototype2();
	ConcretePrototype2(const ConcretePrototype2&);
	virtual Prototype* Clone() const;
};

Prototype::Prototype()
{
	cout << "Prototype" << endl;
}

Prototype::~Prototype()
{
	cout << "~Prototype" << endl;
}

//ConcretePrototype1
ConcretePrototype1::ConcretePrototype1()
{
	cout << "ConcretePrototype1" << endl;
}

ConcretePrototype1::~ConcretePrototype1()
{
	cout << "~ConcretePrototype1" << endl;
}

ConcretePrototype1::ConcretePrototype1(const ConcretePrototype1& cp)
{
	cout << "ConcretePrototype1 copy" << endl;
}

Prototype* ConcretePrototype1::Clone() const
{
	return new ConcretePrototype1(*this);
}

//ConcretePrototype2
ConcretePrototype2::ConcretePrototype2()
{
	cout << "ConcretePrototype2" << endl;
}

ConcretePrototype2::~ConcretePrototype2()
{
	cout << "~ConcretePrototype2" << endl;
}

ConcretePrototype2::ConcretePrototype2(const ConcretePrototype2& cp)
{
	cout << "ConcretePrototype2 copy" << endl;
}

Prototype* ConcretePrototype2::Clone() const
{
	return new ConcretePrototype2(*this);
}