/* main.c */
#include "a1_functions.h"
#include <stdio.h>
#include <string.h>

/**
 * PROJECT MANAGEMENT SYSTEM
 * 
 * This program implements a hierarchical project management system with:
 * - Projects containing multiple Milestones
 * - Milestones containing multiple Activities  
 * - Unified ID management to ensure uniqueness
 * - Cost and time tracking with variance analysis
 * - Dynamic memory allocation for scalability
 * 
 * Program Flow:
 * 1. Initialize project with user-defined structure
 * 2. Set up milestones and activities with unique IDs
 * 3. Enter main loop for activity updates and reporting
 * 4. Clean up all allocated memory on exit
 */

/**
 * Find activity by ID across all milestones
 * 
 * Helper function to locate an activity by its unique ID.
 * Searches through all milestones and their activities.
 * 
 * @param project Project to search in
 * @param activity_id ID of activity to find
 * @param milestone_out Output parameter for containing milestone
 * @return Pointer to activity if found, NULL otherwise
 */
activity_t* find_activity_by_id(project_t* project, unsigned short int activity_id, milestone_t** milestone_out) {
    for (int i = 0; i < project->num_milestones; i++) {
        milestone_t* milestone = &project->milestone_list[i];
        for (int j = 0; j < milestone->num_activities; j++) {
            if (milestone->activity_list[j].id == activity_id) {
                if (milestone_out) {
                    *milestone_out = milestone;
                }
                return &milestone->activity_list[j];
            }
        }
    }
    return NULL;
}

/**
 * Display all incomplete activities with their IDs
 * 
 * Searches through all milestones and activities to find incomplete ones.
 * Returns the count of incomplete activities found.
 * 
 * @param project Project to search for incomplete activities
 * @return Number of incomplete activities found
 */
int display_incomplete_activities(const project_t* project) {
    int incomplete_count = 0;
    
    printf("\nINCOMPLETE ACTIVITIES:\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < project->num_milestones; i++) {
        const milestone_t* milestone = &project->milestone_list[i];
        for (int j = 0; j < milestone->num_activities; j++) {
            const activity_t* activity = &milestone->activity_list[j];
            if (!activity->completed) {
                printf("ID: %hu | %s (in milestone: %s)\n", 
                       activity->id, activity->name, milestone->name);
                incomplete_count++;
            }
        }
    }
    
    if (incomplete_count == 0) {
        printf("All activities are completed!\n");
    }
    
    return incomplete_count;
}

/**
 * Get unique ID from user with validation
 * 
 * Continuously prompts user until a unique ID is provided.
 * Uses the project's ID manager to check uniqueness.
 * 
 * @param project Project containing ID manager
 * @param item_type Description of item (e.g., "milestone", "activity")
 * @param item_number Item number for display purposes
 * @return Unique validated ID
 */
unsigned short int get_unique_id(project_t* project, const char* item_type, int item_number) {
    unsigned short int id;
    
    do {
        printf("Enter unique ID for %s %d: ", item_type, item_number);
        id = get_input_usi();
        
        if (!is_id_unique(id, project->id_manager)) {
            printf("ID %hu is already in use. Please enter a different ID.\n", id);
        }
    } while (!is_id_unique(id, project->id_manager));
    
    // Add the ID to the manager
    if (!add_id(id, project->id_manager)) {
        printf("ERROR: Failed to register ID. Exiting...\n");
        exit(EXIT_FAILURE);
    }
    
    return id;
}

