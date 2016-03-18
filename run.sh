clear
echo "Running Makefile, cleaning .o's and running map 42.fdf"
make clean
make all
echo "RUNNING..."
sleep 0.7
./fdf ./maps/42.fdf
