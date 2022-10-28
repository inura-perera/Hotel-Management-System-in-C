#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define MAX 256

struct customerInfo{

    int roomNo;
    char firstName[20];
    char lastName[20];
    char phn[15];
    char adress[30];
    int noPer; //Number of persons staying
    int checkInDate;
    int checkInMon;
    int checkInYear;
    int checkOutDate;

}CI[20];

struct roomInfo{

    int roomNo ;
    char *type[10];
    int bed;
    int ac;
    int rate ;
    int avail;

}RI[10];

void bookings(void);
void header(void);
void createAccount(void);
void deleteAccount(void);
void roomInfo(void);
void checkRoomInfo(void);
int  login(char *filename) ;
void updateRate(void);
void manager(void);
void reception(void);
void checkIn(void);
void checkOut(void);
int mobileNumberCheck(char*contact);
char nameCheck(char*name);


int main() {

    system("cls");
 	printf("\t\t*******************************************************************************\n");
	printf("\t\t*                                                                             *\n");
	printf("\t\t*                                                                             *\n");
	printf("\t\t*                         ---------------------------                         *\n");
	printf("\t\t*                           HOTEL MANAGEMENT SYSTEM                           *\n");
	printf("\t\t*                         ---------------------------                         *\n");
	printf("\t\t*                                                                             *\n");
	printf("\t\t*                                                                             *\n");
	printf("\t\t*                                                                             *\n");
	printf("\t\t*******************************************************************************\n\n\n");

    printf(" \n ENTER ANY KEY TO CONTINUE ");

	getch();

    roomInfo();

	int selection1=0;
	int selection2;
	int errorLoop=0;
	int result=0 ;
	char *loginFile[2] ;


	do {
            while(errorLoop!=1){

		system("cls");
        header();


		printf(" \n                       (1) LOGIN AS THE MANAGER");
        printf(" \n                       (2) LOGIN AS A RECEPTIONIST");
        printf(" \n                       (3) EXIT");
        printf(" \n\n\n\n\n\n\n\n\n\n ENTER YOUR SELECTION : ");
        scanf("%d",&selection1);

		if (selection1==1) {
            errorLoop=1;
			loginFile[1]="manager.txt";
		} else if (selection1==2) {
		    errorLoop=1;
			loginFile[1]="login.txt";
		}else if (selection1==3){
		    errorLoop=1;
            exit(0);
		}else{
            errorLoop=2;
            printf(" INVALID SELECTION ENTER ANY KEY TO RETRY\n\n\n");
            getch();
		}
            }

		result = login(loginFile[1]);

		if (result==1) {
			break;
		} else if (result==0) {
			printf("\n");
			printf("\n");
			printf("\t\t                     ENTER 1 TO TRY AGAIN .\n\n" );
			printf("\t\t                     ENTER 2 TO EXIT PROGRAM .\n\n" );
			printf("\t\t\n\n\nENTER YOUR SELECTION : " );
			scanf("%d",&selection2);

			if (selection2==2) {
				printf("\n");
				printf("\n");
				printf("\t\t\t\t\tPROGRAM CLOSING." );
				Sleep(1000);
				printf("." );
				Sleep(1000);
				printf("." );
				Sleep(1000);
				printf("." );
				printf("\n\n\t\t\t\t\tPROGRAM CLOSED.");
				exit(0);
			}
		}

	} while(selection2==1);



	if (selection1==1) {
		 manager();
	 } else if (selection1==2) {
         reception();
	 }


return(0);

}

void createAccount(void){

    system("cls");
    header();

    char username1[20];
    char password1[10];
    printf("\n\n");
    printf("\n\n");
    printf("\t\t\t  CHOOSE A USERNAME AND A PASSWORD TO CREATE A NEW ACCOUNT\n\n\n" );


     FILE *fp ;
     fp=fopen("login.txt","a");
     printf("\n\n\t\t\t\tENTER RECEPTIONIST USERNAME : ");
     scanf(" %s",username1 );
     fprintf(fp,"%s\n",username1 );
     printf("\n");
     printf("\t\t\t\tENTER RECEPTIONIST PASSWORD : ");
     scanf(" %s",password1 );
     fprintf(fp,"%s\n",password1 );

     fclose(fp);

     printf("\n\n\t\t\tNEW RECEPTIONIST ADDED SUCCESSFULLY\n\n");
     printf("\tENTER ANY KEY TO RETURN TO MENU" );
     getch();
     manager();

}

