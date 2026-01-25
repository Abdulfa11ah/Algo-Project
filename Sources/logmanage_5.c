#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"
#include<stdio.h>
#include<string.h>

void initLogs(struct Log logs[], int n){
    for (int i = 0; i < n; i++) {
        logs[i].id = 0;
        logs[i].level = 0;
        strcpy(logs[i].message, "");   // Empty string
    }
}

void addLog(struct Log logs[], int n,char user[],char action[],int code){
    for (int i = 0; i < n; i++) {
        if (logs[i].used == 0) {  // find an empty slot
            snprintf(logs[i].user, sizeof(logs[i].user), "%s", user);
            snprintf(logs[i].action, sizeof(logs[i].action), "%s", action);
            // using fixed date/time
            snprintf(logs[i].date, sizeof(logs[i].date), "2024-01-01");
            snprintf(logs[i].time, sizeof(logs[i].time), "12:00:00");
            logs[i].code = code;
            logs[i].id = i + 1;  // Simple ID assignment
            snprintf(logs[i].message, sizeof(logs[i].message), "Log message %d", i + 1);
            logs[i].level = code; 
            logs[i].used = 1; // Mark as used
            return;
        }
    }
    printf("Log storage full, cannot add new log.\n");
}

void displayLogs(struct Log logs[], int n){
    int i;

    for (i = 0; i < n; i++) {
        if (logs[i].used == 1) {   // only display filled logs
            printf("========== Log %d ==========\n", i + 1);
            printf("User     : %s\n", logs[i].user);
            printf("Action   : %s\n", logs[i].action);
            printf("Date     : %s\n", logs[i].date);
            printf("Time     : %s\n", logs[i].time);
            printf("Code     : %d\n", logs[i].code);
            printf("Log ID   : %d\n", logs[i].id);
            printf("Message  : %s\n", logs[i].message);
            printf("Level    : %d\n", logs[i].level);
            printf("------------------------------\n");
        }
    }
}

void searchLogsByUser(struct Log logs[], int n, char user[]){
    int i;
    int found = 0;
    for (i = 0; i < n; i++) {
        if (logs[i].used == 1 && strcmp(logs[i].user, user) == 0) {
            printf("========== Log %d ==========\n", i + 1);
            printf("User     : %s\n", logs[i].user);
            printf("Action   : %s\n", logs[i].action);
            printf("Date     : %s\n", logs[i].date);
            printf("Time     : %s\n", logs[i].time);
            printf("Code     : %d\n", logs[i].code);
            printf("Log ID   : %d\n", logs[i].id);
            printf("Message  : %s\n", logs[i].message);
            printf("Level    : %d\n", logs[i].level);
            printf("------------------------------\n");
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
        if (logs[i].used == 1 && strcmp(logs[i].date, date) == 0) {
            printf("========== Log %d ==========\n", i + 1);
            printf("User     : %s\n", logs[i].user);
            printf("Action   : %s\n", logs[i].action);
            printf("Date     : %s\n", logs[i].date);
            printf("Time     : %s\n", logs[i].time);
            printf("Code     : %d\n", logs[i].code);
            printf("Log ID   : %d\n", logs[i].id);
            printf("Message  : %s\n", logs[i].message);
            printf("Level    : %d\n", logs[i].level);
            printf("------------------------------\n");
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
        if (logs[i].used == 1 && logs[i].code >= 400) {
            count++;
        }
    }

    return count;
}

int countLoginLogs(struct Log logs[], int n)
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].used == 1 && strcmp(logs[i].action, "Login") == 0) {
            count++;
        }
    }

    return count;
}

int countBlockedLogs(struct Log logs[], int n)
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].used == 1 && strcmp(logs[i].action, "Blocked") == 0) {
            count++;
        }
    }

    return count;
}

void displayLogStats(struct Log logs[], int n)
{
    int total = 0;
    int errors;
    int logins;
    int blocked;
    int i;

    /* Count total used logs */
    for (i = 0; i < n; i++) {
        if (logs[i].used == 1) {
            total++;
        }
    }

    errors  = countErrorLogs(logs, n);
    logins  = countLoginLogs(logs, n);
    blocked = countBlockedLogs(logs, n);

    printf("\n===== LOG STATISTICS =====\n");
    printf("Total logs   : %d\n", total);
    printf("Error logs   : %d\n", errors);
    printf("Login logs   : %d\n", logins);
    printf("Blocked logs : %d\n", blocked);
    printf("==========================\n");
}

