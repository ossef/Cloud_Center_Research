variables = commandArgs(trailingOnly=TRUE)
modelname = variables[1]

data = read.table(modelname)
attach(data);
e1 =V1
e0 =V2
Power =V3

library(lattice)


levelplot(
  Power ~ e1*e0, data = data, 
  xlab = "e1", ylab = "e0",
  main = "Power Consuming, SLB, buffer = 50",
  col.regions = topo.colors(20)  #cm terrain topo heat
)


