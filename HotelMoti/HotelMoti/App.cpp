#include "App.h"
#include <stdio.h>
#include <stdlib.h>


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
	char message[100] = {""};

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

		selection -= 48; // XDDDDDDDDDD Works tho

		fflush(stdin);

		switch (selection)
		{
		case 1:
			// select * from table;
			//printf("Feature pending.");
			sprintf_s(message, "Pending implementation!");
			break;
		case 2:
			printf("\n>> Enter message:\n\n> ");
			fgets(message, 100, stdin);
			break;
		case 3:
			select(*db);
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

int App::select(const sqlite3& database)
{
	// Ask nice stuff about what to select and so, maybe ask for ALL first.
	char statementData[50] = { "" };
	


	return 0;
}