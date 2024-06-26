// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/* CustomException class allows throwing custom exceptions
   that can be caught separately from standard exceptions.
   Inherits from std::exception and provides a constructor
   to set a custom error message, and overrides the what()
   function to return the custom message.*/
class CustomException : public std::exception {
private:
    std::string message;
public:
    // constructor
    CustomException(const char* msg) : message(msg) {}

    // override what() function in std::exception
    const char* what() const noexcept override {
        return message.c_str();
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    throw std::runtime_error("An error occurred in do_even_more_custom_application_logic.");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;
    // try block to wrap do_even_more_custom_application_logic()
    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    // use std::exception to catch exceptions since it will catch all standard exceptions
    } catch (const std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    // create a exception from the CustomException class we created
    throw CustomException("Custom exception thrown");


    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    // check to see if denominator is 0 and throw error if it is
    if (den == 0) {
        throw std::domain_error("Division by zero error");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;
    // wrap divide in a try block
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    // if divide throws exception catch and print out error message
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    // wrap function in try block
    try {
        do_division();
        do_custom_application_logic();
    }
    // catches CustomExceptions first
    catch (const CustomException& e) {
        std::cerr << "Custom exception caught: " << e.what() << std::endl;
    }
    // catches standard exceptions second
    catch (const std::exception& e) {
        std::cerr << "Std::exception caught: " << e.what() << std::endl;
    }
    // catches any uncaught exceptions
    catch (...) {
        std::cerr << "Uncaught exception caught" << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu