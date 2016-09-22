require(ggplot2)
require(reshape2)

d <- read.csv('rocksdb.csv')

dlong = melt(d, id='time_us')

p <- ggplot(data = dlong, 
  aes(x=time_us, y=value, colour = variable)) + 
  geom_smooth() +
  geom_line() +
  annotate("text", x = 150000, y = 800, label = "only hi pri;1024 bytes/sec")

ggsave(file='rocksdb_rate_limit.png')
#ggplot(d, aes(time_us)) + 
  #geom_line(aes(y = available, colour="var0")) +
  #geom_line(aes(y = requested, colour="var1"))

