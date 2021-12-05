#pragma once

#include <asio>
#include <array>
#include <functional>

#include <Experimental>

#include <format>

template<typename StringType, typename... Args>
void println(StringType &&format, Args &&... args)
{
    fmt::print(std::forward<StringType>(format), std::forward<Args>(args)...);
    std::putc('\n', stdout);
}

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

namespace Network
{

class Manager : public ASingleton<Manager>
{
    boost::asio::io_context Context;
    AThread Thread;

    bool Active = false;
public:
    boost::asio::io_context &GetContext()
    {
        return Context;
    }

    bool IsActive() const { return Active; }

    void Activate()
    {
        Active = true;
    }

    void Deactivate()
    {
        Active = false;
    }

    template<typename Functor>
    void Start(Functor &&callback)
    {
        Active = true;
        Thread = AThread([this, callback]() {
            callback(Context);
            Context.run();
        });
    }

    template<typename Functor>
    void Stop(Functor &&callback)
    {
        Context.stop();
        if (Thread.isJoinable())
        {
            Thread.join();
        }

        callback();
        Active = false;
    }
};

namespace UDP
{

class Request
{
public:

};

class Server
{
public:
    Server(int16_t port): socket_(Network::Manager::getInstance().GetContext(), udp::endpoint(udp::v4(), port))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_, std::bind(&Server::handle_receive, this, std::placeholders::_1));
    }

    void handle_receive(const boost::system::error_code &error)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            boost::shared_ptr<std::string> message(new std::string("HelloWorld"));

            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_, std::bind(&Server::handle_send, this, message));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/)
    {
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1> recv_buffer_;
};

}

namespace TCP
{

class Request
{
public:

};

class Response
{
public:
    Request *request = nullptr;
};

class Parser
{
public:
    virtual void Parse(const String &buffer) = 0;
    virtual bool IsComplete() const = 0;
    virtual String Flush() = 0;
};

class CommandParser : public Parser
{
    String command;
    bool complete = false;
public:
    void Parse(const String &buffer) override
    {
        if (complete)
        {
            return;
        }

        for (size_t i = 0; i < buffer.size(); ++i)
        {
            if (buffer[i] == '\n')
            {
                complete = true;
                return;
            }

            command += buffer[i];
        }
    }

    bool IsComplete() const override { return complete; }

    String Flush() override
    {
        String result;

        if (complete)
        {
            result = HandleCommand(command);
            complete = false;
        }

        command.clear();

        return result;
    }

    virtual String HandleCommand(const String &command)
    {
        return command + "\n";
    }
};

class HTTPParser : public Parser
{
public:

};


class Connection
{
public:

    Connection(): Context(Network::Manager::getInstance().GetContext()), Socket(Context)
    {

    }

    SharedReference<Parser> protocol;

    tcp::socket &GetSocket()
    {
        return Socket;
    }

    void Connect(const String &host, const String &port)
    {
        boost::asio::ip::tcp::resolver resolver(Context);
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host.toUtf8().data(), port.toUtf8().data());
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(query);
        //boost::asio::ip::tcp::endpoint ep = *iter;
        //boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 8080);
        boost::asio::ip::tcp::endpoint ep = *endpoints;
        println("Connecting: {}:{}/{}", ep.address().to_string(), ep.port(), ep.protocol().protocol());

        boost::asio::async_connect(Socket, endpoints, std::bind([this](const boost::system::error_code &error) {
            if (!error)
            {
                println("Connected");
            }
            else
            {
                println("Error: {}", error.message());
            }
        }, std::placeholders::_1));
    }

    void Disconnect()
    {
        Socket.close();
        println("Disconnected");
    }

    void Send(const std::string &buffer)
    {
        boost::asio::write(Socket, boost::asio::buffer(buffer.data(), buffer.size()));
        println("Sent: {}", buffer);

        /*boost::asio::async_write(Socket, boost::asio::buffer(command.data(), command.size()), std::bind([](const boost::system::error_code &error) {
            if (!error)
            {
                println("Sent");
            }
            else
            {
                println("Error: {}", error.message());
            }
        }, std::placeholders::_1));*/
    }

