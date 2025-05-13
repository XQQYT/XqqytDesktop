## Package Release tar.gz / deb
Note: Please check the version in settings-example.json before packaging.
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
3. Return to the project root:
```bash
cd ../
```

#### Package to tar.gz
4. Run the packaging script:
```bash
bash Scripts/package/package_release.sh build/XqqytDesktop Output_path Your_Qt_Path
# Example
# bash Scripts/package/generate_release_tar_gz.sh build/XqqytDesktop ~/release /opt/Qt5.14.2/5.14.2/gcc_64
```

#### Package to deb
4. Run the packaging script:
```bash
bash Scripts/package/package_release.sh build/XqqytDesktop Output_path Your_Qt_Path
# Example
# bash Scripts/package/generate_release_deb.sh build/XqqytDesktop ~/temp /opt/Qt5.14.2/5.14.2/gcc_64

```
5. Output:
The release package will be generated in the <output_path> you specified in the command.