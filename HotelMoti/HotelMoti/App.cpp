#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void App::run()
{
	
	// Initializations and opening the database.
	sqlite3* db;
	bool running = true;
	int rc;

	rc = sqlite3_open("../Database/MotiDB", &db);

	if (rc != 0) // Error handling for each code maybe possibly soon
	{
		printf("Error habbend fugg :--DD");
	}
	
	int selection;
	char* message = nullptr;

	while (running) // Main loopage
	{	
		system("cls");
		
		printf("Welcome to the Motihotel database program v0.0.0.0.1 All Rights Reserved.\n\n");
		
		if (message) // Hyvvää koodiam
		{
			printf("\n>> %s\n\n", message);
		}

		printf("Please select an action.\n");
		printf("6. Quit\n"); // Switch to last
		printf("1. Ebin\n");
		
		fflush(stdin);
		
		printf("> ");

		

		selection = _getch();

		switch (selection)
		{
		case 1:
			// select * from table;
			//printf("Feature pending.");
			message = "Feature pending";
			break;
		case 6:
			running = false;
			break;
		default:
			message = "Invalid selection!";
			break;
		}
		
		
	}
	
	// Close database.
	sqlite3_close(db);

}