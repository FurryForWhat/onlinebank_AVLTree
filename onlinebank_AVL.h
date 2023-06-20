//
// Created by ADMIN on 09-Jun-23.
//
//"AVL/onlinebank_AVL.h" "AVL/bank_tree.c"

#ifndef MYFIRSTPROGRAM_ONLINEBANK_AVL_H
#define MYFIRSTPROGRAM_ONLINEBANK_AVL_H


#include "stdio.h"
#include "stdlib.h"
#define SIZE 5000

struct trans{
    char note[200];
};
//id name nrc email password pOrb loan_status monthly_income
//  accountStatus account_Level phNumber current_amount address TransRC
struct data{

    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20]; // personal or business
    char loan_s[2]; // loan status
    unsigned int monthly_income;
    char acc_s[10]; //account status
    int acc_level; // copy
    unsigned long long int phNumber;
    unsigned int cur_amount; //current amount
    char address[100];
    int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];

};

struct node{
    int id;
    struct data* info;
    struct node* right;
    struct node* left;
    int height;
};
//**************     for node   **********************
struct node* root= NULL;


//***************   global db malloc *******************
struct node* db[SIZE];


//***********   Global Variable     *****************
int users=0;
int g_id= 0;    // should use before loading file for txt file user indexing
int mail_validate_flag= 0; // for Mail Validation
int mail_exist_flag= 0;


// ************ Global Variable(array)  ***************
int space_array[30];
char int_to_char_array_data[10];

//***********   function declaration   ***************
void main_section();
void sign_in();
void signUp();
int charCounting(char toCount[50]);
void space_counter();
void integer_to_char(unsigned int value);
struct node* newNode(int id);
void copy_two_char_array(char receiver[200] ,char transmitter[200] );
void data_record();
void data_load();
void mail_validate(char toValidate[50]);
void mail_exist(char Exist[50]);



void main_section(){
    int input= 0;
    printf("\n************ Welcome from online bank***********\n");
    printf("Press:1 For Sign in\nPress:2 for Sign up\nPress:3 for Exit\n");
    scanf("%d",&input);

    if(input == 1){
         sign_in();
    }else if( input == 2){
            signUp();
    }else if( input == 3){
        data_record();
        exit(0);

    }else{
        printf("******Your input is invalid:Try again********\n");
        main_section();
    }
}

void mail_validate(char toValidate[50]){
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int mail_count= 0;
    int name_count= 0;

    for (int i = 0; i < charCounting(toValidate); ++i) {
        if(toValidate[i] == ' '){
            printf(" Your mail contain spaces which is not allowed!!");
            exit(1);
        }else{
            if(toValidate[i] == '@'){
                break;
            }
            name_count++;
        }
    }
    for (int i = 0; i < charCounting(toValidate); ++i) {
        if(toValidate[name_count] != form[i]){
            break;
        }else{
            name_count++;
            mail_count++;
        }

    }

    if(mail_count == 10){
        mail_validate_flag= 1;
    }
}

void mail_exist(char Exist[50]){
    int input_check= charCounting(Exist);
    int sameCount= 0;
    for (int i = 0; i < users ; ++i) {
     int email_check= charCounting(db[i]->info->email);

        if(input_check != email_check) {
            break;
        }else {
            for (int j = 0; j < input_check; ++j) {
                if (Exist[j] == db[i]->info->email[j]) {
                    sameCount++;
                } else{
                    break;
                }
            }
        }

        if( sameCount == input_check){
            mail_exist_flag= i;
        }

    }


}
int charCounting(char toCount[50]){ // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void space_counter(){
    FILE *fptr = fopen("ncc_db1.txt","r");

    if(fptr==NULL){
        printf("File opening error at space_counter fun:\n");
    } else{
        char c = fgetc(fptr);
        int index=0;

        while (!feof(fptr)){
            if( c !='\n'){
                if(c==' '){
                    space_array[index]+=1;

                }
                c = fgetc(fptr);

            } else{

                index++;
                c = fgetc(fptr);
            }

        }

        for (int aaa = 0; aaa < 30; ++aaa) {
            printf("%d ",space_array[aaa]);
        }
        printf("\n");
    }


}

