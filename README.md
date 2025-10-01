# SlaSimHash

## Pseudocode

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

### Salted string demonstration
    Input: I bought pizza for 10,000 bitcoin!
    Generated salt: t658u66Hqz
    Hash without salt: d9c1c590c469dfb54e53f04ae3fd9535b8697dbcb8697dbcc31dde33e23b1367
    Hash with salt: d360055b69dcd0a3d360055bc1372c3084d87755cf4f8a38d360055be74a72a4

## Conclusion

### Strengths
- Avoids collisions
- Achieves the avalanche effect

### Weaknesses
- Not as time efficient
- Uses smaller numbers in calculations (`2^32, 2^8`) which could allow for more specific guesses and make dehashing easier.

---

# AI improved algorithm

## Testing

### Time testing
- The test conducted with file `konstitucija.txt` concluded, that increasing the input does not significantly effect the runtime of the hashing algorithm. The complexity seems to be O(`n log(n)`). It is slightly faster than the original.
<img width="886" height="523" alt="image" src="https://github.com/user-attachments/assets/81d262ad-881d-4e22-be2b-d6d02e0c4d7b" />

### Collision testing
- Tests with 100k pairs of strings length 10, 100, 500 and 1000 all did not yield any collisions. Same as the original.

### Avalanche testing
- Tests with 100k pairs of strings length 10 yielded such results for hashes:
    - Max similarity (hex): 23.4375%
    - Min similarity (hex): 0%
    - Average similarity (hex): 6.74216%
    - Max similarity (bin): 68.3594%
    - Min similarity (bin): 37.1094%
    - Average similarity (bin): 52.352%
- These are similar results as the original function, with the averages staying the same.

### Salted string demonstration
    Input: I bought pizza for 10,000 bitcoin!
    Generated salt: 7FumfFcrCQ
    Hash without salt: d9c1c590c469dfb54e53f04ae3fd9535b8697dbcb8697dbcc31dde33e23b1367
    Hash with salt: f6ae61c67a407160f6ae61c67e2f1983f401e35afe0ac3ddb651702c6ebc86f9

## Conclusion

- The AI improved algorithm yields same results as the original, whith slighly smaller computing duration.
- AI tried to improve the avalanche effect of the algorithm as well, but did not achieve better similarity results. However, they did eliminate the posibility for calculated guesses because of higher mixing (which could have been a problem in the original).

---

# Comparison (MD5/SHA-1/SHA-256)

### Time testing

- The new algorithms have a constant time whereas our algorithms do not. This makes them significantly faster than ours for larger inputs.
<img width="1333" height="882" alt="image" src="https://github.com/user-attachments/assets/e87df2a6-bdd1-4d75-a06b-761b88a709ae" />

### Collision testing
- Tests with 100k pairs of strings length 10, 100, 500 and 1000 all did not yield any collisions.

### Avalanche testing
- Tests with 100k pairs of strings length 10 yielded such results for hashes:
<img width="1328" height="896" alt="image" src="https://github.com/user-attachments/assets/849c7ebe-de0f-43ae-90ad-21428fa1eedb" />
- The most important metric (average similarity) of our algorithms and SHA-256 is identical, however MD5 and SHA-1 achieved smaller similarity, but that does not necessarily mean better hashing.

## Conclusion

- The only major disadvantage of our algorithms that tests detected was time complexity which becomes problematic with larger input.
- Other metrics seem similar across all algorithms.
- Our tests could not detect such aspects as difficulty to decrypt the hash, but it is likely that our hashes are much less safe.

---

# Comparison with colleagues

### Time testing
- The slowest hashes were PatrickHash and MonikaHash, whereas the fastest was NikitaHash.
<img width="1329" height="666" alt="image" src="https://github.com/user-attachments/assets/9dfb2f6c-5e9d-42c9-a61d-90ae044ede3f" />

### Collision testing

- NikitaHash had 4 collisions, PatrickHash had 15 collisions, the rest were zero.

### Avalanche testing

- All hashes achieved similar similarity ratings except MonikaHash, which was much more similar.
<img width="1330" height="557" alt="image" src="https://github.com/user-attachments/assets/be5c4f0a-7cd7-4174-a885-30666cf84efb" />

## Conclusion

- NikitaHash and PatrickHash are not really reliable because of multiple collisions.
- MonikaHash had an unreliable avalanche effect.
- Overall, the best hash in terms of time, collisions and avalanche effect was MatrixHash (Arnas Matuolis and Justinas Letukas).
- Our tests could not determine the safety and complexity of these hashes.
