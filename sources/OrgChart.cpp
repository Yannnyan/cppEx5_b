#include "OrgChart.hpp"
#include <string>
#include <iostream>
#include <queue>
#include <deque>
#include <stdexcept>
#include <stack>

using namespace std;
using namespace ariel;

ariel::OrgChart::Node::Node(string name)
{
    this->name = move(name);
}
ariel::OrgChart::OrgChart()
{
    this->root = nullptr;
}
ariel::OrgChart::~OrgChart()
{
    // vector<Node *> temp = this->root->below_me;
    delete(this->root);
    // std::queue<vector<Node *>> q;
    // q.push(temp);
    // while(!q.empty())
    // {
    //     temp = q.front();
    //     q.pop();
    //     for(Node * node : temp)
    //     {
    //         if(!node->below_me.empty())
    //         {
    //             q.push(node->below_me);
    //         }
    //         delete node;
    //     }

    // }
}
ariel::OrgChart::iterator::iterator(iterator & iter)
{
    this->start = iter.start;
    this->q = iter.get_q();
}
std::queue<ariel::OrgChart::Node *> ariel::OrgChart::iterator::get_q()
{
    return this->q;
}
ariel::OrgChart & ariel::OrgChart::add_root(string const & str)
{
    if(this->root == nullptr)
    {
        this->root = new Node(str);
    }
    else
    {
        this->root->name = str;
    }
    return *this;
}
ariel::OrgChart & ariel::OrgChart::add_sub(string const & father, string const &child)
{
    // find the member inside the chart
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot add a sub while the root is null."));
    }
    OrgChart::iterator iter;
    iter = this->begin();
    while(iter != this->end())
    {
        if((*iter) == father)
        {
            iter.add_child(child);
            return *this;
        }
        ++iter;
    }
    throw(invalid_argument("father does not exist."));
}
void ariel::OrgChart::iterator::add_child(string const & child_name)
{
    for(Node * node : this->q.front()->below_me)
    {
        if(node->name == child_name)
        {
            return;
            // throw(invalid_argument("cannot add the child, it already exists."));
        }
    }
    this->q.front()->below_me.push_back(new Node(child_name));
}
ariel::OrgChart::iterator ariel::OrgChart::begin()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(this->root);
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::end()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(nullptr);
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::begin_level_order()
{  
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(this->root, OrgChart::traversals::lev_order);
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::begin_preorder()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(this->root, OrgChart::traversals::pre_order);
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::begin_reverse_order()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(this->root, OrgChart::traversals::rev_order);
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::end_level_order()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(this->root, OrgChart::traversals::lev_order);
    if(iter.size_q() == 0)
    {
        return iter;
    }
    while(iter.size_q() > 1)
    {
        iter++;
    }
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::end_preorder()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot iterate through an empty orgchart."));
    }
    iterator iter(this->root, OrgChart::traversals::pre_order);
    if(iter.size_q() == 0)
    {
        return iter;
    }
    while(iter.size_q() > 1)
    {
        iter++;
    }
    return iter;
}
ariel::OrgChart::iterator ariel::OrgChart::reverse_order()
{
    if(this->root == nullptr)
    {
        throw(invalid_argument("cannot traverse over null orgchart."));
    }
    iterator iter(this->root, OrgChart::traversals::rev_order);
    if(iter.size_q() == 0)
    {
        return iter;
    }
    while(iter.size_q() > 1)
    {
        iter++;
    }
    return iter;
}
void OrgChart::iterator::preorder(Node * current_node, queue<Node *> * q)
{
    q->push(current_node);
    for(Node * node: current_node->below_me)
    {
        preorder(node, q);
    }
}
ariel::OrgChart::iterator::iterator(Node * root , int traversal)
{
    if(root == nullptr)
    {
        this->q.push(nullptr);
        return;
    }
    // the default traversal is level order traversal
    if(traversal == OrgChart::traversals::def_order || traversal == OrgChart::traversals::lev_order)
    {
        this->start = root;
        queue<Node *> temp;
        temp.push(root);
        Node * current = nullptr;
        while(!temp.empty())
        {
            current = temp.front();
            this->q.push(current);
            temp.pop();
            for(Node * node : current->below_me)
            {
                temp.push(node);
            }
        }
        this->q.push(nullptr);
    }
    else if(traversal == OrgChart::traversals::pre_order)
    {
        this->start = root;
        preorder(this->start, &q);
        this->q.push(nullptr);
    }
    else if (traversal == OrgChart::traversals::rev_order)
    {
        this->start = root;
        queue<Node *> temp_queue;
        stack<Node *> temp_stack;
        temp_queue.push(root);
        Node * current = nullptr;
        long long i = 0;
        while(!temp_queue.empty())
        {
            current = temp_queue.front();
            temp_stack.push(current);
            temp_queue.pop();
            for(i = static_cast<long long>(current->below_me.size() - 1); i >= 0; i--)
            {
                temp_queue.push(current->below_me.at((size_t)i));
            }  
        }
        while(!temp_stack.empty())
        {
            this->q.push(temp_stack.top());
            temp_stack.pop();
        }
        this->q.push(nullptr);
    }
    else
    {
        throw(invalid_argument("cannot identify the travesal in the iterator constructor."));
    }
    
}
size_t OrgChart::iterator::size_q()
{
    return this->q.size();
}
ariel::OrgChart::iterator & ariel::OrgChart::iterator::operator=(ariel::OrgChart::iterator iter)
{
    this->q = iter.get_q();
    this->start = iter.start;
    return *this;
}
bool ariel::OrgChart::iterator::operator!=(ariel::OrgChart::iterator iter)
{
    if(iter.q.front() == nullptr && this->q.front() == nullptr)
    {
        return false;
    }
    if ( (this->q.front() == nullptr && iter.q.front() != nullptr) || (this->q.front() != nullptr && iter.q.front() == nullptr) )
    {
        return true;
    }
    return this->operator*() != (*iter);
}
string ariel::OrgChart::iterator::operator*()
{
    return this->q.front()->name;
}
ariel::OrgChart::iterator & ariel::OrgChart::iterator::operator++()
{
    this->q.pop();
    return *this;
}
ariel::OrgChart::iterator ariel::OrgChart::iterator::operator++(int)
{
    iterator iter(*this);
    this->q.pop();
    return iter;
}
string * ariel::OrgChart::iterator::operator->()
{
    return &(this->q.front()->name);
}
std::ostream & ariel::operator<<(std::ostream & stream, OrgChart const & chart)
{
    return stream;
}











