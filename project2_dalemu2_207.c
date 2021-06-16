#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_CHAIN_BYTES 100
#define MAX_STRING_LENGTH 400
#define MAX_SUBSTR_LENGTH 400
#define FNAME_SIZE 100
#define BSIZE 100	

/*proto types for 
 *- print current sequence
 *- mmenu functionn, save current function, finde a sub-sequence occurence
 *- read Sequence from binary file, inert a sub-string function
 *- remove a sub-sequence function, and replace sequence function.
 */

void menu();
void desplaySequence(char currentSequence[MAX_STRING_LENGTH]);
int saveSequence(char currentSequence[MAX_STRING_LENGTH]);

int findInstances(char currentSequence[MAX_STRING_LENGTH],char subSequence[MAX_SUBSTR_LENGTH]);
int subSequencePosition(char *Sequence, char subsequence[MAX_SUBSTR_LENGTH], int position);

char *DNASequence();

char *spliceInsert(char currentSequence[MAX_STRING_LENGTH]);
char *removeSequence(char currentSequence[MAX_STRING_LENGTH]);
char *sequenceReplace(char currentSequence[MAX_STRING_LENGTH]);

/* 
 * struct 
 * a  composite data type declaration
 * (size_t type)Sequence length and sequence(unsigned char type)
 */

typedef struct _Chain
{
        size_t  SeqLen;  // Number of letters in sequence
        unsigned char Sequence[MAX_CHAIN_BYTES];

}Chain;

/*
 * a void  menu() function
 * displayes 7 menu list and program name when it called called in main function
 */

void menu()
{
	
	printf("\t\tSplicing and Chains of Nucleotide Bases Simulation\n\t\t\tChoose from the following menu options: \n");
	printf("1 - Read a DNA sequence from a file\n");
	printf("2 - Save the current sequence to a file\n");
	printf("3 - Print the current sequence\n");
	printf("4 - Splice and insert a sub-sequence\n");
	printf("5 - Remove a sub-sequence\n");
	printf("6 - Replace a sub-sequence with another sub-sequence\n");
	printf("7 - Exit the program\n");	
	printf("Enter your choice :  ");
}

/* 
 * main function
 * call and exicute every function listed in menu
 */

int main()
{


int  option;
char Buffer[BSIZE];	// 
char *currentSequence;	


   do{	
	menu();		// menu function called 
	fgets(Buffer,100,stdin);
	sscanf(Buffer,"%d",&option);	// read int type from the consule
	
	if(option)
	{	
	    switch(option)
	    {	
		case 1:
		currentSequence=DNASequence();		//Sequence function called 
		break;

		case 2:
		saveSequence(currentSequence);		//save sequence function called
		break;

		case 3:
  		desplaySequence(currentSequence);	// display sequence(print) called
		break;

		case 4:
		currentSequence = spliceInsert(currentSequence);	// insert function 
		break;
			
		case 5:
		currentSequence = removeSequence(currentSequence);	// remove function
		break;
	
		case 6:
		currentSequence = sequenceReplace(currentSequence);	// replace function
		break;
	
		case 7:
		printf("program exit...\n");				// exit the program if 7 is choosen
		exit(0);
		break;
	
		default:
		printf("Invalid  Input choose 1 to 7 \n");		/* if the user enter other than the menu list display error message */
	    }
	}
   }while(1);
return 0;
}
/*
 * DNASequence function a char pointer type function
 * 	open the given file and extracts bits from a binary file then return 
 * 	the sequence
 */
