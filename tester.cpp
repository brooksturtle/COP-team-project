#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <limits>
#include "fileObject.h"
#include "memory.h"
#include "dirent.h"
#include "FileIO.h"

using namespace std;
vector<string> splitString(string);

int main()
{
    vector<string> stuff;

    vector<fileObject> init;
    memory test(init);

    if(!test.initializeMemory()){
        cout << "Error reading memory. Shutting down." << endl;
        return 1;
    }



    int choice;
    string tag1;
    string tag;
    string file;
    bool keepGoing = true;
    char y[1000];
    vector<string> fileList;
    int counter;
    int enormity;
    string decision = "x";



    while(keepGoing)
    {
        //1 addtag, 2 deleteTag, 3 print, 4 search, 5 stringifyMemory, 6 quit
        cout<<"1. Add a tag\n2. Delete a tag\n3. Print\n4. Search\n5. Save\n6. Quit"<<endl;
        cin>>choice;
        while (choice >6 || choice < 1 || cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout<<"Invalid Input"<<endl;
            cin>>choice;
        }

        switch(choice)
        // takes one string at a time.
        {
			int checker;
            case 1:
                
                cout<<"To what file would you like to add a tag to?"<<endl;
                cin>>file;
                if(test.checkFileExistence(file) == -1)
                {
					cout << "A file with that name does not exist. Returning to menu." << endl;
					break;
				}
                cout<<"What tags would you like to add?"<<endl;
                // this takes in whole line cin as a string tag
                // converts char array into vector of individual words.
                cin>>tag1;
                cin.getline(y, 1000);
                tag = y;
                tag = tag1+ tag;
                stuff = splitString(tag);

                /// takes one string at a time
                for (unsigned int i =0; i<stuff.size(); i++)
                {
                        test.switchAdd(stuff[i], file);
                }
                break;
            case 2: {
                
                cout<<"What file would you like to delete the tag from?"<<endl;
                cin>>file;
                checker = test.checkFileExistence(file);
                if(checker == -1)
                {
					cout << "A file with that name does not exist. Returning to menu." << endl;
					break;
				} 
				
				
				
                
				cout<<"Which tag would you like to delete?"<<endl;
                cin>>tag;
           
                test.deleteTagFromFile(file, tag);
                
               
                break;
			}

            case 3:
                test.printMemory();
                break;

            case 4: 
                cout<<"What tag would you like to search for?"<<endl;
                cin>>tag;
                fileList = test.searchForFilesWithTag(tag);
                if(fileList.size() == 0)
                {
					cout << "There are no files with that tag. Returning to menu." << endl;
					break;
				}

                counter = 0;
                enormity = fileList.size();
                cout<<"Files with tag '"<<tag<<"': ";
                while (counter < enormity)
                {
                    cout<<fileList[counter]<<" ";
                    counter++;
                }
                break;
			

            case 5:
                test.stringifyMemory();
                cout << "Tags and file(s) saved!" << endl;
                break;
            case 6:
                keepGoing=false;
                cout<<"Save Changes? y/n"<<endl;
                while (decision != "y"  && decision != "n" || cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin>>decision;
                transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
                if (decision != "y" && decision!= "n")
                    cout<<"Invalid Input"<<endl;
            }
            if (decision=="y")
            {
                test.stringifyMemory();
            }
                cout << "Closing program.";
                break;
        }
        cout<<endl;
    }

    return 0;
}


vector<string> splitString(string tagString)
 {
    string buf; // Have a buffer string
    stringstream ss(tagString); // Insert the string into a stream

    vector<string> tags; // Create vector to hold our words

    while (ss >> buf)
        tags.push_back(buf);

     return tags;
}
