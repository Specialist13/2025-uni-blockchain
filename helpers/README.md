# String Pair Generator

Generates random pairs of strings where each pair differs by exactly one character. Useful for testing hash function avalanche effects.

## Usage

### Basic Usage
```cpp
#include "helpers/string_pair_generator.h"

// Generate 100,000 pairs of length 10 (defaults)
helpers::generate_string_pairs(100000, 10);
```

### Advanced Usage
```cpp
#include "helpers/string_pair_generator.h"

helpers::StringPairGeneratorOptions options;
options.pairCount = 50000;
options.stringLength = 16;
options.alphabet = "abcdefghijklmnopqrstuvwxyz";
options.seed = 12345; // 0 = random seed
options.outputDirectory = "my_test_data";

helpers::generate_string_pairs(options);
```

## Output

Files are written to `input_files/avalanche/` by default:
- `pair_0_a.txt` and `pair_0_b.txt`
- `pair_1_a.txt` and `pair_1_b.txt`
- ...

Each pair contains two strings that differ by exactly one character at a random position.

## Options

- `pairCount`: Number of string pairs to generate (default: 100,000)
- `stringLength`: Length of each string (default: 10)
- `alphabet`: Character set to use (default: alphanumeric)
- `seed`: Random seed, 0 for non-deterministic (default: 0)
- `outputDirectory`: Where to write files (default: "input_files/avalanche")
