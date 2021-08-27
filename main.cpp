#include "Skip_list.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main ()
{
    Skip_list sl;                   // Initializing an empty Skip list

    for(int i = 0; i < 25; ++i)     //Inserting
    {
        std::stringstream slt;
        slt << i;
        sl.insert(i, slt.str());
    }
    cout<<"______________SKIP LIST_______________\n";
    cout<<"\nThe Values present in the Skip List\n\n";
    sl.print();                     //Display

    cout<<"\nSearching 10....\n\n";
    Skip_Node* pt = nullptr;
    pt = sl.find(10);               //Seaching 10
    if (pt)
        cout <<"Found!!\n";
    else
        cout <<"OPPS !! NOT Found!\n";

    cout<<"\nDeleting 5...\n\n";
    sl.erase(5);

    cout<<"Updated Skip List\n\n";
    sl.print();

    getchar();
}

