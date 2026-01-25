#ifndef USERMANAGE_3_H
#define USERMANAGE_3_H

struct User {
    char name[20];
    char password[20];
    int role;// 0: user, 1: admin
    int state;// 0: active, 1: blocked
};

void initUsers(struct User users[], int n);
void displayUsers(struct User users[], int n);
void addUser(struct User users[], int n);
void deleteUser(struct User users[], int n, char name[]);
int searchUser(struct User users[], int n, char name[]);
void changePassword(struct User users[], int n, char name[]);
int checkLogin(struct User users[], int n, char name[], char pass[]);
int strongPassword(char pass[]);
void blockUser(struct User users[], int n, char name[]);
void unblockUser(struct User users[], int n, char name[]);
void changeRole(struct User users[], int n, char name[], int role);
void listAdmins(struct User users[], int n);
int stringLength(char str[]);
int containsUppercase(char str[]);
int containsLowercase(char str[]);
int containsDigit(char str[]);
int containsSymbol(char str[]);
void userStatistics(struct User users[], int n);
void saveUsers(struct User users[], int n);
void loadUsers(struct User users[], int n);

