#ifndef QUEUECONTAINER_H
#define QUEUECONTAINER_H

#include <queue>
#include <stack>
#include <list>
#include "ContainerElement.h"

using T = Object*;
class QueueContainer : public ContainerElement, private std::list<T>{
private:
	void split(QueueContainer& l1, QueueContainer& l2);
	void merge(std::list<T> & l1, std::list<T> & l2);

	void clean();
public:
	friend class QueueIterator;

	bool member(T const& x);
	bool hasMemberPredicate(Condition c);
	void filter(Condition c);

	std::ostream& print(std::ostream& os);
	void push(const T& el);
	bool empty();
	T front();
	size_t size();
	void insert(T const& x, std::list<T>::iterator iter);
	void erase(std::list<T>::iterator iter);
	T get(std::list<T>::iterator iter);
	void pop();
	T top();
	int getType()const;

	abstractIterator* my_begin();
	abstractIterator* my_end();

	void sort();
	~QueueContainer();

	class QueueIterator : public abstractIterator {
	private:
		QueueContainer::iterator iter;
		QueueContainer* sc;
	public:
		friend class QueueContainer;
		QueueIterator(QueueContainer& sc);
		T& operator*();
		abstractIterator* operator++();
		bool hasNext();
		operator bool();
	};
};


#endif // !QUEUECONTAINER_H
