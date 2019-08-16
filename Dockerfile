# the base image to use
FROM swift:5.0

# copy all files from folder root into image
COPY . .

# this will be run when building the image
RUN swift build

# this will be called when executing the image as container
CMD swift test
