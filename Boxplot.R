library(readxl)
dados_graficos <- read_excel("~/UEL2018/TCC/dados-graficos.xlsx")
#View(dados_graficos)


pdf("~/UEL2018/TCC/box-120.pdf")
boxplot(dados_graficos, col = (c("darkred", "darkgreen", "lightblue")), 
        xlab="Obstáculo"  ,ylab="Distância(cm)", ylim = c(26, 34))
dev.off()

