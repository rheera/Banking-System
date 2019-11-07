//
//  system.hpp
//  BankingSystem
//
//  Created by Raman H on 2016-10-23.
//  Copyright © 2016 Raman H. All rights reserved.
//

#ifndef system_hpp
#define system_hpp
#define MemberFile "/Users/Raman/Desktop/c++ docs/cs3307ass1/BankingSystem/BankingSystem/memberData.txt"
#define AccountFile "/Users/Raman/Desktop/c++ docs/cs3307ass1/BankingSystem/BankingSystem/clientAccounts.txt"
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "members.hpp"
using namespace std;

class system{
private:
    int findMem(int);
    bool trace=true;
public:
    vector<member> array;
    void start();
    void login();
    void listMem();
    void newMem();
    void delMem(int);
    void seeMem(int);
    void seeAll();
    void manMenu();
    void mainMenu();
    void openAcc(int);
    void closeAcc(int);
    void deposit(int, double);
    void withdraw(int, double);
    void transfer(int, double);
    vector<string> members, accounts;
    
};

void system::start() {
    string name, pw;
    ifstream memData (MemberFile);
    if (memData.is_open())
    {
        for(string line; getline(memData, line); )
        {
            members.push_back(line);
        }
        for (int i=0; i<members.size();i+=4){
            array.push_back(member(members[i],members[i+1],stoi(members[i+2]),stoi(members[i+3])));
        }
        memData.close();
    }
    else {
        cout << "Unable to open member data file";
    }
    
    
    ifstream clientData (AccountFile);
    if (clientData.is_open())
    {
        for(string line; getline(clientData, line); )
        {
            accounts.push_back(line);
        }
        for (int i=0; i<accounts.size();i+=4){
            int mem = findMem(stoi(accounts[i+1]));
            array[mem].setSavBal(stoi(accounts[i+2]));
            array[mem].setCheqBal(stoi(accounts[i+3]));
        }
        clientData.close();
    }
    else {
        cout << "Unable to open client data file";
    }

    
    if (array.size() == 0){
        cout<<"\nEnter a name: \n";
        cin>>name;
        cout<<"\nEnter a password: \n";
        cin>>pw;
        array.push_back(member(name,pw,1,0));
        members.push_back(name);
        members.push_back(pw);
        members.push_back(to_string(1));
        members.push_back(to_string(0));
        
    }
};

