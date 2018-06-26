#pragma once
#include <vector>
/*

���ģʽ��Composite Pattern�����ֽв�������ģʽ�������ڰ�һ�����ƵĶ�����һ����һ�Ķ���
���ģʽ�������νṹ����϶���������ʾ�����Լ������Ρ��������͵����ģʽ���ڽṹ��ģʽ���������˶���������νṹ��
����ģʽ������һ�������Լ���������ࡣ�����ṩ���޸���ͬ������ķ�ʽ��

��ͼ����������ϳ����νṹ�Ա�ʾ"����-����"�Ĳ�νṹ�����ģʽʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�
��Ҫ����������������ͽṹ�������У�ģ���˼�Ԫ�غ͸���Ԫ�صĸ���ͻ�������������Ԫ��һ����������Ԫ�أ��Ӷ�ʹ�ÿͻ������븴��Ԫ�ص��ڲ��ṹ���
��ʱʹ�ã� 1�������ʾ����Ĳ���-�����νṹ�����νṹ���� 
			2����ϣ���û�������϶����뵥������Ĳ�ͬ���û���ͳһ��ʹ����Ͻṹ�е����ж���
��ν������֦��Ҷ��ʵ��ͳһ�ӿڣ���֦�ڲ���ϸýӿڡ�
�ؼ����룺��֦�ڲ���ϸýӿڣ����Һ����ڲ����� List������� Component��
Ӧ��ʵ���� 1���������ʽ����������������������һ�������������У���һ��������Ҳ�����ǲ�����������������һ���������� 
			2���� JAVA AWT �� SWING �У����� Button �� Checkbox ����Ҷ��Container ����֦��
�ŵ㣺 1���߲�ģ����ü򵥡� 2���ڵ��������ӡ�
ȱ�㣺��ʹ�����ģʽʱ����Ҷ�Ӻ���֦����������ʵ���࣬�����ǽӿڣ�Υ������������ԭ��
ʹ�ó��������֡����峡���������β˵����ļ����ļ��еĹ���
ע���������ʱΪ�����ࡣ

*/

// Purpose.  Composite design pattern
class Component { 
public: 
	virtual void traverse() = 0; 
};

class Leaf : public Component {        // 1. Scalar class   3. "isa" relationship
	int value;
public:
	Leaf(int val) { 
		value = val; 
	}
	void traverse() { 
		cout << value << ' '; 
	}
};

class Composite : public Component {   // 1. Vector class   3. "isa" relationship
	vector<Component*> children;        // 4. "container" coupled to the interface
public:
	// 4. "container" class coupled to the interface
	void add(Component* ele) { 
		children.push_back(ele); 
	}
	void traverse() {
		for (int i = 0; i < children.size(); i++)
			// 5. Use polymorphism to delegate to children
			children[i]->traverse();
	}
};


/*

// Purpose.  Composite design pattern - multiple container classes
class Component { 
public: 
	virtual void traverse() = 0; 
};

class Primitive : public Component {
	int value;
public:
	Primitive(int val) { 
		value = val; 
	}
	void traverse() { 
		cout << value << "  "; 
	}
};

class Composite : public Component {
	vector<Component*> children;
	int  value;
public:
	Composite(int val) { 
		value = val; 
	}
	void add(Component* c) { 
		children.push_back(c); 
	}
	void traverse() {
		cout << value << "  ";
		for (int i = 0; i < children.size(); i++)
			children[i]->traverse();
	}
};

class Row : public Composite {
public:     // Two different kinds of "con-tainer" classes.  Most of the "meat" is in the Composite base class.
	Row(int val) : Composite(val) { }  
	void traverse() {                      
		cout << "Row";                      
		Composite::traverse();
	}
};

class Column : public Composite {
public:
	Column(int val) : Composite(val) { }
	void traverse() {
		cout << "Col";
		Composite::traverse();
	}
};
*/