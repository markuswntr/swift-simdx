FROM swift:5.1
COPY . .
RUN swift build -c release
CMD swift test -c release
