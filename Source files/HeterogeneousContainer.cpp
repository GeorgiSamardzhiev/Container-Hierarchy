#include "HeterogeneousContainer.h"

void HeterogeneousContainer::readFromFile(std::string nameOfFile) {
	std::ifstream file(nameOfFile, std::ios::in);
	std::string line = "";
	unsigned int size;
	file>>size;
	for (size_t i = 0; file && i<size; i++) {
		std::getline(file, line);
		std::istringstream iss(line);
		char c;
		iss>>c;
		ContainerElement* el;
		if (c == 's') {
			el = new StackContainer;
		} else if (c == 'q') {
			el = new QueueContainer;
		} else if (c == 'l') {
			el = new ListContainer;
		}
		el->readLine(iss);
		push_back(el);
	}

	file.close();
}

bool HeterogeneousContainer::member(T const & x) {
	for (iterator iter = begin(); iter != end(); ++iter) {
		if ((*iter)->member(x)) {
			return true;
		}
	}
	return false;
}

void HeterogeneousContainer::loadBallancedPush(const T & x) {
	ContainerElement* ce = (*begin());
	size_t min = ce->size();
	bool pushed = false;
	for (HeterogeneousContainer::iterator container = begin(); container != end(); ++container) {
		size_t size = (*container)->size();
		if (size <= min && (empty()||(*container)->top()->getControlNumber() == x->getControlNumber())) {
			min = size;
			ce = (*container);
			pushed = true;
		}
	}
	if (pushed) {
		ce->push(x);
	} else {
		ContainerElement* lc = new ListContainer;
		lc->push(x);
		push_back(lc);
	}
}

HeterogeneousContainer::OneByOneIterator HeterogeneousContainer::find(const T & x) {
	OneByOneIterator iter(*this);
	while (iter) {
		if ((*iter)->getControlNumber() == x->getControlNumber() && (*iter)->compare(x)==0) {
			return iter;
		}
		++iter;
	}
	return iter;
}

HeterogeneousContainer::ParallelIterator HeterogeneousContainer::findParallel(const T & x) {
	ParallelIterator iter(*this);
	while (iter) {
		if ((*iter)->getControlNumber() == x->getControlNumber() && (*iter)->compare(x) == 0) {
			return iter;
		}
		++iter;
	}
	return iter;
}

bool HeterogeneousContainer::hasMemberPredicate(Condition c) {
	for (HeterogeneousContainer::iterator container = begin(); container != end(); ++container) {
		if ((*container)->hasMemberPredicate(c)) {
			return true;
		}
	}
	return false;
}

void HeterogeneousContainer::filter(Condition c) {
	for (HeterogeneousContainer::iterator container = begin(); container != end(); ++container) {
		(*container)->filter(c);
	}
}

void HeterogeneousContainer::sort() {
	for (HeterogeneousContainer::iterator container = begin(); container != end(); ++container) {
		(*container)->sort();
	}
}

void HeterogeneousContainer::print() {
	for (ContainerElement* container: *this) {
		container->print();
	}
}

void HeterogeneousContainer::safeToFile(std::string path) {
	std::ofstream file(path, std::ios::out);
	if (file) {
		file<<size();
		for (HeterogeneousContainer::iterator container = begin(); container != end(); ++container) {
			(*container)->print(file);
		}
	}

}

HeterogeneousContainer::~HeterogeneousContainer() {
	for (HeterogeneousContainer::iterator iter = begin(); iter != end(); ++iter) {
		(*iter)->~ContainerElement();
		delete (*iter);
	}
}

HeterogeneousContainer::OneByOneIterator::OneByOneIterator(HeterogeneousContainer & hc) {
	it = hc.begin();
	litleList = (*it);
	container = &hc;
	if (hc.size()>0) {
		iterator = (*it)->my_begin();
	}
}

HeterogeneousContainer::OneByOneIterator & HeterogeneousContainer::OneByOneIterator::operator++() {
	if (iterator->hasNext()) {
		iterator->operator++();
	} else {
		++it;
		if (*this) {
			litleList = (*it);
			delete iterator;
			iterator = (*it)->my_begin();
		}
	}
	return *this;
}

HeterogeneousContainer::OneByOneIterator HeterogeneousContainer::OneByOneIterator::operator++(int) {
	OneByOneIterator temp = ++(*this);
	return temp;
}

T HeterogeneousContainer::OneByOneIterator::operator*() {
	return **iterator;
}

HeterogeneousContainer::OneByOneIterator::operator bool() const {
	return it != container->end();
}

size_t HeterogeneousContainer::ParallelIterator::maxSize(std::list<ContainerElement*>* l) const {
	size_t max = 0;
	for (HeterogeneousContainer::iterator i = l->begin(); i !=l->end(); ++i) {
		if ((*i)->size()>max) {
			max = (*i)->size();
		}
	}
	return max;
}

HeterogeneousContainer::ParallelIterator::ParallelIterator(HeterogeneousContainer & hc) : depth(0) {
	it = hc.begin();
	litleList = (*it);
	container = &hc;
	if (hc.size()>0) {
		iterator = (*it)->my_begin();
	}
}

HeterogeneousContainer::ParallelIterator & HeterogeneousContainer::ParallelIterator::operator++() {
	bool isList = true;
	if (*this) {
		++it;
		if (it == container->end()) {
			it = container->begin();
			isList = ((*it)->getType() == 2);
			delete iterator;
			iterator = (*it)->my_begin();
			litleList = (*it);
			if (isList) {
				depth++;
				for (unsigned int i = 0; i<depth; i++) {
					iterator->operator++();
					if (!(iterator->operator bool())) {
						return ++(*this);
					}
				}
			}
		} else {
			isList = ((*it)->getType() == 2);
			litleList = (*it);
			delete iterator;
			iterator = (*it)->my_begin();
			if (!iterator->operator bool()) {
				return ++(*this);
			} else if (depth >0) {
				iterator->operator++();
				if (!iterator->operator bool()) {
					return ++(*this);
				}
			}
			if (isList) {
				for (unsigned int i = 0; i<depth; i++) {
					iterator->operator++();
					if (!iterator->operator bool()) {
						return ++(*this);
					}
				}
			}
		}
	}
	return *this;
}

HeterogeneousContainer::ParallelIterator HeterogeneousContainer::ParallelIterator::operator++(int) {
	ParallelIterator temp = ++(*this);
	return temp;
}

T HeterogeneousContainer::ParallelIterator::operator*() {
	return **iterator;
}

HeterogeneousContainer::ParallelIterator::operator bool() const {
	return depth <= maxSize(container);
}
