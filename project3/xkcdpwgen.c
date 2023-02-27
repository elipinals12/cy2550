#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORDLIST_SIZE 2048     // maximum number of words in the word list
#define MAX_PASSWORD_LENGTH 64 // maximum length of the generated password

// void function to print full help message
void print_help()
{
    printf("usage: xkcdpwgen [-h] [-w WORDS] [-c CAPS] [-n NUMBERS] [-s SYMBOLS]
                
Generate a secure, memorable password using the XKCD method
                
optional arguments:
    -h, --help            show this help message and exit
    -w WORDS, --words WORDS
                          include WORDS words in the password (default=4)
    -c CAPS, --caps CAPS  capitalize the first letter of CAPS random words
                          (default=0)
    -n NUMBERS, --numbers NUMBERS
                          insert NUMBERS random numbers in the password
                          (default=0)
    -s SYMBOLS, --symbols SYMBOLS
                          insert SYMBOLS random symbols in the password
                          (default=0)");
}

// function to generate a random integer between min and max (inclusive)
int generate_random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// function to read in a wordlist from a file
int read_wordlist(char **wordlist, const char *filename)
{
    FILE *file;
    char word[256];
    int i = 0;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        return -1; // error opening file
    }

    while (fgets(word, 256, file))
    {
        if (i >= WORDLIST_SIZE)
        {
            break; // word list is full
        }
        word[strcspn(word, "\n")] = '\0'; // remove trailing newline
        wordlist[i] = strdup(word);       // allocate memory for the word and add to the wordlist
        i++;
    }

    fclose(file);
    return i; // return number of words read
}

// function to generate an xkcd-style password
void generate_password(char *password, char **wordlist, int wordlist_size, int num_words)
{
    int i;
    int word_index;

    for (i = 0; i < num_words; i++)
    {
        word_index = generate_random_int(0, wordlist_size - 1); // generate a random word index
        strcat(password, wordlist[word_index]);                 // append the word to the password
        if (i < num_words - 1)
        {
            strcat(password, " "); // add a space between words (except for the last word)
        }
    }
}

int main(int argc, char *argv[])
{
    char *wordlist[WORDLIST_SIZE];          // initialize the word list
    char password[MAX_PASSWORD_LENGTH + 1]; // initialize the password buffer
    int num_words = 4;                      // default number of words in password
    char *filename = "words.txt";           // default filename for wordlist
    srand(time(NULL));                      // seed the random number generator with the current time

    // parse command-line arguments
    int i;
    for (i = 1; i < argc; i++)
    {

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) // help option
        {
            print_help();
            return 0;
        }
        else if (argc > 1 + i)
        {
            if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-w") == 0) // words option
            {
                num_words = atoi(argv[i + 1]); // set number of words in password
                if (num_words < 1)
                {
                    printf("Invalid number of words\n");
                    return 1;
                }
                i++;
            }
            if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--caps") == 0) // caps option
            {
                // TODO IMPLEMENT CAPS
            }
            if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--numbers") == 0) // num option
            {
                // TODO IMPLEMENT numbers
            }
            if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symbols") == 0) // sym option
            {
                // TODO IMPLEMENT symbols
            }
        }
        else
        {
            printf("Invalid/missing argument: %s\n", argv[i]);
            return 1;
        }
    }

    int wordlist_size = read_wordlist(wordlist, filename); // read in the wordlist from file
    if (wordlist_size < 0)
    {
        printf("Error opening wordlist file\n"); // error opening file
        return 1;
    }

    // generate password
    memset(password, 0, sizeof(password)); // clear password buffer
    generate_password(password, wordlist, wordlist_size, num_words);
    printf("%s\n", password);

    // free memory allocated for wordlist
    for (i = 0; i < wordlist_size; i++)
    {
        free(wordlist[i]);
    }

    return 0;
}