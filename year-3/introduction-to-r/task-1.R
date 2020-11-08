# Copyright 2020, Sergey Popov (i@sergobot.com)

library(dplyr)
data("airquality")

# - Wind speed should be converted into metres per second
airquality$Wind <- airquality$Wind / 2.237

# - Temperature should be converted into Celsius degrees
airquality$Temp <- (airquality$Temp - 32) * 5/9

# - Add new column with day of the week
airquality$Weekday <- weekdays(ISOdate(1973, airquality$Month, airquality$Day))

# - Only weekends data should be emitted (=Sundays and Saturdays)
aqFiltered <- filter(airquality, Weekday == "Saturday" | Weekday == "Sunday")

write.table(aqFiltered,"output.csv",sep=",",row.names=TRUE)

# - Days (month and date), when ozon level and solar radiation were maximal and minimal
airquality[c("Ozone", "Month", "Day")][c(which.max(airquality$Ozone), which.min(airquality$Ozone)),]
airquality[c("Solar.R", "Month", "Day")][c(which.max(airquality$Solar.R), which.min(airquality$Solar.R)),]

# - Average temperature and wind speed
mean(airquality$Temp)
mean(airquality$Wind)

# - Day, when solar radiation level did "highest jump"
airquality$Solar.R.Diff <- c(NA, tail(airquality$Solar.R, -1) - head(airquality$Solar.R, -1))
airquality[c("Solar.R.Diff", "Month", "Day")][which.max(airquality$Solar.R.Diff),]
