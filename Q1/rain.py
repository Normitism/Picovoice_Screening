from scipy.fft import fft, ifft
from typing import Sequence

def prob_rain_more_than_n(p: Sequence[float], n: int) -> float: 
    fft_p = []
    padding = [0]*(len(p) - 1)
    for probability in p:
        #convolute and apply fft and add padding
        fft_p.append(fft([1-probability, probability]+ padding))
    fft_total = fft_p[0]
    #pointwise multiplication of all ffts
    for i in fft_p[1:]:
        fft_total *= i
    return sum(ifft(fft_total).real[n+1:])

p = [0.2, 0.4, 0.7]
print(prob_rain_more_than_n(p,2))