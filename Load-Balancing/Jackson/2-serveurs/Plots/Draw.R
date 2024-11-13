#Execution : R CMD BATCH "Draw.R"

library(gplots)
library(grid)
#library(fields)
library(lattice)
  
modelname1 = "Fonction_gamma1_eb1.resultat"

data1 = read.table(modelname1)
attach(data1);

eb = V1
gama = V2
Nv2 = V3
Nv1 = V4
Nvt = V5
E2 = V9
E1 = V10
Et = V11 


plot(gama, E2 , ylim=c(0,400), type="l", pch=15, lwd=1.2, cex = 0.4,col ="black",xlab="Migration rate", ylab = "Energy consumption (W)")

text(0.65,276,"(0.60 , 241.31)",pos=1 , col="#666666")
text(0.13,318,"(0 , 287.00)",pos=1 , col="#666666")
lines(gama, E1, type="l", font.lab=2, pch=16, lty=1, lwd=1.2, col="red" )
lines(gama, Et, type="l", font.lab=2, pch=17, lty=1, lwd=1.2, col="#009900" )
segments(0, 241.313, 0.6, 241.313, col="#666666" ,lty=2, lwd =2 )
segments(0.6, 0, 0.6, 241.313, col="#666666",lty=2, lwd =2 )
points(0.6,241.313,pch=19,col="grey")
points(0,287,pch=19,col="grey")

legend(x="topleft",legend=c("Data center","Server 2","Server 1"),text.col=c("#009900" ,"black","red"),col=c("#009900" ,"black","red"),lty=1:1, cex=1.2) 
#panel.first = grid()


plot(gama, Nv2 , ylim=c(0,25), type="l", pch=15, lwd=1.2, cex = 0.4,col ="black",xlab="Migration rate", ylab = "Mean number of activated VMs")
points(0.6,10.62,pch=19,col="grey")
points(0,17,pch=19,col="grey")
text(0.085,19,"(0 , 17)",pos=1 , col="black")

lines(gama, Nv1 , type="l", font.lab=2, pch=16, lty=1, lwd=1.2, col="red" )
points(0.6,8.37,pch=19,col="grey")
points(0,2,pch=19,col="grey")
text(0.087,1.7,"(0 , 2)",pos=1 , col="red")

segments(0.6, 0, 0.6, 10.608, col="#666666" ,lty=2, lwd =2 )
segments(0, 8.3902, 0.6,8.3902, col="#666666",lty=2, lwd =2 )
segments(0, 10.608, 0.6, 10.608, col="#666666",lty=2, lwd =2 )
text(0.75,12.7,"(0.6 , 10.61)",pos=1 , col="black")
text(0.82,7.5,"(0.6 , 8.39)",pos=1 , col="red")

#------------------------- Cas de eb = 3 ----------------------------------

modelname2 = "Fonction_gamma1_eb3.resultat"

data2 = read.table(modelname2)
attach(data2);

eb = V1
gama = V2
Nv2 = V3
Nv1 = V4
Nvt = V5
E2 = V9
E1 = V10
Et = V11 


plot(gama, E2 , ylim=c(0,400), pch=15, cex = 0.8,col ="black",xlab="Migration rate", ylab = "Energy consumption (W)")

text(0.65,282,"(0.55 , 249.20)",pos=1 , col="#009900")
text(0.13,318,"(0 , 287.00)",pos=1 , col="#009900")
points(gama, E1, pch=8, cex=0.8, col="red"  )
lines(gama, Et, type="b", pch=16, lty=1, cex=1.1, col="#009900" )
segments(0, 249.20, 0.553, 249.20, col="#666666" ,lty=5, lwd =2 )
segments(0.553, 0, 0.553, 249.20, col="#666666",lty=5, lwd =2 )
points(0.553,249.20,pch=19,col="grey")
points(0,287,pch=19,col="grey")

legend(x="topleft",legend=c("Data center","Server 2","Server 1"),text.col=c("#009900" ,"black","red"),col=c("#009900" ,"black","red"), pch=c(16,15,8)) 
#panel.first = grid()


