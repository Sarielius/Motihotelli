#pragma once
#include "sqlite3.h"

class App
{
public:

	void run();
	int selectAll(sqlite3* database);
	int selectCond(sqlite3* database);
};

