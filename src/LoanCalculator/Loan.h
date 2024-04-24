#include <iostream>
#include "Person.cpp"
using namespace std;

#ifndef LOAN_H
#define LOAN_H

class Loan
{
private:
    Person person;
    double totalAmount;
    double currentlyOwed;
    string loanStartDate;
    double termLength;
    double interestRate;

public:
    Loan(Person person, double totalLoan, string loanStartDate, double termLength = 3.5, double interestRate = 12.5);
    void makePayment(double amount);
    double calculateInterest(string typeOfInterest);
    void scheduledPayment();
    double getRemainingAmount();
    void print() const;
    string getName() const;
};

class CarLoan : public Loan
{
public:
    CarLoan(Person person, double totalLoan, string loanStartDate, double termLength = 3.5, double interestRate = 7.25)
        : Loan(person, totalLoan, loanStartDate, termLength, interestRate) {}
    void print() const;
};

class BusinessLoan : public Loan
{
public:
    BusinessLoan(Person person, double totalLoan, string loanStartDate, double termLength = 3.5, double interestRate = 17.5)
        : Loan(person, totalLoan, loanStartDate, termLength, interestRate) {}
    void print() const;
};

class HouseLoan : public Loan
{
public:
    HouseLoan(Person person, double totalLoan, string loanStartDate, double termLength = 30, double interestRate = 7)
        : Loan(person, totalLoan, loanStartDate, termLength, interestRate) {}
    void print() const;
};

#endif
