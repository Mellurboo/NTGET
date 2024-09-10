//
//  [=>                 Myles Wilson 2024                   <=]
//                  https://github.com/Mellurboo

//
//  This version of the write registry file has been completly stripped
//  of all printf statements and move to rust becuase i hate the cmd it uses
//  when in elevated permissions lol
//

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "write_registry.h"

char current_path[PATH_VAR_MAX];
DWORD getNTPATH(void);
DWORD path;

int32_t ntpath(void) {
    path = getNTPATH();

    if (path == 1){
        return 1;
    }

    // Check if the variable is already there, if so this installer has already been run
    if (strstr(current_path, NTGET_ROOT_PATH) != NULL) {
        return -1;
    }

    if (formatNTPATH() != 0){
        return -2;
    }

    if (registryNTPATH() == 0){
    }else if (registryNTPATH() == 1){
        return -3;
    }else if (registryNTPATH() == 2){
        return -4;
    }

    // Verify the change worked
    char updated_path[PATH_VAR_MAX];
    if (GetEnvironmentVariable("PATH", updated_path, sizeof(updated_path)) == 0) {
        return -5;
    }

    return 0;
}

/// @brief gets the PATH environment variable
/// @return returns DWORD Path Environment Variable
DWORD getNTPATH(void){
    DWORD len = GetEnvironmentVariable("PATH", current_path, sizeof(current_path));
    if (len == 0) {
        return -1;
    } else return len;
}

/// @brief formats the current path to ensure it fits in the maximum size and contains the new NTGET path
/// @return int
int formatNTPATH(){
    if (path + strlen(";") + strlen(NTGET_ROOT_PATH) < PATH_VAR_MAX) {
        strcat(current_path, ";");
        strcat(current_path, NTGET_ROOT_PATH);
    } else {
        return -1;
    }
    return 0;
}

/// @brief opens and changes the registry to contain the new PATH variable
/// @return int
int registryNTPATH(){
    // Open the registry key for system environment variables to edit PATH
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return -1;
    }

    // Set the new PATH in registry
    if (RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)current_path, strlen(current_path) + 1) != ERROR_SUCCESS) {
        return -1;
    }

    RegCloseKey(hKey);
    return 0;
}
