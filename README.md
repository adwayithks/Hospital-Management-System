# HOSPITAL MANAGEMENT SYSTEM

## Table of Contents
- [Why this Project](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#why-this-project)
- [Prerequisites](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#prerequisites)
- [How to Install an run the Project](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#how-to-install-and-run-the-project)
- [How to use the Software](https://github.com/adwayithks/hospital_management_project?tab=readme-ov-file#how-to-use-the-software)
  

---

### Why this project
 This is a project which can be deployed in hospitals for managing things like :-
 1) Creating tokens
 2) Creating unique Patient-id for Patients
 3) Maintaining the queue to the doctor
 4) Creating records of patients diagnosis, prescription, lab-reports
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
 1) This software has 3 acting agents namely , the doctor, the office, the lab-assistant.
 2) When you run the software, It will ask for login, the default logins are as follows :
    - Doctor :- username : doctor , password : nurse
    - Office :- username : office , password : computer
    - Lab    :- username : lab    , password : testing
 
 3) Btw while you type the password it won't show in the terminal. 
 4) The password for any agent can be changed by the agent by the agent itself after logging in.
 
 5) Now let's look at the first agent say office in detail :
    - The office clerk can do the following :-
      - Create the details file of the patient
      - Create a patient id (pid) to a new patient visiting the hospital.
      - Add the patient to the doctor's queue.
 
 This is how the menu of an office assistant looks :- 
 
 ![image](https://github.com/adwayithks/hospital_management_project/assets/132866560/e464f348-3929-4ef6-90b3-e8adc0e01464)

    - It will ask us if the patient has a pid
      - If yes we can just enter the patient id.
      - Else we can say no, and it will ask us about some patient details, we can enter them and then it will give us a patient id, and also generate a token for the patient.


