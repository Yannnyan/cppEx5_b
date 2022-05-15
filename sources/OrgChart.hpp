#include <string>
#include <iostream>
#include <vector>

namespace ariel
{
    class OrgChart
    {
        
        private:
            class Node
            {
                public:
                    // my name as the the root of the values below me
                    std::string name;
                    // the values that below me
                    std::vector<Node> below_me;
            };
            Node * root;
            

        public:
            // iterator
            class iterator
            {
                private:
                    Node * current;

                public:
                    iterator(OrgChart * current);
                    // prefix
                    iterator & operator++();
                    // postfix
                    iterator & operator++(int); 
                    std::string operator*();
                    bool operator!=(iterator comp);
                    std::string * operator->();

            };
            // iterator functions
            iterator begin();
            iterator end();
            // constructors
            OrgChart();
            // functions to set the tree
            OrgChart & add_root(std::string root);
            OrgChart & add_sub(std::string father, std::string child);
            // traversing the tree
            iterator reverse_order();
            iterator begin_level_order();
            iterator begin_reverse_order();
            iterator begin_preorder();
            iterator end_preorder();
            iterator end_level_order();
            iterator end_reverse_order();
            // operators
            friend std::ostream & operator <<(std::ostream & stream, OrgChart const & chart);

        
    };
}




