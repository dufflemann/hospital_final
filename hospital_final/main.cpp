#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "PatientAccount.h"

void populateVector(std::vector<PatientAccount>& myPatients);
void populateObjects(std::vector<PatientAccount>& myPatients);
void mainMenu(std::vector<PatientAccount> myPatients);
void checkoutMenu(std::vector<PatientAccount> myPatients);
void enterSurgery(std::vector<PatientAccount>& myPatients);
void enterMedication(std::vector<PatientAccount>& myPatients);

int main() {
	std::vector<PatientAccount> patients;
	populateVector(patients);
	populateObjects(patients);
	mainMenu(patients);
	return 0;
}

void populateVector(std::vector<PatientAccount>& myPatients) { //Reads the # of lines in patientaccounts.txt and creates that many objects
	int count = 0;
	std::string line;
	std::ifstream file("patientaccounts.txt");
	if (!file.is_open())
		std::cout << "ERROR OPENING FILE!";
	while (getline(file, line))
		count++;
	file.close();
	for (int i = 0; i < count; i++) {
		PatientAccount newPatient;
		myPatients.push_back(newPatient);
	}
}

void populateObjects(std::vector<PatientAccount>& myPatients) { // Populates the patient objects with information from patientaccounts.txt
	size_t size = myPatients.size();
	std::ifstream file("patientaccounts.txt");
	if (!file.is_open())
		std::cout << "ERROR OPENING FILE!";
	for (size_t i = 0; i < size; i++) {
		std::string ID, firstName, lastName, surgery, medication, admitted;
		getline(file, ID, ' ');
		getline(file, firstName, ' ');
		getline(file, lastName, ' ');
		getline(file, surgery, ' ');
		getline(file, medication, ' ');
		getline(file, admitted, '\n');
		myPatients[i].setID(ID);
		myPatients[i].setFirstName(firstName);
		myPatients[i].setLastName(lastName);
		myPatients[i].setSurgery(surgery);
		myPatients[i].setMedication(medication);
		myPatients[i].setAdmittedDate(admitted);
	}
	file.close();
}
void mainMenu(std::vector<PatientAccount> myPatients) { //Creates the main menu
	bool repeat = true;
	do {
		int userChoice;
		std::cout << "Hospital Main Menu\n==================\n[1] Enter surgery\n[2] Enter medication\n[3] Check out of hospital\n[4] Quit\n\nEnter a choice: ";
		std::cin >> userChoice;
		switch (userChoice) {
		case 1: enterSurgery(myPatients); repeat = false; break;
		case 2: enterMedication(myPatients); repeat = false; break;
		case 3: checkoutMenu(myPatients); repeat = false; break;
		case 4: repeat = false; break;
		default:
			std::cout << "\nYou entered an invalid command. Try again.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Makes sure input is valid
			repeat = true;
			break;
		}
	} while (repeat == true);
}

void checkoutMenu(std::vector<PatientAccount> myPatients) { // Creates a menu for checking out and calculates total hospital fees
	bool isRunning = true;
	int userChoice, x = 0;
	const int DAILYRATE = 500;
	std::time_t currentTime = time(NULL);
	std::ifstream file("patientaccounts.txt");
	if (!file.is_open())
		std::cout << "ERROR OPENING FILE!";
	system("CLS");
	std::cout << "Patient List\n============\n";
	while (!file.eof()) {
		std::string ID, firstName, lastName, surgery, medication, admitted;
		getline(file, ID, ' ');
		getline(file, firstName, ' ');
		getline(file, lastName, ' ');
		getline(file, surgery, ' ');
		getline(file, medication, ' ');
		getline(file, admitted, '\n');
		int patientID = std::stoi(ID) + 1; // Set the first patient to 1 instead of 0

		std::cout << "[" << patientID << "] " << firstName << " " << lastName << '\n';
	}
	file.close();
	do {
		std::cout << "\nSelect patient to checkout: ";
		std::cin >> userChoice;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter a valid number\n";
		}
		else if (userChoice <= (int)myPatients.size() && userChoice > 0) {
			std::stringstream convertedDate(myPatients[userChoice-1].getDateAdmitted());
			convertedDate >> x; // Convert string dateAdmitted to int
			std::time_t temp = x; // Convert int dateAdmitted to time_t
			double dtime = ceil(std::difftime(currentTime, temp) / (60 * 60 * 24)); // Rounding up since partial days in the hospital would be billed as full days
			std::cout << dtime * DAILYRATE << " is what is due.";
			isRunning = false;
		}
		else if (userChoice > (int)myPatients.size() || userChoice <= 0) {
			std::cout << "Patient #" << userChoice << " does not exist.\n";
		}
	} while (isRunning == true);
}

