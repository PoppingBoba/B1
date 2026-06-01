echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "     B1 Build Script         "
echo ""
echo " Wrriten by Nakada Tokumei    "
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

make LLVM=/usr/lib/llvm-20/bin/ GENERATE_COMPILE_DB=1 pc-x86-64-test -j$(nproc)
