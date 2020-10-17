
/*
 * no space, 
 * lowercase english(0-25)
 * len=N
 * exactly K letters from 26
 * one prefix matches suffix for sublen < N/2
 *
 * 1 <= N <= 10^5
 * 1 <= K <= 26
 *
 * N   K   O
 * 2   1   26
 * 4   2   
 *
 * 1char suffix = C(26,K) * 
 * 2char suffix = C(26,K) * 
 *
 * for (int prefixLen = 1; prefixLen < N/2; prefixLen ++)
 * {
 *      
 * }
 *    C ( N - 2.prefixLen, K )
 *    C ( prefixLen, K )
 *
 */
