#include "history.h"

// put your functions here. 

// TODO: check input data, make sure it's valid integer data, and a valid year number
// TODO: You must use seekg to position the "get" (read) pointer, and seekp to position the put (write) pointer in all places where you read/write


// Function ShowYear() function opens the file for input and output in binary mode
// we check if the file is open, If its not we'll return an error, 
// we prompt the User for the year and the major event that happened and then 
// we read the info into a variable struct called y in human readable language, 
//(after conversion from Binary file), the Year,  record and world population are reinterpreted in 
// human redable language and display them ,  otherwise we return an error for the inputs 

void checkInput(int myYear) {
	do {
		cout << "Please enter a positive year :";
		cin >> myYear;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n'); // ignore characters through newline
		}
	} while (myYear < 1950 && myYear > 2020);
}

void ShowYear() {
	int year;
	char event[200];
	Year y;
	int index = 0;
	long int offset;
	fstream fileName;
	fileName.open("worldHistory.dat", ios::out | ios::in | ios::binary);

	if (!fileName) {
		cout << " Error opening file" << endl;
	}


	cout << "Enter the year of the World Event?" << endl;
	cin >> year;

	checkInput(year);

	/*cout << " Enter the major Event that happened" << endl;
	cin.getline(event,200);*/


	offset = getRecordOffset(year);
	fileName.seekg(offset);

	while (fileName.read(reinterpret_cast<char*>(&y), sizeof(Year))) {
		if (y.year == year && y.event == event)
		{
			cout << "Year: " << y.year << endl;
			cout << "Major event: " << y.event << endl;
			cout << "World population (in billions): " << (y.population / 1000.0) << "billion" << endl;
			break;

		}
		else {
			cout << " No record found for this Year" << year << endl;
		}
	}
	fileName.close();
}
//fileName.seekp(index * sizeof(Year), ios::beg);





// The Show Population Range() function have a slightly different mission to accomplish, 
// we do propmt the user for the beginning and ending years, we read the  data from the binaryfile
// into a variable struct Y again and then use a for loop to check and make sure we had information
// between the beginning of the year and the end of the year. 
// the next thing we do here is we display the years and Population in between on a Histogram using **
// and we finally close the file. 



void ShowPopulationRange() {
	Year y;
	int yearBegin, yearEnd;
	long int offset;
	fstream fileName("worldHistory.dat", ios::in | ios::out | ios::binary);


	cout << "Enter the beginning of the Year" << endl;
	cin >> yearBegin;
	checkInput(yearBegin);
	cout << " Enter the end of the Year" << endl;
	cin >> yearEnd;
	checkInput(yearEnd);

	int index = yearBegin;
	for (index = 1950; index < yearEnd; index++) {

		offset = getRecordOffset(index);
		fileName.seekg(offset);

		while (fileName.read(reinterpret_cast<char*>(&y), sizeof(Year)))
		{
			if (y.year >= yearBegin && y.year <= yearEnd) {

				cout << y.year << fixed << setprecision(6) << (y.population / 1000.0);
				int starsNumber = 0;
				starsNumber = static_cast<int>(y.population / 1000.0 * 3);
				// a star for each one third of a billion people and the result is rounded 
				// to the nearest integer because there are no half stars if we were to use it 
				// in the following loap
				for (int index = 0; index < starsNumber; index++) {
					cout << "*";
				}
				cout << endl;
			}
		}
		fileName.close();
	}
}



/// <summary>
/// Third Function here was the ChangeRecord function, we prompted the user for a Year input, 
/// and then we jumped within the binary file at the exact year to read the records for the Year, i.e the Year, event and population
/// which we immediately display on the screen.
/// 
/// What follows next was then going forward to change the record within the binary file but seeking the position of the offset. 
/// well, before everything else we're try to prompt the user for the new population that we'll substitute the old one with.
/// Later on we use one of the binary random access features including the seekp function sets the position of the write position in the binary file
/// for put or write to the specified offset .Well How do we get the Offset?? we create a separate function called getRecordOffset that 
/// is passed an int and then performs some calculations (which I'll explain later) and then returns the offset. 
/// Finally after writing to the offset, we'll display a message that tell us that the action is done
/// 
///     
/// </summary>

void ChangeRecord() {

	Year y;
	int year;
	fstream fileName("worldHistory.dat", ios::in | ios::out | ios::binary);

	cout << " Enter a year for an event for which an event happened" << endl;
	cin >> year;

	checkInput(year);
	long int offset = getRecordOffset(year);
	fileName.seekp(offset);

	while (fileName.read(reinterpret_cast<char*>(&y), sizeof(Year))) {
		if (y.year == year) {
			cout << "current record:" << endl;
			cout << "Year: " << y.year << endl;
			cout << "Major event: " << y.event << endl;
			cout << "World population (in billions): " << (y.population / 1000.0) << endl;
			cout << endl;

			cout << "Please enter a New Population in billions " << endl;
			double newPopulation;
			cin >> newPopulation;
			y.population = static_cast<int>(newPopulation * 1000.0);

			checkInput(y.population);

			cout << "Enter the new Event:";
			cin.ignore();
			cin.getline(y.event, 200);


			//argument specifies that the offset is '-sizeof(Year)' and the write pointer 

			long int offset = getRecordOffset(y.population);

			fileName.seekp(offset);
			fileName.write(reinterpret_cast<char*>(&y), sizeof(Year));
			cout << " Record changed." << endl;
			break;
		}

	}
	fileName.close();
}

// Welcome to the getRecordOffset function, generally as simply put an offset is a value that 
// represents the difference between two separate location in memory, so in this case, we pass the function 
// an int called year, then we'll return the position of the Year from the starting year, in this case 1950, and the 
// multiply it by the size of the Struct year, The reason for this was necessary because the
// record's offset must be specified in bytes,hence calculating the number of bytes the record is offset from the start of the .dat file
// instead of just the number of 'Year' Structs. 


int getRecordOffset(int year) {
	return (year - 1950) * sizeof(Year);

}

// the sizeof operator returns the size in bytes of its operand , in this case the Year Struct, 

/// <summary>
/// Finally, the ShowWorldRecord Event, in this function the user is prompted for a beginning and ending year.
///  The program displays those years and the world event that occured in those years. 
/// Again here we use the idea of the offset, the only difference is that we create a for loop
/// that was to initialise the index from the startyear and then pass the index into the getRecord function to get its offset, which 
/// we later on use the seekg for get to get the location in bytes for the offset and 
/// then read the record using the binary random access features. If for some reason, we 
/// had some bugs, from the wrong user inputs , we print on the screen that 
/// we found no record for the year. otherwise we print the record on the Screen as well  
/// 
/// </summary>

void showWorldEvents() {

	Year y;
	int startYear, endYear;
	long int offset;


	cout << " Enter the beginning of the year." << endl;
	cin >> startYear;

	checkInput(startYear);
	cout << "Enter the end of the Year" << endl;
	cin >> endYear;
	checkInput(endYear);


	fstream fileName("worldHistory.dat", ios::in | ios::out | ios::binary);

	int index = startYear;
	for (index; index <= endYear; index++) {
		offset = getRecordOffset(index);
		fileName.seekg(offset);
		fileName.read(reinterpret_cast<char*>(&y), sizeof(Year));
		if (y.year != index) {
			cout << "No record found for year!" << endl;
		}
		else {

			cout << "Year :" << y.year << endl;
			cout << " Event:" << y.year << endl;
			cout << "Population(in Billions):" << y.population << endl;

		}
	}
}