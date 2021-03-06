#include <stdlib.h>
#include <iostream>
#include <random>
#include <algorithm> 
#include <vector>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <fstream>

auto prefix_function(const std::string needle)
{
	std::vector<int> pi(needle.size()+1, 0);

	for (int i = 1; i < needle.size(); ++i)
	{
		int j = pi[i - 1];

		while (j > 0 && needle[i] != needle[j])
			j = pi[j - 1];
		if (needle[i] == needle[j])
			pi[i] = j + 1;
		else 
			pi[i] = j;
	}
	return pi;
}

auto kmp_tmp(std::string haystack, std::string needle)
{
	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<int> pi, vec(haystack.size(), 0);

	pi = prefix_function(needle);
	if (haystack[0] == needle[0]) vec[0] = 1;
	else vec[0] = 0;

	int j = 0;
	for (int i = 1; i < haystack.size(); ++i)
	{
		j = vec[i-1];
		if (j == needle.size()) j = pi[j];
		while (j > 0 && needle[j] != haystack[i])
		{
			j = pi[j-1];
		}

		if (haystack[i] == needle[j]) vec[i] = j + 1;
		else vec[i] = 0;
		i++;
	}

	std::cout << "\n";
	for (int i : vec) std::cout << i << " ";
	std::cout << "\n";

	auto t2 = std::chrono::high_resolution_clock::now();
	auto dt = ((std::chrono::nanoseconds)(t2 - t1)).count();

	return dt;
}

