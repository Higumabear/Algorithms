#バグありぽい
def multikey_qsort(arr, idx = 0):
	if not arr:
		return []
	
	pivot = arr[0]
	left = []
	center = []
	right = []
	
	for i in xrange(len(arr)):
		if(arr[i][idx] < pivot[idx]):
			left.append(arr[i])
		elif(arr[i][idx] > pivot[idx]):
			right.append(arr[i])
		else:
			center.append(arr[i])
	
	if(len(center) >= 2):
		center = multikey_qsort(center, idx + 1)
		
	return multikey_qsort(left, idx) + center + multikey_qsort(right, idx)

seq = ['ofjg','ahefherkrfj','aefjerof','hdfriheri'
		,'efjoer','jkgh','lihgf','etrujg','yeuvero']
print multikey_qsort(seq)