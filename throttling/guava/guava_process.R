require(ggplot2)
require(reshape2)

d <- read.csv('guava.csv')

ggplot(d, aes(time)) + 
  geom_line(aes(y = permit, colour="peak")) +
  geom_smooth(aes(y = permit, colour="average")) +
  # annotate("text", x = 150000, y = 800, label = "only hi pri;1024 bytes/sec")

ggsave(file='guava.png')

