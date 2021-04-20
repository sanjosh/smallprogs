
http://www.geeksforgeeks.org/check-if-a-number-is-palindrome/

http://stackoverflow.com/questions/199184/how-do-i-check-if-a-number-is-a-palindrome

n = num;
rev = 0;
while (num > 0)
{
     dig = num % 10;
     rev = rev * 10 + dig;
     num = num / 10;
}

if (n == rev) palindrome


boolean isPalindrome(int x) 
{
        if (x < 0) return false;
        int div = 1;

        while (x / div >= 10) 
        {
             div *= 10;
        }

        while (x != 0) 
        {
           int l = x / div;
           int r = x % 10;
           if (l != r) return false;
           x = (x % div) / 10;
           div /= 100;
        }

        return true;
 }
