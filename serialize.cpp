
#include "./serialize.hpp"

// First 4 bytes are for number of planets.
// Other bytes are for portals (from <planet_*> to <planet_*>; portal id)
/*******************************************************************/
bool serialize_bin(int planet_num, struct portal *ptr)
{
	if (!ptr || planet_num < 2)
	{
		return false;
	}

	constexpr int size = sizeof(int);
	constexpr int sstr = size * 3;
	int pnum = planet_num * planet_num;
	int shift = 0;
	char *buff;

	buff = new char[pnum * sstr + size];
	if (!buff)
	{
		cout << "Error: Can't allocate space.\n";
		return false;
	}

	memcpy(buff, &planet_num, size);

	for (int i = 0 ; i < pnum; i++)
	{
		shift = i * sstr + size;
		memcpy(buff + shift, &ptr[i].from, size);
		memcpy(buff + shift + size, &ptr[i].to, size);
		memcpy(buff + shift + size * 2, &ptr[i].id, size);
	}

	ofstream fs("./map.bin", ios::binary);

	if (!fs.good())
	{
		cout << "Error: Can't create new map file.\n";
		delete[] buff;
		return false;
	}

	fs.write(buff, pnum * sstr + size);
	fs.close();

	delete[] buff;
	return true;
}
/*******************************************************************/
struct portal *unserialize_bin(char *name, int *planet_num)
{
	constexpr int size = sizeof(int);
	string fname = string(name);
	ifstream fs(fname, ios::binary);
	char *buff;

	if (!fs.good())
	{
		cout << "Error: Can't open " << string(name) << endl;
		return nullptr;
	}

	int fsize = file_size(fname);

	if (fsize < size * 2 + size)
	{
		cout << "Error: Incorrect file.\n";
		return nullptr;
	}

	buff = new char[fsize];
	if (!buff)
	{
		cout << "Error: Can't allocate space.\n";
		return nullptr;
	}

	fs.read(buff, fsize);
	fs.close();
	memcpy(planet_num, buff, size);

	if (*planet_num < 2)
	{
		return nullptr;
	}

	int portal_num = *planet_num * *planet_num;
	struct portal *portals = new portal[portal_num];
	int shift = size;

	if (!portals)
	{
		cout << "Error: Can't allocate space.\n";
		return nullptr;
	}

	for (int i = 0; i < portal_num; i++)
	{
		memcpy(&portals[i].from, buff + shift, size);
		shift += size;

		memcpy(&portals[i].to, buff + shift, size);
		shift += size;

		memcpy(&portals[i].id, buff + shift, size);
		shift += size;
	}

	delete[] buff;
	return portals;
}
/*******************************************************************/
int file_size(string name)
{
	ifstream fs(name, ios::binary | ios::ate);
	int size = fs.tellg();
	fs.close();

	return size;
}