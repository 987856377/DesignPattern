// DesignPattern.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 创建模式
#include "Singleton.h"
#include "AbstractFactory.h"
#include "Factory.h"
#include "Builder.h"
#include "Prototype.h"

// 结构模式
#include "Adapter.h"
#include "Proxy.h"
#include "Facade.h"
#include "Composite.h"
#include "Decorator.h"
#include "Bridge.h"
#include "Flyweight.h"

// 行为模式
#include "Commond.h"
//#include "Observe.h"
//#include "Iterator.h"
//#include "Template.h"
//#include "Strategy.h"
//#include "ChainofResponsibility.h"
//#include "Mediator.h"
//#include "State.h"
//#include "Memento.h"
//#include "Interpreter.h"
//#include "Visitor.h"
using namespace std;

int main() {

	/*		//单例模式
	Singleton * instance = Singleton::getInstance();
	cout << sizeof(instance) << endl;
	Singleton::destroyInstance();*/


	/*		//抽象工厂模式
	//AbstractFactory * abstractFactory = new ShapeFactory();						// 直接使用抽象工厂
	AbstractFactory * abstractFactory = FactoryProducer::getFactory("SHAPE");		// 使用工厂代理
	Shape * shape = abstractFactory->getShape("circle");
	shape->draw();*/

	/*		//工厂模式
	BallFactory * ballFactory = new BallFactory;
	Ball * ball = ballFactory->playBall("football");
	ball->play();*/

	/*		//建造者模式
	CarBuilder * builder = new ConcretBuilder();
	Car * car = CarDirector::constructor(builder);
	// string to char 
	cout << car->getColor().data() << endl << car->getType().data() << endl << car->getEngine().data() << endl;*/

	/*		//原型模式
	Prototype* p1 = new ConcretePrototype1();
	Prototype* p2 = p1->Clone();
	Prototype* p3 = new ConcretePrototype2();
	Prototype* p4 = p3->Clone();*/

	/*		// 适配器模式
	//MediaAdapter * player = new MediaAdapter("MP4");		// 直接使用适配器
	AudioPlayer * player = new AudioPlayer();				// 间接使用适配器
	player->play("MP4", "骄傲的少年");*/

	/*		//桥接模式
	DrawAPI * api = new RedCircle();
	ConcreteCircle * circle = new ConcreteCircle(api, 5, 8, 8);
	circle->draw();*/

	/*		组合模式
	// Purpose.  Composite design pattern
	Composite containers[4];
	int i = 0;
	for (i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			containers[i].add(new Leaf(i * 3 + j));

	for (i = 1; i < 4; i++)
		containers[0].add(&(containers[i]));

	for (i = 0; i < 4; i++) {
		containers[i].traverse();
		cout << endl;
	}

	
	// Purpose.  Composite design pattern - multiple container classes
	Row    first(1);                     // Row1
	Column second(2);                    //   |
	Column third(3);                     //   +-- Col2
	Row    fourth(4);                    //   |     |
	Row    fifth(5);                     //   |     +-- 7
	first.add(&second);                  //   +-- Col3
	first.add(&third);                   //   |     |
	third.add(&fourth);                  //   |     +-- Row4
	third.add(&fifth);                   //   |     |     |
	first.add(&Primitive(6));            //   |     |     +-- 9
	second.add(&Primitive(7));           //   |     +-- Row5
	third.add(&Primitive(8));            //   |     |     |
	fourth.add(&Primitive(9));           //   |     |     +-- 10
	fifth.add(&Primitive(10));           //   |     +-- 8
	first.traverse();  cout << '\n';*/   //   +-- 6

	/*		装饰器模式
	Widget * widget = new TextField(20, 40);
	Decorator * decorator = new BorderDecorator(widget);
	decorator->draw();*/

	/*		外观模式
	WannaGo * wanna = new WannaGo;
	wanna->doGoTop();*/
	

	/*		享元模式
	DialogBox * dialogs[2];
	dialogs[0] = new FileSelection(
		FlyweightFactory::getIcon("go"),
		FlyweightFactory::getIcon("stop"),
		FlyweightFactory::getIcon("select"));
	dialogs[1] = new CommitTransaction(
		FlyweightFactory::getIcon("select"),
		FlyweightFactory::getIcon("stop"),
		FlyweightFactory::getIcon("undo"));

	for (int i = 0; i < 2; i++)
		dialogs[i]->draw();

	FlyweightFactory::reportTheIcons();*/

	
	/*		代理模式
	Find * find_room = new ConcretFindRoom("两室一厅");
	FindProxy * proxy = new FindProxy(find_room);
	proxy->FindRoom();
	*/

	/*		责任链模式
	srand(time(0));
	Handler1 root;   Handler2 two;   Handler3 thr;
	root.add(&two);   root.add(&thr);
	thr.setNext(&root);
	for (int i = 1; i < 10; i++) {
		root.handle(i);   cout << '\n';
	}*/
	
	/*		命令模式
	// Fred will "execute" Barney which will result in a call to passOn()
	// Barney will "execute" Betty which will result in a call to gossip()
	// Betty will "execute" Wilma which will result in a call to listen()
	Person wilma("Wilma", Command());
	// 2. Instantiate an object for each "callback"
	// 3. Pass each object to its future "sender"
	Person betty("Betty", Command(&wilma, &Person::listen));
	Person barney("Barney", Command(&betty, &Person::gossip));
	Person fred("Fred", Command(&barney, &Person::passOn));
	fred.talk();*/

	/*		解释器模式
	RNInterpreter interpreter;
	char          input[20];
	cout << "Enter Roman Numeral: ";
	while (cin >> input)
	{
		cout << "   interpretation is " << interpreter.interpret(input) << endl;
		cout << "Enter Roman Numeral: ";
	}*/

	/*		迭代器模式
	Stack  s1;
	for (int i = 1; i < 5; i++) s1.push(i);
	Stack  s2(s1), s3(s1), s4(s1), s5(s1);
	s3.pop();       s5.pop();
	s4.push(2);   s5.push(9);
	cout << "1 == 2 is " << (s1 == s2) << endl;
	cout << "1 == 3 is " << (s1 == s3) << endl;
	cout << "1 == 4 is " << (s1 == s4) << endl;
	cout << "1 == 5 is " << (s1 == s5) << endl;*/

	/*		中介者模式
	FileSelectionDialog fileDialog;
	int                 i;

	cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
	cin >> i;

	while (i)
	{
		fileDialog.handleEvent(i - 1);
		cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
		cin >> i;
	}*/
	
	


	/*		
	delete instance ;
	delete abstractFactory, shape;
	delete ballFactory, ball;
	delete builder, car;
	delete p1, p2, p3, p4;
	delete player;
	delete api, circle;
	delete widget, decorator;
	delete wanna;
	delete dialogs[0], dialogs[1];
	delete find_room, proxy;
	*/
	

	/*
	instance = NULL;
	abstractFactory = shape = NULL;
	ballFactory = ball = NULL;
	builder = car = NULL;
	p1 = p2 = p3 = p4 = NULL;
	player = NULL;
	api = ciecle = NULL;
	widget = decorator = NULL;
	wanna = NULL;
	dialogs[0] = dialogs[1] = NULL;
	find_room = proxy = NULL;
	*/
	return 0;

}
