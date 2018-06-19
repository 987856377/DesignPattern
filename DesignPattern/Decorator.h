#pragma once
/*

��ͼ����̬�ظ�һ���������һЩ�����ְ�𡣾����ӹ�����˵��װ����ģʽ������������Ϊ��
��Ҫ�����һ��ģ�����Ϊ����չһ���ྭ��ʹ�ü̳з�ʽʵ�֣����ڼ̳�Ϊ�����뾲̬����������������չ���ܵ����࣬���������͡�
��ʱʹ�ã��ڲ������Ӻܶ�������������չ�ࡣ
��ν���������幦��ְ�𻮷֣�ͬʱ�̳�װ����ģʽ��
�ؼ����룺 1��Component ��䵱�����ɫ����Ӧ�þ���ʵ�֡� 2�����������úͼ̳� Component �࣬������չ����д���෽����
Ӧ��ʵ���� 1��������� 72 �䣬�������"����"�����ĸ�������һֻ���ӣ�����������������Ĺ��ܡ� 
			2������һ������û�л��򶼿��Թ���ǽ�ϣ�����ͨ�������л���ģ�����ʵ�����ǻ��򱻹���ǽ�ϡ�
				�ڹ���ǽ��֮ǰ�������Ա����ϲ�����װ���������ʱ���������ͻ����γ���һ�����塣
�ŵ㣺װ����ͱ�װ������Զ�����չ�������໥��ϣ�װ��ģʽ�Ǽ̳е�һ�����ģʽ��װ��ģʽ���Զ�̬��չһ��ʵ����Ĺ��ܡ�
ȱ�㣺���װ�αȽϸ��ӡ�
ʹ�ó����� 1����չһ����Ĺ��ܡ� 2����̬���ӹ��ܣ���̬������
ע������ɴ���̳С�

*/

class Widget {
public:
	virtual void draw() = 0;
};

class TextField : public Widget {
public:
	TextField(int h,int w):height(h),width(w){}
	void draw() {
		std::cout<< "TextField: " << width << ", " << height << std::endl;
	}

private:
	int height;
	int width;
};

class Decorator : public Widget {
public:
	Decorator(Widget *& widget) {
		this->widget = widget;
	}

	void draw() {
		widget->draw();
	}
private:
	Widget * widget;
};

class BorderDecorator : public Decorator {
public:
	BorderDecorator(Widget *& widget) : Decorator(widget) {}

	void draw() {
		Decorator::draw();
		std::cout << "TextField: " << "set Border" << std::endl;
	}
};

class ScrollDecorator : public Decorator {
public:
	ScrollDecorator(Widget *& widget) : Decorator(widget) {}

	void draw() {
		Decorator::draw();
		std::cout << "TextField: " << "set ScrollBar" << std::endl;
	}
};