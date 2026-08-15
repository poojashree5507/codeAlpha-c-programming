#include <stdio.h>

int main() {
    int choice;
    float a, b, result;

    do {
        printf("\n==============================");
        printf("\n       SIMPLE CALCULATOR");
        printf("\n==============================");
        printf("\n1. ADDITION");
        printf("\n2. SUBTRACTION");
        printf("\n3. MULTIPLICATION");
        printf("\n4. DIVISION");
        printf("\n5. EXIT");
        printf("\n==============================");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("\n----- ADDITION -----");
                printf("\nEnter two numbers: ");
                scanf("%f %f", &a, &b);

                result = a + b;
                printf("Addition = %.2f", result);
                break;

            case 2:
                printf("\n----- SUBTRACTION -----");
                printf("\nEnter two numbers: ");
                scanf("%f %f", &a, &b);

                result = a - b;
                printf("Subtraction = %.2f", result);
                break;

            case 3:
                printf("\n----- MULTIPLICATION -----");
                printf("\nEnter two numbers: ");
                scanf("%f %f", &a, &b);

                result = a * b;
                printf("Multiplication = %.2f", result);
                break;

            case 4:
                printf("\n----- DIVISION -----");
                printf("\nEnter two numbers: ");
                scanf("%f %f", &a, &b);

                if (b != 0) {
                    result = a / b;
                    printf("Division = %.2f", result);
                }
                else {
                    printf("Cannot divide by zero!");
                }
                break;

            case 5:
                printf("\nThank you!");
                break;

            default:
                printf("\nInvalid choice!");
        }

    } while(choice != 5);

    return 0;
}
