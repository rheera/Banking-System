//
//  main.cpp
//  BankingSystem
//
//  Created by Raman H on 2016-10-24.
//  Copyright © 2016 Raman H. All rights reserved.
//

#include <stdio.h>
#include "members.hpp"
#include "system.hpp"
using namespace std;

int main() {
    class system Bank = *new class system();
    Bank.start();
    Bank.login();
    return 0;
}