void deleteAccount(){

            system("cls");
            header();

            printf("\n\n");

            printf("\n\n\t\t\tENTER THE USERNAME OF THE ACCOUNT YOU WANT TO DELETE\n\n");

    		char username2[20];
    		char filename2[]="login.txt";
    		int matchedLine1;
    		int line_num = 1;
    		int find_result = 0;
    		char temp3[512];



    		printf("\t\t\t\t\t USERNAME  :" );

    		scanf("%s",&username2);


    		FILE *fp;

    		if((fp = fopen(filename2, "r")) == NULL) {
    			return(-1);
    		}
    		while(fgets(temp3, 512, fp) != NULL) {
    			if((strstr(temp3, username2)) != NULL) {
    				// printf("A match found on line: %d\n", line_num);
    				// printf("\n%s\n", temp);
    				find_result++;
    				matchedLine1=line_num;

    			}
    			line_num++;
    		}


    		if(fp) {
    			fclose(fp);
    		}


    		int line_no,line_no2, i = 0;
            FILE *fptr1, *fptr2;
    		char filename[]="login.txt";
            char str[MAX], temp[] = "temp.txt";

            fptr1 = fopen(filename, "r");
            if (!fptr1)
    		{
                    printf(" FILE NOT FOUND OR UNABLE TO OPEN!!\n");
                    return 0;
            }
            fptr2 = fopen(temp, "w"); // open the temporary file in write mode
            if (!fptr2)
    		{
                    printf("UNABLE TO OPEN A TEMPORARY FILE!!\n");
                    fclose(fptr1);
                    return 0;
            }
            line_no=matchedLine1;
    		line_no2=matchedLine1+1;
                                    // copy all contents to the temporary file except the specific line
            while (!feof(fptr1))
            {
                strcpy(str, "\0");
                fgets(str, MAX, fptr1);
                if (!feof(fptr1))
                {
                    i++;
                                    // skip the line at given line number
                    if (i != line_no && i != line_no2)
                    {
                        fprintf(fptr2, "%s", str);
                    }
                }
            }
            fclose(fptr1);
            fclose(fptr2);
            remove(filename);  		     // remove the original file
            rename(temp, filename); 	// rename the temporary file to original name
            Sleep(2000);
            printf("\n\n\t\t\t %s ACCOUNT DELETED SUCCESSFULLY ......",username2);
            Sleep(2000);
            printf("\n\n\t\tRETURNING TO MENU " );
            Sleep(1000);
            printf(" ." );
            Sleep(1000);
            printf(" ." );
            Sleep(1000);
            printf(" ." );

            manager();
}

void updateRate(void){

    int roomNo,i,rate ;

    system("cls");
    header();

    printf("\n\n\t\t\t\t **CURRENT ROOM RATES**\n" );

    printf("\n\n\t\t ROOM NO\t ROOM TYPE\t  RATE/NIGHT  \n\n" );

    for (i = 0; i < 10; i++) {

        Sleep(300);

        printf("\t\t  %d   \t %s\t     $ %d\  \n\n",RI[i].roomNo,RI[i].type,RI[i].rate);

    }

    printf("\n\n\n" );
    printf("\t\tENTER THE ROOM NUMBER TO CHANGE RATE : ");

    scanf("%d",&roomNo);

    printf("\n\n\t\tENTER NEW RATE FOR THE ROOM  : " );

    scanf("%d",&rate );

    switch (roomNo) {
        case 101:
            RI[0].rate=rate ;
            break;
        case 102:
            RI[1].rate=rate ;
            break;
        case 103:
            RI[2].rate=rate ;
            break;
        case 104:
            RI[3].rate=rate ;
            break;
        case 105:
            RI[4].rate=rate ;
            break;
        case 106:
            RI[5].rate=rate ;
            break;
        case 107:
            RI[6].rate=rate ;
            break;
        case 108:
            RI[7].rate=rate ;
            break;
        case 109:
            RI[8].rate=rate ;
            break;
        case 110:
            RI[9].rate=rate ;
            break;
        default:
            printf("\n\t\tINVALID ROOM NUMBER" );
    }

    FILE *fp3 ;

    int k=0;

    fp3=fopen("rates.txt","w");

    for(k=0;k<10;k++){
        fprintf(fp3,"%d\n",RI[k].rate);
    }

    fclose(fp3);

    printf("\n\n\t\tROOM RATE CHANGED SUCCESSFULLY..\n");

    printf("\n\t\tENTER ANY KEY TO RETURN TO MENU" );

    getch();

    manager() ;

}

