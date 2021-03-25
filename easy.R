library(volesti)
library(ggplot2)

x1<-runif(100, min = -1, max = 1)
x2<-runif(100, min = -1, max = 1)

g<-ggplot(data.frame( x=x1+x2, y=x1-x2 )) + geom_point( aes(x=x, y=y)) + xlim(-2,2) + ylim(-2,2)

plot(g)
