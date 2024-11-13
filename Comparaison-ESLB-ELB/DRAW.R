variables = commandArgs(trailingOnly=TRUE)
modelname1 = variables[1]
modelname2 = variables[2]

data1 = read.table(modelname1)
attach(data1);
e1 =V1
e0 =V2
Eslb =V3

data2 = read.table(modelname2)
attach(data2);
e1 =V1
e0 =V2
Elb =V3

E = Elb - Eslb
E
x = [0 1 2]
x1 = [3 3 3]
x1-x

library(lattice)


levelplot(
  E ~ e1*e0, 
  xlab = "e1", ylab = "e0",
  main = "EenergieLB(eb=20,gama=10)-EnergieSLB,buffer = 50",
  col.regions = topo.colors(20)  #cm terrain topo heat
)


