#include <iostream>
#include <iomanip>
#include <ctime>
#include "login.h"
#include "doctor.h"
#include "office.h"
using namespace std;

int main()
{

// current date/time based on current system
    time_t now = time(0);

    tm *ltm = localtime(&now);
    stringstream ss;
    ss<<setw(2)<<setfill('0')<<ltm->tm_mday<<"-"<<setw(2)<<setfill('0')<<ltm->tm_mon+1<<"-"<<1900+ltm->tm_year;
    string date = ss.str();

    Login login;
    Doctor doctor(date);
    Office office;

// system("clear");
    int ret{};
    while(1)
    {
        ret = 0;
        switch(login.loginManager())
        {
            case 1:
                ret = doctor.doctorOpFn(date);
                if(ret == 3) login.changePassword("doctor");
                cout<<"logout successful\n";
                break;

            case 2:
                cout<<"welcome pharmacist";
                break;

            case 3:
                ret = office.officeFn(date);
                if(ret == 2) login.changePassword("office");
                cout<<"logout successful\n";
                break;
                
            default: 
                cout<<"\nlogin unsuccessful\n";
                break;
        }
    }
    return 0;
}                       