
angle(hr) = (60.h + m)/2
angle(min) = 6.m

http://en.wikipedia.org/wiki/Clock_angle_problem#When_are_the_hour_and_minute_hands_of_a_clock_superimposed.3F

hr   min   angle
1     0     5    (0  - 5)
1     15         (15 - 5 - (1/4)5)
1     30    22.5 (30 - 5 - (1/2)5)
1     45         (45 - 5 - (3/4)5)
2     0     10
2     15         (15 - 10 - (1/4)5)
2     30         (30 - 10 - (30/60)5)

10    15         (15 - 50 + (1/4)5) ? = 35 + 1.25

angle = min - (hr * 5) + (min/60)*5

The idea is to take 12:00 (h = 12, m = 0) as a reference. Following are detailed steps.

1) Calculate the angle made by hour hand with respect to 12:00 in h hours and m minutes.
2) Calculate the angle made by minute hand with respect to 12:00 in h hours and m minutes.
3) The difference between two angles is the angle between two hands.

How to calculate the two angles with respect to 12:00?
The minute hand moves 360 degree in 60 minute(or 6 degree in one minute) and hour hand moves 360 degree in 12 hours(or 0.5 degree in 1 minute). In h hours and m minutes, the minute hand would move (h*60 + m)*6 and hour hand would move (h*60 + m)*0.5.
// C program to find angle between hour and minute hands
#include <stdio.h>
#include <stdlib.h>
 
// Utility function to find minimum of two integers
int min(int x, int y) { return (x < y)? x: y; }
 
int calcAngle(double h, double m)
{
    // validate the input
    if (h <0 || m < 0 || h >12 || m > 60)
        printf("Wrong input");
 
    if (h == 12) h = 0;
    if (m == 60) m = 0;
 
    // Calculate the angles moved by hour and minute hands
    // with reference to 12:00
    int hour_angle = 0.5 * (h*60 + m);
    int minute_angle = 6*m;
 
    // Find the difference between two angles
    int angle = abs(hour_angle - minute_angle);
 
    // Return the smaller angle of two possible angles
    angle = min(360-angle, angle);
 
    return angle;
}
 
// Driver program to test above function
int main()
{
    printf("%d \n", calcAngle(9, 60));
    printf("%d \n", calcAngle(3, 30));
    return 0;
}

