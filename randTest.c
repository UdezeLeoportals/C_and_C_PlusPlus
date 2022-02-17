/////////////TITLE//////////////////////////////////////
////////////AUTHOR: UDEZE LEONARD CHINEDU//////////////
//////////////////////////////////

//////////PREPROCESSOR DIRECTIVES////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

////////////////FUNCTIONS DECLARATION FOR THE 5 TASKS///////////////
void Jesus_mean1(); //Mean test
void Jesus_freq2(); //Frequency test
void Jesus_serial3(); //Serial test
void Jesus_poker4(); //Poker test
void Jesus_pokerfile5(); //Poker test with file

//////////////////DECLARATION OF OTHER FUNCTIONS////////////////////////
int Christ_3digit_same(int LORD[]);//function to test if three digits are the same
int Christ_2pairs(int LORD[]); //function to test if 4 digits contains 2 pairs
int Christ_1pair(int LORD[]); //function to test if 4 digits contain 1 pair
int Christ_none_identical(int LORD[]); //function to test if none of the 4 digits are identical
int JesusChrist_occur(int Word, int Spirit[]); //function to count how many times a number occurs in 4 digits
int Jesus_decide(int LORD[]); //Function to decide which comparison to make
void convert(int LORD);

/////////////GLOBAL VARIABLE//////////////////////////////////////
int random_number;

///////////////////////////MAIN FUNCTION/////////////////////////////
int main(int argc, char *argv[])
{
    int Jesus_choice = atoi(argv[1]); //convert argument to int
    //if the user fails to put an argument
    if(argc < 2){
        printf("Please type a parameter for program execution.\n");
        return 1;
    }
    //Choose which of the test functions to call
    switch(Jesus_choice){
        case 1: //Mean test
            Jesus_mean1();
        break;
        case 2: //Frequency test
            Jesus_freq2();
        break;
        case 3:   //Serial test
            Jesus_serial3();
        break;
        case 4: //Poker test
            Jesus_poker4();
        break;
        case 5:   //Poker test with file
            Jesus_pokerfile5();
        break;
        default:   //Error message for invalid argument
            printf("Please the argument is not within the expected range. \n Enter a number between 1 and 5 inclusive");
        break;
    }
    return 0;
}

///////////////////////////Function definitions//////////////////////////
void Jesus_mean1(){//Mean test
    float Christ_sum=0; //variable to hold sum of random numbers
    int JesusChrist;
    //srand(time(NULL));
    //loop to generate 1000 random numbers and add them
    printf("\n The 1000 random numbers generated are shown below:\n");
    for(JesusChrist=1; JesusChrist<=1000; JesusChrist++){
        random_number = (int) (10.0*rand()/(RAND_MAX + 1.0));
        printf("%d  ",  random_number); //Print them on the screen
        if(JesusChrist%25==0) printf("\n");
        Christ_sum += random_number;
    }
    float Christ_mean = Christ_sum/1000;
    float Jesus_diff = Christ_mean - 4.50;
    printf("\n\nThe mean of the 1000 random numbers = %.5f \n ", Christ_mean);
    printf("\nThe expected value is 4.5 and the difference is  %.5f \n ", Jesus_diff);
}

void Jesus_freq2(){ //Frequency test
    float Christ_counter[10]; //an array to count the occurrence of each digit
    //srand(time(NULL));
    int Christ, Jesus;
    for( Christ=0; Christ<=9; Christ++)//initialize counter
        Christ_counter[Christ]=0.0;

    printf("\n The generated 10000 random numbers are:\n\n");
    //Loop to generate 10,000 random digits and count their occurrence
    for( Jesus=1; Jesus<=10000; Jesus++){
       random_number = (int) (10.0*rand()/(RAND_MAX + 1.0));
       printf("%d ",  random_number);
       if(Jesus%50==0) printf("\n ");

       Christ_counter[random_number]++; //counting the frequency of each digit
   }
   printf("\nThe numbers above are the 10000 generated random numbers\n\n ");
   printf("Digit \t Frequency \t Percentage  \t Expected value \t Difference\n");
   for( Christ=0; Christ<=9; Christ++)
        printf("%d \t %d  \t\t %.2f %% \t 10%% \t\t\t %.2f\n", Christ, (int) Christ_counter[Christ], (Christ_counter[Christ]/100), ((Christ_counter[Christ]/100)-10) );
}

