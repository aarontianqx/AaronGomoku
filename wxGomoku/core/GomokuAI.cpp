/***************************************************************
 * Name:      GomokuAI.cpp
 * Purpose:   Code for AI Algorithm and Bot Thread
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-20
 **************************************************************/


#include "GomokuAI.h"

#include <algorithm>
#include <random>
#include <string>

static const int PATTERN_WIN = 0;
static const int PATTERN_L4 = 1;
static const int PATTERN_S4 = 2;
static const int PATTERN_CL3 = 3;
static const int PATTERN_JL3 = 4;
static const int PATTERN_S3 = 5;
static const int PATTERN_L2 = 6;
static const int PATTERN_S2A = 7;
static const int PATTERN_S2B = 8;
static const int PATTERN_S2C = 9;
static const int PATTERN_ONE = 10;
static const int PATTERN_NONE = 11;

static const int PATTERN_D44 = 12;
static const int PATTERN_D43 = 13;
static const int PATTERN_D33 = 14;
static const int PATTERN_ML2 = 15;


const char *PatternName[16]{
    "WIN", "L4", "S4", "CL3",
    "JL3", "S3", "L2", "S2A",
    "S2B", "S2C" "ONE", "NONE",
    "D44", "D43", "D33", "ML2"
};

const int PatternScore[16]{
    15000, 6000, 500, 400,
    300, 120, 150, 60,
    40, 20, 5, 0,
    6000, 4000, 2000, 60
};

