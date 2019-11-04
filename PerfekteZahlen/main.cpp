#include <iostream>
#include <ctime>

using namespace std;

int main() {
	auto searching{ true };
	auto number{ 5 };
	auto startTime = time(nullptr);

	while (searching) {
		auto sum{ 0 };
		auto dividersCount{ 0 };
		int dividers[100]{ 0 };

		++number;
		for (auto i{ number - 1 }; i > 0; --i) {
			if (number % i == 0) {
				dividers[dividersCount] = i;
				sum += i;
				++dividersCount;
			}
		}

		if (sum == number) {
			cout << "Perfekte Zahl gefunden: " << number << " (";
			for (auto i{ dividersCount - 1}; i >= 0; --i) {
				cout << dividers[i] << (i > 0 ? " + " : "");
			}
			cout << ")" << endl;
			startTime = time(nullptr);
		}

		searching = (time(nullptr) - startTime) < 120;
	};

	std::cout << "Letzte Zahl: " << number << endl;
	return 0;
}