FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -o contactbook contacts.cpp

CMD ["./contactbook"]

