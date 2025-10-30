#include <stdbool.h>
#include <string.h>

bool isInterleave(char * s1, char * s2, char * s3) {
    int m = strlen(s1), n = strlen(s2), len = strlen(s3);

    // If total lengths don't match, it's impossible
    if (m + n != len) return false;

    // dp[i][j] = true if s3[0...(i+j-1)] can be formed by interleaving s1[0...(i-1)] and s2[0...(j-1)]
    bool dp[m + 1][n + 1];
    memset(dp, false, sizeof(dp));

    dp[0][0] = true; // Empty strings interleave to form empty string

    // Initialize first row (using only s2)
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
    }

    // Initialize first column (using only s1)
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                       (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }

    return dp[m][n];
}
