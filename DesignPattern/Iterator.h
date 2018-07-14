#pragma once
/*

������ģʽ��Iterator Pattern���� Java �� .Net ��̻����зǳ����õ����ģʽ��
����ģʽ����˳����ʼ��϶����Ԫ�أ�����Ҫ֪�����϶���ĵײ��ʾ��
������ģʽ������Ϊ��ģʽ��

��ͼ���ṩһ�ַ���˳�����һ���ۺ϶����и���Ԫ��, �������뱩¶�ö�����ڲ���ʾ��
��Ҫ�������ͬ�ķ�ʽ�������������϶���
��ʱʹ�ã�����һ���ۺ϶���
��ν��������Ԫ��֮�����ߵ����ν����������������Ǿۺ϶���
�ؼ����룺����ӿڣ�hasNext, next��
Ӧ��ʵ����JAVA �е� iterator��
�ŵ㣺 1����֧���Բ�ͬ�ķ�ʽ����һ���ۺ϶��� 2�����������˾ۺ��ࡣ 3����ͬһ���ۺ��Ͽ����ж�������� 4���ڵ�����ģʽ�У������µľۺ���͵������඼�ܷ��㣬�����޸�ԭ�д��롣
ȱ�㣺���ڵ�����ģʽ���洢���ݺͱ������ݵ�ְ����룬�����µľۺ�����Ҫ��Ӧ�����µĵ������࣬��ĸ����ɶ����ӣ�����һ���̶���������ϵͳ�ĸ����ԡ�
ʹ�ó����� 1������һ���ۺ϶�������ݶ����뱩¶�����ڲ���ʾ�� 2����ҪΪ�ۺ϶����ṩ���ֱ�����ʽ�� 3��Ϊ������ͬ�ľۺϽṹ�ṩһ��ͳһ�Ľӿڡ�
ע�����������ģʽ���Ƿ����˼��϶���ı�����Ϊ�������һ���������������������ȿ�����������¶���ϵ��ڲ��ṹ���ֿ����ⲿ����͸���ط��ʼ����ڲ������ݡ�

*/

class Stack {
	int items[10];
	int sp;
public:
	friend class StackIter;
	Stack() { sp = -1; }
	void push(int in) { items[++sp] = in; }
	int  pop() { return items[sp--]; }
	bool isEmpty() { return (sp == -1); }
	StackIter* createIterator() const { return new StackIter(this); }     // 2. Add a createIterator() member
};

class StackIter {                          // 1. Design an "iterator" class
	const Stack* stk;
	int index;
public:
	StackIter(const Stack* s) { stk = s; }
	void first() { index = 0; }
	void next() { index++; }
	bool isDone() { return index == stk->sp + 1; }
	int  currentItem() { return stk->items[index]; }
};


bool operator==(const Stack& l, const Stack& r) {
	// 3. Clients ask the container object to create an iterator object
	StackIter* itl = l.createIterator();
	StackIter* itr = r.createIterator();
	// 4. Clients use the first(), isDone(), next(), and currentItem() protocol
	for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next())
		if (itl->currentItem() != itr->currentItem()) break;
	bool ans = itl->isDone() && itr->isDone();
	delete itl;   delete itr;
	return ans;
}

