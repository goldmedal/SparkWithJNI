#/bin/shell
g++ -shared -O3 \
    -g \
    -I /usr/include \
    -I $JAVA_HOME/include \
    -I $JAVA_HOME/include/linux \
    -fPIC \
    Data2Hex.cpp -o libData2Hex.so
