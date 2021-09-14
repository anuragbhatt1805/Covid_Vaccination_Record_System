#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

    /*GLOBAL DECLERATION OF STRUCTURE FOR BENEFICIERY & NO OF BENEFICIERY*/
struct Beneficiery
{
    /*structure to store details of all beneficiery who have registered for vaccination.*/
    char Ref_Id[11], Name[30], Password[12], Vaccine[3][12];
    int Age, status;
} Reg[1500];
int No_Reg = 0;     /*No of beneficiary registered (acccess for "struct Beneficiery")*/

    /*GLOBAL DECLERATION OF STRUCTURE FOR VACCINATED_BENEFICIERY & NO OF VACCINATED_BENEFICIERY*/
struct Vaccinated_Beneficiery
{
    /*structure to store beneficiery details who got vaccinated or have booked slot for getting vaccination.*/
    char Ref_Id[11], Name[30], Vaccine[12];
    int slot, Price;
} VacBen[1500];
int No_VacBen = 0;  /*No of vaccinated beneficiary (access for "struct Vaccinated_Beneficiery")*/

    /*GLOBAL DECLARATION OF FUNCTIONS*/
void Generate_Password(char *password);
int Registration();
int Login_Account();
int Slot_Booking(char*, int);
int Vaccinated();


int main()
{
    printf("\t\t===============================================\n");
    printf("\t\t\\\\🩺\\\\💉COVID VACCINATION RECORD SYSTEM💉//🩺//\n");
    while (1)
    {
                    /*Displays Main Menu For Beneficiery*/
        printf("___________________________________________________________________\n");
        printf("\n\
        t😉|:| MAIN MENU |:|😉\n");
        printf("=========================================");
        printf("\n| 1. | New Registration For Vaccination\t|");
        printf("\n-----------------------------------------");
        printf("\n| 2. | Login to Beneficiery Account\t|");
        printf("\n-----------------------------------------");
        printf("\n| 3. | Getting Vaccinated\t\t|");
        printf("\n-----------------------------------------");
        printf("\n| 4. | Exit😥😥😥\t\t\t|");
        printf("\n=========================================");
        printf("\nEnter a Valid Option from above 🙄 : ");
        fflush(stdin);
        switch (getchar())  /*Accepts Integer Input from the user and directly uses it in switch statement*/
        {
            case '1':
                    /*Jump to Registration() Function*/
                Registration();
                break;
            
            case '2':
                    /*Jump to Login_Account() Function*/
                Login_Account();
                break;
            
            case '3':
                    /*Jump to Vaccinated() Function*/
                Vaccinated();
                break;
            
            case '4':
                    /*Exit the program*/
                printf("\n😀😀😀 Thanks For using offline Covid Vaccination Record System 😀😀😀");
                printf("\n\t\t\t\t\t\tBy~ Simple Coders😪🥱😴\n");
                return 0;

            default:
                    /*for invalid inputs*/
                printf("\nInvalid Operation 🤦‍♂️🤦‍♀️\n Please Choose from Valid Function\n");
        }
    }
}

