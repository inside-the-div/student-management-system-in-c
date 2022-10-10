#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// some global variables
int i,j;
int LineLenth;
char StudentID[10];
FILE *AllStudents;
FILE *AllCourses;
FILE *ExistingAllStudents;
FILE *TempAllStudents;
FILE *ExistingAllCourses;
FILE *TempAllCourses;
// end

bool IsRunning = true;
void Menu();
void AddNewStudent();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
void EditStudent(char StudentID[10]);
int  DeleteStudent(char StudentID[10]);
int DeleteAllStudents();
int IsAlreadyExists(char GivenLine[30],char InfoType);
void ErrorAndRestart(char *Error[100]);
void UserGuideline();
void AboutUs();

int main()
{
    while(IsRunning)
    {
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            break;
        case 1:
            AddNewStudent();
            break;
        case 2:
            ShowAllStudents();
            break;
        case 3:
        {
            system("cls");
            printf("\n\t\t **** Search Students ****\n\n");
            printf("Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);
            if(!IsFound)
            {
                printf("No Student Found\n");
            }
            break;
        }
        case 4:
            //EditStudent();
            printf("Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);

            if(IsFound)
            {
                EditStudent(StudentID);
            }
            else
            {
                printf("No Student Found\n");
            }
            break;
        case 5:
            system("cls");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf("Enter The Student ID: ");
            scanf("%s",StudentID);
            int isDeleted = DeleteStudent(StudentID);

            break;
        case 6:
        {
            char Sure = 'N';
            getchar();
            printf("Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                int IsDeleted = DeleteAllStudents();
                if(IsDeleted)
                {
                    printf("Success\n");
                }
                else
                {
                    printf("Your Data is Safe.\n");
                }
            }
            else
            {
                printf("Your Data is Safe.\n");
            }
            break;
        }

        case 7:
            //ClearWindow();
            break;
        case 8:
            //UserGuideline();
            break;
        case 9:
            //AboutUs();
            break;
        default:
            break;
        }
    }

    return 0;
} // end main function

void Menu()
{
    printf("\n\n\t***Student Management System Using C***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add a new student.\n");
    printf("\t\t[2] Show all students.\n");
    printf("\t\t[3] Search students.\n");
    printf("\t\t[4] Edit a student.\n");
    printf("\t\t[5] Delete a student.\n");
    printf("\t\t[6] Delete all students.\n");
    printf("\t\t[7] Clear the window.\n");
    printf("\t\t[i] User Guideline.\n");
    printf("\t\t[a] About Us.\n");
    printf("\t\t[0] Exit the program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
} // end menu

void AddNewStudent()
{
    system("cls");
    printf("\n\t\t **** Add A New Student ****\n\n");

    char IDStr[10];
    char Name[20];
    char Phone[20];
    char Email[30];
    int NumberOfCourses;
    char NumberOfCoursesStr[2];
    char NewStudent[200];

    char StudentCourses[30];
    char CourseCode[5];
    char CourseName[10];


    int IsNewID = 0;
    while(!IsNewID)
    {
        printf("Enter The ID: ");
        scanf("%s",&IDStr);
        if(IsAlreadyExists(IDStr,'i'))
        {
            printf("This ID is Already Exists\n");
        }
        else
        {
            IsNewID = 1;
        }
    }

    printf("Enter The Name: ");
    scanf(" %[^\n]s",&Name);

    int IsNewPhone = 0;
    while(!IsNewPhone)
    {
        printf("Enter The Phone: ");
        scanf("%s",&Phone);
        if(IsAlreadyExists(Phone,'p'))
        {
            printf("This Phone Already Exists\n");
        }
        else
        {
            IsNewPhone = 1;
        }
    }

    int IsNewEmail = 0;
    while(!IsNewEmail)
    {
        printf("Enter The Email: ");
        scanf("%s",&Email);
        if(IsAlreadyExists(Email,'e'))
        {
            printf("This Email Already Exists.\n");
        }
        else
        {
            IsNewEmail = 1;
        }
    }

    printf("Number of courses: ");
    scanf("%d",&NumberOfCourses);
    if(NumberOfCourses <= 0 || NumberOfCourses > 4)
    {
        printf("Student Must Have at list 1 and At most 4 courses\n");
    }
    itoa(NumberOfCourses,NumberOfCoursesStr,10);

    NewStudent[0] = 0;
    strcat(NewStudent,IDStr);
    strcat(NewStudent,"|");
    strcat(NewStudent,Name);
    strcat(NewStudent,"|");
    strcat(NewStudent,Phone);
    strcat(NewStudent,"|");
    strcat(NewStudent,Email);
    strcat(NewStudent,"|");
    strcat(NewStudent,NumberOfCoursesStr);
    strcat(NewStudent,"\n");

    AllCourses  = fopen("data/All-Courses.txt","a");
    StudentCourses[0] = 0;
    strcat(StudentCourses,IDStr);

    for(i=0; i<NumberOfCourses; i++)
    {
        printf("Enter Course %d The Code: ",i+1);
        scanf("%s",&CourseCode);

        printf("Enter Course %d The Name: ",i+1);
        scanf(" %[^\n]s",&CourseName);

        strcat(StudentCourses,"|");
        strcat(StudentCourses,CourseCode);
        strcat(StudentCourses,"|");
        strcat(StudentCourses,CourseName);

    }
    strcat(StudentCourses,"\n");
    AllStudents = fopen("data/All-Students.txt","a");
    fprintf(AllStudents,NewStudent);
    fclose(AllStudents);

    fprintf(AllCourses,StudentCourses);
    strcat(StudentCourses,"\n");
    fclose(AllCourses);

    printf("Student Added Success\n");
}

void ShowAllStudents()
{
    system("cls");

    printf("\n\t\t **** All Students ****\n\n");
    printf("|==========|====================|====================|==============================|=============|\n");
    printf("|    ID    |        Name        |    Phone Number    |          Email               |  NO.Course  |\n");
    printf("|==========|====================|====================|==============================|=============|\n");

    AllStudents = fopen("data/All-Students.txt","r");

    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,AllStudents))
    {
        printf("|");
        int TotalSpace = 10;
        int j;
        int Pipe = 0;
        for(i=0; i<strlen(Student)-1; i++)
        {
            if(Student[i] == '|')
            {
                Pipe++;
                for(j=0; j<TotalSpace; j++)
                {
                    printf(" ");
                }
                printf("|");
                if(Pipe == 1 || Pipe == 2)
                {
                    TotalSpace = 20;
                }
                else if(Pipe == 3)
                {
                    TotalSpace = 30;
                }
                else if(Pipe == 4)
                {
                    TotalSpace = 13;
                }
            }
            else
            {
                printf("%c",Student[i]);
                TotalSpace--;
            }
        }
        for(j=1; j<=TotalSpace; j++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|----------|--------------------|--------------------|------------------------------|-------------|\n");
    }
    fclose(AllStudents);
}

int SearchStudent(char StudentID[10])
{
    system("cls");
    char ThisStudetID[10];
    int StudentFound = 0;
    int Pipe;
    AllStudents = fopen("data/All-Students.txt","r");
    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,AllStudents))
    {
        for(i=0; Student[i] != '|'; i++)
        {
            ThisStudetID[i] = Student[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            StudentFound = 1;
            break;
        }
        else
        {
            StudentFound = 0;
        }
    }

    if(StudentFound)
    {

        printf("\n One Student Found for ID: %s\n\n",StudentID);
        printf(" Student Informations\n");

        printf(" ID:    ");
        Pipe = 0;
        for(i=0; i<strlen(Student); i++)
        {
            if(Student[i] == '|')
            {
                Pipe++;
                printf("\n");
                if(Pipe == 1)
                {
                    printf(" Name:  ");
                }
                else if(Pipe == 2)
                {
                    printf(" Phone: ");
                }
                else if(Pipe == 3)
                {
                    printf(" Email: ");
                }
                else if(Pipe == 4)
                {
                    printf("\n Total Number of Courses: ");
                }
            }
            else
            {
                printf("%c",Student[i]);
            }
        }
    }

    int CourseFound = 0;
    AllCourses = fopen("data/All-Courses.txt","r");
    char Course[LineLenth];

    while(fgets(Course,LineLenth,AllCourses))
    {
        for(i=0; Course[i] != '|'; i++)
        {
            ThisStudetID[i] = Course[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            CourseFound = 1;
            break;
        }
        else
        {
            CourseFound = 0;
        }
    }
    int CourseCount = 1;
    if(CourseFound)
    {
        Pipe = 1;
        for(i=0; i<strlen(Course); i++)
        {
            if(Course[i] == '|')
            {

                Pipe++;
                if(Pipe > 2 && Pipe %2 != 0)
                {
                    printf("\n Course %d Name: ",CourseCount);
                    CourseCount++;
                }
                else
                {
                    if(CourseCount != 1){
                        printf("\n");
                    }
                    printf("\n Course %d Code: ",CourseCount);
                }

            }
            else if(Pipe > 1)
            {
                printf("%c",Course[i]);
            }
        }
    }
    fclose(AllStudents);
    fclose(AllCourses);
    return StudentFound;
}

void EditStudent(char StudentID[10])
{
    printf("\n\t\t **** Update The New Student ****\n\n");

    char OldName[20];
    char OldPhone[20];
    char OldEmail[30];
    char OldEmail2[100];
    OldEmail2[0] = 0;
    char OldNumberOfCoursesStr[2];
    char NewStudent[200];
    NewStudent[0] = 0;
    char StudentCourses[30];
    char OldCourseCode[5];
    char OldCourseName[10];

    char NewName[20];
    char NewPhone[20];
    char NewEmail[30];
    int NewNumberOfCourses;
    char NewNumberOfCoursesStr[2];

    char NewCourseCode[5];
    char NewCourseName[10];

    printf("Enter The New Name: ");
    scanf(" %[^\n]s",&NewName);

    int IsNewPhone = 0;
    while(!IsNewPhone)
    {
        printf("Enter The New Phone: ");
        scanf("%s",&NewPhone);
        if(IsAlreadyExists(NewPhone,'p'))
        {
            printf("This Phone Already Exists\n");
        }
        else
        {
            IsNewPhone = 1;
        }
    }

    int IsNewEmail = 0;
    while(!IsNewEmail)
    {
        printf("Enter The New Email: ");
        scanf("%s",&NewEmail);
        if(IsAlreadyExists(NewEmail,'e'))
        {
            printf("This Email Already Exists.\n");
        }
        else
        {
            IsNewEmail = 1;
        }
    }

    printf("Number of New courses: ");
    scanf("%d",&NewNumberOfCourses);
    itoa(NewNumberOfCourses,NewNumberOfCoursesStr,10);

    int Index;
    char ThisStudetID[10];
    int StudentFound = 0;
    int Pipe;
    ExistingAllStudents = fopen("data/All-Students.txt", "r");
    TempAllStudents = fopen("data/Temp-All-Students.txt","w");
    LineLenth = 200;
    char Student[LineLenth];

    while (fgets(Student, LineLenth, ExistingAllStudents))
    {
        if (!StudentFound)
        {
            for (i = 0; Student[i] != '|'; i++)
            {
                ThisStudetID[i] = Student[i];
            }
            ThisStudetID[i] = '\0';
            if (strcmp(StudentID, ThisStudetID) == 0)
            {
                StudentFound = 1;
                Pipe = 0;
                Index = 0;
                for (i = 0; i < strlen(Student); i++)
                {
                    if (Student[i] == '|')
                    {
                        Pipe++;
                        if (Pipe == 2)
                        {
                            OldName[Index] = '\0';
                        }
                        else if (Pipe == 3)
                        {
                            OldPhone[Index] = '\0';
                        }
                        else if (Pipe == 4)
                        {
                            OldEmail[Index] = '\0';
                        }
                        Index = 0;
                    }
                    else
                    {
                        if (Pipe == 1)
                        {
                            OldName[Index] = Student[i];
                            Index++;
                        }
                        else if (Pipe == 2)
                        {
                            OldPhone[Index] = Student[i];
                            Index++;
                        }
                        else if (Pipe == 3)
                        {
                            OldEmail[Index] = Student[i];
                            Index++;
                        }
                        else if (Pipe == 4)
                        {
                            OldNumberOfCoursesStr[Index] = Student[i];
                            Index++;
                        }
                    }
                }
                OldNumberOfCoursesStr[Index] = '\0';

                strcat(NewStudent,StudentID);
                strcat(NewStudent,"|");

                if(strcmp(NewName,"0") == 0)
                {
                    strcat(NewStudent,OldName);
                }
                else
                {
                    strcat(NewStudent,NewName);
                }
                strcat(NewStudent,"|");

                if(strcmp(NewPhone,"0") == 0)
                {
                    strcat(NewStudent,OldPhone);
                }
                else
                {
                    strcat(NewStudent,NewPhone);
                }
                strcat(NewStudent,"|");

                if(strcmp(NewEmail,"0") == 0)
                {
                    strcat(NewStudent,OldEmail);
                }
                else
                {
                    strcat(NewStudent,NewEmail);
                }
                strcat(NewStudent,"|");

                if(strcmp(NewNumberOfCoursesStr,"0") == 0)
                {
                    strcat(NewStudent,OldNumberOfCoursesStr);
                }
                else
                {
                    strcat(NewStudent,NewNumberOfCoursesStr);
                    strcat(NewStudent,"\n");
                }

                printf("Old Name: %s\n",OldName);
                printf("Old Phone: %s\n",OldPhone);
                printf("Old Email: %s\n",OldEmail);
                printf("Old Course: %s\n",OldNumberOfCoursesStr);

                fprintf(TempAllStudents,NewStudent);
            }
            else
            {
                fprintf(TempAllStudents,Student);
                StudentFound = 0;
            }
        }
        else
        {
            fprintf(TempAllStudents,Student);
        }
    }
    fclose(ExistingAllStudents);
    fclose(TempAllStudents);
    remove("data/All-Students.txt");
    rename("data/Temp-All-Students.txt", "data/All-Students.txt");

    if(NewNumberOfCourses > 0)
    {
        ExistingAllCourses = fopen("data/All-Courses.txt","r");
        TempAllCourses = fopen("data/Temp-All-Courses.txt","w");
        int IsCourseFound = 0;
        LineLenth = 200;

        char StudentCourses[30];
        char Course[LineLenth];
        char CourseCode[5];
        char CourseName[10];

        StudentCourses[0] = 0;

        while (fgets(Course, LineLenth, ExistingAllCourses))
        {
            if (!IsCourseFound)
            {
                for (i = 0; Course[i] != '|'; i++)
                {
                    ThisStudetID[i] = Course[i];
                }
                ThisStudetID[i] = '\0';
                if (strcmp(StudentID, ThisStudetID) == 0)
                {
                    IsCourseFound = 1;
                    for(i=0; i<NewNumberOfCourses; i++)
                    {
                        strcat(StudentCourses,StudentID);
                        printf("Enter Course %d The Code: ",i+1);
                        scanf("%s",&CourseCode);

                        printf("Enter Course %d The Name: ",i+1);
                        scanf(" %[^\n]s",&CourseName);

                        strcat(StudentCourses,"|");
                        strcat(StudentCourses,CourseCode);
                        strcat(StudentCourses,"|");
                        strcat(StudentCourses,CourseName);
                    }
                    strcat(StudentCourses,"\n");
                    fprintf(TempAllCourses,StudentCourses);
                }
                else
                {
                    fprintf(TempAllCourses,Course);
                }
            }
            else
            {
                fprintf(TempAllCourses,Course);
            }
        }

        fclose(ExistingAllStudents);
        fclose(TempAllStudents);
        remove("data/All-Courses.txt");
        rename("data/Temp-All-Courses.txt", "data/All-Courses.txt");
    }
}

int DeleteStudent(char StudentID[10])
{
    char ThisStudetID[10];
    int StudentFound = 1;
    int Pipe;
    ExistingAllStudents = fopen("data/All-Students.txt","r");
    TempAllStudents = fopen("data/Temp-All-Students.txt","w");
    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,ExistingAllStudents))
    {
        for(i=0; Student[i] != '|'; i++)
        {
            ThisStudetID[i] = Student[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            StudentFound = 1;
        }
        else
        {
            StudentFound = 0;
            fprintf(TempAllStudents,Student);
        }
    }
    fclose(ExistingAllStudents);
    fclose(TempAllStudents);

    int CourseFound = 1;
    ExistingAllCourses = fopen("data/All-Courses.txt","r");
    TempAllCourses = fopen("data/Temp-All-Courses.txt","w");
    char Course[LineLenth];

    while(fgets(Course,LineLenth,ExistingAllCourses))
    {
        for(i=0; Course[i] != '|'; i++)
        {
            ThisStudetID[i] = Course[i];
        }
        ThisStudetID[i] = '\0';
        if(strcmp(StudentID,ThisStudetID) == 0)
        {
            CourseFound = 1;
        }
        else
        {
            fprintf(TempAllCourses,Course);
            CourseFound = 0;
        }
    }
    fclose(ExistingAllCourses);
    fclose(TempAllCourses);
    remove("data/All-Students.txt");
    remove("data/All-Courses.txt");
    rename("data/Temp-All-Students.txt", "data/All-Students.txt");
    rename("data/Temp-All-Courses.txt", "data/All-Courses.txt");

    if(StudentFound || CourseFound)
    {
        printf("Successfully Deleted The Student.\n");
        return 1;
    }
    else
    {
        printf("Student/Courses Not Found!\nMake sure you enter the correct ID.\n");
        return 0;
    }
}

