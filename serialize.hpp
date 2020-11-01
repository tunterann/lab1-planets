
#ifndef _SERIALIZE_LIB_
#define _SERIALIZE_LIB_

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef vector<struct portal> vec;
struct portal
{
	int from, to, id;
};

bool serialize_bin(int, struct portal *);
	struct portal *unserialize_bin(char *, int *);

int file_size(string);

#endif