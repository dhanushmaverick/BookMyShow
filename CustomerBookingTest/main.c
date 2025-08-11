/* main data display
to display the intilal menu*/

#include "main.h"

int main()
{
    int choice;
    Booking_tickets booking_tickets;
    //booking_tickets.movies_count = 0;
    printf("in main\n");
    initialize(&booking_tickets); // Initializing the file to load
    // for(int i = 0; i < MAX_MOVIES; i++)
    // {
    //     booking_tickets.booking_movie[i].price = 0.0;
    // }
    printf("At intilize\n");
    //bool adminMain() ->
    //bool customerMain() //secret input value 
    do
    {
        printf("\n----------Admin Menu----------\n");
        printf("1. Create Movie\n");
        printf("2. Edit Movie\n");
        printf("3. Delete Movie\n");
        printf("4. List all Movies\n");
        printf("5. Exit Program\n"); //return false
        printf("6. Exit to Customer Version\n"); //return true
        printf("Enter your choice: ");//entering the choice
        scanf("%d", &choice);//reading the choice from the user

        switch (choice) {
            case 1:
            create_movie(&booking_tickets);
            break;
            case 2:
            edit_movie(&booking_tickets);//edit
            break;
            case 3:
            delete_movie(&booking_tickets);//delete movie
            break;
            case 4:
            list_movie(&booking_tickets);//list movies
            break;
            case 5:
            printf("Saving and Exiting...\n");
            printf("You Got exited\n");
            save_movie(&booking_tickets);
            break;
            default:
            printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 5);
    return 0;
}