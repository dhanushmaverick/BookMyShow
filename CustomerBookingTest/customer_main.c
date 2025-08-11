#include "customer_main.h"

void initialize_user(User* user)
{
    strcpy(user->first_name_ ,"\0");
    strcpy(user->last_name_ ,"\0");
    strcpy(user->number_ ,"\0");
    strcpy(user->email_ ,"\0");
    strcpy(user->password_ ,"\0");
    user->isRegistered_ = false;
    for(int i = 0; i < MAX_TICKETS_; i++)
    user->tickets_[i].isBooked_ = false;
}

void initialize_user_reg(User* user, char* first_name, char* last_name, char* number, char* email, char* password)
{
    strcpy(user->first_name_ ,first_name);
    strcpy(user->last_name_ ,last_name);
    strcpy(user->number_,number);
    strcpy(user->email_,email);
    strcpy(user->password_, password);
    user->isRegistered_ = true;
}

void initialize_ticket(Ticket* ticket)
{
    static int count = 1;
    ticket->ID_ = count++;
    ticket->isBooked_ = false;
}

void initialize_seat(Seat* seat)
{
    static int count = 1;
    seat->number_ = count++;
    seat->isEmpty_ = true;
}

bool customer_main(Booking_tickets* booking_tickets)
{

    User user;
    initialize_user(&user);

    printf("-----Welcome to BookMyShow!-----\n");
    int choice = 0; 
    do
    {
        printf("Please choose an action below:\n");
        printf("1. User Login\n");
        printf("2. Register new User\n");
        printf("3. View Available Movies\n");
        printf("4. Book Tickets\n");
        printf("5. View Booked Tickets\n");
        printf("6. Exit Program\n"); //return false
       // printf("6. Exit to Admin Version\n"); //return true //make secret
        printf("Enter your choice: ");//entering the choice
        scanf("%d", &choice);//reading the choice from the user

        switch (choice) {
            case 1:
            login_user(&user);//Login user
            break;
            case 2:
            register_user(&user);//register new user
            break;
            case 3:
            list_movies(booking_tickets);
            break;
            case 4:
            book_tickets(&user, booking_tickets);//Book tickets
            break;
            case 5:
            int i = 0;
            while(user.tickets_[i].isBooked_ == true)
            view_ticket(&user.tickets_[i++]);
            if(i == 0)
            printf("No tickets booked yet!\n");
            break;
            case 6:
            printf("Thank you for using BookMyShow!\n");
            printf("Goodbye and see you again!\n"); 
            return 0;
            break;
            case 7:
            return 1; // secret input, for admins to access admin view
            default:
            printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 5);

}


void view_ticket(Ticket* ticket)
{
    printf("Seat Number: %d\n", ticket->seat_.number_);
    printf("Movie Details: \n");
    print_movie(&(ticket->movie_));
}

void login_user(User* user)
{
    //username is users firstname+lastname without space
}

void register_user(User* user)
{
    //take inputs for all members of user
    //call initialize_user_reg
}

void book_tickets(User* user, Booking_tickets* booking_tickets)
{
    bool booked = false;
    do
    {
        printf("Please select a Movie from the list below: \n");
        list_movies(booking_tickets);
        int movie_number = 0;
        int result;
        char ch;
        do {
            printf("Movie Number: ");
            result = scanf("%d", &movie_number);
            if (result != 1 && movie_number <= booking_tickets.movie_count && movie_number > 0) {
                printf("Invalid input. Please enter a valid movie number.\n");
                // Clear input buffer
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            int option = 0;
            printf("Options:\n")
            printf("1. View Seats\n");
            printf("2. Select/change Seats\n");
            printf("3. Proceed to payment\n");
            printf("4. Select different movie\n");
            printf("5. Return to Main menu\n");
            printf("Input: ");
            scanf("%d", &option)
            switch(option)
            {
                case(1):
                view_seats(booking_tickets.booking_movie[result-1]);
                break;
                case(2):
                select_seats(&user,booking_tickets.booking_movie[result-1]);
                break;
                case(3):
                pay_for_seats(&user);
                break;
                case(4):
                break;
                case(5):
                booked = true;
                return;
                default:
                printf("Invalid input. Please enter a valid choice.\n");
                break;
            }
        } while (result != 1);
    }
    while(!booked);
}

