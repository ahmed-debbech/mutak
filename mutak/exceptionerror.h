#ifndef EXCEPTIONERROR_H
#define EXCEPTIONERROR_H

#include <iostream>

class exceptionError{
    int errorCode;
    char * errorMsg;
public:
    exceptionError(int error, char errorMsg[]);
    int getErrorCode();
    char * getErrorMsg();
};

#endif // EXCEPTIONERROR_H
