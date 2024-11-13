variables = commandArgs(trailingOnly=TRUE)
modelname = variables[1]

name1 = paste0(modelname,".cd")
name2 = paste0(modelname,".pi")

data1 = read.table(name1)
attach(data1);
i =V1
x1 =V2
x2 =V3

data2 = read.table(name2)
attach(data2);
Pi =log10(V1)


library(lattice)
require(rasterVis)

theme = viridisTheme()#le theme bleu rouge
numberOfBreaks = 6   #nombre de break point axe z
brksUniv <- seq(-12,-1, length.out=numberOfBreaks) #joue le role de zlim
myColor <- list(at=brksUniv, col=theme$regions$col)  #couleur qu'on defini


levelplot(
  Pi ~ x1*x2, data = data2, 
  xlab = "X1", ylab = "X2",
  main = "Stationnary Distribution",
   par.settings=theme,
  at=brksUniv,
  colorkey=myColor, #col.regions = topo.colors(20)  #cm terrain topo heat
  #scales=list(draw=FALSE)
)


