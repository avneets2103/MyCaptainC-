#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;
int main()
{
    FILE *p, *t;
    char another, choice;

    struct student
    {
        char first_name[50], last_name[50];
        char course[100];
        int section;
    };

    struct student std1;
    char xfirst_name[50], xlast_name[50];
    long int recsize;

    p=fopen("users.txt","rb+");

    if (p == NULL)
    {
        p = fopen("users.txt","wb+");

        if (p==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }


    recsize = sizeof(std1);

    while(1)
    {
        system("cls");

        cout << "                                 STUDENT DATABASE MANAGEMENT SYSTEM";
        cout <<endl<< "1. Add Records";
        cout <<endl<<"2. List Records";
        cout <<endl<<"3. Modify Records";
        cout <<endl<<"4. Delete Records";
        cout <<endl<<"5. Exit Program";
        cout <<endl<<endl;
        cout <<"Select Your Choice :";
        fflush(stdin);
        choice = getche();
        switch(choice)
        {
        case '1' :
            fseek(p,0,SEEK_END);
            another ='Y';
            while(another == 'Y' || another == 'y')
            {
                system("cls");
                cout << "Enter Firt Name : ";
                cin >> std1.first_name;
                cout << "Enter Last Name : ";
                cin >> std1.last_name;
                cout << "Enter Course    : ";
                cin >> std1.course;
                cout << "Enter Section   : ";
                cin >> std1.section;
                fwrite(&std1,recsize,1,p);
                cout <<endl<<"Add Another Record (Y/N)?";
                fflush(stdin);
                another = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(p);
            cout <<endl;
            while (fread(&std1,recsize,1,p) == 1)
            {
                cout <<"\n" << std1.first_name << setw(10)  << std1.last_name;
                cout <<"\n" <<std1.course <<  setw(8)  << std1.section;
            }
            system("pause");
            break;

        case '3' :
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the student : ";
                cin >> xlast_name;

                rewind(p);
                while (fread(&std1,recsize,1,p) == 1)
                {
                    if (strcmp(std1.last_name,xlast_name) == 0)
                    {
                        cout << "Enter new Firt Name : ";
                        cin >> std1.first_name;
                        cout << "Enter new Last Name : ";
                        cin >> std1.last_name;
                        cout << "Enter new Course    : ";
                        cin >> std1.course;
                        cout << "Enter new Section   : ";
                        cin >> std1.section;
                        fseek(p, - recsize, SEEK_CUR);
                        fwrite(&std1,recsize,1,p);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }
            break;


        case '4':
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the student to delete : ";
                cin >> xlast_name;

                t = fopen("temp.dat", "wb");

                rewind(p);
                while (fread (&std1, recsize,1,p) == 1)

                    if (strcmp(std1.last_name,xlast_name) != 0)
                    {
                        fwrite(&std1,recsize,1,t);
                    }
                fclose(p);
                fclose(t);
                remove("users.txt");
                rename("temp.dat","users.txt");

                p=fopen("users.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }

            break;

        case '5':
            fclose(p);
            cout <<endl<<endl<<"THANK YOU FOR USING THIS SOFTWARE";
            exit(0);
        }
    }
}    