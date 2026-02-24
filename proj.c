#include <stdio.h>
#include <string.h>

// Color Macros
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

struct Room {
    int roomNumber;
    char type[20];
    float pricePerDay;
    int isBooked;
    char customerName[50];
    char phone[15];
    int days;
    float totalBill;
};

int main() {

    const int totalRooms = 5;
    struct Room rooms[5];
    int i, choice;

    // Initialize Rooms
    for (i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = 0;

        if (i < 2) {
            strcpy(rooms[i].type, "Standard");
            rooms[i].pricePerDay = 1000;
        } else if (i < 4) {
            strcpy(rooms[i].type, "Deluxe");
            rooms[i].pricePerDay = 2000;
        } else {
            strcpy(rooms[i].type, "Suite");
            rooms[i].pricePerDay = 3000;
        }
    }

    do {
        printf(CYAN "\n====== HOTEL MANAGEMENT SYSTEM ======\n" RESET);
        printf(YELLOW "1. View All Rooms\n");
        printf("2. Book a Room\n");
        printf("3. Cancel Booking\n");
        printf("4. Search Booking\n");
        printf("5. Exit\n" RESET);
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

        case 1:
            printf(BLUE "\nRoom Details:\n" RESET);
            for (i = 0; i < totalRooms; i++) {
                printf("Room %d | Type: %s | Price: %.2f | Status: ",
                       rooms[i].roomNumber,
                       rooms[i].type,
                       rooms[i].pricePerDay);

                if (rooms[i].isBooked)
                    printf(RED "Booked\n" RESET);
                else
                    printf(GREEN "Available\n" RESET);
            }
            break;

        case 2: {
            int roomNo;
            printf("Enter Room Number to Book: ");
            scanf("%d", &roomNo);

            if (roomNo < 1 || roomNo > totalRooms) {
                printf(RED "Invalid Room Number!\n" RESET);
            }
            else if (rooms[roomNo - 1].isBooked) {
                printf(RED "Room Already Booked!\n" RESET);
            }
            else {
                printf("Enter Customer Name: ");
                scanf(" %[^\n]", rooms[roomNo - 1].customerName);

                printf("Enter Phone Number: ");
                scanf("%s", rooms[roomNo - 1].phone);

                printf("Enter Number of Days: ");
                scanf("%d", &rooms[roomNo - 1].days);

                rooms[roomNo - 1].totalBill =
                    rooms[roomNo - 1].days * rooms[roomNo - 1].pricePerDay;

                rooms[roomNo - 1].isBooked = 1;

                printf(GREEN "\nBooking Successful!\n" RESET);
                printf(CYAN "Total Bill: %.2f\n" RESET,
                       rooms[roomNo - 1].totalBill);
            }
            break;
        }

        case 3: {
            int roomNo;
            printf("Enter Room Number to Cancel: ");
            scanf("%d", &roomNo);

            if (roomNo < 1 || roomNo > totalRooms) {
                printf(RED "Invalid Room Number!\n" RESET);
            }
            else if (!rooms[roomNo - 1].isBooked) {
                printf(RED "Room is Not Booked!\n" RESET);
            }
            else {
                rooms[roomNo - 1].isBooked = 0;
                printf(GREEN "Booking Cancelled Successfully!\n" RESET);
            }
            break;
        }

        case 4: {
            char name[50];
            int found = 0;

            printf("Enter Customer Name to Search: ");
            scanf(" %[^\n]", name);

            for (i = 0; i < totalRooms; i++) {
                if (rooms[i].isBooked &&
                    strcmp(rooms[i].customerName, name) == 0) {

                    printf(GREEN "\nBooking Found!\n" RESET);
                    printf("Room: %d\n", rooms[i].roomNumber);
                    printf("Type: %s\n", rooms[i].type);
                    printf("Phone: %s\n", rooms[i].phone);
                    printf("Days: %d\n", rooms[i].days);
                    printf(CYAN "Total Bill: %.2f\n" RESET,
                           rooms[i].totalBill);
                    found = 1;
                }
            }

            if (!found)
                printf(RED "No Booking Found!\n" RESET);

            break;
        }

        case 5:
            printf(GREEN "Thank You!\n" RESET);
            break;

        default:
            printf(RED "Invalid Choice!\n" RESET);
        }

    } while (choice != 5);

    return 0;
}