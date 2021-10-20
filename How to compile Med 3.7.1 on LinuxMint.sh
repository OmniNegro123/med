sudo apt-get install -y cxxtest git build-essential cmake qt5-default qtscript5-dev libssl-dev qttools5-dev qttools5-dev-tools qtmultimedia5-dev libqt5svg5-dev libqt5webkit5-dev libsdl2-dev libasound2 libxmu-dev libxi-dev freeglut3-dev libasound2-dev libjack-jackd2-dev libxrandr-dev libqt5xmlpatterns5-dev libqt5xmlpatterns5 libreadline6-dev libjsoncpp-dev libicu-dev
mkdir build
cmake ../
make
cd ui
cp ./*.* ../build
