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
       // printf("7. Exit to Admin Version\n"); //return true //make secret
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
    User *newuser = &user[user->count];

    read_firstname:
    printf("Please Enter Your First Name: ");
    getchar();
    scanf("%[^\n]", newuser->first_name_);
    if (!validname(newuser->first_name_)) //function call of validating name
    {
        printf("Invalid name\nEnter only characters\n");
        goto read_firstname;//if the entered name does not pass function it prints invalid and calls goto function
    }

    read_lastname:
    printf("Please Enter Your Last Name: ");
    getchar();
    scanf("%[^\n]", newuser->last_name_);
    if (!validname(newuser->first_name_)) //function call of validating name
    {
        printf("Invalid name\nEnter only characters\n");
        goto read_lastname;//if the entered name does not pass function it prints invalid and calls goto function
    }

    readphone:
    printf("Please Enter Your Mobile Number: ");
    getchar();
    scanf("%[^\n]", newuser->number_);
    if(!validphone(newuser->number_, user))//function call of validating phone number
    {
        printf("Invalid phone number\n");
        printf("Enter phone number(10 digits)\n");
        goto readphone;//if the entered phone number does not pass function it prints invalid and calls goto function
    }

    reademail:
    printf("Please Enter Your Mail ID: ");
    getchar();
    scanf("%[^\n]", newuser->email_);
    if(!validemail(newuser->email_, user)) //function call of validating email
    {
        printf("Invalid email_id\n");
        printf("Enter valid email_id\n");
        goto reademail;//if the entered email-id does not pass function it prints invalid and calls goto function
    }
    strcat(newuser->username,newuser->first_name_); 
    strcat(newuser->username,newuser->last_name_); 
    printf("New User Created\n\nYour Username is Firstname + Lastname\n\nUsername:%s\n", newuser->username);

    printf("Please Choose Your Password: ");
    getchar();
    scanf("%[^\n]", newuser->password_);

    user->count++;
    newuser->isRegistered_ = true;
    save_user_file(user);
}


void view_seats(Movies* movie)//View seats
{
    printf("Seat Number = count from left to right, increasing as you go lower\n");
    printf("* = Unoccupied Seat\nX = Occupied Seat\n\n");
    printf("0 1 2 3 4 5 6 7 8 9...\n");
    for(int i = 1; i < 6; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(movie->seats_[((i-1)*10)+j].isEmpty_)
            printf("* ");
            else
            printf("X ");
        }
        printf("%d\n", (i*10)+10);
    }
    printf("\n");
    printf("Please proceed to selecting your seats.\n");
}
void select_seats(User* user, Movies* movie)//Select seats
{
    static int Tickets = 123;
    //clear prev selection
    for(int i = 0; i < MAX_TICKETS_; i++)
    {
        if(movie->seats_[i].number_ == user->tickets_[i].seat_.number_)
        {
            initialize_seat(&movie->seats_[i]);
        }
        initialize_ticket(&user->tickets_[i]);
        user->tickets_[i].ID_ = Tickets++;
    }
    printf("How many tickets would you like to purchase?\n");
    int tickets = 1;
    int result;
    char ch;
    do {
        printf("Number of tickets: ");
        result = scanf("%d", &tickets);
        if(tickets == 0)
        {
            printf("Seat selection terminated since 0 tickets selected.\n");
        }
        if (result != 1 || tickets > MAX_TICKETS_) {
            printf("Invalid input. Please enter a valid number of tickets, max is 10 per person.\n");
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } while (result != 1);
    printf("Please choose the seat numbers:\n");
    int count = 0;
    for(int i = 0; i < tickets; i++)
    {
        bool valid = false;
        do
        {
            printf("%d. ", i+1);
            int no = 0;
            bool result = scanf("%d", &no);
            if((result != 1) || (i > MAX_SEATS_) || (i < 0) || (movie->seats_[i].isEmpty_ == true))
            {
                printf("Invalid input. Please enter a valid unoccupied seat number.\n");
                // Clear input buffer
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else
            {
                movie->seats_[i].isEmpty_ = false;
                user->tickets_[count].movie_ = *movie;
                user->tickets_[count++].seat_ = movie->seats_[i];
                valid = true;
            }
        }
        while(valid != true);
    }
    printf("Selection Confirmed. You can now proceed to checkout if you'd like.\n");
    return;
}
void pay_for_seats(User* user)//Pay for seats
{
    int i = 0;
    double cost = 0.0;
    for(i = 0; i < MAX_TICKETS_; i++)
    {
        if(!user->tickets_[i].isBooked_)
        break;
        printf("Ticket ID: %d",user->tickets_[i].ID_);
        printf("Movie Name: %s",user->tickets_[i].movie_.movie_name);
        printf("Ticket Price: %lf",user->tickets_[i].movie_.price);
        cost+= user->tickets_[i].movie_.price;
        user->tickets_[i].isBooked_ = true;
    }
    if(i == 0)
    {
        printf("You haven't selected any seats yet! Please come back after selecting the seats.");
        return;
    }

    printf("Number of tickets being purchased: %d", i+1);
    printf("Total Cost: %lf", cost);
    printf("Please make the payment at the theater before your movie.\nThe ticket price is displayed on the ticket.");
    printf("Thank you for your purchase!\nWe wish you a great time at the cinemas :)\n");
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
            //printf("Result = %d",result);

            if (result != 1 && (movie_number < booking_tickets->movies_count) || movie_number < 0) 
            {
                printf("Invalid input. Please enter a valid movie number.\n");
                // Clear input buffer
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            int option = 0;
            printf("Options:\n");
            printf("1. View Seats\n");
            printf("2. Select/change Seats\n");
            printf("3. Proceed to payment\n");
            printf("4. Select different movie\n");
            printf("5. Return to Main menu\n");
            printf("Input: ");
            scanf("%d", &option);
            switch(option)
            {
                case(1):
                view_seats(&booking_tickets->booking_movie[result-1]);
                break;
                case(2):
                select_seats(user,&booking_tickets->booking_movie[result-1]);
                break;
                case(3):
                pay_for_seats(user);
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

