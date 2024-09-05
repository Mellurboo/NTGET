//
//  Myles "Mellurboo" Wilson 2024
//

#include <Windows.h>
#include <stdio.h>
#include "setup.h"

int main(){
    printf("NTGET Install\n\tby Myles Wilson\n\tCopyleft Licence, See Licence file on Github\n");
    
    // check how making the folders went
    if (folders() != 0){
        printf("an error occured while creating NTGET folders, this error was fatal");
        return -1;
    }else{
        printf("Created NTGET Folders\n");
    }

    if (setNTPath() != 0){
        printf("the installer failed, please ensure the installer ran in administrator and try again!\n");
        return -1;
    }else printf("Updated PATH success\n");

    // curl NTGET client -> C:\NTGET
        // when NTGET actually Exsists lol

    printf("Press enter to exit the NTGET Installer...");
    getchar();
}

int folders(){
    if (CreateDirectory(NTGET_ROOT_PATH, NULL) || GetLastError() == ERROR_ALREADY_EXISTS){
        return 0;
    }else{
        printf("Error %s", GetLastError());
        return -1;
    }
}