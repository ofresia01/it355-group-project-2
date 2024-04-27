#include "Loan.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
Doesn't involve direct array access where there's a risk of reading beyond array bounds. Conforms to (CWE-125).
Doesn't use arrays or array indexing, so there's no risk of improper validation of array indexes. Conforms to (CWE-129).
Doesn't perform unsigned to signed conversion, so there's no risk of this error. Conforms to (CWE-196).
Doesn't utilize sizeof() on pointer types, so there's no risk here. Conforms to (CWE-467).
Doesn't involve bitwise operations on integers, hence no risk of incorrect bitwise shifts. Conforms to (CWE-1335).
Properly initializes pointers, so there's no risk of NULL pointer dereference. Conforms to (CWE-476).
Public methods don't return private data structures, ensuring encapsulation. Conforms to (CWE-495).
Initializes all variables before use, so there's no risk of uninitialized variable usage. Conforms to (CWE-457).
*/

/*
CWE-197: Doesn't involve any numeric truncation operations where significant digits might be lost, so this CWE doesn't apply.
CWE-192: There are no instances in  where integer coercion could lead to unintended behavior, so this CWE is not relevant.
CWE-396: Doesn't include exception handling with generic catch statements, so this CWE doesn't apply.
CWE-131: Doesn't perform buffer size calculations in a way that could lead to incorrect results, so this CWE isn't relevant.
CWE-787: Properly manages array writes and doesn't allow writes beyond the bounds of allocated memory, so this CWE doesn't apply.
CWE-242: Doesn't utilize any inherently dangerous functions that could lead to vulnerabilities, so this CWE is not relevant.
CWE-789: Doesn't involve dynamic memory allocation with potentially excessive size values, so this CWE doesn't apply.
CWE-805: Doesn't access buffers with incorrect length values, so this CWE doesn't apply.
*/

// Constructor for Loan class, initializes loan details
Loan::Loan(Person loanHolder, double totalLoan, string startDate, double length, double interest)
    : person(loanHolder), totalAmount(totalLoan), currentlyOwed(totalLoan), loanStartDate(startDate), termLength(length), interestRate(interest) {}

// Function to make a payment towards the loan
void Loan::makePayment(double amount)
{
    // Check if the payment amount is less than the total loan amount
    if (currentlyOwed > amount)
    {
        amount = floor(amount * 100) / 100;
        this->currentlyOwed = this->currentlyOwed - amount;
        cout << "Payment of $ " << amount << " made by " << this->person.getName() << endl;
    }
    else
    {
        double amountPayed = this->currentlyOwed;
        this->currentlyOwed = 0;
        cout << "Payment of $" << amountPayed << " made by " << this->person.getName() << endl;
    }
}

// Function to calculate interest based on the specified type
double Loan::calculateInterest(string typeOfInterest)
{
    if (typeOfInterest.compare("Total Interest") || typeOfInterest.compare("total interest"))
    {
        return this->totalAmount * this->interestRate / 100;
    }
    else if (typeOfInterest.compare("Interest Left") || typeOfInterest.compare("interest left"))
    {
        return this->currentlyOwed * this->interestRate / 100;
    }
    else
    {
        cout << "Invalid loan calculation." << endl;
        return 0.0;
    }
}

// Function to make scheduled payments towards the loan
void Loan::scheduledPayment()
{
    double monthlyPayment = this->totalAmount * ((this->interestRate / 12) * pow((1 + (this->interestRate / 12)), (this->termLength))) / (pow((1 + (this->interestRate / 12)), (this->termLength)) - 1);
    monthlyPayment = floor(monthlyPayment * 100) / 100;
    double biweeklyPayment = monthlyPayment / 2;
    biweeklyPayment = floor(biweeklyPayment * 100) / 100;

    double amountToInterest = (biweeklyPayment * this->interestRate) / 100;
    amountToInterest = floor(amountToInterest * 100) / 100;
    double amountToPrincipal = biweeklyPayment - amountToInterest;

    this->currentlyOwed = this->currentlyOwed - amountToPrincipal;
}

// Function to get the remaining amount of the loan
double Loan::getRemainingAmount()
{
    return currentlyOwed;
}

// Function to print loan details
void Loan::print() const
{
    cout << "Loan Holder: " << person.getName() << endl;
    cout << "Total Loan Amount: " << this->totalAmount << endl;
    cout << "Term Length: " << this->termLength << " Years" << endl;
    cout << "Interest Rate: " << this->interestRate << endl;
    cout << "Amount Left to Pay: " << this->currentlyOwed << endl;
    cout<<endl;
}

string Loan::getName() const
{
    return this->person.getName();
}

// Function to print loan details for a car loan
void CarLoan::print() const
{
    cout << "Type of Loan: Car Loan" << endl;
    Loan::print();
}

// Function to print loan details for a house loan
void HouseLoan::print() const
{
    cout << "Type of Loan: House Loan" << endl;
    Loan::print();
}

// Function to print loan details for a business loan
void BusinessLoan::print() const
{
    cout << "Type of Loan: Business Loan" << endl;
    Loan::print();
}