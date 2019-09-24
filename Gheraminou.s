.name "Geral De Riv"
.comment "Le sorceleur est en ville"

sti	r1, %:aard,%1
sti r1, %:igni,%1
sti r1, %:zork,%1
st r3,-10
st r3,-20
st r3,-33
ld %0,r13
aard: live %1
fork %:igni
#zjmp %:aard

igni: live %1
fork %:zork
ld 9, r2
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500
st  r2,-500


#zjmp %666
st	r1,-500
zjmp %:igni

zork: live %1
zjmp %:zork
