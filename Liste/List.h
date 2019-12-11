#pragma once
#include <stdexcept>

struct Node {
	float val;
	Node* next;
};

class List
{
public:
	List() : head(nullptr) {};
	List(const List& src) : List() {
		copyList(src.head);
	};
	virtual ~List() {
		if (nullptr != head) {
			deleteEntries(head);
		}
		head = nullptr;
	};
	Node* getHead() {
		return head;
	};
	bool isEmpty() const {
		return nullptr == head;
	};
	void pushback(float val) {
		if (nullptr == head) {
			createHead(val);
			return;
		}
		Node* tail = head;
		if (nullptr != tail) {
			while (nullptr != tail->next) {
				tail = tail->next;
			}
		}
		tail->next = new Node{ val, nullptr };
	};
	float& operator[](size_t index) {
		if (index >= getSize()) {
			throw std::logic_error("Index out of bounds");
		}
		else {
			return getValAt(index);
		}
	};
	List& operator=(const List& src) {
		if (this != &src) {
			deleteEntries(head);
			copyList(src.head);
		}
		return *this;
	};
private:
	void createHead(float val) {
		head = new Node{ val, nullptr };
	};
	void copyList(Node* src) {
		Node* srcNode = src;
		if (nullptr != srcNode) {
			head = new Node{ srcNode->val, nullptr };

			while (nullptr != srcNode->next) {
				srcNode = srcNode->next;
				pushback(srcNode->val);
			}
		}
	};
	size_t getSize() {
		size_t size{ 0 };
		Node* node = head;
		if (nullptr != head) {
			size++;
			while (nullptr != node->next) {
				size++;
				node = node->next;
			}
		}
		return size;
	};
	float& getValAt(size_t index) {
		size_t idx{ 0 };
		Node* node = head;
		float val;
		while (index != idx) {
			node = node->next;
			idx++;
		}
		return node->val;
	};
	void deleteEntries(Node* node) {
		if (nullptr != node->next) {
			deleteEntries(node->next);
		}
		delete node;
	};
	Node* head;
};

