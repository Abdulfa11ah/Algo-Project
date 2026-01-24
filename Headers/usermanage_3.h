#ifndef USERMAN_H
#define USERMAN_H
// Define your User struct in your .c or another header before using these functions
 

#define MAX_USERS 100

#define EMPTY2   2
#define ACTIVE  0
#define BLOCKED 1
#define USER    0
#define ADMIN   1

 struct User{
char name[20];
char password[20];
int role; // 0: user, 1: admin
int state; // 0: active, 1: blocked 2: empty
};
char Max_USERS [20];
// Initialize an array of users
 void initUsers(struct User users[], int n); 
 // Display all users
 void displayUsers(struct User users[], int n); 
    // Add a new user
 void addUser(struct User users[], int n); 
    // Delete a user by name
 void deleteUser(struct User users[], int n, char name[]); 
    // Search for a user by name, return index or -1 if not found
 int searchUser(struct User users[], int n, char name[]); 
    // Change password for a user by name
 void changePassword(struct User users[], int n, char name[]);
    // Check login credentials, return 1 if valid, 0 otherwise
 int checkLogin(struct User users[], int n, char name[], char pass[]);
    // Check if password is strong (at least 8 chars, includes uppercase, lowercase, digit, symbol)
 int strongPassword(char pass[]); 
    // Block a user by name
 void blockUser(struct User users[], int n, char name[]); 
    // Unblock a user by name
 void unblockUser(struct User users[], int n, char name[]);
    // Change role of a user by name
 void changeRole(struct User users[], int n, char name[], int role);
    // List all admin users
 void listAdmins(struct User users[], int n); 
    // Get length of a string
 int stringLength(char str[]);
    // Check if string contains uppercase, lowercase, digit, symbol
 int containsUppercase(char str[]); 
    // Check if string contains lowercase
 int containsLowercase(char str[]); 
   // Check if string contains digit
 int containsDigits(char str[]);
    // Check if string contains symbol
 int containsSymbol(char str[]); 
    // Display user statistics
 void userStatistics(struct User users[], int n); 
    // Saves users to file.
 void saveUsers(struct User users[], int n); 
    //Loads users from file
 void loadUsers(struct User users[], int n); 

#endif 
