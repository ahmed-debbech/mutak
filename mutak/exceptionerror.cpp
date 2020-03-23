#include "exceptionerror.h"
#include <iostream>

exceptionError::exceptionError(int errorCode, char * errorMsg){
    this->errorMsg = errorMsg;
    this->errorCode = errorCode;
}
int exceptionError::getErrorCode(){
    return this->errorCode;
}
char * exceptionError::getErrorMsg(){
    return this->getErrorMsg();
}
