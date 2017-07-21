#pragma once

#include "./asio-1.10.8/asio.hpp"
#include <iostream>
#include <string>

using asio::ip::tcp;

class Client {
private:
    asio::io_service io_service;
    tcp::socket sock{ io_service };
    bool gameflug;
    int turn;

    void Send(const std::string str);
    std::string Recv(int byte);
    void Recv(int value[], int byte);

public:
    //接続
    void connectToServer();

    //getReady.配列はint型で要素数10.
    bool getReady(int value[]);

    //メソッド.配列はint型で要素数10.
    void walkUp     (int value[]);
    void walkDown   (int value[]);
    void walkRight  (int value[]);
    void walkLeft   (int value[]);
    void putUp      (int value[]);
    void putDown    (int value[]);
    void putRight   (int value[]);
    void putLeft    (int value[]);
    void lookUp     (int value[]);
    void lookDown   (int value[]);
    void lookRight  (int value[]);
    void lookLeft   (int value[]);
    void searchUp   (int value[]);
    void searchDown (int value[]);
    void searchRight(int value[]);
    void searchLeft (int value[]);
};


/*~~~~~~~~~~~~~~~~~以下、クラスじゃなく書けるように無理やり直したもの~~~~~~~~~~~~~~~~~*/

extern Client client;

//接続
void connectToServer();

//getReady.配列はint型で要素数10.
bool getReady   (int value[]);

//メソッド.配列はint型で要素数10.
void walkUp     (int value[]);
void walkDown   (int value[]);
void walkRight  (int value[]);
void walkLeft   (int value[]);
void putUp      (int value[]);
void putDown    (int value[]);
void putRight   (int value[]);
void putLeft    (int value[]);
void lookUp     (int value[]);
void lookDown   (int value[]);
void lookRight  (int value[]);
void lookLeft   (int value[]);
void searchUp   (int value[]);
void searchDown (int value[]);
void searchRight(int value[]);
void searchLeft (int value[]);