void Jesus_serial3(){ //Serial test
    //srand(time(NULL));
    float Jesus_counter[100]; //Declare and initialize array to count the random pairs
    int Lord, Jesus, Christ;
    for( Lord=0; Lord<=99; Lord++) //initialize counter
        Jesus_counter[Lord]=0.0;
    int random_number2 =0;

    printf(" \nThe 10000 generated pairs of random digits are:\n\n");
    for( Jesus=1; Jesus<=10000; Jesus++){
        random_number = (int) (10.0*rand()/(RAND_MAX + 1.0)); //first digit
        random_number2 = (int) (10.0*rand()/(RAND_MAX + 1.0)); //second digit

        char Word[32];
        sprintf(Word, "%d%d", random_number, random_number2); //concatenate both digits
        int Jesusnum = atoi(Word); //convert digits to an integer

        Jesus_counter[Jesusnum]++;//count the occurrence of the resulting number

        if(Jesusnum<10) printf("0");
        printf("%d ", Jesusnum);
        if(Jesus%50==0) printf("\n");
    }
    printf("\nThe numbers above are the 10000 generated pairs of random numbers\n\n ");
    printf("\n");
    printf("Digits \t Frequency \t Percentage \t Expected value \t Difference \n");
    for(Christ=0; Christ<=99; Christ++){
        if(Christ<10) printf("0");
        printf("%d", Christ);
        printf("\t %d \t\t %.2f %% \t 1%% \t\t\t %.2f\n ", (int) Jesus_counter[Christ], (Jesus_counter[Christ]/100), ((Jesus_counter[Christ]/100)-1.0));
    }
}


