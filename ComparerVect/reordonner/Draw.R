
"variables = commandArgs(trailingOnly=TRUE)
modelname1 = mod70-V1.resultat
modelname2 = mod70-V2.resultat

data1 = read.table(modelname1)
attach(data1);
U1 =V1
D1 =V2
Loss1 =V3
Power1 =V4
NbreMoyen1 =V5
TempsMoyen1 =V6

data2 = read.table(modelname2)
attach(data2);
U2 =V1
D2 =V2
Loss2 =V3
Power2 =V4
NbreMoyen2 =V5
TempsMoyen2 =V6

#library(fields)
library(lattice)


levelplot(
  Power1-Power2 ~ U1*D1, 
  scales=list(Power=list(at=seq(10,20,1))),
  xlab = U, ylab = D,
  main = Power Consuming,
  col.regions = topo.colors(20)  #cm terrain topo heat
)

levelplot(
  Loss1-Loss2 ~ U1*D1,
  xlab = U, ylab = D,
  main = Costumers Loss,
  col.regions = topo.colors(20)
)"

#------------------- Aprés re order de la matrice ------------------#
variables = commandArgs(trailingOnly=TRUE)
modelname1 = "mod50-V1.lexico.resultat"
modelname2 = "mod50-V2.lexico.resultat"

data1 = read.table(modelname1)
attach(data1);
U1 =V1
D1 =V2
Loss1 =V3
Power1 =V4
NbreMoyen1 =V5
TempsMoyen1 =V6

data2 = read.table(modelname2)
attach(data2);
U2 =V1
D2 =V2
Loss2 =V3
Power2 =V4
NbreMoyen2 =V5
TempsMoyen2 =V6

library(lattice)


levelplot(
  Power1-Power2 ~ U1*D1, 
  scales=list(Power=list(at=seq(10,20,1))),
  xlab = "U", ylab = "D",
  main = "Power Consuming",
  col.regions = topo.colors(20)  #cm terrain topo heat
)

levelplot(
  Loss1-Loss2 ~ U1*D1,
  xlab = "U", ylab = "D",
  main = "Costumers Loss",
  col.regions = topo.colors(20)
)









