#include <stdio.h>
#include "logger.h"
int main()
{
    int loginAttempt=0;
    const char* admin_username;
    const char* admin_passwd;
    while(loginAttempt<2)
    {
        LOG_PRINT("\nenter  admin username");
        scanf("%s",admin_username);
        LOG_PRINT("\nenter admin password");
        scanf("%s",admin_passwd);
        if(admin_username=="usernma" && admin_passwd=="userpa")
        {
            LOG_PRINT("Welcome admin");
            break;
        }
        else
        {
            LOG_PRINT("invalid");
            exit(0);
        }
    }
    return 0;
}
