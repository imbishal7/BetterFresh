/* ***************************************************************
* Objectives/Description: A ticket management system that could be an alternative to one used in Fresh Food Company at the USM.
*                         Supports two plans currently: Unlimited Plan and Limited Plan. Plan features might not be what Fresh Food offer.
* Input: student or guest check-in. Student Id for students and card details for outsiders.
* Output: Status of the account for students. Confirmation for purchase or entrance, or denial of entrance.
* ***************************************************************
*/

#include "ticket.h"
#include <fstream>
#include <sstream>

using namespace std;


void student_entrance();
void guest_entrance();
vector <vector <string>> read_csv(string filename);
void save_csv(vector<vector<string>>& data, string filename);


/* *************************************************
* Function Name: main
* Function Description: Shows the menu for students and guests.
* Function Parameters: NA
* What is returned, if anything: NA
* *************************************************
*/
int main(){
    char response = 'q';

    cout << 
    
        "  ██████╗ ███████╗████████╗████████╗███████╗██████╗     ███████╗██████╗ ███████╗███████╗██╗  ██╗\n"
        "  ██╔══██╗██╔════╝╚══██╔══╝╚══██╔══╝██╔════╝██╔══██╗    ██╔════╝██╔══██╗██╔════╝██╔════╝██║  ██║\n"
        "  ██████╔╝█████╗     ██║      ██║   █████╗  ██████╔╝    █████╗  ██████╔╝█████╗  ███████╗███████║\n"
        "  ██╔══██╗██╔══╝     ██║      ██║   ██╔══╝  ██╔══██╗    ██╔══╝  ██╔══██╗██╔══╝  ╚════██║██╔══██║\n"
        "  ██████╔╝███████╗   ██║      ██║   ███████╗██║  ██║    ██║     ██║  ██║███████╗███████║██║  ██║\n"
        "  ╚═════╝ ╚══════╝   ╚═╝      ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝\n"

    << endl;
    do
    {
        cout << "Enter s for student, g for guest, & q to quit:";
        cin >> response;

        if (response == 's'){
            student_entrance();
        }
        else if(response == 'g'){
            guest_entrance();
        }
    }
    while(response!='q');
    

    return 0;
}


/* *************************************************
* Function Name: student_entrance
* Function Description: allows students to enter their details and use or deny their swipes
* Function Parameters: NA
* What is returned, if anything: NA
* *************************************************
*/
void student_entrance(){
    string wid;
    cout << "Enter Your Student ID: ";
    cin >> wid;

    vector<vector<string>> student_data;
    student_data = read_csv("student_data.csv");

    string name, plan, weekly_available, daily_available, guest_swipes, dining_dollars, last_swipe;

    int student_index;

    for (int i=0; i< size(student_data); i++){

        if (student_data[i][0] == wid){
            student_index = i;
            break;
        }
        else{
            student_index = -1;
        }
    }

    if (student_index != -1){
        vector<string> row = student_data[student_index];

        wid = row[0];
        name = row[1];
        plan = row[2];
        weekly_available = row[3];
        daily_available = row[4];
        guest_swipes = row[5];
        dining_dollars = row[6];
        last_swipe = row[7];

        Student student = Student(  wid,
                                    name,
                                    plan,
                                    weekly_available,
                                    daily_available,
                                    guest_swipes,
                                    dining_dollars,
                                    last_swipe);
        student.swipe();
        student.get_status();

        row = student.vectorize();
        student_data.at(student_index) = row;
        save_csv(student_data, "student_data.csv");
    }
    else{
        cout << "Student is not in the database." << endl;
    }
    
}


/* *************************************************
* Function Name: guest_entrance
* Function Description: allows guests to enter the Fresh using their payment card.
* Function Parameters: NA
* Paramter type, name and use: NA
* What is returned, if anything: NA
* *************************************************
*/

void guest_entrance(){
    long number;
    string uname;

    cout << "Enter Your Card Number: ";
    cin >> number;
    cout << "Enter Your Name: ";
    cin >> uname;

    Outsider(number,uname).make_purchase();
}


/* *************************************************
* Function Name: read_csv
* Function Description: reads the given csv file into a 2D vector.
* Function Parameters: filename
* Paramter type, name and use: string
* What is returned, if anything: vector
* *************************************************
*/
vector<vector<string>> read_csv(string filename){
    ifstream input_file(filename);

    if (!input_file) {
        cout << "Failed to open the file." << endl;
    }

    vector<vector<string>> data; 
    string line;

    while (getline(input_file, line)) { 

        istringstream iss(line);
        vector<string> lineData;
        string item;

        while(getline(iss, item, ',')) {
            lineData.push_back(item);
        }
        data.push_back(lineData);
    }

    input_file.close(); 
    return data;
    
}

/* *************************************************
* Function Name: save_csv
* Function Description: saves the given 2D vector into csv file
* Function Parameters: data, filename
* Paramter type, name and use: vector data, string filename
* What is returned, if anything: NA
* *************************************************
*/
void save_csv(vector<vector<string>>& data, string filename) {
    ofstream output_file(filename);

    if (!output_file) {
        cout << "Failed to open the file for writing." << endl;
        return;
    }
    for (const auto& line : data) { 

        for (auto it = line.begin(); it != line.end(); ++it) {
            output_file << *it;

            if (it != line.end() - 1) {
                output_file << ",";
            }
        }
        output_file << endl;
    }

    output_file.close();
}

