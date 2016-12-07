import numpy as np
import math

#			0		 1		  2		  3		  4 	  5       6     ...
HEADER = "timeIndex	noteX	noteY	Action	Param1	Param2	Param3	..."
PARAMS_N = 2
AN_ATTACK =0	#AN == ActionName
AN_RELEASE=1
AN_BEND   =2


#------------------------------------------------------------------------------
def generateSample1(tB, tDelta, noteX, noteY):
	rowN = tDelta
	
	myEvents = np.zeros(shape=(rowN, 4+PARAMS_N))
	myEvents[:, 1:4] = np.matrix([[noteX,noteY,AN_BEND]])
	
	myEvents[:, 0] = range(tB, tB+tDelta)
	
	start 	= 0 
	step 	= 0.1
	###
	myEvents[:, 4] = np.arange(start, start + step * tDelta,  step )
	myEvents[:, 5] = np.arange(start, start + step * tDelta,  step )
	###
	myEvents[:, 4] = np.sin(myEvents[:, 4])
	myEvents[:, 5] = np.sin(myEvents[:, 5])

	#START END
	myEvents[0,      0:4] = np.matrix([[tB,        noteX, noteY, AN_ATTACK]])
	myEvents[rowN-1, 0:4] = np.matrix([[tB+tDelta, noteX, noteY, AN_ATTACK]])

	return myEvents
#------------------------------------------------------------------------------



myEvents = generateSample1(tB=30, tDelta=80, noteX=3, noteY=3)
# myEvents2= generateSample1(tB=90, tDelta=80, noteX=2, noteY=2)

# alla = np.concatenate( (myEvents, myEvents2) )
# alla = alla[alla[:,0].argsort()]

np.savetxt(
	"kaka.tsv", 
	myEvents, 
	delimiter="\t", 
	fmt="%.0f\t%.0f\t%.0f\t%.0f\t%.2f\t%.2f",
	header=HEADER
)