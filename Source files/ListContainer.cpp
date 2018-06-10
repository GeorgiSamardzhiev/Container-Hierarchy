#include "ListContainer.h"

void ListContainer::split(ListContainer& l1, ListContainer& l2) {
	ListContainer* addNow = &l1, *addLater = &l2;
	for (std::list<T>::iterator it = begin(); it != end(); ++it) {
		addNow->push(*it);
		std::swap(addNow, addLater);
	}
}

void ListContainer::merge(std::list<T>& l1, std::list<T>& l2) {
	iterator it1 = l1.begin(), it2 = l2.begin();
	while (it1 != l1.end() && it2 != l2.end()) {
		if ((*it1)->compare(*it2) < 0) {
			push(*it1);
			++it1;
		} else {
			push(*it2);
			++it2;
		}
	}
	while (it1 != l1.end()) {
		push(*it1);
		++it1;
	}
	while (it2 != l2.end()) {
		push(*it2);
		++it2;
	}
}

void ListContainer::clean() {
	for (std::list<Object*>::iterator iter = begin(); iter != end(); ++iter) {
		delete (*iter);
	}
	clear();
}

bool ListContainer::member(T const & x) {
	for (iterator it = begin(); it!=end(); ++it) {
		if ((*it)->getControlNumber() == x->getControlNumber() && x->compare(*it) == 0) {
			return true;
		}
	}
	return false;
}

bool ListContainer::hasMemberPredicate(Condition c) {
	for (iterator it = begin(); it!=end(); ++it) {
		if (c(*it)) {
			return true;
		}
	}
	return false;
}

void ListContainer::filter(Condition c) {
	for (iterator it = begin(); it!=end(); ++it) {
		if (!c(*it)) {
			std::list<T>::erase(it);
			it = begin();
			if (empty()) {
				return;
			}
		}
	}
}

std::ostream & ListContainer::print(std::ostream & os) {
	if (empty()) {
		os<<"l"<<' ';
	} else {
		os<<"l"<<' '<<top()->getControlNumber();
		for (iterator it = begin(); it!=end(); ++it) {
			(*it)->writeLine(os);
		}
	}
	return os<<std::endl;
}

void ListContainer::push(const T & el) {
	Object* newObject = ObjectFactory::createObject((el)->getControlNumber());
	newObject->setValue(el);
	std::list<T>::push_back(newObject);
}

T ListContainer::top() {
	return front();
}

bool ListContainer::empty() {
	return std::list<Object*>::empty();
}

size_t ListContainer::size() {
	return std::list<T>::size();
}

void ListContainer::pop() {
	delete front();
	std::list<T>::pop_front();
}

void ListContainer::insert(T const & x, std::list<T>::iterator iter) {
	Object* newObject = ObjectFactory::createObject((x)->getControlNumber());
	newObject->setValue(x);
	std::list<T>::insert(iter, newObject);
}

void ListContainer::erase(std::list<T>::iterator iter) {
	delete *iter;
	std::list<T>::erase(iter);
}

T ListContainer::get(std::list<T>::iterator iter) {
	return *iter;
}

int ListContainer::getType() const {
	return 2;
}

abstractIterator * ListContainer::my_begin() {
	return new ListIterator(*this);
}

abstractIterator * ListContainer::my_end() {
	ListIterator* li = new ListIterator(*this);
	li->iter = end();
	return li;
}

void ListContainer::sort() {
	if (size() == 0 || size() == 1) {
		return;
	}
	ListContainer l1, l2;
	split(l1, l2);
	clean();
	l1.sort();
	l2.sort();

	merge(l1, l2);
}

ListContainer::~ListContainer() {
	clean();
}

ListContainer::ListIterator::ListIterator(ListContainer & sc) {
	iter = sc.begin();
	this->sc = &sc;
}

T & ListContainer::ListIterator::operator*() {
	return *iter;
}

abstractIterator * ListContainer::ListIterator::operator++() {
	iter++;
	return (this);
}

bool ListContainer::ListIterator::hasNext() {
	return std::next(iter) != sc->end();
}

ListContainer::ListIterator::operator bool() {
	return iter != sc->end();
}