#include "Guilty.h"

Guilty::Guilty() // Default Constructor
{
}

Guilty::Guilty(Employee &source) // Copy constructor from Employee class. (There is a composition between them)
{
    name = source.getName();
    surname = source.getSurname();
    age = source.getAge();
    nationallity = source.getNationallity();
    gender = source.getGender();
    id = source.getID();
}

Guilty::Guilty(Refugee &source) // Copy constructor from Refugee class. (There is a composition between them)
{
    name = source.getName();
    surname = source.getSurname();
    age = source.getAge();
    nationallity = source.getNationallity();
    gender = source.getGender();
    id = source.getID();
}

void Guilty::setCrime(int migrantType) // According to the migrant type (refugee or employee) set the crimes. (Refugees dont have these crime types:  Money Laundering and Tax Evuation).
{
    int option, j = 0;
    cout << "\n";
    cout << ++j << "- Making Robbery" << endl;
    cout << ++j << "- Commit Murder" << endl;
    cout << ++j << "- Terror Activity" << endl;
    cout << ++j << "- Drug Dealing" << endl;
    cout << ++j << "- Disturb Environment" << endl;
    cout << ++j << "- Injured Fight" << endl;
    if (migrantType == 1)
    {
        cout << ++j << "- Tax Evasion" << endl;
        cout << ++j << "- Money Laundering" << endl;

        cout << "Choose crime type: ";
        cin >> option;

        while (option < 1 || option > 8)
        {
            cout << "You entered invalid choice!! Please again enter your choose: ";
            cin >> option;
        }
    }
    else
    {
        cout << "Choose crime type: ";
        cin >> option;

        while (option < 1 || option > 6)
        {
            cout << "You entered invalid choice!! Please again enter your choose: ";
            cin >> option;
        }
    }

    // Assigning the crimes according to the user choices.
    if (option == 1)
    {
        crime = "Making Robbery";
    }
    else if (option == 2)
    {
        crime = "Commit Murder";
    }
    else if (option == 3)
    {
        crime = "Terror Activity";
    }
    else if (option == 4)
    {
        crime = "Drug Dealing";
    }
    else if (option == 5)
    {
        crime = "Disturb Environment";
    }
    else if (option == 6)
    {
        crime = "Injured Fight";
    }
    else if (option == 7)
    {
        crime = "Tax Evasion";
    }
    else if (option == 8)
    {
        crime = "Money Laundering";
    }
}

// Set Guilty information to the person's informations.
void Guilty::setGuiltyData(const string &id, const string &name, const string &surname, const int &age, const string &nationallity, const string &gender, const string &crime, const string &punishment)
{
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->age = age;
    this->nationallity = nationallity;
    this->gender = gender;
    this->crime = crime;
    this->punishment = punishment;
}

void Guilty::setPunishment(int migrantType) // Set punishments according to the migrants' types.
{
    if (migrantType == 1) // Punishment is determined for employees.
    {
        if (crime == "Making Robbery" || crime == "Injured Fight" || crime == "Tax Evasion" || crime == "Money Laundering")
        {
            punishment = "Deport";

            if (crime == "Tax Evasion" || crime == "Money Laundering")
            {
                punishment = "Deport+Penalty";
            }
        }
        else if (crime == "Commit Murder" || crime == "Terror Activity" || crime == "Drug Dealing")
        {
            punishment = "Arrest";
        }
        else
        {
            punishment = "Penalty";
        }
    }
    else // Punishment is determined for refugees.
    {
        if (crime == "Commit Murder" || crime == "Terror Activity" || crime == "Drug Dealing" || crime == "Disturb Environment")
        {
            punishment = "Arrest";
        }
        else
        {
            punishment = "Deport";
        }
    }
}

// After the set punishment apply the punishment.
void Guilty::applyPunsihment(int migrantType, int &budget, int &usingBudget, Employee *employeeArray, Refugee *refugeeArray, int &employeeSize, int &refugeeSize, int index)
{
    ofstream myFile1;

    if (punishment == "Deport" || punishment == "Arrest" || punishment == "Deport+Penalty") // For these punishment.
    {
        if (migrantType == 1)
        {
            budget -= employeeArray[index].getTax(); // If employees deported or arrested, they cannot give tax. Therefore decrease budget.

            if (punishment == "Deport+Penalty")
            {
                budget += 50000; // If there is a penalty, penalty tranfer to the budget.
            }

            for (size_t i = index; i < employeeSize - 1; i++) // Shifted employees' array. Becasue they are arrested or deported.
            {
                employeeArray[i] = employeeArray[i + 1];
            }
            employeeSize--; // Employee decrease by one.

            myFile1.open("employee.txt", ios::out);

            for (size_t i = 0; i < employeeSize; i++) // Write employee information.
            {
                myFile1 << employeeArray[i].getID() << " " << employeeArray[i].getName() << " " << employeeArray[i].getSurname() << " " << employeeArray[i].getAge()
                        << " " << employeeArray[i].getNationallity() << " " << employeeArray[i].getGender() << " " << employeeArray[i].getJob()
                        << " " << employeeArray[i].getCity() << " " << employeeArray[i].getSalary() << " " << employeeArray[i].getTax() << endl;
            }

            myFile1.close();
        }
        else if (migrantType == 2) // If refugees deported or areested, they cannot live in a camp. Therefore using budget is decreased.
        {
            usingBudget -= 1000;

            for (size_t i = index; i < refugeeSize - 1; i++) // Shifted refugees' array. Becasue they are arrested or deported.
            {
                refugeeArray[i] = refugeeArray[i + 1];
            }
            refugeeSize--;

            myFile1.open("refugee.txt", ios::out);

            for (size_t i = 0; i < refugeeSize; i++) // Write refugee information.
            {
                myFile1 << refugeeArray[i].getID() << " " << refugeeArray[i].getName() << " " << refugeeArray[i].getSurname() << " " << refugeeArray[i].getAge()
                        << " " << refugeeArray[i].getNationallity() << " " << refugeeArray[i].getGender() << " " << refugeeArray[i].getCamp() << endl;
            }

            myFile1.close();
        }
    }
    else // Directly pay to penalty, and these penalty transfer to the budget.
    {
        budget += 15000;
    }
}

int Guilty::search(Employee *array, int size, string id) // Thanks to the this function, matching the idies according to the user's entering id for the employees.
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i].getID() == id)
        {
            return i;
        }
    }

    return -1;
}

int Guilty::search(Refugee *array, int size, string id) // Thanks to the this function, matching the idies according to the user's entering id for the refugees.
{
    for (size_t i = 0; i < size; i++)
    {
        if (array[i].getID() == id)
        {
            return i;
        }
    }

    return -1;
}

void Guilty::addGuiltyFile() // Adding guilty to the end of the file. (app mode).
{
    ofstream myFile;
    myFile.open("guilty.txt", ios::app);

    myFile << id << " " << name << " " << surname << " " << age << " " << nationallity << " " << gender << " " << crime << " " << punishment << endl;

    myFile.close();
}
// Getter methods.
string Guilty::getCrime()
{
    return crime;
}

string Guilty::getPunishment()
{
    return punishment;
}