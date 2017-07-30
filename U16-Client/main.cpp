#include "./client/Client.h"
#include <thread>
#include <exception>
#include <cstdlib>

#define WALK    1   //0000 0001
#define PUT     2   //0000 0010
#define LOOK    4   //0000 0100
#define SEARCH  8   //0000 1000
#define UP      16  //0001 0000
#define LEFT    32  //0010 0000
#define RIGHT   64  //0100 0000
#define DOWN    128 //1000 0000

void delayPrint(std::string str) {
    for (auto i = str.begin(); i != str.end(); i++) {
        std::cout << *i;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

int main(int argc, char* argv[]) {
    std::cout << "\n*****                                 *****";
    for (int i = 0; i < 33; i++) { std::cout << "\b"; }
    delayPrint("This program is sample.");
    std::cout << std::endl << std::endl;

    connectToServer();

    enum Dir { up = 2, left = 4, right = 6, down = 8, off = -1 };

    int value_ready[10];
    int value_method[10];
    unsigned int mode = WALK | UP;
    Dir item_dir = off;

    try {
    //以下、ゲームのループ
        while (getReady(value_ready)) {

            //敵をつぶすところ
            if (value_ready[up] == 1) {
                mode = PUT | UP;
            }
            else if (value_ready[left] == 1) {
                mode = PUT | LEFT;
            }
            else if (value_ready[right] == 1) {
                mode = PUT | RIGHT;
            }
            else if (value_ready[down] == 1) {
                mode = PUT | DOWN;
            }
            else {

                //アイテムを取るところ
                
                

                //動くところ
                   
                

            }

            //メソッド実行部分
            if (mode & WALK) {          //Walk
                if (mode & UP) { walkUp(value_method); }
                else if (mode & LEFT) { walkLeft(value_method); }
                else if (mode & RIGHT) { walkRight(value_method); }
                else if (mode & DOWN) { walkDown(value_method); }
                else { throw "Walk: The Direction is unknown"; }
            }
            else if (mode & PUT) {      //Put
                if (mode & UP) { putUp(value_method); }
                else if (mode & LEFT) { putLeft(value_method); }
                else if (mode & RIGHT) { putRight(value_method); }
                else if (mode & DOWN) { putDown(value_method); }
                else { throw "Put: The Direction is unknown"; }
            }
            else if (mode & LOOK) {     //Look
                if (mode & UP) { lookUp(value_method); }
                else if (mode & LEFT) { lookLeft(value_method); }
                else if (mode & RIGHT) { lookRight(value_method); }
                else if (mode & DOWN) { lookDown(value_method); }
                else { throw "Look: The Direction is unknown"; }
            }
            else if (mode & SEARCH) {   //Search
                if (mode & UP) { searchUp(value_method); }
                else if (mode & LEFT) { searchLeft(value_method); }
                else if (mode & RIGHT) { searchRight(value_method); }
                else if (mode & DOWN) { searchDown(value_method); }
                else { throw "Search: The Direction is unknown"; }
            }


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

    return 0;
}
