#include<stdio.h>
#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"

int countUppercase(char text[]){
    int i=0,coun=0;
    while (text[i]!=0)
    {
        if (text[i]<=90&&text[i]>=65)coun++;
        i++;
    }
    return coun; 
}

int countLowercase(char text[]){
    int i=0,coun=0;
    while (text[i]!=0)
    {
        if (text[i]<=122&&text[i]>=97)coun++;
        i++;
    }
    return coun;    
}
int countDigits(char text[]){
    int i=0,coun=0;
    while (text[i]!=0)
    {
        if (text[i]<=57&&text[i]>=48)coun++;
        i++;
    }
    return coun;     
}
float percentUppercase(char text[]){
    int i=0,coun=0,size=1;
    while (text[i]!=0)
    {
        if (text[i]<=90&&text[i]>=65)coun++;
        i++;size++;
    }
    return 100*coun/(size-1);  
}
int textLength(char text[]){
    int i=0,length=1;
    while (text[i]!=0)
    {
        length++;i++;
    }
    return length-1;
}
void displayTextStats(char text[]){
    printf("Total Uppercase Letters: %d\n",countUppercase(text[]));
    printf("Total Lowercase Letters:%d\n",countLowercase(text[]));
    printf("Total    Digits   found: %d\n",countDigits(text[]));
    printf("Percentage of Uppercase: %.2f\n",percentUppercase(text[]));
    printf("Length      of     Text: %d",textLength(text[]));
}
int veryStrongPassword(char pass[]){

}
void generateKey(int length, char key[]){

}
int isHexKey(char key[]){
    
}
void generateRandomPassword(int length,char pass[]){
    
}


