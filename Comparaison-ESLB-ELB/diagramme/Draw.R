#Execution : R CMD BATCH "Draw.R"

modelname1 = "LB-mod-50-gama2.resultat"
modelname2 = "SLB-mod-50.resultat"





#-------------BarrePlot-----------------
data1 = read.table(modelname1)
attach(data1);
e0 =V1
e1 =V2
eb =V3
Elb = V4

data2 = read.table(modelname2)
attach(data2);
e0 =V1
e1 =V2
Eslb = V3


barplot(Elb-Eslb,names.arg = eb,xlab = "eb : l'énergie consommé lors d'un LB",ylab = "Diffèrence d'énergie",col = "blue", main = "Difference d'énergie entre modèle LB et modèle SLB",border = "black")
abline(v=12.1, col="Red",lwd="4",lty=1)
legend("topleft", legend=c("Elb - Eslb","eb = e0 = 10"),
       col=c("blue","red"), lty=1:1, cex=1.3)

#plot(x,pi1,type="h",xlab="X",ylab="Marginale sortie de X")
#title("Courbe de la marginale conditionnel sur les paquets qui sortent") 
#legend(40, 0.145, legend=c("Pi0"),
#       col=c("black"), lty=1:1, cex=1.2)




