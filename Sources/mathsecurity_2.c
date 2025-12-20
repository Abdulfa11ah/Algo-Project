#include<stdio.h>
#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"

int isPrime(int num){
    int prime;
    prime=1;
    if(num<=1){
        prime=0;
    }else{
    for (int i = 2; i < num/2 && prime==1; i++ )
    {
        if(num%i==0){
            prime=0;
        }
    }
}
    return prime;
}
int gcd(int a,int b){
    if(a%b==0)return b;
    return gcd(b,a%b);
}
int factorial(int n){
    if (n=0)return 1;
    else return n*factorial(n-1);
}
int countdigits(int n){
    int digit;
    while (n>0)
    {
        n/=10;
        digit++;
    }
    return digit;
}
int reversenumber(int n){
    int rev=0;
    while (n>0)
    {
        rev=rev*10+n%10;
        n/=10;
    }
    return rev;
}
int sumDivisors(int n){
    int sum=0;
    for (int i = 1; i <=n/2; i++)
    {
        if(n%i==0){
            sum+=i;
        }
    }
    return sum;
}
int isArmstrong(int n){
    int sum=0,temp=n,digits=0;
    while (temp>0)
    {
        digits++;
        temp/=10;
    }
    temp=n;
    while (temp>0)
    {
        int r=temp%10;
        int p=1;
        for (int i = 0; i < digits; i++)
        {
            p*=r;
        }
        sum+=p;
        temp/=10;
    }
    return sum==n;
}
int sumArray(int T[],int n){
    int sum=0;
    for (int i = 0; i <=n; i++)
    {
        sum+=T[i];
    }
    return sum;
}
int maxArray(int T[],int n){
    int max=T[0];
    for (int i = 1; i <=n; i++)
    {
        if (T[i]>max)max=T[i]
    }
    return max;
}
void sortAscending (int T[],int n){
    int temp;
    if (n=1)break;
    else if (n=0)break;
    else{
    for (int j = 0; j < n-1; j++){
       for (int i = 0; i < n-1; i++){
    
        if (T[i]>T[i+1])
        {
            temp=T[i];
            T[i]=T[i+1];
            T[i+1]=temp;
        }  
    }
    }
    }
}
void displayMatrix(struct Matrix M){
    for (int i = 0; i < M.n; i++){
        for (int j = 0; i < M.p; i++){
            printf(" %d ",M.data[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(struct Matrix A,struct Matrix B,struct Matrix *C){
    if (A.n!=B.n||A.p!=B.p)
     {
        printf("Error");
    }else{
        for (int i = 0; i < A.n; i++)
        {
            for (int j = 0; j < A.p; j++)
            {
                C->data[i][j]=A.data[i][j]+B.data[i][j];
            }
            
        }
     }
     
}
void transposeMatrix(struct Matrix A,struct Matrix *T){
    for (int i = 0; i < A.p; i++)
    {
        for (int j = 0; i < A.p; i++)
        {
            T->data[i][j]=A.data[j][i];
        }
        
    }
    
}

