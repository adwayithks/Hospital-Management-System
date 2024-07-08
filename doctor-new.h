#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

class Doctor
{
    private:
        int seek{};
        int position{};
        vector<string> q{};

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
            system("clear");
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

        ////  function to "remove patients from the temp queue"
        void rm_q(ifstream &if_temp)
        {
            if(position<=q.size())
            {
                q.erase(q.begin()+position);
                string temp{};
                while(getline(if_temp,temp))
                {
                    q.push_back(temp);
                }
                ofstream writeout{"./queue/doctor_queue/.doc_temp_q"};
                int curr{};
                for(int i{};i<q.size();i++)
                {
                    curr += q[i].size()+1;
                    writeout<<q[i]<<endl;
                }
                if_temp.clear();
                if_temp.seekg(curr,ios::beg);
            }
            else cout<<"Invalid Position Entered"; 
        }
    public:

        Doctor(string date)
        {
        
        // Creating seek file for the doctor
        // it helps in maintaing the location of last diagnosed patient
        // in case of abrupt program shutdown or other unforeseen conditions

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
                string seek1{}, seek_date{};
                inf>>seek_date;
            
            // resetting seek to 0 for a new date
                if(seek_date != date) seek = 0;
                else
                {
                    inf>>seek1;
                    seek = stoi(seek1);
                }
            }

