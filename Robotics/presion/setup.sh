if [ -d "data" ]; then
	echo "data directory found correctly"
	zip_data_folder=true
else
	zip_data_folder=false
	while true; do
    read -p "data directory does not exist, do you want to continue? [Yy/Nn]" yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) echo "exit"; exit;;
        * ) echo "Please answer yes or no.";;
    esac
done
fi
if [ -d "include" ]; then
	echo "include directory found correctly"
	zip_include_folder=true
else
	zip_include_folder=false
	while true; do
    read -p "include directory does not exist, do you want to continue? [Yy/Nn]" yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) echo "exit"; exit;;
        * ) echo "Please answer yes or no.";;
    esac
done
fi
if [ -d "src" ]; then
	echo "src directory found correctly"
else
	echo "src directory does not exist"
	exit;
fi

if [ -d "build" ]; then
	echo "build directory found correctly"
else
	echo "build directory does not exist"
	exit;
fi


if [ -f "CMakeLists.txt" ]; then
	echo "CMakeLists file found correctly"
else
	echo "CMakeLists file does not exist"
	exit;
fi
echo "please write your student ID..."
read student_id
if [ ${#student_id} -ne 9 ]; then
	echo "student ID worng format"
	exit;
fi
if ${zip_data_folder} && ${zip_include_folder}; then
	zip -r ${student_id}.zip src CMakeLists.txt data include build
	echo "zip file was generated correctly"
	exit;
fi
if ${zip_data_folder}; then
	zip -r ${student_id}.zip src CMakeLists.txt data build
	echo "zip file was generated correctly"
	exit;
fi
if ${zip_include_folder}; then
	zip -r ${student_id}.zip src CMakeLists.txt include build
	echo "zip file was generated correctly"
	exit;
fi
zip -r ${student_id}.zip src CMakeLists.txt build
echo "zip file was generated correctly"