int main(void) {
    printf("WELCOME TO THE PROJECT MANAGEMENT SYSTEM!\n");
    printf("============================================================\n");
    
    // =========================================================================
    // PROJECT INITIALIZATION
    // =========================================================================
    
    // Get project name with improved input handling
    char project_name[100];
    printf("Enter project name: ");
    
    // Clear any residual input and get project name
    while (getchar() != '\n'); // Clear buffer
    if (fgets(project_name, sizeof(project_name), stdin)) {
        // Remove newline character if present
        project_name[strcspn(project_name, "\n")] = '\0';
    }
    
    project_t* project = init_project(project_name);
    printf("\nProject '%s' created successfully!\n", project->name);
    
    // =========================================================================
    // MILESTONE AND ACTIVITY SETUP
    // =========================================================================
    
    printf("\nSetting up %d milestone(s)...\n", project->num_milestones);
    
    for (int i = 0; i < project->num_milestones; i++) {
        milestone_t* milestone = &project->milestone_list[i];
        
        printf("\nMILESTONE %d SETUP\n", i + 1);
        printf("-------------------------\n");
        
        // Get unique milestone ID
        milestone->id = get_unique_id(project, "milestone", i + 1);
        
        // Get milestone name
        printf("Enter name for milestone %d: ", i + 1);
        scanf("%99s", milestone->name); // Prevent buffer overflow
        
        // Initialize milestone (creates activity array)
        init_milestone(milestone);
        
        // =====================================================================
        // ACTIVITY SETUP FOR THIS MILESTONE
        // =====================================================================
        
        printf("\nSetting up %d activity/activities for milestone '%s':\n", 
               milestone->num_activities, milestone->name);
        
        for (int j = 0; j < milestone->num_activities; j++) {
            activity_t* activity = &milestone->activity_list[j];
            
            printf("\n  Activity %d/%d:\n", j + 1, milestone->num_activities);
            
            // Get unique activity ID
            activity->id = get_unique_id(project, "activity", j + 1);
            
            // Get activity name
            printf("  Enter name for activity %d: ", j + 1);
            scanf("%99s", activity->name); // Prevent buffer overflow
            
            // Initialize activity with planned values
            init_activity(activity);
            
            printf("  Activity '%s' (ID: %hu) created successfully!\n", 
                   activity->name, activity->id);
        }
        
        printf("\nMilestone '%s' setup complete!\n", milestone->name);
    }
    
    printf("\nProject setup complete! Ready for activity tracking.\n");
    
    // =========================================================================
    // MAIN APPLICATION LOOP
    // =========================================================================
    
    int choice;
    do {
        print_main_menu();
        choice = get_input_usi();
        
        switch (choice) {
            case 1: {
                // UPDATE ACTIVITY WORKFLOW
                printf("\nUPDATE ACTIVITY WORKFLOW\n");
                printf("===================================\n");
                
                // Display incomplete activities and get count
                int incomplete_count = display_incomplete_activities(project);
                
                if (incomplete_count == 0) {
                    printf("\nCongratulations! All activities are completed!\n");
                    break;
                }
                
                // Get activity ID to update
                printf("\nEnter ID of activity to update (0 to cancel): ");
                unsigned short int update_id = get_input_usi();
                
                if (update_id == 0) {
                    printf("Update cancelled.\n");
                    break;
                }
                
                // Find the activity and its containing milestone
                milestone_t* containing_milestone = NULL;
                activity_t* activity = find_activity_by_id(project, update_id, &containing_milestone);
                
                if (activity == NULL) {
                    printf("Activity with ID %hu not found.\n", update_id);
                    break;
                }
                
                if (activity->completed) {
                    printf("Activity '%s' is already completed.\n", activity->name);
                    break;
                }
                
                // Update the activity
                printf("\nUpdating activity: %s\n", activity->name);
                update_activity(activity);
                
                // Propagate updates up the hierarchy
                update_milestone(containing_milestone);
                update_project(project);
                
                printf("\nActivity and related milestones updated successfully!\n");
                
                // Check if milestone or project just became complete
                if (containing_milestone->completed) {
                    printf("Milestone '%s' is now COMPLETE!\n", containing_milestone->name);
                }
                
                if (project->completed) {
                    printf("PROJECT '%s' IS NOW COMPLETE!\n", project->name);
                }
                
                break;
            }
            
            case 2:
                // PRINT STATISTICS
                print_project_stats(project);
                break;
                
            case 3:
                // EXIT
                printf("\nThank you for using the Project Management System!\n");
                printf("Cleaning up and exiting...\n");
                break;
                
            default:
                printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
        
        // Add pause for better user experience (except on exit)
        if (choice != 3) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n'); // Clear any remaining input
            getchar(); // Wait for Enter key
        }
        
    } while (choice != 3);
    
    // =========================================================================
    // CLEANUP AND EXIT
    // =========================================================================
    
    // Free all allocated memory
    free_project(project);
    printf("Memory cleanup complete. Goodbye!\n");
    
    return 0;
}