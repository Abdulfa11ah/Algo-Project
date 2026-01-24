#ifndef USERMANAGE_4_H
#define USERMANAGE_3_H
struct User {
    char name[20];
    char password[20];
    int role; // 0: user, 1: admin
    int state; // 0: active, 1: blocked
};
int comparechars(char a[], char b[])
void initUsers(struct User users[], int n)
void displayUsers(struct User users[], int n)
void addUser(struct User users[], int n)
void deleteuser(struct User users[], int n, char name[])
int searchUser(struct User users[], int n, char name[])
void changepassword(struct User users[], int n, char name [])
int checklogin(struct User users[], int n, char name[], char pass[])
int strongpassword(char pass[])
void blockuser(struct User users[], int n, char name[])
void unblockuser(struct User users[], int n, char name[])
void changerole(struct User users[], int n, char name[], int role)
void listadmins(struct User users[], int n)
int stringlength(char str[])
int containsuppercase(char str[])
int containslowercase(char str[])
int containsdigit(char str[])
int containspecialsymbol(char str[])
void userstatistics(struct User users[], int n)
void saveUsers(struct User users[], int n)
void loadUsers(struct User users[], int n)

#endif 
