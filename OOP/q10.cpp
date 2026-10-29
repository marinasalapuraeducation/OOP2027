//Сервер(server.cpp)

#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

int server() {
    const int port = 8080;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }

    // Разрешить повторное использование адреса (удобно при перезапуске)
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;   // слушать на всех интерфейсах
    addr.sin_port = htons(port);         // сетевой порядок байт

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); return 1;
    }
    if (listen(server_fd, 5) < 0) {      // очередь до 5 ожидающих
        perror("listen"); return 1;
    }
    std::cout << "Server listening on port " << port << "\n";

    while (true) {
        sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        int client_fd = accept(server_fd, (sockaddr*)&client_addr, &len);
        if (client_fd < 0) { perror("accept"); continue; }

        std::cout << "Client connected\n";

        char buf[1024];
        ssize_t n;
        // Построчный протокол: читаем, пока клиент не закроет соединение
        while ((n = recv(client_fd, buf, sizeof(buf) - 1, 0)) > 0) {
            buf[n] = '\0';
            std::string line(buf);
            // простая обработка: в верхний регистр
            for (char& c : line) c = std::toupper((unsigned char)c);
            send(client_fd, line.c_str(), line.size(), 0);
        }
        close(client_fd);
        std::cout << "Client disconnected\n";
    }

    close(server_fd);
    return 0;
}

//Клиент(client.cpp)
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

int client() {
    const char* server_ip = "127.0.0.1";
    const int   port = 8080;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect"); return 1;
    }
    std::cout << "Connected to server\n";

    std::string line;
    while (std::getline(std::cin, line)) {          // запрос: строка от пользователя
        send(sock, line.c_str(), line.size(), 0);   // отправить запрос

        char buf[1024];
        ssize_t n = recv(sock, buf, sizeof(buf) - 1, 0);  // получить ответ
        if (n <= 0) break;
        buf[n] = '\0';
        std::cout << "Server: " << buf << "\n";
    }

    close(sock);
    return 0;
}


//Сервер пассивен, ждёт	bind → listen → accept
//Клиент активен, инициирует	connect()
//Адрес сервера известен клиенту	127.0.0.1:8080
//Обмен сообщениями по протоколу	send запрос / recv ответ
//Разделение ролей	Разные процессы, разный код, общая сеть
//Независимость	Запускаются отдельно, могут быть на разных машинах
//
//Суть модели можно показать «сервер» как модель черного ящика, с котрой клиент взаимодействует через открытый API 
