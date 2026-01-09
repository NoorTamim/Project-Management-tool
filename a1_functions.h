/********* a1_functions.h ********
*
* Student Name: Noor Karabala
*
* Purpose:
*   Function prototypes for the project/milestone/activity tracker.
*/
#ifndef __A1_FUNCTIONS_H__
#define __A1_FUNCTIONS_H__
#include "a1_data_structures.h"



/*
   Get unsigned short integer user input.
   Ensures the returned value is positive.
*/
unsigned short int get_input_usi(void);


/*
   Get float user input.
   Ensures the returned value is positive.
*/
float get_input_f(void);


/*
   Initialize all fields of an activity.
*/
void init_activity(activity_t * activity_to_int);


/*
   Initialize all fields of a milestone.
   Calls init_activity for each activity in the milestone.
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities);


/*
   Initialize all fields of a project.
   number_activities contains the number of activities per milestone.
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities);


/*
   Print the main program menu.
*/
void print_main_menu(void);


/*
   Print statistics for each milestone.
   number_activities contains the number of activities per milestone.
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities);


/*
   Print overall project statistics.
   Calls print_milestone_stats if the project is not yet completed.
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Update the data of a single activity.
*/
void update_activity(activity_t * activity_to_update);


/*
   Update milestone status and totals based on its activities.
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone);


/*
   Update project status and totals based on its milestones.
*/
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project);


/*
   Generate and return a unique ID.
   Prompts the user again if a duplicate ID is entered.
*/
unsigned short int get_unique_id();

#endif