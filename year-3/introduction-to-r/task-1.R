# Copyright 2020, Sergey Popov (i@sergobot.com)

library(dplyr)
data("airquality")

# - Wind speed should be converted into metres per second
# - Temperature should be converted into Celsius degrees
# - Add new column with day of the week
airquality <-
  airquality %>% mutate(
    Wind = Wind / 2.237,
    Temp = (Temp - 32) * 5 / 9,
    Weekday = weekdays(ISOdate(1973, Month, Day))
  )

# - Only weekends data should be emitted (= Sundays and Saturdays)
aqFiltered <- filter(airquality, Weekday == "Saturday" | Weekday == "Sunday")
write.table(aqFiltered,"output.csv", sep=",",row.names=TRUE)

# - Days (month and date), when ozone level and solar radiation were maximal and minimal
airquality %>% slice_max(Ozone)
airquality %>% slice_min(Ozone)
airquality %>% slice_max(Solar.R)
airquality %>% slice_min(Solar.R)

# - Average temperature and wind speed
mean(airquality$Temp)
mean(airquality$Wind)

# - Day, when solar radiation level did "highest jump"
airquality <- mutate(airquality, Solar.R.Diff = Solar.R - lag(Solar.R, default = Solar.R[1]))
airquality %>% slice_max(Solar.R.Diff)