auto kmp(std::string haystack, std::string needle) 
{
	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<int> pi, vec2(1);

	pi = prefix_function(needle);

	int j = 0, k = 0;
	if (haystack[0] == needle[0]) vec2.push_back(0);
	for (int i = 1; i < haystack.size(); ++i)
	{
		while (j > 0 && haystack[i] != needle[j])
		{
			j = pi[j-1];
		}
		if (haystack[i] == needle[j]) j++;
		if (j == needle.size())
		{
			vec2.push_back(i - needle.size() + 1);
			j = 0;
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto dt = ((std::chrono::nanoseconds)(t2 - t1)).count();

	return dt;
}

auto triv_search(const std::string haystack,const  std::string needle)
{
	auto t1 = std::chrono::high_resolution_clock::now();

	int n = haystack.size();
	int m = needle.size();

	std::vector<int> ans;
	int j;

	for (int i = 0; i <= n-m; ++i)
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && (j < m))
		{	
			//std::cout << j << "\n";
			if (j == m-1 ) ans.push_back(i + j - 1);
			j++;
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto dt = ((std::chrono::nanoseconds)(t2 - t1)).count();

	return dt;
}

void experiment1()
{
	std::ofstream fout, fout2;
	fout.open("exp_1_graphic_trivTMP.txt");
	fout2.open("exp_1_graphic_prefixTMP.txt");

	std::string haystack;
	std::string needle;

	std::cout << "?????????? ab, ?????????????? ?????????? ?????????? (???? ???????? ????????):";
	std::cin >> needle;
	std::string needle_tmp = needle;
	std::cout << "??????????, ?? ?????????????? ?????????? ????????????, ?????????? ?????????? (ab)^(1000*k). k = 1, ??? ,1001 ?? ?????????? 10\n";
	haystack = needle;

	int k = 1;
	while(k < 1001)
	{
		for (int i(1); i < k; ++i)
		{
			needle += (needle_tmp);
		}

		for (int i(1); i < 1000*k; ++i)
		{
			haystack += (needle_tmp);
		}

		auto prefix = kmp(haystack, needle);
		std::cout << "???????????????? ??????????-??????????????-???????????? ???????????????????? ";
		if (prefix < 1000000000)
		{
			fout2 << "0." << prefix << " " << k << "\n";
			std::cout << prefix << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << k << "\n";
		}
		else if (prefix >= 1000000000)
		{
			fout2  << prefix / 1000000000 << " " << k << "\n";
			std::cout << double(prefix / 1000000000) << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << k << "\n";
		}
		haystack = needle_tmp;
		needle = needle_tmp;
		k += 10;
	}

	fout.close();
	fout2.close();

}

void experiment2()
{
	std::string haystack;
	std::string needle;
	std::ofstream fout, fout2;
	fout.open("exp_2_graphic_triv.txt");
	fout2.open("exp_2_graphic_prefix.txt");

	char a, b;
	std::cout << "?????????????? 1-???? ?????????? ????????????????: ";
	std::cin >> a;
	std::cout << "?????????????? 2-???? ?????????? ????????????????: ";
	std::cin >> b;

	for (int m(1); m < 1e+6 + 1; ++m)
	{
		if (m % 2)
			haystack += a;
		else haystack += b;
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(haystack.begin(), haystack.end(), g);

	for (int m(1); m < 1e+6+1; m+=1e+4)
	{
		for (int i(0); i < m; ++i)
		{
			needle += a;
		}

		auto triv = triv_search(haystack, needle);
		std::cout << "?????????????? ???????????????? ???????????????????? ";
		if (triv < 1000000000)
		{
			fout << triv << " " << m << "\n";
			std::cout << triv << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << m << "\n";
		}

		else if (triv >= 1000000000)
		{
			fout << triv / 1000000000 << " " << m << "\n";
			std::cout << double(triv / 1000000000) << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << m << "\n";
		}

		auto prefix = kmp(haystack, needle);
		std::cout << "???????????????? ??????????-??????????????-???????????? ???????????????????? ";
		if (prefix < 1000000000)
		{
			fout2 << "0." << prefix << " " << m << "\n";
			std::cout << prefix << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << m << "\n";
		}
		else if (prefix >= 1000000000)
		{
			fout2 << prefix / 1000000000 << " " << m << "\n";
			std::cout << double(prefix / 1000000000) << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << m << "\n";
		}	

		needle = "";
	}

	fout.close();
	fout2.close();
}

void experiment3()
{
	std::string haystack;
	std::string needle;
	int i = 0;
	std::string word1, word2;
	std::ofstream fout, fout2;
	fout.open("exp_3_graphic_triv.txt");
	fout2.open("exp_3_graphic_prefix.txt");

	char a, b;
	std::cout << "?????????????? ?????????? ??: ";
	std::cin >> a;
	std::cout << "?????????????? ?????????? b: ";
	std::cin >> b;
	while (i < 5)
	{
		needle += a;
		i++;
	}

	for (int h(1); h < 1e+6 + 1; h += 1e+4)
	{
		for (int i(1); i < h+1; ++i)
		{
			if (i % 6 == 0) haystack += b;
			else haystack += a;
		}

		auto triv = triv_search(haystack, needle);
		std::cout << "?????????????? ???????????????? ???????????????????? ";
		if (triv < 1000000000)
		{
			fout << triv << " " << h << "\n";
			std::cout << triv << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << h << "\n";
		}

		else if (triv >= 1000000000)
		{
			fout << triv / 1000000000 << " " << h << "\n";
			std::cout << double(triv / 1000000000) << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << h << "\n";
		}

		auto prefix = kmp(haystack, needle);
		std::cout << "???????????????? ??????????-??????????????-???????????? ???????????????????? ";
		if (prefix < 1000000000)
		{
			fout2 << "0." << prefix << " " << h << "\n";
			std::cout << prefix << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << h << "\n";
		}
		else if (prefix >= 1000000000)
		{
			fout2 << prefix / 1000000000 << " " << h << "\n";
			std::cout << double(prefix / 1000000000) << "\n";
			std::cout << needle.size() << " " << haystack.size() << " " << h << "\n";
		}

		haystack = "";
	}

	fout.close();
	fout2.close();
}

void choose_algorithm(std::string haystack, std::string needle)
{
	int choice_alp = 0;
	std::cout << "\n1.?????????????? ????????????????\n2.???????????????? ??????????-??????????????-????????????\n3.?????????????????? ??????: ";
	std::cin >> choice_alp;
	if (choice_alp == 1)
	{
		auto triv = triv_search(haystack, needle);
		std::cout << "?????????????? ???????????????? ???????????????????? ";
		if (triv / 1000000000 < 1)
			std::cout << triv << " ????????????????????\n";
		else if (triv / 1000000000 >= 1)
			std::cout << triv / 1000000000 << " ????????????\n";
	}
	else if (choice_alp == 2)
	{
		auto prefix = kmp(haystack, needle);
		std::cout << "???????????????? ??????????-??????????????-???????????? ???????????????????? ";
		if (prefix / 1000000000 < 1)
			std::cout << prefix << " ????????????????????\n";
		else if (prefix / 1000000000 >= 1)
			std::cout << prefix / 1000000000 << " ????????????\n";
	}
	else if (choice_alp == 3)
	{
		auto triv = triv_search(haystack, needle);
		std::cout << "?????????????? ???????????????? ???????????????????? ";
		if (triv / 1000000000 < 1)
			std::cout << triv << " ????????????????????\n";
		else if (triv / 1000000000 >= 1)
			std::cout << triv / 1000000000 << " ????????????\n";

		auto prefix = kmp(haystack, needle);
		std::cout << "???????????????? ??????????-??????????????-???????????? ???????????????????? ";
		if (prefix / 1000000000 < 1)
			std::cout << prefix << " ????????????????????\n";
		else if (prefix / 1000000000 >= 1)
			std::cout << prefix / 1000000000 << " ????????????\n";
	}
	else std::cout << "???????????? ???????????????? ??????";
}

void choose_alphabet(std::string str)
{
	srand(time(NULL));
	std::string haystack, needle;
	int word_length = 0, alp_range_begin = 0, alp_range_end = 0;
	std::cout << "?????????????? ?????????? ??????????, ?? ?????????????? ?????????? ????????????: ";
	std::cin >> word_length;
	std::cout << "?????????????? ???????????????? ???????? ?? ????????????????: \n";
	for (char ch : str) std::cout << ch << "  ";
	std::cout << "\n";
	for (int i(0); i < str.length(); ++i)
	{
		std::cout << i << " ";
		if (i < 10) std::cout << " ";
	}
	std::cout << "\n???????????? ??????????????????: ";
	std::cin >> alp_range_begin;
	std::cout << "?????????? ??????????????????: ";
	std::cin >> alp_range_end;

	for (int i = 0; i < word_length; ++i)
		haystack.push_back(char(str[alp_range_begin] + rand() % (str[alp_range_begin] - str[alp_range_end])));

	std::cout << "?????????????? ?????????? ??????????, ?????????????? ?????????? ??????????: ";
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
	for (char i = '??'; i <= '??'; i++)
	{
		rus_alphabet.push_back(i);
	}

	int choice = 0, choice_alp = 0, n = 0;
	bool check = true;
	while (check == true)
	{
		std::cout << "????????????????:\n1.???????????? ?????????? ??????????????\n2.?????????????? ?????????? ???????????????? ?? ?????????????????? ???? ?????? ??????????" << 
		"\n3.?????????? ???????? (B1 B2 ??? Bs)^n\n4.?????????????????????? 1\n5.?????????????????????? 2\n6.?????????????????????? 3\n7.??????????\n";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "??????????, ?? ?????????????? ?????????? ????????????:";
			std::cin >> haystack;
			std::cout << "??????????, ?????????????? ?????????? ??????????:";
			std::cin >> needle;
			choose_algorithm(haystack, needle);
			std::cout << "\n";
			break;
		case 2:
			std::cout << "1.??????????????\n2.????????????????????: ";
			std::cin >> choice_alp;
			if (choice_alp == 1)
				choose_alphabet(rus_alphabet);
			else if (choice_alp == 2)
				choose_alphabet(eng_alphabet);
			else std::cout << "???????????? ???????????????? ??????";
			std::cout << "\n";
			break;
		case 3:
			std::cout << "??????????, ?? ?????????????? ?????????? ????????????:";
			std::cin >> haystack;
			std::cout << "?????????????? n:";
			std::cin >> n;
			haystack = mul_num_string(haystack, n);
			std::cout << "??????????, ?????????????? ?????????? ??????????:";
			std::cin >> needle;
			std::cout << "?????????????? n:";
			std::cin >> n;
			needle = mul_num_string(needle, n);

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
			std::cout << "???????????? ???????????????? ??????\n";
			break;
		}
	}

	return 0;
}
