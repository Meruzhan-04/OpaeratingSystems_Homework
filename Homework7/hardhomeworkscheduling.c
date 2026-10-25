#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

typedef struct {
    int pid;
    int start_time;
    int end_time;
} GanttEntry;

void fcfs(Process processes[], int n, GanttEntry schedule[]) {
    int order[MAX_PROCESSES];
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        order[i] = i;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int left = order[i];
            int right = order[j];

            if (processes[right].arrival_time <
                    processes[left].arrival_time ||
                (processes[right].arrival_time ==
                     processes[left].arrival_time &&
                 processes[right].pid < processes[left].pid)) {

                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int index = order[i];
        Process *p = &processes[index];

        if (current_time < p->arrival_time) {
            current_time = p->arrival_time;
        }

        schedule[i].pid = p->pid;
        schedule[i].start_time = current_time;

        p->waiting_time = current_time - p->arrival_time;
        p->response_time = p->waiting_time;

        current_time += p->burst_time;

        schedule[i].end_time = current_time;
        p->turnaround_time = current_time - p->arrival_time;
    }
}

void sjf(Process processes[], int n, GanttEntry schedule[]) {
    int completed[MAX_PROCESSES] = {0};
    int current_time = 0;
    int scheduled = 0;

    while (scheduled < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (completed[i] ||
                processes[i].arrival_time > current_time) {
                continue;
            }

            if (selected == -1 ||
                processes[i].burst_time <
                    processes[selected].burst_time ||
                (processes[i].burst_time ==
                     processes[selected].burst_time &&
                 processes[i].arrival_time <
                    processes[selected].arrival_time) ||
                (processes[i].burst_time ==
                     processes[selected].burst_time &&
                 processes[i].arrival_time ==
                    processes[selected].arrival_time &&
                 processes[i].pid < processes[selected].pid)) {

                selected = i;
            }
        }

        if (selected == -1) {
            int earliest_arrival = INT_MAX;

            for (int i = 0; i < n; i++) {
                if (!completed[i] &&
                    processes[i].arrival_time < earliest_arrival) {
                    earliest_arrival = processes[i].arrival_time;
                }
            }

            current_time = earliest_arrival;
            continue;
        }

        Process *p = &processes[selected];

        schedule[scheduled].pid = p->pid;
        schedule[scheduled].start_time = current_time;

        p->waiting_time = current_time - p->arrival_time;
        p->response_time = p->waiting_time;

        current_time += p->burst_time;

        schedule[scheduled].end_time = current_time;
        p->turnaround_time = current_time - p->arrival_time;

        completed[selected] = 1;
        scheduled++;
    }
}

void print_gantt_chart(const GanttEntry schedule[], int n) {
    int current_time = 0;

    printf("Gantt Chart: %d", current_time);

    for (int i = 0; i < n; i++) {
        if (schedule[i].start_time > current_time) {
            printf(" | IDLE | %d", schedule[i].start_time);
            current_time = schedule[i].start_time;
        }

        printf(" | P%d | %d",
               schedule[i].pid,
               schedule[i].end_time);

        current_time = schedule[i].end_time;
    }

    printf("\n");
}

void print_results(const char *title, const Process processes[],
                   int n, const GanttEntry schedule[]) {
    double total_waiting_time = 0.0;
    double total_turnaround_time = 0.0;
    double total_response_time = 0.0;

    printf("\n=== %s ===\n", title);

    print_gantt_chart(schedule, n);

    printf("%-6s %-6s %-6s %-6s %-7s %-6s\n",
           "PID", "AT", "BT", "WT", "TAT", "RT");

    for (int i = 0; i < n; i++) {
        const Process *p = &processes[schedule[i].pid - 1];

        printf("%-6d %-6d %-6d %-6d %-7d %-6d\n",
               p->pid,
               p->arrival_time,
               p->burst_time,
               p->waiting_time,
               p->turnaround_time,
               p->response_time);

        total_waiting_time += p->waiting_time;
        total_turnaround_time += p->turnaround_time;
        total_response_time += p->response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n",
           total_waiting_time / n);

    printf("Average Turnaround Time: %.2f\n",
           total_turnaround_time / n);

    printf("Average Response Time: %.2f\n",
           total_response_time / n);
}

int main(void) {
    Process original[MAX_PROCESSES];
    Process fcfs_processes[MAX_PROCESSES];
    Process sjf_processes[MAX_PROCESSES];

    GanttEntry fcfs_schedule[MAX_PROCESSES];
    GanttEntry sjf_schedule[MAX_PROCESSES];

    int n;

    printf("Enter the number of processes: ");

    if (scanf("%d", &n) != 1 ||
        n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. "
               "Enter a value from 1 to %d.\n", MAX_PROCESSES);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        original[i].pid = i + 1;

        printf("Enter the arrival time and burst time "
               "for process %d: ", i + 1);

        if (scanf("%d %d",
                  &original[i].arrival_time,
                  &original[i].burst_time) != 2 ||
            original[i].arrival_time < 0 ||
            original[i].burst_time <= 0) {

            printf("Invalid input. Arrival time must be "
                   "non-negative and burst time must be positive.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        fcfs_processes[i] = original[i];
        sjf_processes[i] = original[i];
    }

    fcfs(fcfs_processes, n, fcfs_schedule);
    sjf(sjf_processes, n, sjf_schedule);

    print_results("First Come First Served (FCFS)",
                  fcfs_processes, n, fcfs_schedule);

    print_results("Shortest Job First (SJF)",
                  sjf_processes, n, sjf_schedule);

    return 0;
}
