#include <iostream>
#include <vector>

#include "polynomial.h"

using namespace std;

int main(int argc, char *argv[])
{
    polynomial<double> a;
    vector<double> expansion_points;

    a.set(0, 1.f);
    a.set(2, 1.f);
    a.set(5, 0.5f);

    cout << a << endl;

    expansion_points.push_back(2.f);
    expansion_points.push_back(1.f);
    expansion_points.push_back(-1.f);
    expansion_points.push_back(25.f);
    expansion_points.push_back(-25.f);
    expansion_points.push_back(5.f);

    polynomial<double> d = a;
    polynomial<double> result;
    for(vector<double>::size_type i = 0;i < expansion_points.size();i++)
    {
        polynomial<double> e = d.eval_at(expansion_points[i]);

        polynomial<double> tmp;
        tmp.set(0, 1.f);
        for(vector<double>::size_type j = 0;j < i;j++)
        {
            tmp = tmp.indefinite_integral() - tmp.indefinite_integral().eval_at(expansion_points[i-j - 1]);
        }

        result = result + e * tmp;

        d = d.differentiate();
    }

    cout << result << endl;
    return 0;
}