void system::login(){
    int memNum, mem;
    string pw;
    bool changed = false;
    cout<<"\nEnter member id num: \n";
    cin>>memNum;
    if(memNum < 0){
        ofstream memFile;
        memFile.open (MemberFile);
        for (int i=0; i<members.size();i++){
            memFile<<members[i]<<"\n";
        }
        ofstream accFile;
        accFile.open (AccountFile);
        for (int i=0; i<accounts.size();i++){
            accFile<<accounts[i]<<"\n";
        }
        return;
    }
    cout<<"\nEnter password: \n";
    cin>>pw;
    mem=findMem(memNum);
    if (mem == -1){
        cout<<"\nWrong member id or password";
        login();
    }
    else {
        if (array[mem].corrPass(pw)==true){
            cout<<"\nWelcome";
            if (array[mem].getMemType() == 1){
                manMenu();
            }
            if (array[mem].getMemType() == 2){
                mainMenu();
            }
            if (array[mem].getMemType() == 3) {
                if (trace == false){
                    cout<<"\nBank is closed";
                }
                else{
                    while (changed == false){
                        int input = 0;
                        cout<<"\n[0] Exit"
                        <<"\n[1] Savings account balance"
                        <<"\n[2] Chequings account balance"
                        <<"\n[3] Withdraw money"
                        <<"\n[4] Deposit money"
                        <<"\n[5] Recent Transactions"
                        <<"\n[6] Account manager"
                        <<"\n[7] Transfer Money"
                        <<"\n[8] Change password\n";
                        cin>>input;
                        switch (input) {
                            case 0:
                                cout<<"\nGoodbye\n";
                                changed = true;
                                login();
                                break;
                            case 1:
                                if(array[mem].getSavBal() == -1){
                                    cout<<"\nSavings account not opened";
                                }
                                else{
                                    cout<<"\nSavings account balance: "<<array[mem].getSavBal();
                                }
                                break;
                            case 2:
                                if(array[mem].getCheqBal() == -1){
                                    cout<<"\nChequings account not opened";
                                }
                                else{
                                    cout<<"\nChequings account balance: "<<array[mem].getCheqBal();
                                }
                                break;
                            case 3:
                                double amtW;
                                cout<<"\nEnter how much would you like to withdraw? or press [0] to quit\n";
                                cin>>amtW;
                                withdraw(memNum,amtW);
                                break;
                            case 4:
                                double amtD;
                                cout<<"\nEnter how much would you like to deposit? or press [0] to quit\n";
                                cin>>amtD;
                                deposit(memNum,amtD);
                                break;
                            case 5:
                                cout<<"\nRecent transactions";
                                break;
                            case 6:
                                int opt;
                                cout<<"\nRequst for an account change or [0] to exit: "
                                <<"\n[1] Open account"
                                <<"\n[2] Close account\n";
                                cin>>opt;
                                switch (opt) {
                                    case 0:
                                        cout<<"\nGoodbye\n";
                                        break;
                                    case 1:
                                        openAcc(mem);
                                        break;
                                    case 2:
                                        closeAcc(mem);
                                        break;
                                    default:
                                        cout<<"\nInvalid input. Try again.";
                                }
                                break;
                            case 7:
                                double amtT;
                                cout<<"\nEnter how much would you like to transfer? or press [0] to quit\n";
                                cin>>amtT;
                                transfer(memNum, amtT);
                                break;
                            case 8:
                                array[mem].newPass();
                                for(int k=3;k<members.size();k+=4){
                                    if(array[mem].getMemNum()==stoi(members[k])){
                                        members[k-2]=array[mem].getPass();
                                    }
                                }
                                break;
                            default:
                                cout<<"\nInvalid input. Try again.";
                        }
                    }
                }
            }
        }
        else {
            cout<<"\nWrong member id or password";
            login();
        }
    }
};

void system::manMenu() {
    int input = 0, memID;
    cout<<"\n[0] Exit"
    <<"\n[1] Open account"
    <<"\n[2] Close account"
    <<"\n[3] View member details"
    <<"\n[4] View all member details"
    <<"\n[5] Add new member"
    <<"\n[6] Delete a member\n";
    cin>>input;
    switch (input) {
        case 0:
            cout<<"\nGoodbye\n";
            login();
            break;
        case 1:
            cout<<"\nWhich member would like to add an account to? Enter member ID: \n";
            cin>>memID;
            if (findMem(memID) == -1) {
                cout<<"\nUser does not exist";
            }
            else {
                if(array[findMem(memID)].getMemType() != 3){
                    cout<<"\nUser is not a client";
                }
                else{
                openAcc(memID);
                }
            }
            manMenu();
            break;
        case 2:
            cout<<"\nWhich member would like to close an account for? Enter member ID: \n";
            cin>>memID;
            if (findMem(memID) == -1) {
                cout<<"\nUser does not exist";
            }
            else {
                if(array[findMem(memID)].getMemType() != 3){
                    cout<<"\nUser is not a client";
                }
                else {
                    closeAcc(memID);
                }
            }
            manMenu();
            break;
        case 3:
            cout<<"\nWhich member would like to view details for? Enter member ID: \n";
            cin>>memID;
            seeMem(memID);
            manMenu();
            break;
        case 4:
            seeAll();
            manMenu();
            break;
        case 5:
            newMem();
            manMenu();
            break;
        case 6:
            cout<<"\nWhich member would like to delete? Enter member ID: \n";
            cin>>memID;
            delMem(memID);
            manMenu();
            break;
        default:
            cout<<"\nInvalid input. Try again.";
    }
}

