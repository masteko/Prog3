#include <iostream>
#include <ctime>

using namespace std;

int SumDividers(int dividersCount, const int dividers[])
{
	auto sum{ 0 };
	for (auto i{ 0 }; i < dividersCount; ++i) {
		sum += dividers[i];
	}
	return sum;
}

int CalcDividers(int number, int dividers[]) {
	auto dividersCount{ 0 };
	for (auto i{ number - 1 }; i > 0; --i) {
		if (0 == number % i) {
			dividers[dividersCount] = i;
			++dividersCount;
		}
	}
	return dividersCount;
}

void PrintPerfectNumber(int dividersCount, int number, int dividers[]) {
	cout << "Perfekte Zahl gefunden: " << number << " (";
	for (auto i{ dividersCount - 1 }; i >= 0; --i) {
		cout << dividers[i] << (i > 0 ? " + " : "");
	}
	cout << ")" << endl;
}

bool IsPerfectNumber(int sum, int number) {
	return sum == number;
}

bool IsTimeLimitExceeded(time_t startTime, int MaxCalcTime) {
	return (time(nullptr) - startTime) < MaxCalcTime;
}

void PrintLastNumber(int number) {
	std::cout << "Letzte Zahl: " << number << endl;
}

int main() {
	auto number{ 5 };
	auto startTime = time(nullptr);
	const int MaxCalcTime{ 120 };

	while (IsTimeLimitExceeded(startTime, MaxCalcTime)) {
		const int MaxDividers{ 1000 };
		int dividers[MaxDividers];
		++number;

		auto dividersCount{ CalcDividers(number, dividers)};
		auto sum{ SumDividers(dividersCount, dividers) };

		if (IsPerfectNumber(sum, number)) {
			PrintPerfectNumber(dividersCount, number, dividers);
			startTime = time(nullptr);
		}
	};

	PrintLastNumber(number);
	return 0;
}