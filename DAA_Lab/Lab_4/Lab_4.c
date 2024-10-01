//4) Implement the activity selection problem to get a clear understanding of greedy approach.

#include <stdio.h>

// Function to display the maximum number of non-overlapping tasks
void selectActivities(int startTime[], int finishTime[], int totalActivities) {
    int lastSelectedActivity, currentActivity;

    printf("Selected non-overlapping tasks are:\n");

    // Always select the first task
    lastSelectedActivity = 0;
    printf("Task %d (Start: %d, Finish: %d)\n", lastSelectedActivity + 1, startTime[lastSelectedActivity], finishTime[lastSelectedActivity]);

    // Iterate through the remaining tasks
    for (currentActivity = 1; currentActivity < totalActivities; currentActivity++) {
        // If the start time of the current task is greater than or equal to
        // the finish time of the last selected task, select it
        if (startTime[currentActivity] >= finishTime[lastSelectedActivity]) {
            printf("Task %d (Start: %d, Finish: %d)\n", currentActivity + 1, startTime[currentActivity], finishTime[currentActivity]);
            lastSelectedActivity = currentActivity;  // Update lastSelectedActivity to current task
        }
    }
}

int main() {
    // Example set of tasks with their start and finish times
    int startTime[] = {2, 3, 1, 6, 7, 8};
    int finishTime[] = {3, 5, 4, 9, 10, 11};
    int totalActivities = sizeof(startTime) / sizeof(startTime[0]);

    selectActivities(startTime, finishTime, totalActivities);

    return 0;
}