void roomInfo(void){

    RI[0].roomNo=101;
    RI[1].roomNo=102;
    RI[2].roomNo=103;
    RI[3].roomNo=104;
    RI[4].roomNo=105;
    RI[5].roomNo=106;
    RI[6].roomNo=107;
    RI[7].roomNo=108;
    RI[8].roomNo=109;
    RI[9].roomNo=110;

    strcpy(RI[0].type,"STANDARD    ");
    strcpy(RI[1].type,"STANDARD    ");
    strcpy(RI[2].type,"STANDARD    ");
    strcpy(RI[3].type,"STANDARD    ");
    strcpy(RI[4].type,"DELUXE      ");
    strcpy(RI[5].type,"DELUXE      ");
    strcpy(RI[6].type,"DELUXE      ");
    strcpy(RI[7].type,"SUPERIOR    ");
    strcpy(RI[8].type,"SUPERIOR    ");
    strcpy(RI[9].type,"SUPERIOR    ");

    RI[0].bed=1;
    RI[1].bed=1;
    RI[2].bed=2;
    RI[3].bed=2;
    RI[4].bed=1;
    RI[5].bed=1;
    RI[6].bed=2;
    RI[7].bed=1;
    RI[8].bed=2;
    RI[9].bed=3;

    RI[0].ac=1;
    RI[1].ac=0;
    RI[2].ac=1;
    RI[3].ac=0;
    RI[4].ac=0;
    RI[5].ac=0;
    RI[6].ac=0;
    RI[7].ac=0;
    RI[8].ac=0;
    RI[9].ac=0;


    FILE *fp2 ;

    int j=0;

    fp2=fopen("rates.txt","r");

    while (!feof(fp2)) {
        fscanf(fp2,"%d",&RI[j].rate);
        j++;
    }

    fclose(fp2);




    FILE *fp1 ;

    int i=0;

    fp1=fopen("avail.txt","r");

    while (!feof(fp1)) {
        fscanf(fp1,"%d",&RI[i].avail);
        i++;
    }

    fclose(fp1);


}

void checkRoomInfo(void){

    int i ;

    system("cls");
    header();

    printf("\n\n" );
    printf("\n\n" );

    printf("\tROOM NO\tROOM TYPE \t NUMBER OF BEDS    A/C     RATE/NIGHT     AVAILABILITY[0=available,1=Not available] \n");
    printf("\t_______\t__________\t_______________   _____   _____________  ______________");
    printf("\n");
    for (i = 0; i < 10; i++) {

    Sleep(500);

    printf("\t %d   \t%s\t\t %d\t    %d        Rs.%d\t     %d \t\t  \n\n",RI[i].roomNo,RI[i].type,RI[i].bed,RI[i].ac,RI[i].rate,RI[i].avail);

    }

    printf("\n\n\t\t PRESS ANY KEY TO RETURN TO MENU _ _ _ " );
    getch();

}

