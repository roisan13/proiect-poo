//
// Created by Radu on 6/14/2024.
//

#ifndef OOP_SINGLETONGAME_H
#define OOP_SINGLETONGAME_H

#include "pveGame.h"
#include "Game.h"

template<typename T>
class SingletonGame {
    SingletonGame() {}

    ~SingletonGame() {}

public:

    SingletonGame(const SingletonGame &) = delete;

    SingletonGame &operator=(const SingletonGame &) = delete;

    static T &getGameInstance() {
        static T gameInstance;
        return gameInstance;
    }

};

template
class SingletonGame<Game>;

template
class SingletonGame<pveGame>;


#endif //OOP_SINGLETONGAME_H
