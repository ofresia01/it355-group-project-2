#include <iostream>
#include <fstream>
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
    vector<Loan> loans;

    while(getline(infile, line))
    {
        istringstream iss(line);
        string name;
        int age;
        getline(iss, name, ',') >>age;
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

    int choice;
    do
    {
        cout << "Please select your choice:\nCreate a new loanholder: 1\nCreate a new loan: 2\nPrint loan information: 3\nExit: 4" << endl;
        cout << "Enter your choice here: ";
        cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                cout<<"Please enter loan holder's age: ";
                int age;
                string name;
                cin>>age;
                if(age < 0 || age > 100)
                {
                    while(age > 100 || age <= 0)
                    {
                        cout<<"You have entered an invalid age. Please enter a valid age(0-99) here: ";
                        cin>>age;
                    }
                }
                if(age < 18 && age >= 0)
                {
                    cout<<"We do not allow minors to take on loans. Our apologies."<<endl;
                }
                else
                {
                    cin.ignore();
                    cout<<"Please enter loan holder's name here: ";
                    getline(cin, name);
                }
                Person person(name, age);
                people.push_back(person);
                break;
            }
            case 2:
            {
                cin.ignore();
                cout<<"Please enter name loan will be stored under: ";
                string name;
                bool validPerson = false;
                getline(cin, name);
                for (const auto& person : people)
                {
                    if(name == person.getName())
                    {
                        validPerson = true;
                        cout<<"Please enter type of loan you would like to create.\nPersonal Loan: 1\nCar Loan: 2\nHouse Loan: 3\nBusiness Loan: 4"<<endl;
                        cout<<"Please enter your choice here: ";
                        int loanChoice;
                        cin>>loanChoice;
                        while(loanChoice < 1 || loanChoice > 4)
                        {
                            cout<<"Invalid choice, please enter a valid choice.\nEnter your choice here: ";
                            cin>>loanChoice;
                        }
                        cout<<"Please enter the total loan amount you'd like to have: $";
                        double totalAmount;
                        cin>>totalAmount;
                        while(totalAmount < 0)
                        {
                            cout<<"Invalid loan amount. Please enter a valid loan amount: $";
                            cin>>totalAmount;
                        }
                        cout<<"Please enter how long you'd like the term date to be in years: ";
                        double termLength;
                        cin>>termLength;
                        while(termLength < 0)
                        {
                            cout<<"Invalid term length. Please enter a valid term length: ";
                            cin>>termLength;
                        }

                        if(loanChoice == 1)
                        {
                            Loan loan(person, totalAmount, "4/24/24", termLength);
                            loans.push_back(loan);
                        }
                        if(loanChoice == 2)
                        {
                            CarLoan loan(person, totalAmount, "4/24/24", termLength);
                            loans.push_back(loan);
                        }
                        if(loanChoice == 3)
                        {
                            HouseLoan loan(person, totalAmount, "4/24/24", termLength);
                            loans.push_back(loan);
                        }
                        if(loanChoice == 4)
                        {
                            BusinessLoan loan(person, totalAmount, "4/24/24", termLength);
                            loans.push_back(loan);
                        }
                    }
                }

                if(!validPerson)
                {
                    cout<<"No loanholders under that name exist."<<endl;
                }
                break;
            }
            case 3:
            {
                cin.ignore();
                cout<<"Please enter loan holder's name to display loans: ";
                string name;
                bool validName = false;
                getline(cin, name);
                for (const auto& person : people)
                {
                    if(name == person.getName())
                    {
                        validName = true;
                        cout<<"Displaying all loans under "<<name<<endl;
                        for(const auto& loan : loans)
                        {
                            if(loan.getName() == name)
                            {
                                loan.print();
                            }
                            }
                    }
                }
            
                if(!validName)
                {
                    cout<<"No loanholders under that name exist."<<endl;
                }
                break;
            }
            case 4:
            {
                cout << "Thank you for using our loan calculator." << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
            }
        }
    } while(choice != 4);

    return 0;
}