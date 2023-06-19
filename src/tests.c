#include "tests.h"

#define maxTests 1000
bool testResults[maxTests];
int currInd = 0;

void printResults();
void test(bool res);

bool floatsEqual(float a, float b) {
    float diff = a-b;
    if (diff < 0) diff *= -1;
    return diff < 0.05;
}
bool vec2Equal(vec2 a, vec2 b) {
    return (floatsEqual(a.x,b.x) && floatsEqual(a.y,b.y));
}
bool vec3Equal(vec3 a, vec3 b) {
    return (floatsEqual(a.x,b.x) && floatsEqual(a.y,b.y) && floatsEqual(a.z,b.z));
}
void runTests() {
    test(floatsEqual(-5,-5.001));
    test(floatsEqual(-5.001,-5));

    test(vec2Equal(
        (vec2){3,4},
        (vec2){3.001,3.999}
    ));
    test(vec2Equal(
        (vec2){3.001,3.999},
        (vec2){3,4}
    ));

    test(vec3Equal(
        (vec3){3,-4,10},
        (vec3){3.001,-4.001,9.999}
    ));
    test(vec3Equal(
        (vec3){3.001,-4.001,9.999},
        (vec3){3,-4,10}
    ));

    //vector operations
    vec2 magnitudeTestVec2 = {3,4};
    vec2 arbitraryVec2 = {102.3, 200.6};
    test(vec2Magnitude(magnitudeTestVec2) == 5);
    test(floatsEqual(vec2Magnitude(arbitraryVec2), 225.1791509));

    vec2 one = {101.1,203.24};
    vec2 two = {193.45,293.9};
    test(vec2Equal(vec2Add(one,two), (vec2){294.55,497.14}));
    test(vec2Equal(vec2Subtract(one,two), (vec2){-92.35,-90.66}));
    one = (vec2){-5,-6};
    two = (vec2){1,-3};
    test(vec2Equal(vec2Add(one,two), (vec2){-4,-9}));
    test(vec2Equal(vec2Subtract(one,two), (vec2){-6,-3}));

    one = (vec2){-5,3};
    vec2Scale(&one, 3);
    test(vec2Equal((vec2){-15,9},one));
    vec2Divide(&one,3);
    test(vec2Equal((vec2){-5,3},one));

    one = (vec2) {293.24, 182.3};
    vec2Normalize(&one);
    test(floatsEqual(vec2Magnitude(one),1));
    one = (vec2) {-324, 19};
    vec2Normalize(&one);
    test(floatsEqual(vec2Magnitude(one),1));

    vec3 a = {192.3,4,-293.3};
    vec3 b = {3,4,5};
    test(floatsEqual(vec3Magnitude(a), 350.742327));
    test(floatsEqual(vec3Magnitude(b), 7.07106));

    a = (vec3){-3, 5, 10};
    b = (vec3){2, 5, -5};
    test(vec3Equal(vec3Add(a,b), (vec3){-1,10,5}));
    test(vec3Equal(vec3Subtract(a,b), (vec3){-5,0,15}));

    a = (vec3){10,15,20};
    vec3Divide(&a, 5);
    test(vec3Equal(a, (vec3){2,3,4}));
    vec3Scale(&a, 5);
    test(vec3Equal(a, (vec3){10,15,20}));

    a = (vec3){102.25,342.2,123.523};
    vec3Normalize(&a);
    test(floatsEqual(vec3Magnitude(a),1));
    a = (vec3){31,3,2};
    vec3Normalize(&a);
    test(floatsEqual(vec3Magnitude(a),1));

    a = (vec3){12.532,5.23,9.39};
    b = (vec3){31.2,3,6.32};
    test(floatsEqual(dot(a,b),466.033));
    test(vec3Equal(
        cross(a,b),
        (vec3){
            4.8836,
            213.76576,
            -125.58
        }
    ));

    a = (vec3){-2,3,12};
    b = (vec3){-5,-3,13};
    test(floatsEqual(dot(a,b),157));
    test(vec3Equal(
        cross(a,b),
        (vec3){75,-34,21}
    ));

    printResults();
}
void printResults() {
    int passed = 0;
    int failed = 0;
    for (int i = 0; i < currInd; i++) {
        if (testResults[i]) {
            passed++;
        } else {
            failed++;
        }
    }
    printf("Passed %d out of %d tests\n", passed, currInd);
    if (passed < currInd) {
        printf("Failed tests are indices");
        for (int i = 0; i < currInd; i++) {
            if (!testResults[i]) {
                printf(" %d", i);
            }
        }
        printf("\n");
    }
}
void test(bool res) {
    testResults[currInd] = res;
    currInd++;
}
