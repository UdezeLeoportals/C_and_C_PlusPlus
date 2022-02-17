#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "omp.h"
//#include "freq.h"

int main(int argc, char* argv[]){
	if(argc<2){
		printf("Please specify the number of threads as command line argument if num_threads>2");
		omp_set_num_threads(2);
	}
	else
		omp_set_num_threads(atoi(argv[1]));
    int keywordlinenumber = 0;  
    int keywordbufferlength = 32;
    int textbufferlength = 128;
    int reallength = 0;  

    
	double start = omp_get_wtime(), end;
    FILE *fp = fopen("keywords.txt", "r");
    if(fp==NULL)
        return 0; 
    
    char keywordbuffer[keywordbufferlength];
    // get the line number of the keyword file
    while((fgets(keywordbuffer, keywordbufferlength, fp)) != NULL){
        keywordlinenumber++;
    }

    // the array of all the keywords
    char keywords[keywordlinenumber][keywordbufferlength];
    // the frequencies of all the keywords
    int frequencies[keywordlinenumber];
    //init the frequencies
	
    //parallelization of frequency initialization loop
    #pragma omp parallel for schedule (static, 4)
    for(int i=0; i<keywordlinenumber;i++)
        frequencies[i] = 0;

    // Move the file pointer to the start.
    fseek(fp, 0, SEEK_SET);

    keywordlinenumber = 0;
    while((fgets(keywords[keywordlinenumber], keywordbufferlength, fp)) != NULL){
        //remove '/n' from the end
        reallength = strlen(keywords[keywordlinenumber]);
        if (keywords[keywordlinenumber][reallength-1] == '\n')
            keywords[keywordlinenumber][reallength-1] = '\0';

        keywordlinenumber++;
    }

    fclose(fp);

    fp = fopen("harrypotter.txt", "r");
    if(fp==NULL)
        return 0; 
    
    char textbuffer[textbufferlength];
    char *p;
    //parallelization of the region where the word count takes place in the harrypotter text file
    while((fgets(textbuffer, textbufferlength, fp)) != NULL){
        #pragma omp parallel for private(p) firstprivate(keywordlinenumber, textbuffer) shared(keywords, frequencies) schedule (dynamic, 3)
        for(int i=0; i<keywordlinenumber;i++)
	{
            p = textbuffer;
            while((p=strstr(p, keywords[i]))!=NULL){
                frequencies[i]++;
                p = p+ strlen(keywords[i]);
            }
		
        }
    }    
    

    fclose(fp);
   
    // order the name list
    struct NameAndCount{
        char *name;
        int count;
    };
	//parallelization of the region where the word list is copied into a data structure
    struct NameAndCount namelist[keywordlinenumber];
    #pragma omp parallel for firstprivate(keywordlinenumber, keywords, frequencies) shared(namelist) 
    for(int i=0; i<keywordlinenumber;i++){
        namelist[i].name = keywords[i];
        namelist[i].count = frequencies[i]; 
	
    }

    // bubble sort
    
    struct NameAndCount temp;

    for(int i=0; i<keywordlinenumber-1; i++)
	{
	#pragma omp parallel for private (temp) firstprivate(keywordlinenumber) shared (namelist) 
        for(int j=0; j<keywordlinenumber-i-1; j++){
            if(namelist[j].count > namelist[j+1].count){
                temp = namelist[j+1];
                namelist[j+1] = namelist[j]; 
                namelist[j] = temp;
            }
        }
	
    }

    #pragma omp for ordered
    for(int i =0; i<keywordlinenumber; i++)
        printf("%s, %d\n", namelist[i].name, namelist[i].count);
	//parallel region created to print the number of threads
	#pragma omp parallel for 
        for(int i =0; i<2; i++){
        
	if(i==1) printf("Number of threads = %d", omp_get_num_threads());
	}
    clock_t end1 = clock();

       
	end = omp_get_wtime();
      		   printf(" \nTime elapsed is %f seconds", end-start);
    
}
