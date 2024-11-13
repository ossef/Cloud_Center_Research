
variables = commandArgs(trailingOnly=TRUE)
model1 = variables[1]
model2 = variables[2]


data1 = read.table(model1)
attach(data1);
I =V1
PI0 =V2



data2 = read.table(model2)
attach(data2);
I =V1
PI1 =V2



plot(I,PI0,type="l",xlab="i",ylab="Marginale(i)")
title("Spectre Marginale de Pi0 et Pi1") 
lines(PI1,type="l",col="red")
legend(80, 0.145, legend=c("Pi0", "Pi1"),
       col=c("black", "red"), lty=1:1, cex=1.2)



