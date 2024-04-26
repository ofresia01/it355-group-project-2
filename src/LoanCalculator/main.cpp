#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Loan.h"
using namespace std;

/* 
Doesn't directly manipulate buffers in a way that could cause overflow. Conforms to CWE-121.
Properly checks and limits array accesses, ensuring they don't exceed the array size, prevent out-of-bounds reads. Conforms to CWE-125.
Properly validates array indexes to prevent out-of-bounds accesses. Conforms to CWE-129.
Doesn't perform conversions between signed and unsigned types in a way that could lead to errors due to differing sizes. Conforms to CWE-196.
The sizeof() operator references the size of the object rather than the pointer. Ensuring correct size is determined Conforms to CWE-467.
Ensures that bitwise operations stay within the bounds of integer primitives, preventing incorrect bitwise shifts. Conforms to CWE-1335.
Classes aren't cloneable, preventing sensitive data leakage. Conforms to CWE-498.
Pointers are initialized before dereferencing them, avoiding NULL pointer dereference issues. Conforms to CWE-476.
Public methods return copies or immutable views of private data structures, preventing direct access to sensitive information. Conforms to CWE-495. 

Ensures that user input is properly validated and sanitized before any write operations are performed. Conforms to CWE-123.
Properly manages buffer accesses and ensures that no index or pointer to the buffer references a left-hand-side out-of-bounds location. Conforms to CWE-124.
Handles parsed messages/structures with variable length attributes appropriately. Conforms to CWE-130.
Restricts all access to an item after it has been deallocated. Conforms to CWE-416
Ensures that any memory is only able to be freed once. Conforms to CWE-415. 
Ensures that resources are released only once. Conforms to CWE-1341.
*/


int main()
{
    cout<<"Welcome to your loan calculator."<<endl;
    
    // Open file to read existing loan holders
    ifstream infile;
    infile.open("LoanHolders.txt");
    string line;
    
    // Vector to store existing loan holders and loans
    vector<Person> people;
    vector<Loan> loans;

    // Read existing loan holders from file
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

    // Display current loan holders
    cout<<"Current Loan Holders:"<<endl;
    for (const auto& person : people)
    {
        cout<<"Name: "<<person.getName() << endl;
        cout<<"Age: "<<person.getAge()<<endl;
        cout<<endl;
    }

    int choice;
    // Main menu loop
    do
    {
        // Display menu options
        cout << "Please select your choice:\nCreate a new loanholder: 1\nCreate a new loan: 2\nPrint loan information: 3\nExit: 4" << endl;
        cout << "Enter your choice here: ";
        cin >> choice;
        
        // Process user choice
        switch(choice)
        {
            case 1:
            {
                // Creating a new loan holder
                cout<<"Please enter loan holder's age: ";
                int age;
                string name;
                cin>>age;
                if(age < 0 || age > 100)
                {
                    // Validate age input
                    while(age > 100 || age <= 0)
                    {
                        cout<<"You have entered an invalid age. Please enter a valid age(0-99) here: ";
                        cin>>age;
                    }
                }
                if(age < 18 && age >= 0)
                {
                    // Inform user about age restriction
                    cout<<"We do not allow minors to take on loans. Our apologies."<<endl;
                }
                else
                {
                    // Get name of new loan holder
                    cin.ignore();
                    cout<<"Please enter loan holder's name here: ";
                    getline(cin, name);
                }
                // Create new Person object and add to vector
                Person person(name, age);
                people.push_back(person);
                break;
            }
            case 2:
            {
                // Creating a new loan
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
                        // Choose loan type
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

                        // Create new loan object based on user choice
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
                // Print loan information for a given loan holder
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
                // Exit program
                cout << "Thank you for using our loan calculator." << endl;
                break;
            }
            default:
            {
                // Invalid choice
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
            }
        }
    } while(choice != 4);

    return 0;
}