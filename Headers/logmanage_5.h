#ifndef LOGMANAGE_5_H
#define LOGMANAGE_5_H

/* declarations here */
struct Log{
    char user[20];
    char action[50];
    char date[20];
    char time[10];
    int code;
}
void initLogs(struct Log logs[], int n); 
void addLog(struct Log logs[], int n, char user[], char action[], int code);
void displayLogs(struct Log logs[], int n);
void searchLogsByUser(struct Log logs[], int n, char user[]);
void searchLogsByDate(struct Log logs[], int n, char date[]);
int countErrorLogs(struct Log logs[], int n);
int countLoginLogs(struct Log logs[], int n); 
int countBlockedLogs(struct Log logs[], int n); 
void displayLogStats(struct Log logs[], int n); 
void sortLogsByDate(struct Log logs[], int n); 
void sortLogsByUser(struct Log logs[], int n); 
int detectSuspiciousActivity(struct Log logs[], int n, char user[]);
int dailyConnections(struct Log logs[], int n, char date[]);
float errorRate(struct Log logs[], int n);
void exportLogsCSV(struct Log logs[], int n); 
void importLogsCSV(struct Log logs[], int n); 
void clearLogs(struct Log logs[], int n); 
void recentLogs(struct Log logs[], int n, int nb); 
void archiveLogs(struct Log logs[], int n); 
void showTopErrors(struct Log logs[], int n);

#endif 