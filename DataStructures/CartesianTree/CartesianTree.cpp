int ls[MAXN], rs[MAXN];
stack<int> st;
void CartesianTree() {
    while (!st.empty()) {
        st.pop();
    }
    for (int i = 1; i <= n; i++) {
        int lst = -1;
        while (!st.empty() && a[st.top()] > a[i]) {
            lst = st.top();
            st.pop();
        }
        if (lst != -1) {
            ls[i] = lst;
        }
        if (!st.empty()) {
            rs[st.top()] = i;
        }
        st.push(i);
    }
}