const uint64_t PatternMap[411]{
0x9524857aaa958a9a, 0x24756aaaaaaaaa99, 0x9995552014238885, 0xaaaaaaaaaa999999,
0xaaaaaaaaaaaaaaaa, 0x222444777555666a, 0x2333888888888555, 0x5522200011144422,
0x9999999995555555, 0x9999999999999999, 0x25b59bbbb59b9a99, 0xb59bbbbbbbbbbbbb,
0xbbbbb02b25bbbb25, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x4555777777777bbb,
0x4488888888855552, 0x2222012224445244, 0x9999999555555555, 0x9999999999999999,
0x2223333333339999, 0x1444444444222222, 0x0000000011111111, 0x5555552222222220,
0x5555555555555555, 0x59bbbb59b9a55555, 0xbbbbbbbbbbbbb25b, 0xbb02b25bbbb25b59,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x8bbb958a9abbbbbb, 0xbbbbbbbbbbb52495,
0x201524bbb524958b, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0xbbb555999bbbbbbb,
0xbbbbbbbbbb222555, 0x00222bbb222555bb, 0xbbbbbbbbbbbbbbb0, 0xbbbbbbbbbbbbbbbb,
0xbbb59b9abbbbbbbb, 0xbbbbbbbbbb25b59b, 0x2b25bbbb25b59bbb, 0xbbbbbbbbbbbbbbb0,
0xbbbbbbbbbbbbbbbb, 0x8958888bbbbbbbbb, 0x8888899952485788, 0x4235555245558888,
0x9555555555555201, 0x9999999999999999, 0x4444449999999999, 0x4444555222444444,
0x1122222222244444, 0x2222222222220001, 0x5555555555555555, 0x59b9a55555555555,
0xbbbbbbb25b59bbbb, 0x5bbbb25b59bbbbbb, 0xbbbbbbbbbbbb02b2, 0xbbbbbbbbbbbbbbbb,
0x4444bbbbbbbbbbbb, 0x4455552455544444, 0x2225242224444444, 0x2222222222201222,
0x5555555555555522, 0x1115555555555555, 0x1111111111111111, 0x0000000011111111,
0x0000000000000000, 0x2222222222222000, 0x9a22222222222222, 0xbbbb25b59bbbb59b,
0xbb25b59bbbbbbbbb, 0xbbbbbbbbb02b25bb, 0xbbbbbbbbbbbbbbbb, 0xabbbbbbbbbbbbbbb,
0xbb524958bbb958a9, 0x524958bbbbbbbbbb, 0xbbbbbbb201524bbb, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0xb222555bbb555999, 0x22555bbbbbbbbbbb, 0xbbbbbb000222bbb2,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0xb25b59bbbb59b9ab, 0x5b59bbbbbbbbbbbb,
0xbbbbbb02b25bbbb2, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x24857aaa958a9abb,
0x857bbbbbbbbb9995, 0xb555201423999524, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb,
0x2444999555888bbb, 0x44bbbbbbbbb55522, 0x2220001115552224, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0xb59bbbb59b9abbbb, 0x9bbbbbbbbbbbbb25, 0xbbb02b25bbbb25b5,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x55999999999bbbbb, 0xbbbbbbbbb5555245,
0x2201222555524555, 0xbbbbbbbbbbbbbb22, 0xbbbbbbbbbbbbbbbb, 0x2555555555bbbbbb,
0xbbbbbbbb22222222, 0x000000222222222b, 0xbbbbbbbbbbbbb000, 0xbbbbbbbbbbbbbbbb,
0xbbbb59b9abbbbbbb, 0xbbbbbbbbbbb25b59, 0x02b25bbbb25b59bb, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0xbb958a9abbbbbbbb, 0xbbbbbbbbb524958b, 0x1524bbb524958bbb,
0xbbbbbbbbbbbbbb20, 0xbbbbbbbbbbbbbbbb, 0xb555999bbbbbbbbb, 0xbbbbbbbb222555bb,
0x222bbb222555bbbb, 0xbbbbbbbbbbbbb000, 0xbbbbbbbbbbbbbbbb, 0xb59b9abbbbbbbbbb,
0xbbbbbbbb25b59bbb, 0x25bbbb25b59bbbbb, 0xbbbbbbbbbbbbb02b, 0xbbbbbbbbbbbbbbbb,
0x58999bbbbbbbbbbb, 0x9999995248579999, 0x3888524756999999, 0x9999999955520142,
0x9999999999999999, 0x5555999999999999, 0x5555522244455555, 0x4442223335555555,
0x5555555222000111, 0x5555555555555555, 0xb9a5555555555555, 0xbbbbb25b59bbbb59,
0xbbb25b59bbbbbbbb, 0xbbbbbbbbbb02b25b, 0xbbbbbbbbbbbbbbbb, 0x55bbbbbbbbbbbbbb,
0x5555245555555555, 0x4524444555555555, 0x5555522220122244, 0x5555555555555555,
0x2555555555555555, 0x2222222222222222, 0x1111112222222222, 0x2222000000000111,
0x2222222222222222, 0x2222222222222222, 0xbb25b59bbbb59b9a, 0x25b59bbbbbbbbbbb,
0xbbbbbbb02b25bbbb, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x524958bbb958a9ab,
0x4958bbbbbbbbbbbb, 0xbbbbb201524bbb52, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb,
0x22555bbb555999bb, 0x555bbbbbbbbbbbb2, 0xbbbb000222bbb222, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0x5b59bbbb59b9abbb, 0x59bbbbbbbbbbbbb2, 0xbbbb02b25bbbb25b,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x857555958555bbbb, 0x5555555555999524,
0x5520142355552455, 0x5555555555555555, 0x5555555555555555, 0x4422222222255555,
0x2222222225552224, 0x2000111222222222, 0x2222222222222222, 0x2222222222222222,
0x9bbbb59b9a222222, 0xbbbbbbbbbbbb25b5, 0xb02b25bbbb25b59b, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0x222222222bbbbbbb, 0x2222222555524555, 0x0122222252422222,
0x2222222222222222, 0x2222222222222222, 0x0000000022222222, 0x0000000000000000,
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xbb59b9a000000000,
0xbbbbbbbbb25b59bb, 0xb25bbbb25b59bbbb, 0xbbbbbbbbbbbbbb02, 0xbbbbbbbbbbbbbbbb,
0x958a9abbbbbbbbbb, 0xbbbbbbb524958bbb, 0x24bbb524958bbbbb, 0xbbbbbbbbbbbb2015,
0xbbbbbbbbbbbbbbbb, 0x55999bbbbbbbbbbb, 0xbbbbbb222555bbb5, 0x2bbb222555bbbbbb,
0xbbbbbbbbbbb00022, 0xbbbbbbbbbbbbbbbb, 0x9b9abbbbbbbbbbbb, 0xbbbbbb25b59bbbb5,
0xbbbb25b59bbbbbbb, 0xbbbbbbbbbbb02b25, 0xbbbbbbbbbbbbbbbb, 0xa9abbbbbbbbbbbbb,
0xb999524857aaa958, 0x99524857bbbbbbbb, 0xbbbbbb5552014239, 0xbbbbbbbbbbbbbbbb,
0x88bbbbbbbbbbbbbb, 0x5552224449995558, 0x5222444bbbbbbbbb, 0xbbbbb22200011155,
0xbbbbbbbbbbbbbbbb, 0xabbbbbbbbbbbbbbb, 0xbbb25b59bbbb59b9, 0xb25b59bbbbbbbbbb,
0xbbbbbbbb02b25bbb, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x5524555999999999,
0x24555bbbbbbbbb55, 0xbbb2222012225555, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb,
0x222222555555555b, 0x2222bbbbbbbbb222, 0xbb00000000022222, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0x25b59bbbb59b9abb, 0xb59bbbbbbbbbbbbb, 0xbbbbb02b25bbbb25,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x4958bbb958a9abbb, 0x58bbbbbbbbbbbb52,
0xbbb201524bbb5249, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x555bbb555999bbbb,
0x5bbbbbbbbbbbb222, 0xbb000222bbb22255, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb,
0x59bbbb59b9abbbbb, 0xbbbbbbbbbbbbb25b, 0xbb02b25bbbb25b59, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0x7aaa958a9abbbbbb, 0xaaaaaaaa99952485, 0x201423888524756a,
0xbbbb999999999555, 0xbbbbbbbbbbbbbbbb, 0x888555777bbbbbbb, 0x9999999555222444,
0x0011144422233399, 0xbbb5555555552220, 0xbbbbbbbbbbbbbbbb, 0xbbb59b9abbbbbbbb,
0xbbbbbbbbbb25b59b, 0x2b25bbbb25b59bbb, 0xbbbbbbbbbbbbbbb0, 0xbbbbbbbbbbbbbbbb,
0x8888888bbbbbbbbb, 0x9999955552455588, 0x2224445244449999, 0xb555555555222201,
0xbbbbbbbbbbbbbbbb, 0x444444bbbbbbbbbb, 0x5555222222222444, 0x0011111111155555,
0x2222222220000000, 0xbbbbbbbbbbbbbbbb, 0x59b9abbbbbbbbbbb, 0xbbbbbbb25b59bbbb,
0x5bbbb25b59bbbbbb, 0xbbbbbbbbbbbb02b2, 0xbbbbbbbbbbbbbbbb, 0x8a9abbbbbbbbbbbb,
0xbbbbb524958bbb95, 0xbbb524958bbbbbbb, 0xbbbbbbbbbb201524, 0xbbbbbbbbbbbbbbbb,
0x999bbbbbbbbbbbbb, 0xbbbb222555bbb555, 0xbb222555bbbbbbbb, 0xbbbbbbbbb000222b,
0xbbbbbbbbbbbbbbbb, 0x9abbbbbbbbbbbbbb, 0xbbbb25b59bbbb59b, 0xbb25b59bbbbbbbbb,
0xbbbbbbbbb02b25bb, 0xbbbbbbbbbbbbbbbb, 0x9bbbbbbbbbbbbbbb, 0x9952485799995899,
0x5245559999999999, 0x5555555201423555, 0xbbbbbbbbbbb55555, 0xbbbbbbbbbbbbbbbb,
0x5222444555555555, 0x2222255555555555, 0x2222220001112222, 0xbbbbbbbbbb222222,
0xbbbbbbbbbbbbbbbb, 0xb25b59bbbb59b9ab, 0x5b59bbbbbbbbbbbb, 0xbbbbbb02b25bbbb2,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x24555555555555bb, 0x2225555555555555,
0x2222201222222524, 0xbbbbbbbb22222222, 0xbbbbbbbbbbbbbbbb, 0x2222222222222bbb,
0x0022222222222222, 0x0000000000000000, 0xbbbbbbb000000000, 0xbbbbbbbbbbbbbbbb,
0xb59bbbb59b9abbbb, 0x9bbbbbbbbbbbbb25, 0xbbb02b25bbbb25b5, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0x58bbb958a9abbbbb, 0xbbbbbbbbbbbb5249, 0xb201524bbb524958,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x5bbb555999bbbbbb, 0xbbbbbbbbbbb22255,
0x000222bbb222555b, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0xbbbb59b9abbbbbbb,
0xbbbbbbbbbbb25b59, 0x02b25bbbb25b59bb, 0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb,
0xaa958a9abbbbbbbb, 0xbbbbbb999524857a, 0x1423999524857bbb, 0xbbbbbbbbbbb55520,
0xbbbbbbbbbbbbbbbb, 0x9555888bbbbbbbbb, 0xbbbbb55522244499, 0x111555222444bbbb,
0xbbbbbbbbbb222000, 0xbbbbbbbbbbbbbbbb, 0xb59b9abbbbbbbbbb, 0xbbbbbbbb25b59bbb,
0x25bbbb25b59bbbbb, 0xbbbbbbbbbbbbb02b, 0xbbbbbbbbbbbbbbbb, 0x99999bbbbbbbbbbb,
0xbbb5555245559999, 0x2555524555bbbbbb, 0xbbbbbbbb22220122, 0xbbbbbbbbbbbbbbbb,
0x5555bbbbbbbbbbbb, 0xbb22222222255555, 0x222222222bbbbbbb, 0xbbbbbbb000000000,
0xbbbbbbbbbbbbbbbb, 0xb9abbbbbbbbbbbbb, 0xbbbbb25b59bbbb59, 0xbbb25b59bbbbbbbb,
0xbbbbbbbbbb02b25b, 0xbbbbbbbbbbbbbbbb, 0x9abbbbbbbbbbbbbb, 0xbbb524958bbb958a,
0xb524958bbbbbbbbb, 0xbbbbbbbb201524bb, 0xbbbbbbbbbbbbbbbb, 0x9bbbbbbbbbbbbbbb,
0xbb222555bbb55599, 0x222555bbbbbbbbbb, 0xbbbbbbb000222bbb, 0xbbbbbbbbbbbbbbbb,
0xbbbbbbbbbbbbbbbb, 0xbb25b59bbbb59b9a, 0x25b59bbbbbbbbbbb, 0xbbbbbbb02b25bbbb,
0xbbbbbbbbbbbbbbbb, 0xbbbbbbbbbbbbbbbb, 0x000000000000000b
};

