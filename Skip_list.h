#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include<string>
#include <vector>

using namespace std;

struct Skip_Node
{
    int key;
    std::string value;

    std::vector<Skip_Node*> forward;    // pointers to successor nodes

    Skip_Node (int k, const std::string& v, int level);
};

class Skip_list
{
    public:
        /** Default constructor */
        Skip_list();
        /** Default destructor */
        virtual ~Skip_list();

    void print ();
    Skip_Node* find (int searchKey);


    void insert (int searchKey, string newValue);
    void erase (int searchKey);

    private:

    Skip_Node* head;    // pointer to first node
    Skip_Node* NIL;     // last node


    int randomLevel ();
    int nodeLevel(const vector<Skip_Node*>& v);
    Skip_Node* makeNode (int key, string val, int level);

    // data members
    float p;
    int maxLevel;

    protected:


};

#endif // SKIP_LIST_H

