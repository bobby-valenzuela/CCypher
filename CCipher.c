#include <stdio.h>
#include <string.h>


void cypherize(char* message);
int isUpper(int ascii);
int isLower(int ascii);

int main(){

    // Read input and write to file
    printf("Enter a message to encode (only letters): ");
    char msg[1000];

    // Using %99 instead of %s as it allows for spaces - stops at newline char
    scanf("%99[^\n]",msg);

    // ROT-13 the msg  - changes in place so no need to return the string
    cypherize(msg);
    char* enc_msg_ptr = msg;

    // Write to file
    FILE* fptr;
    fptr = fopen("encoded.txt", "w");
    fputs(enc_msg_ptr, fptr);
    fclose(fptr);

    // Read file
    fptr = fopen("encoded.txt", "r");
    char content[1000];
    if(fptr != NULL){

        while(fgets(content,1000, fptr)){

            printf("Encoded Message: %s\n",content);

        }

    }else{
        printf("File could not be opened\n");
    }

    return 0;

}

int isUpper(int ascii){ return (ascii >= 65  && ascii <= 90) ? 1 : 0;}
int isLower(int ascii){ return (ascii >= 97  && ascii <= 122) ? 1 : 0;}

// Implement ROT-13 Caesar Cypher
void cypherize(char* message){
    int i;
    int key = 13;
    char ch;
    int msg_len = strlen(message);

    for(i = 0; i < msg_len; ++i){
        ch = message[i];

        if(message[i] == '\0') break;
        int ascii = (int) ch;
        int isLowerCase = isLower(ascii);
        int isUpperCase = isUpper(ascii);

        if( isLowerCase || isUpperCase ){
            // Rotate +13
            ascii = (int) ch + key;
            ch = (char) ascii;

            // If past 'z' - loop around
            if( isLowerCase && ascii > 122){
                ascii -= 122;
                ascii += 96;
                ch = (char) ascii;
            }

            // If past 'Z' - loop around
            if( isUpperCase && ascii > 90){
                ascii -= 90;
                ascii += 64;
                ch = (char) ascii;
            }
            message[i] = ch;
        }

    }

}
