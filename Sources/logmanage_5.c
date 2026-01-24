#include "endecryption_1.h"
#include "mathsecurity_2.h"
#include "logmanage_3.h"
#include "securityAudit_4.h"
#include "usermanage_5.h"
#include<string.h>

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

void exportLogsCSV(struct Log logs[], int count) {
    const char* filename = "logs_export.csv";
    FILE* file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    
    fprintf(file, "ID,Timestamp,Level,Source,Message\n");
    
    for (int i = 0; i < count; i++) {
        int needs_quotes = 0;
        if (strchr(logs[i].message, ',') != NULL || 
            strchr(logs[i].message, '"') != NULL ||
            strchr(logs[i].message, '\n') != NULL) {
            needs_quotes = 1;
        }
        
        if (needs_quotes) {
            fprintf(file, "%d,%s,%s,%s,\"", 
                    logs[i].id,
                    logs[i].timestamp,
                    logs[i].level,
                    logs[i].source);
            
            for (int j = 0; logs[i].message[j] != '\0'; j++) {
                if (logs[i].message[j] == '"') {
                    fputc('"', file);
                    fputc('"', file);
                } else {
                    fputc(logs[i].message[j], file);
                }
            }
            
            fprintf(file, "\"\n");
        } else {
            fprintf(file, "%d,%s,%s,%s,%s\n",
                    logs[i].id,
                    logs[i].timestamp,
                    logs[i].level,
                    logs[i].source,
                    logs[i].message);
        }
    }
    
    fclose(file);
    printf("Exported %d logs to %s\n", count, filename);
}

void importLogsCSV(struct Log logs[], int max_count) {
    const char* filename = "logs_export.csv";
    FILE* file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    
    char line[1024];
    
    fgets(line, sizeof(line), file);
    
    int index = 0;
    while (fgets(line, sizeof(line), file) && index < max_count) {
        char* fields[5];
        int field_count = 0;
        char* ptr = line;
        
        while (*ptr && field_count < 5) {
            if (*ptr == '"') {
                ptr++;
                char* start = ptr;
                while (*ptr) {
                    if (*ptr == '"' && *(ptr + 1) == '"') ptr += 2;
                    else if (*ptr == '"') break;
                    else ptr++;
                }
                *ptr = '\0';
                fields[field_count++] = start;
                ptr += 2;
            } else {
                char* start = ptr;
                while (*ptr && *ptr != ',' && *ptr != '\n') ptr++;
                char separator = *ptr;
                *ptr = '\0';
                fields[field_count++] = start;
                ptr++;
            }
        }
        
        if (field_count >= 1) logs[index].id = atoi(fields[0]);
        if (field_count >= 2) strncpy(logs[index].timestamp, fields[1], 19);
        if (field_count >= 3) strncpy(logs[index].level, fields[2], 9);
        if (field_count >= 4) strncpy(logs[index].source, fields[3], 49);
        if (field_count >= 5) strncpy(logs[index].message, fields[4], 255);
        
        logs[index].timestamp[19] = '\0';
        logs[index].level[9] = '\0';
        logs[index].source[49] = '\0';
        logs[index].message[255] = '\0';
        
        index++;
    }
    
    fclose(file);
    printf("Imported %d logs from %s\n", index, filename);
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

void archiveLogs(struct Log logs[], int count, int days) {
    const char* archive_filename = "logs_archive.csv";
    const char* current_filename = "logs_current.csv";
    
    FILE* archive_file = fopen(archive_filename, "a");
    if (archive_file == NULL) {
        printf("Error: Could not open archive file %s\n", archive_filename);
        return;
    }
    
    FILE* current_file = fopen(current_filename, "w");
    if (current_file == NULL) {
        printf("Error: Could not create current file %s\n", current_filename);
        fclose(archive_file);
        return;
    }
    
    if (ftell(archive_file) == 0) {
        fprintf(archive_file, "ID,Timestamp,Level,Source,Message\n");
    }
    
    fprintf(current_file, "ID,Timestamp,Level,Source,Message\n");
    
    time_t current_time = time(NULL);
    struct tm* time_info = localtime(&current_time);
    time_info->tm_mday -= days;
    time_t cutoff_time = mktime(time_info);
    
    int archived_count = 0;
    int current_count = 0;
    
    for (int i = 0; i < count; i++) {
        struct tm log_time;
        memset(&log_time, 0, sizeof(struct tm));
        sscanf(logs[i].timestamp, "%d-%d-%d %d:%d:%d",
               &log_time.tm_year, &log_time.tm_mon, &log_time.tm_mday,
               &log_time.tm_hour, &log_time.tm_min, &log_time.tm_sec);
        log_time.tm_year -= 1900;
        log_time.tm_mon -= 1;
        time_t log_timestamp = mktime(&log_time);
        
        if (log_timestamp < cutoff_time) {
            if (strchr(logs[i].message, ',') != NULL || 
                strchr(logs[i].message, '"') != NULL) {
                fprintf(archive_file, "%d,%s,%s,%s,\"", 
                        logs[i].id,
                        logs[i].timestamp,
                        logs[i].level,
                        logs[i].source);
                
                for (int j = 0; logs[i].message[j] != '\0'; j++) {
                    if (logs[i].message[j] == '"') {
                        fputc('"', archive_file);
                        fputc('"', archive_file);
                    } else {
                        fputc(logs[i].message[j], archive_file);
                    }
                }
                
                fprintf(archive_file, "\"\n");
            } else {
                fprintf(archive_file, "%d,%s,%s,%s,%s\n",
                        logs[i].id,
                        logs[i].timestamp,
                        logs[i].level,
                        logs[i].source,
                        logs[i].message);
            }
            archived_count++;
        } else {
            fprintf(current_file, "%d,%s,%s,%s,%s\n",
                    logs[i].id,
                    logs[i].timestamp,
                    logs[i].level,
                    logs[i].source,
                    logs[i].message);
            current_count++;
        }
    }
    
    fclose(archive_file);
    fclose(current_file);
    
    printf("Archived %d logs older than %d days to %s\n", archived_count, days, archive_filename);
    printf("Kept %d recent logs in %s\n", current_count, current_filename);
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
