#ifndef SERVER_EXCEPTION_H

#inclcude <stdexcept>
#include<string>

class ServerExcpetion:public std::runtime_erro
{
    public:
    std::string message;
    std::string func_name;
    ServerExcpetion()=delete;
    ServerException(std::string const& func_name, std::string const& message);

    char const* what() const noexcept override;

    char const* where() const noexcept;

};

#endif