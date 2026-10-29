# Contributing

Thanks for helping improve the Low-Latency Limit Order Book & Matching Engine.

## Before opening a pull request

1. Keep changes focused and explain the problem they solve.
2. Preserve deterministic matching behavior and price-time priority.
3. Add or update tests when changing engine behavior, order-book operations, or queue semantics.
4. For performance changes, compare the same workload, compiler, build mode, and machine; include raw results rather than only the best number.
5. Update the README or `docs/BENCHMARKING.md` when commands, supported workloads, or benchmark interpretation change.

## Build and test locally

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```

If changing concurrency or memory-sensitive code, also run the repository's Debug sanitizer test configuration used by CI.

## Pull request checklist

- [ ] The change has a clear, scoped purpose.
- [ ] Relevant tests pass locally or any limitation is explained.
- [ ] Documentation reflects user-visible behavior and commands.
- [ ] Performance claims include workload and environment context.
- [ ] No generated build artifacts or machine-specific output are committed.

This is an educational project, not production exchange infrastructure. Contributions should not imply production readiness without the corresponding engineering work and evidence.