void sortLogsByDate(struct Log logs[], int n)
{
    int i, j;
    struct Log temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (logs[j].used == 1 && logs[j + 1].used == 1) {
                if (strcmp(logs[j].date, logs[j + 1].date) > 0) {
                    /* Swap */
                    temp = logs[j];
                    logs[j] = logs[j + 1];
                    logs[j + 1] = temp;
                }
            }
        }
    }
}

void sortLogsByUser(struct Log logs[], int n)
{
    int i, j;
    struct Log temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (logs[j].used == 1 && logs[j + 1].used == 1) {
                if (strcmp(logs[j].user, logs[j + 1].user) > 0) {
                    /* Swap */
                    temp = logs[j];
                    logs[j] = logs[j + 1];
                    logs[j + 1] = temp;
                }
            }
        }
    }
}

int detectSuspiciousActivity(struct Log logs[], int n, char user[])
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].used == 1 && strcmp(logs[i].user, user) == 0) {
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
        if (logs[i].used == 1 && strcmp(logs[i].date, date) == 0) {
            count++;
        }
    }

    return count;
}

float errorRate(struct Log logs[], int n)
{
    int i;
    int totalUsed = 0;
    int errorCount = 0;

    for (i = 0; i < n; i++) {
        if (logs[i].used == 1) {
            totalUsed++;

            if (logs[i].code >= 400) { // assuming code >= 400 = error
                errorCount++;
            }
        }
    }

    if (totalUsed == 0) {
        return 0.0; // avoid division by zero
    }

    return (float)errorCount / totalUsed * 100;
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
        if (logs[i].used == 1) {
            fprintf(file, "%s,%s,%s,%d\n",
                    logs[i].user,
                    logs[i].action,
                    logs[i].date,
                    logs[i].code);
        }
    }

    fclose(file);
    printf("Logs exported to logs.csv successfully.\n");
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

    // Read each line
    while (fgets(line, sizeof(line), file) != NULL && index < n) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Split CSV by commas
        char *token = strtok(line, ",");
        if (token != NULL) strcpy(logs[index].user, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(logs[index].action, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(logs[index].date, token);

        token = strtok(NULL, ",");
        if (token != NULL) logs[index].code = atoi(token);

        logs[index].used = 1;  // mark as used
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
        logs[i].used = 0;  // mark as empty
    }

    printf("All logs have been cleared.\n");
}

void recentLogs(struct Log logs[], int n, int nb)
{
    int i, count = 0;

    // First, find how many logs are used
    int usedCount = 0;
    for (i = 0; i < n; i++) {
        if (logs[i].used == 1) usedCount++;
    }

    if (usedCount == 0) {
        printf("No logs to display.\n");
        return;
    }

    // Determine starting index to display last nb logs
    int start = usedCount - nb;
    if (start < 0) start = 0;

    printf("===== Most Recent %d Logs =====\n", nb);

    for (i = start; i < usedCount; i++) {
        printf("Log %d\n", i + 1);
        printf("User   : %s\n", logs[i].user);
        printf("Action : %s\n", logs[i].action);
        printf("Date   : %s\n", logs[i].date);
        printf("Code   : %d\n", logs[i].code);
        printf("---------------------\n");
        count++;
    }

    if (count == 0) {
        printf("No recent logs found.\n");
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
        if (logs[i].used == 1) {
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
            logs[i].used = 0;
        }
    }

    fclose(file);
    printf("All logs have been archived and cleared.\n");
}

void showTopErrors(struct Log logs[], int n)
{
    // First, make a copy of logs to sort so we don't alter the original array
    struct Log temp[n];
    int i, j;
    int foundError = 0;

    // Copy used logs
    int count = 0;
    for (i = 0; i < n; i++) {
        if (logs[i].used == 1 && logs[i].code >= 400) {
            temp[count++] = logs[i];
        }
    }

    if (count == 0) {
        printf("No error logs found.\n");
        return;
    }

    // Sort temp array descending by code (simple bubble sort)
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (temp[j].code < temp[j + 1].code) {
                struct Log t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }


// Display top errors
    printf("===== Top Error Logs =====\n");
    for (i = 0; i < count; i++) {
        printf("User   : %s\n", temp[i].user);
        printf("Action : %s\n", temp[i].action);
        printf("Date   : %s\n", temp[i].date);
        printf("Code   : %d\n", temp[i].code);
        printf("---------------------\n");
    }
}