void system::mainMenu() {
    int input = 0;
    cout<<"\n[0] Exit"
    <<"\n[1] Turn on trace"
    <<"\n[2] Turn off trace\n";
    cin>>input;
    switch (input) {
        case 0:
            cout<<"\nGoodbye\n";
            login();
            break;
        case 1:
            trace = true;
            cout<<"\nTrace is on";
            mainMenu();
            break;
        case 2:
            trace = false;
            cout<<"\nTrace is off";
            mainMenu();
            break;
        default:
            cout<<"\nInvalid input. Try again.";
    }
    cout<<"\nGoodbye\n";
};

int system::findMem(int memNum) {
    for (int i=0; i<array.size(); i++) {
        if (array[i].getMemNum() == memNum){
            return i;
        }
    }
    return -1;
};

void system::newMem() {
    string name, pw="0000";
    int memNum = 0, memType = 0;
    bool changed = false;
    cout<<"\nEnter users name or [0] to quit\n";
    cin >> name;
    if (name == "0"){
        return;
    }
    cout<<"\nEnter users member type (Manager [1], Maintenance [2], Client[3]) or [0] to quit\n";
    cin >> memType;
    if (memType <= 0 || memType > 3){
        return;
    }
    while (changed == false){
        cout<<"\nEnter a member id (number): or [0] to quit\n";
        cin >> memNum;
        if (findMem(memNum) == -1){
            changed = true;
        }
        if (memNum <= 0){
            changed = true;
            return;
        }
        if (findMem(memNum) >= 0) {
            cout<<"\nMember id already exists, try again";
        }
    }
    cout<<"\nDefault password is 0000, change password on first login";
    array.push_back(member(name,pw,memType,memNum));
    members.push_back(name);
    members.push_back(pw);
    members.push_back(to_string(memType));
    members.push_back(to_string(memNum));
    if(memType == 3){
        accounts.push_back(name);
        accounts.push_back(to_string(memNum));
        accounts.push_back(to_string(-1));
        accounts.push_back(to_string(-1));
    }
};

void system::delMem(int memNum) {
    int mem = findMem(memNum);
    if (mem == -1) {
        cout<<"\nMember does not exist";
    }
    else {
        if ((array[mem].getSavBal() == 0 || array[mem].getSavBal() == -1) && (array[mem].getCheqBal() == 0 || array[mem].getCheqBal() == -1)) {
            int i=3; bool del = false;
            while(i<members.size() || del == false){
                if(array[mem].getMemNum() == stoi(members[i])){
                    members.erase(members.begin() + i);
                    members.erase(members.begin() + (i-1));
                    members.erase(members.begin() + (i-2));
                    members.erase(members.begin() + (i-3));
                    del=true;
                    break;
                }
                i+=4;
            }
            if(array[mem].getMemType()==3){
                int k=1; bool del1 = false;
                while(k<accounts.size() || del1 == false){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts.erase(accounts.begin() + k);
                        accounts.erase(accounts.begin() + k);
                        accounts.erase(accounts.begin() + k);
                        accounts.erase(accounts.begin() + (k-1));
                        del1=true;
                        break;
                    }
                    k+=4;
                }
            }
            array.erase(array.begin() + mem);
        }
        else {
            cout<<"\nMember needs to empty his/her accounts first";
        }
    }
};

void system::seeMem(int memNum) {
    int mem = findMem(memNum);
    if (mem == -1) {
        cout<<"\nMember does not exist";
    }
    else {
        cout<<"\n\nName: "<< array[mem].getName();
        cout<<"\n Account: "<< array[mem].getStringType();
        cout<<"\n Member ID: "<< array[mem].getMemNum();
        if (array[mem].getMemType() == 3){
            cout<<"\n Savings Account Balance: "<< array[mem].getSavBal();
            cout<<"\n Chequings Account Balance: "<< array[mem].getCheqBal();
        }
    }
}

void system::seeAll() {
    for (int i=0; i<array.size(); i++){
        seeMem(array[i].getMemNum());
    }
}

