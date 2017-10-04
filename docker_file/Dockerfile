FROM ubuntu:16.04

RUN apt-get update && apt-get -y upgrade
RUN apt-get -y install build-essential
RUN apt-get -y install git wget curl

RUN apt-get -y install language-pack-ja
RUN echo "export LANG=ja_JP.UTF-8" >> ~/.bashrc
RUN update-locale LANG=ja_JP.UTF-8 LANGUAGE=”ja_JP:ja”

RUN apt-get -y install libsvm-dev libicu-dev libmecab-dev mecab-ipadic-utf8 pkg-config 

WORKDIR /var/tmp
RUN echo ''
RUN git clone https://github.com/atlimited/resembla.git

WORKDIR resembla/src
RUN make
RUN make install

WORKDIR executable
RUN make
RUN make install
RUN ldconfig

RUN apt-get -y install unzip
WORKDIR /var/tmp/resembla/misc/mecab_dic/unidic/
RUN ./install-unidic.sh

RUN apt-get -y install mecab file sudo
WORKDIR /var/tmp/resembla/misc/mecab_dic/mecab-unidic-neologd/
RUN ./install-mecab-unidic-neologd.sh

WORKDIR executable
