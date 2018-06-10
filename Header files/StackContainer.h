#ifndef STACKCONTAINER_H
#define STACKCONTAINER_H

#include <stack>
#include <list>
#include "ContainerElement.h"
#include "Object.h"

using T = Object*;
class StackContainer : public ContainerElement, private std::list<T> {
private:
	friend class StackIterator;

	void split(StackContainer& l1, StackContainer& l2);
	void merge(StackContainer & l1, StackContainer & l2);

	void clean();
public:
	bool member(T const& x);
	bool hasMemberPredicate(Condition c);
	void filter(Condition c);
	std::ostream& print(std::ostream& os);
	void push(const T& el);
	size_t size();
	bool empty();
	void insert(T const& x, std::list<T>::iterator iter);
	void erase(std::list<T>::iterator iter);
	T get(std::list<T>::iterator iter);
	T top();
	void pop();
	int getType()const;

	abstractIterator* my_begin();
	abstractIterator* my_end();

	void sort();
	~StackContainer();


	class StackIterator : public abstractIterator {
	private:
		StackContainer::reverse_iterator iter;
		StackContainer* sc;
	public:
		friend class StackContainer;
		StackIterator(StackContainer& sc);
		T& operator*();
		abstractIterator* operator++();
		bool hasNext();
		operator bool();
	};
};


#endif // !STACKCONTAINER_H
