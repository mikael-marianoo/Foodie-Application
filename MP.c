#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_FOODS 50
#define MAX_NAME_LEN 50
#define MAX_LOC_LEN 30
#define MAX_DESC_LEN 300

// User struct
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

// Data structure for a food entry
struct FoodEntry {
    char name[MAX_NAME_LEN+1];
    char type;
    int timesEaten;
    char dateFirstTried[11];
    char locationFirstTried[MAX_LOC_LEN+1];
    char description[MAX_DESC_LEN+1];
};

int authenticate(User users[], int num_users, char *username, char *password) {
    // Check if the provided credentials match any of the stored usernames and passwords
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

struct FoodEntry foodLog[MAX_FOODS];
int numFoods = 0;

// Function to add a new food entry to the log
void addFood()
{
    if (numFoods >= MAX_FOODS)
    {
        printf("Error: food log is full\n");
        return;
    }

    struct FoodEntry newFood;

    // Get user input for new food entry
    printf("Enter food name: ");
    scanf(" %[^\n]", newFood.name);

    printf("Enter food type ('a' for appetizer, 'm' for main course, 'd' for dessert): ");
    scanf(" %c", &newFood.type);

    printf("Enter number of times eaten: ");
    scanf("%d", &newFood.timesEaten);

    printf("Enter date first tried (mm/dd/yyyy): ");
    scanf("%s", newFood.dateFirstTried);

    printf("Enter location first tried: ");
    scanf("%s", newFood.locationFirstTried);

    printf("Enter description: ");
    scanf(" %[^\n]", newFood.description);

    // Add new food entry to log and increment number of foods
    foodLog[numFoods] = newFood;
    numFoods++;

    printf("Food entry added to log.\n");
    getch();
    system("cls");
}

void deleteFood()
{
    char foodName[MAX_NAME_LEN+1];
    int indexToDelete = -1;

    if (numFoods == 0)
    {
        printf("Food log is empty.\n");
        return;
    }

    // Get the name of the food to delete from the user
    printf("Enter the name of the food to delete: ");
    scanf(" %[^\n]", foodName);

    // Find the index of the food in the log
    for (int i = 0; i < numFoods; i++)
    {
        if (strcmp(foodLog[i].name, foodName) == 0)
        {
            indexToDelete = i;
            break;
        }
    }

    // If the food is not found in the log, display an error message and return
    if (indexToDelete == -1)
    {
        printf("Error: food not found in log.\n");
        return;
    }

    // Shift all entries after the deleted entry back by one index
    for (int i = indexToDelete; i < numFoods-1; i++)
    {
        foodLog[i] = foodLog[i+1];
    }

    // Decrement the number of foods and display a success message
    numFoods--;
    printf("Food entry deleted from log.\n");
}

void deleteAllFoodLog() {
    // Prompt user to confirm deletion
    printf("Are you sure you want to delete the entire food log? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);

    // If user confirms deletion, reset the food log
    if (confirm == 'y' || confirm == 'Y')
    {
        numFoods = 0;
        printf("Food log deleted.\n");
    }
}

// Function to display all food entries in the log
void displayFoodLog()
{
    if (numFoods == 0)
    {
        printf("Food log is empty.\n");
        return;
    }

    // Sort foodLog by name using bubble sort algorithm
    for (int i = 0; i < numFoods - 1; i++)
    {
        for (int j = 0; j < numFoods - i - 1; j++)
        {
            if (strcmp(foodLog[j].name, foodLog[j+1].name) > 0)
            {
                struct FoodEntry temp = foodLog[j];
                foodLog[j] = foodLog[j+1];
                foodLog[j+1] = temp;
            }
        }
    }

    printf("Food Log:\n");
    printf("\n%-20s %-10s %-10s %-20s %-30s %-30s\n", "Name", "Type", "Times", "Date First Tried", "Location First Tried", "Description");
    for (int i = 0; i < numFoods; i++)
    {
        printf("%-20s %-10c %-10d %-20s %-30s %-30s\n\n", foodLog[i].name, foodLog[i].type, foodLog[i].timesEaten, foodLog[i].dateFirstTried, foodLog[i].locationFirstTried, foodLog[i].description);
    }
    
}

int main()
{
    int i, j, k = 0;
    int choice;
    int c;
    User users[MAX_USERS] = {
        {"Admin", "adM1n"},
        {"Client", "cL13nt"},
        {"Management", "M4nag3ment"},
        // Add more users here
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    char input_username[MAX_USERNAME_LEN];
    char input_password[MAX_PASSWORD_LEN];

    // Prompt user to enter username and password
    while (k != 3) {
        printf("Enter username: ");
        scanf("%s", input_username);
        printf("Enter password: ");

        i = 0;
        while (1) {
            int c = getch();
            //This part of code replaces the text input password into *
            if (c == '\r')
            {
                input_password[i] = '\0';
                break;
            }
            else if (c == '\b' && i > 0)
            {
                i--;
                printf("\b \b");
            } else if (i < 20 && c != '\b')
            {
                input_password[i++] = c;
                printf("*");
            }
        }

        //Check if the combination of input username and password provided matches with any of the username-password
        //stored  in the users array
        if (authenticate(users, num_users, input_username, input_password))
        {
            printf("\nWelcome, %s!\n", input_username);
            getch();
            system("cls");
            while (1)
            {
                // Print menu and get user choice
                printf("\nFood Log Menu:\n");
                printf("1. Add food entry\n");
                printf("2. Delete food log\n");
                printf("3. Display food entry\n");
                printf("4. Exit\n");
                printf("Enter your choice (1-3): ");
                scanf("%d", &choice);

                // Call corresponding function based on user choice
                switch (choice)
                {
                    case 1:
                        addFood();
                        break;
                    case 2:
                            printf("Would You Like to (1) Delete All or (2) Delete Specific Food?: ");
                            scanf("%d", &c);
                            switch(c)
                            {
                                case 1:
                                    deleteAllFoodLog();
                                    break;
                                case 2:
                                    deleteFood();
                                    break;
                                default:
                                    printf("Invalid choice.\n");
                                    break;
                            }

                        
                    case 3:
                        displayFoodLog();
                        break;
                    case 4:
                        printf("Exiting program...\n");
                        return 0;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
            }
        }
        else
        {
            printf("\nIncorrect username or password.\n");
            k++;
        }
    }
    
    printf("Too many attempts. Exiting program...\n");
    return 0;
}
