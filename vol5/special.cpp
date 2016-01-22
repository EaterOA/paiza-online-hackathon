#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define LOOPGRID(e) \
    for (int i = 0; i < 4; i++) {   \
    for (int j = 0; j < 4; j++) {   \
        e   \
    }       \
    }

struct Loc {
    int r, c;
    bool operator==(const Loc &other) const {
        return r == other.r && c == other.c;
    }
};

int board[4][4] = {0};
Loc blank;

void do_move(Loc loc)
{
    cout << board[loc.r][loc.c] << "\n";
    swap(board[loc.r][loc.c], board[blank.r][blank.c]);
    blank = loc;
}

bool dfsid(Loc cur, Loc dest, vector<Loc> &moves, bool locks[4][4], int level)
{
    if (cur == dest) {
        return true;
    } else if (level == 0) {
        return false;
    }

    const int dR[] = {1,0,-1,0};
    const int dC[] = {0,1,0,-1};
    for (int i = 0; i < 4; i++) {
        Loc next_loc = {cur.r + dR[i], cur.c + dC[i]};
        if (next_loc.r < 4 && next_loc.r >= 0 &&
                next_loc.c < 4 && next_loc.c >= 0 &&
                !locks[next_loc.r][next_loc.c]) {
            locks[next_loc.r][next_loc.c] = true;
            moves.push_back(next_loc);
            bool res = dfsid(next_loc, dest, moves, locks, level-1);
            locks[next_loc.r][next_loc.c] = false;
            if (res) {
                return true;
            } else {
                moves.pop_back();
            }
        }
    }

    return false;
}

vector<Loc> find_path(Loc cur, Loc dest, const bool locks[4][4])
{
    vector<Loc> moves;
    for (int d = 0; d < 16; d++) {
        bool new_locks[4][4];
        LOOPGRID(
            new_locks[i][j] = locks[i][j];
        );
        if (dfsid(cur, dest, moves, new_locks, d)) {
            return moves;
        }
    }
    cout << "WTFFFFF\n";
    exit(0);
}

void move_to(Loc dest, const bool locks[4][4])
{
    vector<Loc> moves = find_path(blank, dest, locks);
    for (int i = 0; i < moves.size(); i++) {
        do_move(moves[i]);
    }
}

void arrange(int num, Loc dest, const char lock_config[16+1])
{
    Loc cur;
    bool locks[4][4];

    LOOPGRID(
        if (board[i][j] == num) {
            cur.r = i;
            cur.c = j;
        }
        locks[i][j] = lock_config[i*4 + j] == '1';
    );

    vector<Loc> path = find_path(cur, dest, locks);
    for (int i = 0; i < path.size(); i++) {
        locks[cur.r][cur.c] = true;
        move_to(path[i], locks);
        locks[cur.r][cur.c] = false;
        do_move(cur);
        cur = path[i];
    }
}

void print_board()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++ ){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    LOOPGRID(
        string s;
        cin >> s;
        if (s == "*") {
            board[i][j] = 0;
            blank.r = i;
            blank.c = j;
        } else {
            board[i][j] = stoi(s);
        }
    );

    arrange(1,  {0, 0}, "0000000000000000");
    arrange(2,  {0, 1}, "1000000000000000");
    if (!(board[0][2] == 3 && board[0][3] == 4)) {
        arrange(4,  {0, 2}, "1100000000000000");
        arrange(3,  {1, 2}, "1110000000000000");
        arrange(4,  {0, 3}, "1100001000000000");
        arrange(3,  {0, 2}, "1101000000000000");
    }
    arrange(5,  {1, 0}, "1111000000000000");
    arrange(6,  {1, 1}, "1111100000000000");
    if (!(board[1][2] == 7 && board[1][3] == 8)) {
        arrange(8,  {1, 2}, "1111110000000000");
        arrange(7,  {2, 2}, "1111111000000000");
        arrange(8,  {1, 3}, "1111110000100000");
        arrange(7,  {1, 2}, "1111110100000000");
    }
    if (!(board[2][0] == 9 && board[3][0] == 13)) {
        if (!(board[2][0] == 13 && board[2][1] == 9)) {
            arrange(9,  {3, 2}, "1111111100000000");
            arrange(13, {2, 0}, "1111111100000000");
            arrange(9,  {2, 1}, "1111111110000000");
        }
        arrange(13, {3, 0}, "1111111101000000");
        arrange(9,  {2, 0}, "1111111100001000");
    }
    if (!(board[2][1] == 10 && board[3][1] == 14)) {
        if (!(board[2][1] == 14 && board[2][2] == 10)) {
            arrange(10, {3, 3}, "1111111110001000");
            arrange(14, {2, 1}, "1111111110001000");
            arrange(10, {2, 2}, "1111111111001000");
        }
        arrange(14, {3, 1}, "1111111110101000");
        arrange(10, {2, 1}, "1111111110001100");
    }
    arrange(11, {2, 2}, "1111111111001100");
    arrange(12, {2, 3}, "1111111111101100");
    arrange(15, {3, 2}, "1111111111111100");
}
