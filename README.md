Onyx is a minimax-based engine for Splendor, compatible with the specifications at [splendor-tools](https://github.com/nerdvana-ro/splendor-tools/).

## Installation

```bash
git clone https://github.com/CatalinFrancu/onyx
cd onyx/build
cmake ..
make
```

## Configuration

You can change values in `include/Config.h`. In particular, `STRATEGY` can be `STRAT_MCTS` or `STRAT_MINIMAX`. For Monte Carlo Tree Search, `MILLISECONDS_PER_MOVE` controls the time limit. For Minimax, `MINIMAX_DEPTH` controls the depth.

You can take a look at `include/Constants.h`, where you can tweak some more values pertaining to the MCTS algorithm.
