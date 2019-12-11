#include "List.h"
#include <cassert>
#include <iostream>
#include <string>

struct Test {
	int val;
	double dval;
};

std::ostream& operator<<(std::ostream& out, const Test& data) {
	out << "Test Objekt mit den Werten:\nval: " << data.val << "\ndval: " << data.dval;
	return out;
}

using List = cns::List<Test>;

void checkMemory() {
	assert(_CrtCheckMemory());
	assert(false == _CrtDumpMemoryLeaks());
}

void List_DefaultConstructorIsEmpty() {
	List empty;
	assert(true == empty.isEmpty());
}

void List_pushback_InsertElementAtListEndAndListIsNotMoreEmpty() {
	List list;
	list.pushback(Test{ 1, 1.2 });
	assert(false == list.isEmpty());
}

void List_pushback_InsertThreeElementsAtListAndReadThemWithIndexOperator() {
	List list;
	list.pushback(Test{ 1, 1.2 });
	list.pushback(Test{ 2, 2.2 });
	list.pushback(Test{ 3, 3.3 });
	assert(1 == list[0].val);
	assert(2 == list[1].val);
	assert(3 == list[2].val);
}

void List_index_outOfBounds() {
	List list;

	try {
		list[0];
		std::cerr << "Index out of bound expected";
	} catch (const std::logic_error & ex) {
		assert(0 == std::strcmp("Index out of bounds", ex.what()));
	}
}

void List_copyConstructor() {
	List list;
	list.pushback(Test{ 1, 1.2 });

	List list2{ list };
	assert(list[0].val == list2[0].val);
	assert(&list[0] != &list2[0]);
}

void List_delegateOperator() {
	List list;
	list.pushback(Test{ 1, 1.2 });

	List list2 = list;
	assert(list[0].val == list2[0].val);
	assert(&list[0] != &list2[0]);
}

void List_remove_Elements() {
	List list;
	list.pushback(Test{ 1, 1.2 });
	list.pushback(Test{ 2, 2.2 });
	list.pushback(Test{ 3, 3.2 });
	list.pushback(Test{ 4, 4.4 });

	list.removeAt(2);
	assert(4 == list[2].val);
	assert(2 == list[1].val);

	list.removeAt(0);
	assert(2 == list[0].val);

	list.removeAt(1);
	assert(1 == list.size());

	list.removeAt(0);
	assert(list.isEmpty());
}

void List_remove_ElementsAtWrongIndex() {
	List list;

	try {
		list.removeAt(0);
		std::cerr << "Index out of bounds expected";
	}
	catch (const std::logic_error ex) {
		assert(0 == std::strcmp("Index out of bounds", ex.what()));
	}

	list.pushback(Test{ 1, 1.2 });

	try {
		list.removeAt(1);
		std::cerr << "Index out of bounds expected";
	}
	catch (const std::logic_error ex) {
		assert(0 == std::strcmp("Index out of bounds", ex.what()));
	}
}

void List_moveConstructor() {
	List list;
	list.pushback(Test{ 1, 1.2 });
	list.pushback(Test{ 2, 2.2 });
	auto n = list.getPtrAt(1);

	List list2{ std::move(list) };
	assert(list.isEmpty());
	assert(n == list2.getPtrAt(1));
	assert(1 == list2[0].val);
	assert(2 == list2[1].val);
}

void List_streamOperator() {
	List list;
	list.pushback(Test{ 1, 1.2 });
	list.pushback(Test{ 2, 2.2 });

	std::cout << list << std::endl;
}

int main() {
	using testFnc = void(*)();
	testFnc tests[]{
		List_DefaultConstructorIsEmpty,
		List_pushback_InsertElementAtListEndAndListIsNotMoreEmpty,
		List_pushback_InsertThreeElementsAtListAndReadThemWithIndexOperator,
		List_index_outOfBounds,
		List_copyConstructor,
		List_delegateOperator,
		List_remove_Elements,
		List_remove_ElementsAtWrongIndex,
		List_moveConstructor,
		List_streamOperator,
	};

	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
		tests[i]();
		checkMemory();
	}
}