std::random_device rd;

GomokuAI::GomokuAI(GomokuBoard *board, int difficulty)
    : gomoku_board(board)
{
    max_depth = std::min(difficulty * 2, 224 - gomoku_board->pieceCount());
    max_depth = std::min(max_depth, gomoku_board->pieceCount() + 2);
    if (max_depth % 2 == 1)
        max_depth--;
}

// evaluate a point with a specific color on a certain direction
int getLinePattern(GomokuBoard *board, PiecePosition pos, uint8_t direction, PieceColor color)
{
    assert(pos.isLegal());
    assert(board->at(pos) != color.opponent());
    // passed the piece '1' at index 4
    std::string pattern("22222222");
    int l = 3, r = 4;
    for(auto tmp=pos+direction; r < 8; tmp+=direction, r++){
        PieceColor tc = board->at(tmp);
        if (tc == color)
            pattern[r] = '1';
        else if (tc.isBlank())
            pattern[r] = '0';
        else  // illegal position or opponent color
            break;
    }
    for (auto tmp=pos-direction; l >= 0; tmp-=direction, l--){
        PieceColor tc = board->at(tmp);
        if (tc == color)
            pattern[l] = '1';
        else if (tc.isBlank())
            pattern[l] = '0';
        else  // illegal position or opponent color
            break;
    }

    // improve performance by looking up table
    int ternary = pattern[7] - '0';
    for (int i=6; i>=0; i--)
        ternary = ternary * 3 + pattern[i] - '0';
    uint64_t res = (PatternMap[ternary / 16] >> ((ternary%16) * 4));
    res &= 0xF;
    return int(res);

}

