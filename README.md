# SlaSimHash

## Psuedocode

### 1. Convert Input String to Bits
- Turn each character of the input string into its binary representation.
- Collect all bits into a list.

### 2. Compute Weighted Numbers
- Group bits into chunks of 8.
- For each chunk, calculate a number based on bit positions and scale it by its chunk index.
- Collect all these numbers.
- Calculate their sum and call it (`total`).

### 3. XOR Reduction
- Start with the first 4 bits from the bit list from step 1.
- For each following 4 bits, XOR it with the current results.
- Convert the last 4 bits into a number called (`xor_numerical_value`).

### 4. Compute Offset
- Calculate `total^xor_numerical_value (mod 2^8)`

### 5. Build Partial Hashes (8 Times)
- Split the bit list into 8 sections (one per loop).
- For each section:
  - Count how many zeros and ones it has.
  - Perform a sequence of calculations:
      - Initialize `partial_numerical_hash` equal to one.
      - Multiply it by `(zero_count + total + 10 + last digit of partial_numerical_hash)`.
      - If `partial_numerical_hash` is a multiple of `2^32`, subtract one from `partial_numerical_hash`.
      - Calculate `partial_numerical_hash (mod 2^32)`.
      - Convert the result into hexadecimal.
      - Append it to the final hash string.

### 6. Return Final Hash String
- Combine all partial hashes to produce the final hash.

---

## Testing

### Time testing
- The test conducted with file `konstitucija.txt` concluded, that increasing the input does not significantly effect the runtime of the hashing algorithm. The complexity seems to be O(`n log(n)`).
<img width="886" height="523" alt="image" src="https://github.com/user-attachments/assets/ec42f629-7ccf-40f4-bb7b-241912396572" />

### Collision testing
- Tests with 100k pairs of strings length 10, 100, 500 and 1000 all did not yield any collisions.

### Avalanche testing
- Tests with 100k pairs of strings length 10 yielded such results for hashes:
    - Max similarity (hex): 39.0625%
    - Min similarity (hex): 0%
    - Average similarity (hex): 6.72661%
    - Max similarity (bin): 78.125%
    - Min similarity (bin): 25%
    - Average similarity (bin): 52.4543%

