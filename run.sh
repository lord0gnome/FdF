clear
echo "Running Makefile, cleaning .o's and running map 42.fdf"
make clean
make all
echo "RUNNING..."
./fdf ./maps/42.fdf