void system::openAcc(int memID) {
    int input;
    int mem=findMem(memID);
    cout<<"\n What account would you like to open [1] Savings or [2] Chequings, or [0] to exit?\n";
    cin>>input;
    switch (input) {
        case 0:
            break;
        case 1:
            if (array[mem].getSavBal() == -1){
                array[mem].setSavBal(0);
                cout<<"\n Savings account open";
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+1]=to_string(0);
                    }
                }
            }
            if (array[mem].getSavBal() >= 0){
                cout<<"\n Savings account already open";
            }
            break;
        case 2:
            if (array[mem].getCheqBal() == -1){
                array[mem].setCheqBal(0);
                cout<<"\n Chequings account open";
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+2]=to_string(0);
                    }
                }
            }
            if (array[mem].getCheqBal() >= 0) {
                cout<<"\n Chequings account already open";
            }
            break;
        default:
            cout<<"Invalid input. Try again.";
    }
};

void system::closeAcc(int memID) {
    int input;
    int mem=findMem(memID);
    cout<<"\n What account would you like to close [1] Savings or [2] Chequings, or [0] to exit?\n";
    cin>>input;
    switch (input) {
        case 0:
            break;
        case 1:
            if (array[mem].getSavBal() == 0){
                array[mem].setSavBal(-1);
                cout<<"\n Savings account closed";
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+1]=to_string(-1);
                    }
                }
            }
            if (array[mem].getSavBal() > 0) {
                cout<<"\n Savings account still has funds, transfer or withdraw them to close";
            }
            if (array[mem].getSavBal() == -1) {
                cout<<"\n Savings account already closed";
            }
            break;
        case 2:
            if (array[mem].getCheqBal() == 0){
                array[mem].setCheqBal(-1);
                cout<<"\n Chequings account closed";
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+2]=to_string(-1);
                    }
                }
            }
            if (array[mem].getCheqBal() > 0) {
                cout<<"\n Chequings account still has funds, transfer or withdraw them to close";
            }
            if (array[mem].getCheqBal() == -1) {
                cout<<"\n Chequings account already closed";
            }
            break;
        default:
            cout<<"Invalid input. Try again.";
    }
};

void system::deposit(int memID, double amt) {
    int account;
    int mem=findMem(memID);
    if(array[mem].getCheqBal() == -1 && array[mem].getSavBal() == -1){
        cout<<"\n User does not have any accounts open";
    }
    if(amt <= 0){
        return;
    }
    else{
        cout<<"\nChoose an account(Savings [1] or Chequings [2]): or [0] to quit\n";
        cin>>account;
        switch(account){
            case 0:
                break;
            case 1:
                array[mem].setSavBal(array[mem].getSavBal() + amt);
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+1]=to_string(array[mem].getSavBal());
                    }
                }
                break;
            case 2:
                array[mem].setCheqBal(array[mem].getCheqBal() + amt);
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+2]=to_string(array[mem].getCheqBal());
                    }
                }
                break;
            default:
                cout<<"\nInvalid entry, try again";
        }
    }
};

void system::withdraw(int memID,double amt) {
    int account;
    int mem=findMem(memID);
    string approve;
    if(array[mem].getCheqBal() == -1 && array[mem].getSavBal() == -1){
        cout<<"\n User does not have any accounts open";
        return;
    }
    if(amt <= 0){
        return;
    }
    else{
        cout<<"\nChoose an account(Savings [1] or Chequings [2]): or [0] to quit\n";
        cin>>account;
        if (account <= 0){
            return;
        }
        if (account == 1){
            if (array[mem].getSavBal() >= amt) {
                array[mem].setSavBal(array[mem].getSavBal() - amt);
                cout<<"\nNew savings account balance is "<< array[mem].getSavBal();
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+1]=to_string(array[mem].getSavBal());
                    }
                }
            }
            else {
                cout<<"\nInsufficient funds";
                return;
            }
        }
        if (account ==2){
            if (array[mem].getCheqBal() >= amt) {
                if(array[mem].getCheqBal() - amt >= 1000){
                    array[mem].setCheqBal(array[mem].getCheqBal() -amt);
                    cout<<"\nNew chequings account balance is "<< array[mem].getCheqBal();
                    for(int k =1; k<accounts.size(); k+=4){
                        if(array[mem].getMemNum() == stoi(accounts[k])){
                            accounts[k+2]=to_string(array[mem].getCheqBal());
                        }
                    }
                }
                else {
                    cout<<"\nChequings balance will drop below $1000, are you sure you want to continue the transaction, a $2.00 fee will apply? (Y/N)\n";
                    cin>>approve;
                    if (approve == "Y" || approve == "y"){
                        array[mem].setCheqBal(array[mem].getCheqBal() - (amt +2));
                        cout<<"\nNew chequings account balance is "<< array[mem].getCheqBal();
                        for(int k =1; k<accounts.size(); k+=4){
                            if(array[mem].getMemNum() == stoi(accounts[k])){
                                accounts[k+2]=to_string(array[mem].getCheqBal());
                            }
                        }
                    }
                    else {
                        return;
                    }
                }
            }
            else {
                cout<<"\nInsufficient funds";
            }
        }
        else {
            cout<<"/nInvalid entry, try again";
        }
    }
};