int Registration()
{
    /*registration of new beneficiery*/
    char USN[11], Name[30], Pswd[12];
    int YoB, Age, i, Cur_Year, Aadhaar[12];
    long Year_Var;

    printf("___________________________________________________________________\n");
    printf("\n\t_____🧾REGISTRATION PORTAL🧾______\n");
    printf("\nEnter USN as Refernce ID: ");
    fflush(stdin);
    for(i = 0; i < 10; scanf("%c", &USN[i++]));
    USN[10] = '\0'; /*accepts USN to compare whether it exists in Beneficiery structure(Ref_Id) */
    for (i = 0; i <= No_Reg; i++)
        if (!(strcmp(USN, Reg[i].Ref_Id)))
        {
            /*If USN already exists Beneficiery structure(Ref_Id)*/
            printf("USN Already Exist😂🤣...\nUse Login Page to Login to your Account.\n");
            Login_Account(); /*jumps to login Account() only for existing users*/
            return 0;
        }
    
    printf("Enter Name of Beneficinery: ");
    fflush(stdin);
    gets(Name);     /*stores beneficiery's name*/

    printf("Enter Your Year of Birth: ");
    scanf("%d", &YoB);      /*stores beneficiery's year of birth*/
    fflush(stdin);
    Year_Var = time(NULL);
    Cur_Year = localtime(&Year_Var)->tm_year + 1900;    /*Calculates the current year From the system*/
    Age = Cur_Year-YoB;     /*Age is calculated from YOB and current year*/
    if (Age < 12)
    {
            /*For Age under 12 */
        printf("%s is under 12;\n\tBenificiary is uneligible for any vaccine.\n", Name);
        return 0;
    } else if (Age >= 12 && Age < 18)
    {
            /*for Age between 12 to 17*/
        printf("%s is eligible for Sputnik-V single dose vaccine.\n", Name);
        strcpy(Reg[No_Reg].Vaccine[0], "Sputnik-V");
        strcpy(Reg[No_Reg].Vaccine[1], "\0");
        strcpy(Reg[No_Reg].Vaccine[2], "\0");
    } else if (Age >= 18 && Age < 45)
    {
            /*for Age between 18 to 44*/
        printf("%s is eligible for Sputnik-V single dose & Covishield double dose vaccine\n", Name);
        strcpy(Reg[No_Reg].Vaccine[0], "Sputnik-V");
        strcpy(Reg[No_Reg].Vaccine[1], "Covishield");
        strcpy(Reg[No_Reg].Vaccine[2], "\0");
    } else
    {
            /*for Age above 44*/
        printf("%s is eligible for all available vaccine\n", Name);
        strcpy(Reg[No_Reg].Vaccine[0], "Sputnik-V");
        strcpy(Reg[No_Reg].Vaccine[1], "Covishield");
        strcpy(Reg[No_Reg].Vaccine[2], "Covaxin");
    }

        /*for age above 12 and valid USN data of the beneficery is stored in structure "beneficery"*/
    strcpy(Reg[No_Reg].Ref_Id, USN);
    strcpy(Reg[No_Reg].Name, Name);
    Reg[No_Reg].Age = Age;
    Reg[No_Reg].status = 0;

        /*Accept or generates a valid password*/
    printf("Enter Password for the account (password must have 6 to 12 characters only): ");
    fflush(stdin);
    scanf("%s", &Pswd);
    if (strlen(Pswd) > 12 || strlen(Pswd) < 6 || Pswd[0] == '\n')
    {
        /*ONLY In case of Invalid Password*/
        printf("Not a Valid Password...System would assign you a password\n");
        Generate_Password(Pswd);        /*Jump to Generate_Password() function*/
        printf("System Generated Password: %s", Pswd);
    }
    strcpy(Reg[No_Reg].Password, Pswd); /*Stores in structure "beneficery"*/
    printf("\n%s, You have been successfully registered for vaccination😊😊", Name);
    printf("\n====================================================================\n");
    No_Reg++; /*Increment No of Registered Beneficiery by 1*/
    return 0;
}

int Login_Account()
{
    /*Access of existing beneficery details for slot booking and certificates*/
    char USN[11], Pswd[12];
    int i, m = -1;

    printf("___________________________________________________________________\n");
    printf("\n\t_____📑LOGIN PORTAL📑______\n");
    printf("\nEnter Refernce ID: ");
    fflush(stdin);
    for(i = 0; i < 10; scanf("%c", &USN[i++]));
    USN[10] = '\0';    /*accepts USN to compare whether it exists in Beneficiery structure(Ref_Id) */
    for (i = 0; i <= No_Reg; i++)
        if (!(strcmp(USN, Reg[i].Ref_Id)))
        {
            /*If USN already exists Beneficiery structure(Ref_Id)*/
            m = i;
            break;
        }
    if (m == -1)
    {
        /*If USN doesn't exists in Beneficiery structure(Ref_Id)*/
        printf("\nNo such Refrence ID found...🤣🤣\nPlease register yourself first...\n\n");
        Registration();
        return 0;
    }
    printf("Enter Password: ");
    fflush(stdin);
    scanf("%s", &Pswd);     /*accepts password to compares with Beneficiery password */
    if (!(strcmp(Pswd, Reg[m].Password)))
    {
        /*If passowrd got verified*/
        while (1)
        {
            printf("\n==================================");
            printf("\n| 1. | Slot Booking⌚⌚\t\t|");
            printf("\n----------------------------------");
            printf("\n| 2. | Download Certificate📰📰\t |");
            printf("\n----------------------------------");
            printf("\n| 3. | Logout↩↩\t\t\t |");
            printf("\n==================================");
            printf("\nEnter you choice: ");
            fflush(stdin);
            switch (getchar())  /*Accepts Integer Input from the user and directly uses it in switch statement*/
            {
            case '1':
                    /*Jump to Slot_Booking() function*/
                Slot_Booking(USN, m);
                break;
            
            case '2':
                    /*Certificate related queries*/
                if (Reg[m].status == 2)
                    printf("\nYour Certificate has been downloaded📰📰");
                else
                    printf("\nYou are not vaccinated completely, you can't download the certificate😑😑");
                break;
            
            case '3':
                    /*Logout from the portal */
                printf("\nYou are getting logged out from this portal🤔🤔");
                printf("\n====================================================================\n");
                return 0;
            
            default:
                printf("\nInvalid Choice!! 🤦‍♂️🤦‍♀️");
            }
        }
    }
    else
    {
        printf("\n🤷🤷‍♂️Sorry, Your password was incorrect\n");
    }
    printf("\n====================================================================\n");
    return 0;
}

