#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <set>
#include <time.h>

struct Struct
{
	int i;
	char c;
	float f;
};

Struct** losowanie(int amnt)
{
	std::random_device seed;
	std::mt19937 engine(seed()); //mersenne_twister_engine
	std::uniform_int_distribution<> distribution_int(-1000 , 9000);
	std::uniform_int_distribution<> distribution_char(66, 83); //B-S ASCII

	Struct** struct_arr = new Struct*[amnt];
	std::set<int> already_used;

	for (int n = 0; n < amnt; n++)
	{
		Struct* _struct = new Struct();

		int _int = 0;
		do
		{
			_int = distribution_int(engine);
		} while (already_used.find(_int) != already_used.end());
		already_used.insert(_int);
		_struct->i = _int;

		_struct->c = (char)distribution_char(engine);

		_struct->f = 1000.0f + (float)n + 1.0f;

		struct_arr[n] = _struct;
	}

	return struct_arr;
}

void kasowanie(Struct** struct_arr, int amnt)
{
	for (int n = 0; n < amnt; n++)
	{
		delete struct_arr[n];
	}

	delete[] struct_arr;
}

void sortowanie(Struct** struct_arr, int amnt)
{
	Struct* temp;

	for (int i = 0; i < amnt; i++) 
	{
		for (int j = i + 1; j < amnt; j++)
		{
			if (struct_arr[j]->i < struct_arr[i]->i) {
				temp = struct_arr[i];
				struct_arr[i] = struct_arr[j];
				struct_arr[j] = temp;
			}
		}
	}

}

int zliczanie(Struct** struct_arr, int amnt, char _char)
{
	int found = 0;

	for (int n = 0; n < amnt; n++)
	{
		if (struct_arr[n]->c == _char) found++;
	}

	return found;
}

int main()
{
	int n;
	char x;
	std::ifstream file;
	std::string line;

	file.open("inlab01.txt");
	if (!file.is_open())
	{
		return -1;
	}
	
	std::getline(file, line);
	if (line.empty())
	{
		return -1;
	}
	std::stringstream line_stream(line);
	line_stream >> n;
	line_stream >> x;

	clock_t begin, end;
	double time_spent;
	begin = clock();

	Struct* sorted = new Struct[20];

	Struct** struct_arr = losowanie(n);
	sortowanie(struct_arr, n);

	int n2 = (n > 20) ? 20 : n;

	for (int i = 0; i < n2; i++)
	{
		sorted[i] = *struct_arr[i];
	}
	int counted = zliczanie(struct_arr, n, x);
	kasowanie(struct_arr, n);

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	for (int i = 0; i < n2; i++)
	{
		std::cout << "Struktura " << i << ": i wynosi " << sorted[i].i << ", c wynosi " << sorted[i].c << ", f wynosi " << sorted[i].f << '\n';
	}

	std::cout << '\n' << "Liczba wystapien znaku " << x << " wynosi: " << counted << '\n' << '\n';
	std::cout << "Czas wykonania wynosi: " << time_spent  << "s" << '\n';
}