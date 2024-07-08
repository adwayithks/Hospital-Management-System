# HOSPITAL MANAGEMENT SYSTEM

## Table of Contents
- [Why this Project](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#why-this-project)
- [Prerequisites](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#prerequisites)
- [How to Install an run the Project](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#how-to-install-and-run-the-project)
- [How to use the Software](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#how-to-use-the-software)
- [How to use the Software](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#how-to-use-the-software)
  

---

### Why this project
 This is a project which can be deployed in hospitals for managing things like :-
 1) Creating tokens
 2) Creating unique Patient-id for Patients
 3) Maintaining the queue to the doctor
 4) Maintaining records of patients diagnosis, prescription, lab-reports
 5) Maintaining the queue to the lab from the doctor
 6) Creating lab reports

---

### Prerequisites
 1) This project will run only on linux based system as shell scripting has been used in different parts of the project.
    
 2) You also need to have libre office suite as it is the one used to create lab reports.
     - If you are using any other software instead of libre-office, then just change the code in the "lab.h" file, where I used libre-office specific commands.
 3) You also need nautilus.
     - If you use any other file manager just change the code a little bit in the "doctor.h" file by replacing nautilus with your file manager name.

---

### How to Install and run the Project 
 1) If you want to download this project in an x64 system you can [download the binary file](https://github.com/adwayithks/hospital_management_project/raw/main/hospital_management).
 2) Or you can clone this repo and compile the file named "hospital_management.cpp" and run the executable.

---

### How to use the software
 1) This software has 3 acting agents namely the doctor, office, lab-assistant.
 2) When you run the software, It will ask for login, the default logins are as follows :
    - Doctor :- username : doctor , password : nurse
    - Office :- username : office , password : computer
    - Lab    :- username : lab    , password : testing
 
 3) Btw while you type the password it won't show in the terminal. 
 4) The password for any agent can be changed by the agent by the agent itself after logging in.
 5) Everything in this system is saved in files so that no need to worry about unsaved data due to abrupt program shut down or anything.
 6) Everything is recorded including the queue of each day, the lab queue, the patient details, diagnosis and prescription history, lab reports etc.
 7) In the queue's and everything the patients name is not used instead the patient id (pid) is used.
 8) We also maintain a hidden file which maintains the patient id to patient name matching, which can be only accessed by the administrator of the system.
 
 9) Now let's look at the first agent say office in detail :
    - This is how the menu of an office assistant looks :-
       
       ![image](https://github.com/adwayithks/hospital_management_project/assets/132866560/fee0206e-c7a8-4fa8-87ff-5cfd9a4d0da8)
       
       - The office clerk can do the following :-
       - Create the details file of the patient
       - Create a patient id (pid) to a new patient visiting the hospital.
       - Add the patient to the doctor's queue.

         ![image](https://github.com/adwayithks/hospital_management_project/assets/132866560/e464f348-3929-4ef6-90b3-e8adc0e01464)
         
       - While creating a new token, it will ask us if the patient has a pid
         - If yes we can just enter the patient id.
         - Else we can say no, and it will ask us about some patient details, we can enter them and then it will give us a patient id, and also generate a token for the patient.

  7) Now let's look at the next agent say doctor in detail :
     - This is how the menu of doctor looks :-
     
       ![image](https://github.com/adwayithks/hospital_management_project/assets/132866560/2924a25e-c0ac-457f-8a7e-5a55288c3df7)

       - The doctor can see the list of first few token holders directly in his view.
       - Here we have the following options :-
         - Diagnose             :- Writes the disease of the patient into a text file in the patients directory
         - Prescribe            :- Writes the medicines and dosage into another text file in the patients directory
         - See patients history :- Shows the doctor the patients previous diagnosis, prescription, and lab reports
         - Send to lab          :- This allows the doctor to push the patients to the lab queue after specifying the tests to be done
         - Change Password      :- With this the doctor can change his password
         - Logout               :- Doctor can logout
         - Refresh              :- This refreshes the screen of the doctor incase any new tokens were added
        
       - If we choose any of the first 4 options the doctor can choose any patient from the first 5 shown in the token display.
       - It is done to give flexibility to the doctor, in case a patient is not present, or to give preference to senior citizens or any other unforeseen cases.
       - Whenever writing diagnosis, prescription or the tests which should be done on the patient, the doctor can write multiple lines, and after completing all the writing he can type "over" in a new line and this stops the fetching of characters from the input stream, and all the lines before this will be saved to a text file.

  8) Now let's look at the next agent lab in detail :
     - This is how the menu of lab incharge looks :-

       ![image](https://github.com/adwayithks/hospital_management_project/assets/132866560/87df790c-91d1-43ce-a69c-01dcbb15adfa)

       - Here we can see the token number, the patient id and the tests to be done on the screen.
       - Here we have the following options :-
         - Generate Report :- With this we can generate the lab report for the patient
         - Send to doctor  :- This helps us to push a patient to the doctor queue after performing all tests.
         - Change password :- change password
         - Logout          :- logout
         - Refresh         :- Refreshes the screen and includes new patients who were pushed to the queue.
        
       - If we chose "Generate report" option we should specify the pid and test to be done on the patients, this is kept like this for flexibility.
       - And if we chose "Send to doctor" option we should chose a position from 1 to 5, this is to select a patient from the onscreen display to send to the doctor.

---

### Directory Structure used in the program (Incase you want to know how the filesystem is organised)

![image](https://github.com/adwayithks/hospital_management_project/assets/132866560/2018f4ee-8a0e-4abf-8a82-38a9071ed7bc)


         

   



