#pragma once
#include <iostream>
#include <string>

class PatientAccount {
public:
	PatientAccount();
	~PatientAccount();

	std::string getLastName() const;
	std::string getFirstName() const;
	std::string getDateAdmitted() const;
	std::string getSurgery() const;
	std::string getMedication() const;

	void setSurgery(std::string);
	void setMedication(std::string);
	void setID(std::string);
	void setLastName(std::string);
	void setFirstName(std::string);
	void setAdmittedDate(std::string);

private:
	std::string lastName;
	std::string firstName;
	std::string surgery;
	std::string medication;
	std::string ID;
	std::string dateAdmitted;
};