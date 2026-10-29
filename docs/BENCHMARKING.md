# Benchmarking and performance evidence

This repository's benchmark is a microbenchmark, not an exchange-grade performance claim. Use the same source revision, compiler, build mode, machine, and workload when comparing changes.

## Reproduce

Build the `engine_benchmark` target using the repository's CMake instructions, then run:

```bash
./engine_benchmark 1000000 5 100
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

The benchmark currently uses one mixed limit-order workload. Separate marketable, non-crossing, cancellation-heavy, and skewed-price workloads would improve coverage before making broad performance claims.
