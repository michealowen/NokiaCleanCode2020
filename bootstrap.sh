#!/usr/bin/env bash
docker_cmd=$(which docker)
if echo "$docker_cmd" | grep "not found"; then
    echo -e "Please install docker firstly!"
    exit 1
fi

if sudo ${docker_cmd} images | grep -q "nsbboamfh/cppdev"; then
    echo "Docker image has been pulled locally"
else
    echo "Pulling docker image from dockerhub..."
    sudo docker pull nsbboamfh/cppdev:latest
fi

echo "Entering docker environment, your source will be mounted to /ccc2020/..."
sudo docker run -v $(pwd)/:/ccc2020/ -it nsbboamfh/cppdev /bin/bash