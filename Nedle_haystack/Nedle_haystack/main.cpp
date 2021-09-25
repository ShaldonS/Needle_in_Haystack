#include <iostream>
#include <vector>
#include <windows.h>

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
	return ans;
}

void choose_alphabet(std::string str)
{

}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string haystack, needle;
	std::string eng_alphabet;
	std::string rus_alphabet;

	for (char i = 'A'; i <= 'Z'; i++)
	{
		eng_alphabet.push_back(i);
		eng_alphabet.push_back(char(i+32));
	}
	for (char i = 'А'; i <= 'Я'; i++)
	{
		rus_alphabet.push_back(i);
		rus_alphabet.push_back(char(i + 32));
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
			break;
		case 3:
			std::cout << "В разработке";
			break;
		case 4:
			check = false;
			break;
		case 5:
			std::cout << "Такого варианта нет";
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




/*
std::vector<int> triv_search(std::string haystack, std::string needle)
{
	std::vector<int> vec;
	int n = needle.length();
	int m = haystack.length();
	for (int i(0); i <= m; ++i)
	{
		vec.push_back(0);
	}
	int s;

	for (int i(n); i < m; ++i)
	{
		s = 1;
		while (needle[s] == haystack[i - (s)] && (s < n))
		{
			s++;
			std::cout << i - (s) << "\n";
		}
		if ((s == n) && (needle[n] == haystack[i]))
			vec[i] = n;
		else
			vec[i] = 0;
	}
	return vec;
}


void search(char* haystack, const char* needle)
{
	std::vector<int> word;
	int m = strlen(haystack);
	int n = strlen(needle);
	char* str = new char[n + 1];
	str[n] = '\0';
	for (int i(0); i < m; ++i)
	{
		for (int j(0), k(0); j < n; ++j, ++k)
		{
			if (needle[j] == haystack[i])
			{
			}
		}
	}
	for (int i : word)
		std::cout << i << "\n";
}*/