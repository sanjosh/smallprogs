require(ggplot2)
require(reshape2)

d <- read.csv('rocksdb.csv')

dlong = melt(d, id='time')

p <- ggplot(data = dlong, 
  aes(x=time, y=value, colour = variable)) + 
  geom_line() +
  ylab("rate")
  annotate("text", x = 200, y = 1000, label = "1024 bytes/sec")

ggsave(file='rocksdb_rate_limit.png')
#ggplot(d, aes(time_us)) + 
  #geom_line(aes(y = available, colour="var0")) +
  #geom_line(aes(y = requested, colour="var1"))

