#include "header.h"

int main() {
    Patient tp(1, "小红", 14, female, "外科");
    Doctor td(1, "小黑", 27, male, "外科", "专家");

    PatientSys::GetPatientSys().Register(tp);
    PatientSys::GetPatientSys().SeeDoctor(1);
    PatientSys::GetPatientSys().Print();

    DoctorSys::GetDoctorSys().onDuty(td);
    DoctorSys::GetDoctorSys().Print();
}