    void Receive2()
    {
        std::memset(Buffer.data(), 0, 512);
        /*size_t reply_length = */Socket.async_read_some(boost::asio::buffer(Buffer.data(), Buffer.size() - 1), std::bind([this](const boost::system::error_code &error, std::size_t bytes_transferred) {
            if (!error)
            {
                println("Received: {}", Buffer.data());
            }
            Receive2();
        }, std::placeholders::_1, std::placeholders::_2));
    }

    void Receive()
    {
        Size = 0;
        //Buffer.resize(512, '\0');
        std::memset(Buffer.data(), 0, 512);
        /*boost::asio::async_read(Socket, boost::asio::buffer((uint8_t *)&Size, sizeof(Size)), std::bind([this](const boost::system::error_code &error) {
            if (!error)
            {
                println("Incomming package size: {}", Size);
                Buffer.resize(Size);
                boost::asio::async_read(Socket, boost::asio::buffer(Buffer.data(), Buffer.size()), std::bind(&Connection::OnReceive, this, std::placeholders::_1));
            }
        }, std::placeholders::_1));*/
        Socket.async_read_some(boost::asio::buffer(Buffer.data(), Buffer.size() - 1), std::bind([this](const boost::system::error_code &error, std::size_t bytes_transferred) {
            if (!error)
            {
                println("Received: {}", Buffer.data());
                protocol->Parse(Buffer.data());
                if (protocol->IsComplete())
                {
                    String result = protocol->Flush();
                    Send(result.toUtf8().data());
                }
                Receive();
            }
            else if (error == boost::asio::error::eof ||
                error == boost::asio::error::connection_aborted ||
                error == boost::asio::error::connection_refused ||
                error == boost::asio::error::connection_reset)
            {
                println("Client disconnected");
            }
            else
            {
                println("Error[{}]:{}: {}", error.category().name(), error.value(), error.message());
            }

            /*if (error == boost::system::errc::)
            {

            }*/
        }, std::placeholders::_1, std::placeholders::_2));
        /*static char data[2];
        boost::asio::async_read(Socket, boost::asio::buffer(&data, 1), std::bind([this](const boost::system::error_code &error) {
            fmt::print("{}", data);
            Receive();
        }, std::placeholders::_1));*/
        //message_ = make_daytime_string();
        //boost::asio::async_write(socket_, buffer, std::bind(this, &Connection::handle_write));
    }

    void OnReceive(const boost::system::error_code &error)
    {
        if (!error)
        {
            println("Received: {}", Buffer.data());
            Receive();
        }
        else
        {
            println("Error: {}", error.message());
        }
    }

private:

    boost::asio::io_context &Context;
    tcp::socket Socket;

    uint16_t Size = 0;
    std::array<char, 512> Buffer;
};

template<typename Protocol>
class Server
{
public:
    Server(int16_t port): Context(Network::Manager::getInstance().GetContext()), acceptor_(Context, tcp::endpoint(tcp::v4(), port))
    {
        Listen();
    }

private:
    void Listen()
    {
        Connection *new_connection = Create<Connection>();
        new_connection->protocol = Create<Protocol>();
        acceptor_.async_accept(new_connection->GetSocket(), std::bind(&Server::OnClientConnected, this, new_connection, std::placeholders::_1));
    }

    void OnClientConnected(Connection *new_connection, const boost::system::error_code &error)
    {
        if (!error)
        {
            println("Client connected");
            new_connection->Receive();
        }
        else
        {
            println("Error: {}", error.message());
        }

        Listen();
    }

    std::vector<Connection *> ActiveClients;

    boost::asio::io_context &Context;
    tcp::acceptor acceptor_;
};

}

namespace HTTP
{

class Connection
{
public:

};

class Request
{
public:

};

class Response
{
public:
    Request *request = nullptr;
};

class Server
{
public:

};
}

}

class ConsoleApplication : public AApplication, public ARunnable
{
    ARunLoop loop;
public:
    ConsoleApplication():
        loop(*this)
    {

    }

    AError execute() override
    {
        loop.resume();
        loop.execute();
        return AError::getEmptyError();
    }

protected:
    void onExecute() override
    {
        std::string command;
        std::getline(std::cin, command);
        if (command == "exit")
        {
            loop.exit();
            return;
        }

        Console::getInstance().applyCommand(command);
        loop.resume();
    }
};