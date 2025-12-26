#include<stdio.h>
#include "../Headers/endecryption_1.h"
#include "../Headers/mathsecurity_2.h"
#include "../Headers/usermanage_3.h"
#include "../Headers/securityAudit_4.h"
#include "../Headers/logmanage_5.h"


int isEven(int n){
    return n%2==0;
}

int isPrime(int n){
    if (n<=1)return 0;
    for (int i = 2; i*i <=n; i++){
        if (n%i==0)return 0;
    }
    return 1;
}

int gcd(int a, int b){
    int temp;
    while (b!=0)
    {
        temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

int lcm(int a,int b){
    return (a*b)/gcd(a,b);
}
int modExp(int base, int exp, int mod){
    int result=1;
    base=base%mod;
    while (exp>0)
    {
        if (exp%2==1)
            result=(result*base)%mod;
        exp=exp>>1;
        base=(base*base)%mod;
    }
    return result;
}

int factorial(int n){
    if (n==0)return 1;
    else return n*factorial(n-1);
}
int sumDigits(int n){
    int sum=0;
    while (n>0)
    {
        sum+=n%10;
        n/=10;
    }
    return sum;
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

int reverseNumber(int n){
    int rev=0;
    while (n>0)
    {
        rev=rev*10+n%10;
        n/=10;
    }
    return rev;
}

int isPalindromeNumber(int n){
    return n==reversenumber(n);
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

int isPerfectNumber(int n){
    return sumDivisors(n)==n;
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

float averageArray(int T[],int n){
    int sum=sumArray(T,n);
    return (float)sum/(n+1);
}

int maxArray(int T[],int n){
    int max=T[0];
    for (int i = 1; i <=n; i++)
    {
        if (T[i]>max)max=T[i];
    }
    return max;
}

int minArray(int T[],int n){
    int min=T[0];
    for (int i = 1; i <=n; i++)
    {
        if (T[i]<min)min=T[i];
    }
    return min;
}

void sortAscending (int T[],int n){
    int temp;
    if (n==1) return;
    else if (n==0)return;
    else{
        for (int j = 0; j < n-1; j++){
        for (int i = 0; i < n-1; i++){
        if (T[i]>T[i+1]){
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
        for (int j = 0; j < M.p; j++){
            printf(" %4d ",M.data[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(struct Matrix A, struct Matrix B, struct Matrix *C) {
    if (A.n != B.n || A.p != B.p) {
        printf("Error");
    } else {
        for (int i = 0; i < A.n; i++) {
            for (int j = 0; j < A.p; j++) {
                C->data[i][j] = A.data[i][j] + B.data[i][j];
            }
        }
    }
}

void multiplyMatrices(struct Matrix A,struct Matrix B,struct Matrix *C){
    C->n = A.n;
    C->p = B.p;

    if (A.p!=B.n){
        printf("Cannot multiply matrices. Reminder: columns of A must equal rows of B.");
        return;
    }
    
    for (int i = 0; i < A.n; i++){
        for (int j = 0; j < B.p; j++){
            C->data[i][j]=0;
            for (int k = 0; k < A.p; k++){
                C->data[i][j]+=A.data[i][k]*B.data[k][j];
            } 
        }
    }
}


void transposeMatrix(struct Matrix A,struct Matrix *T){
    T->n = A.p;
    T->p = A.n;
    for (int i = 0; i < A.p; i++)
    {
        for (int j = 0; j < A.n; j++)
        {
            T->data[i][j]=A.data[j][i];
        }
        
    }
    
}

int determinant2x2(int A[2][2]){
    int determinate=A[0][0]*A[1][1]-A[0][1]*A[1][0];
    return determinate;
}

int isSymmetric(struct Matrix M){
    if (M.n!=M.p)return 0;
    for (int i = 0; i < M.n; i++){
        for (int j = 0; j < M.p; j++){
            if(M.data[i][j]!=M.data[j][i])return 0;
        }
    }  
    return 1;
}

int isIdentity(struct Matrix M){
    if (M.n!=M.p)return 0;
    for (int i = 0; i < M.n; i++){
        for (int j = 0; j < M.n; j++){
            if(i==j && M.data[i][i]!=1)return 0;
            else if(M.data[i][j]!=0)return 0;
        }
    }
    return 1;
}
