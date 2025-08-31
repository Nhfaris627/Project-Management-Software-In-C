/* a1_functions.h */
#ifndef A1_FUNCTIONS_H
#define A1_FUNCTIONS_H

#include "a1_data_structures.h"

// System Constants
#define HOURS_PER_DAY 8          // Standard 8-hour work day for conversion
#define INITIAL_ID_CAPACITY 100  // Starting capacity for ID manager array

// =============================================================================
// INPUT VALIDATION FUNCTIONS
// =============================================================================

/**
 * Get validated unsigned short integer input from user
 * Continuously prompts until valid positive integer is entered
 * @return Valid unsigned short integer (1 to 65535)
 */
unsigned short int get_input_usi(void);

/**
 * Get validated float input from user
 * Continuously prompts until valid positive float is entered
 * @return Valid positive float value
 */
float get_input_f(void);

// =============================================================================
// ID MANAGEMENT FUNCTIONS (Task 5)
// =============================================================================

/**
 * Initialize ID manager with specified initial capacity
 * @param initial_capacity Starting size of ID array
 * @return Pointer to initialized ID manager, exits on allocation failure
 */
id_manager_t* init_id_manager(int initial_capacity);

/**
 * Free all memory associated with ID manager
 * @param manager Pointer to ID manager to free
 */
void free_id_manager(id_manager_t* manager);

/**
 * Check if an ID is unique (not already in use)
 * @param id ID to check for uniqueness
 * @param manager ID manager to search in
 * @return true if ID is unique, false if already used
 */
bool is_id_unique(unsigned short int id, id_manager_t* manager);

/**
 * Add a new ID to the manager (assumes ID is unique)
 * Automatically grows array capacity if needed
 * @param id ID to add to the manager
 * @param manager ID manager to add ID to
 * @return true on success, false on memory allocation failure
 */
bool add_id(unsigned short int id, id_manager_t* manager);

// =============================================================================
// MEMORY MANAGEMENT FUNCTIONS
// =============================================================================

/**
 * Create and initialize a new project structure
 * Includes ID manager initialization
 * @return Pointer to new project, exits on allocation failure
 */
project_t* create_project(void);

/**
 * Create dynamic array of milestones
 * @param size Number of milestones to allocate
 * @return Pointer to milestone array, exits on allocation failure
 */
milestone_t* create_milestone_array(int size);

/**
 * Create dynamic array of activities
 * @param size Number of activities to allocate
 * @return Pointer to activity array, exits on allocation failure
 */
activity_t* create_activity_array(int size);

/**
 * Free entire project and all associated memory
 * Recursively frees milestones, activities, and ID manager
 * @param project Pointer to project to free
 */
void free_project(project_t* project);

/**
 * Free milestone's activity array
 * @param milestone Pointer to milestone whose activities to free
 */
void free_milestone(milestone_t* milestone);

// =============================================================================
// CORE PROJECT MANAGEMENT FUNCTIONS
// =============================================================================

/**
 * Initialize activity with user input for planned values
 * Sets actual values to 0 and completed to false
 * @param activity_to_init Pointer to activity to initialize
 */
void init_activity(activity_t* activity_to_init);

/**
 * Initialize milestone with user input for number of activities
 * Creates activity array and sets initial values
 * @param milestone_to_init Pointer to milestone to initialize
 */
void init_milestone(milestone_t* milestone_to_init);

/**
 * Create and initialize project with given name
 * Gets number of milestones from user and creates milestone array
 * @param name Project name to set
 * @return Pointer to initialized project
 */
project_t* init_project(char name[]);

// =============================================================================
// USER INTERFACE FUNCTIONS
// =============================================================================

/**
 * Display main menu options to user
 */
void print_main_menu(void);

/**
 * Print detailed statistics for all milestones in project
 * Shows completion status and progress for each milestone
 * @param project Project containing milestones to display
 */
void print_milestone_stats(const project_t* project);

/**
 * Print comprehensive project statistics
 * Includes cost/schedule variance analysis if completed
 * @param project Project to display statistics for
 */
void print_project_stats(const project_t* project);

// =============================================================================
// UPDATE FUNCTIONS
// =============================================================================

/**
 * Update activity with actual duration, cost, and completion status
 * Gets input from user for all actual values
 * @param activity_to_update Pointer to activity to update
 */
void update_activity(activity_t* activity_to_update);

/**
 * Update milestone based on its activities' current status
 * Recalculates completion status, total cost, and duration
 * @param milestone_to_update Pointer to milestone to update
 */
void update_milestone(milestone_t* milestone_to_update);

/**
 * Update project based on its milestones' current status
 * Recalculates overall completion status, total cost, and duration
 * @param project Pointer to project to update
 */
void update_project(project_t* project);

#endif