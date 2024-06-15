//
// Created by Radu on 6/14/2024.
//

#ifndef OOP_SINGLETONGAME_H
#define OOP_SINGLETONGAME_H

template<typename Derived>
class SingletonGame {
protected:
    SingletonGame() = default;
public:
    static Derived &getGameInstance() {
        static DerivedGameInstance instance;
        return instance;
    }


    SingletonGame(const SingletonGame &) = delete;

    SingletonGame &operator=(const SingletonGame &) = delete;


private:

    class DerivedGameInstance : public Derived {
    public:
        DerivedGameInstance() : Derived() {}
    };
};


#endif //OOP_SINGLETONGAME_H
