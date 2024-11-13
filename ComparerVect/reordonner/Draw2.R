
variables = commandArgs(trailingOnly=TRUE)
modelname1 = "mod50-V1.mod50-V2.comp"

data1 = read.table(modelname1)
attach(data1);
U1 =V1
D1 =V2
comp =V3

library(lattice)


levelplot(
  comp ~ U1*D1, 
  scales=list(Power=list(at=seq(10,20,1))),
  xlab = "U", ylab = "D",
  main = "V1-St-Comparaison-V2",
  col.regions = topo.colors(20)  #cm terrain topo heat
)











