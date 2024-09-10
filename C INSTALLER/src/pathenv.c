//
//  Myles "Mellurboo" Wilson 2024
//  While yes I use 'NT' in my function names, to avoid ambiguity with
//  System functions for Windows they do not go at the front of the name
//

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "setup.h"

char current_path[PATH_VAR_MAX];
DWORD getNTPATH(void);
DWORD path;

int setNTPath() {
    path = getNTPATH();

    if (path == 1){
        printf("There was an Error Getting the PATH environment Variable, this error was fatal\n");
        return -3;
    }

    // Check if the variable is already there, if so this installer has already been run
    if (strstr(current_path, NTGET_ROOT_PATH) != NULL) {
        printf("The path '%s' is already in the PATH variable.\n", NTGET_ROOT_PATH);
        return 0;
    }

    if (formatNTPATH() != 0){
        printf("PATH length exceeds buffer size.\n");
        return -1;
    }

    if (registryNTPATH() == 0){
        printf("Successfully wrote PATH to registry");
    }else if (registryNTPATH() == 1){
        printf("Failed to open registry key.\n");
        return -1;
    }else if (registryNTPATH() == 2){
        printf("Failed to set PATH in the registry.\n");
        return -1;
    }

    // Verify the change worked
    char updated_path[PATH_VAR_MAX];
    if (GetEnvironmentVariable("PATH", updated_path, sizeof(updated_path)) == 0) {
        fprintf(stderr, "Failed to get updated PATH environment variable.\n");
        return 1;
    }

    return 0;
}

/// @brief gets the PATH environment variable
/// @return returns DWORD Path Environment Variable
DWORD getNTPATH(void){
    DWORD len = GetEnvironmentVariable("PATH", current_path, sizeof(current_path));
    if (len == 0) {
        return 1;
    }else return len;
}

/// @brief formats the current path to ensure it fits in the maximum size and contains the new NTGET path
/// @return int
int formatNTPATH(){
    if (path + strlen(";") + strlen(NTGET_ROOT_PATH) < PATH_VAR_MAX) {
        strcat(current_path, ";");
        strcat(current_path, NTGET_ROOT_PATH);
    } else {
        return 1;
    }
    return 0;
}

/// @brief opens and changes the registry to contain the new PATH variable
/// @return int
int registryNTPATH(){
    // Open the registry key for system environment variables to edit PATH
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return 1;
    }

    // Set the new PATH in registry
    if (RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)current_path, strlen(current_path) + 1) != ERROR_SUCCESS) {
        fprintf(stderr, "Failed to set PATH in the registry.\n");
        return 2;
    }

    RegCloseKey(hKey);
    return 0;
}

// Long live Win32API