void bookings(void){

    system("cls");
    header();

    printf("\n\t\t\t\t\t    **** CUSTOMER DETAILS ****\n" );

    FILE *fp;
    char a,b ;

    fp=fopen("checkins.txt","r");

    if(fp == NULL)
             {
                    printf("\nFILE DOESN'T EXISTS OR UNABLE TO OPEN FILE.");
                    exit(0);
             }
             int i=0;
             printf("\n\n \t\t\t\t DETAILS OF CUSTOMERS CURRENTRLY STAYING IN THE HOTEL  \n" );
             printf("\n \t\t\t\t______________________________________________________ \n\n" );
        while(!feof(fp)){
             fscanf(fp,"%d\n",&CI[i].roomNo);
             printf("\t\t\t\t\t\t ROOM NO     : %d  \n\n",CI[i].roomNo );
             fscanf(fp,"%s\n",&CI[i].firstName);
             printf("\t\t\t FIRST NAME        : %s  \n\n",CI[i].firstName );
             fscanf(fp,"%s\n",&CI[i].lastName);
             printf("\t\t\t LAST NAME         : %s  \n\n",CI[i].lastName );
             fscanf(fp,"%s\n",&CI[i].phn);
             printf("\t\t\t PHONE NO          : %s  \n\n",CI[i].phn );
             fscanf(fp,"%s\n",&CI[i].adress);
             printf("\t\t\t ADDRESS           : %s  \n\n",CI[i].adress );
             fscanf(fp,"%d\n",&CI[i].noPer);
             printf("\t\t\t NUMBER OF PERSONS : %d  \n\n",CI[i].noPer );
             fscanf(fp,"%d%c%d%c%d\n",&CI[i].checkInDate,&a,&CI[i].checkInMon,&b,&CI[i].checkInYear);
             printf("\t\t\t CHECK-IN DATE     : %d/%d/%d  \n\n\n",CI[i].checkInDate,CI[i].checkInMon,CI[i].checkInYear);

             i++;
             Sleep(400);
        }

        fclose(fp);
        printf("\t\t\t NUMBER OF ROOMS OCCUPIED CURRENTLY : %d \n\n",i );

        FILE *fp1;

        fp1=fopen("checkouts.txt","r");

        char *checkOutDate[15];
        int bill;
        if(fp1 == NULL)
                 {
                        printf("\nFILE DOESN'T EXISTS OR UNABLE TO OPEN FILE");
                        exit(0);
                 }
                 int j=0;
                 printf("\n\n\n\n\t\t\t\t        DETAILS OF CUSTOMERS STAYED IN THE HOTEL     \n" );
                 printf("\n \t\t\t\t_______________________________________________________\n\n" );
            while(!feof(fp1)){
                 fscanf(fp1,"%d\n",&CI[j].roomNo);
                 printf("\t\t\t\t\t\t ROOM NO     : %d  \n\n",CI[j].roomNo );
                 fscanf(fp,"%s\n",&CI[i].firstName);
                 printf("\t\t\t FIRST NAME        : %s  \n\n",CI[j].firstName );
                 fscanf(fp,"%s\n",&CI[i].lastName);
                 printf("\t\t\t LASt NAME         : %s  \n\n",CI[j].lastName );
                 fscanf(fp,"%s\n",&CI[i].phn);
                 printf("\t\t\t PHONE NO          : %s  \n\n",CI[j].phn );
                 fscanf(fp,"%s\n",&CI[i].adress);
                 printf("\t\t\t ADDRESS           : %s  \n\n",CI[j].adress );
                 fscanf(fp1,"%d\n",&CI[j].noPer);
                 printf("\t\t\t NUMBER OF PERSONS : %d  \n\n",CI[j].noPer );
                 fscanf(fp1,"%d%c%d%c%d\n",&CI[j].checkInDate,&a,&CI[j].checkInMon,&b,&CI[j].checkInYear);
                 printf("\t\t\t CHECK-IN DATE     : %d/%d/%d  \n\n\n",CI[j].checkInDate,CI[j].checkInMon,CI[j].checkInYear);
                 fscanf(fp,"%s\n",&checkOutDate);
                 printf("\t\t\t CHECK-OUT DATE    : %s\n\n",checkOutDate);
                 fscanf(fp1,"%d\n",&bill);
                 printf("\t\t\t TOTAL AMOUNT PAID : Rs. %d\n\n",bill);
                 j++;
                 Sleep(500);
            }

            fclose(fp1);

        printf("PRESS ANY KEY TO GO BACK _ _ _ " );

        getch();

}

