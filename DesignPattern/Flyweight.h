#pragma once
#include <string>
/*

��Ԫģʽ��Flyweight Pattern����Ҫ���ڼ��ٴ���������������Լ����ڴ�ռ�ú�������ܡ�
�������͵����ģʽ���ڽṹ��ģʽ�����ṩ�˼��ٶ��������Ӷ�����Ӧ������Ķ���ṹ�ķ�ʽ��
��Ԫģʽ�����������е�ͬ��������δ�ҵ�ƥ��Ķ����򴴽��¶���

��ͼ�����ù�������Ч��֧�ִ���ϸ���ȵĶ���
��Ҫ��������д�������ʱ���п��ܻ�����ڴ���������ǰ����й�ͬ�Ĳ��ֳ��������
			�������ͬ��ҵ������ֱ�ӷ������ڴ������еĶ��󣬱������´�����
��ʱʹ�ã� 1��ϵͳ���д������� 
			2����Щ�������Ĵ����ڴ档 
			3����Щ�����״̬�󲿷ֿ����ⲿ���� 
			4����Щ������԰�������״̬��Ϊ�ܶ��飬�������̶���Ӷ������޳�����ʱ��ÿһ����󶼿�����һ�����������档 
			5��ϵͳ����������Щ������ݣ���Щ�����ǲ��ɷֱ�ġ�
��ν������Ψһ��ʶ���жϣ�������ڴ����У��򷵻����Ψһ��ʶ������ʶ�Ķ���
�ؼ����룺�� HashMap �洢��Щ����
Ӧ��ʵ���� 1��JAVA �е� String��������򷵻أ����û���򴴽�һ���ַ����������ַ�����������档 
			2�����ݿ�����ݳء�
�ŵ㣺�����ٶ���Ĵ���������ϵͳ���ڴ棬ʹЧ����ߡ�
ȱ�㣺�����ϵͳ�ĸ��Ӷȣ���Ҫ������ⲿ״̬���ڲ�״̬�������ⲿ״̬���й��л������ʣ�
		��Ӧ�������ڲ�״̬�ı仯���仯����������ϵͳ�Ļ��ҡ�
ʹ�ó����� 1��ϵͳ�д������ƶ��� 2����Ҫ����صĳ�����
ע����� 1��ע�⻮���ⲿ״̬���ڲ�״̬��������ܻ������̰߳�ȫ���⡣ 2����Щ�������һ������������Կ��ơ�

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
			if (!name._Equal(_icons[i]->getName()))
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
