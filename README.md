# Project Management System

A comprehensive C-based project management system that enables hierarchical tracking of projects, milestones, and activities with dynamic memory allocation and unified ID management.

## Overview

This system implements a three-tier hierarchical structure where:
- **Projects** contain multiple **Milestones**
- **Milestones** contain multiple **Activities**
- Each component tracks both planned and actual costs/durations for variance analysis

## Features

### Core Functionality
- **Hierarchical Project Structure**: Organize work into projects → milestones → activities
- **Unified ID Management**: Ensures unique IDs across all project components
- **Dynamic Memory Allocation**: Scalable to handle projects of any size
- **Cost & Time Tracking**: Compare planned vs actual values with variance analysis
- **Automatic Status Updates**: Project and milestone completion calculated automatically
- **Interactive CLI Interface**: User-friendly command-line interface with input validation

### Technical Features
- **Memory Safety**: Comprehensive memory management with proper cleanup
- **Input Validation**: Robust error handling for all user inputs
- **Efficient Data Structures**: Dynamic arrays with automatic resizing
- **Modular Design**: Well-organized code structure with clear separation of concerns

## File Structure

```
project-management-system/
├── a1_data_structures.h    # Core data structure definitions
├── a1_functions.h          # Function declarations and constants
├── a1_functions.c          # Implementation of all core functions
├── main.c                  # Main program and user interface
└── README.md              # This file
```

## Data Structure Hierarchy

```
Project
├── Name, costs, duration, completion status
├── ID Manager (unified across project)
└── Milestones[]
    ├── Name, ID, costs, duration, completion status
    └── Activities[]
        └── Name, ID, planned/actual costs, planned/actual duration, completion status
```

## Compilation and Usage

### Prerequisites
- GCC compiler or any C99-compatible compiler
- Standard C libraries (stdio.h, stdlib.h, string.h, math.h, stdbool.h)

### Compilation
```bash
gcc -o project_manager main.c a1_functions.c -lm
```

### Running the Program
```bash
./project_manager
```

## Program Flow

1. **Project Initialization**
   - Enter project name
   - Define number of milestones
   - Set up milestone structure

2. **Milestone & Activity Setup**
   - Assign unique IDs to milestones
   - Define activities for each milestone
   - Assign unique IDs to activities
   - Set planned costs and durations

3. **Activity Management**
   - View incomplete activities
   - Update activity progress with actual values
   - Automatic propagation of updates to milestones and project

4. **Reporting**
   - View project statistics
   - Analyze cost and schedule variances
   - Track milestone completion progress

## Key Functions

### Memory Management
- `create_project()` - Allocate project structure with ID manager
- `create_milestone_array()` - Dynamic milestone allocation
- `create_activity_array()` - Dynamic activity allocation
- `free_project()` - Complete memory cleanup

### ID Management
- `init_id_manager()` - Initialize unified ID system
- `is_id_unique()` - Check ID uniqueness
- `add_id()` - Register new ID with automatic array expansion

### Core Operations
- `update_activity()` - Update activity with actual values
- `update_milestone()` - Recalculate milestone status and totals
- `update_project()` - Recalculate project status and totals
- `print_project_stats()` - Generate comprehensive reports

### Input Validation
- `get_input_usi()` - Validated unsigned short integer input
- `get_input_f()` - Validated positive float input

## Usage Example

```
WELCOME TO THE PROJECT MANAGEMENT SYSTEM!
============================================================
Enter project name: Website Redesign

Enter number of milestones: 2

MILESTONE 1 SETUP
-------------------------
Enter unique ID for milestone 1: 100
Enter name for milestone 1: Design
Enter number of activities for this milestone: 2

  Activity 1/2:
  Enter unique ID for activity 1: 101
  Enter name for activity 1: Wireframes
  Enter planned duration (in hours) for activity 'Wireframes': 20
  Enter planned cost ($) for activity 'Wireframes': 500

[... continues with setup ...]

Please select one of the following options:
1. Update activity
2. Print stats
3. Exit
```

## Memory Management

The system uses dynamic memory allocation throughout:
- **Project Structure**: Contains ID manager and milestone array
- **ID Manager**: Dynamic array that grows as needed (starts at 100, doubles when full)
- **Milestone Arrays**: Allocated based on user input
- **Activity Arrays**: Allocated per milestone based on user input

All memory is properly freed on program exit to prevent memory leaks.

## Error Handling

- **Input Validation**: Continuous prompts for valid input
- **Memory Allocation**: Program exits gracefully if allocation fails
- **ID Uniqueness**: Enforced across all project components
- **Buffer Overflow Protection**: Safe string operations with bounds checking

## Variance Analysis

When a project is completed, the system provides:
- **Cost Variance**: Actual vs planned costs with percentage over/under budget
- **Schedule Variance**: Actual vs planned duration with days ahead/behind schedule

## Technical Specifications

- **ID Range**: 1 to 65,535 (unsigned short int)
- **String Limits**: 99 characters + null terminator for names
- **Work Day**: 8 hours (configurable constant)
- **Initial ID Capacity**: 100 IDs (automatically expands)

## Contributing

This project demonstrates:
- Dynamic memory management in C
- Hierarchical data structures
- Input validation and error handling
- Modular programming practices
- Memory safety and cleanup

## License

This project is available for educational and personal use. Please provide attribution if used in academic or commercial contexts.
