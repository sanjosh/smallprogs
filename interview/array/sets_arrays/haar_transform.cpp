/*
FINDING SIMILAR SUBSEQ in a SEquence of time series by sliding window

taking average is equiv to low-pass filter

The first DWT was invented by the Hungarian mathematician Alfréd Haar. For an input represented by a list of 2n numbers, the Haar wavelet transform may be considered to simply pair up input values, storing the difference and passing the sum. This process is repeated recursively, pairing up the sums to provide the next scale: finally resulting in 2n-1 differences and one final sum.

Suppose you are given N values

x = (x1, x2, … xN)

where N is even.

We take pair-wise average of numbers

THIS IS LOW PASS FILTER (AKA SCALING FUNC)
sk = (x2k + x2k+1)/2 for k=0, …, N/2 -1

For example,

x = (6, 12, 15, 15, 14, 12, 120, 116) -> s = (9, 15, 13, 118)

We need second list of data d so that the original list x can be recovered from s and d.

For dk (called directed distances), we have:
THIS IS HIGH PASS FILTER (AKA WAVELET FUNC)

dk = (x2k - x2k+1)/2 for k=0, …, N/2 -1

The process is invertible since:

sk + dk = (x2k + x2k+1)/2 + (x2k - x2k+1)/2 = x2k

sk - dk = (x2k + x2k+1)/2 - (x2k - x2k+1)/2 = x2k+1

So we map x = (x1, x2, … , xN) to (s | d) = (s1, … , sN/2 | d1, … , dN/2).

Using our example values, we have:

(6, 12, 15, 15, 14, 12, 120, 116) -> (9, 15, 13, 118 | -3, 0, 1, 2)

This process is repeated recursively for s:

(9, 15, 13, 118 | -3, 0, 1, 2) -> (12, 65.5 | -3, -52.5 | -3, 0, 1, 2)

(12, 65.5 | -3, -52.5 | -3, 0, 1, 2) -> (38.75 | -26.75 | -3, -52.5 | -3, 0, 1, 2)

So final result is:

(38.75, -26.75, -3, -52.5, -3, 0, 1, 2) 

first number is overall average of sequence

http://www.codeproject.com/Articles/683663/Discrete-Haar-Wavelet-Transformation

http://www.bearcave.com/misl/misl_tech/wavelets/haar.html

*/

