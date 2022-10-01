#include "stdlib.h"
#include "stdio.h"
//#include "assert.h"

void createFactorial(int* orig, int amountOfZeros)
{
    int y = 10;
    for(int x = 1; x < amountOfZeros; ++x)
    {
      y *= 10;
    }
    *orig *= y;
}

int main(int argc, char* argv[])
{   
    if (argc < 2) {
        printf("Usage: %s, <path_to_file>\n", argv[0]);
        exit(0);
    }

    char* fileName = argv[1];
    FILE* file = fopen(fileName, "r");

    if(!file)
    {
        printf("Failed to open file!\n");
        exit(0);
    }

    fseek(file, 0L, SEEK_END);
    const int size = ftell(file);
    char buffer[size];
    //char tokens[size];

    rewind(file);

    char c = fgetc(file);
    int i = 0;

    while (c != EOF)
    {
        buffer[i] = c;
        i++;
        c = fgetc(file);
    }
    
    /*for(int i = 0; i < size; ++i)
    {
        if(buffer[i] >= '0' && buffer[i] <= '9')
        {
            printf("%c", buffer[i]);
            for(int x = i+1; x < size; x++)
            {
                if(buffer[x] >= '0' && buffer[x] <= '9') {
                    printf("%c", buffer[x]);
                }
                else { 
                    printf("\n");
                    i=x;
                    break;
                }
                
            }
        }
        
        else if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '/' || buffer[i] == '*') { printf("%c\n", buffer[i]); }
        else if (buffer[i] == ' ' || buffer[i] == '\n') { continue; }
    }*/

    printf("\n\n");

        /*if(!((buffer[0] >= '0') && buffer[0] <= '9'))
        {
            printf("Error! Cannot start with a non-numeric token.\n");
            exit(EXIT_FAILURE);
        }
        
        else if(!((buffer[size-1] >= '0') && buffer[size-1] <= '9'))
        {
            printf("Error! Cannot end with a non-numeric token.\n");
            exit(EXIT_FAILURE);
        }*/


    /*int parsedNumber = 0; //Represents the number that has been parsed from a character to a real number
    int tokenAmount = 0; //Will keep track of the amount of tokens within the array of tokens.
    char parsedTokens[size];

    for(int x = 0; x < size; ++x)
    {
        int factor = 10;
        if(buffer[x] >= '0' && buffer[x] <= '9')
        {
            while(buffer[x] >= '0' && buffer[x] <= '9') {
                factor *= 10;
            }
            /*if(buffer[x] > '0' && buffer[x] <= '9')
            {
                for(int y = x; y < size; ++y)
                {

                }
            }

            else if(buffer == '0') {
                continue;
            }
        }

        if(buffer[x] == '+' || buffer[x] == '-' || buffer[x] == '*' || buffer[x] == '/')
        {
            tokenAmount++;
            switch(buffer[x])
            {
                case '+':
                    parsedTokens[tokenAmount] = '+';
                    break;
                case '-':
                    parsedTokens[tokenAmount] = '+';
                    break;
                case '*':
                    parsedTokens[tokenAmount] = '+';
                    break;
                case '/':
                    parsedTokens[tokenAmount] = '+';
                    break;
            }
        }
    }*/

    int parsedIntegerCount = 0;
    int parsedIntegers[size];
    char parsedSymbols[size-1];
    int parsedSymbolCount = 0;
    int numberCounter = 0;
    int factor = 10;

    for(int x = 0; x < size; ++x)
    {
        if(!((buffer[0] >= '0') && buffer[0] <= '9'))
        {
            printf("Error! Cannot start with a non-numeric token.\n");
            exit(EXIT_FAILURE);
        }
        
        else if(!((buffer[size-1] >= '0') && buffer[size-1] <= '9'))
        {
            printf("Error! Cannot end with a non-numeric token.\n");
            exit(EXIT_FAILURE);
        }

        int num = 0;
        if(buffer[x] >= '0' && buffer[x] <= '9')
        {
            numberCounter++;
            
            if(!(size - x < 2) || buffer[x+1] == '\0')
            {
                int test = buffer[x] - '0';
                parsedIntegers[parsedIntegerCount] = test;
            }

            continue;
        }
        else if(buffer[x] == '+' || buffer[x] == '-' || buffer[x] == '*' || buffer[x] == '/')
        {
            num = buffer[x - numberCounter] - '0';
            createFactorial(&num, numberCounter - 1); //The first number of the set will be parsed.

            for(int y = x - (numberCounter - 1); y < x; ++y)
            {
                int tempNum = 0; // Number to be added into the first number
                tempNum = buffer[y] - '0';
                if(x - y == 1)
                {
                    num+=tempNum;
                    break;
                }
                createFactorial(&tempNum, ((x-y) - 1));
                num+=tempNum;

            }
            parsedIntegers[parsedIntegerCount] = num;
            parsedIntegerCount++;
            parsedSymbols[parsedSymbolCount] = buffer[x];
            parsedSymbolCount++;
            numberCounter = 0;
        }
    }

    int totalNum = parsedIntegers[0];
    printf("Equation: ");
    for(int x = 0; x < parsedIntegerCount + 1; ++x)
    {
        printf("%d ", parsedIntegers[x]);
        if(!(x >= parsedSymbolCount)) {
            printf("%c ", parsedSymbols[x]);
        }
        switch(parsedSymbols[x])
        {
            case '+':
                totalNum += parsedIntegers[x+1];
                break;
            case '-':
                totalNum -= parsedIntegers[x+1];
                break;
            case '*':
                totalNum *= parsedIntegers[x+1];
                break;
            case '/':
                totalNum /= parsedIntegers[x+1];
                break;
        }        

        if(x == parsedIntegerCount)
        {
            printf("= %d", totalNum);
        }
       
    }

    fclose(file);

    return 0;
}