#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define YOUR_SPECIAL_USER_ID 12345
#define SPECIAL_DISCOUNT_RATE 20

typedef struct {
    char item[100];
    int price;
} MenuItem;

typedef struct {
    int userId;
    int visitCount;
} User;

void displayMenu(MenuItem menu[], int numItems) {
    printf("Menu:\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d. %s  Price: RS = %d\n", i + 1, menu[i].item, menu[i].price);
    }
}

int calculateDiscount(int count) {
    if (count >= 2) {
        if (YOUR_SPECIAL_USER_ID != -1) {
            // Apply special discount rate for specific user
            return SPECIAL_DISCOUNT_RATE;
        }
        return 20;
    }
    return 0;
}

int validateIntegerInput(int min, int max, const char* message) {
    int choice;
    char input[100];
    while (1) {
        if (scanf("%d", &choice) != 1 || choice < min || choice > max) {
            printf("Invalid input. %s", message);
            fgets(input, sizeof(input), stdin);  // Clear the input buffer
        } else {
            break;
        }
    }
    return choice;
}

bool wantsToContinue() {
    char input[100];
    printf("\nDo you want to continue? (y/n): ");
    fgets(input, sizeof(input), stdin);
    char continueProgram = input[0];
    while (continueProgram != 'y' && continueProgram != 'Y' && continueProgram != 'n' && continueProgram != 'N') {
        printf("Invalid input. Please enter 'y' or 'n': ");
        fgets(input, sizeof(input), stdin);
        continueProgram = input[0];
    }
    return (continueProgram == 'y' || continueProgram == 'Y');
}

User* findUser(User userList[], int numUsers, int userId) {
    for (int i = 0; i < numUsers; i++) {
        if (userList[i].userId == userId) {
            return &userList[i];
        }
    }
    return NULL;
}

void registerUser(User userList[], int numUsers, int userId) {
    User newUser;
    newUser.userId = userId;
    newUser.visitCount = 0;
    userList[numUsers] = newUser;
}

int main() {
    MenuItem menu1[2] = {
        {"Cup", 5},
        {"Cone", 10}
    };

    MenuItem menu2[5] = {
        {"Chocolate Flavor", 140},
        {"Strawberry Flavor", 120},
        {"Vanilla Flavor", 100},
        {"Coffee Flavor", 120},
        {"Chocolate Chip Flavor", 160}
    };

    MenuItem menu3[6] = {
        {"Caramel Sauce Flavor Topping", 60},
        {"Chocolate Sauce Flavor Topping", 50},
        {"Strawberry Sauce Flavor Topping", 50},
        {"Sprinkles Flavor Topping", 60},
        {"Crushed Oreo Cookies Flavor Topping", 80},
        {"Without Topping", 0}
    };

    int numItems1 = sizeof(menu1) / sizeof(menu1[0]);
    int numItems2 = sizeof(menu2) / sizeof(menu2[0]);
    int numItems3 = sizeof(menu3) / sizeof(menu3[0]);

    int numUsers = 0;
    User userList[100];

    int quantity, choice1, choice2, choice3;
    char continueProgram;
    do {
        // User Registration
        int userId;
        printf("Enter User ID: ");
        scanf("%d", &userId);
        User* currentUser = findUser(userList, numUsers, userId);
        if (currentUser == NULL) {
            registerUser(userList, numUsers, userId);
            currentUser = &userList[numUsers];
            numUsers++;
        }
        currentUser->visitCount++;

        // First Menu: Cup or Cone
        printf("<===== W E L C O M E  T0  I C E - C R E A M =====>\n");
        printf("CONE OR CUP:\n");
        displayMenu(menu1, numItems1);
        printf("YOUR CHOICE (1-%d): ", numItems1);
        choice1 = validateIntegerInput(1, numItems1, "Please enter a valid Item Number: ");
        printf("\n");

        // Second Menu: Ice Cream Flavor
        printf("F L A V O U R:\n");
        displayMenu(menu2, numItems2);
        printf("YOUR CHOICE (1-%d): ", numItems2);
        choice2 = validateIntegerInput(1, numItems2, "Please enter a valid Item Number: ");
        printf("\n");

        // Third Menu: Ice Cream Flavor Topping
        printf("T O P P I N G:\n");
        displayMenu(menu3, numItems3);
        printf("YOUR CHOICE (1-%d): ", numItems3);
        choice3 = validateIntegerInput(1, numItems3, "Please enter a valid Item Number: ");
        printf("\n");

        printf("ENTER QUANTITY: ");
        quantity = validateIntegerInput(1, INT_MAX, "Please enter a valid quantity: ");

        MenuItem selected1 = menu1[choice1 - 1];
        MenuItem selected2 = menu2[choice2 - 1];
        MenuItem selected3 = menu3[choice3 - 1];

        printf("\n--- Selected Items ---\n");
        printf("CATEGORY: %s  Price: RS = %d\n", selected1.item, selected1.price);
        printf("FLAVOR: %s  Price: RS = %d\n", selected2.item, selected2.price);
        printf("TOPPING: %s  Price: RS = %d\n", selected3.item, selected3.price);
        printf("Quantity: %d %s", quantity, "item \n");

        int totalPrice = (selected1.price + selected2.price + selected3.price) * quantity;
        int discount = calculateDiscount(currentUser->visitCount);
        int discountedPrice = totalPrice - (totalPrice * discount / 100);

        printf("Total Price: RS = %d\n", totalPrice);
        if (discount > 0) {
            printf("Discount: %d%%\n", discount);
            if (currentUser->userId == YOUR_SPECIAL_USER_ID) {
                // Apply special discount for specific user
                discountedPrice = discountedPrice - (totalPrice * SPECIAL_DISCOUNT_RATE / 100);
            }
            printf("Discounted Price: RS = %d\n", discountedPrice);
        }

        if (!wantsToContinue()) {
            break;
        }

        printf("\n");
    } while (1);

    printf("Thank you for visiting the Ice Cream Parlor!\n");

    return 0;
}