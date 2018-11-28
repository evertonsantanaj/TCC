library(readr)
library(fmsb)
data <- read_csv("~/Documents/radar-centro.csv")[1:3,2:5]

rownames(data)<- c("Pilar", "Tubo", "Madeira")
colnames(data)<-c("30", "60", "90", "120")
n.targets <-4

data=rbind(rep(1, n.targets) , rep(0, n.targets) , data)

colors_border=c( "darkred", "darkgreen" , "lightblue" )


pdf("~/Documents/radar-centro.pdf")
radarchart(data, maxmin = TRUE, 
           pcol=colors_border , #pfcol=colors_in , 
           plwd=3 , plty=1, axistype = 4, seg = 9, pty=12,
           #custom the grid
           cglcol="grey", cglty=5, axislabcol="black", cglwd=0.8,
           #custom labels
           vlcex=1, centerzero = TRUE
)

legend(x=0.4, y=-0.8,  legend = c("Pilar", "Tubo", "Madeira"), bty = "n", pch=20 , col=colors_border , text.col = "black", cex=1.1, pt.cex=3)
dev.off()
