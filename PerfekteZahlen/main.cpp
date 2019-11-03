#include <iostream>
#include <ctime>

using namespace std;

int main() {
	bool timeCheck{ true };
	int number{ 5 };
	time_t timeBefore = time(nullptr);

	while (timeCheck) {
		int sum{ 0 };
		int dividorCount{ 0 };
		int Dividors[1000];

		++number;
		for (auto i{ number - 1 }; i > 0; --i) {
			if (number % i == 0) {
				Dividors[dividorCount] = i;
				sum += i;
				++dividorCount;
			}
		}
		timeCheck = (time(nullptr) - timeBefore) < 120;

		if (sum == number) {
			cout << "Perfekte Zahl gefunden: " << number << " (";
			for (auto i{ dividorCount - 1}; i >= 0; --i) {
				cout << Dividors[i] << (i > 0 ? " + " : "");
			}
			cout << ")" << endl;
			timeBefore = time(nullptr);
		}
	};

	std::cout << "Letzte Zahl: " << number << endl;
	return 0;
}