void checkIn(void){

    system("cls");
    header();
    int flag;
    int flag1;

    printf("\n\n\t\t\t\t\t  *** ENTER CUSTOMER DETAILS  ***" );

    printf("\n\n\t\t\t ROOM NO           : ");

    scanf("%d",&CI[0].roomNo);

    fflush(stdin);
 do{
    printf("\n\n\t\t\t FIRST NAME        : ");

    gets(CI[0].firstName);

    flag=nameCheck(CI[0].firstName);

     if(flag==0)
	{
    	printf(" INVALID NAME ! ENTER NAME AGAIN \n ");
	}

  }while(flag==0);
  do{
    printf("\n\n\t\t\t LAST NAME         : ");

    gets(CI[0].lastName);

    flag=nameCheck(CI[0].lastName);

     if(flag==0)
	{
    	printf(" INVALID NAME ! ENTER NAME AGAIN \n ");
	}

  }while(flag==0);
do{

    printf("\n\n\t\t\t PHONE NO          : ");

    gets(CI[0].phn);

    flag1=mobileNumberCheck(CI[0].phn);
    if(flag1==0)
    {
    	printf("INVALID MOBILE NUMBER ! ENTER MOBILE NUMBER AGAIN\n ");
	}
	 if(strlen(CI[0].phn)!=10){
    		printf("INVALID MOBILE NUMBER ! ENTER MOBILE NUMBER AGAIN\n ");
    		flag1=0;
	}
}while(flag1==0);

    printf("\n\n\t\t\t ADDRESS           : ");

    gets(CI[0].adress);

    printf("\n\n\t\t\t NUMBER OF PERSONS : ");

    scanf("%d",&CI[0].noPer);
                                                           //getting current time to this program
        time_t currentTime ;                               //reference = stackoverflow.com

        time(&currentTime);

        struct tm *myTime =localtime(&currentTime);

        CI[0].checkInDate= myTime->tm_mday;
        CI[0].checkInMon=myTime->tm_mon;
        CI[0].checkInYear=myTime->tm_year;

    FILE *fp1 ;

    fp1=fopen("checkins.txt","a");

    fprintf(fp1,"%d\n",CI[0].roomNo);
    fprintf(fp1,"%s\n",CI[0].firstName);
    fprintf(fp1,"%s\n",CI[0].lastName);
    fprintf(fp1,"%s\n",CI[0].phn);
    fprintf(fp1,"%s\n",CI[0].adress);
    fprintf(fp1,"%d\n",CI[0].noPer);
    fprintf(fp1,"%d/%d/%d\n",CI[0].checkInDate,CI[0].checkInMon+1,CI[0].checkInYear+1900);

    fclose(fp1);

    switch (CI[0].roomNo) {
        case 101:
            RI[0].avail=1 ;
            break;
        case 102:
            RI[1].avail=1 ;
            break;
        case 103:
            RI[2].avail=1 ;
            break;
        case 104:
            RI[3].avail=1 ;
            break;
        case 105:
            RI[4].avail=1 ;
            break;
        case 106:
            RI[5].avail=1 ;
            break;
        case 107:
            RI[6].avail=1 ;
            break;
        case 108:
            RI[7].avail=1 ;
            break;
        case 109:
            RI[8].avail=1 ;
            break;
        case 110:
            RI[9].avail=1 ;
            break;
        default:
            printf("\n\t\t INVALID ROOM NUMBER" );
    }

    FILE *fp3 ;

    int k=0;

    fp3=fopen("avail.txt","w");

    for(k=0;k<10;k++){
        fprintf(fp3,"%d\n",RI[k].avail);
    }

    fclose(fp3);

    printf("\n\n\t\t\t\t\t CHECK=IN COMPLETE FOR %s %s ",CI[0].firstName,CI[0].lastName);

    printf("\n\n\t\t\t\t\t CHECK=IN DATE : %d/%d/%d",CI[0].checkInDate,CI[0].checkInMon+1,CI[0].checkInYear+1900);

    printf("\n\n\t\t\t\t\t ROOM NO. %d IS OCCUPIED BY %s %s",CI[0].roomNo,CI[0].firstName,CI[0].lastName);

    printf("\n\n\t\tENTER ANY KEY TO RETURN TO MENU" );

    getch();

    reception();
}

