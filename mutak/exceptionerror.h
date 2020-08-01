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
/**
 * @file exceptionerror.h
 *
 * @brief The exception classes for error
 *
 * @author Ahmed Debbech
 *
 */
#ifndef EXCEPTIONERROR_H
#define EXCEPTIONERROR_H

#include <iostream>
#include <QString>

/**
 * A genral class for all exceptions raised by the app for errors
 * 
 * This class is used for any error detection in the app.
 */
class exceptionError{
    int errorCode; ///< error code
    QString errorMsg; ///< error message
public:
    exceptionError(int error, QString errorMsg);
    int getErrorCode();
    char * getErrorMsg();
};

#endif // EXCEPTIONERROR_H
