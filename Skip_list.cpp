#include "Skip_list.h"
#include <iostream>
#include<string>
#include <vector>
#include<limits>

Skip_Node::Skip_Node(int k, const string & v, int level): key(k), value(v)
{
    for (int i= 0; i< level; ++i)
        forward.emplace_back(nullptr);
}

Skip_list::Skip_list(): p(0.5), maxLevel(5)    //p=probablity
{


     int headKey= numeric_limits<int>::min();     // Initialize the head of the skip list- smallest possible key
     head = new Skip_Node(headKey, "head", maxLevel);

     int nilKey= numeric_limits<int>::max();      // Initialize the last element of the list- largest possible key
     NIL= new Skip_Node(nilKey, " ", maxLevel);

     for(size_t i= 0; i < head->forward.size(); ++i) //Connecting the starting & the end also all the levels
        head->forward[i] = NIL;

}

Skip_list::~Skip_list ()
{
    delete head;
    delete NIL;
}

// Function to generate random numbers
int Skip_list::randomLevel()
 {
    int level= 0;
    while((((double)rand()/ RAND_MAX))< p
          && level< maxLevel)
    {
        level ++;
    }
    return (level);
}

int Skip_list::nodeLevel (const std::vector<Skip_Node*>& v)
{
    int currentLevel = 1;
    int nilKey = std::numeric_limits<int>::max();       // last element's key is the largest
    if(v[0]->key == nilKey)
        return currentLevel;
    for(size_t i = 0; i < v.size(); ++i)
    {

        if(v[i] != nullptr && v[i]->key != nilKey)
        {
            ++currentLevel;
        }
        else
            break;

    }
    return currentLevel;
}

//Display

void Skip_list::print ()
{
    for(int i=0; i<=maxLevel;i++)
    {
        Skip_Node *list = head->forward[i];
        cout<<"Level  "<<i <<":  ";
        while (list != nullptr)
        {
            cout<<list->value<<" ";
            list = list->forward[i];

        }
        cout <<"\n";
    }
}

// Searching

Skip_Node* Skip_list::find(int searchKey)
{
    Skip_Node *x= head;
    unsigned int currentMaximum= nodeLevel(head->forward);
    for (int i= currentMaximum; i--> 0;)
    {
        while(x->forward[i] != nullptr && x->forward[i]->key < searchKey)
        {
            x= x->forward[i];
        }
    }
    x= x->forward[0];

    if(x->key == searchKey)
    {
        return x;
    }
    else
        return nullptr;

}


//Making a Node

Skip_Node* Skip_list::makeNode(int key, string val, int level)
{
    return new Skip_Node(key, val, level);
}

//Insert

void Skip_list::insert(int searchKey, std::string newValue)
{
    // reassign if node exists
    Skip_Node *x= nullptr;
    x= find(searchKey);
    if(x)
    {
        x->value= newValue;
        return;
    }

    // vector of pointers that needs to be updated to account for the new node
    vector<Skip_Node*> update(head->forward);
    int currentMaximum= nodeLevel(head->forward);
    x= head;

    // Search the list
    for(int i= currentMaximum; i--> 0;)
    {

        while(x->forward[i] != nullptr && x->forward[i]->key< searchKey)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    // Create new node

    int newNodeLevel = 1;
    if(x->key != searchKey)
    {
        newNodeLevel = randomLevel();
        int currentLevel = nodeLevel(update);
        if (newNodeLevel > currentLevel)
        {

            for(int i= currentLevel + 1; i< newNodeLevel; ++i)
            {
                update[i]= head;
            }
        }
        x= makeNode(searchKey, newValue, newNodeLevel);
    }

    // connect pointers of predecessors and new node to successors
    for (int i = 0; i < newNodeLevel; ++i)
    {
        x->forward[i]= update[i]->forward[i];
        update[i]->forward[i]= x;
    }
}
//Delete

void Skip_list::erase(int searchKey)
{
    // vector of pointers that needs to be updated to account for the deleted node
    vector<Skip_Node*> update(head->forward);
    Skip_Node* x= head;
    int currentMaximum= nodeLevel(head->forward);

    // search and update pointers
    for(int i = currentMaximum; i--> 0;)
    {

        while(x->forward[i] != nullptr && x->forward[i]->key < searchKey)
            x = x->forward[i];
        update[i]= x;
    }
    x= x->forward[0];

    // update pointers and delete node
    if(x->key == searchKey)
    {
        for(size_t i = 0; i< update.size(); ++i)
        {
            if (update[i]->forward[i] != x)
                break;

            update[i]->forward[i]= x->forward[i];
        }
        delete x;
    }
}

