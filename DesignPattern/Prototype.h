#pragma once
/*

ԭ��ģʽ��Prototype Pattern�������ڴ����ظ��Ķ���ͬʱ���ܱ�֤���ܡ�
�������͵����ģʽ���ڴ�����ģʽ�����ṩ��һ�ִ����������ѷ�ʽ��
����ģʽ��ʵ����һ��ԭ�ͽӿڣ��ýӿ����ڴ�����ǰ����Ŀ�¡����ֱ�Ӵ�������Ĵ��۱Ƚϴ�ʱ�����������ģʽ��
���磬һ��������Ҫ��һ���ߴ��۵����ݿ����֮�󱻴�����
���ǿ��Ի���ö�������һ������ʱ�������Ŀ�¡������Ҫ��ʱ��������ݿ⣬�Դ����������ݿ���á�

��ͼ����ԭ��ʵ��ָ��������������࣬����ͨ��������Щԭ�ʹ����µĶ���
��Ҫ������������ڽ�����ɾ��ԭ�͡�
��ʱʹ�ã� 1����һ��ϵͳӦ�ö��������Ĳ�Ʒ���������ɺͱ�ʾʱ�� 
			2����Ҫʵ����������������ʱ��ָ��ʱ�����磬ͨ����̬װ�ء� 
			3��Ϊ�˱��ⴴ��һ�����Ʒ����ƽ�еĹ�������ʱ�� 
			4����һ�����ʵ��ֻ���м�����ͬ״̬����е�һ��ʱ��������Ӧ��Ŀ��ԭ�Ͳ���¡���ǿ��ܱ�ÿ���ú��ʵ�״̬�ֹ�ʵ�������������һЩ��
��ν�����������е�һ��ԭ�Ͷ��󣬿��ٵ����ɺ�ԭ�Ͷ���һ����ʵ����
�ؼ����룺 1��ʵ�ֿ�¡�������� JAVA �̳� Cloneable����д clone()���� .NET �п���ʹ�� Object ��� MemberwiseClone() ������ʵ�ֶ����ǳ������ͨ�����л��ķ�ʽ��ʵ������� 
			2��ԭ��ģʽͬ�����ڸ���������ʹ���ߺ;������ͣ��ױ��ࣩ֮�����Ϲ�ϵ����ͬ��Ҫ����Щ"�ױ���"ӵ���ȶ��Ľӿڡ�
Ӧ��ʵ���� 1��ϸ�����ѡ� 2��JAVA �е� Object clone() ������
�ŵ㣺 1��������ߡ� 2���ӱܹ��캯����Լ����
ȱ�㣺 1���䱸��¡������Ҫ����Ĺ��ܽ���ͨ�̿��ǣ������ȫ�µ��಻�Ǻ��ѣ����������е��಻һ�������ף��ر�һ�������ò�֧�ִ��л��ļ�Ӷ��󣬻������ú���ѭ���ṹ��ʱ�� 
		2������ʵ�� Cloneable �ӿڡ�
ע�������ͨ����һ�������ʵ�����������¶���ͬ���ǣ�ԭ��ģʽ��ͨ������һ�����ж��������¶���ġ�ǳ����ʵ�� Cloneable����д�������ͨ��ʵ�� Serializable ��ȡ����������

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