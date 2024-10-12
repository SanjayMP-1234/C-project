# Calendar Application

A simple console-based calendar application written in C that allows users to view a calendar for a specific month and year, add events, view events, and delete events.

## Features

- View the calendar for any month and year.
- Add events with descriptions to specific dates.
- View all events for a specific date.
- Delete events from a specific date.

## Structure

The main components of the application are:

- **Data Structures**: 
  - `struct Event`: Holds event details (day and description).
  
- **Functions**:
  - `isLeapYear(int year)`: Determines if a year is a leap year.
  - `getDaysInMonth(int month, int year)`: Returns the number of days in a given month and year.
  - `getFirstDayOfMonth(int month, int year)`: Calculates the first day of the month using Zeller's Congruence.
  - `printCalendar(int month, int year)`: Prints the calendar for a given month and year.
  - `addEvent(int day, int month, int year, char description[])`: Adds an event to a specific date.
  - `displayEvents(int day, int month, int year)`: Displays all events for a specific date.
  - `deleteEvent(int day, int month, int year)`: Deletes an event from a specific date.

## Installation

1. Ensure you have a C compiler installed (e.g., GCC).
2. Clone or download this repository.
3. Navigate to the project folder.
4. Compile the application:

   ```bash
   gcc -o calendar calendar.c
