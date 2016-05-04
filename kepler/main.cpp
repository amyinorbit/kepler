//
//  main.cpp
//  kepler
//
//  Created by Cesar Parent on 04/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#include <iostream>
#include "vec.hpp"
#include "matrix.hpp"

int main(int argc, const char * argv[]) {
    
    matrix<3, 3> a = matrix<3, 3>::identity();
    vec<double, 3> b = {1, 2, 3};
    
    
    std::cout << "Result: " << a * b << std::endl;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
