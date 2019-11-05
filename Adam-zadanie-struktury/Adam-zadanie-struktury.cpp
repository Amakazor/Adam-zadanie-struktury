#include <iostream>
#include <random>
#include <set>

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

		_struct->c = distribution_char(engine);

		_struct->f = 1000.0f + (float)n + 1.0f;

		struct_arr[n] = _struct;
	}

	return struct_arr;
}

int main()
{
	Struct** struct_arr = losowanie(10000);


}