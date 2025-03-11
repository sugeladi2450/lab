#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printScoreStats();
    void printGrade();
    void saveScore();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");
    if (!stfile.is_open()) {
        cerr << "Failed to open Students.txt" << endl;
        return;
    }

    while (getline(stfile, line)) {
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;

        // The bufv vector stores each column in the line.
        bufv.clear();
        // Split the line into columns.
        //   pos1: beginning of the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';',pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);


        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
    ifstream clfile("./Classes.txt");
    if (!clfile.is_open()) {
        cerr << "Failed to open Classes.txt" << endl;
        return;
    }
    while(getline(clfile,line)){
        if (line.empty())
          continue;
        if (line[0] == '#')
          continue;
        int pos = line.find(':');
        clsname = line.substr(pos+1,string::npos);

        getline(clfile, line);
        pos = line.find(':');
        point = stoi(line.substr(pos+1,string::npos));
        cl = new Class(clsname,point);

        while(getline(clfile, line)){
          if (line.empty())
            break;
          for(auto &student : studentVec) {
            if(student->id == line){
              student->addClass(cl);
              cl->addStudent(*student);
              break;
            }
          }
        }
        classVec.push_back(cl);
    }
    clfile.close();
}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printScoreStats().
    string sbuf;

    while (true) {
      cout << "Please input the class name (or input a q to quit): ";
      cin >> sbuf;
      if(sbuf == "q")
        break;

      Class *cl = nullptr;
      for (auto & it : classVec) {
            if (it->name == sbuf) {
                cl = it;
                break;
            }
      }
      if (cl == nullptr) {
            cerr << "No Match Class" << endl;
            continue;
      }
      while (true) {
          cin >> sbuf;
          if (sbuf == "q")
              break;

          int pos = sbuf.find(',');
          if (pos == string::npos) {
              cerr << "No Valid Score" << endl;
              continue;
          }
          string  studentId;
          double studentScore;
          try {
              studentId = sbuf.substr(0,pos);
              studentScore = stod(sbuf.substr(pos+1,string::npos));

              if(studentScore > 100 || studentScore < 0){
                  cerr<<"Wrong Score" << endl;
                  continue;
              }

              Student *st=nullptr;
              for (auto & it : studentVec) {
                  if (studentId == it->id) {
                      st = it;
                      break;
                  }
              }
              if (st == nullptr) {
                  cerr << "No Match Student" << endl;
                  continue;
              }


              StudentWrapper &sw = cl->getStudentWrapper(studentId);
              sw.setScore(studentScore);

      } catch (const invalid_argument &) {
          cerr << "No Valid Score" << endl;  continue;
      } catch (const out_of_range &) {
          cerr << "Out of Range" << endl;  continue;
      }
          catch (const char *e) {
              cerr << e << endl;   continue;
          }
         catch (...) {
            cerr << "Unknown Error" << endl;  continue;
        }
      }
    }
}

void AppX::printScoreStats()
{
    string sbuf;
    Class* cl = nullptr;
    double highest, lowest, avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
          break;

        cl = nullptr;
        for (auto & it : classVec) {
            if (it->name == sbuf) {
                cl = it;
                break;
            }
        }
        if (cl == nullptr) {
            cerr << "No Match Class" << endl;
            continue;
        }

        try {
            highest = cl->getHighestScore();
            lowest = cl->getLowestScore();
            avg = cl->getAvgScore();

            cout << cl->toString() << endl;
            cout << fixed << setprecision(2)<< "Highest,Lowest,Avg = " << highest << "," << lowest << "," << avg << endl;
        } catch (string e) {
            cerr << e << endl;
        } catch (char const* e){
            cerr << e << endl;
        } catch (...) {
            cerr << "Unknown exception caught" << endl;
        }
    }
}

void AppX::printGrade()
{
    // TODO: implement printGrade.
    // Hint: Take a look at printScoreStats().
    string sbuf;

    while(true){
        cin>>sbuf;
        if(sbuf == "q") break;
        Student *st=nullptr;
        for (auto & it : studentVec) {
            if (sbuf == it->id) {
                st = it;
                break;
            }
        }
        if(st == nullptr){
            cerr<<"No Match Student\n";
            continue;
        }
        cout<<st->toString();
        cout<< fixed << setprecision(2) << "GPA,AVG = " << st->getGpa() << ',' << st->getAvgScore() << endl;
    }
}

void AppX::saveScore() {
    // TODO: implement saveScore.
    ofstream outfile("./scores.txt");
    if (!outfile.is_open()) {
        cerr << "Failed to open scores.txt" << endl;
        return;
    }
    for (auto &cl : classVec) {
        outfile << cl->name <<endl;
        for (auto& sw : cl->getStudents()) {
            if (sw.getScore() != -1.0) {
                outfile << sw.id << "," << sw.getScore()<<endl;
            }
        }
    }
    outfile.close();

}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute score statistics of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printScoreStats();
        } else if (cmd == 'g') {
            printGrade();
        } else if (cmd == 'q') {
            saveScore();
            break;
        } else {
            cerr << "Invalid Command\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