void checkOut(void){

    system("cls");
    header();

    printf("\n\t\t\t\t\t\t\t  ****CHECK-OUT DASHBOARD**** \n" );

    FILE *fp;
    char a,b,c ;

    fp=fopen("checkins.txt","r");

    if(fp == NULL)
             {
                    printf("\nFILE DOESN'T EXISTS OR UNABLE TO OPEN FILE");
                    exit(0);
             }
             int i=0;
        while(!feof(fp)){
             fscanf(fp,"%d\n",&CI[i].roomNo);
             fscanf(fp,"%s\n",&CI[i].firstName);
             fscanf(fp,"%s\n",&CI[i].lastName);
             fscanf(fp,"%s\n",&CI[i].phn);
             fscanf(fp,"%s\n",&CI[i].adress);
             fscanf(fp,"%d\n",&CI[i].noPer);
             fscanf(fp,"%d%c%d%c%d\n",&CI[i].checkInDate,&a,&CI[i].checkInMon,&b,&CI[i].checkInYear);

             i++;
        }

        int roomNo,date,mon,year,bill,stay,rate;

        printf("\n\n\t\t\t ENTER THE ROOM NO :  " );

        scanf("%d",&roomNo);
                                                            //getting current time to this program
                time_t currentTime ;                        //reference = stackoverflow.com

                time(&currentTime);

                struct tm *myTime =localtime(&currentTime);

                date= myTime->tm_mday;
                mon=myTime->tm_mon;
                year=myTime->tm_year;

        i=0;

        for(i=0;i<10;i++){

            if(roomNo==CI[i].roomNo){
                printf("\n\n\t\t\t CUSTOMER NAME  : %s %s\n\n",CI[i].firstName,CI[i].lastName );

                    printf("\t\t\t CHECK-IN DATE  : %d/%d/%d\n",CI[i].checkInDate,CI[i].checkInMon,CI[i].checkInYear );

                  printf("\n\t\t\t CHECK-OUT DATE : %d/%d/%d",date,mon+1,year+1900);

                if (date>CI[i].checkInDate) {
                    stay=date-CI[i].checkInDate;
                } else if (date<CI[i].checkInDate) {
                    stay=(30-CI[i].checkInDate)+date ;
                } else if(date==CI[i].checkInDate){
                    stay=1 ;
                }

                     printf("\n\n\t\t\tSTAY TIME : %d  days",stay );

                switch (roomNo) {
                    case 101:
                        rate=RI[0].rate;
                        RI[0].avail=0;
                        break;
                    case 102:
                        rate=RI[1].rate;
                        RI[1].avail=0;
                        break;
                    case 103:
                        rate=RI[2].rate;
                        RI[2].avail=0;
                        break;
                    case 104:
                        rate=RI[3].rate;
                        RI[3].avail=0;
                        break;
                    case 105:
                        rate=RI[4].rate;
                        RI[4].avail=0;
                        break;
                    case 106:
                        rate=RI[5].rate;
                        RI[5].avail=0;
                        break;
                    case 107:
                        rate=RI[6].rate;
                        RI[6].avail=0;
                        break;
                    case 108:
                        rate=RI[7].rate;
                        RI[7].avail=0;
                        break;
                    case 109:
                        rate=RI[8].rate;
                        RI[8].avail=0;
                        break;
                    case 110:
                        rate=RI[9].rate;
                        RI[9].avail=0;
                        break;
                }

                bill=stay*rate ;

                printf("\n\n\t\t\tAMOUNT TO BE PAID  : Rs. %d ",bill);


            FILE *fp ;
            fp=fopen("checkouts.txt","a");
            fprintf(fp,"%d\n",CI[i].roomNo);
            fprintf(fp,"%s\n",CI[i].firstName);
            fprintf(fp,"%s\n",CI[i].lastName);
            fprintf(fp,"%s\n",CI[i].phn);
            fprintf(fp,"%s\n",CI[i].adress);
            fprintf(fp,"%d\n",CI[i].noPer);
            fprintf(fp,"%d/%d/%d\n",CI[i].checkInDate,CI[i].checkInMon,CI[i].checkInYear);
            fprintf(fp,"%d/%d/%d\n",date,mon+1,year+1990);
            fprintf(fp,"%d\n",bill);

            fclose(fp);


            printf("\n\n\t\t\t\tENTER ANY KEY AFTER THE PAYMENT " );

            getch();
            printf("\n\n\t\t\t\t**** PAYMENT RECEIVED ***** " );

            FILE *fp3 ;

            int k=0;

            fp3=fopen("avail.txt","w");

            for(k=0;k<10;k++){
                fprintf(fp3,"%d\n",RI[k].avail);
            }

            fclose(fp3);


            printf("\n\n\t\t\t ENTER ANY KEY TO RETURN TO MENU");

            getch();

            reception();
        }
}
}

char nameCheck(char*name)
{
	int numDigitCount=0,strDigitCount=0,i=0;
    for( i = 0; i < strlen(name); i++)
	{
        if(isalpha(name[i]))
		{
            strDigitCount++;
        } else{
            numDigitCount++;
        }
    }
    if(numDigitCount !=0)
	return 0;
    else
	return 1;


}
int mobileNumberCheck(char*mobNumber)
{
    char numDigitCount=0,strDigitCount=0,i=0;
    for( i = 0; i < strlen(mobNumber); i++)
	{
        if(isdigit(mobNumber[i]))
		{
            numDigitCount++;
        } else{
            strDigitCount++;
        }
    }
    if(strDigitCount !=0)
	return 0;
    else
	return 1;
}


