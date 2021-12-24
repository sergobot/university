library(gridExtra)
library(ggplot2)
library(tseries)
library(dplyr)
library(tidyr)

mu <- 3
variance <- 1

# Apply Jarque-Bera test on $count$ samples of $n$ elements, for each $n$ in $Ns$
jarque_bera_samples <- function(Ns, count, distr, ...) {
  p <- lapply(
    Ns, function(n) apply(
      matrix(
        distr(n * count, ...),
        nrow = n,
        byrow = TRUE
      ),
      2,
      function(c) jarque.bera.test(c)$statistic
    )
  )
  df <- data.frame(matrix(unlist(p), ncol=length(p), byrow=F))
  colnames(df) <- lapply(Ns, toString)
  return(gather_(df, "N", "jarque_bera", colnames(df)))
}

plot_jq <- function(Ns, count, distr, ...) {
  jbs <- jarque_bera_samples(Ns, count, distr, ...)
  ggplot() +
    stat_ecdf(geom = "step", aes(x = jarque_bera, color = N), jbs)
}

# 1: Compute Jarque-Bera test with several sample sizes
Ns <- c(10, 100, 1000, 10000)

true_distr <- data.frame(x = 0:10) %>%
  mutate(chisq = pchisq(q = x, df = 2)) %>%
  gather(key = "df", value="func", chisq)

show(plot_jq(Ns, 2000, rnorm, mu, variance) + xlim(0, 10) + geom_line(aes(x = x, y = func), true_distr))

# 2: Plot ECDF of Jarque-Bera for other distributions
pois <- plot_jq(Ns, 200, rpois, 5) + labs(title = "ECDF of Jarque-Bera on Poisson distribution")
exp <-  plot_jq(Ns, 200, rexp, 1.5) + labs(title = "ECDF of Jarque-Bera on exponential distribution")

show(grid.arrange(pois, exp, nrow=2))
