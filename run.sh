mkdir -p build
cd build
cmake ..
make clean
make
# ./main.out "../ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb"
# ./main.out "../ROMS/Legend of Zelda, The - Link's Awakening (USA, Europe) (Rev 2).gb"
# ./main.out "../ROMS/04-op r,imm.gb.gb"
# ./main.out "../ROMS/01-special.gb"
# ./main.out "../ROMS/02-interrupts.gb"
./main.out "../ROMS/03-op sp,hl.gb"