// evaluate a blank point with a specific color
int evalSpec(GomokuBoard *board, PiecePosition pos, PieceColor color)
{
    int score = 0;
    int pattern[4]{
        getLinePattern(board, pos, PiecePosition::Right, color),
        getLinePattern(board, pos, PiecePosition::Down, color),
        getLinePattern(board, pos, PiecePosition::RightUp, color),
        getLinePattern(board, pos, PiecePosition::RightDown, color)
    };
    std::sort(pattern, pattern+4);
    if (pattern[1] <= PATTERN_S4)
        pattern[1] = PATTERN_D44;
    else if (pattern[1] <= PATTERN_JL3){
        if (pattern[0] <= PATTERN_S4)
            pattern[1] = PATTERN_D43;
        else
            pattern[1] = PATTERN_D33;
    }
    else {
        int l2c;
        for (l2c=0; l2c<4; l2c++)
            if (pattern[l2c] > PATTERN_L2)
                break;
        if (l2c > 2)
            score = (l2c - 2) * PatternScore[PATTERN_ML2];
    }
    for(int i=0; i<4; i++)
        score += PatternScore[pattern[i]];
    return score;
}
// evaluate priority at a certain point
int evaluate(GomokuBoard *board, PiecePosition pos)
{
    int a_score = evalSpec(board, pos, board->nextColor());
    int d_score = evalSpec(board, pos, board->nextColor().opponent());
    return a_score + d_score * 2 / 3;
}

