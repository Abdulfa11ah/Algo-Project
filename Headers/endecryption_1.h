#ifndef ENDECRYPTION_1_H
#define ENDECRYPTION_1_H

struct Message
{
    char text[200];
    int length;
}m,m1,m2;
void inputMessage(struct Message m[]);
void displayMessage(struct Message m);
int isUppercase(char c);
int isLowercase(char c);
int isAlphabetic(char c);
void toUppercase(struct Message m);
void toLowercase(struct Message m);
void reverseMesage(struct Message m);
void removeSpaces(struct Message m);
void encryptCesar(struct Message m, int key);
void decryptCesar(struct Message m, int key);
void encryptXOR(struct Message m, int key);
void decryptXOR(struct Mesage m, int key);
void encyptSubstitution(struct Message m,char key[26]);
void decryptSubstitution(struct Message m,char key[26]);
int isValidKey(char key[26]);
int compareMessages(struct Message m,char c);
int countCharcter(struct Message m,char c);
void frequencyAnalysis(struct Message m);
int coincidenceIndex(struct Mesage m);

#endif 