char *DNASequence()
{
   static char inFileName[FNAME_SIZE];
   static char DNASequence[MAX_STRING_LENGTH];
   char x;
   int count=0;
   FILE *inFile;
   Chain file;

   printf("Enter a File Name to Read  :-> ");	// read a file name from console
   fgets(inFileName,MAX_STRING_LENGTH,stdin);
   
   inFileName[strlen(inFileName)-1]='\0';
   inFile=fopen(inFileName,"rb");			//open a file in bynary read moode 
   if (inFile == NULL)
   {
      printf("Error opening file\n");	// if can't open the file display error message and return to main function	
      return 0;
   }
   fread(&file,sizeof(file.Sequence),1,inFile);	// read a bynary file 
   
   char chainValue[file.SeqLen];	
   for(int i=0;i<sizeof(file.SeqLen)*3;i++)	// extract the bynary file bits 
   {
      for(int j=0;j<4;j++)
      {
         if((count)==file.SeqLen)
            break;
         if(j==0)				// check the current two bits and assign the corresponding char value
         {
            x=file.Sequence[i]>>6;	// shift the bits 6 times to the right 
            x=x&3;
            if(x==0)
   	         chainValue[count]='A';
            else if(x==1)
                 chainValue[count]='C';
            else if(x==2)
                 chainValue[count]='G';
            else if(x==3)
                 chainValue[count]='T';
	 }
        else if(j==1)			// check the current two bits and assign the corresponding char value
        {
            x=file.Sequence[i]>>4;	// shift the bits 4 times to the right
            x=x&3;
            if(x==0)
               chainValue[count]='A';
            else if(x==1)
               chainValue[count]='C';
            else if(x==2)
               chainValue[count]='G';
            else if(x==3)
               chainValue[count]='T';
	}
        else if(j==2)			// check the current two bits and assign the corresponding char value
        {
             x=file.Sequence[i]>>2;	// shift the bits  times to the right
             x=x&3;
             if(x==0)
               chainValue[count]='A';
             else if(x==1)
               chainValue[count]='C';
            else if(x==2)
               chainValue[count]='G';
            else if(x==3)
               chainValue[count]='T';
        }
        else				// check the current two bits and assign the corresponding char value
        {
            x=file.Sequence[i];
            x=x&3;
            if(x==0)
               chainValue[count]='A';
            else if(x==1)
               chainValue[count]='C';
            else if(x==2)
               chainValue[count]='G';
            else if(x==3)
               chainValue[count]='T';
        }
            count++;
     }
  }
chainValue[strlen(chainValue)-1]='\0';
strcpy(DNASequence,chainValue);		// copy the chainValue to new array (static char type)
fclose(inFile);		// close  file
return DNASequence;
}

/*
 *  save function writes the current sequence on file
 *  check current sequence is existed,
 *  open a new file, then change the char value in bits 
 *  at the end  write the current sequence bit representation on the file  in bynary format
 */


int saveSequence(char currentSequence[MAX_STRING_LENGTH])
{
	char outFileName[FNAME_SIZE];
	FILE *outFile;
	int flag=0;
	Chain file;

	if(currentSequence != NULL)	// check current sequence if not null 
        {
		currentSequence[strlen(currentSequence)]='\0';	// put a null terminator at the end of the sequence
		printf("Enter a File Name to write  :-> ");	
	 	fgets(outFileName,FNAME_SIZE,stdin);	// read file name from consule 
        
		outFileName[strlen(outFileName)-1]='\0';	

        	outFile = fopen(outFileName,"wb");
        	if (outFile == NULL)
         	{
			printf("Error opening file\n");
                	flag=0;					// set the flag to zero if it is unable to open the file
         	}
		else
		{
			for(int i=0; i<strlen(currentSequence); i++)
        		{
       			   if(currentSequence[i]=='A')		//// change 'A' to bit represantation '00'
                	   {
                		file.Sequence[i/4]= 0<<(6-(2*(i%4)))| file.Sequence[i/4];
	       		   }
	      
		          else if(currentSequence[i]=='C')	// change 'C' to  bit represantation '01'
                	   {
                		file.Sequence[i/4]= 1<<(6-(2*(i%4)))| file.Sequence[i/4];
                	   }
	       
			  else if(currentSequence[i]=='G')	// change 'G' to  bit represantation '10'
               		   {
                		file.Sequence[i/4]= 2<<(6-(2*(i%4)))| file.Sequence[i/4];
               		   }
	       		  else if(currentSequence[i]=='T')		// change 'T' to  bit represantation '11'
               		   {
                		file.Sequence[i/4]= 3<<(6-(2*(i%4)))| file.Sequence[i/4];
                	   }

   	             	}
          	     file.SeqLen=strlen(currentSequence);
        	     fwrite(&file,sizeof(Chain),1,outFile);		//write the bit representation on file in bynary moode
       		     fclose(outFile);
		     flag=1;	// set the flag if file wrighting process is successful
	}
	}
	else
	    printf("There is no Sequence to Save\n");		//error message if the currentSequence array has no data
	return flag;						
}
/*
 * despllaySequence function  
 * write the current Sequence on consule
 */

void desplaySequence(char currentSequence[MAX_STRING_LENGTH])
{
	
 	if(currentSequence != NULL)	// check current sequence if not null
	{	

		printf("Current sequence is: %s\n ",currentSequence);	// print the current sequence
    	}
	else
		printf("current sequence is empity\n");			// print if current sequence is NULL
}
/*
 * Insert  function 
 * 	find the position and insert the sub-sequence
 * 	read the place and the sub-sequence to be inserted from the console
 * 	return the modified sequence.
 */
