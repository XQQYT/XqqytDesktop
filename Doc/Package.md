## Build Release Package

1. Enter the project directory:
```bash
cd XqqytDesktop
```
2. Prepare the executable file:
```bash
cd build
cmake ..
make -j$(nproc)
```
3. Run the packaging script:
```bash
cd ../
bash Scripts/package/package_release.sh build/XqqytDesktop Output_path Your_Qt_Path
# Example
# bash Scripts/package/package_release.sh build/XqqytDesktop release_package /opt/Qt5.14.2/5.14.2/gcc_64 
```
4. Output:
The release package will be generated in the <output_path> you specified in the command.