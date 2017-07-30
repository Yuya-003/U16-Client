#include "./client/Client.h"

//nothing:0, other player:1, block:2, item:3

int main(int argc, char* argv[]) {
    std::cout   << " **************************************\n"
                << " *                                    *\n"
                << " *       This program is sample.      *\n"
                << " *                                    *\n"
                << " **************************************" << std::endl;
    connectToServer();

    enum Dir { up = 2, down = 8, left = 4, right = 6, off = -1 };

    int value_ready[10];
    int value_method[10];
    Dir walk_dir = up;
    Dir item_dir = off;

    //以下、ゲームのループ
    while (getReady(value_ready)) {
        
        //敵をつぶすところ
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

            //アイテムを取るところ
            if (item_dir != off) {
                walk_dir = item_dir;
                walk(item_dir, value_method);
                item_dir = off;
            }
            else if (value_ready[up] == 3) {
                item_dir = up;
                lookUp(value_method);
                if (value_method[up] == 2 && value_method[left] == 2 && value_method[right] == 2) {
                    item_dir = off;
                }
            }
            else if (value_ready[left] == 3) {
                item_dir = left;
                lookLeft(value_method);
                if (value_method[up] == 2 && value_method[left] == 2 && value_method[down] == 2) {
                    item_dir = off;
                }
            }
            else if (value_ready[right] == 3) {
                item_dir = right;
                lookRight(value_method);
                if (value_method[up] == 2 && value_method[right] == 2 && value_method[down] == 2) {
                    item_dir = off;
                }
            }
            else if (value_ready[down] == 3) {
                item_dir = down;
                lookDown(value_method);
                if (value_method[left] == 2 && value_method[right] == 2 && value_method[down] == 2) {
                    item_dir = off;
                }
            }
            else {

                //動くところ
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




    }
    //ここまでゲームのループ

    std::cout << "<<----ゲーム終了---->>" << std::endl;

    return 0;
}
