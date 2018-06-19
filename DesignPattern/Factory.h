#pragma once

/*

��ͼ������һ����������Ľӿڣ����������Լ�����ʵ������һ�������࣬����ģʽʹ�䴴�������ӳٵ�������С�
��Ҫ�������Ҫ����ӿ�ѡ������⡣
��ʱʹ�ã�������ȷ�ؼƻ���ͬ�����´�����ͬʵ��ʱ��
��ν������������ʵ�ֹ����ӿڣ����ص�Ҳ��һ������Ĳ�Ʒ��
�ؼ����룺����������������ִ�С�
Ӧ��ʵ���� 1������Ҫһ������������ֱ�Ӵӹ������������������ȥ��������������ô�������ģ��Լ������������ľ���ʵ�֡� 
			2��Hibernate �����ݿ�ֻ�軻���Ժ������Ϳ��ԡ�
�ŵ㣺  1��һ���������봴��һ������ֻҪ֪�������ƾͿ����ˡ� 
		2����չ�Ըߣ����������һ����Ʒ��ֻҪ��չһ��������Ϳ��ԡ� 
		3�����β�Ʒ�ľ���ʵ�֣�������ֻ���Ĳ�Ʒ�Ľӿڡ�
ȱ�㣺ÿ������һ����Ʒʱ������Ҫ����һ��������Ͷ���ʵ�ֹ�����ʹ��ϵͳ����ĸ����ɱ����ӣ���һ���̶���������ϵͳ�ĸ��Ӷȣ�
		ͬʱҲ������ϵͳ��������������Ⲣ����ʲô���¡�
ʹ�ó�����  1����־��¼������¼���ܼ�¼������Ӳ�̡�ϵͳ�¼���Զ�̷������ȣ��û�����ѡ���¼��־��ʲô�ط��� 
			2�����ݿ���ʣ����û���֪�����ϵͳ������һ�����ݿ⣬�Լ����ݿ�����б仯ʱ�� 
			3�����һ�����ӷ������Ŀ�ܣ���Ҫ����Э�飬"POP3"��"IMAP"��"HTTP"�����԰���������Ϊ��Ʒ�࣬��ͬʵ��һ���ӿڡ�
ע�������Ϊһ�ִ�����ģʽ�����κ���Ҫ���ɸ��Ӷ���ĵط���������ʹ�ù�������ģʽ����һ����Ҫע��ĵط����Ǹ��Ӷ����ʺ�ʹ�ù���ģʽ��
			���򵥶����ر���ֻ��Ҫͨ�� new �Ϳ�����ɴ����Ķ�������ʹ�ù���ģʽ�����ʹ�ù���ģʽ������Ҫ����һ�������࣬������ϵͳ�ĸ��Ӷȡ�

*/
class Ball {
public:
	virtual void play() = 0;
};

class Footbal : public Ball {
public:
	void play() {
		std::cout << "play footbal!" << std::endl;
	}
};

class Basketball : public Ball {
public:
	void play() {
		std::cout << "play basketball!" << std::endl;
	}
};

class Tabletennis : public Ball {
public:
	void play() {
		std::cout << "play tabletennis!" << std::endl;
	}
};

class BallFactory {
public :
	Ball * playBall(string type) {
		if (type._Equal(""))
		{
			return NULL;
		}
		if (type._Equal("FOOTBALL") || type._Equal("football"))
		{
			return new Footbal;
		}
		else if (type._Equal("BASKETBALL") || type._Equal("basketball"))
		{
			return new Basketball;
		}
		else if (type._Equal("TABLETENNIS") || type._Equal("tabletennis"))
		{
			return new Tabletennis;
		}
		return NULL;
	}
};