
variables = commandArgs(trailingOnly=TRUE)
modelname = variables[1]

data = read.table(modelname)
attach(data);
e0 =V1
e1 =V2
eb =V3
Power =V4

library("plot3D")
library(lattice)



png(file="example%03d.png", width=600, heigh=600)
  for (i in seq(0, 250 ,2)){
   scatter3D(e0,e1,eb,colvar = Power,clab = c("Power"),ticktype = "detailed",type = "h",pch = 15, cex = 1, phi = 40, theta = i,xlab = "e0",ylab="e1",zlab="eb")
  }
dev.off()
# convert pngs to one gif using ImageMagick
system("convert -delay 40 *.png spectre.gif")

# cleaning up
file.remove(list.files(pattern=".png"))


