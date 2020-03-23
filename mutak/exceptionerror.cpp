#include "exceptionerror.h"
#include <iostream>

exceptionError::exceptionError(int errorCode, QString errorMsg){
    this->errorMsg = errorMsg;
    this->errorCode = errorCode;
}
int exceptionError::getErrorCode(){
    return this->errorCode;
}
char * exceptionError::getErrorMsg(){
    char * buff;
    QByteArray ba = errorMsg.toLocal8Bit();
     buff = ba.data();
    return buff;
}