void reception(void){

        system("cls");
        header();

		int selection4 ;
		int errorLoop=0;

    while(errorLoop!=1){

		Sleep(1500);
	    printf("                            .................WELCOME  RECEPTIONIST ...................\n" );
	    printf("\n" );
		Sleep(1500);
	    printf("\n" );

	    printf("\t \t                      1 --> CHECK IN \n\n" );
        Sleep(300);
	    printf("\t \t                      2 --> CHECK OUT  \n\n" );
        Sleep(300);
	    printf("\t \t                      3 --> CHECK ROOM AVAILABILITY       \n\n" );
        Sleep(300);
	    printf("\t \t                      4 --> VIEW CUSTOMER DETAILS       \n\n" );
        Sleep(300);
        printf("\t \t                      5 --> UPDATE DATABASE       \n\n" );
        Sleep(300);
	    printf("\t \t                      6 --> LOG OUT                 \n\n" );
        Sleep(300);
        printf("\t \t                      7 --> EXIT                 \n\n" );
        printf("\n" );
	    printf("\n" );

	    printf("\t\t\t\tENTER YOUR SELECTION   :  " );

	    scanf("%d",&selection4 );

        switch (selection4) {
            case 1:
                errorLoop=1;
                checkIn();
                break;
            case 2:
                errorLoop=1;
                checkOut();
                break;
            case 4:
                errorLoop=1;
                bookings();
                reception();
                break;
            case 3:
                errorLoop=1;
                checkRoomInfo();
                reception();
                break;
            case 5:
                errorLoop=1;
                updateCustomer();
                break;
            case 6:
                errorLoop=1;
                main();
            case 7:
                errorLoop=1;
                exit(0) ;
            default :
         errorLoop=2;

        printf("\n\nINVALID SELECTION ENTER ANY KEY TO RETRY\n");
        getch();
        }
        }

}

void manager(void){

        system("cls");
        header();

		int selection3 ;
		int errorLoop=0;

    while(errorLoop!=1){

		Sleep(1500);
	    printf("                              ..................WELCOME  MANAGER ....................\n" );
	    printf("\n" );
		Sleep(1500);
	    printf("\n" );

	    printf("\t \t                      1 --> ADD NEW RECEPTIONIST ACCOUNT \n\n" );
        Sleep(300);
	    printf("\t \t                      2 --> DELETE A RECEPTIONIST ACCOUNT  \n\n" );
        Sleep(300);
	    printf("\t \t                      3 --> VIEW ROOM DETAILS           \n\n" );
        Sleep(300);
	    printf("\t \t                      4 --> UPDATE ROOM RATES        \n\n" );
        Sleep(300);
	    printf("\t \t                      5 --> CUSTOMER DETAILS                    \n\n" );
        Sleep(300);
        printf("\t \t                      6 --> LOG OUT                \n\n" );
        Sleep(300);
	    printf("\t \t                      7 --> EXIT                 \n\n" );
	    printf("\n" );
	    printf("\n" );
	    printf("\t\t\t\tENTER YOUR SELECTION   :  " );

	    scanf("%d",&selection3 );
        fflush (stdin);

        switch (selection3) {
            case 1:
                errorLoop=1;
                createAccount();
                break;
            case 2:
                errorLoop=1;
                deleteAccount();
                break;
            case 3:
                errorLoop=1;
                checkRoomInfo();
                manager();
                break;
            case 4:
                errorLoop=1;
                updateRate();
                break;
            case 5:
                errorLoop=1;
                bookings();
                manager();
                break;
            case 6:
                errorLoop=1;
                main();
                break;
            case 7:
                errorLoop=1;
                exit(0) ;
            default :
         errorLoop=2;

        printf("\n\nINVALID SELECTION ENTER ANY KEY TO RETRY\n");
        getch();
        }
        }

}

