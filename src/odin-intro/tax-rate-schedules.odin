package main

import "core:fmt"

income : f32 : 100_000
expectedTaxes : f32 : 13_580

Schedule :: struct {
  limit : f32,
  rate : f32,
}

schedules :: [?]Schedule{
  Schedule{622050, 0.37},
  Schedule{414701, 0.35},
  Schedule{326600, 0.32},
  Schedule{171050, 0.24},
  Schedule{80250, 0.22},
  Schedule{19750, 0.12},
  Schedule{0, 0.1},
}

main :: proc() {
  for key in schedules {
    fmt.printf("% 6.0f\n", key.limit)
  }
}
