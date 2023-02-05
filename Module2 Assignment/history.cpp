#include "history.h"

int main() {


	//Year y;

	// reading the binary file for input and output mode,
	// using the fstream library and the input and output flag

	fstream fileName("worldHistory.dat", ios::in | ios::out | ios::binary);

	int choice; // initialising the integer for the user input choice Menu! 

	do
	{
		//  a do while loop for initialising the choices we'll need for user input 
		cout << "Welcome to the History Lab,Today We're learning US History from 1950 to 2020" << endl;
		cout << "1. Show Year" << endl;
		cout << "2. Show Population Range" << endl;
		cout << "3. Change Record" << endl;
		cout << "4. Show World Events" << endl;
		cout << "5. Exit" << endl;

		cout << "Enter any Choice you Desire! We're at your Service!" << endl;

		// some little secret Sauce just to make it a little active to the user

		this_thread::sleep_for(chrono::seconds(3));

		cout << "Oh Sorry,we meant positive integers from 1 to 5!" << endl;
		// TODO: fix this. 
		// User enters the desired number input for finding the number 
		// for any of the five functions in order to perform their everything

		cin >> choice;

		// using a switch statement to switch back and until the user presses the number 5,
		//which is made up for exiting the Program. once the user doesn't do that 
		// we'll respong with a easy to fix quick response and return the choice menu

		switch (choice) {
		case 1:
			ShowYear();
			break;
		case 2:
			ShowPopulationRange();
			break;
		case 3:
			ChangeRecord();
			break;
		case 4:
			showWorldEvents();
			break;
		case 5:
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid choice. Try again." << endl;
			break;
		}
	} while (choice != 5);

	// As required within the program we'll also need close the fileName
	// in this case as far as this program goes, its the .dat file 
	// right in the solution explorer resource file location..
	// Once the fileName is not saved we'll return with an error and 
	// go for some more pain in debuging why NOT. 
	if (fileName) {
		fileName.close();
	}
	else {
		cout << "Error File not Saved." << endl;
		return 1;
	}

	return 0;
}