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
    user->tickets_[i].isBooked = false;
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
    isBooked_ = false;
}

void initialize_seat(Seat* seat)
{
    static int count = 1;
    seat.number = count++;
    seat.isEmpty_ = true;
}

bool customer_main()
{
    Seat seats_[MAX_SEATS_];
    for(int i = 0; i < MAX_SEATS_; i++)
    initialize(&seats_[i]);

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
            list_movies();
            break;
            case 4:
            book_tickets(&user);//Book tickets
            break;
            case 5:
            int i = 0;
            while(user.ticket[i].isBooked == true)
            view_ticket(&user.ticket[i++]);
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
    printf("Seat Number: %d\n", ticket->seat.number);
    printf("Movie Details: ");
    print_movie(&(ticket->movie));
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

void book_tickets(User* user);
{

}