// evaluate the whole situation (for leaf node)
int GomokuAI::evaluateSituation(GomokuBoard *board, int alpha, int beta)
{
    PieceScore d_max1, d_max2;
    PieceColor color = board->nextColor(), opponent_color = color.opponent();
    int best = INT_MIN;
    // evaluate each point for the opponent
    for (PiecePosition pos: blank_points){
        if(!board->at(pos).isBlank()) continue;
        int score = evalSpec(board, pos, opponent_color) / 2;
        if (score > d_max2.score){
            d_max2.pos = pos;
            d_max2.score = score;
            if (d_max1.score < d_max2.score)
                std::swap(d_max1, d_max2);
        }
    }
    // evaluate situation
    for (PiecePosition pos: blank_points){
        if(!board->at(pos).isBlank()) continue;
        int score = evalSpec(board, pos, color);
        // PointSituation = PointScore - max(OpponentPointScore except this point)
        int situation = score - (pos == d_max1.pos?d_max2.score:d_max1.score);
        if (situation > best) best = situation;
        if (best > beta) return best;
    }
    return best;
}

// generate posible points in a limit number
// blank_points have been calculated previously
std::vector<PieceScore>
GomokuAI::generatePoints(GomokuBoard *board, uint32_t limit)
{
    std::vector<PieceScore> v;
    for(PiecePosition pos: blank_points){
        if (board->at(pos).isBlank()){
            int value = evaluate(board, pos);
            value += 7 - std::max(abs(7 - pos.getX()), abs(7 - pos.getY()));
            if (value >= PatternScore[PATTERN_WIN]){
                v.clear();
                v.push_back(PieceScore(pos, value));
                return v;
            }
            v.push_back(PieceScore(pos, value));
        }
    }
    std::sort(v.begin(), v.end(), std::greater<PieceScore>());
    if (v.size() > limit)
        v.resize(limit);
    return std::move(v);
}

// Max-Min Search with Alpha-Beta Pruning
int GomokuAI::dfSearchScore(GomokuBoard *board, int ply, int alpha, int beta)
{
    node++;
    if ((ply & 1) == 0 && ply >= max_depth)
        return evaluateSituation(board, alpha, beta);

    std::vector<PieceScore> points = generatePoints(board, std::max(20 - 4 * ply, 6));
    if (points[0].score >= PatternScore[PATTERN_WIN])
        return (ply & 1) ? -points[0].score : points[0].score;
    int best = (ply & 1)?INT_MAX:INT_MIN;
    for(auto& point: points){
        board->put(point.pos);
        int score = dfSearchScore(board, ply+1, alpha, beta);
        board->withDraw(point.pos);
        if (ply % 2 == 0){
            if (score > best) best = score;
            if (score > alpha) alpha = score;
            if (alpha > beta) break;
        }
        else{
            if (score < best) best = score;
            if (score < beta) beta = score;
            if (alpha > beta) break;
        }
    }
    return best;
}

// The entrance of search method
PiecePosition GomokuAI::operator()(uint32_t& _node)
{
    assert(gomoku_board->pieceCount() < 225);
    blank_points = gomoku_board->blankPoints();
    std::vector<PieceScore> points = generatePoints(gomoku_board, 20);

    node = 1;
    int best = INT_MIN;
    if (max_depth > 1){
        GomokuBoard board(*gomoku_board);
        for (auto& point: points){
            board.put(point.pos);
            point.score = dfSearchScore(&board, 1, -100000000, 100000000);
            board.withDraw(point.pos);

            // avoid putting randomly when calculate too lose
            if (point.score > best)
                best = point.score;
        }
        if (best < 0){
            _node = node;
            return points[0].pos;
        }
    }
    std::sort(points.begin(), points.end(), std::greater<PieceScore>());
    size_t count;
    int base_score = int(0.9 * points[0].score);
    for (count=1; count<points.size() && points[count].score >= base_score; count++);
    _node = node;
    return points[rd() % count].pos;
}

