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
    fgets(profile->description, sizeof(profile->description), stdin);
    profile->description[strcspn(profile->description, "\n")]='\0';
}

void show_profile(Profile *profile)
{
    printf("\nName: %s %s\n", profile->name, profile->last_name);
    printf("Age: %d\n", profile->age);
    printf("Hobby: %s\n", profile->hobby);
    printf("Height: %.2f metres\n", profile->height);
    printf("Sign: %s\n", profile->sign);
    printf("Description: %s\n", profile->description);
}
int search_profile_by_name(Profile *profiles, int num_profiles, const char *name)
{
    printf("\nSearching for profile with name: %s\n", name);
    for(int i=0;i<num_profiles;i++)
    {
        printf("Comparing with profile name: %s\n", profiles[i].name);
        if (strcmp(profiles[i].name, name)==0)
        {
            return i;
        }
    }
    return -1;
}


int main()
{

    Profile profiles[50];
    int num_profiles=0;
    int choice;
    char search_name[50];

    do {
        printf("\n\t\t**| MENU |**\n");
        printf("1. Enter profile data\n");
        printf("2. Display profile data\n");
        printf("3. Search profile by name\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                read_profile(&profiles[num_profiles]);
                num_profiles++;
                break;
            case 2:
                printf("\nProfile Data:\n");
                for(int i=0;i<num_profiles;i++)
                {
                    printf("\nProfile %d:\n",i+1);
                    show_profile(&profiles[i]);
                }
                break;
            case 3:
                printf("\nEnter the name to search for: ");
                scanf("%s", search_name);
                int position=search_profile_by_name(profiles, num_profiles, search_name);
                if(position!=-1)
                {
                    printf("\nProfile found at position %d\n",position+1);
                }
                else
                {
                    printf("\nProfile with the name %s not found\n", search_name);
                }
                break;
            case 4:
                printf("\nExit\n");
                break;
            default:
                printf("\nInvalid option\n");
        }
    }
    while(choice!=4);

    return 0;
}