int login(char *filename) {

	char username[20];
	char password[10];

	system("cls");
    header();

	printf("\n");
	printf("\n");

	printf("\t\t\t ***************LOGIN FIRST TO CONTINUE***************\n" );

	printf("\n");
	printf("\n");
	printf("\n");

	printf("                \t USERNAME   : " );

	scanf("%s",&username);




	int matchedLine1,matchedLine2 ;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	int result1 ,result2 ;

	int line_num2 = 1;
	int find_result2 = 0;
	char temp2[512];

	FILE *fp;

	if((fp = fopen(filename, "r")) == NULL) {
		return(-1);
	}
	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, username)) != NULL) {

			find_result++;
			result1=1 ;
			matchedLine1=line_num;

		}
		line_num++;
	}


	if(fp) {
		fclose(fp);
	}

	fflush(stdin);

	printf("\n");
	printf("\n");

	printf("                \t PASSWORD   : " );

	scanf("%s",&password);

	FILE *fp1;



	if((fp = fopen(filename, "r")) == NULL) {
		return(-1);
	}

	while(fgets(temp2, 512, fp) != NULL) {
		if((strstr(temp2, password)) != NULL) {

			find_result2++;
			result2=1 ;
			matchedLine2=line_num2;
		}
		line_num2++;
	}



	if (matchedLine1==matchedLine2-1) {
		system("cls");
		printf("\n               SIGN IN SUCCESSFUL." );
		Sleep(600);
		printf("." );
		Sleep(600);
		printf("." );
		Sleep(600);
		printf("." );
		Sleep(600);
		printf("." );
		printf("\n");
		return 1 ;

	} else {
		system("cls");
		printf("\n\n\t\tENTERED USERNAME OR PASSWORD INCORRECT  \n" );
		printf("\n");
		return 0 ;
	}

	if(fp1) {
		fclose(fp1);
	}
   	return(0);
}

void updateCustomer(){

            system("cls");
            header();

            printf("\n\n");

            printf("\n\n\t\t\tENTER THE ROOM NUMBER OF THE CUSTOMER TO UPDATE DATABASE\n\n");
            char roomNumber[20];
            printf("\t\t\t\t\t ROOM NUMBER  :" );

    		scanf("%s",&roomNumber);

    		char filename2[]="checkins.txt";
    		int matchedLine1;
    		int line_num = 1;
    		int find_result = 0;
    		char temp3[512];


    		FILE *fp;

    		if((fp = fopen(filename2, "r")) == NULL) {
    			return(-1);
    		}
    		while(fgets(temp3, 512, fp) != NULL) {
    			if((strstr(temp3, roomNumber)) != NULL) {
    				// printf("A match found on line: %d\n", line_num);
    				// printf("\n%s\n", temp);
    				find_result++;
    				matchedLine1=line_num;

    			}
    			line_num++;
    		}


    		if(fp) {
    			fclose(fp);
    		}


    		int line_no,line_no2,line_no3, line_no4, line_no5, line_no6, line_no7, i = 0;

            FILE *fptr1, *fptr2;
    		char filename[]="checkins.txt";
            char str[MAX], temp[] = "temp.txt";

            fptr1 = fopen(filename, "r");
            if (!fptr1)
    		{
                    printf(" FILE NOT FOUND OR UNABLE TO OPEN!!\n");
                    return 0;
            }
            fptr2 = fopen(temp, "w"); // open the temporary file in write mode
            if (!fptr2)
    		{
                    printf("UNABLE TO OPEN A TEMPORARY FILE!!\n");
                    fclose(fptr1);
                    return 0;
            }
            line_no=matchedLine1;
    		line_no2=matchedLine1+1;
    		line_no3=matchedLine1+2;
    		line_no4=matchedLine1+3;
    		line_no5=matchedLine1+4;
    		line_no6=matchedLine1+5;
    		line_no7=matchedLine1+6;
                                    // copy all contents to the temporary file except the specific line
            while (!feof(fptr1))
            {
                strcpy(str, "\0");
                fgets(str, MAX, fptr1);
                if (!feof(fptr1))
                {
                    i++;
                                    // skip the line at given line number
                    if (i != line_no && i != line_no2 && i != line_no3 && i != line_no4 && i != line_no5 && i != line_no6 && i != line_no7 )
                    {
                        fprintf(fptr2, "%s", str);
                    }
                }
            }
            fclose(fptr1);
            fclose(fptr2);
            remove(filename);  		     // remove the original file
            rename(temp, filename); 	// rename the temporary file to original name

            Sleep(1000);
            printf(" ." );
            Sleep(1000);
            printf(" ." );
            Sleep(1000);
            printf(" ." );
            printf("\n\n\t\t\t  DATABASE UPDATED SUCCESSFULLY ......");

            printf("\n\n\t\t\t ENTER ANY KEY TO RETURN TO MENU");

            getch();

            reception();

}

void header(){

	printf("\t\t*******************************************************************************\n");
	printf("\t\t*                         ---------------------------                         *\n");
	printf("\t\t*                           HOTEL MANAGEMENT SYSTEM                           *\n");
	printf("\t\t*                         ---------------------------                         *\n");
	printf("\t\t*******************************************************************************\n");


	printf("\n" );

}
