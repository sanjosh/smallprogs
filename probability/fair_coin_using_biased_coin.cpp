
http://stackoverflow.com/questions/5429045/c-puzzle-make-a-fair-coin-from-a-biased-coin

Von Neumann's idea

if we have a biased coin (i.e. a coin that comes up heads with probability different from 1/2), 
we can simulate a fair coin by tossing pairs of coins until the two results are different. 
Given that we have different results, the probability that the first is “heads” and the second is “tails” is the same as the probability of “tails” then “heads”. 
So if we simply return the value of the first coin, we will get “heads” or “tails” with the same probability, i.e. 1/2.

def fairCoin(biasedCoin):
   coin1, coin2 = 0,0
   while coin1 == coin2:
      coin1, coin2 = biasedCoin(), biasedCoin()
   return coin1
