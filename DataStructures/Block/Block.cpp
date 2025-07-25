#define belong(x) ((x - 1) / blsfk + 1)
#define bll(x) ((x - 1) * blsfk + 1)
#define blr(x) min((x * blsfk), n)

int blsfk;
blsfk = sqrt(n);