void Jesus_poker4(){ //Poker test
    //srand(time(NULL));
     int random_num[4]; //array to hold four random digits
    int Jesus_counter[5]; //array to count the occurrence of each of the 5 special cases
    int Lord, Jesus, Christ, Glory;
    for( Lord=0; Lord<5; Lord++) //initialization of the counter array
        Jesus_counter[Lord]=0;

    int Lord5[800], Lord4[600], Lord3[300], Lord2[200], Lord1[100];
    int Chr5=0, Chr4=0, Chr3=0, Chr2=0, Chr1=0, word4;

    printf("\n Below is 1000 Samples of 4 digit random numbers\n");
    for( Jesus=1; Jesus<=1000; Jesus++){
        for(Christ=0; Christ<4; Christ++)//loop to generate 4 random numbers
            random_num[Christ] = (int) (10.0*rand()/(RAND_MAX + 1.0));

      int Jesus_option = Jesus_decide(random_num); //check which of the 5 categories the 4 digits fall into

        char Word[4];
        sprintf(Word, "%d%d%d%d", random_num[0], random_num[1], random_num[2], random_num[3]); //concatenate the 4-digits
        int Word1 = atoi(Word);

    //Test which of the 5 categories the 4-digits fall into
      switch(Jesus_option){
        case 4: //if all digits are the same
             Jesus_counter[0]++;
             Lord1[Chr1] =Word1;
             if(Chr1==0) Glory = Lord1[0];
             Chr1++;
             break;
        case 3: // if three digits are the same
             Jesus_counter[1]++;
             Lord2[Chr2++] =Word1;
              break;
        case 2: // if 4 digits contains 2 pairs
             Jesus_counter[2]++;
             Lord3[Chr3++] =Word1;
             break;
        case 1: // if 4 digits contains 1 pair
            Jesus_counter[3]++;
            Lord4[Chr4++] =Word1;
            break;
        case 5: //if all digits are unique
              Jesus_counter[4]++;
              Lord5[Chr5++] =Word1;
              break;
      }
    }
    int humble;
    //Printing out of the several categories on screen
        if(Chr1>0){
                printf("\n\nThe numbers with identical digits\n\n");
            for(humble=0; humble<Chr1; humble++){
                 if(humble==0) convert(Glory);
                else convert(Lord1[humble]);
                if(humble%30==20) printf("\n");
            }
        }
           printf("\n\nThe numbers with 3 identical digits\n\n");
        for(humble=0; humble<Chr2; humble++){
             convert(Lord2[humble]);
            if(humble%30==20) printf("\n");
        }
       printf("\n\nThe numbers with 2 pairs of similar digits\n\n");
        for(humble=0; humble<Chr3; humble++){
             convert(Lord3[humble]);
            if(humble%30==20) printf("\n");
        }
           printf("\n\nThe numbers with 1 pair of identical digits\n\n");
        for(humble=0; humble<Chr4; humble++){
            convert(Lord4[humble]);
            if(humble%30==20) printf("\n");
        }
           printf("\n\nThe numbers with no identical digits\n\n");
        for(humble=0; humble<Chr5; humble++){
            convert(Lord5[humble]);
            if(humble%30==20) printf("\n");
        }
        printf("\n\nAbove is the 1000 Samples of 4 digit random numbers\n\n");
        printf("Please if you scroll up, you will see the grouping of each of the 4 digits according to the 5 categories\n\n");
        printf("\n\n Set of Pattern\t\t\tFrequency \t Expected value \t Difference\n");
        printf("\nIdentical 4-digit number:\t %d \t\t 1 \t\t\t %d",  Jesus_counter[0], (Jesus_counter[0]-1));
        printf("\nThree similar digits:\t\t %d \t\t 36 \t\t\t %d",  Jesus_counter[1], (Jesus_counter[1]-36));
        printf("\nTwo pairs of digits:\t\t %d \t\t 27 \t\t\t %d",  Jesus_counter[2], (Jesus_counter[2]-27));
        printf("\nOne pair of digits:\t\t %d \t\t 432 \t\t\t %d",  Jesus_counter[3], (Jesus_counter[3]-432));
        printf("\nNon-identical digits:\t\t %d \t\t 504 \t\t\t %d\n",  Jesus_counter[4], (Jesus_counter[4]-504));
}