void enterSurgery(std::vector<PatientAccount>& myPatients) {
	bool isRunning = true;
	int userChoice;
	std::string newSurgery;
	std::ifstream file("patientaccounts.txt");
	if (!file.is_open())
		std::cout << "ERROR OPENING FILE!";
	system("CLS");
	while (!file.eof()) {
		std::string ID, firstName, lastName, surgery, medication, admitted;
		getline(file, ID, ' ');
		getline(file, firstName, ' ');
		getline(file, lastName, ' ');
		getline(file, surgery, ' ');
		getline(file, medication, ' ');
		getline(file, admitted, '\n');
		int patientID = std::stoi(ID) + 1; // Set the first patient to 1 instead of 0

		std::cout << "[" << patientID << "] " << firstName << " " << lastName << '\n';
	}
	file.close();
	do {
		std::cout << "Enter the patient number: ";
		std::cin >> userChoice;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter a valid number\n";
		}
		else if (userChoice <= (int)myPatients.size() && userChoice > 0) {
			std::cout << "Enter the surgery: ";
			std::cin >> newSurgery;
			myPatients[userChoice - 1].setSurgery(newSurgery);
			std::string outputSurgery = myPatients[userChoice - 1].getSurgery();
			std::cout << myPatients[userChoice - 1].getFirstName() << " " << myPatients[userChoice - 1].getLastName() 
				      << "'s surgery has been updated to " << myPatients[userChoice - 1].getSurgery() << ".";
			isRunning = false;
		}
		else if (userChoice > (int)myPatients.size() || userChoice <= 0) {
			std::cout << "Patient #" << userChoice << " does not exist.\n";
		}
	} while (isRunning == true);
}
void enterMedication(std::vector<PatientAccount>& myPatients) {
	bool isRunning = true;
	int userChoice;
	std::string newMedication;
	std::ifstream file("patientaccounts.txt");
	if (!file.is_open())
		std::cout << "ERROR OPENING FILE!";
	system("CLS");
	while (!file.eof()) {
		std::string ID, firstName, lastName, surgery, medication, admitted;
		getline(file, ID, ' ');
		getline(file, firstName, ' ');
		getline(file, lastName, ' ');
		getline(file, surgery, ' ');
		getline(file, medication, ' ');
		getline(file, admitted, '\n');
		int patientID = std::stoi(ID) + 1; // Set the first patient to 1 instead of 0

		std::cout << "[" << patientID << "] " << firstName << " " << lastName << '\n';
	}
	file.close();
	do {
		std::cout << "Enter the patient number: ";
		std::cin >> userChoice;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter a valid number\n";
		}
		else if (userChoice <= (int)myPatients.size() && userChoice > 0) {
			std::cout << "Enter the medication: ";
			std::cin >> newMedication;
			myPatients[userChoice - 1].setMedication(newMedication);
			std::string outputSurgery = myPatients[userChoice - 1].getSurgery();
			std::cout << myPatients[userChoice - 1].getFirstName() << " " << myPatients[userChoice - 1].getLastName()
				<< "'s medication has been updated to " << myPatients[userChoice - 1].getMedication() << ".";
			isRunning = false;
		}
		else if (userChoice > (int)myPatients.size() || userChoice <= 0) {
			std::cout << "Patient #" << userChoice << " does not exist.\n";
		}
	} while (isRunning == true);
}