# Multiplication
Repository for Big Homework.

This is repository for Big HW ads Workshop. 

The main file is project.cpp. It includes 2 header file LargeInteger.h for LargeInteger class and Multiplicator.h for algorithm classes.

Uvaliable methods at main:
DAC::test() - test of Divide and Conquer algorithm, it prints errors if they are and return true, if it works correctly (on small numbers) anf false otherwise
Same goes for KM::test() and GSM::test()

DAC::time(k) - returns milliseconds required for Divide and Conquer algorithm to muliply 2 numbers with k length
Same goes for KM::time(k) and GSM::time(k)

DAC::multiply(num1, num2) - takes 2 parameters - numbers, represented by LargeInteger and return product of them also as LargeInteger using Divide and Conquer algoithm.
Same goes for KM::multiply(num1, num2) and GSM::multiply(num1, num2)


store(vector<vector<double> >) - takes vector of vectors, which contain time results of 3 algorithms and writes them in output.csv

get_results(k, step=1, attemps=3) - function to get time results of 3 algorithm as vector<vector<double> > using average mean of attemps on range [0; k]
