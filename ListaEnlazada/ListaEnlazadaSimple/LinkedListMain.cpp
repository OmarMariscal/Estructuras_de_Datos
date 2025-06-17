#include <iostream>
#include "LinkedList.h"

int main(){
    LinkedList::LinkedList<int> list;


    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    std::cout<<*list.searchByValue(4)<<std::endl;

    return 0;
}