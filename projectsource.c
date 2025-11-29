#include "projectheader.h"

int add(int a,int b){
    return a+b;
}
int gcd(int a,int b){
    if(a%b==0)return b;
    return gcd(b,a%b);
}