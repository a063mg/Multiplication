#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
// #include "LargeInteger.h"

using namespace std;

// Grade School Multiplication algorithm
class GSM {
public:
    static LargeInteger multiply(const LargeInteger& num1, const LargeInteger& num2);
    static double time(const size_t& k);
    static bool test();
};


// Karatsuba Multiplication algorithm
class KM {
public:
    static LargeInteger multiply(const LargeInteger &num1, const LargeInteger &num2);
    static double time(const size_t& k);
    static bool test();
};

// Grade School Multiplication algorithm
class DAC {
public:
    static LargeInteger multiply(const LargeInteger& num1, const LargeInteger& num2);
    static double time(const size_t& k);
    static bool test();
};

// Grade School Multiplication algorithm
LargeInteger GSM::multiply(const LargeInteger& num1, const LargeInteger& num2) {
    if (num1.size() < 1 || num2.size() < 1) return LargeInteger(0);

    size_t m1 = num1.size();
    size_t m2 = num2.size();

    size_t sz = m1+m2;            //size of the answer
    string result(sz, '0');       //init of answer

    int sum, carry, n, k;
    k = 0;
    for (int i = m1-1; i >= 0; i--){ 
        carry = 0;
        n = sz-1-k; //current margin
        for (int j = m2-1; j >= 0; j--){ 
            sum = num1.index(i)*num2.index(j) + (result[n]-'0') + carry;
            result[n] = (sum%10) + '0';
            carry = sum/10;
            n--;
        }
        result[n] = (carry + (result[n]-'0') + '0');
        k++;
    }

    LargeInteger prod = LargeInteger(result);  // init of the return value

    prod.removeLeftZeros();       

    return prod;
}

// Karatsuba Multiplication algorithm
LargeInteger KM::multiply(const LargeInteger &num1, const LargeInteger &num2) {
    if (num1.size() < 1 || num2.size() < 1) return LargeInteger(0);

    if (num1.size() == 1 && num2.size() == 1)
        return LargeInteger::table[num1.index(0)][num2.index(0)];

    size_t m = max(num1.size(), num2.size());

    LargeInteger a;
    LargeInteger b;
    LargeInteger c;
    LargeInteger d;

    LargeInteger::split(num1, num2, a, b, c, d);

    LargeInteger a_b = a;
    a_b += b; // = a+b
    LargeInteger c_d = c;
    c_d += d; // = c+d
    
    LargeInteger ac = multiply(a, c); // = ac
    LargeInteger bd = multiply(b, d); // = bd
    LargeInteger a_bc_d = multiply(a_b, c_d); // = (a+b)*(c+d)

    a_bc_d -= ac; // = (a+b)*(c+d) - ac
    a_bc_d -= bd; // = (a+b)*(c+d) - ac - bd
    
    ac.r_shift(2*(m-m/2));
    a_bc_d.r_shift(m-m/2);

    bd += ac;
    bd += a_bc_d;

    bd.removeLeftZeros();

    return bd;
}

// Divide and Conquer Multiplication algorithm
LargeInteger DAC::multiply(const LargeInteger &num1, const LargeInteger &num2) {
    if (num1.size() < 1 || num2.size() < 1) return LargeInteger(0);

    if (num1.size() == 1 && num2.size() == 1)
        return LargeInteger::table[num1.index(0)][num2.index(0)];

    size_t m = max(num1.size(), num2.size());

    LargeInteger a;
    LargeInteger b;
    LargeInteger c;
    LargeInteger d;

    LargeInteger::split(num1, num2, a, b, c, d);

    LargeInteger ac = multiply(a, c); // = a*c
    LargeInteger ad_bc = multiply(a, d); // = a*d
    ad_bc += multiply(b, c); // = (a*d + b*c)
    LargeInteger bd = multiply(b, d); // = b*d

    ac.r_shift(2*(m-m/2));
    ad_bc.r_shift(m-m/2);

    bd += ac;
    bd += ad_bc;

    bd.removeLeftZeros();

    return bd;
}

// Functions to measure time of exact algorithm on k length numbers.
double GSM::time(const size_t& k){
    LargeInteger num1, num2, ans;
    double elapsed;
    num1 = LargeInteger::randint(k);
    num2 = LargeInteger::randint(k);
    clock_t start = clock();
    ans = GSM::multiply(num1, num2);
    return round((clock() - start)/100)/10;
}

