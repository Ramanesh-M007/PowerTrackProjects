#include<stdio.h> 
#include<ctype.h> 
#include "lexer.h" 


void tokenize(FILE *fp) // Function to read the source file and identify tokens
{
    char ch; // Variable to store each character

    while((ch=getc(fp))!= EOF) // Read one character until end of file
    {
        if(isspace(ch)) // Check if the character is a space or new line
        {
            continue; // Skip white spaces
        }
        else if(isalpha(ch) || ch =='_') // Check if it is the start of an identifier
        {
            readIdentifier(fp, ch); // Read the complete identifier
        }
        else if(isdigit(ch)) // Check if it is a number
        {
            readNumber(fp,ch); // Read the complete number
        }
        else
        {
            switch(ch) // Check for special symbols
            {
                case '/': // Handle comments
                    skipComment(fp); // Skip the comment part
                    break; // Exit the switch

                case '"': // Handle string literals
                    readString(fp); // Read the complete string
                    break; // Exit the switch

                default: // Handle operators and delimiters
                    readOperator(fp,ch); // Process the current symbol

            }
        }
    }
}

void readIdentifier(FILE *fp, char first) // Function to read identifiers and keywords
{
    char str[100]; // Store the identifier
    int i=0; // Start index from 0
    str[i++]=first; // Store the first character
    char c; // Variable to read remaining characters
    while((c=getc(fp))!=EOF) // Read characters until end of file
    {
        if(isalpha(c) || c=='_') // Check if it is still part of an identifier
        {
            str[i++] = c; // Store the character
        }
        else
        {
            ungetc(c,fp); // Put back the extra character
            break; // Stop reading the identifier
        }
    }
    str[i]='\0'; // End the string
    int p = isKeyword(str); // Check whether it is a keyword
    if(p==1) // If it is a keyword
    {
        printf("%-20s %-40s\n",str,"Keyword"); // Print keyword
    }
    else
    {
        printf("%-20s %-40s\n",str,"Identifier"); // Print identifier
    }
}

void readNumber(FILE *fp, char first) // Function to read integer and floating values
{
    char c; // Variable to read characters
    char num[100]; // Store the number
    int i = 0; // Start index from 0

    num[i++] = first; // Store the first digit

    while ((c = fgetc(fp)) != EOF) // Read remaining characters
    {
        if (isdigit(c) || c=='.') // Accept digits and decimal point
        {
            num[i++] = c; // Store the character
        }
        else
        {
            ungetc(c, fp); // Put back the extra character
            break; // Stop reading the number
        }
    }

    int x=0; // Flag to check whether it is a float
    num[i] = '\0'; // End the string
    for(int i=0;num[i]!=0;i++) // Check every character
    {
        if(num[i]=='.') // Check for decimal point
        {
            x=1; // Mark it as a floating value
        }
    }
    if(x==0) // If decimal point is not found
    {
        printf("%-20s %-40s\n", num,"Integer"); // Print integer
    }
    else
    {
        printf("%-20s %-40s\n", num,"Float"); // Print float
    }
}

void readOperator(FILE *fp, char first) // Function to identify operators and delimiters
{
    if(isOperator(first)) // Check whether it is an operator
    {
        printf("%-20c %-40s\n",first,"Operator"); // Print operator
    }

    if(isDelimiter(first)) // Check whether it is a delimiter
    {
        printf("%-20c %-40s\n",first,"Delimeter"); // Print delimiter
    }

}
int isOperator(char ch) // Function to check for operators
{
        char op[]="+-,*/%=<>!&|#@^?~`"; // List of supported operators

        int i; // Loop variable

        for(i=0;op[i]!='\0';i++) // Check each operator
        {
            if(op[i]==ch) // Compare current character
                return 1; // Operator found
        }

        return 0; // Not an operator
}

int isDelimiter(char ch) // Function to check for delimiters
{
        char d[]="(){}[];:"; // List of delimiters

        int i; // Loop variable

        for(i=0;d[i]!='\0';i++) // Check each delimiter
        {
            if(d[i]==ch) // Compare current character
                return 1; // Delimiter found
        }

        return 0; // Not a delimiter
}

void readString(FILE *fp) // Function to read string literals
{
    char ch; // Variable to read characters
    int c=0; // Temporary variable
    char str[100]; // Store the string
    int i=0; // Start index from 0
    while((ch=getc(fp))!=EOF) // Read characters until end of string
    { 
        if(ch=='"') // Check for closing double quote
        {
            str[i]='\0'; // End the string
            printf("%-20s %-40s\n",str,"String"); // Print string literal
            return; // Exit the function
        }
        str[i++] = ch; // Store each character
    }
    return; // Return if end of file is reached
}

void skipComment(FILE *fp) // Function to skip single line comments
{
    char ch; // Variable to read characters

    while((ch=getc(fp))!=EOF) // Read characters until end of line
    {
        if(ch=='\n') // Check for new line
        {
            break; // Stop skipping
        }
    }
    return; // Return to tokenize

}