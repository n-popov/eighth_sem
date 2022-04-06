#include <iostream>

#include <boost/asio.hpp>

bool read(boost::asio::ip::tcp::socket& socket, std::string& message)
{
    // Буфер -- "коробочка" с байтами
    boost::asio::streambuf buffer;
    // Достаём байты из сокета, пока не встретится \n
    // Выбран этот разделитель, но можно выбирать любой, какой угодно
    boost::asio::read_until(socket, buffer, '\n');
    // Создаём поток на основе буфера
    std::istream stream(&buffer);
    // Достаём из потока строчку с сообщением
    std::getline(stream, message);
    return message != "EXIT";
}

int main()
{
    auto port = 65000u;
    // Специальный ip -- адрес компьютера,
    // на котором запущены процессы.
    std::string ip = "127.0.0.1";

    // Адаптер для порта
	boost::asio::ip::tcp::endpoint endpoint(
            boost::asio::ip::address::from_string(ip), port);

    // Технический класс -- сервис ввода-вывода
    boost::asio::io_service io_service;

    // Специальный адаптер -- acceptor -- нужен для того,
    // чтобы занять эндпоинт и ждать на нём
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
    acceptor.bind(endpoint);
    // Начинаем ждать
    acceptor.listen();


    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);

    std::string message;

    while (read(socket, message)) {
        std::cout << message << std::endl;
    }
}