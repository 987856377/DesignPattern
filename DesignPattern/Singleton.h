#pragma once
/*

1��������ֻ����һ��ʵ����
2������������Լ������Լ���Ψһʵ����
3�������������������������ṩ��һʵ����

��ͼ����֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣
��Ҫ�����һ��ȫ��ʹ�õ���Ƶ���ش��������١�
��ʱʹ�ã����������ʵ����Ŀ����ʡϵͳ��Դ��ʱ��
��ν�����ж�ϵͳ�Ƿ��Ѿ������������������򷵻أ����û���򴴽���
�ؼ����룺���캯����˽�еġ�
�ŵ㣺 1�����ڴ���ֻ��һ��ʵ�����������ڴ�Ŀ�����������Ƶ���Ĵ���������ʵ�����������ѧԺ��ҳҳ�滺�棩�� 
	   2���������Դ�Ķ���ռ�ã�����д�ļ���������
ȱ�㣺û�нӿڣ����ܼ̳У��뵥һְ��ԭ���ͻ��һ����Ӧ��ֻ�����ڲ��߼�����������������ô����ʵ������
ʹ�ó����� 1��Ҫ������Ψһ���кš� 
		   2��WEB �еļ�����������ÿ��ˢ�¶������ݿ����һ�Σ��õ����Ȼ��������� 
		   3��������һ��������Ҫ���ĵ���Դ���࣬���� I/O �����ݿ�����ӵȡ�

*/


class Singleton {

public:
	static Singleton * getInstance();
	static void destroyInstance();

private: 
	Singleton(){}
	Singleton(const Singleton&) {}
	
private:
	const static Singleton * m_Instance;
};

const Singleton * Singleton::m_Instance = new Singleton();

Singleton * Singleton::getInstance() {
	return const_cast<Singleton*>(m_Instance);
}

void Singleton::destroyInstance() {
	if (m_Instance!=nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}