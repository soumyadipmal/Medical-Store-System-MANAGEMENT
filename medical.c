#include <stdio.h>
#include <string.h>
#define MAX 100

struct med {
    int id;
    char name[50];
    char company[50];
    char mft[15];
    char exp[15];
    int avlble;
    float price;
};
struct med store[MAX];
int cnt = 0;
void save() {
    FILE *file = fopen("medicines.dat", "wb");
    if (file) {
        fwrite(&cnt, sizeof(int), 1, file);
        fwrite(store, sizeof(struct med), cnt, file);
        fclose(file);
    }
}
void load() {
    FILE *file = fopen("medicines.dat", "rb");
    if (file) {
        fread(&cnt, sizeof(int), 1, file);
        fread(store, sizeof(struct med), cnt, file);
        fclose(file);
    }
}
void add() {
    if (cnt >= MAX) {
        printf("\nStore is full\n");
        return;
    }
    store[cnt].id = cnt + 1;
    printf("\nEnter the Medicine Name: ");
    scanf("%s", store[cnt].name);
    printf("Enter the Company Name: ");
    scanf("%s", store[cnt].company);
    printf("Enter Manufacturing Date (DD/MM/YYYY): ");
    scanf("%s", store[cnt].mft);
    printf("Enter Expiry Date (DD/MM/YYYY): ");
    scanf("%s", store[cnt].exp);
    printf("Enter Availability (1 for YES, 0 for NO): ");
    scanf("%d", &store[cnt].avlble);
    printf("Enter Price: ");
    scanf("%f", &store[cnt].price);
    cnt++;
    save();
    printf("\nMedicine added to stock\n");
}

void displayMedicines() {
    if (cnt == 0) {
        printf("\nNo medicines available\n");
        return;
    }
    printf("\nMedicine List:\n");
   printf("ID     \tNAME     \tCOMPANY        \tMFT. DATE  \tExp Date   \tAvailable  \tPRICE\n");
    for (int i = 0; i < cnt; i++) {
        printf("%d\t%s\t%s         \t%s  \t%s      \t%s        \t%.2f\n", store[i].id, store[i].name, store[i].company, store[i].mft, store[i].exp, store[i].avlble ? "Yes" : "No", store[i].price);
    }
}
void updateStock() {
    int id, found = 0;
    printf("\nEnter the medicine ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < cnt; i++) {
        if (store[i].id == id) {
            printf("Enter new availability (1 for YES, 0 for NO): ");
            scanf("%d", &store[i].avlble);
            printf("Enter new price: ");
            scanf("%f", &store[i].price);
            printf("Enter new Manufacturing Date: ");
            scanf("%s", store[i].mft);
            printf("Enter new Expiry Date: ");
            scanf("%s", store[i].exp);
            save();
            printf("\nStock, price, and dates updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nMedicine ID not found!\n");
    }
}

void removeMedicine() {
    int id, found = 0;
    printf("\nEnter the medicine ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < cnt; i++) {
        if (store[i].id == id) {
            found = 1;
            for (int j = i; j < cnt - 1; j++) {
                store[j] = store[j + 1];
                store[j].id = j + 1;
            }
            cnt--;
            save();
            printf("\nMedicine removed from stock\n");
            break;
        }
    }
    if (!found) {
        printf("\nMedicine ID not found\n");
    }
}
void check() {
    int id, found = 0;
    printf("\nEnter the medicine ID to check availability: ");
    scanf("%d", &id);
    for (int i = 0; i < cnt; i++) {
        if (store[i].id == id) {
            printf("\nMedicine %s is %s\n", store[i].name, store[i].avlble ? "Available" : "Not Available");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nMedicine ID not found!\n");
    }
}
int main() {
    load();
    int choice;
    do {
        printf("\nMedical Store Management System\n");
        printf("1. Add Medicine\n");
        printf("2. Display Medicines\n");
        printf("3. Update Stock, Price & Dates\n");
        printf("4. Remove Medicine\n");
        printf("5. Check Availability\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: add(); break;
            case 2: displayMedicines(); break;
            case 3: updateStock(); break;
            case 4: removeMedicine(); break;
            case 5: check(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}


