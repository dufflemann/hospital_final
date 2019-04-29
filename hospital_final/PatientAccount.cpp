#include "pch.h"
#include <iostream>
#include <string>
#include "PatientAccount.h"


PatientAccount::PatientAccount() {

}
PatientAccount::~PatientAccount() {

}

std::string PatientAccount::getLastName() const {
	return lastName;
}
std::string PatientAccount::getFirstName() const {
	return firstName;
}
std::string PatientAccount::getDateAdmitted() const {
	return dateAdmitted;
}
std::string PatientAccount::getSurgery() const {
	return surgery;
}
std::string PatientAccount::getMedication() const {
	return medication;
}
void PatientAccount::setMedication(std::string med) {
	medication = med;
}
void PatientAccount::setSurgery(std::string cut) {
	surgery = cut;
}
void PatientAccount::setID(std::string idNumber) {
	ID = idNumber;
}
void PatientAccount::setFirstName(std::string name) {
	firstName = name;
}
void PatientAccount::setLastName(std::string name) {
	lastName = name;
}
void PatientAccount::setAdmittedDate(std::string date) {
	dateAdmitted = date;
}
