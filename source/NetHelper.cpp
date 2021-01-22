#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <msgpack.hpp>
#include <chrono>
#include <thread>
#include <pthread.h>

//NOTE: WORKS
#define PORT 2001

class NetHelper
{
public:
    NetHelper()
    {
        std::cout << "Enter s for server, c for client:" << std::endl;
        std::cin >> connectionType;
        this->init();
        threadPointer = new std::thread(&NetHelper::getMsg<std::pair<int, int>>, this);
    }
    ~NetHelper() { delete this->threadPointer; }
    void run()
    {
        //this->getMsg();
        this->sendMsg(std::make_pair(5, 5));
    }

    template <typename T>
    void sendMsg(T value)
    {
        std::cout << "sending " << value.first << value.second << std::endl;
        std::stringstream buffer1;
        //if (mode == 's')
        //{
        msgpack::pack(buffer1, value);
        socket.send(buffer1.str().c_str(), buffer1.str().length() + 1);
        //mode = 'r';
        //}
    }

    template <typename T>
    void getMsg()
    {
        while (true)
        {
            //if (mode == 'r')
            //{
            socket.receive(buffer, sizeof(buffer), recived);
            //std::cout << recived;
            if (recived > 0)
            {
                this->fullyRecive = true;
                msgpack::object_handle oh1;
                std::string str(buffer);
                try
                {
                    oh1 =
                        msgpack::unpack(str.data(), str.size());
                    std::cout << str.c_str() << std::endl;
                }
                catch (...)
                {
                    //oh1 = msgpack.unpack(str.data(), str.size());
                    std::cout << str.c_str() << "error" << std::endl;
                }
                msgpack::object deserialized = oh1.get();
                this->deserializedCopy = deserialized;
                std::pair<int, int> strtest;
                deserialized.convert(strtest);
                std::cout << "before print recived" << std::endl;
                std::cout << "received " << strtest.first << strtest.second << std::endl;
                //mode = 's';
                //return std::make_pair(true, deserialized);
            }
        }
    }
    //return std::make_pair(false, msgpack::object(NULL));
    msgpack::object getMsgCopy() const
    {
        return this->deserializedCopy;
    }

    bool getFullyRecive() const
    {
        return this->fullyRecive;
    }

    void setFullyRecive(bool value)
    {
        this->fullyRecive = value;
    }

private:
    std::thread *threadPointer = nullptr;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType, mode;
    char buffer[2000];
    bool fullyRecive = false;
    std::size_t recived;
    std::string text = "connected";
    msgpack::object deserializedCopy;
    void init()
    {
        if (connectionType == 's')
        {
            sf::TcpListener listner;
            listner.listen(PORT);
            listner.accept(socket);
        }
        else
        {
            socket.connect(ip, PORT);
        }
        //socket.send(text.c_str(), text.length() + 1);
        //socket.receive(buffer, sizeof(buffer), recived);
    }
};
