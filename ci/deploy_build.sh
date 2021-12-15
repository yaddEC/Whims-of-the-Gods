#!/bin/bash

# show environment variables
set
set -x

echo "deploying to server, please be patient..."

base_file_name=$1
deployed_files=()

echo $base_file_name

mkdir -p $base_file_name

# add correct files for the type of build requested
if [ $base_file_name == 'linux_build' ] 
then
	cp -r tower assets/ $base_file_name
	zip -r $base_file_name.zip $base_file_name
	deployed_files+=($base_file_name.zip)
elif [ $base_file_name == 'windows_build' ] 
then
	cp -r tower.exe assets/ $base_file_name
	zip -r $base_file_name.zip $base_file_name
	deployed_files+=($base_file_name.zip)
elif [ $base_file_name == 'emscripten_build' ] 
then
	cp -r tower.js tower.html tower.data tower.wasm $base_file_name
	deployed_files+=($base_file_name)
fi

# print our contents of files added 
echo ${deployed_files[*]}

# deploy zip to deploy folder
deploy_folder=~/public_html/testdir/Caprice_Des_Dieux_${CI_COMMIT_TIMESTAMP:-no_date}_${CI_COMMIT_SHORT_SHA:-no_hash}

mkdir -p $deploy_folder

cp -r ${deployed_files[*]} $deploy_folder
