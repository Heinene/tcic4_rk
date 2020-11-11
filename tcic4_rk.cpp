#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

const double mi = -2.0;
const double ma = 2.0;
const double mut = 0.3;


double f(const double x, const double y)
{
    return cos(x) * cos(y);
}

double random(const double min, const double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

struct Chrome
{
    double x, y;
    double Fit;
    Chrome() : x(0), y(0), Fit(0) {}
    Chrome(double x, double y) : x(x), y(y), Fit(f(x, y)) {}
};

void print(const vector<Chrome>& chrome, unsigned int no)
{
    double FitRedn = 0.0;
    for (const auto& ch : chrome)
    {
        FitRedn += ch.Fit;
    }
    FitRedn = FitRedn / 4;
    cout << "No pokol: " << setw(10) << left << no
        << "Fitred: " << setw(20) << left << FitRedn
        << "Fitma: " << setw(20) << left << chrome[0].Fit << endl;
    for (const auto& ch : chrome)
    {
        cout << "x: " << setw(20) << left << ch.x
            << "y: " << setw(20) << left << ch.y
            << "Fit: " << setw(20) << left << ch.Fit << endl;
    }
    cout << endl;
}

bool ravnchrome(const Chrome& one, const Chrome& to)
{
    return one.Fit > to.Fit;
};

void GEn(const int N) {
    vector<Chrome> gener;
    for (unsigned int i = 0; i < 4; i++) {
        gener.emplace_back(random(mi, ma), random(mi, ma));
    }
    sort(gener.begin(), gener.end(), ravnchrome);
    print(gener, 0);
    for (unsigned int i = 1; i <= N; i++)
    {
        for (unsigned int j = 0; j < gener.size(); j++)
        {
            auto ver = random(0, 1);
            if (ver < mut)
            {
                auto x = fmod(gener[j].x * random(-5, 5), 2);
                auto y = fmod(gener[j].y * random(-5, 5), 2);
                gener[j] = Chrome(x, y);
            }
        }
        vector<Chrome> pair;
        for (unsigned int i = 0; i < gener.size(); i++)
        {
            for (unsigned int j = 0; j < gener.size(); j++)
            {
                pair.emplace_back(gener[i].x, gener[j].y);
            }
        }
        sort(pair.begin(), pair.end(), ravnchrome);
        vector<Chrome> negen;
        for (unsigned int i = 0; i < gener.size(); i++)
        {
            negen.emplace_back(pair[i]);
        }
        gener = negen;
        print(gener, i);
    }
}

int main()
{
    cout << "Var 6" << endl;
    cout << "Func cos(x) * cos(y)" << endl;
    cout << "Mutation 30%, point 4 " << endl;
    vector<int> num = { 11 };
    for (const auto& chpok : num) {
        cout << "Pokol " << chpok << endl << endl;
        GEn(chpok);
    }
}