#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>
#include <chrono>

//std::vector<int> prefix_function(const std::string s)
auto prefix_function(const std::string s)
{
	auto t1 = std::chrono::high_resolution_clock::now();
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
	auto t2 = std::chrono::high_resolution_clock::now();
	long dt = ((std::chrono::nanoseconds)(t2 - t1)).count();

	//std::cout << "Алгоритм выполнялся " << dt << " наносекунд\n";
	//return pi;
	return dt;
}

//std::vector<int> triv_search(std::string haystack, std::string needle)
auto triv_search(std::string haystack, std::string needle)
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
		if (flag && haystack[i] == needle[0])
		{
			//std::cout << "\nYe\n";
			ans.push_back(i);
		}
		
		flag = false;
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto dt = ((std::chrono::nanoseconds)(t2 - t1)).count();
	//auto dt = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();


	//std::cout << "\n" << ans.size() << "\n";

	//std::cout << "Алгоритм выполнялся " << dt << " наносекунд\n";

	return dt;
}

void choose_algorithm(std::string haystack, std::string needle);

void experiment1()
{
	std::string haystack;
	std::string needle;

	std::cout << "Слово ab, которое нужно найти (из двух букв):";
	std::cin >> needle;
	std::string needle_tmp = needle;
	std::cout << "Слово, в котором нужно искать, будет равно (ab)^(1000*k). k = 1, … ,1001 с шагом 10\n";
	haystack = needle;
	
	for (int k(1); k < 1001; k += 10)
	{
		for (int i(1); i < k; ++i)
		{
			needle += needle_tmp;
		}

		for (int i(1); i < 1000*k; ++i)
		{
			haystack += needle_tmp;
		}
		
		//triv_search(haystack, needle);
		auto triv = triv_search(haystack, needle);
		std::cout << "Наивный алгоритм выполнялся ";
		if (triv < 1000000000)
			std::cout << triv << " наносекунд\n";
		else if (triv > 1000000000)
			std::cout << triv/ 1000000000 << " секунд\n";
	}

	std::cout << needle.size() << " " << haystack.size() << "\n";


	choose_algorithm(haystack, needle);


}

void experiment2()
{
	std::string haystack;
	std::string needle;

	char a, b;
	std::cout << "Введите 1-ую букву алфавита: ";
	std::cin >> a;
	std::cout << "Введите 2-ую букву алфавита: ";
	std::cin >> b;

	for (int m(1); m < 1e+6+1; m+=1e+4)
	{
		for (int i(0); i < m; ++i)
		{
			needle += a;
		}
	}

	for (int m(1); m < 1e+6 + 1; ++m)
	{
		if (m % 2)
			haystack += a;
		else haystack += b;
	}
}

void experiment3()
{
	std::string haystack;
	std::string needle;
	int i = 0;
	std::string word1, word2;

	char a, b;
	std::cout << "Введите букву а: ";
	std::cin >> a;
	std::cout << "Введите букву b: ";
	std::cin >> b;
	while (i < 5)
	{
		word1 += a;
		i++;
	}

	word2 = word1 + b;

	for (int h(1); h < 1e+6 + 1; h += 1e+4)
	{
		for (int i(0); i < h; ++i)
		{
			needle += a;
		}
	}
}

void choose_algorithm(std::string haystack, std::string needle)
{
	int choice_alp = 0;
	std::cout << "\n1.Наивный алгоритм\n2.Алгоритм Кнута-Морриса-Пратта\n3.Выполнить оба: ";
	std::cin >> choice_alp;
	if (choice_alp == 1)
	{
		/*std::vector<int> vec = triv_search(haystack, needle);
		std::cout << "Ответ: ";
		for (int i : vec)
		{
			std::cout << i << " ";
		}*/
		long triv = triv_search(haystack, needle);
		std::cout << "Наивный алгоритм выполнялся ";
		if (triv / 1000000000 < 1)
			std::cout << triv << " наносекунд\n";
		else if (triv / 1000000000 >= 1)
			std::cout << triv / 1000000000 << " секунд\n";
	}
	else if (choice_alp == 2)
	{
		/*std::vector<int> vec2 = prefix_function(needle + ' ' + haystack);

		int n = needle.length();

		std::cout << "Ответ: ";
		for (int i = 0; i < haystack.length(); i++)
		{
			if (vec2[n + 1 + i] == n)
			{
				std::cout << i - n + 1 << " ";
			}
		}*/
		long prefix = prefix_function(needle + ' ' + haystack);
		std::cout << "Алгоритм Кнута-Морриса-Пратта выполнялся ";
		if (prefix / 1000000000 < 1)
			std::cout << prefix << " наносекунд\n";
		else if (prefix / 1000000000 >= 1)
			std::cout << prefix / 1000000000 << " секунд\n";
	}
	else if (choice_alp == 3)
	{
		long triv = triv_search(haystack, needle);
		std::cout << "Наивный алгоритм выполнялся ";
		if (triv / 1000000000 < 1)
			std::cout << triv << " наносекунд\n";
		else if (triv / 1000000000 >= 1)
			std::cout << triv / 1000000000 << " секунд\n";

		long prefix = prefix_function(needle + ' ' + haystack);
		std::cout << "Алгоритм Кнута-Морриса-Пратта выполнялся ";
		if (prefix / 1000000000 < 1)
			std::cout << prefix << " наносекунд\n";
		else if (prefix / 1000000000 >= 1)
			std::cout << prefix / 1000000000 << " секунд\n";
	}
	else std::cout << "Такого варианта нет";
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
	if (rnd!= 0) rnd--;
	for (int i = 0; i < word_length; ++i)
	{	
		needle.push_back(haystack[rnd++]);
	}

	choose_algorithm(haystack, needle);
}

std::string mul_num_string(std::string str, int n)
{
	std::string str_tmp = str;
	for (int i(0); i < n-1; ++i)
	{
		str += str_tmp;
	}
	
	return str;
}

int main(int argc, char**argv) 
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

	int choice = 0, choice_alp = 0, n = 0;
	bool check = true;
	while (check == true)
	{
		std::cout << "Выберите:\n1.Ввести слова вручную\n2.Выбрать буквы алфавита и составить из них слова" << 
		"\n3.Слово вида (B1 B2 … Bs)^n\n4.Эксперимент 1\n5.Эксперимент 2\n6.Эксперимент 3\n7.Выйти\n";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Слово, в котором нужно искать:";
			std::cin >> haystack;
			std::cout << "Слово, которое нужно найти:";
			std::cin >> needle;
			choose_algorithm(haystack, needle);
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
			std::cout << "Слово, в котором нужно искать:";
			std::cin >> haystack;
			std::cout << "Степень n:";
			std::cin >> n;
			haystack = mul_num_string(haystack, n);
			std::cout << "Слово, которое нужно найти:";
			std::cin >> needle;
			std::cout << "Степень n:";
			std::cin >> n;
			needle = mul_num_string(needle, n);

			//std::cout << haystack << " " << needle << "\n";

			choose_algorithm(haystack, needle);
			std::cout << "\n";
			break;
		case 4:
			experiment1();
			break;
		case 5:
			experiment2();
			break;
		case 6:
			experiment3();
			break;
		case 7:
			check = false;
			break;
		default:
			std::cout << "Такого варианта нет\n";
			break;
		}
	}

	return 0;
}
