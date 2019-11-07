//
//  members.hpp
//  BankingSystem
//
//  Created by Raman H on 2016-10-23.
//  Copyright © 2016 Raman H. All rights reserved.
//

#ifndef members_h
#define members_h
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class member
{
private:
    int memNum;
    string name;
    string password;
    double savBal=-1;
    double cheqBal=-1;
    
public:
    bool corrPass(string);
    void newPass();
    string getName();
    int getMemNum();
    double getSavBal();
    void setSavBal(double);
    double getCheqBal();
    void setCheqBal(double);
    int memType;
    string getStringType();
    string getPass();
    int getMemType();
    member(string, string, int, int);
};

member::member(string name, string password, int memType, int memNum) {
    this->name=name;
    this->password=password;
    this->memNum=memNum;
    this->memType=memType;
    this->savBal=-1;
    this->cheqBal=-1;
};

bool member::corrPass(string currPass){
    if (currPass == this->password){
        return true;
    }
    else
        return false;
};

void member::newPass() {
    string currPass, newPass, newPass2;
    bool changed=false;
    while (changed == false){
        cout<<"\nEnter your current password or [0] to quit: \n";
        cin >> currPass;
        if (currPass == "0"){
            return;
        }
        if (corrPass(currPass) == true){
            while (changed == false){
                cout<<"\nEnter your new password or [0] to quit: \n";
                cin >> newPass;
                if (newPass == "0"){
                    return;
                }
                cout<<"\nEnter your new password again to verify or [0] to quit: \n";
                cin >> newPass2;
                if (newPass2 == "0"){
                    return;
                }
                if(newPass == newPass2){
                    password = newPass;
                    cout<<"\nPassword has been changed";
                    changed = true;
                }
                else {
                    cout<<"\nPasswords dont match, try again";
                }
            }
        }
        else {
            cout<<"\nPassword was incorrect, try again ";
        }
    }
};

string member::getName() {
    return name;
}
double member::getSavBal() {
    return savBal;
};

void member::setSavBal(double amt){
    savBal=amt;
};

double member::getCheqBal() {
    return cheqBal;
};

void member::setCheqBal(double amt){
    cheqBal=amt;
}

int member::getMemType() {
    return memType;
};
string member::getStringType() {
    if (getMemType() == 1){
        return "Manager";
    }
    if (getMemType() == 2){
        return "Maintenance";
    }
    else{
        return "Client";
    }
}
int member::getMemNum() {
    return memNum;
};

string member::getPass() {
    return password;
}

#endif /* members_h */
