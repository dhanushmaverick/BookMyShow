#include "customer.h"
#include "admin.h"

int validname(char *p)
{
    int flag = 1;//intilization of flag to zero
    for(int i = 0; p[i] != '\0';i++)
    {
        //if the entered name having other than alphabets then flag is set ot zero
        if(!((p[i] >= 'a' && p[i] <= 'z') || (p[i] >= 'A' && p[i] <= 'Z') || (p[i] == ' ')))
        {
            flag = 0;// flag set to zero
            break;
        }
    }
    if(flag == 1)
    {
        return 1;//if the flag is 1 the the entered name is correct and returning 1
    }
    else
    {
        return 0;//else returning 0
    }
}
int validemail(char* email, User *user)
{
    char* at = strchr(email, '@');//intilizing  @ and .com
    char* dot = strstr(email, ".com");

    if (email == NULL || strlen(email) < 6) 
    {
        return 0;
    }

    if (!at || !dot || at > dot) 
    {
        return 0; // '@' must exist before ".com"
    }
    return 1; // Valid
}


int validphone(char *phone, User *user)
{
    if (phone == NULL || strlen(phone) != 10) return 0;

    for (int i = 0; phone[i] != '\0'; i++) 
    {
        if (!isdigit((unsigned char)phone[i])) 
        {
            return 0; // Found non-digit
        }
    }
    return 1; // Valid
}



void list_users(UserDetails *ud) 
{
    if (ud->users_count_ == 0) 
    {
        printf("No Users Found\n");
        return;
    }
    printf("------------------------------------------------------------------Users List-----------------------------------------------------------------\n");
    printf("%-5s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n", 
           "S.No", "Firstname", "Lastname", "Number", "Email ID", "Username", "Password", "Registration");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < ud->users_count_; i++) 
    {
        printf("%-5d %-20s %-20s %-20s %-20s %-20s %-20s %-20d\n",
               i + 1,
               ud->user_details[i].first_name_,
               ud->user_details[i].last_name_,
               ud->user_details[i].number_,
               ud->user_details[i].email_,
               ud->user_details[i].username_,
               ud->user_details[i].password_,
               ud->user_details[i].isRegistered_);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

// void save_user(User *user)
// {
//     save_user_file(user); // Save movies to file
//     //exit(EXIT_SUCCESS); // Exit the program
// }

// void initialize_users_start(User *user)
// {
//     user->ID_ = 0;
//     load_from_userfile(user);
// }


void load_from_userfile(UserDetails *user)
{
    FILE *fptr = fopen("userdetails.csv", "r");
    if (!fptr) 
    {
        printf("No existing user file found. Starting fresh.\n");
        return;
    }
    fscanf(fptr, "#%d\n", &user->users_count_);
    ensure_capacity(user);
    for (int i = 0; i < user->users_count_; i++) {
        fscanf(fptr, "%[^,],", user->user_details[i].first_name_);
        fscanf(fptr, "%[^,],", user->user_details[i].last_name_);
        fscanf(fptr, "%[^,],", user->user_details[i].number_);
        fscanf(fptr, "%[^,],", user->user_details[i].email_);
        fscanf(fptr, "%[^,],", user->user_details[i].username_);
        fscanf(fptr, "%[^\n]\n", user->user_details[i].password_);
        user->user_details[i].isRegistered_ = true;
        user->user_details[i].ID_ = i + 1;
    }
    fclose(fptr);
    printf("%d users loaded from file.\n", user->users_count_);
}

void save_user_file(UserDetails *user) 
{
    FILE *fptr = fopen("userdetails.csv", "w+");
    if (!fptr) 
    {
        printf("Error opening file for writing\n");
        return;
    }
    fprintf(fptr, "#%d\n", user->users_count_);
    for (int i = 0; i < user->users_count_; i++) 
    {
        fprintf(fptr, "%s,%s,%s,%s,%s,%s\n",
                user->user_details[i].first_name_,user->user_details[i].last_name_,user->user_details[i].number_,
                user->user_details[i].email_,user->user_details[i].username_,user->user_details[i].password_);
    }
    fclose(fptr);
    printf("User data saved successfully.\n");
}


void ensure_capacity(UserDetails *user) 
{
    if (user->users_count_ >= user->users_capacity_) 
    {
        user->users_capacity_ *= 2; // double capacity
        User *temp = realloc(user->user_details, user->users_capacity_ * sizeof(User));
        if (!temp) 
        {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
        user->user_details = temp;
    }
}