void integer_to_char(unsigned int value){

    FILE *fptr = fopen("100.txt","w");

    if(fptr==NULL){
        printf("file opening error at integer_to_char:\n");
    } else{
        fprintf(fptr,"%u",value);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("100.txt","r");
    fscanf(fptr2,"%s",&int_to_char_array_data[0]);


}

void sign_in(){
    char id[6];
    char password[30];

    printf("Enter your id:");
    scanf(" %[^\n]", &id);
    printf("Enter your password:");
    scanf(" %[^\n]", &password);

}

void signUp(){
    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_pass[50];
    unsigned long long int re_phone=0;

    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);
    mail_validate(reEmail);
    if(mail_validate_flag == 1){
        mail_exist(reEmail);
        if( mail_exist_flag == 0){
            printf("Your mail can be used !!!!!\n");
            printf("Enter your name:");
            scanf(" %[^\n]",&re_name[0]);
            //****** add more ********
            printf("Enter your NRC:");
            scanf(" %[^\n]",&re_nrc[0]);
            //****** add more ********
            printf("Enter your password!:");
            scanf(" %[^\n]",&re_pass[0]);
            //****** add more ********
            printf("Enter your Phone Number:");
            scanf("%llu",&re_phone);
            //id name nrc email password pOrb loan_status monthly_income
//  accountStatus account_Level phNumber current_amount address TransRC
            struct node* new= newNode(users);

            //to insert data
            copy_two_char_array(new->info->name,re_name);
            copy_two_char_array(new->info->email,reEmail);
            copy_two_char_array(new->info->nrc,re_nrc);
            copy_two_char_array(new->info->password,re_pass);
            new->info->phNumber= re_phone;
            db[users] = new;

    printf("\nUser name is: %s and email: %s\n",db[users]->info->name,db[users]->info->email);
            users++;
            printf("Your registration is Successful");
//    data_load();
            char flag;
            printf("\nWould u like to go Main Section?\nPress 'Y' for yes:");
            scanf(" %c",&flag);

            if( flag == 'Y' || flag == 'y'){
                main_section();
            }else{
                data_record();
                exit(1);
            }

        }else{
            printf("Your mail is used!!!!\n Try with new one!!!\n");
            signUp();
        }

    }else{
        printf("your mail format isn't correct\n");
        signUp();
    }
    //****** add more ********




}
void data_record(){
FILE *fptr= fopen("final_project_AVL.txt","w");

if( fptr == NULL){
    printf("cannot open file to record:\n");
    return exit(1);
}
//id name email nrc pass phNumber
for (int i = 0; i < users; ++i) { // perfect timing for users (hapi hapi hapi)
        fprintf(fptr,"%d%c%s%c%s%c%s%c%s%c%llu",db[i]->id,' ',db[i]->info->name,' ',db[i]->info->email,' ',db[i]->info->nrc,' ',db[i]->info->password,' ',db[i]->info->phNumber);
        fprintf(fptr,"%c",'\n');
}
    fclose(fptr);
}

void data_load(){
    int id;
    char name[30];
    char email[50];
    char nrc[30];
    char password[30];
    unsigned long long int phone;
    FILE *fptr= fopen("final_project_AVL.txt","r");

if( fptr == NULL){
    printf("Error at loadingAllDataFromFile Function!!!!!!!");
    exit(1);
}

//id name email nrc pass phNumber
    for (int i = 0; i < SIZE ; ++i) {
        struct node* new= newNode(i);
        fscanf(fptr, "%d%s%s%s%s%llu",&new->id,&new->info->name,&new->info->email,&new->info->nrc,&new->info->password,&new->info->phNumber);



        //to insert data

        db[users] = new;


        if( db[i]->info->email[1] < 1 || db[i]->info->email[2] < 1){
            break;
        }
        users++;

    }
    fclose(fptr);
}

struct node* newNode(int id){

    struct node* new=(struct node*)malloc(sizeof(struct node));
    if (new == NULL){
        return 0;
    }else{
        new->id= id;
        new->info= (struct data*)malloc(sizeof(struct data));
        new->right= NULL;
        new->left= NULL;
        new->height= 0;
        return new;
    }
}

void copy_two_char_array(char receiver[200] ,char transmitter[200] ){
    int transmit_counter = charCounting(transmitter);
    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }
}

#endif MYFIRSTPROGRAM_ONLINEBANK_AVL_H