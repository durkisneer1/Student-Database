#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>  
#include <cstdlib>  

struct Student {
    std::string name;
    std::string major;
};


bool assignNames(std::map<std::string, Student> &studentMap) {
    std::ifstream nameFile("../resources/names.txt");
    if (!nameFile.is_open()) {
        return false;
    }
    std::string name;
    while (getline(nameFile, name)) {
        Student newStudent;
        newStudent.name = name;
        studentMap[name] = newStudent;
    }
    nameFile.close();
    return true;
}


int main() {
    srand(time(nullptr));

    std::map<std::string, Student> studentMap;
    if (!assignNames(studentMap)) {
        std::cout << "Failed to open names file.\n";
        return 3;
    }

    std::vector<std::string> majorList = {"Computer Science", "Business", "Culinary", "Nursing", "Philosophy",
                                          "Criminal Justice"};
    std::map<std::string, std::vector<std::string>> courseList;

    // Courses for one semester
    courseList[majorList[0]] = {"Calculus", "Linear Algebra", "Data Structures and Algorithms", "Discrete Mathematics"};
    courseList[majorList[1]] = {"Statistics", "Economics", "Marketing", "Financing"};
    courseList[majorList[2]] = {"Gastronomy", "Nutrition", "Marketing", "Sanitation and Safety"};
    courseList[majorList[3]] = {"Anatomy", "Biology", "Physical Education", "Statistics"};
    courseList[majorList[4]] = {"Ancient Philosophy", "Ethics", "Metaphysics", "Epistemology"};
    courseList[majorList[5]] = {"Administration", "Ethics", "Eyewitness Testimony", "Constitutional Law"};
    for (auto& student: studentMap) {
        int randomIndex = rand() % courseList.size();
        std::string chosenMajor = majorList[randomIndex];
        student.second.major = chosenMajor;
    }

    std::cout << "\nEnter 'close' to exit.";
    std::string inputName;
    bool searching = true;
    while (searching) {
        std::cout << "\nEnter student name:";
        getline(std::cin, inputName);
        transform(inputName.begin(), inputName.end(), inputName.begin(), ::toupper);
        if (inputName == "CLOSE") {
            searching = false;
        } else if (studentMap.find(inputName) == studentMap.end()) {
            std::cout << "Student Not Found. Try again.\n";
        } else {
            Student searchStudent = studentMap[inputName];
            std::cout << "Name: " << searchStudent.name << "\nMajor: " << searchStudent.major << "\n";
        }
    }

    return 0;
}
