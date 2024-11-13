
variables = commandArgs(trailingOnly=TRUE)
modelname1 = "mod50-V1.mod50-V2.comp"

data1 = read.table(modelname1)
attach(data1);
U1 =V1
D1 =V2
comp =V3
I=1:1225

library(lattice)

plot(I,comp,type="l",col="black",xlab="U,D",ylab="Comparaison-ST")
title("V1-St-Comparaison-V2")













