#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_COURSES 5
#define MAX_NAME_LEN 50
#define DATA_FILE "student_data.txt"

int student_count = 0;

struct StudentInfo {
    char fname[MAX_NAME_LEN];
    char lname[MAX_NAME_LEN];
    int roll;
    float cgpa;
    int cid[MAX_COURSES];
} students[MAX_STUDENTS];

void save_to_file() {
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        printf("\033[0;31mError opening file for writing.\033[0m\n");
        return;
    }

    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(struct StudentInfo), student_count, file);
    fclose(file);
}

void load_from_file() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("\033[0;33mNo previous data found. Starting fresh.\033[0m\n");
        return;
    }

    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(struct StudentInfo), student_count, file);
    fclose(file);
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("\033[0;31mMaximum number of students reached.\033[0m\n");
        return;
    }

    struct StudentInfo *student = &students[student_count];

    printf("\033[0;34mEnter the first name of the student: \033[0m");
    scanf("%s", student->fname);

    printf("\033[0;34mEnter the last name of the student: \033[0m");
    scanf("%s", student->lname);

    printf("\033[0;34mEnter the roll number: \033[0m");
    scanf("%d", &student->roll);

    printf("\033[0;34mEnter the CGPA: \033[0m");
    scanf("%f", &student->cgpa);

    printf("\033[0;34mEnter the course IDs (up to %d courses):\033[0m\n", MAX_COURSES);
    for (int j = 0; j < MAX_COURSES; j++) {
        scanf("%d", &student->cid[j]);
    }

    student_count++;
    printf("\033[0;32mStudent added successfully.\033[0m\n");
}

void find_by_roll_number() {
    int roll;
    printf("\033[0;34mEnter the roll number of the student: \033[0m");
    scanf("%d", &roll);

    for (int j = 0; j < student_count; j++) {
        if (students[j].roll == roll) {
            printf("\033[0;32mStudent found:\033[0m\n");
            printf("First Name: %s\n", students[j].fname);
            printf("Last Name: %s\n", students[j].lname);
            printf("CGPA: %.2f\n", students[j].cgpa);
            printf("Course IDs: ");
            for (int d = 0; d < MAX_COURSES; d++) {
                printf("%d ", students[j].cid[d]);
            }
            printf("\n");
            return;
        }
    }

    printf("\033[0;31mNo student found with roll number %d.\033[0m\n", roll);
}

void find_by_first_name() {
    char fname[MAX_NAME_LEN];
    printf("\033[0;34mEnter the first name of the student: \033[0m");
    scanf("%s", fname);

    for (int j = 0; j < student_count; j++) {
        if (strcmp(students[j].fname, fname) == 0) {
            printf("\033[0;32mStudent found:\033[0m\n");
            printf("First Name: %s\n", students[j].fname);
            printf("Last Name: %s\n", students[j].lname);
            printf("Roll Number: %d\n", students[j].roll);
            printf("CGPA: %.2f\n", students[j].cgpa);
            printf("Course IDs: ");
            for (int d = 0; d < MAX_COURSES; d++) {
                printf("%d ", students[j].cid[d]);
            }
            printf("\n");
            return;
        }
    }

    printf("\033[0;31mNo student found with first name %s.\033[0m\n", fname);
}

void find_by_course_id() {
    int course_id;
    printf("\033[0;34mEnter the course ID: \033[0m");
    scanf("%d", &course_id);

    int found = 0;
    for (int j = 0; j < student_count; j++) {
        for (int d = 0; d < MAX_COURSES; d++) {
            if (students[j].cid[d] == course_id) {
                if (!found) {
                    printf("\033[0;32mStudents enrolled in course ID %d:\033[0m\n", course_id);
                    found = 1;
                }
                printf("First Name: %s, Last Name: %s, Roll Number: %d, CGPA: %.2f\n",
                       students[j].fname, students[j].lname, students[j].roll, students[j].cgpa);
                break;
            }
        }
    }

    if (!found) {
        printf("\033[0;31mNo students found enrolled in course ID %d.\033[0m\n", course_id);
    }
}

void total_students() {
    printf("\033[0;32mTotal number of students: %d\033[0m\n", student_count);
    printf("You can add %d more students.\n", MAX_STUDENTS - student_count);
}

void delete_student() {
    int roll;
    printf("\033[0;34mEnter the roll number of the student to delete: \033[0m");
    scanf("%d", &roll);

    for (int j = 0; j < student_count; j++) {
        if (students[j].roll == roll) {
            for (int k = j; k < student_count - 1; k++) {
                students[k] = students[k + 1];
            }
            student_count--;
            printf("\033[0;32mStudent with roll number %d deleted successfully.\033[0m\n", roll);
            return;
        }
    }

    printf("\033[0;31mNo student found with roll number %d.\033[0m\n", roll);
}

void update_student() {
    int roll;
    printf("\033[0;34mEnter the roll number of the student to update: \033[0m");
    scanf("%d", &roll);

    for (int j = 0; j < student_count; j++) {
        if (students[j].roll == roll) {
            printf("\033[0;34mSelect field to update:\033[0m\n");
            printf("1. First Name\n");
            printf("2. Last Name\n");
            printf("3. Roll Number\n");
            printf("4. CGPA\n");
            printf("5. Courses\n");
            int choice;
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("\033[0;34mEnter new first name: \033[0m");
                    scanf("%s", students[j].fname);
                    break;
                case 2:
                    printf("\033[0;34mEnter new last name: \033[0m");
                    scanf("%s", students[j].lname);
                    break;
                case 3:
                    printf("\033[0;34mEnter new roll number: \033[0m");
                    scanf("%d", &students[j].roll);
                    break;
                case 4:
                    printf("\033[0;34mEnter new CGPA: \033[0m");
                    scanf("%f", &students[j].cgpa);
                    break;
                case 5:
                    printf("\033[0;34mEnter new course IDs: \033[0m");
                    for (int d = 0; d < MAX_COURSES; d++) {
                        scanf("%d", &students[j].cid[d]);
                    }
                    break;
                default:
                    printf("\033[0;31mInvalid choice.\033[0m\n");
                    return;
            }
            printf("\033[0;32mStudent details updated successfully.\033[0m\n");
            return;
        }
    }

    printf("\033[0;31mNo student found with roll number %d.\033[0m\n", roll);
}

int main() {
    load_from_file();

    while (1) {
        printf("\033[0;32m\n-------------------------------------------\n");
        printf("Welcome to SIMS (Student Information Management System)\n");
        printf("-------------------------------------------\033[0m\n");
        printf("\033[0;34mSelect an option:\033[0m\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll Number\n");
        printf("3. Find Student by First Name\n");
        printf("4. Find Students by Course ID\n");
        printf("5. View Total Number of Students\n");
        printf("6. Delete Student by Roll Number\n");
        printf("7. Update Student Details\n");
        printf("8. Exit\n");

        int choice;
        printf("\033[0;34mEnter your choice: \033[0m");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                find_by_roll_number();
                break;
            case 3:
                find_by_first_name();
                break;
            case 4:
                find_by_course_id();
                break;
            case 5:
                total_students();
                break;
            case 6:
                delete_student();
                break;
            case 7:
                update_student();
                break;
            case 8:
                save_to_file();
                printf("\033[0;32mData saved. Exiting...\033[0m\n");
                exit(0);
                break;
            default:
                printf("\033[0;31mInvalid choice. Please try again.\033[0m\n");
        }
    }

    return 0;
}

