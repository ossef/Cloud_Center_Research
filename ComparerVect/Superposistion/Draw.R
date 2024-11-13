

nom1 = "exp0.0.pi"
nom2 = "exp0.1.pi"
nom3 = "exp1.0.pi"
nom4 = "exp1.1.pi"
nom5 = "exp2.0.pi"
nom6 = "exp2.1.pi"
nom7 = "exp3.0.pi"
nom8 = "exp3.1.pi"
nom9 = "exp4.0.pi"
nom10 = "exp4.1.pi"




data1 = read.table(nom1)
attach(data1);
I =V1
PI1 =V2

data2 = read.table(nom2)
attach(data2);
I =V1
PI2 =V2

data3 = read.table(nom3)
attach(data3);
I =V1
PI3 =V2

data4 = read.table(nom4)
attach(data4);
I =V1
PI4 =V2

data5 = read.table(nom5)
attach(data5);
I =V1
PI5 =V2

data6 = read.table(nom6)
attach(data6);
I =V1
PI6 =V2

data7 = read.table(nom7)
attach(data7);
I =V1
PI7 =V2

data8 = read.table(nom8)
attach(data8);
I =V1
PI8 =V2

data9 = read.table(nom9)
attach(data9);
I =V1
PI9 =V2

data10 = read.table(nom10)
attach(data10);
I =V1
PI10 =V2



plot(I,PI1,type="l",col="black",xlab="i",ylab="Marginale(i)")
lines(PI2,type="l",col="black")
lines(PI3,type="l",col="yellow")
lines(PI4,type="l",col="yellow")
lines(PI5,type="l",col="pink")
lines(PI6,type="l",col="pink")
lines(PI7,type="l",col="green")
lines(PI8,type="l",col="green")
lines(PI9,type="l",col="red")
lines(PI10,type="l",col="red")
title("Superposition de 5 courbes")















