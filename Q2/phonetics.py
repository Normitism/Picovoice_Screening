from typing import Sequence
from collections import defaultdict
from time import perf_counter

pron_dict = {
   "ABACUS": [["AE", "B", "AH", "K", "AH", "S"]],
   "BOOK": [["B", "UH", "K"]],
   "THEIR": [["DH", "EH", "R"]],
   "THERE": [["DH", "EH", "R"]],
   "TOMATO": [["T", "AH", "M", "AA", "T", "OW"], ["T", "AH", "M", "EY", "T", "OW"]]
}


pron_to_word = defaultdict(list)

#invert dict
for key, val in pron_dict.items():
    for pron in val:
        pron_to_word[tuple(pron)].append(key)

def find_word_combos_with_pronunciation(phonemes: Sequence[str]) -> Sequence[Sequence[str]]: 
    # use memoization to prevent the recalculations of permutations
    cache = {}
    def dfs(start):
        if start in cache:
            return cache[start]
        if start == len(phonemes):
            return [[]]
        res = []
        # create a moving window to find all possible sequences
        for end in range(start + 1, len(phonemes) + 1):
            window = tuple(phonemes[start:end])
            words = pron_to_word.get(window, [])
            for word in words:
                # find the rest of the combinations for a given word
                for i in dfs(end):
                    res.append([word] + i)
        cache[start] = res.copy()
        return res
    return dfs(0)

