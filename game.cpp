
#include "./game.hpp"

planet_game::planet_game(struct portal *map, int len)
{
	if (!map || len < 2)
	{
		cout << "Error: Incorrect args form planet_game.\n";
		return;
	}

	struct gportal one;

	for (int i = 0; i < len * len; i++)
	{
		one.id = map[i].id;
		one.to = map[i].to;
		one.from = map[i].from;
		portals.push_back(one);
	}

	init = true;
}

int planet_game::start(void)
{
	if (!init)
	{
		return 1;
	}

	bool to_next = false;
	string in;
	int id;

	for (;; system("clear"), to_next = false)
	{
		cout << "Ok, right now you are on the planet number " << cur_planet
			 << "\nHere is a list of available portals:\n";

		for (auto &p : portals)
		{
			if (p.from != cur_planet || p.to == p.from)
			{
				continue;
			}

			cout << p.id << ") to ";

			if (p.visited)
			{
				cout << p.to << endl;
			}
			else
			{
				cout << "?" << endl;
			}
		}

		cout << "\nRight now write port number for moving to some planet: ";
		cin >> in;

		if (in == "exit")
		{
			break;
		}

		id = atoi(in.c_str());

		if (!set_visited(id))
		{
			cout << "It's incorrect id. Leave...\n";
			break;
		}
	}

	return 0;
}

bool planet_game::set_visited(int id)
{
	bool to_next = false;
	int prev_cur = cur_planet;

	for (auto &p : portals)
	{
		if (p.from == cur_planet && p.id == id)
		{
			p.visited = true;
			cur_planet = p.to;
			to_next = true;
			break;
		}
	}

	for (auto &p : portals)
	{
		if (p.to == prev_cur && p.from == cur_planet)
		{
			p.visited = true;
			break;
		}
	}

	return to_next;
}