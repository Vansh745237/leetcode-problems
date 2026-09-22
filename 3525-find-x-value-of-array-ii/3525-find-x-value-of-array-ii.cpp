class Solution {
public:
    struct Node {
        int p;
        int pre[5];

        Node() {
            p = 1;
            for (int i = 0; i < 5; i++) pre[i] = 0;
        }
    };

    int k;
    vector<Node> st;

    Node merge(Node &a, Node &b) {
        Node c;
        c.p = (a.p * b.p) % k;

        for (int i = 0; i < k; i++)
            c.pre[i] = a.pre[i];

        for (int i = 0; i < k; i++) {
            int r = (a.p * i) % k;
            c.pre[r] += b.pre[i];
        }

        return c;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            int x = nums[l] % k;
            st[p].p = x;
            st[p].pre[x] = 1;
            return;
        }

        int m = (l + r) / 2;

        build(p * 2, l, m, nums);
        build(p * 2 + 1, m + 1, r, nums);

        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    void update(int p, int l, int r, int pos, int val) {
        if (l == r) {
            st[p] = Node();
            val %= k;
            st[p].p = val;
            st[p].pre[val] = 1;
            return;
        }

        int m = (l + r) / 2;

        if (pos <= m)
            update(p * 2, l, m, pos, val);
        else
            update(p * 2 + 1, m + 1, r, pos, val);

        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return st[p];

        int m = (l + r) / 2;

        if (qr <= m)
            return query(p * 2, l, m, ql, qr);

        if (ql > m)
            return query(p * 2 + 1, m + 1, r, ql, qr);

        Node a = query(p * 2, l, m, ql, qr);
        Node b = query(p * 2 + 1, m + 1, r, ql, qr);

        return merge(a, b);
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();
        st.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.pre[x]);
        }

        return ans;
    }
};