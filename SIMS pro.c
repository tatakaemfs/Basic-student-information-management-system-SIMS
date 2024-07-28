#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0;

struct sinfo {
    char fname[50];
    char lname[50];
    int roll;
    float cgpa;
    int cid[10];
} st[55];

void save_to_file() {
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&i, sizeof(int), 1, file); // Save the total number of students

    for (int j = 0; j < i; j++) {
        fwrite(&st[j], sizeof(struct sinfo), 1, file); // Save each student's details
    }

    fclose(file);
}


void load_from_file() {
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(&i, sizeof(int), 1, file); // Read the total number of students

    for (int j = 0; j < i; j++) {
        fread(&st[j], sizeof(struct sinfo), 1, file); // Read each student's details
    }

    fclose(file);
}


void add_student() {
    printf("Add the Students Details\n");
    printf("-------------------------\n\n");

    printf("Enter the first name of student\n");
    scanf("%s", st[i].fname);

    printf("Enter the last name of student\n");
    scanf("%s", st[i].lname);

    printf("Enter the Roll Number\n");
    scanf("%d", &st[i].roll);

    printf("Enter the CGPA you obtained\n");
    scanf("%f", &st[i].cgpa);

    printf("Enter the course ID of each course\n");
    for (int j = 0; j < 5; j++) {
        scanf("%d", &st[i].cid[j]);
    }
    printf("-------------------------\n");

    i = i + 1;
}

void find_rl() {
    int x;
    printf("\nEnter the Roll Number of the student\n");
    scanf("%d", &x);
    printf("-------------------------\n");
    for (int j = 0; j < i; j++) {
        if (x == st[j].roll) {
            printf("\n\nThe Students Details are:\n\n");
            printf("The First name is %s\n", st[j].fname);
            printf("The Last name is %s\n", st[j].lname);
            printf("The CGPA is %f\n", st[j].cgpa);
            printf("Enter the course ID of each course\n");

            for (int d = 0; d < 5; d++) {
                printf("The course ID are %d\n", st[j].cid[d]);
            }

            return;
        }
    }

    printf("Roll Number not Found\n");
}

void find_fn() {
    char a[50];
    printf("\nEnter the First Name of the student\n");
    scanf("%s", a);

    printf("-------------------------\n");

    int c = 0;
    for (int j = 0; j < i; j++) {
        if (!strcmp(st[j].fname, a)) {
            printf("\n\nThe Students Details are:\n\n");
            printf("The First name is %s\n", st[j].fname);
            printf("The Last name is %s\n", st[j].lname);
            printf("The Roll Number is %d\n", st[j].roll);
            printf("The CGPA is %f\n", st[j].cgpa);
            printf("Enter the course ID of each course\n");

            for (int d = 0; d < 5; d++) {
                printf("The course ID are %d\n", st[j].cid[d]);
            }

            c = 1;
            break;
        }
    }

    if (c == 0) {
        printf("First Name not Found\n");
    }
}

void find_c() {
    int id;
    printf("\nEnter the course ID\n");
    scanf("%d", &id);

    printf("-------------------------\n");

    int c = 0;
    for (int j = 0; j < i; j++) {
        for (int d = 0; d < 5; d++) {
            if (id == st[j].cid[d]) {
                printf("\n\nThe Students Details are:\n\n");
                printf("The First name is %s\n", st[j].fname);
                printf("The Last name is %s\n", st[j].lname);
                printf("The Roll Number is %d\n", st[j].roll);
                printf("The CGPA is %f\n", st[j].cgpa);
                c = 1;
                break;
            }
        }
    }

    if (c == 0) {
        printf("Course ID not Found\n");
    }
}

void tot_s() {
    printf("-------------------------\n");

    printf("\nThe total number of Students is %d\n", i);
    printf("You can have a max of 50 students\n");
    printf("You can have %d more students\n", 50 - i);
}

void del_s() {
    int a;
    printf("\nEnter the Roll Number to delete\n");
    scanf("%d", &a);

    for (int j = 0; j < i; j++) {
        if (a == st[j].roll) {
            for (int k = j; k < 49; k++) {
                st[k] = st[k + 1];
            }
            i--;
            printf("Roll Number removed Successfully\n");
            return;
        }
    }

    printf("Roll Number not Found\n");
}

void up_s() {
    printf("\nEnter the Roll Number to update the entry: ");
    int x;
    scanf("%d", &x);

    printf("-------------------------\n");

    for (int j = 0; j < i; j++) {
        if (st[j].roll == x) {
            printf("1. first name\n2. last name\n3. roll no.\n4. CGPA\n5. courses\n");
            int z;
            scanf("%d", &z);

            switch (z) {
                case 1:
                    printf("Enter the new first name: ");
                    scanf("%s", st[j].fname);
                    break;
                case 2:
                    printf("Enter the new last name: ");
                    scanf("%s", st[j].lname);
                    break;
                case 3:
                    printf("Enter the new roll number: ");
                    scanf("%d", &st[j].roll);
                    break;
                case 4:
                    printf("Enter the new CGPA: ");
                    scanf("%f", &st[j].cgpa);
                    break;
                case 5:
                    printf("Enter the new courses: ");
                    scanf("%d %d %d %d %d", &st[j].cid[0], &st[j].cid[1], &st[j].cid[2], &st[j].cid[3], &st[j].cid[4]);
                    break;
            }

            printf("UPDATED SUCCESSFULLY.\n");
            return;
        }
    }

    printf("Roll Number not Found\n");
}

int main() {
    int choice;
    printf("\033[0;32m");
    printf("-------------------------------------------welcome to SIMS project--------------------------------------------------\n\n\n");
    printf("\033[0m");

     // Load existing data from file
    load_from_file();


    while (1) {
        printf("\033[0;31m");
        printf("\t\t\t\t\tThe Task that you want to perform\n");
        printf("\t\t\t\t\t1. Add the Student Details\n");
        printf("\t\t\t\t\t2. Find the Student Details by Roll Number\n");
        printf("\t\t\t\t\t3. Find the Student Details by First Name\n");
        printf("\t\t\t\t\t4. Find the Student Details by Course ID\n");
        printf("\t\t\t\t\t5. Find the Total number of Students\n");
        printf("\t\t\t\t\t6. Delete the Students Details by Roll Number\n");
        printf("\t\t\t\t\t7. Update the Students Details by Roll Number\n");
        printf("\t\t\t\t\t8. To Exit\n");
        printf("\033[0m");

        printf("\n\nEnter your choice to find the task\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                find_rl();
                break;
            case 3:
                find_fn();
                break;
            case 4:
                find_c();
                break;
            case 5:
                tot_s();
                break;
            case 6:
                del_s();
                break;
           case 7:
                up_s();
                break;

            case 8:
                save_to_file(); // Save data before exiting
                exit(0);
                break;


        }

    }
}
