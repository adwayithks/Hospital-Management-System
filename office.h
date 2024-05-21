#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

class Office
{
    private:
        int token{};
        int patient_id{};
    
        string getPatientid()
        {
            string pid = to_string(patient_id);
            patient_id++;
            ofstream out{"./patient/.patient_id"};
            out<<patient_id<<endl;
            return pid;
        }
        string patientDetails()
        {
            while(1)
            {
            //creating patient register file
                ofstream otf{"./patient/.patient_register",ios::app};
            //creating patient file
                cout<<"does the patient have a patient id (y or n) : ";
                char temp;
                cin>>temp;
                if(temp == 'y')
                {
                    string pid;
                    cout<<"enter patient id : ";
                    cin>>pid;

                    if(!is_directory("./patient/"+pid))
                    {
                        cout<<"enter valid pid\n";
                        cout<<'\n';
                        continue;
                    }
                    return pid;
                }
                else if(temp == 'n')
                {
                    string name,age,gender;
                    cout<<"\nenter name : ";
                    getline(cin>>ws, name);
                    cout<<"\nenter age : ";
                    getline(cin>>ws, age);
                    cout<<"\nenter gender : ";
                    getline(cin>>ws, gender);
                
                //creating patient details folder and directory
                    string pid = getPatientid();
                //creating entry in patient register file
                    otf<<pid<<" "<<name<<endl;
                    string location = "./patient/"+pid;
                    create_directory(location);
                    location = location+"/details";
                    ofstream outf{location};
                    outf<<"Name\t:  "<<name<<endl;
                    outf<<"Age\t:  "<<age<<endl;
                    outf<<"Gender\t:  "<<gender<<endl;
                    cout<<"\nyour patient id is : "<<pid;
                    return pid;                
                }
                else cin.ignore(numeric_limits<streamsize>::max(), '\n');;
            }
        }
    public:

        Office()
        {

        //creating queue folder and doctor folder
            if(!is_directory("queue")) system("mkdir queue");
            if(!is_directory("./queue/doctor_queue")) create_directory("./queue/doctor_queue");

        //creating patient folder  
            if(!is_directory("patient")) system("mkdir patient");

            ifstream inf{"./patient/.patient_id"};
            if(!inf)
            {
                patient_id = 100000;
                ofstream out{"./patient/.patient_id"};
                out<<patient_id<<endl;
            }
            else
            {
                string pid;
                getline(inf,pid);
                patient_id = stoi(pid);
            } 
        }

        int officeFn(string date)
        {
            system("clear");
            cout<<"\n\nwelcome office clerk";

        // Creating token file
            string token2;
            ofstream of;
            ifstream inf{"./queue/doctor_queue/.token"};
            ifstream in{"./queue/doctor_queue/"+date};
        
        // Token file is reset if its a new date
            if(!inf || !in)
            {
                ofstream outf{"./queue/doctor_queue/.token"};
                outf<<1;
                token = 1;
            }
            else
            {
                getline(inf,token2);
                token = stoi(token2);
            }

        // Creating queue file
            string filename;
            filename = "./queue/doctor_queue/" + date;
            ofstream outf{filename,ios::app};

            while(1)
            {
                system("clear");
                cout<<"\n\nOptions : ";
                cout<<"\n1- Create new token";
                cout<<"\n2- change password";
                cout<<"\n3- logout\n\n";
                int temp{};
                cin>>temp;
            //handling the infinite loop case when char is entered instead of int
                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string pid;

                switch(temp)
                {
                    case 1:
                        pid = patientDetails();
                        outf<<token<<" "<<pid<<endl;
                        cout<<"\nyour token number is : "<<token<<"\tyour patient id is : "<<pid;
                        token++;
                        of.open("./queue/doctor_queue/.token");
                        of<<token<<"\n"<<endl;
                        of.close();
                        break;
                    case 2:
                        return 2;
                    case 3:
                        return 3;
                    default:
                        break;
                }
            }
        }
};