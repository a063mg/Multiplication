#include <iostream>
#include <string>
#include <vector>
#include "LargeInteger.h"
#include "Multiplicator.h"

using namespace std;

vector<vector<LargeInteger> > LargeInteger::table = init_table(); // Fillinig multiplication table.

int main(){
    store(get_results(1000,10,5));
}

