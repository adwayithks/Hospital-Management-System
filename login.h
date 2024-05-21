#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

class Login
{
    private:
        struct cred                    // credentials
        {
            string username;
            string password;
        }doctor,lab,office;

        string salt = "!&*)iamthe@%#&salt^here#$%^";

        string hasher(const string& password) 
        {
            hash<string> hasher;
            string saltedPassword = salt + password + salt;
            size_t hash = hasher(saltedPassword);
            return to_string(hash);
        }

        void fileInitialiser(string username,string password,string location)
        {
            ofstream outf{location};
            outf<<username<<endl;
            outf<<password<<endl;
        }

        void initialiser()
        {
        
        //creating login folder  
            if(!is_directory("login")) system("mkdir login");

        // Iniatialising doctor's password file
            ifstream inf{"./login/doctor"};

            if (!inf)
            {
                doctor.username = "doctor";
                doctor.password = hasher("nurse");
                fileInitialiser("doctor",doctor.password,"./login/doctor");
            }
            else
            {
                getline(inf, doctor.username);
                getline(inf, doctor.password);
            }
            inf.close();

            // Iniatialising lab's password file
            inf.open("./login/lab");
            if (!inf)
            {
                lab.username = "lab";
                lab.password = hasher("testing");
                fileInitialiser("lab",lab.password,"./login/lab");
            }
            else
            {
                getline(inf, lab.username);
                getline(inf, lab.password);
            }
            inf.close();

            // Iniatialising office's password file
            inf.open("./login/office");
            if (!inf)
            {
                office.username = "office";
                office.password = hasher("computer");
                fileInitialiser("office",office.password,"./login/office");
            }
            else
            {
                getline(inf, office.username);
                getline(inf, office.password);
            }
            inf.close();
        }

        string newPassword(string username, string oldPassword, string location)
        {
            for(int i{3};i>0;)
            {
                string s,s1;
                cout<<"\nenter new password (space not allowed): ";
                cin>>s;
                cout<<"\nre-enter new password : ";
                cin>>s1;
                if(s1==s)
                {
                    oldPassword = hasher(s1);
                    fileInitialiser(username,oldPassword,location);
                    cout<<"\n\npassword change successful\n";
                    break;
                }
                else
                {
                    i--;
                    cout<<"\nonly "<<i<<" attempt(s) remaining\n";
                    cout<<"The re-entered password doesn't match\n\n";
                    continue;
                }
            }
            system("stty echo");
            cout<<"login again\n";
            return oldPassword;
        }

    public:

        Login()
        {
            initialiser();
        }

        int loginManager()
        {
            cred temp;
            cout<<"\nenter username : ";
            cin>>temp.username;
            if(temp.username == doctor.username)
            {
                cout<<"\nenter password : ";
                system("stty -echo");
                cin>>temp.password;
                system("stty echo");
                if(hasher(temp.password) == doctor.password) return 1;
                else return 0;
            }
            else if(temp.username == lab.username)
            {
                cout<<"\nenter password : ";
                system("stty -echo");
                cin>>temp.password;
                system("stty echo");
                if(hasher(temp.password) == lab.password) return 2;
                else return 0;
            }
            else if(temp.username == office.username)
            {
                cout<<"\nenter password : ";
                system("stty -echo");
                cin>>temp.password;
                system("stty echo");
                if(hasher(temp.password) == office.password) return 3;
                else return 0;
            }
            else return 0;
        }

        void changePassword(string s)
        {
            cred temp;
            temp.username = s;
            if(temp.username == doctor.username)
            {
                cout<<"\nenter previous password : ";
                system("stty -echo");
                cin>>temp.password;
                if(hasher(temp.password) == doctor.password) 
                    doctor.password = newPassword("doctor",doctor.password,"./login/doctor");
                else
                {
                    cout<<"wrong password\n";
                    system("stty echo");
                    return;
                }
            }
            else if(temp.username == lab.username)
            {
                cout<<"\nenter previous password : ";
                system("stty -echo");
                cin>>temp.password;
                if(hasher(temp.password) == lab.password) 
                    lab.password = newPassword("lab",lab.password,"./login/lab");
                else
                {
                    cout<<"wrong password\n";
                    system("stty echo");
                    return;
                }
            }
            else if(temp.username == office.username)
            {
                cout<<"\nenter previous password : ";
                system("stty -echo");
                cin>>temp.password;
                if(hasher(temp.password) == office.password)
                    office.password = newPassword("office",office.password,"./login/office");
                else
                {
                    cout<<"wrong password\n";
                    system("stty echo");
                    return;
                }
            }
            else return;
        }
};