#include "OrgChart.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace ariel;
ariel::OrgChart::OrgChart()
{}
ariel::OrgChart & ariel::OrgChart::add_root(string str)
{return *this;}
ariel::OrgChart & ariel::OrgChart::add_sub(string father, string child)
{return *this;}
ariel::OrgChart::iterator ariel::OrgChart::begin()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::end()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::begin_level_order()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::begin_preorder()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::begin_reverse_order()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::end_level_order()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::end_preorder()
{return iterator(this);}
ariel::OrgChart::iterator ariel::OrgChart::reverse_order()
{return iterator(this);}
ariel::OrgChart::iterator::iterator(ariel::OrgChart * current)
{}
bool ariel::OrgChart::iterator::operator!=(ariel::OrgChart::iterator iter)
{return false;}
string ariel::OrgChart::iterator::operator*()
{return "not implemented yet";}
ariel::OrgChart::iterator & ariel::OrgChart::iterator::operator++()
{return *this;}
ariel::OrgChart::iterator & ariel::OrgChart::iterator::operator++(int)
{return *this;}
string * ariel::OrgChart::iterator::operator->()
{return &(this->current)->name;}
std::ostream & ariel::operator<<(std::ostream & stream, OrgChart const & chart)
{return stream;}











