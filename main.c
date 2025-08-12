/* main data display
to display the intilal menu*/


#include "admin_main.h"
#include "customer_main.h"

int main()
{
    
    Booking_tickets booking_tickets;
    User users;
    //booking_tickets.movies_count = 0;
    
    initialize(&booking_tickets); // Initializing the file to load at the start
    initialize_users_start(&users);
    
    bool status = false;
    int choice;
    printf("---------------Main Menu---------------\n");
    printf("1.Admin\n2.Customer\n3.Exit\nEnter your Choice: ");
    scanf("%d", &choice);
    switch(choice) 
    {
        case 1:
        printf("You Accessed As Admin\n");
        do
        {
            status = admin(&booking_tickets, &users);
            if(status != 1)
            return 0;
            else
            status = customer_main(&booking_tickets);
            if(!status)
            return 0;
        } while (status != 1);
        break;

        case 2:
        do
        {
            status = customer_main(&booking_tickets);
            if(status != 1)
            return 0;
            else
            status = admin(&booking_tickets, &users);
            if(!status)
            return 0;
        } while (status != 1);
        break;
        break;
        case 3: 
        exit(EXIT_SUCCESS);
        break;
        default:
        printf("Invalid choice. Please try again.\n");

    }

    
    
    //bool customer_main() //secret input value 
    
    return 0;
}