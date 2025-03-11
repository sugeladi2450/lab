#ifndef CLASS_H_
#define CLASS_H_

#include "Student.h"
#include <string>
#include <utility>
#include <vector>
class Student;

class Class {
private:
    std::vector<StudentWrapper> students;

public:
    const std::string name;
    const int point;
    Class(const std::string &name, const int point)
        : name(name), point(point) { }

    std::string toString() const;
    void addStudent(const Student &st);
    StudentWrapper& getStudentWrapper(const std::string &studentId);
    double getHighestScore();
    double getLowestScore();
    double getAvgScore();
    void saveScore(const std::string& filename);
    std::vector<StudentWrapper>& getStudents() {
        return students;
    };
};

#endif // CLASS_H_
