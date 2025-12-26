#include <stdio.h>
#include <time.h>
#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"

int countUppercase(char text[])
{
    int i = 0, coun = 0;
    while (text[i] != 0)
    {
        if (text[i] <= 90 && text[i] >= 65)
            coun++;
        i++;
    }
    return coun;
}

int countLowercase(char text[])
{
    int i = 0, coun = 0;
    while (text[i] != 0)
    {
        if (text[i] <= 122 && text[i] >= 97)
            coun++;
        i++;
    }
    return coun;
}
int countDigits(char text[])
{
    int i = 0, coun = 0;
    while (text[i] != 0)
    {
        if (text[i] <= 57 && text[i] >= 48)
            coun++;
        i++;
    }
    return coun;
}
float percentUppercase(char text[])
{
    int i = 0, coun = 0, size = 1;
    while (text[i] != 0)
    {
        if (text[i] <= 90 && text[i] >= 65)
            coun++;
        i++;
        size++;
    }
    return 100 * coun / (size - 1);
}
int textLength(char text[])
{
    int i = 0, length = 1;
    while (text[i] != 0)
    {
        length++;
        i++;
    }
    return length - 1;
}
void displayTextStats(char text[])
{
    printf("Total Uppercase Letters: %d\n", countUppercase(text[]));
    printf("Total Lowercase Letters:%d\n", countLowercase(text[]));
    printf("Total    Digits   found: %d\n", countDigits(text[]));
    printf("Percentage of Uppercase: %.2f\n", percentUppercase(text[]));
    printf("Length      of     Text: %d", textLength(text[]));
}
int veryStrongPassword(char pass[])
{
}
void generateKey(int length, char key[])
{
    char base[36] = "0123456789abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++)
    {
        key[i] = base[time(NULL) % 36]
    }
    key[length] = '\0';
}
int isHexKey(char key[])
{
    if (key[0] == '\0')
        return 0;
    int i = 0;
    while (key[i] != '\0')
    {
        if (!((key[i] >= '0' && key[i] <= '9') ||
              (key[i] >= 'a' && key[i] <= 'f') ||
              (key[i] >= 'A' && key[i] <= 'F')))
            return 0;
        i++;
    }
    return 1;
}
void generateRandomPassword(int length, char pass[])
{
    char base[75] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*()_+-=[]{}|;:'";
    for (int i = 0; i < length; i++)
    {
        pass[i] = base[time(NULL) % 36]
    }
}
int passwordScore(char pass[])
{
    if (pass[0] == '\0')
        return 0;
    int i, score = 0, lower = 0, upper = 0, digit = 0, symbols = 0;
    for (i = 0; pass[i] != '\0'; i++)
    {
        if (isLowercase(pass[i]))
            lower = 1;
        else if (isUppercase(pass[i]))
            upper = 1;
        else if (pass[i] >= '0' && pass[i] <= '9')
            digit = 2;
        else
            symbols = 2;
    }
    if (i >= 8)
        score += 2;
    if (i >= 12)
        score += 2;
    score += lower + upper + digit + symbols;

    return score;
}
float averageScore(struct User users[], int n)
{
    if (n <= 0)
        return 0.0f;
    float total = 0;
    for (int i = 0; i < n; i++)
    {
        total += passwordScore(users[i].password);
    }
    return total / n;
}
void displaySecurityReport(struct User users[], int n)
{
    printf("1. Total users: %d ", n);
}
int countStrongUsers(struct User users[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (passwordScore(users[i].password) >= 7)
            count++;
    }
    return count;
}
void showSecurityTips()
{
    printf("Security Tips:\n");
    printf("1. Use a mix of uppercase, lowercase, numbers, and symbols.\n");
    printf("2. Avoid common words or patterns.\n");
    printf("3. Change passwords regularly.\n");
    printf("4. Enable two-factor authentication when available.\n");
}
int checkEmailFormat(char email[])
{
    int length = 0, atCount = 0, domainpart, dotAfterAt = 0;
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[0] == '@' ||
            email[0] == '.' ||
            (email[i] == '.' && email[i + 1] == '.') ||
            email[i] == '!' ||
            email[i] == '#' ||
            email[i] == '$' ||
            email[i] == '%' ||
            email[i] == '&' ||
            email[i] == '*' ||
            email[i] == '(' ||
            email[i] == ')' ||
            email[i] == ' ')
            return 0;
        if (email[i] == '@')
            atCount++;
        if (atCount == 1 && email[i] == '.')
            dotAfterAt = 1 length += 1;
    }
    if (email[length - 1] == '@' ||
        email[length - 1] == '.' ||
        atCount != 1 ||
        dotAfterAt == 0 ||
        length < 8)
        return 0;

    return 1;
}
int checkLoginFormat(char name[])
{
}
void generateHexKey(int length, char key[])
{
}
void top3Passwords(struct User users[], int n)
{
}
int globalSecurityLevel(struct User users[], int n    )
{
}
int checkEmailFormat(char email[])
{
}