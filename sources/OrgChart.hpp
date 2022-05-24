#include <string>
#include <iostream>
#include <vector>
#include <queue>


namespace ariel
{
    class OrgChart
    {
        enum traversals
        {
            def_order, 
            lev_order,
            pre_order,
            rev_order
        };
        
        private:
            class Node
            {
                public:
                    Node(std::string name);
                    // my name as the the root of the values below me
                    std::string name;
                    // the values that below me
                    std::vector<Node *> below_me;
            };
            Node * root;
            

        public:
            // iterator
            class iterator
            {
                private:
                    // points at the current member
                    Node * start;
                    std::queue<Node *> q;
                    void preorder(Node * current_node, std::queue<Node *> * q);
                public:
                    iterator(Node * root = nullptr, int traversal = OrgChart::traversals::def_order);
                    iterator(iterator & iter);
                    iterator & operator=(iterator iter);
                    // prefix
                    iterator & operator++();
                    // postfix
                    iterator operator++(int); 
                    std::string operator*();
                    bool operator!=(iterator iter);
                    std::string * operator->();
                    size_t size_q();
                    std::queue<Node *> get_q();
                    void add_child(std::string const & child_name);

            };
            // iterator functions
            iterator begin();
            iterator end();
            // constructors
            OrgChart();
            // destructor
            ~OrgChart();
            // functions to set the tree
            /**
             * @brief This function supposed to insert a root into the orgchart
             * if a root already exists it replaces it.
             * 
             * @param root 
             * @return OrgChart& 
             */
            OrgChart & add_root(std::string const & str);
            /**
             * @brief this function is supposed to insert a child into the orgchart under
             * the father.
             * 
             * @param father 
             * @param child 
             * @return OrgChart& 
             */
            OrgChart & add_sub(std::string const & father, std::string const & child);
            
            // traversing the tree
            /**
             * @brief traversal on the tree from up to bottom
             * 
             * @return iterator 
             */
            iterator begin_level_order();
            /**
             * @brief traversal on the tree from bottom up
             * 
             * @return iterator 
             */
            iterator begin_reverse_order();
            /**
             * @brief traverse the tree by branches from top to bottom
             * 
             * @return iterator 
             */
            iterator begin_preorder();
            iterator end_preorder();
            iterator end_level_order();
            iterator reverse_order();
            // operators
            friend std::ostream & operator <<(std::ostream & stream, OrgChart const & chart);

        
    };
}




