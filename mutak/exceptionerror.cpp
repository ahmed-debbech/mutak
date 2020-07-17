/*
    Copyright (c) 2020 Ahmed Debbech

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#include "exceptionerror.h"
#include <iostream>

/**
 * Contructor for exceptionError class 
 * 
 * It sets the error code and error message that will be used by the class.
 * @param int errorCode : the error code that will identiy the error
 * @param QString errorMsg : the error's message that will be displayed alongside the error code.
*/
exceptionError::exceptionError(int errorCode, QString errorMsg){
    this->errorMsg = errorMsg;
    this->errorCode = errorCode;
}
/** 
 * It gets the error code
 * @return int : the error code
*/
int exceptionError::getErrorCode(){
    return this->errorCode;
}
/**
 * It returns the error message in array of char
 * 
 * It converts the QString that contains the message initially to a char* pointer that points 
 * to the first place in array. This should be converted to char * to be able to use it in QMessageBox::tr
 * @return char * : a pointer to the first letter of the error message
 */
char * exceptionError::getErrorMsg(){
    char * buff;
    QByteArray ba = errorMsg.toLocal8Bit();
     buff = ba.data();
    return buff;
}
