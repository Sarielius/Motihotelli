#pragma once
#include "sqlite3.h"

class App
{
public:

	void run();
	int select(const sqlite3& database);
};

