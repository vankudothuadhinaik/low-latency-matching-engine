# Benchmarking and performance evidence

This repository's benchmark is a microbenchmark, not an exchange-grade performance claim. Use the same source revision, compiler, build mode, machine, and workload when comparing changes.

## Reproduce

Build the `engine_benchmark` target using the repository's CMake instructions, then run:

```bash
./engine_benchmark 1000000 5 100 mixed
./engine_benchmark 1000000 5 100 marketable
./engine_benchmark 1000000 5 100 non-crossing
./engine_benchmark 1000000 5 100 cancellation-heavy
```

Arguments are measured order count, number of throughput runs, and latency sampling interval. Defaults are one million measured orders, five runs, and one latency sample per 100 orders. The benchmark warms up the engine before timing and uses a deterministic random seed for each run.

## Interpret the output

- Throughput is measured over all submitted orders in each measured run.
- Summary statistics include min/max/mean/median, population standard deviation, and coefficient of variation.
- Latency percentiles are sampled only in the final run; they are not a full distribution.
- Clock-pair overhead is reported separately and is not subtracted from each sample.
- Results depend on CPU scheduling, power management, compiler, build flags, allocator behavior, and host load.

## Comparison checklist

1. Use a Release build and record compiler/version, CMake configuration, OS, CPU model, and commit SHA.
2. Run at least five trials after warm-up; avoid concurrent CPU-heavy work.
3. Compare identical order counts and sampling intervals.
4. Keep raw output for every trial; do not compare a single best run.
5. Treat latency percentiles as sampled estimates and report the sample count.
6. Do not describe these numbers as production exchange performance without independent profiling and a realistic workload.

The benchmark supports three deterministic workload profiles: `mixed` (random sides and prices), `marketable` (alternating sides at one price, exercising immediate matching), and `non-crossing` (alternating sides at separated prices, growing the resting book), and `cancellation-heavy` (non-crossing orders with every other newly submitted order cancelled). The cancellation workload reports submissions per second; each measured pair of submissions also includes periodic cancellation operations, so it is not a pure cancellation-only throughput figure. These profiles cover different engine paths but are not a complete market workload suite; The profiles are synthetic and should be supplemented with representative order-flow traces where available.


### Skewed-price workload

Use `engine_benchmark 1000000 5 100 skewed-price` to stress an asymmetric price distribution: buy prices are concentrated near 10000 while sell prices are spread across a wider upper range. This is a synthetic workload for comparative testing, not a claim about production order flow.
