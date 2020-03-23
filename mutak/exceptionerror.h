#ifndef EXCEPTIONERROR_H
#define EXCEPTIONERROR_H

#include <iostream>
#include <QString>

class exceptionError{
    int errorCode;
    QString errorMsg;
public:
    exceptionError(int error, QString errorMsg);
    int getErrorCode();
    char * getErrorMsg();
};

#endif // EXCEPTIONERROR_H
