# build

```
docker build --tag python-docker
```

# with CMD

```
CMD [ "python3", "-m" , "flask", "run", "--host=0.0.0.0"]

docker run --name singleton python-docker
```

# without CMD or ENTRYPOINT

```
docker run -it python-docker /bin/bash -c "python -m flask run --host=0.0.0.0"
```

