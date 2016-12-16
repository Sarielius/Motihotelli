#pragma once
#include "sqlite3.h"

class App
{
public:

	void run();
	int selectAll(sqlite3* database);
	int selectCond(sqlite3* database);
	int insertRec(sqlite3* database);
	int updateRec(sqlite3* database);
	int deleteRec(sqlite3* database);
};

