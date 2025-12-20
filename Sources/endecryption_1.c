#include<stdio.h>
#include "../Headers/endecryption_1.h"
#include "../Headers/mathsecurity_2.h"
#include "../Headers/usermanage_3.h"
#include "../Headers/securityAudit_4.h"
#include "../Headers/logmanage_5.h"

void inputMessage(struct Message m[]){
    printf("Please enter a message less then 200 characters: \n");
    for (int i = 0; i < m->length; i++)
    {
        scanf("%c",m->text[i]);
    }
    
}
void displayMessage(struct Message m){
    for (int i = 0; i < m.length; i++)
    {
        printf("%c",m.text[i]);
    }
    
}
int isUppercase(char c){
    if (c<=90&&c>=65) return 1;
    else if (c<=122&&c>=97) return 0;
}
int isLowercase(char c){
    if (c<=90&&c>=65) return 0;
    else if (c<=122&&c>=97) return 1;   
}
int isAlphabetic(char c){
    if ((c<=90&&c>=65)||(c<=122&&c>=97)) return 1;
    else return 0;
}
void toUppercase(struct Message *m){
    for (int i = 0; i < m->length; i++){
        if (m->text[i]<=122||m->text[i]>=97){
            m->text[i]-=32;
        }
    } 
}
void toLowercase(struct Message m){
    for (int i = 0; i < m.length; i++)
    {
        if (m.text[i]<=90||m.text[i]>=65)
        {
            m.text[i]+=32;
        }
        
    } 
}
void reverseMesage(struct Message *m){
    char temp;
    for (int i = 0; i < length/2; i++)
    {
        temp=m->text[i];
        m->text[i]=m->text[length-i-1];
        m->text[length-i-1]=temp;
    }
}
void removeSpaces(struct Message *m){7
    for (int i = 0; i < length; i++){
        if (m->text[i]!=32){
            
        }   
    }
}
void encryptCesar(struct Message *m, int *key){
    printf("Enter the key: ");
    scanf("%d",key);
    *key=*key%26;
    for (int i = 0; i < m->length; i++){
        if (isUppercase){
            m->text[i]=('A'+(m->text[i]+*key-'A')%26);
        }else if(isLowercase){
            m->text[i]=('a'+(m->text[i]+*key-'a')%26);
        }
    } 
}
void decryptCesar(struct Message *m, int *key){
    printf("Enter the key: ");
    scanf("%d",key);
    *key=*key%26;
    for (int i = 0; i < m->length; i++){
        if (isUppercase){
            m->text[i]=('Z'-(m->text[i]-*key+'Z')%26);
        }else if(isLowercase){
            m->text[i]=('z'-(m->text[i]-*key+'z')%26);
        }
    } 
}
void encryptXOR(struct Message *m, int *key){
    // printf("Enter the key: ");
    // scanf("%d",key);
    for (int i = 0; i < m->length; i++){
        m->text[i]=m->text[i]^*key;
    }
    
}
void decryptXOR(struct Message *m, int *key){
    // printf("Enter the key: ");
    // scanf("%d",key);
    for (int i = 0; i < m->length; i++){
        m->text[i]=m->text[i]^*key;
    }
}
void encyptSubstitution(struct Message *m,char key[26]){
    if(isValidKey(key)){
        for (int i = 0; i < m->length; i++){
            if(isUppercase(m->text[i]))m->text[i]=key[m->text[i]-'A'];
            if(isLowercase(m->text[i]))m->text[i]=key[m->text[i]-'a'];
        }
    }else{
        printf("Invalid key. Try again!");
    }
}
void decryptSubstitution(struct Message *m,char key[26]){
    if(isValidKey(key)){
        for (int i = 0; i < m->length; i++){
            if(isUppercase(m->text[i]))m->text[i]=key[m->text[i]+'A'];
            if(isLowercase(m->text[i]))m->text[i]=key[m->text[i]+'a'];
        }
    }else{
        printf("Invalid key. Try again!");
    }
}
int isValidKey(char key[26]){
    for (int i = 0; i < 26; i++){
       if(!isAlphabetic(char[26]))return 0;
    }
    return 1;
}
int compareMessages(struct Message m1,struct Message m2){
    if (m1.length!=m2.length)return 0;
    for (int i = 0; i < m1.length; i++){
        if (m1.text[i]!=m2.text[i])return 0;  
    }
    return 1;
}
int countCharcter(struct Message m,char c){
    int times=0;
    for (int i = 0; i < m.length; i++){
        if(m.text[i]==c)times++;
    }
    return times;
}
void frequencyAnalysis(struct Message *m){
    toUppercase(m);
    for (int i = 'A'; i <= 'Z'; i++){
        int count=0;
        for (int j = 0; j < m->length; j++){
            if (m->text[j]==i)count++;
        }
        if(count>0)printf("%c : %d \n",i,count);
    }
}
void frequencyAnalysis(struct Message *m,int freq[26]){
    toUppercase(m);
    for(int i=0;i<m->length;i++){
        if(isUppercase(m->text[i]))freq[m->text[i]-'A']++;
    }
    // for (int j = 0; j < 26; j++){
    //     if (arr[j]!=0)printf("%c : %d \n",j+'A',arr[j]);
    // }
    
}
float coincidenceIndex(struct Mesage *m){
    float IC,sum=0,N=0;
    int freq[26]={0};
    frequencyAnalysis(m,freq);
    for (int i = 0; i < 26; i++){
        sum+=freq[i]*(freq[i]-1);
        N+=freq[i];
    }
    IC=sum/(N*(N-1));
    return IC;
}

