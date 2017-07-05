#include "Client.h"


int main(int argc, char* argv[]) {
    //Client client;
    //client.connectToServer();
    connectToServer();

    enum Dir { up, down, left, right };

    int value_ready[10];
    int value_method[10];
    Dir walk_dir = up;

    while (client.getReady(value_ready)) {

        if (value_ready[2] == 1) {
            client.putUp(value_method);
        }
        else if (value_ready[4] == 1) {
            client.putLeft(value_method);
        }
        else if (value_ready[6] == 1) {
            client.putRight(value_method);
        }
        else if (value_ready[8] == 1) {
            client.putDown(value_method);
        }
        else {
            while (true) {
                if (walk_dir == up) {
                    if (value_ready[2] != 2) {
                        client.walkUp(value_method);
                        break;
                    }
                    else {
                        walk_dir = left;
                    }
                }
                if (walk_dir == left) {
                    if (value_ready[4] != 2) {
                        client.walkLeft(value_method);
                        break;
                    }
                    else {
                        walk_dir = down;
                    }
                }
                if (walk_dir == down) {
                    if (value_ready[8] != 2) {
                        client.walkDown(value_method);
                        break;
                    }
                    else {
                        walk_dir = right;
                    }
                }
                if (walk_dir == right) {
                    if (value_ready[6] != 2) {
                        client.walkRight(value_method);
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
