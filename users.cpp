#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>

struct User
{
    int id;
    std::string firstname;
    std::string name;
    int age;
    std::string pin;
    std::string gender;
    long long int balance;
};

auto const STRING_NOT_FOUND = std::string::npos;
typedef std::vector<User> container;

void write_users(const container& con, const std::string& path);

void print_user_vars(const User& user)
{
   std::cout << "{\n" << "  id: " << user.id << "\n  firstname: " << user.firstname
             << "\n  name: " << user.name << "\n  age: " << user.age
             << "\n  PIN: " << user.pin << "\n  gender: " << user.gender 
             << "\n  balance: " << user.balance << "\n}" << "\n" << std::endl;
}

container get_users(const std::string& path){
    std::ifstream file;
    std::string line;
    container con;
    std::vector<std::string> values = {"id", "firstname", "name", "age", "pin", "gender", "balance"};

    file.open(path, std::ios::binary | std::ios::in);
    User proto_user;
    while(true){
        std::getline(file , line);
        if(file.fail())
            break;
        if(line.find(":") != STRING_NOT_FOUND){
            for(int i = 0; i < values.size(); i++){
                if(line.find(values[i]) != STRING_NOT_FOUND){
                    std::string value;
                    for(int v = 0; v < line.length(); v++){
                        if(v > line.find(":") && v != line.length() - 1){
                            value += line[v];
                        }
                    }
                    
                    //std::cout << "String: " << value << "\nLen: " << value.length() << std::endl;
                    if(strcmp(values[i].c_str(), "id") == 0){
                        proto_user.id = stoi(value);
                    }
                    else if(strcmp(values[i].c_str(), "firstname") == 0){
                        proto_user.firstname = value;
                    }
                    else if(strcmp(values[i].c_str(), "name") == 0){
                        proto_user.name = value;
                    }
                    else if(strcmp(values[i].c_str(), "age") == 0){
                        proto_user.age = stoi(value);
                    }
                    else if(strcmp(values[i].c_str(), "pin") == 0){
                        proto_user.pin = value;
                    }
                    else if(strcmp(values[i].c_str(), "gender") == 0){
                        proto_user.gender = value;
                    }
                    else if(strcmp(values[i].c_str(), "balance") == 0){
                        proto_user.balance = std::stoll(value);
                    }
                    break;
                }
            } 
        }
        else if(line.find("}") != STRING_NOT_FOUND){
            //print_user_vars(&proto_user);
            con.push_back(proto_user);
            //cout << "Added user at " << user_num << endl;
        }
    }

    file.close();
    /*for(container::const_iterator it = con.begin(); it != con.end(); ++it){
        User user = *it;
        print_user_vars(user);
    }*/

    return con;
}

void write_users(const container& con, const std::string& path){
    std::ofstream file;
    file.open(path);
    std::vector<std::string> user_strings (con.size());
    for(container::const_iterator iter = con.begin(); iter != con.end(); ++iter){
        User user = *iter;
        std::ostringstream stream;
        stream << "{\n    id:" << user.id << "\n    firstname:" << user.firstname << "\n    name:" << user.name << "\n    age:" << user.age << "\n    pin:" << user.pin << "\n    gender:" << user.gender << "\n    balance:" << user.balance << "\n}\n";
        user_strings.push_back(stream.str());
    }
    std::string user_string;
    
    for(std::vector<std::string>::iterator iter = user_strings.begin(); iter != user_strings.end(); ++iter){
        user_string += *iter;
    }

    //std::cout << user_string;
    file << user_string;
    file.close();
}
