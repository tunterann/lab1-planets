
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "game.hpp"

using namespace std;

int gen_map(char *);
int load(char *);

/*******************************************************************/
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Error: Incorrect args number.\n";
		return 1;
	}

	string command = string(argv[1]);

	if (command == "gen")
	{
		return gen_map(argv[2]);
	}

	if (command == "load")
	{
		return load(argv[2]);
	}

	cout << "Error: Incoreect start command.\n";
	return 1;
}
/*******************************************************************/
int gen_map(char *arg)
{
	int planet_num = atoi(arg), id = 0;
	vector<struct portal> portals;
	struct portal one;

	if (planet_num < 2)
	{
		cout << "Error: Min planet number is 2.\n";
		return 1;
	} 

	for (int i = 0; i < planet_num; i++)
	{
		one.from = i;
		for (int j = 0; j < planet_num; j++)
		{
			one.to = j;
			one.id = id++;
			portals.push_back(one);
		}
	}

	shuffle(portals.begin(), portals.end(),
			default_random_engine(random_device()()));

	struct portal *ptr = new portal[planet_num * planet_num];

	if (!ptr)
	{
		cout << "Error: Can't allocate memory.\n";
		return 1;
	}

	for (size_t i = 0; i < planet_num * planet_num; i++)
	{
		ptr[i] = portals[i];
	}

	for (int i = 0; i < planet_num * planet_num; i++)
	{
		cout << "Id: " << ptr[i].id
			 << ", from: " << ptr[i].from
			 << ", to: "<< ptr[i].to << endl;
	}

	return serialize_bin(planet_num, ptr) ? 0 : 1;
}
/*******************************************************************/
int load(char *arg)
{
	int planet_num = 0;
	struct portal *ptr = unserialize_bin(arg, &planet_num);

	if (!ptr || planet_num < 2 || !ptr)
	{
		cout << "Error: Incorrect map file.\n";
		return 1;
	}

	planet_game play(ptr, planet_num);
	return play.start();
}