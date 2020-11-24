#include"header.h"
#include<iostream>

PeopleInHos::PeopleInHos(int no, string name, int age, Gender gender, string depart):
        _no(no), _name(name), _age(age), _gender(gender), _department(depart) {}

Patient::Patient(int no, string name, int age, Gender gender, string depart):
        PeopleInHos(no, name, age, gender, depart) {}

string Patient::tellIllness() {
    std::cout << "enter Patient's illness: ";
    std::cin >> _illnessDetails;
    return _illnessDetails;
}

ostream& operator<< (ostream& os, const Patient& t) {
    os << "Patient " << t._no << endl
       << "name: " << t._name << endl
       << "age: " << t._age << endl
       << "gender: " << t._gender << endl
       << "department: " << t._department << endl
       << "illness details: " << t._illnessDetails << endl
       << "treatment details: " << t._treatmentDetails;
    return  os;
}

Doctor::Doctor(int no, string name, int age, Gender gender,
               string depart, string proTitle):
        PeopleInHos(no, move(name), age, gender, move(depart)),
        _professionalTitle(move(proTitle)) {}

ostream& operator<< (ostream& os, const Doctor& t) {
    os << "Doctor " << t._no << endl
       << "name: " << t._name << endl
       << "age: " << t._age << endl
       << "gender: " << t._gender << endl
       << "department: " << t._department << endl
       << "profession title: " << t._professionalTitle << endl
       << "diagnose detail: " << t._diagnosisDetails;
    return  os;
}

PatientSys& PatientSys::GetPatientSys() {
    static PatientSys ps;
    return ps;
}

void PatientSys::Register(const Patient& t) {
    int patientNo = t._no;

    _mP[patientNo] = t;
}

void PatientSys::SeeDoctor(int no) {
    string illness = _mP[no].tellIllness();

    string diagnoseRes;
    diagnoseRes = DoctorSys::GetDoctorSys().Diagnose(illness);

    _mP[no]._treatmentDetails = diagnoseRes;
}

void PatientSys::Print() const {
    for(auto& it: _mP){
        cout << it.second << endl;
    }
}

DoctorSys& DoctorSys::GetDoctorSys() {
    static DoctorSys ds;
    return ds;
}

void DoctorSys::onDuty(const Doctor& t) {
    int doctorNo = t._no;

    _mD[doctorNo] = t;
}

string DoctorSys::Diagnose(string detail) {
    string res = "I think you should ...";

    /*
     * Diagnosing....
     */
    _mD[1]._diagnosisDetails = res;
    return res;
}

void DoctorSys::Print() const {
    for(auto& it: _mD){
        cout << it.second << endl;
    }
}
