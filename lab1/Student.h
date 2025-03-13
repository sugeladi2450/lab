#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <iostream>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:
    Degree degree;
    std::string name,year;

protected:
  std::vector<Class*> classes;
public:
    const std::string id;
    Student(const std::string &id,const std::string &name,const std::string &year,Degree degree):id(id),name(name),year(year),degree(degree){}
    Student(){}
    Student(const Student &other):id(other.id),name(other.name),year(other.year){}
    virtual double getGpa() = 0;
    virtual double getAvgScore() = 0;
    std::string toString() const;
    void addClass(Class *c);
    bool AllScoresInvalid(const std::vector<Class*>& classes) const;

};

// TODO: implement class Graduate.
class Graduate:public Student {
  public:
    Graduate(const std::string &id,const std::string &name,const std::string &year):Student(id,name,year,graduate){}
    Degree degree = graduate;
    double getGpa() override;
    double getAvgScore() override;

};
// TODO: implement class Undergraduate.
class Undergraduate:public Student{
public:
    Undergraduate(const std::string &id,const std::string &name,const std::string &year):Student(id,name,year,undergraduate){}
    Degree degree = undergraduate;
    double getGpa() override;
    double getAvgScore() override;
};

class StudentWrapper {
private:
    const Student &student;
    double score = -1.0;//Invalid Score;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &id, const Student &student):id(id),student(student) {}

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Wrong Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};


#endif // STUDENT_H_