char *spliceInsert(char currentSeq[MAX_STRING_LENGTH])
{
	
	char Buffer[MAX_SUBSTR_LENGTH];
	char subSeq[MAX_STRING_LENGTH];
	char placeLocater[MAX_SUBSTR_LENGTH];

	char newSeq[MAX_STRING_LENGTH];
	char temp[MAX_STRING_LENGTH];
	int position=0,j=0;

	int subSeqLen;

	int instances;
	if(currentSeq!=NULL)		// check current sequence if not null
	{	
		
		
		printf("Enter Sub-Sequence of Nucleotide letterse to Insert :-> ");
		fgets(Buffer,MAX_SUBSTR_LENGTH,stdin);
    		sscanf(Buffer,"%s",subSeq);		// red sub-sequence from consule
		
	 	printf("Enter The place to insert the sequence :-> ");
		fgets(Buffer,MAX_SUBSTR_LENGTH,stdin);
		sscanf(Buffer,"%s",placeLocater);	// read the place string
	
		subSeq[strlen(subSeq)]='\0';
        	placeLocater[strlen(placeLocater)]='\0';	
	
		instances = findInstances(placeLocater,currentSeq);	// check the occurence of the place locater
		if(instances)			// check if place locator is existed
		{
			
			if(subSequencePosition(subSeq,placeLocater,position)==-1)	// check If the sub-sequence happens to contain the subsequence after which to insert
			{	
			subSeqLen=strlen(subSeq);	
 			strcpy(newSeq,currentSeq);
			position = subSequencePosition(currentSeq,placeLocater,position);	// find the first index  place locater sub-sequence  position 
			
				if(strlen(newSeq)>=MAX_STRING_LENGTH)			// if the current sequence has max-string length
				{
					printf("Crrent Sequence holds the maximum sequence!");
				}
				else
				{
					int c=0;
					for(int k=0;k<instances;k++)			// loop run number of sub-sequence instances in the current sequence times 
					{	
						if(c>=MAX_STRING_LENGTH)		// check the current sequence array index
                        				break;
						else{
							j=0;
							c=0;
							strcpy(temp,newSeq);
							for(int i=0;i<position;i++)	// copy the chars upto place indecator index
							{
						
								if(c>=MAX_STRING_LENGTH)
                        	                	  	      	break;
							else
							  {
								newSeq[i]=newSeq[i];	
							  }
								c++;
							}
							for(int i=0;i<subSeqLen;i++)	// copy the sub sequence chars upto place indecator index
       					 		{
								if(c>=MAX_STRING_LENGTH)
                                                		   break;
								else{
        				        			newSeq[position + i]=subSeq[i];
								}	c++;
					
	       					 	}	
							for(int i=position;i<strlen(temp);i++)	// copy the existed chars 
       		 					{
		
            							if(c>=MAX_STRING_LENGTH)
                                               				 break;
								else
								{
									newSeq[position + subSeqLen+j]= temp[i];
									j++;
								}
								c++;
       			 				}
							strcpy(currentSeq,newSeq);
							position = subSequencePosition(currentSeq,placeLocater,position + 1); // find the first index  place locater sub-sequence  position
							currentSeq[MAX_STRING_LENGTH]='\0';

	       					}
					}
				}
			}
			else
			{
				 	printf("\n Sub-sequence happens to contain the subsequence after which to insert");
			}
		}
		else
		{
			printf("\n place locater subsequence not found in the current sequence");
		}	
	}
	else
	{	
		printf("sequence is not existed");
	}
	return currentSeq;
}
/*
 * remove sequence function
 * find the subsequence to be removed and 
 * remove it from the current sequence
 */
char *removeSequence(char currentSeq[MAX_STRING_LENGTH])
{
	char subSeq[MAX_SUBSTR_LENGTH];
	char Buffer[MAX_SUBSTR_LENGTH];
        
        int subSeqLen;
	int SeqLen;  
	int x;      
	int instances;
	if(currentSeq!=NULL)		// check current sequence if not null
        {
	
		printf("Enter Sub-Sequence of Nucleotide letterse to Remove :-> ");	// read a subsequence
   		fgets(Buffer,MAX_STRING_LENGTH,stdin);
     		sscanf(Buffer,"%s",subSeq);

     		subSeq[strlen(subSeq)]='\0';
		instances = findInstances(subSeq,currentSeq);
                if(instances)			// check if place locator is existed in the current sequence
                {
     		
	    		subSeqLen=strlen(subSeq);
			SeqLen=strlen(currentSeq);

			char *posi = currentSeq;
			while((posi=strstr(posi,subSeq))!= NULL )	//use strstr function to get the subsequence index to be removed
       			 {
       			     x= SeqLen-(posi + subSeqLen - currentSeq);
          	    	     memmove(posi, posi + subSeqLen, x + 1);
        	         }
		}
		else
			printf("\nsubsequence is not found in the current sequence");	// 
	}
        else
                printf("current sequence is not existed");	// current sequence is empty
        return currentSeq;
}

