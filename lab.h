#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class Lab
{
    private:
        int lab_seek{};
        int doctor_push{};
        vector<string> lab_q{};
    
    public:

        Lab(string date)
        {
            ifstream inf{"./queue/lab_queue/.lab_seek"};
            if(!inf)
            {
                ofstream outf{"./queue/lab_queue/.lab_seek"};
                outf<<date<<endl;
                outf<<0<<endl;
                lab_seek = 0;
            }
            else
            {
                string seek1{}, seek_date{};
                inf>>seek_date;

                if(seek_date != date) lab_seek = 0;
                else 
                {
                    inf>>seek1;
                    lab_seek = stoi(seek1);
                }
            }
        }

        int labFn(string date)
        {
            lab_q.clear();
            // int lab_temp {lab_seek};
            system("clear");
            cout<<"\n\nwelcome Lab Assistant"<<endl<<endl;

            ////  creating a temp queue file to save temporarily  ////

            ifstream if_temp{"./queue/lab_queue/.lab_temp_q"};
            ofstream of_temp;
            if(!if_temp)
            {
                of_temp.open("./queue/lab_queue/.lab_temp_q");
                if_temp.open("./queue/lab_queue/.lab_temp_q");
            }
            of_temp.close();
            
            while(1)
            {
                string token, pid, test;
                system("clear");
                cout<<"\ntoken no.     patient id \t test\n\n";
                ifstream inf{"./queue/lab_queue/"+date};
                inf.seekg(lab_seek);

                of_temp.open("./queue/lab_queue/.lab_temp_q", ios::app);
                string stuff{};
                while(getline(if_temp,stuff))
                {
                    lab_q.push_back(stuff);
                }
                if_temp.clear();

                while(lab_q.size()<5 && inf>>token)
                {
                    inf>>pid;
                    getline(inf,test);
                    string pusher = " "+token+"\t\t"+pid+"\t\t"+test;
                    lab_q.push_back(pusher);
                    of_temp<<pusher<<endl;
                    lab_seek += token.size()+pid.size()+test.size()+2; //this is 2 instead of 3 bcoz 
                                                                       //the space before test is included along with test
                    token.clear();  // it is similar to : token = "";
                    pid.clear();
                    test.clear();
                }

                ofstream of{"./queue/lab_queue/.lab_seek"};
                of<<date<<endl;
                of<<lab_seek<<endl;

                for(int i{};i<lab_q.size() && i<5;i++)
                {
                    cout<<lab_q[i]<<endl;
                }
                cout<<endl<<"---------------------------------------"<<endl<<endl;

                cout<<"\n\nOptions : \n";
                cout<<"\n1- Generate report";
                cout<<"\n2- Send to Doctor";
                cout<<"\n3- Change password";
                cout<<"\n4- Logout";
                cout<<"\n5- Refresh\n\n";
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
                
                if(temp == 1)
                {
                    cout<<endl<<"What is the pid of the patient : ";
                    string pid1{};
                    getline(cin,pid1);
                    cout<<pid1;
                    cout<<endl<<"What test should be performed on the patient : ";
                    string test{};
                    getline(cin,test);
                    string location = "./patient/"+pid1+"/details";
                    ifstream if_check{location};
                    if(!if_check)
                    {
                        cerr<<"Enter valid pid ";
                        continue;
                    }
                    ofstream of4{"./.report"};
                    if(!of4)
                    {
                        cout<<"nowork";
                    }
                    of4<<"#!/bin/bash"<<endl<<endl;
                    of4<<"date="<<"\""<<date<<"\""<<endl;
                    of4<<"test="<<"\""<<test<<"\""<<endl;
                    of4<<"pid="<<"\""<<pid1<<"\""<<endl;
                    of4<<"location=\"./patient/${pid}/lab-reports\""<<endl;
                    of4<<"d_location=\"./patient/${pid}\""<<endl;
                    of4<<endl<<"# Making directory if it does not already exist"<<endl<<"mkdir -p \"$location\""<<endl;
                    of4<<endl<<"# Convert the text file to .odt using LibreOffice"<<endl<<"libreoffice --headless --convert-to odt \"${d_location}/details\" --outdir \"$location\""<<endl;
                    of4<<endl<<"#rename-file"<<endl<<"mv \"${location}/details.odt\" \"${location}/lab_${date}_${test}.odt\""<<endl;
                    of4<<endl<<"# Opening the file in libre office"<<endl<<"libreoffice \"${location}/lab_${date}_${test}.odt\""<<endl;
                    of4.close();
                    system("mv .report .report.sh");
                    system("./.report.sh");

                }
                else if(temp == 2)
                {
                    cout<<"\n\nEnter the position of the patient in the queue : ";
                    int position{};
                    cin>>position;

                    if(position<=lab_q.size())
                    {
                        ofstream writeout{"./queue/doctor_queue/.doc_temp_q",ios::app};
                        writeout<<lab_q[position-1]<<endl;
                        lab_q.erase(lab_q.begin()+position-1);
                        writeout.close();

                        writeout.open("./queue/lab_queue/.lab_temp_q");
                        for(int i{};i<lab_q.size();i++)
                        {
                            writeout<<lab_q[i]<<endl;
                        }
                        writeout.close();
                    }
                    else cout<<"invalid position entered";                    
                }
                else if(temp == 3) return 3;
                else if(temp == 4) return 4;
            }
            return 0;
            
        }
};