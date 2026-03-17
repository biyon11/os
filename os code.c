#include <stdio.h>

struct Process {
    char pid[10];
    int at, bt, pr;
    int wt, tat, ct;
    int completed;
};

int main() {
    int n, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes:\n");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].completed = 0;
    }

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        // Find process with highest priority (lowest PR) among arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {
                if (p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                }
                // Tie-breaking: earlier arrival time
                else if (p[i].pr == highest_priority) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        } else {
            time++; // CPU idle
        }
    }

    // Output
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}