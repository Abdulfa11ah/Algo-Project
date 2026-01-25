#include<stdio.h>
#include "../Headers/endecryption_1.h"
#include "../Headers/mathsecurity_2.h"
#include "../Headers/usermanage_3.h"
#include "../Headers/securityAudit_4.h"
#include "../Headers/logmanage_5.h"

void initUsers(struct User users[], int n) {
    for(int i = 0; i < n; i++) {
        strcpy(users[i].name, "");
        strcpy(users[i].password, "");
        users[i].role = 0;
        users[i].state = 2; // EMPTY
    }
}

void displayUsers(struct User users[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d. %s | %s | %d | %d\n",
               i+1, users[i].name, users[i].password, users[i].role, users[i].state);
    }
}

void addUser(struct User users[], int n) {
    if(userCount >= n) {
        printf("User list is full.\n");
        return;
    }
    printf("Enter name: ");
    scanf("%s", users[userCount].name);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    printf("Enter role (0: user, 1: admin): ");
    scanf("%d", &users[userCount].role);
    users[userCount].state = 0; // Active
    userCount++;
}

void deleteUser(struct User users[], int n, char name[]) {
    int found = -1;
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if(found != -1) {
        for(int i = found; i < userCount - 1; i++) {
            users[i] = users[i + 1];
        }
        userCount--;
    }
}

int searchUser(struct User users[], int n, char name[]) {
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].name, name) == 0) {
            printf("User found: %s | %s | %d | %d\n",
                   users[i].name, users[i].password, users[i].role, users[i].state);
            return i;
        }
    }
    printf("User %s not found.\n", name);
    return -1;
}

void changePassword(struct User users[], int n, char name[]) {
    int index = searchUser(users, n, name);
    if(index != -1) {
        printf("Enter new password for user %s: ", name);
        scanf("%s", users[index].password);
        printf("Password changed successfully for user %s.\n", name);
    } else {
        printf("User %s not found. Cannot change password.\n", name);
    }
}

int checkLogin(struct User users[], int n, char name[], char pass[]) {
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].name, name) == 0 && strcmp(users[i].password, pass) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

int strongPassword(char pass[]) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSymbol = 0;
    int length = strlen(pass);
    if(length < 8) return 0;
    for(int i = 0; i < length; i++) {
        if(isupper(pass[i])) hasUpper = 1;
        else if(islower(pass[i])) hasLower = 1;
        else if(isdigit(pass[i])) hasDigit = 1;
        else hasSymbol = 1;
    }
    return (hasUpper + hasLower + hasDigit + hasSymbol) >= 3 ? 1 : 0;
}

void blockUser(struct User users[], int n, char name[]) {
    int index = searchUser(users, n, name);
    if(index == -1) {
        printf("User %s not found.\n", name);
        return;
    }
    users[index].state = 1;
}

void unblockUser(struct User users[], int n, char name[]) {
    int index = searchUser(users, n, name);
    if(index == -1) {
        printf("User %s not found.\n", name);
        return;
    }
    users[index].state = 0;
}

void changeRole(struct User users[], int n, char name[], int role) {
    int index = searchUser(users, n, name);
    if(index == -1) {
        printf("User %s not found.\n", name);
        return;
    }
    if(role == 0 || role == 1) {
        users[index].role = role;
        printf("Role changed successfully for user %s.\n", name);
    } else {
        printf("Invalid role. Please enter 0 for user or 1 for admin.\n");
    }
}

void listAdmins(struct User users[], int n) {
    printf("Admin Users:\n");
    for(int i = 0; i < userCount; i++) {
        if(users[i].role == 1) {
            printf("%s | %s | %d | %d\n",
                   users[i].name, users[i].password, users[i].role, users[i].state);
        }
    }
}

int stringLength(char str[]) {
    int len = 0;
    while(str[len] != '\0') len++;
    return len;
}

int containsUppercase(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(isupper(str[i])) return 1;
    }
    return 0;
}

int containsLowercase(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(islower(str[i])) return 1;
    }
    return 0;
}

int containsDigit(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(isdigit(str[i])) return 1;
    }
    return 0;
}

int containsSymbol(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalnum(str[i])) return 1;
    }
    return 0;
}

void userStatistics(struct User users[], int n) {
    int totalUsers = 0, activeUsers = 0, blockedUsers = 0, adminUsers = 0;
    for(int i = 0; i < userCount; i++) {
        totalUsers++;
        if(users[i].state == 0) activeUsers++;
        else if(users[i].state == 1) blockedUsers++;
        if(users[i].role == 1) adminUsers++;
    }
    printf("Total Users: %d\n", totalUsers);
    printf("Active Users: %d\n", activeUsers);
    printf("Blocked Users: %d\n", blockedUsers);
    printf("Admin Users: %d\n", adminUsers);
}

void saveUsers(struct User users[], int n) {
    FILE *file = fopen("users.txt", "w");
    if(file) {
        fprintf(file, "%d\n", userCount);
        for(int i = 0; i < userCount; i++) {
            fprintf(file, "%s %s %d %d\n",
                    users[i].name, users[i].password,
                    users[i].role, users[i].state);
        }
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

void loadUsers(struct User users[], int n) {
    FILE *file = fopen("users.txt", "r");
    if(file) {
        fscanf(file, "%d\n", &userCount);
        for(int i = 0; i < userCount; i++) {
            fscanf(file, "%s %s %d %d\n",
                   users[i].name, users[i].password,
                   &users[i].role, &users[i].state);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}
