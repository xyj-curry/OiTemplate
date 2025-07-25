while (!q.empty()) {
    q.pop_back();
}
for (int i = 1; i <= n; i++) {
    while ((!q.empty()) && ((i - q.back() + 1) > k)) {
        q.pop_back();
    }
    
    while ((!q.empty()) && (a[q.front()] <= a[i])) {
        q.pop_front();
    }
    q.push_front(i);
}