#include "customer.h"


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
    user->isLoggedIn_ = false;
}

void initialize_user_reg(User* user, char* first_name, char* last_name, char* number, char* email, char* password)
{
    strcpy(user->first_name_ ,first_name);
    strcpy(user->last_name_ ,last_name);
    strcpy(user->number_,number);
    strcpy(user->email_,email);
    strcpy(user->password_, password);
    user->isLoggedIn_ = false;
    user->isRegistered_ = true;
}

void init_user_details(UserDetails *ud) 
{
    ud->users_capacity_ = 2; // start small
    ud->users_count_ = 0;
    ud->user_details = malloc(ud->users_capacity_ * sizeof(User));
    if (!ud->user_details) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    load_from_userfile(ud);
}

void init_user_details(UserDetails *ud) 
{
    ud->users_capacity_ = 2; // start small
    ud->users_count_ = 0;
    ud->user_details = malloc(ud->users_capacity_ * sizeof(User));
    if (!ud->user_details) 
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    load_from_userfile(ud);
}

void initialize_ticket(Ticket* ticket, bool withID)
{
    static int count = 1;
    if(withID)
    ticket->ID_ = count++;
    else
    {
        ticket->ID_ = 0;
        count--;
    }
    ticket->isBooked_ = false;
}



bool customer(Booking_tickets* booking_tickets, UserDetails* ud)
{
    User user;
    initialize_user(&user);
    system("cls");
    printf("-----Welcome to BookMyShow!-----\n");
    int choice = 0; 
    do
    {
        printf("Please choose an action below:\n");
        printf("1. User Login\n");
        printf("2. Register New User\n");
        printf("3. View Available Movies\n");
        printf("4. Book Tickets\n");
        printf("5. View Booked Tickets\n");
        printf("6. Exit Program\n"); //return false
       // printf("7. Exit to Admin Version\n"); //return true //make secret
        printf("Enter your choice: ");//entering the choice
        scanf("%d", &choice);//reading the choice from the user

        switch (choice) {
            case 1:
            login_user(ud);//Login user
            break;
            case 2:
            register_user(ud);//register new user
            break;
            case 3:
            list_movies(booking_tickets);
            break;
            case 4:
            book_tickets(&user, booking_tickets);//Book tickets
            break;
            case 5:
            int i = 0;
            while(i < MAX_TICKETS_ && user.tickets_[i].isBooked_ == true)
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

void login_user(UserDetails* ud)
{
    //username is users firstname+lastname+ID without space
    char username[100];
    char password[100];
    printf("Please Enter Your Username: ");
    getchar();
    scanf("%[^\n]", username);
    printf("Please Enter Your Password: ");
    getchar();
    scanf("%[^\n]", password);
    for(int i = 0; i < ud->users_count_; i++)
    {
        if(strcmp(ud->user_details[i].username_, username) == 0 && strcmp(ud->user_details[i].password_, password) == 0)
        {
            printf(" You Logined Successfully!\n");
            return;
        }
        else
        {
            printf("Invalid Username or Password\nPlease Try Again\n");
            return;
        }
    }
}

void register_user(UserDetails* ud)
{
    //take inputs for all members of user
    //call initialize_user_reg
    ensure_capacity(ud);
    User *newuser = &ud->user_details[ud->users_count_];

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
    if (!validname(newuser->last_name_)) //function call of validating name
    {
        printf("Invalid name\nEnter only characters\n");
        goto read_lastname;//if the entered name does not pass function it prints invalid and calls goto function
    }

    readphone:
    printf("Please Enter Your Mobile Number: ");
    getchar();
    scanf("%[^\n]", newuser->number_);
    if(!validphone(newuser->number_, ud->user_details))//function call of validating phone number
    {
        printf("Invalid phone number\n");
        printf("Enter phone number(10 digits)\n");
        goto readphone;//if the entered phone number does not pass function it prints invalid and calls goto function
    }

    reademail:
    printf("Please Enter Your Mail ID: ");
    getchar();
    scanf("%[^\n]", newuser->email_);
    if(!validemail(newuser->email_, ud->user_details)) //function call of validating email
    {
        printf("Invalid email_id\n");
        printf("Enter valid email_id\n");
        goto reademail;//if the entered email-id does not pass function it prints invalid and calls goto function
    }
    strcat(newuser->username_,newuser->first_name_); 
    strcat(newuser->username_,newuser->last_name_); 
    newuser->ID_ = ud->users_count_ + 1;
    char id[30];
    id[30] = (char)newuser->ID_ + '0';
    strcat(newuser->username_, id);
    printf("New User Created\n\nYour Username is Firstname + Lastname + ID\n\nUsername:%s\n", newuser->username_);

    printf("Please Choose Your Password: ");
    getchar();
    scanf("%[^\n]", newuser->password_);

    newuser->ID_ = ud->users_count_ + 1;
    ud->users_count_++;
    newuser->isRegistered_ = true;
    save_user_file(ud);
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
        printf("%d\n", (i*10));
    }
    printf("\n");
    printf("Please proceed to selecting your seats.\n");
}

void select_seats(User* user, Movies* movie)//Select seats
{
    //clear prev selection
    if(user->isRegistered_ == false)
    {
        printf("You cannot select tickets as you aren't registered!\nPlease register yourself and login in order to select seats!\n");
        return;
    }
    else if(user->isLoggedIn_ == false)
    {
        printf("Please login first in order to select seats!\n");
        return;
    }
    for(int i = 0; i < MAX_TICKETS_; i++)
    {
        for(int j = 0; j < MAX_SEATS_; j++)
        {
            if(movie->seats_[j].number_ == user->tickets_[i].seat_.number_)
            {
                initialize_seat(&movie->seats_[j]);
                initialize_ticket(&user->tickets_[i], false);
            }
        }
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
            return;
        }
        if (result != 1 || tickets > MAX_TICKETS_ || tickets <= 0) {
            printf("Invalid input. Please enter a valid number of tickets, max is 10 per person.\n");
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } while (result != 1);
    printf("Please choose the seat numbers:\n");
    int count = 0;
    for(int i = 0; i < tickets; i++)
    {
        int valid = 0;
        do
        {
            printf("Seat %d: ", i+1);
            int no = 0;
            valid = scanf("%d", &no);
            if((valid != 1) || (no > MAX_SEATS_) || (no < 1) || (movie->seats_[no-1].isEmpty_ == false))
            {
                printf("Invalid input. Please enter a valid unoccupied seat number.\n");
                // Clear input buffer
                while ((ch = getchar()) != '\n' && ch != EOF);
                valid = 0;
            }
            else
            {
                initialize_ticket(&user->tickets_[count], true);
                movie->seats_[no-1].isEmpty_ = false;
                user->tickets_[count].movie_ = *movie;
                user->tickets_[count++].seat_ = movie->seats_[no-1];
                valid = 1;
            }
        }
        while(valid != 1);
    }
    printf("Selection Confirmed. You can now proceed to checkout if you'd like.\n");
    return;
}
void pay_for_seats(User* user)//Pay for seats
{
    if(user->isRegistered_ == false)
    {
        printf("You cannot pay for tickets as you aren't registered!\n Please register yourself and login in order to pay!\n");
        return;
    }
    else if(user->isLoggedIn_ == false)
    {
        printf("Please login first in order to pay!\n");
        return;
    }
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
    int movie_number = 0;
    int result = 0;
    char ch;
    select_movie(user, booking_tickets, &movie_number);
    do
    {
        do {
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
                view_seats(&booking_tickets->booking_movie[movie_number]);
                break;
                case(2):
                select_seats(user,&booking_tickets->booking_movie[movie_number]);
                break;
                case(3):
                pay_for_seats(user);
                break;
                case(4):
                select_movie(user, booking_tickets, &movie_number);
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

void select_movie(User* user,Booking_tickets* booking_tickets, int* movie)
{
    int result = 0;
    char ch;
    printf("Please select a Movie from the list below: \n");
    list_movies(booking_tickets);
    do
    {
        printf("Movie Number: ");
        result = scanf("%d", movie);
        //printf("Result = %d",result);
        
        if (result != 1 || (*movie > booking_tickets->movies_count) || (*movie <= 0)) 
        {
            printf("Invalid input. Please enter a valid movie number.\n");
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
            result = 0;
        }
    }
    while(result != 1);
    *movie -= 1;
    printf("Movie %d successfully chosen.\n",*movie + 1);
    return;
}