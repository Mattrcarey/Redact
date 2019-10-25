#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//@author Matthew Carey

char symbol[1];//this is used to print symbols before the word
char endingsymbol[1];//this is used to print symbols that are at the end of a work
int space = 0;//this is used to track if their is a space after a work instead of a dash or symbol.


//the readword function reads through the standard input and returns the next work, I use this function until their are no words left.
char* readword(void){	
    char ch;
    static char token[40];//this is for the word
    //char symbol[1];//this is used to deal with symbols
    int i =0;
    ch= getchar();
    if (ch==EOF){//if the first char is EOF the code is at the end of the file and the code exits
	    printf("\n");
	    exit( EXIT_SUCCESS);
    }
    if (!((ch>64 && ch<91)||(ch>96 && ch<123))){//this if statement checks if the first letter is a symbol and if so prints and calls itself recusively
        symbol[0]=ch;
	symbol[1]='\0';
	printf("%s",symbol);

	return readword();	
    }
    //while(ch!=EOF && ch!= ' '&& ch!='\n'){
    while((ch>64 && ch<91)||(ch>96 && ch<123)){	    
	token[i]=ch;//token is filled with chars until a space or EOF is hit.
	ch=getchar();
	i++;
    }
    token[i]='\0';//string terminator
    if(!((ch>64&&ch<91)||(ch>96 &&ch<123))&&ch!=32){
        endingsymbol[0]=ch;
	endingsymbol[1]='\0';
    }
    if(ch==32){
        space = 1;
    }
    return (token); 
}


//This function redacts the words using all modes.
char* redact(char* word, int argc, char **argv){
    for(int y=1;y<argc;y++){//this first for loop checks if -p is on and if so checks if the first char of the word is Uppercase
	if(strcmp(argv[y],"-p")==0){
            if(word[0] <91 &&word[0]>59){//checks if uppercase
                for(int x=0;(unsigned)x<strlen(word);x++){//I cast as unsigned to make a wierd error go away
	            printf("*");
                }
		if(space==1){
	            printf(" ");
		    space = 0;
		}
		printf("%c",endingsymbol[0]);
		endingsymbol[0]='\0';
	        return "match";//this return does nothing but I put it here so it doesn't move on to the rest of this function
            }
        }
    }
    char buffer[strlen(word)];
    strncpy(buffer,word,strlen(word));
    for(int i=0;(unsigned)i<strlen(buffer);i++)
	    buffer[i]=word[i];
    for(int y=1;y<argc;y++){//this checks if -c is being used and if so converts the word to lowercase
        if(strcmp(argv[y],"-c")==0){
            for(int i=0;(unsigned)i<strlen(buffer);i++)
                buffer[i]=tolower(word[i]);
        }
    }
    for(int i = 1; i<argc;i++){//checks every argv >1 to see if their is a match
	for(int y=1;y<argc;y++){//checks if -c is used and if so converts the argv value to lowercase    
            if(strcmp(argv[y],"-c")==0){
	        for(int j = 0;(unsigned)j <strlen(argv[i]); j++)
                    argv[i][j] = tolower(argv[i][j]);
	    }
	}
        if (strcmp(argv[i], buffer) ==0){//checks it the argv matches the word
	    for(int x=0;(unsigned)x<strlen(word);x++){
	        printf("*");
	    }
	    printf("%c",endingsymbol[0]);
	    endingsymbol[0]='\0';
	    if(space==1){
	        printf(" ");
		space=0;
	    }
	    return "match";//this does nothing but I put is here to it wouldnt print *'s and the word
        }
    }
    printf("%s",word);
    printf("%c",endingsymbol[0]);
    endingsymbol[0]='\0';
    if(space==1){
	    printf(" ");
	    space=0;
    }
    return "no_match";//another return that does nothing I just like it. 
}


//main just calls other functions
int main(int argc, char **argv){
    char *word = readword();//sets word to the first word in the standard input
    while(1){//never ending loop eventually ends because of an exit(EXIT_SUCCESS) statment in the readword function
        //printf("%s",endingsymbol);
	redact(word,argc, argv);
	//printf(" ");
	word = readword();//reads the next word
    }
}
