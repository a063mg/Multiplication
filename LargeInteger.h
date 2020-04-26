#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class LargeInteger {
private:
    string num;
public:
    LargeInteger();
    LargeInteger(const int& i);
    LargeInteger(const string& s);

    static vector<vector<LargeInteger> > table; // Multiplication table

    friend ostream& operator<<(ostream& os, const LargeInteger& output);

    LargeInteger& operator+=(const LargeInteger& other);
    LargeInteger& operator-=(const LargeInteger& other);
    LargeInteger operator+(const LargeInteger& other) const;
    LargeInteger operator-(const LargeInteger& other) const;

    bool operator==(const LargeInteger& other) const;
    bool operator!=(const LargeInteger& other) const;

    int index(const int& i) const;
    char element(const int& i) const;
    size_t size() const;
    bool isZero() const;
    void removeLeftZeros();
    void make_equal(LargeInteger& num1, LargeInteger& num2);

    static LargeInteger randint(size_t numberOfDigits);
    static void split(const LargeInteger& num1, const LargeInteger& num2, LargeInteger& a, LargeInteger& b, LargeInteger& c, LargeInteger& d);
    void r_shift(size_t t);
    void l_shift(size_t t);
};


LargeInteger::LargeInteger(){ }

LargeInteger::LargeInteger(const int& i): num(to_string(i)) { }

LargeInteger::LargeInteger(const string& s): num(s) { }


ostream& operator<<(ostream& os, const LargeInteger& output){
    os<<output.num;
    return os;
}

LargeInteger& LargeInteger::operator+=(const LargeInteger& other){
    if (size() == 0 || other.size() == 0)
        return *this;

    LargeInteger nc_other = other; // non-const "other" variablie, which can be changed,

    // *this should have bigger size for this algorithm
    if (nc_other.size() > size()){
        nc_other.num = num;
        num = other.num;
    }

  

    size_t n1 = nc_other.size();
    size_t n2 = size(); 
    size_t diff = n2 - n1; 

    int sum, carry = 0; 

    for (int i = n1-1; i >= 0; i--) 
    { 
        sum = (index(i+diff) + nc_other.index(i) + carry); 
        num[i+diff] = (sum%10 + '0'); 
        carry = sum/10; 
    } 
      
    // Add remaining digits of num
    for (int i=n2-n1-1; i >= 0; i--) 
    { 
        sum = index(i) + carry; 
        num[i] = (sum%10 + '0'); 
        carry = sum/10; 
    } 
      
    // Add remaining carry 
    if (carry) 
        num = to_string(carry) + num;
        
    return *this;
}

LargeInteger& LargeInteger::operator-=(const LargeInteger& other) {
    if (other.isZero())
        return *this;

    LargeInteger nc_other = other; //non-const "other" variablie which can be resized 

    make_equal(nc_other, *this);
    size_t n = size();

    int sum, carry;
    carry = 0;
    for (int i = n-1; i >= 0; i--) {
        sum = index(i) - nc_other.index(i) - carry;
        if (sum >= 0){
            num[i] = (sum+'0');
            carry = 0;
        }
        else{
            num[i] = ((sum+10)+'0');
            carry = 1;
        }
    }

    removeLeftZeros();

    return *this;
}

LargeInteger LargeInteger::operator+(const LargeInteger& other) const
{
    LargeInteger sum = *this;
    sum += other;
    return sum;
}

LargeInteger LargeInteger::operator-(const LargeInteger& other) const
{
    LargeInteger sum = *this;
    sum -= other;
    return sum;
}

bool LargeInteger::operator==(const LargeInteger& other) const {
    return num == other.num;
}

bool LargeInteger::operator!=(const LargeInteger& other) const {
    return num != other.num;
}

bool LargeInteger::isZero() const {
    for (size_t i = 0; i < size(); i++) 
        if (index(i) != 0) return false;
    return true;
}

size_t LargeInteger::size() const {
    return num.length();
}

int LargeInteger::index(const int& i) const { // return int at some position of a string
    return num[i]-'0'; // same as int(num[i])
}

char LargeInteger::element(const int& i) const { // return char at some position of a string
    return num[i];
}

// Removing all unnecessary zeros from the left
void LargeInteger::removeLeftZeros() {
    while (index(0) == 0 and size() > 1){
        num.erase(num.begin());
    }
}

// Resize num1 and num2, so they have same length
void LargeInteger::make_equal(LargeInteger& num1, LargeInteger& num2) {
    size_t n1 = num1.size();
    size_t n2 = num2.size();
    if (n2 > n1){
        num1.l_shift(n2-n1);
    }
    else{
        num2.l_shift(n1-n2);
    }
}

// Method which splits *this and num1 LargeIntegers in 4 variables: a,b,c,d using only 1 cycle
void LargeInteger::split(const LargeInteger& num1, const LargeInteger& num2, LargeInteger& a, LargeInteger& b, LargeInteger& c, LargeInteger& d){
    size_t m1 = num1.size();
    size_t m2 = num2.size(); 
    size_t m = max(m1, m2);
    for (size_t i = 0; i < m; i++){
        if (i < m/2){
            if (i>=m-m1){
                a.num += num1.element(i-m+m1);
            }
            else{
                a.num += '0';
            }
            if (i>=m-m2){
                c.num += num2.element(i-m+m2);
            }
            else{
                c.num += '0';
            }
        }
        else{
            if (i>=m-m1){
                b.num += num1.element(i-m+m1);;
            }
            else{
                b.num += '0';
            }
            if (i>=m-m2){
                d.num += num2.element(i-m+m2);
            }
            else{
                d.num += '0';
            }
        }
    }
}

// Right shif
void LargeInteger::r_shift(size_t t) {
    string s(t, '0');
    num += s;
}

// Left shift
void LargeInteger::l_shift(size_t t) {
    string s(t, '0');
    num = s + num;
}

//Random function
LargeInteger LargeInteger::randint(size_t numberOfDigits) {
    string fst = "123456789";
    string digits = "0123456789";
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<size_t> frst(0, fst.size() - 1);
    uniform_int_distribution<size_t> dist(0, digits.size() - 1);

    string s;

    if (numberOfDigits != 0) { // In case to avoid infinite loop
        s.push_back(fst.at(frst(mt))); // First digit can't be equal to 0

        for (size_t i = 0; i < numberOfDigits-1; i++) {
            s.push_back(digits.at(dist(mt)));
        }
    }

    return LargeInteger(s);
}

// Function to initialize multiplication table, for quick multiplication of 1 digit numbers.
vector<vector<LargeInteger> > init_table(){
    vector<vector<LargeInteger> > t;
    vector<LargeInteger> row;
    for (int i = 0; i < 10; i++){
        row.clear();
        for (int j = 0; j < 10; j++){
            row.push_back(LargeInteger(i*j));
        }
        t.push_back(row);
    }
    return t;
}
