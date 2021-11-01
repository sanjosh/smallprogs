
# run in background

use -d

# publish ports

```
 -p [host_ip]:[host_port]:[container_port]
```

# bind, tmpfs and volume mounts

## create docker volume

Unlike a bind mount, you can create and manage volumes outside the scope of any container.

```
docker volume create my-vol --driver
```

## create shared volume

```
docker volume create my-vol --driver vieux/sshfs
```

## tmpfs mount

```
--mount type=tmpfs,destination=/app 
```

## volume mount

write speed to a volume mount is far greater than the write speed within the container's filesystem

```
-v [/host/volume/location]:[/container/storage]
```

https://docs.docker.com/storage/volumes/

```
In general, --mount is more explicit and verbose. The biggest difference is that the -v syntax combines all the options together in one field, while the --mount syntax separates them.
```

# restart container

https://docs.docker.com/config/containers/start-containers-automatically/

# limit to one running container per image

by running using name 

```
docker run --name 
```

# privileged mode

# set PATH
 
```
docker -e "PATH=$(PATH)"
```

# ENTRYPOINT vs CMD vs nothing


# inspect

```
docker inspect devtest 
```

for images
```
docker image inspect
```

# replicas

```
docker service create -d --replicas=4 
```

# docker dir

```
/var/lib/docker (overlay2)
```

# CI/CD and github actions

https://docs.docker.com/ci-cd/github-actions/

# multi-stage build


https://docs.docker.com/develop/develop-images/multistage-build/

each line adds a layer

earlier pattern : concat multiple RUN into one line

new pattern : use multiple FROM to create new stages

can give name to each stage `FROM image AS <name>`