void system::transfer(int memID, double amt) {
    int account;
    string approve;
    int mem=findMem(memID);
    if(array[mem].getCheqBal() == -1 || array[mem].getSavBal() == -1){
        cout<<"\n User does not have two accounts to transfer between";
        return;
    }
    if(amt <= 0){
        return;
    }
    else {
        cout<<"\nDo you want to transfer from savings to chequings [1] or chequings to savings [2]: or [0] to quit\n";
        cin>>account;
        if (account <= 0){
            return;
        }
        if (account == 1){
            if (array[mem].getSavBal() >= amt) {
                array[mem].setSavBal(array[mem].getSavBal() -amt);
                cout<<"\nNew savings account balance is "<< array[mem].getSavBal();
                array[mem].setCheqBal(array[mem].getCheqBal() + amt);
                cout<<"\nNew chequings account balance is "<< array[mem].getCheqBal();
                for(int k =1; k<accounts.size(); k+=4){
                    if(array[mem].getMemNum() == stoi(accounts[k])){
                        accounts[k+1]=to_string(array[mem].getSavBal());
                        accounts[k+2]=to_string(array[mem].getCheqBal());
                    }
                }
                return;
            }
            else {
                cout<<"\nInsufficient funds";
                return;
            }
        }
        if (account == 2){
            if (array[mem].getCheqBal() >= amt) {
                if(array[mem].getCheqBal() - amt >= 1000){
                    array[mem].setCheqBal(array[mem].getCheqBal() - amt);
                    cout<<"\nNew chequings account balance is "<< array[mem].getCheqBal();
                    array[mem].setSavBal(array[mem].getSavBal() + amt);
                    cout<<"\nNew savings account balance is "<< array[mem].getSavBal();
                    for(int k =1; k<accounts.size(); k+=4){
                        if(array[mem].getMemNum() == stoi(accounts[k])){
                            accounts[k+1]=to_string(array[mem].getSavBal());
                            accounts[k+2]=to_string(array[mem].getCheqBal());
                        }
                    }
                }
                else {
                    cout<<"\nChequings balance will drop below $1000, are you sure you want to continue the transaction, a $2.00 fee will apply? (Y/N)\n";
                    cin>>approve;
                    if (approve == "Y" || approve == "y"){
                        array[mem].setCheqBal((array[mem].getCheqBal() - amt) - 2);
                        cout<<"\nNew chequings account balance is "<< array[mem].getCheqBal();
                        array[mem].setSavBal(array[mem].getSavBal() + amt);
                        cout<<"\nNew savings account balance is "<< array[mem].getSavBal();
                        for(int k =1; k<accounts.size(); k+=4){
                            if(array[mem].getMemNum() == stoi(accounts[k])){
                                accounts[k+1]=to_string(array[mem].getSavBal());
                                accounts[k+2]=to_string(array[mem].getCheqBal());
                            }
                        }
                        return;
                    }
                    else {
                        return;
                    }
                }
            }
            else {
                cout<<"\nInsufficient funds";
            }
        }
        else {
            cout<<"/nInvalid entry, try again";
        }
    }
};

#endif /* system_hpp */
