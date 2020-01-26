#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;

struct segment
{
    int level;
    int amount;
};

ostream &operator<<(ostream &os, const segment &seg)
{
    return os << "{ level = " << seg.level << ", amount =  " << seg.amount << " }";
}

int step(int level)
{
    if (level == 0)
        return 1;
    return pow(10, pow(2, level - 1));
}

int next_segment_start(int L, int R, int level)
{
    int cur_step = step(level);
    int next_step = step(level + 1);
    int start = (L / next_step + 1) * next_step;
    if (start > R)
    {
        start = R - R % cur_step;
    }

    return start;
}

segment find_segment(int L, int R)
{
    int level, next_level = 0, level_step = 1;
    bool dividable = true;
    while (dividable) {
        level = next_level++;
        level_step = step(next_level);
        dividable = (L % level_step == 1 && (R - L + 1) >= level_step);
    }

    level_step = step(level);
    int next_start = next_segment_start(L, R, level);
    int amount = (next_start - L + 1) / level_step;
    return {level, amount};
}

vector<segment> square_ten(int L, int R)
{
    vector<segment> segs;
    do
    {
        segment seg = find_segment(L, R);
        L += seg.amount * step(seg.level);

        segs.push_back(seg);
    } while (L < R);

    return segs;
}

void segments_output(vector<segment> segs)
{
    cout << segs.size() << '\n';
    for (auto seg : segs)
    {
        cout << seg.level << ' ' << seg.amount << '\n';
    }
}

int main()
{
    int L, R;
    cin >> L >> R;

    segments_output(square_ten(L, R));
    return 0;
}
