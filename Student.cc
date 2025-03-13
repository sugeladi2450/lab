#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

bool Student::AllScoresInvalid(const std::vector<Class*>& classes) const {
    for (auto &cl : classes) {
        if (cl->getStudentWrapper(id).getScore() != -1.0) {
            return false;
        }
    }
    return true;
}

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
}

// TODO: implement functions which are declared in Student.h.
double Graduate::getGpa() {
    if (classes.empty() || AllScoresInvalid(classes)) return 0.0;

    double total_point = 0.0,total_score = 0.0,gpa=0.0;

    for (auto it : classes) {

            double score = it->getStudentWrapper(id).getScore();
            if (score == -1.0)  continue;
            double gp;
            switch ((int)score / 10) {
                case 10: gp = 4.0; break;
                case 9: gp = 4.0; break;
                case 8: gp = 3.5; break;
                case 7: gp = 3.0; break;
                case 6: gp = 2.5; break;
                default: gp = 2.0; break;
            }
            total_point += it->point;
            total_score += gp * it->point;
    }

    gpa = total_score / total_point;
    return gpa;
}

double Graduate::getAvgScore() {
    if (classes.empty() || AllScoresInvalid(classes)) return 0.0;

    double total_score = 0.0;
    double total_point = 0.0;
    for(int i = 0;i<classes.size();i++) {
        if (classes[i]->getStudentWrapper(id).getScore() != -1.0) {
            total_score += classes[i]->getStudentWrapper(id).getScore() * classes[i]->point;
            total_point += classes[i]->point;
        }
    }
    return total_score/total_point;

}
double Undergraduate::getGpa(){
    if (classes.empty() || AllScoresInvalid(classes)) return 0.0;

    double total_point = 0.0,total_score = 0.0,gpa = 0.0;
    for (int i = 0;i<classes.size();i++) {
        if (classes[i]->getStudentWrapper(id).getScore() == -1.0) continue;

        total_score += classes[i]->getStudentWrapper(id).getScore()/20 * classes[i]->point;
        total_point += classes[i]->point;
    }
    gpa = total_score / total_point;
    return gpa;
}
double Undergraduate::getAvgScore(){
    if (classes.empty() || AllScoresInvalid(classes)) return 0.0;

    return Undergraduate::getGpa() * 20;
}

void Student::addClass(Class *c) {
    for (auto& cls : classes) {
        if (cls == c) return;
    }
    classes.push_back(c);
}
