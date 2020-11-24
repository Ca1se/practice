#ifndef _HEADER_H_
#define _HEADER_H_

#include<string>
#include<unordered_map>
using namespace std;

using namespace std;
enum Gender {
    male,
    female,
    alien,
};

class PeopleInHos {
protected:
    PeopleInHos(int, string, int, Gender, string);
    PeopleInHos() = default;

    int _no;
    int _age;
    string _name;
    Gender _gender;
    string _department;
};

class Patient: public PeopleInHos {
public:
    Patient(int, string, int, Gender, string);
    Patient(const Patient&) = default;
    Patient() = default;
    string tellIllness();
private:
    string _illnessDetails;
    string _treatmentDetails;
    friend class PatientSys;

    friend ostream& operator<< (ostream&, const Patient&);
};

class Doctor: public PeopleInHos {
public:
    Doctor(int, string, int, Gender, string, string);
    Doctor(const Doctor&) = default;
    Doctor() = default;
private:
    string _professionalTitle;
    string _diagnosisDetails;
    friend class DoctorSys;

    friend ostream& operator<< (ostream&, const Doctor&);
};

class BaseSys {
public:
    virtual ~BaseSys() = default;

    virtual void Print() const = 0;
};

class PatientSys: public BaseSys {
public:
    void Register(const Patient&);
    void SeeDoctor(int) ;
    void Print() const override;

    static PatientSys& GetPatientSys();
private:
    PatientSys() = default;
    unordered_map<int, Patient> _mP;
};

class DoctorSys: public BaseSys {
public:
    void onDuty(const Doctor&);
    string Diagnose(string);
    void Print() const override;

    static DoctorSys& GetDoctorSys();
private:
    unordered_map<int, Doctor> _mD;
};
#endif