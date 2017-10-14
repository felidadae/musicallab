import matplotlib.pyplot as plt
from spectrum import *
data = data_cosine(N=1024, A=0.1, sampling=1024, freq=200)
import ipdb; ipdb.set_trace()

p = Periodogram(data, sampling=1024)
p.run()

fig = plt.figure()
# fig.subplots_adjust(right=1.5)
# fig.subplots_adjust(top=1.5)
ax = fig.add_subplot(221)
ax1 = fig.add_subplot(222)
ax2 = fig.add_subplot(223)
ax3 = fig.add_subplot(224)

p.plot(marker='o',ax=ax) 
p.plot(marker='o',ax=ax1) 
ax2.plot(data)
ax3.plot(data,'r')
ax1.set_xlim(150, 250)
ax1.set_ylim(-20, 20)
ax.legend(['Periodigram']);
plt.show()