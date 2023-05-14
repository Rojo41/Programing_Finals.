#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

typedef struct student
{
    long int IDno;  //student.IDno
    char name[20];  //student.name
    struct subject  //student.sub
    {
        char sname;
        int grade;  //student.sub.grade
    } sub[7];       //student.sub
    int total;      //student.total
    float average;  //student.average
} student;
//function Prototypes
void create();
void display();
void deleterec();
void search();
void update();
void studentsearch();
void Changepass();
void SelTeacher();
void Register();
void Login();
void Selection();
void Forgot();
int main(){

    int sel;
    do{
        printf("[1]Student\n");
        printf("[2]Teacher\n");
        printf("[0]Exit\n");
        printf("Are you a?:");
        scanf("%d", &sel);
        system("cls");

        switch(sel){

    case 1:
        studentsearch();
        sleep(2);
    break;
    case 2:
        Selection();
        break;
        case 0:
            printf("Exiting the Program");
            exit(0);
            break;
        default:
            printf("Invalid Selection!\n");
            sleep(2);
            return main();
    }
    }
    while(sel != 0);

    return 0;
}
void create(){

    FILE *fp;
    //and FILE gideclare as *fp
    student *s;
    //ang student gideclare as *s
    //ang student kay ang name sa struct sa babaw
    int n, i, j;
    printf("How many Students: ");
    scanf("%d", &n);
    s = (student*)calloc(n, sizeof(student));
    // ang s gi assign kung kapila sya tawagon
    fp = fopen("studentdata.txt", "w");
    //ang fp gi declare as file open sa studentdata.txt nga file gamit ang write append mode
    //append meaning musumpay sya sa file nga studentdata.txt
    //example: n = 1
    for(i = 0; i < n; i++)
    {
        //loop kung pila kabouk students
        s[i].total = 0;
        //s[i].total = total nga naa sa struct sa babaw
        s[i].average = 0;
        //s[i].average = average nga naa sa struct sa babaw
        printf("Enter the Student ID: ");
        scanf("%ld", &s[i]);
        //s[i] kay silbi mao nani ilang ID number
        fflush(stdin);
        //gigamit ang fflsuh para ma erase ang buffer sa gi enter nga student id
        printf("Enter Name: ");
        scanf("%[^\n]s", s[i].name);
        //kwaon ang name sa student except sa newline
        printf("Subject 1: Math\nSubject 2: English\nSubject 3: Science\nSubject 4: Filipino\nSubject 5: TLE\nSubject 6: PE\nSubject 7: AP\n");
        for(j = 0; j < 7; j++)
        {
            //loop para sa mga subjects
            printf("Enter the grade in Subject %d: ", j + 1);

            scanf("%d", &s[i].sub[j].grade);
            //s[1].sub[0].grade = grade sa student 1 sa iyang subject 0.
            s[i].total += s[i].sub[j].grade;
            //total equals to total plus grade
        }
        s[i].average = s[i].total / 7.0;
        //average equals to ang total sa kung pila ang grade sa tanan subject tas e devide kung pila kabouk subjects
        fwrite(&s[i], sizeof(student),1,fp);
        //ebutang ang record sa s[1] or sa student 1 sa file nga fp, fp = studentdata.txt
        //ebutang ang record padulong sa file in binary form
    }
    fclose(fp);
    //closed the file
}
void display(){


    student s1;
    //declared student as s1
    FILE *fp;
    int j;
    fp = fopen("studentdata.txt","r");
    //gi open ang file in read mode
    while(fread(&s1, sizeof(student),1,fp))
    {
        //read file in binary file and display it in readable
        printf("\n%-5ld\t%-20s\t",s1.IDno,s1.name);
        //ang kanang -5 og -20 kay mao na sya ang width or space sa ID or name
        for(j = 0; j<7; j++)
        {
            //loop para ma display ang grade sa students
            printf("\t%4d",s1.sub[j].grade);
        }
        //eprint ang average sa students grade pag ka human sa loop
        printf("\t%7.2f",s1.average);
    }
    fclose(fp);
    //close ang file
}
void deleterec(){
    student s1;
    //edeclare ang student as s1
    FILE *fp, *fp1;
    int j, ID,result = 0;
    fp = fopen("studentdata.txt","r");
    //fp open the file studentdata.txt in read mode
    fp1 = fopen("temprecord.txt", "w");
    //fp open the file temprecord.txt in write mode
    printf("Enter the Student Id to Delete: ");
    scanf("%d", &ID);
    while(fread(&s1, sizeof(student),1,fp))
    {
        //read every id of fp or studentdata.txt
        if(s1.IDno == ID)
        {
            //kung ang ID kay nag match sa s1.IDno tas tas ang result mag equal to 1 tas dili na sya ebalhin sa temprecord.txt
            result = 1;

        }else{
        fwrite(&s1, sizeof(student), 1, fp1);
        //ebalhin ang student record nga wala nag match sa Id nga gi enter sa user
        }
    }
    fclose(fp);
    fclose(fp1);
    //close ang file
    if(result  == 1)
    {

        fp1 = fopen("temprecord.txt", "r");
        // fp1 eopen ang file nga temprecord.txt in read mode
        fp = fopen("studentdata.txt", "w");
        // fp eopen ang file nga studentdata.txt in write mode
        printf("Deleted Successfuly");
        while(fread(&s1, sizeof(student), 1, fp1))
        {
            //ebalhin sa fp1 or temprecord.txt sa fp or studentrecord.txt
            fwrite(&s1, sizeof(student), 1, fp);
        }
        fclose(fp);
        fclose(fp1);

    }
    else
    {
        //kung wala nag match ang ID nga gienter sa user sa mga ID nga na sa sulod sa file
        printf("Student ID does Not Exist!\n");
    }

}
void search(){

    student s1;
    FILE *fp;
    int j, ID,result = 0;
    fp = fopen("studentdata.txt","r");
    //fp eopen ang studentdata.txt in read mode
    printf("Enter the Student Id to search: ");
    scanf("%d", &ID);

    while(fread(&s1, sizeof(student),1,fp))
    {
        if(s1.IDno == ID)
            //if nag match ang ID nga gienter sa user og sa ID sa mga student nga naa sa file

            //edisplay ang records sa student
        {
             printf("\n---------------------------------------------------------------------------------\n");
    printf("   ID              Name                          Math\t Eng\t Sci\t Fil\t TLE\t PE\t AP\t  GPA");
    printf("\n---------------------------------------------------------------------------------\n");
    //ang resut mahimong equals to 1 KUNG ANG mga ID nga naa sa file kay naay kaparehas sa ID nga gi search
            result = 1;
            printf("\n%-5d\t%-20s\t",s1.IDno,s1.name);
            //siplay ang ID number of name sa student
            for(j = 0; j<7; j++)
            {
                //loop aron madisplay kung pila kabouk ang subject of grades
                printf("\t%4d",s1.sub[j].grade);
            }
            printf("\t%7.2f",s1.average);
            printf("\n\n======================================End===========================================\n");
        }
    }
    if(result != 1)
        //kung ang result kay equal to 0
    {
        printf("Student ID does Not Exist!\n");
    }
    fclose(fp);
}
void update(){

    student s1;
    FILE *fp, *fp1;
    int j, ID,result = 0;
    fp = fopen("studentdata.txt","r");
    //fp eopen ang studentdata.txt in read mode
    fp1 = fopen("temprecord.txt", "w");
    //fp1 eopen ang temprecord.txt in write mode
    printf("Enter the Student ID to Update: ");
    scanf("%d", &ID);
    //ibutang ang ID sa student nga esearch
    while(fread(&s1, sizeof(student),1,fp))
    //mag run ang while nga loop samtang naa pay sulod ang file nga fp kung wala nay sulod ang fp or studentdata.txt automatic ma 0 ang fp nga naa sa fread
    {
        if(s1.IDno == ID)
        //kung ang ID kay naa kaparehas sa mga ID nga naa sa file
        {
            s1.total = 0;
            //student.total = 0
            result = 1;
            // ang result ma himong 1
            fflush(stdin);
            //fflush para ma back to 0 to ang nabilin nga new line sa scanf sa ID tas para dili ma direct sa pag input og grade og pwede paka maka inout og name
            printf("Enter New Name of the student: ");
            scanf("%[^\n]s", s1.name);
            //scanf syag mga character exept sa newline or \n
            printf("Subject 1: Math\nSubject 2: English\nSubject 3: Science\nSubject 4: Filipino\nSubject 5: TLE\nSubject 6: PE\nSubject 7: AP\n");
            for(j = 0; j < 7; j++)
            {
                //loop kung pila kabouk sujects
                printf("Enter the New grade in Subject %d: ", j + 1);
                scanf("%d", &s1.sub[j].grade);
                //student.sub.grade sa struct naa sa babaw
                s1.total += s1.sub[j].grade;
                //student.total = student.total + student.sub.grade
            }
            s1.average = s1.total / 7.0;
            //student.grade = student.total devide 7 subjects
        }
        fwrite(&s1, sizeof(student), 1, fp1);
        //ibutang sad tong mga na update ganina sa temporary nga file or sa temprecord.txt kung naay kaparehas ang ID nga gi search para maupdate sa mga ID sa studentdata.txt
        //ibalhin tong sulod sa studentdata.txt nga file sa temprecord.txt nga file
    }
    fclose(fp);
    fclose(fp1);
    if(result  == 1)
        //kung ang result nahimong 1 mag run ni nga condition
    {
        //diri kabaliktaran ato ganina katong naa sa babaw, ang e read napud nato kay ang temprecord.txt tas ang write napud tong sa studentdata.txt
        fp1 = fopen("temprecord.txt", "r");
        fp = fopen("studentdata.txt", "w");

        while(fread(&s1, sizeof(student), 1, fp1))
        {
            //ipangbalhin tong naa sa temprecord.txt padulong sa studentdata.txt
            fwrite(&s1, sizeof(student), 1, fp);
        }
        fclose(fp);
        fclose(fp1);
        //close tanan file

    }
    else
    {
        //kung walay kaparehas og ID
        printf("Student ID does Not Exist!\n");
    }

}
void studentsearch(){

    student s1;
    //declare tong student struct as s1
    FILE *fp;
    //File as fp
    int j, ID,result;
    fp = fopen("studentdata.txt","r");
    //eopen ang studentdata.txt in read mode
    printf("==Using as Student==\n");
    printf("Enter your ID(-1 to back): ");
    scanf("%d", &ID);
    if(ID == -1){
        //kung -1 ilang ibutang ibalik niya sa main nga function
        system("cls");
    //eclear ang screen
        main();
    }
    while(fread(&s1, sizeof(student),1,fp))
    {
        if(s1.IDno == ID)
        //kung naa kaparehas og ID sa file ang gienter nga ID sa student
        {
    printf("\n---------------------------------------------------------------------------------------------------------------------\n");
    printf("\n   ID              Name                          Math\t Eng\t Sci\t Fil\t TLE\t PE\t AP\t GPA");
    printf("\n---------------------------------------------------------------------------------------------------------------------\n");
            result = 1;
            //ang result kay mahimong 1
            printf("\n%-5d\t%-20s\t",s1.IDno,s1.name);
            //kanang mga number nga after sa % kay mao na sya ang ilang spacing, sa name of sa ID

            for(j = 0; j<7; j++)
            {
                //loop kung pila kabouk subject
                printf("\t%4d",s1.sub[j].grade);
                //kanang number kay spacing gyapon na nila
            }
            printf("\t%.2f",s1.average);
            printf("\n\n================================================End==============================================================\n");
        }
    }
    if(result != 1)
    {
        //kung walay kaparehas og ID sa file sa ID nga gi input sa student
        printf("Student ID does Not Exist!\n");
    }
    fclose(fp);
}
void Changepass(){
 FILE *fp, *fp1;
 //eopen ang Username.txt in read mode kay didto nato echeck kung naa ba syay kaparehas og username sa username nga gi input sa user
    fp = fopen("Usernamepassword.txt", "r");
    fp1 = fopen("tempuser.txt", "w");
    //eopen nag tempuser.txt in write mode kay didto nat temporary ibalhin ang mga username og password aron ma ilisan nato og password
    char user[20], pass[20], username[20], password[20];
    int result = 0;
    printf("\n====Change Password====");
    //user input
    printf("\nEnter your Username: ");
    scanf("%s", user);
    while(fscanf(fp,"%s %s", username, password) != EOF){
            //mag run ang while samtang wala pa nag End of file or nahuman na tanan og scan ang file
        if(strcmp(user, username) == 0){
            //gi compare ang username nga gi input sa user og mga user name nga naa sa file
            //kung tama ang conditon mag kuha syag new password sa user
            printf("Enter your New Password: ");
            scanf("%s", pass);
            result = 1;
            fprintf(fp1,"%s %s", user, pass); //ibutang nato sa fp1 or sa tempuser.txt ang username og ang updated nga password
        }else{
            //kung mali ang condition ibalhin n-niya diritso ang username og password nga daan
            fprintf(fp1,"%s %s", username, password);
        }
    }
    fclose(fp1);
    fclose(fp);
    // close ang file

    fp = fopen("Usernamepassword.txt", "w");
    fp1 = fopen("tempuser.txt", "r");
    //eopen ang file kabaliktaran ganina kay eread nato ang tempuser.txt tas ipang balhin nato sa usernamepassword.txt
    if(result == 1){
        while(fscanf(fp1,"%s %s", username, password) != EOF){
                //mag run ang while samtang dili pa end of file
            fprintf(fp,"%s %s", username, password);// ibalhin ang katong naa sa tempuser.txt nga file padulong sa usernamepassword.txt

        }
        printf("Password Successfully Changed!");
    }else{
        //kung wala nameet ang condtion
        printf("User not Found!\n");
    }
    fclose(fp);
    fclose(fp1);
}
void SelTeacher(){
    int choice;
  do
    {
        //mag run ni samtang dili 0 ang input sa user
        printf("[1]ADD A STUDENT RECORD\n");
        printf("[2]DISPLAY ALL STUDENT RECORD\n");
        printf("[3]DELETE A STUDENT RECORD\n");
        printf("[4]SEARCH A STUDENT RECORD\n");
        printf("[5]UPDATE A STUDENT RECORD\n");
        printf("[6]CHANGE PASSWORD\n");
        printf("[7]LOG OUT\n");
        printf("[0]EXIT\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        system("cls");
        switch(choice)
        {
        case 1:
            create();
            break;
        case 2:
            printf("\n=================================Students Data===========================================\n");
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            printf("\n   ID              Name                          Math\t Eng\t Sci\t Fil\t Tle\t PE\t AP\t GPA");
            printf("\n-----------------------------------------------------------------------------------------------------------------\n");
            display();
            //run ang display function
            printf("\n\n======================================End================================================\n");
            sleep(3);
            break;
        case 3:
            deleterec();
            //run ang deleterec nga function
            break;
        case 4:
            search();
            //run ang search nga function
            break;
        case 5:
            update();
            //run ang update nga function
            break;
        case 6:
            Changepass();
            break;
        case 7:
            Selection();
            //run ang selection nga function
            break;
        case 0:
            printf("Exiting the program");
            exit(0);
            //exit ang program
            break;
        default:
            printf("Invalid Choice!, Please Try Agian!");
            sleep(2);

        }
    }


    while(choice != 0);
}
void Register(){
    FILE *fp;
    fp = fopen("Usernamepassword.txt","a+");
    //eopen ang Usernamepassword.txt in append mode tas kanang + kay aron pwede pud ta maka read sa file
    char user[20], pass[20], username[20], password[20];
    int result = 0;
    printf("\nEnter Username: ");
    scanf("%s", user);
    printf("Enter Password: ");
    scanf("%s", pass);
    //kwaon ang input sa user
    while(fscanf(fp,"%s %s", username, password) != EOF){
            //fscanf kay echeck niyang ang sulod sa file every space
            //first word kay username tas space mao to ang password
            //mag run ang while samtang dili pa End of File or dili pa mahuman og scan ang file
        if (strcmp(user, username) == 0){
            //ecompare  ang username nga input sa user og ang mga username nga naa sa file
            result = 1;
        }
    }if(result == 1){
        //kung ang result nahimong 1 meaning naa syay kaparehas og username sa file
        printf("\nUsername already Taken, Please try Again");
        sleep(2);
        system("cls");
        //clear ang screen
    }else{
            fprintf(fp,"\n%s %s", &user, &pass);
            //gibutangan of \n para dili mag sumpay2
            //ibutang niya sa file ang username og password sa user nga nag register,
            printf("\nRegister Successfully\n");
        }

    fclose(fp);
}
void Login(){
    FILE *fp;
    fp = fopen("Usernamepassword.txt","r");
    //open ang file in read mode ra kay igo ramn nato basahon ang file
    char user[20], pass[20], username[20], password[20];
    int result = 0;
    //iput sa user
    printf("\nEnter your Username: ");
    scanf("%s", user);
    printf("Enter your Password: ");
    scanf("%s", pass);
     while(fscanf(fp,"%s %s", username, password) != EOF){
            //mag run ang while samtang dili pa End of File or dili pa ma 0 ang file
        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0){
            //compare ang username og ang password sa file og sa username og password nga gi input sa user
            result = 1;
            //ang result kay mahimong 1 kung na meet ang conditions
        }
     }
        if(result == 1){
                //kung tama ang username og password or kung naa sa file ang username og password nga gi input sa user
        printf("\n\nPlease Wait a moment...");
        sleep(2);
        //sleep sya og 2 seconds
        system("cls");
        //tawagon niya ang SelTeacher nga function
        SelTeacher();
    }else{
        //kung naay mali sa username or sa password

            printf("\nInvalid Username or Password, Please Try again!");
            sleep(2);
            system("cls");
            //clear ang screen
        }

    fclose(fp);
}
void Forgot(){
    //same ranig comments sa changepass nga function!
    FILE *fp, *fp1;
    fp = fopen("Usernamepassword.txt", "r");
    fp1 = fopen("tempuser.txt", "w");
    char user[20], pass[20], username[20], password[20];
    int result = 0;
    printf("\n====Forgot Password====");
    printf("\nEnter your Username: ");
    scanf("%s", user);
    while(fscanf(fp,"%s %s", username, password) != EOF){
        if(strcmp(user, username) == 0){
            printf("Enter your New Password: ");
            scanf("%s", pass);
            result = 1;
            fprintf(fp1,"%s %s\n", user, pass);
        }else{
            fprintf(fp1,"%s %s\n", username, password);
        }
    }
    fclose(fp1);
    fclose(fp);

    fp = fopen("Usernamepassword.txt", "w");
    fp1 = fopen("tempuser.txt", "r");
    if(result == 1){
        while(fscanf(fp1,"%s %s", username, password) != EOF){
            fprintf(fp,"%s %s\n", username, password);

        }
        printf("\nPassword Successfully Changed!\n");
    }else{
        printf("User not Found!\n");
    }
    fclose(fp);
    fclose(fp1);
}
void Selection(){
    int ch;
    do{
            //mag run samtang dili 0 or 3(back) ang gi input sa user
        printf("[1]Register\n[2]Log in\n[3]Forgot Password\n[4]Back\n[0]Exit");
        printf("\nSelect your choice: ");
        scanf("%d", &ch);

        switch(ch){
    case 1:
        //tawagon ang Register nga function
        Register();
        break;
    case 2:
        //tawagon ang LOg in nga function
        Login();
        break;
    case 3:
        Forgot();
        break;
    case 4:
        system("cls");
        //balik sa main nga function
        main();
        break;
    case 0:
        printf("Exiting The Program!");
    default:
        printf("\nInvalid Selection!");
        }
    }while(ch != 0);

    getch();
}
