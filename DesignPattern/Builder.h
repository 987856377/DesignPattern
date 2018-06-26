#pragma once
/*

������ģʽ��Builder Pattern��ʹ�ö���򵥵Ķ���һ��һ��������һ�����ӵĶ���
�������͵����ģʽ���ڴ�����ģʽ�����ṩ��һ�ִ����������ѷ�ʽ��
һ�� Builder ���һ��һ���������յĶ��󡣸� Builder ���Ƕ�������������ġ�

��ͼ����һ�����ӵĹ��������ʾ����룬ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ��
��Ҫ�������Ҫ��������ϵͳ�У���ʱ��������"һ�����Ӷ���"�Ĵ�����������ͨ���ɸ������ֵ��Ӷ�����һ�����㷨���ɣ�
��������ı仯��������Ӷ���ĸ������־��������ž��ҵı仯�����ǽ����������һ����㷨ȴ����ȶ���
��ʱʹ�ã�һЩ������������䣬������Ͼ����仯��ʱ��
��ν���������벻����뿪��
�ؼ����룺�����ߣ��������ṩʵ�������ݣ������������ʵ����������ϵ��
Ӧ��ʵ���� 1��JAVA �е� StringBuilder��
�ŵ㣺 1�������߶���������չ�� 2�����ڿ���ϸ�ڷ��ա�
ȱ�㣺 1����Ʒ�����й�ͬ�㣬��Χ�����ơ� 2�����ڲ��仯���ӣ����кܶ�Ľ����ࡣ
ʹ�ó����� 1����Ҫ���ɵĶ�����и��ӵ��ڲ��ṹ�� 2����Ҫ���ɵĶ����ڲ����Ա����໥������
ע������빤��ģʽ�������ǣ�������ģʽ���ӹ�ע�����װ���˳��

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
