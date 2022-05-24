#include "sources/OrgChart.hpp"

using namespace ariel;
using namespace std;


int main()
{
    OrgChart org;
    // OrgChart org_empty;
    // OrgChart org_double_names;
    /* create normal tree */
    // (org.add_sub("tal", "renana"));
    (org.add_root("dana"));
    (org.add_root("shir"));
    cout << (*org.begin()) << endl;
    (org.add_sub("shir", "tal"));
    OrgChart::iterator iter = org.begin();
    cout << iter.get_q().front() << endl;
    iter++;
    cout << iter.get_q().front() << endl;
    // (org.add_sub("adi", "sapir"));
    // (org.add_sub("shir", "sapir"));
    // (org.add_sub("sapir", "dan"));
    // (org.add_sub("dan", "ziv"));
    // (org.add_sub("tal", "avi"));
    // (org.add_sub("tal", "yossi"));
    // (org.add_sub("shir", "ido"));
    // (org.add_sub("ziv", "shaked"));
    // (org.add_sub("ziv", "ofer"));

    return 0;
}





