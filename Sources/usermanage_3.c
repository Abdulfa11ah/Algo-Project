#include <stdio.h>
#include <string.h>
#include "UserMan.h"


   // Initializes user list
 void initUsers(struct User users[], int n){
     for (int i = 0; i < n; i++){
         strcpy(users[i].name, "");
         strcpy(users[i].password , "");
         users[i].role  =  0  ;
         users[i].state =  2  ;
 }
}
    // Display all users
    void displayUsers(struct User users[], int n){
       printf("Users list : ");
       for (int i = 0 ; i < n ; i++ ){
         if (strcmp(users[i].name , "") != 0  ){
             printf("Name =%s ", users[i].name);
             printf("Role =%d ", users[i].role);
             printf("State =%d \n", users[i].state);
            }
       }
    }
    // Add a new user
    void addUser(struct User users[], int n) {
    printf("Enter information of new user:\n");

    for (int i = 0; i < n; i++) {
        if (users[i].state == EMPTY2 ) { // empty slot
            printf("Name: ");
            scanf("%19s", users[i].name);

            printf("Password: ");
            scanf("%19s", users[i].password);

            do {
                printf("Role (0: user, 1: admin): ");
                scanf("%d", &users[i].role);
            } while (users[i].role != 0 && users[i].role != 1);

            users[i].state = ACTIVE; // active
            printf("User added successfully.\n");
            return;
        }
    }
    printf("User list is full.\n");
}
  // Delete a user by name
   void deleteUser(struct User users [] , int n , char name []){
        printf("Enter name of user to delete: ");
        scanf("%19s", name);
        for (int i = 0 ; i < n ; i++ ){
            if (strcmp(users[i].name , name) == 0  ){
                strcpy(users[i].name , "");
                strcpy(users[i].password , "");
                users[i].role  =  0  ;
                users[i].state =  EMPTY2  ;
                printf("User %s deleted successfully.\n", name);
                return;
            }
        }
   }
   // Search for a user by name
    int searchUser(struct User users [] , int n , char name []){
        for (int i = 0 ; i < n ; i++ ){
            if (strcmp(users[i].name , name )==0){
                printf("User found : name = %s , password = %s, role = %d , state = %d\n",
                            users[i].name , users[i].password , users[i].role , users[i].state) ;
                return i; // Return index of found user
                }
            }
                printf("User %s not found.\n", name);
                return -1; // Return -1 if user not found       
    }

    // Change password for a user by name
    void changePassword(struct User users [] , int n , char name []){
         int index = searchUser(users,n,name);
         if (index != -1) {
            printf("Enter new password for user %s  : ",users[index].name);
            scanf("%19s", users[index].password);
            printf("Password changed successfully for user %s.\n", users[index].name);
        } else {
            printf("User %s not found. Cannot change password.\n", name);
         }
    }
    // verify login credentials
