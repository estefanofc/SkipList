//
// Test Class
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int TotalPassed = 0;
int TotalTests = 0;

template<typename T>
string isOK(const T &got, const T &expected) {
    ++TotalTests;
    if (got == expected) {
        ++TotalPassed;
        return "OK: ";
    }
    cout << "Got\n" << got << "\nexpected\n" << expected << endl;
    return "ERR: ";
}

void test2() {
    srand(100);
    cout << "TEST 2" << endl;
    SkipList Skip(3);
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 2 -- -2147483648, 2147483647, \n"s +
                           "Level: 1 -- -2147483648, 2147483647, \n"s +
                           "Level: 0 -- -2147483648, 2147483647, \n"s)
         << "Empty SkipList of Depth=3" << endl;
    Skip.add(10);
    Skip.add(30);
    Skip.add(5);
    Skip.add(25);
    Ss.str("");
    Ss << Skip;
    cout << isOK(Ss.str(),
                 "Level: 2 -- -2147483648, 30, 2147483647, \n"s +
                 "Level: 1 -- -2147483648, 5, 10, 30, 2147483647, \n"s +
                 "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
    cout << isOK(Skip.contains(10), true) << "Contains 10" << endl;
    cout << isOK(Skip.contains(30), true) << "Contains 30" << endl;
    cout << isOK(Skip.contains(71), false) << "Does not contain 71" << endl;
}

void test1() {
    srand(100);
    cout << "TEST 1" << endl;
    SkipList Skip;
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 0 -- -2147483648, 2147483647, \n"s)
         << "Empty SkipList" << endl;
    Skip.add(10);
    Skip.add(30);
    Skip.add(5);
    Skip.add(25);
    Ss.str("");
    Ss << Skip;
    cout << isOK(Ss.str(),
                 "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
         << "Added 10, 30, 5, 25," << endl;
}

void test3() {
    srand(100);
    cout << "TEST 3" << endl;
    SkipList Skip(5);
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 4 -- -2147483648, 2147483647, \n"s +
                           "Level: 3 -- -2147483648, 2147483647, \n"s +
                           "Level: 2 -- -2147483648, 2147483647, \n"s +
                           "Level: 1 -- -2147483648, 2147483647, \n"s +
                           "Level: 0 -- -2147483648, 2147483647, \n"s)
         << "Empty SkipList of Depth=5" << endl;
    for (int I = 0; I < 10; I++) {
        Skip.add(rand() % 100);
    }
    Ss.str("");
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 4 -- -2147483648, 2147483647, \n"s +
                           "Level: 3 -- -2147483648, 2147483647, \n"s +
                           "Level: 2 -- -2147483648, 75, 91, 2147483647, \n"s +
                           "Level: 1 -- -2147483648, 39, 75, 77, 91, 2147483647, \n"s +
                           "Level: 0 -- -2147483648, 12, 23, 29, 31, 39, 72, 73, 75, 77, 91, 2147483647, \n"s)
         << "SkipList of Depth=5 with 12, 23, 29, 31, 39, 72, 73, 75, 77, 91" << endl;
    cout << isOK(Skip.remove(73), true)
         << "Removed 73 from SkipList" << endl;

}

void test4() {
    srand(100);
    cout << "TEST 4" << endl;
    //empty list
    SkipList Skip(3);
    cout << isOK(Skip.remove(100), false)
         << "Removing non existing element from empty list" << endl;
    cout << isOK(Skip.contains(100), false)
         << "Searching for non existing element in empty list" << endl;

}

void test5() {
    srand(100);
    cout << "TEST 2" << endl;
    SkipList Skip(5);
    stringstream Ss;
    Ss << Skip;
    cout << isOK(Ss.str(), "Level: 2 -- -2147483648, 2147483647, \n"s +
                           "Level: 1 -- -2147483648, 2147483647, \n"s +
                           "Level: 0 -- -2147483648, 2147483647, \n"s)
         << "Empty SkipList of Depth=3" << endl;
    Skip.add(10);
    Skip.add(30);
    Skip.add(5);
    Skip.add(25);
    cout << isOK(Skip.add(10), false) << "Can't add duplicate elements" << endl;
}

int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    // NOLINTNEXTLINE

    test1();
    test2();
    test3();
    test4();
    test5();
    cout << "Passed: " << TotalPassed << "/" << TotalTests << endl;
    return 0;
}