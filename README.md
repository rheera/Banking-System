# Banking-System
A simple banking system project for class.

Deliverable 1

Manager Requirements A:

1.	Open accounts for bank clients
2.	Close accounts for bank clients-with 0 balance
3.	View a member’s account details
4.	View all member’s account details

Maintenance Requirements B:

1.	Turn trace on
2.	Turn trace off

Client Requirements C:

1.	Check savings account balance
2.	Check chequings account balance
3.	Withdraw money from chequings – warn not sufficient funds
4.	Deposit money to savings
5.	Transfer money to savings – warn not sufficient funds 
6.	Print recent transactions
7.	Request to open savings account
8.	Request to open chequings account
9.	Request to close savings account
10.	Request to close chequings account 
11.	If Chequings drops below 1000 during withdrawal / transfer, if continue 2$ fee
12.	Can only use their accounts 
13.	Can change their password


Bank Requirements D:

1.	Infinite number of members
2.	Each member has unique id
3.	Each member can only do actions specific to their role 
4.	Members and accounts persist through runs
5.	Bank has text UI for user to interact with 


Deliverable 2

Manager E:
1.	Manager can add new members to bank (clients, maintenance or another manager)
2.	Manager can remove any accounts

Client F:
1.	Transfer money to and from either account
2.	Deposit money to any account 
3.	Clients can change their passwords

Bank G:
1.	If no previous information stored, then start banking software with prompt to create a new manager account
2.	If trace is off clients cannot use the bank 


Deliverable 3

How to use:
1.	In system.hpp defined locations for “MemberFile” and “AccountFile” change to wherever program is stored for persistency. 
2.	-1 to quit login menu and save run
3.	type numbers and enter for selections 
4.	Run main program (can make main.cpp then run ./main in terminal)


Deliverable 4
 
Bank: Login and logout
-	Manager logs in
-	Welcomed, with manager actions
-	Exits
-	Shuts down system

Client: Check balances
-	Client logs in
-	Welcomed, with client actions
-	Chooses, 1, savings balance
-	Displayed
-	Chooses 2, chequing balance
-	Displayed
-	Logs out
-	Shuts down system 

Client: Change Password
-	Client logs in
-	Welcomed, with client actions
-	Chooses, 8, change password
-	Promted to enter old password
-	Prompted to enter new password, twice to verify it was typed correctly
-	Logs out
-	Shuts down system 

Maintenance: Trace on and Off
-	Maintenance logs in
-	Welcomed, maintenance actions
-	Turns trace on
-	Turns trace off
-	Exits
-	Shuts down system

Manager: Add new member 
-	Manager logs in
-	Welcomed, with manager actions
-	Chooses 5, add new member
-	Prompts to enter user name, type, and id number
-	Tells you default password is 0000
-	Exits
-	Shuts down system


