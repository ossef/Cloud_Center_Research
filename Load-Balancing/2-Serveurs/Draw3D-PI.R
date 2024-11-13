
variables = commandArgs(trailingOnly=TRUE)
modelname1 = variables[1]
modelname2 = variables[2]

data1 = read.table(modelname1)
attach(data1);
n = V1
x1 =V2
x2 =V3

data2= read.table(modelname2)
attach(data2);
pi = V1


library(lattice)


levelplot(
  pi ~ x1*x2, data = data, 
  xlab = "x1", ylab = "x2",
  main = "Stationnary Distribution with LB",
  col.regions = topo.colors(20)  #cm terrain topo heat
)

