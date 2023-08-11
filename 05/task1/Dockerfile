FROM ubuntu:16.04
	RUN apt-get update && apt-get install -y g++ mc net-tools build-essential
	WORKDIR /root/hello/
	COPY task1.cpp .
	RUN g++ -o hello task1.cpp
	CMD ["./hello"]	