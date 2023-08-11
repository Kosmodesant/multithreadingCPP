FROM ubuntu:16.04

RUN apt-get update && apt-get install -y g++ clang nano net-tools inetutils-ping

WORKDIR /root/task2/

COPY task2v2.cpp  .

COPY task2.cpp  .

RUN g++ -std=c++14 task2v2.cpp -o task2v2

RUN clang -pthread -std=c++14 task2.cpp -o task2

CMD ["./task2v2"]


ENTRYPOINT [ "./task2" ]