        // Creating a directory for lab queue
            if(!is_directory("./queue/lab_queue")) create_directory("./queue/lab_queue");
        }

        int doctorOpFn(string date)
        {
            system("clear");
            cout<<"\n\nwelcome doctor"<<endl<<endl;

            ////  creating a temp queue file to save temporarily  ////

            ifstream if_temp{"./queue/doctor_queue/.doc_temp_q"};
            ofstream of_temp;
            if(!if_temp)
            {
                of_temp.open("./queue/doctor_queue/.doc_temp_q");
                if_temp.open("./queue/doctor_queue/.doc_temp_q");
            }
            of_temp.close();

            while(1)
            {
                string token, token1, pid, pid1, test1;
                system("clear");
                cout<<"\ntoken no.     patient id         test(if any)\n\n";
                ifstream inf{"./queue/doctor_queue/"+date};
                inf.seekg(seek);
                
                // if(!if_temp) cout<<"not working";
                of_temp.close();
                of_temp.open("./queue/doctor_queue/.doc_temp_q", ios::app);
                string q_stuff{};
                while(getline(if_temp,q_stuff))
                {
                    q.push_back(q_stuff);
                }
                if_temp.clear(); /// to clear the eof flag if set

                while(inf>>token && q.size()<5)
                {
                    inf>>pid;
                    string pusher = " "+token+"\t\t"+pid;
                    q.push_back(pusher);
                    of_temp<<pusher<<endl;
                    if_temp.seekg(of_temp.tellp(),ios::beg);

                    seek = seek + pid.length() + token.length() + 2;
                    token.clear();
                    pid.clear();
                }

                for(int i{};i<q.size() && i<5;i++)
                {
                    cout<<q[i]<<endl;
                }
                ofstream of{"./queue/doctor_queue/.doctor_seek"};
                of<<date<<endl;
                of<<seek<<endl;

                cout<<endl<<"--------------------------------------------"<<endl<<endl;

                if(q.size()==0)
                {
                    cout<<"No patient Currently"<<"\n\n\n";
                    cout<<"\nOptions : \n";
                    cout<<"\n5- Change password";
                    cout<<"\n6- Logout";
                    cout<<"\n7- Refresh\n\n";
                    int temp1{};
                    cin>>temp1;

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
                    
                    
                    if(temp1 == 5)
                        return 3;

                    else if(temp1 == 6)
                        return 4;

                    else
                        continue;
                }

                else
                {
                    cout<<"\nOptions : \n";
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
                    
                    if(temp>0 && temp<5)
                    {
                        cout<<"Enter the position of the patient in the queue : ";
                        cin>>position;
                        if(position > q.size())
                        {
                            cout<<endl<<"Invalid position"<<endl;
                            cout<<endl<<"Press enter to continue ... ";
                            system("stty -echo");
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("stty echo");
                            continue;
                        }
                        position--;
                        cout<<endl;
                        int i{1};
                        while(i<q[position].size() && q[position][i]!='\t')
                        {
                            token1+=q[position][i];
                            i++;
                        }
                        i+=2;
                        while(i<q[position].size() && q[position][i]!='\t')
                        {
                            pid1+=q[position][i];
                            i++;
                        }
                        i+=2;
                        while(i<q[position].size())
                        {
                            test1+=q[position][i];
                            i++;
                        }

                        ifstream inf3{"./patient/"+pid1+"/details"};
                        if(!inf3)
                        {
                            cout<<"Invalid pid";
                            continue;
                        }
                        
                        system("clear");
                        

                        cout<<"Patient id : "<<pid1<<endl;
                        if(test1 != "")
                        {
                            cout<<"\nTest done : "<<test1<<endl;
                        }
                        cout<<'\n';
                        string stuff{};
                        while(getline(inf3,stuff))
                            cout<<stuff<<endl;
                        cout<<"\n----------------------------------\n\n";
                        if(temp == 1)
                        {
                            diag_presc(pid1,"diagnosis",date);
                        }
                        else if(temp == 2)
                        {
                            diag_presc(pid1,"prescription",date);
                            rm_q(if_temp);
                        }
                        else if(temp == 3)
                        {
                            {
                                while(1)
                                {
                                    cout<<"\n\nOptions : \n";
                                    cout<<"\n1- See previous diagnosis of "<<pid1;
                                    cout<<"\n2- See previous prescription of "<<pid1;
                                    cout<<"\n3- See lab reports folder of "<<pid1;
                                    cout<<"\n4- Return to previous menu\n\n";

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
                                    else if(temp3 == 3)
                                    {
                                        // creating a shell script to open the folder in nautilus
                                        // you can change the nautilus app with any other file manager
                                        
                                        ofstream of3{"./.open_folder"};
                                        of3<<"#!/bin/bash"<<endl;
                                        of3<<"pid="<<pid1<<endl;
                                        of3<<"location=./patient/$pid/lab-reports"<<endl;
                                        of3<<"mkdir -p $location"<<endl;
                                        of3<<"nautilus $location"<<endl;
                                        of3.close();
                                        system("mv .open_folder .open_folder.sh");
                                        system("./.open_folder.sh");
                                    }
                                    else if(temp3 == 4) break;
                                }
                            }
                        }

                        else if(temp == 4)
                        {
                        
                        // Writing test to be done into a file

                            ofstream out4 {"./patient/"+pid1+"/lab"};

                            if(!out4) cout<<"error";

                            out4<<endl<<"--------------------"<<endl;
                            out4<<date<<endl<<endl;

                            string test{};
                            string s{};
                            
                        ////  making sure test variable is not empty ////
                            while(test=="")
                            {
                                cout<<"\nWhat test should be done on the patient "<<pid1<<" : "<<endl<<endl;
                                while(1)
                                {
                                    getline(cin>>ws,s);
                                    if(s == "over") break;
                                    if(test != "") test += ", ";
                                    test += s;
                                    out4<<s<<endl;
                                }
                            }
                            out4<<endl<<"--------------------"<<endl;
                            out4.close();

                        // Adding patient to lab_queue
                            out4.open("./queue/lab_queue/"+ date, ios::app);
                            if(!out4) cout<<"error";
                            out4<<token1<<" "<<pid1<<" "<<test<<endl;
                            out4.close();

                        // update the seek to next patient

                            rm_q(if_temp);        
                        }
                    }

                    else if(temp == 5)
                        return 3;

                    else if(temp == 6)
                        return 4;

                    else
                        continue;
                }
            }
            return 0;
        }
};