//// Purpose.  Iterator using operators instead of methods
////
//// Discussion.  John Lakos suggests the GOF and STL iterator interfaces are:
//// error-prone (possibility of misspelling method names), clumsy, and require
//// too much typing.  This design uses nothing but "intuitive" operators.
//// Notice also that no createIterator() was specified.  The user creates these
//// iterators as local variables, and no clean-up is necessary.
//
//#include <iostream>
//using namespace std;
//
//class Stack {
//	int items[10];
//	int sp;
//public:
//	friend class StackIter;
//	Stack() { sp = -1; }
//	void push(int in) { items[++sp] = in; }
//	int  pop() { return items[sp--]; }
//	bool isEmpty() { return (sp == -1); }
//};
//
//class StackIter {
//	const Stack& stk;
//	int index;
//public:
//	StackIter(const Stack& s) : stk(s) { index = 0; }
//	void operator++() { index++; }
//	bool operator()() { return index != stk.sp + 1; }
//	int  operator*() { return stk.items[index]; }
//};
//
//bool operator==(const Stack& l, const Stack& r) {
//	StackIter itl(l), itr(r);
//	for (; itl(); ++itl, ++itr)
//		if (*itl != *itr) break;
//	return !itl() && !itr();
//}
//
//void main(void) {
//	Stack  s1;   int  i;
//	for (i = 1; i < 5; i++) s1.push(i);
//	Stack  s2(s1), s3(s1), s4(s1), s5(s1);
//	s3.pop();       s5.pop();
//	s4.push(2);   s5.push(9);
//	cout << "1 == 2 is " << (s1 == s2) << endl;
//	cout << "1 == 3 is " << (s1 == s3) << endl;
//	cout << "1 == 4 is " << (s1 == s4) << endl;
//	cout << "1 == 5 is " << (s1 == s5) << endl;
//}
//
//// 1 == 2 is 1
//// 1 == 3 is 0
//// 1 == 4 is 0
//// 1 == 5 is 0
//
//
//
//
//// Purpose.  Iterator using the Java interface
////
//// Discussion.  Java's standard collection classes have a much leaner inter-
//// face.  Their next() methods combine the next() and currentItem() methods.
//
//#include <iostream>
//using namespace std;
//
//class Stack {
//	int items[10];
//	int sp;
//public:
//	friend class StackIter;
//	Stack() { sp = -1; }
//	void push(int in) { items[++sp] = in; }
//	int  pop() { return items[sp--]; }
//	bool isEmpty() { return (sp == -1); }
//	StackIter* iterator() const;
//};
//
//class StackIter {
//	const Stack* stk;
//	int index;
//public:
//	StackIter(const Stack* s) { stk = s;  index = 0; }
//	int  next() { return stk->items[index++]; }
//	bool hasNext() { return index != stk->sp + 1; }
//};
//
//StackIter* Stack::iterator() const { return new StackIter(this); }
//
//bool operator==(const Stack& l, const Stack& r) {
//	StackIter* itl = l.iterator();
//	StackIter* itr = r.iterator();
//	while (itl->hasNext())
//		if (itl->next() != itr->next()) {
//			delete itl;   delete itr;
//			return false;
//		}
//	bool ans = (!itl->hasNext()) && (!itr->hasNext());
//	delete itl;   delete itr;
//	return ans;
//}
//
//void main(void) {
//	Stack  s1;   int  i;
//	for (i = 1; i < 5; i++) s1.push(i);
//	Stack  s2(s1), s3(s1), s4(s1), s5(s1);
//	s3.pop();       s5.pop();
//	s4.push(2);   s5.push(9);
//	cout << "1 == 2 is " << (s1 == s2) << endl;
//	cout << "1 == 3 is " << (s1 == s3) << endl;
//	cout << "1 == 4 is " << (s1 == s4) << endl;
//	cout << "1 == 5 is " << (s1 == s5) << endl;
//}
//
//// 1 == 2 is 1
//// 1 == 3 is 0
//// 1 == 4 is 0
//// 1 == 5 is 0
//
//
//
//
//// Purpose.  Simple implementation of an Iterator (uses parallel dynamic array)
////
//// Discussion.  Instead of having to write an involved stack-like solution to
//// handle step-wise recursive descent, use a little extra memory to maintain a
//// sequential representation of the original hierarchical data.  The replicated
//// data are not Node objects, they are lightweight pointers.  The array is
//// initialized using a recursive method similar to traverse(Node*).
//
//#include <iostream>
//#include <ctime>
//using namespace std;
//
//class BST {
//	friend class Iterator;
//	struct Node {
//		Node(int);
//		int value;
//		Node* left;
//		Node* rite;
//	};
//	Node* root;
//	int   size;
//	void add(Node**, int);
//	void traverse(Node*);
//public:
//	BST() { root = 0;  size = 0; }
//	void add(int);
//	void traverse();
//	Iterator* createIterator() const;
//};
//
//class Iterator {
//	const BST* tree;
//	BST::Node** array;
//	int index;
//	void populateArray(BST::Node* current) {
//		if (current->left) populateArray(current->left);
//		array[index++] = current;
//		if (current->rite) populateArray(current->rite);
//	}
//public:
//	Iterator(const BST* s) {
//		tree = s;
//		array = 0;  index = 0;
//	}
//	~Iterator() { delete[] array; }
//	void first() {
//		delete[] array;
//		array = new BST::Node*[tree->size];
//		index = 0;
//		populateArray(tree->root);
//		index = 0;
//	}
//	void next() { index++; }
//	bool isDone() { return index == tree->size; }
//	BST::Node* currentItem() { return array[index]; }
//};
//
//void main(void) {
//	srand(time(0));
//	BST  tree;
//	for (int i = 0; i < 20; i++) tree.add(rand() % 20 + 1);
//	cout << "traverse: ";
//	tree.traverse();
//	cout << "\niterator: ";
//	Iterator* it = tree.createIterator();
//	for (it->first(); !it->isDone(); it->next())
//		cout << it->currentItem()->value << ' ';
//	cout << "\niterator: ";
//	for (it->first(); !it->isDone(); it->next())
//		cout << it->currentItem()->value << ' ';
//	cout << '\n';
//}
//
//// traverse: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
//// iterator: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
//// iterator: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
//
//
//BST::Node::Node(int v) { value = v;  left = rite = 0; }
//
//void BST::add(Node** n, int v) {
//	if (!*n) { *n = new Node(v);  size++; }
//	else if (v <= (*n)->value) add(&((*n)->left), v);
//	else                       add(&((*n)->rite), v);
//}
//
//void BST::add(int v) { add(&root, v); }
//void BST::traverse() { traverse(root); }
//
//void BST::traverse(Node* n) {
//	if (n->left) traverse(n->left);
//	cout << n->value << ' ';
//	if (n->rite) traverse(n->rite);
//}
//
//Iterator* BST::createIterator() const { return new Iterator(this); }
//
//
//
//
//// Purpose.  Fairly reusable iterator for step-wise recursive descent
////
//// Discussion.  The Composite/Component/Leaf code is one of the previous
//// Composite demos.  Methods added were: Component::outputValue() and
//// Composite::createIterator().
//
//#include <iostream>
//#include <vector>
//using namespace std;
//
//class Component {
//public:
//	virtual void traverse() = 0;
//	virtual void outputValue() { }
//};
//
//class Leaf : public Component {
//	int value;
//public:
//	Leaf(int val) { value = val; }
//	/*virtual*/ void traverse() { cout << value << ' '; }
//	/*virtual*/ void outputValue() { traverse(); }
//};
//
//class Composite : public Component {
//	vector<Component*> children;
//public:
//	friend class Iterator;
//	void add(Component* ele) { children.push_back(ele); }
//	/*virtual*/ void traverse() {
//		for (int i = 0; i < children.size(); i++)
//			children[i]->traverse();
//	}
//	Iterator* createIterator();
//};
//
//class Memento {
//public:
//	struct MgrIdx {
//		MgrIdx(Composite* m = 0, int i = 0) { mgr = m;  idx = i; }
//		Composite* mgr;
//		int        idx;
//	};
//	void initialize(Composite* root) {
//		vec.resize(0);
//		vec.push_back(MgrIdx(root, 0));
//	}
//	bool isEmpty() { return vec.size() == 0; }
//	void push(MgrIdx ds) { vec.push_back(ds); }
//	MgrIdx top() { return vec.back(); }
//	MgrIdx pop() {
//		MgrIdx ds = vec.back();
//		vec.pop_back();
//		return ds;
//	}
//private:
//	vector<MgrIdx> vec;
//};
//
//// Dependencies on actual class playing the role of "Composite":
////    Composite class name, children attribute name
//class Iterator {
//	Composite* root;
//	Memento    memento;
//	bool       done;
//public:
//	Iterator(Composite* rooot) { root = rooot; }
//	void first() {
//		memento.initialize(root);
//		done = false;
//	}
//	void next() {
//		Memento::MgrIdx ds = memento.pop();
//		ds.idx++;
//		// if (and while) you are at end-of-composite, go up
//		while (ds.idx == ds.mgr->children.size()) {
//			if (memento.isEmpty()) { done = true;  return; }
//			ds = memento.pop();
//			ds.idx++;
//		}
//		memento.push(ds);
//		Composite* compo;
//		if (compo = dynamic_cast<Composite*>(ds.mgr->children[ds.idx]))
//			memento.push(Memento::MgrIdx(compo, 0));
//	}
//	Component* currentItem() {
//		Memento::MgrIdx ds = memento.top();
//		return ds.mgr->children[ds.idx];
//	}
//	bool isDone() { return done; }
//};
//
//Iterator* Composite::createIterator() { return new Iterator(this); }
//
//void main(void) {
//	Composite containers[4];
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 3; j++)
//			containers[i].add(new Leaf(i * 3 + j));
//	for (i = 1; i < 4; i++) containers[0].add(&(containers[i]));
//	cout << "traverse: ";
//	containers[0].traverse();
//
//	Iterator* it = containers[0].createIterator();
//	cout << "\niterator: ";
//	for (it->first(); !it->isDone(); it->next())
//		it->currentItem()->outputValue();
//	cout << '\n';
//	cout << "iterator: ";
//	for (it->first(); !it->isDone(); it->next())
//		it->currentItem()->outputValue();
//	cout << '\n';
//	delete it;
//}
//
//// traverse: 0 1 2 3 4 5 6 7 8 9 10 11
//// iterator: 0 1 2 3 4 5 6 7 8 9 10 11
//// iterator: 0 1 2 3 4 5 6 7 8 9 10 11