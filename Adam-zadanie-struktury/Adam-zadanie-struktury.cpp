#include <iostream>
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
	std::uniform_int_distribution<> distribution_int(-1000, 9000);
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
		delete struct_arr[amnt];
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
	Struct** struct_arr = losowanie(10000);
}