/*
// to make pattern-map
int judge_pattern(std::string pattern)
{
    int l = 3, r = 5;
    while (l >= 0 && pattern[l] != '2') l--;
    while (r < pattern.size() && pattern[r] != '2') r++;
    l++;
    if (r - l < 5)  // less than 5, no chance
        return PATTERN_NONE;
    pattern = pattern.substr(l, r-l);
    l = r = 4 - l;
    int count = 1, tl = l-1, tr = r+1;
    while (tr - l < 5 || r - tl < 5){
        if (tl >= 0 && r - tl < 5 && pattern[tl] == '1'){
            count++;
            l = tl--;
        }
        else if (tr < pattern.size() && tr - l < 5 && pattern[tr] == '1'){
            count++;
            r = tr++;
        }
        else
            tl--, tr++;
    }
    assert(r - l < 5);
    if (count == 5)
        return PATTERN_WIN;
    tl = std::max(0, r-4), tr = std::min(int(pattern.size()), l+5);
    l -= tl, r -= tl;
    pattern = pattern.substr(tl, tr - tl);
    if (count == 4){
        if (r - l == 3 && l > 0 && r < pattern.size()-1)
            // 011110
            return PATTERN_L4;
        else
            return PATTERN_S4;
    }
    if (count == 3){
        switch (pattern.size())
        {
            case 7:
                return PATTERN_CL3;
            case 6:
                return PATTERN_JL3;
            default: // 5
                return PATTERN_S3;
        }
    }
    if (count == 2){
        switch (pattern.size())
        {
            case 8:
                return PATTERN_L2;
            case 7:
                return PATTERN_S2A;
            case 6:
                return PATTERN_S2B;
            default: // 5
                return PATTERN_S2C;
        }
    }
    return PATTERN_ONE;
}

void make_pattern()
{
    for (int i=0; i<6561; i++){
        std::string pattern("000010000");
        int low = i % 81, high = i / 81;
        int index = 0;
        while (low != 0){
            pattern[index++] = '0' + low % 3;
            low /= 3;
        }
        index = 5;
        while (high != 0){
            pattern[index++] = '0' + high % 3;
            high /= 3;
        }
        uint64_t mark = judge_pattern(pattern);
        PatternMap[i/16] |= (mark << ((i%16) * 4));
    }
    for (int i=0; i<411; i++){
        if (i % 4 == 0) std::cout<< std::endl;
        std::cout<< "0x" << hex << setw(16) << setfill('0') << PatternMap[i] << ", ";
    }
}
*/

/*
// getLinePattern backup
int getLinePattern(GomokuBoard *board, PiecePosition pos, Direction dir, PieceColor color)
{
    std::string pattern("222212222");
    int l = 3, r = 5;
    for(auto tmp=pos.adjacent(dir); tmp.isLegal() && r < 9; tmp.move(dir), r++){
        PieceColor tc = board->at(tmp);
        if (tc == color)
            pattern[r] = '1';
        else if (tc.isBlank())
            pattern[r] = '0';
        else
            break;
    }
    Direction opdir = opponentDir(dir);
    for (auto tmp=pos.adjacent(opdir); tmp.isLegal() && l >= 0; tmp.move(opdir), l--){
        PieceColor tc = board->at(tmp);
        if (tc == color)
            pattern[l] = '1';
        else if (tc.isBlank())
            pattern[l] = '0';
        else
            break;
    }
    l++;

    if (r - l < 5)  // less than 5, no chance
        return PATTERN_NONE;
    pattern = pattern.substr(l, r-l);
    l = r = 4 - l;
    int count = 1, tl = l-1, tr = r+1;
    while (tr - l < 5 || r - tl < 5){
        if (tl >= 0 && r - tl < 5 && pattern[tl] == '1'){
            count++;
            l = tl--;
        }
        else if (tr < pattern.size() && tr - l < 5 && pattern[tr] == '1'){
            count++;
            r = tr++;
        }
        else
            tl--, tr++;
    }
    assert(r - l < 5);
    if (count == 5)
        return PATTERN_WIN;
    tl = std::max(0, r-4), tr = std::min(int(pattern.size()), l+5);
    l -= tl, r -= tl;
    pattern = pattern.substr(tl, tr - tl);
    if (count == 4){
        if (r - l == 3 && l > 0 && r < pattern.size()-1)
            // 011110
            return PATTERN_L4;
        else
            return PATTERN_S4;
    }
    if (count == 3){
        switch (pattern.size())
        {
            case 7:
                return PATTERN_CL3;
            case 6:
                return PATTERN_JL3;
            default: // 5
                return PATTERN_S3;
        }
    }
    if (count == 2){
        switch (pattern.size())
        {
            case 8:
                return PATTERN_L2;
            case 7:
                return PATTERN_S2A;
            case 6:
                return PATTERN_S2B;
            default: // 5
                return PATTERN_S2C;
        }
    }
    return PATTERN_ONE;
}
*/
