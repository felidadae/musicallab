import numpy as np
from scipy.io.wavfile import write
from spectrum import *
import matplotlib.pyplot as plt
import math
import sys

length = 10
Nsample = 44100*5
step = 1.0/44100.0

# data = np.random.uniform(-1, 1, 44100) # 44100 random samples between -1 and 1

x = np.arange(0, Nsample*step, step)
# print x
# sys.exit()

sinX = 3 * np.sin( 200*2*math.pi*x ) #+ 1 * np.sin( 300*2*math.pi*x ) + 0.3 * np.sin( 400*2*math.pi*x )

AnalyzeFourier = 0
if AnalyzeFourier == 1:
	p = Periodogram(sinX, sampling=Nsample)
	p.run()
	fig = plt.figure()
	ax = fig.add_subplot (221)
	ax1 = fig.add_subplot(222)
	ax2 = fig.add_subplot(223)
	ax3 = fig.add_subplot(224)
	#----
	p.plot(marker='o',ax=ax) 
	p.plot(marker='o',ax=ax1) 
	ax2.plot(sinX)
	ax3.plot(sinX,'r')
	ax1.set_xlim(150, 250)
	ax1.set_ylim(-20, 20)
	ax.legend(['Periodigram']);
	plt.show()

MyAnalyzeFourier = 0
if MyAnalyzeFourier == 1:
	dft_data = np.abs(np.fft.rfft(sinX))
	plt.plot(dft_data)
	plt.show()




# dft_data = np.fft.fft(sinX)
# plt.plot(dft_data)
# plt.show()


# import ipdb; ipdb.set_trace()

# plt.plot(sinX)
# plt.show()

# plt.plot(dft_data)
# plt.show()

# scount, bins, ignored = plt.hist(data, 15, normed=True)
# plt.plot(bins, np.ones_like(bins), linewidth=2, color='r')
# plt.show()


scaled = np.int16(sinX/np.max(np.abs(sinX)/4) * 32767)
write('test.wav', 44100, scaled)