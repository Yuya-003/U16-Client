#include "./client/Client.h"
#include <thread>
#include <exception>
#include <cstdlib>

void delayPrint(std::string str);
void searchGame();

int main(int argc, char* argv[]) {
    std::cout << "\n*****                                 *****";
    for (int i = 0; i < 33; i++) { std::cout << "\b"; }
    delayPrint("This program is sample.");
    std::cout << std::endl << std::endl;

    connectToServer();

    searchGame();

    return 0;
}


void delayPrint(std::string str) {
    for (auto i = str.begin(); i != str.end(); i++) {
        std::cout << *i;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void searchGame() {

    static const unsigned int OFF    = 0;   //0000 0000
    static const unsigned int WALK   = 1;   //0000 0001
    static const unsigned int PUT    = 2;   //0000 0010
    static const unsigned int LOOK   = 4;   //0000 0100
    static const unsigned int SEARCH = 8;   //0000 1000
    static const unsigned int UP     = 16;  //0001 0000
    static const unsigned int LEFT   = 32;  //0010 0000
    static const unsigned int RIGHT  = 64;  //0100 0000
    static const unsigned int DOWN   = 128; //1000 0000

    enum Mode { up = 2, left = 4, right = 6, down = 8, off = 0, skip = -1 };

    int value_ready[10];
    int value_method[10];

    unsigned int behavior = WALK | UP;
    unsigned int prev_behavior = WALK | UP;
    Mode item_mode = off;

    try {
        //以下、ゲームのループ
        while (getReady(value_ready)) {

            //敵をつぶすところ
            if (value_ready[up] == 1) {
                behavior = PUT | UP;
            }
            else if (value_ready[left] == 1) {
                behavior = PUT | LEFT;
            }
            else if (value_ready[right] == 1) {
                behavior = PUT | RIGHT;
            }
            else if (value_ready[down] == 1) {
                behavior = PUT | DOWN;
            }
            else {

                //アイテムを取るところ
                if (item_mode != skip) {
                    if (item_mode != off) {
                        if (item_mode == up) { behavior = WALK | UP; }
                        else if (item_mode == left) { behavior = WALK | LEFT; }
                        else if (item_mode == right) { behavior = WALK | RIGHT; }
                        else if (item_mode == down) { behavior = WALK | DOWN; }
                    }
                    else if (value_ready[up] == 3) {
                        if (value_ready[up - 1] != 2 || value_ready[up + 1] != 2) {
                            behavior = WALK | UP;
                        }
                        else {
                            behavior = LOOK | UP;
                            item_mode = up;
                        }
                    }
                    else if (value_ready[left] == 3) {
                        if (value_ready[up - 1] != 2 || value_ready[down - 1] != 2) {
                            behavior = WALK | LEFT;
                        }
                        else {
                            behavior = LOOK | LEFT;
                            item_mode = left;
                        }
                    }
                    else if (value_ready[down] == 3) {
                        if (value_ready[down - 1] != 2 || value_ready[down + 1] != 2) {
                            behavior = WALK | DOWN;
                        }
                        else {
                            behavior = LOOK | DOWN;
                            item_mode = down;
                        }
                    }
                    else if (value_ready[right] == 3) {
                        if (value_ready[up + 1] != 2 || value_ready[down + 1] != 2) {
                            behavior = WALK | RIGHT;
                        }
                        else {
                            behavior = LOOK | RIGHT;
                            item_mode = right;
                        }
                    }

                    else {

                        //動くところ
                        if (prev_behavior & UP) {
                            if (value_ready[up] != 2) { behavior = WALK | UP; }
                            else if (value_ready[left] != 2) { behavior = WALK | LEFT; }
                            else if (value_ready[down] != 2) { behavior = WALK | DOWN; }
                            else { behavior = WALK | RIGHT; }
                        }
                        else if (prev_behavior & LEFT) {
                            if (value_ready[left] != 2) { behavior = WALK | LEFT; }
                            else if (value_ready[down] != 2) { behavior = WALK | DOWN; }
                            else if (value_ready[right] != 2) { behavior = WALK | RIGHT; }
                            else { behavior = WALK | UP; }
                        }
                        else if (prev_behavior & DOWN) {
                            if (value_ready[down] != 2) { behavior = WALK | DOWN; }
                            else if (value_ready[right] != 2) { behavior = WALK | RIGHT; }
                            else if (value_ready[up] != 2) { behavior = WALK | UP; }
                            else { behavior = WALK | LEFT; }
                        }
                        else if (prev_behavior & RIGHT) {
                            if (value_ready[right] != 2) { behavior = WALK | RIGHT; }
                            else if (value_ready[up] != 2) { behavior = WALK | UP; }
                            else if (value_ready[left] != 2) { behavior = WALK | LEFT; }
                            else { behavior = WALK | DOWN; }
                        }

                    }

                }
            }

            //メソッド実行部分
            if (behavior & WALK) {          //Walk
                if (behavior & UP) { walkUp(value_method); }
                else if (behavior & LEFT) { walkLeft(value_method); }
                else if (behavior & RIGHT) { walkRight(value_method); }
                else if (behavior & DOWN) { walkDown(value_method); }
                else { throw "Walk: The Direction is unknown"; }
            }
            else if (behavior & PUT) {      //Put
                if (behavior & UP) { putUp(value_method); }
                else if (behavior & LEFT) { putLeft(value_method); }
                else if (behavior & RIGHT) { putRight(value_method); }
                else if (behavior & DOWN) { putDown(value_method); }
                else { throw "Put: The Direction is unknown"; }
            }
            else if (behavior & LOOK) {     //Look
                if (behavior & UP) { lookUp(value_method); }
                else if (behavior & LEFT) { lookLeft(value_method); }
                else if (behavior & RIGHT) { lookRight(value_method); }
                else if (behavior & DOWN) { lookDown(value_method); }
                else { throw "Look: The Direction is unknown"; }
            }
            else if (behavior & SEARCH) {   //Search
                if (behavior & UP) { searchUp(value_method); }
                else if (behavior & LEFT) { searchLeft(value_method); }
                else if (behavior & RIGHT) { searchRight(value_method); }
                else if (behavior & DOWN) { searchDown(value_method); }
                else { throw "Search: The Direction is unknown"; }
            }

            //メソッド後の探索
            if (item_mode == skip) {
                item_mode = off;
            }
            else if (item_mode != off) {
                if (item_mode == up) {
                    if (value_method[left + 1] == 2) { item_mode = skip; }
                }
                else if (item_mode == left) {
                    if (value_method[left + 1] == 2) { item_mode = skip; }
                }
                else if (item_mode == down) {
                    if (value_method[left + 1] == 2) { item_mode = skip; }
                }
                else if (item_mode == right) {
                    if (value_method[left + 1] == 2) { item_mode = skip; }
                }
            }

            prev_behavior = behavior;

        }
        //ここまでゲームのループ

        std::cout << "<<---- Game over ---->>" << std::endl;

    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::string &e) {
        std::cout << e << std::endl;
    }

}
