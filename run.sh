rm log.txt
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make clean
make
# ./main.out "../ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb"
# ./main.out "../ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb"
# ./main.out "../ROMS/04-op r,imm.gb.gb"
# ./main.out "../ROMS/01-special.gb" - passed V
# ./main.out "../ROMS/02-interrupts.gb" - implement interruprs
# ./main.out "../ROMS/03-op sp,hl.gb" - passed V
#./main.out "../ROMS/04-op r,imm.gb" # - failed DE
# ./main.out "../ROMS/05-op rp.gb" - passed V
# ./main.out "../ROMS/06-ld r,r.gb" -- passed V
# ./main.out "../ROMS/07-jr,jp,call,ret,rst.gb" -- passed V
# ./main.out "../ROMS/08-misc instrs.gb"
# ./main.out "../ROMS/09-op r,r.gb"
# ./main.out "../ROMS/10-bit ops.gb"
./main.out "../ROMS/tetris.gb"