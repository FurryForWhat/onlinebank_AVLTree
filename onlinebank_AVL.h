//
// Created by ADMIN on 09-Jun-23.
//
//"AVL/onlinebank_AVL.h" "AVL/bank_tree.c"

#ifndef MYFIRSTPROGRAM_ONLINEBANK_AVL_H
#define MYFIRSTPROGRAM_ONLINEBANK_AVL_H


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
    char pOrb[10]; // personal or business
    char loan_s[2]; // loan status
//    unsigned int monthly_income;
    char acc_s[10]; //account status
    int acc_level; // copy
    unsigned long long int phNumber;
    unsigned int cur_amount; //current amount
    char address[100];
    int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];
 //amount, loan,trc,ph,cash in out record, trs limit(depend on acc lvl)p or b
 // account status, address
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
int checker_count= 0;

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
void copy_two_char_array(struct node* receiver ,struct node* transmitter );
void data_record();
void data_load();
void mail_validate(char toValidate[50]);
void mail_exist(char Exist[50]);
int check_input(char input);



//************* for node *******************
int balance_factor(struct node* root);
int height(struct node* root);
struct node* insert(struct node* root, int data);
struct node* rotate_left(struct node* root);
struct node* rotate_right(struct node* root);

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
    struct node* new= newNode(users);
    db[users] = new;

    printf("Enter your email:");
    scanf(" %[^\n]",&db[users]->info->email);
    mail_validate(db[users]->info->email);
    if(mail_validate_flag == 1){
        mail_exist(db[users]->info->email);
        if( mail_exist_flag == 0){
            printf("Your mail can be used !!!!!\n");
            printf("Enter your name:");
            scanf(" %[^\n]",&db[users]->info->name);
            checker_count = 0;
            for (int i = 0; i < charCounting(db[users]->info->name);++i) {
                 int result= check_input(db[users]->info->name[i]);
                 if (result == 1){
                        checker_count++;
                 }else{
                     printf("Your name contain unsual word :%c\n", db[users]->info->name[i]);
                     signUp();
                 }
            }
            if(charCounting(db[users]->info->name) == checker_count){
                //****** add more ********
                printf("Enter your NRC:");
                scanf(" %[^\n]",&db[users]->info->nrc);
                //****** add more ********
                printf("Enter your password!:");
                scanf(" %[^\n]",&db[users]->info->password);
                //****** add more ********
                printf("Enter your Phone Number:");
                scanf("%llu",&db[users]->info->phNumber);

                printf("Enter your Deposit amount:");
                scanf("%u",&db[users]->info->cur_amount);

                printf("Enter your address:");
                scanf(" %[^\n]", &db[users]->info->address);
                copy_two_char_array(db[users]->info->pOrb,db[0]->info->pOrb);
                copy_two_char_array(db[users]->info->acc_s,db[0]->info->acc_s);
                new->info->acc_level=  db[0]->info->acc_level;
                //id name nrc email password pOrb loan_status monthly_income
//  accountStatus account_Level phNumber current_amount address TransRC


                printf("\nUser name is: %s and email: %s\n",db[users]->info->name,db[users]->info->email);
                users++;
                printf("Your registration is Successful");
//    data_load();
                char flag;
                printf("\nWould u like to go Main Section?\nPress 'Y' for yes:");
                scanf(" %c",&flag);

                if( flag == 'Y' || flag == 'y'){
                    data_record();
                    main_section();
                }else{
                    data_record();

                }
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
        fprintf(fptr,"%d%c%s%c%s%c%s%c%s%c%llu%c%u%c%s%c%s%c%s%c%d",db[i]->id,' ',db[i]->info->name,' ',db[i]->info->email,' ',db[i]->info->nrc,' ',db[i]->info->password,' ',db[i]->info->phNumber,' ',db[i]->info->cur_amount,' ',db[i]->info->address,' ',db[i]->info->pOrb,' ',db[i]->info->acc_s,' ',db[i]->info->acc_level);
        fprintf(fptr,"%c",'\n');

}
    fclose(fptr);
}

void data_load(){

    FILE *fptr= fopen("final_project_AVL.txt", "r");


    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile:\nError code: 1\n");
        exit(1);
    }


//id name email nrc pass phNumber
        for (int i = 0; i < SIZE ; ++i) {
            struct node* new_node= newNode(i);
            db[users] = new_node;
            fscanf(fptr, "%d%s%s%s%s%llu",&new_node->id,&new_node->info->name,&new_node->info->email,&new_node->info->nrc,&new_node->info->password,&new_node->info->phNumber);



            if(i == 0){
                root= new_node;
            }else{
                root = insert(root,new_node->id);
            }
            //to insert data



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
        return NULL;
    }else{
        new->id= id;
        new->info= (struct data*)malloc(sizeof(struct data));
        new->right= NULL;
        new->left= NULL;
        new->height= 0;
        return new;
    }
}

void copy_two_char_array(struct node* receiver ,struct node* transmitter ){
    int transmit_counter = charCounting(transmitter);
    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }
}

int check_input(char input){
    if( input >= 49 && input<= 57 && input =='\0'){
        return 1;
    }else if(input >= 65 && input  <= 90 ){
        return 1;
    }else if ( input >= 97 && input <= 122){
        return 1;
    }
    else{
        return -1;
    }
}

int balance_factor(struct node* root)
{
    int lh, rh;
    if (root == NULL)
        return 0;
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->height;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->height;
    return lh - rh;
}

int height(struct node* root)
{
    int lh, rh;
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL)
        lh = 0;
    else
        lh = 1 + root->left->height;
    if (root->right == NULL)
        rh = 0;
    else
        rh = 1 + root->right->height;

    if (lh > rh)
        return (lh);
    return (rh);
}
struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->height = height(root);
    left_child->height = height(left_child);

    // return the new node after rotation
    return left_child;
}

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes  
    root->height = height(root);
    right_child->height = height(right_child);

    // return the new node after rotation
    return right_child;
}

struct node* insert(struct node* bla, int data)
{
    if (bla == NULL)
    {
        struct node* new_node = newNode(data);
        if (new_node == NULL)
        {
            return NULL;
        }
        bla = new_node;
    }
    else if (data > bla->id)
    {
        // insert the new node to the right
        bla->right = insert(bla->right, data);


        // tree is unbalanced, then rotate it
        if (balance_factor(root) == -2)
        {
            if (data > bla->right->id)
            {
                bla = rotate_left(bla);
            }
            else
            {
                bla->right = rotate_right(bla->right);
                bla = rotate_left(bla);
            }
        }
    }
    else
    {
        // insert the new node to the left
        bla->left = insert(bla->left, data);

        // tree is unbalanced, then rotate it
        if (balance_factor(bla) == 2)
        {
            if (data < bla->left->id)
            {
                bla = rotate_right(bla);
            }
            else
            {
                bla->left = rotate_left(bla->left);
                bla = rotate_right(bla);
            }
        }
    }
    // update the heights of the nodes
    bla->height = height(bla);
    return bla;
}
#endif MYFIRSTPROGRAM_ONLINEBANK_AVL_H