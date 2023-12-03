#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Date {
    int day, month, year;
};

struct Doctor {
    char name[50];
    char specialization[50];
};

struct Patient {
    char name[100];
    int age;
    char gender;
    char contact[100];
    struct Date admissionDate;
    int isdischarge;
    struct Doctor assignedDoctor;
    int patientID;
};

struct Patient patients[100];
struct Doctor doctors[10];

int patientCount = 0;
int doctorCount = 0;

void registerPatient();
void displayPatients();
void searchPatients();
void addDoctor();
void assignDoctor();
void displayDoctorPatientAssociation();

int main() {
    while (1) {
        int value;

        printf("\nHospital Management System Menu\n");
        printf("1. Register Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patients\n");
        printf("4. Add Doctor\n");
        printf("5. Assign Doctor\n");
        printf("6. Display Doctor-Patient Association\n");
        printf("0. Exit the program\n");
        printf("Enter your choice: ");
        scanf("%d", &value);

        switch (value) {
            case 1:
                registerPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                searchPatients();
                break;
            case 4:
                addDoctor();
                break;
            case 5:
                assignDoctor();
                break;
            case 6:
                displayDoctorPatientAssociation();
                break;
            case 0:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Error! Wrong Input.\n");
                break;
        }
    }

    return 0;
}

void registerPatient() {
    FILE *file;
    file = fopen("file.txt", "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("Enter patient name: ");
    scanf("%s", patients[patientCount].name);
    fprintf(file, "Name: %s\n", patients[patientCount].name);

    printf("Enter patient age: ");
    scanf("%d", &patients[patientCount].age);
    fprintf(file, "Age: %d\n", patients[patientCount].age);

    printf("Enter patient gender (M/F): ");
    scanf(" %c", &patients[patientCount].gender);
    fprintf(file, "Gender: %c\n", patients[patientCount].gender);

    printf("Enter contact information: ");
    scanf("%s", patients[patientCount].contact);
    fprintf(file, "Contact: %s\n", patients[patientCount].contact);

    printf("Is the patient an discharge? (0 for admit, 1 for discharge): ");
    scanf("%d", &patients[patientCount].isdischarge);
    fprintf(file, "Is discharge: %d\n", patients[patientCount].isdischarge);

    if (!patients[patientCount].isdischarge) {
        // Validate the admission date
        bool validDate = false;
        while (!validDate) {
            printf("Enter Admission Date (day/month/year): ");
            scanf("%d/%d/%d", &patients[patientCount].admissionDate.day,
                  &patients[patientCount].admissionDate.month, &patients[patientCount].admissionDate.year);
            validDate = (patients[patientCount].admissionDate.day > 0 && patients[patientCount].admissionDate.day < 32) &&
                        (patients[patientCount].admissionDate.month > 0 && patients[patientCount].admissionDate.month < 13);
            if (!validDate) {
                printf("Invalid dates. Please enter again.\n");
            }
        }
        fprintf(file, "Admission Date: %d/%d/%d\n", patients[patientCount].admissionDate.day,
                patients[patientCount].admissionDate.month, patients[patientCount].admissionDate.year);
    }

    patientCount++;
    fprintf(file, "\n");
    fclose(file);

    printf("Patient registered successfully.\n");
}

void displayPatients() {
    FILE *file;
    file = fopen("file.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("\nList of Patients\n");
    printf("Name\t\tAge\t\tGender\t\tContact\t\t\tAdmission Date\n");

    char line[100];
    int lineNumber = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            lineNumber = 1; 
            printf("\n") ;
            continue;
        }
    
        switch (lineNumber) {
            case 1:  // Name
                for(int i = 6;line[i] != '\n';i++)printf("%c" , line[i]);
                printf("\t\t");
                break;
            case 2:
                for(int i = 5;line[i] != '\n';i++)printf("%c" , line[i]);
                printf("\t\t");
                break;
            case 3:
                for(int i = 8;line[i] != '\n';i++)printf("%c" , line[i]);
                printf("\t\t");
                break;
            case 4:
                for(int i = 9;line[i] != '\n';i++)printf("%c" , line[i]);
                printf("");
                break;
            case 5:
               for(int i = 15;line[i] != '\n';i++)printf("%c" , line[i]);
                printf("\t\t");
                break;
            case 6:
                for(int i = 15;line[i] != '\n';i++)printf("%c" , line[i]);
                printf("\t\t");
                break;
        }

        lineNumber++;
    }

    fclose(file);
}

void searchPatients() {
    char Name[50];
    printf("\nEnter patient name to search: ");
    scanf("%s", Name);

    int found = 0;
    printf("\nSearch Results\n");
    printf("ID\tName\t\tAge\tGender\tContact\t\tAdmission Date\n");
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(Name, patients[i].name) == 0) {
            printf("%d\t%s\t\t%d\t%c\t%s\t%d/%d/%d\n", i + 1, patients[i].name, patients[i].age,
                   patients[i].gender, patients[i].contact, patients[i].admissionDate.day,
                   patients[i].admissionDate.month, patients[i].admissionDate.year);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching patient found.\n");
    }
}

void assignDoctor() {
    displayPatients();
    int patientID;
    char Name[100];
    printf("\nEnter patient name to assign a doctor: ");
    scanf("%s", Name);
    int f = 0;
        for (int i = 0; i < patientCount; i++) {
        if (strcmp(Name, patients[i].name) == 0) {
            f = i;
            break;
        }
        }
    if (patients[f].isdischarge == 0) {
        printf("\nAvailable Doctors\n");
        printf("ID\tName\tSpecialization\n");
        for (int i = 0; i < doctorCount; i++) {
            printf("%d\t%s\t%s\n", i + 1, doctors[i].name, doctors[i].specialization);
        }

        int doctorID;
        printf("\nEnter doctor ID to assign to the patient: ");
        scanf("%d", &doctorID);

        if (doctorID >= 1 && doctorID <= doctorCount) {
            patients[f].assignedDoctor = doctors[doctorID - 1];

            printf("Doctor assigned successfully.\n");
        } else {
            printf("Invalid doctor ID.\n");
        }
    } else {
        printf("Invalid patient ID or patient is an discharge.\n");
    }
}

void displayDoctorPatientAssociation() {
    printf("\nDoctor-Patient Association\n");
    printf("Patient Name\tAssigned Doctor\tSpecialization\n");
    for (int i = 0; i < patientCount; i++) {
        printf("%s\t        %s\t        %s\n", patients[i].name, patients[i].assignedDoctor.name,
               patients[i].assignedDoctor.specialization);
    }
}

void addDoctor() {
    printf("Enter the name of Doctor: ");
    scanf("%s", doctors[doctorCount].name);
    printf("Enter the specialization of doctor: ");
    scanf("%s", doctors[doctorCount].specialization);

    doctorCount++;
    printf("Doctor registered successfully.\n");
}