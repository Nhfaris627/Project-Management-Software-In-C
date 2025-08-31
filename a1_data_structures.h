/* a1_data_structures.h */
#ifndef A1_DATA_STRUCTURES_H
#define A1_DATA_STRUCTURES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * ID Manager Structure (Task 5)
 * 
 * This structure manages unique IDs across the entire project to ensure
 * no two activities or milestones share the same ID. Uses dynamic array
 * allocation to grow as needed.
 * 
 * Fields:
 * - used_ids: Dynamic array storing all allocated IDs
 * - num_used: Current number of IDs in use
 * - capacity: Maximum capacity of the used_ids array before reallocation
 */
typedef struct {
    unsigned short int* used_ids;  // Dynamic array of used IDs
    int num_used;                  // Number of currently used IDs
    int capacity;                  // Current capacity of the array
} id_manager_t;

/**
 * Activity Structure
 * 
 * Represents the smallest unit of work in a project. Each activity has
 * both planned and actual values for cost and duration to track variance.
 * 
 * Fields:
 * - id: Unique identifier for the activity
 * - name: Human-readable name (max 99 chars + null terminator)
 * - planned_cost/actual_cost: Budget vs reality tracking
 * - planned_duration/actual_duration: Time estimation vs reality (in hours)
 * - completed: Boolean flag indicating if work is done
 */
typedef struct activity {
    unsigned short int id;              // Unique ID (0-65535)
    char name[100];                     // Activity name
    float planned_cost, actual_cost;    // Financial tracking
    unsigned short int planned_duration, actual_duration;  // Time in hours
    bool completed;                     // Completion status
} activity_t;

/**
 * Milestone Structure
 * 
 * Groups related activities together. A milestone is complete only when
 * ALL its activities are complete. Costs and durations are calculated
 * as the sum of all contained activities.
 * 
 * Fields:
 * - id: Unique identifier for the milestone
 * - name: Human-readable name
 * - activity_list: Dynamically allocated array of activities
 * - num_activities: Size of the activity array
 * - completed: Auto-calculated based on activity completion
 * - actual_cost: Sum of all activity actual costs
 * - actual_duration: Sum of all activity durations converted to days
 */
typedef struct milestone {
    unsigned short int id;              // Unique ID
    char name[100];                     // Milestone name
    activity_t* activity_list;          // Dynamic array of activities
    int num_activities;                 // Number of activities in this milestone
    bool completed;                     // Calculated completion status
    float actual_cost;                  // Sum of activity costs
    short int actual_duration;          // Total duration in days
} milestone_t;

/**
 * Project Structure
 * 
 * Top-level container for the entire project. Contains multiple milestones
 * and manages the unified ID system. Project completion depends on all
 * milestones being complete.
 * 
 * Fields:
 * - name: Project name
 * - planned_cost/actual_cost: Total project budget tracking
 * - planned_duration/actual_duration: Total project timeline
 * - completed: Auto-calculated based on milestone completion
 * - milestone_list: Dynamic array of milestones
 * - num_milestones: Size of the milestone array
 * - id_manager: Unified ID management system for uniqueness
 */
typedef struct project {
    char name[100];                     // Project name
    float planned_cost, actual_cost;    // Total project costs
    unsigned short int planned_duration, actual_duration;  // Total time in days
    bool completed;                     // Overall completion status
    milestone_t* milestone_list;        // Dynamic array of milestones
    int num_milestones;                 // Number of milestones
    id_manager_t* id_manager;          // Unified ID manager for uniqueness
} project_t;

#endif