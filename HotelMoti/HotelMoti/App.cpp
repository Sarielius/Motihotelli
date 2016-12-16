#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

static int callback(void* data, int colNum, char** fieldData, char** colName)
{
	for (int i = 0; i < colNum; i++)
	{
		printf("%s = %s\n", colName[i], fieldData[i] ? fieldData[i] : "NULL");
	}
	printf("\n");
	return 0;
}


void App::run()
{
	
	// Initializations and opening the database.
	sqlite3* db;
	bool running = true;
	int rc;

	rc = sqlite3_open("../Database/MotiDB", &db);

	if (rc != 0) // Error handling for each code maybe possibly soon
	{
		printf("Error opening database!");
	}
	


	char selection = 0;
	char debug = 0;
	char message[256] = {""};

	while (running) // Main loopage
	{	
		system("cls");
		
		printf("Welcome to the Motihotel database program v0.0.0.0.1 All Rights Reserved.\n\n");
		
		printf("Please select an action number and press Enter.\n");
		printf("1. Print table contents\n");
		printf("2. Print using a condition\n");
		printf("3. Add a new record\n");
		printf("4. Update an existing record\n");
		printf("5. Delete an existing record\n");
		
		printf("6. Quit\n"); // Switch to last
		
		if (message) // Hyvvää koodiam
		{
			printf("\n>> %s\n\n   Key pressed: %d\n\n", message, selection);
		}

		fflush(stdin);
		
		printf("> ");

		selection = getchar();

		printf("\n");

		selection -= 48; // getchar gets keycode for reasons

		fflush(stdin);

		switch (selection)
		{
		case 1:
			rc = selectAll(db);
			break;
		case 2:
			rc = selectCond(db);
			break;
		case 3:
			rc = insertRec(db);
			break;
		case 4:
			rc = updateRec(db);
			break;
		case 5:
			rc = deleteRec(db);
			break;
		case 6:
			running = false;
			break;
		default:
			sprintf_s(message, "Invalid selection!");
			break;
		}
		
		switch (rc)
		{
		case SQLITE_MISMATCH:
			sprintf_s(message, "Value not matching expected type!");
			break;
		case SQLITE_RANGE:
			sprintf_s(message, "Value out of range!");
			break;
		default:
			break;
		}

	}
	
	// Close database.
	sqlite3_close(db);

}


int App::selectAll(sqlite3* database)
{
	sqlite3_stmt *stmt;

	std::string statementData = "select * from customers;"; 
	char* errorMsg = 0;
	
	int rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)data
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}
	else
	{
		printf("Operation completed succesfully!\n\n");
	}
	
	printf("Enter a key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}


int App::selectCond(sqlite3* database)
{
	sqlite3_stmt *stmt;

	char* errorMsg = 0;

	std::stringstream ss;
	std::string statementData;


	ss << "select * from customers where ";

	printf("\n>> Enter the column name (ID, firstname, lastname, phonenumber, enddate):\n\n> ");
	std::cin >> statementData;

	ss << statementData << " like '";

	printf("\n>> Enter a conditional value:\n\n> ");
	std::cin >> statementData;

	ss << statementData << "';";
	statementData = ss.str();
	
	//printf("\n%s\n\n", statementData.c_str());
	
	int rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)msg
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}
	else
	{
		printf("Operation completed successfully!\n\n");
	}
	
	printf("Enter a key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}


int App::insertRec(sqlite3* database)
{
	sqlite3_stmt *stmt;
	
	char* errorMsg = 0;

	std::stringstream ss;
	std::string statementData;

	// Repeated concatenation of strings is good for you. Shlemiel says hi.
	// Usability vs efficiency? 

	ss << "insert into customers (firstname, lastname, phonenumber, enddate) values ('";

	printf("\n>> Enter the client's first name:\n\n> ");
	std::cin >> statementData;
	ss << statementData << "','";

	printf("\n>> Enter the client's surname:\n\n> ");
	std::cin >> statementData;
	ss << statementData << "',";

	printf("\n>> Enter the client's phonenumber (10 numbers):\n\n> ");
	std::cin >> statementData;
	ss << statementData << ",'";

	printf("\n>> Enter the end date of the reservation (dd.mm.yyyy format):\n\n> ");
	std::cin >> statementData;
	ss << statementData << "');";

	statementData = ss.str();

	//printf("\n%s\n\n", statementData.c_str());

	int rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)msg
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}
	else
	{
		printf("Operation completed succesfully!\n\n");
	}

	printf("Enter a key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}


int App::updateRec(sqlite3* database)
{
	sqlite3_stmt *stmt;

	char* errorMsg = 0;

	std::stringstream ss;
	std::string statementData = "select * from customers;";

	int rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)data
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}

	ss << "update customers set ";

	printf("\n>> Enter the column name which you wish to UPDATE:\n\n> ");
	std::cin >> statementData;

	ss << statementData << "='";

	printf("\n>> Enter the UPDATED VALUE for the selected column:\n\n> ");
	std::cin >> statementData;

	ss << statementData << "' where ";

	printf("\n>> Enter the column name by which to apply the update (e.g. -> FIRSTNAME=kallu):\n\n> ");
	std::cin >> statementData;

	ss << statementData << "='";

	printf("\n>> Enter a value for the condition column (e.g. firstname=KALLU <-):\n\n> ");
	std::cin >> statementData;

	ss << statementData << "';";

	statementData = ss.str();

	

	rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)msg
	if (rc != SQLITE_OK)
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return 1;
	}
	else
	{
		system("cls");
	}
	statementData = "select * from customers;";

	//printf("\n%s\n\n", statementData.c_str());

	rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)data
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}
	else
	{
		printf("Operation completed succesfully!\nValue(s) updated!\n\n");
	}

	printf("Enter a key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}


int App::deleteRec(sqlite3* database)
{
	sqlite3_stmt *stmt;
	
	char* errorMsg = 0;

	std::stringstream ss;
	std::string statementData = "select * from customers;";

	int rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)data
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}

	ss << "delete from customers where ";

	printf("\n>> Enter the column name by which to DELETE\n   CAUTION! USE ID TO PREVENT ACCIDENTAL DELETIONS!:\n\n> ");
	std::cin >> statementData;

	ss << statementData << "='";

	printf("\n>> Enter a VALUE by which to DELETE:\n\n> ");
	std::cin >> statementData;

	ss << statementData << "';";

	statementData = ss.str();

	

	rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)msg
	if (rc != SQLITE_OK) 
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return 1;
	}
	else
	{
		system("cls");
	}

	//printf("\n%s\n\n", statementData.c_str());

	statementData = "select * from customers;";

	rc = sqlite3_exec(database, statementData.c_str(), callback, 0, &errorMsg); // (void*)data
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return rc;
	}
	else
	{
		printf("Operation completed succesfully!\nEntry deleted!\n\n");
	}

	printf("Enter a key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}

