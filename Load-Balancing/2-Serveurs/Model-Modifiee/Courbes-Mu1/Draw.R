#Execution : R CMD BATCH "Draw.R"

modelname1 = "SLB-mod-10.resultat"
modelname2 = "LB-mod-10.resultat"





#-------------CourbeLines-----------------
data1 = read.table(modelname1)
attach(data1);
Mu1 =V1
E1 =V2


data2 = read.table(modelname2)
attach(data2);
Mu1 =V1
E2 =V2


plot(Mu1,E2,type="l",col="red",xlab="Mu1", ylab="Energie")
abline(h=E1[1], col="blue")
text(1, 267.3, "ESLB = 265.99")
title(main = "Variation du taux de service Mu1 (file1 chargé à 90%)", sub="file2 chargé à 10% avec Mu2 = 1")
legend("center", legend=c("ESLB","ELB"),
       col=c("blue","red"), lty=1:1, cex=1.3)






