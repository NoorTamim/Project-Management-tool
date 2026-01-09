/********* a1_functions.c ********

* Student Name: Noor Karabala
*
* Purpose:
*   Implements input helpers, initialization, updates, and stats printing
*   for the project / milestone / activity tracking system.
*/

#include <math.h>   
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "a1_functions.h"
#include "a1_data_structures.h"

/*
   Get unsigned short integer user input.
   The value entered by the user must be positive.
   If the user enters a non-positive value, the function asks user to re-enter.
*/
unsigned short int get_input_usi(void){

	signed int user_input;
	scanf("%i", &user_input);

	while(user_input <= 0){

		printf("\n-----------------------------------------------------\n");
		printf("The value you entered is either zero or negative.\n");
		printf("Enter a positive value: ");
		scanf("%i", &user_input);
	}

	return (unsigned short int) user_input;
}


/*
   Get float user input. The value must be positive.
   If the user enters a non-positive value, the function asks user to re-enter.
*/
float get_input_f(void){

	float user_input;
	scanf("%f", &user_input);
	
	while(user_input <= 0){

		printf("-----------------------------------------------------\n");
		printf("The value you entered either zero or negative.\n");
		printf("Please enter a positive value: ");
		scanf("%f", &user_input);
	}

	return (float) user_input;
}


/* 
   Initialize all fields in an activity
*/
void init_activity(activity_t * activity_to_int){

	printf("\nEnter the activity ID (must be unique): ");
	activity_to_int -> id = get_unique_id();

    printf("Enter the activity name: ");
	scanf("%s", activity_to_int -> name);

    printf("Enter the planned duration in hours: ");
	activity_to_int -> planned_duration = get_input_usi();
    activity_to_int -> actual_duration = 0;

    activity_to_int -> planned_cost = (activity_to_int -> planned_duration) * SALARY;
	activity_to_int -> actual_cost = 0;

	activity_to_int -> completed = false;
}


/*
   Initialize all fields in the milestone.
   The implementation of your function MUST call the function init_activity.
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities){

    
	printf("Enter the milestone ID (must be unique): ");
	milestone_to_int -> id = get_unique_id();

	printf("Enter the milestone name: ");
	scanf("%s", milestone_to_int -> name);

	for (int i = 0; i < num_activities; i++) {

        printf("\n- Initializing Activity %d -", i + 1);
        init_activity(&milestone_to_int->activity_list[i]);
    }

    milestone_to_int -> completed = false;
    milestone_to_int -> actual_cost = 0;
    milestone_to_int -> actual_duration = 0;
}


/*
   Initialize all fields in the project.
   number_activities contains the number of activities per milestone.
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int* number_activities){

	project_t the_project;
	strcpy(the_project.name, name);

	for (int i = 0; i < number_milestones; i++) {
		
        printf("\n--- Initializing milestone %d ---\n", i + 1);
        init_milestone(&milestone_list[i], number_activities[i]);

        for (int j = 0; j < number_activities[i]; j++) {

            the_project.planned_cost += milestone_list[i].activity_list[j].planned_cost;
            the_project.planned_duration += milestone_list[i].activity_list[j].planned_duration;
        }
    }

    the_project.actual_cost = 0;
    the_project.actual_duration = 0;

	the_project.planned_duration = (the_project.planned_duration + HOURS_DAY - 1) / HOURS_DAY;
    
    the_project.completed = false;

	return the_project;
}

/* 
   Print the main menu
*/
void print_main_menu(void){

	printf("\n--- Main Menu --- Please select one of the following options: \n");
    printf("1. Update activity\n");
    printf("2. Print stats\n");
    printf("3. Exit\n");
}


