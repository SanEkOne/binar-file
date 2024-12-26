#include <iostream>
#include <fstream>

using namespace std;

class Student {
    string Name;
    int Age;
    double AverageMark;

public:

    void SetInfo(const string& name, int age, double averageMark) {
        Name = name;
        Age = age;
        AverageMark = averageMark;
    }

    void PrintInfo() const {
        cout << "Name: " << Name << endl;
        cout << "Age: " << Age << endl;
        cout << "Average Mark: " << AverageMark << endl;
    }

    void SaveToBinaryFile(const string& fileName) const {
        ofstream file(fileName, ios::binary);
        size_t nameLength = Name.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(Name.c_str(), nameLength);
        file.write(reinterpret_cast<const char*>(&Age), sizeof(Age));
        file.write(reinterpret_cast<const char*>(&AverageMark), sizeof(AverageMark));
        file.close();
    }

    void LoadFromBinaryFile(const string& fileName) {
        ifstream file(fileName, ios::binary);
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        Name.resize(nameLength);
        file.read(&Name[0], nameLength);
        file.read(reinterpret_cast<char*>(&Age), sizeof(Age));
        file.read(reinterpret_cast<char*>(&AverageMark), sizeof(AverageMark));
        file.close();
    }
};

int main() {
    Student student;

    student.SetInfo("Alex", 17, 9.2);
    student.SaveToBinaryFile("StudentInfo");

    Student loadedStudent;
    loadedStudent.LoadFromBinaryFile("StudentInfo");
    loadedStudent.PrintInfo();

    return 0;
}
