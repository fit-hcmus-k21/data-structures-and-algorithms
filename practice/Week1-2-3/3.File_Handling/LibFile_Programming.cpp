#include "Examinee.h"

// check the field of a subject and assign score to subject
float checkScore(string token) {
    if (token == "") {
        return 0;
    } else {
        return stof(token);
    }
}

// split string by delimiter comma 
string splitWithComma(string &str) {
    int pos = str.find(',');
    if (pos != -1) {
        string token = str.substr(0, pos);
        str.erase(0, pos + 1);
        return token;
    } else {
        return str;
    }
}

// printf the information of a examinee
void outputExaminee (Examinee examinee) {
    cout << "ID: " << examinee.id << endl;
    cout << "Maths: " << examinee.maths << endl;
    cout << "Literature: " << examinee.literature << endl;
    cout << "Physics: " << examinee.physics << endl;
    cout << "Chemistry: " << examinee.chemistry << endl;
    cout << "Biology: " << examinee.biology << endl;
    cout << "History: " << examinee.history << endl;
    cout << "Geography: " << examinee.geography << endl;
    cout << "Civic Education: " << examinee.civic_education << endl;
    cout << "Foreign Language: " << examinee.foreign_language << endl;
}

// 1. Read the information of one examinee:
Examinee readExaminee (string line_info) {
    // declare examinee variable
    Examinee examinee;

    // split string with comma
    string token;

    // store data into examinee variable
    token = splitWithComma(line_info);
    examinee.id = token;

    // ignore full name
    token = splitWithComma(line_info);

    // split string with comma to get the score of each subject
    float subjects[11] = {0};
    for (int i = 0; i < 11; i++) {
        token = splitWithComma(line_info);
        subjects[i] = checkScore(token);
    }
    memcpy(&examinee.maths, subjects, sizeof(float) * 11);

    return examinee;
}

// 2. Read the information of all examinees:
vector <Examinee> readExamineeList(string file_name) {
    fstream fin(file_name, ios::in) ;

    // check whether opening file fail or not
    if (fin.fail()) {
        cout << "fail opening file" << endl;
        exit(225);
    }
    vector <Examinee> listExaminee;
    
    // ignore the first line of file
    string line_info;
    getline(fin, line_info);

    // read the information util end of file
    while ( ! fin.eof()) {
        getline(fin, line_info);
        Examinee examinee = readExaminee(line_info);
        listExaminee.push_back(examinee);
    }

    // check if the final examinee gotten from empty line
    if (listExaminee[listExaminee.size() - 1].id == "" ) {
        listExaminee.pop_back();
    }
    
    // close file
    fin.close();

    return listExaminee;
}

// 3. Write the total score of examinees to file
void writeScores(vector <Examinee> examinee_list, string out_file_name) {
    // open file 
    fstream fout(out_file_name, ios :: out);
    
    // check whether opening file success or not
    if (fout.fail()) {
        cout << "opening file not success " << endl;
        return;
    }

    // declare some necessary variable 
    double totalScore = 0;
    float BB = 0, KHTN = 0, KHXH = 0;

    // write header information in output file
    fout << "SBD BB KHTN KHXH" << endl;

    for (int i = 0; i < examinee_list.size(); i++) {
        // calculate 
        BB = examinee_list[i].maths + examinee_list[i].literature + examinee_list[i].foreign_language;
        KHTN = examinee_list[i].physics + examinee_list[i].chemistry + examinee_list[i].biology;
        KHXH = examinee_list[i].history + examinee_list[i].geography + examinee_list[i].civic_education;
        totalScore += examinee_list[i].maths + examinee_list[i].literature + examinee_list[i].foreign_language + KHTN + KHXH;
        
        // output to file
        fout << examinee_list[i].id << " " << BB << " " << KHTN << " " << KHXH << endl;
    }
 

    // write the total score to file 
    fout << "The total score: " << totalScore << endl ;

    // close file
    fout.close();
}

int main() {
    vector <Examinee> list_examinees;

    // read information from input file
    list_examinees = readExamineeList("data.txt");
    
    // write the total score to output file
    string out_file_name = "output.txt";
    writeScores(list_examinees, out_file_name);

    cout << "successfully" << endl;

    return 225;
}
