#pragma once
#include <string>
using namespace std;
/*

享元模式（Flyweight Pattern）主要用于减少创建对象的数量，以减少内存占用和提高性能。
这种类型的设计模式属于结构型模式，它提供了减少对象数量从而改善应用所需的对象结构的方式。
享元模式尝试重用现有的同类对象，如果未找到匹配的对象，则创建新对象。

意图：运用共享技术有效地支持大量细粒度的对象。
主要解决：在有大量对象时，有可能会造成内存溢出，我们把其中共同的部分抽象出来，
			如果有相同的业务请求，直接返回在内存中已有的对象，避免重新创建。
何时使用： 1、系统中有大量对象。 
			2、这些对象消耗大量内存。 
			3、这些对象的状态大部分可以外部化。 
			4、这些对象可以按照内蕴状态分为很多组，当把外蕴对象从对象中剔除出来时，每一组对象都可以用一个对象来代替。 
			5、系统不依赖于这些对象身份，这些对象是不可分辨的。
如何解决：用唯一标识码判断，如果在内存中有，则返回这个唯一标识码所标识的对象。
关键代码：用 HashMap 存储这些对象。
应用实例： 1、JAVA 中的 String，如果有则返回，如果没有则创建一个字符串保存在字符串缓存池里面。 
			2、数据库的数据池。
优点：大大减少对象的创建，降低系统的内存，使效率提高。
缺点：提高了系统的复杂度，需要分离出外部状态和内部状态，而且外部状态具有固有化的性质，
		不应该随着内部状态的变化而变化，否则会造成系统的混乱。
使用场景： 1、系统有大量相似对象。 2、需要缓冲池的场景。
注意事项： 1、注意划分外部状态和内部状态，否则可能会引起线程安全问题。 2、这些类必须有一个工厂对象加以控制。

*/

class Icon {
public:
	Icon(string fileName) {
		this->_name = fileName;
		if (!fileName._Equal("go")) { _width = 20;  _height = 20; }
		if (!fileName._Equal("stop")) { _width = 40;  _height = 40; }
		if (!fileName._Equal("select")) { _width = 60;  _height = 60; }
		if (!fileName._Equal("undo")) { _width = 30;  _height = 30; }
	}
	const string getName() { return _name.data(); }
	void draw(int x, int y) {
		cout << "   drawing " << _name.data() << ": upper left (" << x << "," << y
			<< ") - lower right (" << x + _width << "," << y + _height << ")"
			<< endl;
	}
private:
	string  _name;
	int   _width;
	int   _height;
};


class FlyweightFactory {
public:
	static Icon* getIcon(string name) {
		for (int i = 0; i < _numIcons; i++)
			if (name._Equal(_icons[i]->getName()))
				return _icons[i];
		_icons[_numIcons] = new Icon(name);
		return _icons[_numIcons++];
	}
	static void reportTheIcons() {
		cout << "Active Flyweights: ";
		for (int i = 0; i < _numIcons; i++)
			cout << _icons[i]->getName().data() << " ";
		cout << endl;
	}
private:
	enum { MAX_ICONS = 5 };
	static int    _numIcons;
	static Icon*  _icons[MAX_ICONS];
};

int   FlyweightFactory::_numIcons = 0;
Icon* FlyweightFactory::_icons[];


class DialogBox {
public:
	DialogBox(int x, int y, int incr) : _iconsOriginX(x), _iconsOriginY(y),
		_iconsXIncrement(incr) { }
	virtual void draw() = 0;
protected:
	Icon * _icons[3];
	int   _iconsOriginX;
	int   _iconsOriginY;
	int   _iconsXIncrement;
};

class FileSelection : public DialogBox {
public:
	FileSelection(Icon* first, Icon* second, Icon* third) :
		DialogBox(100, 100, 100) {
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}
	void draw() {
		cout << "drawing FileSelection:" << endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX + (i * _iconsXIncrement),
				_iconsOriginY);
	}
};

class CommitTransaction : public DialogBox {
public:
	CommitTransaction(Icon* first, Icon* second, Icon* third) :
		DialogBox(150, 150, 150) {
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}
	void draw() {
		cout << "drawing CommitTransaction:" << endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX + (i * _iconsXIncrement),
				_iconsOriginY);
	}
};
