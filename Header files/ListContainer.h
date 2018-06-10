#ifndef DLIST_H
#define DLIST_H

#include <list>
#include "ContainerElement.h"
#include "Object.h"

using T = Object*;
class ListContainer: public ContainerElement, public std::list<T> {
private:
	friend class ListIterator;

	void split(ListContainer& l1, ListContainer& l2);
	void merge(std::list<T> & l1, std::list<T> & l2);

	void clean();

public:
	bool member(T const& x);
	bool hasMemberPredicate(Condition c);
	void filter(Condition c);
	std::ostream& print(std::ostream& os);
	void push(const T& el);
	T top();
	bool empty();
	size_t size();
	void pop();
	void insert(T const& x, std::list<T>::iterator iter);
	void erase(std::list<T>::iterator iter);
	T get(std::list<T>::iterator iter);
	int getType()const;

	abstractIterator* my_begin();
	abstractIterator* my_end();

	void sort();

	~ListContainer();

	class ListIterator : public abstractIterator {
	private:
		ListContainer::iterator iter;
		ListContainer* sc;
	public:
		friend class ListContainer;
		ListIterator(ListContainer& sc);
		T& operator*();
		abstractIterator* operator++();
		bool hasNext();
		operator bool();
	};
};

#endif // !LISTCONTAINER_H