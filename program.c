#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// some global variables
int i,j;
int LineLenth;
// end

bool IsRunning = true;
void Menu();
void AddNewStudent();
void ShowAllStudents();
int SearchStudent(char StudentId[10]);
void EditStudent(int StudentId);
void DeleteStudent(int StudentId);
void DeleteAllStudents();
bool IsAlreadyExists(char *GivenLine[30],char InfoType);
void ErrorAndRestart(char *Error[100]);
void UserGuideline();
void AboutUs();

int main(){
    while(IsRunning){
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option){
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
//               {
//                    char StudentID[10];
//                    scanf("%s",StudentID);
//                    SearchStudent(StudentID);
//                    break;
//               }
            case 4:
                //EditStudent();
                break;
            case 5:
                //DeleteStudent();
                break;
            case 6:
                //DeleteAllStudents();
                break;
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


void Menu(){
    printf("\n\n\t***welcome to the student management system***\n\n");
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


void AddNewStudent(){
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

    printf("Enter The ID: ");
    scanf("%s",&IDStr);

    printf("Enter The Name: ");
    scanf(" %[^\n]s",&Name);

    printf("Enter The Email: ");
    scanf("%s",&Email);

    printf("Enter The Phone: ");
    scanf("%s",&Phone);

    printf("Number of courses: ");
    scanf("%d",&NumberOfCourses);
    itoa(NumberOfCourses,NumberOfCoursesStr,10);

    NewStudent[0] = 0;
    strcat(NewStudent,IDStr);
    strcat(NewStudent,"|");
    strcat(NewStudent,Name);
    strcat(NewStudent,"|");
    strcat(NewStudent,Email);
    strcat(NewStudent,"|");
    strcat(NewStudent,Phone);
    strcat(NewStudent,"|");
    strcat(NewStudent,NumberOfCoursesStr);
    strcat(NewStudent,"\n");

    for(i=0;i<NumberOfCourses;i++){
        printf("Enter Course %d The Code: ",i+1);
        scanf(" %[^\n]s",&CourseCode);

        printf("Enter Course %d The Name: ",i+1);
        scanf(" %[^\n]s",&CourseName);

        StudentCourses[0] = 0;
        strcat(StudentCourses,IDStr);
        strcat(StudentCourses,"|");
        strcat(StudentCourses,CourseCode);
        strcat(StudentCourses,"|");
        strcat(StudentCourses,CourseName);
        strcat(StudentCourses,"\n");
    }
    FILE *AllStudents;
    FILE *AllCourses;

    AllStudents = fopen("data/All-Students.txt","a");
    fprintf(AllStudents,NewStudent);
    fclose(AllStudents);

    AllCourses  = fopen("data/All-Courses.txt","a");
    fprintf(AllCourses,StudentCourses);
    fclose(AllCourses);

    printf("Student Added Success\n");
}

void ShowAllStudents(){
    system("cls");

    printf("\n\t\t **** All Students ****\n\n");
    printf("|==========|====================|====================|==============================|=============|\n");
    printf("|    ID    |        Name        |    Phone Number    |          Email               |  NO.Course  |\n");
    printf("|==========|====================|====================|==============================|=============|\n");

    FILE *AllStudents;
    AllStudents = fopen("data/All-Students.txt","r");

    LineLenth = 200;
    char Student[LineLenth];

    while(fgets(Student,LineLenth,AllStudents)){
        printf("|");
        int TotalSpace = 10;
        int j;
        int Pipe = 0;
        for(i=0;i<strlen(Student)-1;i++){
            if(Student[i] == '|'){
                Pipe++;
                for(j=0;j<TotalSpace;j++){
                    printf(" ");
                }
                printf("|");
                if(Pipe == 1 || Pipe == 2){
                    TotalSpace = 20;
                }else if(Pipe == 3){
                    TotalSpace = 30;
                }else if(Pipe == 4){
                    TotalSpace = 13;
                }
            }else{
                printf("%c",Student[i]);
                TotalSpace--;
            }
        }
        for(j=1; j<=TotalSpace;j++){
            printf(" ");
        }
        printf("|\n");
        printf("|----------|--------------------|--------------------|------------------------------|-------------|\n");
    }
    fclose(AllStudents);
}

int SearchStudent(char StudentID[10]){
    printf("%s",StudentID);
    return 1;
}

void EditStudent(int StudentId){
    printf("EditStudent");
}

void DeleteStudent(int StudentId){
    printf("EditStudent");
}

bool IsAlreadyExists(char *GivenLine[30],char InfoType){
    return 1;
}

void ErrorAndRestart(char *Error[100]){
    printf("ErrorAndRestart");
}

void UserGuideline(){
    printf("UserGuideline");
}

void AboutUs(){
    printf("AboutUs");
}















