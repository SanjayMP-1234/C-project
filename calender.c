#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Event {
    int day;
    char description[100];
};

int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    return 0;
}

int getDaysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

int getFirstDayOfMonth(int month, int year) {
    // Zeller's Congruence
    if (month < 3) {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int dayOfWeek = (1 + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j)) % 7;
    
    dayOfWeek = (dayOfWeek + 6) % 7;

    return dayOfWeek;
}

void printCalendar(int month, int year) {
    printf("\n  Calendar for %d/%d\n", month, year);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int daysInMonth = getDaysInMonth(month, year);
    int firstDay = getFirstDayOfMonth(month, year);

    for (int i = 0; i < firstDay; i++) {
        printf("     ");
    }

    for (int day = 1; day <= daysInMonth; day++) {
        printf("%5d", day);
        if ((firstDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}

void addEvent(int day, int month, int year, char description[]) {
    struct Event event;
    event.day = day;
    strcpy(event.description, description);

    char filename[20];
    sprintf(filename, "events_%d_%d.txt", month, year);

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s\n", event.day, event.description);
    fclose(file);
    printf("Event added successfully!\n");
}

void displayEvents(int day, int month, int year) {
    char filename[20];
    sprintf(filename, "events_%d_%d.txt", month, year);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No events found for %d/%d/%d.\n", day, month, year);
        return;
    }

    struct Event event;
    int found = 0;
    while (fscanf(file, "%d %[^\n]", &event.day, event.description) != EOF) {
        if (event.day == day) {
            printf("Event on %d/%d/%d: %s\n", day, month, year, event.description);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No events found for %d/%d/%d.\n", day, month, year);
    }
}

void deleteEvent(int day, int month, int year) {
    char filename[20];
    sprintf(filename, "events_%d_%d.txt", month, year);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No events found for %d/%d/%d.\n", day, month, year);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    struct Event event;
    int found = 0;
    while (fscanf(file, "%d %[^\n]", &event.day, event.description) != EOF) {
        if (event.day == day) {
            found = 1;
        } else {
            fprintf(tempFile, "%d %s\n", event.day, event.description);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        printf("Event(s) on %d/%d/%d deleted successfully!\n", day, month, year);
    } else {
        remove("temp.txt");
        printf("No events found for %d/%d/%d to delete.\n", day, month, year);
    }
}

int main() {
    int choice;
    int month, year, day;
    char description[100];

    do {
        printf("\n** Calendar Application **\n");
        printf("1. View Calendar\n");
        printf("2. Add Event\n");
        printf("3. View Events\n");
        printf("4. Delete Event\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                printCalendar(month, year);
                break;
            case 2:
                printf("Enter day: ");
                scanf("%d", &day);
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                printf("Enter event description: ");
                getchar();
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0;
                addEvent(day, month, year, description);
                break;
            case 3:
                printf("Enter day: ");
                scanf("%d", &day);
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                displayEvents(day, month, year);
                break;
            case 4:
                printf("Enter day: ");
                scanf("%d", &day);
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                deleteEvent(day, month, year);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);
    return 0;
}