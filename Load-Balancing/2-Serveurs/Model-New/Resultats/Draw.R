#Execution : R CMD BATCH "Draw.R"

modelname1 = "Variation-Mu2-90"

#-------------CourbeLines-----------------
data1 = read.table(modelname1)
attach(data1);
Mu2 =V1
E1 =V2
E2 =V3
E3 =V4


plot(Mu2,E1,type="b",col="black",xlab="charge file2", ylab="Energie",ylim=c(230,320))
lines(Mu2,E2,type="b",col="green")
lines(Mu2,E3,type="b",col="red")

title(main = "Variation de la charge2, File 1 chargé à 90% puis 60% ")
legend("topleft", legend=c("ELB","ESLB","Ereboot"),
       col=c("green","black","red"), lty=1:1, cex=1.3)
       
       

modelname2 = "Variation-Mu2-60"

#-------------CourbeLines-----------------
data2 = read.table(modelname2)
attach(data2);
Mu2 =V1
E1 =V2
E2 =V3
E3 =V4


lines(Mu2,E1,type="b",col="black",xlab="charge file2", ylab="Energie",ylim=c(230,320))
lines(Mu2,E2,type="b",col="green")
lines(Mu2,E3,type="b",col="red")
text(0.3,290,"File1 : 90%",cex=1.4);
text(0.3,263,"File1 : 60%",cex=1.4);
#title(main = "Variation de la charge de la file 2 (file1 chargé à 60%)")
#legend("topleft", legend=c("ELB","ESLB","Ereboot"),
#       col=c("green","black","red"), lty=1:1, cex=1.3)







