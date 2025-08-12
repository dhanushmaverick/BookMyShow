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



void list_users(User *user)
{
    if (user->count == 0)
    {
        printf("No Users Found\n");//if the movie is zero it prints no movies
    } 
    else 
    {
        printf("------------------------------------------------------------------Users List-----------------------------------------------------------------\n");
        //if movie count is not zero then it prints movies
        printf("%-5s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n", "S.No", "Firstname", "Lastname", "Number", "Email ID", "Username", "Password", "Registration");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < user->count; i++) 
        {
            printf("%-5d", i + 1);
            printf(" %-20s", user->first_name_);
            printf(" %-20s", user->last_name_);
            printf(" %-20s", user->number_);
            printf(" %-20s", user->email_);
            printf(" %-20s", user->username);
            printf(" %-20s", user->password_);
            printf(" %-20d", user->isRegistered_);
            printf("\n");
        }
        printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void save_user(User *user)
{
    save_user_file(user); // Save movies to file
    //exit(EXIT_SUCCESS); // Exit the program
}

void initialize_users_start(User *user)
{
    user->count = 0;
    load_from_userfile(user);
}

void load_from_userfile(User *user)//loading users to file function definition 
{
    FILE* fptr = fopen("userdetails.csv","r");//opening the file in read format
    if (!fptr) 
    {
        printf("Error opening file for reading\n");//printing error opening if file doesn't opened
    }
    fscanf(fptr,"#%d\n",&user->count);
    for (int i = 0; i < user->count; i++) 
    {

        fscanf(fptr, "%[^,],",user->first_name_);
        fscanf(fptr, "%[^,],", user->last_name_);
        fscanf(fptr, "%[^,],", user->number_);
        fscanf(fptr, "%[^,],",user->email_);
        fscanf(fptr, "%[^,],", user->username);
        fscanf(fptr, "%[^\n]\n", user->password_);
    }
    fclose(fptr);//closing the file
    printf("Users loaded from file successfully\n");
}

void save_user_file(User *user) //save to file definition
{
    FILE* fptr = fopen("userdetails.csv","w+");//opening the file
    if (!fptr) 
    {
        printf("Error opening file for writing\n");//printing the error if the file is not opened
    }
    fprintf(fptr,"#%d\n", user->count);//printing the number of movies in address book
    for (int i = 0; i < user->count ;i++) 
    {
        //printing  in the file 
        fprintf(fptr, "%s,%s,%s,%s,%s,%s\n", user->first_name_,user->last_name_,user->number_,user->email_,user->username,user->password_);
    }
    fclose(fptr);//closing the file
    printf("User Registered successfully\n");//printing the statment that movies are saved to file successfully
}