void Jesus_pokerfile5(){ //Poker test with ASCII file
    //srand(time(NULL));
    //create a file named Jesus_random.txt to save the numbers
    FILE *Lordfp, *Heavenfp;
    Lordfp = fopen("Jesus_random.txt", "w");
    int Lord, Jesus, Christ[4000], Spirit, Word[4], Glory;
    int Jesus_counter[5];
    for( Lord=0; Lord<5; Lord++)
        Jesus_counter[Lord]=0;

     int Lord5[800], Lord4[600], Lord3[300], Lord2[200], Lord1[100];
    int Chr5=0, Chr4=0, Chr3=0, Chr2=0, Chr1=0;

    if(Lordfp != NULL){
        //generate 4000 random numbers and write their ASCII equivalent to a file
        for(Jesus=1; Jesus<=4000; Jesus++){
            random_number = (int) (10.0*rand()/(RAND_MAX + 1.0));
            fprintf(Lordfp, "%d ", (random_number+48)); //add 48 to the number to obtain the ASCII equivalent to the file
            if(Jesus%50==0) fprintf(Lordfp, "%s \n", " ");
        }
    }

        fclose(Lordfp);
        printf("\n The 4000 random numbers generated in the file are:\n\n");
        Spirit=0;
        Heavenfp = fopen("Jesus_random.txt", "r");
        //Read the random numbers from the file to an array named Christ
        if(Heavenfp != NULL){
            while(!feof(Heavenfp) && Spirit<4000 ){
                    Lord=0;
                    fscanf(Heavenfp, "%d", &Lord);
                    Christ[Spirit++] = Lord-48; //subtract 48 from the number to decode the ASCII equivalent, save in an array
                    printf("%d ", Lord-48);
                    if(Spirit%50==0) printf("\n");
            }
    }

    fclose(Heavenfp);

        Spirit=0;
        int Almighty, Worship;
        printf("\n After grouping the numbers in 4-digits, we obtain the following:\n\n");
        for(Jesus=0; Jesus<1000; Jesus++){
            Almighty = 4*Jesus;
            //Pick 4 consecutive digits at a time
            for(Worship=0; Worship<4; Worship++)
                Word[Worship] = Christ[Almighty++];
            //Conduct the Poker test on the 4 digits
          int Jesus_option =Jesus_decide(Word);

        char Word2[4];
        sprintf(Word2, "%d%d%d%d", Word[0], Word[1], Word[2],Word[3]);
        printf("%s ", Word2);
        if(Jesus%20==0) printf("\n");
        int Word1 = atoi(Word2);
        //Test for each of the 5 categories of Poker test
       switch(Jesus_option){
        case 4: //if all digits are the same
             Jesus_counter[0]++;
             Lord1[Chr1] =Word1;
             if(Chr1==0) Glory= Lord1[0];
             Chr1++;
             break;
        case 3: // if three digits are the same
             Jesus_counter[1]++;
             Lord2[Chr2++] =Word1;
              break;
        case 2: // if 4 digits contains 2 pairs
             Jesus_counter[2]++;
             Lord3[Chr3++] =Word1;
             break;
        case 1: // if 4 digits contains 1 pair
            Jesus_counter[3]++;
            Lord4[Chr4++] =Word1;
            break;
        case 5: //if all digits are unique
              Jesus_counter[4]++;
              Lord5[Chr5++] =Word1;
              break;
       }
}
    int humble;
 //Print out all the categories of the generated numbers
        if(Chr1>0){
                printf("\n\nThe numbers with identical digits\n\n");
            for(humble=0; humble<Chr1; humble++){
                 if(humble==0) convert(Glory);
                else convert(Lord1[humble]);
                if(humble%30==20) printf("\n");
            }
        }
           printf("\n\nThe numbers with 3 identical digits\n\n");
        for(humble=0; humble<Chr2; humble++){
             convert(Lord2[humble]);
            if(humble%30==20) printf("\n");
        }
       printf("\n\nThe numbers with 2 pairs of similar digits\n\n");
        for(humble=0; humble<Chr3; humble++){
             convert(Lord3[humble]);
            if(humble%30==20) printf("\n");
        }
           printf("\n\nThe numbers with 1 pair of identical digits\n\n");
        for(humble=0; humble<Chr4; humble++){
            convert(Lord4[humble]);
            if(humble%30==20) printf("\n");
        }
           printf("\n\nThe numbers with no identical digits\n\n");
        for(humble=0; humble<Chr5; humble++){
            convert(Lord5[humble]);
            if(humble%30==20) printf("\n");
        }
        printf("\n\nPlease if you scroll up, you will see the grouping of each of the 4 digits according to the 5 categories\n\n");
        printf("\n\n Set of Pattern\t\t\tFrequency \t Expected value \t Difference\n");
        printf("\nIdentical 4-digit number:\t %d \t\t 1 \t\t\t %d",  Jesus_counter[0], (Jesus_counter[0]-1));
        printf("\nThree similar digits:\t\t %d \t\t 36 \t\t\t %d",  Jesus_counter[1], (Jesus_counter[1]-36));
        printf("\nTwo pairs of digits:\t\t %d \t\t 27 \t\t\t %d",  Jesus_counter[2], (Jesus_counter[2]-27));
        printf("\nOne pair of digits:\t\t %d \t\t 432 \t\t\t %d",  Jesus_counter[3], (Jesus_counter[3]-432));
        printf("\nNon-identical digits:\t\t %d \t\t 504 \t\t\t %d\n",  Jesus_counter[4], (Jesus_counter[4]-504));

}

