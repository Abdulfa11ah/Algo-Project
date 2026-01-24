#include<stdio.h>
#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"

int main(){
    return 0;
}


void subMenuUserManagement() {
    struct User users[MAX_USERS];
    int n = MAX_USERS;
    int choice;
    char name[20], password[20];
    int role;

    // Initialize users
    initUsers(users, n);

    do {
        printf("\n===== Full User Management Menu =====\n");
        printf("0. Exit\n");
        printf("1. Display all users\n");
        printf("2. Add a new user\n");
        printf("3. Delete a user\n");
        printf("4. Change user password\n");
        printf("5. Search for a user\n");
        printf("6. Block a user\n");
        printf("7. Unblock a user\n");
        printf("8. Change user role\n");
        printf("9. List all admins\n");
        printf("10. Display user statistics\n");
        printf("11. Save users to file\n");
        printf("12. Load users from file\n");
        printf("13. String length\n");
        printf("14. Check contains uppercase\n");
        printf("15. Check contains lowercase\n");
        printf("16. Check contains digits\n");
        printf("17. Check contains symbol\n");
        printf("18. Check login credentials\n");
        printf("19. Strong password check\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 0) {
            printf("Exiting menu...\n");
            break;  // exit while loop
        }

        switch (choice) {
            case 1: displayUsers(users, n); break;
            case 2: addUser(users, n); break;
            case 3:
                printf("Enter username to delete: ");
                scanf("%s", name);
                deleteUser(users, n, name);
                break;
            case 4:
                printf("Enter username to change password: ");
                scanf("%s", name);
                changePassword(users, n, name);
                break;
            case 5:
                printf("Enter username to search: ");
                scanf("%s", name);
                int idx = searchUser(users, n, name);
                if (idx != -1)
                    printf("User found: Name=%s, Role=%d, State=%d\n",
                        users[idx].name, users[idx].role, users[idx].state);
                else
                    printf("User not found.\n");
                break;
            case 6:
                printf("Enter username to block: ");
                scanf("%s", name);
                blockUser(users, n, name);
                break;
            case 7:
                printf("Enter username to unblock: ");
                scanf("%s", name);
                unblockUser(users, n, name);
                break;
            case 8:
                printf("Enter username to change role: ");
                scanf("%s", name);
                printf("Enter new role (0=user, 1=admin): ");
                scanf("%d", &role);
                changeRole(users, n, name, role);
                break;
            case 9: listAdmins(users, n); break;
            case 10: userStatistics(users, n); break;
            case 11: saveUsers(users, n); break;
            case 12: loadUsers(users, n); break;
            case 13:
                printf("Enter string: ");
                scanf(" %[^\n]", name);
                printf("Length: %d\n", stringLength(name));
                break;
            case 14:
                printf("Enter string: ");
                scanf(" %[^\n]", name);
                printf("Contains uppercase: %d\n", containsUppercase(name));
                break;
            case 15:
                printf("Enter string: ");
                scanf(" %[^\n]", name);
                printf("Contains lowercase: %d\n", containsLowercase(name));
                break;
            case 16:
                printf("Enter string: ");
                scanf(" %[^\n]", name);
                printf("Contains digits: %d\n", containsDigits(name));
                break;
            case 17:
                printf("Enter string: ");
                scanf(" %[^\n]", name);
                printf("Contains symbol: %d\n", containsSymbol(name));
                break;
            case 18:
                printf("Enter username: ");
                scanf("%s", name);
                printf("Enter password: ");
                scanf("%s", password);
                if (checkLogin(users, n, name, password))
                    printf("Login valid.\n");
                else
                    printf("Login invalid.\n");
                break;
            case 19:
                printf("Enter password to check: ");
                scanf("%s", password);
                if (strongPassword(password))
                    printf("Password is strong.\n");
                else
                    printf("Password is weak.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }while(choice != 0);
}
#define MAX_USERS 100