/*
   Print out milestone stats
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){

    for (int i = 0; i < num_milestones; i++) {

        const milestone_t *milestone = &list_milestones[i];
        printf("\nMilestone: %s\n", milestone->name);
        
        if (milestone->completed) {
            
            float budget_difference = milestone->actual_cost - (milestone->actual_duration * SALARY); 
            int duration_difference = milestone->actual_duration - milestone->actual_duration; 
            printf("Completed: Yes\n");
            printf("Budget Status: %s $%.2f\n", 
                   (budget_difference >= 0) ? "Over budget" : "Under budget", 
                   fabs(budget_difference));
            printf("Duration Status: %s %d days\n", 
                   (duration_difference >= 0) ? "Delayed by" : "Early by", 
                   abs(duration_difference));
        } else {
            
            int completed_activities = 0;
            for (int j = 0; j < number_activities[i]; j++) {
                if (milestone->activity_list[j].completed) {
                    completed_activities++;
                }
            }
            printf("Completed: No\n");
            printf("Activities Completed: %d out of %d\n", completed_activities, number_activities[i]);
            printf("Planned Duration: %d hours\n", milestone->actual_duration); 
            printf("Planned Cost: $%.2f\n", milestone->actual_cost); 
        }
    }
}

/*
   Print out project stats
   number_activities contains the number of activities per milestone
   
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	printf("\nProject Name: %s\n", details.name);
    printf("Completed: %s\n", details.completed ? "Yes" : "No");

    if (details.completed){
        float budget_difference = details.actual_cost - details.planned_cost;
        int duration_difference = details.actual_duration - details.planned_duration;
        
        printf("Budget Status: %s $%.2f\n", (budget_difference >= 0) ? "Over budget" : "Under budget", fabs(budget_difference));
        printf("Duration Status: %s %d days\n", (duration_difference >= 0) ? "Delayed by" : "Early by", abs(duration_difference));

    }
    if (!details.completed) {
        print_milestone_stats(list_milestones, num_milestones, number_activities);
    }
}


/*
   Update activity
*/
void update_activity(activity_t * activity_to_update){
	printf("\nUpdating activity: %s\n", activity_to_update->name);

    printf("Enter actual duration in hours: ");
    activity_to_update->actual_duration = get_input_usi();

    printf("Enter actual cost in hours: ");
    activity_to_update->actual_cost = get_input_f();

    printf("Is the activity completed? (1 for Yes, 0 for No): ");
    unsigned short int completed_status = get_input_usi();
    activity_to_update->completed = (completed_status == 1);

    
    
}


/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){
	printf("\nUpdating milestone: %s\n", milestone_to_update->name);
    
    
    for (int i = 0; i < activities_in_milestone; i++) {
        update_activity(&milestone_to_update->activity_list[i]);
    }

    
    milestone_to_update->completed = true;
    for (int i = 0; i < activities_in_milestone; i++) {
        if (!milestone_to_update->activity_list[i].completed) {
            milestone_to_update->completed = false;
            break;
        }
    }

    
    milestone_to_update->actual_cost = 0;
    milestone_to_update->actual_duration = 0;
    for (int i = 0; i < activities_in_milestone; i++) {
        milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
        milestone_to_update->actual_duration += milestone_to_update->activity_list[i].actual_duration;
    }
}


/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	
    my_project->actual_cost = 0;
    my_project->actual_duration = 0;

    for (int i = 0; i < num_milestones; i++) {
        my_project->actual_cost += milestone_array[i].actual_cost;
        my_project->actual_duration += milestone_array[i].actual_duration;
    }

    
    my_project->actual_duration = (my_project->actual_duration + HOURS_DAY - 1) / HOURS_DAY;

    
    my_project->completed = true;
    for (int i = 0; i < num_milestones; i++) {
        if (!milestone_array[i].completed) {
            my_project->completed = false;
            break;
        }
    }
}


/* 
    checks if the entered id is unique
    If not it asks to input another id
*/
unsigned short int get_unique_id() {

    static unsigned short int id_array[MAX_MILESTONES * NUM_ACTIVITIES]; // Static array to store IDs
    static int id_count = 0;  // Counter for number of IDs stored
    unsigned short int new_id;
    int is_unique;
    
    do {
        printf("Enter a unique ID: ");
        new_id = get_input_usi(); 
        
        // Check if the ID is unique
        is_unique = 1; 
        for (int i = 0; i < id_count; i++) {
            if (id_array[i] == new_id) {
                is_unique = 0; 
                printf("ID already exists. Please enter a unique ID.\n");
                break;
            }
        }
        
        // If the ID is unique, store it
        if (is_unique) {
            id_array[id_count] = new_id;
            id_count++;  
        }
    } while (!is_unique); // Repeat until a unique ID is entered
    
    return new_id;  // Return the unique ID
}