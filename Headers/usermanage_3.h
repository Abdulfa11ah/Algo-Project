#ifndef USERMANAGE_4_H
#define USERMANAGE_3_H
struct User {
    char name[20];
    char password[20];
    int role; // 0: user, 1: admin
    int state; // 0: active, 1: blocked
};

#endif 
