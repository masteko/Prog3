#pragma once
#include <stdexcept>
#include <iostream>

namespace cns {

	template<typename T>
	class List {
	public:
		List() : head(nullptr) {}
		List(const List& src) : List() {
			copyList(src.head);
		}
		List(List&& src) : List() {
			*this = std::move(src);
		}
		~List() {
			emptyList();
		}
		List& operator=(const List& src) {
			if (this != &src) {
				emptyList();
				copyList(src.head);
			}
			return *this;
		}
		List& operator=(List&& src) {
			if (this != &src) {
				emptyList();
				head = src.head;
				src.head = nullptr;
			}
			return *this;
		};
		T& operator[](size_t index) const {
			return getNodeAtIndex(index)->value;
		}
		void removeAt(size_t index) {
			Node* oldNode;

			if (0 == index) {
				oldNode = getNodeAtIndex(0);
				head = oldNode->next;
			}
			else {
				Node* prev = getNodeAtIndex(index - 1);
				oldNode = prev->next;

				if (nullptr == oldNode) {
					throw std::logic_error("Index out of bounds");
				}

				prev->next = oldNode->next;
			}

			delete oldNode;
		}
		void pushback(T val) {
			if (nullptr == head) {
				head = new Node{ val, nullptr };
				return;
			}

			Node* last = getLast();
			last->next = new Node{ val, nullptr };
		}
		size_t size() const {
			size_t len{ 0 };

			if (isEmpty()) return len;

			Node* current = head;

			while (nullptr != current) {
				current = current->next;
				++len;
			}

			return len;
		}
		bool isEmpty() const {
			return nullptr == head;
		}
		const void* const getPtrAt(size_t index) const {
			return getNodeAtIndex(index);
		}
	private:
		struct Node {
			T value;
			Node* next;
		};
		Node* head;
		Node* getNodeAtIndex(size_t index) const {
			Node* current = head;

			while (nullptr != current && index > 0) {
				current = current->next;
				--index;
			}

			if (0 == index && !isEmpty()) {
				return current;
			}

			throw std::logic_error("Index out of bounds");
		}
		void copyList(Node* src) {
			if (nullptr == src) {
				return;
			}

			head = new Node{ src->value, nullptr };
			src = src->next;
			Node* current = head;

			while (nullptr != src) {
				current = new Node{ src->value, nullptr };
				src = src->next;
			}
		}
		void emptyList() {
			Node* current = head;

			while (nullptr != current) {
				Node* next = current->next;
				delete current;
				current = next;
			}

			head = nullptr;
		}
		Node* getLast() {
			Node* current = head;

			while (nullptr != current->next) {
				current = current->next;
			}

			return current;
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const List<T>& data) {
		auto size = data.size();
	
		out << "Liste mit " << size << " items: \n\n";

		for (size_t i = 0; i < size; ++i) {
			out << data[i] << (i < size -1 ? "\n-----------------\n" : "");
		}

		return out;
	}
}
