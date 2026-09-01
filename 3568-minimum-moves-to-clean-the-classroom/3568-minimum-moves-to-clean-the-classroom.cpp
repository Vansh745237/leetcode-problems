class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();

        vector<pair<int,int>> litter;
        int sx = 0, sy = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (classroom[i][j] == 'L')
                    litter.push_back({i, j});
                else if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        vector<vector<int>> id(n, vector<int>(m, -1));

        for (int i = 0; i < k; i++)
            id[litter[i].first][litter[i].second] = i;

        int total = 1 << k;

        vector<vector<vector<int>>> best(
            n, vector<vector<int>>(m, vector<int>(total, -1))
        );

        queue<array<int,4>> q;

        q.push({sx, sy, 0, energy});
        best[sx][sy][0] = energy;

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        int steps = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [x, y, mask, e] = q.front();
                q.pop();

                if (mask == total - 1)
                    return steps;

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                        continue;

                    if (classroom[nx][ny] == 'X')
                        continue;

                    if (e == 0)
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (id[nx][ny] != -1)
                        nmask |= (1 << id[nx][ny]);

                    if (classroom[nx][ny] == 'R')
                        ne = energy;

                    if (ne <= best[nx][ny][nmask])
                        continue;

                    best[nx][ny][nmask] = ne;
                    q.push({nx, ny, nmask, ne});
                }
            }

            steps++;
        }

        return -1;
    }
};