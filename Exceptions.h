//
// Created by Radu on 5/26/2024.
//

#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <stdexcept>

class gameError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class attributeError : public gameError {
public:
    explicit attributeError() :
            gameError("Incorrect/invalid attribute given as parameter in constructor") {}
};

class gameLogicError : public gameError {
public:
    explicit gameLogicError() :
            gameError("Invalid game logic regarding player/computer turns or selecting target/attacker.") {}
};

class grahicsError : public gameError {
public:
    explicit grahicsError() :
            gameError("Error regarding SFML.") {}
};


#endif //OOP_EXCEPTIONS_H
