# Project Management Application 
A command-line project management application that tracks projects, milestones, and activities, allowing users to update progress and view cost and duration statistics.

## Features
- Create a project with multiple milestones and activities
- Assign unique IDs to activities and milestones
- Track planned vs actual duration and cost
- Update activity completion status
- Automatically update milestone and project status
- Display detailed project and milestone statistics

## Program Structure
- **Activity**: Represents a task with duration, cost, and completion status
- **Milestone**: Groups multiple activities and tracks overall progress
- **Project**: Aggregates milestones and provides overall statistics

## How It Works
1. User enters a project name
2. User specifies the number of milestones and activities
3. The program initializes all data through user input
4. A menu allows the user to:
   - Update activity progress
   - View project and milestone statistics
   - Exit the application

## Files
- `main.c` — Program entry point and menu-driven interface
- `a1_functions.c` — Core logic for initialization, updates, and statistics
- `a1_functions.h` — Function declarations
- `a1_data_structures.h` — Data structures and constants
