# syntax=docker/dockerfile:1

# https://docs.docker.com/language/python/build-images/

FROM python:3.7.3-stretch

WORKDIR /app

RUN pip install --upgrade pip

COPY requirements.txt requirements.txt

RUN pip3 install -r requirements.txt

COPY . .

# EXPOSE port purely for documentation

# ENV
# https://docs.docker.com/engine/reference/builder/#env
ENV PATH="/app:${PATH}"

# ENTRYPOINT
# CMD [ "python3", "-m" , "flask", "run", "--host=0.0.0.0"]

