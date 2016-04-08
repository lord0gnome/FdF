clear
echo "Running Makefile, cleaning .o's and running map 42.fdf"
make clean
make all
./fdf maps/42_10height.fdf
exit
./fdf ./maps/42.fdf