int Slot_Booking(char *USN, int m)
{
    /*Slot Booking for a beneficiery to get a desired vaccine*/
    int i, ch, n, price;
    printf("___________________________________________________________________\n");
    printf("\n\t_____🪑SLOT BOOKING PORTAL🪑______\n");
    if (Reg[m].status == 0)
    {
        /*For beneficiery with NIL dose of any vaccine*/
        n = No_VacBen;
        strcpy(VacBen[n].Ref_Id, Reg[m].Ref_Id);    /*Stores Ref_ID of Beneficiery in Structure 'Vaccinated_Beneficiery'*/
        strcpy(VacBen[n].Name, Reg[m].Name);        /*Stores Name of Beneficiery in Structure 'Vaccinated_Beneficiery'*/
        while (1)
        {
            for ( i = 0; i < 3; i++)
            {
                /*Print all vaccine suggested for beneficiery according to their age*/
                if (!(strcmp(Reg[m].Vaccine[i], "\0")))
                    break;
                printf("\n%d. %s Vaccine💉", i+1, Reg[m].Vaccine[i]);
            }
            
            printf("\nEnter the vaccine choice from above: ");
            fflush(stdin);
            scanf("%d", &ch); /*Enter the vaccine number choosen from above given option*/
            if (ch > 3 || ch < 1 || !(strcmp(Reg[m].Vaccine[ch-1], "\0")))
                printf("Invalid Choice...🤦‍♂️🤦‍♀️\nRe-nter the value: \n");
            else
            {
                /*After choosing valid number, Vaccine would be updated in Vaccinated_Beneficiery sturcture(Vaccine)*/
                strcpy(VacBen[n].Vaccine, Reg[m].Vaccine[ch-1]);
                break;
            }
        }
    }
    else if (Reg[m].status == 2)
    {
        /*For beneficiery who completed all dosage of vaccine*/
        printf("\nYou are fully vaccinated. Thanks for helping for safer side.🙏🙏");
        return 0;
    }
    
    for (i = 0; i <= No_VacBen; i++)
        if (!(strcmp(USN, VacBen[i].Ref_Id)))
        {
            /*Finding the beneficiery details in Beneficiery structure and returns its index value*/
            n = i;
            break;
        }
    printf("\n1. Free Vaccine\n2. Paid Vaccine");
    printf("\nEnter the cost which you would prefer for getting vaccinated (default is 'paid'): ");
    fflush(stdin);
    scanf("%d", &price);    /*mode of vaccine in terms of price*/
    if (price == 1)
    {
        /*For free vaccine*/
        VacBen[n].Price = 0;
        printf("\n%s, your free slot has been booked.\nYou have to pay %d at the time of Vaccination.\n", VacBen[n].Name, VacBen[n].Price);
    }
    else
    {   
        /*For paid Vaccine*/
        if (!(strcmp(VacBen[n].Vaccine, "Sputnik-V")))
            VacBen[n].Price = 1200;
        else if (!(strcmp(VacBen[n].Vaccine, "Covaxin")))
            VacBen[n].Price = 900;
        else
            VacBen[n].Price = 600;
        printf("%s, your paid slot has been booked.\nYou have to pay %d at the time of Vaccination.", VacBen[n].Name, VacBen[n].Price);
    }
    VacBen[n].slot = 1;     /*Slot booked for getting vaccination.*/
    printf("\n%s", VacBen[n].Vaccine);
    if (n == No_VacBen)
        No_VacBen++;        /*If its first dose of the beneficiery then no of Vaccinated Beneficiery would be increased by one*/
    return 0;
}

