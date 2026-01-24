#include<stdio.h>
#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"

struct User {
    char name[20];
    char password[20];
    int role; // 0: user, 1: admin
    int state; // 0: active, 1: blocked
};

int comparechars(char a[], char b[]){
    int i;
    i = 0;
    while (a[i] == b[i]){
        if(a[i] == '\0' && b[i] =='\0'){
            return 1;
            i++;
        }
    }
    return 0;
}

void initUsers(struct User users[], int n){
    for (int i = 0; i < n; i++) {
        users[i].role = 0;
        users[i].state = 0;
    }
}

void displayUsers(struct User users[], int n){
    for (int i = 0; i < n; i++) {
        printf("User: %s , Password: %s, Role: %d, State: %d\n", users[i].name, users[i].password, users[i].role, users[i].state);
    }
}

void addUser(struct User users[], int n){
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (users[i].name[0] == '\0') {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("No space to add new user.\n");
        return;
    }
    printf("Add new user username:");
    scanf("%19s", users[pos].name);
    printf("enter password:");
    scanf("%19s", users[pos].password);
    printf("Enter role (0 for user, 1 for admin):");
    scanf("%d", &users[pos].role);
    printf("enter state (0 for active, 1 for blocked):");
    scanf("%d", &users[pos].state);
    printf("user added at position %d .", pos);
}

void deleteuser(struct User users[], int n, char name[]){
    int index;
    printf("Enter the index to delete:");
    scanf("%d", &index);
    if (index < 0 || index >= n){
        printf("Innvalid index.\n");
        return;
    }
    if(users[index].name[0] == '\0'){
        printf("Already empty.\n");
        return;
    }
    users[index].name[0]= '\0';
    users[index].password[0]= '\0';
    users[index].role= 0;
    users[index].state= 0;
    printf("Account deleted.\n");
}

int searchUser(struct User users[], int n, char name[]){
    int i;
    for (i = 0; i < n; i++){
        if(comparechars(users[i].name, name)){
            printf("user found at index %d\n", i);
            return i;
        }
    }
    printf("user not found.\n");
    return -1;
}

void changepassword(struct User users[], int n, char name []){
    int index;
    printf("Enter user index:");
    scanf("%d", &index);
    if (index < 0 || index >= n){
        printf("Innvalid index.\n");
        return;
    }
    if(users[index].name[0] == '\0'){
        printf("No account in this index.\n");
        return;
    }
    char newpassword[20];
    printf("Enter new password:");
    scanf("%19s", newpassword);
    int i;
    i =0;
    while(newpassword[i] != '\0' && i < 19){
        users[index].password[i]=newpassword[i];
        i++;
    }
    users[index].password[i] = '\0';
    printf("Password updated.");
}

int checklogin(struct User users[], int n, char name[], char pass[]){
    int i;
    for (i = 0 ; i < n ; i++){
        if(users[i].name[0 == '\0'])continue;
        if (comparechars(users[i].name, name) && comparechars(users[i].password, pass)){
            printf("Login successful for user %s \n", name );
            return 1;
        }   
    }
    printf("Login failed for user %s\n", name);
    return 0;
}

int strongpassword(char pass[]){
    int i;
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    for (i = 0; pass[i] != '\0'; i++){
        if (pass[i] >= 'A' && pass[i] <= 'Z') hasUpper = 1;
        else if (pass[i] >= 'a' && pass[i] <= 'z') hasLower = 1;
        else if (pass[i] >= '0' && pass[i] <= '9') hasDigit = 1;
        else hasSpecial = 1;
    }
    if (hasUpper && hasLower && hasDigit && hasSpecial && i >= 8){
        return 1;
    }
    return 0;
}

void blockuser(struct User users[], int n, char name[]){
    int index;
    printf("Enter user index to block:");
    scanf("%d", &index);
    if (index < 0 || index >= n){
        printf("Innvalid index.\n");
        return;
    }
    if(users[index].name[0] == '\0'){
        printf("No account in this index.\n");
        return;
    }
    users[index].state = 1;
    printf("User %s blocked.\n", users[index].name);
}

void unblockuser(struct User users[], int n, char name[]){
    int index;
    printf("Enter user index to unblock:");
    scanf("%d", &index);
    if (index < 0 || index >= n){
        printf("Innvalid index.\n");
        return;
    }
    if(users[index].name[0] == '\0'){
        printf("No account in this index.\n");
        return;
    }
    users[index].state = 0;
    printf("User %s unblocked.\n", users[index].name);
}

void changerole(struct User users[], int n, char name[], int role){
    int index;
    printf("Enter user index to change role:");
    scanf("%d", &index);
    if (index < 0 || index >= n){
        printf("Innvalid index.\n");
        return;
    }
    if(users[index].name[0] == '\0'){
        printf("No account in this index.\n");
        return;
    }
    users[index].role = role;
    printf("User %s role changed to %d.\n", users[index].name, role);
}

void listadmins(struct User users[], int n){
    printf("List of admin users:\n");
    for (int i = 0; i < n; i++) {
        if (users[i].role == 1 && users[i].name[0] != '\0') {
            printf("Admin User: %s , Password: %s, State: %d\n", users[i].name, users[i].password, users[i].state);
        }
    }
}

int stringlength(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        i++;
    }
    return i;
}
   
int containsuppercase(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            return 1;
        }
        i++;
    }
    return 0;
}

int containslowercase(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'a' && str[i] <= 'z'){
            return 1;
        }
        i++;
    }
    return 0;
}

int containsdigit(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= '0' && str[i] <= '9'){
            return 1;
        }
        i++;
    }
    return 0;
}

int containspecialsymbol(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        if ((str[i] >= 33 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64) ||
            (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126)){
            return 1;
        }
        i++;
    }
    return 0;
}

void userstatistics(struct User users[], int n){
    int totalUsers = 0, activeUsers = 0, blockedUsers = 0, adminUsers = 0;
    for (int i = 0; i < n; i++) {
        if (users[i].name[0] != '\0') {
            totalUsers++;
            if (users[i].state == 0) {
                activeUsers++;
            } else {
                blockedUsers++;
            }
            if (users[i].role == 1) {
                adminUsers++;
            }
        }
    }
    printf("Total Users: %d\n", totalUsers);
    printf("Active Users: %d\n", activeUsers);
    printf("Blocked Users: %d\n", blockedUsers);
    printf("Admin Users: %d\n", adminUsers);
}

void saveUsers(struct User users[], int n){
    FILE *file = fopen("users.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(users, sizeof(struct User), n, file);
    fclose(file);
    printf("Users saved to users.dat\n");
}

void loadUsers(struct User users[], int n){
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fread(users, sizeof(struct User), n, file);
    fclose(file);
    printf("Users loaded from users.dat\n");
}
