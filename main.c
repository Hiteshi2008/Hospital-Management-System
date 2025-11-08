#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- Structure for Patient ----------------
struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
};

// ---------------- Structure for Doctor ----------------
struct Doctor {
    int id;
    char name[50];
    char specialization[50];
};

// ---------------- Function Declarations ----------------
void addPatient();
void viewPatients();
void addDoctor();
void viewDoctors();
void generateBill();
void searchPatient();
int login();

// ---------------- Files ----------------
#define PATIENT_FILE "patients.txt"
#define DOCTOR_FILE "doctors.txt"

// ---------------- LOGIN SYSTEM ----------------
int login() {
    char username[30], password[30];
    char fileUser[30], filePass[30];
    int success = 0;

    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("\nError: users.txt file not found! Creating default admin account...\n");
        fp = fopen("users.txt", "w");
        fprintf(fp, "admin admin123\n");
        fclose(fp);
        fp = fopen("users.txt", "r");
    }

    printf("\n=== LOGIN SYSTEM ===\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            success = 1;
            break;
        }
    }

    fclose(fp);

    if (success) {
        printf("\n✅ Login successful! Welcome, %s.\n\n", username);
        return 1;
    } else {
        printf("\n❌ Invalid username or password!\n");
        return 0;
    }
}

// ---------------- Add Patient ----------------
void addPatient() {
    struct Patient p;
    FILE *fp = fopen(PATIENT_FILE, "a");

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf("%s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender: ");
    scanf("%s", p.gender);
    printf("Enter Disease: ");
    scanf("%s", p.disease);

    fprintf(fp, "%d,%s,%d,%s,%s\n", p.id, p.name, p.age, p.gender, p.disease);
    fclose(fp);

    printf("\nPatient record added successfully!\n");
}

// ---------------- View Patients ----------------
void viewPatients() {
    struct Patient p;
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (fp == NULL) {
        printf("\nNo patient records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");
    printf("ID\tName\tAge\tGender\tDisease\n");
    printf("---------------------------------------------\n");

    while (fscanf(fp, "%d,%[^,],%d,%[^,],%[^\n]\n",
                  &p.id, p.name, &p.age, p.gender, p.disease) != EOF) {
        printf("%d\t%s\t%d\t%s\t%s\n", p.id, p.name, p.age, p.gender, p.disease);
    }

    fclose(fp);
}

// ---------------- Add Doctor ----------------
void addDoctor() {
    struct Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "a");

    printf("\nEnter Doctor ID: ");
    scanf("%d", &d.id);
    printf("Enter Name: ");
    scanf("%s", d.name);
    printf("Enter Specialization: ");
    scanf("%s", d.specialization);

    fprintf(fp, "%d,%s,%s\n", d.id, d.name, d.specialization);
    fclose(fp);

    printf("\nDoctor record added successfully!\n");
}

// ---------------- View Doctors ----------------
void viewDoctors() {
    struct Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "r");
    if (fp == NULL) {
        printf("\nNo doctor records found!\n");
        return;
    }

    printf("\n--- Doctor Records ---\n");
    printf("ID\tName\tSpecialization\n");
    printf("---------------------------------------------\n");

    while (fscanf(fp, "%d,%[^,],%[^\n]\n", &d.id, d.name, d.specialization) != EOF) {
        printf("%d\t%s\t%s\n", d.id, d.name, d.specialization);
    }

    fclose(fp);
}

// ---------------- Search Patient ----------------
void searchPatient() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (fp == NULL) {
        printf("\nNo patient records found!\n");
        return;
    }

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%[^,],%d,%[^,],%[^\n]\n",
                  &p.id, p.name, &p.age, p.gender, p.disease) != EOF) {
        if (p.id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d | Name: %s | Age: %d | Gender: %s | Disease: %s\n",
                   p.id, p.name, p.age, p.gender, p.disease);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nPatient not found!\n");

    fclose(fp);
}

// ---------------- Generate Bill ----------------
void generateBill() {
    int pid, found = 0;
    float fee;
    struct Patient p;
    FILE *fp = fopen(PATIENT_FILE, "r");

    if (fp == NULL) {
        printf("\nNo patient records found!\n");
        return;
    }

    printf("\nEnter Patient ID for billing: ");
    scanf("%d", &pid);

    while (fscanf(fp, "%d,%[^,],%d,%[^,],%[^\n]\n",
                  &p.id, p.name, &p.age, p.gender, p.disease) != EOF) {
        if (p.id == pid) {
            printf("\nEnter Consultation Fee: ");
            scanf("%f", &fee);
            printf("\n--- BILL ---\n");
            printf("Patient Name: %s\n", p.name);
            printf("Consultation Fee: %.2f\n", fee);
            printf("GST (5%%): %.2f\n", fee * 0.05);
            printf("Total: %.2f\n", fee * 1.05);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nPatient ID not found!\n");

    fclose(fp);
}

// ---------------- MAIN ----------------
int main() {
    int choice;

    if (!login()) {
        printf("\nAccess Denied. Exiting...\n");
        return 0;
    }

    do {
        printf("\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient Record\n");
        printf("2. View Patients\n");
        printf("3. Add Doctor Record\n");
        printf("4. View Doctors\n");
        printf("5. Search Patient by ID\n");
        printf("6. Generate Bill\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: addDoctor(); break;
            case 4: viewDoctors(); break;
            case 5: searchPatient(); break;
            case 6: generateBill(); break;
            case 7: printf("\nExiting program... Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
