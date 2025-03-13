#include "Class.h"
#include <string>
#include <vector>
#include "Student.h"
#include <sstream>
#include<fstream>
#include<algorithm>
#include<iomanip>

bool allScoresInvalid(const std::vector<StudentWrapper>& students) {
    for (auto &student : students) {
        if (student.getScore() != -1.0) {
            return false;
        }
    }
    return true;
}

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
    for (std::vector<StudentWrapper>::iterator it = students.begin();
            it != students.end();
            ++ it) {
        if (it->id == studentId)
            return *it;
            }
    throw "No Match Student!";
}

double Class::getHighestScore() {
    // TODO implement getHighestScore
    if (allScoresInvalid(students) || students.empty()) {
         throw "No Valid Score";
    }
    double highestScore;
    for (auto &student : students) {
        if (student.getScore() != -1.0) {
            highestScore = student.getScore();
            break;
        }
    }
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
    if (allScoresInvalid(students) || students.empty()) {
        throw "No Valid Score";
    }
    double lowestScore;
    for (auto &student : students) {
        if (student.getScore() != -1.0) {
            lowestScore = student.getScore();
            break;
        }
    }
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
    if (allScoresInvalid(students) || students.empty()) {
        throw "No Valid Score";
    }
    double aveScore = 0.0,totalScore = 0.0;
    int n = 0;
    for (int i = 0; i < students.size(); ++i){
        if (students[i].getScore() != -1.0) {
            totalScore += students[i].getScore();
            n++;
        }
    }
    aveScore = totalScore / n;
    return aveScore;
}

void Class::saveScore(const std::string& filename) {
    // TODO implement saveScore
    std::ofstream outfile(filename);
    outfile << name << std::endl;
    for (const auto &sw : students) {
        if (sw.getScore() != -1.0) {
            outfile << sw.id << "," << std::fixed << std::setprecision(2) << sw.getScore() << std::endl;
        }
    }
}
