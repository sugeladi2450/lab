#include "Class.h"
#include <string>
#include <vector>
#include "Student.h"
#include <sstream>
#include<iostream>
#include<fstream>

std::string Class::toString() const {
    std::ostringstream oss;
    oss << "Class Information:"
        << "\n\tname: " << name
        << "\n\tpoint: " << point
        << std::endl;
    return oss.str();
}

void Class::addStudent(const Student& st) {
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper& Class::getStudentWrapper(const std::string& studentId) {
    for (auto& sw : students) {
        if (sw.id == studentId)
            return sw;
    }
    throw "No Match Student";
}

double Class::getHighestScore() {
    // TODO implement getHighestScore
    if (students.empty()) {
        return -1.0;
    }
    double highestScore = students[0].getScore();
    for (std::vector<StudentWrapper>::iterator it = students.begin();it != students.end();++it){
        if (it->getScore() == -1.0) continue;
        if (it->getScore() >highestScore){
          highestScore = it->getScore();
        }
    }
    return highestScore;
}

double Class::getLowestScore() {
    // TODO implement getLowestScore
    if (students.empty()) {
        return -1.0; //
    }
    double lowestScore = students[0].getScore();
    for (std::vector<StudentWrapper>::iterator it = students.begin();it != students.end();++it){
        if (it->getScore() == -1.0) continue;
        if (it->getScore() <lowestScore){
           lowestScore = it->getScore();
        }
    }
    return lowestScore;;
}  

double Class::getAvgScore() {
    // TODO implement getAvgScore
    double aveScore = 0.0,totalScore = 0.0,n=0;
    for (int i = 0; i < students.size(); ++i){
        if (students[i].getScore() != -1.0) {
            totalScore += students[i].getScore();
            n++;
        }
    }
    aveScore = totalScore/n;
    return aveScore;
}

void Class::saveScore(const std::string& filename) {
    // TODO implement saveScore
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Can't Open File" << std::endl;
        return;
    }
    outfile << name << std::endl;
    for (const auto &sw : students) {
        if (sw.getScore() != -1.0) {
            outfile << sw.id << "," << sw.getScore() << std::endl;
        }
    }
    outfile.close();
}
