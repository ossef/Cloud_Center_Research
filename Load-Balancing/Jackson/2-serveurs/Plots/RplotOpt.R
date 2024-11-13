
modelname = "Fonction_Opt.resultat"

data = read.table(modelname)
attach(data);


plot(V1, V11 , ylim=c(0,400), pch=15, cex = 1,col ="black",xlab="Migration cost (W)", ylab = "Optimal energy consumption (W)")
points(V1, V12, pch=8, cex=1, col="red"  )
lines(V1, V13, type="b", pch=16, lty=1, cex=1.25, col="#009900" )

text(1.8,284,"Gain : 17.31%",pos=1 , col="red")
text(16.2,317,"Gain : 0% ",pos=1 , col="red")
abline(v=18, col="blue")

legend(x="topleft",legend=c("Data center","Server 2","Server 1"),text.col=c("#009900" ,"black","red"),col=c("#009900" ,"black","red"), pch=c(16,15,8)) 
