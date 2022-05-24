#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace ariel;

// test constructors
TEST_CASE("Constructors")
{
    CHECK_NOTHROW(OrgChart c);
}

// test getters and setters
TEST_CASE("add_root")
{
    OrgChart c;
    c.add_root("carrot");
    CHECK((*c.begin())==("carrot"));
    c.add_root("artishock");
    CHECK((*c.begin())==("artishock"));
}
TEST_CASE("add_sub")
{
    OrgChart c;
    c.add_root("tea");
    c.add_sub("tea","ginger");
    c.add_sub("tea", "lemon");
    c.add_sub("tea","sugar");
    c.add_sub("lemon","seed");
    c.add_sub("sugar", "cane");
    
    auto it = c.begin_level_order();
    // first level
    CHECK((*it)==("tea"));
    // increment
    it++;
    // store variables and counter
    // [ginger, lemon, sugar]
    vector<bool> sec_level(3);
    sec_level.at(0) = false;
    sec_level.at(1) = false;
    sec_level.at(2) = false;
    // second level
    for(int i=0; i<3; i++)
    {
        if((*it)==("ginger"))
        {
            if(sec_level.at(0) == true)
            {
                CHECK_NOTHROW(throw("ginger found twice."));
            }
            else
            {
                sec_level.at(0) = true;
            }
        }
        else if((*it)==("lemon"))
        {
            if(sec_level.at(1) == true)
            {
                CHECK_NOTHROW(throw("lemon found twice."));
            }
            else
            {
                sec_level.at(1) = true;
            }
        }
        else if((*it)==("sugar"))
        {
            if(sec_level.at(2) == true)
            {
                CHECK_NOTHROW(throw("sugar found twice."));
            }
            else
            {
                sec_level.at(2) = true;
            }
        }
        else
        {
            CHECK_NOTHROW(throw("unknown word to orgchart is found"));
        }
        it++;

    }
    // third level
    // [seed, cane]
    bool seed = false;
    bool cane = false;
    for(int i=0; i<2; i++)
    {
        if((*it)==("seed"))
        {
            if (seed == true)
            {
                CHECK_NOTHROW(throw("seed found twice."));
            }
            else
            {
                seed = true;
            }
        }
        else if ((*it)==("cane"))
        {
            if (cane == true)
            {
                CHECK_NOTHROW(throw("cane found twice."));
            }
            else
            {
                cane = true;
            }
        }
        else
        {
            CHECK_NOTHROW(throw("value unknown to OrgChart was found."));
        }
        it++;
    }
    
}

// test traversals
TEST_CASE("Reverse_order")
{
    /*
        ? ------------------*root---------------- ?
        ? ----|---------------|------------|----- ?
        ? *sub_root------*sub_root1----*sub_root2 ?
        ?  ---|---------------|------------------ ?
        ? *sub_sub_root-- *sub_sub_root1 -------- ?

    */
    OrgChart c;
    c.add_root("root");
    c.add_sub("root","sub_root");
    c.add_sub("sub_root","sub_sub_root");
    c.add_sub("root", "sub_root1");
    c.add_sub("root", "sub_root2");
    c.add_sub("sub_root1", "sub_sub_root1");
    string result;
    for(auto it = c.begin_reverse_order(); it != c.reverse_order(); it++)
    {
        result += (*it);
        result += " ";
    }
    result.pop_back();
    string compare = "sub_sub_root1 sub_sub_root sub_root2 sub_root1 sub_root root";
    CHECK(result == (compare));
}
// check that the pre order visit traversal is visiting the father before it is visiting it's children
TEST_CASE("Pre_order")
{
     /*
        ? ------------------*root---------------- ?
        ? ----|---------------|------------|----- ?
        ? *sub_root------*sub_root1----*sub_root2 ?
        ?  ---|---------------|------------------ ?
        ? *sub_sub_root-- *sub_sub_root1 -------- ?

    */
    OrgChart c;
    c.add_root("root");
    c.add_sub("root","sub_root");
    c.add_sub("sub_root","sub_sub_root");
    c.add_sub("root", "sub_root1");
    c.add_sub("root", "sub_root2");
    c.add_sub("sub_root1", "sub_sub_root1");
    string result;
    for(auto it = c.begin_preorder(); it != c.end_preorder(); it++)
    {
        result += *it;
        result.push_back(' ');
    }
    result.pop_back();
    // doing one compare case because there are too many to write
    string compare = "root sub_root sub_sub_root sub_root1 sub_sub_root1 sub_root2";
    CHECK(result == (compare));

}
TEST_CASE("Level_order")
{
     /*
        ? ------------------*root---------------- ?
        ? ----|---------------|------------|----- ?
        ? *sub_root------*sub_root1----*sub_root2 ?
        ?  ---|---------------|------------------ ?
        ? *sub_sub_root-- *sub_sub_root1 -------- ?

    */
    OrgChart c;
    c.add_root("root");
    c.add_sub("root","sub_root");
    c.add_sub("sub_root","sub_sub_root");
    c.add_sub("root", "sub_root1");
    c.add_sub("root", "sub_root2");
    c.add_sub("sub_root1", "sub_sub_root1");
    string result;
    for(auto it = c.begin_level_order(); it != c.end_level_order(); it++)
    {
        result += *it;
        result.push_back(' ');
    }
    result.pop_back();
    string compare = "root sub_root sub_root1 sub_root2 sub_sub_root sub_sub_root1";
    CHECK(result == (compare));
}

TEST_CASE("Operator <<")
{
    /*
        ? ------------------*root---------------- ?
        ? ----|---------------|------------|----- ?
        ? *sub_root------*sub_root1----*sub_root2 ?
        ?  ---|---------------|------------------ ?
        ? *sub_sub_root-- *sub_sub_root1 -------- ?

    */
    OrgChart c;
    c.add_root("root");
    c.add_sub("root","sub_root");
    c.add_sub("sub_root","sub_sub_root");
    c.add_sub("root", "sub_root1");
    c.add_sub("root", "sub_root2");
    c.add_sub("sub_root1", "sub_sub_root1");
    stringstream stream;
    stream << c;
    string result = stream.str();
    string compare = "root sub_root sub_root1 sub_root2 sub_sub_root sub_sub_root1";
    CHECK(result == (compare));
}
// not throwing here
TEST_CASE("Good_input")
{
    OrgChart c;
    CHECK_NOTHROW(c.add_root("root"));
    CHECK_NOTHROW(c.add_sub("root","sub_root"));
    CHECK_NOTHROW(c.add_sub("sub_root","sub_sub_root"));
    CHECK_NOTHROW(c.add_sub("root", "sub_root1"));
    CHECK_NOTHROW(c.add_sub("root", "sub_root2"));
    CHECK_NOTHROW(c.add_sub("sub_root1", "sub_sub_root1"));
    CHECK_NOTHROW(c.begin());
    CHECK_NOTHROW(c.end());
    CHECK_NOTHROW(c.begin_level_order());
    CHECK_NOTHROW(c.begin_preorder());
    CHECK_NOTHROW(c.begin_reverse_order());
    CHECK_NOTHROW(c.end_level_order());
    CHECK_NOTHROW(c.end_preorder());
    CHECK_NOTHROW(c.reverse_order());
}

TEST_CASE("Bad_input")
{
    OrgChart c1;
    // adding a sub without any root
    CHECK_THROWS(c1.add_sub("ROOT", "SUBROOT"));

}


