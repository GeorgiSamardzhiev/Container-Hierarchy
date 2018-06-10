#ifndef HETEROGENEOUSLIST_H
#define HETEROGENEOUSLIST_H

#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>     // std::next
#include "Object.h"
#include "ContainerElement.h"
#include "StackContainer.h"
#include "QueueContainer.h"
#include "ListContainer.h"

using T = Object*;
class HeterogeneousContainer: public std::list<ContainerElement*> {
public:
	using Condition = bool(*)(T const&);
	
	class OneByOneIterator {
	private:
		friend HeterogeneousContainer;
		ContainerElement* litleList;
		std::list<ContainerElement*>* container;
		//std::list<T>::iterator iterator; -->iterate without pop(will work only of use stl functions below)
		abstractIterator* iterator; //iterate with pop
		std::list<ContainerElement*>::iterator it;
	public:
		OneByOneIterator(HeterogeneousContainer& hc);
		OneByOneIterator& operator++();
		OneByOneIterator operator++(int);
		T operator*();
		operator bool() const;
	};

	class ParallelIterator {
	private:
		ContainerElement* litleList;
		std::list<ContainerElement*>* container;
		//std::list<T>::iterator iterator; -->iterate without pop(will work only of use stl functions below)
		abstractIterator* iterator; //iterate with pop
		std::list<ContainerElement*>::iterator it;
		unsigned int depth;

		size_t maxSize(std::list<ContainerElement*>* l)const;
	public:
		ParallelIterator(HeterogeneousContainer& hc);
		ParallelIterator& operator++();
		ParallelIterator operator++(int);
		T operator*();
		operator bool() const;

	};

	void readFromFile(std::string nameOfFile);
	bool member(T const& x);
	void loadBallancedPush(const T& x);
	OneByOneIterator find(const T& x);
	ParallelIterator findParallel(const T& x);
	bool hasMemberPredicate(Condition c);
	void filter(Condition c);
	void sort();
	void print();
	void safeToFile(std::string path);
	~HeterogeneousContainer();
};
#endif // !HETEROGENEOUSLIST_H
