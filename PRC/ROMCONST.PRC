print "\ncopy ROMCONST for simulation"

set map /read/code H'FF4000..H'FFffff
set map /read H'4000..H'ffff
move H'ff4000..H'FFFFFF,H'4000