double KM::time(const size_t& k){
    LargeInteger num1, num2, ans;
    double elapsed;
    num1 = LargeInteger::randint(k);
    num2 = LargeInteger::randint(k);
    clock_t start = clock();
    ans = KM::multiply(num1, num2);
    return round((clock() - start)/100)/10;
}

double DAC::time(const size_t& k){
    LargeInteger num1, num2, ans;
    double elapsed;
    num1 = LargeInteger::randint(k);
    num2 = LargeInteger::randint(k);
    clock_t start = clock();
    ans = DAC::multiply(num1, num2);
    return round((clock() - start)/100)/10;
}

// Functions to test exact algorithm for correctness.
bool GSM::test(){
    bool ok = true;
    string correct;
    LargeInteger num1, num2, ans;

    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            num1 = LargeInteger(i);
            num2 = LargeInteger(j);
            ans = DAC::multiply(num1, num2);
            correct = to_string(i*j);
            if (ans != correct){
                cout<<"Error "<<num1<<" * "<<num2<<" = "<<correct<<" instead of "<<ans<<endl;
                ok = false;
            }
        }   
    }

    return ok;
}

bool KM::test(){
    bool ok = true;
    string correct;
    LargeInteger num1, num2, ans;

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            num1 = LargeInteger(i);
            num2 = LargeInteger(j);
            ans = KM::multiply(num1, num2);
            correct = to_string(i*j);
            if (ans != correct){
                cout<<"Error "<<num1<<" * "<<num2<<" = "<<correct<<" instead of "<<ans<<endl;
                ok = false;
            }
        }   
    }

    return ok;
}

bool DAC::test(){
    bool ok = true;
    string correct;
    LargeInteger num1, num2, ans;

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            num1 = LargeInteger(i);
            num2 = LargeInteger(j);
            ans = DAC::multiply(num1, num2);
            correct = to_string(i*j);
            if (ans != correct){
                cout<<"Error "<<num1<<" * "<<num2<<" = "<<correct<<" instead of "<<ans<<endl;
                ok = false;
            }
        }   
    }

    return ok;
}


// Function to test algorithms and write results in vector
vector<vector<double> > get_results(const int& k, const int& step=1, const int& attempts=3) {

    vector<vector<double> > results;
    vector<double> row;

    row.clear();
    results.clear();

    for (int i = 1; i <= k; i += step){

        double sum1 = 0, sum2 = 0, sum3 = 0;

        for (int j = 0; j < attempts; j++){ 
            sum1 += DAC::time(i);
            sum2 += KM::time(i);
            sum3 += GSM::time(i);
        }
        row.push_back(sum1/attempts);
        row.push_back(sum2/attempts);
        row.push_back(sum3/attempts);

        results.push_back(row);
        row.clear();

        //cout<<"Ok: "<<i<<endl;
    }

    return results;
}

// Function to write results in output csv file
void store(const vector<vector<double> >& results){
    std::ofstream output;
    output.open("output.csv");
    //output<<"Length"<<" "<<"DAC"<<" "<<"KM"<<" "<<"GSM"<<endl;
    for (int i = 0; i < results.size(); i++){
        output<<i+1<<","<<results[i][0]<<","<<results[i][1]<<","<<results[i][2]<<endl;
    }
    output.close();
}

// Writes results immediatelyafter testing (In case of termination of this function, all calculated results will be saved) Also, it writes length of number.
void quick_test(const int& k, const int& step=1, const int& attempts=3) {
    std::ofstream output;
    output.open("output.csv");

    //output<<"Length"<<" "<<"DAC"<<" "<<"KM"<<" "<<"GSM"<<endl;

    for (int i = 0; i <= k; i += step){

        double sum1 = 0, sum2 = 0, sum3 = 0;

        for (int j = 0; j < attempts; j++){ 
            sum1 += DAC::time(i);
            sum2 += KM::time(i);
            sum3 += GSM::time(i);
        }

        output<<i<<","<<sum1/attempts<<","<<sum2/attempts<<","<<sum3/attempts<<endl;

        //cout<<"Ok: "<<i<<endl;
    }

    output.close();
}

