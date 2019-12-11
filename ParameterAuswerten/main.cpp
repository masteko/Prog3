#include <iostream>
#include <cstring>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

void printArray(int argc, char* argv[]) {
	cout << "---------------------------" << endl;
	for (auto i{ 0 }; i < argc; ++i) {
		cout << argv[i] << endl;
	}
}

int getArrayLength(char* envp[]) {
	auto pt{ envp };
	auto envpLen{ 0 };

	while (nullptr != *pt++) {
		++envpLen;
	}

	return envpLen;
}

class JaggedArray {
public: 
	JaggedArray() : arr(nullptr), len(0) {};
	JaggedArray(const JaggedArray& src) : JaggedArray() {
		clone(src.len, src.arr);
	};
	void clone(int argc, char* argv[]) {
		len = argc;
		arr = new char* [argc];
		for (auto i{ 0 }; i < argc; ++i) {
			auto strBuffer = new char[strlen(argv[i]) + 1];
			strcpy(strBuffer, argv[i]);
			arr[i] = strBuffer;
		}
	};
	void sort() {
		qsort(arr, len, sizeof(char *), cmpFnc);
	};
	void print() {
		printArray(len, arr);
	};
	const char* const* getArray() const {
		return arr;
	};
	int getLength() {
		return len;
	};
	~JaggedArray() {
		deleteData();
	};
	JaggedArray& operator=(const JaggedArray& src) {
		if (this != &src) {
			deleteData();
			clone(src.len, src.arr);
		}
		return *this;
	};

private:
	char** arr;
	int len;
	static int cmpFnc(const void* p1, const void* p2) {
		return strcmp(*(char**)p1, *(char**)p2);
	};
	void deleteData() {
		for (auto i{ 0 }; i < len; ++i) {
			delete[] arr[i];
		}

		delete[] arr;
		arr = nullptr;
		len = 0;
	};
};

int main(int argc, char* argv[], char* envp[]) {
	{
		JaggedArray argClone;
		JaggedArray envClone;

		argClone.clone(argc, argv);

		argClone.print();
		argClone.sort();
		argClone.print();

		envClone.clone(getArrayLength(envp), envp);

		envClone.print();
		envClone.sort();
		envClone.print();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}