/********* main.c ********
*	
* Student Name: Noor Karabala
*
* Purpose: Runs the CLI menu loop to initialize a project, update activities, and print stats.
*/



#include <stdio.h>
#include <stdlib.h>
#include "a1_data_structures.h"
#include "a1_functions.h"
 
int main() {
    
    printf("Welcome to Project Management Application\n");

    
    char project_name[100];
    printf("Please enter the project name: ");
    scanf("%s", project_name); 

    unsigned short int num_milestones = 0;
    unsigned short int number_of_activities = 0;
    
    printf("Please enter the number of milestones (1 to %d): ", MAX_MILESTONES);
    num_milestones = get_input_usi();

    if(num_milestones > MAX_MILESTONES){
        printf("\n-----------------------------------------------------\n");
        printf("YOUR INPUT IS NOT FROM 1 TO %d \n", MAX_MILESTONES);
        printf("Please enter the number of milestones (1 to %d) again: ", MAX_MILESTONES);
        num_milestones = get_input_usi();
    }
    
   
    milestone_t milestone_list_[MAX_MILESTONES];
    int num_activities_[NUM_ACTIVITIES];

    
    for (int i = 0; i < num_milestones; i++) {
        
        printf("Please enter the number of activities for milestone %d (1 to %d): ", i + 1, NUM_ACTIVITIES);
        num_activities_[i] = get_input_usi();
        if(num_activities_[i] > NUM_ACTIVITIES){
            printf("\n-----------------------------------------------------\n");
            printf("YOUR INPUT IS NOT FROM 1 TO 3 \n");
            printf("Please enter the number of activities for milestone %d (1 to %d): ", i + 1, NUM_ACTIVITIES);
            num_activities_[i] = get_input_usi();
        }
    }

    
    project_t my_project = init_project(project_name, milestone_list_, num_milestones, num_activities_);

    

    int choice;
    do {
        print_main_menu(); 
        printf("Please enter your choice: ");
        choice = get_input_usi();

        while (choice > 3) {
            printf("\n-----------------------------------------------------\n");
            printf("YOUR INPUT IS NOT FROM 1 TO 3\n");
            printf("Please enter your choice (1 to 3) again: ");
            choice = get_input_usi();
        }

        if (choice == 1) {
            int has_incomplete_activity = 0;

            // Check if there are any incomplete activities
            for (int i = 0; i < num_milestones; i++) {
                for (int j = 0; j < num_activities_[i]; j++) {
                    if (!milestone_list_[i].activity_list[j].completed) {
                        has_incomplete_activity = 1;
                        break;
                    }
                }
                if (has_incomplete_activity) break;
            }

            if (!has_incomplete_activity) {
                printf("No incomplete activities to update.\n");
            } else {
                
                for (int i = 0; i < num_milestones; i++) { 
                    for (int j = 0; j < num_activities_[i]; j++) { 
                        if (!milestone_list_[i].activity_list[j].completed) { 
                            printf("Activity name: %s.      Activity ID: %d.        Completed: %s.\n", 
                            milestone_list_[i].activity_list[j].name, 
                            milestone_list_[i].activity_list[j].id, 
                            milestone_list_[i].activity_list[j].completed ? "true" : "false");
                        }
                    }
                }

                int activity_id_to_change;
                printf("Which activity do you want to update? (Enter the ID only, not the name): ");
                activity_id_to_change = get_input_usi();

                int is_valid = 0; 
                int milestone_index = -1;
                for (int i = 0; i < num_milestones; i++) { 
                    for (int j = 0; j < num_activities_[i]; j++) { 
                        if ((milestone_list_[i].activity_list[j].id == activity_id_to_change) && !milestone_list_[i].activity_list[j].completed) {
                            is_valid = 1; 
                            milestone_index = i; 
                            break; 
                        }
                    }
                    if (is_valid) break; 
                }

                if (is_valid) {
                    update_milestone(&milestone_list_[milestone_index], num_activities_[milestone_index]);
                    update_project(milestone_list_, num_milestones, num_activities_, &my_project);
                } else {
                    printf("Invalid selection. Please enter a valid ID for an uncompleted activity.\n");
                }
            }
        } else if (choice == 2) {
            printf("\nPrinting project stats\n");
            print_project_stats(my_project, milestone_list_, num_milestones, num_activities_);
        }
    } while (choice != 3); 

    printf("Goodbye!\n");
    return 0;
}