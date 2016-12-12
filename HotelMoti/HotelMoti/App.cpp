#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

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
		printf("2. Write string (Select)\n");
		printf("3. Write string (Insert)\n");
		printf("4. Write string (Update)\n");
		printf("5. Write string (Delete)\n");
		
		printf("6. Quit\n"); // Switch to last
		
		if (message) // Hyvvää koodiam
		{
			printf("\n>> %s\n\n   Key pressed debug: %d\n\n", message, selection);
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
			// select * from table;
			//printf("Feature pending.");
			//sprintf_s(message, "Pending implementation!");
			rc = selectAll(db);
			if (rc != SQLITE_OK)
			{
				printf("Shit got fucked\n");
			}
			
			break;
		case 2:

			selectCond(db);

			/*printf("\n>> Enter message:\n\n> ");
			fgets(message, sizeof(message), stdin);*/
			break;
		case 3:
			selectAll(db);
			sprintf_s(message, "Pending implementation!");
			break;
		case 4:
			sprintf_s(message, "Pending implementation!");
			break;
		case 5:
			sprintf_s(message, "Pending implementation!");
			break;
		case 6:
			running = false;
			break;
		default:
			sprintf_s(message, "Invalid selection!");
			break;
		}
		
	}
	
	// Close database.
	sqlite3_close(db);

}

int App::selectAll(sqlite3* database)
{
	sqlite3_stmt *stmt;
	// Ask nice stuff about what to select and so, maybe ask for ALL first.
	char statementData[256] = { "select * from customers;" };
	char* msg = "Ping";
	char* errorMsg = 0;
	/*int code = sqlite3_prepare_v2(database, statementData,)*/
	
	int rc = sqlite3_exec(database, statementData, callback, 0, &errorMsg); // (void*)msg
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return 1;
	}
	else
	{
		printf("Operation completed succesfully!\n\n");
	}

	printf("Press any key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}

int App::selectCond(sqlite3* database)
{
	sqlite3_stmt *stmt;
	// Ask nice stuff about what to select and so, maybe ask for ALL first.
	char statementData[256]; // = { "select * from customers;" };
	char colData[64]; 
	char condition[64];
	char* errorMsg = 0;
	size_t len;


	printf("\n>> Enter column name (ID, firstname, lastname, phonenumber, enddate):\n\n> ");
	fgets(colData, sizeof(colData), stdin);

	len = strlen(colData);
	if (colData[len - 1] == '\n' && len != 0) // FAILS when len == 0
	{
		colData[len - 1] = '\0';
	}

	fflush(stdin);

	printf("\n>> Enter conditional value:\n\n> ");
	fgets(condition, sizeof(condition), stdin);
	
	len = strlen(condition);
	if (condition[len - 1] == '\n' && len != 0) // FAILS when len == 0
	{  
		condition[len - 1] = '\0';
	}

	fflush(stdin);

	sprintf_s(statementData, "select * from customers where %s like '%s';", colData, condition);


	printf("\n%s\n\n", statementData);

	int rc = sqlite3_exec(database, statementData, callback, 0, &errorMsg); // (void*)msg
	if (rc != SQLITE_OK) // SQLITE_OK = 0
	{
		printf("SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
		return 1;
	}
	else
	{
		printf("Operation completed succesfully!\n\n");
	}
	
	printf("Press any key to return.\n");

	fflush(stdin);

	printf("> ");

	char selection = getchar();

	return 0;
}

