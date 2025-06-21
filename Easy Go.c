#include <stdio.h>
#include <string.h>

struct Topic {
    char name[50];
    int interest;
    int complexity;
    int weight;
};

void swap(struct Topic *a, struct Topic *b) {
    struct Topic temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, days, i, j, totalWeight = 0;

    printf("Enter number of topics: ");
    scanf("%d", &n);

    struct Topic topics[n];

    for (i = 0; i < n; i++) {
        printf("\nEnter name of topic %d: ", i + 1);
        scanf("%s", topics[i].name);
        printf("Enter interest level (1-5): ");
        scanf("%d", &topics[i].interest);
        printf("Enter complexity level (1-5): ");
        scanf("%d", &topics[i].complexity);

        topics[i].weight = topics[i].interest + topics[i].complexity;
        totalWeight += topics[i].weight;
    }

    printf("\nEnter number of days to complete syllabus: ");
    scanf("%d", &days);

    int schedule[days][n];
    int scheduleCount[days];
    memset(scheduleCount, 0, sizeof(scheduleCount));

    // Allocate topics to days based on weight proportionally
    int allocated[n];
    memset(allocated, 0, sizeof(allocated));

    for (i = 0; i < n; i++) {
        int share = (topics[i].weight * days) / totalWeight;

        if (share == 0) share = 1; // Assign at least one day

        for (j = 0; j < share && j < days; j++) {
            schedule[j][scheduleCount[j]++] = i;
            allocated[i]++;
        }
    }

    // Allocate remaining topics if any day is still empty
    for (i = 0; i < days; i++) {
        if (scheduleCount[i] == 0) {
            for (j = 0; j < n; j++) {
                if (allocated[j] < (topics[j].weight * days) / totalWeight) {
                    schedule[i][scheduleCount[i]++] = j;
                    allocated[j]++;
                    break;
                }
            }
        }
    }

    printf("\n--- Easy Go Study Schedule ---\n");
    for (i = 0; i < days; i++) {
        printf("Day %d:\n", i + 1);
        if (scheduleCount[i] == 0) {
            printf("  Revision / Free\n");
        } else {
            for (j = 0; j < scheduleCount[i]; j++) {
                printf("  - %s\n", topics[schedule[i][j]].name);
            }
        }
    }

    return 0;
}
