#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>
#include <chrono>

std::vector<int> prefix_function(const std::string s) {
	std::vector<int> pi(s.length(), 0);

	for (int i = 1; i < s.length(); i++) {
		int j = pi[i - 1];

		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}

		if (s[i] == s[j]) {
			pi[i] = j + 1;
		}
		else {
			pi[i] = j;
		}
	}
	return pi;
}

std::vector<int> triv_search(std::string haystack, std::string needle)
{
	auto t1 = std::chrono::high_resolution_clock::now();

	int n = haystack.length();
	int m = needle.length();
	std::vector<int> ans;
	int j;
	bool flag = false;
	for (int i = 0; i < n; ++i)
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && (j < n - i))
		{
			j++;
			if (j == m)
			{
				flag = true;
				break;
			}
		}
		if (flag && haystack[i] == needle[0]) ans.push_back(i);
		flag = false;
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	long dt = ((std::chrono::nanoseconds)(t2 - t1)).count();
	std::cout << "Алгоритм выполнялся " << dt << " наносекунд\n";

	return ans;
}

void choose_alphabet(std::string str)
{
	srand(time(NULL));
	std::string haystack, needle;
	int word_length = 0, alp_range_begin = 0, alp_range_end = 0;
	std::cout << "Введите длину слова, в котором нужно искать: ";
	std::cin >> word_length;
	std::cout << "Введите диапазон букв в алфавите: \n";
	for (char ch : str) std::cout << ch << "  ";
	std::cout << "\n";
	for (int i(0); i < str.length(); ++i)
	{
		std::cout << i << " ";
		if (i < 10) std::cout << " ";
	}
	std::cout << "\nНачало диапазона: ";
	std::cin >> alp_range_begin;
	std::cout << "Конец диапазона: ";
	std::cin >> alp_range_end;

	for (int i = 0; i < word_length; ++i)
		haystack.push_back(char(str[alp_range_begin] + rand() % (str[alp_range_begin] - str[alp_range_end])));

	std::cout << "Введите длину слова, которое нужно найти: ";
	std::cin >> word_length;

	int rnd = rand() % haystack.length();
	while(haystack.length() - rnd < word_length) rnd = rand() % haystack.length();
	rnd--;
	for (int i = 0; i < word_length; ++i)
	{	
		needle.push_back(haystack[rnd++]);
	}

	for (char ch : haystack) std::cout << ch;
	std::cout << "\n";
	for (char ch : needle) std::cout << ch;

}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string haystack, needle;
	std::string eng_alphabet;
	std::string rus_alphabet;

	for (char i = 'a'; i <= 'z'; i++)
	{
		eng_alphabet.push_back(i);
	}
	for (char i = 'а'; i <= 'я'; i++)
	{
		rus_alphabet.push_back(i);
	}

	int choice = 0, choice_alp = 0;
	bool check = true;
	while (check = true)
	{
		std::cout << "Выберите:\n1.Ввести слова вручную\n2.Выбрать буквы алфавита и составить из них слова\n3.Слово вида (B1 B2 … Bs)\n4.Выйти\n";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Слово, в котором нужно искать:";
			std::cin >> haystack;
			std::cout << "Слово, которое нужно найти:";
			std::cin >> needle;
			std::cout << "1.Наивный алгоритм\n2.Алгоритм Кнута-Морриса-Пратта: ";
			std::cin >> choice_alp;
			if (choice_alp == 1)
			{
				std::vector<int> vec = triv_search(haystack, needle);
				std::cout << "Ответ: ";
				for (int i : vec)
				{
					std::cout << i << " ";
				}
			}
			else if (choice_alp == 2)
			{
				std::vector<int> vec2 = prefix_function(needle + ' ' + haystack);

				int n = needle.length();

				std::cout << "Ответ: ";
				for (int i = 0; i < haystack.length(); i++) 
				{
					if (vec2[n + 1 + i] == n)
					{
						std::cout << haystack << "[" << i - n + 1 << "..." << i << "] = " << needle << "\n";
					}
				}
			}
			else std::cout << "Такого варианта нет";
			std::cout << "\n";
			break;
		case 2:
			std::cout << "1.Русский\n2.Английский: ";
			std::cin >> choice_alp;
			if (choice_alp == 1)
				choose_alphabet(rus_alphabet);
			else if (choice_alp == 2)
				choose_alphabet(eng_alphabet);
			else std::cout << "Такого варианта нет";
			std::cout << "\n";
			break;
		case 3:
			std::cout << "В разработке";
			break;
		case 4:
			check = false;
			break;
		case 5:
			std::cout << "Такого варианта нет\n";
			break;
		}
	}



	/*std::vector<int> vec = triv_search(haystack, needle);
	for (int i : vec)
	{
		std::cout << i << " ";
	}

	std::vector<int> f = prefix_function(needle + ' ' + haystack);

	int n = needle.length();

	for (int i = 0; i < haystack.length(); i++) {
		if (f[n + 1 + i] == n) 
		{
			std::cout << "haystack[" << i - n + 1 << ".." << i << "] = " << needle << "\n";
		}
	}*/
}
