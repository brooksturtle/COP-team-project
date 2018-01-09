#include <dirent.h> // directory header
#include <stdio.h> // printf()
#include <stdlib.h> // exit()
#include <iostream> // for output
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio> // for the snippet


int main () // entry point of the program
{
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    struct dirent *pent = NULL;
    std::cout<<"Current Directory \n"<< getcwd(NULL, 0);
    chdir ("..\\");
    std::cout<<"\nMoved back, now in \n"<<getcwd(NULL, 0)<<"\n";


    pdir = opendir ("."); // "." will refer to the current directory
    if (pdir == NULL) // if pdir wasn't initialised correctly
    { // print an error message and exit the program
        printf ("\nERROR! pdir could not be initialised correctly");
        exit (1); // exit the program, using 1 as the status (most common for a failed execution)
    } // end if
    while (pent = readdir (pdir)) // while there is still something in the directory to list
    {
      if (pent == NULL) // if pent has not been initialised correctly
      { // print an error message, and exit the program
          printf ("ERROR! pent could not be initialised correctly");
          exit (3);
      }
      // otherwise, it was initialised correctly. let's print it on the console:
      printf ("%s\n", pent->d_name);
    }
    closedir (pdir);
    return 0;// everything went OK
  }
