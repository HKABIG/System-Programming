macro ABC &a, &b
load &a 
add &b 
mend 
macro XYZ &a, &b, &c 
load x
add &a 
sub &b 
mult y
store &c 
mend 
.code 
ABC 7, 4
XYZ 9, 10, 11
XYZ 3, 4, 5
endp