#!/bin/bash

imageName="gtcs2110/tl4-spring19:latest"

docker -v >/dev/null

dockerExists=$?

if  [ $dockerExists != 0 ]; then
    echo ERROR: Please install Docker before running this script. Refer to the CS 2110 Docker Guide.
    exit
fi

docker container ls >/dev/null
dockerNotRunning=$?

if [ $dockerNotRunning != 0 ]; then
    echo ERROR: Docker is not currently running. Please start Docker before running this script.
    exit
fi

docker pull $imageName
docker run --rm -it -v "$(pwd)":/autograder/submission/ $imageName /bin/sh -c '/autograder/run_local'
