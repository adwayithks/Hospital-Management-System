#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

class Doctor
{
    private:
        int seek{};

        void diag_presc(string pid, string option, string date)
        {
            ofstream outf{"./patient/"+pid+"/"+option,ios::app};
            cout<<"enter "<<option<<" for "<<pid<<" :"<<endl<<endl;
            outf<<endl<<"--------------------"<<endl;
            outf<<date<<endl<<endl;
            string s;
            while(1)
            {
                getline(cin>>ws,s);
                if(s == "over") break;
                outf<<s<<endl;
            }             
            outf<<endl<<"--------------------"<<endl;
        }

        void fileReader(string location)
        {
            cout<<'\n';
            ifstream inf3{location};
            if(!inf3)
            {
                cout<<"\npatient details not found";
                return;
            }
            else
            {
                while(1)
                {
                    string stuff{};
                    while(getline(inf3,stuff))
                        cout<<stuff<<endl;
                    cout<<"\n\nEnter q to exit the view : ";
                    cin>>stuff;
                    if(stuff == "q") break;
                }
                return;
            }
        }
    public:
        Doctor(string date)
        {
        
        // Creating seek file for the doctor
        // it helps in maintaing the location of last diagnosed patient
        // in case of abrupt program shutdown or other unforeseen conditions

            string seek_date{};
            ifstream inf{"./queue/doctor_queue/.doctor_seek"};
            if(!inf)
            {
                ofstream outf{"./queue/doctor_queue/.doctor_seek"};
                outf<<date<<endl;
                outf<<0<<endl;
                seek = 0;
            }
            else
            {
                string seek1;
                inf>>seek_date;
            
            // resetting seek to 0 for a new date
                if(seek_date != date) seek = 0;
                else
                {
                    inf>>seek1;
                    seek = stoi(seek1);
                }
            }


            if(!is_directory("./queue/lab_queue")) create_directory("./queue/lab_queue");
        }
        int doctorOpFn(string date)
        {
            system("clear");
            cout<<"\n\nwelcome doctor"<<endl<<endl;

            while(1)
            {
                string token, token1, pid, pid1;
                system("clear");
                cout<<"\ntoken no.     patient id\n\n";
                ofstream of{"./queue/doctor_queue/.doctor_seek"};
                of<<date<<endl;
                of<<seek<<endl;
                ifstream inf{"./queue/doctor_queue/"+date};
                inf.seekg(seek);

                for(int i{};i<5;i++)
                {
                    token.clear();  // it is similar to : token = "";
                    pid.clear();
                    inf>>token;
                    inf>>pid;
                    if(i == 0)
                    {
                        pid1 = pid;
                        token1 = token;
                    }
                    cout<<token<<"\t\t"<<pid<<endl;
                }

                cout<<"\n\nOptions : \n";
                cout<<"\n1- Diagnose";
                cout<<"\n2- Prescribe";
                cout<<"\n3- See patient details/history";
                cout<<"\n4- Send to lab";
                cout<<"\n5- Change password";
                cout<<"\n6- Logout";
                cout<<"\n7- Refresh\n\n";
                int temp{};
                cin>>temp;

            //handling the infinite loop case when char is entered instead of int
                if (cin.fail()) 
                {
                    // clear the error flag
                    cin.clear();
                    // clear the input buffer // this one is required bcoz of the below continue
                    // we clear the buffer before continuing
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(temp == 1)
                {
                    diag_presc(pid1,"diagnosis",date);
                }
                else if(temp == 2)
                {
                    diag_presc(pid1,"prescription",date);
                    seek = seek + pid1.length() + token1.length() + 2;

                }
                else if(temp == 3)
                {
                    system("clear");

                    if(pid1 == "") cout<<"Patient not selected";
                    else
                    {
                        while(1)
                        {
                            system("clear");
                            cout<<"Patient id : "<<pid1<<endl;

                            cout<<'\n';
                            ifstream inf3{"./patient/"+pid1+"/details"};
                            string stuff{};
                            while(getline(inf3,stuff))
                                cout<<stuff<<endl;

                            cout<<"\n\nOptions : \n";
                            cout<<"\n1- See previous diagnosis of "<<pid1;
                            cout<<"\n2- See previous prescription of "<<pid1;
                            cout<<"\n3- Return to previous menu\n\n";

                            int temp3{};
                            cin>>temp3;

                        //handling the infinite loop case when char is entered instead of int
                            if (cin.fail()) 
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                continue;
                            }
                            else if(temp3 == 1)
                            {
                                string location = "./patient/"+pid1+"/diagnosis";
                                fileReader(location);
                            }
                            else if(temp3 == 2)
                            {
                                string location = "./patient/"+pid1+"/prescription";
                                fileReader(location);
                            }
                            else if(temp3 == 3) break;
                        }
                    }
                }

                else if(temp == 4)
                {
                    ofstream out4{"./queue/lab_queue/" + date};
                    out4<<pid1<<endl;
                    
                }
                else if(temp == 5)
                    return 3;

                else if(temp == 6)
                    return 4;

                else
                    continue;
            }
            return 0;
        }
};