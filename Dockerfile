FROM ubuntu:latest

ENV CC="/usr/bin/gcc-9"
ENV CXX="/usr/bin/g++-9"
ENV TZ="Europe/Budapest"

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install --no-install-recommends -y \
  gcc-9 \
  g++-9 \
  make \
  cppcheck \
  valgrind \
  doxygen \
  graphviz \
  libgtest-dev \
  cmake \
  git \
  ca-certificates \
  && cd /usr/src/gtest \
  && cmake CMakeLists.txt \
  && make \
  && ln -st /usr/lib/ /usr/src/gtest/libgtest.a \
  && ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a \
  && rm -rf /var/lib/apt/lists/*
