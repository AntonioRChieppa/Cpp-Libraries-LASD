
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
#include <limits>

/* ************************************************************************** */

int main() {
  std::cout << "LASD Libraries 2025" << std::endl;
  
  char repeat;
  do{
    std::cout << "Scegliere quali test eseguire: "<<std::endl;
    std::cout << "1. Simpletest.cpp" << std::endl;
    std::cout << "2. Mytest.cpp" << std::endl;
    int choice;
    std::cin >> choice;

    switch(choice){

      case 1:
        lasdtest();
        break;

      case 2:
        mytest();
        break;

      default:
        std::cout << "Scelta non valida. " << std::endl;
        break;
    }

    std::cout << "\nVuoi eseguire un altro test? (s/n): ";
    std::cin >> repeat;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  }while(repeat == 's' || repeat == 'S');
  
  return 0;
}
