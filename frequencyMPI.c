#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "mpi/mpi.h"
#include <mpi.h>

int main(int argc, char* argv[]){

    int keywordlinenumber = 0;  
    int keywordbufferlength = 32;
    int textbufferlength = 128;
    int reallength = 0;  

   clock_t begin = clock();

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
       int sum=0;
    int rank, size, root=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double segment = (double) keywordlinenumber/size;
    int segment_int = ((int) segment) +2;
    char exactkeywords[segment_int][keywordbufferlength];
    // the frequencies of all the keywords
    int exactfrequencies[segment_int];
    int counter=0, counte=0;
 	while((fgets(textbuffer, textbufferlength, fp)) != NULL){
        //parallelization of the region where word matching is done on the harrypotter text file
        for(int i=rank*segment; i<segment*(rank+1);i++){
            p = textbuffer;
            while((p=strstr(p, keywords[i]))!=NULL){
                frequencies[i]++;
                p = p+ strlen(keywords[i]);
            }
        }
        
    }
	//copying out of the exact keywords counted by the process
	//This will aid in sorting and printing out the segment handled by the process
    for(int i=rank*segment; i<segment*(rank+1);i++){
	if(i!=keywordlinenumber){
	strcpy(exactkeywords[counter++], keywords[i]);
  	exactfrequencies[counte++] = frequencies[i];
	}
    }
	
    
    fclose(fp);
    // order the name list
    struct NameAndCount{
        char *name;
        int count;
    };
    struct NameAndCount namelist[keywordlinenumber];
    //Notice that the number of keywords copied to namelist is no longer keywordlinenumber but counter
    //counter keeps track of the number of keywords which the process found the frequency
    //counter is approximately equal to the size of segment but may vary slightly accross processes
    for(int i=0; i<counter;i++){
        namelist[i].name = exactkeywords[i];
        namelist[i].count = exactfrequencies[i]; 
    }

   //bubble sort
    struct NameAndCount temp;
    //notice also that the number of keywords to be sorted is counter not keywordlinenumber
    for(int i=0; i<counter-1; i++){
        for(int j=0; j<counter-i-1; j++){
            if(namelist[j].count > namelist[j+1].count){
                temp = namelist[j+1];
                namelist[j+1] = namelist[j]; 
                namelist[j] = temp;
            }
        }
    }

    printf("\nKeywords counted by process %d\n", rank);
    for(int i=0; i<counter;i++)
	printf("%s, %d\n", namelist[i].name, namelist[i].count);
		
        MPI_Finalize();    
        if(rank==size-1){ 
	
    clock_t end = clock();
    printf("\nTime elpased is %f seconds \n", (double) (end-begin)/CLOCKS_PER_SEC);
    }       
}
