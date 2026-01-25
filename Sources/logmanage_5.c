#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"
#include<stdio.h>
#include<string.h>






void initLogs(struct Log logs[], int n){
    for (int i = 0; i < n; i++){
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
        logs[i].date[0] = '\0';
        logs[i].time[0] = '\0';
        logs[i].code = -1; // indicates empty log
    }
}

void addLog(struct Log logs[], int n,char user[],char action[],int code){
    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] == '\0') {  // find an empty slot
            snprintf(logs[i].user, sizeof(logs[i].user), "%s", user);
            snprintf(logs[i].action, sizeof(logs[i].action), "%s", action);
            // using fixed date/time
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
        if (logs[i].user[0] != '\0'){
            printf("Log %d: [%s %s] User: %s Action: %s Code: %d\n", i+1, logs[i].date, logs[i].time, logs[i].user, logs[i].action, logs[i].code);
        }
    }
}

void searchLogsByUser(struct Log logs[], int n, char user[]){
    int i;
    int found = 0;
    for (i = 0; i < n; i++) {
        if (logs[i].user[0] != '\0' && strcmp(logs[i].user, user) == 0) {
            printf("Log %d: [%s] User: %s Action: %s\n", i, logs[i].time, logs[i].user, logs[i].action);
            found = 1;
        }
    }
    if (!found) {
        printf("No logs found for user: %s\n", user);
    }
}

void searchLogsByDate(struct Log logs[], int n, char date[]){
    int i;
    int found = 0;
    for (i = 0; i < n; i++) {
        if (logs[i].date[0] != '\0' && strcmp(logs[i].date, date) == 0) {
            printf("Log %d: [%s] User: %s Action: %s\n", i, logs[i].time, logs[i].user, logs[i].action);
            found = 1;
        }
    }
    if (!found) {
        printf("No logs found for date: %s\n", date);
    }
}

int countErrorLogs(struct Log logs[], int n){
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].code == 2) { // assuming code 2 = error
            count++;
        }
    }

    return count;
}

int countLoginLogs(struct Log logs[], int n){
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].code == 1 && strcmp(logs[i].action, "Login") == 0) { // assuming code 1 = login
            count++;
        }
    }

    return count;
}

int countBlockedLogs(struct Log logs[], int n){
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].code == 1 && strcmp(logs[i].action, "Blocked") == 0) {
            count++;
        }
    }

    return count;
}

void displayLogStats(struct Log logs[], int n)
{
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (logs[i].code == 0)
            infoCount++;
        else if (logs[i].code == 1)
            warningCount++;
        else if (logs[i].code == 2)
            errorCount++;
    }

    printf("Log Statistics:\n");
    printf("Info logs: %d\n", infoCount);
    printf("Warning logs: %d\n", warningCount);
    printf("Error logs: %d\n", errorCount);
}

void sortLogsByDate(struct Log logs[], int n)
{
    struct Log temp;
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (logs[i].date[0] != '\0' && logs[j].date[0] != '\0' &&
                strcmp(logs[i].date, logs[j].date) > 0){
                temp = logs[i];
                logs[i] = logs[j];
                logs[j] = temp;
            }
        }
    }
}

void sortLogsByUser(struct Log logs[], int n)
{
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

int detectSuspiciousActivity(struct Log logs[], int n, char user[])
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].user == 1 && strcmp(logs[i].user, user) == 0) {
            /* Suspicious if blocked or error login */
            if ((strcmp(logs[i].action, "Blocked") == 0) ||
                (strcmp(logs[i].action, "Login") == 0 && logs[i].code >= 400)) 
            {
                count++;
            }
        }
    }

    return count;
}

int dailyConnections(struct Log logs[], int n, char date[])
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].date[0] != '\0' && strcmp(logs[i].date, date) == 0) {
            count++;
        }
    }

    return count;
}

float errorRate(struct Log logs[], int n)
{
    int i;
    int totalLogs = 0;
    int errorLogs = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].date[0] != '\0') {
            totalLogs++;
            if (logs[i].code == 2) { // assuming code 2 = error
                errorLogs++;
            }
        }
    }

    if (totalLogs == 0) return 0.0;

    return ((float)errorLogs / totalLogs) * 100;
}

void exportLogsCSV(struct Log logs[], int n)
{
    FILE *file = fopen("logs.csv", "w");
    if (file == NULL) {
        printf("Error: Cannot open file for writing.\n");
        return;
    }

    // Write CSV header
    fprintf(file, "User,Action,Date,Code\n");

    // Write log entries
    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] != '\0') {
            fprintf(file, "%s,%s,%s,%d\n",
                    logs[i].user,
                    logs[i].action,
                    logs[i].date,
                    logs[i].code);
        }
    }
}

void importLogsCSV(struct Log logs[], int n)
{
    FILE *file = fopen("logs.csv", "r");
    if (file == NULL) {
        printf("Error: Cannot open logs.csv for reading.\n");
        return;
    }

    char line[200];
    int index = 0;

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("CSV file is empty.\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL && index < n) {
        sscanf(line, "%19[^,],%49[^,],%19[^,],%d",
               logs[index].user,
               logs[index].action,
               logs[index].date,
               &logs[index].code);
        index++;
    }

    fclose(file);
    printf("%d logs imported successfully from logs.csv\n", index);
}

void clearLogs(struct Log logs[], int n)
{
    for (int i = 0; i < n; i++) {
        logs[i].user[0] = '\0';
        logs[i].action[0] = '\0';
        logs[i].date[0] = '\0';
        logs[i].code = 0;
    }

    printf("All logs have been cleared.\n");
}

void recentLogs(struct Log logs[], int n, int nb)
{
    printf("Most recent %d logs:\n", nb);
    int count = 0;
    for (int i = n - 1; i >= 0 && count < nb; i--){
        if (logs[i].user[0] != '\0'){
            printf("Log %d: [%s %s] User: %s Action: %s Code: %d\n", i+1, logs[i].date, logs[i].time, logs[i].user, logs[i].action, logs[i].code);
            count++;
        }
    }
}

void archiveLogs(struct Log logs[], int n)
{
    FILE *file = fopen("archive_logs.csv", "a"); // append to archive
    if (file == NULL) {
        printf("Error: Cannot open archive_logs.csv for writing.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (logs[i].user[0] != '\0') {
            fprintf(file, "%s,%s,%s,%d\n",
                    logs[i].user,
                    logs[i].action,
                    logs[i].date,
                    logs[i].code);
            // Clear the log after archiving
            logs[i].user[0] = '\0';
            logs[i].action[0] = '\0';
            logs[i].date[0] = '\0';
            logs[i].code = 0;
        }
    }
    fclose(file);
    printf("All logs have been archived and cleared.\n");
}

void showTopErrors(struct Log logs[], int n)
{
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

    printf("Top Errors:\n");
    for (int i = 0; i < errorCountSize && i < 5; i++){
        printf("%s - %d occurrences\n", errorCounts[i].errorMsg, errorCounts[i].count);
    }
}
