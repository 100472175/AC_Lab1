#include <iostream>
// Created by paula on 29/09/23.
//

namespace Sim{

  int my_is_digit(const std::string &string_to_try){
    for(int i = 1; i < int(string_to_try.length()); i++){
      if(std::isdigit(string_to_try[i]) !=1){
        std::cout << "Error: time steps must be numeric.\n";
        return -1;
      }
    }
    if(string_to_try[0] == '-'){
      std::cout << "Error: Invalid number of time steps.\n";
      return -2;
    }
    if(std::isdigit(string_to_try[0]) != 1){
      return -1;
    }
    return 0;
  }

  int validate_arguments(int num_args, char** args){
    if(num_args != 4){
      std::cerr << "Error: invalid number of arguments: " << num_args -1 << ".\n";
      return -1;
    }
    int first_argument_validation = my_is_digit(args[1]);
    if(first_argument_validation != 0){
      return first_argument_validation;
    }
    return 0;
  }

}