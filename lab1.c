//**************************************************************************
//Lab :		1  
//Date: 	09-26-15
//Author: 	Tark Raj Ojha 
//Purpose:  The purpose of this lab is to write a C program to duplicate
//			(a subset of ) the functioanlity of the Linux/UNIX "tr" command.
//			'tr' is a command that goes through every character in the input
//			stream, writing the characters out, but possibly eithe traslating
//			characters or deleting particular characters.

//Goal:  	The program need to accept only the -d option to delete the ch, 
// 			translate the particular ch & to accept the limited set of 
//			"interpreted charaters".
//**************************************************************************

	// C libraries
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>
	
	//Prototypes:
	int chpos(char ch, char *set);
	void interp_set(char  *c_set);
	
	
	/* 
	 * This is main program which take reads the input from Standard input 
	 * and writes the output accordling users input.
	 */
	
	int main(int argc, char *argv[])
	{		
			//argc should be 3 for correct execution 
			if ( argc != 3 ) 
				{
					//print the error message
					
					fprintf(stderr,"There is an error %s",strerror(errno));
					return EXIT_FAILURE;
				}
				
				// calling interpt_set function to the main program
				interp_set(argv[2]);
				interp_set(argv[1]);
		
				int next; // hold input char
					for (int i=0; i<argc; i++)
						//printf("argv[%d]: %s\n",i,argv[i]);
						
							// checks -d charcters to go to the delete mode
						
							if (strcmp(argv[1],"-d")==0) 
							{
								//printf("Delete mode:\n");
								
									// loop through all input character
									while ((next=getchar()) != EOF)
									
									// camparing the input next  and arg[2]
										if (chpos(next,argv[2]) == -1)
										
											// if input is not found in argv[2] print the characters
											putchar(next);
											
											//checking an error while calling getchar & putchar
												if (ferror(stdin))
												{   
													// print an error while calling getchar/putchar
													perror("Error");
														return (EXIT_FAILURE);
												}
							}
		
							else 
							{
								// translate mode agrv[2] array
								char *TSET=argv[2];
								int f; // holds the input argv1
		
								//printf("Translate mode:\n");
								
								// to check the length of argv2
								int len=strlen(argv[2]);
								//printf("%d",len);
									//looping the input character next 
									while ((next=getchar()) != EOF)
									{
										
										f= chpos(next,argv[1]);
										
										// when argv1 is found 
											if (f!=-1)
											{
												//if arv2 length is greater than argv1
												if(len>f)
													
													// print argv2 lenth's  character
													putchar(TSET[f]);
												else
					
													putchar(TSET[strlen(argv[2])-1]);
		
											}
											else
											{
												// print the input
												putchar(next);
											}
									}
								
								// checking input error
								if (ferror(stdin))
								{
									perror("Error");
									return (EXIT_FAILURE);
								}
							}
							
				return EXIT_SUCCESS;
	}
	
	/*
	 * This function is using to iterate through the char's in the 'set'
	 * array looking for a match with character (for loop) and if statement helps 
	 * to match that characher and return an int p , if char found (true) in the 
	 * the array otherwise -1 for false.
	 */
	int chpos(char ch, char *set)
		{
	
			for (int p=0; p<strlen(set); p++)
				if (set[p] == ch)
					return p;
			return -1;
		}
	
	
	/*
	 * This function is taking a character set argument string as input, 
	 * and convert any of the specific interpreted character sequence to 
	 * their corresponding single character.
	 */
	 
	void interp_set(char *c_set)
	{
		int in = 0;			// hold input read characters 	
		int out = 0;		// hold output write characters
		int len = strlen(c_set); // checking the length of the charactets
			while (in < len) 
				{
					if (c_set[in] == '\\')  // if character find '/' then it checks the swich 
											//statement to the following interpreted characters
						{
							switch (c_set[in+1]) 
								{
									case 'n':
									c_set[out++] = '\n';
									in = in+2;
									break;
									
									case 'r':
									c_set[out++] = '\r';
									in = in+2;
									break;
									
									case 't':
									c_set[out++] = '\t';
									in = in+2;
									break;
									
									case '\\':
									c_set[out++] = '\\';
									in = in+2;
									break;
									
									default: c_set[out++] = c_set[in++];//increment the position
								}	
						}
					else 
						c_set[out++] = c_set[in++];
				}
			c_set [out] = '\0';  // null character sentinal
			
			// no value return -void function
		return ;	
	}
	
	
	
