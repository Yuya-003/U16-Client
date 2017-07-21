#include "./client/Client.h"


int main(int argc, char* argv[]) {
    connectToServer();

    enum Dir { up = 2, down = 8, left = 4, right = 6 };

    int value_ready[10];
    int value_method[10];
    Dir walk_dir = up;

    while (getReady(value_ready)) {

        if (value_ready[up] == 1) {
            putUp(value_method);
        }
        else if (value_ready[left] == 1) {
            putLeft(value_method);
        }
        else if (value_ready[right] == 1) {
            putRight(value_method);
        }
        else if (value_ready[down] == 1) {
            putDown(value_method);
        }
        else {
            while (true) {
                if (walk_dir == up) {
                    if (value_ready[up] != 2) {
                        walkUp(value_method);
                        break;
                    }
                    else {
                        walk_dir = left;
                    }
                }
                if (walk_dir == left) {
                    if (value_ready[left] != 2) {
                        walkLeft(value_method);
                        break;
                    }
                    else {
                        walk_dir = down;
                    }
                }
                if (walk_dir == down) {
                    if (value_ready[down] != 2) {
                        walkDown(value_method);
                        break;
                    }
                    else {
                        walk_dir = right;
                    }
                }
                if (walk_dir == right) {
                    if (value_ready[right] != 2) {
                        walkRight(value_method);
                        break;
                    }
                    else {
                        walk_dir = up;
                    }
                }
            }
        }




    }
    std::cout << "<<----ゲーム終了---->>" << std::endl;

    return 0;
}
