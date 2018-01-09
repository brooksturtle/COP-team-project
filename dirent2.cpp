#include <dirent.h>
#include <cstdio> // for the snippet
#include <iostream> // for output
#include <unistd.h>
#include <sys/stat.h>

void listdir (const char *path);

int main ()
{
    if (!mkdir (".\\dream.in.code", NULL))
    {
        printf ("mkdir() unsuccessful. Terminating...");
        return (1); // exit after a 3 second pause
    } // otherwise, it was created, so we can continue
    std::cout << "dream.in.code folder created successfully!"
              << "Currently viewing:\n%s\n" << getcwd(NULL,0);
    listdir (".");
    std::cout << "\nMoving into our newly created directory";
    chdir (".\\dream.in.code");
    std::cout << "\nCurrently viewing:\n%s\n" << getcwd(NULL,0);
    listdir (".");
    chdir ("..\\"); // move back one
    rmdir (".\dream.in.code");
    listdir (".");

    std::cin.get (); // pause for input
    return (0); // program was executed successfully

}

void listdir (const char *path)
{
    // first off, we need to create a pointer to a directory
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    pdir = opendir (path); // "." will refer to the current directory
    struct dirent *pent = NULL;
    if (pdir == NULL) // if pdir wasn't initialised correctly
    { // print an error message and exit the program
        printf ("\nERROR! pdir could not be initialised correctly");
        return; // exit the function
    } // end if

    while (pent = readdir (pdir)) // while there is still something in the directory to list
    {
        if (pent == NULL) // if pent has not been initialised correctly
        { // print an error message, and exit the program
            printf ("\nERROR! pent could not be initialised correctly");
            return; // exit the function
        }
        // otherwise, it was initialised correctly. let's print it on the console:
        printf ("%s\n", pent->d_name);
    }

    // finally, let's close the directory
    closedir (pdir);
}
