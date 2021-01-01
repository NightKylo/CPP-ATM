#include <iostream>
#include "includes/users.h"
#include <vector>
#include <conio.h>

auto const PATH = std::string("users");

void atm(User user);
void update_users(User user);

int main(void){
    int id;
    std::string pin;
    std::cout << "\n    Welcome to your ATM of trust\n\n    ID\n>>> ";
    std::cin >> id;
    std::cout << "    PIN\n>>> ";
    std::cin >> pin;
    container con = get_users(PATH);
    
    /*for(container::const_iterator it = con.begin(); it != con.end(); ++it){
        User user = *it;
        print_user_vars(user);
    }*/

    //Loop that finds the correct user by id and pin
    for(container::const_iterator iter = con.begin(); iter != con.end(); ++iter){
        User user = *iter;
        if(user.id == id && user.pin == pin){
            atm(user);
            break;
        }
    }
    
    std::cout << "LOGOUT" << std::endl;
    return 0;
}

void atm(User user){
    //print_user_vars(user);
    if(user.gender.find("female") != STRING_NOT_FOUND){
        std::cout << "\n    What do you want to do Mrs. " << user.name << std::endl;
    }
    else{
        std::cout << "\n    What do you want to do Mr. " << user.name << std::endl;
    }

    std::cout << "\n    [0] Show balance\n    [1] Withdraw money\n    [2] Pay money in\n    [3] Change PIN\n    [4] Personal information\n    [5] Quit\n>>> ";
    int key;
    int money = 0;
    std::cin >> key;
    std::string pin;

    switch (key)
    {
        case 0:
            std::cout << "\n    Your current balance is " << user.balance << " $" << std::endl;
            getch();
            
            break;
        case 1:
            std::cout << "\n    How much money do you want to withdraw\n\n    [0] 20 $\n    [1] 50 $\n    [2] 100 $\n    [3] 250 $\n    [4] Custom\n    [5] Cancel\n>>> ";
            int index;
            std::cin >> index;
            switch (index)
            {
                case 0:
                    money = 20;
                    break;
                case 1:
                    money = 50;
                    break;
                case 2:
                    money = 100;
                    break;
                case 3:
                    money = 250;
                    break;
                case 4:
                    std::cout << "\n>>> ";
                    std::cin >> money;
                    break;
                case 5:
                    break;
                default:
                    std::cout << "\n    There is no option with key " << index << std::endl;
                    break;
            }
            if(money != 0 && user.balance - money > -2000){
                user.balance -= money;
                std::cout << "\n    Your new balance is " << user.balance << " $" << std::endl;
                getch();
            }
            break;
        case 2:
            std::cout << "\n    How much money do you want to pay in\n>>> ";
            std::cin >> money;
            user.balance += money;
            std::cout << "\n    Your new balance is " << user.balance << " $" << std::endl;
            getch();
            break;
        case 3:
            std::cout << "\n    Which PIN do you want to have\n>>> ";
            std::cin >> pin;
            if(pin.length() == 4 && pin.find("0000") == STRING_NOT_FOUND){
                user.pin = pin;
            }
            else{
                std::cout << "\n    The pin needs a size of 4 digits." << std::endl;
                break;
            }
            user.pin = pin;
            std::cout << "\n    Your new PIN is " << user.pin << std::endl;
            getch();
            break;  
        case 4:
            std::cout << "\n    ID:          " << user.id << "\n    firstname:   " << user.firstname << "\n    name:        " << user.name << "\n    age:         " << user.age << "\n    pin:         " << user.pin << "\n    gender:      " << user.gender << "\n    balance:     " << user.balance << " $" << std::endl;
            getch();
            break;
        case 5:
            main();
            return;
        default:
            std::cout << "\n    There is no option with key " << key << std::endl;
            break;
    }

    update_users(user);
    atm(user);
}

void update_users(User user){
    container con  = get_users(PATH);
    for(container::iterator iter = con.begin(); iter != con.end(); ++iter){
        User con_user = *iter;
        if(user.id == con_user.id){
            con.erase(iter);
            con.insert(iter, user);
        }
    }
    write_users(con, PATH);
}