///////////////////DEFINITION OF OTHER FUNCTIONS/////////////////////////////////////
//function to decide the category a 4-digit random number falls into
int Jesus_decide(int LORD[]){
    if(JesusChrist_occur(LORD[0], LORD)==4) return 4; //if the first number occurs 4 times
    else if(Christ_3digit_same(LORD)==3) return 3; //if the numbers contains 3 identical digits
    else if(Christ_2pairs(LORD)==2)  return 2;//if 4 digits contain 2 pairs
    else if(Christ_1pair(LORD)==1) return 1; //if 4 digits contains 1 pair
    else if(Christ_none_identical(LORD)==4)  return 5;//if no digit is identical
}
int Christ_3digit_same(int LORD[]){ //function to check if 3 digits are the same
    int love = ((JesusChrist_occur(LORD[0], LORD)==3) || (JesusChrist_occur(LORD[1], LORD)==3)) ? 3 : 1;
    return love;
    //if the first digit occurs 3 times or the 2nd digit occurs 3 times e.g. 3334, 5666, 6766 or 7787
}

int Christ_2pairs(int LORD[]){ //Function to check if 4 digits contain 2 pairs
    int joy = ((JesusChrist_occur(LORD[0], LORD)==2) && (JesusChrist_occur(LORD[1], LORD)==2) && (JesusChrist_occur(LORD[2], LORD)==2)) ? 2 : 1;
    return joy;
    //if the 1st digit occurs twice and the 2nd digit occurs twice and the 3rd digit occurs twice e.g. 3344, 5656, 5665
}

int Christ_1pair(int LORD[]){//function to confirm that the 4 digits contains exactly 1 pair
    int JesusC[3] , JChrist;
    //count the number of times each of the 1ast 3 digits occur
    for(JChrist=0; JChrist<3; JChrist++)
        JesusC[JChrist] = JesusChrist_occur(LORD[JChrist], LORD);

    //Confirm that they all occur 1 or 2 times
    int LordFlag=1, HolyGhost; //LordFlag is used to check that all the digits occur 1 or 2 times
    for(HolyGhost=0; HolyGhost<3; HolyGhost++)
        if(JesusC[HolyGhost]>2) LordFlag=0;
    //if no digit appears more than twice and only one occurs appears twice e.g. 1123, 3435, 5605, 5667, 6787, 6799
    int peace = (!((JesusC[0]==1) && (JesusC[1]==1) && (JesusC[2]==1)) && LordFlag) ? 1 : 2;
    return peace;
}
//function to check if none of the four digits are identical
int Christ_none_identical(int LORD[]){
     int JesusC[4], JChrist;
    //count the number of times each of the 1st 4 digits occur
     for(JChrist=0; JChrist<4; JChrist++)
        JesusC[JChrist] = JesusChrist_occur(LORD[JChrist], LORD);
    //if all the digits occurs only once return 4
    if((JesusC[0]==1) && (JesusC[1]==1) && (JesusC[2]==1) && (JesusC[3]==1)) return 4;
    else return 10;
}
int JesusChrist_occur(int Word, int Spirit[]){
     //function to count how many times a number occurs in 4 digits
    int Lord_count=0, Holy;
    for(Holy=0; Holy<4; Holy++)
        if(Word== Spirit[Holy]) Lord_count++;
    return Lord_count;
}
//function to pad 0's to the front of 4-digit number less than 1000 before printing
void convert(int LORD){
    if(LORD>1000) printf("%d ", LORD);
    else if(LORD>100) printf("0%d ", LORD);
    else if(LORD>10) printf("00%d ", LORD);
    else printf("000%d ", LORD);
}
