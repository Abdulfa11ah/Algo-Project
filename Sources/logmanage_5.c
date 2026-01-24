#include<stdio.h>
#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"


int comparechars(char a[], char b[]){
    int i = 0;
    while (a[i] == b[i]){
        if(a[i] == '\0' && b[i] =='\0'){
            return 1;
        }
        i++;
    }
    return 0;
}

void initLogs(struct Log logs[], int n){
    for (int i = 0; i < n; i++){
        logs[i].time[0] = '\0';
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
    }
}

void addLog(struct Log logs[], int n, char user[], char action[], int code){
    for (int i = 0; i < n; i++){
        if (logs[i].time[0] == '\0'){
            snprintf(logs[i].user, sizeof(logs[i].user), "%s", user);
            snprintf(logs[i].action, sizeof(logs[i].action), "%s", action);
            // For simplicity, using fixed date/time. In real scenario, fetch current date/time.
            snprintf(logs[i].date, sizeof(logs[i].date), "2024-01-01");
            snprintf(logs[i].time, sizeof(logs[i].time), "12:00:00");
            logs[i].code = code;
            return;
        }
    }
    printf("Log storage full, cannot add new log.\n");
}

void displayLogs(struct Log logs[], int n){
    for (int i = 0; i < n; i++){
        if (logs[i].time[0] != '\0'){
            printf("Log %d: [%s] User: %s Action: %s\n", i, logs[i].time, logs[i].user, logs[i].action);
        }
    }
}

void searchLogsByUser(struct Log logs[], int n, char user[]){
    int found = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].user[0] != '\0' && comparechars(logs[i].user, user)){
            printf("Log %d: [%s] User: %s Action: %s\n", i, logs[i].time, logs[i].user, logs[i].action);
            found = 1;
        }
    }
    if (!found){
        printf("No logs found for user %s.\n", user);
    }
}

void searchLogsByDate(struct Log logs[], int n, char date[]){
    int found = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].time[0] != '\0' && strncmp(logs[i].time, date, 10) == 0){
            printf("Log %d: [%s] User: %s Action: %s\n", i, logs[i].time, logs[i].user, logs[i].action);
            found = 1;
        }
    }
    if (!found){
        printf("No logs found for date %s.\n", date);
    }
}

int countErrorLogs(struct Log logs[], int n){
    int count = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].action[0] != '\0' && strstr(logs[i].action, "ERROR") != NULL){
            count++;
        }
    }
    return count;
}

int countLoginLogs(struct Log logs[], int n){
    int count = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].action[0] != '\0' && strstr(logs[i].action, "LOGIN") != NULL){
            count++;
        }
    }
    return count;
}

int countBlockedLogs(struct Log logs[], int n){
    int count = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].action[0] != '\0' && strstr(logs[i].action, "BLOCKED") != NULL){
            count++;
        }
    }
    return count;
}

void DisplayLogStats(struct Log logs[], int n){
    int errorCount = countErrorLogs(logs, n);
    int loginCount = countLoginLogs(logs, n);
    int blockedCount = countBlockedLogs(logs, n);

    printf("Log Statistics:\n");
    printf("Total ERROR logs: %d\n", errorCount);
    printf("Total LOGIN logs: %d\n", loginCount);
    printf("Total BLOCKED logs: %d\n", blockedCount);
}

void SortLogsByDate(struct Log logs[], int n){
    struct Log temp;
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (logs[i].time[0] != '\0' && logs[j].time[0] != '\0' &&
                strcmp(logs[i].time, logs[j].time) > 0){
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
        }
    }
}

void sortLogsByUser(struct Log logs[], int n){
    struct Log temp;
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (logs[i].user[0] != '\0' && logs[j].user[0] != '\0' &&
                strcmp(logs[i].user, logs[j].user) > 0){
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
        }
    }
}

int DetectSuspiciousActivity(struct Log logs[], int n, char user[]){
    int suspiciousCount = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].user[0] != '\0' && comparechars(logs[i].user, user)){
            if (strstr(logs[i].action, "FAILED LOGIN") != NULL || strstr(logs[i].action, "UNAUTHORIZED ACCESS") != NULL){
                suspiciousCount++;
            }
        }
    }
    return suspiciousCount;
}
    
int DailyConnections(struct Log logs[], int n, char date[]){
    int connectionCount = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].time[0] != '\0' && strncmp(logs[i].time, date, 10) == 0){
            if (strstr(logs[i].action, "LOGIN") != NULL){
                connectionCount++;
            }
        }
    }
    return connectionCount;
}

float errorRate(struct Log logs[], int n){
    int totalLogs = 0;
    int errorLogs = 0;
    for (int i = 0; i < n; i++){
        if (logs[i].time[0] != '\0'){
            totalLogs++;
            if (strstr(logs[i].action, "ERROR") != NULL){
                errorLogs++;
            }
        }
    }
    if (totalLogs == 0) return 0.0;
    return ((float)errorLogs / totalLogs) * 100;
}

void exportLogsCSV(struct Log logs[], int n){
    const char* filename = "exported_logs.csv";
    FILE* file = fopen(filename, "w");
    if (file == NULL){
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
}

void importLogsCSV(struct Log logs[], int n){
    const char* filename = "imported_logs.csv";
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file %s for reading.\n", filename);
        return;
    }
}
   
void clearLogs(struct Log logs[], int n){
    for (int i = 0; i < n; i++){
        logs[i].time[0] = '\0';
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
    }
    printf("All logs cleared.\n");
}

void recentLogs(struct Log logs[], int n, int nb){
    printf("Most recent %d logs:\n", nb);
    int count = 0;
    for (int i = n - 1; i >= 0 && count < nb; i--){
        if (logs[i].time[0] != '\0'){
            printf("Log %d: [%s] User: %s Action: %s\n", i, logs[i].time, logs[i].user, logs[i].action);
            count++;
        }
    }
}

void archiveLogs(struct Log logs[], int n){
    const char* filename = "archived_logs.dat";
    FILE* file = fopen(filename, "wb");
    if (file == NULL){
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
}

void showTopErrors(struct Log logs[], int n){
    struct ErrorCount {
        char errorMsg[50];
        int count;
    } errorCounts[100];
    int errorCountSize = 0;

    for (int i = 0; i < n; i++){
        if (logs[i].action[0] != '\0' && strstr(logs[i].action, "ERROR") != NULL){
            int found = 0;
            for (int j = 0; j < errorCountSize; j++){
                if (strcmp(errorCounts[j].errorMsg, logs[i].action) == 0){
                    errorCounts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && errorCountSize < 100){
                snprintf(errorCounts[errorCountSize].errorMsg, sizeof(errorCounts[errorCountSize].errorMsg), "%s", logs[i].action);
                errorCounts[errorCountSize].count = 1;
                errorCountSize++;
            }
        }
    }

    // Sort errors by count
    struct ErrorCount temp;
    for (int i = 0; i < errorCountSize - 1; i++){
        for (int j = i + 1; j < errorCountSize; j++){
            if (errorCounts[i].count < errorCounts[j].count){
                temp = errorCounts[i];
                errorCounts[i] = errorCounts[j];
                errorCounts[j] = temp;
            }
        }
    }

    printf("Top Error Messages:\n");
    for (int i = 0; i < errorCountSize && i < 5; i++){
        printf("%s - %d occurrences\n", errorCounts[i].errorMsg, errorCounts[i].count);
    }
}