plot(gama, Nv2 , ylim=c(0,25), pch=15, cex = 0.8,,col ="black",xlab="Migration rate", ylab = "Mean number of activated VMs")
points(0.553,10.94,pch=19,col="grey")
points(0,17,pch=19,col="grey")
text(0.085,19,"(0 , 17)",pos=1 , col="black")

points(gama, Nv1 , pch=8, cex=0.8, col="red" )
points(0.553,8.058,pch=19,col="grey")
points(0,2,pch=19,col="grey")
text(0.087,1.7,"(0 , 2)",pos=1 , col="red")

segments(0.553, 0, 0.553, 10.94, col="#666666" ,lty=2, lwd =2 )
segments(0, 8.058, 0.553,8.058, col="#666666",lty=2, lwd =2 )
segments(0, 10.94, 0.553, 10.94, col="#666666",lty=2, lwd =2 )
text(0.75,12.7,"(0.55 , 10.94)",pos=1 , col="black")
text(0.75,7.5,"(0.55 , 8.05)",pos=1 , col="red")
legend(x="topleft",legend=c("Server 2","Server 1"),text.col=c("black","red"),col=c("black","red"), pch=c(15,8)) 


#------------------------- Cas de eb = 4 ----------------------------------

modelname3 = "Fonction_gamma1_eb4.resultat"

data3 = read.table(modelname3)
attach(data3);

eb = V1
gama = V2
Nv2 = V3
Nv1 = V4
Nvt = V5
E2 = V9
E1 = V10
Et = V11 


plot(gama, E2 , ylim=c(0,400), type="l", pch=15, lwd=1.2, cex = 0.4,col ="black",xlab="Migration rate", ylab = "Energy consumption (W)")

text(0.65,276,"(0.52 , 253.07)",pos=1 , col="#666666")
text(0.13,318,"(0 , 287.00)",pos=1 , col="#666666")
lines(gama, E1, type="l", font.lab=2, pch=16, lty=1, lwd=1.2, col="red" )
lines(gama, Et, type="l", font.lab=2, pch=17, lty=1, lwd=1.2, col="#009900" )
segments(0, 253.07, 0.525, 253.07, col="#666666" ,lty=2, lwd =2 )
segments(0.525, 0, 0.525, 253.07, col="#666666",lty=2, lwd =2 )
points(0.525,253.07,pch=19,col="grey")
points(0,287,pch=19,col="grey")

legend(x="topleft",legend=c("Data center","Server 2","Server 1"),text.col=c("#009900" ,"black","red"),col=c("#009900" ,"black","red"),lty=1:1, cex=1.2) 
#panel.first = grid()


plot(gama, Nv2 , ylim=c(0,25), type="l", pch=15, lwd=1.2, cex = 0.4,col ="black",xlab="Migration rate", ylab = "Mean number of activated VMs")
points(0.525,11.14,pch=19,col="grey")
points(0,17,pch=19,col="grey")
text(0.085,19,"(0 , 17)",pos=1 , col="black")

lines(gama, Nv1 , type="l", font.lab=2, pch=16, lty=1, lwd=1.2, col="red" )
points(0.525,7.85,pch=19,col="grey")
points(0,2,pch=19,col="grey")
text(0.087,1.7,"(0 , 2)",pos=1 , col="red")

segments(0.525, 0, 0.525, 11.14, col="#666666" ,lty=2, lwd =2 )
segments(0, 7.85, 0.525,7.85, col="#666666",lty=2, lwd =2 )
segments(0, 11.14, 0.525, 11.14, col="#666666",lty=2, lwd =2 )
text(0.75,12.7,"(0.52 , 11.14)",pos=1 , col="black")
text(0.82,7.5,"(0.52 , 7.85)",pos=1 , col="red")

#------------------------- Courbe de l'optimalité ----------------------------------

modelname4 = "Fonction_Opt.resultat"

data4 = read.table(modelname4)
attach(data4);

eb = V1
E = V16


plot(eb, E, ylim=c(0,20), type="l", pch=15, lwd=1.2, cex = 0.4,col ="#009900",xlab="Migration cost", ylab = "Energy Gain in optimal case (%)")
points(0,17.314221,pch=19,col="grey")
points(18,0,pch=19,col="grey")

text(3,19,"Best case : 17.31%",pos=1 , col="red")
text(17.314221,2,"Worst case : 0%",pos=1 , col="red")




