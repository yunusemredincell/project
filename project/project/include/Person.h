#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Person
{
protected:
    string id, name, surname, nationallity, gender;
    int age, iqPoint, mentalPoint, healthPoint, acculturationPoint;
    float personPoint;

public:
    void createPerson();
    void createID();
    void addFile();
    void setData(string name, string surname, int age, string nationallity, string gender, string id);
    int filter(Person p);
    string getName();
    string getSurname();
    int getAge();
    string getNationallity();
    string getGender();
    string getID();
    Person();
};

#endif