#pragma once

/*

��ͼ������һϵ�е��㷨,������һ������װ����, ����ʹ���ǿ��໥�滻��
��Ҫ��������ж����㷨���Ƶ�����£�ʹ�� if...else �������ĸ��Ӻ�����ά����
��ʱʹ�ã�һ��ϵͳ���������࣬���������ǵ�ֻ������ֱ�ӵ���Ϊ��
��ν��������Щ�㷨��װ��һ��һ�����࣬������滻��
�ؼ����룺ʵ��ͬһ���ӿڡ�
Ӧ��ʵ���� 1��������Ľ�����ƣ�ÿһ�����Ҿ���һ�����ԡ� 2�����еĳ��η�ʽ��ѡ�������г�����������ÿһ�����з�ʽ����һ�����ԡ� 3��JAVA AWT �е� LayoutManager��
�ŵ㣺 1���㷨���������л��� 2������ʹ�ö��������жϡ� 3����չ�����á�
ȱ�㣺 1������������ࡣ 2�����в����඼��Ҫ���Ⱪ¶��
ʹ�ó����� 1�������һ��ϵͳ����������࣬����֮���������������ǵ���Ϊ����ôʹ�ò���ģʽ���Զ�̬����һ�������������Ϊ��ѡ��һ����Ϊ�� 2��һ��ϵͳ��Ҫ��̬���ڼ����㷨��ѡ��һ�֡� 3�����һ�������кܶ����Ϊ���������ǡ����ģʽ����Щ��Ϊ��ֻ��ʹ�ö��ص�����ѡ�������ʵ�֡�
ע��������һ��ϵͳ�Ĳ��Զ����ĸ�������Ҫ����ʹ�û��ģʽ��������������͵����⡣

*/

class Strategy;

class TestBed {
public:
	enum StrategyType { Dummy, Left, Right, Center };
	TestBed() { strategy_ = NULL; }
	void setStrategy(int type, int width);
	void doIt();
private:
	Strategy * strategy_;
};

class Strategy {
public:
	Strategy(int width) : width_(width) { }
	void format() {
		char line[80], word[30];
		ifstream  inFile("quote.txt", ios::in);
		line[0] = '\0';

		inFile >> word;
		strcat(line, word);
		while (inFile >> word)
		{
			if (strlen(line) + strlen(word) + 1 > width_)
				justify(line);
			else
				strcat(line, " ");
			strcat(line, word);
		}
		justify(line);
	}
protected:
	int     width_;
private:
	virtual void justify(char* line) = 0;
};

class LeftStrategy : public Strategy {
public:
	LeftStrategy(int width) : Strategy(width) { }
private:
	/* virtual */ void justify(char* line) {
		cout << line << endl;
		line[0] = '\0';
	}
};

class RightStrategy : public Strategy {
public:
	RightStrategy(int width) : Strategy(width) { }
private:
	/* virtual */ void justify(char* line) {
		char  buf[80];
		int   offset = width_ - strlen(line);
		memset(buf, ' ', 80);
		strcpy(&(buf[offset]), line);
		cout << buf << endl;
		line[0] = '\0';
	}
};

class CenterStrategy : public Strategy {
public:
	CenterStrategy(int width) : Strategy(width) { }
private:
	/* virtual */ void justify(char* line) {
		char  buf[80];
		int   offset = (width_ - strlen(line)) / 2;
		memset(buf, ' ', 80);
		strcpy(&(buf[offset]), line);
		cout << buf << endl;
		line[0] = '\0';
	}
};

void TestBed::setStrategy(int type, int width) {
	delete strategy_;
	if (type == Left)   strategy_ = new LeftStrategy(width);
	else if (type == Right)  strategy_ = new RightStrategy(width);
	else if (type == Center) strategy_ = new CenterStrategy(width);
}

void TestBed::doIt() { strategy_->format(); }


//
//void main() {
//	TestBed  test;
//	int      answer, width;
//	cout << "Exit(0) Left(1) Right(2) Center(3): ";
//	cin >> answer;
//	while (answer)
//	{
//		cout << "Width: ";
//		cin >> width;
//		test.setStrategy(answer, width);
//		test.doIt();
//		cout << "Exit(0) Left(1) Right(2) Center(3): ";
//		cin >> answer;
//	}
//	return 0;
//}