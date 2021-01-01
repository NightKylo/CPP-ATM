#ifndef USERS_H_
#define USERS_H_

#include <iostream>
#include <vector>

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

typedef std::vector<User> container;
auto const STRING_NOT_FOUND = std::string::npos;

container get_users(const std::string& path);
void write_users(const container& con, const std::string& path);
void print_user_vars(const User& user);

#endif