/* a1_functions.h */
#ifndef A1_FUNCTIONS_H
#define A1_FUNCTIONS_H

#include "a1_data_structures.h"

// Constants
#define HOURS_PER_DAY 8
#define INITIAL_ID_CAPACITY 100

unsigned short int get_input_usi(void);
float get_input_f(void);



// ID management functions (Task 5)
id_manager_t* init_id_manager(int initial_capacity);
void free_id_manager(id_manager_t* manager);
bool is_id_unique(unsigned short int id, id_manager_t* manager);
bool add_id(unsigned short int id, id_manager_t* manager);

// Memory management functions
project_t* create_project(void);
milestone_t* create_milestone_array(int size);
activity_t* create_activity_array(int size);
void free_project(project_t* project);
void free_milestone(milestone_t* milestone);

// Core project management functions
void init_activity(activity_t* activity_to_init);
void init_milestone(milestone_t* milestone_to_init);
project_t* init_project(char name[]);
void print_main_menu(void);
void print_milestone_stats(const project_t* project);
void print_project_stats(const project_t* project);
void update_activity(activity_t* activity_to_update);
void update_milestone(milestone_t* milestone_to_update);
void update_project(project_t* project);

#endif
