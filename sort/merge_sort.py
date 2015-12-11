def merge_sort(arr):
    n = len(arr)
    if(n <= 1):
        return arr

    left = merge_sort(arr[:n/2])
    right = merge_sort(arr[n/2:])
    
    idl = 0
    idr = 0
    ret = []
    while(idl < len(left) and idr < len(right)):
        if(left[idl] <= right[idr]):
            ret.append(left[idl])
            idl += 1
        else:
            ret.append(right[idr])
            idr += 1
    
    ret += left[idl:] + right[idr:]
    return ret 
                    

e = [9,8,7,6,5,4,3,2,1]

print merge_sort(e)
