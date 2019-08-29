# the base image to use
FROM kylef/swiftenv

# copy all files from folder root into image
COPY . .

# this will be run when building the image
RUN swiftenv install 5.1-DEVELOPMENT-SNAPSHOT-2019-08-26-a
RUN swift build

# this will be called when executing the image as container
CMD swift test
