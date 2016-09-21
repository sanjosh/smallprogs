package com.google.common.util.concurrent;

import com.google.common.base.Stopwatch;
import com.google.common.util.concurrent.RateLimiter.SleepingStopwatch;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;

import static java.util.concurrent.TimeUnit.MICROSECONDS;

/**
 * Created by sandeep on 18/9/16.
 */
public final class RateLimiterBenchmark {

    public static class LimitRunnable implements Runnable {

        private RateLimiter limiter;
        private int index;

        public LimitRunnable(int i, RateLimiter inputLimiter) {
           index = i; limiter = inputLimiter;
        }
        public void run() {
            long startTime = System.currentTimeMillis();
            for (int i = 0; i < 100; i++) {
                int permit = ThreadLocalRandom.current().nextInt(1, 1024);


                if (i > 40 & i < 60) {
                    // create some slack to display peak bursts
                    try {
                        Thread.sleep(100); // 10 millisec
                        permit = 1;
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                if (i > 60 & i < 70) {
                    // create a peak burst
                    permit = permit * 4;
                }

                limiter.acquire(permit);
                long endTime = System.currentTimeMillis();
                System.out.printf("%d,%d\n", endTime - startTime, permit);
            }

        }
    }

    public static void main(String[] args) {

        RateLimiter.SleepingStopwatch stopwatch = RateLimiter.SleepingStopwatch.createFromSystemTimer();

        RateLimiter limiter = RateLimiter.create(stopwatch, 1024.0);

        List<Thread> listThreads = new ArrayList<Thread>();
        for (int i = 0; i < 5; i++) {
            Runnable r = new LimitRunnable(i, limiter);
            Thread t = new Thread(r);
            t.start();
            listThreads.add(t);
        }

        for (Thread t : listThreads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
