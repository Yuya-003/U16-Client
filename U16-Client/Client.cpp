#include "Client.h"

void Client::connectToServer() {
    try {
        //情報の入力
        std::cout << "IPアドレス\n>";
        std::string addr;
        std::cin >> addr;
        if (addr == "localhost") {
            addr = "127.0.0.1";
            std::cout << addr << std::endl;
        }
        std::cout << "ポート番号\n>";
        unsigned short port = 0;
        std::cin >> port;
        std::cout << "チーム名\n>";
        std::string teamname;
        std::cin >> teamname;
        std::cout << "サーバーに接続します。続行するなら何かキーを押してください。";
        std::cin.ignore(INT_MAX, '\n');
        std::cin.get();

        //接続
        sock.connect(tcp::endpoint(asio::ip::address::from_string(addr), port));
        //チーム名の送信
        Send(teamname);

        gameflug = true;
        turn = 0;
        std::cout << "<<----接続しました---->>" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

void Client::Send(const std::string str) {
    try {
        asio::write(sock, asio::buffer(str));
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

std::string Client::Recv(int byte) {
    try {
        asio::streambuf receive_buffer;
        asio::read(sock, receive_buffer, asio::transfer_at_least(byte));
        return asio::buffer_cast<const char*>(receive_buffer.data());
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

void Client::Recv(int value[], int byte) {
    try {
        std::string receive;
        asio::streambuf receive_buffer;
        asio::read(sock, receive_buffer, asio::transfer_at_least(byte));
        receive = asio::buffer_cast<const char*>(receive_buffer.data());

        for (int i = 0; i < 10; i++) {
            value[i] = receive[i] - 48;
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

bool Client::getReady(int value[]) {
    if (gameflug) {
        //while (Recv(1) != "@\r\n");
        Recv(1);
        Send("gr\r\n");
        Recv(value, 10);
        std::cout << "\n< Turn " << ++turn << " >" << std::endl;
        std::cout << "GetReady    : ";
        for (int i = 0; i < 10; i++)std::cout << value[i];
        std::cout << std::endl;
        if (value[0] == 0)gameflug = false;
    }
    return gameflug;
}

void Client::walkUp(int value[]) {
    Send("wu\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "WalkUp      : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::walkDown(int value[]) {
    Send("wd\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "WalkDown    : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::walkRight(int value[]) {
    Send("wr\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "WalkRight   : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::walkLeft(int value[]) {
    Send("wl\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "WalkLeft    : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::putUp(int value[]) {
    Send("pu\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "PutUp       : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::putDown(int value[]) {
    Send("pd\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "PutDown     : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::putRight(int value[]) {
    Send("pr\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "PutRight    : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::putLeft(int value[]) {
    Send("pl\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "PutLeft     : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::lookUp(int value[]) {
    Send("lu\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "LookUp      : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::lookDown(int value[]) {
    Send("ld\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "LookDown    : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::lookRight(int value[]) {
    Send("lr\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "LookRight   : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::lookLeft(int value[]) {
    Send("ll\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "LookLeft    : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::searchUp(int value[]) {
    Send("su\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "SearchUp    : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::searchDown(int value[]) {
    Send("sd\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "SearchDown  : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::searchRight(int value[]) {
    Send("sr\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "SearchRight : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}

void Client::searchLeft(int value[]) {
    Send("sl\r\n");
    Recv(value, 10);
    Send("#\r\n");
    std::cout << "SearchLeft  : ";
    for (int i = 0; i < 10; i++)std::cout << value[i];
    std::cout << std::endl;
    if (value[0] == 1)gameflug = true;
    else gameflug = false;
}


/*~~~~~~~~~~~~~~~~~以下、クラスじゃなく書けるように無理やり直したもの~~~~~~~~~~~~~~~~~*/

Client client;

void connectToServer() { client.connectToServer(); }

bool getReady   (int value[]) { return client.getReady(value); }

void walkUp     (int value[]) { client.walkUp       (value); }
void walkDown   (int value[]) { client.walkDown     (value); }
void walkRight  (int value[]) { client.walkRight    (value); }
void walkLeft   (int value[]) { client.walkLeft     (value); }
void putUp      (int value[]) { client.putUp        (value); }
void putDown    (int value[]) { client.putDown      (value); }
void putRight   (int value[]) { client.putRight     (value); }
void putLeft    (int value[]) { client.putLeft      (value); }
void lookUp     (int value[]) { client.lookUp       (value); }
void lookDown   (int value[]) { client.lookDown     (value); }
void lookRight  (int value[]) { client.lookRight    (value); }
void lookLeft   (int value[]) { client.lookLeft     (value); }
void searchUp   (int value[]) { client.searchUp     (value); }
void searchDown (int value[]) { client.searchDown   (value); }
void searchRight(int value[]) { client.searchRight  (value); }
void searchLeft (int value[]) { client.searchLeft   (value); }