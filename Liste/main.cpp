#include "List.h"
#include <cassert>
#include <iostream>
#include <string>

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
	list.pushback(1.2f);
	assert(false == list.isEmpty());
}

void List_pushback_InsertThreeElementsAtListAndReadThemWithIndexOperator() {
	List list;
	list.pushback(1.2f);
	list.pushback(2.2f);
	list.pushback(3.2f);
	assert(1.2f == list[0]);
	assert(2.2f == list[1]);
	assert(3.2f == list[2]);
}

void List_index_outOfBounds() {
	List list;

	try {
		list[0];
		std::cerr << "Index out of bound expected";
	} catch (const std::logic_error & ex) {
		assert(std::strcmp("Index out of bounds", ex.what()) == 0);
	}
}

void List_copyConstructor() {
	List list;
	list.pushback(1.2);

	List list2{ list };
	assert(list[0] == list2[0]);
	assert(&list[0] != &list2[0]);
}

void List_delegateOperator() {
	List list;
	list.pushback(1.2);

	List list2 = list;
	assert(list[0] == list2[0]);
	assert(&list[0] != &list2[0]);
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
	};

	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
		tests[i]();
		checkMemory();
	}
}