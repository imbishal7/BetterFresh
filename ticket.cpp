
#include "ticket.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


void student_entrance();
void guest_entrance();
vector <vector <string>> read_csv(string filename);
void saveToFile(vector<vector<string>>& data, string filename);


int main(){
    char response = 'q';
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



void student_entrance(){
    string wid;
    cout << "Enter Your Student ID: ";
    cin >> wid;

    vector<vector<string>> student_data;
    student_data = read_csv("student_data.csv");

    string name, plan, weekly_available, daily_available, guest_swipes, dining_dollars, last_swipe;

    int student_index;

    for (int i=0; i< sizeof(student_data); i++){
        if (student_data[i][0] == wid){
            student_index = i;
        }
        else{
            student_index = -1;
        }
    }

    if (student_index != 0){
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
    }
    else{
        cout << "Student is not in the database." << endl;
    }
    


}

void guest_entrance(){
    long number;
            string uname;

            cout << "Enter Your Card Number: ";
            cin >> number;
            cout << "Enter Your Name: ";
            cin >> uname;

            Outsider(number,uname).make_purchase();
}


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

void saveToFile(vector<vector<string>>& data, string filename) {
    ofstream output_file(filename);

    if (!output_file) {
        cout << "Failed to open the file for writing." << endl;
        return;
    }
    for (const auto& line : data) { 

        for (auto it = line.begin(); it != line.end(); ++it) {
            output_file << *it;

            if (it != line.end() - 1) {
                output_file << ", ";
            }
        }
        output_file << endl;
    }

    output_file.close();
}