int checkLogin(struct User users[], int n, char name[], char pass[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].name, name) == 0 &&
            strcmp(users[i].password, pass) == 0) {
            return 1;   // login successful
        }
    }
    return 0;   // login failed
}
// Check if password is strong
 int strongPassword(char pass[]){
    int hasUpper = 0  , hasLower = 0 , hasNumber  = 0 , hasSymbol = 0 ;
    int Length = strlen(pass) ;
    if (Length < 8 ) return 0 ;
    for (int i = 0 ; i < Length ; i++ ){
        if (pass[i] >= 'A' && pass[i] <= 'Z') 
        hasUpper = 1 ;
        else if (pass[i] >= 'a' && pass[i] <= 'z') 
        hasLower = 1 ;
        else if (pass[i] >= '0' && pass[i] <= '9') 
        hasNumber = 1 ;
        else 
        hasSymbol = 1 ;
    }
    if (hasUpper * hasLower * hasNumber * hasSymbol != 0)
        return 1;
    else
        return 0;
}
// Block a user by name 
void blockUser(struct User users[], int n, char name[]){
    int index = searchUser(users , n , name);
    if (index != -1) {
        users[index].state = BLOCKED ;
        printf("User %s blocked successfully.\n", name);
    } else {
        printf("User %s not found. Cannot block user.\n", name);
    }
}
// Unblock a user by name
void unblockUser(struct User users[], int n, char name[]){
    int index = searchUser(users , n , name);
    if (index != -1) {
        users[index].state = ACTIVE ;
        printf("User %s unblocked successfully.\n", name);
    } else {
        printf("User %s not found. Cannot unblock user.\n", name);
    }
}
// Change role of a user by name
void changeRole(struct User users[], int n, char name[], int newRole) {
    int index = searchUser (users , n , name);
    if (index == -1) {
        printf("User %s not found.\n", name);
        return;
    }
    if (index != -1) {
        if (users[index].role ==  USER && newRole == ADMIN || users[index].role == ADMIN && newRole == USER ) {
            users[index].role = newRole ;
            printf("User %s role changed successfully to %d.\n", name, newRole);
        } else {
            printf("Invalid role change for user %s.\n", name);
        }
    }
}
// List all admin users
void listAdmins(struct User users [] , int n ){
    printf("Admin users List : ");
    for (int i = 0 ; i < n ; i++){
        if (users[i].role == ADMIN && users[i].state != EMPTY2){
            printf("Name = %s", users[i].name);
            printf(" Password = %s", users[i].password);
            printf(" State = %d\n", users[i].state);
            
        }
    }
}
 // string Length 
    int stringLength(char str[]){
     int Length = 0 ;
     while (str[Length] != '\0'){
        Length++ ;
     }
      return Length ;
    }
  // checks for Uppercase
   int containsUppercase(char str[]) {
    int Length = stringLength(str);

    for (int i = 0; i < Length; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            return 1;  // Uppercase found
        }
    }
    return 0;  // No uppercase found
}
 // checks for Lowercase
   
       int containsLowercase(char str[]) {
    int Length = stringLength(str);

    for (int i = 0; i < Length; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            return 1;  // Uppercase found
        }
    }
    return 0;  // No uppercase found
} 

 // checks for Digit
    int containsDigits(char str[]) {
    int Length = stringLength(str);

    for (int i = 0; i < Length; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            return 1;  // Uppercase found
        }
    }
    return 0;  // No uppercase found
}
 // checks for Symbol
    int containsSymbol(char str[]){
        int Length = stringLength(str)  ; 
        for (int i = 0 ; i < Length ; i++){
            if ( (str[i] >= 33 && str[i] <= 47) || (str[i] >=58 && str[i] <=64) ||
                 (str[i] >=91 && str[i] <=96) || (str[i] >=123 && str[i] <=126) )
            return 1 ; 
        }
       
        return 0;
}
// Display user statistics 
    void userStatistics(struct User users [] , int n ){
        int totalUsers = 0 , blockUsers = 0 , adminUsers = 0 ;
        for (int i = 0 ; i < n ; i++){
            if (users[i].state != EMPTY2){
                totalUsers++ ;
                if (users[i].state == BLOCKED)
                blockUsers++ ;
                if (users[i].role == ADMIN)
                adminUsers++ ;
            }
        }
        printf("Total users: %d\n", totalUsers);
        printf("Blocked users: %d\n", blockUsers);
        printf("Admin users: %d\n", adminUsers);
    }
    // Save users to file
    void saveUsers(struct User users[], int n) {
        FILE *file = fopen("users.txt", "w");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }
        for (int i = 0; i < n; i++) {
            if (users[i].state != EMPTY2) {
                fprintf(file, "%s %s %d %d\n", users[i].name, users[i].password, users[i].role, users[i].state);
            }
        }
        fclose(file);
        printf("Users saved to file successfully.\n");
    }
    // Load users from file
    void loadUsers(struct User users[], int n) {
         FILE *file = fopen("users.txt", "r");
        if (file == NULL) {
            printf("Error opening file for reading.\n");
            return;
        }
        for (int i = 0 ; i < n ; i++){
          if (fscanf(file, "%19s %19s %d %d", users[i].name, users[i].password, &users[i].role, &users[i].state) != 4) {
                break; // Stop if we can't read a full user record
            }
        }
        fclose(file);
        printf("Users loaded from file successfully.\n");
    }

