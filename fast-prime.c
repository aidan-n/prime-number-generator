//Aidan
//Aidan.Normanly001@umb.edu

//Please read the header file.

#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    int user_input[argc-1];

    //get user input
    if (argc <= 1)
    {
        printf("error: missing command line argument\n");
        return 0;
    }

    i = 0;
    while (i < argc-1)
    {
        user_input[i] = atoi(argv[i+1]);
        i++;
    }

    //test primality of each inputted number
    i = 1;
    while (i < argc)
    {
        printf("%-5d: ", user_input[i]);//format 5 places before ':'

        int prime_boolean = is_prime(user_input[i]);
        if (prime_boolean == 1)
        {
            printf("prime\n");
        }
        if (prime_boolean == 0)
        {
            printf("not prime\n");
        }
        i++;
    }

}


int is_prime(int maybe_prime)
{

    //check if file exists yet. If it doesn't: make one, and check primes
    //using code. If maybe_prime < max_file_number: check in file.
    if (access("primes.log", F_OK) == -1 )
    {
        new_file();
    }

    if (maybe_prime < 2)
    {
        return 0;
    }

    if (maybe_prime == 2)
    {
        //store to file
        return 1;
    }

    //check the file. and if it's divisible by one of those numbers, return 0.

    int after_check = check_file(maybe_prime);
    //if after_check == 0: maybe_prime was divisible by a number in the file. return 0.
    //if after_check == 1: it's prime. return 1.
    //otherwise after_check is the number to start searching from.

    if (after_check == 0)
    {
        return 0;
    }
    
    if (after_check == 1)
    {
        return 1;
    }


    //boolean so we can keep going even if maybe_prime is prime.
    //this allows us to store numbers up through sqrt(maybe_prime) in the log.
    int ret_prime = 1;

    int i = after_check + 1; // last number in the log + 1
    while (i <= sqrt(maybe_prime))
    {
        //is maybe_prime divisible by i?
        if (maybe_prime % i++ == 0)
        {
            ret_prime = 0;
            //note that incrementing i here can cause
            //a number above sqrt(maybe_prime) to be added
            //to the log.
        }

        //is i prime?
        int j = 2;
        while (j <= i/2)
        {
            if (i % j == 0)
            {
                //it's not prime.
                //go back to incrementing i
                break;        
            }
            if (j == i/2)
            {
                //i is prime. add it to end of the log.
                FILE *primes;
                primes = fopen("primes.log", "a");
                fprintf(primes, "%s%d", "\n", i);
                fclose(primes);
                break;
            }
            j++;
        }
    }
    return ret_prime;

}

int check_file(maybe_prime)
{
    int file_num; //number in the file
    char line[16]; //char array for the number

    FILE *primes;
    primes = fopen("primes.log", "r");
 
    int num = 2;

    while (!feof(primes))
    {
        fscanf(primes, "%d", &num);
        if (maybe_prime % num == 0)
        {
            fclose(primes);
            return 0;
        }
        
    }
    fclose(primes);

    //if maybe_prime exceeds the max value in the log entries,
    //we need to continue checking numbers above that entry.
    if (maybe_prime > num)
    {
        return num;
    }

    //else we know it's prime.
    return 1;
}

int new_file(void)
{
    //creates a new file "primes.log", with "2" and "3" in it.
    FILE *primes;
    primes = fopen("primes.log", "w");
    fprintf(primes, "2");
    fprintf(primes, "\n3");
    fclose(primes);
}




