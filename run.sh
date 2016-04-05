clear
echo "Running Makefile, cleaning .o's and running map 42.fdf"
make clean
make all
./fdf 1by1.fdf
exit
./fdf ./maps/42.fdf
