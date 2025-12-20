#ifndef SECURITYAUDIT_4_H
#define SECURITYAUDIT_4_H

/* declarations here */
int countUppercase(char text[]);
int countLowercase(char text[]);
int countDigits(char text[]);
float percentUppercase(char text[]);
int textLength(char text[]);
void displayTextStats(char text[]);
int veryStrongPassword(char pass[]);
void generateKey(int length, char key[]);
int isHexKey(char key[]);
void generateRandomPassword(int length,char pass[]);

#endif 