int Vaccinated()
{
    /*Vaccination portal for official use, at the place of vaccination*/
    char USN[11];
    int i, m = -1, n = -1;

    printf("___________________________________________________________________\n");
    printf("\n\t_____💉VACCINATION SLOT💉______\n");
    printf("\nEnter Refernce ID: ");
    fflush(stdin);
    for(i = 0; i < 10; scanf("%c", &USN[i++]));
    USN[10] = '\0';         /*accepts USN to compare whether it exists in Beneficiery structure(Ref_Id) */
    for (i = 0; i <= No_VacBen; i++)
        if (!(strcmp(USN, VacBen[i].Ref_Id)))
        {
            /*If USN already exists Vaccinated_Beneficiery structure(Ref_Id)*/
            if (VacBen[i].slot)
                m = i;
            break;
        }
    for (i = 0; i <= No_Reg; i++)
        if (!(strcmp(USN, Reg[i].Ref_Id)))
        {
            /*If USN already exists Beneficiery structure(Ref_Id)*/
            n = i;
            break;
        }
    if (m == -1)
    {
        /*If USN doesn't exists in Vaccinated_Beneficiery structure(Ref_Id)*/
        printf("\nSorry you haven't booked slot for getting vaccincated...\nPlease book a slot from login account:-\n");
        printf("\n====================================================================\n");
        Login_Account();
        return 0;
    }

    if (Reg[n].status == 2)
    {
        /*If Beneficiery is completely vaccinated*/
        printf("\nYou are fully vaccinated 🎉🎉. Thanks for helping for safer side😷😷");
    } else
    {
        if (VacBen[m].Price)
        {
            /*If Beneficiery has choosen paid vaccine*/
            printf("\nPress 'Enter' key after paying %0.2d💸💸:", VacBen[m].Price);
            fflush(stdin);
            getchar();
        }
        printf("\nPress 'Enter' key after getting vaccinated💉💉:");
        fflush(stdin);
        getchar();
        if (!(strcmp(VacBen[m].Vaccine, "Sputnik-V")))
        {
            /*for Beneficiery who opted "Sputnik-V" vaccine*/
            printf("\n%s you had taken your single dose of '%s'💉💉", VacBen[m].Name, VacBen[m].Vaccine);
            Reg[n].status = 2;  /*Status of Beneficiey is updated as fully vaccinated*/
        } else
        {
            if (Reg[n].status == 0)
            {
                /*If Beneficiery haven't taken a single dose of vaccine*/
                printf("\n%s you had taken your first dose of '%s'💉💉", VacBen[m].Name, VacBen[m].Vaccine);
                Reg[n].status = 1;      /*Status of Beneficiey is updated as partially vaccinated*/
                VacBen[m].slot = 0;     /*If Beneficiery has used the booked slot of vaccine, slot value would become '0'*/
            } else if (Reg[n].status == 1)
            {
                /*If Beneficiery is partially vaccinated*/
                printf("\n%s you have taken your second dose of '%s' also💉💉", VacBen[m].Name, VacBen[m].Vaccine);
                Reg[n].status = 2;      /*Status of Beneficiey is updated as completely vaccinated*/
            }
        }
    }
    printf("\nThanks for getting Vaccinated🤗🤗");
    printf("\n====================================================================\n");
    return 0;
}

void Generate_Password(char *password)
{
    /* Used to create Random Password of length '8', if user doesn't have any strong password */
	int i;
    char Character[] = "@#$%&";
    srand(time(0));
    for (i = 0; i < 8; i++)
    {
        switch ((rand() % 4))
        {
        case 0:
            *(password + i) = (char)((rand() % 10) + 48);
                /*  Give character of digits from 0 to 9  */
            continue;

        case 1:
            *(password + i) = (char)((rand() % 26) + 97);
                /*  Give character of uppercase alphabet  */
            continue;

        case 2:
            *(password + i) = (char)((rand() % 26) + 65);
                /*  Give character of lowercase alphabet  */
            continue;

        case 3:
            *(password + i) = Character[rand() % 5];
                /*  Give character of symbols  */
            continue;
        }
    }
    *(password + 8) = '\0';
}