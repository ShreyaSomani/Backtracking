#include <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> > result;
// Program to solve N Quuens problem
void solveBoard(vector<vector<char> >& board, int row,
                int rowmask, int ldmask, int rdmask,
                int& ways)
{
 
    int n = board.size();
 
    // All_rows_filled is a bit mask having all N bits set
    int all_rows_filled = (1 << n) - 1;
 
    // If rowmask will have all bits set, means queen has
    // been placed successfully in all rows and board is
    // diplayed
    if (rowmask == all_rows_filled) {
 
        vector<int> v;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] == 'Q')
                    v.push_back(j + 1);
            }
        }
        result.push_back(v);
        return;
    }
 
    // We extract a bit mask(safe) by rowmask,
    // ldmask and rdmask. all set bits of 'safe'
    // indicates the safe column index for queen
    // placement of this iteration for row index(row).
    int safe
        = all_rows_filled & (~(rowmask | ldmask | rdmask));
    while (safe) {
 
        // Extracts the right-most set bit
        // (safe column index) where queen
        // can be placed for this row
        int p = safe & (-safe);
        int col = (int)log2(p);
        board[row][col] = 'Q';
 
        // This is very important:
        // we need to update rowmask, ldmask and rdmask
        // for next row as safe index for queen placement
        // will be decided by these three bit masks.
 
        // We have all three rowmask, ldmask and
        // rdmask as 0 in beginning. Suppose, we are placing
        // queen at 1st column index at 0th row. rowmask,
        // ldmask and rdmask will change for next row as
        // below:
 
        // rowmask's 1st bit will be set by OR operation
        // rowmask = 00000000000000000000000000000010
 
        // ldmask will change by setting 1st
        // bit by OR operation  and left shifting
        // by 1 as it has to block the next column
        // of next row because that will fall on left
        // diagonal. ldmask =
        // 00000000000000000000000000000100
 
        // rdmask will change by setting 1st bit
        // by OR operation and right shifting by 1
        // as it has to block the previous column
        // of next row because that will fall on right
        // diagonal. rdmask =
        // 00000000000000000000000000000001
 
        // these bit masks will keep updated in each
        // iteration for next row
        solveBoard(board, row + 1, rowmask | p,
                   (ldmask | p) << 1, (rdmask | p) >> 1,
                   ways);
 
        // Reset right-most set bit to 0 so,
        // next iteration will continue by placing the queen
        // at another safe column index of this row
        safe = safe & (safe - 1);
 
        // Backtracking, replace 'Q' by ' '
        board[row][col] = ' ';
    }
    return;
}
 
// Driver Code
int main()
{
    // Board size
    int n = 6;
    int ways = 0;
 
    vector<vector<char> > board;
    for (int i = 0; i < n; i++) {
        vector<char> tmp;
        for (int j = 0; j < n; j++) {
            tmp.push_back(' ');
        }
        board.push_back(tmp);
    }
 
    int rowmask = 0, ldmask = 0, rdmask = 0;
    int row = 0;
 
    // Function Call
    result.clear();
    solveBoard(board, row, rowmask, ldmask, rdmask, ways);
    sort(result.begin(),result.end());
	int count = 0;
    for (auto ar : result) {
        cout << "[";
        for (auto it : ar)
            cout << it << " ";
        cout << "]";
		++count;
	cout << endl;
    }
	cout << count;
    return 0;
}