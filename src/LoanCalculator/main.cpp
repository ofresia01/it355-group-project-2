#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Loan.h"
using namespace std;


int main()
{
    cout<<"Welcome to your loan calculator."<<endl;
    
    ifstream infile;
    infile.open("LoanHolders.txt");
    string line;
    
    vector<Person> people;

    while(getline(infile, line))
    {
        istringstream iss(line);
        string name;
        int age;
        Person person(name, age);
        people.push_back(person);
    }
    infile.close();

    cout<<"Current Loan Holders:"<<endl;
    for (const auto& person : people)
    {
        cout<<"Name: "<<person.getName() << endl;
        cout<<"Age: "<<person.getAge()<<endl;
        cout<<endl;
    }

    cout<<"Please select your choice:\nCreate a new loanholder: 1\nCreate a new loan: 2\nPrint loan information: 3\nExit: 4"<<endl;
    cout<<"Enter you choice here: ";
    int choice;
    cin>>choice;
    while((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4))
    {
        cout<<"Invalid choice, please enter a valid choice.\nEnter your choice here: ";
        cin>>choice;
    }

    while(choice != 4)


    return 0;
}