#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char name[50];
    char last_name[50];
    int age;
    char hobby[50];
    float height;
    char sign[20];
    char description[100];
} Profile;

void read_profile(Profile *profile)
{
    printf("Write the name: ");
    scanf("%s %s", profile->name, profile->last_name);
    printf("Write the age: ");
    scanf("%d", &profile->age);
    printf("Write the hobby: ");
    scanf("%s", profile->hobby);
    printf("Write the height: ");
    scanf("%f", &profile->height);
    printf("Write the sign: ");
    scanf("%s", profile->sign);
    printf("Write a short description about yourself: ");
    getchar();
    fgets(profile->description, sizeof(profile->description),stdin);
    profile->description[strcspn(profile->description, "\n")]='\0';
}

void show_profile(Profile profile)
{
    printf("\nName: %s %s\n", profile.name, profile.last_name);
    printf("Age: %d\n", profile.age);
    printf("Hobby: %s\n", profile.hobby);
    printf("Height: %.2f \n", profile.height);
    printf("Sign: %s\n", profile.sign);
    printf("Description: %s\n", profile.description);
}

int search_profile(Profile profiles[], int num_profiles, char name[])
{
    for(int i=0;i<num_profiles;i++)
    {
        if(strcmp(profiles[i].name, name)==0)
        {
            return i;
        }
    }
    return -1;
}

void free_memory(Profile *profiles)
{
    free(profiles);
}

void sort_by_name(Profile *profiles, int num_profiles)
{
    Profile temp;
    for(int i=0;i<num_profiles-1;i++)
    {
        for(int j=0;j<num_profiles-i-1;j++)
        {
            if(strcmp(profiles[j].name, profiles[j+1].name)>0)
            {
                temp=profiles[j];
                profiles[j]=profiles[j+1];
                profiles[j+1]=temp;
            }
        }
    }
}

void add_profile_in_the_beginning(Profile *profiles, int *num_profiles)
{
    if(*num_profiles<50)
    {
        Profile profile;
        printf("\nWrite the info for a new profile:\n");
        read_profile(&profile);
        for(int i=*num_profiles;i>0;i--)
        {
            profiles[i]=profiles[i-1];
        }
        profiles[0]=profile;
        (*num_profiles)++;
    }
    else
    {
        printf("\nInserting more profiles is not possiblee\n");
    }
}

void add_profile_in_the_end(Profile *profiles, int *num_profiles)
{
    if(*num_profiles<50)
    {
        printf("\nWrite the info for a new profile:\n");
        read_profile(&profiles[*num_profiles]);
        (*num_profiles)++;
    }
    else
    {
        printf("\nInserting more profiles is not possiblee\n");
    }
}

void insert_profile_in_specified_position(Profile *profiles, int *num_profiles, int position)
{
    if(*num_profiles<50 && position>=0 && position<=*num_profiles)
    {
        Profile profile;
        printf("\nWrite the information for a new profile:\n");
        read_profile(&profile);
        for(int i=*num_profiles;i>position;i--)
        {
            profiles[i]=profiles[i-1];
        }
        profiles[position]=profile;
        (*num_profiles)++;
    }
    else
    {
        printf("\nInsertion not possiblee\n");
    }
}

void delete_profile_from_position(Profile *profiles, int *num_profiles, int position)
{
    if(position>=0 && position<*num_profiles)
    {
        for(int i=position;i<*num_profiles-1;i++)
        {
            profiles[i]=profiles[i+1];
        }
        (*num_profiles)--;
        printf("\nProfile from position %d was deleted successfully\n",position+1);
    }
    else
    {
        printf("\nProfile was not deleted\n");
    }
}

void display_the_menu()
{
    printf("\n\t\t**|MENIU|**\n");
    printf("1. Add a profile at the beginning of the list\n");
    printf("2. Add a profile at the end of the list\n");
    printf("3. Insert a profile in a specified position\n");
    printf("4. Delete a profile from a specified position\n");
    printf("5. Display all profiles\n");
    printf("6. Search for a profile by name\n");
    printf("7. Sort the profiles by name\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

void evaluate_the_option(int choice, Profile *profiles, int *num_profiles)
{
    switch (choice)
    {
        case 1:
            add_profile_in_the_beginning(profiles, num_profiles);
            break;
        case 2:
            add_profile_in_the_end(profiles, num_profiles);
            break;
        case 3:
            if(*num_profiles>0)
            {
                int position;
                printf("\nSpecify the position: ");
                scanf("%d", &position);
                insert_profile_in_specified_position(profiles, num_profiles, position);
            }
            else
            {
                printf("\nThere are no profiles to insert\n");
            }
            break;
        case 4:
            if(*num_profiles>0)
            {
                int position;
                printf("\nSpecify the position: ");
                scanf("%d",&position);
                delete_profile_from_position(profiles, num_profiles, position);
            }
            else
            {
                printf("\nThere are no profiles to delete\n");
            }
            break;
        case 5:
            printf("\nAll profiles:\n");
            for(int i=0;i<*num_profiles;i++)
            {
                show_profile(profiles[i]);
            }
            break;
        case 6:
            if(*num_profiles>0)
            {
                char search_name[50];
                printf("\nEnter the profile name: ");
                scanf("%s", search_name);
                int position=search_profile(profiles, *num_profiles, search_name);
                if(position!=-1)
                {
                    printf("\nProfile was found at position %d.\n",position+1);
                }
            else
                {
                    printf("\nProfile was not found\n");
                }
            }
            else
            {
                printf("\nNo profiles to search for\n");
            }
            break;
        case 7:
            sort_by_name(profiles, *num_profiles);
            printf("\nProfiles have been sorted by name\n");
            break;
        case 8:
            free_memory(profiles);
            printf("\nMemory freed successfully. Exiting\n");
            break;
        default:
            printf("\nInvalid option\n");
    }
}

int main()
{
    Profile *profiles=(Profile*)malloc(50 * sizeof(Profile));
    int num_profiles=0;
    int choice;

    if(profiles==NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    do
    {
        display_the_menu();
        scanf("%d", &choice);
        evaluate_the_option(choice, profiles, &num_profiles);
    }
    while (choice != 8);
    return 0;
}
