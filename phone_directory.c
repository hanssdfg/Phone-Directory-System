#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

// Structure for Contact Node
typedef struct Contact {
    char name[50];
    char phone[15];
    struct Contact *left, *right;
} Contact;

// Function to create a new contact node
Contact* createContact(char name[], char phone[]) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (!newContact) {
        printf(RED "Memory allocation failed!\n" RESET);
        exit(1);
    }
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->left = newContact->right = NULL;
    return newContact;
}

// Insert contact into BST
Contact* insertContact(Contact* root, char name[], char phone[]) {
    if (root == NULL) return createContact(name, phone);
    if (strcmp(name, root->name) < 0)
        root->left = insertContact(root->left, name, phone);
    else if (strcmp(name, root->name) > 0)
        root->right = insertContact(root->right, name, phone);
    return root;
}

// Search for a contact
Contact* searchContact(Contact* root, char name[]) {
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;
    if (strcmp(name, root->name) < 0)
        return searchContact(root->left, name);
    return searchContact(root->right, name);
}

// Find minimum value node in BST (used for deletion)
Contact* minValueNode(Contact* node) {
    Contact* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete a contact
Contact* deleteContact(Contact* root, char name[]) {
    if (root == NULL) return root;
    if (strcmp(name, root->name) < 0)
        root->left = deleteContact(root->left, name);
    else if (strcmp(name, root->name) > 0)
        root->right = deleteContact(root->right, name);
    else {
        if (root->left == NULL) {
            Contact* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Contact* temp = root->left;
            free(root);
            return temp;
        }
        Contact* temp = minValueNode(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);
        root->right = deleteContact(root->right, temp->name);
    }
    return root;
}

// Update a contact
void updateContact(Contact* root, char name[], char newPhone[]) {
    Contact* contact = searchContact(root, name);
    if (contact != NULL) {
        strcpy(contact->phone, newPhone);
        printf(GREEN "Contact updated successfully!\n" RESET);
    } else {
        printf(RED "Contact not found!\n" RESET);
    }
}

// Display contacts in alphabetical order
void displayContacts(Contact* root) {
    if (root != NULL) {
        displayContacts(root->left);
        printf(YELLOW "Name: %s, Phone: %s\n" RESET, root->name, root->phone);
        displayContacts(root->right);
    }
}

// Driver program
int main() {
    Contact* root = NULL;
    int choice;
    char name[50], phone[15];
    while (1) {
        printf(BLUE "\nPhone Directory System:\n" RESET);
        printf("1. Add Contact\n2. Search Contact\n3. Update Contact\n4. Delete Contact\n5. Display Contacts\n6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer
        switch (choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter phone: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0;
                root = insertContact(root, name, phone);
                printf(GREEN "Contact added successfully!\n" RESET);
                break;
            case 2:
                printf("Enter name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                Contact* found = searchContact(root, name);
                if (found)
                    printf(GREEN "Found - Name: %s, Phone: %s\n" RESET, found->name, found->phone);
                else
                    printf(RED "Contact not found!\n" RESET);
                break;
            case 3:
                printf("Enter name to update: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter new phone number: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0;
                updateContact(root, name, phone);
                break;
            case 4:
                printf("Enter name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                root = deleteContact(root, name);
                printf(GREEN "Contact deleted successfully!\n" RESET);
                break;
            case 5:
                printf(BLUE "\nPhone Directory:\n" RESET);
                displayContacts(root);
                break;
            case 6:
                printf(GREEN "Exiting...\n" RESET);
                exit(0);
            default:
                printf(RED "Invalid choice! Try again.\n" RESET);
        }
    }
    return 0;
}