int DeleteAllStudents()
{
    remove("data/All-Students.txt");
    remove("data/All-Courses.txt");
    return 1;
}

int IsAlreadyExists(char GivenLine[30],char InfoType)
{
    char ThisPhone[20];
    char ThisEmail[30];
    char ThisStudetID[10];
    int Index;
    int Pipe;
    AllStudents = fopen("data/All-Students.txt", "r");
    LineLenth = 200;
    char Student[LineLenth];
    int EmailFound = 0;
    int PhoneFound = 0;
    while (fgets(Student, LineLenth, AllStudents))
    {
        for(i=0; Student[i] != '|'; i++)
        {
            ThisStudetID[i] = Student[i];
        }
        ThisStudetID[i] = '\0';
        if(InfoType == 'i' && strcmp(GivenLine,ThisStudetID) == 0)
        {
            return 1; // id already exists
        }

        Pipe = 0;
        Index = 0;
        for (i = 0; i < strlen(Student); i++)
        {
            if (Student[i] == '|')
            {
                Pipe++;
                if (Pipe == 3)
                {
                    ThisEmail[Index] = '\0';
                }
                else if (Pipe == 4)
                {
                    ThisPhone[Index] = '\0';
                }
                Index = 0;
            }
            else
            {
                if (Pipe == 2)
                {
                    ThisEmail[Index] = Student[i];
                    Index++;
                }
                else if (Pipe == 3)
                {
                    ThisPhone[Index] = Student[i];
                    Index++;
                }
            }
        }

        if(InfoType == 'e' && strcmp(ThisEmail,GivenLine) == 0)
        {
            EmailFound++; // to check when edit
            if(EmailFound > 1)
            {
                return EmailFound; // email already exists
            }
        }
        else if(InfoType == 'p' && strcmp(ThisPhone,GivenLine) == 0)
        {
            PhoneFound++;
            if(PhoneFound > 1)
            {
                return 1; // phone already exists
            }
        }
    }
    fclose(AllStudents);
    if(InfoType == 'p')
    {
        return PhoneFound;
    }
    else if(InfoType == 'e')
    {
        return EmailFound;
    }
    else
    {
        return 0;
    }
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void UserGuideline()
{
    printf("UserGuideline");
}

void AboutUs()
{
    printf("AboutUs");
}
