# Saran-Project
#  Teacher management
## Abstract

This project is a simple Teacher Management System developed using basic C programming concepts such as loops, arrays, and string functions. The program allows users to create, update, delete, and view teacher profiles through a menu-driven interface. Each teacher profile includes details such as ID, name, age, qualification, phone number, and address.
To ensure data persistence, the system stores all teacher records in a text file (teachers_db.txt). When the program starts, it automatically loads the previously saved data from the file, allowing users to continue from where they left off. Any new changes, such as adding, updating, or deleting profiles, are immediately saved to the file.
The project demonstrates core programming concepts like file handling, data manipulation using arrays, and basic user input validation. It provides a practical example of how structured data can be managed in C without using advanced features like structures or dynamic memory allocation.

## Fundamental Requirements of the Code
### 1. A C Compiler

You must have a working C compiler such as:

a.GCC (Recommended)
b.Clang
c.MinGW (Windows)
d.Turbo C (not recommended but possible)
This is required to compile .c files into an executable

### 2. A Text Editor or IDE

You need a place to write and edit the code, such as:

a.Notepad / Notepad++
        or
b.VS Code (best option)
        or
c.Code::Blocks
        or
d.Dev C++
        or 
e.CLion
        or
f.GCC terminal editor (nano, vim)

### 3. Basic C Libraries

The code only uses standard libraries available in all C compilers:

These libraries provide:

a.Input/output functions
b.String manipulation
c.File handling

### 4. Understanding of Basic C Concepts

To follow or modify the code, you should know:

#### a.Loops
for, while

#### b.Arrays

Used to store:

names[],ages[],phones[],addresses[],IDs[]

#### c.String functions

Examples used:

fgets(),strncpy(),strtok(),strlen()

#### d.Conditionals

if, else, switch

#### e.File Handling

The program reads/writes a file:

teachers_db.txt

Functions used:
fopen(),fgets(),fprintf(),fclose()

This allows data to be saved permanently.

### 5. Basic Terminal/Command-Line Usage

You need to know how to:

Compile:
gcc teacher_manager.c -o teacher_manager

Run:
Windows:
teacher_manager.exe

Mac/Linux:
./teacher_manager


### 6. Storage File (Automatically Created)
The program requires a text file to store records:
teachers_db.txt

a.If it doesn’t exist, the program creates it
b.If it exists, it loads existing teacher data


## Features of the Project:
### 1. Create Teacher Profile

Allows the user to enter details:
Name, Age, Qualification, Phone Number, Address, ID

Stores each entry into arrays.

Automatically saves the new teacher record into teachers_db.txt.

### 2. Update Teacher Profile by ID

User enters the teacher’s ID.

Can update any individual field:
Name, Age, Qualification, Phone Number, Address

Updates are saved back to the file immediately.

### 3. Delete Teacher Profile by ID

Deletes the teacher record from arrays.

Automatically removes it permanently from the file on disk.

### 4. View All Teacher Profiles

Displays all stored records with complete details.

Shows data from both:

The file loaded on program start

New entries added during runtime

### 5. Data Persistence (File Storage)

Uses a simple text file teachers_db.txt.

Automatically loads all previously saved teacher profiles when the program starts.

Automatically saves after every:

Create

Update

Delete

### 6. Simple Menu-Driven Interface

Easy-to-understand options:

1) Create
2) Update
3) Delete
4) View
5) Exit


Uses only loops, arrays, and string functions, keeping it basic and beginner-friendly.

### 7. Input Validation

Rejects invalid ID updates/deletes.

Checks for duplicate IDs.

Ensures numeric values for age and choice selections.

### 8. Works Without Structures

Uses parallel arrays instead of struct, keeping the code completely “basic C”.

### 9. Cross-Platform

Works on Windows, Linux, and macOS with any standard C compiler (GCC, Clang, etc.).

## SCREEN SHOTS
### When you run the code the output put is 




<img width="328" height="161" alt="image" src="https://github.com/user-attachments/assets/98df05e3-b711-4c9c-8fb6-e170c966767d" />


### and when you give some inputs and your output will be 



<img width="411" height="325" alt="Screenshot 2025-11-21 154119" src="https://github.com/user-attachments/assets/1789a32c-2cdd-4ab7-bc2a-b6da263292e6" />



### and when you want to delete the output look like


<img width="436" height="180" alt="image" src="https://github.com/user-attachments/assets/d5900cad-c2c0-4699-a719-6f6c5907b2d3" />



### and when you want to updat the teacher profile the output looks like


<img width="343" height="192" alt="image" src="https://github.com/user-attachments/assets/1dc43164-c1d8-401f-b6c7-ebfeda0d788a" />


### and when youn want create a new teacher profile the input you can look like  this

<img width="412" height="156" alt="image" src="https://github.com/user-attachments/assets/0689393b-44cc-4df5-b1ed-e18a0aca1ce0" />
