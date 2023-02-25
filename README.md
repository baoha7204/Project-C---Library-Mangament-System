"# Project-C---Library-Mangament-System" 
When login, the user has to input role from 1->3, which is student, librarian and admin respectively. Reasons for this input is firstly, I cannot add the generic data type to Account struct :) and secondly, to intialize the data structures for each role (1 for Student, 1 for Librarian/Admin). The account will accompany with 1 and only 1 user. Therefore, I'd like to contain the information of the user (like name, ID, date of birth, etc.) inside the Account database. But to implement that, I have to use the generic data type for each role. I'm really struggle with these stuff since it's related to pointer and DMA (dynamic memory allocation). For simpler program, I decide to cut off the librarian database to focus on 2 main databases that the system deals with: Account (2 subdatabases is Account, which contains Librarian/Admin account, and StudentAccount), Book.
