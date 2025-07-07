#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FILE_NAME "information.dat"

// Define the contact structure
typedef struct {
    char name[100];
    char phone[20];
    char email[100];
} contacts;

// Function to add a new contact to the file
int add_contact(){
    FILE *fp = fopen(FILE_NAME, "ab");  // Open file in append binary mode
    if (!fp){
        perror("Failed to open the file");
        return 1;
    }

    contacts c;

    // Input contact details
    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", c.phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", c.email);

    // Write the contact to the file
    fwrite(&c, sizeof(contacts), 1, fp);
    fclose(fp);

    printf("✅ Contact added.\n");
    return 0;
}

// Function to view all contacts from the file
int view_contact(){
    FILE *fp = fopen(FILE_NAME, "rb");  // Open file in read binary mode
    if (!fp){
        perror("Failed to open the file");
        return 1;
    }

    contacts c;
    int i = 1;

    printf("\n📒 THE CONTACT DETAILS:\n");
    // Read and print each contact
    while (fread(&c, sizeof(c), 1, fp)){
        printf("[%d] %s | %s | %s\n", i++, c.name, c.phone, c.email);
    }

    fclose(fp);
    return 0;
}

// Function to search for a contact by name
int search_contact(){
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp){
        perror("Failed to open the file");
        return 1;
    }

    contacts c;
    int found = 0;
    char se_name[100];

    // Input name to search
    printf("\nEnter the name you want to search: ");
    scanf(" %[^\n]", se_name);
    getchar();

    // Search and print matching contacts
    while (fread(&c, sizeof(contacts), 1, fp)){
        if (strcmp(c.name, se_name) == 0){
            printf("\nFOUND: %s | %s | %s\n", c.name, c.phone, c.email);
            found = 1;
        }
    }

    if (!found){
        printf("\n❌ Entry not found in the record.\n");
    }

    fclose(fp);
    return 0;
}

// Function to delete a contact by name
int delete_contact(){
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *fm = fopen("temp.dat", "wb");  // Temp file for storing valid contacts

    if (!fp || !fm) {
        perror("Error opening files");
        return 1;
    }

    contacts c;
    int found = 0;
    char del_name[100];

    // Input name to delete
    printf("\nEnter the name to be deleted: ");
    scanf(" %[^\n]", del_name);
    getchar();

    // Copy all contacts except the one to be deleted
    while (fread(&c, sizeof(contacts), 1, fp)){
        if (strcmp(c.name, del_name) == 0){
            found = 1;
            continue; // Skip the contact to delete
        }
        fwrite(&c, sizeof(contacts), 1, fm);  // Write others to temp
    }

    fclose(fp);
    fclose(fm);

    if (!found){
        printf("\n❌ Contact not found.\n");
    } else {
        printf("\n✅ Contact deleted successfully.\n");
        remove(FILE_NAME);               // Delete old file
        rename("temp.dat", FILE_NAME);   // Rename temp file
    }

    return 0;
}

// Main menu-driven function
int main(){
    int choice;

    do {
        // Print menu options
        printf("\n========== 📞 CONTACT BOOK ==========\n");
        printf("[1] ➕ Add Contact\n");
        printf("[2] 📄 View Contacts\n");
        printf("[3] 🔍 Search by Name\n");
        printf("[4] 🗑️  Delete Contact by Name\n");
        printf("[5] 🚪 Exit\n");
        printf("=====================================\n");
        printf("\033[1;32m[✓] Success!\n"); 
        printf("Enter your choice:\033[0m ");
        
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        // Handle user choice
        switch(choice){
            case 1: add_contact(); break;
            case 2: view_contact(); break;
            case 3: search_contact(); break;
            case 4: delete_contact(); break;
            case 5: printf("\n👋 Logging out... Goodbye!\n"); break;
            default: printf("\n❌ Invalid choice. Try again.\n"); break;
        }
    }
    while(choice != 5);

    return 0;
}