/*
 * sequenceReplace funcion 
 * find the subsequene and replace it with new sub sequence
 */
char *sequenceReplace(char currentSeq[MAX_STRING_LENGTH])
{

  char subSeq[MAX_STRING_LENGTH];
  char newSubSeq[MAX_STRING_LENGTH];
  static char newArray[MAX_STRING_LENGTH];
  char Buffer[MAX_SUBSTR_LENGTH];
  int position=0;
  int newSubSeqLen;
  int instances;
  if(currentSeq!=NULL)	 // check current sequence if not null
    {
      	printf("Enter Sub-Sequence of Nucleotide letterse to Remove :-> ");   
	fgets(Buffer,MAX_STRING_LENGTH,stdin);
        sscanf(Buffer,"%s",subSeq);	// read subSequence from the consule
	printf("Enter The sub-Sequence to replace the sequence :-> ");
	fgets(Buffer,MAX_STRING_LENGTH,stdin);
       	sscanf(Buffer,"%s",newSubSeq);		// read new subsequence which replace the existing one
		
	subSeq[strlen(subSeq)]='\0';
      	newSubSeq[strlen(newSubSeq)]='\0';

	newSubSeqLen=strlen(newSubSeq);
        instances = findInstances(subSeq,currentSeq);
        if(instances)				// check the occurence of the subsequence
          {
 	    static char newSeq[MAX_STRING_LENGTH];
            strcpy(newSeq,currentSeq);
             position = subSequencePosition(currentSeq,subSeq,position);
       	     int j;
	     char temp[MAX_STRING_LENGTH];
	     for(int i=0;i<instances;i++)
        	{
 	               j=0;
                      				 	
               	       strcpy(temp,newSeq);
               	       for(int i=0;i< position - strlen(subSeq);i++)
               	 	{
			  newSeq[i]= newSeq[i];
			}
		
     		  for(int i=0;i<newSubSeqLen;i++)
                   {
                        newSeq[(position-strlen(subSeq))+i]=newSubSeq[i];
		   }
	     	  for(int i=position;i<strlen(temp);i++)
 	          {
		   
	       		newSeq[position-strlen(subSeq) + newSubSeqLen + j]= temp[i];
			j++;
		   }
           	  strcpy(newArray,newSeq);
           	  position = subSequencePosition(newArray,subSeq,position + strlen(subSeq));
              	  currentSeq[MAX_STRING_LENGTH]='\0';  
		}
	     } 
	  else
		{
	    		printf("\n Sub Sequene is not Foutnd");
		}
	}       
		else
          	      printf("sequence is not existed");
        return newArray;
}
/*
 * find instance function returns number of 
 * the occurences of a sub string with in string
 */	
int findInstances(char subStr[MAX_SUBSTR_LENGTH], char currentSeq[MAX_STRING_LENGTH])
{

	int currentSeqLen;
	int counter=0;
	int instance=0;
	int j,i=0;

	currentSeqLen=strlen(currentSeq);

	while(i<currentSeqLen)
	{
	
		counter=0;
		j=0;
		while(currentSeq[i]==subStr[j])
		{
			counter++;
			i++;
			j++;	
		}
			if(counter==strlen(subStr))
			{
				counter=0;
				instance++;
			}
		else
		{
			i++;
		}
	}
	return instance;
}
/* subsequence positon function returns 
 * the index of a sub sequence in the string
 * */
int subSequencePosition(char Sequence[MAX_STRING_LENGTH], char subSequence[MAX_SUBSTR_LENGTH], int position)
{
	char temp[MAX_STRING_LENGTH];
	char *pIndex;
	int index;
	strncpy(temp,(Sequence + position),(strlen(Sequence) - position));
	pIndex=strstr(temp,subSequence);
	if(pIndex!=0)
	{
		index = pIndex - temp + position + strlen(subSequence);

	}
	else
	{
		index=-1;
	}
		return index;
} 
